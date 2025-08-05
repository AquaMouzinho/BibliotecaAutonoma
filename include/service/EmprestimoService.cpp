#include "EmprestimoService.hpp"
#include "../command/ComandoEmprestarLivro.hpp"
#include "../command/ComandoDevolverLivro.hpp"
#include "../utils/DateTimeUtils.hpp"

EmprestimoService::EmprestimoService(EmprestimoRepository* emprestimoRepo, UsuarioRepository* usuarioRepo, LivroRepository* livroRepo, NotificacaoService* notificacaoService) :
    emprestimoRepo(emprestimoRepo), usuarioRepo(usuarioRepo), livroRepo(livroRepo),
    notificacaoService(notificacaoService),
    invoker(new Invoker()) {};

bool EmprestimoService::criarEmprestimo(const std::string& matricula, const std::string& tagRFID) {
    // Verifica se já existe um empréstimo ativo para o mesmo livro
    auto emprestimoExistente = buscarEmprestimoAtivoPorTag(tagRFID);
    if (emprestimoExistente.getId() > 0)
        return false;

    // Verifica se usuario existe
    if (!usuarioRepo->buscarUsuarioPorMatricula(matricula)) return false;
    // Verifica se livro existe
    if (!livroRepo->buscarPorRfid(tagRFID)) return false;

    // Cria um novo empréstimo
    Emprestimo novo;
    novo.setLivroIsbn(livroRepo->buscarPorRfid(tagRFID)->getIsbn());
    novo.setUsuarioMatricula(matricula);
    novo.setDataEmprestimo(DateTimeUtils::getCurrentDateTime());
    novo.setStatus("ativo");
    novo.setTagLivro(tagRFID);

    return emprestimoRepo->criarEmprestimo(novo);
}

bool EmprestimoService::encerrarEmprestimo(int emprestimoId) {
    // Verifica se o empréstimo existe e está ativo
    auto emprestimo = emprestimoRepo->buscarPorId(emprestimoId);
    if (!emprestimo || emprestimo->getStatus() != "ativo"){
        delete emprestimo;
        return false;
    }

    // Atualiza a data de devolução
    emprestimo->setDataDevolucao(DateTimeUtils::getCurrentDateTime());
    emprestimo->setStatus("finalizado");
    
    // Atualiza o status do empréstimo para "finalizado"
    return emprestimoRepo->atualizarEmprestimo(*emprestimo);
}

// Métodos para os comandos
bool EmprestimoService::executarCriacaoEmprestimo(const std::string& matricula, const std::string& tagRFID) {
    return criarEmprestimo(matricula, tagRFID);
}

bool EmprestimoService::executarEncerramentoEmprestimo(int emprestimoId) {
    return encerrarEmprestimo(emprestimoId);
}

// Controle de comandos
void EmprestimoService::emprestarLivro(const std::string& matricula, const std::string& tagRFID) {
    auto cmd = new ComandoEmprestarLivro(this, matricula, tagRFID);
    invoker->executarComando(cmd);
}

void EmprestimoService::devolverLivro(const std::string& tagRFID) {
    auto cmd = new ComandoDevolverLivro(this, tagRFID);
    invoker->executarComando(cmd);
}

void EmprestimoService::desfazerUltimaOperacao() {
    invoker->desfazerUltimoComando();
}

// Consultas
Emprestimo EmprestimoService::buscarEmprestimoAtivoPorTag(const std::string& tagRFID) const {
    return emprestimoRepo->buscarEmprestimoAtivoPorTag(tagRFID);
}

std::vector<Emprestimo> EmprestimoService::buscarEmprestimosAtivosPorUsuario(const std::string& matricula) const {
    return emprestimoRepo->buscarPorUsuario(matricula);
}

void EmprestimoService::notificarDonoLivro(const std::string& tagRFID, const std::string& mensagem) {
    if (notificacaoService) {
        // Obter matrícula do dono do livro
        std::string donoMatricula = emprestimoRepo->buscarDonoLivro(tagRFID);
        if (!donoMatricula.empty()) {
            notificacaoService->notificar(donoMatricula, mensagem);
        }
    }
}