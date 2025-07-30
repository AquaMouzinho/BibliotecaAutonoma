#include "service/RFIDService.hpp"
#include <thread>

RFIDService::RFIDService(SensorRFID *sensor,
                         LivroRepository *livroRepo,
                         EmprestimoRepository *emprestimoRepo)
    : sensorRFID(sensor),
      livroRepository(livroRepo),
      emprestimoRepository(emprestimoRepo) {}

void RFIDService::monitorarTags()
{
  while (true)
  {
    auto tags = sensorRFID->lerTags();
    for (const auto &tag : tags)
    {
      processarTag(tag);
    }
    // std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

void RFIDService::processarTag(const std::string &tag)
{
  auto livro = livroRepository->buscarPorRfid(tag);
  if (livro)
  {
    // auto emprestimo = emprestimoRepository->buscarEmprestimosAtivosPorLivro(livro->getId());
    // Lógica de processamento...
  }
}
