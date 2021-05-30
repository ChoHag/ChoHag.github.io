/*1:*/
#line 51 "lossless.w"

#ifndef LOSSLESS_H
#define LOSSLESS_H
/*4:*/
#line 85 "lossless.w"

#include <ctype.h> 
#include <limits.h> 
#include <setjmp.h> 
#include <stdarg.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>  
#include <sys/types.h> 
#ifndef LL_ALLOCATE
#define LL_ALLOCATE reallocarray
#endif

/*:4*/
#line 54 "lossless.w"

#define bfalse 0
#define btrue 1
#define ERR_UNIMPLEMENTED "unimplemented"
#define error(x,d) error_imp((x) ,NIL,(d) ) 
#define ex_id car
#define ex_detail cdr
#define NIL -1
#define FALSE -2
#define TRUE -3
#define END_OF_FILE -4
#define VOID -5
#define UNDEFINED -6 \

#define TAG_NONE 0x00
#define TAG_MARK 0x80
#define TAG_STATE 0x40
#define TAG_ACARP 0x20
#define TAG_ACDRP 0x10
#define TAG_FORMAT 0x3f \

#define HEAP_SEGMENT 0x8000
#define ERR_OOM "out-of-memory"
#define ERR_OOM_P(p) do{if((p) ==NULL) error(ERR_OOM,NIL) ;}while(0) 
#define ERR_DOOM_P(p,d) do{if((p) ==NULL) error(ERR_OOM,(d) ) ;}while(0) 
#define enlarge_pool(p,m,t) do{ \
void*n; \
n= LL_ALLOCATE((p) ,(m) ,sizeof(t) ) ; \
ERR_OOM_P(n) ; \
(p) = n; \
}while(0) 
#define special_p(p) ((p) <0) 
#define boolean_p(p) ((p) ==FALSE or(p) ==TRUE) 
#define eof_p(p) ((p) ==END_OF_FILE) 
#define false_p(p) ((p) ==FALSE) 
#define null_p(p) ((p) ==NIL) 
#define true_p(p) ((p) ==TRUE) 
#define void_p(p) ((p) ==VOID) 
#define undefined_p(p) ((p) ==UNDEFINED)  \

#define mark_p(p) (!special_p(p) &&(TAG[(p) ]&TAG_MARK) ) 
#define state_p(p) (!special_p(p) &&(TAG[(p) ]&TAG_STATE) ) 
#define acar_p(p) (!special_p(p) &&(TAG[(p) ]&TAG_ACARP) ) 
#define acdr_p(p) (!special_p(p) &&(TAG[(p) ]&TAG_ACDRP) ) 
#define mark_clear(p) (TAG[(p) ]&= ~TAG_MARK) 
#define mark_set(p) (TAG[(p) ]|= TAG_MARK) 
#define state_clear(p) (TAG[(p) ]&= ~TAG_STATE) 
#define state_set(p) (TAG[(p) ]|= TAG_STATE) 
#define format(p) (TAG[(p) ]&TAG_FORMAT)  \

#define tag(p) (TAG[(p) ])  \

#define car(p) (CAR[(p) ]) 
#define cdr(p) (CDR[(p) ]) 
#define caar(p) (CAR[CAR[(p) ]]) 
#define cadr(p) (CAR[CDR[(p) ]]) 
#define cdar(p) (CDR[CAR[(p) ]]) 
#define cddr(p) (CDR[CDR[(p) ]]) 
#define caaar(p) (CAR[CAR[CAR[(p) ]]]) 
#define caadr(p) (CAR[CAR[CDR[(p) ]]]) 
#define cadar(p) (CAR[CDR[CAR[(p) ]]]) 
#define caddr(p) (CAR[CDR[CDR[(p) ]]]) 
#define cdaar(p) (CDR[CAR[CAR[(p) ]]]) 
#define cdadr(p) (CDR[CAR[CDR[(p) ]]]) 
#define cddar(p) (CDR[CDR[CAR[(p) ]]]) 
#define cdddr(p) (CDR[CDR[CDR[(p) ]]]) 
#define caaaar(p) (CAR[CAR[CAR[CAR[(p) ]]]]) 
#define caaadr(p) (CAR[CAR[CAR[CDR[(p) ]]]]) 
#define caadar(p) (CAR[CAR[CDR[CAR[(p) ]]]]) 
#define caaddr(p) (CAR[CAR[CDR[CDR[(p) ]]]]) 
#define cadaar(p) (CAR[CDR[CAR[CAR[(p) ]]]]) 
#define cadadr(p) (CAR[CDR[CAR[CDR[(p) ]]]]) 
#define caddar(p) (CAR[CDR[CDR[CAR[(p) ]]]]) 
#define cadddr(p) (CAR[CDR[CDR[CDR[(p) ]]]]) 
#define cdaaar(p) (CDR[CAR[CAR[CAR[(p) ]]]]) 
#define cdaadr(p) (CDR[CAR[CAR[CDR[(p) ]]]]) 
#define cdadar(p) (CDR[CAR[CDR[CAR[(p) ]]]]) 
#define cdaddr(p) (CDR[CAR[CDR[CDR[(p) ]]]]) 
#define cddaar(p) (CDR[CDR[CAR[CAR[(p) ]]]]) 
#define cddadr(p) (CDR[CDR[CAR[CDR[(p) ]]]]) 
#define cdddar(p) (CDR[CDR[CDR[CAR[(p) ]]]]) 
#define cddddr(p) (CDR[CDR[CDR[CDR[(p) ]]]]) 
#define FORMAT_CONS (TAG_ACARP|TAG_ACDRP|0x00) 
#define FORMAT_APPLICATIVE (TAG_ACARP|TAG_ACDRP|0x01) 
#define FORMAT_OPERATIVE (TAG_ACARP|TAG_ACDRP|0x02) 
#define FORMAT_SYNTAX (TAG_ACARP|TAG_ACDRP|0x03) 
#define FORMAT_ENVIRONMENT (TAG_ACARP|TAG_ACDRP|0x04) 
#define FORMAT_EXCEPTION (TAG_ACARP|TAG_ACDRP|0x05) 
#define FORMAT_INTEGER (TAG_ACDRP|0x00) 
#define FORMAT_SYMBOL (TAG_NONE|0x00) 
#define FORMAT_VECTOR (TAG_NONE|0x01) 
#define FORMAT_COMPILER (TAG_NONE|0x02)  \

