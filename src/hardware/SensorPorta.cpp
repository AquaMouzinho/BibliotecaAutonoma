#include "../../include/hardware/SensorPorta.hpp"
#include <iostream>

class SensorPortaReal : public SensorPorta
{
private:
  bool aberta = false;

public:
  bool estaAberta() const override
  {
    return (rand() % 2) == 0; // 50% aberta/fechada
  }
};