#include "../../include/state/SessaoAtiva.hpp"
#include <iostream>

SessaoAtiva::SessaoAtiva() : context(nullptr), timer(0) {}

void SessaoAtiva::setContext(Sessao *ctx)
{
    context = ctx;
}

bool SessaoAtiva::autenticar(const std::string &matricula, const std::string &senha)
{
    return false;
}

void SessaoAtiva::processarRFID(const std::vector<std::string> &tags)
{
    std::cout << "Processando RFID em SessaoAtiva\n";
}

void SessaoAtiva::lidarTimeout()
{
    std::cout << "Timeout em SessaoAtiva\n";
}