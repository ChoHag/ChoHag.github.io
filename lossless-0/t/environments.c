/*354:*/
#line 6694 "lossless.w"

/*255:*/
#line 4821 "lossless.w"

#define LL_TEST
#include "lossless.h"
#include "llt.h"

/*:255*/
#line 6695 "lossless.w"


struct llt_Fixture{
LLT_FIXTURE_HEADER;
cell expect;
cell formals;
boolean had_ex_p;
int layers;
cell layer[3];
boolean new_p;
int null_pos;
boolean proper_p;
cell ret_val;
llt_buffer*save_Env;
jmp_buf save_goto;
int save_RTSp;
cell(*search_fn)(cell,cell);

int stack;
cell sym_mpf[3];
cell sym_var[3];
cell sym_val[3];
boolean want_ex_p;
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
#line 6720 "lossless.w"


/*355:*/
#line 6733 "lossless.w"

void
llt_Environments_prepare(llt_Fixture*fix)
{
char buf[TEST_BUFSIZE]= {0};
cell e[3];
int i;
fix->sym_mpf[0]= sym(LLT_VALUE_MARCO);
fix->sym_mpf[1]= sym(LLT_VALUE_POLO);
fix->sym_mpf[2]= sym(LLT_VALUE_FISH);
/*356:*/
#line 6753 "lossless.w"

vms_push(Env);
Env= e[0]= env_empty();
if(fix->layers> 1)
Env= e[1]= env_extend(e[0]);
if(fix->layers> 2)
Env= e[2]= env_extend(e[1]);
for(i= 0;i<fix->layers;i++)
if(!null_p(fix->layer[i]))
env_set(e[i],fix->sym_mpf[0],fix->layer[i],btrue);
fix->save_Env= llt_serialise(Env,btrue);
fix->save_RTSp= RTSp;
for(i= 0;i<3;i++){
snprintf(buf,TEST_BUFSIZE,"test-variable-%d",i+1);
fix->sym_var[i]= sym(buf);
snprintf(buf,TEST_BUFSIZE,"test-value-%d",i+1);
fix->sym_val[i]= sym(buf);
}

/*:356*/
#line 6743 "lossless.w"

if(fix->stack){
/*357:*/
#line 6774 "lossless.w"

rts_push(fix->sym_val[fix->stack-1]);
if(!fix->proper_p)
fix->formals= fix->sym_var[fix->stack-1];
else if(fix->null_pos==fix->stack)
fix->formals= cons(NIL,NIL);
else
fix->formals= cons(fix->sym_var[fix->stack-1],NIL);
vms_push(fix->formals);
for(i= fix->stack-1;i> 0;i--){
rts_push(fix->sym_val[i-1]);
if(fix->null_pos&&fix->null_pos==i)
fix->formals= cons(NIL,fix->formals);
else
fix->formals= cons(fix->sym_var[i-1],
fix->formals);
vms_set(fix->formals);
}

/*:357*/
#line 6745 "lossless.w"

}
bcopy(fix->save_goto,Goto_Error,sizeof(jmp_buf));
Error_Handler= btrue;
}

/*:355*//*358:*/
#line 6793 "lossless.w"

void
llt_Environments_destroy(llt_Fixture*fix __unused)
{
Env= ((cell*)fix->save_Env->data)[0];
Acc= VMS= NIL;
free(fix->save_Env);
bcopy(fix->save_goto,Goto_Error,sizeof(jmp_buf));
Error_Handler= bfalse;
}

/*:358*//*359:*/
#line 6806 "lossless.w"

void
llt_Environments_fix(llt_Fixture*fix,
const char*name)
{
fix->name= (char*)name;
fix->prepare= llt_Environments_prepare;
fix->destroy= llt_Environments_destroy;
fix->act= NULL;
fix->test= NULL;
}

/*:359*//*360:*/
#line 6841 "lossless.w"

void
llt_Environments__Search_act(llt_Fixture*fix)
{
fix->ret_val= fix->search_fn(Env,fix->sym_mpf[0]);
}

/*:360*//*361:*/
#line 6848 "lossless.w"

boolean
llt_Environments__Search_test(llt_Fixture*fix)
{
char buf[TEST_BUFSIZE]= {0};
if(true_p(fix->expect))
return tap_ok(fix->ret_val==fix->sym_mpf[1],
fpmsgf("variable is found & correct"));
else
return tap_ok(undefined_p(fix->ret_val),
fpmsgf("variable is not found"));
}

/*:361*//*362:*/
#line 6863 "lossless.w"

llt_buffer*
llt_Environments__Search_Single_Layer(void)
{
int i;
llt_buffer*r;
llt_Fixture*fix;
r= llt_alloc(4,llt_Fixture);
fix= (llt_Fixture*)r->data;
for(i= 0;i<4;i++){
llt_Environments_fix(fix+i,__func__);
fix[i].act= llt_Environments__Search_act;
fix[i].test= llt_Environments__Search_test;
fix[i].layers= 1;
}
for(i= 0;i<4;i+= 2){
fix[i].search_fn= env_search;
fix[i+1].search_fn= env_here;
}
fix[0].suffix= "env_search: not present";
fix[1].suffix= "env_here: not present";
fix[0].layer[0]= fix[1].layer[0]= NIL;
fix[0].expect= fix[1].expect= FALSE;
fix[2].suffix= "env_search: present";
fix[3].suffix= "env_here: present";
fix[2].layer[0]= fix[3].layer[0]= sym(LLT_VALUE_POLO);
fix[2].expect= fix[3].expect= TRUE;
return r;
}

/*:362*//*363:*/
#line 6896 "lossless.w"

llt_buffer*
llt_Environments__Search_Multi_Simple(void)
{
int i;
llt_buffer*r;
llt_Fixture*fix;
r= llt_alloc(6,llt_Fixture);
fix= (llt_Fixture*)r->data;
for(i= 0;i<6;i++){
llt_Environments_fix(fix+i,__func__);
fix[i].act= llt_Environments__Search_act;
fix[i].test= llt_Environments__Search_test;
fix[i].layers= 3;
fix[i].layer[0]= fix[i].layer[1]= fix[i].layer[2]= NIL;
}
for(i= 0;i<6;i+= 2){
fix[i].search_fn= env_search;
fix[i+1].search_fn= env_here;
}
fix[0].suffix= "env_search: present in top";
fix[1].suffix= "env_here: present in top";
fix[0].expect= fix[1].expect= TRUE;
fix[0].layer[2]= fix[1].layer[2]= sym(LLT_VALUE_POLO);
fix[2].suffix= "env_search: present in parent";
fix[3].suffix= "env_here: present in parent";
fix[2].expect= TRUE;
fix[3].expect= FALSE;
fix[2].layer[1]= fix[3].layer[1]= sym(LLT_VALUE_POLO);
fix[4].suffix= "env_search: not present";
fix[5].suffix= "env_here: not present";
fix[4].expect= fix[5].expect= FALSE;
return r;
}

/*:363*//*364:*/
#line 6934 "lossless.w"

llt_buffer*
llt_Environments__Search_Multi_Masked(void)
{
int i;
llt_buffer*r;
llt_Fixture*fix;
r= llt_alloc(4,llt_Fixture);
fix= (llt_Fixture*)r->data;
for(i= 0;i<4;i++){
llt_Environments_fix(fix+i,__func__);
fix[i].act= llt_Environments__Search_act;
fix[i].test= llt_Environments__Search_test;
fix[i].layers= 3;
fix[i].layer[0]= fix[i].layer[1]= fix[i].layer[2]= NIL;
}
for(i= 0;i<4;i+= 2){
fix[i].search_fn= env_search;
fix[i+1].search_fn= env_here;
}
fix[0].suffix= "env_search: present in top, conflict in parent";
fix[1].suffix= "env_here: present in top, conflict in parent";
fix[0].expect= fix[1].expect= TRUE;
fix[0].layer[2]= fix[1].layer[2]= sym(LLT_VALUE_POLO);
fix[0].layer[1]= fix[1].layer[1]= sym(LLT_VALUE_FISH);
fix[2].suffix= "env_search: present in parent, conflict in ancestor";
fix[3].suffix= "env_here: present in parent, conflict in ancestor";
fix[2].expect= TRUE;
fix[3].expect= FALSE;
fix[2].layer[1]= fix[3].layer[1]= sym(LLT_VALUE_POLO);
fix[2].layer[0]= fix[3].layer[0]= sym(LLT_VALUE_FISH);
return r;
}

/*:364*//*365:*/
#line 6980 "lossless.w"

void
llt_Environments__Set_act(llt_Fixture*fix)
{
fix->had_ex_p= bfalse;
if(!setjmp(Goto_Error))
env_set(Env,fix->sym_mpf[0],fix->sym_mpf[1],fix->new_p);
else
fix->had_ex_p= btrue;
}

/*:365*//*366:*/
#line 6994 "lossless.w"

boolean
llt_Environments__Set_test(llt_Fixture*fix)
{
char buf[TEST_BUFSIZE]= {0};
boolean ok;
cell found;
if(fix->want_ex_p){
ok= tap_ok(fix->had_ex_p,
fpmsgf("an error was raised"));
if(fix->new_p){
tap_again(ok,ex_id(Acc)==Sym_ERR_BOUND
&&ex_detail(Acc)==fix->sym_mpf[0],
fpmsgf("the error is bound marco"));
}else{
tap_again(ok,ex_id(Acc)==Sym_ERR_UNBOUND
&&ex_detail(Acc)==fix->sym_mpf[0],
fpmsgf("the error is unbound marco"));
}
}else
ok= tap_ok(!fix->had_ex_p,
fpmsgf("an error was not raised"));
found= env_search(Env,fix->sym_mpf[0]);
tap_more(ok,found==fix->expect,
fpmsgf("the variable has the correct value"));
return ok;
}

/*:366*//*367:*/
#line 7026 "lossless.w"

llt_buffer*
llt_Environments__Set(void)
{
int i;
llt_buffer*r;
llt_Fixture*fix;
r= llt_alloc(6,llt_Fixture);
fix= (llt_Fixture*)r->data;
for(i= 0;i<6;i++){
llt_Environments_fix(fix+i,__func__);
fix[i].act= llt_Environments__Set_act;
fix[i].test= llt_Environments__Set_test;
fix[i].layers= 2;
fix[i].new_p= !(i%2);
}
fix[0].suffix= "define: already present";
fix[1].suffix= "set: already present";
fix[0].layer[1]= fix[1].layer[1]= sym(LLT_VALUE_FISH);
fix[0].layer[0]= fix[1].layer[0]= NIL;
fix[0].want_ex_p= btrue;
fix[0].expect= sym(LLT_VALUE_FISH);
fix[1].expect= sym(LLT_VALUE_POLO);
fix[2].suffix= "define: in an ancestor";
fix[3].suffix= "set: in an ancestor";
fix[2].layer[1]= fix[3].layer[1]= NIL;
fix[2].layer[0]= fix[3].layer[0]= sym(LLT_VALUE_FISH);
fix[2].expect= sym(LLT_VALUE_POLO);
fix[3].want_ex_p= btrue;
fix[3].expect= sym(LLT_VALUE_FISH);
fix[4].suffix= "define: not in the environment";
fix[5].suffix= "set: not in the environment";
fix[4].layer[1]= fix[5].layer[1]= NIL;
fix[4].layer[0]= fix[5].layer[0]= NIL;
fix[4].expect= sym(LLT_VALUE_POLO);
fix[5].want_ex_p= btrue;
fix[5].expect= UNDEFINED;
return r;
}

/*:367*//*368:*/
#line 7107 "lossless.w"

void
llt_Environments__Lift_Stack_act(llt_Fixture*fix)
{
fix->ret_val= env_lift_stack(Env,fix->formals);
}

/*:368*//*369:*/
#line 7114 "lossless.w"

boolean
llt_Environments__Lift_Stack_test(llt_Fixture*fix)
{
char buf[TEST_BUFSIZE]= {0};
cell found;
boolean ep,ok;
ok= tap_ok(ep= environment_p(fix->ret_val),
fpmsgf("the return value is an environment"));
tap_again(ok,env_parent(fix->ret_val)==Env,
fpmsgf("the correct environment is extended"));
tap_more(ok,llt_compare_serial(fix->save_Env,Env,btrue),
fpmsgf("the parent environment is unchanged"));
tap_more(ok,RTSp==fix->save_RTSp,
fpmsgf("the stack is reset"));
found= NIL;
switch(fix->stack){
case 3:
if(ep)found= env_here(fix->ret_val,fix->sym_var[2]);
tap_more(ok,found==fix->sym_val[2],
fpmsgf("3rd argument is lifted"));
case 2:
if(ep)found= env_here(fix->ret_val,fix->sym_var[1]);
if(fix->null_pos==2)
tap_more(ok,undefined_p(found),
fpmsgf("2nd argument is ignored"));
else
tap_more(ok,found==fix->sym_val[1],
fpmsgf("2nd argument is lifted"));
case 1:
if(ep)found= env_here(fix->ret_val,fix->sym_var[0]);
if(fix->null_pos==1)
tap_more(ok,undefined_p(found),
fpmsgf("1st argument is ignored"));
else
tap_more(ok,found==fix->sym_val[0],
fpmsgf("1st argument is lifted"));
}
return ok;
}

/*:369*//*370:*/
#line 7155 "lossless.w"

llt_buffer*
llt_Environments__Lift_Stack(void)
{
int i;
llt_buffer*r;
llt_Fixture*fix;
r= llt_alloc(11,llt_Fixture);
fix= (llt_Fixture*)r->data;
for(i= 0;i<11;i++){
llt_Environments_fix(fix+i,__func__);
fix[i].act= llt_Environments__Lift_Stack_act;
fix[i].test= llt_Environments__Lift_Stack_test;
fix[i].layers= 1;
fix[i].layer[0]= NIL;
fix[i].proper_p= btrue;
fix[i].formals= NIL;
}
fix[i= 0].suffix= "NIL";
fix[++i].suffix= "symbol";
fix[i].stack= 1;
fix[i].proper_p= bfalse;
fix[++i].suffix= "pair of two symbols";
fix[i].stack= 2;
fix[i].proper_p= bfalse;
fix[++i].suffix= "improper list of symbols";
fix[i].stack= 3;
fix[i].proper_p= bfalse;
fix[++i].suffix= "list of NIL";
fix[i].stack= 1;
fix[i].null_pos= 1;
fix[++i].suffix= "list of 1 symbol";
fix[i].stack= 1;
fix[++i].suffix= "list of 2 symbols";
fix[i].stack= 2;
fix[++i].suffix= "list of 2 with NIL first";
fix[i].stack= 2;
fix[i].null_pos= 1;
fix[++i].suffix= "list of 2 with NIL last";
fix[i].stack= 2;
fix[i].null_pos= 2;
fix[++i].suffix= "list of 3 symbols";
fix[i].stack= 3;
fix[++i].suffix= "list of 3 with a NIL";
fix[i].stack= 3;
fix[i].null_pos= 2;
return r;
}

/*:370*/
#line 6722 "lossless.w"


llt_fixture Test_Fixtures[]= {
llt_Environments__Lift_Stack,
llt_Environments__Search_Multi_Masked,
llt_Environments__Search_Multi_Simple,
llt_Environments__Search_Single_Layer,
llt_Environments__Set,
NULL
};

/*:354*/
