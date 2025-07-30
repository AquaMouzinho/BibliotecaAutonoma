#ifndef WEB_SYSTEM_FACADE_H
#define WEB_SYSTEM_FACADE_H

#include "LivroController.h"
#include "UsuarioController.h"
#include "PermissaoController.h"
#include <string>

class WebSystemFacade {
private:
    LivroController* livroController;
    UsuarioController* usuarioController;
    PermissaoController* permissaoController;

public:
    WebSystemFacade(LivroController* lc, UsuarioController* uc, PermissaoController* pc);

    void notificarUsuario(int usuarioId, const std::string& mensagem);
    std::string gerarRelatorio(int usuarioId);
};

#endif // WEB_SYSTEM_FACADE_H
