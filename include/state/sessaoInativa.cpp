#include "SessaoInativa.h"
#include <iostream>

void SessaoInativa::setContext(Sessao* ctx) {
    context = ctx;
}

bool SessaoInativa::autenticar(const std::string& matricula, const std::string& senha) {
    std::cout << "Autenticando em SessaoInativa\n";
    return true; // Lógica de autenticação real seria aqui
}

void SessaoInativa::processarRFID(const std::vector<std::string>& tags) {
    // Não faz nada
}

void SessaoInativa::lidarTimeout() {
    std::cout << "Timeout em SessaoInativa\n";
}
