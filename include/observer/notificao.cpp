#include "Notificador.hpp"
#include <iostream>

void Notificador::adicionarObservador(const std::string& rfid, Observer* obs) {
    observadores[rfid].push_back(obs);
}

void Notificador::notificarDoadorDeRetirada(Livro* livro) {
    std::string rfid = livro->getRFID();  // Assumindo que Livro tem getRFID()
    auto it = observadores.find(rfid);
    if (it != observadores.end()) {
        for (Observer* obs : it->second) {
            obs->atualizar(rfid, "Livro retirado");
        }
    }
}

void Notificador::notificarDoadorDeDevolucao(Livro* livro) {
    std::string rfid = livro->getRFID();
    auto it = observadores.find(rfid);
    if (it != observadores.end()) {
        for (Observer* obs : it->second) {
            obs->atualizar(rfid, "Livro devolvido");
        }
    }
}

void Notificador::notificarDevolucaoObrigatoria(Usuario* usuario, Livro* livro) {
    std::string rfid = livro->getRFID();
    std::cout << "[NOTIFICADOR] Usuário " << usuario->getNome() 
              << " deve devolver o livro com RFID: " << rfid << std::endl;

    auto it = observadores.find(rfid);
    if (it != observadores.end()) {
        for (Observer* obs : it->second) {
            obs->atualizar(rfid, "Devolução obrigatória solicitada");
        }
    }
}
