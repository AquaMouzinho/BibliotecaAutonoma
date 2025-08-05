#pragma once
#include "../model/Usuario.hpp"
#include <string>

class AutenticacaoStrategy {
public:
    virtual ~AutenticacaoStrategy() = default;
    virtual Usuario* autenticar(const std::string& credencial, const std::string& senha) = 0;
};
