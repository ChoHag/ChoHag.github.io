/*300:*/
#line 5644 "lossless.w"

/*258:*/
#line 4878 "lossless.w"

#define LL_TEST
#include "lossless.h"
#include "llt.h"

/*:258*/
#line 5645 "lossless.w"


enum llt_GC_Mark_flat{
LLT_GC_MARK_SIMPLE_ATOM,
LLT_GC_MARK_SIMPLE_LONG_ATOM,
LLT_GC_MARK_SIMPLE_PAIR,
LLT_GC_MARK_SIMPLE_VECTOR
};

enum llt_GC_Mark_recursion{
LLT_GC_MARK_RECURSIVE_PA,
LLT_GC_MARK_RECURSIVE_PL,
LLT_GC_MARK_RECURSIVE_PP,
LLT_GC_MARK_RECURSIVE_PV,
LLT_GC_MARK_RECURSIVE_PLL,
LLT_GC_MARK_RECURSIVE_VA,
LLT_GC_MARK_RECURSIVE_VL,
LLT_GC_MARK_RECURSIVE_VP,
LLT_GC_MARK_RECURSIVE_VV,
LLT_GC_MARK_RECURSIVE_VLL,
LLT_GC_MARK_RECURSIVE_LL,
LLT_GC_MARK_RECURSIVE_LLL,
LLT_GC_MARK_RECURSIVE_PPA,
LLT_GC_MARK_RECURSIVE_PPL,
LLT_GC_MARK_RECURSIVE_PPP,
LLT_GC_MARK_RECURSIVE_PPV,
LLT_GC_MARK_RECURSIVE_PVA,
LLT_GC_MARK_RECURSIVE_PVL,
LLT_GC_MARK_RECURSIVE_PVP,
LLT_GC_MARK_RECURSIVE_PVV,
LLT_GC_MARK_RECURSIVE_VPA,
LLT_GC_MARK_RECURSIVE_VPL,
LLT_GC_MARK_RECURSIVE_VPP,
LLT_GC_MARK_RECURSIVE_VPV,
LLT_GC_MARK_RECURSIVE_VVA,
LLT_GC_MARK_RECURSIVE_VVL,
LLT_GC_MARK_RECURSIVE_VVP,
LLT_GC_MARK_RECURSIVE_VVV
};

