#ifndef NOTIFICACAO_H
#define NOTIFICACAO_H

#include <string>
#include <chrono>

class Usuario;

class Notificacao {
private:
    int id;                                                 
    Usuario* usuario;                                        
    std::string mensagem;                                    
    std::chrono::system_clock::time_point data;              
    bool lida;                                               

public:
    Notificacao(int id, Usuario* usuario, const std::string& mensagem,
                std::chrono::system_clock::time_point data);

    void marcarComoLida();                                   

};

#endif // NOTIFICACAO_H
