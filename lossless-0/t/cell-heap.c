/*264:*/
#line 5050 "lossless.w"

#define LLT_NOINIT
/*255:*/
#line 4821 "lossless.w"

#define LL_TEST
#include "lossless.h"
#include "llt.h"

/*:255*/
#line 5052 "lossless.w"


enum llt_Grow_Pool_result{
LLT_GROW_POOL_SUCCESS,
LLT_GROW_POOL_FAIL_CAR,
LLT_GROW_POOL_FAIL_CDR,
LLT_GROW_POOL_FAIL_TAG
};

struct llt_Fixture{
LLT_FIXTURE_HEADER;
enum llt_Grow_Pool_result expect;
int allocations;
int Poolsize;
int Segment;
llt_buffer*CAR;
llt_buffer*CDR;
llt_buffer*TAG;
cell*save_CAR;
cell*save_CDR;
char*save_TAG;
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
#line 5075 "lossless.w"


/*265:*/
#line 5091 "lossless.w"

void
llt_Grow_Pool_prepare(llt_Fixture*fix)
{
if(Cells_Poolsize){
free(CAR);
free(CDR);
free(TAG);
}
CAR= CDR= NULL;
TAG= NULL;
if(fix->Poolsize){
enlarge_pool(CAR,fix->Poolsize,cell);
enlarge_pool(CDR,fix->Poolsize,cell);
enlarge_pool(TAG,fix->Poolsize,char);
bcopy(fix->CAR->data,CAR,sizeof(cell)*fix->Poolsize);
bcopy(fix->CDR->data,CDR,sizeof(cell)*fix->Poolsize);
bcopy(fix->TAG->data,TAG,sizeof(char)*fix->Poolsize);
fix->save_CAR= CAR;
fix->save_CDR= CDR;
fix->save_TAG= TAG;
}
Cells_Poolsize= fix->Poolsize;
Cells_Segment= fix->Segment;
}

/*:265*//*266:*/
#line 5117 "lossless.w"

void
llt_Grow_Pool_destroy(llt_Fixture*fix __unused)
{
free(CAR);
free(CDR);
free(TAG);
CAR= CDR= NULL;
TAG= NULL;
Cells_Poolsize= 0;
Cells_Segment= HEAP_SEGMENT;
}

/*:266*//*267:*/
#line 5134 "lossless.w"

void
llt_Grow_Pool_act(llt_Fixture*fix)
{
jmp_buf save_jmp;
Allocate_Success= fix->allocations;
memcpy(&save_jmp,&Goto_Begin,sizeof(jmp_buf));
if(!setjmp(Goto_Begin))
new_cells_segment();
Allocate_Success= -1;
memcpy(&Goto_Begin,&save_jmp,sizeof(jmp_buf));
}

/*:267*//*268:*/
#line 5147 "lossless.w"

boolean
llt_Grow_Pool_test(llt_Fixture*fix)
{
boolean ok;
char buf[TEST_BUFSIZE]= {0};
switch(fix->expect){
case LLT_GROW_POOL_SUCCESS:
/*269:*/
#line 5170 "lossless.w"

ok= tap_ok(Cells_Poolsize==(fix->Poolsize+fix->Segment),
fpmsgf("Cells_Poolsize is increased"));
tap_more(ok,Cells_Segment==(fix->Poolsize+fix->Segment)/2,
fpmsgf("Cells_Segment is increased"));
tap_more(ok,CAR!=CDR&&CAR!=(cell*)TAG,
fpmsgf("CAR, CDR & TAG are unique"));
tap_more(ok,CAR!=NULL,
fpmsgf("CAR is not NULL"));
tap_more(ok,!bcmp(CAR,fix->CAR->data,sizeof(cell)*fix->Poolsize),
fpmsgf("CAR heap is unchanged"));
tap_more(ok,CDR!=NULL,
fpmsgf("CDR is not NULL"));
tap_more(ok,!bcmp(CDR,fix->CDR->data,sizeof(cell)*fix->Poolsize),
fpmsgf("CDR heap is unchanged"));
tap_more(ok,TAG!=NULL,
fpmsgf("TAG is not NULL"));
tap_more(ok,!bcmp(TAG,fix->TAG->data,sizeof(char)*fix->Poolsize),
fpmsgf("TAG heap is unchanged"));

/*:269*/
#line 5155 "lossless.w"

break;
case LLT_GROW_POOL_FAIL_CAR:
/*270:*/
#line 5190 "lossless.w"

ok= tap_ok(Cells_Poolsize==fix->Poolsize,
fpmsgf("Cells_Poolsize is not increased"));
tap_more(ok,Cells_Segment==fix->Segment,
fpmsgf("Cells_Segment is not increased"));
tap_more(ok,CAR==fix->save_CAR,
fpmsgf("CAR is unchanged"));
tap_more(ok,CDR==fix->save_CDR,
fpmsgf("CDR is unchanged"));
tap_more(ok,TAG==fix->save_TAG,
fpmsgf("TAG is unchanged"));

/*:270*/
#line 5158 "lossless.w"

break;
case LLT_GROW_POOL_FAIL_CDR:
/*271:*/
#line 5202 "lossless.w"

ok= tap_ok(Cells_Poolsize==fix->Poolsize,
fpmsgf("Cells_Poolsize is not increased"));
tap_more(ok,Cells_Segment==fix->Segment,
fpmsgf("Cells_Segment is not increased"));
tap_more(ok,!bcmp(CAR,fix->CAR->data,sizeof(cell)*fix->Poolsize),
fpmsgf("CAR heap is unchanged"));
tap_more(ok,CDR==fix->save_CDR,
fpmsgf("CDR is unchanged"));
tap_more(ok,TAG==fix->save_TAG,
fpmsgf("TAG is unchanged"));

/*:271*/
#line 5161 "lossless.w"

break;
case LLT_GROW_POOL_FAIL_TAG:
/*272:*/
#line 5214 "lossless.w"

ok= tap_ok(Cells_Poolsize==fix->Poolsize,
fpmsgf("Cells_Poolsize is not increased"));
tap_more(ok,Cells_Segment==fix->Segment,
fpmsgf("Cells_Segment is not increased"));
tap_more(ok,!bcmp(CAR,fix->CAR->data,sizeof(cell)*fix->Poolsize),
fpmsgf("CAR heap is unchanged"));
tap_more(ok,!bcmp(CDR,fix->CDR->data,sizeof(cell)*fix->Poolsize),
fpmsgf("CDR heap is unchanged"));
tap_more(ok,TAG==fix->save_TAG,
fpmsgf("TAG is unchanged"));

/*:272*/
#line 5164 "lossless.w"

break;
}
return ok;
}

/*:268*//*273:*/
#line 5226 "lossless.w"

llt_buffer*
llt_Grow_Pool_fix(const char*name)
{
llt_buffer*r;
llt_Fixture*fix;
r= llt_alloc(1,llt_Fixture);
fix= (llt_Fixture*)r->data;
fix->name= (char*)name;
fix->prepare= llt_Grow_Pool_prepare;
fix->destroy= llt_Grow_Pool_destroy;
fix->act= llt_Grow_Pool_act;
fix->test= llt_Grow_Pool_test;
fix->skip_gc_p= btrue;
fix->expect= LLT_GROW_POOL_SUCCESS;
fix->allocations= -1;
fix->Segment= HEAP_SEGMENT;
return r;
}

/*:273*//*274:*/
#line 5249 "lossless.w"

llt_buffer*
llt_Grow_Pool__Initial_Success(void)
{
return llt_Grow_Pool_fix(__func__);
}

/*:274*//*275:*/
#line 5259 "lossless.w"

llt_buffer*
llt_Grow_Pool__Immediate_Fail(void)
{
llt_buffer*r= llt_Grow_Pool_fix(__func__);
((llt_Fixture*)r->data)->expect= LLT_GROW_POOL_FAIL_CAR;
((llt_Fixture*)r->data)->allocations= 0;
return r;
}

/*:275*//*276:*/
#line 5269 "lossless.w"

llt_buffer*
llt_Grow_Pool__Second_Fail(void)
{
llt_buffer*r= llt_Grow_Pool_fix(__func__);
((llt_Fixture*)r->data)->expect= LLT_GROW_POOL_FAIL_CDR;
((llt_Fixture*)r->data)->allocations= 1;
return r;
}

/*:276*//*277:*/
#line 5279 "lossless.w"

llt_buffer*
llt_Grow_Pool__Third_Fail(void)
{
llt_buffer*r= llt_Grow_Pool_fix(__func__);
((llt_Fixture*)r->data)->expect= LLT_GROW_POOL_FAIL_TAG;
((llt_Fixture*)r->data)->allocations= 2;
return r;
}

/*:277*//*278:*/
#line 5291 "lossless.w"

void
llt_Grow_Pool__fill(llt_Fixture*fix)
{
size_t i;
fix->CAR= llt_alloc(fix->Poolsize,cell);
fix->CDR= llt_alloc(fix->Poolsize,cell);
fix->TAG= llt_alloc(fix->Poolsize,char);
for(i= 0;i<(fix->Poolsize*sizeof(cell))/sizeof(int);i++)
*(((int*)fix->CAR->data)+i)= rand();
for(i= 0;i<(fix->Poolsize*sizeof(cell))/sizeof(int);i++)
*(((int*)fix->CDR->data)+i)= rand();
for(i= 0;i<(fix->Poolsize*sizeof(char))/sizeof(int);i++)
*(((int*)fix->TAG->data)+i)= rand();
}

/*:278*//*279:*/
#line 5307 "lossless.w"

llt_buffer*
llt_Grow_Pool__Full_Success(void)
{
llt_buffer*r= llt_Grow_Pool_fix(__func__);
((llt_Fixture*)r->data)->Poolsize= HEAP_SEGMENT;
llt_Grow_Pool__fill((llt_Fixture*)r->data);
return r;
}

/*:279*//*280:*/
#line 5317 "lossless.w"

llt_buffer*
llt_Grow_Pool__Full_Immediate_Fail(void)
{
llt_buffer*r= llt_Grow_Pool_fix(__func__);
((llt_Fixture*)r->data)->expect= LLT_GROW_POOL_FAIL_CAR;
((llt_Fixture*)r->data)->allocations= 0;
((llt_Fixture*)r->data)->Poolsize= HEAP_SEGMENT;
llt_Grow_Pool__fill((llt_Fixture*)r->data);
return r;
}

/*:280*//*281:*/
#line 5329 "lossless.w"

llt_buffer*
llt_Grow_Pool__Full_Second_Fail(void)
{
llt_buffer*r= llt_Grow_Pool_fix(__func__);
((llt_Fixture*)r->data)->expect= LLT_GROW_POOL_FAIL_CDR;
((llt_Fixture*)r->data)->allocations= 1;
((llt_Fixture*)r->data)->Poolsize= HEAP_SEGMENT;
llt_Grow_Pool__fill((llt_Fixture*)r->data);
return r;
}

/*:281*//*282:*/
#line 5341 "lossless.w"

llt_buffer*
llt_Grow_Pool__Full_Third_Fail(void)
{
llt_buffer*r= llt_Grow_Pool_fix(__func__);
((llt_Fixture*)r->data)->expect= LLT_GROW_POOL_FAIL_TAG;
((llt_Fixture*)r->data)->allocations= 2;
((llt_Fixture*)r->data)->Poolsize= HEAP_SEGMENT;
llt_Grow_Pool__fill((llt_Fixture*)r->data);
return r;
}

/*:282*/
#line 5077 "lossless.w"


llt_fixture Test_Fixtures[]= {
llt_Grow_Pool__Initial_Success,
llt_Grow_Pool__Immediate_Fail,
llt_Grow_Pool__Second_Fail,
llt_Grow_Pool__Third_Fail,
llt_Grow_Pool__Full_Success,
llt_Grow_Pool__Full_Immediate_Fail,
llt_Grow_Pool__Full_Second_Fail,
llt_Grow_Pool__Full_Third_Fail,
NULL
};

/*:264*/
