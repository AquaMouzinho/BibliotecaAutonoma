#include "../../include/repository/EmprestimoRepository.hpp"

#include <libpq-fe.h>
#include <chrono>
#include <sstream>
#include <stdexcept>

// using namespace pqxx;
using namespace std::chrono;

EmprestimoRepository::EmprestimoRepository(IDatabaseConnector *connector)
    : dbConnector(connector) {}

bool EmprestimoRepository::criarEmprestimo(Emprestimo &emprestimo)
{
  try
  {
    /*

    work txn(*dbConnector->getConnection());

      std::stringstream query;
      query << "INSERT INTO emprestimos (livro_id, usuario_emprestimo_id, "
            << "armario_id, data_emprestimo, data_devolucao_prevista, status) "
            << "VALUES ("
            << emprestimo.getLivroId() << ", "
            << emprestimo.getUsuarioId() << ", "
            << (emprestimo.getArmarioId() ? std::to_string(emprestimo.getArmarioId()) : "NULL") << ", "
            << "CURRENT_TIMESTAMP, "
            << "CURRENT_TIMESTAMP + INTERVAL '" << emprestimo.getDiasPrazo() << " days', "
            << "'ativo') RETURNING id;";

            result res = txn.exec(query.str());
            txn.commit();

            if (!res.empty()) {
              emprestimo.setId(res[0][0].as<int>());
              return true;
            }
            */
    return false;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao criar empréstimo: " + std::string(e.what()));
  }
}

bool EmprestimoRepository::atualizarEmprestimo(const Emprestimo &emprestimo)
{
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    std::stringstream query;
    query << "UPDATE emprestimos SET "
    << "data_devolucao_prevista = '" << emprestimo.getDataDevolucaoPrevista() << "', "
    << "data_devolucao_real = "
    << (emprestimo.getDataDevolucaoReal().empty() ? "NULL" : "'" + emprestimo.getDataDevolucaoReal() + "'") << ", "
    << "status = '" << emprestimo.getStatus() << "', "
    << "armario_id = " << (emprestimo.getArmarioId() ? std::to_string(emprestimo.getArmarioId()) : "NULL") << " "
    << "WHERE id = " << emprestimo.getId() << ";";

    txn.exec(query.str());
    txn.commit();
    */
    return true;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao atualizar empréstimo: " + std::string(e.what()));
  }
}

bool EmprestimoRepository::removerEmprestimo(int id)
{
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    txn.exec("DELETE FROM emprestimos WHERE id = " + std::to_string(id) + ";");
    txn.commit();
    */
    return true;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao remover empréstimo: " + std::string(e.what()));
  }
}

Emprestimo *EmprestimoRepository::buscarPorId(int id)
{
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    result res = txn.exec(
      "SELECT id, livro_id, usuario_emprestimo_id, armario_id, "
      "data_emprestimo, data_devolucao_prevista, data_devolucao_real, status "
      "FROM emprestimos WHERE id = " +
      std::to_string(id) + ";");

      if (!res.empty())
      {
        auto row = res[0];
        Emprestimo emprestimo(
          row["livro_id"].as<int>(),
          row["usuario_emprestimo_id"].as<int>(),
          row["armario_id"].is_null() ? 0 : row["armario_id"].as<int>(),
          row["data_devolucao_prevista"].as<std::string>());

          emprestimo.setId(row["id"].as<int>());
          emprestimo.setDataEmprestimo(row["data_emprestimo"].as<std::string>());
          if (!row["data_devolucao_real"].is_null())
          {
            emprestimo.setDataDevolucaoReal(row["data_devolucao_real"].as<std::string>());
          }
          emprestimo.setStatus(row["status"].as<std::string>());
          return emprestimo;

        }
        */
    return nullptr;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao buscar empréstimo: " + std::string(e.what()));
  }
}

std::vector<Emprestimo> EmprestimoRepository::buscarTodos()
{
  std::vector<Emprestimo> emprestimos;
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    result res = txn.exec(
      "SELECT id, livro_id, usuario_emprestimo_id, armario_id, "
      "data_emprestimo, data_devolucao_prevista, data_devolucao_real, status "
        "FROM emprestimos;");

    for (const auto &row : res)
    {
      Emprestimo emprestimo(
          row["livro_id"].as<int>(),
          row["usuario_emprestimo_id"].as<int>(),
          row["armario_id"].is_null() ? 0 : row["armario_id"].as<int>(),
          row["data_devolucao_prevista"].as<std::string>());

          emprestimo.setId(row["id"].as<int>());
          emprestimo.setDataEmprestimo(row["data_emprestimo"].as<std::string>());
          if (!row["data_devolucao_real"].is_null())
          {
            emprestimo.setDataDevolucaoReal(row["data_devolucao_real"].as<std::string>());
          }
          emprestimo.setStatus(row["status"].as<std::string>());
          emprestimos.push_back(emprestimo);
        }
        */
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao buscar empréstimos: " + std::string(e.what()));
  }
  return emprestimos;
}

