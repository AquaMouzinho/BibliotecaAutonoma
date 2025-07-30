CREATE TABLE Usuario (
    id SERIAL PRIMARY KEY,
    matricula VARCHAR(20) UNIQUE NOT NULL,
    nome VARCHAR(100) NOT NULL,
    senha_hash VARCHAR(255) NOT NULL,
    role VARCHAR(20) CHECK (role IN ('USUARIO', 'ADMIN'))
);

CREATE TABLE Armario (
    id SERIAL PRIMARY KEY,
    localizacao VARCHAR(50) NOT NULL,
    disponivel BOOLEAN DEFAULT TRUE
);

CREATE TABLE Livro (
    id SERIAL PRIMARY KEY,
    isbn VARCHAR(20) UNIQUE NOT NULL,
    titulo VARCHAR(100) NOT NULL,
    autor VARCHAR(100) NOT NULL,
    tag_rfid VARCHAR(50) UNIQUE NOT NULL,
    usuario_id INTEGER REFERENCES Usuario(id) ON DELETE SET NULL,
    armario_id INTEGER REFERENCES Armario(id) ON DELETE SET NULL
);

CREATE TABLE Emprestimo (
    id SERIAL PRIMARY KEY,
    livro_id INTEGER REFERENCES Livro(id),
    usuario_locatario_id INTEGER REFERENCES Usuario(id),
    usuario_dono_id INTEGER REFERENCES Usuario(id),
    data_emprestimo TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    data_devolucao TIMESTAMP
    status VARCHAR(20) CHECK (status IN ('ATIVO', 'DEVOLVIDO', 'ATRASADO'))
);

CREATE TABLE Sessao (
    id SERIAL PRIMARY KEY,
    usuario_id INTEGER REFERENCES Usuario(id),
    armario_id INTEGER REFERENCES Armario(id),
    tipo VARCHAR(20) CHECK (tipo IN ('WEB', 'FISICA'))
    inicio TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    fim TIMESTAMP,
    status VARCHAR(20) CHECK (status IN ('ATIVA', 'FINALIZADA', 'EXPIRADA'))
);

CREATE TABLE Notificacao (
    id SERIAL PRIMARY KEY,
    usuario_id INTEGER REFERENCES Usuario(id),
    mensagem TEXT NOT NULL,
    data_criacao TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    lida BOOLEAN DEFAULT FALSE
);