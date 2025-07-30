#include "../../include/service/ArmarioService.hpp"

ArmarioService::ArmarioService(ArmarioRepository *armarioRepo,
                               LivroRepository *livroRepo,
                               EmprestimoRepository *emprestimoRepo,
                               TrancaDigital *tranca,
                               SensorPorta *sensorPorta)
    : armarioRepository(armarioRepo),
      livroRepository(livroRepo),
      emprestimoRepository(emprestimoRepo),
      tranca(tranca),
      sensorPorta(sensorPorta) {}

bool ArmarioService::abrirArmario(int armarioId)
{
  if (armarioRepository->verificarDisponibilidade(armarioId))
  {
    tranca->liberar();
    return true;
  }
  return false;
}

bool ArmarioService::fecharArmario(int armarioId)
{
  if (sensorPorta->estaAberta())
  {
    return false;
  }
  tranca->bloquear();
  return true;
}

bool ArmarioService::adicionarLivro(int armarioId, int livroId)
{
  if (!livroRepository->livroEstaDisponivel(livroId))
  {
    return false;
  }
  return armarioRepository->adicionarLivro(armarioId, livroId);
}