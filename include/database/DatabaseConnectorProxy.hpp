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

  // Métodos herdados
  bool executarQuery(const std::string &query) override;
  std::vector<std::vector<std::string>> fetchData(const std::string &query) override;

  void iniciarTransacao() override;
  void commit() override;
  void rollback() override;

private:
  IDatabaseConnector *realConnector;
  std::vector<std::string> logComandos;
};

#endif // DATABASE_CONNECTOR_PROXY_HPP