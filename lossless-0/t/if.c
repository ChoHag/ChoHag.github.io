/*475:*/
#line 8578 "lossless.w"

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
#line 8579 "lossless.w"

void
test_main(void)
{
cell fcorrect,tcorrect,fwrong,twrong;
cell talt,tcons,tq;
cell marco,polo,t;
char*prefix= NULL;
char msg[TEST_BUFSIZE]= {0};
fcorrect= sym("correct-false");
fwrong= sym("wrong-false");
tcorrect= sym("correct-true");
twrong= sym("wrong-true");
talt= sym("test-alternate");
tcons= sym("test-consequent");
tq= sym("test-query");
marco= sym("marco?");
polo= sym("polo!");
/*476:*/
#line 8606 "lossless.w"

vm_reset();
t= cons(synquote_new(polo),NIL);
t= cons(TRUE,t);
Acc= cons(sym("if"),t);
prefix= "(if #t 'polo!)";
interpret();
tap_ok(symbol_p(Acc)&&Acc==polo,tmsgf("symbol?"));
test_vm_state_full(prefix);

/*:476*//*477:*/
#line 8618 "lossless.w"

vm_reset();
t= cons(synquote_new(marco),NIL);
t= cons(FALSE,t);
Acc= cons(sym("if"),t);
prefix= "(if #f 'marco?)";
interpret();
tap_ok(void_p(Acc),tmsgf("void?"));
test_vm_state_full(prefix);

/*:477*//*478:*/
#line 8630 "lossless.w"

vm_reset();
t= cons(synquote_new(polo),NIL);
t= cons(synquote_new(marco),t);
t= cons(TRUE,t);
Acc= cons(sym("if"),t);
prefix= "(if #t 'marco? 'polo!)";
interpret();
tap_ok(symbol_p(Acc)&&Acc==marco,tmsgf("symbol?"));
test_vm_state_full(prefix);

/*:478*//*479:*/
#line 8643 "lossless.w"

vm_reset();
t= cons(synquote_new(polo),NIL);
t= cons(synquote_new(marco),t);
t= cons(FALSE,t);
Acc= cons(sym("if"),t);
prefix= "(if #f 'marco? 'polo!)";
interpret();
tap_ok(symbol_p(Acc)&&Acc==polo,tmsgf("symbol?"));
test_vm_state_full(prefix);

/*:479*/
#line 8597 "lossless.w"

/*480:*/
#line 8660 "lossless.w"

t= env_layer(Tmp_Test= Root);
Root= env_empty();
for(;!null_p(t);t= cdr(t))
if(caar(t)!=sym("if"))
env_set(Root,caar(t),cadar(t),btrue);
env_set(Root,sym("if"),env_search(Tmp_Test,sym("error")),btrue);
env_set(Root,talt,fwrong,btrue);
env_set(Root,tcons,twrong,btrue);
env_set(Root,tq,VOID,btrue);
Env= env_extend(Root);
env_set(Env,sym("if"),env_search(Tmp_Test,sym("if")),btrue);
env_set(Env,talt,fcorrect,btrue);
env_set(Env,tcons,tcorrect,btrue);
env_set(Env,tq,VOID,btrue);

/*:480*//*481:*/
#line 8679 "lossless.w"

vm_reset();
env_set(Env,tq,FALSE,bfalse);
t= cons(talt,NIL);
t= cons(tcons,t);
t= cons(tq,t);
Acc= cons(sym("if"),t);
prefix= "(let ((query #f)) (if query consequent alternate))";
t= Env;
interpret();
tap_ok(symbol_p(Acc)&&Acc==fcorrect,tmsgf("symbol?"));
test_vm_state_normal(prefix);
tap_ok(Env==t,tmsgf("(unchanged? Env)"));

/*:481*//*482:*/
#line 8693 "lossless.w"

vm_reset();
env_set(Env,tq,TRUE,bfalse);
t= cons(talt,NIL);
t= cons(tcons,t);
t= cons(tq,t);
Acc= cons(sym("if"),t);
prefix= "(let ((query #t)) (if query consequent alternate))";
t= Env;
interpret();
tap_ok(symbol_p(Acc)&&Acc==tcorrect,tmsgf("symbol?"));
test_vm_state_normal(prefix);
tap_ok(Env==t,tmsgf("(unchanged? Env)"));

/*:482*//*483:*/
#line 8710 "lossless.w"

Root= Tmp_Test;

/*:483*/
#line 8598 "lossless.w"

}

/*:475*/
