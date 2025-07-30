#include "../../include/facade/HardwareSystemFacade.hpp"

HardwareSystemFacade::HardwareSystemFacade(
    std::unique_ptr<TrancaDigital> tranca,
    std::unique_ptr<Display> display,
    std::unique_ptr<SensorRFID> sensorRFID,
    std::unique_ptr<SensorPorta> sensorPorta)
    : tranca(std::move(tranca)),
      display(std::move(display)),
      sensorRFID(std::move(sensorRFID)),
      sensorPorta(std::move(sensorPorta)) {}

void HardwareSystemFacade::travarArmario()
{
  tranca->bloquear();
  mostrarMensagemDisplay("Armário travado com sucesso");
}

void HardwareSystemFacade::destravarArmario()
{
  tranca->liberar();
  mostrarMensagemDisplay("Armário destravado");
}

bool HardwareSystemFacade::isArmarioTravado() const
{
  return tranca->estaTrancada();
}

void HardwareSystemFacade::mostrarMensagemDisplay(const std::string &mensagem)
{
  display->mostrarMensagem(mensagem);
}

std::string HardwareSystemFacade::lerInputDisplay()
{
  return display->solicitarMatricula();
}

void HardwareSystemFacade::limparDisplay()
{
  display->limpar();
}

std::vector<std::string> HardwareSystemFacade::lerTagsLivros()
{
  return sensorRFID->lerTags();
}

bool HardwareSystemFacade::verificarTagPresente(const std::string &tag)
{
  // return sensorRFID->lerTags();
}

bool HardwareSystemFacade::isPortaAberta() const
{
  return sensorPorta->estaAberta();
}

bool HardwareSystemFacade::autenticarUsuario()
{
  limparDisplay();
  mostrarMensagemDisplay("Digite sua matrícula:");
  std::string matricula = lerInputDisplay();

  mostrarMensagemDisplay("Digite sua senha:");
  std::string senha = lerInputDisplay();

  // Validação básica
  return !matricula.empty() && !senha.empty();
}

void HardwareSystemFacade::registrarLivrosRetirados()
{
  mostrarMensagemDisplay("Aproxime os livros...");

  while (!isPortaAberta())
  {
    auto tags = lerTagsLivros();
    if (!tags.empty())
    {
      std::string mensagem = "Livro detectado: " + tags.front();
      mostrarMensagemDisplay(mensagem);
    }
  }

  mostrarMensagemDisplay("Retirada registrada com sucesso");
}