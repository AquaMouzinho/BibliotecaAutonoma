#include "../../include/service/SessionService.hpp"
#include "../../include/state/SessaoAtiva.hpp"
#include "../../include/state/SessaoInativa.hpp"
#include <chrono>
#include <thread>

SessionService::SessionService(SessaoRepository *sessaoRepo,
                               UsuarioRepository *usuarioRepo,
                               ArmarioRepository *armarioRepo)
    : sessaoRepository(sessaoRepo),
      usuarioRepository(usuarioRepo),
      armarioRepository(armarioRepo),
      estadoAtual(std::make_unique<SessaoInativa>()) {}

bool SessionService::iniciarSessao(int usuarioId, int armarioId)
{
  if (usuarioRepository->usuarioPossuiEmprestimosAtrasados(usuarioId))
  {
    return false;
  }

  // Sessao novaSessao(usuarioId, armarioId);
  // if (sessaoRepository->criarSessao(novaSessao))
  //{
  transicionarEstado(std::make_unique<SessaoAtiva>());
  armarioRepository->atualizarStatus(armarioId, "ocupado");
  return true;
  //}
  // return false;
}

bool SessionService::encerrarSessao(int sessaoId)
{
  auto sessao = sessaoRepository->buscarPorId(sessaoId);
  if (sessao)
  {
    sessao->setTipo("encerrada");
    sessaoRepository->atualizarSessao(*sessao);
    armarioRepository->atualizarStatus(sessao->getArmario()->getId(), "disponivel");
    transicionarEstado(std::make_unique<SessaoInativa>());
    return true;
  }
  return false;
}

void SessionService::verificarTimeoutSessao()
{
}
