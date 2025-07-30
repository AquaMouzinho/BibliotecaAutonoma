#pragma once
#include "../repository/LivroRepository.hpp"
#include "../repository/UsuarioRepository.hpp"
#include "../entidades/Livro.hpp"
#include <vector>

class BibliotecaService
{
private:
  LivroRepository *livroRepository;
  UsuarioRepository *usuarioRepository;

public:
  BibliotecaService(LivroRepository *livroRepo,
                    UsuarioRepository *usuarioRepo);

  bool doarLivro(int usuarioDoadorId, const Livro &livro);
  bool removerLivro(int livroId);
  std::vector<Livro> buscarLivrosPorTitulo(const std::string &titulo);
  std::vector<Livro> buscarLivrosPorAutor(const std::string &autor);
  std::vector<Livro> listarLivrosDisponiveis();
  std::vector<Livro> listarLivrosUsuario(int usuarioId);
  bool associarRFID(int livroId, const std::string &tagRFID);
};