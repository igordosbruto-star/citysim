@echo off
setlocal enabledelayedexpansion

rem This batch file mirrors the minimal environment setup described in docs/SETUP.md.
rem It ensures vcpkg is available, installs the required ports, and generates a Release build.

set "ROOT_DIR=%~dp0.."
for %%I in ("%ROOT_DIR%") do set "ROOT_DIR=%%~fI"

if defined VCPKG_ROOT (
    set "VCPKG_DIR=%VCPKG_ROOT%"
) else (
    set "VCPKG_DIR=%ROOT_DIR%\third_party\vcpkg"
)

if not exist "%VCPKG_DIR%\.git" (
    echo Cloning vcpkg into %VCPKG_DIR%
    if not exist "%VCPKG_DIR%" mkdir "%VCPKG_DIR%"
    git clone https://github.com/microsoft/vcpkg.git "%VCPKG_DIR%"
)

if not exist "%VCPKG_DIR%\vcpkg.exe" (
    echo Bootstrapping vcpkg
    pushd "%VCPKG_DIR%"
    call .\bootstrap-vcpkg.bat
    popd
)

echo Installing CitySimulator dependencies via vcpkg
"%VCPKG_DIR%\vcpkg.exe" install ^
    sfml ^
    nlohmann-json ^
    lua ^
    sol2 ^
    entt ^
    glew ^
    wxwidgets ^
    gtest

set "BUILD_DIR=%ROOT_DIR%\build"
cmake -S "%ROOT_DIR%" -B "%BUILD_DIR%" ^
    -DCMAKE_TOOLCHAIN_FILE="%VCPKG_DIR%\scripts\buildsystems\vcpkg.cmake" ^
    -DCMAKE_BUILD_TYPE=Release

cmake --build "%BUILD_DIR%" --config Release

echo Environment setup complete. Binaries are available in %BUILD_DIR%.
endlocal
