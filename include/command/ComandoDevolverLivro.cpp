#include "ComandoDevolverLivro.hpp"
#include "../model/Emprestimo.hpp"

void ComandoDevolverLivro::executar() {
    if (!executado) {
        emprestimo = service->buscarEmprestimoAtivoPorTag(tagRFID);
        if (emprestimo.getId() > 0) {
            service->encerrarEmprestimo(emprestimo.getId());
            service->notificarDonoLivro(tagRFID, "Seu livro foi devolvido: " + tagRFID);
            executado = true;
        }
    }
}

void ComandoDevolverLivro::desfazer() {
    if (executado) {
        service->criarEmprestimo(emprestimo.getUsuarioMatricula(), 
                               emprestimo.getTagLivro());
        executado = false;
    }
}

std::string ComandoDevolverLivro::getMensagem() const {
    return "Devolução realizada para livro " + tagRFID;
}