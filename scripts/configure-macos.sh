#!/usr/bin/env bash
set -euo pipefail

cmake -S . -B build-macos -G Xcode -DCMAKE_OSX_DEPLOYMENT_TARGET=12.0 "$@"
