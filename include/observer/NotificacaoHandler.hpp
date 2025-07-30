// UsuarioObservador.h
#ifndef NOTIFICACAO_HANDLER_HPP
#define NOTIFICACAO_HANDLER_HPP

#include <vector>
#include "Observador.hpp"
#include "../entidades/Notificacao.hpp"

class NotificacaoHandler
{
private:
  std::vector<Observador *> observadores;

public:
  void adicionarObservador(Observador *o);
  void enviarNotificacao(const Notificacao &notificacao);
};

#endif // USUARIO_OBSERVADOR_H