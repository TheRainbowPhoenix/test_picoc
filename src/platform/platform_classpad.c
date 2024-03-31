//
// Created by Phoebe on 11/09/2022.
//

#include "../picoc/picoc.h"
#include "../picoc/interpreter.h"
#include <stdio.h>
#include <sys/stat.h>

// void* calloc(int num, int size) {
//     void* p = malloc(num*size);
//     if(!p) return NULL;
//     memset(p, 0, num*size);
//     return p;
// }

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

void FPUTS_DEBUG(char *message) {
    #ifdef DEBUG_FPUTS
    fputs(message, stdout);
    #endif
}

//char* curoutptr = (char*)0xE5200000;
/* write a character to the console */
void PlatformPutc(unsigned char OutCh, union OutputStreamInfo *Stream)
{
//    if(curoutptr < (char*)0xE5200FFF) {
//        *curoutptr = (char)OutCh;
//        curoutptr++;
//    }
    fputc(OutCh, stdout);
}

/* mark where to end the program for platforms which require this */
jmp_buf PicocExitBuf;

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
    printf("## TODO: ClearOutput ##\n");
//    curoutptr = (char*)0xE5200000;
}

void ProgramFailNoParser(const char *Message, ...)
{
    va_list Args;

    va_start(Args, Message);
    printf(Message, Args);
    va_end(Args);
    printf("\n");
    PlatformExit(1);
}

char* PlatformReadFile(const char* FileName)
{
    struct stat FileInfo;
    char* ReadText;
    FILE* InFile;
    int BytesRead;
    char* p;

    if (stat(FileName, &FileInfo))
    {
        ProgramFailNoParser("can't read file %s\n", FileName);
    }

    ReadText = malloc(FileInfo.st_size + 1);
    if (ReadText == NULL)
    {
        ProgramFailNoParser("out of memory\n");
    }

    InFile = fopen(FileName, "r");
    if (InFile == NULL)
    {
        ProgramFailNoParser("can't read file %s\n", FileName);
    }

    BytesRead = fread(ReadText, 1, FileInfo.st_size, InFile);
    fclose(InFile);
    if (BytesRead == 0)
    {
        ProgramFailNoParser("can't read file %s\n", FileName);
    }

    ReadText[BytesRead] = '\0';

    if ((ReadText[0] == '#') && (ReadText[1] == '!'))
    {
        for (p = ReadText; (*p != '\0') && (*p != '\r') && (*p != '\n'); ++p)
        {
            *p = ' ';
        }
    }

    return ReadText;
}

void PicocPlatformScanFile(const char *filename) {
    printf("PicocPlatformScanFile:\n%s\n", filename);

    char* SourceStr = PlatformReadFile(filename);

    /* ignore "#!/path/to/picoc" .. by replacing the "#!" with "//" */
    if (SourceStr != NULL && SourceStr[0] == '#' && SourceStr[1] == '!')
    {
        SourceStr[0] = '/';
        SourceStr[1] = '/';
    }

    // char* asrc = "#include <stdio.h>\nprintf(\"Hello world\\n\");\nint Count;\nfor (Count = -5; Count <= 5; Count++)\nprintf(\"Count = %d\\n\", Count);\nvoid main() {}\n\0";

    // TODO: check enough stack
    // if(0x881E0000 - (int)GetStackPtr() < 500000 - filesize*sizeof(unsigned char) - 30000) {
//    asrc = (char*)alloca(filesize*sizeof(unsigned char)+5);
//    asrc[filesize] = '\0';
    printf("PicocParse:\n%s\n", SourceStr);

    PicocParse(filename, SourceStr, strlen(SourceStr), 1, 0, 1);
}