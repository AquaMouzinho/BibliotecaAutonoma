#pragma once
#include "Comando.hpp"
#include "../service/EmprestimoService.hpp"

class ComandoDevolverLivro : public Comando
{
private:
  EmprestimoService *emprestimoService;
  int emprestimoId;
  bool devolvidoComSucesso;

public:
  ComandoDevolverLivro(EmprestimoService *emprestimoService,
                       int emprestimoId);

  void executar() override;

  bool desfazer();
};