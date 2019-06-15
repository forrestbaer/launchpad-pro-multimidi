#ifndef note_func_h
#define note_func_h

#include "app.h"
#include "visual/color.h"

u8 roundrobin;

void MakeStar(u8 index, u8 value);
void DropRock(u8 index, u8 value);
void DropLight(u8 index, u8 value);
void DoNote(u8 index, u8 value);
void DoNoteMicrotonal(u8 index, u8 value);
void DoNoteMarked(u8 index, u8 value);
void FixedNote(u8 index, u8 value);
void McpNote(u8 index, u8 value);
void McpFixedNote(u8 index, u8 value);
void McpCCStatic(u8 index, u8 value);
void rrUpCheck();
void CircuitDrum(u8 index, u8 value);
void CircuitChromaticSample(u8 index, u8 value);
void CircuitChromaticSample2(u8 index, u8 value);
void CircuitMicrotonalSet(u8 index, u8 value);
void CircuitMicrotonalNotes(u8 index, u8 value);

#endif /* note_func_h */
