#ifndef WEB_SYSTEM_FACADE_H
#define WEB_SYSTEM_FACADE_H

#include "../web/LivroController.hpp"
#include "../web/UsuarioController.hpp"
#include "../web/PermissaoController.hpp"
#include <string>

class WebSystemFacade
{
private:
    LivroController *livroController;
    UsuarioController *usuarioController;
    PermissaoController *permissaoController;

public:
    WebSystemFacade(LivroController *lc, UsuarioController *uc, PermissaoController *pc);

    void notificarUsuario(int usuarioId, const std::string &mensagem);
    std::string gerarRelatorio(int usuarioId);
};

#endif // WEB_SYSTEM_FACADE_H
