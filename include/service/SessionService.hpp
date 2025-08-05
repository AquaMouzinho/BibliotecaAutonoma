#pragma once
#include "../model/Sessao.hpp"
#include "../repositorios/SessaoRepository.hpp"
#include "../service/AutenticacaoService.hpp"
#include "../hardware/SensorPorta.hpp"
#include "../hardware/TrancaDigital.hpp"
#include <memory>
#include <thread>
#include <atomic>
#include <chrono>

class SessionService {
private:
    // Dependências
    SessaoRepository* sessaoRepo;
    AutenticacaoService* authService;
    SensorPorta* sensorPorta;
    TrancaDigital* trancaDigital;

    // Controle de sessão
    std::atomic<bool> sessionActive;
    std::atomic<bool> monitoring;
    std::thread monitorThread;
    Sessao* currentSession;

    // Controle de timeout
    std::chrono::steady_clock::time_point lastActivity;
    std::chrono::seconds timeoutDuration;

    void monitorSession();
    void closeSession();

public:
    SessionService(SessaoRepository* sessaoRepo,
                 AutenticacaoService* authService,
                 SensorPorta* sensorPorta,
                 TrancaDigital* trancaDigital);
    ~SessionService();

    // Controle de sessão
    bool iniciarSessaoFisica(int armario_id, const std::string& matricula, const std::string& senha);
    bool iniciarSessaoWeb(const std::string& matricula, const std::string& senha);
    bool encerrarSessao();

    // Controle de timeout
    void resetTimeout();
    void setTimeout(int segundos);

    // Status
    bool temSessaoAtiva() const;
    Sessao* getSessaoAtual() const;
    bool isPortaAberta() const;
    bool verificarTimeout() const;

};
