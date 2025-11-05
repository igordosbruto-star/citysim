# CONTRIBUTING — City Simulator

Obrigado por querer contribuir com o **City Simulator**! 🏙️  
Este guia explica como propor ideias, reportar bugs e enviar PRs de forma eficiente.

## Como posso ajudar?
- **Bugs**: abra uma *issue* descrevendo passos para reproduzir.
- **Novas features**: proponha primeiro em uma *issue* explicando contexto e motivação.
- **Docs**: melhorias no `VISION.md`, `ROADMAP.md`, tutoriais e documentação técnica.
- **Sistemas de jogo**: sugestões para tech-tree, simulação, economia ou UI.

## Requisitos básicos
- **Linguagem**: C++17
- **Build**: CMake
- **Gráficos/Audio/Input**: SFML
- **ECS**: Entity Component System (entt)
- **Dados**: JSON (nlohmann/json)
- **Arte**: Pixel art top-down (estilo RPG Maker)

> **Dica importante**: Consulte o `ROADMAP.md` para alinhar sua contribuição com os marcos do projeto.

## Fluxo para contribuir
1. **Abra uma issue** (bug/feature) e descreva o objetivo.
2. **Crie uma branch** a partir da `main`:  
   `feature/nome-curto` ou `fix/descricao-breve`
3. **Faça commits pequenos e claros** (ver padrão abaixo).
4. **Inclua testes** quando alterar lógica central (tech-tree, simulação, economia).
5. **Atualize a documentação** afetada (VISION.md, ROADMAP.md, docs técnicas).
6. **Atualize o CHANGELOG** (seção **[Unreleased]**).
7. **Abra o PR** linkando a issue e marcando o checklist.

## Padrão de commits
Use mensagens descritivas e no imperativo. Você pode seguir *Conventional Commits* (opcional), por exemplo:
- `feat(tech-tree): adiciona sistema de ramificações exclusivas`
- `fix(pathfinding): corrige travamento com 500+ veículos`
- `docs(vision): atualiza metas de performance para 15k habitantes`
- `perf(ecs): otimiza atualização de componentes de cidadãos`

## Diretrizes de código (resumo)
- **Estilo**: C++ moderno, RAII, `unique_ptr`/`shared_ptr` quando apropriado
- **Arquitetura**: ECS para entidades (cidadãos, veículos, edifícios)
- **Performance**: Mantenha 60 FPS como meta, otimize para grandes cidades
- **Nomes**: `PascalCase` para tipos, `camelCase` para variáveis/funções
- **Dados**: Estruturas eficientes para tilemaps e grafos de pathfinding
- **Tech-tree**: Sistema modular para fácil expansão de tecnologias

## Abrindo issues
- **Bug**: passos para reproduzir, resultado esperado x obtido, logs/prints, versão/OS
- **Feature**: problema que resolve, proposta, impacto na tech-tree/simulação, alternativas consideradas

## Abrindo PRs (checklist)
- [ ] Issue linkada (`Closes #123`)
- [ ] Pequeno e focado (ou explique por que precisa ser maior)
- [ ] **CHANGELOG** atualizado em **[Unreleased]**
- [ ] Documentação atualizada (se aplicável)
- [ ] Alinhado ao `ROADMAP.md` **ou** justificada a exceção
- [ ] Testes passam (quando aplicável)

## Documentação
- **VISION.md**: Diretrizes de design e escopo do jogo
- **ROADMAP.md**: Marcos de desenvolvimento e progressão
- **AGENTS.md**: Guidelines para assistentes de IA
- Mudanças relevantes em docs entram no CHANGELOG em **Docs**

## Foco do Projeto
Lembre-se que o City Simulator é centrado em:
- **Tech-tree progressiva** como núcleo da jogabilidade
- **Simulação profunda** com agentes inteligentes
- **Performance** estável mesmo com cidades grandes
- **Pixel art top-down** com estilo consistente

## Licença
Ao contribuir, você concorda que sua contribuição será licenciada sob **MIT** junto com o City Simulator.

## Código de Conduta
Seja respeitoso, acolhedor e colaborativo. Mantenha o foco no desenvolvimento do jogo e na construção de uma comunidade positiva.

---

**Última atualização:** 04-11-2025  
**Próxima revisão:** Quinzenal ou conforme necessidade