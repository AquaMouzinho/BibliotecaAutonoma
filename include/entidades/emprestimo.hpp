#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H

#include <chrono>

#include "Livro.hpp"
#include "Usuario.hpp"

enum class StatusEmprestimo
{
    ATIVO,
    CONCLUIDO,
    ATRASO
};

class Emprestimo
{
private:
    int id;
    Livro *livro;
    Usuario *usuario;
    std::chrono::system_clock::time_point dataInicio;
    std::chrono::system_clock::time_point dataFim;
    StatusEmprestimo status;

public:
    Emprestimo(int id, Livro *livro, Usuario *usuario,
               std::chrono::system_clock::time_point dataInicio,
               std::chrono::system_clock::time_point dataFim)
        : id(id), livro(livro), usuario(usuario),
          dataInicio(dataInicio), dataFim(dataFim), status(StatusEmprestimo::ATIVO) {}

    int calcularAtraso() const;
    void finalizar(std::chrono::system_clock::time_point dataDevolucao);

    int getId() const { return id; };
    void setId(int id) { this->id = id; };
    Livro *getLivro() const { return livro; };
    void setLivro(Livro *livro) { this->livro = livro; };
    Usuario *getUsuario() const { return usuario; };
    void setUsuario(Usuario *usuario) { this->usuario = usuario; };
    std::chrono::system_clock::time_point getDataEmprestimo() const { return dataInicio; };
    void setDataEmprestimo(std::chrono::system_clock::time_point data_emprestimo) { this->dataInicio = data_emprestimo; };
    std::chrono::system_clock::time_point getDataDevolucao() const { return dataFim; };
    void setDataDevolucao(std::chrono::system_clock::time_point data_devolucao) { this->dataFim = data_devolucao; };
    StatusEmprestimo getStatus() const { return status; };
    void setStatus(StatusEmprestimo status) { this->status = status; };
    bool estaEmAberto() const { return status == StatusEmprestimo::ATIVO; }
    bool estaVencido() const { return status == StatusEmprestimo::ATRASO; }
};

#endif // EMPRESTIMO_H
