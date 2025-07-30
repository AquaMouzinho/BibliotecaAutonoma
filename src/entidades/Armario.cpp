#include "../../include/entidades/Armario.hpp"
#include "../../include/entidades/Livro.hpp"
#include <algorithm>

Armario::Armario(const std::string &id, const std::string &localizacao, bool disponivel)
    : id(id), localizacao(localizacao), disponivel(disponivel) {}

bool Armario::getStatus() const
{
    return disponivel;
}