std::vector<Emprestimo> EmprestimoRepository::buscarPorUsuario(int usuarioId)
{
  std::vector<Emprestimo> emprestimos;
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    result res = txn.exec(
        "SELECT id, livro_id, armario_id, data_emprestimo, "
        "data_devolucao_prevista, data_devolucao_real, status "
        "FROM emprestimos WHERE usuario_emprestimo_id = " +
        std::to_string(usuarioId) + ";");

    for (const auto &row : res)
    {
      Emprestimo emprestimo(
        row["livro_id"].as<int>(),
        usuarioId,
        row["armario_id"].is_null() ? 0 : row["armario_id"].as<int>(),
        row["data_devolucao_prevista"].as<std::string>());

        emprestimo.setId(row["id"].as<int>());
        emprestimo.setDataEmprestimo(row["data_emprestimo"].as<std::string>());
        if (!row["data_devolucao_real"].is_null())
        {
          emprestimo.setDataDevolucaoReal(row["data_devolucao_real"].as<std::string>());
        }
        emprestimo.setStatus(row["status"].as<std::string>());
        emprestimos.push_back(emprestimo);
      }
      */
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao buscar empréstimos do usuário: " + std::string(e.what()));
  }
  return emprestimos;
}

std::vector<Emprestimo> EmprestimoRepository::buscarPorLivro(int livroId)
{
  std::vector<Emprestimo> emprestimos;
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    result res = txn.exec(
        "SELECT id, usuario_emprestimo_id, armario_id, data_emprestimo, "
        "data_devolucao_prevista, data_devolucao_real, status "
        "FROM emprestimos WHERE livro_id = " +
        std::to_string(livroId) + ";");

    for (const auto &row : res)
    {
      Emprestimo emprestimo(
        livroId,
          row["usuario_emprestimo_id"].as<int>(),
          row["armario_id"].is_null() ? 0 : row["armario_id"].as<int>(),
          row["data_devolucao_prevista"].as<std::string>());

      emprestimo.setId(row["id"].as<int>());
      emprestimo.setDataEmprestimo(row["data_emprestimo"].as<std::string>());
      if (!row["data_devolucao_real"].is_null())
      {
        emprestimo.setDataDevolucaoReal(row["data_devolucao_real"].as<std::string>());
      }
      emprestimo.setStatus(row["status"].as<std::string>());
      emprestimos.push_back(emprestimo);
    }
    */
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao buscar empréstimos do livro: " + std::string(e.what()));
  }
  return emprestimos;
}

std::vector<Emprestimo> EmprestimoRepository::buscarEmprestimosAtivos()
{
  std::vector<Emprestimo> emprestimos;
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    result res = txn.exec(
        "SELECT id, livro_id, usuario_emprestimo_id, armario_id, "
        "data_emprestimo, data_devolucao_prevista "
        "FROM emprestimos WHERE status = 'ativo';");

    for (const auto &row : res)
    {
      Emprestimo emprestimo(
        row["livro_id"].as<int>(),
        row["usuario_emprestimo_id"].as<int>(),
        row["armario_id"].is_null() ? 0 : row["armario_id"].as<int>(),
        row["data_devolucao_prevista"].as<std::string>());

      emprestimo.setId(row["id"].as<int>());
      emprestimo.setDataEmprestimo(row["data_emprestimo"].as<std::string>());
      emprestimo.setStatus("ativo");
      emprestimos.push_back(emprestimo);
    }
    */
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao buscar empréstimos ativos: " + std::string(e.what()));
  }
  return emprestimos;
}

std::vector<Emprestimo> EmprestimoRepository::buscarEmprestimosAtrasados()
{
  std::vector<Emprestimo> emprestimos;
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    result res = txn.exec(
        "SELECT id, livro_id, usuario_emprestimo_id, armario_id, "
        "data_emprestimo, data_devolucao_prevista "
        "FROM emprestimos WHERE status = 'ativo' "
        "AND data_devolucao_prevista < CURRENT_TIMESTAMP;");

    for (const auto &row : res)
    {
      Emprestimo emprestimo(
        row["livro_id"].as<int>(),
        row["usuario_emprestimo_id"].as<int>(),
        row["armario_id"].is_null() ? 0 : row["armario_id"].as<int>(),
          row["data_devolucao_prevista"].as<std::string>());

      emprestimo.setId(row["id"].as<int>());
      emprestimo.setDataEmprestimo(row["data_emprestimo"].as<std::string>());
      emprestimo.setStatus("atrasado");
      emprestimos.push_back(emprestimo);
    }
    */
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao buscar empréstimos atrasados: " + std::string(e.what()));
  }
  return emprestimos;
}

