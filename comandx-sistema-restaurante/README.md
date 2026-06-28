# ComandX — Sistema de Gestão para Restaurante

Sistema desktop para gestão de restaurantes, desenvolvido como projeto final da disciplina de Engenharia de Software I. Cobre controle de acesso, gestão de salão (mesas), comandas e cardápio digital, com arquitetura orientada a serviços e cobertura de testes.

## Contexto

O projeto foi construído em sprints incrementais (metodologia ágil — Scrum/Kanban), com levantamento de requisitos, modelagem, implementação e **validação junto ao cliente** a cada entrega. Este repositório representa a versão final do sistema (não foi totalmente implementada).

## Arquitetura

O sistema é dividido em módulos independentes (cada um com sua própria interface e implementação, seguindo o padrão **Factory**):

| Módulo | Responsabilidade |
|---|---|
| `ControleAcessoService` | Autenticação e controle de acesso de usuários |
| `GestaoSalaoService` | Gestão de mesas e status do salão |
| `GestaoComandasService` | Abertura, fechamento e itens das comandas |
| `CardapioDigitalService` | Cadastro e consulta de itens do cardápio |
| `core` | Entidades compartilhadas (`Usuario`, `Mesa`, `Comanda`, `ItemCardapio`) |

Cada serviço expõe uma interface (`I*Service.h`) implementada por uma classe concreta (`*ServiceImpl`), permitindo baixo acoplamento e testes isolados por módulo.

## Tecnologias

- **C++** com **Qt** (interface gráfica e build system `qmake`)
- Documentação técnica gerada com **Doxygen**
- Testes unitários com **Qt Test**

## Como executar

```bash
qmake ComandX.pro
make
./app/ComandX
```

(Requer Qt 6 instalado com suporte a `qmake`.)

## Testes

```bash
cd tests
qmake tests.pro && make && ./tests
```

## Metodologia de desenvolvimento

- Sprints semanais com entregas incrementais
- Testes unitários e automatizados por módulo
- Documentação técnica em Doxygen
- Versionamento de código em Git
- Validação de requisitos com o cliente a cada sprint
