/*439:*/
#line 7927 "lossless.w"

/*255:*/
#line 4821 "lossless.w"

#define LL_TEST
#include "lossless.h"
#include "llt.h"

/*:255*/
#line 7928 "lossless.w"


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
#line 7941 "lossless.w"


/*440:*/
#line 7950 "lossless.w"

void
llt_Compiler_prepare(llt_Fixture*fix)
{
Tmp_Test= fix->src_val= read_cstring(fix->src_exp);
Error_Handler= btrue;
}

/*:440*//*441:*/
#line 7958 "lossless.w"

void
llt_Compiler_destroy(llt_Fixture*fix __unused)
{
Tmp_Test= NIL;
Error_Handler= bfalse;
}

/*:441*//*442:*/
#line 7966 "lossless.w"

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

/*:442*//*443:*/
#line 7978 "lossless.w"

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

/*:443*//*444:*/
#line 8019 "lossless.w"

boolean
llt_Compiler_test(llt_Fixture*fix)
{
char buf[TEST_BUFSIZE]= {0};
boolean ok,match;
if(fix->want==NULL){
ok= tap_ok(fix->had_ex_p,fpmsgf("an error was raised"));
tap_more(ok,ex_id(Acc)==fix->want_ex,
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

/*:444*//*445:*/
#line 8044 "lossless.w"

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

/*:445*//*446:*/
#line 8120 "lossless.w"

void
llt_Compiler__Eval_prepare(llt_Fixture*fix)
{
llt_Compiler_prepare(fix);
car(fix->src_val)= env_search(Root,sym("eval"));
}

/*:446*//*447:*/
#line 8128 "lossless.w"

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
/*448:*/
#line 8148 "lossless.w"

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

/*:448*//*449:*/
#line 8165 "lossless.w"

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

/*:449*//*450:*/
#line 8179 "lossless.w"

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

/*:450*//*451:*/
#line 8196 "lossless.w"

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

/*:451*//*452:*/
#line 8213 "lossless.w"

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

/*:452*/
#line 8142 "lossless.w"

return r;
}

/*:447*/
#line 7943 "lossless.w"


llt_fixture Test_Fixtures[]= {
llt_Compiler__Eval,
NULL
};

/*:439*/
