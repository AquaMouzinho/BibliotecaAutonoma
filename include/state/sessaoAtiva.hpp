#ifndef SESSAO_ATIVA_H
#define SESSAO_ATIVA_H

#include "EstadoSessao.h"
#include "Sessao.h"

class SessaoAtiva : public EstadoSessao {
private:
    Sessao* context;
    int timer;

public:
    SessaoAtiva();

    void setContext(Sessao* context) override;
    bool autenticar(const std::string& matricula, const std::string& senha) override;
    void processarRFID(const std::vector<std::string>& tags) override;
    void lidarTimeout() override;
};

#endif // SESSAO_ATIVA_H