struct llt_Fixture{
LLT_FIXTURE_HEADER;
cell safe;
llt_buffer*copy;
size_t len;
boolean proper_pair_p;
enum llt_GC_Mark_recursion complex;
enum llt_GC_Mark_flat simplex;
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
#line 5695 "lossless.w"


/*301:*/
#line 5720 "lossless.w"

boolean
llt_GC_Mark_is_marked_p(cell c)
{
return special_p(c)||(mark_p(c)
&&(!acar_p(c)||llt_GC_Mark_is_marked_p(car(c)))
&&(!acdr_p(c)||llt_GC_Mark_is_marked_p(cdr(c))));
}

/*:301*//*302:*/
#line 5735 "lossless.w"

void
llt_GC_Mark_unmark_m(cell c)
{
int i;
if(special_p(c))return;
mark_clear(c);
if(acar_p(c))llt_GC_Mark_unmark_m(car(c));
if(acdr_p(c))llt_GC_Mark_unmark_m(cdr(c));
if(vector_p(c))
for(i= 0;i<vector_length(c);i++)
llt_GC_Mark_unmark_m(vector_ref(c,i));
}

/*:302*//*303:*/
#line 5753 "lossless.w"

cell
llt_GC_Mark_mklong(int x,
int y)
{
cell r;
vms_push(int_new(y));
r= int_new(x);
cdr(r)= vms_pop();
return r;
}

/*:303*//*304:*/
#line 5765 "lossless.w"

cell
llt_GC_Mark_mklonglong(int x,
int y,
int z)
{
cell r;
vms_push(int_new(z));
r= int_new(y);
cdr(r)= vms_pop();
vms_push(r);
r= int_new(x);
cdr(r)= vms_pop();
return r;
}

/*:304*//*305:*/
#line 5781 "lossless.w"

cell
llt_GC_Mark_mkpair(boolean proper_p)
{
cell r= cons(VOID,UNDEFINED);
if(proper_p)
cdr(r)= NIL;
return r;
}

/*:305*//*306:*/
#line 5791 "lossless.w"

cell
llt_GC_Mark_mkvector(void)
{
cell r;
int i,j;
r= vector_new_imp(abs(UNDEFINED),0,NIL);
for(i= 0,j= -1;j>=UNDEFINED;i++,j--)
vector_ref(r,i)= j;
return r;
}

/*:306*//*307:*/
#line 5806 "lossless.w"

void
llt_GC_Mark_prepare(llt_Fixture*fix)
{
fix->copy= llt_serialise(fix->safe,btrue);
}

/*:307*//*308:*/
#line 5813 "lossless.w"

void
llt_GC_Mark_destroy(llt_Fixture*fix)
{
free(fix->copy);
}

/*:308*//*309:*/
#line 5820 "lossless.w"

void
llt_GC_Mark_act(llt_Fixture*fix)
{
mark(fix->safe);
}

/*:309*//*310:*/
#line 5827 "lossless.w"

boolean
llt_GC_Mark_test(llt_Fixture*fix)
{
char buf[TEST_BUFSIZE];
boolean ok;
ok= tap_ok(llt_GC_Mark_is_marked_p(fix->safe),
fpmsgf("the object is fully marked"));
llt_GC_Mark_unmark_m(fix->safe);
tap_again(ok,llt_compare_serial(fix->copy,fix->safe,btrue),
fpmsgf("the object is unchanged"));
return ok;
}

/*:310*//*311:*/
#line 5841 "lossless.w"

void
llt_GC_Mark_fix(llt_Fixture*fix,
const char*name,
char*suffix,
cell value)
{
fix->prepare= llt_GC_Mark_prepare;
fix->destroy= llt_GC_Mark_destroy;
fix->act= llt_GC_Mark_act;
fix->test= llt_GC_Mark_test;
fix->name= (char*)name;
fix->suffix= suffix;
fix->safe= value;
}

/*:311*//*312:*/
#line 5860 "lossless.w"

#define mkfix(n,o) \
        llt_GC_Mark_fix(((llt_Fixture *) r->data) + (n), __func__, #o, o)
llt_buffer*
llt_GC_Mark__Global(void)
{
llt_buffer*r= llt_alloc(6,llt_Fixture);
mkfix(0,NIL);
mkfix(1,FALSE);
mkfix(2,TRUE);
mkfix(3,END_OF_FILE);
mkfix(4,VOID);
mkfix(5,UNDEFINED);
return r;
}
#undef mkfix

/*:312*//*313:*/
#line 5880 "lossless.w"

void
llt_GC_Mark__PLAV_prepare(llt_Fixture*fix)
{
switch(fix->simplex){
case LLT_GC_MARK_SIMPLE_ATOM:
fix->safe= llt_GC_Mark_mkatom("forty-two");
break;
case LLT_GC_MARK_SIMPLE_LONG_ATOM:
fix->safe= int_new(42);
break;
case LLT_GC_MARK_SIMPLE_PAIR:
fix->safe= llt_GC_Mark_mkpair(fix->proper_pair_p);
break;
case LLT_GC_MARK_SIMPLE_VECTOR:
fix->safe= llt_GC_Mark_mkvector();
break;
}
llt_GC_Mark_prepare(fix);
}

/*:313*//*314:*/
#line 5901 "lossless.w"

llt_buffer*
llt_GC_Mark__Atom(void)
{
llt_buffer*fix= llt_alloc(1,llt_Fixture);
llt_GC_Mark_fix((llt_Fixture*)fix->data,__func__,NULL,NIL);
((llt_Fixture*)fix->data)->simplex= LLT_GC_MARK_SIMPLE_ATOM;
((llt_Fixture*)fix->data)->prepare= llt_GC_Mark__PLAV_prepare;
return fix;
}

/*:314*//*315:*/
#line 5912 "lossless.w"

llt_buffer*
llt_GC_Mark__Long_Atom(void)
{
llt_buffer*fix= llt_alloc(1,llt_Fixture);
llt_GC_Mark_fix((llt_Fixture*)fix->data,__func__,NULL,NIL);
((llt_Fixture*)fix->data)->simplex= LLT_GC_MARK_SIMPLE_LONG_ATOM;
((llt_Fixture*)fix->data)->prepare= llt_GC_Mark__PLAV_prepare;
return fix;
}

/*:315*//*316:*/
#line 5923 "lossless.w"

llt_buffer*
llt_GC_Mark__Pair(void)
{
llt_buffer*r;
llt_Fixture*fix;
r= llt_alloc(2,llt_Fixture);
fix= (llt_Fixture*)r->data;
llt_GC_Mark_fix(fix+0,__func__,NULL,NIL);
llt_GC_Mark_fix(fix+1,__func__,NULL,NIL);
fix[0].simplex= fix[1].simplex= LLT_GC_MARK_SIMPLE_PAIR;
fix[0].prepare= fix[1].prepare= llt_GC_Mark__PLAV_prepare;
fix[0].proper_pair_p= btrue;
return r;
}

/*:316*//*317:*/
#line 5939 "lossless.w"

llt_buffer*
llt_GC_Mark__Vector(void)
{
llt_buffer*fix= llt_alloc(1,llt_Fixture);
llt_GC_Mark_fix((llt_Fixture*)fix->data,__func__,NULL,NIL);
((llt_Fixture*)fix->data)->simplex= LLT_GC_MARK_SIMPLE_VECTOR;
((llt_Fixture*)fix->data)->prepare= llt_GC_Mark__PLAV_prepare;
return fix;
}

/*:317*//*318:*/
#line 5953 "lossless.w"

void
llt_GC_Mark__Recursive_prepare_imp(llt_Fixture*fix,
enum llt_GC_Mark_recursion c)
{
switch(c){
/*319:*/
#line 5977 "lossless.w"

case LLT_GC_MARK_RECURSIVE_PA:
fix->safe= llt_GC_Mark_mkpair(bfalse);
car(fix->safe)= llt_GC_Mark_mkatom("forty-two");
cdr(fix->safe)= llt_GC_Mark_mkatom("twoty-four");
break;
case LLT_GC_MARK_RECURSIVE_PL:
fix->safe= llt_GC_Mark_mkpair(bfalse);
car(fix->safe)= llt_GC_Mark_mklong(2048,42);
cdr(fix->safe)= llt_GC_Mark_mklong(8042,24);
break;
case LLT_GC_MARK_RECURSIVE_PP:
fix->safe= llt_GC_Mark_mkpair(bfalse);
car(fix->safe)= llt_GC_Mark_mkpair(btrue);
cdr(fix->safe)= llt_GC_Mark_mkpair(bfalse);
break;
case LLT_GC_MARK_RECURSIVE_PV:
fix->safe= llt_GC_Mark_mkpair(bfalse);
car(fix->safe)= llt_GC_Mark_mkvector();
cdr(fix->safe)= llt_GC_Mark_mkvector();
break;
case LLT_GC_MARK_RECURSIVE_PLL:
fix->safe= llt_GC_Mark_mkpair(bfalse);
car(fix->safe)= llt_GC_Mark_mklonglong(1024,2048,42);
cdr(fix->safe)= llt_GC_Mark_mklonglong(4201,4820,24);
break;

/*:319*/
#line 5959 "lossless.w"

/*320:*/
#line 6004 "lossless.w"

case LLT_GC_MARK_RECURSIVE_VA:
fix->safe= llt_GC_Mark_mkvector();
vector_ref(fix->safe,4)= llt_GC_Mark_mkatom("42");
vector_ref(fix->safe,2)= llt_GC_Mark_mkatom("24");
break;
case LLT_GC_MARK_RECURSIVE_VL:
fix->safe= llt_GC_Mark_mkvector();
vector_ref(fix->safe,4)= llt_GC_Mark_mklong(2048,42);
vector_ref(fix->safe,2)= llt_GC_Mark_mklong(8042,24);
break;
case LLT_GC_MARK_RECURSIVE_VP:
fix->safe= llt_GC_Mark_mkvector();
vector_ref(fix->safe,4)= llt_GC_Mark_mkpair(btrue);
vector_ref(fix->safe,2)= llt_GC_Mark_mkpair(bfalse);
break;
case LLT_GC_MARK_RECURSIVE_VV:
fix->safe= llt_GC_Mark_mkvector();
vector_ref(fix->safe,4)= llt_GC_Mark_mkvector();
vector_ref(fix->safe,2)= llt_GC_Mark_mkvector();
break;
case LLT_GC_MARK_RECURSIVE_VLL:
fix->safe= llt_GC_Mark_mkvector();
vector_ref(fix->safe,4)= llt_GC_Mark_mklonglong(1024,2048,42);
vector_ref(fix->safe,2)= llt_GC_Mark_mklonglong(4201,4820,24);
break;

/*:320*/
#line 5960 "lossless.w"

/*321:*/
#line 6031 "lossless.w"

case LLT_GC_MARK_RECURSIVE_LL:
fix->safe= llt_GC_Mark_mklong(1024,42);
break;
case LLT_GC_MARK_RECURSIVE_LLL:
fix->safe= llt_GC_Mark_mklonglong(1024,2048,42);
break;

/*:321*/
#line 5961 "lossless.w"

/*322:*/
#line 6039 "lossless.w"

case LLT_GC_MARK_RECURSIVE_PPA:
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_PA);
Tmp_Test= fix->safe;
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_PA);
fix->safe= cons(fix->safe,Tmp_Test);
break;
case LLT_GC_MARK_RECURSIVE_PPL:
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_PL);
Tmp_Test= fix->safe;
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_PL);
fix->safe= cons(fix->safe,Tmp_Test);
break;
case LLT_GC_MARK_RECURSIVE_PPP:
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_PP);
Tmp_Test= fix->safe;
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_PP);
fix->safe= cons(fix->safe,Tmp_Test);
break;
case LLT_GC_MARK_RECURSIVE_PPV:
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_PV);
Tmp_Test= fix->safe;
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_PV);
fix->safe= cons(fix->safe,Tmp_Test);
break;

