#ifndef OBSERVADOR_H
#define OBSERVADOR_H

#include "Notificacao.h"

class Observador {
public:
    virtual ~Observador() = default;
    virtual void atualizar(const Notificacao& notificacao) = 0;
};

#endif // OBSERVADOR_H