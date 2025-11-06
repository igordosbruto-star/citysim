#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="${BUILD_DIR:-"$ROOT_DIR/build"}"
CONFIG="${CONFIG:-Debug}"

EXTRA_CMAKE_ARGS=()

if [ -n "${TOOLCHAIN_FILE:-}" ]; then
    EXTRA_CMAKE_ARGS+=("-DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN_FILE}")
elif [ -n "${VCPKG_ROOT:-}" ] && [ -f "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" ]; then
    EXTRA_CMAKE_ARGS+=("-DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
fi

cmake -S "$ROOT_DIR" -B "$BUILD_DIR" \
    -DBUILD_TESTS=ON \
    -DCMAKE_BUILD_TYPE="$CONFIG" \
    "${EXTRA_CMAKE_ARGS[@]}"

cmake --build "$BUILD_DIR" --config "$CONFIG"

ctest --test-dir "$BUILD_DIR" --output-on-failure -C "$CONFIG"
