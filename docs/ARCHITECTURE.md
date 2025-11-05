# Arquitetura do Sistema

## Visão Geral
- **Motor**: SFML + ECS
- **Renderização**: Tile-based top-down
- **Simulação**: Sistema baseado em agentes
- **Dados**: JSON para configuração

## Componentes Principais
- `GameEngine` - Loop principal e gerenciamento de estados
- `WorldSystem` - Gerenciamento do mundo e tilemaps
- `TechTreeSystem` - Sistema de tecnologia e pesquisa
- `EconomySystem` - Simulação econômica