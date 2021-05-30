/*283:*/
#line 5357 "lossless.w"

#define LLT_NOINIT
/*255:*/
#line 4821 "lossless.w"

#define LL_TEST
#include "lossless.h"
#include "llt.h"

/*:255*/
#line 5359 "lossless.w"


enum llt_Grow_Vector_Pool_result{
LLT_GROW_VECTOR_POOL_SUCCESS,
LLT_GROW_VECTOR_POOL_FAIL
};

struct llt_Fixture{
LLT_FIXTURE_HEADER;
enum llt_Grow_Vector_Pool_result expect;
int allocations;
int Poolsize;
int Segment;
cell*VECTOR;
cell*save_VECTOR;
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
#line 5376 "lossless.w"


/*284:*/
#line 5388 "lossless.w"

void
llt_Grow_Vector_Pool_prepare(llt_Fixture*fix)
{
if(fix->Poolsize){
int cs= fix->Poolsize;
fix->save_VECTOR= reallocarray(NULL,cs,sizeof(cell));
bcopy(fix->VECTOR,fix->save_VECTOR,sizeof(cell)*cs);
}
VECTOR= fix->VECTOR;
Vectors_Poolsize= fix->Poolsize;
Vectors_Segment= fix->Segment;
}

/*:284*//*285:*/
#line 5402 "lossless.w"

void
llt_Grow_Vector_Pool_destroy(llt_Fixture*fix)
{
free(VECTOR);
free(fix->save_VECTOR);
VECTOR= NULL;
Vectors_Poolsize= 0;
Vectors_Segment= HEAP_SEGMENT;
}

/*:285*//*286:*/
#line 5413 "lossless.w"

void
llt_Grow_Vector_Pool_act(llt_Fixture*fix)
{
jmp_buf save_jmp;
Allocate_Success= fix->allocations;
memcpy(&save_jmp,&Goto_Begin,sizeof(jmp_buf));
if(!setjmp(Goto_Begin))
new_vector_segment();
Allocate_Success= -1;
memcpy(&Goto_Begin,&save_jmp,sizeof(jmp_buf));
}

/*:286*//*287:*/
#line 5426 "lossless.w"

boolean
llt_Grow_Vector_Pool_test(llt_Fixture*fix)
{
boolean ok;
char buf[TEST_BUFSIZE]= {0};
switch(fix->expect){
case LLT_GROW_VECTOR_POOL_SUCCESS:
/*288:*/
#line 5443 "lossless.w"

ok= tap_ok(Vectors_Poolsize==(fix->Poolsize+fix->Segment),
fpmsgf("Vectors_Poolsize is increased"));
tap_more(ok,Vectors_Segment==(fix->Poolsize+fix->Segment)/2,
fpmsgf("Vectors_Segment is increased"));
tap_more(ok,VECTOR!=NULL,
fpmsgf("VECTOR is not NULL"));
tap_more(ok,!bcmp(VECTOR,fix->save_VECTOR,sizeof(cell)*fix->Poolsize),
fpmsgf("VECTOR heap is unchanged"));

/*:288*/
#line 5434 "lossless.w"

break;
case LLT_GROW_VECTOR_POOL_FAIL:
/*289:*/
#line 5453 "lossless.w"

ok= tap_ok(Vectors_Poolsize==fix->Poolsize,
fpmsgf("Vectors_Poolsize is not increased"));
tap_more(ok,Vectors_Segment==fix->Segment,
fpmsgf("Vectors_Segment is not increased"));
tap_more(ok,VECTOR==fix->VECTOR,
fpmsgf("VECTOR is unchanged"));

/*:289*/
#line 5437 "lossless.w"

break;
}
return ok;
}

/*:287*//*290:*/
#line 5461 "lossless.w"

llt_buffer*
llt_Grow_Vector_Pool_fix(const char*name)
{
llt_buffer*r;
llt_Fixture*fix;
r= llt_alloc(1,llt_Fixture);
fix= (llt_Fixture*)r->data;
fix->name= (char*)name;
fix->prepare= llt_Grow_Vector_Pool_prepare;
fix->destroy= llt_Grow_Vector_Pool_destroy;
fix->act= llt_Grow_Vector_Pool_act;
fix->test= llt_Grow_Vector_Pool_test;
fix->skip_gc_p= btrue;
fix->expect= LLT_GROW_VECTOR_POOL_SUCCESS;
fix->allocations= -1;
fix->Segment= HEAP_SEGMENT;
return r;
}

/*:290*//*291:*/
#line 5481 "lossless.w"

llt_buffer*
llt_Grow_Vector_Pool__Empty_Success(void)
{
return llt_Grow_Vector_Pool_fix(__func__);
}

/*:291*//*292:*/
#line 5488 "lossless.w"

llt_buffer*
llt_Grow_Vector_Pool__Empty_Fail(void)
{
llt_buffer*r= llt_Grow_Vector_Pool_fix(__func__);
((llt_Fixture*)r->data)->expect= LLT_GROW_VECTOR_POOL_FAIL;
((llt_Fixture*)r->data)->allocations= 0;
return r;
}

/*:292*//*293:*/
#line 5498 "lossless.w"

void
llt_Grow_Vector_Pool__fill(llt_Fixture*fix)
{
size_t i;
fix->VECTOR= reallocarray(NULL,fix->Poolsize,sizeof(cell));
for(i= 0;i<(fix->Poolsize*sizeof(cell))/sizeof(int);i++)
*(((int*)fix->VECTOR)+i)= rand();
}

/*:293*//*294:*/
#line 5508 "lossless.w"

llt_buffer*
llt_Grow_Vector_Pool__Full_Success(void)
{
llt_buffer*r= llt_Grow_Vector_Pool_fix(__func__);
((llt_Fixture*)r->data)->Poolsize= HEAP_SEGMENT;
llt_Grow_Vector_Pool__fill((llt_Fixture*)r->data);
return r;
}

/*:294*//*295:*/
#line 5518 "lossless.w"

llt_buffer*
llt_Grow_Vector_Pool__Full_Fail(void)
{
llt_buffer*r= llt_Grow_Vector_Pool_fix(__func__);
((llt_Fixture*)r->data)->expect= LLT_GROW_VECTOR_POOL_FAIL;
((llt_Fixture*)r->data)->allocations= 0;
((llt_Fixture*)r->data)->Poolsize= HEAP_SEGMENT;
llt_Grow_Vector_Pool__fill((llt_Fixture*)r->data);
return r;
}

/*:295*/
#line 5378 "lossless.w"


llt_fixture Test_Fixtures[]= {
llt_Grow_Vector_Pool__Empty_Success,
llt_Grow_Vector_Pool__Empty_Fail,
llt_Grow_Vector_Pool__Full_Success,
llt_Grow_Vector_Pool__Full_Fail,
NULL
};

/*:283*/
