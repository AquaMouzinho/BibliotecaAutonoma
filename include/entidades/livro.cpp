#include "Livro.h"
#include "Usuario.h"
#include "Armario.h"
#include "Emprestimo.h"

#include <vector>

Livro::Livro(const std::string& isbn, const std::string& titulo,
             const std::string& autor, const std::string& tagRFID,
             Usuario* proprietario, Armario* armario, bool disponivel)
    : isbn(isbn), titulo(titulo), autor(autor), tagRFID(tagRFID),
      proprietario(proprietario), armario(armario), disponivel(disponivel) {}

Emprestimo* Livro::getEmprestimoAtivo() const {
    if (!proprietario) return nullptr;

    const std::vector<Emprestimo*>& emprestimos = proprietario->getEmprestimosAtivos();
    for (Emprestimo* emp : emprestimos) {
        if (emp->getLivro() == this && emp->estaEmAberto()) {
            return emp;
        }
    }

    return nullptr;
}

Armario* Livro::getLocalizacaoAtual() const {
    return armario;
}

Usuario* Livro::getProprietario() const {
    return proprietario;
}