#define atom_p(p) (!special_p(p) &&((tag(p) &TAG_FORMAT) !=(TAG_ACARP|TAG_ACDRP) ) ) 
#define pair_p(p) (!special_p(p) &&((tag(p) &TAG_FORMAT) ==(TAG_ACARP|TAG_ACDRP) ) ) 
#define applicative_p(p) (!special_p(p) &&((tag(p) &TAG_FORMAT) ==FORMAT_APPLICATIVE) ) 
#define compiler_p(p) (!special_p(p) &&((tag(p) &TAG_FORMAT) ==FORMAT_COMPILER) ) 
#define environment_p(p) (!special_p(p) &&((tag(p) &TAG_FORMAT) ==FORMAT_ENVIRONMENT) ) 
#define exception_p(p) (!special_p(p) &&((tag(p) &TAG_FORMAT) ==FORMAT_EXCEPTION) ) 
#define integer_p(p) (!special_p(p) &&((tag(p) &TAG_FORMAT) ==FORMAT_INTEGER) ) 
#define operative_p(p) (!special_p(p) &&((tag(p) &TAG_FORMAT) ==FORMAT_OPERATIVE) ) 
#define symbol_p(p) (!special_p(p) &&((tag(p) &TAG_FORMAT) ==FORMAT_SYMBOL) ) 
#define syntax_p(p) (!special_p(p) &&((tag(p) &TAG_FORMAT) ==FORMAT_SYNTAX) ) 
#define vector_p(p) (!special_p(p) &&((tag(p) &TAG_FORMAT) ==FORMAT_VECTOR) ) 
#define cons(a,d) atom((a) ,(d) ,FORMAT_CONS) 
#define VECTOR_CELL 0
#define VECTOR_SIZE 1
#define VECTOR_HEAD 2 \

#define vector_realsize(s) ((s) +VECTOR_HEAD)  \

#define vector_cell(v) (VECTOR[vector_offset(v) -(VECTOR_HEAD-VECTOR_CELL) ]) 
#define vector_index(v) (car(v) ) 
#define vector_length(v) (VECTOR[vector_offset(v) -(VECTOR_HEAD-VECTOR_SIZE) ]) 
#define vector_offset(v) (cdr(v) ) 
#define vector_ref(v,o) (VECTOR[vector_offset(v) +(o) ]) 
#define ERR_UNDERFLOW "underflow"
#define ERR_OVERFLOW "overflow"
#define CHECK_UNDERFLOW(s) if(null_p(s) ) error(ERR_UNDERFLOW,VOID) 
#define RTS_UNDERFLOW(p) if((p) <-1) error(ERR_UNDERFLOW,RTS) 
#define RTS_OVERFLOW(p) if((p) > RTSp) error(ERR_OVERFLOW,RTS) 
#define vms_clear() ((void) vms_pop() ) 
#define cts_clear() ((void) cts_pop() ) 
#define cts_reset() CTS= NIL
#define RTS_SEGMENT 0x1000
#define rts_clear(c) ((void) rts_pop(c) ) 
#define rts_reset() Fp= RTSp= -1;
#define sym(s) symbol((s) ,1) 
#define symbol_length car
#define symbol_offset cdr
#define symbol_store(s) (SYMBOL+symbol_offset(s) ) 
#define fixint_p(p) (integer_p(p) &&null_p(int_next(p) ) ) 
#define smallint_p(p) (fixint_p(p)  \
&&int_value(p) >=SCHAR_MIN \
&&int_value(p) <=SCHAR_MAX) 
#define int_value(p) ((int) (car(p) ) ) 
#define int_next cdr
#define ERR_IMPROPER_LIST "improper-list"
#define ERR_BOUND "already-bound"
#define ERR_UNBOUND "unbound" \

