//
// Created by Phoebe on 11/09/2022.
//
/*------------------------------------------------------*/
/* SH SERIES C Compiler Ver. 1.0                        */
/* Copyright (c) 1992 Hitachi,Ltd.                      */
/* Licensed material of Hitachi,Ltd.                    */
/*------------------------------------------------------*/
/***********************************************************************/
/* SPEC;                                                               */
/*  NAME = stdio : header file for standard I/O function ;             */
/*                                                                     */
/*  FUNC = this header file do the following functions;                */
/*         (1) file entry table define;                                */
/*         (2) I/O macro define;                                       */
/*         (3) symbol define;                                          */
/*  CLAS = UNIT;                                                       */
/*                                                                     */
/* END;                                                                */
/***********************************************************************/
#ifndef _STDIO
#define _STDIO

#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define _NFILE 20
#define SYS_OPEN 20
typedef struct _iobuf {
    unsigned char *_bufptr;          /* buffer pointer              */
    long _bufcnt;          /* buffer count                */
    unsigned char *_bufbase;         /* buffer base pointer         */
    long _buflen;          /* buffer length               */
    char _ioflag1;         /* I/O control flag 1          */
    char _ioflag2;         /* I/O control flag 2          */
    char _iofd;
} _iob[_NFILE];

extern volatile int _errno;

typedef struct _iobuf FILE;             /* define FILE of file-stream    */

/* define function of prototype  */

#ifdef __cplusplus
}
#endif

#define _IOFBF 1                        /* define _IOFBF of full buffering */
#define _IOLBF 2                        /* define _IOLBF of line buffering */
#define _IONBF 3                        /* define _IONBF of non buffering  */

//#define SEEK_SET 0                      /* allocate top position */
//#define SEEK_CUR 1                      /* allocate current position */
//#define SEEK_END 2                      /* allocate bottom position */

#define BUFSIZ 512                      /* default buffer size */

/* error number define */
//#ifndef EBADF
//#define EBADF  1302                     /* I/O operation error */
//#endif

#ifndef PTRERR
#define PTRERR 1106                     /* fp null */
#endif

#ifndef ECSPEC
#define ECSPEC 1304                     /* format err */
#endif

#ifndef NOTOPN
#define NOTOPN 1300                     /* file not open */
#endif

/* I/O flags for _ioflag1      */
#define _IOREAD    1                    /* only read or update read    */
#define _IOWRITE   2                    /* only write or update write  */
#define _IORW      4                    /* update file                 */
#define _IOUNBUF   8                    /* unbffering I/O              */
#define _IOBGBUF  16                    /* automatic buffer allocate   */
#define _IOEOF    32                    /* end of file                 */
#define _IOERR    64                    /* I/O error                   */
#define _IOBIN   128                    /* binaly file                 */
#define _UNGTC     1                    /* ungetc issued (_ioflag2)    */
#define _IOLINBUF  2                    /* line buffering              */

#define EOF     (-1)
#define _EOL    (0X0A)                  /* end of line                 */

#define stdin       (&_iob[0])          /* standard input file */
#define stdout      (&_iob[1])          /* standard output file */
#define stderr      (&_iob[2])          /* standard error output file */

#define getc(fp) ((fp)->_ioflag2&=~_UNGTC,(((fp)->_ioflag1&(_IORW|_IOWRITE))==\
 (_IORW|_IOWRITE))&&(fp)->_bufcnt==(fp)->_buflen?(_fillbuf(fp)):\
 --(fp)->_bufcnt>=0 ?((int)*(fp)->_bufptr++):_fillbuf(fp))
#define putc(x,fp) (((((fp)->_ioflag1&_IORW)!=0&&((fp)->_ioflag1&_IOWRITE)==0)\
 ?_putcsub(fp):(void)0),((((fp)->_bufcnt==0)||((((fp)->_ioflag2&_IOLINBUF)!=0)\
 && ((fp)->_bufbase!=(fp)->_bufptr)&&(*((fp)->_bufptr-1)==_EOL)))\
 ?_flshbuf((int)(x),(fp)):\
 (((fp)->_bufcnt--),((int)(*(fp)->_bufptr++=(unsigned char)(x))))))
#define getchar()   getc(stdin)
#define putchar(x)  putc(x,stdout)
#define feof(fp)    ((fp)->_ioflag1&_IOEOF)
#define ferror(fp)  ((fp)->_ioflag1&_IOERR)
#define clearerr(fp) ((void)((fp)->_ioflag1&=~(_IOEOF|_IOERR)))

#endif
