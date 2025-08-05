#include "EmprestimoRepository.hpp"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace std;

EmprestimoRepository::EmprestimoRepository(IDatabaseConnector *connector) 
    : dbConnector(connector) {}

bool EmprestimoRepository::criarEmprestimo(const Emprestimo &emprestimo) {
    // Verifica se já existe empréstimo com o mesmo ID
    if (emprestimo.getId() != 0) {
        json condition = {{"id", emprestimo.getId()}};
        auto emprestimos = dbConnector->read("emprestimos", condition);
        if (!emprestimos.empty()) {
            return false; // ID já existe
        }
    }

    // Verifica se existe usuário e livro
    if (emprestimo.getUsuarioMatricula().empty() || emprestimo.getLivroIsbn().empty())
        return false;

    // Encontra o próximo ID disponível
    int proximoId = 1;
    auto todosEmprestimos = dbConnector->read("emprestimos", json::object());
    for (const auto& emprestimoJson : todosEmprestimos) {
        if (emprestimoJson["id"] >= proximoId) {
            proximoId = emprestimoJson["id"].get<int>() + 1;
        }
    }

    // Obtém a data/hora atual para data_emprestimo se não foi fornecida
    string data_emprestimo = emprestimo.getDataEmprestimo();
    if (data_emprestimo.empty()) {
        auto now = time(nullptr);
        auto tm = *localtime(&now);
        ostringstream oss;
        oss << put_time(&tm, "%Y-%m-%d %H:%M:%S");
        data_emprestimo = oss.str();
    }

    // Obtém a data/hora atual e soma 15 dias para data_devolucao se não foi fornecida
    string data_devolucao = emprestimo.getDataDevolucao();
    if (data_devolucao.empty()) {
        auto now = time(nullptr);
        auto tm = *localtime(&now);
        tm.tm_mday += 15; // Adiciona 15 dias
        mktime(&tm); // Normaliza a data
        ostringstream oss;
        oss << put_time(&tm, "%Y-%m-%d %H:%M:%S");
        data_devolucao = oss.str();
    }

    // Cria o JSON do empréstimo
    json novoEmprestimo;
    novoEmprestimo["id"] = proximoId;
    novoEmprestimo["livro_isbn"] = emprestimo.getLivroIsbn();
    novoEmprestimo["usuario_matricula"] = emprestimo.getUsuarioMatricula();
    novoEmprestimo["data_emprestimo"] = data_emprestimo;
    novoEmprestimo["data_devolucao"] = data_devolucao;
    novoEmprestimo["status"] = "ativo";
    novoEmprestimo["tag_rfid"] = emprestimo.getTagLivro();

    return dbConnector->create("emprestimos", novoEmprestimo);
}

bool EmprestimoRepository::atualizarEmprestimo(const Emprestimo &emprestimo) {
    json condition = {{"id", emprestimo.getId()}};
    json updates;
    updates["livro_isbn"] = emprestimo.getLivroIsbn();
    updates["usuario_matricula"] = emprestimo.getUsuarioMatricula();
    updates["data_emprestimo"] = emprestimo.getDataEmprestimo();
    updates["data_devolucao"] = emprestimo.getDataDevolucao();
    updates["status"] = emprestimo.getStatus();
    updates["tag_rfid"] = emprestimo.getTagLivro();

    return dbConnector->update("emprestimos", condition, updates);
}

bool EmprestimoRepository::removerEmprestimo(int id) {
    json condition = {{"id", id}};
    return dbConnector->remove("emprestimos", condition);
}

bool EmprestimoRepository::removerEmprestimo(std::string usuario_matricula, std::string livro_isbn) {
    json condition = {
        {"usuario_matricula", usuario_matricula},
        {"livro_isbn", livro_isbn}
    };
    return dbConnector->remove("emprestimos", condition);
}

