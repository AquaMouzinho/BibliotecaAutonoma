#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include "Observador.hpp"
#include <vector>
#include <memory>

class Subject {
protected:
    std::vector<Observador*> observadores;

public:
    virtual ~Subject() = default;
    void adicionarObservador(Observador* observador);
    void removerObservador(Observador* observador);
    void notificarObservadores(const std::string& matricula, const std::string& mensagem);
};

#endif