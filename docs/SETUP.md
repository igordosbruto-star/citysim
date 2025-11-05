# Configuração do Ambiente CitySimulator

## Pré-requisitos
- **CMake**: 3.25+
- **Compilador**: C++20 (MSVC, GCC, Clang)
- **Git**: Para versionamento
- **vcpkg**: Gerenciador de dependências

## Configuração com vcpkg

### 1. Instalação do vcpkg
```bash
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh  # Linux/macOS
.\bootstrap-vcpkg.bat # Windows
```

### 2. Instalação de Dependências
```bash
vcpkg install sfml nlohmann-json lua sol2 entt glew wxwidgets gtest
```

### 3. Configuração do Projeto
```bash
# Clone o repositório
git clone https://github.com/seu-usuario/city-simulator.git
cd city-simulator

# Configure com vcpkg
cmake -B build -DCMAKE_TOOLCHAIN_FILE=[caminho-para-vcpkg]/scripts/buildsystems/vcpkg.cmake

# Compile
cmake --build build --config Release

# Execute
./build/bin/Release/city-simulator  # Linux/macOS
.\build\bin\Release\city-simulator.exe  # Windows
```

## Estrutura de Build

`city-simulator`: Jogo principal
`city-editor`: Editor integrado (wxWidgets)
`city-tests`: Testes unitários
`city-editor-tests`: Testes do editor

Opções de CMake

`BUILD_EDITOR=ON/OFF` - Construir o editor
`BUILD_TESTS=ON/OFF` - Construir testes
`COPY_ASSETS=ON/OFF` - Copiar assets automaticamente

