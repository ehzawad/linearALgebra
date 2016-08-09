// header guard
// This file specific Linux
// for Windows, logic is same
// but implementation will differ
#ifndef _LinuxTermios_HPP_
#define _LinuxTermios_HPP_

#include <termios.h>
#include <unistd.h>

namespace linuxUtil {

termios setNotEchoingMode()
{
    // instantiating termios object type
    // which immediately help us to know the currentState
    termios currentState;

    // tcgetattr() gets the parameters associated with the object referred  by
    // fd  and  stores  them in the termios structure referenced by termios_p.
    // This function may be invoked from a background  process;  however,  the
    // terminal  attributes  may  be  subsequently  changed  by  a  foreground
    // process.
    //
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

    return currentState;
}

void goBack(termios& previouslyRunningState)
{
    // go back to normal state
    // otherwise it will non ECHO mode in current bash session
    tcsetattr(STDIN_FILENO, TCSANOW, &previouslyRunningState);
}

}

#endif
