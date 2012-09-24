/************************************************************************
    
    Allgemein.h (Header) - Allgemeine Definitionen fuer alle Module
    
    Copyright (C) 1995-96  by Steaphan Toggweiler

    "$Id: Allgemein.h,v 1.3 1996/01/17 20:54:30 develadm Exp develadm $"

****************************************************************************/

#ifndef _H_ALLGEMEIN
#define _H_ALLGEMEIN
             
#define LOBYTE(w)           ((BYTE)(w))
#define HIBYTE(w)           ((BYTE)(((WORD)(w) >> 8) & 0xFF))

// Boolsche Werte
#define FALSE 0
#define TRUE  1

typedef unsigned short WORD;
typedef unsigned char  BYTE;
typedef BYTE           BOOL;
typedef unsigned int   LONG;

// Maximum und Minimum von Zahlen bestimmen
#define	min(a,b)	((a) < (b) ? (a) : (b))
#define	max(a,b)	((a) > (b) ? (a) : (b))

#endif /* _H_ALLGEMEIN */
