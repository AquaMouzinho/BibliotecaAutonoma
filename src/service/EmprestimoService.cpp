#include "../../include/service/EmprestimoService.hpp"
#include <chrono>

EmprestimoService::EmprestimoService(EmprestimoRepository *emprestimoRepo,
                                     LivroRepository *livroRepo,
                                     UsuarioRepository *usuarioRepo,
                                     NotificacaoRepository *notifRepo)
    : emprestimoRepository(emprestimoRepo),
      livroRepository(livroRepo),
      usuarioRepository(usuarioRepo),
      notificacaoRepository(notifRepo) {}

bool EmprestimoService::realizarEmprestimo(int livroId, int usuarioId, int armarioId)
{
  if (!livroRepository->livroEstaDisponivel(livroId))
  {
    return false;
  }

  /*
  Emprestimo novoEmprestimo(livroId, usuarioId, armarioId);
  if (emprestimoRepository->criarEmprestimo(novoEmprestimo))
  {
    auto livro = livroRepository->buscarPorId(livroId);
    if (livro && livro->getUsuarioDoadorId() > 0)
    {
      notificarDonoLivro(livroId, usuarioId, "Seu livro foi emprestado: " + livro->getTitulo());
    }
    return true;
  }
  */
  return false;
}

void EmprestimoService::notificarDonoLivro(int livroId, int usuarioEmprestimoId, const std::string &mensagem)
{
  auto livro = livroRepository->buscarPorId(livroId);
  /*
  if (livro && livro->getUsuarioDoadorId() > 0)
  {
    auto usuario = usuarioRepository->buscarPorId(usuarioEmprestimoId);
    if (usuario)
    {
      std::string msgCompleta = mensagem + " por " + usuario->getNome();
      notificacaoRepository->criarNotificacao(Notificacao(livro->getUsuarioDoadorId(), msgCompleta));
    }
  }
  */
}
