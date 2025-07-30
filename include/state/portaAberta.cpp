#include "PortaAberta.h"
#include <iostream>

PortaAberta::PortaAberta() : context(nullptr), timer(0) {}

void PortaAberta::setContext(Sessao* ctx) {
    context = ctx;
}

bool PortaAberta::autenticar(const std::string& matricula, const std::string& senha) {
    return false;
}

void PortaAberta::processarRFID(const std::vector<std::string>& tags) {
    std::cout << "Processando RFID em PortaAberta\n";
}

void PortaAberta::lidarTimeout() {
    std::cout << "Timeout em PortaAberta\n";
}
