# Arquitetura do Sistema CitySimulator

## Visão Geral
- **Motor**: SFML 3 + ECS (entt)
- **Renderização**: Tile-based top-down com OpenGL
- **Simulação**: Sistema baseado em agentes com tech-tree progressiva
- **Dados**: JSON (nlohmann_json) para configuração e save games
- **Scripting**: Lua + sol2 para mods e comportamentos

## Arquitetura em Camadas

### Camada de Core
- `GameEngine` - Loop principal e gerenciamento de estados
- `EntityManager` - Gerenciamento ECS de entidades
- `ResourceManager` - Carregamento de assets

### Camada de Simulação  
- `WorldSystem` - Gerenciamento do mundo e tilemaps
- `TechTreeSystem` - Sistema de tecnologia e pesquisa
- `EconomySystem` - Simulação econômica
- `CitizenSystem` - Simulação de cidadãos
- `TrafficSystem` - Sistema de tráfego e pathfinding

### Camada de Renderização
- `TilemapRenderer` - Renderização de mapas tile-based
- `UIRenderer` - Interface do usuário
- `LightingSystem` - Iluminação dinâmica

### Camada do Editor
- `CityEditor` - Aplicação principal do editor
- `MapEditor` - Edição de mapas e tilesets  
- `TechTreeEditor` - Edição visual da árvore tecnológica
- `BuildingEditor` - Ferramentas de edição de construções

## Componentes Principais (ECS)
- `CityComponent` - Dados da cidade
- `CitizenComponent` - Cidadãos com necessidades e rotinas
- `BuildingComponent` - Edifícios e zonas
- `VehicleComponent` - Veículos em tráfego
- `TechnologyComponent` - Tecnologias da tech-tree