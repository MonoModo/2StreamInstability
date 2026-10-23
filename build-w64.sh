#!/usr/bin/env bash
set -Eeuo pipefail

project_dir="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
cd "$project_dir"

required_tools=(cmake ninja x86_64-w64-mingw32-gcc x86_64-w64-mingw32-g++ x86_64-w64-mingw32-windres)
for tool in "${required_tools[@]}"; do
	if ! command -v "$tool" >/dev/null 2>&1; then
		printf 'Required tool not found: %s\n' "$tool" >&2
		exit 1
	fi
done

cmake --preset linux-mingw-x64
cmake --build --preset linux-mingw-x64-release --clean-first

printf 'Built Windows executable: %s\n' "$project_dir/build/linux-mingw-x64/example_glfw_opengl3.exe"