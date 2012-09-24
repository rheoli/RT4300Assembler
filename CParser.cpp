/************************************************************************
    
    CParser.cc - Class to parse an assembler-codefile
    
    Copyright (C) 1996  by Steaphan Toggweiler

    $Id$

****************************************************************************/

#ifndef _CC_CPARSER
#define _CC_CPARSER

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Allgemein.h" 
#include "CParser.h"
#include "CAss.h"
#include "CLabel.h"

// Konstruktor: 
CParser::CParser ( void )
   {
   }

// Destruktor: 
CParser::~CParser ( void )
   {
   }
   
// Parser zum aufteilen der Kommandos
BOOL CParser::ParseFile ( char *pszFilename, CAss &assCode, CLabel &labCode )
   {
      FILE *fFile;
      char szCode[100];
      WORD wSrcLine = 0;
      
      fFile = fopen ( pszFilename, "rt" );
      if ( fFile == NULL )
      {
         printf ( "CParser - Can\'t open file %s.\n", pszFilename );
         exit ( 1 );
      }
   
      while ( !feof ( fFile ) && fgets ( szCode, 99, fFile ) )
      {         
         char *pCommand = szCode;
         char *pComment;
         char *pDest, *pDest2;
         char *pSrc, *pSrc2;
         char *pLabel;
         int  i;

         wSrcLine++;

         szCode[strlen(szCode)-1] = '\0';

         pComment = strchr ( pCommand, ';' );
         if ( pComment != NULL )
            *pComment = '\0';
         
         while ( *pCommand == ' ' )
            pCommand++;

         if ( strlen ( pCommand ) < 1 )
            continue;         

         for ( i = 0; i < strlen(pCommand); i++ )
            *(pCommand+i) = toupper ( *(pCommand+i) );                  

         // Wenn die Linie ein Label ist
         pLabel = strchr ( pCommand, ':' );
         if ( pLabel != NULL )
         {
            *pLabel = '\0';
            labCode.AddLabel ( pCommand, assCode.GetCodeAnzahl() );
            
            continue;
         }
         
         // Testen wieviele Parameter vorhanden sind
         pDest = strchr ( pCommand, ' ' );
         if ( pDest == NULL )
         {
            assCode.AddCode ( wSrcLine, pCommand, 0, NULL, NULL );
            continue;
         }
         
         *pDest = '\0';
         pDest++;

         while ( *pDest == ' ' )
            pDest++;

         pSrc = strchr ( pDest, ',' );               
         if ( pSrc == NULL )
         {
            // Ist Befehl ein Jump-Befehl ?            
            if ( *pCommand == 'J' )
            {
               WORD wID;
               char szTemp[30];
               
               labCode.AddJump ( pDest, wID );
               sprintf ( szTemp, "L%05d", wID );
               
               assCode.AddCode ( wSrcLine, pCommand, 1, szTemp, NULL );
            }
            else
            {
               char *pSpc = strchr ( pDest, ' ' );
            
               if ( pSpc != NULL )
                  *pSpc = '\0';            
               
               assCode.AddCode ( wSrcLine, pCommand, 1, pDest, NULL );
            }
            
            continue;
         }

         *pSrc = '\0';
         pSrc++;
         
         while ( *pSrc == ' ' )
            pSrc++;
            
         pDest2 = strchr ( pDest, ' ' );            
         if ( pDest2 != NULL )
            *pDest2 = '\0';
          
         pSrc2 = strchr ( pSrc, ' ' );            
         if ( pSrc2 != NULL )
            *pSrc2 = '\0';
         
         assCode.AddCode ( wSrcLine, pCommand, 2, pDest, pSrc );
      }

      fclose ( fFile );

      return ( TRUE );
   }

#endif // _CC_CPARSER