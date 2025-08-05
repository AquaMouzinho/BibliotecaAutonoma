#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>
#include <vector>

class Usuario {
  private:
    int id;
    std::string matricula;
    std::string nome;
    std::string senha_hash;
    std::string role;
    bool ativo;

  public:
    Usuario() : id(0), matricula(""), nome(""), senha_hash(""), role(""), ativo(true) {};

Usuario(int id, std::string matricula, std::string nome, std::string senha_hash) : id(id), matricula(matricula), nome(nome), senha_hash(senha_hash), role("user"), ativo(true) {}
    ~Usuario() = default;

    int getId() const { return this->id; }
    void setId(int id) { this->id = id; }

    std::string getMatricula() const { return this->matricula; };
    void setMatricula(std::string matricula) { this->matricula = matricula; };
    std::string getNome() const { return this->nome; };
    void setNome(std::string nome) { this->nome = nome; };
    std::string getSenhaHash() const { return this->senha_hash; };
    void setSenhaHash(std::string senha_hash) { this->senha_hash = senha_hash; };
    std::string getRole() const { return this->role; };
    void setRole(std::string role) { this->role = role; };

    bool isAdmin() const { return this->role == "admin"; };

    bool getAtivo() const { return this->ativo; };
    void setAtivo(bool ativo) { this->ativo = ativo; }

};

#endif // USUARIO_HPP