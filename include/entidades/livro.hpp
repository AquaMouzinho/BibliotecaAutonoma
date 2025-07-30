#ifndef LIVRO_H
#define LIVRO_H

#include <string>

class Usuario;
class Armario;

class Livro {
private:
    std::string isbn;            
    std::string titulo;          
    std::string autor;           
    std::string tagRFID;         
    Usuario* proprietario;       
    Armario* armario;            
    bool disponivel;             

public:
    Livro(const std::string& isbn, const std::string& titulo,
          const std::string& autor, const std::string& tagRFID,
          Usuario* proprietario, Armario* armario, bool disponivel = true);

    Emprestimo* getHistoricoEmprestimos() const;
    Armario* getLocalizacaoAtual() const;
    Usuario* getProprietario() const;
    
};

#endif // LIVRO_H
