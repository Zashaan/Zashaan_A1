#include <stdio.h>
#include <ctype.h>

/*--------------------------------------------------------------------*/

/* all of the different states in the decomment DFA */
enum Statetype {
    BASE,
    SLASH_SEEN,
    IN_COMMENT,
    LEAVE_COMMENT,
    IN_DOUBLE_QUOTES,
    TEMP_LEAVE_DOUBLE_QUOTES,
    IN_SINGLE_QUOTES,
    TEMP_LEAVE_SINGLE_QUOTES
};

/*--------------------------------------------------------------------*/

/* the functions defined below are the functions for each of the states
   each function will take an input of a character c and returns the 
   correct next state while also executing any necessary action such
   as printing a char, updating values, etc. */

enum Statetype base_state{

}

/*--------------------------------------------------------------------*/

/* main function
   reads the characters given and removes comments from the lines and
   then outputs the comment free text. throws errors for unterminated
   comments */

int main(void) {

}