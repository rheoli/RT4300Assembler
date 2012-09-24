/************************************************************************
    
    CAss.cc - Speichern von Assembler-Befehlen, die vom Parser
              aus dem File gefiltert werden.
    
    Copyright (C) 1996  by Stiofán Toggweiler

    $Id$

****************************************************************************/

#ifndef _H_CASS
#define _H_CASS

#include <stdio.h>
#include <stdlib.h>
#include "Allgemein.h" 

#define COMMAND_LEN_MAX 15   // Maximale Commandlänge
#define SRC_LEN_MAX     6    // Maximale Source-Parameterlänge
#define DEST_LEN_MAX    15   // Max. Destination-Parameterlänge

struct ASSEMBLER_T
{
   char szCommand[COMMAND_LEN_MAX+1];   // Assembler Command
   char szSrc[SRC_LEN_MAX+1];           // Source Parameter
   char szDest[DEST_LEN_MAX+1];         // Ein Label des Jump-Befehls darf hoechstens DEST_LEN_MAX Zeichen lang sein !
   BYTE bParameter;                     // Gibt die Anzahl Parameter am (von Src und Dest)
   WORD wSrcLine;                       // Position in SourceCode
};

class CAss
{
 private:
   ASSEMBLER_T *pasmCode;
   WORD        wAsmAnz;
      
 public:
 
   // Konstruktor: Speicher reservieren und Variable setzen
   CAss ( void );

   // Destruktor: Speicher freigeben   
   ~CAss ( void );
   
   // Neuer Befehls-Code addieren
   // Parameter:
   //   - _wSrcLine:   In welcher Zeile der Befehlcode im Source-
   //                  Code steht
   //   - _pszCommand: Befehlscode aus Source-Code
   //   - _bParam:     Anzahl Parameter
   //   - _pszSrc:     Source-Parameter als Text
   //   - _pszDest:    Destination-Parameter als Text
   BOOL AddCode ( WORD _wSrcLine, char *_pszCommand, BYTE _bParam, char *_pszSrc, char *_pszDest );

   // Ausgeben der bereits gespeicherten Befehlen auf dem Bildschirm
   BOOL PrintCode ( void );
         
   // Befehlscode an aufrufende Prozedur zurückgeben
   // Parameter:
   //   - _wNr:        Welche Zeile von Liste
   //   - _assCode:    Struktur, in welcher der Befehl und
   //                  die Parameter gesichert sind
   BOOL GetCode ( WORD _wNr, ASSEMBLER_T &_assCode );

   // Anzahl bereits gespeichert Befehlscode ausgeben
   WORD GetCodeAnzahl ( void );
};

#endif // _H_CASS
