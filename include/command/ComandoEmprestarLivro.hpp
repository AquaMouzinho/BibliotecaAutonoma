#ifndef COMANDO_EMPRESTAR_HPP
#define COMANDO_EMPRESTAR_HPP

#include <string>
#include "Comando.hpp"
#include "../entidades/Usuario.hpp"
#include "../entidades/Livro.hpp"
#include "../service/BibliotecaService.hpp"

class ComandoEmprestarLivro : public Comando
{
public:
  void executar() override;
  std::string getNome() const override { return "Emprestar"; };

private:
  Livro *livro;
  Usuario *usuario;
  BibliotecaService *servico;
};

#endif