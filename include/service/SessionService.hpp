#pragma once
#include "../repository/SessaoRepository.hpp"
#include "../repository/UsuarioRepository.hpp"
#include "../repository/ArmarioRepository.hpp"
#include "../entidades/Sessao.hpp"
#include "../state/EstadoSessao.hpp"
#include <memory>
#include <chrono>

class SessionService
{
private:
  SessaoRepository *sessaoRepository;
  UsuarioRepository *usuarioRepository;
  ArmarioRepository *armarioRepository;
  std::unique_ptr<EstadoSessao> estadoAtual;

  void transicionarEstado(std::unique_ptr<EstadoSessao> novoEstado);

public:
  SessionService(SessaoRepository *sessaoRepo,
                 UsuarioRepository *usuarioRepo,
                 ArmarioRepository *armarioRepo);

  bool iniciarSessao(int usuarioId, int armarioId);
  bool encerrarSessao(int sessaoId);
  bool verificarSessaoAtiva(int usuarioId);
  std::shared_ptr<Sessao> getSessaoAtual(int usuarioId);
  void verificarTimeoutSessao();
  bool liberarArmario(int sessaoId);
};