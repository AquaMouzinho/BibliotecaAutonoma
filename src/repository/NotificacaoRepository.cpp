#include "../../include/repository/NotificacaoRepository.hpp"

#include <libpq-fe.h>
#include <sstream>
#include <stdexcept>

// using namespace pqxx;

NotificacaoRepository::NotificacaoRepository(IDatabaseConnector *connector)
    : dbConnector(connector) {}

bool NotificacaoRepository::criarNotificacao(const Notificacao &notificacao)
{
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    std::stringstream query;
    query << "INSERT INTO notificacoes (usuario_id, mensagem) VALUES ("
      << notificacao.getUsuarioId() << ", '"
      << txn.esc(notificacao.getMensagem()) << "') RETURNING id;";

      result res = txn.exec(query.str());
      txn.commit();

      if (!res.empty()) {
        const_cast<Notificacao&>(notificacao).setId(res[0][0].as<int>());
        return true;
      }
      */
    return false;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao criar notificação: " + std::string(e.what()));
  }
}

std::vector<Notificacao> NotificacaoRepository::buscarPorUsuario(int usuarioId, bool apenasNaoLidas)
{
  std::vector<Notificacao> notificacoes;
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    std::string query =
    "SELECT id, usuario_id, mensagem, data_criacao, lida "
    "FROM notificacoes WHERE usuario_id = " +
    std::to_string(usuarioId);

    if (apenasNaoLidas)
    {
      query += " AND lida = FALSE";
    }

    query += " ORDER BY data_criacao DESC;";

    result res = txn.exec(query);

    for (const auto &row : res)
    {
      Notificacao notificacao(
        row["usuario_id"].as<int>(),
        row["mensagem"].as<std::string>());

        notificacao.setId(row["id"].as<int>());
        notificacao.setDataCriacao(row["data_criacao"].as<std::string>());
        notificacao.setLida(row["lida"].as<bool>());

        notificacoes.push_back(notificacao);
      }
      */
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao buscar notificações: " + std::string(e.what()));
  }
  return notificacoes;
}

bool NotificacaoRepository::marcarComoLida(int notificacaoId)
{
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    txn.exec(
        "UPDATE notificacoes SET lida = TRUE "
        "WHERE id = " +
        std::to_string(notificacaoId) + ";");
    txn.commit();
    */
    return true;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao marcar notificação como lida: " + std::string(e.what()));
  }
}

bool NotificacaoRepository::removerNotificacao(int notificacaoId)
{
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    txn.exec(
      "DELETE FROM notificacoes WHERE id = " + std::to_string(notificacaoId) + ";");
      txn.commit();
      */
    return true;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao remover notificação: " + std::string(e.what()));
  }
}

int NotificacaoRepository::removerTodasDoUsuario(int usuarioId)
{
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    result res = txn.exec(
      "DELETE FROM notificacoes WHERE usuario_id = " + std::to_string(usuarioId) + " "
      "RETURNING id;");
      txn.commit();
      return res.affected_rows();
      */
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao remover notificações: " + std::string(e.what()));
  }
}

Notificacao *NotificacaoRepository::buscarPorId(int notificacaoId)
{
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    result res = txn.exec(
      "SELECT id, usuario_id, mensagem, data_criacao, lida "
      "FROM notificacoes WHERE id = " +
      std::to_string(notificacaoId) + ";");

      if (!res.empty())
    {
      auto row = res[0];
      auto notificacao = std::make_unique<Notificacao>(
          row["usuario_id"].as<int>(),
          row["mensagem"].as<std::string>());

          notificacao->setId(row["id"].as<int>());
          notificacao->setDataCriacao(row["data_criacao"].as<std::string>());
          notificacao->setLida(row["lida"].as<bool>());

          return notificacao;
        }
        */
    return nullptr;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao buscar notificação: " + std::string(e.what()));
  }
}

int NotificacaoRepository::criarEmLote(const std::vector<int> &usuariosIds, const std::string &mensagem)
{
  try
  {
    if (usuariosIds.empty())
      return 0;

    /*
    work txn(*dbConnector->getConnection());

    std::stringstream query;
    query << "INSERT INTO notificacoes (usuario_id, mensagem) VALUES ";

    for (size_t i = 0; i < usuariosIds.size(); ++i)
    {
      if (i != 0)
      query << ", ";
      query << "(" << usuariosIds[i] << ", '" << txn.esc(mensagem) << "')";
    }

    query << ";";

    result res = txn.exec(query.str());
    txn.commit();
    return res.affected_rows();
    */
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao criar notificações em lote: " + std::string(e.what()));
  }
}