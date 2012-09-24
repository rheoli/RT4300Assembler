// Name      :  CCopyright.cc
// Version   :  $Id: CCopyright.cc,v 1.1 1995/12/02 15:25:47 root Exp root $
// Verwendung:  Ausgeben des Copyright-Textes
//
// Copyright (c) 1995-96 by Charlie Development
//
// Damit in einer Classe auch bereits Funktionen bei der Initialisierung
// ausgefuehrt werden koennen
// 

#include <stdio.h>
#include "CCopyright.h"

   CCopyright::CCopyright ( char *pszProgName,
                                      char *pszVersion,
                                      char *pszJahr )
   {
      printf ( "\nCharlie Development %s,  %s\n", pszProgName, pszVersion );
      printf ( "Copyright (c) %s by Charlie Dev. All rights reserved.\n\n", pszJahr );   
   }
 