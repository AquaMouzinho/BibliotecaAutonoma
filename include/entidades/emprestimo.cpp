#include "Emprestimo.h"
#include "Livro.h"
#include "Usuario.h"

using namespace std::chrono;

Emprestimo::Emprestimo(int id, Livro* livro, Usuario* usuario,
                       system_clock::time_point dataInicio,
                       system_clock::time_point dataFim)
    : id(id), livro(livro), usuario(usuario),
      dataInicio(dataInicio), dataFim(dataFim), status(StatusEmprestimo::ATIVO) {}

bool Emprestimo::estaEmAberto() const {
    return status == StatusEmprestimo::ATIVO;
}

int Emprestimo::calcularAtraso() const {
    auto agora = system_clock::now();

    if (status == StatusEmprestimo::CONCLUIDO) return 0;
    if (agora <= dataFim) return 0;

    auto atraso = duration_cast<duration<int, std::ratio<86400>>>(agora - dataFim).count(); // dias
    return atraso;
}

void Emprestimo::finalizar(system_clock::time_point dataDevolucao) {
    if (dataDevolucao > dataFim) {
        status = StatusEmprestimo::ATRASO;
    } else {
        status = StatusEmprestimo::CONCLUIDO;
    }
}