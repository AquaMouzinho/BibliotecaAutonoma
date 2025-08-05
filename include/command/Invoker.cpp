#include "Invoker.hpp"

void Invoker::executarComando(Comando* comando) {
    comando->executar();
    historicoComandos.push(std::move(comando));
}

void Invoker::desfazerUltimoComando() {
    if (!historicoComandos.empty()) {
        auto& comando = historicoComandos.top();
        comando->desfazer();
        historicoComandos.pop();
    }
}

void Invoker::executarEmLote() {
    for (auto& comando : comandosEmLote) {
        executarComando(std::move(comando));
    }
    comandosEmLote.clear();
}

void Invoker::adicionarAoLote(Comando* comando) {
    comandosEmLote.push_back(std::move(comando));
}

void Invoker::limparHistorico() {
    while (!historicoComandos.empty()) {
        historicoComandos.pop();
    }
}