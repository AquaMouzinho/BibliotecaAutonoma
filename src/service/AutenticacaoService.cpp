#include "../../include/service/AutenticacaoService.hpp"
#include <algorithm>

AutenticacaoService::AutenticacaoService(UsuarioRepository *usuarioRepo)
    : usuarioRepository(usuarioRepo) {}

std::shared_ptr<Usuario> AutenticacaoService::autenticarUsuario(const std::string &matricula, const std::string &senha)
{
  try
  {
    auto usuario = usuarioRepository->autenticar(matricula, senha);
    if (usuario)
    {
      // logger->log("Usuário " + matricula + " autenticado com sucesso");
      return std::make_shared<Usuario>(*usuario);
    }
    return nullptr;
  }
  catch (const std::exception &e)
  {
    // logger->error("Falha na autenticação: " + std::string(e.what()));
    throw;
  }
}

bool AutenticacaoService::usuarioPossuiAtrasos(int usuarioId)
{
  return usuarioRepository->usuarioPossuiEmprestimosAtrasados(usuarioId);
}

bool AutenticacaoService::bloquearUsuario(int usuarioId)
{
  return usuarioRepository->bloquearUsuario(usuarioId);
}

bool AutenticacaoService::desbloquearUsuario(int usuarioId)
{
  return usuarioRepository->desbloquearUsuario(usuarioId);
}

bool AutenticacaoService::alterarSenha(int usuarioId, const std::string &senhaAtual, const std::string &novaSenha)
{
  auto usuario = usuarioRepository->buscarPorId(usuarioId);
  // if (usuario && usuario->autenticar(senhaAtual))
  //{
  usuario->setSenhaHash(novaSenha); // Na prática, usar hash seguro
  return usuarioRepository->atualizarUsuario(*usuario);
  //}
  // return false;
}