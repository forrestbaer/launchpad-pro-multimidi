#include "atoms/function/clear_func.h"
#include "environment/surface.h"

void clear_all_functions() {
    for ( u8 fdx = 0; fdx < 100; fdx++ ) {
      grid_func[fdx] = &NullFunction;
      grid_pres[fdx] = &NullFunction;
      grid_params[fdx].p1 = 0;
      grid_params[fdx].p2 = 0;
      grid_params[fdx].p3 = 0;
      grid_params[fdx].p4 = 0;
      grid_params[fdx].p5 = 0;
      grid_params[fdx].p6 = 0;
      grid_params[fdx].p7 = 0;
      grid_params[fdx].p8 = 0;
    }
}
