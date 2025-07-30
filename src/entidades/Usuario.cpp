#include "../../include/entidades/Usuario.hpp"

Usuario::Usuario(int id, const std::string &matricula, const std::string &nome,
                 const std::string &senha_hash, const std::string &role)
    : id(id), matricula(matricula), nome(nome),
      senha_hash(senha_hash), role(role) {}

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
