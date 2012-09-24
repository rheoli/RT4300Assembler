// Name      :  CParseParam.h (Headerfile)
// Version   :  $Id$
// Verwendung:  Parameter entschlueseln
//
// Copyright (c) 1996 by Stiofan Toggweiler
//

#ifndef _H_CPARSEPARAM
#define _H_CPARSEPARAM

#include "Allgemein.h"
#include "RT4300Def.h"

struct REGISTERLIST
{
   char szReg[5];
   WORD wReg;
   BYTE bArt;
};

class CParseParam
{
 public:
   BOOL IsJUMP     ( BYTE _bArt );
   BOOL ParseParam ( char *_pszParam, BYTE &_bArt, WORD &_wReg );

};

#endif  // _H_CPARSEPARAM
