#!/usr/bin/env bash
set -euo pipefail

HEX=${1:?Usage: ./upload.sh path/to/sketch.hex [port]}

if [[ -n ${2:-} ]]; then
    PORT=$2
else
    PORT=$(ls /dev/cu.usbmodem* 2>/dev/null | head -1)
    [[ -n $PORT ]] || { echo "No Arduino found on /dev/cu.usbmodem* — is it plugged in?"; exit 1; }
fi

AVRDUDE=$HOME/Library/Arduino15/packages/arduino/tools/avrdude/8.0.0-arduino1
CONF=$AVRDUDE/etc/avrdude.conf

[[ -f $HEX ]] || { echo "No HEX found — run ./build.sh $SKETCH first"; exit 1; }

"$AVRDUDE/bin/avrdude" -C"$CONF" -patmega328p -carduino -P$PORT -b115200 -Uflash:w:"$HEX":i
