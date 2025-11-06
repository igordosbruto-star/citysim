cmake_minimum_required(VERSION 3.25)
project(CitySimulator VERSION 1.0.0 LANGUAGES CXX)

# ===== Build type padrão =====
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
endif()

# ===== Opções de configuração =====
option(BUILD_EDITOR "Build the CitySimulator editor" OFF)  # DESATIVADO por enquanto
option(BUILD_TESTS "Build tests" OFF)                      # DESATIVADO por enquanto
option(COPY_ASSETS "Copy assets to output directory" ON)

# ===== Configuração de compilação =====
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ===== Diretório de saída comum =====
set(OUT_DIR "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")

# ===== Fontes do CitySimulator (Jogo Principal) =====
set(CITY_SIMULATOR_SOURCES
    src/main.cpp
    src/Core/Application.cpp
    src/Utils/Logger.cpp
    src/Core/Game.cpp
    src/Core/Config.cpp
    src/Graphics/Window.cpp
    src/Graphics/Renderer.cpp
    src/Graphics/Camera.cpp
    src/Input/InputManager.cpp
    src/Input/Keyboard.cpp
    src/Input/Mouse.cpp

)

# Criar executável principal
add_executable(city-simulator ${CITY_SIMULATOR_SOURCES})
target_compile_features(city-simulator PRIVATE cxx_std_20)

# ===== Warnings e configurações do compilador =====
if(MSVC)
  target_compile_options(city-simulator PRIVATE /W4 /permissive- /EHsc)
  target_compile_definitions(city-simulator PRIVATE 
    _CRT_SECURE_NO_WARNINGS
    NOMINMAX
    WIN32_LEAN_AND_MEAN
  )
else()
  target_compile_options(city-simulator PRIVATE -Wall -Wextra -Wpedantic -Wshadow)
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(city-simulator PRIVATE -Wduplicated-cond -Wlogical-op)
  elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(city-simulator PRIVATE -Weverything -Wno-c++98-compat)
  endif()
endif()

# ===== Dependências =====

# SFML 3
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)
target_link_libraries(city-simulator PRIVATE
  SFML::Graphics SFML::Window SFML::System
)

# JSON (opcional)
find_package(nlohmann_json 3.11.2 QUIET)
if(nlohmann_json_FOUND)
    target_link_libraries(city-simulator PRIVATE nlohmann_json::nlohmann_json)
    target_compile_definitions(city-simulator PRIVATE HAS_JSON)
    message(STATUS "nlohmann_json encontrado")
else()
    message(STATUS "nlohmann_json não encontrado - recursos de JSON desativados")
endif()

# ===== Includes próprios =====
target_include_directories(city-simulator PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/include
)

# ===== Configuração de saída =====
set_target_properties(city-simulator PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${OUT_DIR}"
)

# ===== Configurações específicas para Windows =====
if(WIN32)
    # Encontrar e linkar com Windows libraries
    find_library(KERNEL32_LIBRARY kernel32)
    find_library(USER32_LIBRARY user32)
    find_library(GDI32_LIBRARY gdi32)
    find_library(OPENGL32_LIBRARY opengl32)
    
    if(KERNEL32_LIBRARY)
        target_link_libraries(city-simulator PRIVATE ${KERNEL32_LIBRARY})
    endif()
    if(USER32_LIBRARY)
        target_link_libraries(city-simulator PRIVATE ${USER32_LIBRARY})
    endif()
    if(GDI32_LIBRARY)
        target_link_libraries(city-simulator PRIVATE ${GDI32_LIBRARY})
    endif()
    if(OPENGL32_LIBRARY)
        target_link_libraries(city-simulator PRIVATE ${OPENGL32_LIBRARY})
    endif()
endif()

# ===== Cópia de recursos =====
if(COPY_ASSETS)
    # Assets do jogo
    set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")
    if(EXISTS "${ASSETS_DIR}")
        add_custom_command(TARGET city-simulator POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E echo "Copiando assets para ${OUT_DIR}/assets"
            COMMAND ${CMAKE_COMMAND} -E make_directory "${OUT_DIR}/assets"
            COMMAND ${CMAKE_COMMAND} -E copy_directory "${ASSETS_DIR}" "${OUT_DIR}/assets"
            COMMENT "Copiando assets do jogo"
            VERBATIM
        )
    else()
        message(STATUS "Diretório de assets não encontrado: ${ASSETS_DIR}")
    endif()

    # Configurações
    set(CONFIG_DIR "${CMAKE_SOURCE_DIR}/config")
    if(EXISTS "${CONFIG_DIR}")
        add_custom_command(TARGET city-simulator POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory "${OUT_DIR}/config"
            COMMAND ${CMAKE_COMMAND} -E copy_directory "${CONFIG_DIR}" "${OUT_DIR}/config"
            COMMENT "Copiando configurações"
            VERBATIM
        )
    endif()
endif()

# ===== Instalação =====
include(GNUInstallDirs)

install(TARGETS city-simulator
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    BUNDLE DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# ===== Mensagem final de configuração =====
message(STATUS "")
message(STATUS "=== CitySimulator Configuration Summary ===")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Output directory: ${OUT_DIR}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build editor: ${BUILD_EDITOR}")
message(STATUS "Build tests: ${BUILD_TESTS}")
message(STATUS "Copy assets: ${COPY_ASSETS}")
message(STATUS "")
message(STATUS "Dependencies:")
message(STATUS "  - SFML: ${SFML_VERSION}")
if(nlohmann_json_FOUND)
    message(STATUS "  - nlohmann_json: OK")
else()
    message(STATUS "  - nlohmann_json: Não encontrado")
endif()
message(STATUS "")
message(STATUS "Available targets:")
message(STATUS "  - city-simulator (main game)")
message(STATUS "")
message(STATUS "Configured successfully! 🏙️")
message(STATUS "Next: Run 'cmake --build build --config Release'")
message(STATUS "===========================================")