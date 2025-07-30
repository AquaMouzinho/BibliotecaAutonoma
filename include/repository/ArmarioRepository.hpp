#pragma once
#include "../entidades/Armario.hpp"
#include "../database/IDatabaseConnector.hpp"
#include <vector>
#include <memory>

class ArmarioRepository
{
private:
  IDatabaseConnector *dbConnector;

public:
  explicit ArmarioRepository(IDatabaseConnector *connector);

  // CRUD básico
  bool criarArmario(Armario &armario);
  bool atualizarArmario(const Armario &armario);
  bool removerArmario(int id);
  Armario *buscarPorId(int id);
  std::vector<Armario> buscarTodos();

  // Métodos específicos do domínio
  std::vector<Armario> buscarPorLocalizacao(const std::string &localizacao);
  bool atualizarStatus(int armarioId, const std::string &status);
  bool verificarDisponibilidade(int armarioId);
  std::vector<int> buscarLivrosNoArmario(int armarioId);
  bool adicionarLivro(int armarioId, int livroId);
  bool removerLivro(int armarioId, int livroId);
  int quantidadeLivrosArmario(int armarioId);
};