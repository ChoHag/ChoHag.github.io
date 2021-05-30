/*484:*/
#line 8722 "lossless.w"

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
#line 8723 "lossless.w"

void
test_main(void)
{
boolean ok;
cell ie,oe,len;
cell t,m,p;
cell sn,si,sin,sinn,so,sout,soutn;
char*prefix;
char msg[TEST_BUFSIZE]= {0};


sn= sym("n");
si= sym("inner");
sin= sym("in");
sinn= sym("in-n");
so= sym("outer");
sout= sym("out");
soutn= sym("out-n");
/*485:*/
#line 8755 "lossless.w"

Env= env_extend(Root);
Tmp_Test= test_copy_env();
Acc= read_cstring(TEST_AB);
prefix= TEST_AB_PRINT;
vm_reset();
interpret();

ok= tap_ok(applicative_p(Acc),tmsgf("applicative?"));
tap_again(ok,applicative_formals(Acc)==sym("x"),tmsgf("formals"));
if(ok)t= applicative_closure(Acc);
tap_again(ok,environment_p(car(t)),tmsgf("environment?"));
tap_again(ok,test_is_env(car(t),Tmp_Test),tmsgf("closure"));

if(ok)t= cdr(t);
tap_again(ok,car(t)!=Prog,tmsgf("prog"));
test_vm_state_normal(prefix);
tap_ok(test_compare_env(Tmp_Test),tmsgf("(unchanged? Env)"));

/*:485*/
#line 8742 "lossless.w"

/*486:*/
#line 8780 "lossless.w"

Env= env_extend(Root);
Tmp_Test= cons(test_copy_env(),NIL);
Acc= read_cstring(TEST_AC);
vm_reset();
interpret();

Env= env_extend(Root);
cdr(Tmp_Test)= test_copy_env();
t= read_cstring("(LAMBDA)");
car(t)= Acc;
Acc= t;
prefix= TEST_AC_PRINT;
vm_reset();
interpret();

t= assoc_value(Acc,sym("Env"));
ok= tap_ok(environment_p(t),tmsgf("(environment? (assoc-value T 'Env))"));
tap_again(ok,test_is_env(env_parent(t),car(Tmp_Test)),
tmsgf("(eq? (assoc-value T 'Env) (env.parent E))"));
test_vm_state_normal(prefix);
tap_ok(test_compare_env(cdr(Tmp_Test)),tmsgf("(unchanged? Env)"));

/*:486*/
#line 8743 "lossless.w"

/*487:*/
#line 8821 "lossless.w"

Env= env_extend(Root);
Tmp_Test= cons(test_copy_env(),NIL);
Acc= read_cstring(TEST_ACA_INNER);
vm_reset();
interpret();

vms_push(Acc);
Env= env_extend(Root);
cdr(Tmp_Test)= test_copy_env();
Acc= read_cstring(TEST_ACA);
cadr(Acc)= vms_pop();
prefix= TEST_ACA_PRINT;
vm_reset();
interpret();

t= assoc_value(Acc,sym("Env"));
ok= tap_ok(environment_p(t),tmsgf("(environment? inner)"));
if(ok)p= env_search(t,sym("T"));
if(ok)m= assoc_value(p,sym("Env"));
tap_again(ok,environment_p(m),tmsgf("(environment? outer)"));
tap_again(ok,m!=t,tmsgf("(¬eq? outer inner)"));
tap_again(ok,test_is_env(env_parent(m),cdr(Tmp_Test)),
tmsgf("(parent? outer)"));
tap_again(ok,test_is_env(env_parent(t),car(Tmp_Test)),
tmsgf("(parent? inner)"));
test_vm_state_normal(prefix);
tap_ok(test_compare_env(cdr(Tmp_Test)),tmsgf("(unchanged? Env)"));

/*:487*/
#line 8744 "lossless.w"

/*488:*/
#line 8865 "lossless.w"

Env= env_extend(Root);
Tmp_Test= cons(test_copy_env(),NIL);
Acc= read_cstring(TEST_ACO_INNER);
vm_reset();
interpret();

vms_push(Acc);
Env= env_extend(Root);
cdr(Tmp_Test)= test_copy_env();
Acc= read_cstring(TEST_ACO);
cadr(Acc)= vms_pop();
prefix= TEST_ACO_PRINT;
vm_reset();
interpret();

t= assoc_value(Acc,sym("Env"));
p= car(assoc_value(Acc,sym("Args")));
m= assoc_value(p,sym("Env"));
ok= tap_ok(environment_p(m),tmsgf("(environment? outer)"));
tap_again(ok,test_is_env(env_parent(m),cdr(Tmp_Test)),
tmsgf("(parent? outer)"));
ok= tap_ok(environment_p(t),tmsgf("(environment? inner)"));

if(ok)p= env_search(t,sym("E"));
tap_again(ok,environment_p(p),tmsgf("(environment? E)"));
tap_again(ok,test_is_env(p,m),tmsgf("operative environment"));
tap_ok(!test_is_env(m,t),tmsgf("(¬eq? outer inner)"));
tap_again(ok,test_is_env(env_parent(t),car(Tmp_Test)),
tmsgf("(parent? inner)"));
test_vm_state_normal(prefix);
tap_ok(test_compare_env(cdr(Tmp_Test)),tmsgf("(unchanged? Env)"));

/*:488*/
#line 8745 "lossless.w"

/*489:*/
#line 8920 "lossless.w"

Env= env_extend(Root);
Tmp_Test= cons(test_copy_env(),NIL);
Acc= read_cstring(TEST_ARA_BUILD);
vm_reset();
interpret();

vms_push(Acc);
Env= env_extend(Root);
cdr(Tmp_Test)= test_copy_env();
Acc= read_cstring(TEST_ARA_CALL);
caar(Acc)= vms_pop();
prefix= TEST_ARA_PRINT;
vm_reset();
interpret();

ie= assoc_value(Acc,sym("Env"));
ok= tap_ok(environment_p(ie),tmsgf("(environment? inner)"));
tap_again(ok,env_search(ie,sn)==sinn,tmsgf("(eq? n 'in-n)"));
tap_again(ok,env_search(ie,si)==sin,tmsgf("(eq? inner 'in)"));
tap_again(ok,env_search(ie,so)==sout,tmsgf("(eq? outer 'out)"));

if(ok)oe= env_parent(ie);
tap_again(ok,environment_p(oe),tmsgf("(environment? outer)"));
tap_again(ok,env_search(oe,sn)==soutn,tmsgf("(eq? n 'out-n)"));
tap_again(ok,undefined_p(env_search(oe,si)),tmsgf("(¬defined? inner)"));
tap_again(ok,env_search(oe,so)==sout,tmsgf("(eq? outer 'out)"));
tap_again(ok,test_is_env(env_parent(oe),car(Tmp_Test)),
tmsgf("(parent? outer)"));
test_vm_state_normal(prefix);
tap_ok(test_compare_env(cdr(Tmp_Test)),tmsgf("(unchanged? Env)"));

/*:489*/
#line 8746 "lossless.w"

/*490:*/
#line 8965 "lossless.w"

Env= env_extend(Root);
Tmp_Test= cons(test_copy_env(),NIL);
Acc= read_cstring(TEST_ARO_BUILD);
vm_reset();
interpret();

vms_push(Acc);
Env= env_extend(Root);
cdr(Tmp_Test)= test_copy_env();
Acc= read_cstring(TEST_ARO_CALL);
caar(Acc)= vms_pop();
prefix= TEST_ARO_PRINT;
vm_reset();
interpret();

ie= assoc_value(Acc,sym("Env"));
ok= tap_ok(environment_p(ie),tmsgf("(environment? inner)"));
tap_again(ok,undefined_p(env_here(ie,sn)),tmsgf("(¬lifted? n)"));
tap_again(ok,undefined_p(env_here(ie,so)),tmsgf("(¬lifted? outer)"));
tap_again(ok,env_search(ie,sn)==soutn,tmsgf("(eq? n 'out-n)"));
tap_again(ok,env_search(ie,so)==sout,tmsgf("(eq? outer 'out)"));

if(ok)oe= env_parent(ie);
tap_again(ok,environment_p(oe),tmsgf("(environment? outer)"));
tap_again(ok,env_search(ie,sn)==soutn,tmsgf("(eq? n 'out-n)"));
tap_again(ok,env_search(ie,so)==sout,tmsgf("(eq? outer 'out)"));
tap_again(ok,undefined_p(env_search(oe,sym("A"))),tmsgf("(¬defined? A)"));
tap_again(ok,undefined_p(env_search(oe,sym("E"))),tmsgf("(¬defined? E)"));
tap_again(ok,test_is_env(env_parent(oe),car(Tmp_Test)),
tmsgf("(parent? outer)"));

if(ok)t= env_search(ie,sym("A"));
tap_again(ok,true_p(list_p(t,FALSE,&len)),tmsgf("(list? A)"));
tap_again(ok,int_value(len)==2,tmsgf("length"));
tap_again(ok,syntax_p(car(t))&&cdar(t)==sin
&&syntax_p(cadr(t))&&cdadr(t)==sinn,tmsgf("unevaluated"));
tap_again(ok,test_is_env(env_search(ie,sym("E")),cdr(Tmp_Test)),
tmsgf("(eq? E Env)"));
test_vm_state_normal(prefix);
tap_ok(test_compare_env(cdr(Tmp_Test)),tmsgf("(unchanged? Env)"));

/*:490*/
#line 8747 "lossless.w"

}

/*:484*/
