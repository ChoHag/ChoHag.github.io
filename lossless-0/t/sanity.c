/*266:*/
#line 5046 "lossless.w"

#define LL_TEST
#include "lossless.h"
int
main()
{
tap_plan(1);
vm_init();
vm_prepare();
vm_reset();
interpret();
tap_pass("LossLess compiles and runs");
}

/*:266*/
