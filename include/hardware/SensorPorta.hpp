#pragma once

class SensorPorta
{
public:
  virtual ~SensorPorta() = default;
  virtual bool estaAberta() const = 0;
};