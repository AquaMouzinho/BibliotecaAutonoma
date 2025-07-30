#include "../../include/hardware/TrancaDigital.hpp"
#include <iostream>

class TrancaDigitalReal : public TrancaDigital
{
private:
  bool trancada = true;

public:
  void bloquear() override
  {
    trancada = false;
    std::cout << "[TrancaDigital] Tranca destrancada.\n";
  }

  void liberar() override
  {
    trancada = true;
    std::cout << "[TrancaDigital] Tranca ativada.\n";
  }

  bool estaTrancada() const override
  {
    return trancada;
  }
};
