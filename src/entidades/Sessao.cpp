#include "../../include/entidades/Sessao.hpp"

#include <chrono>

Sessao::Sessao(int id, Usuario *usuario, Armario *armario, TipoSessao tipo)
    : id(id), usuario(usuario), armario(armario),
      estadoAtual(nullptr), tipo(tipo), timeout_timer(0) {}

void Sessao::iniciar()
{
    inicio = std::chrono::system_clock::now();
    fim = std::chrono::system_clock::time_point(); // indefinido ainda
    reiniciarTimeout();
}

void Sessao::reiniciarTimeout()
{
    timeout_timer = 300; // Exemplo: reinicia para 5 minutos (300 segundos)
}

void Sessao::encerrar()
{
    fim = std::chrono::system_clock::now();
}

void Sessao::setEstado(EstadoSessao *novoEstado)
{
    estadoAtual = novoEstado;
}