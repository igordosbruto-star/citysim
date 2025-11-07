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
  - Sistema de tiles flexível usando SFML Quads
  - Suporte a textura única com múltiplos tiles
  - Otimização de renderização por batching
  - Controle dinâmico de visibilidade por tile
  - Sistema de coordenadas baseado em grid
- `UIRenderer` - Interface do usuário
- `LightingSystem` - Iluminação dinâmica

#### Sistema de Tiles
O sistema de tiles implementa:
- Gerenciamento eficiente de memória usando VertexArray
- Coordenadas de textura automáticas por tile
- Suporte a tiles vazios (ID -1)
- Validação de posições e limites
- Sistema de cache para otimização
- Interface clara para manipulação de tiles:
  - `Create(width, height, tileset)`: Inicialização do mapa
  - `SetTile(x, y, tileId)`: Definição de tiles
  - `GetTile(x, y)`: Consulta de tiles
  - `IsValidPosition(x, y)`: Validação de coordenadas

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