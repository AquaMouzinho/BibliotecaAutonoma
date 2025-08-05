#ifndef EMPRESTIMO_HPP
#define EMPRESTIMO_HPP

#include <string>

class Emprestimo {
  private:
    int id;
    std::string livro_isbn;
    std::string usuario_matricula;
    std::string data_emprestimo;
    std::string data_devolucao;
    std::string status;
    std::string tag_rfid;
    
  public:
    Emprestimo() : id(0), livro_isbn(""), usuario_matricula(""), data_emprestimo(""), data_devolucao(""), status(""), tag_rfid("") {};

    Emprestimo(int id, std::string livro_isbn, std::string usuario_matricula, std::string data_emprestimo, std::string data_devolucao, std::string status, std::string tag_rfid) : id(id), livro_isbn(livro_isbn), usuario_matricula(usuario_matricula), data_emprestimo(data_emprestimo), data_devolucao(data_devolucao), status(status), tag_rfid(tag_rfid) {}

    ~Emprestimo() = default;

    int getId() const { return id; };
    void setId(int id) { this->id = id; };

    std::string getLivroIsbn() const { return livro_isbn; };
    void setLivroIsbn(std::string livro_isbn) { this->livro_isbn = livro_isbn; };

    std::string getUsuarioMatricula() const { return usuario_matricula; };
    void setUsuarioMatricula(std::string usuario_matricula) { this->usuario_matricula = usuario_matricula; }

    std::string getDataEmprestimo() const { return data_emprestimo; };
    void setDataEmprestimo(std::string data_emprestimo) { this->data_emprestimo = data_emprestimo; };

    std::string getDataDevolucao() const { return data_devolucao; };
    void setDataDevolucao(std::string data_devolucao) { this->data_devolucao = data_devolucao; };

std::string getStatus() const { return status; };
    void setStatus(std::string status) { this->status = status; };

    std::string getTagLivro() const { return tag_rfid; };
    void setTagLivro(std::string tag_rfid) { this->tag_rfid = tag_rfid; }
};

#endif