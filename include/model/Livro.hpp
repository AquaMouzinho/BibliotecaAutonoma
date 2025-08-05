#ifndef LIVRO_HPP
#define LIVRO_HPP

#include <string>

class Livro {
  private:
    std::string isbn;
    std::string titulo;
    std::string autor;
    std::string tag_rfid;
    std::string matricula_doador;
    int id_armario;
    bool disponivel;

  public: 
    Livro() : isbn(""), titulo(""), autor(""), tag_rfid(""), matricula_doador(""), id_armario(0), disponivel(true) {};
    Livro(std::string isbn, std::string titulo, std::string autor, std::string tag_rfid, std::string matricula_doador, int id_armario, bool disponivel) : isbn(isbn) , titulo(titulo), autor(autor), tag_rfid(tag_rfid), matricula_doador(matricula_doador), id_armario(id_armario), disponivel(disponivel) {};
    ~Livro() = default;

    std::string getIsbn() const { return this->isbn; };
    void setIsbn(std::string isbn) { this->isbn = isbn; };
    std::string getTitulo() const { return this->titulo; };
    void setTitulo(std::string titulo) { this->titulo = titulo; };
    std::string getAutor() const { return this->autor; };
    void setAutor(std::string autor) { this->autor = autor; };
    std::string getTagRfid() const { return this->tag_rfid; };
    void setTagRfid(std::string tag_rfid) { this->tag_rfid = tag_rfid; };

    std::string getMatriculaDoador() const { return this->matricula_doador; };
    void setMatriculaDoador(std::string matricula_doador) { this->matricula_doador = matricula_doador; };

    int getIdArmario() const { return this->id_armario; };
    void setIdArmario(int id_armario) { this->id_armario = id_armario; }

    bool isDisponivel() const { return this->disponivel; };
    void setDisponivel(bool disponivel) { this->disponivel = disponivel; };
};

#endif