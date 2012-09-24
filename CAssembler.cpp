/************************************************************************
    
    CAssembler.cc - Uebersetzen von Assembler-Befehlen in
                    Binarycode
    
    Copyright (C) 1996  by Stiofán Toggweiler

    $Id$

****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "Allgemein.h"
#include "CAssembler.h"
#include "CKeywords.h"
#include "CParseParam.h"

#ifndef _CC_CASSEMBLER
#define _CC_CASSEMBLER

// von Befehlscode wird Binarycode erstellt
BOOL CAssembler::AssembleCommands ( CAss &assCode, CLabel &labCode )
{
   int         i;
   CKeywords   keyRT4300;   // Reference auf RT4300 Befehle
   CParseParam parParam;    // Parameter entschlüsseln
   
   for ( i = 0; i < assCode.GetCodeAnzahl(); i++ )
   {
      ASSEMBLER_T aBefehl;
      BYTE        bID;
      
      BYTE        bSrcArt = 0;
      WORD        wSrcReg = 0;
      BYTE        bDestArt = 0;
      WORD        wDestReg = 0;
      BYTE        bOpcDest = 0;
      BYTE        bOpcSrc  = 0;
      BYTE        bOpcExtra = 0;
      WORD        wLabID;
      
      assCode.GetCode ( i, aBefehl ); // Befehl von Zeile i holen
      
      // Befehl in Befehlsliste suchen
      if ( !keyRT4300.GetCommand ( aBefehl.szCommand, bID ) )
      {
         printf ( "CAssembler - Befehl %s nicht im Befehlsatz. (LINE: %d)\n", aBefehl.szCommand, aBefehl.wSrcLine );
         exit ( 1 );
      }
      
      // Parameteranzahl überprüfen ( zu viele Parameter )
      if ( aBefehl.bParameter > keyRT4300.GetParam(bID) )
      {
         printf ( "CAssembler - Zu viele Parameter angegeben. (LINE %d)\n", aBefehl.wSrcLine );
         exit ( 1 );
      }

      // Parameteranzahl überprüfen ( zu wenige Parameter )         
      if ( aBefehl.bParameter < keyRT4300.GetParam(bID) )
      {
         printf ( "CAssembler - Zu wenige Parameter angegeben. (LINE %d)\n", aBefehl.wSrcLine );
         exit ( 1 );
      }

      // Destinationsparameter auf Richtigkeit überprüfen
      if ( keyRT4300.GetParam(bID) > 0 )
      {
         if ( !parParam.ParseParam ( aBefehl.szDest, bDestArt, wDestReg ) )
         {
            printf ( "CAssembler - Befehl hat falscher Destinationparameter. (LINE %d)\n", aBefehl.wSrcLine );
            exit ( 1 );
         }
         
         // Source-Parameter auf Null setzen, im Falle, dass
         // dieser Parameter nicht vorhanden ist.
         bSrcArt = 0;
         wSrcReg = 0;
      }

      // Source-Parameter auf Richtigkeit überprüfen
      if ( keyRT4300.GetParam(bID) > 1 )
      {
         if ( !parParam.ParseParam ( aBefehl.szSrc, bSrcArt, wSrcReg ) )
         {
            printf ( "CAssembler - Befehl hat falscher Sourceparameter. (LINE %d)\n", aBefehl.wSrcLine );
            exit ( 1 );
         }
      }      
      
      // Ist der aktuelle Befehlscode ein Label
      if ( labCode.IsLabel ( i, wLabID ) )
      {
         // Adresse in Labelmodul eintragen
         labCode.SetAddress ( wLabID, opcPrgr.GetPos () );
      }      
      
      // NOP Befehl
      if ( keyRT4300.IsNOP(bID) )
      {
         // bOpcDest = 0x00;
         // bOpcSrc  = 0x00;
         
         opcPrgr.AddOpcode ( keyRT4300.GetCode(bID)*0x10 );
         
         continue;  // nächster Befehl
      }

      // Jump-Befehle
      if ( parParam.IsJUMP(bDestArt) )
      {
         // bOpcDest = 0x03;
         // bOpcSrc  = 0x03;
         
         opcPrgr.AddOpcode ( (keyRT4300.GetCode(bID)*0x10)+0x0F, TRUE );
         opcPrgr.AddOpcode ( wDestReg%0x100 );
         opcPrgr.AddOpcode ( wDestReg/0x100 );
         
         continue;  // nächster Befehl
      }

      // Source-Parameter überprüfen auf Richtigkeit
      if ( !keyRT4300.IsSrcParamOK ( bID, bSrcArt ) )
      {
         printf ( "CAssembler - Source-Parameter nicht zugelassen. (LINE %d)\n", aBefehl.wSrcLine );
         exit ( 1 );
      }
      
      // Detsinationsparameter überprüfen auf Richtigkeit
      if ( !keyRT4300.IsDestParamOK ( bID, bDestArt ) )
      {
         printf ( "CAssembler - Dest-Parameter nicht zugelassen. (LINE %d)\n", aBefehl.wSrcLine );
         exit ( 1 );
      }
      
      // Wenn TEST Befehl
      if ( keyRT4300.IsTEST(bID) )
      {
         wSrcReg = 2 << wSrcReg;
      }
      
      // IN- oder OUT-Befehl
      if ( keyRT4300.IsINOUT(bID) )
      {
         wSrcReg = RT4300_REG_R2_CODE;
         bSrcArt = CPU_REGISTER;
      }      
      
      // Befehle Swappen
      if ( keyRT4300.Swap(bID) )
      {
         WORD wTemp = wDestReg;
         BYTE bTemp = bDestArt;
         
         wDestReg = wSrcReg;
         bDestArt = bSrcArt;
         
         wSrcReg = wTemp;
         bSrcArt = bTemp;         
      }                  
      
      if ( (bDestArt == CPU_NUMBER) && (bSrcArt == CPU_NUMBER) )
      {
         printf ( "CAssembler - Parameter <konst>, <konst> nicht moeglich. (LINE %d)\n", aBefehl.wSrcLine );
         exit ( 1 );
      }            
      
      if ( bDestArt == CPU_NUMBER )
      {
         bOpcDest  = 0x03;
         bOpcSrc   = (BYTE)wSrcReg;
         bOpcExtra = (BYTE)wDestReg;
      }
      else
      {
         if ( bSrcArt == CPU_NUMBER )
         {
            bOpcDest  = (BYTE)wDestReg;
            bOpcSrc   = 0x03;
            bOpcExtra = (BYTE)wSrcReg;
         }
         else
         {
            bOpcDest = (BYTE)wDestReg;
            bOpcSrc  = (BYTE)wSrcReg;
         }
      }
      
      opcPrgr.AddOpcode ( (keyRT4300.GetCode(bID)*0x10)+(bOpcDest*0x04)+bOpcSrc );
      
      if ( bSrcArt == CPU_NUMBER || bDestArt == CPU_NUMBER )
      {
         opcPrgr.AddOpcode ( bOpcExtra );               
      }
   }
   
   opcPrgr.UpdateJump ( labCode );

   return ( TRUE );
}         

BOOL CAssembler::WriteIntelHexProgram ( char *pszFilename )
{
   return ( opcPrgr.WriteIntelHexOpcode ( pszFilename ) );
}

BOOL CAssembler::WriteListeProgram ( char *pszFilename )
{
   return ( opcPrgr.WriteListeOpcode ( pszFilename ) );
}


#endif  // _CC_CASSEMBLER     