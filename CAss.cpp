/************************************************************************
    
    CAss.cc - Speichern von Assembler-Befehlen, die vom Parser
              aus dem File gefiltert werden.
    
    Copyright (C) 1996  by Stiofán Toggweiler

    $Id$

****************************************************************************/

#ifndef _CC_CASS
#define _CC_CASS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Allgemein.h" 
#include "CAss.h"

// Konstruktor: Speicher reservieren und Variable setzen
CAss::CAss ( void )
{
   pasmCode = (ASSEMBLER_T *) malloc ( sizeof(ASSEMBLER_T)*2 );
   if ( pasmCode == NULL )
   {
       printf ( "CAss - Can\'t allocate memory.\n" );
       exit ( 1 );
   }
    
   wAsmAnz = 0; // Noch keine Befehle im Speicher
}

// Destruktor: Speicher freigeben   
CAss::~CAss ( void )
{
   free ( pasmCode );
}
   
// Neuer Befehls-Code addieren
BOOL CAss::AddCode ( WORD _wSrcLine, char *_pszCommand, BYTE _bParam, char *_pszDest, char *_pszSrc )
{
   strncpy ( pasmCode[wAsmAnz].szCommand, _pszCommand, COMMAND_LEN_MAX );
   pasmCode[wAsmAnz].szCommand[COMMAND_LEN_MAX] = '\0';
     
   pasmCode[wAsmAnz].bParameter = _bParam;
   pasmCode[wAsmAnz].wSrcLine   = _wSrcLine;

   // Source Parameter vorhanden
   if ( _pszSrc != NULL )
   {
      strncpy ( pasmCode[wAsmAnz].szSrc, _pszSrc, SRC_LEN_MAX );
      pasmCode[wAsmAnz].szSrc[SRC_LEN_MAX] = '\0';      
   }
   else
   {
      pasmCode[wAsmAnz].szSrc[0] = '\0';
   }
      
   // Destination Parameter vorhanden
   if ( _pszDest != NULL )
   {      
      strncpy ( pasmCode[wAsmAnz].szDest, _pszDest, DEST_LEN_MAX );
      pasmCode[wAsmAnz].szDest[DEST_LEN_MAX] = '\0';
   }
   else
   {
      pasmCode[wAsmAnz].szDest[0] = '\0';
   }
      
   // Neuen Speicher reservieren für weitere Daten
   pasmCode = (ASSEMBLER_T *) realloc ( pasmCode, sizeof(ASSEMBLER_T)*(wAsmAnz+2) );
   if ( pasmCode == NULL )
   {
      printf ( "CAss - Can\'t allocate memory.\n" );
      exit ( 1 );
   }
      
   wAsmAnz++;
      
   return ( TRUE );
}

// Ausgeben der bereits gespeicherten Befehlen auf dem Bildschirm
BOOL CAss::PrintCode ( void )
{
   int i;
  
   printf ( "CAss - Codelist:\n\n" );
      
   for ( i = 0; i < wAsmAnz; i++ )
   {
      printf ( "%2d:  %s %s %s\n", i+1, pasmCode[i].szCommand,
                 pasmCode[i].szDest, pasmCode[i].szSrc );
   }
      
   printf ( "\n" );
      
   return ( TRUE );
}
         
         
         
// Befehlscode an aufrufende Prozedur zurückgeben
BOOL CAss::GetCode ( WORD _wNr, ASSEMBLER_T &_assCode )
{
   if ( _wNr >= wAsmAnz )
   {
      return ( FALSE );
   }
      
   _assCode = pasmCode[_wNr];
      
   return ( TRUE );
}
   
// Anzahl bereits gespeichert Befehlscode ausgeben
WORD CAss::GetCodeAnzahl ( void )
{
   return ( wAsmAnz );
}            

#endif // _CC_CASS