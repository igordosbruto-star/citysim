#!/usr/bin/env bash
set -euo pipefail

# This script bootstraps the minimal development environment described in docs/SETUP.md.
# It installs vcpkg (if necessary), fetches core dependencies, and configures a Release build.

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
VCPKG_ROOT="${VCPKG_ROOT:-"$ROOT_DIR/third_party/vcpkg"}"
BUILD_DIR="$ROOT_DIR/build"

if [ ! -d "$VCPKG_ROOT/.git" ]; then
    echo "Cloning vcpkg into $VCPKG_ROOT"
    mkdir -p "$(dirname "$VCPKG_ROOT")"
    git clone https://github.com/microsoft/vcpkg.git "$VCPKG_ROOT"
fi

if [ ! -x "$VCPKG_ROOT/vcpkg" ]; then
    echo "Bootstrapping vcpkg"
    (cd "$VCPKG_ROOT" && ./bootstrap-vcpkg.sh)
fi

echo "Installing CitySimulator dependencies via vcpkg"
"$VCPKG_ROOT/vcpkg" install \
    sfml \
    nlohmann-json \
    lua \
    sol2 \
    entt \
    glew \
    wxwidgets \
    gtest

cmake -S "$ROOT_DIR" -B "$BUILD_DIR" \
    -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" \
    -DCMAKE_BUILD_TYPE=Release

cmake --build "$BUILD_DIR" --config Release

echo "Environment setup complete. Binaries are available in $BUILD_DIR."

cmake -S "$ROOT_DIR" -B "$BUILD_DIR" \
    -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" \
    -DVCPKG_FEATURE_FLAGS=manifests \
    -DCMAKE_BUILD_TYPE=Release