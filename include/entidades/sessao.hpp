#ifndef SESSAO_H
#define SESSAO_H

#include <chrono>

class Usuario;
class Armario;
class EstadoSessao;

enum class TipoSessao {
    WEB,
    FISICA
};

class Sessao {
private:
    int id;                                               
    Usuario* usuario;                                     
    Armario* armario;                                     
    EstadoSessao* estadoAtual;                            
    TipoSessao tipo;                                      
    std::chrono::system_clock::time_point inicio;        
    std::chrono::system_clock::time_point fim;             
    int timeout_timer;                                     

public:
    Sessao(int id, Usuario* usuario, Armario* armario, TipoSessao tipo);

    void iniciar();                                         
    void reiniciarTimeout();                            
    void encerrar();                                       
    void setEstado(EstadoSessao* novoEstado);           

};

#endif // SESSAO_H
