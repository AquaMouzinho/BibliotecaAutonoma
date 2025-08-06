# Biblioteca Autônoma - Sistema de Armários Inteligentes para Bibliotecas
---
## 📖 Visão Geral
Este projeto implementa um ecossistema de armários inteligentes para bibliotecas com dois modos de operação:
- Modo Físico: Interface direta com armários equipados com RFID, tranca digital e sensores
- Modo Web: Plataforma administrativa e de consulta para usuários e administradores

Ambos os sistemas compartilham um banco de dados comum (JSON-based) para sincronização em tempo real.

## ℹ️ Sobre
O projeto Biblioteca Autônoma foi desenvolvido por Marino Mouzinho e Lucas Silva Tavares como projeto final da disciplina "Padrões de Projeto" - orientada pelo Professor Katyusco Santos - do IFPB Campus Campina Grande.

## 🏗️ Arquitetura do Sistema
```
BibliotecaSistema/
├── include/
│   ├── model/       # Entidades do domínio
│   ├── repository/  # Camada de persistência
│   ├── database/    # Gerenciamento do banco de dados JSON
│   ├── controllers/ # Endpoints da API Web
│   ├── hardware/    # Interfaces e simuladores de hardware
│   ├── strategy/    # Padrão Strategy para autenticação
│   ├── command/     # Padrão Command para operações
│   ├── observer/    # Sistema de notificações
│   ├── facade/      # Fachadas para subsistemas
│   ├── service/     # Lógica de negócio
│   ├── web/         # Páginas Web + API
│   └── utils/       # Utilitários
└── main.cpp         # Ponto de entrada para Simulação de Hardware
```

## ⚙️ Funcionalidades Principais
### Modo Físico
- 🚪 Autenticação por matrícula/senha no display
- 🔓 Liberação automática da tranca após autenticação
- 📚 Detecção automática de livros via RFID
- ⏱️ Timeout de sessão (30s com porta fechada)
- 🔄 Processamento automático de empréstimos/devoluções
- 🔔 Notificações internas para donos de livros

### Modo Web
- 👤 Autenticação tradicional (matrícula/senha)
- 📊 Dashboard pessoal com:
  - Livros doados
  - Empréstimos ativos
  - Notificações
- 🛠️ Painel administrativo (CRUD completo) para:
  - Usuários
  - Livros
  - Empréstimos
