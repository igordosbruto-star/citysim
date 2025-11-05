# 📘 Plano de Implementação - Marco 1: Fundação Técnica

## 🔍 Visão Geral
Este plano detalha a implementação sequencial do **Marco 1**, organizado por fases de desenvolvimento e arquivos específicos a serem criados.

---

## 🧩 FASE 1: Configuração do Ambiente e Estrutura Base

### 1.1 Configuração do Projeto
**Arquivos a criar:**
```
CMakeLists.txt                    # Configuração principal do CMake
README.md                         # Documentação inicial do projeto
.gitignore                        # Arquivos ignorados pelo Git
docs/CONTRIBUTING.md              # Guia de contribuição
scripts/setup_environment.sh      # Script de setup do ambiente (Linux/Mac)
scripts/setup_environment.bat     # Script de setup do ambiente (Windows)
```

### 1.2 Estrutura de Diretórios
**Criar diretórios:**
```
src/
include/
third_party/
assets/
build/
tests/
docs/
```

---

## ⚙️ FASE 2: Motor do Jogo - Núcleo

### 2.1 Sistema de Gerenciamento Principal
```
include/Core/Application.hpp      # Classe principal da aplicação
src/Core/Application.cpp
include/Core/Game.hpp             # Gerenciador principal do jogo
src/Core/Game.cpp
include/Core/Config.hpp           # Configurações globais
src/Core/Config.cpp
```

### 2.2 Sistema de Janela e Renderização
```
include/Graphics/Window.hpp       # Gerenciador de janela SFML
src/Graphics/Window.cpp
include/Graphics/Renderer.hpp     # Sistema de renderização
src/Graphics/Renderer.cpp
include/Graphics/Camera.hpp       # Controle de câmera
src/Graphics/Camera.cpp
```

### 2.3 Sistema de Entrada
```
include/Input/InputManager.hpp    # Gerenciador de input
src/Input/InputManager.cpp
include/Input/Keyboard.hpp        # Controles de teclado
src/Input/Keyboard.cpp
include/Input/Mouse.hpp           # Controles de mouse
src/Input/Mouse.cpp
```

---

## 🧱 FASE 3: Entity Component System (ECS)

### 3.1 Núcleo do ECS
```
include/ECS/Entity.hpp            # Entidade base
src/ECS/Entity.cpp
include/ECS/Component.hpp         # Componente base
src/ECS/Component.cpp
include/ECS/System.hpp            # Sistema base
src/ECS/System.cpp
include/ECS/World.hpp             # Mundo/Registry do ECS
src/ECS/World.cpp
```

### 3.2 Componentes Básicos
```
include/ECS/Components/Transform.hpp      # Posição, rotação, escala
src/ECS/Components/Transform.cpp
include/ECS/Components/Renderable.hpp     # Componente de renderização
src/ECS/Components/Renderable.cpp
include/ECS/Components/Tag.hpp            # Identificação de entidades
src/ECS/Components/Tag.cpp
```

### 3.3 Sistemas Básicos
```
include/ECS/Systems/RenderSystem.hpp      # Sistema de renderização
src/ECS/Systems/RenderSystem.cpp
include/ECS/Systems/TransformSystem.hpp   # Sistema de transformação
src/ECS/Systems/TransformSystem.cpp
```

---

## 🗺️ FASE 4: Sistema de Tilemap

### 4.1 Tilemap Base
```
include/Graphics/Tile.hpp                 # Tile individual
src/Graphics/Tile.cpp
include/Graphics/Tilemap.hpp              # Mapa de tiles
src/Graphics/Tilemap.cpp
include/Graphics/Tileset.hpp              # Conjunto de tiles
src/Graphics/Tileset.cpp
```

### 4.2 Carregamento de Assets
```
include/Resources/ResourceManager.hpp     # Gerenciador de recursos
src/Resources/ResourceManager.cpp
include/Resources/TextureManager.hpp      # Gerenciador de texturas
src/Resources/TextureManager.cpp
```

---

## 🎮 FASE 5: Loop Principal e Prova de Conceito

### 5.1 Loop de Jogo
```
include/Core/GameLoop.hpp                 # Loop principal do jogo
src/Core/GameLoop.cpp
include/Core/Time.hpp                     # Gerenciamento de tempo
src/Core/Time.cpp
```

### 5.2 Main e Inicialização
```
src/main.cpp                              # Ponto de entrada do jogo
include/Core/Engine.hpp                   # Motor principal
src/Core/Engine.cpp
```

