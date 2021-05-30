/*376:*/
#line 7216 "lossless.w"

/*255:*/
#line 4821 "lossless.w"

#define LL_TEST
#include "lossless.h"
#include "llt.h"

/*:255*/
#line 7217 "lossless.w"


struct llt_Fixture{
LLT_FIXTURE_HEADER;
/*377:*/
#line 7246 "lossless.w"

boolean custom_p;
boolean env_found_p;
cell env_new_p;
int extra_stack;
boolean had_ex_p;
int opcode;
cell set_Acc;
cell sym_mpft[4];
boolean want_ex_p;

/*:377*/
#line 7221 "lossless.w"

/*378:*/
#line 7260 "lossless.w"

boolean mutate_Acc_p;
boolean mutate_Env_p;
boolean mutate_Fp_p;
boolean mutate_Ip_p;
boolean mutate_Prog_p;
boolean mutate_RTS_p;
boolean mutate_RTSp_p;
boolean mutate_Root_p;
boolean mutate_VMS_p;

int want_Ip;
int want_Fp;
int want_RTSp;

/*:378*/
#line 7222 "lossless.w"

/*379:*/
#line 7279 "lossless.w"

cell backup_Env;
llt_buffer*save_Acc;
llt_buffer*save_Env;
llt_buffer*save_Prog;
llt_buffer*save_RTS;
llt_buffer*save_Root;
llt_buffer*save_VMS;
int save_Fp;
jmp_buf save_goto;
int save_Ip;
int save_RTSp;

/*:379*/
#line 7223 "lossless.w"

};

/*256:*/
#line 4826 "lossless.w"

int
main(int argc __unused,
char**argv __unused)
{
llt_buffer*suite;
if(argc> 1){
printf("usage: %s",argv[0]);
return EXIT_FAILURE;
}
#ifndef LLT_NOINIT
vm_init();
#endif
suite= llt_prepare();
llt_main(suite->len,(llt_Fixture*)suite->data);
free(suite);
tap_plan(0);
}

/*:256*//*257:*/
#line 4845 "lossless.w"

boolean
llt_main(size_t count,
llt_Fixture*suite)
{
int i;
int d,f0,f1;
boolean all,ok;
char buf[TEST_BUFSIZE]= {0},*name;
all= btrue;
for(i= 0;i<(int)count;i++){
if(suite[i].suffix)
snprintf(buf,TEST_BUFSIZE,"%s (%s)",
suite[i].name,suite[i].suffix);
else
snprintf(buf,TEST_BUFSIZE,"%s",suite[i].name);
/*258:*/
#line 4870 "lossless.w"

name= (char*)suite[i].name;
suite[i].name= (char*)buf;
if(suite[i].prepare)
suite[i].prepare(suite+i);
f0= test_count_free_list();
suite[i].act(suite+i);
f1= test_count_free_list();
ok= suite[i].test(suite+i);
if(suite[i].destroy)
suite[i].destroy(suite+i);
suite[i].name= name;

/*:258*/
#line 4861 "lossless.w"

if((d= f0-f1)> 0&&!suite[i].skip_gc_p){
/*259:*/
#line 4887 "lossless.w"

int j,k;
for(j= d;j>=0;j--){
sprintf(buf,"%s: trigger gc at %d free cells",
name,j);
name= (char*)suite[i].name;
suite[i].name= buf;
if(suite[i].prepare)
suite[i].prepare(suite+i);
d= test_count_free_list();
for(k= 0;k<d-j;k++)
cons(NIL,NIL);
suite[i].act(suite+i);
ok= suite[i].test(suite+i)&&ok;
if(suite[i].destroy)
suite[i].destroy(suite+i);
suite[i].name= name;
}
if(suite[i].suffix)
snprintf(buf,TEST_BUFSIZE,"%s (%s)",
name,suite[i].suffix);
else
snprintf(buf,TEST_BUFSIZE,"%s",name);
suite[i].name= buf;

/*:259*/
#line 4863 "lossless.w"

}
tap_more(all,ok,buf);
}
return all;
}

/*:257*//*260:*/
#line 4912 "lossless.w"

