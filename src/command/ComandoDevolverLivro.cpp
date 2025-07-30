#include "../../include/command/ComandoDevolverLivro.hpp"
#include "../../include/service/EmprestimoService.hpp"

ComandoDevolverLivro::ComandoDevolverLivro(EmprestimoService *emprestimoService,
                                           int emprestimoId)
    : emprestimoService(emprestimoService),
      emprestimoId(emprestimoId),
      devolvidoComSucesso(false) {}

void ComandoDevolverLivro::executar()
{
  try
  {
    devolvidoComSucesso = emprestimoService->registrarDevolucao(emprestimoId);
    /// return devolvidoComSucesso;
  }
  catch (const std::exception &e)
  {
    // Logar erro
    // return false;
  }
}

bool ComandoDevolverLivro::desfazer()
{
  if (!devolvidoComSucesso)
    return false;

  try
  {
    return false;
    // return emprestimoService->reabrirEmprestimo(emprestimoId);
  }
  catch (const std::exception &e)
  {
    // Logar erro
    return false;
  }
}