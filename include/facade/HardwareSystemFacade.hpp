#ifndef HARDWARE_SYSTEM_FACADE_H
#define HARDWARE_SYSTEM_FACADE_H

#include "../service/ArmarioService.hpp"
#include "../service/SessionService.hpp"
#include "../service/RFIDService.hpp"

#include <string>

class WebSystemFacade
{
private:
  ArmarioService *armarioService;
  SessionService *sessionService;
  RFIDService *rfidService;

public:
  void liberarArmario(int armarioId, const std::string &matricula, const std::string senha);
  void processarEventosRFID();
  void finalizarUsoArmario(int armarioId);
};

#endif // WEB_SYSTEM_FACADE_H
