# Guia de Contribuição — City Simulator

> Este documento espelha o conteúdo do [CONTRIBUTING.md](../CONTRIBUTING.md) na raiz do repositório.
> Consulte-o para a versão completa e mantenha ambos alinhados ao atualizar o processo de contribuição.

## Visão Geral
- Alinhe propostas ao [ROADMAP](./ROADMAP.md) e à [VISION](./VISION.md).
- Use C++20, CMake e SFML como base técnica.
- Priorize tech-tree funcional, simulação profunda e performance estável.

## Passos Rápidos
1. Abra uma issue descrevendo contexto e objetivo.
2. Crie uma branch a partir da `main` (ex.: `feature/nome-curto`).
3. Faça commits pequenos, no imperativo (padrão *Conventional Commits* opcional).
4. Adicione testes quando afetar tech-tree, simulação ou economia.
5. Atualize documentação relacionada e o [CHANGELOG](./CHANGELOG.md) (`[Unreleased]`).
6. Abra o PR preenchendo o checklist e linkando a issue (`Closes #123`).

## Padrões Essenciais
- Estilo moderno em C++ (RAII, `unique_ptr`, ECS com entt).
- Meta de 60 FPS; evite regressões de performance.
- Componentes usam `PascalCase` (tipos) e `camelCase` (funções/variáveis).
- Assets seguem pixel art top-down.

## Recursos Úteis
- [docs/SETUP.md](./SETUP.md): instalação detalhada.
- [docs/ARCHITECTURE.md](./ARCHITECTURE.md): visão dos subsistemas.
- [docs/AGENTS.md](./AGENTS.md): diretrizes adicionais para agentes de IA.

> Ao contribuir, você concorda com a licença MIT aplicada ao City Simulator.
