#ifndef OBSERVADOR_H
#define OBSERVADOR_H

#include "../entidades/Notificacao.hpp"

class Observador
{
public:
  virtual ~Observador() = default;
  virtual void atualizar(const Notificacao &notificacao) = 0;
};

#endif // OBSERVADOR_H