#ifndef SESSAO_INATIVA_H
#define SESSAO_INATIVA_H

#include "EstadoSessao.h"
#include "Sessao.h"

class SessaoInativa : public EstadoSessao {
private:
    Sessao* context;

public:
    void setContext(Sessao* context) override;
    bool autenticar(const std::string& matricula, const std::string& senha) override;
    void processarRFID(const std::vector<std::string>& tags) override;
    void lidarTimeout() override;
};

#endif // SESSAO_INATIVA_H