llt_buffer*
llt_prepare(void)
{
llt_fixture*t;
llt_buffer*f,*r;
size_t old;
int i;
r= llt_alloc(0,llt_Fixture);
for(t= Test_Fixtures;*t!=NULL;t++){
f= (*t)();
old= r->len;
llt_grow_by(r,f->len);
bcopy(f->data,((llt_Fixture*)r->data)+old,
f->len*f->size);
free(f);
}
for(i= 0;i<(int)r->len;i++)
((llt_Fixture*)r->data)[i].id= i;
return r;
}

/*:260*/
#line 7226 "lossless.w"


/*380:*/
#line 7297 "lossless.w"

void
llt_Interpreter_prepare(llt_Fixture*fix)
{
fix->sym_mpft[0]= sym(LLT_VALUE_MARCO);
fix->sym_mpft[1]= sym(LLT_VALUE_POLO);
fix->sym_mpft[2]= sym(LLT_VALUE_FISH);
fix->sym_mpft[3]= sym(LLT_TEST_VARIABLE);
if(!fix->custom_p){
Prog= vector_new(2,int_new(OP_HALT));
vector_ref(Prog,0)= int_new(fix->opcode);
Ip= 0;
}
if(!fix->mutate_Acc_p)
fix->save_Acc= llt_serialise(Acc,bfalse);
if(!fix->mutate_Prog_p)
fix->save_Prog= llt_serialise(Prog,bfalse);
if(!fix->mutate_Env_p)
fix->save_Env= llt_serialise(Env,bfalse);
if(!fix->mutate_Root_p)
fix->save_Root= llt_serialise(Root,bfalse);
if(!fix->mutate_VMS_p)
fix->save_VMS= llt_serialise(VMS,bfalse);
if(!fix->mutate_RTS_p)
fix->save_RTS= llt_serialise(RTS,bfalse);
if(!fix->mutate_Fp_p)
fix->save_Fp= Fp;
if(!fix->mutate_Ip_p)
fix->save_Ip= Ip;
if(!fix->mutate_RTSp_p)
fix->save_RTSp= RTSp;
bcopy(Goto_Error,fix->save_goto,sizeof(jmp_buf));
Error_Handler= btrue;
}

/*:380*//*381:*/
#line 7332 "lossless.w"

void
llt_Interpreter_destroy(llt_Fixture*fix)
{
free(fix->save_Acc);
free(fix->save_Env);
free(fix->save_Prog);
free(fix->save_RTS);
free(fix->save_Root);
free(fix->save_VMS);
VMS= RTS= NIL;
RTSp= -1;
RTS_Size= 0;
bcopy(fix->save_goto,Goto_Begin,sizeof(jmp_buf));
Error_Handler= bfalse;
}

/*:381*//*382:*/
#line 7349 "lossless.w"

void
llt_Interpreter_act(llt_Fixture*fix __unused)
{

fix->had_ex_p= bfalse;
if(!setjmp(Goto_Begin))
interpret();
else
fix->had_ex_p= btrue;
}

/*:382*//*383:*/
#line 7365 "lossless.w"

boolean
llt_Interpreter_test(llt_Fixture*fix)
{
char buf[TEST_BUFSIZE];
boolean all= btrue;
if(!fix->mutate_Acc_p)
llt_Interpreter_test_compare(Acc);
if(!fix->mutate_Env_p)
llt_Interpreter_test_compare(Env);
if(!fix->mutate_Fp_p)
tap_more(all,Fp==fix->save_Fp,
fpmsgf("Fp is unchanged"));
else
tap_more(all,Fp==fix->want_Fp,
fpmsgf("Fp is changed correctly"));
if(!fix->mutate_Ip_p)
tap_more(all,Ip==fix->save_Ip,
fpmsgf("Ip is unchanged"));
else
tap_more(all,Ip==fix->want_Ip,
fpmsgf("Ip is changed correctly"));
if(!fix->mutate_Prog_p)
llt_Interpreter_test_compare(Prog);
if(!fix->mutate_RTS_p)
llt_Interpreter_test_compare(RTS);
if(!fix->mutate_RTSp_p)
tap_more(all,RTSp==fix->save_RTSp,
fpmsgf("RTSp is unchanged"));
else
tap_more(all,RTSp==fix->want_RTSp,
fpmsgf("RTSp is changed correctly"));
if(!fix->mutate_Root_p)
llt_Interpreter_test_compare(Root);
if(!fix->mutate_VMS_p)
llt_Interpreter_test_compare(VMS);
if(fix->want_ex_p)
tap_more(all,fix->had_ex_p,
fpmsgf("an error was raised"));
else
tap_more(all,!fix->had_ex_p,
fpmsgf("an error was not raised"));
return all;
}

