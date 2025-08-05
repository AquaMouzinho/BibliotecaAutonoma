#pragma once
#include "../repositorios/ArmarioRepository.hpp"
#include "../repositorios/LivroRepository.hpp"
#include <vector>

class ArmarioService {
private:
    ArmarioRepository& armarioRepo;
    LivroRepository& livroRepo;

public:
    ArmarioService(ArmarioRepository& armarioRepo, LivroRepository& livroRepo)
        : armarioRepo(armarioRepo), livroRepo(livroRepo) {}

    bool verificarDisponibilidade(int armarioId) {
        return armarioRepo.buscarPorId(armarioId)->isDisponivel();
    }

    std::vector<Livro> listarLivrosNoArmario(int armarioId) {
        std::vector<Livro> livros;
        auto tags = armarioRepo.buscarLivrosNoArmario(armarioId);
        for (const auto& tag : tags) {
            auto livro = livroRepo.buscarPorRfid(tag);
            if (livro) livros.push_back(*livro);
        }
        return livros;
    }

    bool atualizarStatus(int armarioId, bool disponivel) {
        auto armario = armarioRepo.buscarPorId(armarioId);
        if (!armario) return false;

        armario->setDisponivel(disponivel);
        return armarioRepo.atualizarArmario(*armario);
    }

    bool adicionarLivro(int armarioId, const std::string& tagRFID) {
        auto armario = armarioRepo.buscarPorId(armarioId);
        if (!armario) return false;

        auto livro = livroRepo.buscarPorRfid(tagRFID);
        if (!livro) return false;

        auto livros = armario->getLivros();
        if (std::find(livros.begin(), livros.end(), tagRFID) == livros.end()) {
            livros.push_back(tagRFID);
            armario->setLivros(livros);
        }

        if (livro) {
            livro->setIdArmario(armarioId);
            livro->setDisponivel(true);
            livroRepo.atualizarLivro(*livro);
        }
        
        return armarioRepo.atualizarArmario(*armario);
    }

    bool removerLivro(int armarioId, const std::string& tagRFID) {
        auto armario = armarioRepo.buscarPorId(armarioId);
        if (!armario) return false;

        auto livro = livroRepo.buscarPorRfid(tagRFID);
        if (!livro) return false;

        auto livros = armario->getLivros();
        livros.erase(std::remove(livros.begin(), livros.end(), tagRFID), livros.end());
        armario->setLivros(livros);

        // Atualiza livro
        if (livro) {
            livro->setIdArmario(0); // 0 = não está em armário
            livro->setDisponivel(false);
            livroRepo.atualizarLivro(*livro);
        }
        
        return armarioRepo.atualizarArmario(*armario);
    }
};