/*343:*/
#line 6496 "lossless.w"

/*258:*/
#line 4878 "lossless.w"

#define LL_TEST
#include "lossless.h"
#include "llt.h"

/*:258*/
#line 6497 "lossless.w"


struct llt_Fixture{
LLT_FIXTURE_HEADER;
char*pattern;
int ret_val;
size_t safe_size;
llt_buffer*cell_buf;
llt_buffer*offset_buf;
llt_buffer*safe_buf;
llt_buffer*unsafe_buf;
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
#line 6510 "lossless.w"


/*344:*/
#line 6533 "lossless.w"



void
llt_GC_Vector_prepare(llt_Fixture*fix)
{
cell g,v;
char buf[TEST_BUFSIZE],*p,*s,*t;
int i,n,z;
if(!fix->pattern)
fix->pattern= "L";
fix->cell_buf= llt_alloc(0,cell);
fix->offset_buf= llt_alloc(0,cell);
g= NIL;
n= SCHAR_MAX;
s= LLT_GC_VECTOR__SIZE;
t= LLT_GC_VECTOR__SHAPE;
for(p= (char*)fix->pattern;*p;p++){
if(*s=='\0')
s= LLT_GC_VECTOR__SIZE;
/*345:*/
#line 6570 "lossless.w"

v= vector_new((z= *s++-'0'),NIL);
for(i= 0;i<z;i++){
if(*t=='\0')
t= LLT_GC_VECTOR__SHAPE;
switch(*t++){
case'G':
vector_ref(v,i)= g--;
if(g<UNDEFINED)
g= NIL;
break;
case'N':
vector_ref(v,i)= int_new(n+= 42);
break;
case'S':
snprintf(buf,TEST_BUFSIZE,"testing-%d",n+= 42);
vector_ref(v,i)= sym(buf);
break;
}
}

/*:345*/
#line 6553 "lossless.w"

if(*p=='L'){
/*346:*/
#line 6595 "lossless.w"

n= fix->cell_buf->len;
llt_grow(fix->cell_buf,1);
llt_grow(fix->offset_buf,1);
((cell*)fix->cell_buf->data)[n]= v;
((cell*)fix->offset_buf->data)[n]= vector_offset(v);

/*:346*/
#line 6555 "lossless.w"

vms_push(v);
}else
cts_push(v);
}
/*347:*/
#line 6606 "lossless.w"

fix->safe_buf= llt_alloc(0,llt_buffer*);
VMS= list_reverse_m(VMS,btrue);
n= 0;
for(v= VMS;!null_p(v);v= cdr(v),n++){
llt_grow(fix->safe_buf,1);
((llt_buffer**)fix->safe_buf->data)[n]
= llt_serialise(car(v),bfalse);
}

/*:347*/
#line 6560 "lossless.w"

/*348:*/
#line 6620 "lossless.w"

fix->unsafe_buf= llt_alloc(0,cell);
n= 0;
for(v= CTS;!null_p(v);v= cdr(v))
llt_extend_serial(fix->unsafe_buf,llt_copy_refs(car(v)),n);

/*:348*/
#line 6561 "lossless.w"

cts_reset();
}

/*:344*//*349:*/
#line 6626 "lossless.w"

boolean
llt_GC_Vector_test(llt_Fixture*fix)
{
char buf[TEST_BUFSIZE],*p,*s;
boolean ok,liveok,freeok,tagok,*freelist;
int delta,live,unused,f,i;
cell j;
freelist= calloc(Cells_Poolsize,sizeof(boolean));
for(j= Cells_Free;!null_p(j);j= cdr(j))
freelist[j]= btrue;
delta= live= unused= 0;
s= LLT_GC_VECTOR__SIZE;
ok= btrue;
for(i= 0,p= (char*)fix->pattern;*p;i++,p++){
if(*s=='\0')
s= LLT_GC_VECTOR__SIZE;
if(*p=='L'){
/*350:*/
#line 6654 "lossless.w"

liveok= llt_compare_serial(((llt_buffer**)fix->safe_buf->data)[live],
((cell*)fix->cell_buf->data)[live],bfalse);
tap_more(ok,liveok,fpmsgf("(L-%d) object is unchanged",live));
liveok= vector_offset(((cell*)fix->cell_buf->data)[live])
==((cell*)fix->offset_buf->data)[live]-delta;
tap_more(ok,liveok,fpmsgf("(L-%d), object is defragmented",live));
live++;

/*:350*/
#line 6644 "lossless.w"

}else{
/*351:*/
#line 6663 "lossless.w"

f= *s-'0';
delta+= f?vector_realsize(f):0;
tagok= freeok= btrue;
for(i= 0;i<(int)fix->unsafe_buf->len;i++){
j= ((cell*)fix->unsafe_buf->data)[i];
if(special_p(j)||symbol_p(j)||smallint_p(j))
continue;
tagok= (tag(j)==TAG_NONE)&&tagok;
freeok= freelist[i]&&freeok;
}
tap_more(ok,tagok,fpmsgf("(U-%d) object's tag is cleared",unused));
tap_more(ok,freeok,fpmsgf("(U-%d) object is in the free list",unused));
unused++;

/*:351*/
#line 6646 "lossless.w"

}
s++;
}
free(freelist);
return ok;
}

/*:349*//*352:*/
#line 6678 "lossless.w"

void
llt_GC_Vector_destroy(llt_Fixture*fix)
{
free(fix->cell_buf);
free(fix->offset_buf);
free(fix->safe_buf);
free(fix->unsafe_buf);
vm_init_imp();
}

/*:352*//*353:*/
#line 6689 "lossless.w"

void
llt_GC_Vector_act(llt_Fixture*fix)
{
fix->ret_val= gc_vectors();
}

/*:353*//*354:*/
#line 6696 "lossless.w"

void
llt_GC_Vector_fix(llt_Fixture*fix,
const char*name)
{
fix->name= (char*)name;
fix->prepare= llt_GC_Vector_prepare;
fix->destroy= llt_GC_Vector_destroy;
fix->act= llt_GC_Vector_act;
fix->test= llt_GC_Vector_test;
}

/*:354*//*355:*/
#line 6711 "lossless.w"

llt_buffer*
llt_GC_Vector__All(void)
{
static char*test_patterns[]= {
"L",
"LL",
"LLL",
"LLLU",
"LLLUUU",
"LLUL",
"LLUUUL",
"LULL",
"LUULL",
"LULUL",
"LUULUL",
"LUULUUL",
"LLLULLLULLL",
"LLLUUULLLUUULLL",
"UL",
"ULLL",
"ULLLU",
"UUULLL",
"UUULLLUUU",
"UUULLLUUULLL",
"UUULLLUUULLLUUU",
NULL
};
llt_buffer*r;
llt_Fixture*f;
char**p;
int i;
r= llt_alloc(0,llt_Fixture);
for(p= test_patterns,i= 0;*p;p++,i++){
r= llt_grow(r,1);
f= ((llt_Fixture*)r->data)+r->len-1;
llt_GC_Vector_fix(f,__func__);
f->suffix= f->pattern= test_patterns[i];
}
return r;
}

/*:355*/
#line 6512 "lossless.w"


llt_fixture Test_Fixtures[]= {
llt_GC_Vector__All,
NULL
};

/*:343*/