#define env_empty() atom(NIL,NIL,FORMAT_ENVIRONMENT) 
#define env_extend(e) atom((e) ,NIL,FORMAT_ENVIRONMENT) 
#define env_layer cdr
#define env_parent car
#define env_empty_p(e) (environment_p(e) &&null_p(car(e) ) &&null_p(cdr(e) ) ) 
#define env_root_p(e) (environment_p(e) &&null_p(car(e) ) ) 
#define env_set_fail(e) do{ \
vms_clear() ; \
error((e) ,name) ; \
}while(0) 
#define applicative_closure cdr
#define applicative_formals car
#define applicative_new(f,e,p,i)  \
closure_new_imp(FORMAT_APPLICATIVE,(f) ,(e) ,(p) ,(i) ) 
#define operative_closure cdr
#define operative_formals car
#define operative_new(f,e,p,i)  \
closure_new_imp(FORMAT_OPERATIVE,(f) ,(e) ,(p) ,(i) ) 
#define compiler_cname(c) COMPILER[car(c) ].name
#define compiler_fn(c) COMPILER[car(c) ].fn
#define vm_init() do{ \
if(setjmp(Goto_Begin) ) { \
Acc= sym("ABORT") ; \
return EXIT_FAILURE; \
} \
if(setjmp(Goto_Error) ) { \
Acc= sym("ABORT") ; \
return EXIT_FAILURE; \
} \
vm_init_imp() ; \
}while(0) 
#define vm_prepare() do{ \
setjmp(Goto_Begin) ; \
vm_prepare_imp() ; \
}while(0) 
#define vm_runtime() do{ \
if(setjmp(Goto_Error) ) { \
Ip= -1; \
if(Ip<0)  \
longjmp(Goto_Begin,1) ; \
} \
}while(0) 
#define FRAME_HEAD 4
#define frame_ip(f) rts_ref_abs((f) +1) 
#define frame_prog(f) rts_ref_abs((f) +2) 
#define frame_env(f) rts_ref_abs((f) +3) 
#define frame_fp(f) rts_ref_abs((f) +4) 
#define frame_set_ip(f,v) rts_set_abs((f) +1,(v) ) ;
#define frame_set_prog(f,v) rts_set_abs((f) +2,(v) ) ;
#define frame_set_env(f,v) rts_set_abs((f) +3,(v) ) ;
#define frame_set_fp(f,v) rts_set_abs((f) +4,(v) ) ;
#define ERR_INTERRUPTED "interrupted"
#define ERR_RECURSION "recursion"
#define ERR_UNEXPECTED "unexpected"
#define WARN_AMBIGUOUS_SYMBOL "ambiguous" \

#define READER_MAX_DEPTH 1024
#define READ_SPECIAL -10
#define READ_DOT -10
#define READ_CLOSE_BRACKET -11
#define READ_CLOSE_PAREN -12 \

#define SYNTAX_DOTTED "dotted"
#define SYNTAX_QUOTE "quote"
#define SYNTAX_QUASI "quasiquote"
#define SYNTAX_UNQUOTE "unquote"
#define SYNTAX_UNSPLICE "unquote-splicing"
#define CHAR_TERMINATE "()[]\"; \t\r\n"
#define terminable_p(c) strchr(CHAR_TERMINATE,(c) ) 
#define CHUNK_SIZE 0x80
#define READSYM_EOF_P if(c==EOF) error(ERR_ARITY_SYNTAX,NIL) 
#define BUFFER_SEGMENT 1024
#define WRITER_MAX_DEPTH 1024
#define append(b,r,c,s) do{ \
ssize_t _l= strlen(c) ; \
if((r) <=0)  \
return-1; \
if(strlcpy((b) ,(c) ,(r) ) >=(size_t) (r) )  \
return-(r) ; \
(s) += _l; \
(b) += _l; \
(r) -= _l; \
}while(0) 
#define append_write(b,r,w,d,s) do{ \
ssize_t _l= write_form((w) ,(b) ,(r) ,(d) ) ; \
if(_l<=0)  \
return-1; \
(s) += _l; \
(b) += _l; \
(r) -= _l; \
}while(0) 
#define skip(d) Ip+= (d) 
#define fetch(d) vector_ref(Prog,Ip+(d) ) 
#define ERR_COMPILE_DIRTY "compiler"
#define ERR_UNCOMBINABLE "uncombinable"
#define COMPILATION_SEGMENT 0x80 \

