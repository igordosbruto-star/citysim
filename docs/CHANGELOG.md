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

### Changed
- Atualizado padrão para C++20 em toda a codebase
- Integrado editor em todos os marcos do roadmap
- Ajustado build para localizar SFML 2.5+ (mantendo compatibilidade futura com SFML 3)
- Correção do sistema de criação de janela e loop de eventos para suportar tanto SFML 2.5 quanto SFML 3
- Atualização do sistema de eventos para usar uma camada de compatibilidade baseada em `std::optional`

### Fixed
- Erros de compilação com VideoMode no SFML 3
- Problemas com métodos setPosition e setRotation
- Erro C2171 com método create() da janela
- Sistema de handling de eventos com nova API SFML 3
- Warning C4127 em loop condicional
- Compatibilidade de build restaurada no ambiente container padrão (SFML 2.5)

### Docs
- `VISION.md` - Documento de visão completo com editor integrado
- `ROADMAP.md` - Roadmap detalhado com 11 marcos + desenvolvimento paralelo
- `README.md` - Descrição básica e referências gerais
- `AGENTS.md` - Guidelines para assistentes de IA no projeto
- `CHANGELOG.md` - Este arquivo de histórico de mudanças


[0.1.0] - 2024-XX-XX
Added
- Base funcional do motor gráfico com SFML 3
- Sistema de aplicação singleton gerenciável
- Controle de FPS e delta time
- Sistema de eventos básico (teclado, mouse, janela)
- Renderização de teste com shape rotativo
- Configurações de janela e performance