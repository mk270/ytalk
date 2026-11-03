#!/bin/sh
# Build ytalk's terminal emulation with ASan/UBSan and feed it hostile
# escape sequences.  Needs ./configure to have been run (for config.h).
# usage: tests/run.sh [number-of-random-streams]
set -e
here=$(cd "$(dirname "$0")" && pwd)
top=$here/..
n=${1:-300}
[ -f "$top/config.h" ] || { echo "run ./configure first"; exit 2; }
out=${TMPDIR:-/tmp}/ytalk-test.$$
trap 'rm -rf "$out"' EXIT
mkdir -p "$out"

${CC:-cc} -g -O1 -fsanitize=address,undefined \
    -fno-sanitize-recover=undefined -DHAVE_CONFIG_H \
    -I"$top" -I"$top/src" -o "$out/vt100" \
    "$here/vt100_driver.c" "$here/stubs.c" \
    "$top/src/term.c" "$top/src/vt100.c" "$top/src/mem.c"

export ASAN_OPTIONS=detect_leaks=0
bad=0
# a number with far more digits than an int holds, as an argument
printf '\033[99999999999999999999999999A\033[99999999999999999999@' \
    > "$out/digits.bin"
for f in "$out/digits.bin"; do
    "$out/vt100" "$f" 2>"$out/err" || { cat "$out/err"; bad=1; }
    [ -s "$out/err" ] && { cat "$out/err"; bad=1; }
done
i=1
while [ "$i" -le "$n" ]; do
    python3 -I "$here/gen.py" "$i" > "$out/in.bin"
    "$out/vt100" "$out/in.bin" 2>"$out/err" || bad=1
    if [ -s "$out/err" ]; then
        echo "stream $i:"; head -5 "$out/err"; bad=1
    fi
    i=$((i + 1))
done
[ $bad -eq 0 ] && echo "PASS vt100 ($n random streams)"
exit $bad