#define emitop(o) emit(int_new(o) ) 
#define emitq(o) do{emitop(OP_QUOTE) ;emit(o) ;}while(0) 
#define patch(i,v) (vector_ref(Compilation,(i) ) = (v) ) 
#define undot(p) ((syntax_p(p) &&car(p) ==Sym_SYNTAX_DOTTED) ?cdr(p) :(p) ) 
#define ERR_ARITY_EXTRA "extra"
#define ERR_ARITY_MISSING "missing"
#define ERR_ARITY_SYNTAX "syntax"
#define arity_error(e,c,a) error((e) ,cons((c) ,(a) ) ) 
#define llt_alloc(l,t) llt_alloc_imp((l) ,sizeof(t) ) 
#define llt_grow(o,l) ((o) = llt_grow_imp((o) ,(l) ) ) 
#define llt_grow_by(o,d) ((o) = llt_grow_imp((o) ,(o) ->len+(d) ) ) 
#define llt_extend_serial(buf,by,off) do{ \
llt_buffer*q= (by) ; \
llt_grow_by((buf) ,q->len) ; \
bcopy(q->data,(buf) ->data+((off) *q->size) ,q->len*q->size) ; \
(off) += q->len; \
free(q) ; \
}while(0) 
#define tap_fail(m) tap_ok(bfalse,(m) ) 
#define tap_pass(m) tap_ok(btrue,(m) ) 
#define tap_again(t,r,m) tap_ok(((t) = ((t) &&(r) ) ) ,(m) )  \

#define tap_more(t,r,m) (t) &= tap_ok((r) ,(m) ) 
#define tap_or(p,m) if(!tap_ok((p) ,(m) ) ) 
#define TEST_BUFSIZE 1024
#define probe_push(n,o) do{ \
vms_push(cons((o) ,NIL) ) ; \
vms_set(cons(sym(n) ,vms_ref() ) ) ; \
t= vms_pop() ; \
vms_set(cons(t,vms_ref() ) ) ; \
}while(0) 
#define TEST_VMSTATE_RUNNING 0x01
#define TEST_VMSTATE_NOT_RUNNING 0x00
#define TEST_VMSTATE_INTERRUPTED 0x02
#define TEST_VMSTATE_NOT_INTERRUPTED 0x00
#define TEST_VMSTATE_VMS 0x04
#define TEST_VMSTATE_CTS 0x08
#define TEST_VMSTATE_RTS 0x10
#define TEST_VMSTATE_STACKS (TEST_VMSTATE_VMS|TEST_VMSTATE_CTS|TEST_VMSTATE_RTS) 
#define TEST_VMSTATE_ENV_ROOT 0x20
#define TEST_VMSTATE_PROG_MAIN 0x40 \

