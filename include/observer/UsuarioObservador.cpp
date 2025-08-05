#include "UsuarioObservador.hpp"
#include <iostream>

UsuarioObservador::UsuarioObservador(NotificacaoService* service)
    : notificacaoService(service) {}

void UsuarioObservador::atualizar(const std::string& matricula, const std::string& mensagem) {
    notificacaoService->notificar(matricula, mensagem);
}