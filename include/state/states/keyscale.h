#ifndef keyscale_h
#define keyscale_h

#include "app.h"
#include "state/state.h"

void SetSubModePlay(u8 index, u8 value);
void SetSubModeUser(u8 index, u8 value);
void SetSubModeSends(u8 index, u8 value);
void SetSubModeAftertouch(u8 index, u8 value);
void SetSubModeColorScheme(u8 index, u8 value);
void SetAftertouchCcOnes( u8 index, u8 value );
void SetAftertouchCcTens( u8 index, u8 value );
void SetAftertouchCcHundreds( u8 index, u8 value );
void paint_state_notes();
void SetKey(u8 index, u8 value);
void SetModal(u8 index, u8 value);
void SetOffset(u8 index, u8 value);
void SetHideNonscale(u8 index, u8 value);
void SetAftertouch(u8 index, u8 value);
void SetMidiChannelSlot(u8 index, u8 value);
void SetMidiChannel(u8 index, u8 value);
void SetVelocityCurve(u8 index, u8 value);
void clear_keyscale();
void build_keyscale();
void build_scaleplay();
void build_midi_channels();
void build_aftertouch();
void build_colorscheme();
void build_keyscale_header_footer();
void state_keyscale(StateEvent msg, u8 index, u8 value);
void recursiveAdjust(s8 *adj, u8 *oct);

#endif /* keyscale_h */
