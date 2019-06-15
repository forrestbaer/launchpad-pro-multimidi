#ifndef pad_h
#define pad_h

#include "app.h"
#include "visual/color.h"

#define LP_FIRST_BUTTON (1)
#define LP_LAST_BUTTON  (98)

#define LP_OCTAVE_DOWN    (92)
#define LP_OCTAVE_UP      (91)
#define LP_TRANSPOSE_DOWN (93)
#define LP_TRANSPOSE_UP   (94)

#define LP_SESSION        (95)
#define LP_NOTE           (96)
#define LP_DEVICE         (97)
#define LP_USER           (98)

#define LP_SETUP          (90)
#define LP_SHIFT          (80)
#define LP_CLICK          (70)
#define LP_UNDO           (60)
#define LP_DELETE         (50)
#define LP_QUANTISE       (40)
#define LP_DUPLICATE      (30)
#define LP_DOUBLE         (20)
#define LP_RECORD         (10)

#define LP_FIRST_PLAY     (19)
#define LP_LAST_PLAY      (89)
#define LP_PLAY_GAP       (ROW_SIZE)

#define LP_RECORD_ARM     (1)
#define LP_TRACK_SELECT   (2)
#define LP_MUTE           (3)
#define LP_SOLO           (4)
#define LP_VOLUME         (5)
#define LP_PAN            (6)
#define LP_SENDS          (7)
#define LP_STOP_CLIP      (8)


/*******************************************************************************
 * Defines/helpers
 ******************************************************************************/

#define NUM_NOTES   (12)
#define MAX_NOTE    (0x7F)
#define NUM_OCTAVES (MAX_NOTE / NUM_NOTES)

#define GRID_SIZE (8)
#define ROW_GAP   (2)
#define ROW_SIZE  (GRID_SIZE + ROW_GAP)
#define FIRST_PAD (11)
#define LAST_PAD  (FIRST_PAD + GRID_SIZE * ROW_SIZE - (ROW_GAP + 1))

#define BUTTON_COUNT 100

typedef enum
{
    DIR_TL,
    DIR_UP,
    DIR_TR,
    DIR_RIGHT,
    DIR_BR,
    DIR_DOWN,
    DIR_BL,
    DIR_LEFT,
    DIR_NUM
} Direction;

u8 directional(Direction whichDir, u8 fromPad);

// Pad Functions (visual, animation...) -> The music side of the Pad functions will be part of this but done thru atoms/function/

typedef struct {
   s8 note;
   s8 channel;
   s8 note2;
   s8 note3;
} heldnote;

void recrsvDirFill(u8 dirInt, u8 index, u8 recrsvDepth);
void recrsvDirClear(u8 dirInt, u8 index);


// This pattern of Function and FilledFunction is for having a base generic function and then giving it more
// parameters to load it into the Grid of Functional Pointers. Example: HitNoteAndLightPad would be the generic
// then the FilledHitNoteAndLightPad would tell it play Middle C and Light it White.
// Actual Final implementation of this may be a little more complete/complex OR it may end up being simpler

void DoMore(u8 setting, u8 index, u8 value);
void FilledDoMore(u8 index, u8 value);

void DoSpiral(u8 setting, u8 index, u8 value);
void FilledDoSpiral(u8 index, u8 value);

void DoLeft(u8 setting, u8 index, u8 value);
void FilledDoLeft(u8 index, u8 value);

void DoNoteTest(u8 setting, u8 index, u8 value);
void FilledDoNoteTest(u8 index, u8 value);

void DoNoteBeams(u8 setting, u8 index, u8 value);
void FilledDoNoteBeams(u8 index, u8 value);

void DoStar(u8 setting, u8 index, u8 value);
void FilledDoStar(u8 index, u8 value);

void Pressure(u8 setting, u8 index, u8 value);
void FilledPressure(u8 index, u8 value);

void NullFunction(u8 index, u8 value);
void NullFuncExceptOff(u8 index, u8 value);

u8 pianoDraw(u8 interval);

u8 conv64toGrid( u8 orig64 );
u8 convGridto64( u8 origGrid );

#endif /* pad_h */
