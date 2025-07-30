#ifndef IDATABASE_CONNECTOR_HPP
#define IDATABASE_CONNECTOR_HPP

#include <libpq-fe.h>
#include <string>

class IDatabaseConnector
{
public:
  virtual ~IDatabaseConnector() = default;

  virtual void conectar() = 0;
  virtual void desconectar() = 0;

  virtual PGresult *executarQuery(const std::string &query) = 0;
  virtual void executarComando(const std::string &query) = 0;

  virtual void iniciarTransacao() = 0;
  virtual void commit() = 0;
  virtual void rollback() = 0;
};

#endif // IDATABASE_CONNECTOR_HPP