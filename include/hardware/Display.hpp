#pragma once

#include <string>

class Display
{
public:
  virtual ~Display() = default;

  virtual void mostrarMensagem(const std::string &mensagem) = 0;
  virtual std::string solicitarMatricula() = 0;
  virtual std::string solicitarSenha() = 0;
  virtual bool usuarioDesejaEncerrarSessao() = 0;
  virtual void limpar() = 0;
};