---

## 🧰 FASE 6: Editor - Estrutura Base

### 6.1 Aplicação do Editor
```
editor/include/EditorApp.hpp              # Aplicação principal do editor
editor/src/EditorApp.cpp
editor/include/MainFrame.hpp              # Frame principal
editor/src/MainFrame.cpp
editor/src/main.cpp                       # Ponto de entrada do editor
```

### 6.2 Painéis do Editor
```
editor/include/Panels/ViewportPanel.hpp   # Painel de visualização
editor/src/Panels/ViewportPanel.cpp
editor/include/Panels/ToolsPanel.hpp      # Painel de ferramentas
editor/src/Panels/ToolsPanel.cpp
editor/include/Panels/PropertiesPanel.hpp # Painel de propriedades
editor/src/Panels/PropertiesPanel.cpp
```

### 6.3 Sistema de Renderização do Editor
```
editor/include/Graphics/EditorRenderer.hpp # Renderizador OpenGL do editor
editor/src/Graphics/EditorRenderer.cpp
editor/include/Graphics/GLCanvas.hpp       # Canvas OpenGL
editor/src/Graphics/GLCanvas.cpp
```

---

## 🔗 FASE 7: Comunicação Editor-Motor

### 7.1 Interface de Comunicação
```
include/Core/GameInterface.hpp            # Interface para comunicação externa
src/Core/GameInterface.cpp
editor/include/EngineBridge.hpp           # Ponte entre editor e motor
editor/src/EngineBridge.cpp
```

### 7.2 Sistema de Mensagens
```
include/Utils/MessageBus.hpp              # Barramento de mensagens
src/Utils/MessageBus.cpp
```

---

## 🧮 FASE 8: Utilitários e Debug

### 8.1 Utilitários
```
include/Utils/Logger.hpp                  # Sistema de logging
src/Utils/Logger.cpp
include/Utils/Profiler.hpp                # Profiling de performance
src/Utils/Profiler.cpp
include/Utils/Math.hpp                    # Funções matemáticas utilitárias
src/Utils/Math.cpp
```

### 8.2 Debug e Desenvolvimento
```
include/Debug/DebugTools.hpp              # Ferramentas de debug
src/Debug/DebugTools.cpp
include/Debug/Console.hpp                 # Console de debug
src/Debug/Console.cpp
```

---

## 🧪 FASE 9: Testes e Validação

### 9.1 Testes Unitários
```
tests/test_ecs.cpp                        # Testes do sistema ECS
tests/test_tilemap.cpp                    # Testes do tilemap
tests/test_rendering.cpp                  # Testes de renderização
tests/test_editor.cpp                     # Testes do editor
```

### 9.2 Scripts de Build
```
scripts/build_game.sh                     # Script de build do jogo
scripts/build_editor.sh                   # Script de build do editor
scripts/run_tests.sh                      # Script de execução de testes
```

---

## 🗓️ Ordem de Implementação Recomendada

| Período | Fases |
|----------|--------|
| **Dia 1-2** | Fase 1 (Configuração) + Fase 2.1-2.2 |
| **Dia 3-4** | Fase 3 (ECS) + Fase 2.3 |
| **Dia 5-6** | Fase 4 (Tilemap) + Fase 5 |
| **Dia 7-8** | Fase 6.1-6.2 (Editor base) |
| **Dia 9-10** | Fase 6.3 + Fase 7 (Comunicação) |
| **Dia 11-12** | Fase 8 (Utilitários) + Fase 9 (Testes) |

---

## ✅ Critérios de Validação por Fase

### Fase 2–5 (Motor)
- ✅ Projeto compila sem erros  
- ✅ Janela SFML abre e fecha corretamente  
- ✅ Tilemap básico renderiza a 60 FPS  
- ✅ Câmera se move com teclado/mouse  
- ✅ ECS cria e atualiza entidades  

### Fase 6–7 (Editor)
- ✅ Editor compila e abre janela  
- ✅ Painéis básicos são exibidos  
- ✅ Comunicação editor-motor funciona  
- ✅ Viewport renderiza cena do jogo  

### Fase 8–9 (Final)
- ✅ Build estável e versionada  
- ✅ Testes unitários passam  
- ✅ Performance: 60 FPS constante  
- ✅ Sem crashes em 10 min de uso  

---

> 💡 Este plano garante uma implementação **estruturada e incremental** do Marco 1, seguindo as **boas práticas de desenvolvimento de software**.
