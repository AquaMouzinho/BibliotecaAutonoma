#pragma once
#include "../model/Sessao.hpp"
#include "../database/IDatabaseConnector.hpp"
#include <memory>
#include <vector>

class SessaoRepository
{
private:
  IDatabaseConnector *dbConnector;

public:
  explicit SessaoRepository(IDatabaseConnector *connector);

  // CRUD
  bool criarSessao(const Sessao &sessao);
  bool atualizarSessao(const Sessao &sessao);
  bool removerSessao(const std::string sessaoId);
  int encerrarSessoesExpiradas();

  Sessao* buscarSessaoPorId(int id);
  Sessao* buscarSessaoAtivaPorUsuario(std::string usuario_matricula);
  std::vector<Sessao> buscarSessoesPorArmario(int armarioId);
  std::vector<Sessao> buscarSessoesPorUsuario(std::string usuario_matricula);
  std::vector<Sessao> buscarSessoesPorTipo(std::string tipo);
  std::vector<Sessao> buscarSessoesPorDataCriacao(std::string data_criacao);
  std::vector<Sessao> buscarSessoesPorDataFechamento(std::string data_fechamento);
  std::vector<Sessao> buscarSessoesPorTimer(int timer);

  bool sessaoExiste(const std::string& sessaoId) const;
};