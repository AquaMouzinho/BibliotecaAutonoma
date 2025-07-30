#include "Notificacao.h"
#include "Usuario.h"

Notificacao::Notificacao(int id, Usuario* usuario, const std::string& mensagem,
                         std::chrono::system_clock::time_point data)
    : id(id), usuario(usuario), mensagem(mensagem), data(data), lida(false) {}

void Notificacao::marcarComoLida() {
    lida = true;
}
