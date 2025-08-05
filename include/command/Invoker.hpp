#ifndef INVOKER_HPP
#define INVOKER_HPP

#include "Comando.hpp"
#include <stack>
#include <vector>

class Invoker
{
private:
  std::stack<Comando *> historicoComandos;
  std::vector<Comando *> comandosEmLote;

public:
  void executarComando(Comando *comando);
  void desfazerUltimoComando();
  void executarEmLote();
  void adicionarAoLote(Comando *comando);
  void limparHistorico();
};

#endif