#include "UsuarioRepository.hpp"
#include <algorithm>
#include <string>
#include <iostream>

bool UsuarioRepository::adicionarUsuario(std::string matricula, std::string senha, std::string nome) {
    // Verifica se o usuário já existe
    json condition = {{"matricula", matricula}};
    auto usuarios = db->read("usuarios", condition);
    if (!usuarios.empty()) {
        return false; // Matrícula já existe
    }

    // Busca o próximo ID disponível
    int proximoId = 1;
    auto todosUsuarios = db->read("usuarios", json::object());
    for (const auto& usuario : todosUsuarios) {
        if (usuario["id"] >= proximoId) {
            proximoId = usuario["id"].get<int>() + 1;
        }
    }

    // Cria novo usuário
    json novoUsuario;
    novoUsuario["id"] = proximoId;
    novoUsuario["matricula"] = matricula;
    novoUsuario["senha"] = senha;
    novoUsuario["nome"] = nome;
    novoUsuario["role"] = "user";
    novoUsuario["ativo"] = true;

    return db->create("usuarios", novoUsuario);
}

bool UsuarioRepository::atualizarUsuario(Usuario *usuario) {
    json condition = {{"id", usuario->getId()}};
    json updates;
    updates["matricula"] = usuario->getMatricula();
    updates["nome"] = usuario->getNome();
    updates["role"] = usuario->getRole();
    updates["senha"] = usuario->getSenhaHash();
    updates["ativo"] = usuario->getAtivo();

    return db->update("usuarios", condition, updates);
}

bool UsuarioRepository::removerUsuario(int id) {
    json condition = {{"id", id}};
    return db->remove("usuarios", condition);
}

bool UsuarioRepository::removerUsuario(std::string matricula){
    json condition = {{"matricula", matricula}};
    return db->remove("usuarios", condition);
}

Usuario *UsuarioRepository::buscarUsuarioPorId(int id) {
    json condition = {{"id", id}};
    auto usuarios = db->read("usuarios", condition);

    if (usuarios.empty()) return nullptr;

    auto usuarioJson = usuarios[0];
    auto usuario = new Usuario(
        usuarioJson["id"].get<int>(),
        usuarioJson["matricula"].get<std::string>(),
        usuarioJson["nome"].get<std::string>(),
        usuarioJson["senha_hash"].get<std::string>()
    );
    usuario->setRole(usuarioJson["role"]);
    usuario->setAtivo(usuarioJson["ativo"]);

    return usuario;
}

Usuario *UsuarioRepository::buscarUsuarioPorMatricula(std::string matricula) {
    //std::cout << "Buscando usuario por matricula: " << matricula << std::endl;
    json condition = {{"matricula", matricula}};
    auto usuarios = db->read("usuarios", condition);

    if (usuarios.empty()) return nullptr;

    auto usuarioJson = usuarios[0];
    auto usuario = new Usuario(
        usuarioJson["id"],
        usuarioJson["matricula"],
        usuarioJson["nome"],
        usuarioJson["senha_hash"]
    );
    usuario->setRole(usuarioJson["role"]);
    usuario->setAtivo(usuarioJson["ativo"]);

//std::cout << "Usuario encontrado: " << usuario->getNome() << ", " << usuario->getMatricula() << ", " << usuario->getRole() << ", " << usuario->getAtivo() << ", " << usuario->getSenhaHash() << std::endl;
    
    return usuario;
}

std::vector<Usuario> UsuarioRepository::listarUsuarios() {
    std::vector<Usuario> usuarios;
    auto usuariosJson = db->read("usuarios", json::object());

    for (const auto& usuarioJson : usuariosJson) {
        Usuario usuario(
            usuarioJson["id"].get<int>(),
            usuarioJson["matricula"],
            usuarioJson["nome"],
            usuarioJson["senha_hash"]
        );
        usuario.setRole(usuarioJson["role"]);
        usuario.setAtivo(usuarioJson["ativo"]);
        usuarios.push_back(usuario);
    }

    return usuarios;
}

