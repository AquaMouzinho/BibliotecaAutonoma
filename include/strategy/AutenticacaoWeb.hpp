#pragma once
#include "AutenticacaoStrategy.hpp"
#include "../repository/UsuarioRepository.hpp"
#include "../repository/SessaoRepository.hpp"

class AutenticacaoWeb : public AutenticacaoStrategy
{
private:
  UsuarioRepository *usuarioRepository;
  SessaoRepository *sessaoRepository;
  std::string gerarToken(const Usuario &usuario);

public:
  AutenticacaoWeb(UsuarioRepository *usuarioRepo, SessaoRepository *sessaoRepo);

  std::shared_ptr<Usuario> autenticar(const std::string &email, const std::string &senha) override;
  bool alterarSenha(int usuarioId, const std::string &senhaAtual, const std::string &novaSenha) override;
  bool validarToken(const std::string &token);
  void encerrarSessao(const std::string &token);
};