#include "NotificacaoRepository.hpp"
#include <ctime>
#include <iomanip>
#include <sstream>

NotificacaoRepository::NotificacaoRepository(IDatabaseConnector *connector) 
    : dbConnector(connector) {}

bool NotificacaoRepository::criarNotificacao(const Notificacao &notificacao) {
    // Verifica se já existe notificação com o mesmo ID
    if (notificacao.getId() != 0) {
        json condition = {{"id", notificacao.getId()}};
        auto notificacoes = dbConnector->read("notificacoes", condition);
        if (!notificacoes.empty()) {
            return false; // ID já existe
        }
    }

    // Verifica se existe usuário
    if (notificacao.getUsuarioMatricula().empty())
        return false;

    // Gera timestamp atual se não foi fornecido
    std::string data_criacao = notificacao.getDataCriacao();
    if (data_criacao.empty()) {
        auto now = std::time(nullptr);
        auto tm = *std::localtime(&now);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        data_criacao = oss.str();
    }

    // Encontra o próximo ID disponível
    int proximoId = 1;
    auto todasNotificacoes = dbConnector->read("notificacoes", json::object());
    for (const auto& notificacaoJson : todasNotificacoes) {
        if (notificacaoJson["id"] >= proximoId) {
            proximoId = notificacaoJson["id"].get<int>() + 1;
        }
    }

    // Cria o JSON da notificação
    json novaNotificacao;
    novaNotificacao["id"] = proximoId;
    novaNotificacao["usuario_matricula"] = notificacao.getUsuarioMatricula();
    novaNotificacao["mensagem"] = notificacao.getMensagem();
    novaNotificacao["data_criacao"] = data_criacao;
    novaNotificacao["lida"] = notificacao.isLida();

    return dbConnector->create("notificacoes", novaNotificacao);
}

std::vector<Notificacao> NotificacaoRepository::buscarPorUsuario(std::string usuariomat, bool apenasNaoLidas) {
    json condition = {{"usuario_matricula", usuariomat}};
    if (apenasNaoLidas) {
        condition["lida"] = false;
    }

    auto notificacoesJson = dbConnector->read("notificacoes", condition);

    std::vector<Notificacao> resultado;
    for (const auto& notificacaoJson : notificacoesJson) {
        Notificacao notificacao(
            notificacaoJson["id"],
            notificacaoJson["usuario_matricula"],
            notificacaoJson["mensagem"],
            notificacaoJson["data_criacao"]
        );
        notificacao.setLida(notificacaoJson["lida"]);
        resultado.push_back(notificacao);
    }

    // Ordena por data de criação (mais recentes primeiro)
    std::sort(resultado.begin(), resultado.end(), 
        [](const Notificacao &a, const Notificacao &b) {
            return a.getDataCriacao() > b.getDataCriacao();
        });

    return resultado;
}

bool NotificacaoRepository::marcarComoLida(int notificacaoId) {
    json condition = {{"id", notificacaoId}};
    json updates = {{"lida", true}};
    return dbConnector->update("notificacoes", condition, updates);
}

bool NotificacaoRepository::removerNotificacao(int notificacaoId) {
    json condition = {{"id", notificacaoId}};
    return dbConnector->remove("notificacoes", condition);
}

int NotificacaoRepository::removerTodasDoUsuario(std::string usuariomat) {
    json condition = {{"usuario_matricula", usuariomat}};
    auto notificacoes = dbConnector->read("notificacoes", condition);
    int removidas = 0;

    for (const auto& notificacao : notificacoes) {
        if (dbConnector->remove("notificacoes", {{"id", notificacao["id"]}})) {
            removidas++;
        }
    }

    return removidas;
}

Notificacao* NotificacaoRepository::buscarPorId(int notificacaoId) {
    json condition = {{"id", notificacaoId}};
    auto notificacoes = dbConnector->read("notificacoes", condition);

    if (notificacoes.empty()) return nullptr;

    auto notificacaoJson = notificacoes[0];
    Notificacao* notificacao = new Notificacao(
        notificacaoJson["id"],
        notificacaoJson["usuario_matricula"],
        notificacaoJson["mensagem"],
        notificacaoJson["data_criacao"]
    );
    notificacao->setLida(notificacaoJson["lida"]);

    return notificacao;
}

int NotificacaoRepository::criarEmLote(const std::vector<std::string> &usuariosMats, const std::string &mensagem) {
    if (usuariosMats.empty() || mensagem.empty()) return 0;

    // Obtém a data atual
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    std::string data_criacao = oss.str();

    // Encontra o próximo ID disponível
    int proximoId = 1;
    auto todasNotificacoes = dbConnector->read("notificacoes", json::object());
    for (const auto& notificacaoJson : todasNotificacoes) {
        if (notificacaoJson["id"] >= proximoId) {
            proximoId = notificacaoJson["id"].get<int>() + 1;
        }
    }

    int criadas = 0;
    for (const auto& usuariosMat : usuariosMats) {
        json novaNotificacao;
        novaNotificacao["id"] = proximoId++;
        novaNotificacao["usuario_matricula"] = usuariosMat;
        novaNotificacao["mensagem"] = mensagem;
        novaNotificacao["data_criacao"] = data_criacao;
        novaNotificacao["lida"] = false;

        if (dbConnector->create("notificacoes", novaNotificacao)) {
            criadas++;
        }
    }

    return criadas;
}