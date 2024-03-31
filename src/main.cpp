
#include "picoc/picoc.h"
#include <alloca.h>
#include <appdef.hpp>
#include <cstring>
#include <ctype.h>
#include <fcntl.h>
#include <malloc.h>
#include <sdk/calc/calc.hpp>
#include <sdk/os/debug.hpp>
#include <sdk/os/file.hpp>
#include <sdk/os/input.hpp>
#include <sdk/os/lcd.hpp>
#include <sdk/os/mem.hpp>
#include <sdk/os/string.hpp>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define HEAP_SIZE (16 * 1024)

/*
 * Fill this section in with some information about your app.
 * All fields are optional - so if you don't need one, take it out.
 */
APP_NAME("Pico C")
APP_DESCRIPTION("very small C interpreter")
APP_AUTHOR("Pho3, based on Zik Saleeba")
APP_VERSION("1.0.2")

extern "C" void PlatformExit(int RetVal) {

    while (true) {
    uint32_t key1, key2;  // First create variables
    getKey(&key1, &key2); // then read the keys
    if (testKey(
            key1, key2,
            KEY_CLEAR)) { // Use testKey() to test if a specific key is pressed
      break;
    }
  }

  calcEnd();
  exit(RetVal);
}

extern "C" int __attribute__((section(".bootstrap.text"))) main(void) {
  calcInit(); // backup screen and init some variables

  fillScreen(color(45, 45, 45));

  char filename[] = "\\fls0\\pico.c";

  // char *SourceStr = ReadFileIntoString(filename);

  // Do something with SourceStr
  // printf("File contents:\n%s\n", SourceStr);

  fputs("PICO C Start\n", stdout);

  int StackSize = 16 * 1024;

  PicocInitialise(StackSize);
  fputs("PicocInitialise -- OK\n", stdout);

  // if (PicocPlatformSetExitPoint())
  // {
  //     PicocCleanup();
  //     // setmGetKeyMode(MGETKEY_MODE_NORMAL);
  //     return PicocExitValue;
  // }

  fputs("<PicocParse>\n", stdout);
  PicocPlatformScanFile(filename);
  // PicocParse("nofile", SourceStr, strlen(SourceStr), TRUE, TRUE, FALSE);
  fputs("</PicocParse>\n", stdout);
  // PicocParseInteractive();

  PicocCleanup();
  // Mem_Free(SourceStr); // Free the allocated memory when done

  fputs("PicocCleanup -- OK\n", stdout);

  PlatformExit(EXIT_SUCCESS);
}
