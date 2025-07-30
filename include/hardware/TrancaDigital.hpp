#pragma once
#include <string>

class TrancaDigital
{
public:
  virtual ~TrancaDigital() = default;
  virtual void bloquear() = 0;
  virtual void liberar() = 0;
  virtual bool estaTrancada() const = 0;
};