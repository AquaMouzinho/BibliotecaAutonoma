#include <iostream>
#include <string>
#include <limits>
#include <memory>
#include <thread>
#include <chrono>
#include <atomic>
#include <vector>
#include <iomanip>
#include <sstream>
#include <ctime>

#include "include/facade/HardwareSystemFacade.hpp"

#include "include/repositorios/UsuarioRepository.hpp"
#include "include/repositorios/EmprestimoRepository.hpp"
#include "include/repositorios/LivroRepository.hpp"
#include "include/repositorios/NotificacaoRepository.hpp"
#include "include/repositorios/SessaoRepository.hpp"
#include "include/repositorios/ArmarioRepository.hpp"

#include "include/service/NotificacaoService.hpp"
#include "include/service/EmprestimoService.hpp"
#include "include/service/AutenticacaoService.hpp"
#include "include/service/ArmarioService.hpp"
#include "include/service/RFIDService.hpp"
#include "include/service/SessionService.hpp"

#include "include/hardware/SimuladorArmario.hpp"
#include "include/hardware/SimuladorRFID.hpp"
#include "include/hardware/SimuladorSensorPorta.hpp"
#include "include/hardware/SimuladorTrancaDigital.hpp"

#include "include/database/DatabaseConnectorProxy.hpp"

