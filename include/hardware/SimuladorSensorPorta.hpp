// SimuladorSensorPorta.hpp
#pragma once
#include "../hardware/SensorPorta.hpp"
#include <atomic>

class SimuladorSensorPorta : public SensorPorta {
private:
    std::atomic<bool> portaAberta;
    int armarioId;

public:
    SimuladorSensorPorta(int armarioId) : portaAberta(false), armarioId(armarioId) {};

    bool isPortaAberta() const override { return portaAberta; }
    int getArmarioId() const override { return armarioId; }

    void simularPortaAberta() { portaAberta = true; }
    void simularPortaFechada() { portaAberta = false; }
};
