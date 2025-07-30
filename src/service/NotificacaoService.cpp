#include "../../include/service/NotificacaoService.hpp"

NotificacaoService::NotificacaoService(NotificacaoRepository *notifRepo,
                                       UsuarioRepository *usuarioRepo)
    : notificacaoRepository(notifRepo),
      usuarioRepository(usuarioRepo) {}

bool NotificacaoService::enviarNotificacao(int usuarioId, const std::string &mensagem)
{
  return true;
  // return notificacaoRepository->criarNotificacao(Notificacao(usuarioId, mensagem));
}

void NotificacaoService::notificarAtrasos()
{
  // auto usuariosComAtrasos = usuarioRepository->buscarTodosComAtrasos();
  // for (const auto &usuario : usuariosComAtrasos)
  //{
  //   enviarNotificacao(usuario.getId(), "Você tem empréstimos atrasados");
  // }
}