bool EmprestimoRepository::finalizarEmprestimo(int emprestimoId)
{
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    txn.exec(
        "UPDATE emprestimos SET "
        "data_devolucao_real = CURRENT_TIMESTAMP, "
        "status = 'finalizado' "
        "WHERE id = " +
        std::to_string(emprestimoId) + ";");
    txn.commit();
    return true;
    */
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao finalizar empréstimo: " + std::string(e.what()));
  }
}

bool EmprestimoRepository::renovarEmprestimo(int emprestimoId, const int dias)
{
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    txn.exec(
      "UPDATE emprestimos SET "
      "data_devolucao_prevista = data_devolucao_prevista + INTERVAL '" +
      std::to_string(dias.count()) + " days' "
      "WHERE id = " +
      std::to_string(emprestimoId) + " "
      "AND status = 'ativo';");
      txn.commit();
      */
    return true;
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao renovar empréstimo: " + std::string(e.what()));
  }
}

bool EmprestimoRepository::verificarAtrasos(int usuarioId)
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
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao verificar atrasos: " + std::string(e.what()));
  }
}

std::vector<Emprestimo> EmprestimoRepository::buscarHistoricoCompleto(int usuarioId)
{
  std::vector<Emprestimo> emprestimos;
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    result res = txn.exec(
        "SELECT e.id, e.livro_id, e.armario_id, e.data_emprestimo, "
        "e.data_devolucao_prevista, e.data_devolucao_real, e.status, "
        "l.titulo, l.autor "
        "FROM emprestimos e "
        "JOIN livros l ON e.livro_id = l.id "
        "WHERE e.usuario_emprestimo_id = " +
        std::to_string(usuarioId) + " "
                                    "ORDER BY e.data_emprestimo DESC;");

                                    for (const auto &row : res)
                                    {
                                      Emprestimo emprestimo(
                                        row["livro_id"].as<int>(),
                                        usuarioId,
          row["armario_id"].is_null() ? 0 : row["armario_id"].as<int>(),
          row["data_devolucao_prevista"].as<std::string>());

          emprestimo.setId(row["id"].as<int>());
          emprestimo.setDataEmprestimo(row["data_emprestimo"].as<std::string>());
          if (!row["data_devolucao_real"].is_null())
          {
            emprestimo.setDataDevolucaoReal(row["data_devolucao_real"].as<std::string>());
          }
          emprestimo.setStatus(row["status"].as<std::string>());
          emprestimo.setLivroInfo(row["titulo"].as<std::string>(), row["autor"].as<std::string>());
          emprestimos.push_back(emprestimo);
        }
        */
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao buscar histórico: " + std::string(e.what()));
  }
  return emprestimos;
}

std::vector<Emprestimo> EmprestimoRepository::buscarEmprestimosPorArmario(int armarioId)
{
  std::vector<Emprestimo> emprestimos;
  try
  {
    /*
    work txn(*dbConnector->getConnection());

    result res = txn.exec(
        "SELECT id, livro_id, usuario_emprestimo_id, data_emprestimo, "
        "data_devolucao_prevista, data_devolucao_real, status "
        "FROM emprestimos WHERE armario_id = " +
        std::to_string(armarioId) + " "
                                    "AND status = 'ativo';");

    for (const auto &row : res)
    {
      Emprestimo emprestimo(
        row["livro_id"].as<int>(),
        row["usuario_emprestimo_id"].as<int>(),
        armarioId,
          row["data_devolucao_prevista"].as<std::string>());

      emprestimo.setId(row["id"].as<int>());
      emprestimo.setDataEmprestimo(row["data_emprestimo"].as<std::string>());
      if (!row["data_devolucao_real"].is_null())
      {
        emprestimo.setDataDevolucaoReal(row["data_devolucao_real"].as<std::string>());
      }
      emprestimo.setStatus(row["status"].as<std::string>());
      emprestimos.push_back(emprestimo);
    }
    */
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Erro ao buscar empréstimos do armário: " + std::string(e.what()));
  }
  return emprestimos;
}