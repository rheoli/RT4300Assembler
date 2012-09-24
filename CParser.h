/************************************************************************
    
    CParser.h (Header) - Class to parse an assembler-codefile
    
    Copyright (C) 1996  by Steaphan Toggweiler

    $Id$

****************************************************************************/

#ifndef _H_CPARSER
#define _H_CPARSER

#include <stdio.h>
#include <stdlib.h>
#include "Allgemein.h" 
#include "CAss.h"
#include "CLabel.h"

class CParser
{
 private:
      
 public:
 
   // Konstruktor: 
   CParser ( void );

   // Destruktor: 
   ~CParser ( void );
   
   // Parser zum aufteilen der Kommandos
   BOOL ParseFile ( char *pszFilename, CAss &assCode, CLabel &labCode );

};

#endif // _H_CPARSER