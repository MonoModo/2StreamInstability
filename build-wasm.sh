#!/usr/bin/env bash
set -Eeuo pipefail

project_dir="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
build_dir="$project_dir/build/wasm"

required_tools=(emcmake emcc cmake ninja nproc)
for tool in "${required_tools[@]}"; do
	if ! command -v "$tool" >/dev/null 2>&1; then
		printf 'Required tool not found: %s\n' "$tool" >&2
		printf 'Install and activate the Emscripten SDK, then rerun this script.\n' >&2
		exit 1
	fi
done

available_cores="$(nproc)"
build_jobs=$((available_cores * 8 / 10))
if (( build_jobs < 1 )); then
	build_jobs=1
fi

emcmake cmake -S "$project_dir" -B "$build_dir" -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build "$build_dir" --parallel "$build_jobs" --clean-first

printf 'Built WebAssembly app: %s/example_glfw_opengl3.html\n' "$build_dir"