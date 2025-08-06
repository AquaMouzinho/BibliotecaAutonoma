#include <iostream>
#include <string>

#include "include/database/DatabaseConnectorProxy.hpp"

#include "include/repositorios/LivroRepository.hpp"
#include "include/repositorios/EmprestimoRepository.hpp"
#include "include/repositorios/UsuarioRepository.hpp"
#include "include/repositorios/NotificacaoRepository.hpp"
#include "include/repositorios/ArmarioRepository.hpp"
#include "include/repositorios/SessaoRepository.hpp"

#include "include/service/EmprestimoService.hpp"
#include "include/service/NotificacaoService.hpp"
#include "include/service/SessionService.hpp"
#include "include/service/RFIDService.hpp"
#include "include/service/ArmarioService.hpp"
#include "include/service/AutenticacaoService.hpp"

#include "include/hardware/SimuladorRFID.hpp"
#include "include/hardware/SimuladorSensorPorta.hpp"
#include "include/hardware/SimuladorTrancaDigital.hpp"
#include "include/hardware/SimuladorArmario.hpp"

#include "include/facade/HardwareSystemFacade.hpp"
#include "SimuladorConsole.hpp"

int main()
{
    DatabaseConnectorProxy db("test");

    // Inicializa repositórios
    LivroRepository livroRepo(&db);
    EmprestimoRepository emprestimoRepo(&db);
    UsuarioRepository usuarioRepo(&db);
    NotificacaoRepository notificacaoRepo(&db);
    ArmarioRepository armarioRepo(&db);
    SessaoRepository sessaoRepo(&db);

    // Inicializa hardware
    SimuladorRFID sensorRFID(armarioRepo, 1);
    SimuladorSensorPorta sensorPorta(1);
    SimuladorTrancaDigital trancaDigital(1);

    // Inicializa serviços
    NotificacaoService notificacaoService(&notificacaoRepo);
    EmprestimoService emprestimoService(&emprestimoRepo, &usuarioRepo, &livroRepo, &notificacaoService);
    AutenticacaoService authService(&usuarioRepo, &emprestimoRepo);
    ArmarioService armarioService(armarioRepo, livroRepo);
    SessionService sessionService(&sessaoRepo, &authService, &sensorPorta, &trancaDigital);
    RFIDService rfidService(&emprestimoService, &sessionService, &armarioService, &sensorRFID, &sensorPorta, 1);

    // Inicializa simulador de hardware
    SimuladorArmario hardwareSimulator(trancaDigital, sensorPorta, sensorRFID);
    HardwareSystemFacade facade(sessionService, rfidService, hardwareSimulator);

    // Inicia o simulador de console
    SimuladorConsole console(
        facade,
        usuarioRepo,
        emprestimoRepo,
        livroRepo);

    console.iniciar();
    return 0;
}