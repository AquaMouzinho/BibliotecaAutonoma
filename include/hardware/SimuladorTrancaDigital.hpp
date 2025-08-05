// SimuladorTrancaDigital.hpp
#pragma once
#include "../hardware/TrancaDigital.hpp"
#include <atomic>

class SimuladorTrancaDigital : public TrancaDigital {
private:
    std::atomic<bool> trancada;
    int armarioId;

public:
    SimuladorTrancaDigital(int armarioId) : trancada(true), armarioId(armarioId) {};

    void liberar() override { trancada = false; }
    void trancar() override { trancada = true; }
    bool estaTrancada() const override { return trancada; }
    int getArmarioId() const override { return armarioId; }
};