#ifndef PORTA_ABERTA_H
#define PORTA_ABERTA_H

#include "EstadoSessao.hpp"
#include "../entidades/Sessao.hpp"

class PortaAberta : public EstadoSessao
{
private:
    Sessao *context;
    int timer;

public:
    PortaAberta();

    void setContext(Sessao *context) override;
    bool autenticar(const std::string &matricula, const std::string &senha) override;
    void processarRFID(const std::vector<std::string> &tags) override;
    void lidarTimeout() override;
};

#endif // PORTA_ABERTA_H