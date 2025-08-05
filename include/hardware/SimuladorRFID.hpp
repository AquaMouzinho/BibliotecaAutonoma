#pragma once
#include "SensorRFID.hpp"
#include "../repositorios/ArmarioRepository.hpp" 
#include <vector>
#include <string>
#include <functional>
#include <atomic>
#include <mutex>

class SimuladorRFID : public SensorRFID {
private:
    std::vector<std::string> tagsDetectadas;
    std::function<void(const std::string&)> callback;
    std::atomic<bool> monitorando;
    mutable std::mutex mtx;
    ArmarioRepository& armarioRepo;  // Referência ao repositório
    int armarioId;                   // ID do armário que este sensor monitora

public:
    // Recebe o repositório e o ID do armário no construtor
    SimuladorRFID(ArmarioRepository& repo, int armarioId) 
        : monitorando(false), armarioRepo(repo), armarioId(armarioId)  {
        carregarTagsDoArmario();  // Carrega as tags ao inicializar
    }

    // Carrega as tags presentes no armário
    void carregarTagsDoArmario() {
        std::lock_guard<std::mutex> lock(mtx);
        auto armario = armarioRepo.buscarPorId(armarioId);
        if (armario) {
            tagsDetectadas = armario->getLivros();  // Copia as tags do armário
        }
    }

    // Interface principal (mantida igual)
    void setCallbackLeitura(std::function<void(const std::string&)> cb) override {
        callback = cb;
    }

    std::vector<std::string> getTagsDetectadas() const override {
        std::lock_guard<std::mutex> lock(mtx);
        return tagsDetectadas;
    }

    void iniciarMonitoramento() override {
        monitorando = true;
    }

    void pararMonitoramento() override {
        monitorando = false;
    }

    // Métodos de simulação
    void simularLeitura(const std::string& tag) override {
        std::lock_guard<std::mutex> lock(mtx);
        if (std::find(tagsDetectadas.begin(), tagsDetectadas.end(), tag) == tagsDetectadas.end()) {
            tagsDetectadas.push_back(tag);

            std::cout << "Lendo tag: " << tag << std::endl;
            std::cout << "Tags detectadas: " << std::endl;
            for (auto& tag : tagsDetectadas)
                std::cout << tag << std::endl;

            // Atualiza o armário físico
            auto armario = armarioRepo.buscarPorId(armarioId);
            if (armario) {
                auto livros = armario->getLivros();
                if (std::find(livros.begin(), livros.end(), tag) == livros.end()) {
                    livros.push_back(tag);
                    armario->setLivros(livros);
                    armarioRepo.atualizarArmario(*armario);
                }
            }
            
            if (callback && monitorando) {
                callback(tag);
            }
        }
    }

    void simularRemocao(const std::string& tag) override {
        std::lock_guard<std::mutex> lock(mtx);
        tagsDetectadas.erase(std::remove(tagsDetectadas.begin(), tagsDetectadas.end(), tag), tagsDetectadas.end());

        std::cout << "Removendo tag: " << tag << std::endl;
        std::cout << "Tags detectadas: " << std::endl;
        for (auto& tag : tagsDetectadas){
            std::cout << tag << std::endl;
        }
        auto armario = armarioRepo.buscarPorId(armarioId);
        if (armario) {
            std::cout << "Armário encontrado" << std::endl;
            auto livros = armario->getLivros();
            livros.erase(std::remove(livros.begin(), livros.end(), tag), livros.end());
            armario->setLivros(livros);
            armarioRepo.atualizarArmario(*armario);
        }
    }

    void limparTags() override {
        std::lock_guard<std::mutex> lock(mtx);
        tagsDetectadas.clear();

        auto armario = armarioRepo.buscarPorId(armarioId);
        if (armario) {
            armario->setLivros({});
            armarioRepo.atualizarArmario(*armario);
        }
    }
};