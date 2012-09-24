// Name      :  CKeywords.cc 
// Version   :  $Id$
// Verwendung:  CPU-Keywords
//
// Copyright (c) 1996 by Stiofan Toggweiler
//

#ifndef _CC_CKEYWORDS
#define _CC_CKEYWORDS

#include <stdio.h>
#include <string.h>
#include "Allgemein.h"
#include "RT4300Def.h"
#include "CKeywords.h"

const COMMANDS cmdList[] = { 
          {RT4300_MOV,  RT4300_MOV_CODE,  RT4300_MOV_PARAM,  RT4300_MOV_TYPE},
          {RT4300_OUT,  RT4300_OUT_CODE,  RT4300_OUT_PARAM,  RT4300_OUT_TYPE},
          {RT4300_IN,   RT4300_IN_CODE,   RT4300_IN_PARAM,   RT4300_IN_TYPE},
          {RT4300_NOP,  RT4300_NOP_CODE,  RT4300_NOP_PARAM,  RT4300_NOP_TYPE},                                 
          {RT4300_ADD,  RT4300_ADD_CODE,  RT4300_ADD_PARAM,  RT4300_ADD_TYPE},
          {RT4300_ADC,  RT4300_ADC_CODE,  RT4300_ADC_PARAM,  RT4300_ADC_TYPE},
          {RT4300_SUB,  RT4300_SUB_CODE,  RT4300_SUB_PARAM,  RT4300_SUB_TYPE},
          {RT4300_CMP,  RT4300_CMP_CODE,  RT4300_CMP_PARAM,  RT4300_CMP_TYPE},
          {RT4300_SBC,  RT4300_SBC_CODE,  RT4300_SBC_PARAM,  RT4300_SBC_TYPE},
          {RT4300_AND,  RT4300_AND_CODE,  RT4300_AND_PARAM,  RT4300_AND_TYPE},
          {RT4300_TEST, RT4300_TEST_CODE, RT4300_TEST_PARAM, RT4300_TEST_TYPE},
          {RT4300_OR,   RT4300_OR_CODE,   RT4300_OR_PARAM,   RT4300_OR_TYPE},
          {RT4300_DEC,  RT4300_DEC_CODE,  RT4300_DEC_PARAM,  RT4300_DEC_TYPE},
          {RT4300_INC,  RT4300_INC_CODE,  RT4300_INC_PARAM,  RT4300_INC_TYPE},
          {RT4300_JMP,  RT4300_JMP_CODE,  RT4300_JMP_PARAM,  RT4300_JMP_TYPE},
          {RT4300_JE,   RT4300_JE_CODE,   RT4300_JE_PARAM,   RT4300_JE_TYPE},
          {RT4300_JZ,   RT4300_JZ_CODE,   RT4300_JZ_PARAM,   RT4300_JZ_TYPE},
          {RT4300_JNZ,  RT4300_JNZ_CODE,  RT4300_JNZ_PARAM,  RT4300_JNZ_TYPE},
          {RT4300_JB,   RT4300_JB_CODE,   RT4300_JB_PARAM,   RT4300_JB_TYPE},
          {RT4300_JA,   RT4300_JA_CODE,   RT4300_JA_PARAM,   RT4300_JA_TYPE},
          {RT4300_JC,   RT4300_JC_CODE,   RT4300_JC_PARAM,   RT4300_JC_TYPE} };

BYTE CKeywords::GetParam ( BYTE _bID )
{
   return ( (cmdList[_bID-1].bParam%0x10) );
}

BYTE CKeywords::GetCode ( BYTE _bID )
{
   return ( cmdList[_bID-1].bCode );
}

BOOL CKeywords::IsNOP ( BYTE _bID )
{
   return ( ((cmdList[_bID-1].bParam/0x10)&NOP_PARAM) == NOP_PARAM );
}

BOOL CKeywords::IsINOUT ( BYTE _bID )
{
   return ( ((cmdList[_bID-1].bParam/0x10)&INOUT_PARAM) == INOUT_PARAM );
}

BOOL CKeywords::IsTEST ( BYTE _bID )
{
   return ( ((cmdList[_bID-1].bParam/0x10)&TEST_PARAM) == TEST_PARAM );
}

BOOL CKeywords::Swap ( BYTE _bID )
{
   return ( ((cmdList[_bID-1].bParam/0x10)&SWAP_PARAM) == SWAP_PARAM );
}

BOOL CKeywords::IsDestParamOK ( BYTE _bID, BYTE _bDest )
{
   return (  ((cmdList[_bID-1].bType/0x10) & _bDest) == _bDest );
}

BOOL CKeywords::IsSrcParamOK ( BYTE _bID, BYTE _bSrc )
{
   return (  ((cmdList[_bID-1].bType%0x10) & _bSrc) == _bSrc );
}

BOOL CKeywords::GetCommand ( char *_pszCommand, BYTE &_bID )
{
   int i;
    
   for ( i = 0; i < COMMANDSMAX; i++ )
   {
      if ( !strcmp ( cmdList[i].szCommand, _pszCommand ) )
      {
         _bID = i+1;
             
         return ( TRUE );
      }
   }

   _bID = 0;
    
   return ( FALSE );
}

BOOL CKeywords::GetString ( BYTE _bID, char *pszCode )
{
   strcpy ( pszCode, cmdList[_bID-1].szCommand );

   return ( TRUE );
}

BOOL CKeywords::GetCommand ( BYTE _bCommand, BYTE &_bID )
{
   int i;
    
   for ( i = 0; i < COMMANDSMAX; i++ )
   {
      if ( cmdList[i].bCode == _bCommand )
      {
         _bID = i+1;
             
         return ( TRUE );
      }
   }

   _bID = 0;
    
   return ( FALSE );
}


#endif // _CC_CKEYWORDS
