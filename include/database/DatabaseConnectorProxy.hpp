#ifndef DATABASE_CONNECTOR_PROXY_HPP
#define DATABASE_CONNECTOR_PROXY_HPP

#include "IDatabaseConnector.hpp"
#include <vector>
#include <string>

class DatabaseConnectorProxy : public IDatabaseConnector
{
public:
  explicit DatabaseConnectorProxy(IDatabaseConnector *realConnector);
  ~DatabaseConnectorProxy();

  bool validarSQL(const std::string &sql);
  void registrarLog(const std::string &comando);

  void conectar() override;
  void desconectar() override;
  PGresult *executarQuery(const std::string &query) override;
  void executarComando(const std::string &query) override;
  void iniciarTransacao() override;
  void commit() override;
  void rollback() override;

private:
  IDatabaseConnector *realConnector;
  std::vector<std::string> logComandos;
};

#endif // DATABASE_CONNECTOR_PROXY_HPP