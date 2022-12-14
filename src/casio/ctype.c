//
// Created by Phoebe on 11/09/2022.
//

#include "ctype.h"

int isascii(int c) {
    return c < 128;
}

int isblank(int c) {
    return c == ' ' || c == '\t';
}

int iscntrl(int c) {
    return c >=0 && c < 31;
}

int isgraph(int c) {
    return c > ' ' && c <= '~';
}

int islower(int c) {
    return c >= 'a' && c <= 'z';
}

int isprint(int c) {
    return c >= ' ' && c <= '~';
}

int ispunct(int c) {
    return isgraph(c) && !isalnum(c);
}

int isupper(int c) {
    return c >= 'A' && c <= 'Z';
}

int isxdigit(int c) {
    return isdigit(c) || ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
}


int toupper(int c) {
    return islower(c) ? c - 32 : c;
}

int tolower(int c) {
    return isupper(c) ? c + 32 : c;
}