/*:383*//*384:*/
#line 7410 "lossless.w"

void
llt_Interpreter_fix(llt_Fixture*fix,
const char*name)
{
fix->name= (char*)name;
fix->prepare= llt_Interpreter_prepare;
fix->destroy= llt_Interpreter_destroy;
fix->act= llt_Interpreter_act;
fix->test= llt_Interpreter_test;
fix->opcode= OP_NOOP;
fix->mutate_Ip_p= btrue;
fix->want_Ip= 1;
}

/*:384*//*391:*/
#line 7446 "lossless.w"

void
llt_Interpreter__OP_CYCLE_prepare(llt_Fixture*fix)
{
int i;
for(i= 0;i<fix->extra_stack;i++)
rts_push(int_new(42+3*i));
rts_push(int_new(42));
rts_push(sym("question?"));
llt_Interpreter_prepare(fix);
}

/*:391*//*392:*/
#line 7462 "lossless.w"

boolean
llt_Interpreter__OP_CYCLE_test(llt_Fixture*fix)
{
char buf[TEST_BUFSIZE];
boolean ok= llt_Interpreter_test(fix);
cell top,next;
if(RTSp!=fix->save_RTSp){
tap_fail(fpmsgf("cannot test stack contents"));
tap_fail(fpmsgf("cannot test stack contents"));
return bfalse;
}
top= rts_pop(1);
next= rts_pop(1);
tap_more(ok,top==int_new(42),
fpmsgf("the stack top is correct"));
tap_more(ok,next==sym("question?"),
fpmsgf("the next stack item is correct"));
return ok;
}

/*:392*//*393:*/
#line 7483 "lossless.w"

llt_buffer*
llt_Interpreter__OP_CYCLE(void)
{
llt_buffer*r;
llt_Fixture*fix;
r= llt_alloc(2,llt_Fixture);
fix= (llt_Fixture*)r->data;
llt_Interpreter_fix(fix+0,__func__);
llt_Interpreter_fix(fix+1,__func__);
fix[0].opcode= fix[1].opcode= OP_CYCLE;
fix[0].prepare= fix[1].prepare= llt_Interpreter__OP_CYCLE_prepare;
fix[0].test= fix[1].test= llt_Interpreter__OP_CYCLE_test;
fix[0].mutate_RTS_p= fix[1].mutate_RTS_p= btrue;
fix[0].suffix= "empty stack";
fix[1].extra_stack= 3;
fix[1].suffix= "stack in use";
return r;
}

/*:393*//*395:*/
#line 7509 "lossless.w"

void
llt_Interpreter__OP_ENV_MUTATE_M_prepare(llt_Fixture*fix)
{
Prog= vector_new(4,int_new(OP_HALT));
vector_ref(Prog,0)= int_new(OP_ENV_MUTATE_M);
vector_ref(Prog,1)= sym(LLT_TEST_VARIABLE);
vector_ref(Prog,2)= fix->env_new_p;
Ip= 0;
Acc= sym(LLT_VALUE_POLO);
Tmp_Test= fix->backup_Env= env_empty();
rts_push(fix->backup_Env);
if(false_p(fix->env_new_p))
env_set(fix->backup_Env,
sym(LLT_TEST_VARIABLE),sym(LLT_VALUE_FISH),FALSE);
llt_Interpreter_prepare(fix);
}

/*:395*//*396:*/
#line 7527 "lossless.w"

boolean
llt_Interpreter__OP_ENV_MUTATE_M_test(llt_Fixture*fix)
{
char buf[TEST_BUFSIZE];
boolean ok= llt_Interpreter_test(fix);
cell found;
tap_more(ok,void_p(Acc),fpmsgf("Acc is void"));
found= env_here(fix->backup_Env,fix->sym_mpft[3]);
tap_more(ok,found==fix->sym_mpft[1],fpmsgf("the value is set"));
return ok;
}

