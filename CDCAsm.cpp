/************************************************************************
    
    CDCAsm.cc - Assembler to assemble RT4300 Assembler-Code
    
    Copyright (C) 1994-96  by Stiofan Toggweiler

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

****************************************************************************/

const char *version = "$Id$";

#define CD_PROGNAME  "Cross Assembler for RT4300"
#define CD_VERSION   "Version 1.01Beta"
#define CD_JAHR      "1994-96"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Allgemein.h"
#include "CDCAllg.h"
#include "CParser.h"
#include "CAssembler.h"
#include "CAss.h"
#include "CCopyright.h"

#ifndef _CC_CDCASM
#define _CC_CDCASM

CCopyright crcTitel ( CD_PROGNAME, CD_VERSION, CD_JAHR );

BOOL main ( int argc, char *argv[] )
{
   CParser     cParser;
   CAss        assCode;   
   CLabel      labCode;
   CAssembler  assAssembler;   
   BOOL        fHexCodeOut = FALSE;
   char        szArg[5];   
   char        szASM[50];
   char        szInput[100];
   char        szOutput[100];
   WORD        wLinie;
   int         i;

   {
      BYTE bSchleife;
      BYTE bArg = 0;
      BOOL fFound = FALSE;

      for ( bSchleife = 1; bSchleife < argc; bSchleife++ )
      {
         if ( strchr ( argv[bSchleife], '-' ) != NULL ||
              strchr ( argv[bSchleife], '/' ) )
         {
            szArg[bArg] = argv[bSchleife][1];
            bArg++;
         }
         else
            if ( !fFound )
            {
               fFound = TRUE;
               strcpy ( szInput, argv[bSchleife] );
            }
      }
      szArg[bArg] = '\0';

      if ( !fFound && 
           (strchr(szArg, '?')==NULL&&strchr(szArg, 'I')==NULL) )
      {
         printf ( "CDCASM - Filename required.\n\n" );
         return ( FALSE );
      }
   }

   if ( strchr ( szArg, '?' ) )
   {
      CDCHelp ();
      
      return ( TRUE );
   }

   if ( strchr ( szArg, 'I' ) || strchr ( szArg, 'i' ) )
   {
//      pcpuAssembler->ImplementedCommands ();
      
      return ( TRUE );
   }
   
   if ( strchr ( szArg, 'H' ) || strchr ( szArg, 'h' ) )
   {
      fHexCodeOut = TRUE;
   }

   strcpy ( szOutput, szInput );

// Ab Hier neu !!!

   cParser.ParseFile ( szInput, assCode, labCode );
   
   labCode.TestLabel ();
   
   assAssembler.AssembleCommands ( assCode, labCode );

   if ( fHexCodeOut )
   {
      assAssembler.WriteIntelHexProgram ( szOutput );
   }
   else 
      assAssembler.WriteListeProgram ( szOutput );

   return ( TRUE );
}

#endif  // _CC_CDCASM