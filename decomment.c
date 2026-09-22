#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

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

/* the functions defined below are the functions for each state */

/* each function will take an input of a character c and returns the 
   correct next state while also executing any necessary action such
   as printing a char, updating values, etc. each state behaves 
   according to my decomment DFA */

enum Statetype handleBaseState(int c) {
    if (c == '/') {
        return SLASH_SEEN;
    }
    if (c == '"') {
        putchar('"');
        return IN_DOUBLE_QUOTES;
    }
    if (c == '\'') {
        putchar('\'');
        return IN_SINGLE_QUOTES;
    }
    putchar(c);
    return BASE;
}

enum Statetype handleSlashSeenState(int c) {
    if (c == '*') {
        putchar(' ');
        return IN_COMMENT;
    }
    if (c == '/') {
        putchar('/');
        return SLASH_SEEN;
    }
    if (c == '"') {
        putchar('/');
        putchar('"');
        return IN_DOUBLE_QUOTES;
    }
    if (c == '\'') {
        putchar('/');
        putchar('\'');
        return IN_SINGLE_QUOTES;
    }
    putchar('/');
    putchar(c);
    return BASE;
}

enum Statetype handleInCommentState(int c) {
    if (c == '*') {
        return LEAVE_COMMENT;
    }
    if (c == '\n') {
        putchar('\n');
    }
    return IN_COMMENT;
}

enum Statetype handleLeaveCommentState(int c) {
    if (c == '/') {
        return BASE;
    }
    if (c == '*') {
        return LEAVE_COMMENT;
    }
    if (c == '\n') {
        putchar('\n');
    }
    return IN_COMMENT;
}

enum Statetype handleInDoubleQuotesState(int c) {
    if (c == '\\') {
        putchar('\\');
        return TEMP_LEAVE_DOUBLE_QUOTES;
    }
    if (c == '"') {
        putchar('"');
        return BASE;
    }
    putchar(c);
    return IN_DOUBLE_QUOTES;
}

enum Statetype handleTempLeaveDoubleQuotesState(int c) {
    putchar(c);
    return IN_DOUBLE_QUOTES;
}

enum Statetype handleInSingleQuotesState(int c) {
    if (c == '\\') {
        putchar('\\');
        return TEMP_LEAVE_SINGLE_QUOTES;
    }
    if (c == '\'') {
        putchar('\'');
        return BASE;
    }
    putchar(c);
    return IN_SINGLE_QUOTES;
}

enum Statetype handleTempLeaveSingleQuotesState(int c) {
    putchar(c);
    return IN_SINGLE_QUOTES;
}

/*--------------------------------------------------------------------*/

/* main function
   reads the characters given and removes comments from the lines and
   then outputs the comment free text. throws errors for unterminated
   comments */

int main(void) {

    /* all of the variables needed to loop through chars*/
    int c;
    int currentLine = 1;
    int commentStartLine = 0;
    enum Statetype state = BASE;
    /* nextState helps to record the line when the comment starts */
    enum Statetype nextState = BASE;

    /* loops through all of the chars in input */
    while ((c = getchar()) != EOF) {

        /* assigns the matching function based on the current state 
           and stores the next state */
        switch (state) {
            case BASE:
                nextState = handleBaseState(c);
                break;
            case SLASH_SEEN:
                nextState = handleSlashSeenState(c);
                break;
            case IN_COMMENT:
                nextState = handleInCommentState(c);
                break;
            case LEAVE_COMMENT:
                nextState = handleLeaveCommentState(c);
                break;
            case IN_DOUBLE_QUOTES:
                nextState = handleInDoubleQuotesState(c);
                break;
            case TEMP_LEAVE_DOUBLE_QUOTES:
                nextState = handleTempLeaveDoubleQuotesState(c);
                break;
            case IN_SINGLE_QUOTES:
                nextState = handleInSingleQuotesState(c);
                break;
            case TEMP_LEAVE_SINGLE_QUOTES:
                nextState = handleTempLeaveSingleQuotesState(c);
                break;
        }

        /* logic to check if a comment has been started and to record
           the line where is happens */
        if (state == SLASH_SEEN && nextState == IN_COMMENT) {
            commentStartLine = currentLine;
        }

        /* updates the line counter if c is a newline character */
        if (c == '\n') {
            currentLine++;
        }

        state = nextState;
    }

    /* end of file handling */

    /* checks what state code is in and whether to accept or reject
       accordingly. also throws error for unterminated comment */
    if (state == SLASH_SEEN) {
        putchar('/');
        return 0;
    }
    if (state == IN_COMMENT || state == LEAVE_COMMENT) {
        fprintf(stderr, "Error: line %d: unterminated comment\n", 
        commentStartLine);
        return EXIT_FAILURE;
    }
    return 0;
}
