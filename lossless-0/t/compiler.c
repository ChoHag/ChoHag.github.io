/*443:*/
#line 8002 "lossless.w"

/*258:*/
#line 4878 "lossless.w"

#define LL_TEST
#include "lossless.h"
#include "llt.h"

/*:258*/
#line 8003 "lossless.w"


struct llt_Fixture{
LLT_FIXTURE_HEADER;
cell ret_val;
cell src_val;
char*src_exp;
boolean had_ex_p;
char*want;
cell want_ex;
cell save_Acc;
};

/*259:*/
#line 4883 "lossless.w"

int
main(int argc ll_unused,
char**argv ll_unused)
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

/*:259*//*260:*/
#line 4902 "lossless.w"

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
/*261:*/
#line 4927 "lossless.w"

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

/*:261*/
#line 4918 "lossless.w"

if((d= f0-f1)> 0&&!suite[i].skip_gc_p){
/*262:*/
#line 4944 "lossless.w"

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

/*:262*/
#line 4920 "lossless.w"

}
tap_more(all,ok,buf);
}
return all;
}

/*:260*//*263:*/
#line 4969 "lossless.w"

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
llt_grow(r,f->len);
bcopy(f->data,((llt_Fixture*)r->data)+old,
f->len*f->size);
free(f);
}
for(i= 0;i<(int)r->len;i++)
((llt_Fixture*)r->data)[i].id= i;
return r;
}

/*:263*/
#line 8016 "lossless.w"


/*444:*/
#line 8026 "lossless.w"

void
llt_Compiler_prepare(llt_Fixture*fix)
{
Tmp_Test= fix->src_val= read_cstring(fix->src_exp);
Error_Handler= btrue;
}

/*:444*//*445:*/
#line 8034 "lossless.w"

void
llt_Compiler_destroy(llt_Fixture*fix ll_unused)
{
Tmp_Test= NIL;
Error_Handler= bfalse;
}

/*:445*//*446:*/
#line 8042 "lossless.w"

void
llt_Compiler_act(llt_Fixture*fix)
{
fix->save_Acc= Acc;
fix->had_ex_p= bfalse;
if(!setjmp(Goto_Error))
fix->ret_val= compile(fix->src_val);
else
fix->had_ex_p= btrue;
}

/*:446*//*447:*/
#line 8054 "lossless.w"

boolean
llt_Compiler_compare_bytecode(cell bc,
char*want,
boolean prepared_p)
{
char*g,*w;
ssize_t len;
int i;
boolean r= btrue;
if(!vector_p(bc))
return bfalse;
ERR_OOM_P(g= calloc(TEST_BUFSIZE,sizeof(char)));
if(write_bytecode(bc,g,TEST_BUFSIZE,0)<0){
free(g);
return bfalse;
}
len= (ssize_t)strlen(want);
if(prepared_p)
w= want;
else{
ERR_OOM_P(w= malloc(len+1));
w[0]= '{';
for(i= 1;i<len-1;i++)
w[i]= want[i];
w[i]= '}';
}
if(len!=(ssize_t)strlen(g))
r= bfalse;
else
for(i= 0;i<len;i++)
if(g[i]!=w[i]){
r= bfalse;
break;
}
free(g);
if(!prepared_p)
free(w);
return r;
}

/*:447*//*448:*/
#line 8095 "lossless.w"

boolean
llt_Compiler_test(llt_Fixture*fix)
{
char buf[TEST_BUFSIZE]= {0};
boolean ok,match;
if(fix->want==NULL){
ok= tap_ok(fix->had_ex_p,fpmsgf("an error was raised"));
tap_again(ok,ex_id(Acc)==fix->want_ex,
fpmsgf("the error type is correct"));
}else{
ok= tap_ok(!fix->had_ex_p,
fpmsgf("an error was not raised"));
tap_more(ok,null_p(CTS),
fpmsgf("the compiler stack is clear"));
tap_more(ok,Acc==fix->save_Acc,
fpmsgf("Acc is unchanged"));
match= llt_Compiler_compare_bytecode(fix->ret_val,
fix->want,bfalse);
tap_more(ok,match,
fpmsgf("the correct bytecode is generated"));
}
return ok;
}

/*:448*//*449:*/
#line 8120 "lossless.w"

void
llt_Compiler_fix(llt_Fixture*fix,
const char*name)
{
fix->name= (char*)name;
fix->prepare= llt_Compiler_prepare;
fix->destroy= llt_Compiler_destroy;
fix->act= llt_Compiler_act;
fix->test= llt_Compiler_test;
fix->want= NULL;
fix->want_ex= NIL;
}

/*:449*//*450:*/
#line 8196 "lossless.w"

void
llt_Compiler__Eval_prepare(llt_Fixture*fix)
{
llt_Compiler_prepare(fix);
car(fix->src_val)= env_search(Root,sym("eval"));
}

