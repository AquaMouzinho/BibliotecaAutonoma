#ifndef ARMARIO_H
#define ARMARIO_H

#include <string>
#include <vector>

class Livro; // Declaração antecipada

class Armario {
private:
    std::string id;                    
    std::string localizacao;          
    bool disponivel;                   
    std::vector<Livro*> livros;

public:

    Armario(const std::string& id, const std::string& localizacao, bool disponivel = true);

    bool getStatus() const;

};

#endif // ARMARIO_H
