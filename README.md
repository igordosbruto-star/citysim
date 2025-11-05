# City Simulator 🏙️

**Construa do zero. Evolua com sabedoria.**

[![C++](https://img.shields.io/badge/C++-20-blue.svg)](https://isocpp.org/)
[![SFML](https://img.shields.io/badge/SFML-3.0-green.svg)](https://www.sfml-dev.org/)
[![CMake](https://img.shields.io/badge/CMake-3.25+-brightgreen.svg)](https://cmake.org/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

Um jogo de simulação urbana 2D em pixel art top-down com sistema de tech-tree progressiva **e editor integrado**.

## 🎮 Sobre o Jogo
- **Estilo**: Pixel art top-down (RPG Maker)
- **Foco**: Gestão estratégica com sistema de tecnologia
- **Progressão**: Tech-tree com ramificações exclusivas
- **Editor**: Ferramentas completas de criação e modding
- **Plataforma**: Windows, Linux, macOS

## 🚀 Começando
```bash
# Clone o repositório
git clone https://github.com/seu-usuario/city-simulator.git

# Configure e compile
cmake -B build -DCMAKE_TOOLCHAIN_FILE=[vcpkg]/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release

# Execute o jogo
./build/bin/Release/city-simulator

# Ou o editor
./build/bin/Release/city-editor
```

## 📚 Documentação
`Visão do Projeto` - (VISION.md) - Diretrizes de design e escopo
`Roadmap` - (ROADMAP.md) - Marcos de desenvolvimento detalhados
`Guia de Contribuição` - (CONTRIBUTING.md) - Como contribuir
`Configuração` - (SETUP.md) - Guia de instalação completo

## 🛠️ Tecnologias
`C++20` - Linguagem principal
`SFML 3` - Gráficos, áudio e input
`wxWidgets` - Interface do editor
`ECS (entt)` - Sistema de entidades e componentes
`JSON` - Configurações e save games
`Lua` - Scripting e mods