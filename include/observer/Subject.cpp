#include "Subject.hpp"

void Subject::adicionarObservador(Observador* observador) {
    observadores.push_back(observador);
}

void Subject::removerObservador(Observador* observador) {
    for (auto it = observadores.begin(); it != observadores.end(); ++it){
        if (*it == observador) {
            observadores.erase(it);
        }
    }
}

void Subject::notificarObservadores(const std::string& matricula, const std::string& mensagem) {
    for (auto* obs : observadores) {
        obs->atualizar(matricula, mensagem);
    }
}