Emprestimo* EmprestimoRepository::buscarPorId(int id) {
    json condition = {{"id", id}};
    auto emprestimos = dbConnector->read("emprestimos", condition);

    if (emprestimos.empty()) return nullptr;

    auto emprestimoJson = emprestimos[0];
    return new Emprestimo(
        emprestimoJson["id"],
        emprestimoJson["livro_isbn"],
        emprestimoJson["usuario_matricula"],
        emprestimoJson["data_emprestimo"],
        emprestimoJson["data_devolucao"],
        emprestimoJson["status"],
        emprestimoJson["tag_rfid"]
    );
}

std::vector<Emprestimo> EmprestimoRepository::buscarTodos() {
    std::vector<Emprestimo> resultado;
    auto emprestimosJson = dbConnector->read("emprestimos", json::object());

    for (const auto& emprestimoJson : emprestimosJson) {
        resultado.emplace_back(
            emprestimoJson["id"],
            emprestimoJson["livro_isbn"],
            emprestimoJson["usuario_matricula"],
            emprestimoJson["data_emprestimo"],
            emprestimoJson["data_devolucao"],
            emprestimoJson["status"],
            emprestimoJson["tag_rfid"]
        );
    }

    return resultado;
}

std::vector<Emprestimo> EmprestimoRepository::buscarPorUsuario(string usuarioMatricula) {
    json condition = {{"usuario_matricula", usuarioMatricula}};
    auto emprestimosJson = dbConnector->read("emprestimos", condition);

    std::vector<Emprestimo> resultado;
    for (const auto& emprestimoJson : emprestimosJson) {
        resultado.emplace_back(
            emprestimoJson["id"],
            emprestimoJson["livro_isbn"],
            emprestimoJson["usuario_matricula"],
            emprestimoJson["data_emprestimo"],
            emprestimoJson["data_devolucao"],
            emprestimoJson["status"],
            emprestimoJson["tag_rfid"]
        );
    }

    // Ordena por data de empréstimo (mais recentes primeiro)
    sort(resultado.begin(), resultado.end(), 
        [](const Emprestimo &a, const Emprestimo &b) {
            return a.getDataEmprestimo() > b.getDataEmprestimo();
        });

    return resultado;
}

std::vector<Emprestimo> EmprestimoRepository::buscarPorLivro(string livroIsbn) {
    json condition = {{"livro_isbn", livroIsbn}};
    auto emprestimosJson = dbConnector->read("emprestimos", condition);

    std::vector<Emprestimo> resultado;
    for (const auto& emprestimoJson : emprestimosJson) {
        resultado.emplace_back(
            emprestimoJson["id"],
            emprestimoJson["livro_isbn"],
            emprestimoJson["usuario_matricula"],
            emprestimoJson["data_emprestimo"],
            emprestimoJson["data_devolucao"],
            emprestimoJson["status"],
            emprestimoJson["tag_rfid"]
        );
    }

    return resultado;
}

std::vector<Emprestimo> EmprestimoRepository::buscarEmprestimosAtivos() {
    json condition = {{"status", "ativo"}};
    auto emprestimosJson = dbConnector->read("emprestimos", condition);

    std::vector<Emprestimo> resultado;
    for (const auto& emprestimoJson : emprestimosJson) {
        resultado.emplace_back(
            emprestimoJson["id"],
            emprestimoJson["livro_isbn"],
            emprestimoJson["usuario_matricula"],
            emprestimoJson["data_emprestimo"],
            emprestimoJson["data_devolucao"],
            emprestimoJson["status"],
            emprestimoJson["tag_rfid"]
        );
    }

    return resultado;
}

