// Name      :  CDisAss.h (Header)
// Version   :  $Id$
// Verwendung:  Disassembler Klasse
//
// Copyright (c) 1996 by Stiofán Toggweiler
//

#ifndef _H_CDISASS
#define _H_CDISASS

#include "Allgemein.h"
#include "RT4300Def.h"

class CDisAss
{
 private:
   WORD wAddrPointer;

 public:
   CDisAss ( void )
   {
      wAddrPointer = 0;
   }

   BOOL GetParamAnz     ( BYTE _bCode, BYTE &_bParam );
   BOOL GetRegisterName ( BYTE _bReg, char *_pszReg );
   BOOL GetString       ( BYTE _bCode, BYTE _bPar1, BYTE _bPar2, char *pszDisAss );

};

#endif // _H_CDISASS
