#!/usr/bin/env bash
set -Eeuo pipefail

project_dir="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
cd "$project_dir"

required_tools=(cmake ninja c++ nproc)
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

cmake --preset linux-native
cmake --build --preset linux-native-release --parallel "$build_jobs" --clean-first

printf 'Built Linux executable: %s/build/linux-native/example_glfw_opengl3\n' "$project_dir"