#pragma once
#include "../entidades/Sessao.hpp"
#include "../database/IDatabaseConnector.hpp"
#include <memory>
#include <vector>

class SessaoRepository
{
private:
  IDatabaseConnector *dbConnector;

public:
  explicit SessaoRepository(IDatabaseConnector *connector);

  // Cria uma nova sessão no banco de dados
  bool criarSessao(const Sessao &sessao);

  // Atualiza uma sessão existente
  bool atualizarSessao(const Sessao &sessao);

  // Busca uma sessão ativa por ID de usuário
  std::unique_ptr<Sessao> buscarSessaoAtivaPorUsuario(int usuarioId);

  // Busca sessões por ID de armário
  std::vector<Sessao> buscarSessoesPorArmario(int armarioId);

  // Encerra todas as sessões expiradas
  int encerrarSessoesExpiradas();

  // Busca sessão por ID
  std::unique_ptr<Sessao> buscarPorId(int id);
};