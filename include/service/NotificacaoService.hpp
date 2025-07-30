#pragma once
#include "../repository/NotificacaoRepository.hpp"
#include "../repository/UsuarioRepository.hpp"
#include "../entidades/Notificacao.hpp"
#include <vector>

class NotificacaoService
{
private:
  NotificacaoRepository *notificacaoRepository;
  UsuarioRepository *usuarioRepository;

public:
  NotificacaoService(NotificacaoRepository *notifRepo,
                     UsuarioRepository *usuarioRepo);

  bool enviarNotificacao(int usuarioId, const std::string &mensagem);
  bool marcarComoLida(int notificacaoId);
  std::vector<Notificacao> listarNotificacoesUsuario(int usuarioId, bool apenasNaoLidas = false);
  bool removerNotificacao(int notificacaoId);
  int enviarNotificacaoLote(const std::vector<int> &usuariosIds, const std::string &mensagem);
  void notificarAtrasos();
};