#pragma once
#include "../model/Notificacao.hpp"
#include "../database/IDatabaseConnector.hpp"
#include <vector>
#include <memory>

class NotificacaoRepository
{
private:
  IDatabaseConnector *dbConnector;

public:
  explicit NotificacaoRepository(IDatabaseConnector *connector);

  // Cria uma nova notificação
  bool criarNotificacao(const Notificacao &notificacao);

  // Busca notificações por usuário
  std::vector<Notificacao> buscarPorUsuario(std::string usuariomat, bool apenasNaoLidas = false);

  // Marca notificação como lida
  bool marcarComoLida(int notificacaoId);

  // Remove notificação
  bool removerNotificacao(int notificacaoId);

  // Remove todas as notificações de um usuário
  int removerTodasDoUsuario(std::string usuariomat);

  // Busca uma notificação específica por ID
  Notificacao *buscarPorId(int notificacaoId);

  // Cria notificações em lote (útil para notificar vários usuários)
  int criarEmLote(const std::vector<std::string> &usuariosMats, const std::string &mensagem);
};