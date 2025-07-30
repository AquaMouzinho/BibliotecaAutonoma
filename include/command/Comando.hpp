#ifndef COMANDO_HPP
#define COMANDO_HPP

#include <string>

class Comando
{
public:
  virtual void executar() = 0;
  virtual std::string getNome() const = 0;
};

#endif