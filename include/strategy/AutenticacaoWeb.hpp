// include/strategy/AutenticacaoWeb.hpp
#pragma once
#include "AutenticacaoStrategy.hpp"
#include "../repositorios/UsuarioRepository.hpp"
#include "../utils/JWTUtils.hpp" // Supondo que você terá utilitários JWT

class AutenticacaoWeb : public AutenticacaoStrategy {
private:
    UsuarioRepository* usuarioRepository;

public:
    AutenticacaoWeb(UsuarioRepository* usuarioRepo) : usuarioRepository(usuarioRepo) {}

    Usuario* autenticar(const std::string& token, const std::string& /* não usado */) override {
        // Implemente a validação do token JWT
        std::string matricula = JWTUtils::extrairMatricula(token);
        if (!matricula.empty()) {
            return usuarioRepository->buscarUsuarioPorMatricula(matricula);
        }
        return nullptr;
    }
};