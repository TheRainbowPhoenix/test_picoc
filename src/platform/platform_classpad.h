//
// Created by Phoebe on 11/09/2022.
//

#ifndef TEST_PICOC_PLATFORM_CLASSPAD_H
#define TEST_PICOC_PLATFORM_CLASSPAD_H

#include "../casio/div.h"

// void* calloc(int num, int size);
void PlatformCleanup();
char *PlatformGetLine(char *Buf, int MaxLen, const char *Prompt);
int PlatformGetCharacter();
// void PlatformPutc(unsigned char OutCh, union OutputStreamInfo *Stream);
void PlatformExit(int RetVal);
char* PlatformGetOutputPointer();
char* PlatformGetOutputCursor();
void PlatformClearOutput();
void FPUTS_DEBUG(char *message);

#endif //TEST_PICOC_PLATFORM_CLASSPAD_H