/*:322*/
#line 5962 "lossless.w"

/*323:*/
#line 6065 "lossless.w"

case LLT_GC_MARK_RECURSIVE_PVA:
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_VA);
Tmp_Test= fix->safe;
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_VA);
fix->safe= cons(fix->safe,Tmp_Test);
break;
case LLT_GC_MARK_RECURSIVE_PVL:
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_VL);
Tmp_Test= fix->safe;
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_VL);
fix->safe= cons(fix->safe,Tmp_Test);
break;
case LLT_GC_MARK_RECURSIVE_PVP:
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_VP);
Tmp_Test= fix->safe;
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_VP);
fix->safe= cons(fix->safe,Tmp_Test);
break;
case LLT_GC_MARK_RECURSIVE_PVV:
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_VV);
Tmp_Test= fix->safe;
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_VV);
fix->safe= cons(fix->safe,Tmp_Test);
break;

/*:323*/
#line 5963 "lossless.w"

/*324:*/
#line 6091 "lossless.w"

case LLT_GC_MARK_RECURSIVE_VPA:
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_PA);
Tmp_Test= fix->safe;
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_PA);
Tmp_Test= cons(fix->safe,Tmp_Test);
fix->safe= llt_GC_Mark_mkvector();
vector_ref(fix->safe,4)= car(Tmp_Test);
vector_ref(fix->safe,2)= cdr(Tmp_Test);
break;
case LLT_GC_MARK_RECURSIVE_VPL:
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_PL);
Tmp_Test= fix->safe;
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_PL);
Tmp_Test= cons(fix->safe,Tmp_Test);
fix->safe= llt_GC_Mark_mkvector();
vector_ref(fix->safe,4)= car(Tmp_Test);
vector_ref(fix->safe,2)= cdr(Tmp_Test);
break;
case LLT_GC_MARK_RECURSIVE_VPP:
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_PP);
Tmp_Test= fix->safe;
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_PP);
Tmp_Test= cons(fix->safe,Tmp_Test);
fix->safe= llt_GC_Mark_mkvector();
vector_ref(fix->safe,4)= car(Tmp_Test);
vector_ref(fix->safe,2)= cdr(Tmp_Test);
break;
case LLT_GC_MARK_RECURSIVE_VPV:
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_PV);
Tmp_Test= fix->safe;
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_PV);
Tmp_Test= cons(fix->safe,Tmp_Test);
fix->safe= llt_GC_Mark_mkvector();
vector_ref(fix->safe,4)= car(Tmp_Test);
vector_ref(fix->safe,2)= cdr(Tmp_Test);
break;

