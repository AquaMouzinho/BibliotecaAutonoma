#ifndef SESSAO_H
#define SESSAO_H

#include <chrono>

#include "Usuario.hpp";
#include "Armario.hpp";
#include "../state/EstadoSessao.hpp";

enum class TipoSessao
{
    WEB,
    FISICA
};

class Sessao
{
private:
    int id;
    Usuario *usuario;
    Armario *armario;
    EstadoSessao *estadoAtual;
    TipoSessao tipo;
    std::chrono::system_clock::time_point inicio;
    std::chrono::system_clock::time_point fim;
    int timeout_timer;

public:
    Sessao(int id, Usuario *usuario, Armario *armario, TipoSessao tipo);

    void iniciar();
    void reiniciarTimeout();
    void encerrar();
    void setEstado(EstadoSessao *novoEstado);

    int getId() const { return id; };
    void setId(int id) { this->id = id; };
    Usuario *getUsuario() const { return usuario; };
    void setUsuario(Usuario *usuario) { this->usuario = usuario; };
    Armario *getArmario() const { return armario; };
    void setArmario(Armario *armario) { this->armario = armario; };
    EstadoSessao *getEstado() const { return estadoAtual; };
    TipoSessao getTipo() const { return tipo; };
    void setTipo(TipoSessao tipo) { this->tipo = tipo; };
    std::chrono::system_clock::time_point getDataCriacao() const { return inicio; };
    void setDataCriacao(std::chrono::system_clock::time_point inicio) { this->inicio = inicio; };
    std::chrono::system_clock::time_point getDataFechamento() const { return fim; };
    void setDataFechamento(std::chrono::system_clock::time_point fim) { this->fim = fim; };
    int getTimer() const { return timeout_timer; };
    void setTimer(int timer) { this->timeout_timer = timer; };
};

#endif // SESSAO_H
