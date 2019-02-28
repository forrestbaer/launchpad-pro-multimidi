#include "organisms/states/mastercontrol.h"
#include "environment/surface.h"
#include "organisms/visual/columnset.h"
#include "organisms/visual/rowset.h"
#include "atoms/function/note_func.h"

// Master Control Pads - a performance system for controlling all midi devices connected to the LPP


void Togglemastercontrol(u8 index, u8 value) {
    if (value > 0) {
       build_drumbrute_impact();
    }
}

void TogglemastercontrolBack(u8 index, u8 value) {
    if (value > 0) {
        rebuild_mastercontrol();
    }
}

void SetChannelGroup1(u8 index, u8 value) {
      if (value > 0) {
          for ( u8 cdx = 8; cdx > 0; cdx-- ) { //clean up loop
              // simplest to find the one that's ON and switch it off

              if ( grid_params[cdx*10].p1 == 1 ) {
                change_color(cdx*10, grid_colors[cdx*10].r / 4, grid_colors[cdx*10].g / 4, grid_colors[cdx*10].b / 4);
                grid_params[cdx*10].p1 = 0;
              }
          }
          mcpSet1 = 8 - index/10;
          grid_params[index].p1 = 1;
          change_color(index, grid_colors[index].r * 4, grid_colors[index].g * 4, grid_colors[index].b * 4);
      }
}

void SetChannelGroup2(u8 index, u8 value) {
      if (value > 0) {
          for ( u8 cdx = 8; cdx > 0; cdx-- ) { //clean up loop
              // simplest to find the one that's ON and switch it off

              if ( grid_params[cdx*10+9].p1 == 1 ) {
                change_color(cdx*10+9, grid_colors[cdx*10+9].r / 4, grid_colors[cdx*10+9].g / 4, grid_colors[cdx*10+9].b / 4);
                grid_params[cdx*10+9].p1 = 0;
              }
          }
          mcpSet2 = 8 - index/10;
          grid_params[index].p1 = 1;
          change_color(index, grid_colors[index].r * 4, grid_colors[index].g * 4, grid_colors[index].b * 4);
      }
}

void build_drumbrute_impact() {  // in the upper half always, for now.
    for ( u8 cdx = 5; cdx < 9; cdx++ ) {  //clear out for purity ;)
      for ( u8 rdx = 1; rdx < 9; rdx++ ) {
        grid_params[cdx*10+rdx].p2 = 0;
        change_color(cdx*10+rdx, 0, 0, 0);
        grid_func[cdx*10+rdx] = &NullFunction;
      }
    }
    for ( u8 idx = 1; idx < 9; idx++ ) {
      grid_params[50+idx].p2 = 35+idx;
      change_color(50+idx, 55, 55, 55);
      grid_func[50+idx] = &McpFixedNote;

      grid_params[70+idx].p2 = 47+idx;
      change_color(70+idx, 55, 8, 0);
      grid_func[70+idx] = &McpFixedNote;
    }

    grid_params[67].p2 = 44;
    change_color(67, 55, 55, 55);
    grid_func[67] = &McpFixedNote;

    grid_params[68].p2 = 45;
    change_color(68, 55, 55, 55);
    grid_func[68] = &McpFixedNote;

    grid_params[87].p2 = 56;
    change_color(87, 55, 8, 0);
    grid_func[87] = &McpFixedNote;

    grid_params[88].p2 = 57;
    change_color(88, 55, 8, 0);
    grid_func[88] = &McpFixedNote;

    // grid_params[76].p2 = 0;  // no color option for the ?cowbell?
    // change_color(76, 0, 0, 0);
    // grid_func[76] = &NullFunction;

    // now get the 4 CC options for the ROLLER - CC 9  value 0, 25, 50, 75 , 100
    for ( u8 rdx = 0; rdx < 5; rdx++ ) {
      grid_params[81+rdx].p1 = 8;
      grid_params[81+rdx].p2 = rdx * 25;
      change_color(81+rdx, rdx*12, 0, 10);
      grid_func[81+rdx] = &McpCCStatic;
    }

    grid_func[97] = &TogglemastercontrolBack;
    change_color(97, 21, 12, 16);
}

void rebuild_mastercontrol() {
    for ( u8 idx = 0; idx < 8; idx++ ) {
        columnset_MCP_arp(0, idx, 11 + idx); // basenote, mode, start pad (bottom)
    }

    grid_func[97] = &Togglemastercontrol;
    change_color(97, 21, 12, 0);
}

void build_mastercontrol() {
    for ( u8 idx = 0; idx < 8; idx++ ) {
        columnset_MCP_arp(0, idx, 11 + idx); // basenote, mode, start pad (bottom)
    }

    rowset_octave_mode_etc();

    for ( u8 cdx = 8; cdx > 0; cdx-- ) {
      grid_func[cdx*10] = &SetChannelGroup1;
      grid_params[cdx*10].p1 = 0;  // p1 here is a toggle for on/off 1 = on, 0 = off - like boolean
      change_color(cdx*10, 0, 10, 0);
    }
    grid_params[80].p1 = 1;
    change_color(80, 0, 40, 0);

    for ( u8 c2dx = 8; c2dx > 0; c2dx-- ) {
      grid_func[c2dx*10+9] = &SetChannelGroup2;
      grid_params[c2dx*10+9].p1 = 0;  // p1 here is a toggle for on/off 1 = on, 0 = off - like boolean
      change_color(c2dx*10+9, 0, 10, 0);
    }
    grid_params[89].p1 = 1;
    change_color(89, 0, 40, 0);

    grid_func[97] = &Togglemastercontrol;
    change_color(97, 21, 12, 0);

    grid_func[1] = &ChangeOctaveUp2;
    change_color(1, 33, 33, 33);
    grid_func[2] = &ChangeOctaveDown2;
    change_color(2, 33, 33, 33);
}

void state_mastercontrol(StateEvent msg, u8 index, u8 value) {
  switch (msg) {
    case EVENT_EXIT:
      exit_surface();
      break;
    case EVENT_ENTER:
      current_state = LP_MASTERCONTROL_MODE;
      memory_store[0] = LP_MASTERCONTROL_MODE;
      hal_write_flash(0, memory_store, 30);
      build_mastercontrol();
      break;
    case EVENT_INPUT:
      (*grid_func[index])(index, value);
      break;
    case EVENT_REDRAW:
      //this is nice if it really is redrawing many of the pads,
      // but here it was not (only used for Octave redraw = 2 PADS!) so probably remove this...
      // redraw_surface();
      // break;
    case EVENT_PRESSURE:
      (*grid_pres[index])(index, value);
      break;
    case EVENT_CLOCK:
    case EVENT_MSG_COUNT:
      break;
  }
}
