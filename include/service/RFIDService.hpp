#pragma once
#include "../repositorios/LivroRepository.hpp"
#include "../service/EmprestimoService.hpp"
#include "../service/SessionService.hpp"
#include "../service/ArmarioService.hpp"
#include "../hardware/SensorRFID.hpp"
#include "../hardware/SensorPorta.hpp"
#include <string>

class RFIDService {
private:
    EmprestimoService* emprestimoService;
    SessionService* sessionService;
    ArmarioService* armarioService;
    SensorRFID* sensorRFID;
    SensorPorta* sensorPorta;
    int armarioIdAtual;

public:
    RFIDService(EmprestimoService* emprestimoService, 
               SessionService* sessionService, ArmarioService* armarioService, SensorRFID* sensorRFID, SensorPorta* sensorPorta, int armarioIdAtual);

    void processarTag(const std::string& tagRFID);
    bool livroEstaNoArmario(const std::string& tagRFID) const;

    bool temSessaoFisicaAtiva() const;
    bool isPortaAberta() const { return sensorPorta->isPortaAberta(); }
};