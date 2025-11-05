cmake_minimum_required(VERSION 3.25)
project(CitySimulator VERSION 1.0.0 LANGUAGES CXX)

# ===== Build type padrão =====
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
endif()

# ===== Opções de configuração =====
option(BUILD_EDITOR "Build the CitySimulator editor" ON)
option(BUILD_TESTS "Build tests" ON)
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
    src/game.cpp
    src/game_state.cpp
    src/game_state_manager.cpp
    src/city_map.cpp
    src/building.cpp
    src/road_network.cpp
    src/citizen.cpp
    src/vehicle.cpp
    src/economy_system.cpp
    src/time_system.cpp
    src/weather_system.cpp
    src/camera.cpp
    src/input_handler.cpp
    src/config_manager.cpp
    src/resource_manager.cpp
    
    # Sistemas Core (ECS)
    src/core/entity_manager.cpp
    src/core/system_manager.cpp
    src/core/component_pool.cpp
    
    # Tech Tree System
    src/tech_tree/tech_tree_system.cpp
    src/tech_tree/technology.cpp
    src/tech_tree/research_manager.cpp
    
    # Renderização
    src/rendering/tilemap_renderer.cpp
    src/rendering/sprite_renderer.cpp
    src/rendering/ui_renderer.cpp
    src/rendering/lighting_system.cpp
    
    # Simulação
    src/simulation/citizen_system.cpp
    src/simulation/traffic_system.cpp
    src/simulation/economy_simulator.cpp
    src/simulation/pathfinding_system.cpp
    
    # UI
    src/ui/main_menu.cpp
    src/ui/hud.cpp
    src/ui/tech_tree_ui.cpp
    src/ui/toolbar.cpp
    
    # Utilitários
    src/utils/json_loader.cpp
    src/utils/math_utils.cpp
    src/utils/random.cpp
)

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
  endif()
endif()

# ===== Dependências via vcpkg =====
# Configure com: 
# -DCMAKE_TOOLCHAIN_FILE="C:/Users/fanta/vcpkg/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows

# SFML 3
find_package(SFML CONFIG REQUIRED COMPONENTS Graphics Window Audio System)
target_link_libraries(city-simulator PRIVATE
  SFML::Graphics SFML::Window SFML::Audio SFML::System
)

# JSON para configurações e save games
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(city-simulator PRIVATE nlohmann_json::nlohmann_json)

