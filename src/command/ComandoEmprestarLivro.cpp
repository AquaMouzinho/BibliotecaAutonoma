#include "../../include/command/ComandoEmprestarLivro.hpp"
#include "../../include/service/EmprestimoService.hpp"
#include "../../include/repository/LivroRepository.hpp"

ComandoEmprestarLivro::ComandoEmprestarLivro(EmprestimoService *emprestimoService,
                                             int livroId,
                                             int usuarioId,
                                             int armarioId)
    : emprestimoService(emprestimoService),
      livroId(livroId),
      usuarioId(usuarioId),
      armarioId(armarioId),
      emprestimoRealizado(false) {}

void ComandoEmprestarLivro::executar()
{
  try
  {
    emprestimoRealizado = emprestimoService->realizarEmprestimo(livroId, usuarioId, armarioId);
  }
  catch (const std::exception &e)
  {
    // Logar erro
    // return false;
  }
}

bool ComandoEmprestarLivro::desfazer()
{
  if (!emprestimoRealizado)
    return false;

  try
  {
    // Busca o último empréstimo do livro para este usuário
    /*
    auto emprestimos = emprestimoService->buscarPorLivroEUsuario(livroId, usuarioId);
    if (!emprestimos.empty())
    {
      return emprestimoService->cancelarEmprestimo(emprestimos.back().getId());
    }
    */
    return false;
  }
  catch (const std::exception &e)
  {
    // Logar erro
    return false;
  }
}