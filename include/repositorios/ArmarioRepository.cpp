#include "ArmarioRepository.hpp"
#include <algorithm>

ArmarioRepository::ArmarioRepository(IDatabaseConnector *connector) 
    : dbConnector(connector) {}

bool ArmarioRepository::criarArmario(const Armario &armario) {
    // Verifica se já existe armário com o mesmo ID
    if (armario.getId() != 0) {
        json condition = {{"id", armario.getId()}};
        auto armarios = dbConnector->read("armarios", condition);
        if (!armarios.empty()) {
            return false; // ID já existe
        }
    }

    // Encontra o próximo ID disponível
    int proximoId = 1;
    auto todosArmarios = dbConnector->read("armarios", json::object());
    for (const auto& armarioJson : todosArmarios) {
        if (armarioJson["id"] >= proximoId) {
            proximoId = armarioJson["id"].get<int>() + 1;
        }
    }

    // Cria o JSON do armário
    json novoArmario;
    novoArmario["id"] = proximoId;
    novoArmario["localizacao"] = armario.getLocalizacao();
    novoArmario["disponivel"] = armario.isDisponivel();
    novoArmario["livros"] = json::array(); // Inicializa lista vazia de livros

    return dbConnector->create("armarios", novoArmario);
}

bool ArmarioRepository::atualizarArmario(const Armario &armario) {
    json condition = {{"id", armario.getId()}};
    json updates;
    updates["localizacao"] = armario.getLocalizacao();
    updates["disponivel"] = armario.isDisponivel();
    updates["livros"] = armario.getLivros();

    return dbConnector->update("armarios", condition, updates);
}

bool ArmarioRepository::removerArmario(int id) {
    // Primeiro verifica se o armário está vazio
    auto livros = buscarLivrosNoArmario(id);
    if (!livros.empty()) {
        return false; // Não pode remover armário com livros
    }

    json condition = {{"id", id}};
    return dbConnector->remove("armarios", condition);
}

Armario* ArmarioRepository::buscarPorId(int id) const {
    json condition = {{"id", id}};
    auto armarios = dbConnector->read("armarios", condition);

    if (armarios.empty()) return nullptr;

    auto armarioJson = armarios[0];
    Armario* armario = new Armario();
    armario->setId(armarioJson["id"]);
    armario->setLocalizacao(armarioJson["localizacao"]);
    armario->setDisponivel(armarioJson["disponivel"]);
    if (armarioJson.contains("livros") && armarioJson["livros"].is_array()) {
        std::vector<std::string> livros;
        for (const auto& livro : armarioJson["livros"]) {
            livros.push_back(livro.get<std::string>());
        }
        armario->setLivros(livros);
    }

    return armario;
}

std::vector<Armario> ArmarioRepository::buscarTodos() const {
    std::vector<Armario> resultado;
    auto armariosJson = dbConnector->read("armarios", json::object());

    for (const auto& armarioJson : armariosJson) {
        Armario armario;
        armario.setId(armarioJson["id"]);
        armario.setLocalizacao(armarioJson["localizacao"]);
        armario.setDisponivel(armarioJson["disponivel"]);
        if (armarioJson.contains("livros") && armarioJson["livros"].is_array()) {
            std::vector<std::string> livros;
            for (const auto& livro : armarioJson["livros"]) {
                livros.push_back(livro.get<std::string>());
            }
            armario.setLivros(livros);
        }
        resultado.push_back(armario);
    }

    return resultado;
}

std::vector<Armario> ArmarioRepository::buscarPorLocalizacao(const std::string &localizacao) const {
    json condition = {{"localizacao", localizacao}};
    auto armariosJson = dbConnector->read("armarios", condition);

    std::vector<Armario> resultado;
    for (const auto& armarioJson : armariosJson) {
        Armario armario;
        armario.setId(armarioJson["id"]);
        armario.setLocalizacao(armarioJson["localizacao"]);
        armario.setDisponivel(armarioJson["disponivel"]);
        if (armarioJson.contains("livros") && armarioJson["livros"].is_array()){
            std::vector<std::string> livros;
            for (const auto& livro : armarioJson["livros"]) {
                livros.push_back(livro.get<std::string>());
            }
            armario.setLivros(livros);
        }
        resultado.push_back(armario);
    }

    return resultado;
}

bool ArmarioRepository::atualizarStatus(int armarioId, const std::string &status) {
    bool disponivel = (status == "disponivel");
    json condition = {{"id", armarioId}};
    json updates = {{"disponivel", disponivel}};
    return dbConnector->update("armarios", condition, updates);
}

bool ArmarioRepository::verificarDisponibilidade(int armarioId) const {
    json condition = {
        {"id", armarioId},
        {"disponivel", true}
    };
    auto armarios = dbConnector->read("armarios", condition);
    return !armarios.empty();
}

std::vector<std::string> ArmarioRepository::buscarLivrosNoArmario(int armarioId) const {
    json condition = {{"id", armarioId}};
    auto armarios = dbConnector->read("armarios", condition);

    if (armarios.empty()) return {};

    auto armarioJson = armarios[0];
    std::vector<std::string> livros;

    if (armarioJson.contains("livros") && armarioJson["livros"].is_array()) {
        for (const auto& livroISBN : armarioJson["livros"]) {
            livros.push_back(livroISBN.get<std::string>());
        }
    }

    return livros;
}

bool ArmarioRepository::adicionarLivro(int armarioId, std::string livroISBN) {
    // Verifica se o armário existe e está disponível
    auto armario = buscarPorId(armarioId);
    if (armario == nullptr || !armario->isDisponivel()) {
        delete armario;
        return false;
    }
    delete armario;

    // Obtém a lista atual de livros
    auto livros = buscarLivrosNoArmario(armarioId);

    // Verifica se o livro já está no armário
    if (std::find(livros.begin(), livros.end(), livroISBN) != livros.end()) {
        return false;
    }

    if(livroISBN.empty()) 
        return false;
    
    // Adiciona o livro à lista
    livros.push_back(livroISBN);

    // Atualiza no banco de dados
    json condition = {{"id", armarioId}};
    json updates = {{"livros", livros}};
    return dbConnector->update("armarios", condition, updates);
}

bool ArmarioRepository::removerLivro(int armarioId, std::string ISBN) {
    // Obtém a lista atual de livros
    auto livros = buscarLivrosNoArmario(armarioId);

    // Remove o livro da lista
    auto it = std::remove(livros.begin(), livros.end(), ISBN);
    if (it == livros.end()) {
        return false; // Livro não encontrado no armário
    }
    livros.erase(it, livros.end());

    // Atualiza no banco de dados
    json condition = {{"id", armarioId}};
    json updates = {{"livros", livros}};
    return dbConnector->update("armarios", condition, updates);
}

int ArmarioRepository::quantidadeLivrosArmario(int armarioId) const {
    return buscarLivrosNoArmario(armarioId).size();
}