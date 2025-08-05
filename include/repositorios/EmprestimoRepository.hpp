#pragma once
#include "../model/Emprestimo.hpp"
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
  bool criarEmprestimo(const Emprestimo &emprestimo);
  bool atualizarEmprestimo(const Emprestimo &emprestimo);
  bool removerEmprestimo(int id);
  bool removerEmprestimo( std::string usuario_matricula, std::string livro_isbn);
  Emprestimo *buscarPorId(int id);
  std::vector<Emprestimo> buscarTodos();

  // Métodos específicos do domínio
  std::vector<Emprestimo> buscarPorUsuario(std::string usuario_matricula);
  std::vector<Emprestimo> buscarPorLivro(std::string livro_isbn);
  std::vector<Emprestimo> buscarEmprestimosAtivos();
  Emprestimo buscarEmprestimoAtivoPorTag(std::string tag_rfid);
  std::vector<Emprestimo> buscarEmprestimosAtrasados();
  bool finalizarEmprestimo(int emprestimoId);
  bool renovarEmprestimo(int emprestimoId, int dias);
  bool verificarAtrasos(std::string usuarioMatricula);
  std::vector<Emprestimo> buscarHistoricoCompleto(std::string usuarioMatricula);

  std::string buscarDonoLivro(std::string tag_rfid);
};