#ifndef COMANDO_EMPRESTAR_LIVRO_HPP
#define COMANDO_EMPRESTAR_LIVRO_HPP

#include "Comando.hpp"
#include "../service/EmprestimoService.hpp"

class ComandoEmprestarLivro : public Comando
{
  EmprestimoService *service;
  std::string matricula;
  std::string tagRFID;
  Emprestimo emprestimo;
  bool executado = false;

public:
  ComandoEmprestarLivro(EmprestimoService *service,
                        const std::string &matricula,
                        const std::string &tagRFID) : service(service),
                                                      matricula(matricula), tagRFID(tagRFID) {};

  void executar() override;
  void desfazer() override;
  std::string getMensagem() const override;
};

#endif