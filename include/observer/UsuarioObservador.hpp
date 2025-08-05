#ifndef USUARIO_OBSERVADOR_HPP
#define USUARIO_OBSERVADOR_HPP

#include "Observador.hpp"
#include "../model/Notificacao.hpp"
#include "../service/NotificacaoService.hpp"

class UsuarioObservador : public Observador {
    NotificacaoService* notificacaoService;

public:
    explicit UsuarioObservador(NotificacaoService* service);
    void atualizar(const std::string& matricula, const std::string& mensagem) override;
};

#endif