#define test_vm_state_full(p) test_vm_state((p) , \
TEST_VMSTATE_NOT_RUNNING \
|TEST_VMSTATE_NOT_INTERRUPTED \
|TEST_VMSTATE_ENV_ROOT \
|TEST_VMSTATE_PROG_MAIN \
|TEST_VMSTATE_STACKS) 
#define test_vm_state_normal(p) test_vm_state((p) , \
TEST_VMSTATE_NOT_RUNNING \
|TEST_VMSTATE_NOT_INTERRUPTED \
|TEST_VMSTATE_PROG_MAIN \
|TEST_VMSTATE_STACKS) 
#define test_copy_env() Env
#define test_compare_env(o) ((o) ==Env) 
#define test_is_env(o,e) ((o) ==(e) ) 
#define llt_GC_Mark_mkatom sym
#define llt_GC_Mark_recfix(r,n,c) do{ \
llt_GC_Mark_fix(((llt_Fixture*) (r) ->data) +(n) ,__func__,NULL,NIL) ; \
((llt_Fixture*) (r) ->data) [(n) ].prepare= llt_GC_Mark__Recursive_prepare; \
((llt_Fixture*) (r) ->data) [(n) ].complex= (c) ; \
((llt_Fixture*) (r) ->data) [(n) ].suffix= #c; \
}while(0) 
#define LLT_GC_VECTOR__SIZE "2718281828459"
#define LLT_GC_VECTOR__SHAPE "GNS"
#define LLT_TEST_VARIABLE "test-variable"
#define LLT_VALUE_MARCO "marco?"
#define LLT_VALUE_POLO "polo!"
#define LLT_VALUE_FISH "fish..."
#define llt_Interpreter_test_compare(o) do{ \
boolean ok= llt_compare_serial(fix->save_##o,(o) ,bfalse) ; \
tap_more(all,ok,fpmsgf(#o" is unchanged") ) ; \
}while(0) 
#define CAT2(a,b) a/**/b
#define CAT3(a,b,c) a/**/b/**/c
#define CAT4(a,b,c,d) a/**/b/**/c/**/d
#define LLTCC_EVAL_FIRST_COMPLEX(xc,xa) CAT3(CAT3(" OP_QUOTE (",xa,") OP_PUSH") , \
CAT3(" OP_QUOTE ",xc," OP_LOOKUP") , \
" OP_CONS OP_COMPILE OP_RUN") 
#define LLTCC_EVAL_FIRST_LOOKUP(x) CAT3(" OP_QUOTE ",x," OP_LOOKUP") 
#define LLTCC_EVAL_FIRST_QUOTE(x) CAT2(" OP_QUOTE ",x) 
#define LLTCC_EVAL_SECOND_COMPLEX(xc,xa) CAT2(LLTCC_EVAL_FIRST_COMPLEX(xc,xa) ," OP_PUSH") 
#define LLTCC_EVAL_SECOND_LOOKUP(x) CAT2(LLTCC_EVAL_FIRST_LOOKUP(x) ," OP_PUSH") 
#define LLTCC_EVAL_SECOND_QUOTE(x) CAT2(LLTCC_EVAL_FIRST_QUOTE(x) ," OP_PUSH") 
#define LLTCC_EVAL_VALIDATE(x) CAT3(" OP_ENVIRONMENT_P OP_JUMP_TRUE ",x, \
" OP_QUOTE unexpected OP_ERROR") 
#define LLTCC_EVAL_ONEARG() " OP_COMPILE OP_RUN OP_RETURN "
#define LLTCC_EVAL_TWOARG() " OP_COMPILE OP_RUN_THERE OP_RETURN "
#define TEST_AB "(lambda x)"
#define TEST_AB_PRINT "(lambda x ...)"
#define TEST_AC "(lambda x (test!probe))"
#define TEST_AC_PRINT "("TEST_AC")"
#define TEST_ACA_INNER "(lambda (T . x1) (test!probe))"
#define TEST_ACA_OUTER "(lambda (L . x0) (L (test!probe)))"
#define TEST_ACA "("TEST_ACA_OUTER"LAMBDA)"
#define TEST_ACA_PRINT "("TEST_ACA_OUTER" (LAMBDA))"
#define TEST_ACO_INNER_BODY "(test!probe-applying (eval (car A) E))"
#define TEST_ACO_INNER "(vov ((A vov/args) (E vov/env))"TEST_ACO_INNER_BODY")"
#define TEST_ACO_OUTER "(lambda (V . x0) (V (test!probe)))"
#define TEST_ACO "("TEST_ACO_OUTER"VOV)"
#define TEST_ACO_PRINT "((LAMBDA) (vov (...) "TEST_ACO_INNER_BODY")"
#define TEST_ARA_INNER "(lambda (inner n) (test!probe))"
#define TEST_ARA_BUILD "(lambda (outer n) "TEST_ARA_INNER")"
#define TEST_ARA_PRINT TEST_ARA_BUILD
#define TEST_ARA_CALL "((LAMBDA 'out 'out-n) 'in 'in-n)"
#define TEST_ARO_INNER_BODY "(test!probe-applying A E)"
#define TEST_ARO_INNER "(vov ((A vov/args) (E vov/env))"TEST_ARO_INNER_BODY")"
#define TEST_ARO_BUILD "(lambda (outer n)"TEST_ARO_INNER")"
#define TEST_ARO_CALL "((LAMBDA 'out 'out-n) 'in 'in-n)"
#define TEST_ARO_PRINT "(LAMBDA (vov (...) "TEST_ARO_INNER_BODY"))"
#define TEST_OB "(vov ((E vov/env)))"
#define TEST_OB_PRINT "(vov ((E vov/env)) ...)"
#define TEST_OC "(vov ((A vov/args) (E vov/env)) (test!probe-applying A E))"
#define TEST_OC_PRINT "((vov (...) (test!probe-applying A E)))"
#define TEST_OCA_INNER "(lambda x1 (test!probe))"
#define TEST_OCA_OUTER "(vov ((A vov/args) (E vov/env))" \
"(cons ((eval (car A) E)) (test!probe)))"
#define TEST_OCA "("TEST_OCA_OUTER"LAMBDA)"
#define TEST_OCA_PRINT "((VOV) "TEST_OCA_INNER")"
#define TEST_OCO_INNER "(vov ((yE vov/env)) (test!probe))"
#define TEST_OCO_OUTER "(vov ((xA vov/args) (xE vov/env))" \
"(cons ((eval (car xA) xE)) (test!probe)))"
#define TEST_OCO "("TEST_OCO_OUTER TEST_OCO_INNER")"
#define TEST_OCO_PRINT "((VOV) "TEST_OCO_INNER")"
#define TEST_ORA_INNER "(lambda (inner n) (test!probe))"
#define TEST_ORA_MIXUP "(define! (current-environment) inner 'out)" \
"(define! (current-environment) outer (eval (car yA) yE))" \
"(define! (current-environment) n (eval (car (cdr yA)) yE))"
#define TEST_ORA_BUILD "(vov ((yA vov/args) (yE vov/env))" \
TEST_ORA_MIXUP TEST_ORA_INNER")"
#define TEST_ORA_CALL "((VOV 'out 'out-n) 'in 'in-n)"
#define TEST_ORA_PRINT "(vov (...) (lambda (inner n) (test!probe)))"
#define TEST_ORO_INNER_BODY "(test!probe-applying (eval '(test!probe) oE))"
#define TEST_ORO_INNER "(vov ((oE vov/env))"TEST_ORO_INNER_BODY")"
#define TEST_ORO_BUILD "(vov ((A vov/args) (E vov/env))" \
TEST_ORO_INNER")"
#define TEST_ORO_CALL "((VOV 'out 'out-n) 'in 'in-n)"
#define TEST_ORO_PRINT "(VOV (vov (...) (test!probe (eval '(test!probe) E))))"
#define GOTO_FAIL "((lambda x (error fail)))"
#define synquote_new(o) atom(Sym_SYNTAX_QUOTE,(o) ,FORMAT_SYNTAX) 

