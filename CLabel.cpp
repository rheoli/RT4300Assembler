/************************************************************************
    
    CLabel.h - Class to save labels
    
    Copyright (C) 1996  by Stiofan Toggweiler

    $Id$

****************************************************************************/

#ifndef _CC_CLABEL
#define _CC_CLABEL

#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include "Allgemein.h" 
#include "CLabel.h"

// Konstruktor: Speicher reservieren und Variable setzen
CLabel::CLabel ( void )
   {
      pLabel = (LABEL_T *) malloc ( sizeof(LABEL_T)*2 );
      if ( pLabel == NULL )
      {
          printf ( "CLabel - Can\'t allocate memory.\n" );
          exit ( 1 );
      }
     
      wLabAnz = 0;
   }


// Destruktor: Speicher freigeben   
CLabel::~CLabel ( void )
   {
      free ( pLabel );
   }

   
// Neues Label addieren, sofern noch nicht vorhanden
BOOL CLabel::AddLabel ( char *pszLabel, WORD wLine )
{
   int  i;
   BOOL fFound = FALSE;

   for ( i = 0; i < wLabAnz; i++ )
   {
      if ( !strcmp ( pszLabel, pLabel[i].szName ) )
      {
         fFound = TRUE;
         break;
      }
   }

   if ( fFound && pLabel[i].fLFound )
   {
      printf ( "CLabel - Label %s bereits vorhanden. (LINE %d)\n", pszLabel, wLine );
      exit ( 1 );
   }

   if ( fFound && pLabel[i].fJFound )
   {
      pLabel[i].wLine   = wLine;   
      pLabel[i].fLFound = TRUE;
    
      return ( TRUE );
   }

   if ( !fFound )
   {
      strcpy ( pLabel[wLabAnz].szName, pszLabel );
      pLabel[wLabAnz].wLine     = wLine;
      pLabel[wLabAnz].wAddress  = 0;
      pLabel[wLabAnz].fAddrSet  = FALSE;
      pLabel[wLabAnz].fLFound   = TRUE;
      pLabel[wLabAnz].fJFound   = FALSE;
      pLabel[wLabAnz].wID = wLabAnz+1;
   
      pLabel = (LABEL_T *) realloc ( pLabel, sizeof(LABEL_T)*(wLabAnz+2) );
      if ( pLabel == NULL )
      {
         printf ( "CLabel - Nicht genug Speicher vorhanden.\n" );
         exit ( 1 );
      }
   
      wLabAnz++;
      
      return ( TRUE );
   }

   printf ( "CLabel - Internal Error CLAB::1000\n" );
   exit ( 1 );
   
   return ( FALSE );
}
   

// Testen, ob ein Label zu dieser Zeile ist
BOOL CLabel::IsLabel ( WORD _wLine, WORD &_wID )
{
   int i;
   
   for ( i = 0; i < wLabAnz; i++ )
   {
      if ( pLabel[i].wLine == _wLine )
      {
         _wID = pLabel[i].wID;
         
         return ( TRUE );
      }
   }
   
   _wID = 0;
   
   return ( FALSE );
}
   
// Adresse setzen von Label
BOOL CLabel::SetAddress ( WORD wID, WORD wAddr )
{
   int i;
   
   for ( i = 0; i < wLabAnz; i++ )
   {
      if ( pLabel[i].wID == wID )
      {
         pLabel[i].wAddress = wAddr-1;
         pLabel[i].fAddrSet = TRUE;
         
         return ( TRUE );
      }
   }
   
   return ( FALSE );
}
   
// Label suchen und ID zurueckgeben
BOOL CLabel::AddJump ( char *pszJump, WORD &wID )
{
   int i;
   
   for ( i = 0; i < wLabAnz; i++ )
   {
      if ( !strcmp ( pLabel[i].szName, pszJump ) )
      {
         pLabel[i].fJFound = TRUE;
         wID = pLabel[i].wID;
         
         return ( TRUE );
      }
   }
   
   strcpy ( pLabel[wLabAnz].szName, pszJump );
   pLabel[wLabAnz].wLine     = 0;
   pLabel[wLabAnz].fAddrSet  = FALSE;   
   pLabel[wLabAnz].wAddress  = 0;
   pLabel[wLabAnz].fLFound   = FALSE;
   pLabel[wLabAnz].fJFound   = TRUE;
   wID = pLabel[wLabAnz].wID = wLabAnz+1;
      
   pLabel = (LABEL_T *) realloc ( pLabel, sizeof(LABEL_T)*(wLabAnz+2) );
   if ( pLabel == NULL )
   {
      printf ( "CLabel - Nicht genug Speicher vorhanden.\n" );
      exit ( 1 );
   }
 
   wLabAnz++;
   
   return ( TRUE );      
}      
         
// Testes alle Label, ob Jump-Befehle vorhanden sind und umgegehrt
BOOL CLabel::TestLabel ( void )
{
   int i;
   
   for ( i = 0; i < wLabAnz; i++ )
   {
      if ( !pLabel[i].fLFound )
      {
         printf ( "CLabel - ERROR: Kein Label zu Jump %s gefunden.\n", pLabel[i].szName );
         exit ( 1 );
      }
      
      if ( !pLabel[i].fJFound )
      {
         printf ( "CLabel - WARNING: Kein Jump zu Label %s gefunden. (LINE %d)\n", pLabel[i].szName, pLabel[i].wLine );
      }
   }
   
   return ( TRUE );
}         

// Drucken aller Befehle
BOOL CLabel::PrintCode ( void )
{
   int i;
   
   for ( i = 0; i< wLabAnz; i++ )
   {
      printf ( "Label: %-15s / Line %3d / ID %3d\n", pLabel[i].szName,
                  pLabel[i].wLine, pLabel[i].wID );
   }
   
   return ( TRUE );
}
         
// Adresse von Label zurueckgeben
BOOL CLabel::GetLabel ( const WORD wID, WORD &wAddress )
{
   int i;
   
   for ( i = 0; i < wLabAnz; i++ )
   {
      if ( pLabel[i].wID == wID )
      {
         if ( !pLabel[i].fAddrSet )
         {
            printf ( "CLabel - Internal Error CLAB::1001\n" );
            exit ( 1 );
         }
         
         wAddress = pLabel[i].wAddress;
         
         return ( TRUE );
      }
   }
   
   wAddress = 0;
   
   return ( FALSE );
}


#endif // _CC_CLABEL