/*:450*//*451:*/
#line 8204 "lossless.w"

llt_buffer*
llt_Compiler__Eval(void)
{
int i;
llt_buffer*r;
llt_Fixture*fix;
r= llt_alloc(16,llt_Fixture);
fix= (llt_Fixture*)r->data;
for(i= 0;i<16;i++){
llt_Compiler_fix(fix+i,__func__);
fix[i].prepare= llt_Compiler__Eval_prepare;
}
i= -1;
/*452:*/
#line 8224 "lossless.w"

fix[++i].src_exp= "(eval)";
fix[i].suffix= "eval";
fix[i].want_ex= Sym_ERR_ARITY_SYNTAX;
fix[++i].src_exp= "(eval 42)";
fix[i].suffix= "eval x";
fix[i].want= CAT2(LLTCC_EVAL_FIRST_QUOTE("42"),LLTCC_EVAL_ONEARG());
fix[++i].src_exp= "(eval 4 2)";
fix[i].suffix= "eval x x";
fix[i].want= CAT4(LLTCC_EVAL_SECOND_QUOTE("2"),LLTCC_EVAL_VALIDATE("9"),
LLTCC_EVAL_FIRST_QUOTE("4"),LLTCC_EVAL_TWOARG());
fix[++i].src_exp= "(eval 4 2 ?)";
fix[i].suffix= "eval x x x";
fix[i].want_ex= Sym_ERR_ARITY_SYNTAX;

/*:452*//*453:*/
#line 8241 "lossless.w"

fix[++i].src_exp= "(eval 42)";
fix[i].suffix= "eval <constant>";
fix[i].want= CAT2(LLTCC_EVAL_FIRST_QUOTE("42"),LLTCC_EVAL_ONEARG());
fix[++i].src_exp= "(eval marco?)";
fix[i].suffix= "eval <symbol>";
fix[i].want= CAT2(LLTCC_EVAL_FIRST_LOOKUP("marco?"),LLTCC_EVAL_ONEARG());
fix[++i].src_exp= "(eval (build an expression))";
fix[i].suffix= "eval <complex expression>";
fix[i].want= CAT2(LLTCC_EVAL_FIRST_COMPLEX("build","an expression"),
LLTCC_EVAL_ONEARG());

/*:453*//*454:*/
#line 8255 "lossless.w"

fix[++i].src_exp= "(eval 42 24)";
fix[i].suffix= "eval <constant> <constant>";
fix[i].want= CAT4(LLTCC_EVAL_SECOND_QUOTE("24"),LLTCC_EVAL_VALIDATE("9"),
LLTCC_EVAL_FIRST_QUOTE("42"),LLTCC_EVAL_TWOARG());
fix[++i].src_exp= "(eval 42 marco?)";
fix[i].suffix= "eval <constant> <symbol>";
fix[i].want= CAT4(LLTCC_EVAL_SECOND_LOOKUP("marco?"),LLTCC_EVAL_VALIDATE("10"),
LLTCC_EVAL_FIRST_QUOTE("42"),LLTCC_EVAL_TWOARG());
fix[++i].src_exp= "(eval 42 (get an environment))";
fix[i].suffix= "eval <constant> <complex expression>";
fix[i].want= CAT4(LLTCC_EVAL_SECOND_COMPLEX("get","an environment"),
LLTCC_EVAL_VALIDATE("16"),
LLTCC_EVAL_FIRST_QUOTE("42"),LLTCC_EVAL_TWOARG());

/*:454*//*455:*/
#line 8272 "lossless.w"

fix[++i].src_exp= "(eval marco? 24)";
fix[i].suffix= "eval <symbol> <constant>";
fix[i].want= CAT4(LLTCC_EVAL_SECOND_QUOTE("24"),LLTCC_EVAL_VALIDATE("9"),
LLTCC_EVAL_FIRST_LOOKUP("marco?"),LLTCC_EVAL_TWOARG());
fix[++i].src_exp= "(eval marco? polo!)";
fix[i].suffix= "eval <symbol> <symbol>";
fix[i].want= CAT4(LLTCC_EVAL_SECOND_LOOKUP("polo!"),LLTCC_EVAL_VALIDATE("10"),
LLTCC_EVAL_FIRST_LOOKUP("marco?"),LLTCC_EVAL_TWOARG());
fix[++i].src_exp= "(eval marco? (a new environment))";
fix[i].suffix= "eval <symbol> <complex expression>";
fix[i].want= CAT4(LLTCC_EVAL_SECOND_COMPLEX("a","new environment"),
LLTCC_EVAL_VALIDATE("16"),
LLTCC_EVAL_FIRST_LOOKUP("marco?"),LLTCC_EVAL_TWOARG());

/*:455*//*456:*/
#line 8289 "lossless.w"

fix[++i].src_exp= "(eval (get an expression) 24)";
fix[i].suffix= "eval <complex expression> <constant>";
fix[i].want= CAT4(LLTCC_EVAL_SECOND_QUOTE("24"),LLTCC_EVAL_VALIDATE("9"),
LLTCC_EVAL_FIRST_COMPLEX("get","an expression"),
LLTCC_EVAL_TWOARG());
fix[++i].src_exp= "(eval (get another expression) marco?)";
fix[i].suffix= "eval <complex expression> <symbol>";
fix[i].want= CAT4(LLTCC_EVAL_SECOND_LOOKUP("marco?"),LLTCC_EVAL_VALIDATE("10"),
LLTCC_EVAL_FIRST_COMPLEX("get","another expression"),
LLTCC_EVAL_TWOARG());
fix[++i].src_exp= "(eval (once more) (this time with feeling))";
fix[i].suffix= "eval <complex expression> <complex expression>";
fix[i].want= CAT4(LLTCC_EVAL_SECOND_COMPLEX("this","time with feeling"),
LLTCC_EVAL_VALIDATE("16"),
LLTCC_EVAL_FIRST_COMPLEX("once","more"),
LLTCC_EVAL_TWOARG());

/*:456*/
#line 8218 "lossless.w"

return r;
}

