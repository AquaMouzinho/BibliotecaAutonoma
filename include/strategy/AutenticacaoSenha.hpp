#pragma once
#include "AutenticacaoStrategy.hpp"
#include "../repositorios/UsuarioRepository.hpp"
#include <iostream>

class AutenticacaoSenha : public AutenticacaoStrategy {
private:
    UsuarioRepository* usuarioRepository;

public:
    AutenticacaoSenha(UsuarioRepository* usuarioRepo) : usuarioRepository(usuarioRepo) {}

    Usuario* autenticar(const std::string& matricula, const std::string& senha) override {
        //std::cout << "Autenticando usuario por senha..." << std::endl;
        Usuario* usuario = usuarioRepository->buscarUsuarioPorMatricula(matricula);
        if (usuario && usuario->getSenhaHash() == senha && usuario->getAtivo()) {
            return usuario;
        }
        return nullptr;
    }
};