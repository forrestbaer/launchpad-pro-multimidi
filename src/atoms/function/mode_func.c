#include "atoms/function/mode_func.h"
#include "environment/state.h"
#include "organisms/states/setup.h"
#include "organisms/states/scalearp.h"
#include "organisms/states/mastercontrol.h"
#include "organisms/states/circuitpad.h"
#include "organisms/states/keyscale.h"
#include "organisms/states/digitonepad.h"

void ModeFunc(LpState setting, u8 index, u8 value) {
    //probably some general todo for all ADD here...
    switch (setting) {
        case LP_PLAY_MODE:
            transition_state ( state_play );
        break;
        case LP_OFF_MODE:
            transition_state ( state_off );
        break;
        case LP_OVERLAY_MODE:
            transition_state ( state_overlay );
        break;
        case LP_SETUP_MODE:
            transition_state ( state_setup );
        break;
        case LP_SCALEARP_MODE:
            transition_state ( state_scalearp );
        break;
        case LP_MASTERCONTROL_MODE:
            transition_state ( state_mastercontrol );
        break;
        case LP_CIRCUITPAD_MODE:
            transition_state ( state_circuitpad );
        break;
        case LP_KEYSCALE_MODE:
            transition_state ( state_keyscale );
        break;
        case LP_DIGITONEPAD_MODE:
            transition_state ( state_digitonepad );
        break;
        case LP_NUM_MODES:
        break;
    }
}

void ModePlay(u8 index, u8 value) {
    (*ModeFunc)(LP_PLAY_MODE, index, value);
}

void ModeOff(u8 index, u8 value) {
    (*ModeFunc)(LP_OFF_MODE, index, value);
}

void ModeScaleArp(u8 index, u8 value) {
    (*ModeFunc)(LP_SCALEARP_MODE, index, value);
}

void ModeMastercontrol(u8 index, u8 value) {
    (*ModeFunc)(LP_MASTERCONTROL_MODE, index, value);
}

void ModeCircuitpad(u8 index, u8 value) {
    (*ModeFunc)(LP_CIRCUITPAD_MODE, index, value);
}

void ModeKeyscale(u8 index, u8 value) {
    (*ModeFunc)(LP_KEYSCALE_MODE, index, value);
}

void ModeDigitonepad(u8 index, u8 value) {
    (*ModeFunc)(LP_DIGITONEPAD_MODE, index, value);
}