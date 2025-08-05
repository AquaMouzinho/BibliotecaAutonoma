#ifndef ARMARIO_HPP
#define ARMARIO_HPP

#include <string>
#include <vector>

class Armario {
  private:
    int id;
    std::string localizacao;
    bool disponivel;
    std::vector<std::string> livros;
  
  public:
    Armario() : id(0), localizacao(""), disponivel(true) {};
    Armario(int id, std::string localizacao, bool disponivel)
        : id(id), localizacao(localizacao), disponivel(disponivel) {};
    Armario(int id, std::string localizacao, bool disponivel, std::vector<std::string> livros) : id(id), localizacao(localizacao), disponivel(disponivel), livros(livros) {};
    ~Armario() = default;

    int getId() const { return id; }
    void setId(int id) { this->id = id; }
    std::string getLocalizacao() const { return localizacao; }
    void setLocalizacao(std::string localizacao) { this->localizacao = localizacao; }
    bool isDisponivel() const { return disponivel; }
    void setDisponivel(bool disponivel) { this->disponivel = disponivel; }

    std::vector<std::string> getLivros() const { return livros; }
    void setLivros(std::vector<std::string> livros) { this->livros = livros; }

};

#endif