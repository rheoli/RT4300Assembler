// Name      :  CDisAss.cc
// Version   :  $Id$
// Verwendung:  Disassembler Klasse
//
// Copyright (c) 1996 by Stiofán Toggweiler
//

#ifndef _CC_CDISASS
#define _CC_CDISASS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Allgemein.h"
#include "RT4300Def.h"
#include "CDisAss.h"
#include "CKeywords.h"

BOOL CDisAss::GetParamAnz ( BYTE _bCode, BYTE &_bParam )
   {
      _bParam = 0;

	  if ( (_bCode%0x04) == 3 )
	     _bParam++;

      if ( ((_bCode%0x10)/0x04) == 3 )
	     _bParam++;
      
      return ( TRUE );
   }

BOOL CDisAss::GetRegisterName ( BYTE _bReg, char *_pszReg )
   {
      switch ( _bReg )
      {
         case 0:
            strcpy ( _pszReg, "R0" );
            break;

         case 1:
            strcpy ( _pszReg, "R1" );
            break;

         case 2:
            strcpy ( _pszReg, "R2" );
            break;

         default:
            strcpy ( _pszReg, "NoReg" );
            return ( FALSE );
      }

      return ( TRUE );
   }


BOOL CDisAss::GetString ( BYTE _bCode, BYTE _bPar1, BYTE _bPar2, char *pszDisAss )
   {
      BYTE      bID;
      BYTE      bParam = _bCode%0x10;
      BYTE      bCmd   = _bCode/0x10;
      CKeywords cKey;
      char      szCmd[10];            
      
      cKey.GetCommand ( (_bCode/0x10), bID );
      cKey.GetString ( bID, szCmd );

      switch ( bCmd )
      {
         case RT4300_JMP_CODE:
         case RT4300_JE_CODE:
         case RT4300_JZ_CODE:
         case RT4300_JNZ_CODE:
         case RT4300_JA_CODE:
         case RT4300_JB_CODE:
         case RT4300_JC_CODE:
         {
            WORD wAddress = (WORD)(_bPar2*0x100)+_bPar1+1;

            sprintf ( pszDisAss, "%04X: %s %04X", wAddrPointer, szCmd, wAddress );
            wAddrPointer += 3;
            return ( TRUE );
         }
         
         // Alle MOV-Befehle und Abarten  
         case RT4300_MOV_CODE:      

            // OUT-Befehl 
            if ( (bParam/0x04) == 2 )
            {
               if ( (bParam%0x04) == 3 )
               {
                  sprintf ( pszDisAss, "%04X: OUT %02X", wAddrPointer, _bPar1 );
                  wAddrPointer += 2;
               }
               else
               {
                  char szReg[10];

                  GetRegisterName ( bParam%0x04, szReg );
                  sprintf ( pszDisAss, "%04X: OUT %s", wAddrPointer, szReg );
                  wAddrPointer++;
               }

               return ( TRUE );
            }

            // IN-Befehl 
            if ( (bParam%0x04) == 2 )
            {
               if ( (bParam/0x04) == 3 )
               {
                  sprintf ( pszDisAss, "%04X: IN %02X", wAddrPointer, _bPar1 );
                  wAddrPointer += 2;
               }
               else
               {
                  char szReg[10];

                  GetRegisterName ( bParam/0x04, szReg );
                  sprintf ( pszDisAss, "%04X: IN %s", wAddrPointer, szReg );
                  wAddrPointer++;
               }

               return ( TRUE );
            }

            // NOP-Befehl
            if ( bParam == 0 || bParam == 5 )
            {
               sprintf ( pszDisAss, "%04X: NOP", wAddrPointer );
               wAddrPointer++;
               return ( TRUE );
            }

            // Normaler MOV-Befehl

            // Mit konstanter Source
            if ( (bParam%0x04) == 3 )
            {
               char szReg[10];

               GetRegisterName ( bParam/0x04, szReg );
               sprintf ( pszDisAss, "%04X: MOV %s, %02X", wAddrPointer, szReg, _bPar1 );
               wAddrPointer += 2;
               return ( TRUE );
            }
            else
            {
               char szRegSrc[10];
               char szRegDest[10];

               GetRegisterName ( bParam%0x04, szRegSrc );
               GetRegisterName ( bParam/0x04, szRegDest );

               sprintf ( pszDisAss, "%04X: MOV %s, %s", wAddrPointer, szRegDest, szRegSrc );
               wAddrPointer++;
            }

            return ( TRUE );

         case RT4300_SUB_CODE:
            if ( (bParam/0x04) == 3 )
            {
               char szReg[10];
               BYTE bBit = 0;

               GetRegisterName ( bParam%0x04, szReg );
               sprintf ( pszDisAss, "%04X: CMP %s, %02X", wAddrPointer, szReg, _bPar1 );
               wAddrPointer += 2;
               return ( TRUE );
            }
            else
            {
               char szRegSrc[10];
               char szRegDest[10];

               GetRegisterName ( bParam%0x04, szRegSrc );
               GetRegisterName ( bParam/0x04, szRegDest );

               sprintf ( pszDisAss, "%04X: %s %s, %s", wAddrPointer, szCmd, szRegDest, szRegSrc );
               wAddrPointer++;
            }
            return ( TRUE );
            

         case RT4300_INC_CODE:
         case RT4300_DEC_CODE:
            {
               char szRegDest[10];

               GetRegisterName ( bParam/0x04, szRegDest );

               sprintf ( pszDisAss, "%04X: %s %s", wAddrPointer, szCmd, szRegDest );
               wAddrPointer++;
            }

            return ( TRUE );
            
         case RT4300_AND_CODE:
            if ( (bParam/0x04) == 3 )
            {
               char szReg[10];

               GetRegisterName ( bParam%0x04, szReg );
               sprintf ( pszDisAss, "%04X: TEST %s, %02X", wAddrPointer, szCmd, szReg, _bPar1 );
               wAddrPointer += 2;
               return ( TRUE );
            }

            // Mit konstanter Source
            if ( (bParam%0x04) == 3 )
            {
               char szReg[10];

               GetRegisterName ( bParam/0x04, szReg );
               sprintf ( pszDisAss, "%04X: %s %s, %02X", wAddrPointer, szCmd, szReg, _bPar1 );
               wAddrPointer += 2;
               return ( TRUE );
            }
            else
            {
               char szRegSrc[10];
               char szRegDest[10];

               GetRegisterName ( bParam%0x04, szRegSrc );
               GetRegisterName ( bParam/0x04, szRegDest );

               sprintf ( pszDisAss, "%04X: %s %s, %s", wAddrPointer, szCmd, szRegDest, szRegSrc );
               wAddrPointer++;
            }

            return ( TRUE );


         case RT4300_ADD_CODE:
         case RT4300_OR_CODE:
         case RT4300_ADC_CODE:
         case RT4300_SBC_CODE:
            // Mit konstanter Source
            if ( (bParam%0x04) == 3 )
            {
               char szReg[10];

               GetRegisterName ( bParam/0x04, szReg );
               sprintf ( pszDisAss, "%04X: %s %s, %02X", wAddrPointer, szCmd, szReg, _bPar1 );
               wAddrPointer += 2;
               return ( TRUE );
            }
            else
            {
               char szRegSrc[10];
               char szRegDest[10];

               GetRegisterName ( bParam%0x04, szRegSrc );
               GetRegisterName ( bParam/0x04, szRegDest );

               sprintf ( pszDisAss, "%04X: %s %s, %s", wAddrPointer, szCmd, szRegDest, szRegSrc );
               wAddrPointer++;
            }

            return ( TRUE );

         default:
            strcpy ( pszDisAss, "Command not found" );
            return ( FALSE );
      }

      printf ( "Internal Error CDisAss::1000\n" );
      exit ( 1 );

      return ( FALSE );
   }

#endif // _CC_CDISASS