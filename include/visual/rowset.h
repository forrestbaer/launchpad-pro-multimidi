#ifndef rowset_h
#define rowset_h

#include "app.h"

/* I like most of these sets to be groups of 8 so that 8 of them will join evenly to form the grid
   there may have to be exceptions but hopefully not. Maybe if Less needed, just have PadNull or something

   The rowset is a 8x1 horizontal set

   Any row concieved of with repetitive or unique function should be broken down into this level.
   Things like arp rows can be boiled down to math and parameters to maximize reuse. Minimize Memory use
*/

void rowset_R35_arp(u8 basenote, u8 arpmode, u8 padbase);
void rowset_octave_state_etc();
void rowset_circuit_fingerdrum(u8 base, u8 padbase);  //(idx, 81 - idx * 10);
void rowset_circuit_sampletune(u8 base, u8 padbase);
void rowset_microtonal_setup(u8 base, u8 padbase);
void rowset_microtonal_notes(u8 base, u8 padbase);

#endif /* rowset_h */
