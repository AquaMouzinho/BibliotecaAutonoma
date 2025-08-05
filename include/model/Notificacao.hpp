#ifndef NOTIFICACAO_HPP
#define NOTIFICACAO_HPP

#include <string>

class Notificacao {
  private:
    int id;
    std::string usuario_matricula;
    std::string mensagem;
    std::string data_criacao;
    bool lida;

  public:
    Notificacao() : id(0), usuario_matricula(""), mensagem(""), data_criacao(""), lida(false) {};
    Notificacao(int id, std::string usuario_matricula, std::string mensagem, std::string data_criacao) : id(id), usuario_matricula(usuario_matricula), mensagem(mensagem), data_criacao(data_criacao), lida(false) {}
    ~Notificacao() = default;

    int getId() const { return this->id; };
    void setId(int id) { this->id = id; };

    std::string getUsuarioMatricula() const { return this->usuario_matricula; };
    void setUsuarioMatricula(std::string usuario_matricula) { this->usuario_matricula = usuario_matricula; }
    

    std::string getMensagem() const { return this->mensagem; };
    void setMensagem(std::string mensagem) { this->mensagem = mensagem; };
    std::string getDataCriacao() const { return this->data_criacao; };
    void setDataCriacao(std::string data_criacao) { this->data_criacao = data_criacao; };
    bool isLida() const { return this->lida; };
    void setLida(bool lida) { this->lida = lida; };
    void marcarComoLida() { this->lida = true; };
};

#endif