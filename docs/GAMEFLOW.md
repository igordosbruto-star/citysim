[file name]: GAMEFLOW.md
[file content begin]
# City Simulator - Fluxo de Execução

## FLUXO PRINCIPAL

main.cpp:              main()
    ↓
Logger.cpp:            Logger.initialize("city_simulator.log")
    ↓  
Config.cpp:            Config.load()                            ← "Usando configuração padrão" 
    ↓
Application.cpp:       Application.initialize()                 ← "Application inicializada"
    ↓
Game.cpp:              Game.initialize()                        ← "Game inicializado"
    ↓  
Application.cpp:       Application.run(game)                    ← LOOP PRINCIPAL
    │   ├→ Application.cpp: handleEvents()                      ← Eventos SFML
    │   ├→ Application.cpp: update() → Game.cpp: update()       ← Lógica do jogo
    │   └→ Application.cpp: render() → Game.cpp: render()       ← Renderização
    ↓
Game.cpp:              Game.shutdown()                          ← "Encerrando Game..."
    ↓
Application.cpp:       Application.shutdown()                   ← "Application encerrada"
    ↓
Logger.cpp:            Logger.shutdown()                        ← "Shutting down logger..."

## SISTEMA DE SAVE/LOAD

SaveSystem.cpp:        SaveSystem.saveMap()
    ↓
                       Serializa: ZoneComponent + BuildingComponent + GridComponent
    ↓  
                       Salva como JSON → Arquivo (versão 1.0)

SaveSystem.cpp:        SaveSystem.loadMap()  
    ↓
                       Desserializa: JSON → ECS Entities
    ↓
                       Restaura estado do mapa

## ESTADOS DO JOGO

Game.cpp:              Game State:
                       Uninitialized → Running → Paused (tecla P) → Running

## COMPONENTES PRINCIPAIS

ECS Components:
ZoneComponent.hpp:     ZoneComponent           ← Tipo, nível, felicidade
BuildingComponent.hpp: BuildingComponent       ← Demolível, saúde  
GridComponent.hpp:     GridComponent           ← Posição (x, y)

## LOGGING

Logger.cpp:            Logger:
                       Console (cores) + Arquivo "city_simulator.log"
                       Níveis: TRACE, DEBUG, INFO, WARNING, ERROR, FATAL
                       Thread-safe com std::mutex
[file content end]