#include "SessaoRepository.hpp"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <exception>
#include <iostream>

using namespace std;

SessaoRepository::SessaoRepository(IDatabaseConnector *connector) 
    : dbConnector(connector) {}

bool SessaoRepository::criarSessao(const Sessao &sessao) {
    // Verifica se já existe sessão com o mesmo ID
    if (sessao.getId() != 0) {
        json condition = {{"id", sessao.getId()}};
        auto sessoes = dbConnector->read("sessoes", condition);
        if (!sessoes.empty()) {
            return false; // ID já existe
        }
    }

    // Encontra o próximo ID disponível
    int proximoId = 1;
    auto todasSessoes = dbConnector->read("sessoes", json::object());
    for (const auto& sessaoJson : todasSessoes) {
        if (sessaoJson["id"] >= proximoId) {
            proximoId = sessaoJson["id"].get<int>() + 1;
        }
    }

    // Obtém a data/hora atual para data_criacao se não foi fornecida
    string data_criacao = sessao.getDataCriacao();
    if (data_criacao.empty()) {
        auto now = time(nullptr);
        auto tm = *localtime(&now);
        ostringstream oss;
        oss << put_time(&tm, "%Y-%m-%d %H:%M:%S");
        data_criacao = oss.str();
    }

    // Cria o JSON da sessão
    try{
        json novaSessao;
        novaSessao["id"] = proximoId;
        novaSessao["armario_id"] = sessao.getArmarioId();
        novaSessao["usuario_matricula"] = sessao.getUsuarioMatricula();
        novaSessao["tipo"] = sessao.getTipo();
        novaSessao["data_criacao"] = data_criacao;
        novaSessao["data_fechamento"] = sessao.getDataFechamento();
        novaSessao["ativa"] = sessao.isAtiva();
        novaSessao["timer"] = sessao.getTimer();

        // Atualiza o ID no objeto sessão
        return dbConnector->create("sessoes", novaSessao);
    }catch(const std::exception& e){
        std::cerr << "Erro ao criar sessão: " << e.what() << std::endl;
        return false;
    }
    
}

bool SessaoRepository::atualizarSessao(const Sessao &sessao) {
    json condition = {{"id", sessao.getId()}};
    json updates;
    updates["armario_id"] = sessao.getArmarioId();
    updates["usuario_matricula"] = sessao.getUsuarioMatricula();
    updates["tipo"] = sessao.getTipo();
    updates["data_criacao"] = sessao.getDataCriacao();
    updates["data_fechamento"] = sessao.getDataFechamento();
    updates["timer"] = sessao.getTimer();
    updates["ativa"] = sessao.isAtiva();
    return dbConnector->update("sessoes", condition, updates);
}

bool SessaoRepository::removerSessao(const std::string sessaoId) {
    json condition = {{"id", sessaoId}};
    return dbConnector->remove("sessoes", condition);
}

int SessaoRepository::encerrarSessoesExpiradas() {
    auto now = time(nullptr);
    auto tm = *localtime(&now);
    ostringstream oss;
    oss << put_time(&tm, "%Y-%m-%d %H:%M:%S");
    string dataAtual = oss.str();

    json condition = {{"ativa", true}};
    auto sessoes = dbConnector->read("sessoes", condition);
    int count = 0;
    for (const auto& sessaoJson : sessoes){
        if (sessaoJson["timer"] < dataAtual){
            json updates = {{"ativa", false}, {"data_fechamento", dataAtual}};
            dbConnector->update("sessoes", {{"id", sessaoJson["id"]}}, updates);
            count++;
        }
    }
    return count;
}

Sessao* SessaoRepository::buscarSessaoPorId(int id) {
    json condition = {{"id", id}};
    auto sessoes = dbConnector->read("sessoes", condition);

    if (sessoes.empty()) return nullptr;

    auto sessaoJson = sessoes[0];
    Sessao* sessao = new Sessao();
    sessao->setId(sessaoJson["id"]);
    sessao->setArmarioId(sessaoJson["armario_id"]);
    sessao->setUsuarioMatricula(sessaoJson["usuario_matricula"]);
    sessao->setTipo(sessaoJson["tipo"]);
    sessao->setDataCriacao(sessaoJson["data_criacao"]);
    sessao->setDataFechamento(sessaoJson["data_fechamento"]);
    sessao->setAtiva(sessaoJson["ativa"]);
    sessao->setTimer(sessaoJson["timer"]);

    return sessao;
}

Sessao* SessaoRepository::buscarSessaoAtivaPorUsuario(std::string usuario_matricula) {
    json condition = {
        {"usuario_matricula", usuario_matricula},
        {"ativa", true}
    };

    auto sessoes = dbConnector->read("sessoes", condition);
    if (sessoes.empty()) return nullptr;

    auto sessaoJson = sessoes[0];
    Sessao* sessao = new Sessao();
    sessao->setId(sessaoJson["id"]);
    sessao->setArmarioId(sessaoJson["armario_id"]);
    sessao->setUsuarioMatricula(sessaoJson["usuario_matricula"]);
    sessao->setTipo(sessaoJson["tipo"]);
    sessao->setDataCriacao(sessaoJson["data_criacao"]);
    sessao->setDataFechamento(sessaoJson["data_fechamento"]);
    sessao->setAtiva(sessaoJson["ativa"]);
    sessao->setTimer(sessaoJson["timer"]);

    return sessao;
}

