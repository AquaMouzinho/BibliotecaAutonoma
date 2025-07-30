#include "../../include/repository/LivroRepository.hpp"

#include <libpq-fe.h>
#include <algorithm>
#include <stdexcept>
#include <sstream>

// using namespace pqxx;

LivroRepository::LivroRepository(IDatabaseConnector *connector)
    : dbConnector(connector) {}

bool LivroRepository::criarLivro(Livro &livro)
{
  try
  {
    /*
    work txn(*dbConnector->getConnection());

      std::stringstream query;
      query << "INSERT INTO livros (rfid_tag, titulo, autor, usuario_doador_id) "
            << "VALUES ("
            << (livro.getTagRfid().empty() ? "NULL" : "'" + txn.esc(livro.getTagRfid()) + "'") << ", "
            << "'" << txn.esc(livro.getTitulo()) << "', "
            << "'" << txn.esc(livro.getAutor()) << "', "
            << (livro.getUsuarioDoadorId() ? std::to_string(livro.getUsuarioDoadorId()) : "NULL")
            << ") RETURNING id;";

      result res = txn.exec(query.str());
      txn.commit();

      if (!res.empty()) {
          livro.setId(res[0][0].as<int>());
          return true;
        }
        */
    return false;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao criar livro: " + std::string(e.what()));
  }
}

bool LivroRepository::atualizarLivro(const Livro &livro)
{
  try
  {
    /*
    work txn(*dbConnector->getConnection());

      std::stringstream query;
      query << "UPDATE livros SET "
            << "titulo = '" << txn.esc(livro.getTitulo()) << "', "
            << "autor = '" << txn.esc(livro.getAutor()) << "', "
            << "usuario_doador_id = " << (livro.getUsuarioDoadorId() ? std::to_string(livro.getUsuarioDoadorId()) : "NULL") << " "
            << "WHERE id = " << livro.getId() << ";";

            txn.exec(query.str());
            txn.commit();
            */
    return true;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao atualizar livro: " + std::string(e.what()));
  }
}

bool LivroRepository::removerLivro(int id)
{
  try
  {
    /*

    work txn(*dbConnector->getConnection());

    // Verifica se o livro está emprestado
    result check = txn.exec(
      "SELECT COUNT(*) FROM emprestimos "
      "WHERE livro_id = " +
      std::to_string(id) + " AND status = 'ativo';");

      if (check[0][0].as<int>() > 0)
      {
        throw std::runtime_error("Livro está atualmente emprestado");
      }

      txn.exec("DELETE FROM livros WHERE id = " + std::to_string(id) + ";");
      txn.commit();
      */
    return true;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao remover livro: " + std::string(e.what()));
  }
}

Livro *LivroRepository::buscarPorId(int id)
{
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    result res = txn.exec(
        "SELECT id, rfid_tag, titulo, autor, usuario_doador_id "
        "FROM livros WHERE id = " +
        std::to_string(id) + ";");

    if (!res.empty())
    {
      auto row = res[0];
      Livro livro(
          row["titulo"].as<std::string>(),
          row["autor"].as<std::string>(),
          row["usuario_doador_id"].is_null() ? 0 : row["usuario_doador_id"].as<int>());

          livro.setId(row["id"].as<int>());
          if (!row["rfid_tag"].is_null())
      {
        livro.setRfidTag(row["rfid_tag"].as<std::string>());
      }
      return livro;
    }
    */
    return NULL;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao buscar livro: " + std::string(e.what()));
  }
}

std::vector<Livro> LivroRepository::buscarTodos()
{
  std::vector<Livro> livros;
  try
  {
    /*

    work txn(*dbConnector->getConnection());

    result res = txn.exec(
        "SELECT id, rfid_tag, titulo, autor, usuario_doador_id FROM livros;");

    for (const auto &row : res)
    {
      Livro livro(
          row["titulo"].as<std::string>(),
          row["autor"].as<std::string>(),
          row["usuario_doador_id"].is_null() ? 0 : row["usuario_doador_id"].as<int>());

          livro.setId(row["id"].as<int>());
          if (!row["rfid_tag"].is_null())
          {
            livro.setRfidTag(row["rfid_tag"].as<std::string>());
          }
          livros.push_back(livro);
        }
        */
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao buscar livros: " + std::string(e.what()));
  }
  return livros;
}

Livro *LivroRepository::buscarPorRfid(const std::string &rfid)
{
  try
  {
    /*

    work txn(*dbConnector->getConnection());

    result res = txn.exec(
        "SELECT id, rfid_tag, titulo, autor, usuario_doador_id "
        "FROM livros WHERE rfid_tag = '" +
        txn.esc(rfid) + "';");

    if (!res.empty())
    {
      auto row = res[0];
      Livro livro(
          row["titulo"].as<std::string>(),
          row["autor"].as<std::string>(),
          row["usuario_doador_id"].is_null() ? 0 : row["usuario_doador_id"].as<int>());

          livro.setId(row["id"].as<int>());
          livro.setRfidTag(row["rfid_tag"].as<std::string>());
      return livro;
    }
    */
    return nullptr;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao buscar livro por RFID: " + std::string(e.what()));
  }
}

