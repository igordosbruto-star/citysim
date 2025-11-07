[file name]: GAMEFLOW.md
[file content begin]
# City Simulator - Fluxo de Execução REAL

## FLUXO PRINCIPAL CORRIGIDO

main.cpp:              main()
    ↓
Logger.cpp:            Logger.initialize("city_simulator.log")
    ↓  
Config.cpp:            Config.load()                            ← "Usando configuração padrão" 
    ↓
Application.cpp:       Application.initialize()                 ← "Application inicializada"
    ↓
Game.cpp:              Game.initialize()                        ← "Game inicializado" + debug shape
    ↓  
Application.cpp:       Application.run(game)                    ← LOOP PRINCIPAL
    │   ├→ InputManager.cpp: InputManager::beginFrame()         ← Limpa estados de input
    │   ├→ Application.cpp: handleEvents(game)                  
    │   │   ├→ InputManager.cpp: processEvents()               ← Distribui eventos SFML
    │   │   │   ├→ Keyboard.cpp: handlePressed/Released()      ← Estado do teclado
    │   │   │   └→ Mouse.cpp: handleButtonPressed/Released()   ← Estado do mouse
    │   │   └→ Game.cpp: handleEvent()                         ← Só trata resize por enquanto
    │   ├→ Application.cpp: update(game, deltaTime)
    │   │   ├→ Game.cpp: update()                              ← Atualiza debug shape + input P
    │   │   └→ [SISTEMAS ECS NÃO CHAMADOS AUTOMATICAMENTE]     ← PROBLEMA IDENTIFICADO
    │   └→ Application.cpp: render(game)
    │       └→ Game.cpp: render()                              ← Renderiza apenas debug shape
    ↓
Game.cpp:              Game.shutdown()                          ← "Encerrando Game..."
    ↓
Application.cpp:       Application.shutdown()                   ← "Application encerrada"
    ↓
Logger.cpp:            Logger.shutdown()                        ← "Shutting down logger..."

## PROBLEMAS IDENTIFICADOS NO FLUXO ATUAL

### ❌ SISTEMA ECS NÃO INTEGRADO
World.cpp:             World criado mas NÃO usado no Game.cpp
RenderSystem.cpp:      Sistema de renderização ECS criado mas NÃO conectado
TransformSystem.cpp:   Sistema de transformação NÃO executado

### ❌ SISTEMAS DE SIMULAÇÃO ISOLADOS
ZoningSystem.cpp:      Tem referência ao Game mas NÃO é chamado no update()
BuildingSystem.cpp:    Tem referência ao Game mas NÃO é chamado no update()
PowerSystem.cpp:       Sistema completo mas NÃO conectado ao loop principal
WaterSystem.cpp:       Sistema completo mas NÃO conectado ao loop principal

### ❌ RENDERIZAÇÃO AVANÇADA NÃO UTILIZADA
Tilemap.cpp:           Sistema de tiles implementado mas NÃO usado
Tileset.cpp:           Tilesets prontos mas NÃO carregados
OverlaySystem.cpp:     Overlays implementados mas NÃO conectados
AlertSystem.cpp:       Alertas implementados mas NÃO renderizados

## FLUXO IDEAL (COMO DEVERIA SER)

Application.cpp:       update(deltaTime)
    └→ Game.cpp:       Game::update(deltaTime)
        ├→ World.cpp:  World::Update(deltaTime)                ← FALTA ESTA LINHA
        │   ├→ TransformSystem.cpp: TransformSystem::Update()
        │   ├→ RenderSystem.cpp:    RenderSystem::Update()
        │   ├→ PowerSystem.cpp:     PowerSystem::update()
        │   ├→ WaterSystem.cpp:     WaterSystem::update()
        │   ├→ ZoningSystem.cpp:    ZoningSystem::update()
        │   ├→ BuildingSystem.cpp:  BuildingSystem::update()
        │   ├→ GarbagePollutionSystem.cpp: GarbageSystem/PollutionSystem::update()
        │   ├→ OverlaySystem.cpp:   OverlaySystem::update()
        │   └→ AlertSystem.cpp:     AlertSystem::update()
        └→ Effects.cpp: Effects::update()

Application.cpp:       render()
    └→ Game.cpp:       Game::render()
        ├→ Renderer.cpp:   Renderer::beginFrame()
        ├→ Tilemap.cpp:    Tilemap::draw()                     ← FALTA ESTA LINHA
        ├→ RenderSystem.cpp:RenderSystem::Update() [render ECS]
        ├→ OverlaySystem.cpp:OverlaySystem::render()          ← FALTA
        ├→ AlertSystem.cpp:AlertSystem::render()              ← FALTA  
        ├→ Effects.cpp:    Effects::draw()                    ← FALTA
        └→ Renderer.cpp:   Renderer::endFrame()

## SISTEMAS IMPLEMENTADOS MAS NÃO CONECTADOS

✅ COMPLETOS MAS NÃO USADOS:
- PowerSystem.cpp:     Rede elétrica com propagação
- WaterSystem.cpp:     Rede de água com propagação  
- ZoningSystem.cpp:    Sistema de zonas (residencial/comercial/industrial)
- BuildingSystem.cpp:  Sistema de construção/demolição
- Tilemap.cpp:         Renderização eficiente de tilemaps
- Tileset.cpp:         Gerenciamento de tilesets
- OverlaySystem.cpp:   Overlays visuais (energia/água/poluição)
- AlertSystem.cpp:     Sistema de alertas com ícones
- Effects.cpp:         Partículas e efeitos visuais
- GarbagePollutionSystem.cpp: Coleta de lixo e poluição

## O QUE ESTÁ REALMENTE FUNCIONANDO

✅ FUNCIONANDO:
- Logger.cpp:          Sistema de logging completo
- Config.cpp:          Configurações JSON
- Application.cpp:     Game loop e gerenciamento de janela
- Game.cpp:            Estado do jogo + debug shape giratório
- InputManager.cpp:    Sistema de input completo
- SaveSystem.cpp:      Serialização ECS → JSON
- Window.cpp:          Janela SFML
- Renderer.cpp:        Renderização básica
- Camera.cpp:          Câmera e viewport
