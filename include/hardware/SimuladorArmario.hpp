#pragma once
#include "SimuladorTrancaDigital.hpp"
#include "SimuladorSensorPorta.hpp"
#include "SimuladorRFID.hpp"
#include <vector>

class SimuladorArmario {
private:
SimuladorTrancaDigital& tranca;
SimuladorSensorPorta& sensorPorta;
SimuladorRFID& sensorRFID;

public:
    SimuladorArmario(SimuladorTrancaDigital& t, SimuladorSensorPorta& s, SimuladorRFID& r)
        : tranca(t), sensorPorta(s), sensorRFID(r) {}

    void liberarTranca() { 
        tranca.liberar();
    }

    void abrirPorta() {
        sensorPorta.simularPortaAberta();
    }

    void fecharPorta() {
        sensorPorta.simularPortaFechada();
    }

    void trancar() {
        tranca.trancar();
    }

    bool isTrancado() const {
        return tranca.estaTrancada();
    }

    std::vector<std::string> lerTags() const {
        return sensorRFID.getTagsDetectadas();
    }

    void simularInsercaoLivro(const std::string& tag) {
        sensorRFID.simularLeitura(tag);
    }

    void simularRemocaoLivro(const std::string& tag) {
        sensorRFID.simularRemocao(tag);
    }
};