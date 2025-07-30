#ifndef USUARIO_REPOSITORY_HPP
#define USUARIO_REPOSITORY_HPP

#include "../entidades/Usuario.hpp"
#include "../database/IDatabaseConnector.hpp"
#include <memory>
#include <vector>
// #include <optional>

class UsuarioRepository
{
private:
  IDatabaseConnector *dbConnector;

public:
  explicit UsuarioRepository(IDatabaseConnector *connector);

  // CRUD básico
  bool criarUsuario(const Usuario &usuario);
  bool atualizarUsuario(const Usuario &usuario);
  bool removerUsuario(int id);
  Usuario *buscarPorId(int id);
  std::vector<Usuario> buscarTodos();

  // Métodos específicos do domínio
  Usuario *autenticar(const std::string &matricula, const std::string &senha);
  bool usuarioPossuiEmprestimosAtrasados(int usuarioId);
  bool matriculaExiste(const std::string &matricula);
  bool bloquearUsuario(int id);
  bool desbloquearUsuario(int id);

  // Métodos administrativos
  std::vector<Usuario> buscarPorNome(const std::string &nome);
  std::vector<Usuario> buscarAdministradores();
};

#endif