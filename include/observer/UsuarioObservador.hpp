// UsuarioObservador.h
#ifndef USUARIO_OBSERVADOR_H
#define USUARIO_OBSERVADOR_H

#include "Observador.hpp"
#include "../entidades/Usuario.hpp"

class UsuarioObservador : public Observador
{
private:
  Usuario *usuario;

public:
  UsuarioObservador(Usuario *usuario);
  void atualizar(const Notificacao &notificacao) override;
};

#endif // USUARIO_OBSERVADOR_H