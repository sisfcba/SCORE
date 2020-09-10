/*         Copyright (c) 1987 by  Klondike Software Inc.
MODULE:    keys.h
AUTHOR:    Dominic N. Sotirescu
RELEASE:   1.0
CONTENT:   Key definitions (scan code and mnemonics)
_______________________________________________________________ */


/*
   The activators are used by the TOOLKIT to ensure device
   independence.

   The designer has two choices:

        - use activators, (device independence but some memory
          overhead), or

        - use scan codes (key_scan contains the scan code for
          any key returned: ASCII and extended)

   Activators are stored in key_buf as follows:
   two bytes for the scan code followed by a zero terminated
   string, the name of the activator.

   The first two bytes contain:
   first byte = ASCII code    if the key is an ASCII character
   second byte = 0

   first byte = 0             if the key is an extended character
   second byte = scan code

   More than one activator can be mapped to the same scan code.

   */

#ifdef PROGRAMA_PRINCIPAL

char key_buf[]= {
  RETURN,0,'R','E','T','U','R','N',0,
  HOME & 0xff,HOME>>8,'H','O','M','E',0,
  END & 0xff,END>>8,'E','N','D',0,
  UP & 0xff,UP>>8,'U','P',0,
  DOWN & 0xff,DOWN>>8,'D','O','W','N',0,
  LEFT & 0xff,LEFT>>8,'L','E','F','T',0,
  RIGHT & 0xff,RIGHT>>8,'R','I','G','H','T',0,
  PAGE_UP & 0xff,PAGE_UP>>8,'P','A','G','E','_','U','P',0,
  PAGE_DOWN & 0xff,PAGE_DOWN>>8,'P','A','G','E','_','D','O','W','N',0,
  EXIT,0,'E','X','I','T',0,
  INSERT & 0xff,INSERT>>8,'I','N','S','E','R','T',0,
  DELETE & 0xff,DELETE>>8,'D','E','L','E','T','E',0,
  RUBOUT,0,'R','U','B','O','U','T',0,
  BACKSPACE & 0xff,BACKSPACE>>8,'B','A','C','K','S','P','A','C','E',0,
  TAB,0,'T','A','B',0,
  BACKTAB & 0xff,BACKTAB>>8,'B','A','C','K','T','A','B',0,
  F1 & 0xff,F1>>8,'F','1',0,
  F2 & 0xff,F2>>8,'F','2',0,
  F3 & 0xff,F3>>8,'F','3',0,
  F4 & 0xff,F4>>8,'F','4',0,
  F5 & 0xff,F5>>8,'F','5',0,
  F6 & 0xff,F6>>8,'F','6',0,
  F7 & 0xff,F7>>8,'F','7',0,
  F8 & 0xff,F8>>8,'F','8',0,
  F9 & 0xff,F9>>8,'F','9',0,
  F10 & 0xff,F10>>8,'F','1','0',0
  };

int  key_nc = sizeof(key_buf);

#else

extern char key_buf[];
extern int key_nc;

#endif
