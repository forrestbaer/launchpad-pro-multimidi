#ifndef event_h
#define event_h

#include "app.h"
/* usually: Pad Press Event. also Pad Release event.  ?others? */
void event_sysex(u8 port, u16 count);
void event_aftertouch(u8 index, u8 value);
#endif /* event_h */
