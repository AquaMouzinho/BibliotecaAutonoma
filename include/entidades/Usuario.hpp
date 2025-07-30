#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <vector>

#include "Livro.hpp"
#include "Emprestimo.hpp"
#include "Notificacao.hpp"

class Usuario
{
private:
    int id;
    std::string matricula;
    std::string nome;
    std::string senha_hash;
    std::string role;

    // Essas estruturas n sao daqui
    std::vector<Livro *> livrosDoados;
    std::vector<Emprestimo *> emprestimosAtivos;
    std::vector<Notificacao *> notificacoes;

protected:
    Usuario(int id, const std::string &matricula, const std::string &nome,
            const std::string &senha_hash, const std::string &role);

    bool isAdmin() const;
    bool temEmprestimosVencidos() const;

    std::vector<Livro *> getLivrosDoados() const;
    std::vector<Emprestimo *> getEmprestimosAtivos() const;
    std::vector<Notificacao *> getNotificacoes() const;

    void adicionarNotificacao(Notificacao *n);

    int getId() const { return this->id; };
    void setId(int id) { this->id = id; };
    std::string getMatricula() const { return this->matricula; };
    void setMatricula(std::string matricula) { this->matricula = matricula; };
    std::string getNome() const { return this->nome; };
    void setNome(std::string nome) { this->nome = nome; };
    std::string getSenhaHash() const { return this->senha_hash; };
    void setSenhaHash(std::string senha_hash) { this->senha_hash = senha_hash; };
    std::string getRole() const { return this->role; };
    void setRole(std::string role) { this->role = role; };
};

#endif // USUARIO_H