/*:451*//*457:*/
#line 8367 "lossless.w"

void
llt_Compiler__Lambda_prepare(llt_Fixture*fix)
{
llt_Compiler_prepare(fix);
car(fix->src_val)= env_search(Root,sym("lambda"));
}

/*:457*//*458:*/
#line 8380 "lossless.w"

boolean
llt_Compiler__Lambda_test(llt_Fixture*fix)
{
char buf[TEST_BUFSIZE]= {0};
boolean fok,ok;
cell f,fex,frv;
ok= llt_Compiler_test(fix);
if(fix->want){
fex= cadr(fix->src_val);
frv= vector_ref(fix->ret_val,1);
fok= btrue;
for(f= fex;pair_p(f);f= cdr(f))
if(!special_p(f)&&llt_contains_p(frv,f)){
fok= bfalse;
break;
}
tap_more(ok,fok,fpmsgf("the formals do not share cells"));
}
return ok;
}

/*:458*//*459:*/
#line 8402 "lossless.w"

void
llt_Compiler__Lambda_fix(llt_Fixture*fix,
const char*name)
{
llt_Compiler_fix(fix,name);
fix->prepare= llt_Compiler__Lambda_prepare;
fix->test= llt_Compiler__Lambda_test;
}

/*:459*//*460:*/
#line 8416 "lossless.w"

llt_buffer*llt_Compiler__Lambda_build(const char*,llt_buffer*,
char*,char*,char*);

/*:460*//*461:*/
#line 8431 "lossless.w"

llt_buffer*
llt_Compiler__Lambda(void)
{
llt_buffer*fbuf;
fbuf= llt_alloc(1,llt_Fixture);
llt_Compiler__Lambda_fix((llt_Fixture*)fbuf->data,__func__);
bfix(fbuf).src_exp= "(lambda)";
bfix(fbuf).suffix= "no arguments";
bfix(fbuf).want_ex= Sym_ERR_ARITY_SYNTAX;
/*463:*/
#line 8473 "lossless.w"

lltfix_lambda_fail_formals("O");
lltfix_lambda_fail_formals("OS");
lltfix_lambda_fail_formals("SO");
lltfix_lambda_fail_formals("SD");
lltfix_lambda_fail_formals("OSS");
lltfix_lambda_fail_formals("SOS");
lltfix_lambda_fail_formals("SSO");
lltfix_lambda_fail_formals("SOO");
lltfix_lambda_fail_formals("OSO");
lltfix_lambda_fail_formals("OOS");
lltfix_lambda_fail_formals("OSD");
lltfix_lambda_fail_formals("SOD");
lltfix_lambda_fail_formals("SDO");

/*:463*/
#line 8441 "lossless.w"

/*464:*/
#line 8494 "lossless.w"

lltfix_lambda_fail_body("S","improper body (1 item)");
lltfix_lambda_fail_body("SS","improper body (2 items)");
lltfix_lambda_fail_body("SSS","improper body (3 items)");

/*:464*/
#line 8442 "lossless.w"

/*462:*/
#line 8452 "lossless.w"

lltfix_lambda_success("");
lltfix_lambda_success("I");
lltfix_lambda_success("S");
lltfix_lambda_success("II");
lltfix_lambda_success("IS");
lltfix_lambda_success("SI");
lltfix_lambda_success("SS");
lltfix_lambda_success("III");
lltfix_lambda_success("IIS");
lltfix_lambda_success("ISI");
lltfix_lambda_success("ISS");
lltfix_lambda_success("SII");
lltfix_lambda_success("SIS");
lltfix_lambda_success("SSI");
lltfix_lambda_success("SSS");

/*:462*/
#line 8443 "lossless.w"

return fbuf;
}

