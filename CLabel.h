/************************************************************************
    
    CLabel.h (Header) - Class to save labels
    
    Copyright (C) 1996  by Stiofan Toggweiler

    $Id$

****************************************************************************/

#ifndef _H_CLABEL
#define _H_CLABEL

#include <stdio.h>
#include <stdlib.h>
#include "Allgemein.h" 

#define NAME_LEN_MAX 15

struct LABEL_T
{
   WORD wID;                      // Label ID bei Jump-Befehlen
   WORD wLine;                    // Linien Nummer in Sourcecode (nach dem Parsern)
   char szName[NAME_LEN_MAX+1];   // Labelname
   BOOL fJFound;                  // TRUE wenn Jump gefunden
   BOOL fLFound;                  // TRUE wenn Label gefunden
   BOOL fAddrSet;                 // TRUE wenn Adresse gesetzt
   WORD wAddress;                 // Adresse die beim Jump-Befehl eingefuegt wird
};

class CLabel
{
 private:
   LABEL_T *pLabel;
   WORD    wLabAnz;
      
 public:
 
   // Konstruktor: Speicher reservieren und Variable setzen
   CLabel ( void );

   // Destruktor: Speicher freigeben   
   ~CLabel ( void );
   
   // Neues Label addieren, sofern noch nicht vorhanden
   BOOL AddLabel ( char *pszLabel, WORD wLine );

   // Testen, ob ein Label zu dieser Zeile ist
   BOOL IsLabel ( WORD wLine, WORD &wID );   
   
   // Adresse setzen von Label
   BOOL SetAddress ( WORD wID, WORD wAddr );
   
   // Label suchen und ID zurueckgeben
   BOOL AddJump ( char *pszJump, WORD &wID );

   // Drucken aller Befehle
   BOOL PrintCode ( void );

   // Testes alle Label, ob Jump-Befehle vorhanden sind und umgegehrt
   BOOL TestLabel ( void );
         
   // Adresse von Label zurueckgeben
   BOOL GetLabel ( const WORD wID, WORD &wAddress );
};

#endif // _H_CLABEL
