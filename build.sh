#!/usr/bin/env bash
set -euo pipefail

SKETCH=${1:?Usage: ./build.sh path/to/sketch.ino}
NAME=$(basename "$SKETCH" .ino)
OUT=build/$(dirname "$SKETCH")

ARDUINO=$HOME/Library/Arduino15/packages/arduino
TOOLS=$ARDUINO/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin
CORE=$ARDUINO/hardware/avr/1.8.8/cores/arduino
VARIANT=$ARDUINO/hardware/avr/1.8.8/variants/standard

FLAGS="-mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10819 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -I$CORE -I$VARIANT -Os -ffunction-sections -fdata-sections"

mkdir -p "$OUT" build/core

# Build the Arduino core once; reuse on subsequent runs
if [[ ! -f build/libcore.a ]]; then
    echo "Building Arduino core..."
    for f in "$CORE"/*.c;   do "$TOOLS/avr-gcc" $FLAGS -std=gnu11   -c "$f" -o "build/core/$(basename "$f").o"; done
    for f in "$CORE"/*.cpp; do "$TOOLS/avr-g++" $FLAGS -std=gnu++11 -fno-exceptions -fno-threadsafe-statics -c "$f" -o "build/core/$(basename "$f").o"; done
    "$TOOLS/avr-ar" rcs build/libcore.a build/core/*.o
fi

# Compile sketch (.ino is C++ with an implicit #include <Arduino.h>)
printf '#include <Arduino.h>\n' | cat - "$SKETCH" > "$OUT/$NAME.cpp"
"$TOOLS/avr-g++" $FLAGS -std=gnu++11 -fno-exceptions -fno-threadsafe-statics -c "$OUT/$NAME.cpp" -o "$OUT/$NAME.o"

# Link and produce HEX
"$TOOLS/avr-gcc" -mmcu=atmega328p -Wl,--gc-sections -Os "$OUT/$NAME.o" build/libcore.a -o "$OUT/$NAME.elf"
"$TOOLS/avr-objcopy" -O ihex -R .eeprom "$OUT/$NAME.elf" "$OUT/$NAME.hex"

"$TOOLS/avr-size" --format=avr --mcu=atmega328p "$OUT/$NAME.elf"
echo "HEX: $OUT/$NAME.hex"
