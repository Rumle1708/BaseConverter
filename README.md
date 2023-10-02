# Base Converter
A program that converts numbers from one base to another base.
Currently supports binary, octal, hexa and decimal conversion.

## Usage
Give the program your number with the base indicator at the front of the number.
For example:

```shell
base 0d100
```

This means interpret this number as a decimal.
This command will output the number in other supported bases:

```plain
0b1100100
0o144
0d100
0x64
```

This output shows the other available base indicators that can be used on the input as well.
The leading 0 can also be omitted for faster typing so ```b1100``` is the same as ```0b1100```.
The program defaults to base 10 if no base indicator is given.

## Build
Run command:

```shell
make
```

Executable files should be in ```bin/```.

## Install
Run this command:

```shell
make install
```

You most likely need root priviliges for this to work since install defaults to ```/usr/local/bin/``` but you can change by passing the install directory variable.
For example:

```shell
make install INSTALLDIR=~/.local/bin
```

