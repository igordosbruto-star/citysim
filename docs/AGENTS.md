# AGENTS.md — City Simulator

Diretrizes para assistentes de IA trabalharem no projeto City Simulator.

## 🎯 Objetivo
Este documento estabelece padrões e diretrizes para assistentes de IA contribuírem consistentemente no desenvolvimento do City Simulator, garantindo alinhamento com a visão do projeto e qualidade de código.

## 📚 Fontes de Verdade
- **`VISION.md`** - Diretrizes de design, escopo e filosofia do jogo
- **`ROADMAP.md`** - Marcos de desenvolvimento e prioridades
- **`CONTRIBUTING.md`** - Processos de contribuição e padrões
- **`CHANGELOG.md`** - Histórico de mudanças e versionamento

## 🏗️ Estrutura Útil (Referência)

### Arquitetura do Projeto
```
src/
├── core/ # Núcleo do motor (ECS, sistemas base)
├── rendering/ # Renderização SFML (tilemaps, sprites)
├── simulation/ # Sistemas de simulação (cidadãos, economia)
├── tech_tree/ # Sistema de tecnologia e pesquisa
├── ui/ # Interface do usuário
└── utils/ # Utilitários (JSON, math, helpers)
```

### Entidades Principais (ECS)
- `CityComponent` - Dados da cidade
- `CitizenComponent` - Cidadãos com necessidades e rotinas
- `BuildingComponent` - Edifícios e zonas
- `VehicleComponent` - Veículos em tráfego
- `TechnologyComponent` - Tecnologias da tech-tree

## 💻 Padrões de Código

### C++20 com SFML

// ✅ CORRETO - Estilo preferido
```cpp
class CitySimulator {
public:
    void updateSimulation(float deltaTime);
    bool canBuildAt(const sf::Vector2i& position) const;
    
private:
    std::unique_ptr<TechTreeSystem> m_techTree;
    std::vector<Citizen> m_citizens;
};
```

// ❌ EVITAR - Estilo antigo
```cpp
class old_style {
    public:
    void UpdateSimulation(float DeltaTime);
};
```

### Convenções de Nomenclatura
```
Classes: PascalCase → TechTreeSystem, CitizenManager
Funções: camelCase → calculateHappiness(), updatePopulation()
Variáveis: camelCase → currentPopulation, researchPoints
Constantes: UPPER_CASE → MAX_VEHICLES, TILE_SIZE
```

### Diretrizes ECS

// Componentes devem ser dados puros
```cpp
struct CitizenComponent {
    sf::Vector2f homePosition;
    sf::Vector2f workPosition;
    float happiness = 0.0f;
    CitizenState state = CitizenState::Idle;
};
```

// Sistemas processam lógica
```cpp
class CitizenSystem : public System {
public:
    void update(float deltaTime) override;
    void updateCitizenPaths();
};
```

## 🧪 Testes Mínimos (por PR)

### Testes Obrigatórios
Cada PR deve garantir:

**1- Compilação Limpa**
```bash
cmake --build build --config Debug
cmake --build build --config Release
```

**2- Performance Básica**
- 60 FPS em cena vazia
- 45 FPS com 1k entidades
- Memória estável após 5 minutos

**Funcionalidade Core**

- Tech-tree: desbloqueio e pré-requisitos funcionando
- ECS: entidades sendo atualizadas corretamente
- Save/Load: dados persistindo sem corrupção

**Exemplo de Teste Unitário**
```cpp
TEST_CASE("TechTree Unlock Validation") 
{
    TechTreeSystem techTree;
    techTree.unlockTechnology("basic_roads");
    
    REQUIRE(techTree.isUnlocked("basic_roads") == true);
    REQUIRE(techTree.canUnlock("advanced_roads") == false); // precisa de pré-requisitos
}
```

### 🛠️ Comandos Padrão (CLI)

## Desenvolvimento
```bash
# Configuração inicial
cmake -B build -DCMAKE_TOOLCHAIN_FILE=[vcpkg_root]/scripts/buildsystems/vcpkg.cmake

# Build e execução
cmake --build build --config Debug
./build/CitySimulator

# Build de release
cmake --build build --config Release
```

## Testes e Qualidade
```bash
# Rodar testes unitários
cd build && ctest --output-on-failure

# Verificar vazamentos de memória (Linux)
valgrind --leak-check=full ./CitySimulator

# Análise estática (opcional)
cppcheck --enable=all src/
```

## Utilitários
```bash
# Gerar documentação (quando implementado)
doxygen Doxyfile

# Formatação de código (quando configurado)
clang-format -i src/**/*.cpp include/**/*.hpp
```

### 📋 Checklist para Agentes

## Antes de Implementar

- Consultar ROADMAP.md para alinhamento com marcos
- Verificar VISION.md para consistência de design
- Analisar dependências no CONTRIBUTING.md

## Durante Desenvolvimento

- Seguir padrões de código C++20/SFML
- Manter performance (60 FPS target)
- Implementar testes mínimos
- Documentar mudanças significativas

## Antes de Finalizar
- Atualizar CHANGELOG.md se necessário
- Verificar compatibilidade com sistemas existentes
- Executar comandos de teste padrão

### 🚨 Notas Importantes

## Prioridades do Projeto

- Tech-tree funcional - núcleo da jogabilidade
- Performance estável - 60 FPS é meta
- Simulação realista - cidadãos com comportamentos significativos
- Pixel art consistente - estilo RPG Maker top-down

## Restrições Técnicas
- SFML para gráficos/áudio/input
- ECS para gerenciamento de entidades
- JSON para dados de configuração
- C++20 como versão mínima

## Padrões de Qualidade
- Código deve ser auto-documentado
- Evitar otimizações prematuras
- Manter compatibilidade com save games
- Seguir princípios SOLID quando aplicável

---

Última atualização: 04-11-2025
Manter sincronizado com: VISION.md, ROADMAP.md, CONTRIBUTING.md

---