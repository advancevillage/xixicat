# xixicat
### require
 * version: 0.0.0
 * Clang-LLVM: Apple LLVM version 10.0.0 (clang-1000.10.44.4)

### build
 * clang  src/core/xixicat.c -I src/core/ -I src/os/linux  -o src/test/test
 * clang  src/core/xixicat.c src/core/xxc_string.c -I src/core/ -I src/os/linux  -o src/test/test -g
 * clang  src/core/xixicat.c src/core/xxc_string.c src/core/xxc_times.c src/core/xxc_log.c -I src/core/ -I src/os/linux  -lcjson -o src/test/test -g

### code style
 * Conditionals and Loops
```c
    if(*fmt == '%'){

    }else{

    }
```