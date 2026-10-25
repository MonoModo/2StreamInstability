#!/usr/bin/env bash
set -Eeuo pipefail

project_dir="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
cd "$project_dir"

required_tools=(cmake ninja nproc x86_64-w64-mingw32-gcc x86_64-w64-mingw32-g++ x86_64-w64-mingw32-windres)
for tool in "${required_tools[@]}"; do
	if ! command -v "$tool" >/dev/null 2>&1; then
		printf 'Required tool not found: %s\n' "$tool" >&2
		exit 1
	fi
done

available_cores="$(nproc)"
build_jobs=$((available_cores * 8 / 10))
if (( build_jobs < 1 )); then
	build_jobs=1
fi

cmake --preset linux-mingw-x64
cmake --build --preset linux-mingw-x64-release --parallel "$build_jobs" --clean-first

printf 'Built Windows executable: %s\n' "$project_dir/build/linux-mingw-x64/example_glfw_opengl3.exe"