/*:324*/
#line 5964 "lossless.w"

/*325:*/
#line 6129 "lossless.w"

case LLT_GC_MARK_RECURSIVE_VVA:
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_VA);
Tmp_Test= fix->safe;
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_VA);
Tmp_Test= cons(fix->safe,Tmp_Test);
fix->safe= llt_GC_Mark_mkvector();
vector_ref(fix->safe,4)= car(Tmp_Test);
vector_ref(fix->safe,2)= cdr(Tmp_Test);
break;
case LLT_GC_MARK_RECURSIVE_VVL:
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_VL);
Tmp_Test= fix->safe;
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_VL);
Tmp_Test= cons(fix->safe,Tmp_Test);
fix->safe= llt_GC_Mark_mkvector();
vector_ref(fix->safe,4)= car(Tmp_Test);
vector_ref(fix->safe,2)= cdr(Tmp_Test);
break;
case LLT_GC_MARK_RECURSIVE_VVP:
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_VP);
Tmp_Test= fix->safe;
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_VP);
Tmp_Test= cons(fix->safe,Tmp_Test);
fix->safe= llt_GC_Mark_mkvector();
vector_ref(fix->safe,4)= car(Tmp_Test);
vector_ref(fix->safe,2)= cdr(Tmp_Test);
break;
case LLT_GC_MARK_RECURSIVE_VVV:
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_VV);
Tmp_Test= fix->safe;
llt_GC_Mark__Recursive_prepare_imp(fix,LLT_GC_MARK_RECURSIVE_VV);
Tmp_Test= cons(fix->safe,Tmp_Test);
fix->safe= llt_GC_Mark_mkvector();
vector_ref(fix->safe,4)= car(Tmp_Test);
vector_ref(fix->safe,2)= cdr(Tmp_Test);
break;

