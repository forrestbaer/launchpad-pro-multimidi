#ifndef note_func_h
#define note_func_h

#include "app.h"
#include "atoms/visual/color.h"

u8 roundrobin;

void MakeStar(u8 index, u8 value);
void DropRock(u8 index, u8 value);
void DropLight(u8 index, u8 value);
void DoNote(u8 index, u8 value);
void DoNoteMarked(u8 index, u8 value);
void FixedNote(u8 index, u8 value);
void McpNote(u8 index, u8 value);
void McpFixedNote(u8 index, u8 value);
void McpCCStatic(u8 index, u8 value);
void rrUpCheck();
void CircuitDrum(u8 index, u8 value);
void CircuitChromaticSample(u8 index, u8 value);
color octaveColor(u8 which);
void ChangeOctave(bool isUp, u8 whichOctave);
void ChangeOctaveUp(u8 index, u8 value);
void ChangeOctaveDown(u8 index, u8 value);
void ChangeOctaveUp2(u8 index, u8 value);
void ChangeOctaveDown2(u8 index, u8 value);

#endif /* note_func_h */
