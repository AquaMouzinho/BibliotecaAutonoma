#include "NotificacaoService.hpp"
#include "../observer/NotificacaoHandler.hpp"
#include <stdexcept>
#include <iostream>

NotificacaoService::NotificacaoService(NotificacaoRepository* repo)
    : repository(repo) {
        try{
            if(repo){
                adicionarObservador(new NotificacaoHandler(repo));    
            }
            else {
                throw std::invalid_argument("Repositorio de notificacao invalido");
            }
        }catch(std::exception &e){
            std::cerr << "Erro ao criar NotificacaoService: " << e.what() << std::endl;
        }
}

void NotificacaoService::notificar(const std::string& matricula, const std::string& mensagem) {
    // Persiste no banco e notifica todos os observers
    notificarObservadores(matricula, mensagem);
}

std::vector<Notificacao> NotificacaoService::buscarNotificacoes(const std::string& matricula) const {
    return repository->buscarPorUsuario(matricula);
}

void NotificacaoService::limparNotificacoes(const std::string& matricula) {
    repository->removerTodasDoUsuario(matricula);
}