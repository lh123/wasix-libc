#!/usr/bin/env bash
set -euo pipefail

wasmer pack "$(dirname "$0")/wasmer.toml" -o c-spawn-multiline.webc
wasmer run --enable-all c-spawn-multiline.webc

echo "c_spawn_multiline test passed"