# Lua para scripting e mods
find_package(Lua REQUIRED)
target_include_directories(city-simulator PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(city-simulator PRIVATE ${LUA_LIBRARIES})

# sol2 para binding C++/Lua
find_package(sol2 CONFIG REQUIRED)
target_link_libraries(city-simulator PRIVATE sol2::sol2)

# entt (ECS) - header only
find_package(entt CONFIG REQUIRED)
target_link_libraries(city-simulator PRIVATE entt::entt)

# ===== Includes próprios =====
target_include_directories(city-simulator PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/include
)

# ===== Configuração de saída =====
set_target_properties(city-simulator PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${OUT_DIR}"
  ARCHIVE_OUTPUT_DIRECTORY "${OUT_DIR}"
  LIBRARY_OUTPUT_DIRECTORY "${OUT_DIR}"
)

# ===== Editor CitySimulator (wxWidgets) =====
if(BUILD_EDITOR)
  set(CITY_EDITOR_SOURCES
      editor/main.cpp
      editor/editor_app.cpp
      editor/main_frame.cpp
      editor/city_viewport.cpp
      editor/tool_panel.cpp
      editor/property_panel.cpp
      editor/layer_panel.cpp
      editor/building_editor.cpp
      editor/road_editor.cpp
      editor/zone_editor.cpp
      editor/terrain_editor.cpp
      editor/city_loader.cpp
      editor/city_saver.cpp
      editor/config_dialog.cpp
      editor/resource_manager.cpp
      editor/camera_controller.cpp
      editor/grid_renderer.cpp
      editor/selection_tool.cpp
      editor/tech_tree_editor.cpp
      editor/map_export_dialog.cpp
  )

  # wxWidgets
  find_package(wxWidgets CONFIG REQUIRED COMPONENTS core base aui gl adv)
  if(NOT wxWidgets_FOUND)
    message(WARNING "wxWidgets not found, disabling editor build")
    set(BUILD_EDITOR OFF)
  else()
    # GLEW para OpenGL
    find_package(GLEW REQUIRED)

    add_executable(city-editor ${CITY_EDITOR_SOURCES})
    target_compile_features(city-editor PRIVATE cxx_std_20)

    # wxWidgets setup
    target_link_libraries(city-editor PRIVATE
      wx::core wx::base wx::aui wx::gl wx::adv
      nlohmann_json::nlohmann_json
      GLEW::GLEW
      opengl32
    )

    # Definir flags específicas do wxWidgets para Windows
    if(WIN32)
      target_compile_definitions(city-editor PRIVATE
        WXUSINGDLL
        wxMSVC_VERSION_AUTO
        _CRT_SECURE_NO_WARNINGS
        _WIN32_WINNT=0x0601
      )
      # Configurar como aplicação Windows (não console)
      set_target_properties(city-editor PROPERTIES
        WIN32_EXECUTABLE TRUE
      )
    endif()

    # Incluir diretórios do editor
    target_include_directories(city-editor PRIVATE
      ${CMAKE_SOURCE_DIR}/editor
      ${CMAKE_SOURCE_DIR}/include
    )

    # Warnings para o editor
    if(MSVC)
      target_compile_options(city-editor PRIVATE /W4 /permissive- /EHsc /utf-8)
    else()
      target_compile_options(city-editor PRIVATE -Wall -Wextra -Wpedantic)
    endif()

    # Configuração de saída do editor
    set_target_properties(city-editor PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "${OUT_DIR}"
      ARCHIVE_OUTPUT_DIRECTORY "${OUT_DIR}"
      LIBRARY_OUTPUT_DIRECTORY "${OUT_DIR}"
    )
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
      COMMENT "Copying game assets"
      VERBATIM
    )
    
    if(BUILD_EDITOR)
      add_custom_command(TARGET city-editor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copiando assets para ${OUT_DIR}/assets"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${OUT_DIR}/assets"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${ASSETS_DIR}" "${OUT_DIR}/assets"
        COMMENT "Copying game assets for editor"
        VERBATIM
      )
    endif()
  endif()

  # Shaders para o editor
  set(SHADERS_DIR "${CMAKE_SOURCE_DIR}/shaders")
  if(EXISTS "${SHADERS_DIR}" AND BUILD_EDITOR)
    add_custom_command(TARGET city-editor POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E echo "Copiando shaders para ${OUT_DIR}/shaders"
      COMMAND ${CMAKE_COMMAND} -E make_directory "${OUT_DIR}/shaders"
      COMMAND ${CMAKE_COMMAND} -E copy_directory "${SHADERS_DIR}" "${OUT_DIR}/shaders"
      COMMENT "Copying shaders"
      VERBATIM
    )
  endif()

  # Configurações
  set(CONFIG_DIR "${CMAKE_SOURCE_DIR}/config")
  if(EXISTS "${CONFIG_DIR}")
    add_custom_command(TARGET city-simulator POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E echo "Copiando configurações para ${OUT_DIR}/config"
      COMMAND ${CMAKE_COMMAND} -E make_directory "${OUT_DIR}/config"
      COMMAND ${CMAKE_COMMAND} -E copy_directory "${CONFIG_DIR}" "${OUT_DIR}/config"
      COMMENT "Copying configurations"
      VERBATIM
    )
    
    if(BUILD_EDITOR)
      add_custom_command(TARGET city-editor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copiando configurações para ${OUT_DIR}/config"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${OUT_DIR}/config"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CONFIG_DIR}" "${OUT_DIR}/config"
        COMMENT "Copying configurations for editor"
        VERBATIM
      )
    endif()
  endif()
endif()

