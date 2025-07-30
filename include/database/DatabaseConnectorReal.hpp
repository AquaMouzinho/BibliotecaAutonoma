#ifndef DATABASE_CONNECTOR_REAL_HPP
#define DATABASE_CONNECTOR_REAL_HPP

#include "IDatabaseConnector.hpp"
#include <memory>

class DatabaseConnectorReal : public IDatabaseConnector
{
public:
  static DatabaseConnectorReal &getInstancia();

  void conectar() override;
  void desconectar() override;

  PGresult *executarQuery(const std::string &query) override;
  void executarComando(const std::string &query) override;

  void iniciarTransacao() override;
  void commit() override;
  void rollback() override;

private:
  DatabaseConnectorReal() = default;
  static std::unique_ptr<DatabaseConnectorReal> instancia;

  PGconn *conexao = nullptr;
  bool transacaoAtiva = false;
};

#endif // DATABASE_CONNECTOR_REAL_HPP