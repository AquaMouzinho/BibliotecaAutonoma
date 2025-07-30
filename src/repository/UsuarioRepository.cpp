#include "../../include/repository/UsuarioRepository.hpp"

#include <libpq-fe.h>
#include <algorithm>
#include <stdexcept>
#include <sstream>

// using namespace pqxx;

UsuarioRepository::UsuarioRepository(IDatabaseConnector *connector)
    : dbConnector(connector) {}

bool UsuarioRepository::criarUsuario(const Usuario &usuario)
{
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    std::stringstream query;
    query << "INSERT INTO usuarios (matricula, senha_hash, nome, is_admin) "
    << "VALUES ('" << txn.esc(usuario.getMatricula()) << "', "
    << "'" << txn.esc(usuario.getSenhaHash()) << "', "
    << "'" << txn.esc(usuario.getNome()) << "', "
    << (usuario.isAdmin() ? "TRUE" : "FALSE") << ") "
    << "RETURNING id;";

    result res = txn.exec(query.str());
    txn.commit();

    if (!res.empty()) {
          const int novoId = res[0][0].as<int>();
          const_cast<Usuario&>(usuario).setId(novoId);
          return true;
      }
      */
    return false;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao criar usuário: " + std::string(e.what()));
  }
}

bool UsuarioRepository::atualizarUsuario(const Usuario &usuario)
{
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    std::stringstream query;
    query << "UPDATE usuarios SET "
    << "matricula = '" << txn.esc(usuario.getMatricula()) << "', "
    << "nome = '" << txn.esc(usuario.getNome()) << "', "
    << "is_admin = " << (usuario.isAdmin() ? "TRUE" : "FALSE") << " "
    << "WHERE id = " << usuario.getId() << ";";

    txn.exec(query.str());
    txn.commit();
    */
    return true;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao atualizar usuário: " + std::string(e.what()));
  }
}

bool UsuarioRepository::removerUsuario(int id)
{
  try
  {
    /*
    work txn(*dbConnector->getConnection());

      // Verifica se o usuário possui empréstimos ativos
      result check = txn.exec(
          "SELECT COUNT(*) FROM emprestimos WHERE usuario_emprestimo_id = " +
          std::to_string(id) + " AND status = 'ativo';"
        );

        if (check[0][0].as<int>() > 0) {
          throw std::runtime_error("Usuário possui empréstimos ativos");
        }

        txn.exec("DELETE FROM usuarios WHERE id = " + std::to_string(id) + ";");
        txn.commit();
        */
    return true;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao remover usuário: " + std::string(e.what()));
  }
}

Usuario *UsuarioRepository::buscarPorId(int id)
{
  try
  {
    /*
    work txn(*dbConnector->getConnection());

      result res = txn.exec(
          "SELECT id, matricula, senha_hash, nome, is_admin, bloqueado "
          "FROM usuarios WHERE id = " + std::to_string(id) + ";"
      );

      if (!res.empty()) {
          auto row = res[0];
          Usuario usuario(
              row["matricula"].as<std::string>(),
              row["senha_hash"].as<std::string>(),
              row["nome"].as<std::string>(),
              row["is_admin"].as<bool>()
            );

            usuario.setId(row["id"].as<int>());
            usuario.setBloqueado(row["bloqueado"].as<bool>());
            return usuario;
          }
          */
    return NULL;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao buscar usuário: " + std::string(e.what()));
  }
}

std::vector<Usuario> UsuarioRepository::buscarTodos()
{
  std::vector<Usuario> usuarios;
  try
  {
    /*

    work txn(*dbConnector->getConnection());

    result res = txn.exec(
        "SELECT id, matricula, nome, is_admin, bloqueado FROM usuarios;");

    for (const auto &row : res)
    {
      Usuario usuario(
        row["matricula"].as<std::string>(),
        "", // Senha não é retornada por segurança
        row["nome"].as<std::string>(),
        row["is_admin"].as<bool>());

        usuario.setId(row["id"].as<int>());
        usuario.setBloqueado(row["bloqueado"].as<bool>());
        usuarios.push_back(usuario);
      }
      */
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao buscar usuários: " + std::string(e.what()));
  }
  return usuarios;
}

