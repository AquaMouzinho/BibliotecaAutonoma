#include <iostream>
#include <string>
#include <unistd.h> // Para sleep()

#include "src/hardware/Display.cpp"
#include "src/hardware/SensorPorta.cpp"
#include "src/hardware/SensorRFID.cpp"
#include "src/hardware/TrancaDigital.cpp"

int main()
{
  Display *display = new DisplayReal();
  TrancaDigital *tranca = new TrancaDigitalReal();
  SensorRFID *rfid = new SensorRFIDReal();
  SensorPorta *sensorPorta = new SensorPortaReal();

  // Simulação de fluxo básico
  display->mostrarMensagem("Sistema de Armários Inteligentes");
  display->mostrarMensagem("Inicializando...");
  sleep(2);

  // Teste da tranca
  display->mostrarMensagem("Testando tranca digital:");
  display->mostrarMensagem("Destravando armário...");
  tranca->liberar();
  display->mostrarMensagem(tranca->estaTrancada() ? "Trancado" : "Destrancado");
  sleep(1);

  display->mostrarMensagem("Travando armário...");
  tranca->bloquear();
  display->mostrarMensagem(tranca->estaTrancada() ? "Trancado" : "Destrancado");
  sleep(1);

  // Teste do sensor de porta
  display->mostrarMensagem("\nTestando sensor de porta:");
  display->mostrarMensagem(sensorPorta->estaAberta() ? "Porta ABERTA" : "Porta FECHADA");
  sleep(1);

  // Teste do sensor RFID
  display->mostrarMensagem("\nTestando sensor RFID:");
  display->mostrarMensagem("Aproxime um livro...");

  int tentativas = 5;
  while (tentativas--)
  {
    auto tags = rfid->lerTags();
    if (!tags.empty())
    {
      display->mostrarMensagem("Livro detectado: " + tags[0]);
      break;
    }
    sleep(1);
  }

  if (tentativas <= 0)
  {
    display->mostrarMensagem("Nenhum livro detectado");
  }

  // Encerramento
  display->mostrarMensagem("\nTeste concluído!");
  sleep(2);
  display->limpar();

  // Liberar recursos
  delete display;
  delete tranca;
  delete rfid;
  delete sensorPorta;

  return 0;
}