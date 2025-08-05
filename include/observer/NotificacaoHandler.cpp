#include "NotificacaoHandler.hpp"
#include "../model/Notificacao.hpp"
#include "../utils/DateTimeUtils.hpp"

NotificacaoHandler::NotificacaoHandler(NotificacaoRepository* repo) 
    : repository(repo) {}

void NotificacaoHandler::atualizar(const std::string& matricula, const std::string& mensagem) {
    Notificacao notif;
    notif.setUsuarioMatricula(matricula);
    notif.setMensagem(mensagem);
    notif.setDataCriacao(DateTimeUtils::getCurrentDateTime());
    notif.setLida(false);

    repository->criarNotificacao(notif);
}