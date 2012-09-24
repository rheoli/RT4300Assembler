# Makefile for the Cross-Assembler CDCAsm
all: CDCAsm.exe

CDCAsm.obj: CDCAsm.cpp Allgemein.h CParser.h CAss.h CLabel.h CCopyright.h CAssembler.h
        cl /c CDCAsm.cpp

CDCAllg.obj: CDCAllg.cpp Allgemein.h CDCAllg.h
        cl /c CDCAllg.cpp

CAss.obj: CAss.cpp CAss.h Allgemein.h
        cl /c CAss.cpp

CLabel.obj: CLabel.cpp CLabel.h Allgemein.h
        cl /c CLabel.cpp

COpcode.obj: COpcode.cpp COpcode.h Allgemein.h RT4300Def.h
        cl /c COpcode.cpp

CKeywords.obj: CKeywords.cpp CKeywords.h Allgemein.h RT4300Def.h
        cl /c CKeywords.cpp

CParseParam.obj: CParseParam.cpp CParseParam.h Allgemein.h RT4300Def.h
        cl /c CParseParam.cpp

CParser.obj: CParser.cpp Allgemein.h CParser.h CAss.h CLabel.h
        cl /c CParser.cpp

CAssembler.obj: CAssembler.cpp Allgemein.h CAssembler.h CKeywords.h CParseParam.h
        cl /c CAssembler.cpp

CCopyright.obj: CCopyright.cpp CCopyright.h
        cl /c CCopyright.cpp

CDCAsm.exe: CDCAsm.obj CDCAllg.obj CParser.obj CAss.obj CLabel.obj COpcode.obj \
        CKeywords.obj CParseParam.obj CParser.obj \
        CAssembler.obj CCopyright.obj
        cl /OUT:CDCAsm.exe CDCAsm.obj CDCAllg.obj CParser.obj CAss.obj CLabel.obj \
        COpcode.obj CKeywords.obj CParseParam.obj CParser.obj \
        CAssembler.obj CCopyright.obj 

