## City Simulator — Copilot instructions (concise)

Purpose: help AI coding assistants be productive quickly in this repo. Keep answers focused, make small edits, and prefer referencing existing files listed below.

- Primary language and tools: C++20, CMake, SFML, entt (ECS), vcpkg. See `CMakeLists.txt` and `CMakePresets.json` for exact options.

- Where to start (single-file entry points):
  - Project overview: `README.md`, `docs/AGENTS.md`, `docs/ARCHITECTURE.md`, `docs/SETUP.md`.
  - Build: `CMakePresets.json`, top-level `CMakeLists.txt`.
  - Environment scripts: `scripts/setup_environment.sh` (Linux/macOS) and `scripts/setup_environment.bat` (Windows).
  - Core code: `src/Core/*`, `include/Core/*` (game loop, Application, Game).
  - Systems: `src/tech_tree/`, `src/simulation/`, `src/rendering/`, `src/Graphics/`.
  - Tests: `tests/` and CTest config in `build/CTestTestfile.cmake`.

- Quick actionable workflows (Windows PowerShell):
  - Bootstrap (recommended): `.\\scripts\\setup_environment.bat` — this clones/bootstraps vcpkg and builds Release.
  - Manual configure with vcpkg:
    - `cmake -B build -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake`
    - `cmake --build build --config Release`
  - Using presets (alternative):
    - `cmake --preset windows-vcpkg` (configure)
    - `cmake --build --preset windows-release` or `cmake --build build --config Release` (build)
  - Run tests:
    - `cmake --build build --config Debug` then `cd build ; ctest --output-on-failure`
  - Open solution for debugging: `build/CitySimulator.sln` (Visual Studio) after configure.

- Important project-specific conventions (do not invent):
  - C++ style: C++20, PascalCase for types, camelCase for functions/vars, UPPER_CASE for constants. See `docs/AGENTS.md` for examples.
  - ECS pattern: Components are POD-like structs (in `include/`), Systems encapsulate logic (in `src/`).
  - Tech-tree is core gameplay — changes are high-impact. Look under `src/tech_tree/` and tests related to tech tree in `tests/` before modifying.
  - Asset copy: controlled by CMake option `COPY_ASSETS` — built binaries expect assets under `build/bin/<Config>/assets`.

- Integration points and dependencies to respect:
  - vcpkg-managed libraries (SFML, nlohmann-json, lua, sol2, entt, wxwidgets, gtest). Use the repository presets or `scripts/setup_environment.*` to match CI.
  - CMake feature flags in `CMakePresets.json` (`BUILD_EDITOR`, `BUILD_TESTS`, `COPY_ASSETS`) — toggle them rather than adding ad-hoc steps.
  - Tests are run via CTest; use `ctest` to reproduce CI/test failures.

- Editing guidance for AI agents (how to propose changes):
  - Small, focused PRs. Update `CHANGELOG.md` under **[Unreleased]** when behavior changes.
  - Add or update unit tests under `tests/` for logic changes (tech-tree, ECS updates).
  - Follow existing patterns: e.g., new system → `include/<Subsystem>/*.hpp` (component types) and `src/<Subsystem>/*.cpp` (system implementation). Example files: `include/Core/Application.hpp`, `src/Core/Application.cpp`.

- Quick references/examples you can copy:
  - Add a Debug build and run tests:
    - `cmake -B build -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Debug`
    - `cmake --build build --config Debug`
    - `cd build ; ctest --output-on-failure`

If anything above is unclear or you need more examples (e.g. where exactly tech-tree nodes are implemented), tell me which area and I will expand with file-level examples and a short patch suggestion.

---
Last updated: 2025-11-06 (generated from docs/AGENTS.md, README.md, CMakePresets.json)
