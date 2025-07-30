#ifndef NOTIFICACAO_H
#define NOTIFICACAO_H

#include <string>
#include <chrono>

#include "Usuario.hpp"

class Notificacao
{
private:
  int id;
  Usuario *usuario;
  std::string mensagem;
  std::chrono::system_clock::time_point data;
  bool lida;

public:
  Notificacao(int id, Usuario *usuario, const std::string &mensagem,
              std::chrono::system_clock::time_point data);

  void marcarComoLida();

  int getId() const { return this->id; };
  void setId(int id) { this->id = id; };
  Usuario *getUsuario() const { return this->usuario; };
  void setUsuario(Usuario *usuario) { this->usuario = usuario; };
  std::string getMensagem() const { return this->mensagem; };
  void setMensagem(std::string mensagem) { this->mensagem = mensagem; };
  std::chrono::system_clock::time_point getDataCriacao() const { return this->data; };
  void setDataCriacao(std::chrono::system_clock::time_point data_criacao) { this->data = data_criacao; };
  bool isLida() const { return this->lida; };
  void setLida(bool lida) { this->lida = lida; };
};

#endif // NOTIFICACAO_H
