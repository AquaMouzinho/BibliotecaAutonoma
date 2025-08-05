#ifndef EMPRESTIMO_SERVICE_HPP
#define EMPRESTIMO_SERVICE_HPP

#include "../repositorios/EmprestimoRepository.hpp"
#include "../repositorios/LivroRepository.hpp"
#include "../repositorios/UsuarioRepository.hpp"
#include "../service/NotificacaoService.hpp"
#include "../command/Invoker.hpp"
#include "../model/Emprestimo.hpp"
#include <memory>

class EmprestimoService {
private:
    EmprestimoRepository* emprestimoRepo;
    UsuarioRepository* usuarioRepo;
    LivroRepository* livroRepo;
    NotificacaoService* notificacaoService;
    Invoker* invoker;

public:
  explicit EmprestimoService(EmprestimoRepository* emprestimoRepo, UsuarioRepository* usuarioRepo, LivroRepository* livroRepo, NotificacaoService* notificacaoService);

  // Métodos principais
  bool criarEmprestimo(const std::string& matricula, const std::string& tagRFID);
  bool encerrarEmprestimo(int emprestimoId);

  // Interface para os comandos
  bool executarCriacaoEmprestimo(const std::string& matricula, const std::string& tagRFID);
  bool executarEncerramentoEmprestimo(int emprestimoId);

  // Controle de comandos
  void emprestarLivro(const std::string& matricula, const std::string& tagRFID);
  void devolverLivro(const std::string& tagRFID);
  void desfazerUltimaOperacao();

  // Consultas
  Emprestimo buscarEmprestimoAtivoPorTag(const std::string& tagRFID) const;
  std::vector<Emprestimo> buscarEmprestimosAtivosPorUsuario(const std::string& matricula) const;

  void notificarDonoLivro(const std::string& tagRFID, const std::string& mensagem);

  void setNotificacaoService(NotificacaoService* service){ this->notificacaoService = service; }
    
};

#endif