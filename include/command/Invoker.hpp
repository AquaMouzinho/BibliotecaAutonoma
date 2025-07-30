#ifndef INVOKER_HPP
#define INVOKER_HPP

#include <string>
#include "Comando.hpp"
#include <queue>
#include <stack>

class Invoker
{
public:
  void adicionarComando(Comando *c);
  void executarComandos();

private:
  std::queue<Comando *> filaComandos;
  std::stack<Comando *> historicoComandos;
};

#endif