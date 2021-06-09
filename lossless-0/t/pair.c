/*472:*/
#line 8666 "lossless.w"

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
#line 8667 "lossless.w"

void
test_main(void)
{
boolean ok,okok;
cell marco,polo,t,water;
char*prefix= NULL;
char msg[TEST_BUFSIZE]= {0};
marco= sym("marco?");
polo= sym("polo!");
water= sym("fish out of water!");
/*473:*/
#line 8693 "lossless.w"

vm_reset();
Acc= read_cstring(prefix= "(cons 24 42)");
interpret();
ok= tap_ok(pair_p(Acc),tmsgf("pair?"));
tap_again(ok,integer_p(car(Acc))&&int_value(car(Acc))==24,
tmsgf("car"));
tap_again(ok,integer_p(car(Acc))&&int_value(cdr(Acc))==42,
tmsgf("cdr"));
test_vm_state_full(prefix);

/*:473*/
#line 8678 "lossless.w"

/*474:*/
#line 8704 "lossless.w"

vm_reset();
t= cons(int_new(42),polo);
t= cons(synquote_new(t),NIL);
Tmp_Test= Acc= cons(sym("car"),t);
prefix= "(car '(42 . polo))";
interpret();
tap_ok(integer_p(Acc)&&int_value(Acc)==42,tmsgf("integer?"));
test_vm_state_full(prefix);

/*:474*/
#line 8679 "lossless.w"

/*475:*/
#line 8714 "lossless.w"

vm_reset();
Acc= cons(sym("cdr"),t);
prefix= "(cdr '(42 . polo))";
interpret();
tap_ok(symbol_p(Acc)&&Acc==polo,tmsgf("symbol?"));
test_vm_state_full(prefix);

/*:475*/
#line 8680 "lossless.w"

/*476:*/
#line 8722 "lossless.w"

vm_reset();
t= cons(NIL,NIL);
Acc= cons(sym("null?"),t);
prefix= "(null? ())";
interpret();
tap_ok(true_p(Acc),tmsgf("true?"));
test_vm_state_full(prefix);

/*:476*//*477:*/
#line 8731 "lossless.w"

vm_reset();
t= cons(synquote_new(polo),NIL);
Acc= cons(sym("null?"),t);
prefix= "(null? 'polo!)";
interpret();
tap_ok(false_p(Acc),tmsgf("false?"));
test_vm_state_full(prefix);

/*:477*//*478:*/
#line 8740 "lossless.w"

vm_reset();
t= synquote_new(cons(NIL,NIL));
Acc= cons(sym("null?"),cons(t,NIL));
prefix= "(null? '(()))";
interpret();
tap_ok(false_p(Acc),tmsgf("false?"));
test_vm_state_full(prefix);

/*:478*/
#line 8681 "lossless.w"

/*479:*/
#line 8749 "lossless.w"

vm_reset();
Acc= cons(sym("pair?"),cons(NIL,NIL));
prefix= "(pair? ())";
interpret();
tap_ok(false_p(Acc),tmsgf("false?"));
test_vm_state_full(prefix);

/*:479*//*480:*/
#line 8757 "lossless.w"

vm_reset();
t= cons(synquote_new(polo),NIL);
Acc= cons(sym("pair?"),t);
prefix= "(pair? 'polo!)";
interpret();
tap_ok(false_p(Acc),tmsgf("false?"));
test_vm_state_full(prefix);

/*:480*//*481:*/
#line 8766 "lossless.w"

vm_reset();
t= synquote_new(cons(NIL,NIL));
Acc= cons(sym("pair?"),cons(t,NIL));
prefix= "(pair? '(()))";
interpret();
tap_ok(true_p(Acc),tmsgf("true?"));
test_vm_state_full(prefix);

/*:481*/
#line 8682 "lossless.w"

/*482:*/
#line 8782 "lossless.w"

vm_reset();
Tmp_Test= cons(marco,water);
t= cons(synquote_new(polo),NIL);
t= cons(synquote_new(Tmp_Test),t);
Acc= cons(sym("set-car!"),t);
prefix= "(set-car! '(marco . |fish out of water!|) 'polo!)";
interpret();
ok= tap_ok(void_p(Acc),tmsgf("void?"));
okok= tap_ok(ok&&pair_p(Tmp_Test),tmsgf("(pair? T)"));
tap_again(ok,symbol_p(car(Tmp_Test))&&car(Tmp_Test)==polo,
tmsgf("(eq? (car T) 'polo!)"));
tap_again(okok,symbol_p(cdr(Tmp_Test))&&cdr(Tmp_Test)==water,
tmsgf("(eq? (cdr T) '|fish out of water!|)"));

/*:482*/
#line 8683 "lossless.w"

/*483:*/
#line 8797 "lossless.w"

vm_reset();
Tmp_Test= cons(water,marco);
t= cons(synquote_new(polo),NIL);
t= cons(synquote_new(Tmp_Test),t);
Acc= cons(sym("set-cdr!"),t);
prefix= "(set-cdr! '(|fish out of water!| . marco) 'polo!)";
interpret();
ok= tap_ok(void_p(Acc),tmsgf("void?"));
okok= tap_ok(ok&&pair_p(Tmp_Test),tmsgf("(pair? T)"));
tap_again(ok,symbol_p(car(Tmp_Test))&&car(Tmp_Test)==water,
tmsgf("(eq? (car T) '|fish out of water!|)"));
tap_again(okok,symbol_p(cdr(Tmp_Test))&&cdr(Tmp_Test)==polo,
tmsgf("(eq? (cdr T) 'polo!)"));

/*:483*/
#line 8684 "lossless.w"

}

/*:472*/