# ===== Sistema de Testes =====
if(BUILD_TESTS)
  enable_testing()
  find_package(GTest CONFIG REQUIRED)
  
  if(GTest_FOUND)
    # Testes do simulador
    set(TEST_SOURCES
        tests/test_basic.cpp
        tests/test_city_map.cpp
        tests/test_economy.cpp
        tests/test_building.cpp
        tests/test_tech_tree.cpp
        tests/test_pathfinding.cpp
        
        # Fontes necessárias para os testes
        src/city_map.cpp
        src/building.cpp
        src/economy_system.cpp
        src/time_system.cpp
        src/config_manager.cpp
        src/resource_manager.cpp
        src/tech_tree/tech_tree_system.cpp
        src/tech_tree/technology.cpp
        src/simulation/pathfinding_system.cpp
        src/utils/json_loader.cpp
    )
    
    add_executable(city-tests ${TEST_SOURCES})
    target_compile_features(city-tests PRIVATE cxx_std_20)
    
    target_link_libraries(city-tests PRIVATE
      GTest::gtest_main
      SFML::System
      nlohmann_json::nlohmann_json
      sol2::sol2
      entt::entt
      ${LUA_LIBRARIES}
    )
    
    target_include_directories(city-tests PRIVATE
      ${CMAKE_SOURCE_DIR}/src
      ${CMAKE_SOURCE_DIR}/include
      ${LUA_INCLUDE_DIR}
    )
    
    set_target_properties(city-tests PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "${OUT_DIR}"
    )
    
    # Testes do editor (se o editor estiver sendo construído)
    if(BUILD_EDITOR)
      add_executable(city-editor-tests
        tests/editor/test_city_loader.cpp
        tests/editor/test_building_editor.cpp
        tests/editor/test_tech_tree_editor.cpp
        
        editor/city_loader.cpp
        editor/building_editor.cpp
        editor/tech_tree_editor.cpp
        editor/resource_manager.cpp
      )
      
      target_link_libraries(city-editor-tests PRIVATE
        GTest::gtest_main
        wx::core wx::base
        nlohmann_json::nlohmann_json
      )
      
      target_include_directories(city-editor-tests PRIVATE
        ${CMAKE_SOURCE_DIR}/editor
        ${CMAKE_SOURCE_DIR}/include
      )
      
      set_target_properties(city-editor-tests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${OUT_DIR}"
      )
      
      add_test(NAME editor_basic_tests COMMAND city-editor-tests WORKING_DIRECTORY "${OUT_DIR}")
    endif()
    
    # Adicionar testes ao CTest
    add_test(NAME city_basic_tests COMMAND city-tests WORKING_DIRECTORY "${OUT_DIR}")
    
    # Garantir que os assets estejam disponíveis para os testes
    if(COPY_ASSETS AND EXISTS "${ASSETS_DIR}")
      add_custom_command(TARGET city-tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${ASSETS_DIR}" "${OUT_DIR}/assets"
        VERBATIM
      )
    endif()
  else()
    message(WARNING "GTest not found, tests will not be built")
  endif()
endif()

# ===== Instalação =====
include(GNUInstallDirs)

install(TARGETS city-simulator
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  BUNDLE DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(BUILD_EDITOR)
  install(TARGETS city-editor
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    BUNDLE DESTINATION ${CMAKE_INSTALL_BINDIR}
  )
endif()

# Instalar assets se existirem
if(EXISTS "${ASSETS_DIR}")
  install(DIRECTORY "${ASSETS_DIR}/" 
    DESTINATION ${CMAKE_INSTALL_DATADIR}/citysimulator/assets
  )
endif()

if(EXISTS "${CONFIG_DIR}")
  install(DIRECTORY "${CONFIG_DIR}/" 
    DESTINATION ${CMAKE_INSTALL_DATADIR}/citysimulator/config
  )
endif()

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
message(STATUS "Available targets:")
message(STATUS "  - city-simulator (main game)")
if(BUILD_EDITOR)
  message(STATUS "  - city-editor")
endif()
if(BUILD_TESTS)
  message(STATUS "  - city-tests")
  if(BUILD_EDITOR)
    message(STATUS "  - city-editor-tests")
  endif()
endif()
message(STATUS "")
message(STATUS "Configured successfully! 🏙️")
message(STATUS "Next: Run 'cmake --build build --config Release'")
message(STATUS "===========================================")