#ifndef NOTIFICACAO_H
#define NOTIFICACAO_H

#include <string>
#include "DateTime.h"
class Usuario;

class Notificacao {
private:
    int id;
    Usuario* usuario;
    std::string mensagem;
    DateTime data;
    bool lida;

public:
    Notificacao(int id, Usuario* usuario, const std::string& mensagem, const DateTime& data);
    void marcarComoLida();
};

#endif // NOTIFICACAO_H