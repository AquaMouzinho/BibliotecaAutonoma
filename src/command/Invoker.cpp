#include "../../include/command/Invoker.hpp"

void Invoker::adicionarComando(std::unique_ptr<Comando> comando)
{
  comandos.push_back(std::move(comando));
}

bool Invoker::executarComandos()
{
  bool sucessoTotal = true;
  for (auto &comando : comandos)
  {
    // if (!comando->executar())
    //{
    //   sucessoTotal = false;
    //  Opcional: desfazer comandos já executados
    //  break;
    //}
    historico.push(std::move(comando));
  }
  comandos.clear();
  return sucessoTotal;
}

bool Invoker::desfazerUltimoComando()
{
  if (historico.empty())
    return false;

  auto &comando = historico.top();
  // bool sucesso = comando->desfazer();
  historico.pop();
  // return sucesso;
}