Emprestimo EmprestimoRepository::buscarEmprestimoAtivoPorTag(std::string tag_rfid) {
    json condition = {{"tag_rfid", tag_rfid}, {"status", "ativo"}};
    auto emprestimosJson = dbConnector->read("emprestimos", condition);

    if (emprestimosJson.empty()) return Emprestimo();

    std::vector<Emprestimo> resultado;
    for (const auto& emprestimoJson : emprestimosJson) {
        resultado.emplace_back(
            emprestimoJson["id"],
            emprestimoJson["livro_isbn"],
            emprestimoJson["usuario_matricula"],
            emprestimoJson["data_emprestimo"],
            emprestimoJson["data_devolucao"],
            emprestimoJson["status"],
            emprestimoJson["tag_rfid"]
        );
    }

    return resultado[0];
}

std::vector<Emprestimo> EmprestimoRepository::buscarEmprestimosAtrasados() {
    // Obtém a data atual no formato YYYY-MM-DD
    auto now = time(nullptr);
    auto tm = *localtime(&now);
    ostringstream oss;
    oss << put_time(&tm, "%Y-%m-%d");
    string dataAtual = oss.str();

    // Busca todos os empréstimos ativos
    auto emprestimosAtivos = buscarEmprestimosAtivos();
    std::vector<Emprestimo> atrasados;

    // Filtra os que têm data de devolução menor que a data atual e ainda não foram devolvidos
    copy_if(emprestimosAtivos.begin(), emprestimosAtivos.end(), 
           back_inserter(atrasados),
           [&dataAtual](const Emprestimo &e) {
               return e.getDataDevolucao() < dataAtual && e.getStatus() == "ativo";
           });

    return atrasados;
}

bool EmprestimoRepository::finalizarEmprestimo(int emprestimoId) {
    // Obtém a data atual
    auto now = time(nullptr);
    auto tm = *localtime(&now);
    ostringstream oss;
    oss << put_time(&tm, "%Y-%m-%d %H:%M:%S");
    string dataDevolucao = oss.str();

    json condition = {{"id", emprestimoId}};
    json updates;
    updates["data_devolucao"] = dataDevolucao;
    updates["status"] = "finalizado";

    return dbConnector->update("emprestimos", condition, updates);
}

bool EmprestimoRepository::renovarEmprestimo(int emprestimoId, int dias) {
    // Busca o empréstimo atual
    auto emprestimoPtr = buscarPorId(emprestimoId);
    if (emprestimoPtr == nullptr || emprestimoPtr->getStatus() != "ativo") {
        delete emprestimoPtr;
        return false;
    }

    // Calcula nova data de devolução (implementação simplificada)
    string novaData = emprestimoPtr->getDataDevolucao();
    // TODO: Implementar lógica para adicionar dias à data

    // Atualiza no banco de dados
    json condition = {{"id", emprestimoId}};
    json updates;
    updates["data_devolucao"] = novaData;

    bool success = dbConnector->update("emprestimos", condition, updates);
    delete emprestimoPtr;
    return success;
}

bool EmprestimoRepository::verificarAtrasos(string usuarioMatricula) {
    auto atrasados = buscarEmprestimosAtrasados();
    return any_of(atrasados.begin(), atrasados.end(),
                [usuarioMatricula](const Emprestimo &e) {
                    return e.getUsuarioMatricula() == usuarioMatricula;
                });
}

std::vector<Emprestimo> EmprestimoRepository::buscarHistoricoCompleto(string usuarioMatricula) {
    auto historico = buscarPorUsuario(usuarioMatricula);

    // Ordena por data de empréstimo (mais recentes primeiro)
    sort(historico.begin(), historico.end(),
        [](const Emprestimo &a, const Emprestimo &b) {
            return a.getDataEmprestimo() > b.getDataEmprestimo();
        });

    return historico;
}

std::string EmprestimoRepository::buscarDonoLivro(std::string tag_rfid) {
    json condition = {{"tag_rfid", tag_rfid}, {"status", "ativo"}};
    auto emprestimosJson = dbConnector->read("emprestimos", condition);

    if (emprestimosJson.empty()) return "";

    return emprestimosJson[0]["usuario_matricula"];
}