/*:396*//*397:*/
#line 7540 "lossless.w"

llt_buffer*
llt_Interpreter__OP_ENV_MUTATE_M(void)
{
llt_buffer*r;
llt_Fixture*fix;
r= llt_alloc(2,llt_Fixture);
fix= (llt_Fixture*)r->data;
llt_Interpreter_fix(fix+0,__func__);
llt_Interpreter_fix(fix+1,__func__);
fix[0].custom_p= fix[1].custom_p= btrue;
fix[0].prepare= fix[1].prepare
= llt_Interpreter__OP_ENV_MUTATE_M_prepare;
fix[0].test= fix[1].test= llt_Interpreter__OP_ENV_MUTATE_M_test;
fix[0].want_Ip= fix[1].want_Ip= 3;
fix[0].mutate_Acc_p= fix[1].mutate_Acc_p= btrue;
fix[0].mutate_RTS_p= fix[1].mutate_RTS_p= btrue;
fix[0].mutate_RTSp_p= fix[1].mutate_RTSp_p= btrue;
fix[0].want_RTSp= fix[1].want_RTSp= -1;
fix[0].suffix= "already bound";
fix[0].env_new_p= FALSE;
fix[1].suffix= "not bound";
fix[1].env_new_p= TRUE;
return r;
}

/*:397*//*402:*/
#line 7578 "lossless.w"

llt_buffer*
llt_Interpreter__OP_HALT(void)
{
llt_buffer*r= llt_alloc(1,llt_Fixture);
llt_Interpreter_fix((llt_Fixture*)r->data,__func__);
((llt_Fixture*)r->data)->opcode= OP_HALT;
((llt_Fixture*)r->data)->mutate_Ip_p= bfalse;
return r;
}

/*:402*//*403:*/
#line 7591 "lossless.w"

void
llt_Interpreter__OP_JUMP_prepare(llt_Fixture*fix)
{
Prog= vector_new(4,int_new(OP_HALT));
vector_ref(Prog,0)= int_new(OP_JUMP);
vector_ref(Prog,1)= int_new(3);
Ip= 0;
llt_Interpreter_prepare(fix);
}

/*:403*//*404:*/
#line 7602 "lossless.w"

llt_buffer*
llt_Interpreter__OP_JUMP(void)
{
llt_buffer*r= llt_alloc(1,llt_Fixture);
llt_Interpreter_fix((llt_Fixture*)r->data,__func__);
((llt_Fixture*)r->data)->prepare= llt_Interpreter__OP_JUMP_prepare;
((llt_Fixture*)r->data)->want_Ip= 3;
((llt_Fixture*)r->data)->custom_p= btrue;
return r;
}

/*:404*//*405:*/
#line 7617 "lossless.w"

void
llt_Interpreter__OP_JUMP_FALSE_prepare(llt_Fixture*fix)
{
Prog= vector_new(4,int_new(OP_HALT));
vector_ref(Prog,0)= int_new(fix->opcode);
vector_ref(Prog,1)= int_new(3);
Ip= 0;
Acc= fix->set_Acc;
llt_Interpreter_prepare(fix);
}

/*:405*//*406:*/
#line 7629 "lossless.w"

boolean
llt_Interpreter__OP_JUMP_FALSE_test(llt_Fixture*fix)
{
char buf[TEST_BUFSIZE];
boolean ok= llt_Interpreter_test(fix);
if(void_p(fix->set_Acc)){
tap_more(ok,exception_p(Acc)
&&ex_id(Acc)==Sym_ERR_UNEXPECTED
&&void_p(ex_detail(Acc)),
fpmsgf("error is unexpected void"));
}
return ok;
}

/*:406*//*407:*/
#line 7644 "lossless.w"

