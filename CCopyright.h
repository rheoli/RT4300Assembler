// Name      :  CCopyright.cc - (Headerfile)
// Version   :  $Id: CCopyright.h,v 1.1 1995/12/02 15:27:59 root Exp root $
// Verwendung:  Ausgeben des Copyright-Textes
//
// Copyright (c) 1995-96 by Charlie Development
//
// Damit in einer Classe auch bereits Funktionen bei der Initialisierung
// ausgefuehrt werden koennen
// 

#ifndef _H_COPYRIGHT
#define _H_COPYRIGHT

class CCopyright
{
 public:
   CCopyright ( char *pszProgName, char *pszVersion, char *pszJahr );
};         

#endif     // _H_COPYRIGHT
 