#include "../../include/service/BibliotecaService.hpp"

BibliotecaService::BibliotecaService(LivroRepository *livroRepo,
                                     UsuarioRepository *usuarioRepo)
    : livroRepository(livroRepo),
      usuarioRepository(usuarioRepo) {}

bool BibliotecaService::doarLivro(int usuarioDoadorId, const Livro &livro)
{
  Livro livroParaDoar = livro;
  // livroParaDoar.setUsuarioDoadorId(usuarioDoadorId);
  return livroRepository->criarLivro(livroParaDoar);
}

std::vector<Livro> BibliotecaService::buscarLivrosPorTitulo(const std::string &titulo)
{
  return livroRepository->buscarPorTitulo(titulo);
}
