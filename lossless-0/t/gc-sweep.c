/*333:*/
#line 6290 "lossless.w"

/*258:*/
#line 4878 "lossless.w"

#define LL_TEST
#include "lossless.h"
#include "llt.h"

/*:258*/
#line 6291 "lossless.w"


struct llt_Fixture{
LLT_FIXTURE_HEADER;
boolean preinit_p;
cell safe;
llt_buffer*safe_buf;
size_t expect;
int ret_val;
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
#line 6302 "lossless.w"


/*334:*/
#line 6312 "lossless.w"

size_t
llt_GC_Sweep_mark_m(cell c)
{
int i;
size_t count= 0;
if(special_p(c))return 0;
mark_set(c);
count++;
if(acar_p(c))count+= llt_GC_Sweep_mark_m(car(c));
if(acdr_p(c))count+= llt_GC_Sweep_mark_m(cdr(c));
if(vector_p(c))
for(i= 0;i<vector_length(c);i++)
count+= llt_GC_Sweep_mark_m(vector_ref(c,i));
return count;
}

/*:334*//*335:*/
#line 6333 "lossless.w"

void
llt_GC_Sweep_prepare(llt_Fixture*fix)
{
if(fix->preinit_p){
Cells_Poolsize= 0;
return;
}
vms_push(cons(NIL,NIL));
cons(NIL,vms_pop());
}

/*:335*//*336:*/
#line 6347 "lossless.w"

void
llt_GC_Sweep_destroy(llt_Fixture*fix)
{
free(fix->safe_buf);
vm_init_imp();
}

/*:336*//*337:*/
#line 6355 "lossless.w"

void
llt_GC_Sweep_act(llt_Fixture*fix)
{
fix->ret_val= sweep();
}

/*:337*//*338:*/
#line 6362 "lossless.w"

boolean
llt_GC_Sweep_test(llt_Fixture*fix)
{
char buf[TEST_BUFSIZE]= {0};
cell f;
boolean ok,mark_ok_p,free_ok_p;
int i,rem;
rem= Cells_Poolsize-fix->expect;
ok= tap_ok(fix->ret_val==rem,
fpmsgf("sweep returns the number of free cells (%d)",rem));

i= test_count_free_list();
tap_more(ok,i==rem,
fpmsgf("the number of free cells is correct (%d)",rem));

mark_ok_p= btrue;
for(i= 0;i<(int)fix->expect;i++)
if(mark_p(((cell*)fix->safe_buf->data)[i]))
mark_ok_p= bfalse;
tap_more(ok,mark_ok_p,fpmsgf("the cells are unmarked"));

free_ok_p= btrue;
for(f= Cells_Free;!null_p(f);f= cdr(f))
for(i= 0;i<(int)fix->expect;i++)
if(((cell*)fix->safe_buf->data)[i]==f)
free_ok_p= bfalse;
tap_more(ok,mark_ok_p,
fpmsgf("the used cells are not in the free list"));

return ok;
}

/*:338*//*339:*/
#line 6395 "lossless.w"

void
llt_GC_Sweep_fix(llt_Fixture*fix,
const char*name)
{
fix->name= (char*)name;
fix->prepare= llt_GC_Sweep_prepare;
fix->destroy= llt_GC_Sweep_destroy;
fix->act= llt_GC_Sweep_act;
fix->test= llt_GC_Sweep_test;
fix->skip_gc_p= btrue;
}

/*:339*//*340:*/
#line 6408 "lossless.w"

llt_buffer*
llt_GC_Sweep__Empty_Pool(void)
{
llt_buffer*r;
llt_Fixture*fix;
r= llt_alloc(2,llt_Fixture);
fix= (llt_Fixture*)r->data;
llt_GC_Sweep_fix(fix+0,__func__);
llt_GC_Sweep_fix(fix+1,__func__);
fix[0].preinit_p= btrue;
fix[0].suffix= "no pool";
fix[1].suffix= "unused";
return r;
}

/*:340*//*341:*/
#line 6427 "lossless.w"

void
llt_GC_Sweep__Used_Pool_prepare(llt_Fixture*fix)
{
fix->safe= cons(VOID,UNDEFINED);
vms_push(fix->safe);
fix->expect= llt_GC_Sweep_mark_m(vms_ref());
fix->safe_buf= llt_copy_refs(fix->safe);
llt_GC_Sweep_prepare(fix);
vms_pop();
}

/*:341*//*342:*/
#line 6439 "lossless.w"

llt_buffer*
llt_GC_Sweep__Used_Pool(void)
{
llt_buffer*r= llt_alloc(1,llt_Fixture);
llt_GC_Sweep_fix((llt_Fixture*)r->data,__func__);
((llt_Fixture*)r->data)->prepare= llt_GC_Sweep__Used_Pool_prepare;
return r;
}

/*:342*/
#line 6304 "lossless.w"


llt_fixture Test_Fixtures[]= {
llt_GC_Sweep__Empty_Pool,
llt_GC_Sweep__Used_Pool,
NULL
};

/*:333*/
