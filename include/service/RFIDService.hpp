#pragma once
#include "../repository/LivroRepository.hpp"
#include "../repository/EmprestimoRepository.hpp"
#include "../hardware/SensorRFID.hpp"
#include <vector>
#include <memory>

class RFIDService
{
private:
  SensorRFID *sensorRFID;
  LivroRepository *livroRepository;
  EmprestimoRepository *emprestimoRepository;

  void processarTag(const std::string &tag);

public:
  RFIDService(SensorRFID *sensor,
              LivroRepository *livroRepo,
              EmprestimoRepository *emprestimoRepo);

  void monitorarTags();
  std::vector<std::string> lerTagsAtuais();
  bool associarTagLivro(const std::string &tag, int livroId);
  bool removerAssociacaoTag(const std::string &tag);
  int buscarLivroPorTag(const std::string &tag);
};