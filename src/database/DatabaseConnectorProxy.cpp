#include "../../include/database/DatabaseConnectorProxy.hpp"
#include <algorithm>
#include <stdexcept>

DatabaseConnectorProxy::DatabaseConnectorProxy(IDatabaseConnector *realConnector)
    : realConnector(realConnector) {}

DatabaseConnectorProxy::~DatabaseConnectorProxy()
{
  delete realConnector;
}

bool DatabaseConnectorProxy::validarSQL(const std::string &sql)
{
  const std::vector<std::string> palavrasProibidas = {"DROP", "DELETE", "TRUNCATE", "--"};
  for (const auto &palavra : palavrasProibidas)
  {
    if (sql.find(palavra) != std::string::npos)
    {
      return false;
    }
  }
  return true;
}

void DatabaseConnectorProxy::registrarLog(const std::string &comando)
{
  logComandos.push_back(comando);
  if (logComandos.size() > 100)
  {
    logComandos.erase(logComandos.begin());
  }
}

void DatabaseConnectorProxy::conectar()
{
  realConnector->conectar();
}

void DatabaseConnectorProxy::desconectar()
{
  realConnector->desconectar();
}

PGresult *DatabaseConnectorProxy::executarQuery(const std::string &query)
{
  if (!validarSQL(query))
  {
    throw std::runtime_error("Query inválida detectada");
  }
  registrarLog("QUERY: " + query);
  return realConnector->executarQuery(query);
}

void DatabaseConnectorProxy::executarComando(const std::string &query)
{
  if (!validarSQL(query))
  {
    throw std::runtime_error("Comando inválido detectado");
  }
  registrarLog("CMD: " + query);
  realConnector->executarComando(query);
}

void DatabaseConnectorProxy::iniciarTransacao()
{
  registrarLog("Iniciar Transação");
  realConnector->iniciarTransacao();
}

void DatabaseConnectorProxy::commit()
{
  registrarLog("Commit Transação");
  realConnector->commit();
}

void DatabaseConnectorProxy::rollback()
{
  registrarLog("Rollback Transação");
  realConnector->rollback();
}