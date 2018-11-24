#ifndef keyscale_h
#define keyscale_h

#include "app.h"
#include "environment/state.h"

void SetSubModePlay(u8 index, u8 value);
void SetSubModeUser(u8 index, u8 value);
void SetKey(u8 index, u8 value);
void SetModal(u8 index, u8 value);
void SetOffset(u8 index, u8 value);
void SetHideNonscale(u8 index, u8 value);
void build_keyscale();
void build_scaleplay();
void state_keyscale(StateEvent msg, u8 index, u8 value);
void recursiveAdjust(s8 *adj, u8 *oct);

#endif /* keyscale_h */
