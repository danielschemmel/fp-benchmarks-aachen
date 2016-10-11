rm -rf "$(dirname "$(readlink -f "$0")")"/*/klee-*
rm -rf "$(dirname "$(readlink -f "$0")")"/*/*.bc
