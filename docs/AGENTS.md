# AGENTS.md — Guia para agentes (Codex/assistentes)

> Este documento orienta agentes automáticos ao contribuir no repositório.  
> Fontes de verdade: `VISION.md`, `ROADMAP.md`, `CONTRIBUTING.md`, `CHANGELOG.md`.

## Objetivo
- Automatizar tarefas repetitivas sem quebrar padrões do projeto.
- Sempre priorizar o que está no **ROADMAP** e registrar mudanças no **CHANGELOG** (em `[Unreleased]`).

## Setup rápido
- Windows + MSVC 2022 com CMake ≥ 3.25 e vcpkg (manifest).
- Abra o repo no VS Code com CMake Tools. O manifest baixa dependências automaticamente no primeiro configure.

## Ambiente & Build
- **SO/Toolchain:** Windows, MSVC 2022, CMake ≥ 3.25, vcpkg (manifest).
- **Presets obrigatórios (CMakePresets.json):**
  - `configurePreset`: `msvc-vcpkg`
  - `buildPreset`: `msvc-Debug` (ou `msvc-Release` quando solicitado)
- **Executável principal:** `citysimulator`.

## Comandos padrão (CLI)
cmake --preset msvc-vcpkg
cmake --build build/msvc --config Debug

# binário resultante:
# build/msvc/bin/Debug/citysimulator.exe

## Execução no VS Code (F5)
- CMake: Select Configure Preset → msvc-vcpkg
- CMake: Select Build Preset → msvc-Debug
- Selecione o target citysimulator e pressione F5 (Debug).
- Não gerar build in-source (usar build/msvc dos presets).

## Escopo permitido (✅)
- Ajustes no runtime de exemplo citysimulator (inputs, desenho, logs).
- Leitura de TMX via tmxlite; impressão de dimensões/camadas.
- Infra de build (CMake, presets), .vscode/*, docs (VISION/ROADMAP/CHANGELOG/CONTRIBUTING).
- Refactors pequenos e correções de warnings.

## Fora de escopo (❌) — pedir issue/aprovação antes
- Provas de conceito mínimas.
- Trocar dependências do vcpkg.json ou versões do SFML/Lua/tmxlite.
- Quebrar formatos de dados (JSON/TMX) ou APIs “públicas” do projeto.


## Branch/Commits/PRs
- Branches: agent/<tipo>/<slug-curto>
ex.: agent/feat/wasd-movement

- Commits: Conventional Commits
ex.: feat(runtime): mover com WASD no citysimulator

- PRs:
 - Título claro; descrição curta com o “porquê”.
 - Linkar issue/roadmap quando existir (closes #123).
 - Atualizar CHANGELOG ([Unreleased]).
 - Labels: enhancement/bug/docs + area/runtime (ou area/build, area/docs, area/editor) + roadmap quando aplicável.

## Padrões de Código
- C++20; avisos altos (/W4 MSVC).
- Respeitar .clang-format (se existir); preferir funções curtas e .cpp separados.
- SFML 3.x: componentes SFML::Graphics, SFML::Window, SFML::Audio, SFML::System.
- Não commitar artefatos: build/, bin/, vcpkg_installed/, etc. (ver .gitignore).

## Testes mínimos (por PR)
- Build Debug sem erros.
- Executar citysimulator (abrir janela) sem crash.
- Se tocar TMX: log “TMX carregado” + dimensões/camadas corretas.


## Tarefas comuns (prioridade sugerida)
- feat/runtime: mover com WASD no citysimulator.
- feat/runtime: carregar examples/citysimulator/firsttileset.tmx e imprimir dimensões/camadas.
- chore/docs: manter CHANGELOG.md e ROADMAP.md atualizados.
- refactor/build: pequenos ajustes de CMake/presets sem mudar comportamento.

## Estrutura útil (referência)
- src/ código-fonte | include/ headers
- examples/citysimulator/ assets e TMX de exemplo
- build/msvc/ saída de build (presets)
- docs/ documentação do projeto

## Segurança e Segredos
- **Nunca** commitar chaves/segredos.
- **Não** alterar publicação/CI sem aprovação explícita.

## Fontes de Verdade
- **CONTRIBUTING.md** — fluxos e padrões gerais.
- **ROADMAP.md** — prioridades e milestones.
- **VISION.md** — direção de produto.
- **CHANGELOG.md** — histórico de mudanças.

