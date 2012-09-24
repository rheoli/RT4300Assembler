// Name      :  CKeywords.h (Headerfile)
// Version   :  $Id$
// Verwendung:  CPU-Keywords
//
// Copyright (c) 1996 by Stiofan Toggweiler
//

#ifndef _H_CKEYWORDS
#define _H_CKEYWORDS

#include "Allgemein.h"
#include "RT4300Def.h"

struct COMMANDS
{
   char szCommand[5];
   BYTE bCode;
   BYTE bParam;
   BYTE bType;
};

class CKeywords
{
 public:

   BYTE GetParam      ( BYTE _bID );
   BYTE GetCode       ( BYTE _bID );
   BOOL IsNOP         ( BYTE _bID );
   BOOL IsINOUT       ( BYTE _bID );
   BOOL IsTEST        ( BYTE _bID );
   BOOL Swap          ( BYTE _bID );
   BOOL IsDestParamOK ( BYTE _bID, BYTE _bDest );
   BOOL IsSrcParamOK  ( BYTE _bID, BYTE _bSrc );
   BOOL GetCommand    ( char *_pszCommand, BYTE &_bID );
   BOOL GetCommand    ( BYTE _bCommand, BYTE &_bID );
   BOOL GetString     ( BYTE _bID, char *pszCode );

};

#endif  // _H_CKEYWORDS
