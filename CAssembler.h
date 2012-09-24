// Name      :  CAssembler.h (Headerfile)
// Version   :  $Id$
// Verwendung:  Assemblieren von RT4300-Befehlen
//
// Copyright (c) 1996 by Stiofan Toggweiler
//

#include "Allgemein.h"
#include "COpcode.h"
#include "CAss.h"
#include "CLabel.h"

#ifndef _H_CASSEMBLER
#define _H_CASSEMBLER

class CAssembler
{
 private:
   COpcode opcPrgr;
   
 public:
   BOOL AssembleCommands ( CAss &assCode, CLabel &labCode );
//   BOOL ImplementedCommands ( void );
   BOOL WriteListeProgram ( char *pszFilename );   
   BOOL WriteIntelHexProgram ( char *pszFilename );   
};
  
#endif  // _H_CASSEMBLER     