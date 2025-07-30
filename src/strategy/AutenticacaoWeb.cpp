#include "AutenticacaoWeb.hpp"
#include <ctime>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

AutenticacaoWeb::AutenticacaoWeb(UsuarioRepository *usuarioRepo, SessaoRepository *sessaoRepo)
    : usuarioRepository(usuarioRepo), sessaoRepository(sessaoRepo) {}

std::shared_ptr<Usuario> AutenticacaoWeb::autenticar(const std::string &email, const std::string &senha)
{
  // Implementação específica para web (pode usar email em vez de matrícula)
  // auto usuario = usuarioRepository->buscarPorEmail(email);
  // if (!usuario || !usuario->autenticar(senha))
  //{
  // throw std::runtime_error("Credenciais inválidas");
  //}

  // if (usuario->isBloqueado())
  //{
  //  throw std::runtime_error("Conta bloqueada");
  //}

  // Gera e armazena token de sessão
  // std::string token = gerarToken(*usuario);
  // sessaoRepository->criarSessaoWeb(usuario->getId(), token);

  // return usuario;
}

std::string AutenticacaoWeb::gerarToken(const Usuario &usuario)
{
  auto now = std::time(nullptr);
  std::stringstream ss;
  // ss << usuario.getId() << ":" << now << ":" << usuario.getEmail();

  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256(reinterpret_cast<const unsigned char *>(ss.str().c_str()),
         ss.str().size(),
         hash);

  std::stringstream token;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
  {
    token << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
  }

  return token.str();
}

bool AutenticacaoWeb::alterarSenha(int usuarioId, const std::string &senhaAtual, const std::string &novaSenha)
{
  // Similar à estratégia por senha, mas pode adicionar validações específicas para web
  auto usuario = usuarioRepository->buscarPorId(usuarioId);
  // if (!usuario || !usuario->autenticar(senhaAtual))
  // {
  //   return false;
  // }

  usuario->setSenhaHash(novaSenha);
  return usuarioRepository->atualizarUsuario(*usuario);
}
