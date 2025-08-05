#ifndef COMANDO_HPP
#define COMANDO_HPP

#include <memory>
#include "../model/Emprestimo.hpp"

class Comando
{
public:
  virtual ~Comando() = default;

  virtual void executar() = 0;
  virtual void desfazer() = 0;
  virtual std::string getMensagem() const = 0;
};

#endif