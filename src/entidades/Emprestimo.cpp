#include "../../include/entidades/Emprestimo.hpp"

using namespace std::chrono;

int Emprestimo::calcularAtraso() const
{
    auto agora = system_clock::now();

    if (status == StatusEmprestimo::CONCLUIDO)
        return 0;
    if (agora <= dataFim)
        return 0;

    auto atraso = duration_cast<duration<int, std::ratio<86400>>>(agora - dataFim).count(); // dias
    return atraso;
}

void Emprestimo::finalizar(system_clock::time_point dataDevolucao)
{
    if (dataDevolucao > dataFim)
    {
        status = StatusEmprestimo::ATRASO;
    }
    else
    {
        status = StatusEmprestimo::CONCLUIDO;
    }
}