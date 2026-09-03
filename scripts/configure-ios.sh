#!/usr/bin/env bash
set -euo pipefail

build_dir=build-ios
sdk=iphoneos

if [[ "${1:-}" == "--simulator" ]]; then
  build_dir=build-ios-simulator
  sdk=iphonesimulator
  shift
fi

cmake -S . -B "$build_dir" -G Xcode \
  -DCMAKE_SYSTEM_NAME=iOS \
  -DCMAKE_OSX_SYSROOT="$sdk" \
  -DCMAKE_OSX_DEPLOYMENT_TARGET=15.0 \
  "$@"
