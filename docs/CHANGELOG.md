# CHANGELOG — City Simulator

Todas as mudanças relevantes deste projeto serão documentadas aqui.
Segue SemVer: MAJOR.MINOR.PATCH (ex.: 0.2.1).

## [Unreleased]
### Added
- Estrutura inicial da documentação do projeto.
- Sistema de build com CMake para jogo e editor
- Configuração completa do editor (wxWidgets + OpenGL)
- Arquivos base e headers da aplicação. `Application.cpp`, `Game.cpp`, `Config.cpp`
- Sistema de logging com Logger.cpp/hpp
- Implementação do loop principal da aplicação
- Subsistemas dedicados de janela, renderização e câmera sob `include/Graphics/` e `src/Graphics/`
- Sistema de entrada com `InputManager`, `Keyboard` e `Mouse` encapsulando eventos do SFML
- Renderização básica com formas geométricas
- Scripts de configuração de ambiente (`scripts/setup_environment.sh` e `.bat`) com instalação mínima via vcpkg
- Arquivo `docs/CONTRIBUTING.md` alinhado ao guia raiz de contribuição
- Diretórios `assets/`, `third_party/` e `build/` versionados com placeholders para facilitar estrutura de projeto
- Sistema ECS (Entity Component System) inicial
  - Classe base Entity encapsulando funcionalidade entt
  - Classes base de Component e componentes iniciais (Transform, Tag, Renderable)
  - Classe base System com gerenciamento via World
  - Implementações iniciais de RenderSystem e TransformSystem
  - Testes unitários abrangentes para funcionalidade core do ECS
- Sistema de zoneamento e construção:
  - ZoningSystem com suporte a zonas residenciais, comerciais e industriais
  - BuildingSystem para gerenciamento de construções e demolições
  - Testes unitários para construção e demolição
- UI básica para construção:
  - Botões de seleção de ferramentas com feedback visual
  - Sombras, seleção e partículas leves para feedback ao usuário
  - Sistema de efeitos visuais com partículas e animações
- Sistema de salvamento e carregamento:
  - SaveSystem usando nlohmann-json para persistência
  - Suporte para salvar/carregar zonas e construções
  - Testes de persistência de dados
- Ferramentas do editor:
  - Pincel, borracha e preenchimento para edição de tiles
  - Painel de propriedades com edição de tiles e zonas
  - Separação clara entre editor e motor do jogo

### Changed
- Atualizado padrão para C++20 em toda a codebase
- Integrado editor em todos os marcos do roadmap
- Ajustado build para localizar SFML 2.5+ (mantendo compatibilidade futura com SFML 3)
- Correção do sistema de criação de janela e loop de eventos para suportar tanto SFML 2.5 quanto SFML 3
- Atualização do sistema de eventos para usar uma camada de compatibilidade baseada em `std::optional`
 - CMake: relaxado requisito de versão do SFML e correção de componentes (aceita SFML 3 via vcpkg)
 - Compatibilidade SFML 3: adaptados `VideoMode`, `Transformable::setRotation`, `Window::create` e eventos de teclado
	 - Arquivos modificados: `CMakeLists.txt`, `src/Core/Application.cpp`, `src/Core/Game.cpp`, `src/Graphics/Window.cpp`, `src/Input/Keyboard.cpp`

 - Normalizado o namespace top-level de `CitySimulator` para `CitySim` em múltiplos headers e fontes C++ (ex.: `include/Core/Components/*`, `include/Core/Systems/*`, `src/Systems/*`, `include/Graphics/*`, `src/Graphics/*`, `src/ECS/*`).
 - Corrigidos conflitos entre declarações e implementações de namespace em `OverlaySystem` e `AlertSystem` (header/CPP alinhados).
 - Atualizados testes para usar `using namespace CitySim;` e corrigido estilo de includes para headers do projeto (angulares -> aspas) em `tests/*` para melhorar resolução de includes durante build.

### Fixed
- Erros de compilação com VideoMode no SFML 3
- Problemas com métodos setPosition e setRotation
- Erro C2171 com método create() da janela
- Sistema de handling de eventos com nova API SFML 3
- Warning C4127 em loop condicional
- Compatibilidade de build restaurada no ambiente container padrão (SFML 2.5)
 - Resolução do erro de configuração CMake causado pela incompatibilidade de versão do SFML (2.5 vs 3.x)
 - Corrigidos erros de compilação introduzidos por mudança de API entre SFML 2 -> 3 (nomes de campos de eventos, overloads e headers)
- Correções no sistema ECS:
  - Resolvido problema de duplicação de membros na classe World
  - Corrigido acesso aos métodos FindEntityByName, Clear e GetSystem (movidos para público)
  - Atualizado RenderSystem para compatibilidade com SFML 3.x (usando RenderTarget*)
  - Corrigido estilo de janela para testes (Style::Hidden -> Style::None)
  - Atualizado namespace do Logger para CitySim
  - Adicionados arquivos necessários ao build dos testes (Logger.cpp)
 - Corrigidos erros de compilação causados por inconsistências de namespace (`CitySimulator` vs `CitySim`) e comentários de fechamento de namespace incorretos em diversos arquivos (ex.: `src/ECS/Entity.cpp`, `src/ECS/World.cpp`, `include/Core/Components/*`, `include/Graphics/*`).
 - Ajustes de includes e visibilidade em testes que impediam compilação consistente em builds locais (Debug/Release).
 - Tilemap and rendering fixes:
   - Reworked `Tilemap` to use `sf::PrimitiveType::Triangles` (SFML 3 dropped `Quads`).
   - Updated texture coordinate handling to use `sf::Rect` position/size members.
   - Fixed vertex layout (6 vertices per tile) and texture mapping.
 - Logger shutdown deadlock fixed:
   - `Logger::shutdown()` no longer calls `log()` while holding the internal mutex to avoid resource deadlocks during teardown.
 - Tests updated for SFML 3 API:
   - Updated `tests/test_tilemap.cpp` and `tests/test_tilemap_advanced.cpp` to use `sf::IntRect({pos},{size})` and avoid negative index usage.

### Milestones
- [x] Marco 1 — Fundação Técnica (Engine e Estrutura Base) completo:
  - Base técnica funcional com C++ e SFML 3
  - Sistema de build com CMake e vcpkg
  - Estrutura ECS implementada e testada
  - Sistema de eventos e input funcionando
  - Renderização base com formas e tilemap
  - Editor com estrutura inicial

### Docs
- `VISION.md` - Documento de visão completo com editor integrado
- `ROADMAP.md` - Roadmap detalhado com 11 marcos + desenvolvimento paralelo
- `README.md` - Descrição básica e referências gerais
- `AGENTS.md` - Guidelines para assistentes de IA no projeto
- `CHANGELOG.md` - Este arquivo de histórico de mudanças
 - `.github/copilot-instructions.md` - Guia conciso para assistentes de IA (adicionado)


[0.1.0] - 2024-XX-XX
Added
- Base funcional do motor gráfico com SFML 3
- Sistema de aplicação singleton gerenciável
- Controle de FPS e delta time
- Sistema de eventos básico (teclado, mouse, janela)
- Renderização de teste com shape rotativo
- Configurações de janela e performance