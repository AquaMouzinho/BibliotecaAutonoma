#include "SessionService.hpp"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>

using namespace std;
using namespace std::chrono;

SessionService::SessionService(SessaoRepository* sessaoRepo,
                             AutenticacaoService* authService,
                             SensorPorta* sensorPorta,
                             TrancaDigital* trancaDigital)
    : sessaoRepo(sessaoRepo), authService(authService),
      sensorPorta(sensorPorta), trancaDigital(trancaDigital),
      sessionActive(false), monitoring(true),
      currentSession(nullptr), timeoutDuration(30s) {
    monitorThread = thread(&SessionService::monitorSession, this);
}

SessionService::~SessionService() {
    monitoring = false;
    if (monitorThread.joinable()) {
        monitorThread.join();
    }
    delete currentSession;
}

void SessionService::monitorSession() {
    while (monitoring) {
        if (sessionActive) {
            // Verifica timeout apenas se a porta estiver fechada
            if (!sensorPorta->isPortaAberta()) {
                auto now = steady_clock::now();
                if (now - lastActivity > timeoutDuration) {
                    cout << "Timeout de inatividade atingido (30s com porta fechada)" << endl;
                    closeSession();
                }
            }
        }
        this_thread::sleep_for(seconds(1));
    }
}

void SessionService::closeSession() {
    if (currentSession) {
        // Atualiza dados da sessão
        time_t now = time(nullptr);
        tm* localTime = localtime(&now);
        ostringstream oss;
        oss << put_time(localTime, "%Y-%m-%d %H:%M:%S");

        currentSession->setDataFechamento(oss.str());
        currentSession->setAtiva(false);
        sessaoRepo->atualizarSessao(*currentSession);

        // Tranca o armário se for sessão física
        if (currentSession->getTipo() == "fisica") {
            trancaDigital->trancar();
        }

        delete currentSession;
        currentSession = nullptr;
    }
    sessionActive = false;
}

bool SessionService::iniciarSessaoFisica(int armario_id, const string& matricula, const string& senha) {
    if (sessionActive) return false;

    // Autenticação
    Usuario* usuario = authService->autenticar(matricula, senha);
    if (!usuario || authService->verificarAtrasos(matricula)) {
        return false;
    }

    // Cria nova sessão
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);
    ostringstream oss;
    oss << put_time(localTime, "%Y-%m-%d %H:%M:%S");

    Sessao novaSessao(0, armario_id, matricula, "fisica", 
                     oss.str(), "", true, 30);

    if (sessaoRepo->criarSessao(novaSessao)) {
        currentSession = sessaoRepo->buscarSessaoAtivaPorUsuario(matricula);
        sessionActive = true;
        resetTimeout();
        trancaDigital->liberar();
        return true;
    }
    return false;
}

bool SessionService::iniciarSessaoWeb(const string& matricula, const string& senha) {
    if (sessionActive) return false;

    // Autenticação
    Usuario* usuario = authService->autenticar(matricula, senha);
    if (!usuario) {
        return false;
    }

    // Cria nova sessão
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);
    ostringstream oss;
    oss << put_time(localTime, "%Y-%m-%d %H:%M:%S");

    Sessao novaSessao(0, 0, matricula, "web", 
                     oss.str(), "", true, 0);

    if (sessaoRepo->criarSessao(novaSessao)) {
        currentSession = sessaoRepo->buscarSessaoAtivaPorUsuario(matricula);
        sessionActive = true;
        return true;
    }
    return false;
}

bool SessionService::encerrarSessao() {
    if (!sessionActive) return false;
    closeSession();
    return true;
}

void SessionService::resetTimeout() {
    lastActivity = steady_clock::now();
}

void SessionService::setTimeout(int segundos) {
    timeoutDuration = seconds(segundos);
}

bool SessionService::temSessaoAtiva() const {
    return sessionActive;
}

Sessao* SessionService::getSessaoAtual() const {
    return currentSession;
}

bool SessionService::isPortaAberta() const {
    return sensorPorta->isPortaAberta();
}

bool SessionService::verificarTimeout() const {
    if (!sessionActive) 
        return false;
    else return true;
}