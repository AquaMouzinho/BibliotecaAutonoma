#pragma once
#include "Comando.hpp"
#include <memory>
#include <vector>
#include <stack>

class Invoker
{
private:
  std::vector<std::unique_ptr<Comando>> comandos;
  std::stack<std::unique_ptr<Comando>> historico;

public:
  /// Adiciona um novo comando à fila de execução
  void adicionarComando(std::unique_ptr<Comando> comando);

  /// Executa todos os comandos na fila
  bool executarComandos();

  /// Desfaz o último comando executado
  bool desfazerUltimoComando();

  /// Limpa todos os comandos pendentes
  void limparComandos();

  /// Verifica se existem comandos a serem desfeitos
  bool podeDesfazer() const;
};