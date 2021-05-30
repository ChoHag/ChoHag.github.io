/*491:*/
#line 9012 "lossless.w"

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
#line 9013 "lossless.w"

void
test_main(void)
{
boolean ok;
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
/*492:*/
#line 9040 "lossless.w"

Env= env_extend(Root);
Tmp_Test= test_copy_env();
Acc= read_cstring(TEST_OB);
prefix= TEST_OB_PRINT;
vm_reset();
interpret();

ok= tap_ok(operative_p(Acc),tmsgf("operative?"));
tap_again(ok,pair_p(t= operative_formals(Acc)),tmsgf("formals"));
if(ok)t= operative_closure(Acc);
tap_again(ok,environment_p(car(t)),tmsgf("environment?"));
tap_again(ok,car(t)==Env,tmsgf("closure"));

if(ok)t= cdr(t);
tap_again(ok,car(t)!=Prog,tmsgf("prog"));
test_vm_state_normal(prefix);
tap_ok(test_compare_env(Tmp_Test),tmsgf("(unchanged? Env)"));

/*:492*/
#line 9029 "lossless.w"

/*493:*/
#line 9074 "lossless.w"

Env= env_extend(Root);
Tmp_Test= cons(test_copy_env(),NIL);
Acc= read_cstring(TEST_OC);
vm_reset();
interpret();

Env= env_extend(Root);
cdr(Tmp_Test)= test_copy_env();
t= read_cstring("(VOV)");
car(t)= Acc;
Acc= t;
prefix= TEST_OC_PRINT;
vm_reset();
interpret();

t= assoc_value(Acc,sym("Env"));
ok= tap_ok(environment_p(t),
tmsgf("(environment? (assoc-value T 'Env))"));
tap_again(ok,test_is_env(env_parent(t),car(Tmp_Test)),
tmsgf("(eq? (assoc-value T 'Env) (env.parent E))"));
if(ok)p= env_search(t,sym("E"));
tap_again(ok,environment_p(p),tmsgf("(environment? E)"));
tap_again(ok,test_is_env(p,cdr(Tmp_Test)),
tmsgf("(eq? T (current-environment))"));
test_vm_state_normal(prefix);
tap_ok(test_compare_env(cdr(Tmp_Test)),tmsgf("(unchanged? Env)"));

/*:493*/
#line 9030 "lossless.w"

/*494:*/
#line 9123 "lossless.w"

Env= env_extend(Root);
Tmp_Test= cons(test_copy_env(),NIL);
Acc= read_cstring(TEST_OCA_INNER);
vm_reset();
interpret();

vms_push(Acc);
Env= env_extend(Root);
cdr(Tmp_Test)= test_copy_env();
Acc= read_cstring(TEST_OCA);
cadr(Acc)= vms_pop();
prefix= TEST_OCA_PRINT;
vm_reset();
interpret();

t= assoc_value(cdr(Acc),sym("Env"));
ok= tap_ok(environment_p(t),
tmsgf("(environment? (assoc-value (cdr T) 'Env))"));
tap_again(ok,test_is_env(env_parent(t),cdr(Tmp_Test)),
tmsgf("(parent? E)"));
tap_again(ok,test_is_env(env_search(t,sym("E")),cdr(Tmp_Test)),
tmsgf("(eq? E vov/env)"));
p= assoc_value(car(Acc),sym("Env"));
ok= tap_ok(environment_p(p),
tmsgf("(environment? (assoc-value (car T) 'Env))"));
tap_again(ok,test_is_env(env_parent(p),car(Tmp_Test)),
tmsgf("(parent? E')"));
test_vm_state_normal(prefix);
tap_ok(test_compare_env(cdr(Tmp_Test)),tmsgf("(unchanged? Env)"));

/*:494*/
#line 9031 "lossless.w"

/*495:*/
#line 9173 "lossless.w"

Env= env_extend(Root);
Tmp_Test= cons(test_copy_env(),NIL);
Acc= read_cstring(TEST_OCO_INNER);
vm_reset();
interpret();

vms_push(Acc);
Env= env_extend(Root);
cdr(Tmp_Test)= test_copy_env();
Acc= read_cstring(TEST_OCO);
cadr(Acc)= vms_pop();
prefix= TEST_OCO_PRINT;
vm_reset();
interpret();

t= assoc_value(car(Acc),sym("Env"));
ok= tap_ok(environment_p(t),
tmsgf("(environment? (assoc-value (car T) 'Env))"));
tap_again(ok,test_is_env(env_parent(t),car(Tmp_Test)),
tmsgf("(parent? E)"));
m= env_here(t,sym("yE"));
tap_again(ok,!undefined_p(m),tmsgf("(env.exists? E yE)"));

p= assoc_value(cdr(Acc),sym("Env"));
ok= tap_ok(environment_p(t),
tmsgf("(environment? (assoc-value (cdr T) 'Env))"));
tap_again(ok,test_is_env(m,p),tmsgf("operative environment"));
tap_ok(!test_is_env(p,t),tmsgf("(¬eq? E' E)"));
tap_again(ok,test_is_env(env_parent(p),cdr(Tmp_Test)),
tmsgf("(parent? E')"));
tap_again(ok,!undefined_p(env_here(p,sym("xE"))),
tmsgf("(env.exists? E' xE)"));
tap_again(ok,!undefined_p(env_here(p,sym("xA"))),
tmsgf("(env.exists? E' xA)"));

tap_ok(test_is_env(p,m),tmsgf("(eq? E' yE)"));

test_vm_state_normal(prefix);
tap_ok(test_compare_env(cdr(Tmp_Test)),tmsgf("(unchanged? Env)"));

/*:495*/
#line 9032 "lossless.w"

/*496:*/
#line 9233 "lossless.w"

Env= env_extend(Root);
Tmp_Test= cons(test_copy_env(),NIL);
Acc= read_cstring(TEST_ORA_BUILD);
vm_reset();
interpret();

vms_push(Acc);
Env= env_extend(Root);
cdr(Tmp_Test)= test_copy_env();
Acc= read_cstring(TEST_ORA_CALL);
caar(Acc)= vms_pop();
prefix= TEST_ORA_PRINT;
vm_reset();
interpret();

t= assoc_value(Acc,sym("Env"));
ok= tap_ok(environment_p(t),
tmsgf("(environment? (assoc-value (cdr T) 'Env))"));
m= env_here(t,sym("n"));
tap_again(ok,m==sinn,tmsgf("(eq? (env.here E n) 'in-n)"));
m= env_here(t,sym("inner"));
tap_again(ok,m==sin,tmsgf("(eq? (env.here E inner) 'in)"));
tap_again(ok,undefined_p(env_here(t,sym("outer"))),
tmsgf("(¬exists-here? E outer)"));
m= env_search(t,sym("outer"));
tap_again(ok,m==sout,tmsgf("(eq? (env.lookup E inner) 'out)"));

if(ok)p= env_parent(t);
tap_again(ok,!undefined_p(env_here(p,sym("yE"))),
tmsgf("(exists? (env.parent E) yE)"));
tap_again(ok,test_is_env(env_parent(p),car(Tmp_Test)),
tmsgf("(env.parent? E')"));
m= env_here(p,sym("n"));
tap_again(ok,m==soutn,tmsgf("(eq? (env.here E n) 'out-n)"));
m= env_here(p,sym("inner"));
tap_again(ok,m==sout,tmsgf("(eq? (env.here E inner) 'out)"));
m= env_here(p,sym("outer"));
tap_again(ok,m==sout,tmsgf("(eq? (env.lookup E inner) 'out)"));
test_vm_state_normal(prefix);
tap_ok(test_compare_env(cdr(Tmp_Test)),tmsgf("(unchanged? Env)"));

/*:496*/
#line 9033 "lossless.w"

/*497:*/
#line 9293 "lossless.w"

Env= env_extend(Root);
Tmp_Test= cons(test_copy_env(),NIL);
Acc= read_cstring(TEST_ORO_BUILD);
vm_reset();
interpret();

vms_push(Acc);
Env= env_extend(Root);
cdr(Tmp_Test)= test_copy_env();
Acc= read_cstring(TEST_ORO_CALL);
caar(Acc)= vms_pop();
prefix= TEST_ORO_PRINT;
vm_reset();
interpret();

t= assoc_value(Acc,sym("Env"));
ok= tap_ok(environment_p(t),
tmsgf("(environment? (assoc-value T 'Env))"));
if(ok)m= env_here(t,sym("oE"));
tap_again(ok,environment_p(m),tmsgf("(environment? oE)"));
tap_again(ok,m==cdr(Tmp_Test),tmsgf("(eq? E Env)"));
if(ok)m= env_parent(t);
tap_again(ok,!undefined_p(env_here(m,sym("A"))),
tmsgf("(env.exists? E' A)"));
if(ok)p= env_here(m,sym("E"));
tap_again(ok,!undefined_p(env_here(m,sym("E"))),
tmsgf("(env.exists? E' E)"));
tap_again(ok,p==cdr(Tmp_Test),tmsgf("(eq? E'' Env)"));
tap_again(ok,env_parent(m)==car(Tmp_Test),tmsgf("(eq? (env.parent E') Env)"));
test_vm_state_normal(prefix);
tap_ok(test_compare_env(cdr(Tmp_Test)),tmsgf("(unchanged? Env)"));

/*:497*/
#line 9034 "lossless.w"

}

/*:491*/
