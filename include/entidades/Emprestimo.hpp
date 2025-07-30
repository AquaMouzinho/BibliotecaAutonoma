#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H

#include <chrono>

class Livro;
class Usuario;

enum class StatusEmprestimo {
    ATIVO,
    CONCLUIDO,
    ATRASO
};

class Emprestimo {
private:
    int id;
    Livro* livro;
    Usuario* usuario;
    std::chrono::system_clock::time_point dataInicio;
    std::chrono::system_clock::time_point dataFim;
    StatusEmprestimo status;

public:
    Emprestimo(int id, Livro* livro, Usuario* usuario,
               std::chrono::system_clock::time_point dataInicio,
               std::chrono::system_clock::time_point dataFim);

    bool estaEmAberto() const;
    int calcularAtraso() const;
    void finalizar(std::chrono::system_clock::time_point dataDevolucao);

};

#endif // EMPRESTIMO_H