/*:461*//*465:*/
#line 8519 "lossless.w"

llt_buffer*
llt_Compiler__Lambda_build(const char*name,
llt_buffer*fbuf,
char*formals,
char*body,
char*desc)
{
char*o0,*o1,*s= "xyz";
int i;
if(!*formals){
/*466:*/
#line 8542 "lossless.w"

llt_grow(fbuf,1);
llt_Compiler__Lambda_fix(&bfix(fbuf),name);
if(!*body){
bfix(fbuf).src_exp= "(lambda ())";
bfix(fbuf).suffix= "lambda ()";
bfix(fbuf).want= llt_cat(LLTCC_LAMBDA_SUCCESS,"()")->data;
}else{
/*467:*/
#line 8556 "lossless.w"

bfix(fbuf).suffix= desc;
ERR_OOM_P(bfix(fbuf).src_exp= calloc(LLT_BUFLET_SEGMENT,1));
sprintf(bfix(fbuf).src_exp,"(lambda ()");
o0= bfix(fbuf).src_exp+strlen(bfix(fbuf).src_exp);
while(*body++){
if(!*body){
straffix(o0,' ');
straffix(o0,'.');
}
straffix(o0,' ');
straffix(o0,*s++);
}
straffix(o0,')');
bfix(fbuf).want_ex= Sym_ERR_ARITY_SYNTAX;

/*:467*/
#line 8550 "lossless.w"

}

/*:466*/
#line 8530 "lossless.w"

return fbuf;
}
/*468:*/
#line 8577 "lossless.w"

llt_grow(fbuf,2);
llt_Compiler__Lambda_fix(&bfix0(fbuf),name);
llt_Compiler__Lambda_fix(&bfix1(fbuf),name);
ERR_OOM_P(bfix0(fbuf).src_exp= calloc(LLT_BUFLET_SEGMENT,1));
bfix0(fbuf).suffix= bfix0(fbuf).src_exp+LLT_BUFLET_SLICE*1;
bfix1(fbuf).src_exp= bfix0(fbuf).src_exp+LLT_BUFLET_SLICE*2;
bfix1(fbuf).suffix= bfix0(fbuf).src_exp+LLT_BUFLET_SLICE*3;
sprintf(bfix0(fbuf).src_exp,"(lambda ");
sprintf(bfix1(fbuf).src_exp,"(lambda ");
o0= bfix0(fbuf).src_exp+8;
o1= bfix1(fbuf).src_exp+8;
/*469:*/
#line 8606 "lossless.w"

if(!formals[1])
straffix(o0,'(');
else
straffix_both(o0,o1,'(');
for(i= 0;formals[i];i++){
if(i&&!formals[i+1]){
straffix(o1,' ');
straffix(o1,'.');
}
/*470:*/
#line 8628 "lossless.w"

if(i)
straffix_both(o0,o1,' ');
switch(formals[i]){
case'S':
straffix_both(o0,o1,*s++);
break;
case'D':
straffix_both(o0,o1,*(s-1));
bfix0(fbuf).want_ex= bfix1(fbuf).want_ex= Sym_ERR_ARITY_SYNTAX;
break;
case'I':
straffix_both(o0,o1,'#');
straffix_both(o0,o1,'f');
break;
case'O':
straffix_both(o0,o1,'#');
straffix_both(o0,o1,'t');
bfix0(fbuf).want_ex= bfix1(fbuf).want_ex= Sym_ERR_ARITY_SYNTAX;
break;
}

/*:470*/
#line 8616 "lossless.w"

}
if(!formals[1])
straffix(o0,')');
else
straffix_both(o0,o1,')');

/*:469*/
#line 8589 "lossless.w"

if(null_p(bfix(fbuf).want_ex)){
bfix0(fbuf).want
= llt_cat(LLTCC_LAMBDA_SUCCESS,bfix0(fbuf).src_exp+8)->data;
bfix1(fbuf).want
= llt_cat(LLTCC_LAMBDA_SUCCESS,bfix1(fbuf).src_exp+8)->data;
}
straffix_both(o0,o1,')');
strlcpy(bfix0(fbuf).suffix,bfix0(fbuf).src_exp+1,
strlen(bfix0(fbuf).src_exp)-1);
strlcpy(bfix1(fbuf).suffix,bfix1(fbuf).src_exp+1,
strlen(bfix1(fbuf).src_exp)-1);

/*:468*/
#line 8533 "lossless.w"

return fbuf;
}

/*:465*/
#line 8018 "lossless.w"


llt_fixture Test_Fixtures[]= {
llt_Compiler__Eval,
llt_Compiler__Lambda,
NULL
};

/*:443*/
