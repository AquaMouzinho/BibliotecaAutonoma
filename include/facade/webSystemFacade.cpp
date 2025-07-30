#include "WebSystemFacade.h"
#include <iostream>

WebSystemFacade::WebSystemFacade(LivroController* lc, UsuarioController* uc, PermissaoController* pc)
    : livroController(lc), usuarioController(uc), permissaoController(pc) {}

void WebSystemFacade::notificarUsuario(int usuarioId, const std::string& mensagem) {
    if (usuarioController) {
        usuarioController->enviarNotificacao(usuarioId, mensagem);
    } else {
        std::cerr << "UsuarioController não inicializado.\n";
    }
}

std::string WebSystemFacade::gerarRelatorio(int usuarioId) {
    if (livroController && usuarioController) {
        return livroController->compilarRelatorioDeLivros(usuarioId);
    } else {
        std::cerr << "Controllers não inicializados.\n";
        return "Erro ao gerar relatório.";
    }
}