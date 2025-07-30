#include "../../include/repository/ArmarioRepository.hpp"
#include <libpq-fe.h>
#include <sstream>
#include <stdexcept>

// using namespace pqxx;

ArmarioRepository::ArmarioRepository(IDatabaseConnector *connector)
    : dbConnector(connector) {}

bool ArmarioRepository::criarArmario(Armario &armario)
{
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    std::stringstream query;
    query << "INSERT INTO armarios (localizacao, status) VALUES ('"
          << txn.esc(armario.getLocalizacao()) << "', '"
          << armario.getStatus() << "') RETURNING id;";

    result res = txn.exec(query.str());
    txn.commit();

    if (!res.empty())
    {
      armario.setId(res[0][0].as<int>());
      return true;
    }
    */
    return false;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao criar armário: " + std::string(e.what()));
  }
}

bool ArmarioRepository::atualizarArmario(const Armario &armario)
{
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    std::stringstream query;
    query << "UPDATE armarios SET "
          << "localizacao = '" << txn.esc(armario.getLocalizacao()) << "', "
          << "status = '" << armario.getStatus() << "' "
          << "WHERE id = " << armario.getId() << ";";

    txn.exec(query.str());
    txn.commit();
    */
    return true;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao atualizar armário: " + std::string(e.what()));
  }
}

bool ArmarioRepository::removerArmario(int id)
{
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    // Verifica se o armário contém livros
    result check = txn.exec(
        "SELECT COUNT(*) FROM emprestimos "
        "WHERE armario_id = " +
        std::to_string(id) + " AND status = 'ativo';");

    if (check[0][0].as<int>() > 0)
    {
      throw std::runtime_error("Armário contém livros emprestados");
    }

    txn.exec("DELETE FROM armarios WHERE id = " + std::to_string(id) + ";");
    txn.commit();
    */
    return true;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao remover armário: " + std::string(e.what()));
  }
}

Armario *ArmarioRepository::buscarPorId(int id)
{
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    result res = txn.exec(
        "SELECT id, localizacao, status FROM armarios "
        "WHERE id = " +
        std::to_string(id) + ";");

    if (!res.empty())
    {
      auto row = res[0];
      Armario armario(
        row["localizacao"].as<std::string>());
        armario.setId(row["id"].as<int>());
        armario.setStatus(row["status"].as<std::string>());
        return armario;
      }
      */
    return nullptr;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao buscar armário: " + std::string(e.what()));
  }
}

std::vector<Armario> ArmarioRepository::buscarTodos()
{
  std::vector<Armario> armarios;
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    result res = txn.exec(
      "SELECT id, localizacao, status FROM armarios;");

      for (const auto &row : res)
      {
        Armario armario(
          row["localizacao"].as<std::string>());
          armario.setId(row["id"].as<int>());
          armario.setStatus(row["status"].as<std::string>());
          armarios.push_back(armario);
        }
        */
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao buscar armários: " + std::string(e.what()));
  }
  return armarios;
}

std::vector<Armario> ArmarioRepository::buscarPorLocalizacao(const std::string &localizacao)
{
  std::vector<Armario> armarios;
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    result res = txn.exec(
      "SELECT id, localizacao, status FROM armarios "
      "WHERE localizacao LIKE '%" +
        txn.esc(localizacao) + "%';");

    for (const auto &row : res)
    {
      Armario armario(
        row["localizacao"].as<std::string>());
        armario.setId(row["id"].as<int>());
        armario.setStatus(row["status"].as<std::string>());
        armarios.push_back(armario);
      }
      */
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao buscar armários por localização: " + std::string(e.what()));
  }
  return armarios;
}

bool ArmarioRepository::atualizarStatus(int armarioId, const std::string &status)
{
  try
  {
    /*

    work txn(*dbConnector->getConnection());

    txn.exec(
      "UPDATE armarios SET status = '" + txn.esc(status) + "' "
      "WHERE id = " +
      std::to_string(armarioId) + ";");
      txn.commit();
      */
    return true;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao atualizar status: " + std::string(e.what()));
  }
}

bool ArmarioRepository::verificarDisponibilidade(int armarioId)
{
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    result res = txn.exec(
      "SELECT status FROM armarios "
      "WHERE id = " +
      std::to_string(armarioId) + ";");

      if (!res.empty())
      {
        return res[0][0].as<std::string>() == "disponivel";
      }
      */
    return false;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao verificar disponibilidade: " + std::string(e.what()));
  }
}

std::vector<int> ArmarioRepository::buscarLivrosNoArmario(int armarioId)
{
  std::vector<int> livros;
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    result res = txn.exec(
      "SELECT livro_id FROM emprestimos "
      "WHERE armario_id = " +
      std::to_string(armarioId) + " "
      "AND status = 'ativo';");

      for (const auto &row : res)
      {
        livros.push_back(row["livro_id"].as<int>());
      }
      */
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao buscar livros no armário: " + std::string(e.what()));
  }
  return livros;
}

bool ArmarioRepository::adicionarLivro(int armarioId, int livroId)
{
  try
  {
    /*

    work txn(*dbConnector->getConnection());

    // Verifica se o livro já está em outro armário
    result check = txn.exec(
        "SELECT COUNT(*) FROM emprestimos "
        "WHERE livro_id = " +
        std::to_string(livroId) + " "
                                  "AND status = 'ativo';");

                                  if (check[0][0].as<int>() > 0)
                                  {
                                    throw std::runtime_error("Livro já está emprestado em outro armário");
                                  }

                                  // Atualiza o empréstimo existente ou cria um novo
                                  txn.exec(
                                    "INSERT INTO emprestimos (livro_id, armario_id, status) "
                                    "VALUES (" +
                                      std::to_string(livroId) + ", " + std::to_string(armarioId) + ", 'ativo') "
                                      "ON CONFLICT (livro_id) DO UPDATE "
                                      "SET armario_id = " +
                                      std::to_string(armarioId) + ";");

                                      txn.commit();
                                      */
    return true;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao adicionar livro: " + std::string(e.what()));
  }
}

bool ArmarioRepository::removerLivro(int armarioId, int livroId)
{
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    txn.exec(
      "UPDATE emprestimos SET armario_id = NULL "
      "WHERE livro_id = " +
      std::to_string(livroId) + " "
      "AND armario_id = " +
      std::to_string(armarioId) + ";");

      txn.commit();
      */
    return true;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao remover livro: " + std::string(e.what()));
  }
}

int ArmarioRepository::quantidadeLivrosArmario(int armarioId)
{
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    result res = txn.exec(
      "SELECT COUNT(*) FROM emprestimos "
      "WHERE armario_id = " + std::to_string(armarioId) + " "
      "AND status = 'ativo';"
    );

    return res[0][0].as<int>();
    */
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao contar livros: " + std::string(e.what()));
  }
}