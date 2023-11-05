# genpasswd
simple password generator written in C

## Installation
either grab the [release](https://github.com/lilyyllyyllyly/genpasswd/releases/tag/v1.0.0) or run the following commands to build it yourself:
```
git clone https://github.com/lilyyllyyllyly/genpasswd
cd genpasswd
gcc pass.c -o genpasswd
```
make sure you have gcc installed!

you probably want to put it in your PATH (somewhere like `~/.local/bin/genpasswd` should be fine, if that directory is in your PATH)

### Usage
```
genpasswd SIZE
```
(if you compiled it with the name genpasswd/got the release, then put it in your PATH)

SIZE is the amount of digits of the generated password, must be an integer between 1 and 200
(completely arbitrary limit because having no limit seemed like it could lead to problems and most sites dont accept passwords that long anyways lol)

#### Example
```
> genpasswd 25
U#mKl<EpDQ3Zl.w(mxAf\//kk
```
(notice how the password is 25 characters long)