llt_buffer*
llt_Interpreter__OP_JUMP_FALSE(void)
{
int i;
llt_buffer*r;
llt_Fixture*fix;
r= llt_alloc(4,llt_Fixture);
fix= (llt_Fixture*)r->data;
for(i= 0;i<4;i++){
llt_Interpreter_fix(fix+i,__func__);
fix[i].prepare= llt_Interpreter__OP_JUMP_FALSE_prepare;
fix[i].test= llt_Interpreter__OP_JUMP_FALSE_test;
fix[i].opcode= OP_JUMP_FALSE;
fix[i].custom_p= btrue;
}
fix[0].suffix= "any";
fix[0].set_Acc= int_new(42);
fix[0].want_Ip= 2;
fix[1].suffix= "#t";
fix[1].set_Acc= TRUE;
fix[1].want_Ip= 2;
fix[2].suffix= "#f";
fix[2].set_Acc= FALSE;
fix[2].want_Ip= 3;
fix[3].suffix= "no value";
fix[3].set_Acc= VOID;
fix[3].want_Ip= -1;
fix[3].want_ex_p= btrue;
fix[3].mutate_Acc_p= btrue;
return r;
}

/*:407*//*408:*/
#line 7680 "lossless.w"

llt_buffer*
llt_Interpreter__OP_JUMP_TRUE(void)
{
int i;
llt_buffer*r;
llt_Fixture*fix;
r= llt_Interpreter__OP_JUMP_FALSE();
fix= (llt_Fixture*)r->data;
for(i= 0;i<(int)r->len;i++){
fix[i].name= (char*)__func__;
fix[i].opcode= OP_JUMP_TRUE;
}
i= fix[1].want_Ip;
fix[1].want_Ip= fix[2].want_Ip;
fix[2].want_Ip= i;
return r;
}

/*:408*//*414:*/
#line 7712 "lossless.w"

void
llt_Interpreter__OP_LOOKUP_prepare(llt_Fixture*fix)
{
vms_push(fix->backup_Env= Env);
Env= env_extend(Env);
if(fix->env_found_p)
env_set(Env,sym(LLT_VALUE_MARCO),sym(LLT_VALUE_POLO),btrue);
Acc= sym(LLT_VALUE_MARCO);
llt_Interpreter_prepare(fix);
}

/*:414*//*415:*/
#line 7724 "lossless.w"

void
llt_Interpreter__OP_LOOKUP_destroy(llt_Fixture*fix)
{
Env= fix->backup_Env;
VMS= NIL;
}

/*:415*//*416:*/
#line 7732 "lossless.w"

boolean
llt_Interpreter__OP_LOOKUP_test(llt_Fixture*fix)
{
char buf[TEST_BUFSIZE];
boolean ok= llt_Interpreter_test(fix);
if(fix->env_found_p)
tap_more(ok,Acc= fix->sym_mpft[0],
fpmsgf("Acc contains the looked up value"));
else
tap_more(ok,exception_p(Acc)
&&ex_id(Acc)==Sym_ERR_UNBOUND
&&ex_detail(Acc)==fix->sym_mpft[0],
fpmsgf("error is unbound marco?"));
return ok;
}

/*:416*//*417:*/
#line 7749 "lossless.w"

llt_buffer*
llt_Interpreter__OP_LOOKUP(void)
{
llt_buffer*r;
llt_Fixture*fix;
r= llt_alloc(2,llt_Fixture);
fix= (llt_Fixture*)r->data;
llt_Interpreter_fix(fix+0,__func__);
llt_Interpreter_fix(fix+1,__func__);
fix[0].opcode= fix[1].opcode= OP_LOOKUP;
fix[0].prepare= fix[1].prepare= llt_Interpreter__OP_LOOKUP_prepare;
fix[0].test= fix[1].test= llt_Interpreter__OP_LOOKUP_test;
fix[0].destroy= fix[1].destroy= llt_Interpreter__OP_LOOKUP_destroy;
fix[0].mutate_RTS_p= fix[1].mutate_RTS_p= btrue;
fix[0].mutate_Acc_p= fix[1].mutate_Acc_p= btrue;
fix[0].suffix= "bound";
fix[0].env_found_p= btrue;
fix[1].suffix= "unbound";
fix[1].want_ex_p= btrue;
fix[1].want_Ip= -1;
return r;
}

/*:417*//*419:*/
#line 7780 "lossless.w"

