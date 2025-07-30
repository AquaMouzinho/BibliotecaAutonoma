#pragma once
#include "AutenticacaoStrategy.hpp"
#include "../repository/UsuarioRepository.hpp"

class AutenticacaoSenha : public AutenticacaoStrategy
{
private:
  UsuarioRepository *usuarioRepository;

public:
  explicit AutenticacaoSenha(UsuarioRepository *usuarioRepo);

  std::shared_ptr<Usuario> autenticar(const std::string &matricula, const std::string &senha) override;
  bool alterarSenha(int usuarioId, const std::string &senhaAtual, const std::string &novaSenha) override;
};