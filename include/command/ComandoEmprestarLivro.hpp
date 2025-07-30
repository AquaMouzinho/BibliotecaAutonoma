#pragma once
#include "Comando.hpp"
#include "../service/EmprestimoService.hpp"

class ComandoEmprestarLivro : public Comando
{
private:
  EmprestimoService *emprestimoService;
  int livroId;
  int usuarioId;
  int armarioId;
  bool emprestimoRealizado;

public:
  ComandoEmprestarLivro(EmprestimoService *emprestimoService,
                        int livroId,
                        int usuarioId,
                        int armarioId);

  void executar() override;
  bool desfazer();
};