#pragma once
#include "../model/Livro.hpp"
#include "../database/IDatabaseConnector.hpp"
#include <vector>
#include <memory>

class LivroRepository
{
private:
  IDatabaseConnector *dbConnector;

public:
  explicit LivroRepository(IDatabaseConnector *connector);

  // CRUD básico
  bool criarLivro(Livro &livro);
  bool atualizarLivro(const Livro &livro);
  bool removerLivro(std::string isbn);
  Livro *buscarPorISBN(std::string isbn) const;
  std::vector<Livro> buscarTodos() const;

  // Métodos específicos do domínio
  Livro *buscarPorRfid(const std::string &rfid) const;
  std::vector<Livro> buscarPorTitulo(const std::string &titulo) const;
  std::vector<Livro> buscarPorAutor(const std::string &autor) const;
  std::vector<Livro> buscarLivrosDisponiveis() const;
  std::vector<Livro> buscarLivrosPorDoador(std::string usuarioDoadorMat) const;
  bool atualizarStatusLivro(std::string isbn, const std::string &status);
  bool livroEstaDisponivel(std::string isbn) const;
  bool associarRfid(std::string isbn, const std::string &rfid);
};