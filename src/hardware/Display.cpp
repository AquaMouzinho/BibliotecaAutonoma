#include "../../include/hardware/Display.hpp"
#include <iostream>

class DisplayReal : public Display
{
public:
  void mostrarMensagem(const std::string &mensagem) override
  {
    std::cout << "[Display] " << mensagem << std::endl;
  }

  std::string solicitarMatricula() override
  {
    std::string matricula;
    std::cout << "Digite sua matrícula: ";
    std::getline(std::cin, matricula);
    return matricula;
  }

  std::string solicitarSenha() override
  {
    std::string senha;
    std::cout << "Digite sua senha: ";
    std::getline(std::cin, senha);
    return senha;
  }

  bool usuarioDesejaEncerrarSessao() override
  {
    std::string resposta;
    std::cout << "Deseja encerrar a sessão? (s/n): ";
    std::getline(std::cin, resposta);
    return (resposta == "s" || resposta == "S");
  }

  void limpar() override
  {
    system("cls");
  }
};