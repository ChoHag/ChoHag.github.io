/*454:*/
#line 8247 "lossless.w"

/*261:*/
#line 4942 "lossless.w"

#define LL_TEST 1
#include "lossless.h"
void test_main(void);

int
main(int argc __unused,
char**argv __unused)
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

/*:261*/
#line 8248 "lossless.w"

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
/*455:*/
#line 8274 "lossless.w"

vm_reset();
Acc= read_cstring(prefix= "(cons 24 42)");
interpret();
ok= tap_ok(pair_p(Acc),tmsgf("pair?"));
tap_again(ok,integer_p(car(Acc))&&int_value(car(Acc))==24,
tmsgf("car"));
tap_again(ok,integer_p(car(Acc))&&int_value(cdr(Acc))==42,
tmsgf("cdr"));
test_vm_state_full(prefix);

/*:455*/
#line 8259 "lossless.w"

/*456:*/
#line 8285 "lossless.w"

vm_reset();
t= cons(int_new(42),polo);
t= cons(synquote_new(t),NIL);
Tmp_Test= Acc= cons(sym("car"),t);
prefix= "(car '(42 . polo))";
interpret();
tap_ok(integer_p(Acc)&&int_value(Acc)==42,tmsgf("integer?"));
test_vm_state_full(prefix);

/*:456*/
#line 8260 "lossless.w"

/*457:*/
#line 8295 "lossless.w"

vm_reset();
Acc= cons(sym("cdr"),t);
prefix= "(cdr '(42 . polo))";
interpret();
tap_ok(symbol_p(Acc)&&Acc==polo,tmsgf("symbol?"));
test_vm_state_full(prefix);

/*:457*/
#line 8261 "lossless.w"

/*458:*/
#line 8303 "lossless.w"

vm_reset();
t= cons(NIL,NIL);
Acc= cons(sym("null?"),t);
prefix= "(null? ())";
interpret();
tap_ok(true_p(Acc),tmsgf("true?"));
test_vm_state_full(prefix);

/*:458*//*459:*/
#line 8312 "lossless.w"

vm_reset();
t= cons(synquote_new(polo),NIL);
Acc= cons(sym("null?"),t);
prefix= "(null? 'polo!)";
interpret();
tap_ok(false_p(Acc),tmsgf("false?"));
test_vm_state_full(prefix);

/*:459*//*460:*/
#line 8321 "lossless.w"

vm_reset();
t= synquote_new(cons(NIL,NIL));
Acc= cons(sym("null?"),cons(t,NIL));
prefix= "(null? '(()))";
interpret();
tap_ok(false_p(Acc),tmsgf("false?"));
test_vm_state_full(prefix);

/*:460*/
#line 8262 "lossless.w"

/*461:*/
#line 8330 "lossless.w"

vm_reset();
Acc= cons(sym("pair?"),cons(NIL,NIL));
prefix= "(pair? ())";
interpret();
tap_ok(false_p(Acc),tmsgf("false?"));
test_vm_state_full(prefix);

/*:461*//*462:*/
#line 8338 "lossless.w"

vm_reset();
t= cons(synquote_new(polo),NIL);
Acc= cons(sym("pair?"),t);
prefix= "(pair? 'polo!)";
interpret();
tap_ok(false_p(Acc),tmsgf("false?"));
test_vm_state_full(prefix);

/*:462*//*463:*/
#line 8347 "lossless.w"

vm_reset();
t= synquote_new(cons(NIL,NIL));
Acc= cons(sym("pair?"),cons(t,NIL));
prefix= "(pair? '(()))";
interpret();
tap_ok(true_p(Acc),tmsgf("true?"));
test_vm_state_full(prefix);

/*:463*/
#line 8263 "lossless.w"

/*464:*/
#line 8363 "lossless.w"

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

/*:464*/
#line 8264 "lossless.w"

/*465:*/
#line 8378 "lossless.w"

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

/*:465*/
#line 8265 "lossless.w"

}

/*:454*/