#line 55 "lossless.w"

/*144:*/
#line 2747 "lossless.w"

enum{
OP_APPLY,
OP_APPLY_TAIL,
OP_CAR,
OP_CDR,
OP_COMPILE,
OP_CONS,
OP_CYCLE,
OP_ENVIRONMENT_P,
OP_ENV_MUTATE_M,
OP_ENV_QUOTE,
OP_ENV_ROOT,
OP_ENV_SET_ROOT_M,
OP_ERROR,
OP_HALT,
OP_JUMP,
OP_JUMP_FALSE,
OP_JUMP_TRUE,
OP_LAMBDA,
OP_LIST_P,
OP_LIST_REVERSE,
OP_LIST_REVERSE_M,
OP_LOOKUP,
OP_NIL,
OP_NOOP,
OP_NULL_P,
OP_PAIR_P,
OP_PEEK,
OP_POP,
OP_PUSH,
OP_QUOTE,
OP_RETURN,
OP_RUN,
OP_RUN_THERE,
OP_SET_CAR_M,
OP_SET_CDR_M,
OP_SNOC,
OP_SWAP,
OP_SYMBOL_P,
OP_SYNTAX,
OP_VOV,
#ifdef LL_TEST
/*244:*/
#line 4633 "lossless.w"

OP_TEST_PROBE,

/*:244*/
#line 2790 "lossless.w"

#endif
OPCODE_MAX
};

/*:144*//*145:*/
#line 2799 "lossless.w"

#ifndef LL_TEST
enum{
OP_TEST_UNDEFINED_BEHAVIOUR= 0xf00f,
/*244:*/
#line 4633 "lossless.w"

OP_TEST_PROBE,

/*:244*/
#line 2803 "lossless.w"

};
#endif

/*:145*//*241:*/
#line 4602 "lossless.w"



#define tmsgf(...)test_msgf(msg, prefix, __VA_ARGS__)

/*:241*/
#line 56 "lossless.w"

/*5:*/
#line 106 "lossless.w"

typedef int32_t cell;
typedef int boolean;
typedef cell predicate;

/*:5*//*90:*/
#line 1566 "lossless.w"

typedef void(*native)(cell,cell,boolean);
typedef struct{
char*name;
native fn;
}primitive;

/*:90*//*146:*/
#line 2807 "lossless.w"

typedef struct{
char*name;
int nargs;
}opcode;

/*:146*//*227:*/
#line 4370 "lossless.w"

typedef struct{
size_t len;
size_t size;
char data[];
}llt_buffer;

/*:227*/
#line 57 "lossless.w"

/*8:*/
#line 148 "lossless.w"

void error_imp(char*,cell,cell)__dead;
void warn(char*,cell);

/*:8*//*14:*/
#line 266 "lossless.w"

void new_cells_segment(void);

/*:14*//*22:*/
#line 417 "lossless.w"

cell atom(cell,cell,char);

/*:22*//*27:*/
#line 467 "lossless.w"

void new_vector_segment(void);

/*:27*//*36:*/
#line 532 "lossless.w"

cell vector_new(int,cell);
cell vector_new_imp(int,boolean,cell);
cell vector_new_list(cell,int);
cell vector_sub(cell,int,int,int,int,cell);

/*:36*//*43:*/
#line 639 "lossless.w"

int gc(void);
int gc_vectors(void);
void mark(cell);
int sweep(void);

