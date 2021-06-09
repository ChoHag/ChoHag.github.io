/*484:*/
#line 8823 "lossless.w"

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
#line 8824 "lossless.w"

void
test_main(void){
cell t,m,p;
char*prefix;
char msg[TEST_BUFSIZE]= {0};
/*485:*/
#line 8838 "lossless.w"

vm_reset();
Acc= read_cstring((prefix= "(eval '(test!probe))"));
interpret();
t= assoc_value(Acc,sym("Env"));
tap_ok(environment_p(t),tmsgf("(environment? (assoc-value T 'Env))"));
tap_ok(t==Root,tmsgf("(eq? (assoc-value T 'Env) Root)"));


test_vm_state_full(prefix);

/*:485*//*486:*/
#line 8855 "lossless.w"

vm_reset();
Tmp_Test= env_empty();
env_set(Tmp_Test,sym("alt-test!probe"),
env_search(Root,sym("test!probe")),TRUE);
Acc= read_cstring((prefix= "(eval '(alt-test!probe) E)"));
cddr(Acc)= cons(Tmp_Test,NIL);
interpret();
t= assoc_value(Acc,sym("Env"));
tap_ok(environment_p(t),tmsgf("(environment? (assoc-value T 'Env))"));
tap_ok(t==Tmp_Test,tmsgf("(eq? (assoc-value T 'Env) E)"));
test_vm_state_full(prefix);

/*:486*//*487:*/
#line 8877 "lossless.w"

Tmp_Test= env_empty();
env_set(Tmp_Test,sym("eval"),
env_search(Root,sym("eval")),TRUE);
env_set(Tmp_Test,sym("alt-test!probe"),
env_search(Root,sym("error")),TRUE);

t= read_cstring("(alt-test!probe 'oops)");

env_set(Tmp_Test,sym("testing-program"),t,TRUE);

m= env_empty();
env_set(Tmp_Test,sym("testing-environment"),m,TRUE);
env_set(m,sym("alt-test!probe"),
env_search(Root,sym("test!probe")),TRUE);
env_set(m,sym("testing-environment"),env_empty(),TRUE);
p= read_cstring("(error wrong-program)");
env_set(m,sym("testing-program"),p,TRUE);

/*:487*//*488:*/
#line 8901 "lossless.w"

vm_reset();
prefix= "(eval testing-program testing-environment)";
Acc= read_cstring(prefix);
Env= Tmp_Test;
interpret();
t= assoc_value(Acc,sym("Env"));
tap_ok(environment_p(t),tmsgf("(environment? (assoc-value T 'Env))"));
tap_ok(t==m,tmsgf("(eq? (assoc-value T 'Env) E)"));
test_integrate_eval_unchanged(prefix,Tmp_Test,m);
test_vm_state_normal(prefix);
tap_ok(Env==Tmp_Test,tmsgf("(unchanged? Env)"));

/*:488*/
#line 8830 "lossless.w"

}

/*:484*//*490:*/
#line 8944 "lossless.w"

void
test_integrate_eval_unchanged(char*prefix,
cell outer,
cell inner)
{
boolean oki,oko,fmore;
cell fenv,feval,fprobe,fprog;
cell oeval,oprobe;
cell iprobe;
cell t;
char msg[TEST_BUFSIZE]= {0};
/*491:*/
#line 8960 "lossless.w"

oko= tap_ok(environment_p(outer),tmsgf("(environment? outer)"));
tap_ok(env_root_p(outer),tmsgf("(environment.is-root? outer)"));
if(oko){
oeval= env_search(Root,sym("eval"));
oprobe= env_search(Root,sym("error"));
t= env_layer(outer);
TEST_EVAL_FIND
if(!undefined_p(fprog))
oki= list_p(fprog,FALSE,&t)&&int_value(t)==2;


}
tap_again(oko,!fmore&&feval==oeval
&&fprobe==oprobe&&fenv==inner,
tmsgf("outer environment is unchanged"));

/*:491*/
#line 8956 "lossless.w"

/*492:*/
#line 8977 "lossless.w"

oki= tap_ok(environment_p(inner),tmsgf("(environment? inner)"));
tap_ok(env_root_p(inner),tmsgf("(environment.is-root? inner)"));
if(oki){
iprobe= env_search(Root,sym("test!probe"));
t= env_layer(inner);
TEST_EVAL_FIND
if(!undefined_p(fprog))
oki= list_p(fprog,FALSE,&t)&&int_value(t)==2;
}
tap_again(oki,!fmore&&undefined_p(feval)
&&fprobe==iprobe&&env_empty_p(fenv),
tmsgf("inner environment is unchanged"));

/*:492*/
#line 8957 "lossless.w"

}

/*:490*/
