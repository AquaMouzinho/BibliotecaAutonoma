#ifndef COMANDO_DEVOLVER_HPP
#define COMANDO_DEVOLVER_HPP

#include <string>
#include "Comando.hpp"
#include "../entidades/Usuario.hpp"
#include "../entidades/Livro.hpp"
#include "../service/BibliotecaService.hpp"

class ComandoDevolverLivro : public Comando
{
public:
  void executar() override;
  std::string getNome() const override { return "Devolver"; };

private:
  Livro *livro;
  Usuario *usuario;
  BibliotecaService *servico;
};

#endif