std::vector<Livro> LivroRepository::buscarPorTitulo(const std::string &titulo)
{
  std::vector<Livro> livros;
  try
  {
    /*

    work txn(*dbConnector->getConnection());

    result res = txn.exec(
        "SELECT id, rfid_tag, titulo, autor, usuario_doador_id "
        "FROM livros WHERE titulo LIKE '%" +
        txn.esc(titulo) + "%';");

    for (const auto &row : res)
    {
      Livro livro(
          row["titulo"].as<std::string>(),
          row["autor"].as<std::string>(),
          row["usuario_doador_id"].is_null() ? 0 : row["usuario_doador_id"].as<int>());

      livro.setId(row["id"].as<int>());
      if (!row["rfid_tag"].is_null())
      {
        livro.setRfidTag(row["rfid_tag"].as<std::string>());
      }
      livros.push_back(livro);
    }
    */
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao buscar livros por título: " + std::string(e.what()));
  }
  return livros;
}

std::vector<Livro> LivroRepository::buscarPorAutor(const std::string &autor)
{
  std::vector<Livro> livros;
  try
  {
    /*

    work txn(*dbConnector->getConnection());

    result res = txn.exec(
        "SELECT id, rfid_tag, titulo, autor, usuario_doador_id "
        "FROM livros WHERE autor LIKE '%" +
        txn.esc(autor) + "%';");

    for (const auto &row : res)
    {
      Livro livro(
          row["titulo"].as<std::string>(),
          row["autor"].as<std::string>(),
          row["usuario_doador_id"].is_null() ? 0 : row["usuario_doador_id"].as<int>());

          livro.setId(row["id"].as<int>());
          if (!row["rfid_tag"].is_null())
          {
            livro.setRfidTag(row["rfid_tag"].as<std::string>());
          }
          livros.push_back(livro);
        }
        */
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao buscar livros por autor: " + std::string(e.what()));
  }
  return livros;
}

std::vector<Livro> LivroRepository::buscarLivrosDisponiveis()
{
  std::vector<Livro> livros;
  try
  {
    /*

    work txn(*dbConnector->getConnection());

    // Livros que não estão em empréstimos ativos
    result res = txn.exec(
        "SELECT l.id, l.rfid_tag, l.titulo, l.autor, l.usuario_doador_id "
        "FROM livros l "
        "LEFT JOIN emprestimos e ON l.id = e.livro_id AND e.status = 'ativo' "
        "WHERE e.id IS NULL;");

    for (const auto &row : res)
    {
      Livro livro(
        row["titulo"].as<std::string>(),
        row["autor"].as<std::string>(),
        row["usuario_doador_id"].is_null() ? 0 : row["usuario_doador_id"].as<int>());

        livro.setId(row["id"].as<int>());
        if (!row["rfid_tag"].is_null())
        {
          livro.setRfidTag(row["rfid_tag"].as<std::string>());
        }
        livros.push_back(livro);
      }
      */
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao buscar livros disponíveis: " + std::string(e.what()));
  }
  return livros;
}

std::vector<Livro> LivroRepository::buscarLivrosPorDoador(int usuarioDoadorId)
{
  std::vector<Livro> livros;
  try
  {
    /*

    work txn(*dbConnector->getConnection());

    result res = txn.exec(
        "SELECT id, rfid_tag, titulo, autor, usuario_doador_id "
        "FROM livros WHERE usuario_doador_id = " +
        std::to_string(usuarioDoadorId) + ";");

    for (const auto &row : res)
    {
      Livro livro(
        row["titulo"].as<std::string>(),
        row["autor"].as<std::string>(),
        row["usuario_doador_id"].as<int>());

        livro.setId(row["id"].as<int>());
        if (!row["rfid_tag"].is_null())
        {
          livro.setRfidTag(row["rfid_tag"].as<std::string>());
        }
        livros.push_back(livro);
      }
      */
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao buscar livros por doador: " + std::string(e.what()));
  }
  return livros;
}

bool LivroRepository::atualizarStatusLivro(int livroId, const std::string &status)
{
  try
  {
    /*

    work txn(*dbConnector->getConnection());

    txn.exec(
        "UPDATE livros SET status = '" + txn.esc(status) + "' "
                                                           "WHERE id = " +
        std::to_string(livroId) + ";");
    txn.commit();
    return true;
    */
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao atualizar status do livro: " + std::string(e.what()));
  }
}

bool LivroRepository::livroEstaDisponivel(int livroId)
{
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    result res = txn.exec(
      "SELECT COUNT(*) FROM emprestimos "
      "WHERE livro_id = " +
      std::to_string(livroId) + " AND status = 'ativo';");

      return false;
      */
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao verificar disponibilidade: " + std::string(e.what()));
  }
  return true;
}

bool LivroRepository::associarRfid(int livroId, const std::string &rfid)
{
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    // Verifica se o RFID já está em uso
    result check = txn.exec(
      "SELECT COUNT(*) FROM livros "
      "WHERE rfid_tag = '" +
      txn.esc(rfid) + "' AND id != " + std::to_string(livroId) + ";");

      if (check[0][0].as<int>() > 0)
      {
        throw std::runtime_error("Tag RFID já está em uso por outro livro");
      }

      txn.exec(
        "UPDATE livros SET rfid_tag = '" + txn.esc(rfid) + "' "
        "WHERE id = " +
        std::to_string(livroId) + ";");
        txn.commit();
        */
    return true;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao associar RFID: " + std::string(e.what()));
  }
}