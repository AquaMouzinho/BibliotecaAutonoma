#include "AutenticacaoService.hpp"

#include <memory>
#include <iostream>

void AutenticacaoService::definirEstrategia(AutenticacaoStrategy* novaEstrategia) {
    estrategia = novaEstrategia;
}

Usuario* AutenticacaoService::autenticar(const std::string& credencial, const std::string& senha) {
    //std::cout << "Autenticando usuario..." << std::endl;
    Usuario* usuario = estrategia->autenticar(credencial, senha);

    if (usuario && verificarAtrasos(usuario->getMatricula())) {
        return nullptr; // Usuário com atrasos não pode se autenticar
    }

    return usuario;
}

  // Métodos adicionais
bool AutenticacaoService::verificarAtrasos(const std::string &matricula) {
    return emprestimoRepository->verificarAtrasos(matricula);
}

bool AutenticacaoService::bloquearUsuario(const std::string &matricula){
    Usuario* usuario = usuarioRepository->buscarUsuarioPorMatricula(matricula);
    if (usuario) {
        usuario->setAtivo(false);
        usuarioRepository->atualizarUsuario(usuario);
        return true;
    }
    return false;
}

bool AutenticacaoService::desbloquearUsuario(const std::string &matricula){
    Usuario* usuario = usuarioRepository->buscarUsuarioPorMatricula(matricula);
    if (usuario){
        usuario->setAtivo(true);
        usuarioRepository->atualizarUsuario(usuario);
        return true;
    }
    return false;
}

bool AutenticacaoService::alterarSenha(const std::string &matricula, const std::string &senhaAtual, const std::string &novaSenha){
    Usuario* usuario = usuarioRepository->buscarUsuarioPorMatricula(matricula);
    if (usuario && usuario->getSenhaHash() == senhaAtual){
        usuario->setSenhaHash(novaSenha);
        usuarioRepository->atualizarUsuario(usuario);
        return true;
    }
    return false;
}