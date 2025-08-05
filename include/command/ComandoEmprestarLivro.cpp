#include "ComandoEmprestarLivro.hpp"

void ComandoEmprestarLivro::executar() {
  if (!executado) {
      if(service->criarEmprestimo(matricula, tagRFID)) {
          emprestimo = service->buscarEmprestimoAtivoPorTag(tagRFID);
          service->notificarDonoLivro(tagRFID, "Seu livro foi emprestado: " + tagRFID);
      }
      executado = true;
  }
}

void ComandoEmprestarLivro::desfazer() {
  if (executado) {
      service->encerrarEmprestimo(emprestimo.getId());
      executado = false;
  }
}

std::string ComandoEmprestarLivro::getMensagem() const {
  return "Empréstimo realizado para livro " + tagRFID;
}