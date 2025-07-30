#pragma once
#include "../hardware/TrancaDigital.hpp"
#include "../hardware/Display.hpp"
#include "../hardware/SensorRFID.hpp"
#include "../hardware/SensorPorta.hpp"
#include <memory>

class HardwareSystemFacade
{
private:
  std::unique_ptr<TrancaDigital> tranca;
  std::unique_ptr<Display> display;
  std::unique_ptr<SensorRFID> sensorRFID;
  std::unique_ptr<SensorPorta> sensorPorta;

public:
  HardwareSystemFacade(std::unique_ptr<TrancaDigital> tranca,
                       std::unique_ptr<Display> display,
                       std::unique_ptr<SensorRFID> sensorRFID,
                       std::unique_ptr<SensorPorta> sensorPorta);

  void travarArmario();
  void destravarArmario();
  bool isArmarioTravado() const;
  void mostrarMensagemDisplay(const std::string &mensagem);
  std::string lerInputDisplay();
  void limparDisplay();
  std::vector<std::string> lerTagsLivros();
  bool verificarTagPresente(const std::string &tag);
  bool isPortaAberta() const;
  bool autenticarUsuario();
  void registrarLivrosRetirados();
};