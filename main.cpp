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
    // 1. Inicialização do Database
    auto db = std::make_shared<DatabaseConnectorProxy>("test");

    // 2. Inicialização dos repositórios
    LivroRepository livroRepo(db.get());
    EmprestimoRepository emprestimoRepo(db.get());
    UsuarioRepository usuarioRepo(db.get());
    NotificacaoRepository notificacaoRepo(db.get());
    ArmarioRepository armarioRepo(db.get());
    SessaoRepository sessaoRepo(db.get());

    // 3. Inicialização do hardware simulado
    auto sensorRFID = std::make_shared<SimuladorRFID>(armarioRepo, 1);
    auto sensorPorta = std::make_shared<SimuladorSensorPorta>(1);
    auto trancaDigital = std::make_shared<SimuladorTrancaDigital>(1);
    auto hardwareSimulator = std::make_shared<SimuladorArmario>(*trancaDigital, *sensorPorta, *sensorRFID);

    // 4. Inicialização dos serviços
    NotificacaoService notificacaoService(&notificacaoRepo);
    EmprestimoService emprestimoService(&emprestimoRepo, &usuarioRepo, &livroRepo, &notificacaoService);
    AutenticacaoService authService(&usuarioRepo, &emprestimoRepo);
    ArmarioService armarioService(armarioRepo, livroRepo);

    // Corrigindo a inicialização do SessionService
    SessionService sessionService(
        &sessaoRepo,
        &authService,
        sensorPorta.get(),
        trancaDigital.get());

    // Corrigindo a inicialização do RFIDService
    RFIDService rfidService(
        &emprestimoService,
        &sessionService,
        &armarioService,
        sensorRFID.get(),
        sensorPorta.get(),
        1 // ID do armário
    );

    // 5. Inicialização da fachada
    HardwareSystemFacade hardwareFacade(
        sessionService,
        rfidService,
        *hardwareSimulator);

    // 6. Inicialização do console
    SimuladorConsole console(
        hardwareFacade,
        usuarioRepo,
        emprestimoRepo,
        livroRepo);

    console.iniciar();

    return 0;
}