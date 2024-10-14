# genpasswd

simple password generator written in C, originally made by [lilyyllyyllyly](https://github.com/lilyyllyyllyly), turned into a cryptographically secure password generator by me ([xmm16](https://github.com/xmm16))

[![pre-commit.ci status](https://results.pre-commit.ci/badge/github/xmm16/genpasswd/main.svg)](https://results.pre-commit.ci/latest/github/xmm16/genpasswd/main)

## Installation

### Dependencies

- Clang >=18
- libsodium
- tcl

```
git clone https://github.com/xmm16/genpasswd
cd genpasswd
make
```

you probably want to put it in your PATH (somewhere like `~/.local/bin/genpasswd` should be fine, if that directory is in your PATH)

## Usage

Simply execute `genpasswd`

### Example

```
> genpasswd
Cryptographic engine started successfully!
Result pre-scramble (HEXADECIMAL): 71cb637e88fa9f097af229636f49af90f75e2828ed2e2784c683167a8c2d9f40553fef8643c11d2af722783048fd9bc8d6e32f251a6472d827519b309e7f5889
Result scrambled for password usage (Base64): cctjfoj6nwl68iljb0mvkPdeKCjtLieExoMWeowtn0BVP--GQ8EdKvcieDBI_ZvI1uMvJRpkctgnUZswnn9YiQ==
```
