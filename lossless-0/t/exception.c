/*516:*/
#line 9761 "lossless.w"

/*265:*/
#line 5016 "lossless.w"

#define LL_TEST 1
#include "lossless.h"
void test_main(void);

int
main(int argc ll_unused,
char**argv ll_unused)
{
volatile boolean first= btrue;
vm_init();
if(argc> 1)
error(ERR_ARITY_EXTRA,NIL);
vm_prepare();
if(!first){
printf("Bail out! Unhandled exception in test\n");
return EXIT_FAILURE;
}
first= bfalse;
test_main();
tap_plan(0);
return EXIT_SUCCESS;
}

/*:265*/
#line 9762 "lossless.w"

void
test_main(void)
{
volatile boolean first= btrue;
volatile boolean failed= bfalse;
boolean ok;

Error_Handler= btrue;
vm_prepare();
if(first){
first= bfalse;
vm_reset();
Acc= read_cstring(GOTO_FAIL);
interpret();
}else
failed= btrue;
ok= tap_ok(failed,"an error is raised");
test_vm_state(GOTO_FAIL,
TEST_VMSTATE_RUNNING
|TEST_VMSTATE_NOT_INTERRUPTED
|TEST_VMSTATE_ENV_ROOT
|TEST_VMSTATE_STACKS);
}

/*:516*/
