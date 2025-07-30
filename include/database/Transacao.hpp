#ifndef TRANSACAO_HPP
#define TRANSACAO_HPP

#include "IDatabaseConnector.hpp"

class Transacao
{
public:
  explicit Transacao(IDatabaseConnector &db);
  ~Transacao();

  void confirmar();
  void reverter();
  bool estaAtiva() const;

private:
  IDatabaseConnector &db;
  bool transacaoAtiva;
};

#endif // TRANSACAO_HPP