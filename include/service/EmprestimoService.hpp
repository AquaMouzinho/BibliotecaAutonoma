#pragma once
#include "../repository/EmprestimoRepository.hpp"
#include "../repository/LivroRepository.hpp"
#include "../repository/UsuarioRepository.hpp"
#include "../repository/NotificacaoRepository.hpp"
#include "../entidades/Emprestimo.hpp"
#include "../command/ComandoEmprestarLivro.hpp"
#include "../command/ComandoDevolverLivro.hpp"
#include <memory>

class EmprestimoService
{
private:
  EmprestimoRepository *emprestimoRepository;
  LivroRepository *livroRepository;
  UsuarioRepository *usuarioRepository;
  NotificacaoRepository *notificacaoRepository;

  void notificarDonoLivro(int livroId, int usuarioEmprestimoId, const std::string &mensagem);

public:
  EmprestimoService(EmprestimoRepository *emprestimoRepo,
                    LivroRepository *livroRepo,
                    UsuarioRepository *usuarioRepo,
                    NotificacaoRepository *notifRepo);

  bool realizarEmprestimo(int livroId, int usuarioId, int armarioId);
  bool registrarDevolucao(int emprestimoId);
  bool renovarEmprestimo(int emprestimoId, int diasAdicionais);
  std::vector<Emprestimo> consultarHistoricoUsuario(int usuarioId);
  std::vector<Emprestimo> listarEmprestimosAtivos();
  std::vector<Emprestimo> listarEmprestimosAtrasados();
  bool verificarDisponibilidadeLivro(int livroId);
};