/*:325*/
#line 5965 "lossless.w"

}
}

void
llt_GC_Mark__Recursive_prepare(llt_Fixture*fix)
{
llt_GC_Mark__Recursive_prepare_imp(fix,fix->complex);
Tmp_Test= NIL;
llt_GC_Mark_prepare(fix);
}

/*:318*//*326:*/
#line 6173 "lossless.w"

llt_buffer*
llt_GC_Mark__Recursive_P(void)
{
llt_buffer*r= llt_alloc(5,llt_Fixture);
llt_GC_Mark_recfix(r,0,LLT_GC_MARK_RECURSIVE_PA);
llt_GC_Mark_recfix(r,1,LLT_GC_MARK_RECURSIVE_PL);
llt_GC_Mark_recfix(r,2,LLT_GC_MARK_RECURSIVE_PP);
llt_GC_Mark_recfix(r,3,LLT_GC_MARK_RECURSIVE_PV);
llt_GC_Mark_recfix(r,4,LLT_GC_MARK_RECURSIVE_PLL);
return r;
}

/*:326*//*327:*/
#line 6186 "lossless.w"

llt_buffer*
llt_GC_Mark__Recursive_V(void)
{
llt_buffer*r= llt_alloc(5,llt_Fixture);
llt_GC_Mark_recfix(r,0,LLT_GC_MARK_RECURSIVE_VA);
llt_GC_Mark_recfix(r,1,LLT_GC_MARK_RECURSIVE_VL);
llt_GC_Mark_recfix(r,2,LLT_GC_MARK_RECURSIVE_VP);
llt_GC_Mark_recfix(r,3,LLT_GC_MARK_RECURSIVE_VV);
llt_GC_Mark_recfix(r,4,LLT_GC_MARK_RECURSIVE_VLL);
return r;
}