int main()
{
    // Inicialização (similar ao seu código original)
    auto db = std::make_shared<DatabaseConnectorProxy>("test");

    LivroRepository livroRepo(db.get());
    EmprestimoRepository emprestimoRepo(db.get());
    UsuarioRepository usuarioRepo(db.get());
    NotificacaoRepository notificacaoRepo(db.get());
    SessaoRepository sessaoRepo(db.get());
    ArmarioRepository armarioRepo(db.get());

    auto sensorRFID = std::make_shared<SimuladorRFID>(armarioRepo, 1);
    auto sensorPorta = std::make_shared<SimuladorSensorPorta>(1);
    auto trancaDigital = std::make_shared<SimuladorTrancaDigital>(1);
    auto hardwareSimulator = std::make_shared<SimuladorArmario>(*trancaDigital, *sensorPorta, *sensorRFID);

    // Serviços
    NotificacaoService notificacaoService(&notificacaoRepo);
    EmprestimoService emprestimoService(&emprestimoRepo, &usuarioRepo, &livroRepo, &notificacaoService);
    AutenticacaoService authService(&usuarioRepo, &emprestimoRepo);
    ArmarioService armarioService(armarioRepo, livroRepo);

    SessionService sessionService(&sessaoRepo, &authService, sensorPorta.get(), trancaDigital.get());
    RFIDService rfidService(&emprestimoService, &sessionService, &armarioService, sensorRFID.get(), sensorPorta.get(), 1);

    // Fachada
    HardwareSystemFacade facade(sessionService, rfidService, *hardwareSimulator, emprestimoService);

    while (true)
    {
        std::string matricula, senha;
        std::cout << "========= BIBLIOTECA AUTONOMA - ARMARIO 1 =========\n";
        std::cout << "=== AUTENTICAÇÃO ===\n";
        std::cout << "Matrícula: ";
        std::getline(std::cin, matricula);
        std::cout << "Senha: ";
        std::getline(std::cin, senha);

        if (facade.iniciarSessao(1, matricula, senha))
        {
            std::cout << "Sessão iniciada com sucesso" << std::endl;
            std::string escolha;
            while (facade.getSessionService().temSessaoAtiva())
            {
                std::cout << "=== MENU ===\n";
                std::cout << "=== STATUS DO ARMÁRIO ===\n";
                std::cout << "Armário: " << (facade.isTrancado() ? "Trancado" : "Liberado") << "\n";
                std::cout << "Porta: " << (facade.isPortaAberta() ? "Aberta" : "Fechada") << "\n";
                std::cout << "Livros no armário: " << facade.getLivrosPresentes().size() << "\n\n";
                std::cout << "=== OPÇÕES ===\n";

                if (facade.isPortaAberta())
                {
                    std::cout << "1. Fechar porta\n";
                    if (facade.getLivrosPresentes().size() > 0)
                    {
                        std::cout << "2. Retirar livro\n";
                        std::cout << "3. Devolver livro\n";
                    }
                    else
                    {
                        std::cout << "2. Devolver livro\n";
                    }
                }
                else
                {
                    std::cout << "1. Abrir porta\n";
                    std::cout << "9. Encerrar sessão\n";
                }
                std::cout << "Escolha uma opção: ";
                std::getline(std::cin, escolha);
                if (escolha == "1")
                {
                    if (facade.isPortaAberta())
                    {
                        facade.getSimulador().fecharPorta();
                        facade.getSessionService().resetTimeout();
                    }
                    else
                    {
                        facade.getSimulador().abrirPorta();
                        facade.getSessionService().resetTimeout();
                    }
                }
                else if (escolha == "2")
                {
                    facade.getSessionService().resetTimeout();
                    if (facade.isPortaAberta())
                    {
                        if (facade.getLivrosPresentes().size() > 0)
                        {
                            std::cout << "=== RETIRAR LIVRO ===\n";
                            std::cout << "Livros no armário:\n";
                            for (const auto &livro : facade.getLivrosPresentes())
                            {
                                std::cout << "[" << livro << "] - " << livroRepo.buscarPorRfid(livro)->getTitulo() << "\n";
                            }
                            std::cout << "Digite o código [RFID] do livro: ";
                            std::string codigoLivro;
                            std::getline(std::cin, codigoLivro);
                            if (facade.getLivrosPresentes().end() == std::find(facade.getLivrosPresentes().begin(), facade.getLivrosPresentes().end(), codigoLivro))
                            {
                                std::cout << "Livro não encontrado no armário.\n";
                            }
                            else
                            {
                                facade.getRFIDService().processarTag(codigoLivro);
                                std::cout << "Livro retirado com sucesso!\n";
                            }
                        }
                        else
                        {
                            std::cout << "=== DEVOLVER LIVRO ===\n";
                            if (facade.getEmprestimoService().buscarEmprestimosAtivosPorUsuario(facade.getSessionService().getSessaoAtual()->getUsuarioMatricula()).size() > 0)
                            {
                                std::cout << "Livros emprestados:\n";
                                for (const auto &emprestimo : facade.getEmprestimoService().buscarEmprestimosAtivosPorUsuario(facade.getSessionService().getSessaoAtual()->getUsuarioMatricula()))
                                {
                                    std::cout << "[" << emprestimo.getTagLivro() << "] - " << livroRepo.buscarPorRfid(emprestimo.getTagLivro())->getTitulo() << "\n";
                                }
                                std::cout << "Digite o código [RFID] do livro: ";
                                std::string codigoLivro;
                                std::getline(std::cin, codigoLivro);
                                facade.getRFIDService().processarTag(codigoLivro);
                                std::cout << "Livro devolvido com sucesso!\n";
                            }
                            else
                            {
                                std::cout << "Você não possui livros para devolver.\n";
                            }
                        }
                    }
                    else
                    {
                        std::cout << "Abra a porta antes de retirar um livro.\n";
                    }
                }
                else if (escolha == "3")
                {
                    facade.getSessionService().resetTimeout();
                    if (facade.isPortaAberta() && facade.getLivrosPresentes().size() > 0)
                    {

                        std::cout << "=== DEVOLVER LIVRO ===\n";
                        if (facade.getEmprestimoService().buscarEmprestimosAtivosPorUsuario(facade.getSessionService().getSessaoAtual()->getUsuarioMatricula()).size() > 0)
                        {
                            std::cout << "Livros emprestados:\n";
                            for (const auto &emprestimo : facade.getEmprestimoService().buscarEmprestimosAtivosPorUsuario(facade.getSessionService().getSessaoAtual()->getUsuarioMatricula()))
                            {
                                std::cout << "[" << emprestimo.getTagLivro() << "] - " << livroRepo.buscarPorRfid(emprestimo.getTagLivro())->getTitulo() << "\n";
                            }
                            std::cout << "Digite o código [RFID] do livro: ";
                            std::string codigoLivro;
                            std::getline(std::cin, codigoLivro);
                            facade.getRFIDService().processarTag(codigoLivro);
                            std::cout << "Livro devolvido com sucesso!\n";
                        }
                        else
                        {
                            std::cout << "Você não possui livros para devolver.\n";
                        }
                    }
                    else
                    {
                        std::cout << "Abra a porta antes de devolver um livro.\n";
                    }
                }
                else if (escolha == "9")
                {
                    if (!facade.isPortaAberta())
                    {
                        std::cout << "Encerrando sessão...\n";
                        facade.encerrarSessao();
                    }
                    else
                    {
                        std::cout << "Feche a porta antes de encerrar a sessão.\n";
                    }
                }
                else
                {
                    std::cout << "Opção inválida.\n";
                }
            }
        }
        else
        {
            std::cout << "Falha na autenticação! Tente novamente.\n";
        }
    }

    return 0;
}