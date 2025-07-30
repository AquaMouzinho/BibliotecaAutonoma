#ifndef LIVRO_H
#define LIVRO_H

#include <string>

#include "Usuario.hpp";
#include "Armario.hpp";

class Livro
{
private:
    std::string isbn;
    std::string titulo;
    std::string autor;
    std::string tagRFID;
    Usuario *proprietario;
    Armario *armario;
    bool disponivel;

public:
    Livro(const std::string &isbn, const std::string &titulo,
          const std::string &autor, const std::string &tagRFID,
          Usuario *proprietario, Armario *armario, bool disponivel = true);

    Emprestimo *getHistoricoEmprestimos() const;
    Armario *getLocalizacaoAtual() const;
    Usuario *getProprietario() const;

    std::string getIsbn() const { return this->isbn; };
    void setIsbn(std::string isbn) { this->isbn = isbn; };
    std::string getTitulo() const { return this->titulo; };
    void setTitulo(std::string titulo) { this->titulo = titulo; };
    std::string getAutor() const { return this->autor; };
    void setAutor(std::string autor) { this->autor = autor; };
    std::string getTagRfid() const { return this->tagRFID; };
    void setTagRfid(std::string tagRFID) { this->tagRFID = tagRFID; };
    void setProprietario(Usuario *proprietario) { this->proprietario = proprietario; };
    void setLocalizacao(Armario *localizacao) { this->armario = localizacao; };
    bool isDisponivel() const { return this->disponivel; };
    void setDisponivel(bool disponivel) { this->disponivel = disponivel; };
};

#endif // LIVRO_H
