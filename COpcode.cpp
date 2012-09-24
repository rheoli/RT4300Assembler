// Name      :  COpcode.cc
// Version   :  $Id: COpcode.cc,v 1.1 1995/12/02 15:25:47 root Exp root $
// Verwendung:  Klasse zur Verwaltung der Assembler-Opcode's
//
// Copyright (c) 1994-96 by Stiofan Toggweiler
//

#ifndef _CC_COPCODE
#define _CC_COPCODE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "COpcode.h"
#include "Allgemein.h"
#include "RT4300Def.h"

COpcode::COpcode ( void )
{
   potOpcode = (OPCODE_T *) malloc ( sizeof(OPCODE_T)*3 );
   if ( potOpcode == NULL )
   {
      printf ( "COpcode - Nicht genug Speicher.\n" );
      exit ( 1 );
   }

   wCodeAnz   = 0;
}

WORD COpcode::GetPos ( void )
{
   return ( wCodeAnz );
}

BOOL COpcode::AddOpcode ( BYTE _bCode )
{
   return ( AddOpcode ( _bCode, FALSE ) );
}   

BOOL COpcode::AddOpcode ( BYTE _bCode, BOOL _fJump )
{
   potOpcode[wCodeAnz].bOpcode = _bCode;
   potOpcode[wCodeAnz].fJump   = _fJump;
   
   potOpcode = (OPCODE_T *) realloc ( potOpcode, sizeof(OPCODE_T)*(wCodeAnz+2) );   
   if ( potOpcode == NULL )
   {
      printf ( "COpcode - Nicht genug Speicher.\n" );
      exit ( 1 );
   }
       
   wCodeAnz++;
   
   return ( TRUE );
}

BOOL COpcode::UpdateJump ( CLabel &labCode )
{
   int i;
   
   for ( i = 0; i < wCodeAnz; i++ )
   {
      
      // Wenn Jump-Befehl gefunden
      if ( potOpcode[i].fJump )
      {
         WORD wID = potOpcode[i+2].bOpcode*0x10+potOpcode[i+1].bOpcode;
         WORD wAddr;
         
         if ( !labCode.GetLabel ( wID, wAddr ) )
         {
            printf ( "COpcode - Internal Error COPC::1000.\n" );
            exit ( 1 );
         }
         
         potOpcode[i+1].bOpcode = wAddr%0x100;
         potOpcode[i+2].bOpcode = wAddr/0x100;
         
         i += 2;
      }
   }
   
   return ( TRUE );
}

BOOL COpcode::WriteListeOpcode ( char *pszName )  
{
   FILE *fFile;
   char *pChar;
   WORD wWo = 0;

      pChar = strchr ( pszName, '.' );
      if ( pChar == NULL )
         strcat ( pszName, ".shx" );
      else
         strcpy ( pChar, ".shx" );
   
      fFile = fopen ( pszName, "wt" );
      if ( fFile == NULL )
      {
         printf ( "COpcode - Can't create File %s.\n", pszName );
         return ( FALSE );
      }

      while ( wWo < wCodeAnz )
      {
         WORD ii;

 //        fprintf ( fFile, "%04X:", wWo );

         for ( ii = 0; ii < 16 && wWo < wCodeAnz; ii++ )
         {
            if ( ii == 0 )
               fprintf ( fFile, "%02X", potOpcode[wWo].bOpcode );
            else   
               fprintf ( fFile, " %02X", potOpcode[wWo].bOpcode );
            wWo++;
         }
         fprintf ( fFile, "\n" );
      }
      fclose ( fFile );

      printf ( "Program written to: %s\n\n", pszName );

      return ( TRUE );
   }
   
BOOL COpcode::WriteIntelHexOpcode ( char *pszName )  
{
   FILE *fFile;
   char *pChar;
   WORD wWo = 0;
   WORD wZeichen = 0;
   int  j;

   pChar = strchr ( pszName, '.' );
   if ( pChar == NULL )
      strcat ( pszName, ".hex" );
   else
      strcpy ( pChar, ".hex" );

   fFile = fopen ( pszName, "wt" );
   if ( fFile == NULL )
   {
      printf ( "COpcode - Can't create File %s.\n", pszName );
      exit ( 1 );
   }

   for ( j = 0; j < 9; j++ )
   {
      WORD  ii;         
      int   iChecksum = 0x20+(wWo/16)+(wWo-((wWo/16)*16));

      fprintf ( fFile, ":20%02X%02X00", (BYTE)(wWo/0xff), (BYTE)(wWo%0xff) );

      for ( ii = 0; ii < 0x20; ii++ )
      {
         if ( wWo >= wCodeAnz )
         {
            fprintf ( fFile, "00" );
         }
         else
         {
            fprintf ( fFile, "%02X", potOpcode[wWo].bOpcode );
            iChecksum += potOpcode[wWo].bOpcode;
         }
         wWo++;
      }
      fprintf ( fFile, "%02X\n", 0x100-(iChecksum%0x100) );
   }
   fprintf ( fFile, ":00000001FF\n" );
   fclose ( fFile );
   
   printf ( "Program written to: %s\n\n", pszName );   

   return ( TRUE );
}   

#endif // _CC_COPCODE