#pragma once
#include "../repository/ArmarioRepository.hpp"
#include "../repository/LivroRepository.hpp"
#include "../repository/EmprestimoRepository.hpp"
#include "../hardware/TrancaDigital.hpp"
#include "../hardware/SensorPorta.hpp"
#include <vector>

class ArmarioService
{
private:
  ArmarioRepository *armarioRepository;
  LivroRepository *livroRepository;
  EmprestimoRepository *emprestimoRepository;
  TrancaDigital *tranca;
  SensorPorta *sensorPorta;

  bool verificarIntegridadeArmario(int armarioId);

public:
  ArmarioService(ArmarioRepository *armarioRepo,
                 LivroRepository *livroRepo,
                 EmprestimoRepository *emprestimoRepo,
                 TrancaDigital *tranca,
                 SensorPorta *sensorPorta);

  bool abrirArmario(int armarioId);
  bool fecharArmario(int armarioId);
  bool adicionarLivro(int armarioId, int livroId);
  bool removerLivro(int armarioId, int livroId);
  std::vector<int> listarLivrosNoArmario(int armarioId);
  bool verificarDisponibilidade(int armarioId);
  bool colocarEmManutencao(int armarioId);
  bool retornarDeManutencao(int armarioId);
};