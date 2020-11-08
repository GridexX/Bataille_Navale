	// Inspiration prise d'après http://www.cplusplus.com/forum/unices/27735/
#include <iostream>
#include <stdexcept>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(WINDOWS)\
    || defined(__WINDOWS__)
# ifndef WINDOWS
#  define WINDOWS
# endif
#elif defined(unix) || defined(UNIX) || defined(__UNIX__) || defined(POSIX)    \
      || defined(__POSIX__) || defined(CYGWIN)
# ifndef POSIX
#  define POSIX
# endif
#endif

#if defined(WINDOWS)
# include <windows.h>
#include <conio.h>
#elif defined(POSIX)
# include <unistd.h>
# include <termios.h>
#endif

using namespace std;


#include "hide.h"

// Les variables globales normalement, c'est *mal* ! Mais là, c'est franchement plus simple...
#if defined(WINDOWS)
HANDLE hstdin;
DWORD mode;
#elif defined(POSIX)
struct termios tty_attr;
tcflag_t c_lflag;
#endif

char getHiddenChar()
{
	// Disable character echoing and line buffering
#if defined(WINDOWS)
	hstdin = GetStdHandle(STD_INPUT_HANDLE);

	if (!GetConsoleMode(hstdin, &mode))
		throw runtime_error(__FILE__" : Can't get console mode.");

	if (hstdin == INVALID_HANDLE_VALUE || !(SetConsoleMode(hstdin, 0)))
		throw runtime_error(__FILE__" : Failed to disable buffering.");
#elif defined(POSIX)
	if (tcgetattr(STDIN_FILENO, &tty_attr) < 0)
		throw runtime_error(__FILE__" : Failed call to tcgetattr().");

	c_lflag = tty_attr.c_lflag; /* Allows us to restore this later */
	tty_attr.c_lflag &= ~ICANON;
	tty_attr.c_lflag &= ~ECHO;

	if (tcsetattr(STDIN_FILENO, 0, &tty_attr) < 0)
		throw runtime_error(__FILE__" : Failed call to tcsetattr().");
#else
 cerr << "Unable to stop the echoing." << endl;
#endif
        char c = cin.get();

	// Re-enable character echoing and line buffering
#if defined(WINDOWS)
	if (!SetConsoleMode(hstdin, mode))
		throw runtime_error(__FILE__" : Failed to set console mode back.");
#elif defined(POSIX)
	tty_attr.c_lflag = c_lflag;

	if (tcsetattr(STDIN_FILENO, 0, &tty_attr) < 0)
		throw runtime_error(__FILE__" : Failed restoring call to tcsetattr().");
#endif
 return c;
}

char getChar()
{
	// Disable character echoing and line buffering
#if defined(WINDOWS)
	char c = getche();
#elif defined(POSIX)
	if (tcgetattr(STDIN_FILENO, &tty_attr) < 0)
		throw runtime_error(__FILE__" : Failed call to tcgetattr().");

	c_lflag = tty_attr.c_lflag; /* Allows us to restore this later */
	tty_attr.c_lflag &= ~ICANON;

	if (tcsetattr(STDIN_FILENO, 0, &tty_attr) < 0)
		throw runtime_error(__FILE__" : Failed call to tcsetattr().");
        char c = cin.get();
#else
 cerr << "Unable to stop the echoing." << endl;
#endif


	// Re-enable character echoing and line buffering
#if defined(WINDOWS)
#elif defined(POSIX)
	tty_attr.c_lflag = c_lflag;

	if (tcsetattr(STDIN_FILENO, 0, &tty_attr) < 0)
		throw runtime_error(__FILE__" : Failed restoring call to tcsetattr().");
#endif
 return c;
}


