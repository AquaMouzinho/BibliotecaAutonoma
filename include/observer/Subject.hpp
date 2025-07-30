#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include <string>
#include "Observador.hpp"
#include "../entidades/Notificacao.hpp"

class Subject
{
public:
  virtual void registrarObservador(Observador *o) = 0;
  virtual void notificar(const Notificacao &notificacao) = 0;
};

#endif