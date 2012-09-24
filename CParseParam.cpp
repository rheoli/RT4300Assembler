// Name      :  CParseParam.cc 
// Version   :  $Id$
// Verwendung:  Parameter entschluesseln
//
// Copyright (c) 1996 by Stiofan Toggweiler
//

#ifndef _CC_CPARSEPARAM
#define _CC_CPARSEPARAM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Allgemein.h"
#include "RT4300Def.h"
#include "CParseParam.h"

const REGISTERLIST regList[] = { 
              {RT4300_REG_R0,  RT4300_REG_R0_CODE,  CPU_REGISTER},
              {RT4300_REG_R1,  RT4300_REG_R1_CODE,  CPU_REGISTER},
              {RT4300_REG_R2,  RT4300_REG_R2_CODE,  CPU_REGISTER} };

BOOL CParseParam::IsJUMP ( BYTE _bArt )
{
   return ( (_bArt&CPU_JUMP) == CPU_JUMP );
}

BOOL CParseParam::ParseParam ( char *_pszParam, BYTE &_bArt, WORD &_wReg )
   {
      int i;
       
      for ( i = 0; i < REGISTERSMAX; i++ )
      {
         if ( !strcmp ( regList[i].szReg, _pszParam ) )
         {
            _bArt = regList[i].bArt;
            _wReg = regList[i].wReg;
             
            return ( TRUE );
         }
      }
    
      /*** Wenn Parameter kein Register ist: ***/
      
      // Param eine Labelbezeichnung
      if ( _pszParam[0] == 'L' )
      {
         _bArt = CPU_JUMP;
         _wReg = atoi ( (_pszParam+1) );
         
         return ( TRUE );
      }
      
      // Param eine Zahl, z.Z. nur Dezimalzahlen       
      if ( _pszParam[0] >= '0' && _pszParam[0] <= '9' )
      {
         _bArt = CPU_NUMBER;
         _wReg = atoi ( _pszParam );

         return ( TRUE );
      }

      _bArt = 0;
      _wReg = 0;
      
      return ( FALSE );
   }

#endif // _CC_CPARSEPARAM
