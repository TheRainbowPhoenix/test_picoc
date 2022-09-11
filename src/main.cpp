//
// Created by Phoebe on 10/09/2022.
//

#include <stddef.h>
#include <appdef.hpp>
#include <sdk/os/file.hpp>
#include <sdk/os/debug.hpp>
#include <sdk/os/lcd.hpp>
#include <sdk/os/input.hpp>
#include <sdk/calc/calc.hpp>
#include <sdk/os/string.hpp>
#include <sdk/os/mem.hpp>
#include "snek/snek.h"

// #define MAX_ROM_SIZE 0x10000

/*
 * Fill this section in with some information about your app.
 * All fields are optional - so if you don't need one, take it out.
 */
APP_NAME("PicoC")
APP_DESCRIPTION("very small C interpreter")
APP_AUTHOR("Pho3, based on Zik Saleeba")
APP_VERSION("0.0.1-alpha")

void *memcpy(void *dest, const void *src, size_t count);


extern "C"
void main()
{
	calcInit(); //backup screen and init some variables

    fillScreen(color(45,45,45));

    Debug_Printf(0,0,true,0,"PicoC Test !");

//    snek_init();
//    snek_parse();

    //Don't forget to do LCD_Refresh after setPixel(); line(); and triangle();
    LCD_Refresh();

    // define HEAP_SIZE (16*1024)
    PicocInitialise(HEAP_SIZE);

    if (PicocPlatformSetExitPoint())
    {
        PicocCleanup();
        setmGetKeyMode(MGETKEY_MODE_NORMAL);
        return PicocExitValue;
    }

    PicocPlatformScanFile("SourceFileTest")
    //PicocCallMain(argc - ParamCount, &argv[ParamCount]);

    PicocCleanup();

    Debug_Printf(2,2,true,0,"PicocCleanup ! OK");

    //Example for getKey
    while(true){
        uint32_t key1, key2;	//First create variables
        getKey(&key1, &key2);	//then read the keys
        if(testKey(key1, key2, KEY_CLEAR)){ //Use testKey() to test if a specific key is pressed
            break;
        }
    }

	calcEnd();
}

void *memcpy(void *dest, const void *src, size_t count)
{
	for (size_t i = 0; i < count; i = i + 1)
		((uint8_t *) dest)[i] = ((uint8_t *) src)[i];

	return (dest);
}
