#ifndef ARMARIO_H
#define ARMARIO_H

#include <string>
#include <vector>

#include "Livro.hpp"

class Armario
{
private:
    std::string id;
    std::string localizacao;
    bool disponivel;
    std::vector<Livro *> livros;

public:
    Armario() : id(0), localizacao(""), disponivel(true), livros() {};
    Armario(const std::string &id, const std::string &localizacao, bool disponivel = true) : id(id), localizacao(localizacao), disponivel(disponivel), livros() {};
    ~Armario() = default;

    std::string getId() const { return id; }
    void setId(int id) { this->id = id; }
    std::string getLocalizacao() const { return localizacao; }
    void setLocalizacao(std::string localizacao) { this->localizacao = localizacao; }
    bool isDisponivel() const { return disponivel; }
    void setDisponivel(bool disponivel) { this->disponivel = disponivel; }
    std::vector<Livro *> getLivros() const { return livros; }
    void setLivros(std::vector<Livro *> livros) { this->livros = livros; }

    bool Armario::getStatus() const
    {
        return disponivel;
    }
};

#endif // ARMARIO_H
