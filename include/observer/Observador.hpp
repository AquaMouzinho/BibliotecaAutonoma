#ifndef OBSERVADOR_HPP
#define OBSERVADOR_HPP

#include <string>

class Observador {
public:
    virtual ~Observador() = default;
    virtual void atualizar(const std::string& matricula, const std::string& mensagem) = 0;
};

#endif