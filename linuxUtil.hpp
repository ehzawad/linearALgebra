// header guard
// This file specific Linux
// for Windows, logic is same
// but implementation will differ
#ifndef _LinuxTermios_HPP_
#define _LinuxTermios_HPP_

#include <iostream>
#include <termios.h>
#include <unistd.h>

namespace linuxUtil {

// http://stackoverflow.com/questions/13694170/how-do-i-hide-user-input-with-cin-in-c
void setNotEchoingMode()
{
    // TCIFLUSH: Flushes input data that has been received by the system but not read by an application.
    // STDIN_FILENO is input file descriptor associated with terminal
    if (tcflush(STDIN_FILENO, TCIFLUSH) == 0) {

        // instantiating termios object type
        // which immediately help us to know the currentState

        termios currentState;

        // tcgetattr() gets the parameters associated with the object referred  by
        // fd  and  stores  them in the termios structure referenced by termios_p.
        // This function may be invoked from a background  process;  however,  the
        // terminal  attributes  may  be  subsequently  changed  by  a  foreground
        // process.

        // similarly,
        // tcsetattr() is for setter for termios object

        // On program startup, the integer file descriptors  associated  with  the
        // streams  stdin,  stdout, and stderr are 0, 1, and 2, respectively.  The
        // preprocessor symbols STDIN_FILENO, STDOUT_FILENO, and STDERR_FILENO are
        // defined  with  these values in <unistd.h>.
        //

        tcgetattr(STDIN_FILENO, &currentState);

        termios changeState = currentState;
        // this change store locally in current bash session
        // tcflag c_lflag stands for localmode
        // TCSANOW, the change occurs immediately.
        // ~ECHO means not echoing input character
        changeState.c_lflag &= ~ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &changeState);
    } else {
        std::cerr << "termios process is not successful" << std::endl;
    }
}

void setEchoingMode(void)
{
    if (tcflush(STDIN_FILENO, TCIFLUSH) == 0) {

        termios currentState;

        tcgetattr(STDIN_FILENO, &currentState);

        termios changeState = currentState;
        changeState.c_lflag |= ECHO;

        tcsetattr(STDIN_FILENO, TCSANOW, &changeState);
    } else {
        std::cerr << "termios process is not successful" << std::endl;
    }
}

// automatically called before main starts
// that's why below two functions are static
__attribute__((constructor)) static void hereWeGo(void)
{
    setEchoingMode();
}

// automatically called after execution of main
__attribute__((destructor)) static void tearDown(void)
{
    setEchoingMode();
}

// end namespace
}

#endif
