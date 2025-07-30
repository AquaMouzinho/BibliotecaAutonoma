#pragma once
#include "../entidades/Livro.hpp"
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
  bool removerLivro(int id);
  Livro *buscarPorId(int id);
  std::vector<Livro> buscarTodos();

  // Métodos específicos do domínio
  Livro *buscarPorRfid(const std::string &rfid);
  std::vector<Livro> buscarPorTitulo(const std::string &titulo);
  std::vector<Livro> buscarPorAutor(const std::string &autor);
  std::vector<Livro> buscarLivrosDisponiveis();
  std::vector<Livro> buscarLivrosPorDoador(int usuarioDoadorId);
  bool atualizarStatusLivro(int livroId, const std::string &status);
  bool livroEstaDisponivel(int livroId);
  bool associarRfid(int livroId, const std::string &rfid);
};