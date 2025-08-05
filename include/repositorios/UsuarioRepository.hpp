#ifndef USUARIO_REPOSITORY_HPP
#define USUARIO_REPOSITORY_HPP

#include "../model/Usuario.hpp"
#include "../model/Notificacao.hpp"
#include "../model/Emprestimo.hpp"
#include "../model/Livro.hpp"
#include <vector>
#include "../database/IDatabaseConnector.hpp"

class UsuarioRepository {
  private:
    IDatabaseConnector *db;

  public:
    UsuarioRepository(IDatabaseConnector *db) : db(db) {};
    ~UsuarioRepository() = default;

    bool adicionarUsuario(std::string matricula, std::string senha, std::string nome);
    bool atualizarUsuario(Usuario *usuario);
    bool removerUsuario(int id);
    bool removerUsuario(std::string matricula);

    Usuario *buscarUsuarioPorId(int id);
    Usuario *buscarUsuarioPorMatricula(std::string matricula);
    std::vector<Usuario> listarUsuarios();

    Usuario* autenticarUsuario(std::string matricula, std::string senha);

    std::vector<Notificacao> listarNotificacoes(Usuario *usuario);
    std::vector<Emprestimo> listarEmprestimos(Usuario *usuario);
    std::vector<Livro> listarLivrosDoados(Usuario *usuario);
    std::vector<Livro> listarLivrosDoados(std::string usuarioMatricula);
};

#endif