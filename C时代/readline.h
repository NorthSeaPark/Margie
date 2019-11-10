#ifndef READLINE_H
#define READLINE_H
/*ifndef checks whether the given token has been #defined earlier in the file or
 in an included file; if not, it includes the code
 between it and the closing #else or, if no #else is present, #endif statement.*/
 /*
	Skipes leading white-space characters, then reads the remainder of the input line
	and stores it in str. Truncates the line if its length exceeds n. Returns the number
	of characters stored.
 */
int read_line(char str[], int n);

#endif
