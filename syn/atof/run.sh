set -e

clang -emit-llvm -c -g -O0 -DUSE_KLEE test.c

time klee --solver-backend=z3 -libc=uclibc -use-cex-cache=1 --posix-runtime test.bc --sym-arg 2
#gdb --args klee --solver-backend=z3 -libc=uclibc -use-cex-cache=1 --posix-runtime test.bc --sym-arg 2

