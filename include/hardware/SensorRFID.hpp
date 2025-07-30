#pragma once

#include <string>
#include <vector>

class SensorRFID
{
public:
  virtual ~SensorRFID() = default;

  virtual std::vector<std::string> lerTags() const = 0;
};