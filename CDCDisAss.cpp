// Name      :  CDCDisAss.cc 
// Version   :  $Id$
// Verwendung:  RT4300-Disassembler
//
// Copyright (c) 1996 by Stiofan Toggweiler
//

#define CD_PROGNAME  "Disassembler for RT4300"
#define CD_VERSION   "Version 1.00Concept"
#define CD_JAHR      "1996"


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Allgemein.h"
#include "RT4300Def.h"
#include "CDisAss.h"
#include "CCopyright.h"

CCopyright crcTitel ( CD_PROGNAME, CD_VERSION, CD_JAHR );

int main ( int argc, char *argv[] )
{
   if ( argc == 2 )
   {
      FILE *pfDis;
      int  iCode = 0;
      CDisAss daDecode;
      int    iPar1;
      int    iPar2;
      char    szString[100];

      pfDis = fopen ( argv[1], "rt" );
      if ( pfDis == NULL )
      {
         printf ( "CDCDISASS - Kann File %s nicht öffnen\n", argv[1] );
         exit ( 1 );
      }

      printf ( "Disassemblierter Code des RT4300:\n\n" );

      while ( !feof ( pfDis ) )
      {
         BYTE bParam;

         if ( fscanf ( pfDis, "%x", &iCode ) <= 0 )
         {
            exit ( 1 );
         }
      
         daDecode.GetParamAnz ( iCode, bParam );
         
         if ( bParam > 0 )
         {
            if ( fscanf ( pfDis, "%x", &iPar1 ) <= 0 )
            {
               printf ( "CDCDISASS - Fehler beim Lesen (LINE %d)\n", __LINE__-2 );
               exit ( 1 );
            }
         }
         else
         {
            iPar1 = 0;
         }

         if ( bParam > 1 )
         {
            if ( fscanf ( pfDis, "%x", &iPar2 ) <= 0 )
            {
               printf ( "CDCDISASS - Fehler beim Lesen (LINE %d)\n", __LINE__-2 );
               exit ( 1 );
            }
         }
         else
         {
            iPar2 = 0;
         }

         daDecode.GetString ( iCode, iPar1, iPar2, szString );

         printf ( "%s\n", szString );
      }

      fclose ( pfDis );
   }
   else
   {
      CDisAss daDecode;
      int    bCode;
      int    bPar1;
      int    bPar2;
      BYTE   bParam;
      char    szString[100];

      for ( ;; )
      {
         printf ( "Bitte Code eingeben: " );
      scanf ( "%x", &bCode );

      if ( bCode == 0xFF )
         break;

      daDecode.GetParamAnz ( bCode, bParam );

      printf ( "  Parameteranzahl: %d\n", bParam );

      if ( bParam > 0 )
      {
         printf ( "Bitte Par1 eingeben: " );
         scanf ( "%x", &bPar1 );
      }
      else
      {
         bPar1 = 0;
      }

      if ( bParam > 1 )
      {
         printf ( "Bitte Par2 eingeben: " );
         scanf ( "%x", &bPar2 );
      }
      else
      {
         bPar2 = 0;
      }
      
         daDecode.GetString ( bCode, bPar1, bPar2, szString );

         printf ( "\nBefehl: %s\n\n", szString );
      }
   }

   return ( 0 );
}
      


  