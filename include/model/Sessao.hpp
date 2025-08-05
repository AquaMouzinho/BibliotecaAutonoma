#ifndef SESSAO_HPP
#define SESSAO_HPP

#include <string>
#include <vector>

class Sessao {
  private:
    int id;    
    int armario_id;
    std::string usuario_matricula;
    std::string tipo; // fisica ou web
    std::string data_criacao;
    std::string data_fechamento;
    bool ativa;
    int timer;

  public:
    Sessao() : id(0),  armario_id(0), usuario_matricula(""), tipo(""), data_criacao(""), data_fechamento(""), ativa(false), timer(0) {};
    Sessao(int id, int armario_id, std::string usuario_matricula, std::string tipo, std::string data_criacao, std::string data_fechamento, bool ativa, int timer) : id(id), armario_id(armario_id), usuario_matricula(usuario_matricula), tipo(tipo), data_criacao(data_criacao), data_fechamento(data_fechamento), ativa(ativa) {};
    ~Sessao() = default;

    int getId() const { return id; };
    void setId(int id) { this->id = id; };

std::string getUsuarioMatricula() const { return usuario_matricula; };
    void setUsuarioMatricula(std::string usuario_matricula) { this->usuario_matricula = usuario_matricula; };

 int getArmarioId() const { return armario_id; };
    void setArmarioId(int armario_id) { this->armario_id = armario_id; }

    std::string getTipo() const { return tipo; };
    void setTipo(std::string tipo) { this->tipo = tipo; };

    std::string getDataCriacao() const { return data_criacao; };
    void setDataCriacao(std::string data_criacao) { this->data_criacao = data_criacao; };

    std::string getDataFechamento() const { return data_fechamento; };
    void setDataFechamento(std::string data_fechamento) { this->data_fechamento = data_fechamento; };

    int getTimer() const { return timer; };
    void setTimer(int timer) { this->timer = timer; };

    bool isAtiva() const { return ativa; };
    void setAtiva(bool ativa) { this->ativa = ativa; }
};

#endif