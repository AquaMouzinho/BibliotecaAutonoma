#pragma once
#include "../repositorios/UsuarioRepository.hpp"
#include "../repositorios/EmprestimoRepository.hpp"
#include "../strategy/AutenticacaoStrategy.hpp"
#include "../strategy/AutenticacaoSenha.hpp"
#include "../model/Usuario.hpp"
#include <memory>

class AutenticacaoService
{
private:
  UsuarioRepository *usuarioRepository;
  EmprestimoRepository *emprestimoRepository;
  AutenticacaoStrategy* estrategia;

public:
  AutenticacaoService(UsuarioRepository *usuarioRepo, EmprestimoRepository *emprestimoRepo, AutenticacaoStrategy* estrategia = nullptr) : usuarioRepository(usuarioRepo), emprestimoRepository(emprestimoRepo), estrategia(estrategia) {
    if (!this->estrategia) {
      this->estrategia = new AutenticacaoSenha(usuarioRepo);
    }
  }

  void definirEstrategia(AutenticacaoStrategy* novaEstrategia);
  Usuario* autenticar(const std::string &matricula, const std::string &senha);

  // Métodos adicionais
  bool verificarAtrasos(const std::string &matricula);
  bool bloquearUsuario(const std::string &matricula);
  bool desbloquearUsuario(const std::string &matricula);
  bool alterarSenha(const std::string &matricula, const std::string &senhaAtual, const std::string &novaSenha);
};