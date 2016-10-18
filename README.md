# Hill Cipher

    https://en.wikipedia.org/wiki/Hill_cipher

###### Character mapping Matrix

    A-->1 ... Z-->26

    a-->27 ... b-->28

    and so on..!! see code


### Platform

> LINUX build only

    GUI is coming in future possibly

### First clone the repo
> then go to the project directory and build and run
> so simple

     Sample matrix is given in input.txt

### Build

    make

### Run

    make run

### Clean

    make clean

#### Programm Output Representation

### Core Logic of the Program

#### Hill Class

### namespace is used as helped class

### OOP

    All namespace methods are completely reuseable

### Good side

    No memory leak, uninitized value as programm is checked by google sanitizer

### Downside

    seperation of concern

    Only decryption will not work well here because encrypted code is rounding using required  modulo

    To work with decrypted code you have to work with value not with character

### Linux Terminal Issue

    Linux termios object is called in linuxUtil.hpp file

    If Program crash unexpectedly badly, then you have to close the terminal

##### This codebase is POSIX compatible

### Improvement

    You can apply c++ template(generic) easily
