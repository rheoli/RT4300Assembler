// Name      :  CDCAllg.h (Headerfile)
// Version   :  $Id: CDCAllg.h,v 1.1 1995/12/02 15:27:59 root Exp root $
// Verwendung:  Allgemeine Prozeduren fuer Programm CDCAsm
//
// Copyright (c) 1994-95 by Charlie Development
//

#ifndef _H_CDCALLG
#define _H_CDCALLG

#include <stdio.h>
#include "Allgemein.h"

#define PARAM_SOURCE       0x00
#define PARAM_DESTINATION  0x01

struct PARAM
{
   BYTE bBefehl;
   BOOL fJump;
   BYTE bParamArt[2];
   BYTE bParamLO[2];
   BYTE bParamHI[2];
};

BOOL CDCHelp ( void );

BOOL CDDelSpace ( char *pszWort );
    
WORD hoch ( WORD wBasis, BYTE bExponent );

BOOL HexAscToInt ( char *pszZahl, WORD *pwZahl );

#endif // _H_CDCALLG
