#pragma once
#include "include/facade/HardwareSystemFacade.hpp"
#include "include/repositorios/UsuarioRepository.hpp"
#include "include/repositorios/EmprestimoRepository.hpp"
#include "include/repositorios/LivroRepository.hpp"
#include <iostream>
#include <limits>

class SimuladorConsole
{
private:
    HardwareSystemFacade &hardwareFacade;
    UsuarioRepository &usuarioRepo;
    EmprestimoRepository &emprestimoRepo;
    LivroRepository &livroRepo;

    void limparBuffer()
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    void autenticarUsuario()
    {
        std::string matricula, senha;

        do
        {
            // system("clear || cls");
            std::cout << "\n=== AUTENTICAÇÃO ===\n";
            std::cout << "Matrícula: ";
            std::getline(std::cin, matricula);
            std::cout << "Senha: ";
            std::getline(std::cin, senha);

            if (hardwareFacade.iniciarSessao(1, matricula, senha))
            {
                hardwareFacade.monitorarOperacao();
                break;
            }
            else
            {
                std::cout << "\nFalha na autenticação! Tente novamente.\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        } while (true);
    }

    void menuPrincipal()
    {
        int escolha;
        do
        {
            // system("clear || cls");
            std::cout << "\n=== MENU PRINCIPAL ===\n";
            std::cout << "Armário: " << (hardwareFacade.isTrancado() ? "Trancado" : "Liberado") << "\n";
            std::cout << "Porta: " << (hardwareFacade.isPortaAberta() ? "Aberta" : "Fechada") << "\n";
            std::cout << "Livros no armário: " << hardwareFacade.getLivrosPresentes().size() << "\n\n";

            std::cout << "1. Encerrar sessão\n";
            if (!hardwareFacade.isPortaAberta())
            {
                std::cout << "2. Abrir porta\n";
            }
            else
            {
                std::cout << "2. Fechar porta\n";
                std::cout << "3. Realizar empréstimo\n";
                std::cout << "4. Realizar devolução\n";
            }

            std::cout << "Escolha: ";
            std::cin >> escolha;
            limparBuffer();

            switch (escolha)
            {
            case 1:
                hardwareFacade.encerrarSessao();
                return;
            case 2:
                if (!hardwareFacade.isPortaAberta())
                {
                    hardwareFacade.getSimulador().abrirPorta();
                }
                else
                {
                    hardwareFacade.getSimulador().fecharPorta();
                }
                break;
            case 3:
                if (hardwareFacade.isPortaAberta())
                    menuEmprestimo();
                break;
            case 4:
                if (hardwareFacade.isPortaAberta())
                    menuDevolucao();
                break;
            default:
                std::cout << "Opção inválida!\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        } while (true);
    }

    void menuEmprestimo()
    {
        auto livros = hardwareFacade.getLivrosPresentes();
        if (livros.empty())
        {
            std::cout << "Nenhum livro disponível no armário!\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            return;
        }

        int escolha;
        do
        {
            // system("clear || cls");
            std::cout << "=== EMPRÉSTIMO ===\n";
            std::cout << "Livros no armário:\n";

            for (int i = 0; i < livros.size(); i++)
            {
                auto livro = livroRepo.buscarPorRfid(livros[i]);
                std::cout << i + 1 << ". " << livro->getTitulo() << " (" << livros[i] << ")\n";
            }

            std::cout << "\n0. Voltar\n";
            std::cout << "Escolha o livro para emprestar: ";
            std::cin >> escolha;
            limparBuffer();

            if (escolha == 0)
                return;

            if (escolha > 0 && escolha <= livros.size())
            {
                // std::cout << "Escolha: "<< livros[escolha-1] << "\n";
                hardwareFacade.getRFIDService().processarTag(livros[escolha - 1]);

                std::this_thread::sleep_for(std::chrono::seconds(2));
                return;
            }

            std::cout << "Opção inválida!\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        } while (true);
    }

    void menuDevolucao()
    {
        std::cout << "=== DEVOLUÇÃO ===\n";
        auto usuario = usuarioRepo.buscarUsuarioPorMatricula(
            hardwareFacade.getSessionService().getSessaoAtual()->getUsuarioMatricula());

        auto emprestimos = emprestimoRepo.buscarPorUsuario(usuario->getMatricula());

        if (emprestimos.empty())
        {
            std::cout << "Nenhum empréstimo ativo!\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            return;
        }

        int escolha;
        do
        {
            // system("clear || cls");
            std::cout << "=== DEVOLUÇÃO ===\n";
            std::cout << "Seus empréstimos ativos:\n";

            for (int i = 0; i < emprestimos.size(); i++)
            {
                auto livro = livroRepo.buscarPorISBN(emprestimos[i].getLivroIsbn());
                std::cout << i + 1 << ". " << livro->getTitulo() << " (Devolver até: "
                          << emprestimos[i].getDataDevolucao() << ")\n";
            }

            std::cout << "\n0. Voltar\n";
            std::cout << "Escolha o livro para devolver: ";
            std::cin >> escolha;
            limparBuffer();

            if (escolha == 0)
                return;

            if (escolha > 0 && escolha <= emprestimos.size())
            {
                auto tag = livroRepo.buscarPorISBN(emprestimos[escolha - 1].getLivroIsbn())->getTagRfid();
                hardwareFacade.getSimulador().simularInsercaoLivro(tag);
                std::cout << "Devolução realizada com sucesso!\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                return;
            }

            std::cout << "Opção inválida!\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        } while (true);
    }

public:
    SimuladorConsole(HardwareSystemFacade &facade,
                     UsuarioRepository &uRepo,
                     EmprestimoRepository &eRepo,
                     LivroRepository &lRepo)
        : hardwareFacade(facade), usuarioRepo(uRepo),
          emprestimoRepo(eRepo), livroRepo(lRepo) {}

    void iniciar()
    {
        while (true)
        {
            autenticarUsuario();
            menuPrincipal();
        }
    }
};