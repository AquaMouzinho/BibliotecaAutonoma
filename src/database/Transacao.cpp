#include "../../include/database/Transacao.hpp"

Transacao::Transacao(IDatabaseConnector &db)
    : db(db), transacaoAtiva(true)
{
  db.iniciarTransacao();
}

Transacao::~Transacao()
{
  if (transacaoAtiva)
  {
    db.rollback();
  }
}

void Transacao::confirmar()
{
  if (transacaoAtiva)
  {
    db.commit();
    transacaoAtiva = false;
  }
}

void Transacao::reverter()
{
  if (transacaoAtiva)
  {
    db.rollback();
    transacaoAtiva = false;
  }
}

bool Transacao::estaAtiva() const
{
  return transacaoAtiva;
}