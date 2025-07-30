#ifndef ESTADO_SESSAO_H
#define ESTADO_SESSAO_H

#include <string>
#include <vector>

class Sessao;

class EstadoSessao {
public:
    virtual ~EstadoSessao() = default;

    virtual bool autenticar(const std::string& matricula, const std::string& senha) = 0;
    virtual void processarRFID(const std::vector<std::string>& tags) = 0;
    virtual void lidarTimeout() = 0;
    virtual void setContext(Sessao* context) = 0;
};

#endif // ESTADO_SESSAO_H