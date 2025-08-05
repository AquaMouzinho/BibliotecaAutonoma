#pragma once
#include "../service/SessionService.hpp"
#include "../service/RFIDService.hpp"
#include "../hardware/SimuladorArmario.hpp"
#include "../repositorios/LivroRepository.hpp"

#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

class HardwareSystemFacade {
private:
    SessionService& sessionService;
    RFIDService& rfidService;
    SimuladorArmario& hardwareSimulator;
    std::atomic<bool> emOperacao;

public:
    HardwareSystemFacade(SessionService& session, 
                        RFIDService& rfid,
                        SimuladorArmario& simulator)
        : sessionService(session), 
          rfidService(rfid),
          hardwareSimulator(simulator),
          emOperacao(false) {}

    // Controle de Sessão Física
    bool iniciarSessao(int armarioId, const std::string& matricula, const std::string& senha) {
        if (sessionService.temSessaoAtiva()) return false;

        bool sucesso = sessionService.iniciarSessaoFisica(armarioId, matricula, senha);
        if (sucesso) {
            std::cout << "Sessão iniciada com sucesso" << std::endl;
            hardwareSimulator.liberarTranca();
            emOperacao = true;
            monitorarOperacao();
        }
        return sucesso;
    }

    void encerrarSessao() {
        hardwareSimulator.trancar();
        sessionService.encerrarSessao();
        emOperacao = false;
    }

    // Monitoramento em Tempo Real
    void monitorarOperacao() {
        std::thread([this]() {
            while (emOperacao) {
                // Verifica timeout
                if (sessionService.verificarTimeout()) {
                    this->encerrarSessao();
                    break;
                }

                // Atualiza estado dos livros
                auto tags = hardwareSimulator.lerTags();
                for (const auto& tag : tags) {
                    rfidService.processarTag(tag);
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }).detach();
    }

    // Interface para o Sistema Físico
    std::vector<std::string> getLivrosPresentes() const {
        return hardwareSimulator.lerTags();
    }

    bool isTrancado() const {
        return hardwareSimulator.isTrancado();
    }

    bool isPortaAberta() const {
        return sessionService.isPortaAberta();
    }

    SimuladorArmario& getSimulador() { return hardwareSimulator; }
    SessionService& getSessionService() { return sessionService; }
};