# wintab-proxy

This is a fork of [wintab-interposer](https://github.com/jchv/wintab-interposer) by [jchv](https://github.com/jchv)
that removes all the coolest parts of the original project and only leaves the library proxying part.

It serves as a temporary workaround for [some apps](https://github.com/stopperw/pain-studio-mask/issues/1)
that don't want to play nicely with [Pain Studio Mask](https://github.com/stopperw/pain-studio-mask) directly.

## Usage with PSM

1. Download this from [releases](https://github.com/stopperw/wintab-proxy/releases/latest)
2. Copy the DLL for the correct app architecture next to its executable
3. Rename PSM's DLL to `wintab32_real.dll`

Original README:

# Wintab-Interposer
This is a quick'n'dirty library that sits between wintab32.dll and logs all of the API calls, so that you can examine a program's Wintab usage. It is ultimately based on generated code from Winedump, though it is standalone and only needs MinGW-w64 to compile.

## Build
Because this library is so simple, it just uses a simple GNUmakefile. By default, it will build for both 32-bit (x86) and 64-bit (x86-64) targets, though you can use the x86/x64 targets instead:

```sh
make x86 # build only 32-bit
make x64 # build only 64-bit
```

By default, it assumes the compilers are `i686-w64-mingw32-g++` and `x86_64-w64-mingw32-g++`. If this is not true for your setup, you can override it by passing `CXX32` and `CXX64` to the make invocation:

```sh
make CXX32=g++ x86
```

## Usage
By default, logs go to stderr. If you want to send the logs to file, you can set the environment variable `WINTAB_LOG` to a filename, and that file will be used instead.

By default, Wintab-Interposer will try to find the real Wintab32 from the system directory. If it fails, it will try to load a library called wintab32_real. If both fail, it will log then abort.
