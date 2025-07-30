#include "../../include/repository/SessaoRepository.hpp"
#include "../../include/entidades/Sessao.hpp"
#include "../../include/entidades/Usuario.hpp"

#include <ctime>
#include <sstream>
#include <stdexcept>

// using namespace pqxx;

SessaoRepository::SessaoRepository(IDatabaseConnector *connector)
    : dbConnector(connector) {}

bool SessaoRepository::criarSessao(const Sessao &sessao)
{
  try
  {
    //        work txn(*dbConnector->getConnection());

    std::stringstream query;
    query << "INSERT INTO sessoes (usuario_id, armario_id, data_inicio, status) "
          << "VALUES (" << sessao.getUsuario()->getId() << ", "
          << sessao.getArmario()->getId() << ", "
          << "CURRENT_TIMESTAMP, 'ativa') RETURNING id;";

    //    result res = txn.exec(query.str());
    //   txn.commit();

    //    if (!res.empty())
    //    {
    //      const int novoId = res[0][0].as<int>();
    //      const_cast<Sessao &>(sessao).setId(novoId);
    return true;
    //   }
    //    return false;
  }
  catch (const std::exception &e)
  {
    // Logar erro
    return false;
  }
}

bool SessaoRepository::atualizarSessao(const Sessao &sessao)
{
  try
  {
    // work txn(*dbConnector->getConnection());

    std::stringstream query;
    query << "UPDATE sessoes SET "
          << "data_fim = CURRENT_TIMESTAMP, "
          << "status = '" << sessao.getTipo() << "' "
          << "WHERE id = " << sessao.getId() << ";";

    // txn.exec(query.str());
    // txn.commit();
    return true;
  }
  catch (const std::exception &e)
  {
    // Logar erro
    return false;
  }
}

std::unique_ptr<Sessao> SessaoRepository::buscarSessaoAtivaPorUsuario(int usuarioId)
{
  try
  {
    // work txn(*dbConnector->getConnection());

    std::stringstream query;
    query << "SELECT id, usuario_id, armario_id, "
          << "EXTRACT(epoch FROM data_inicio), "
          << "EXTRACT(epoch FROM data_fim), status "
          << "FROM sessoes "
          << "WHERE usuario_id = " << usuarioId << " "
          << "AND status = 'ativa' "
          << "ORDER BY data_inicio DESC LIMIT 1;";

    // result res = txn.exec(query.str());
    /*
        if (!res.empty())
        {
          auto row = res[0];
          auto sessao = std::make_unique<Sessao>(
              row["usuario_id"].as<int>(),
              row["armario_id"].as<int>());

          sessao->setId(row["id"].as<int>());
          sessao->setDataInicio(static_cast<time_t>(row[3].as<double>()));

          if (!row["data_fim"].is_null())
          {
            sessao->setDataFim(static_cast<time_t>(row[4].as<double>()));
          }

          sessao->setStatus(row["status"].as<std::string>());
          return sessao;
        }
        return nullptr;
        */
  }
  catch (const std::exception &e)
  {
    // Logar erro
    return nullptr;
  }
}

std::vector<Sessao> SessaoRepository::buscarSessoesPorArmario(int armarioId)
{
  std::vector<Sessao> sessoes;
  try
  {
    // work txn(*dbConnector->getConnection());

    std::stringstream query;
    query << "SELECT id, usuario_id, armario_id, "
          << "EXTRACT(epoch FROM data_inicio), "
          << "EXTRACT(epoch FROM data_fim), status "
          << "FROM sessoes "
          << "WHERE armario_id = " << armarioId << ";";

    // result res = txn.exec(query.str());
    /*
        for (const auto &row : res)
        {
          Sessao sessao(
              row["usuario_id"].as<int>(),
              row["armario_id"].as<int>());

          sessao.setId(row["id"].as<int>());
          sessao.setDataInicio(static_cast<time_t>(row[3].as<double>()));

          if (!row["data_fim"].is_null())
          {
            sessao.setDataFim(static_cast<time_t>(row[4].as<double>()));
          }

          sessao.setStatus(row["status"].as<std::string>());
          sessoes.push_back(sessao);
        }
        */
  }
  catch (const std::exception &e)
  {
    // Logar erro
  }
  return sessoes;
}

int SessaoRepository::encerrarSessoesExpiradas()
{
  try
  {
    // work txn(*dbConnector->getConnection());

    // Sessões ativas com mais de 30 minutos sem atividade
    std::string query =
        "UPDATE sessoes "
        "SET status = 'expirada', data_fim = CURRENT_TIMESTAMP "
        "WHERE status = 'ativa' "
        "AND data_inicio < (CURRENT_TIMESTAMP - INTERVAL '30 minutes');";

    // result res = txn.exec(query);
    // txn.commit();
    // return res.affected_rows();
    return 0;
  }
  catch (const std::exception &e)
  {
    // Logar erro
    return 0;
  }
}

std::unique_ptr<Sessao> SessaoRepository::buscarPorId(int id)
{
  try
  {
    // work txn(*dbConnector->getConnection());

    std::stringstream query;
    query << "SELECT id, usuario_id, armario_id, "
          << "EXTRACT(epoch FROM data_inicio), "
          << "EXTRACT(epoch FROM data_fim), status "
          << "FROM sessoes WHERE id = " << id << ";";

    // result res = txn.exec(query.str());
    /*
        if (!res.empty())
        {
          auto row = res[0];
          auto sessao = std::make_unique<Sessao>(
              row["usuario_id"].as<int>(),
              row["armario_id"].as<int>());

          sessao->setId(row["id"].as<int>());
          sessao->setDataInicio(static_cast<time_t>(row[3].as<double>()));

          if (!row["data_fim"].is_null())
          {
            sessao->setDataFim(static_cast<time_t>(row[4].as<double>()));
          }

          sessao->setStatus(row["status"].as<std::string>());
          return sessao;
        }*/
    return nullptr;
  }
  catch (const std::exception &e)
  {
    // Logar erro
    return nullptr;
  }
}