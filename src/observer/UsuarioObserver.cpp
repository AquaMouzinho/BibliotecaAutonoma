#include "../../include/observer/UsuarioObservador.hpp"

UsuarioObservador::UsuarioObservador(Usuario *usuario) : usuario(usuario) {}

void UsuarioObservador::atualizar(const Notificacao &notificacao)
{
    usuario->adicionarNotificacao(new Notificacao(notificacao));
}