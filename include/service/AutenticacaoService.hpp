#pragma once
#include "../repository/UsuarioRepository.hpp"
#include "../entidades/Usuario.hpp"
#include <memory>

class AutenticacaoService
{
private:
  UsuarioRepository *usuarioRepository;

public:
  AutenticacaoService(UsuarioRepository *usuarioRepo);

  std::shared_ptr<Usuario> autenticarUsuario(const std::string &matricula, const std::string &senha);
  bool usuarioPossuiAtrasos(int usuarioId);
  bool bloquearUsuario(int usuarioId);
  bool desbloquearUsuario(int usuarioId);
  bool alterarSenha(int usuarioId, const std::string &senhaAtual, const std::string &novaSenha);
};