/*:327*//*328:*/
#line 6199 "lossless.w"

llt_buffer*
llt_GC_Mark__Recursive_L(void)
{
llt_buffer*r= llt_alloc(2,llt_Fixture);
llt_GC_Mark_recfix(r,0,LLT_GC_MARK_RECURSIVE_LL);
llt_GC_Mark_recfix(r,1,LLT_GC_MARK_RECURSIVE_LLL);
return r;
}

/*:328*//*329:*/
#line 6209 "lossless.w"

llt_buffer*
llt_GC_Mark__Recursive_PP(void)
{
llt_buffer*r= llt_alloc(4,llt_Fixture);
llt_GC_Mark_recfix(r,0,LLT_GC_MARK_RECURSIVE_PPA);
llt_GC_Mark_recfix(r,1,LLT_GC_MARK_RECURSIVE_PPL);
llt_GC_Mark_recfix(r,2,LLT_GC_MARK_RECURSIVE_PPP);
llt_GC_Mark_recfix(r,3,LLT_GC_MARK_RECURSIVE_PPV);
return r;
}

/*:329*//*330:*/
#line 6221 "lossless.w"

llt_buffer*
llt_GC_Mark__Recursive_PV(void)
{
llt_buffer*r= llt_alloc(4,llt_Fixture);
llt_GC_Mark_recfix(r,0,LLT_GC_MARK_RECURSIVE_PVA);
llt_GC_Mark_recfix(r,1,LLT_GC_MARK_RECURSIVE_PVL);
llt_GC_Mark_recfix(r,2,LLT_GC_MARK_RECURSIVE_PVP);
llt_GC_Mark_recfix(r,3,LLT_GC_MARK_RECURSIVE_PVV);
return r;
}

/*:330*//*331:*/
#line 6233 "lossless.w"

llt_buffer*
llt_GC_Mark__Recursive_VP(void)
{
llt_buffer*r= llt_alloc(4,llt_Fixture);
llt_GC_Mark_recfix(r,0,LLT_GC_MARK_RECURSIVE_VPA);
llt_GC_Mark_recfix(r,1,LLT_GC_MARK_RECURSIVE_VPL);
llt_GC_Mark_recfix(r,2,LLT_GC_MARK_RECURSIVE_VPP);
llt_GC_Mark_recfix(r,3,LLT_GC_MARK_RECURSIVE_VPV);
return r;
}

/*:331*//*332:*/
#line 6245 "lossless.w"

llt_buffer*
llt_GC_Mark__Recursive_VV(void)
{
llt_buffer*r= llt_alloc(4,llt_Fixture);
llt_GC_Mark_recfix(r,0,LLT_GC_MARK_RECURSIVE_VVA);
llt_GC_Mark_recfix(r,1,LLT_GC_MARK_RECURSIVE_VVL);
llt_GC_Mark_recfix(r,2,LLT_GC_MARK_RECURSIVE_VVP);
llt_GC_Mark_recfix(r,3,LLT_GC_MARK_RECURSIVE_VVV);
return r;
}

/*:332*/
#line 5697 "lossless.w"


llt_fixture Test_Fixtures[]= {
llt_GC_Mark__Global,
llt_GC_Mark__Atom,
llt_GC_Mark__Long_Atom,
llt_GC_Mark__Pair,
llt_GC_Mark__Vector,
llt_GC_Mark__Recursive_P,
llt_GC_Mark__Recursive_V,
llt_GC_Mark__Recursive_L,
llt_GC_Mark__Recursive_PP,
llt_GC_Mark__Recursive_PV,
llt_GC_Mark__Recursive_VP,
llt_GC_Mark__Recursive_VV,
NULL
};

/*:300*/
