msr-utils
=========

Magnetic stripe utilities, broken out of the libmsr repository.

These utilities have been modified to compile with
[my fork of libmsr](https://github.com/woodruffw/libmsr).

## Compilation

```bash
$ git clone https://github.com/woodruffw/libmsr && cd libmsr
$ make && sudo make install
$ cd ..
$ git clone https://github.com/woodruffw/msr-utils && cd msr-utils
$ make # and optionally install
```
## Caveats

**Some of these utilities are fairly old and may not work properly.**

The only utility I'm currently working on is `msr-dump`. This repo primarily
exists to separate the concerns of `libmsr` without deleting historically
relevant code.
