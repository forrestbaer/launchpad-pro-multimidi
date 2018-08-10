#include "atoms/function/clear_func.h"
#include "environment/surface.h"

void clear_all_functions() {
    for ( u8 fdx = 0; fdx < 100; fdx++ ) {
      grid_func[fdx] = &NullFunction;
      grid_pres[fdx] = &NullFunction;
    }
}
