#pragma once
#include "../repository/EmprestimoRepository.hpp"
#include "../repository/UsuarioRepository.hpp"
#include "../repository/LivroRepository.hpp"
#include <vector>
#include <map>

class BibliotecaService {
private:
    EmprestimoRepository& emprestimoRepo;
    UsuarioRepository& usuarioRepo;
    LivroRepository& livroRepo;

public:
    BibliotecaService(EmprestimoRepository& eRepo, 
                     UsuarioRepository& uRepo,
                     LivroRepository& lRepo)
        : emprestimoRepo(eRepo), usuarioRepo(uRepo), livroRepo(lRepo) {}

    // Relatórios
    std::map<std::string, int> gerarRelatorioEmprestimosPorUsuario() {
        std::map<std::string, int> relatorio;
        auto usuarios = usuarioRepo.listarUsuarios();

        for (const auto& usuario : usuarios) {
            int count = emprestimoRepo.buscarPorUsuario(usuario.getMatricula()).size();
            relatorio[usuario.getNome()] = count;
        }

        return relatorio;
    }

    // Consultas Combinadas
    std::vector<Livro> buscarLivrosDisponiveis() {
        return livroRepo.buscarLivrosDisponiveis();
    }

    std::vector<Livro> buscarLivrosPorDoador(const std::string& matricula) {
        return livroRepo.buscarLivrosPorDoador(matricula);
    }

    // Controle de Disponibilidade
    bool verificarLivroDisponivel(const std::string& isbn) {
        auto livro = livroRepo.buscarPorISBN(isbn);
        return livro && livro->isDisponivel();
    }
};