// Name      :  RT4300Def.h
// Version   :  $Id: RT4300Def.h,v 1.1 1995/12/02 15:27:59 root Exp root $
// Verwendung:  Register- und Befehlscodedefinitionen fuer CDCAsm
//
// Copyright (c) 1994-95 by Charlie Development
//

#ifndef _H_RT4300DEF
#define _H_RT4300DEF

#define CPU_REGISTER         0x01
#define CPU_NUMBER           0x02
#define CPU_JUMP             0x04

// RT4300-Register
#define REGISTERSMAX         0x03
#define RT4300_REG_R0        "R0"
#define RT4300_REG_R0_CODE   0x00
#define RT4300_REG_R1        "R1"
#define RT4300_REG_R1_CODE   0x01
#define RT4300_REG_R2        "R2"
#define RT4300_REG_R2_CODE   0x02
#define RT4300_NUMBER        0x03

// RT4300-Commands Code-Definition
#define COMMANDSMAX          21
// Definitionenbedeutung:
// <Command> <Destination>, <Source> ; Kommentar
// - RT4300_??    -> Command-Name
// - RT4300_??_CODE -> Command-Opcode
// - RT4300_??_PARAM -> Parameteranzahl des Commands
//                                      HI-Nibble fuer Extras:
//                                       - 0x0: keine Extras
#define SWAP_PARAM                         0x1 // Destination und Source Swappen
#define TEST_PARAM                         0x2 //  Test-Befehl
#define NOP_PARAM                          0x4 //  NOP
#define INOUT_PARAM                        0x8 // IN- oder OUT-Befehl
//                                      LO-Nibble fuer Parameteranzahl
//
// - RT4300_??_TYPE  -> Parameter-Typen HI-Nibble fuer Destination
//                                      LO-Nibble fuer Source
//                      Bitaufteilung:
//                       - 0x0 kein Parameter
//                       - 0x1 fuer Registerzugriff zugelassen
//                       - 0x2 fuer ROM-Zugriff zugelassen
//                       - 0x4 fuer Jump-Befehl

#define RT4300_MOV           "MOV"  
#define RT4300_MOV_CODE      0x08
#define RT4300_MOV_PARAM     0x02  
#define RT4300_MOV_TYPE      0x13   
#define RT4300_OUT           "OUT"
#define RT4300_OUT_CODE      0x08    // wie MOV R2, <??>
#define RT4300_OUT_PARAM     0x91
#define RT4300_OUT_TYPE      0x30
#define RT4300_IN            "IN"
#define RT4300_IN_CODE       0x08    // wie MOV <??>, R2
#define RT4300_IN_PARAM      0x81
#define RT4300_IN_TYPE       0x10
#define RT4300_NOP           "NOP"
#define RT4300_NOP_CODE      0x08    // wie MOV R0, R0
#define RT4300_NOP_PARAM     0x40
#define RT4300_NOP_TYPE      0x00
#define RT4300_ADD           "ADD"
#define RT4300_ADD_CODE      0x09
#define RT4300_ADD_PARAM     0x02
#define RT4300_ADD_TYPE      0x13
#define RT4300_ADC           "ADC"
#define RT4300_ADC_CODE      0x01
#define RT4300_ADC_PARAM     0x02
#define RT4300_ADC_TYPE      0x13
#define RT4300_SUB           "SUB"
#define RT4300_SUB_CODE      0x06
#define RT4300_SUB_PARAM     0x02
#define RT4300_SUB_TYPE      0x13
#define RT4300_CMP           "CMP"
#define RT4300_CMP_CODE      0x06    // wie SUB konst, <??> ; 
#define RT4300_CMP_PARAM     0x12
#define RT4300_CMP_TYPE      0x12
#define RT4300_SBC           "SBC"
#define RT4300_SBC_CODE      0x0E
#define RT4300_SBC_PARAM     0x02
#define RT4300_SBC_TYPE      0x13
#define RT4300_AND           "AND"
#define RT4300_AND_CODE      0x05
#define RT4300_AND_PARAM     0x02
#define RT4300_AND_TYPE      0x13
#define RT4300_TEST          "TEST"
#define RT4300_TEST_CODE     0x09    // wie AND <??>, Wert, mit Wert = [1, 2, 4, 8, 16,...]
#define RT4300_TEST_PARAM    0x32
#define RT4300_TEST_TYPE     0x12
#define RT4300_OR            "OR"
#define RT4300_OR_CODE       0x0D
#define RT4300_OR_PARAM      0x02
#define RT4300_OR_TYPE       0x13
#define RT4300_DEC           "DEC"
#define RT4300_DEC_CODE      0x0F
#define RT4300_DEC_PARAM     0x01
#define RT4300_DEC_TYPE      0x10
#define RT4300_INC           "INC"
#define RT4300_INC_CODE      0x00
#define RT4300_INC_PARAM     0x01
#define RT4300_INC_TYPE      0x10

#define RT4300_JMP           "JMP"
#define RT4300_JMP_CODE      0x04
#define RT4300_JMP_PARAM     0x01
#define RT4300_JMP_TYPE      0x40
#define RT4300_JE            "JE"
#define RT4300_JE_CODE       0x0C
#define RT4300_JE_PARAM      0x01
#define RT4300_JE_TYPE       0x40
#define RT4300_JZ            "JZ"
#define RT4300_JZ_CODE       0x02
#define RT4300_JZ_PARAM      0x01
#define RT4300_JZ_TYPE       0x40
#define RT4300_JNZ           "JNZ"
#define RT4300_JNZ_CODE      0x0A
#define RT4300_JNZ_PARAM     0x01
#define RT4300_JNZ_TYPE      0x40
#define RT4300_JB            "JB"
#define RT4300_JB_CODE       0x03
#define RT4300_JB_PARAM      0x01
#define RT4300_JB_TYPE       0x40
#define RT4300_JA            "JA"
#define RT4300_JA_CODE       0x0B
#define RT4300_JA_PARAM      0x01
#define RT4300_JA_TYPE       0x40
#define RT4300_JC            "JC"
#define RT4300_JC_CODE       0x07
#define RT4300_JC_PARAM      0x01
#define RT4300_JC_TYPE       0x40


#endif /* _H_RT4300DEF */