llt_buffer*
llt_Interpreter__OP_NOOP(void)
{
llt_buffer*r= llt_alloc(1,llt_Fixture);
llt_Interpreter_fix((llt_Fixture*)r->data,__func__);
return r;
}

/*:419*//*431:*/
#line 7820 "lossless.w"

void
llt_Interpreter__OP_SNOC_prepare(llt_Fixture*fix)
{
Acc= cons(sym(LLT_VALUE_FISH),int_new(42));
llt_Interpreter_prepare(fix);
}

/*:431*//*432:*/
#line 7828 "lossless.w"

boolean
llt_Interpreter__OP_SNOC_test(llt_Fixture*fix)
{
char buf[TEST_BUFSIZE];
boolean ok= llt_Interpreter_test(fix);
tap_more(ok,Acc==fix->sym_mpft[2],
fpmsgf("The car is in Acc"));
tap_more(ok,RTSp==fix->want_RTSp&&rts_pop(1)==int_new(42),
fpmsgf("The cdr is in RTS"));
return ok;
}

/*:432*//*433:*/
#line 7841 "lossless.w"

llt_buffer*
llt_Interpreter__OP_SNOC(void)
{
llt_buffer*r;
llt_Fixture*fix;
r= llt_alloc(1,llt_Fixture);
fix= (llt_Fixture*)r->data;
llt_Interpreter_fix(fix,__func__);
fix[0].opcode= OP_SNOC;
fix[0].prepare= llt_Interpreter__OP_SNOC_prepare;
fix[0].test= llt_Interpreter__OP_SNOC_test;
fix[0].mutate_Acc_p= btrue;
fix[0].mutate_RTS_p= btrue;
fix[0].mutate_RTSp_p= btrue;
return r;
}

/*:433*//*434:*/
#line 7862 "lossless.w"

void
llt_Interpreter__OP_SWAP_prepare(llt_Fixture*fix)
{
int i;
for(i= 0;i<fix->extra_stack;i++)
rts_push(int_new(42+3*i));
rts_push(int_new(42));
Acc= sym("question?");
llt_Interpreter_prepare(fix);
}

/*:434*//*435:*/
#line 7874 "lossless.w"

boolean
llt_Interpreter__OP_SWAP_test(llt_Fixture*fix)
{
char buf[TEST_BUFSIZE];
boolean ok= llt_Interpreter_test(fix);
if(RTSp!=fix->save_RTSp)
tap_fail(fpmsgf("cannot test stack contents"));
else
tap_more(ok,rts_pop(1)==sym("question?"),
fpmsgf("the stack top is correct"));
tap_more(ok,Acc==int_new(42),
fpmsgf("Acc is correct"));
return ok;
}

/*:435*//*436:*/
#line 7890 "lossless.w"

llt_buffer*
llt_Interpreter__OP_SWAP(void)
{
llt_buffer*r;
llt_Fixture*fix;
r= llt_alloc(2,llt_Fixture);
fix= (llt_Fixture*)r->data;
llt_Interpreter_fix(fix+0,__func__);
llt_Interpreter_fix(fix+1,__func__);
fix[0].opcode= fix[1].opcode= OP_SWAP;
fix[0].prepare= fix[1].prepare= llt_Interpreter__OP_SWAP_prepare;
fix[0].test= fix[1].test= llt_Interpreter__OP_SWAP_test;
fix[0].mutate_Acc_p= fix[1].mutate_Acc_p= btrue;
fix[0].mutate_RTS_p= fix[1].mutate_RTS_p= btrue;
fix[0].suffix= "empty stack";
fix[1].extra_stack= 3;
fix[1].suffix= "stack in use";
return r;
}

/*:436*/
#line 7228 "lossless.w"


llt_fixture Test_Fixtures[]= {
llt_Interpreter__OP_CYCLE,
llt_Interpreter__OP_ENV_MUTATE_M,
llt_Interpreter__OP_HALT,
llt_Interpreter__OP_JUMP,
llt_Interpreter__OP_JUMP_FALSE,
llt_Interpreter__OP_JUMP_TRUE,
llt_Interpreter__OP_LOOKUP,
llt_Interpreter__OP_NOOP,
llt_Interpreter__OP_SNOC,
llt_Interpreter__OP_SWAP,
NULL
};

/*:376*/
