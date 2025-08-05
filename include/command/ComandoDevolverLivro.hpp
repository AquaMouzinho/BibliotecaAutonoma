#ifndef COMANDO_DEVOLVER_LIVRO_HPP
#define COMANDO_DEVOLVER_LIVRO_HPP

#include "Comando.hpp"
#include "../service/EmprestimoService.hpp"

class ComandoDevolverLivro : public Comando
{
  EmprestimoService *service;
  std::string tagRFID;
  Emprestimo emprestimo;
  bool executado = false;

public:
  ComandoDevolverLivro(EmprestimoService *service,
                       const std::string &tagRFID) : service(service), tagRFID(tagRFID) {};

  void executar() override;
  void desfazer() override;
  std::string getMensagem() const override;
};

#endif