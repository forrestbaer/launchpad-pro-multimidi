#ifndef columnset_h
#define columnset_h

#include "app.h"

/* I like most of these sets to be groups of 8 so that 8 of them will join evenly to form the grid
   there may have to be exceptions but hopefully not. Maybe if Less needed, just have PadNull or something

   The columnset is a 1x8 vertical set

   Any column concieved of with repetitive or unique function should be broken down into this level.
   Things like arp columns can be boiled down to math and parameters to maximize reuse. Minimize Memory use
*/

void columnset_R35_arp(u8 basenote, u8 arpmode, u8 padbase);

void columnset_MCP_arp(u8 basenote, u8 arpmode, u8 padbase);

void columnset_superslider(u8 midichannel, u8 cc1, s8 cc2, u8 column, u8 r, u8 g, u8 b);

#endif /* columnset_h */
