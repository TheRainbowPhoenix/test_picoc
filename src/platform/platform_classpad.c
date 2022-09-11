//
// Created by Phoebe on 11/09/2022.
//

#include "../picoc/picoc.h"
#include "../picoc/interpreter.h"

void* calloc(int num, int size) {
    void* p = malloc(num*size);
    if(!p) return NULL;
    memset(p, 0, num*size);
    return p;
}

/* deallocate any storage */
void PlatformCleanup()
{
}

/* get a line of interactive input */
char *PlatformGetLine(char *Buf, int MaxLen, const char *Prompt)
{
    // XXX - unimplemented so far
    return NULL;
}

/* get a character of interactive input */
int PlatformGetCharacter()
{
    // XXX - unimplemented so far
    return 0;
}

//char* curoutptr = (char*)0xE5200000;
/* write a character to the console */
void PlatformPutc(unsigned char OutCh, union OutputStreamInfo *Stream)
{
//    if(curoutptr < (char*)0xE5200FFF) {
//        *curoutptr = (char)OutCh;
//        curoutptr++;
//    }
}

/* mark where to end the program for platforms which require this */
jmp_buf PicocExitBuf;

/* exit the program */
void PlatformExit(int RetVal)
{
//    PicocExitValue = RetVal;
//    longjmp(PicocExitBuf, 1);
}

/* Utilities - PicoC output glue code */

char* PlatformGetOutputPointer() {
//    return (char*)0xE5200000;
    return 0;
}

char* PlatformGetOutputCursor() {
//    return curoutptr;
    return '\0';
}

void PlatformClearOutput() {
//    curoutptr = (char*)0xE5200000;
}

void PicocPlatformScanFile(const char *filename) {
    char* asrc = "#include <stdio.h>\nprintf(\"Hello world\\n\");\nint Count;\nfor (Count = -5; Count <= 5; Count++)\nprintf(\"Count = %d\\n\", Count);\nvoid main() {}\n\0";

    // TODO: open and check the file
    unsigned int filesize = strlen(asrc);
    // TODO: check enough stack
    // if(0x881E0000 - (int)GetStackPtr() < 500000 - filesize*sizeof(unsigned char) - 30000) {
//    asrc = (char*)alloca(filesize*sizeof(unsigned char)+5);
//    asrc[filesize] = '\0';
    PicocParse(filename, asrc, strlen(asrc), 1, 0, 0);
}