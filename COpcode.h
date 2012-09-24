// Name      :  COpcode.h (Headerfile)
// Version   :  $Id: COpcode.h,v 1.1 1995/12/02 15:27:59 root Exp root $
// Verwendung:  Klasse zur Verwaltung der Assembler-Opcode's
//
// Copyright (c) 1994-96 by Stiofan Toggweiler
//

#ifndef _H_COPCODE
#define _H_COPCODE

#include <stdio.h>
#include <string.h>
#include "Allgemein.h"
#include "CLabel.h"

struct OPCODE_T
{
   BYTE bOpcode;
   BOOL fJump;
};

class COpcode
{
 private:
   OPCODE_T *potOpcode;
   WORD     wCodeAnz;
   
 public:
   COpcode ( void );

   BOOL AddOpcode ( BYTE bCode, BOOL fJump );
   BOOL AddOpcode ( BYTE bCode );
   WORD GetPos ( void );

   BOOL UpdateJump ( CLabel &labCode );

   BOOL WriteListeOpcode ( char *pszName );
   BOOL WriteIntelHexOpcode ( char *pszName );
};

#endif // _H_COPCODE
