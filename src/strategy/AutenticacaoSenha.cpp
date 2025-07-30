#include "../../include/strategy/AutenticacaoSenha.hpp"
#include <stdexcept>

AutenticacaoSenha::AutenticacaoSenha(UsuarioRepository *usuarioRepo)
    : usuarioRepository(usuarioRepo) {}

std::shared_ptr<Usuario> AutenticacaoSenha::autenticar(const std::string &matricula, const std::string &senha)
{
  auto usuario = usuarioRepository->autenticar(matricula, senha);
  if (!usuario)
  {
    throw std::runtime_error("Matrícula ou senha inválidos");
  }

  // if (usuario->isBloqueado())
  //{
  //   throw std::runtime_error("Usuário bloqueado");
  // }

  if (usuarioRepository->usuarioPossuiEmprestimosAtrasados(usuario->getId()))
  {
    throw std::runtime_error("Usuário possui empréstimos atrasados");
  }

  return std::make_shared<Usuario>(*usuario);
}

bool AutenticacaoSenha::alterarSenha(int usuarioId, const std::string &senhaAtual, const std::string &novaSenha)
{
  auto usuario = usuarioRepository->buscarPorId(usuarioId);
  // if (!usuario || !usuario->autenticar(senhaAtual))
  //{
  //   return false;
  // }

  usuario->setSenhaHash(novaSenha); // Na prática, usar bcrypt
  return usuarioRepository->atualizarUsuario(*usuario);
}