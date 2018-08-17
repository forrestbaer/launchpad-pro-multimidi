#include "environment/state.h"
#include "organisms/states/setup.h"
#include "organisms/states/scalearp.h"

void ModeFunc(LpState setting, u8 index, u8 value) {
    //probably some general todo for all ADD here...

    switch (setting) {
        case LP_PLAY_MODE:
            // something like...
            // GLOBAL_CURRENT_INSTRUMENT_ETC = value
            // value could be an ENUM for ease of readability
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
        case LP_NUM_MODES:
        break;
    }

}

void ModePlay(u8 index, u8 value) {
    //maybe add specific instruments next...could use "value"
    (*ModeFunc)(LP_PLAY_MODE, index, value);
}

void ModeOff(u8 index, u8 value) {
    (*ModeFunc)(LP_OFF_MODE, index, value);
}

void ModeScaleArp(u8 index, u8 value) {
    (*ModeFunc)(LP_SCALEARP_MODE, index, value);
}
