#include "LivroRepository.hpp"
#include <algorithm>

LivroRepository::LivroRepository(IDatabaseConnector *connector) : dbConnector(connector) {}

bool LivroRepository::criarLivro(Livro &livro) {
    // Verifica se já existe livro com o mesmo RFID
    if (!livro.getTagRfid().empty()) {
        json condition = {{"tag_rfid", livro.getTagRfid()}};
        auto livros = dbConnector->read("livros", condition);
        if (!livros.empty()) {
            return false; // RFID já está em uso
        }
    }

    // Verifica se existe usuário doador
    if (livro.getMatriculaDoador().empty())
        return false;

    // Encontra o próximo ID disponível
    int proximoId = 1;
    auto todosLivros = dbConnector->read("livros", json::object());
    for (const auto& livroJson : todosLivros) {
        if (livroJson["id"] >= proximoId) {
            proximoId = livroJson["id"].get<int>() + 1;
        }
    }

    // Cria o JSON do livro
    json novoLivro;
    novoLivro["id"] = proximoId;
    novoLivro["isbn"] = livro.getIsbn();
    novoLivro["titulo"] = livro.getTitulo();
    novoLivro["autor"] = livro.getAutor();
    novoLivro["tag_rfid"] = livro.getTagRfid();
    novoLivro["matricula_doador"] = livro.getMatriculaDoador();
    novoLivro["id_armario"] = livro.getIdArmario();
    novoLivro["disponivel"] = livro.isDisponivel();

    return dbConnector->create("livros", novoLivro);
}

bool LivroRepository::atualizarLivro(const Livro &livro) {
    json condition = {{"isbn", livro.getIsbn()}};
    json updates;
    updates["titulo"] = livro.getTitulo();
    updates["autor"] = livro.getAutor();
    updates["tag_rfid"] = livro.getTagRfid();
    updates["matricula_doador"] = livro.getMatriculaDoador();
    updates["id_armario"] = livro.getIdArmario();
    updates["disponivel"] = livro.isDisponivel();

    return dbConnector->update("livros", condition, updates);
}

bool LivroRepository::removerLivro(std::string isbn) {
    json condition = {{"isbn", isbn}};
    return dbConnector->remove("livros", condition);
}

Livro* LivroRepository::buscarPorISBN(std::string isbn) const {
    json condition = {{"isbn", isbn}};
    auto livros = dbConnector->read("livros", condition);

    if (livros.empty()) return nullptr;

    auto livroJson = livros[0];
    return new Livro(
        livroJson["isbn"],
        livroJson["titulo"],
        livroJson["autor"],
        livroJson["tag_rfid"],
        livroJson["matricula_doador"],
        livroJson["id_armario"],
        livroJson["disponivel"]
    );
}

std::vector<Livro> LivroRepository::buscarTodos() const {
    std::vector<Livro> resultado;
    auto livrosJson = dbConnector->read("livros", json::object());

    for (const auto& livroJson : livrosJson) {
        Livro livro(
            livroJson["isbn"],
            livroJson["titulo"],
            livroJson["autor"],
            livroJson["tag_rfid"],
            livroJson["matricula_doador"],
            livroJson["id_armario"],
            livroJson["disponivel"]
        );
        resultado.push_back(livro);
    }

    return resultado;
}

Livro* LivroRepository::buscarPorRfid(const std::string &rfid) const {
    json condition = {{"tag_rfid", rfid}};
    auto livros = dbConnector->read("livros", condition);

    if (livros.empty()) return nullptr;

    auto livroJson = livros[0];
    return new Livro(
        livroJson["isbn"],
        livroJson["titulo"],
        livroJson["autor"],
        livroJson["tag_rfid"],
        livroJson["matricula_doador"],
        livroJson["id_armario"],
        livroJson["disponivel"]
    );
}

std::vector<Livro> LivroRepository::buscarPorTitulo(const std::string &titulo) const {
    json condition = {{"titulo", titulo}};
    auto livrosJson = dbConnector->read("livros", condition);

    std::vector<Livro> resultado;
    for (const auto& livroJson : livrosJson) {
        Livro livro(
            livroJson["isbn"],
            livroJson["titulo"],
            livroJson["autor"],
            livroJson["tag_rfid"],
            livroJson["matricula_doador"],
            livroJson["id_armario"],
            livroJson["disponivel"]
        );
        resultado.push_back(livro);
    }

    return resultado;
}

std::vector<Livro> LivroRepository::buscarPorAutor(const std::string &autor) const {
    json condition = {{"autor", autor}};
    auto livrosJson = dbConnector->read("livros", condition);

    std::vector<Livro> resultado;
    for (const auto& livroJson : livrosJson) {
        Livro livro(
            livroJson["isbn"],
            livroJson["titulo"],
            livroJson["autor"],
            livroJson["tag_rfid"],
            livroJson["matricula_doador"],
            livroJson["id_armario"],
            livroJson["disponivel"]
        );
        resultado.push_back(livro);
    }

    return resultado;
}

std::vector<Livro> LivroRepository::buscarLivrosDisponiveis() const {
    json condition = {{"disponivel", true}};
    auto livrosJson = dbConnector->read("livros", condition);

    std::vector<Livro> resultado;
    for (const auto& livroJson : livrosJson) {
        Livro livro(
            livroJson["isbn"],
            livroJson["titulo"],
            livroJson["autor"],
            livroJson["tag_rfid"],
            livroJson["matricula_doador"],
            livroJson["id_armario"],
            livroJson["disponivel"]
        );
        resultado.push_back(livro);
    }

    return resultado;
}

std::vector<Livro> LivroRepository::buscarLivrosPorDoador(std::string usuarioDoadorMat) const {
    json condition = {{"matricula_doador", usuarioDoadorMat}};
    auto livrosJson = dbConnector->read("livros", condition);

    std::vector<Livro> resultado;
    for (const auto& livroJson : livrosJson) {
        Livro livro(
            livroJson["isbn"],
            livroJson["titulo"],
            livroJson["autor"],
            livroJson["tag_rfid"],
            livroJson["matricula_doador"],
            livroJson["id_armario"],
            livroJson["disponivel"]
        );
        resultado.push_back(livro);
    }

    return resultado;
}

bool LivroRepository::atualizarStatusLivro(std::string isbn, const std::string &status) {
    bool disponivel = (status == "disponivel");
    json condition = {{"isbn", isbn}};
    json updates = {{"disponivel", disponivel}};
    return dbConnector->update("livros", condition, updates);
}

bool LivroRepository::livroEstaDisponivel(std::string isbn) const {
    json condition = {
        {"isbn", isbn},
        {"disponivel", true}
    };
    auto livros = dbConnector->read("livros", condition);
    return !livros.empty();
}

bool LivroRepository::associarRfid(std::string isbn, const std::string &rfid) {
    // Verifica se o RFID já está em uso por outro livro
    json verificaRfid = {{"tag_rfid", rfid}};
    auto livrosComRfid = dbConnector->read("livros", verificaRfid);
    if (!livrosComRfid.empty() && livrosComRfid[0]["isbn"] != isbn) {
        return false; // RFID já está em uso
    }

    json condition = {{"isbn", isbn}};
    json updates = {{"tag_rfid", rfid}};
    return dbConnector->update("livros", condition, updates);
}