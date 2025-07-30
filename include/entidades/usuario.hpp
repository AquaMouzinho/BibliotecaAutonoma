#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <vector>

class Livro;
class Emprestimo;
class Notificacao;

class Usuario {
    private:
        int id;
        std::string matricula;
        std::string nome;
        std::string senha_hash;
        std::string role;

        // Essas estruturas n sao daqui
        std::vector<Livro*> livrosDoados;
        std::vector<Emprestimo*> emprestimosAtivos;
        std::vector<Notificacao*> notificacoes;

    protected:
        Usuario(int id, const std::string& matricula, const std::string& nome,
                const std::string& senha_hash, const std::string& role);

        bool isAdmin() const;
        bool temEmprestimosVencidos() const;

        std::vector<Livro*> getLivrosDoados() const;
        std::vector<Emprestimo*> getEmprestimosAtivos() const;
        std::vector<Notificacao*> getNotificacoes() const;

        void adicionarNotificacao(Notificacao* n);

};

#endif // USUARIO_H