Usuario* UsuarioRepository::autenticarUsuario(std::string matricula, std::string senha) {
    json condition = {
        {"matricula", matricula},
        {"senha", senha}
    };
    auto usuarios = db->read("usuarios", condition);
    if (usuarios.empty()) {
      return nullptr; // Autenticação falhou
    }
    
    auto usuarioJson = usuarios[0];
    Usuario* usuario = new Usuario(
      usuarioJson["id"],
      usuarioJson["matricula"],
      usuarioJson["senha_hash"],
      usuarioJson["nome"]
    );
    usuario->setRole(usuarioJson["role"]);
    usuario->setAtivo(usuarioJson["ativo"]);
    
    return usuario;
}

// Implementações futuras
std::vector<Notificacao> UsuarioRepository::listarNotificacoes(Usuario *usuario) {
    json condition = {{"usuario_matricula", usuario->getMatricula()}};
    auto notificacoesJson = db->read("notificacoes", condition);

    std::vector<Notificacao> notificacoes;
    for (const auto& notificacaoJson : notificacoesJson) {
        Notificacao notificacao(
            notificacaoJson["id"].get<int>(),
            notificacaoJson["usuario_matricula"].get<std::string>(),
            notificacaoJson["mensagem"].get<std::string>(),
            notificacaoJson["data_criacao"].get<std::string>()
        );
        notificacoes.push_back(notificacao);
    }
    return notificacoes;
}

std::vector<Emprestimo> UsuarioRepository::listarEmprestimos(Usuario *usuario) {
    json condition = {{"usuario_matricula", usuario->getMatricula()}};
    auto emprestimosJson = db->read("emprestimos", condition);

    std::vector<Emprestimo> emprestimos;
    for (const auto& emprestimoJson : emprestimosJson) {
        Emprestimo emprestimo(
            emprestimoJson["id"].get<int>(),
            emprestimoJson["livro_isbn"].get<std::string>(),
            emprestimoJson["usuario_matricula"].get<std::string>(),
            emprestimoJson["data_emprestimo"].get<std::string>(),
            emprestimoJson["data_devolucao"].get<std::string>(),
            emprestimoJson["status"].get<std::string>(),
            emprestimoJson["tag_rfid"].get<std::string>()
        );
        emprestimos.push_back(emprestimo);
    }
    return emprestimos;
}

std::vector<Livro> UsuarioRepository::listarLivrosDoados(Usuario *usuario) {
    json condition = {{"doador_matricula", usuario->getMatricula()}};
    auto livrosJson = db->read("livros", condition);

    std::vector<Livro> livros;
    for (const auto& livroJson : livrosJson) {
        Livro livro(
            livroJson["isbn"].get<std::string>(),
            livroJson["titulo"].get<std::string>(),
            livroJson["autor"].get<std::string>(),
            livroJson["tag_rfid"].get<std::string>(),
            livroJson["doador_matricula"].get<std::string>(),
            livroJson["armario_id"].get<int>(),
            livroJson["disponivel"].get<bool>()
        );
        livros.push_back(livro);
    }
    return livros;
}

std::vector<Livro> UsuarioRepository::listarLivrosDoados(std::string usuarioMatricula){
    json condition = {{"doador_matricula", usuarioMatricula}};
    auto livrosJson = db->read("livros", condition);
    std::vector<Livro> livros;
    for (const auto& livroJson : livrosJson) {
        Livro livro(
            livroJson["isbn"].get<std::string>(),
            livroJson["titulo"].get<std::string>(),
            livroJson["autor"].get<std::string>(),
            livroJson["tag_rfid"].get<std::string>(),
            livroJson["doador_matricula"].get<std::string>(),
            livroJson["armario_id"].get<int>(),
            livroJson["disponivel"].get<bool>()
        );
        livros.push_back(livro);
    }
    return livros;
}