/*:43*//*51:*/
#line 855 "lossless.w"

cell cts_pop(void);
void cts_push(cell);
cell cts_ref(void);
void cts_set(cell);
cell rts_pop(int);
void rts_prepare(int);
void rts_push(cell);
cell rts_ref(int);
cell rts_ref_abs(int);
void rts_set(int,cell);
void rts_set_abs(int,cell);
cell vms_pop(void);
void vms_push(cell);
cell vms_ref(void);
void vms_set(cell);

/*:51*//*59:*/
#line 1054 "lossless.w"

cell symbol(char*,boolean);
void symbol_expand(void);
void symbol_reify(cell);
boolean symbol_same_p(cell,cell);
cell symbol_steal(char*);

/*:59*//*70:*/
#line 1189 "lossless.w"

cell int_new_imp(int,cell);
cell int_new(int);

/*:70*//*73:*/
#line 1222 "lossless.w"

int list_length(cell);
predicate list_p(cell,predicate,cell*);
cell list_reverse_m(cell,boolean);

/*:73*//*81:*/
#line 1380 "lossless.w"

cell env_here(cell,cell);
cell env_lift_stack(cell,cell);
cell env_search(cell,cell);
void env_set(cell,cell,cell,boolean);

/*:81*//*88:*/
#line 1539 "lossless.w"

cell closure_new_imp(char,cell,cell,cell,cell);

/*:88*//*97:*/
#line 1686 "lossless.w"

void vm_init_imp(void);
void vm_prepare_imp(void);
void vm_reset(void);

/*:97*//*104:*/
#line 1764 "lossless.w"

void frame_consume(void);
void frame_enter(cell,cell,cell);
void frame_leave(void);
void frame_push(int);

/*:104*//*109:*/
#line 1839 "lossless.w"

void interpret(void);

/*:109*//*115:*/
#line 1940 "lossless.w"

int read_byte(void);
cell read_cstring(char*);
cell read_form(void);
cell read_list(cell);
cell read_number(void);
cell read_sexp(void);
cell read_symbol(void);
void unread_byte(char);
int useful_byte(void);

/*:115*//*135:*/
#line 2430 "lossless.w"

ssize_t write_applicative(cell,char*,ssize_t,int);
ssize_t write_bytecode(cell,char*,ssize_t,int);
ssize_t write_compiler(cell,char*,ssize_t,int);
ssize_t write_environment(cell,char*,ssize_t,int);
ssize_t write_integer(cell,char*,ssize_t,int);
ssize_t write_list(cell,char*,ssize_t,int);
ssize_t write_operative(cell,char*,ssize_t,int);
ssize_t write_symbol(cell,char*,ssize_t,int);
ssize_t write_syntax(cell,char*,ssize_t,int);
ssize_t write_vector(cell,char*,ssize_t,int);
ssize_t write_form(cell,char*,ssize_t,int);

/*:135*//*167:*/
#line 3158 "lossless.w"

cell arity(cell,cell,int,boolean);
cell arity_next(cell,cell,cell,boolean,boolean);
int comefrom(void);
cell compile(cell);
cell compile_main(void);
void compile_car(cell,cell,boolean);
void compile_cdr(cell,cell,boolean);
void compile_conditional(cell,cell,boolean);
void compile_cons(cell,cell,boolean);
void compile_define_m(cell,cell,boolean);
void compile_env_current(cell,cell,boolean);
void compile_env_root(cell,cell,boolean);
void compile_error(cell,cell,boolean);
void compile_eval(cell,cell,boolean);
void compile_expression(cell,boolean);
void compile_lambda(cell,cell,boolean);
void compile_list(cell,cell,boolean);
void compile_null_p(cell,cell,boolean);
void compile_pair_p(cell,cell,boolean);
void compile_quasicompiler(cell,cell,cell,int,boolean);
void compile_quasiquote(cell,cell,boolean);
void compile_quote(cell,cell,boolean);
void compile_set_car_m(cell,cell,boolean);
void compile_set_cdr_m(cell,cell,boolean);
void compile_set_m(cell,cell,boolean);
void compile_symbol_p(cell,cell,boolean);
void compile_vov(cell,cell,boolean);
void emit(cell);

/*:167*//*206:*/
#line 4089 "lossless.w"

void compile_quasicompiler(cell,cell,cell,int,boolean);

/*:206*//*228:*/
#line 4377 "lossless.w"

llt_buffer*llt_alloc_imp(size_t,size_t);
llt_buffer*llt_grow_imp(llt_buffer*,size_t);

/*:228*//*232:*/
#line 4420 "lossless.w"

llt_buffer*llt_serialise(cell,boolean);
boolean llt_compare_serial(llt_buffer*,cell,boolean);
llt_buffer*llt_copy_refs(cell);

/*:232*//*236:*/
#line 4538 "lossless.w"