vector<Sessao> SessaoRepository::buscarSessoesPorArmario(int armarioId) {
    json condition = {{"armario_id", armarioId}};
    auto sessoesJson = dbConnector->read("sessoes", condition);

    vector<Sessao> resultado;
    for (const auto& sessaoJson : sessoesJson) {
        Sessao sessao;
        sessao.setId(sessaoJson["id"]);
        sessao.setArmarioId(sessaoJson["armario_id"]);
        sessao.setUsuarioMatricula(sessaoJson["usuario_matricula"]);
        sessao.setTipo(sessaoJson["tipo"]);
        sessao.setDataCriacao(sessaoJson["data_criacao"]);
        sessao.setDataFechamento(sessaoJson["data_fechamento"]);
        sessao.setAtiva(sessaoJson["ativa"]);
        sessao.setTimer(sessaoJson["timer"]);
        resultado.push_back(sessao);
    }

    return resultado;
}

vector<Sessao> SessaoRepository::buscarSessoesPorUsuario(std::string usuario_matricula) {
    json condition = {{"usuario_matricula", usuario_matricula}};
    auto sessoesJson = dbConnector->read("sessoes", condition);

    vector<Sessao> resultado;
    for (const auto& sessaoJson : sessoesJson){
        Sessao sessao;
        sessao.setId(sessaoJson["id"]);
        sessao.setArmarioId(sessaoJson["armario_id"]);
        sessao.setUsuarioMatricula(sessaoJson["usuario_matricula"]);
        sessao.setTipo(sessaoJson["tipo"]);
        sessao.setDataCriacao(sessaoJson["data_criacao"]);
        sessao.setDataFechamento(sessaoJson["data_fechamento"]);
        sessao.setAtiva(sessaoJson["ativa"]);
        sessao.setTimer(sessaoJson["timer"]);
        resultado.push_back(sessao);
    }
    return resultado;
}

vector<Sessao> SessaoRepository::buscarSessoesPorTipo(std::string tipo) {
    json condition = {{"tipo", tipo}};
    auto sessoesJson = dbConnector->read("sessoes", condition);

    vector<Sessao> resultado;
    for (const auto& sessaoJson : sessoesJson) {
        Sessao sessao;
        sessao.setId(sessaoJson["id"]);
        sessao.setArmarioId(sessaoJson["armario_id"]);
        sessao.setUsuarioMatricula(sessaoJson["usuario_matricula"]);
        sessao.setTipo(sessaoJson["tipo"]);
        sessao.setDataCriacao(sessaoJson["data_criacao"]);
        sessao.setDataFechamento(sessaoJson["data_fechamento"]);
        sessao.setAtiva(sessaoJson["ativa"]);
        sessao.setTimer(sessaoJson["timer"]);
        resultado.push_back(sessao);
    }
    return resultado;
}

vector<Sessao> SessaoRepository::buscarSessoesPorDataCriacao(std::string data_criacao) {
    json condition = {{"data_criacao", data_criacao}};
    auto sessoesJson = dbConnector->read("sessoes", condition);

    vector<Sessao> resultado;
    for (const auto& sessaoJson : sessoesJson){
        Sessao sessao;
        sessao.setId(sessaoJson["id"]);
        sessao.setArmarioId(sessaoJson["armario_id"]);
        sessao.setUsuarioMatricula(sessaoJson["usuario_matricula"]);
        sessao.setTipo(sessaoJson["tipo"]);
        sessao.setDataCriacao(sessaoJson["data_criacao"]);
        sessao.setDataFechamento(sessaoJson["data_fechamento"]);
        sessao.setAtiva(sessaoJson["ativa"]);
        sessao.setTimer(sessaoJson["timer"]);
        resultado.push_back(sessao);
    }
    return resultado;
}

vector<Sessao> SessaoRepository::buscarSessoesPorDataFechamento(std::string data_fechamento){
    json condition = {{"data_fechamento", data_fechamento}};
    auto sessoesJson = dbConnector->read("sessoes", condition);

    vector<Sessao> resultado;
    for (const auto& sessaoJson : sessoesJson){
        Sessao sessao;
        sessao.setId(sessaoJson["id"]);
        sessao.setArmarioId(sessaoJson["armario_id"]);
        sessao.setUsuarioMatricula(sessaoJson["usuario_matricula"]);
        sessao.setTipo(sessaoJson["tipo"]);
        sessao.setDataCriacao(sessaoJson["data_criacao"]);
        sessao.setDataFechamento(sessaoJson["data_fechamento"]);
        sessao.setAtiva(sessaoJson["ativa"]);
        sessao.setTimer(sessaoJson["timer"]);
        resultado.push_back(sessao);
    }
    return resultado;
}

vector<Sessao> SessaoRepository::buscarSessoesPorTimer(int timer) {
    json condition = {{"timer", timer}};
    auto sessoesJson = dbConnector->read("sessoes", condition);

    vector<Sessao> resultado;
    for (const auto& sessaoJson : sessoesJson){
        Sessao sessao;
        sessao.setId(sessaoJson["id"]);
        sessao.setArmarioId(sessaoJson["armario_id"]);
        sessao.setUsuarioMatricula(sessaoJson["usuario_matricula"]);
        sessao.setTipo(sessaoJson["tipo"]);
        sessao.setDataCriacao(sessaoJson["data_criacao"]);
        sessao.setDataFechamento(sessaoJson["data_fechamento"]);
        sessao.setAtiva(sessaoJson["ativa"]);
        sessao.setTimer(sessaoJson["timer"]);
        resultado.push_back(sessao);
    }
    return resultado;
}