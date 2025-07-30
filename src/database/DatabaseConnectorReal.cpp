#include "../../include/database/DatabaseConnectorReal.hpp"
#include <stdexcept>
#include <libpq-fe.h>

std::unique_ptr<DatabaseConnectorReal> DatabaseConnectorReal::instancia;

DatabaseConnectorReal &DatabaseConnectorReal::getInstancia()
{
  if (!instancia)
  {
    instancia = std::unique_ptr<DatabaseConnectorReal>(new DatabaseConnectorReal());
  }
  return *instancia;
}

void DatabaseConnectorReal::conectar()
{
  if (conexao)
    return;

  conexao = PQconnectdb(
      "host=localhost dbname=biblioteca_armarios "
      "user=biblioteca_user password=senha_segura");

  if (PQstatus(conexao) != CONNECTION_OK)
  {
    throw std::runtime_error("Falha na conexão: " + std::string(PQerrorMessage(conexao)));
  }
}

void DatabaseConnectorReal::desconectar()
{
  if (conexao)
  {
    PQfinish(conexao);
    conexao = nullptr;
  }
}

PGresult *DatabaseConnectorReal::executarQuery(const std::string &query)
{
  if (!conexao)
    conectar();

  PGresult *res = PQexec(conexao, query.c_str());
  if (PQresultStatus(res) != PGRES_TUPLES_OK)
  {
    std::string erro = PQerrorMessage(conexao);
    PQclear(res);
    throw std::runtime_error("Erro na query: " + erro);
  }
  return res;
}

void DatabaseConnectorReal::executarComando(const std::string &query)
{
  if (!conexao)
    conectar();

  PGresult *res = PQexec(conexao, query.c_str());
  if (PQresultStatus(res) != PGRES_COMMAND_OK)
  {
    std::string erro = PQerrorMessage(conexao);
    PQclear(res);
    throw std::runtime_error("Erro no comando: " + erro);
  }
  PQclear(res);
}

void DatabaseConnectorReal::iniciarTransacao()
{
  executarComando("BEGIN");
  transacaoAtiva = true;
}

void DatabaseConnectorReal::commit()
{
  executarComando("COMMIT");
  transacaoAtiva = false;
}

void DatabaseConnectorReal::rollback()
{
  executarComando("ROLLBACK");
  transacaoAtiva = false;
}