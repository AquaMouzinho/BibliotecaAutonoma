#pragma once
#include "../entidades/Usuario.hpp"
#include <memory>

class AutenticacaoStrategy
{
public:
  virtual ~AutenticacaoStrategy() = default;
  virtual std::shared_ptr<Usuario> autenticar(const std::string &credencial, const std::string &senha) = 0;
  virtual bool alterarSenha(int usuarioId, const std::string &senhaAtual, const std::string &novaSenha) = 0;
};