#ifdef LL_TEST
void tap_plan(int);
boolean tap_ok(boolean,char*);
int test_count_free_list(void);
char*test_msgf(char*,char*,char*,...);
void test_vm_state(char*,int);
#endif

/*:236*//*243:*/
#line 4628 "lossless.w"

void compile_testing_probe(cell,cell,boolean);
void compile_testing_probe_app(cell,cell,boolean);
cell testing_build_probe(cell);

/*:243*//*471:*/
#line 8501 "lossless.w"

#define TEST_EVAL_FOUND(var) \
if (undefined_p(var))        \
         (var) =  cadar(t);   \
else                         \
        fmore =  btrue;
#define TEST_EVAL_FIND                                      \
feval =  fprobe =  fenv =  fprog =  UNDEFINED;                    \
fmore =  bfalse;                                               \
while (!null_p(t)) {                                          \
        if (caar(t) == sym("alt-test!probe")) {             \
                TEST_EVAL_FOUND(fprobe);                    \
        } else if (caar(t) == sym("eval")) {                \
                TEST_EVAL_FOUND(feval);                     \
        } else if (caar(t) == sym("testing-environment")) { \
                TEST_EVAL_FOUND(fenv);                      \
        } else if (caar(t) == sym("testing-program")) {     \
                TEST_EVAL_FOUND(fprog);                     \
        } else                                                \
                fmore =  btrue;                                \
        t =  cdr(t);                                           \
}
void test_integrate_eval_unchanged(char*,cell,cell);

/*:471*//*501:*/
#line 9433 "lossless.w"

cell assoc_member(cell,cell);
cell assoc_content(cell,cell);
cell assoc_value(cell,cell);

/*:501*/
#line 58 "lossless.w"

/*7:*/
#line 143 "lossless.w"

extern volatile boolean Error_Handler;
extern jmp_buf Goto_Begin;
extern jmp_buf Goto_Error;

/*:7*//*13:*/
#line 261 "lossless.w"

extern cell*CAR,*CDR,Cells_Free;
extern char*TAG;
extern int Cells_Poolsize,Cells_Segment;

/*:13*//*20:*/
#line 411 "lossless.w"

extern cell Tmp_CAR,Tmp_CDR;

/*:20*//*26:*/
#line 463 "lossless.w"

extern cell*VECTOR;
extern int Vectors_Free,Vectors_Poolsize,Vectors_Segment;

/*:26*//*31:*/
#line 516 "lossless.w"

extern cell Zero_Vector;

/*:31*//*42:*/
#line 636 "lossless.w"

extern cell*ROOTS;

/*:42*//*48:*/
#line 843 "lossless.w"

extern cell CTS,RTS,VMS;
extern int RTS_Size,RTSp;

/*:48*//*57:*/
#line 1046 "lossless.w"

extern cell Symbol_Table;
extern char*SYMBOL;
extern int Symbol_Free,Symbol_Poolsize;

/*:57*//*67:*/
#line 1169 "lossless.w"

extern cell*Small_Int;

/*:67*//*79:*/
#line 1362 "lossless.w"

extern cell Sym_ERR_BOUND,Sym_ERR_UNBOUND;

/*:79*//*92:*/
#line 1584 "lossless.w"

extern primitive*COMPILER;

/*:92*//*94:*/
#line 1635 "lossless.w"

extern boolean Interrupt,Running;
extern cell Acc,Env,Prog,Prog_Main,Root;
extern int Ip;

/*:94*//*102:*/
#line 1754 "lossless.w"

extern int Fp;

/*:102*//*113:*/
#line 1926 "lossless.w"

extern char Putback[2],*Read_Pointer;
extern int Read_Level;
extern cell Sym_ERR_UNEXPECTED,Sym_SYNTAX_DOTTED,Sym_SYNTAX_QUASI;
extern cell Sym_SYNTAX_QUOTE,Sym_SYNTAX_UNQUOTE,Sym_SYNTAX_UNSPLICE;

/*:113*//*147:*/
#line 2813 "lossless.w"

extern opcode OP[OPCODE_MAX];

/*:147*//*166:*/
#line 3154 "lossless.w"

extern int Here;
extern cell Compilation;

/*:166*//*181:*/
#line 3366 "lossless.w"

extern cell Sym_ERR_ARITY_EXTRA,Sym_ERR_ARITY_MISSING,Sym_ERR_ARITY_SYNTAX;

/*:181*//*221:*/
#line 4316 "lossless.w"

#ifdef LL_TEST
extern int Allocate_Success;
#endif

/*:221*//*224:*/
#line 4342 "lossless.w"

extern cell Tmp_Test;

/*:224*//*238:*/
#line 4552 "lossless.w"

extern int Test_Plan,Next_Test;

/*:238*/
#line 59 "lossless.w"

#endif

/*:1*/
