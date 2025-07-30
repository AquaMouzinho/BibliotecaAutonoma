#include "../../include/entidades/Usuario.hpp"

Usuario::Usuario(int id, const std::string &matricula, const std::string &nome,
                 const std::string &senha_hash, const std::string &role)
    : id(id), matricula(matricula), nome(nome),
      senha_hash(senha_hash), role(role) {}

bool Usuario::isAdmin() const
{
    if (role == "admin")
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool Usuario::temEmprestimosVencidos() const
{
    for (auto e : emprestimosAtivos)
    {
        if (e->estaVencido())
        {
            return true;
        }
    }
    return false;
}

std::vector<Livro *> Usuario::getLivrosDoados() const
{
    return livrosDoados;
}

std::vector<Emprestimo *> Usuario::getEmprestimosAtivos() const
{
    return emprestimosAtivos;
}

std::vector<Notificacao *> Usuario::getNotificacoes() const
{
    return notificacoes;
}

void Usuario::adicionarNotificacao(Notificacao *n)
{
    notificacoes.push_back(n);
}
