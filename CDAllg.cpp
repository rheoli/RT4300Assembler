// Name      :  CDCAllg.cc
// Version   :  $Id: CDCAllg.cc,v 1.1 1995/12/02 15:25:47 root Exp root $
// Verwendung:  Allgemeine Prozeduren fuer Programm CDCAsm
//
// Copyright (c) 1994-95 by Charlie Development
//

#ifndef _CC_CDCALLG
#define _CC_CDCALLG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Allgemein.h"

BOOL CDCHelp ( void )
{
   printf ( "CDCASM [/?] [/I] Filename\n\n" );
   printf ( "   [/?]      Helpinfo\n" );
   printf ( "   [/I]      Info over implemented RT4300 Operators.\n" );
   printf ( "   [/H]      Program-Code in Hex for EPROM's\n" );
   printf ( "   Filename  Assemblercode File (not required for /?, /I)\n\n" );
   return ( TRUE );
}

BOOL CDDelSpace ( char *pszWort )
{
   while ( *pszWort != '\0' )
   {
      if ( *pszWort == ' ' )
      {
         char *pChar = pszWort;

         while ( *pChar != '\0' )
         {
            *pChar = *(pChar+1);
            pChar++;
         }
      }
      if ( *pszWort != ' ' )
         pszWort++;
   }
   return ( TRUE );
}
    
WORD hoch ( WORD wBasis, BYTE bExponent )
{
   WORD wResult = 1;
   BYTE i;

   for ( i = 1; i <= bExponent; i++ )
   {
      wResult *= wBasis;
   }
   return ( wResult );
}

BOOL HexAscToInt ( char *pszZahl, WORD *pwZahl )
{
   BYTE bFaktor = strlen ( pszZahl )-1;

   *pwZahl = 0;

   while ( *pszZahl != '\0' )
   {
      if ( *pszZahl >= '0' && *pszZahl <= '9' )
         *pszZahl -= '0';
      else
      {
         if ( *pszZahl >= 'A' && *pszZahl <= 'F' )
         {
            *pszZahl -= 'A';
            *pszZahl += 10;
         }
         else
         {
            return ( FALSE );
         }
      }
   
      *pwZahl += *pszZahl * hoch(16,bFaktor);
      bFaktor--;
      pszZahl++;
   }
   return ( TRUE );
}

#endif // _CC_CDCALLG
