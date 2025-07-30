#pragma once
#include "../entidades/Emprestimo.hpp"
#include "../database/IDatabaseConnector.hpp"
#include <vector>
#include <memory>

class EmprestimoRepository
{
private:
  IDatabaseConnector *dbConnector;

public:
  explicit EmprestimoRepository(IDatabaseConnector *connector);

  // CRUD básico
  bool criarEmprestimo(Emprestimo &emprestimo);
  bool atualizarEmprestimo(const Emprestimo &emprestimo);
  bool removerEmprestimo(int id);
  Emprestimo *buscarPorId(int id);
  std::vector<Emprestimo> buscarTodos();

  // Métodos específicos do domínio
  std::vector<Emprestimo> buscarPorUsuario(int usuarioId);
  std::vector<Emprestimo> buscarPorLivro(int livroId);
  std::vector<Emprestimo> buscarEmprestimosAtivos();
  std::vector<Emprestimo> buscarEmprestimosAtrasados();
  bool finalizarEmprestimo(int emprestimoId);
  bool renovarEmprestimo(int emprestimoId, int dias);
  bool verificarAtrasos(int usuarioId);
  std::vector<Emprestimo> buscarHistoricoCompleto(int usuarioId);
  std::vector<Emprestimo> buscarEmprestimosPorArmario(int armarioId);
};