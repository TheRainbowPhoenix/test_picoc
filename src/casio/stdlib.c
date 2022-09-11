//
// Created by Phoebe on 11/09/2022.
//

// External linkage
int errno;


extern void Debug_Printf(int x, int y, int invert, int zero, const char *format, ...);
extern void LCD_Refresh();
extern void calcEnd();
extern void getKey(int *key1, int *key2);

void abort() {
    Debug_Printf(0,0,1,0,"ABORT CALLED\nPress menu key to exit\n");
    LCD_Refresh();
    while(1) {
        int key1, key2;	//First create variables
        getKey(&key1, &key2);	//then read the keys
//        if(testKey(key1, key2, KEY_CLEAR)){ //Use testKey() to test if a specific key is pressed
//            break;
//        }
//        break;
    }
//    calcEnd();
}
