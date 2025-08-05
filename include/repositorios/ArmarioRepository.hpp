#pragma once
#include "../model/Armario.hpp"
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
  bool criarArmario(const Armario &armario);
  bool atualizarArmario(const Armario &armario);
  bool removerArmario(int id);
  Armario *buscarPorId(int id) const;
  std::vector<Armario> buscarTodos() const;

  // Métodos específicos do domínio
  std::vector<Armario> buscarPorLocalizacao(const std::string &localizacao) const;
  bool atualizarStatus(int armarioId, const std::string &status);
  bool verificarDisponibilidade(int armarioId) const;
  std::vector<std::string> buscarLivrosNoArmario(int armarioId) const;
  bool adicionarLivro(int armarioId, std::string ISBN);
  bool removerLivro(int armarioId, std::string ISBN);
  int quantidadeLivrosArmario(int armarioId) const;
};