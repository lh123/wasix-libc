#!/usr/bin/env bash
set -euo pipefail

wasmer run --enable-all --env TZ=CST-8 ./main
wasmer run --enable-all \
    --volume /usr/share/zoneinfo:/usr/share/zoneinfo \
    --env TZ=Asia/Shanghai \
    ./main

echo "c_timezone test passed"
