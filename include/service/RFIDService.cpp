#include "RFIDService.hpp"
#include <iostream>

RFIDService::RFIDService(EmprestimoService* emprestimoService,
                       SessionService* sessionService, ArmarioService* armarioService ,SensorRFID* sensorRFID, SensorPorta* sensorPorta, int armarioIdAtual)
    : emprestimoService(emprestimoService),
      sessionService(sessionService), armarioService(armarioService), sensorRFID(sensorRFID), sensorPorta(sensorPorta), armarioIdAtual(armarioIdAtual) {
            sensorRFID->setCallbackLeitura(
                [this](const std::string& tag) {
                    this->processarTag(tag);
                }
            );
      }

void RFIDService::processarTag(const std::string& tagRFID) {
    if (!temSessaoFisicaAtiva()) {
        std::cout << "Nenhuma sessão ativa para processar tag" << std::endl;
        return;
    }

    if(!sessionService->isPortaAberta()){
        std::cout << "Porta não está aberta para processar tag" << std::endl;
        return;
    }

    armarioIdAtual = sessionService->getSessaoAtual()->getArmarioId();
    
    if (livroEstaNoArmario(tagRFID)) {
        //std::cout << "Emprestando livro: " << tagRFID << std::endl;
        sensorRFID->simularRemocao(tagRFID);
        armarioService->removerLivro(armarioIdAtual, tagRFID);
        std::string matricula = sessionService->getSessaoAtual()->getUsuarioMatricula();
        emprestimoService->emprestarLivro(matricula, tagRFID);
    } else {
        //std::cout << "Devolvendo livro: " << tagRFID << std::endl;
        sensorRFID->simularLeitura(tagRFID);
        armarioService->adicionarLivro(armarioIdAtual, tagRFID);
        emprestimoService->devolverLivro(tagRFID);
    }
}

bool RFIDService::temSessaoFisicaAtiva() const {
    return sessionService->temSessaoAtiva() && 
           sessionService->getSessaoAtual()->getTipo() == "fisica";
}

bool RFIDService::livroEstaNoArmario(const std::string& tagRFID) const {
    auto tags = sensorRFID->getTagsDetectadas();
    return std::find(tags.begin(), tags.end(), tagRFID) != tags.end();
}