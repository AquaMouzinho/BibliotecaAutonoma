#include "../../include/hardware/SensorRFID.hpp"
#include <iostream>
#include <ctime>
#include <algorithm>

class SensorRFIDReal : public SensorRFID
{
private:
  std::vector<std::string> tagsPresentes = {
      "RFID-001", "RFID-002", "RFID-003"};
  std::vector<std::string> ultimasTags;

public:
  SensorRFIDReal()
  {
    srand(time(nullptr));
  }
  // Para fins de simulação
  void simularInsercaoTag(const std::string &tag)
  {
    if (std::find(tagsPresentes.begin(), tagsPresentes.end(), tag) == tagsPresentes.end())
    {
      tagsPresentes.push_back(tag);
    }
  }

  void simularRemocaoTag(const std::string &tag)
  {
    tagsPresentes.erase(
        std::remove(tagsPresentes.begin(), tagsPresentes.end(), tag),
        tagsPresentes.end());
  }

  std::vector<std::string> lerTags() const override
  {
    return tagsPresentes;
  }

  void atualizarLeitura()
  {
    ultimasTags = tagsPresentes;
  }
};
