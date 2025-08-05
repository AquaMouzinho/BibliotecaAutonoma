#ifndef NOTIFICACAO_SERVICE_HPP
#define NOTIFICACAO_SERVICE_HPP

#include "../observer/Subject.hpp"
#include "../observer/NotificacaoHandler.hpp"
#include "../repositorios/NotificacaoRepository.hpp"
#include <vector>

class NotificacaoService : public Subject {
private:
    NotificacaoRepository* repository;

public:
    explicit NotificacaoService(NotificacaoRepository* repo);

    void notificar(const std::string& matricula, const std::string& mensagem);
    std::vector<Notificacao> buscarNotificacoes(const std::string& matricula) const;
    void marcarComoLida(const std::string& matricula, int notificacaoId);
    void limparNotificacoes(const std::string& matricula);
};

#endif