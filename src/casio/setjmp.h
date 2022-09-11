/*------------------------------------------------------*/
/* SH SERIES C Compiler Ver. 1.0                        */
/* Copyright (c) 1992 Hitachi,Ltd.                      */
/* Licensed material of Hitachi,Ltd.                    */
/*------------------------------------------------------*/
/***********************************************************************/
/* SPEC;                                                               */
/*  NAME = setjmp.h :                                ;                 */
/*                                                                     */
/*  FUNC = this module do the following functions    ;                 */
/*                                                                     */
/*  CLAS = UNIT;                                                       */
/*                                                                     */
/* END;                                                                */
/***********************************************************************/
#pragma once

#ifndef _SETJMP
#define _SETJMP
typedef int jmp_buf[38];
//SH4
typedef int jmp_buf_a[54];

#ifdef __cplusplus
extern "C" {
#endif
int setjmp(jmp_buf env);
void longjmp(jmp_buf env, int val);
//#ifdef _SH4
//extern int setjmp_a(jmp_buf);
//extern void longjmp_a(jmp_buf, int);
//#endif

//extern volatile int _errno;

#ifdef __cplusplus
}
#endif

extern int setjmp(jmp_buf env);

#ifndef SEQERR
#define SEQERR     1108
#endif

#endif