#ifndef NOTIFICACAO_HANDLER_HPP
#define NOTIFICACAO_HANDLER_HPP

#include "Observador.hpp"
#include "../repositorios/NotificacaoRepository.hpp"

class NotificacaoHandler : public Observador {
    NotificacaoRepository* repository;

public:
    explicit NotificacaoHandler(NotificacaoRepository* repo);
    void atualizar(const std::string& matricula, const std::string& mensagem) override;
};

#endif