Usuario *UsuarioRepository::autenticar(const std::string &matricula, const std::string &senha)
{
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    std::string query =
        "SELECT id, matricula, senha_hash, nome, is_admin, bloqueado "
        "FROM usuarios WHERE matricula = '" +
        txn.esc(matricula) + "';";

    result res = txn.exec(query);

    if (!res.empty())
    {
      auto row = res[0];

      // Verificar se está bloqueado
      if (row["bloqueado"].as<bool>())
      {
        throw std::runtime_error("Usuário bloqueado");
      }

      // Verificar senha (deve ser feita a comparação de hash na prática)
      if (row["senha_hash"].as<std::string>() == senha)
      { // Em produção, use bcrypt
        Usuario usuario(
          row["matricula"].as<std::string>(),
          row["senha_hash"].as<std::string>(),
          row["nome"].as<std::string>(),
          row["is_admin"].as<bool>());

          usuario.setId(row["id"].as<int>());
          return usuario;
        }
      }
      */
    return NULL;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro na autenticação: " + std::string(e.what()));
  }
}

bool UsuarioRepository::usuarioPossuiEmprestimosAtrasados(int usuarioId)
{
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    result res = txn.exec(
      "SELECT COUNT(*) FROM emprestimos "
      "WHERE usuario_emprestimo_id = " +
      std::to_string(usuarioId) + " "
      "AND status = 'ativo' "
      "AND data_devolucao_prevista < CURRENT_TIMESTAMP;");

      return res[0][0].as<int>() > 0;
      */
    return false;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao verificar empréstimos: " + std::string(e.what()));
  }
}

bool UsuarioRepository::matriculaExiste(const std::string &matricula)
{
  try
  {
    /*

    work txn(*dbConnector->getConnection());

    result res = txn.exec(
      "SELECT COUNT(*) FROM usuarios "
      "WHERE matricula = '" +
      txn.esc(matricula) + "';");

      return res[0][0].as<int>() > 0;
      */
    return true;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao verificar matrícula: " + std::string(e.what()));
  }
}

bool UsuarioRepository::bloquearUsuario(int id)
{
  try
  {
    // work txn(*dbConnector->getConnection());

    // txn.exec(
    //    "UPDATE usuarios SET bloqueado = TRUE "
    //  "WHERE id = " +
    // std::to_string(id) + ";");
    // txn.commit();
    return true;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao bloquear usuário: " + std::string(e.what()));
  }
}

bool UsuarioRepository::desbloquearUsuario(int id)
{
  try
  {
    /*

    work txn(*dbConnector->getConnection());

    txn.exec(
      "UPDATE usuarios SET bloqueado = FALSE "
      "WHERE id = " +
      std::to_string(id) + ";");
      txn.commit();
      */
    return true;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao desbloquear usuário: " + std::string(e.what()));
  }
}

std::vector<Usuario> UsuarioRepository::buscarPorNome(const std::string &nome)
{
  std::vector<Usuario> usuarios;
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    result res = txn.exec(
      "SELECT id, matricula, nome, is_admin, bloqueado "
      "FROM usuarios WHERE nome LIKE '%" +
      txn.esc(nome) + "%';");

      for (const auto &row : res)
      {
        Usuario usuario(
          row["matricula"].as<std::string>(),
          "",
          row["nome"].as<std::string>(),
          row["is_admin"].as<bool>());

          usuario.setId(row["id"].as<int>());
          usuario.setBloqueado(row["bloqueado"].as<bool>());
          usuarios.push_back(usuario);
        }
        */
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao buscar por nome: " + std::string(e.what()));
  }
  return usuarios;
}

std::vector<Usuario> UsuarioRepository::buscarAdministradores()
{
  std::vector<Usuario> administradores;
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    result res = txn.exec(
        "SELECT id, matricula, nome FROM usuarios WHERE is_admin = TRUE;");

    for (const auto &row : res)
    {
      Usuario usuario(
          row["matricula"].as<std::string>(),
          "",
          row["nome"].as<std::string>(),
          true);

      usuario.setId(row["id"].as<int>());
      administradores.push_back(usuario);
    }
    */
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao buscar administradores: " + std::string(e.what()));
  }
  return administradores;
}