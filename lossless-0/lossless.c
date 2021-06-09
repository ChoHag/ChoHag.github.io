/*2:*/
#line 68 "lossless.w"

/*4:*/
#line 87 "lossless.w"

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
#line 69 "lossless.w"

/*526:*/
#line 9921 "lossless.w"

#ifndef ll_noreturn
#  ifdef __GNUC__ 
#    define ll_noreturn __attribute__ ((__noreturn__))
#  else
#    ifdef _Noreturn
#      define ll_noreturn _Noreturn
#    else
#      define ll_noreturn 
#    endif
#  endif
#endif

#ifndef ll_unused
#  ifdef __GNUC__ 
#    define ll_unused __attribute__ ((__unused__))
#  else
#    define ll_unused 
#  endif
#endif

#ifndef reallocarray 
#define reallocarray(o,n,s) realloc((o), (n) * (s))
#endif

#ifndef strlcpy
#define strlcpy(d,s,l) ((size_t) snprintf((d), (l), "%s", (s)))
#endif

/*:526*/
#line 70 "lossless.w"

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
#define find_formal_duplicates(n,h) if(symbol_p(n) )  \
for(cell d= (h) ;!null_p(d) ;d= cdr(d) )  \
if(car(d) ==(n) )  \
arity_error(ERR_ARITY_SYNTAX,op,args) ;
#define bfixn(f,n) ((llt_Fixture*) ((f) ->data) ) [(n) ]
#define bfix0(f) bfixn((f) ,(f) ->len-2) 
#define bfix1(f) bfixn((f) ,(f) ->len-1) 
#define bfix bfix1
#define llt_alloc(l,t) llt_alloc_imp((l) ,sizeof(t) ) 
#define llt_grow(o,d) ((o) = llt_grow_imp((o) ,(o) ->len+(d) ) ) 
#define llt_extend_serial(buf,by,off) do{ \
llt_buffer*q= (by) ; \
llt_grow((buf) ,q->len) ; \
bcopy(q->data,(buf) ->data+((off) *q->size) ,q->len*q->size) ; \
(off) += q->len; \
free(q) ; \
}while(0) 
#define tap_fail(m) tap_ok(bfalse,(m) ) 
#define tap_pass(m) tap_ok(btrue,(m) ) 
#define tap_again(t,r,m) tap_ok(((t) = ((t) &&(r) ) ) ,(m) )  \

#define tap_more(t,r,m) (t) &= tap_ok((r) ,(m) ) 
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
#define LLTCC_LAMBDA_SUCCESS "(OP_QUOTE %s OP_PUSH" \
" OP_LAMBDA 7 OP_JUMP 10 OP_QUOTE #<> OP_RETURN" \
" OP_RETURN)"
#define lltfix_lambda_success(f)  \
fbuf= llt_Compiler__Lambda_build(__func__,fbuf,(f) ,"",NULL) 
#define lltfix_lambda_fail_formals(f)  \
fbuf= llt_Compiler__Lambda_build(__func__,fbuf,(f) ,"",NULL) 
#define lltfix_lambda_fail_body(b,d)  \
fbuf= llt_Compiler__Lambda_build(__func__,fbuf,"",(b) ,(d) ) 
#define LLT_BUFLET_SEGMENT 100
#define LLT_BUFLET_SLICE (LLT_BUFLET_SEGMENT/4) 
#define straffix(b,c) do{ \
*(b) ++= (c) ; \
*(b) = '\0'; \
}while(0) 
#define straffix_both(b0,b1,c) do{ \
char _c= (c) ; \
straffix((b0) ,_c) ; \
straffix((b1) ,_c) ; \
}while(0) 
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

#line 71 "lossless.w"

/*146:*/
#line 2776 "lossless.w"

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
/*247:*/
#line 4694 "lossless.w"

OP_TEST_PROBE,

/*:247*/
#line 2819 "lossless.w"

#endif
OPCODE_MAX
};

/*:146*//*147:*/
#line 2828 "lossless.w"

#ifndef LL_TEST
enum{
OP_TEST_UNDEFINED_BEHAVIOUR= 0xf00f,
/*247:*/
#line 4694 "lossless.w"

OP_TEST_PROBE,

/*:247*/
#line 2832 "lossless.w"

};
#endif

/*:147*//*244:*/
#line 4662 "lossless.w"



#define tmsgf(...)test_msgf(msg, prefix, __VA_ARGS__)

/*:244*/
#line 72 "lossless.w"

/*5:*/
#line 108 "lossless.w"

typedef int32_t cell;
typedef int boolean;
typedef cell predicate;

/*:5*//*90:*/
#line 1567 "lossless.w"

typedef void(*native)(cell,cell,boolean);
typedef struct{
char*name;
native fn;
}primitive;

/*:90*//*148:*/
#line 2836 "lossless.w"

typedef struct{
char*name;
int nargs;
}opcode;

/*:148*//*229:*/
#line 4410 "lossless.w"

typedef struct{
size_t len;
size_t size;
char data[];
}llt_buffer;

/*:229*/
#line 73 "lossless.w"

/*8:*/
#line 150 "lossless.w"

void ll_noreturn error_imp(char*,cell,cell);
void warn(char*,cell);

/*:8*//*14:*/
#line 268 "lossless.w"

void new_cells_segment(void);

/*:14*//*22:*/
#line 419 "lossless.w"

cell atom(cell,cell,char);

/*:22*//*27:*/
#line 469 "lossless.w"

void new_vector_segment(void);

/*:27*//*36:*/
#line 534 "lossless.w"

cell vector_new(int,cell);
cell vector_new_imp(int,boolean,cell);
cell vector_new_list(cell,int);
cell vector_sub(cell,int,int,int,int,cell);

/*:36*//*43:*/
#line 641 "lossless.w"

int gc(void);
int gc_vectors(void);
void mark(cell);
int sweep(void);

/*:43*//*51:*/
#line 857 "lossless.w"

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
#line 1056 "lossless.w"

cell symbol(char*,boolean);
void symbol_expand(void);
void symbol_reify(cell);
boolean symbol_same_p(cell,cell);
cell symbol_steal(char*);

/*:59*//*70:*/
#line 1191 "lossless.w"

cell int_new_imp(int,cell);
cell int_new(int);

/*:70*//*73:*/
#line 1224 "lossless.w"

int list_length(cell);
predicate list_p(cell,predicate,cell*);
cell list_reverse_m(cell,boolean);

/*:73*//*81:*/
#line 1382 "lossless.w"

cell env_here(cell,cell);
cell env_lift_stack(cell,cell);
cell env_search(cell,cell);
void env_set(cell,cell,cell,boolean);

/*:81*//*88:*/
#line 1540 "lossless.w"

cell closure_new_imp(char,cell,cell,cell,cell);

/*:88*//*97:*/
#line 1687 "lossless.w"

void vm_init_imp(void);
void vm_prepare_imp(void);
void vm_reset(void);

/*:97*//*104:*/
#line 1765 "lossless.w"

void frame_consume(void);
void frame_enter(cell,cell,cell);
void frame_leave(void);
void frame_push(int);

/*:104*//*109:*/
#line 1840 "lossless.w"

void interpret(void);

/*:109*//*115:*/
#line 1941 "lossless.w"

int read_byte(void);
cell read_cstring(char*);
cell read_form(void);
cell read_list(cell);
cell read_number(void);
cell read_sexp(void);
cell read_special(void);
cell read_symbol(void);
void unread_byte(char);
int useful_byte(void);

/*:115*//*137:*/
#line 2459 "lossless.w"

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

/*:137*//*169:*/
#line 3187 "lossless.w"

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

/*:169*//*208:*/
#line 4124 "lossless.w"

void compile_quasicompiler(cell,cell,cell,int,boolean);

/*:208*//*230:*/
#line 4417 "lossless.w"

llt_buffer*llt_alloc_imp(size_t,size_t);
llt_buffer*llt_cat(const char*,...);
llt_buffer*llt_grow_imp(llt_buffer*,size_t);

/*:230*//*235:*/
#line 4481 "lossless.w"

llt_buffer*llt_serialise(cell,boolean);
boolean llt_compare_serial(llt_buffer*,cell,boolean);
llt_buffer*llt_copy_refs(cell);

/*:235*//*239:*/
#line 4598 "lossless.w"

#ifdef LL_TEST
void tap_plan(int);
boolean tap_ok(boolean,char*);
int test_count_free_list(void);
char*test_msgf(char*,char*,char*,...);
void test_vm_state(char*,int);
#endif

/*:239*//*246:*/
#line 4689 "lossless.w"

void compile_testing_probe(cell,cell,boolean);
void compile_testing_probe_app(cell,cell,boolean);
cell testing_build_probe(cell);

/*:246*//*489:*/
#line 8920 "lossless.w"

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

/*:489*//*519:*/
#line 9852 "lossless.w"

cell assoc_member(cell,cell);
cell assoc_content(cell,cell);
cell assoc_value(cell,cell);

/*:519*/
#line 74 "lossless.w"

/*6:*/
#line 140 "lossless.w"

volatile boolean Error_Handler= bfalse;
jmp_buf Goto_Begin;
jmp_buf Goto_Error;

/*:6*//*12:*/
#line 254 "lossless.w"

cell*CAR= NULL;
cell*CDR= NULL;
char*TAG= NULL;

cell Cells_Free= NIL;
int Cells_Poolsize= 0;
int Cells_Segment= HEAP_SEGMENT;

/*:12*//*19:*/
#line 409 "lossless.w"

cell Tmp_CAR= NIL;
cell Tmp_CDR= NIL;

/*:19*//*25:*/
#line 459 "lossless.w"

cell*VECTOR= NULL;
int Vectors_Free= 0;
int Vectors_Poolsize= 0;
int Vectors_Segment= HEAP_SEGMENT;

/*:25*//*30:*/
#line 515 "lossless.w"

cell Zero_Vector= NIL;

/*:30*//*47:*/
#line 838 "lossless.w"

cell CTS= NIL;
cell RTS= NIL;
cell VMS= NIL;
int RTS_Size= 0;
int RTSp= -1;

/*:47*//*56:*/
#line 1042 "lossless.w"

cell Symbol_Table= NIL;
char*SYMBOL= NULL;
int Symbol_Free= 0;
int Symbol_Poolsize= 0;

/*:56*//*66:*/
#line 1168 "lossless.w"

cell Small_Int[UCHAR_MAX+1];

/*:66*//*78:*/
#line 1360 "lossless.w"

cell Sym_ERR_BOUND= NIL;
cell Sym_ERR_UNBOUND= NIL;

/*:78*//*91:*/
#line 1578 "lossless.w"



primitive COMPILER[]= {
/*517:*/
#line 9792 "lossless.w"


{"error",compile_error},
{"eval",compile_eval},
{"if",compile_conditional},
{"lambda",compile_lambda},
{"vov",compile_vov},
{"quote",compile_quote},
{"quasiquote",compile_quasiquote},

{"car",compile_car},
{"cdr",compile_cdr},
{"cons",compile_cons},
{"null?",compile_null_p},
{"pair?",compile_pair_p},
{"set-car!",compile_set_car_m},
{"set-cdr!",compile_set_cdr_m},

{"current-environment",compile_env_current},
{"root-environment",compile_env_root},
{"set!",compile_set_m},
{"define!",compile_define_m},
#ifdef LL_TEST
/*250:*/
#line 4706 "lossless.w"

{"test!probe",compile_testing_probe},
{"test!probe-applying",compile_testing_probe_app},

/*:250*/
#line 9815 "lossless.w"

#endif

/*:517*//*523:*/
#line 9899 "lossless.w"

{"symbol?",compile_symbol_p},

/*:523*/
#line 1582 "lossless.w"

{NULL,NULL}};

/*:91*//*93:*/
#line 1626 "lossless.w"

boolean Interrupt= 0;
boolean Running= 0;
cell Acc= NIL;
cell Env= NIL;
cell Prog= NIL;
cell Prog_Main= NIL;
cell Root= NIL;
int Ip= 0;

/*:93*//*101:*/
#line 1752 "lossless.w"

int Fp= -1;

/*:101*//*112:*/
#line 1916 "lossless.w"

char Putback[2]= {'\0','\0'};
int Read_Level= 0;
char*Read_Pointer= NULL;
cell Sym_ERR_UNEXPECTED= NIL;
cell Sym_SYNTAX_DOTTED= NIL;
cell Sym_SYNTAX_QUASI= NIL;
cell Sym_SYNTAX_QUOTE= NIL;
cell Sym_SYNTAX_UNQUOTE= NIL;
cell Sym_SYNTAX_UNSPLICE= NIL;

/*:112*//*150:*/
#line 2845 "lossless.w"

opcode OP[OPCODE_MAX]= {
[OP_APPLY]= {.name= "OP_APPLY",.nargs= 1},
[OP_APPLY_TAIL]= {.name= "OP_APPLY_TAIL",.nargs= 1},
[OP_CAR]= {.name= "OP_CAR",.nargs= 0},
[OP_CDR]= {.name= "OP_CDR",.nargs= 0},
[OP_COMPILE]= {.name= "OP_COMPILE",.nargs= 0},
[OP_CONS]= {.name= "OP_CONS",.nargs= 0},
[OP_CYCLE]= {.name= "OP_CYCLE",.nargs= 0},
[OP_ENVIRONMENT_P]= {.name= "OP_ENVIRONMENT_P",.nargs= 0},
[OP_ENV_MUTATE_M]= {.name= "OP_ENV_MUTATE_M",.nargs= 2},
[OP_ENV_QUOTE]= {.name= "OP_ENV_QUOTE",.nargs= 0},
[OP_ENV_ROOT]= {.name= "OP_ENV_ROOT",.nargs= 0},
[OP_ENV_SET_ROOT_M]= {.name= "OP_ENV_SET_ROOT_M",.nargs= 0},
[OP_ERROR]= {.name= "OP_ERROR",.nargs= 0},
[OP_HALT]= {.name= "OP_HALT",.nargs= 0},
[OP_JUMP]= {.name= "OP_JUMP",.nargs= 1},
[OP_JUMP_FALSE]= {.name= "OP_JUMP_FALSE",.nargs= 1},
[OP_JUMP_TRUE]= {.name= "OP_JUMP_TRUE",.nargs= 1},
[OP_LAMBDA]= {.name= "OP_LAMBDA",.nargs= 1},
[OP_LIST_P]= {.name= "OP_LIST_P",.nargs= 2},
[OP_LIST_REVERSE]= {.name= "OP_LIST_REVERSE",.nargs= 2},
[OP_LIST_REVERSE_M]= {.name= "OP_LIST_REVERSE_M",.nargs= 0},
[OP_LOOKUP]= {.name= "OP_LOOKUP",.nargs= 0},
[OP_NIL]= {.name= "OP_NIL",.nargs= 0},
[OP_NOOP]= {.name= "OP_NOOP",.nargs= 0},
[OP_NULL_P]= {.name= "OP_NULL_P",.nargs= 0},
[OP_PAIR_P]= {.name= "OP_PAIR_P",.nargs= 0},
[OP_PEEK]= {.name= "OP_PEEK",.nargs= 0},
[OP_POP]= {.name= "OP_POP",.nargs= 0},
[OP_PUSH]= {.name= "OP_PUSH",.nargs= 0},
[OP_QUOTE]= {.name= "OP_QUOTE",.nargs= 1},
[OP_RETURN]= {.name= "OP_RETURN",.nargs= 0},
[OP_RUN]= {.name= "OP_RUN",.nargs= 0},
[OP_RUN_THERE]= {.name= "OP_RUN_THERE",.nargs= 0},
[OP_SET_CAR_M]= {.name= "OP_SET_CAR_M",.nargs= 0},
[OP_SET_CDR_M]= {.name= "OP_SET_CDR_M",.nargs= 0},
[OP_SNOC]= {.name= "OP_SNOC",.nargs= 0},
[OP_SWAP]= {.name= "OP_SWAP",.nargs= 0},
[OP_SYMBOL_P]= {.name= "OP_SYMBOL_P",.nargs= 0},
[OP_SYNTAX]= {.name= "OP_SYNTAX",.nargs= 1},
[OP_VOV]= {.name= "OP_VOV",.nargs= 1},
#ifdef LL_TEST
/*248:*/
#line 4697 "lossless.w"

[OP_TEST_PROBE]= {.name= "OP_VOV",.nargs= 1},

/*:248*/
#line 2888 "lossless.w"

#endif
};

/*:150*//*167:*/
#line 3179 "lossless.w"

int Here= 0;
cell Compilation= NIL;

/*:167*//*182:*/
#line 3390 "lossless.w"

cell Sym_ERR_ARITY_EXTRA= NIL;
cell Sym_ERR_ARITY_MISSING= NIL;
cell Sym_ERR_ARITY_SYNTAX= NIL;

/*:182*//*196:*/
#line 3691 "lossless.w"

cell Sym_vov_args= UNDEFINED;
cell Sym_vov_args_long= UNDEFINED;
cell Sym_vov_cont= UNDEFINED;
cell Sym_vov_cont_long= UNDEFINED;
cell Sym_vov_env= UNDEFINED;
cell Sym_vov_env_long= UNDEFINED;

/*:196*//*222:*/
#line 4346 "lossless.w"

#ifdef LL_TEST
int Allocate_Success= -1;
#endif

/*:222*//*225:*/
#line 4374 "lossless.w"

cell Tmp_Test= NIL;

/*:225*//*240:*/
#line 4607 "lossless.w"

boolean Test_Passing= btrue;
int Test_Plan= -1;
int Next_Test= 1;

/*:240*/
#line 75 "lossless.w"


/*:2*//*9:*/
#line 163 "lossless.w"

void
error_imp(char*message,
cell id,
cell detail)
{
int len;
char wbuf[BUFFER_SEGMENT]= {0};

if(!null_p(id)){
message= symbol_store(id);
len= symbol_length(id);
}else
len= strlen(message);
if(Error_Handler){

vms_push(detail);
if(null_p(id))
id= sym(message);
Acc= atom(id,detail,FORMAT_EXCEPTION);
vms_clear();
longjmp(Goto_Error,1);
}
write_form(detail,wbuf,BUFFER_SEGMENT,0);
printf("UNHANDLED ERROR: ");
for(;len--;message++)
putchar(*message);
printf(": %s\n",wbuf);
longjmp(Goto_Begin,1);
}

/*:9*//*11:*/
#line 207 "lossless.w"

void
warn(char*message,
cell detail)
{
char wbuf[BUFFER_SEGMENT]= {0};
write_form(detail,wbuf,BUFFER_SEGMENT,0);
printf("WARNING: %s: %s\n",message,wbuf);
}

/*:11*//*16:*/
#line 296 "lossless.w"

void
new_cells_segment(void)
{
enlarge_pool(CAR,Cells_Poolsize+Cells_Segment,cell);
enlarge_pool(CDR,Cells_Poolsize+Cells_Segment,cell);
enlarge_pool(TAG,Cells_Poolsize+Cells_Segment,char);

bzero(CAR+Cells_Poolsize,Cells_Segment*sizeof(cell));
bzero(CDR+Cells_Poolsize,Cells_Segment*sizeof(cell));
bzero(TAG+Cells_Poolsize,Cells_Segment*sizeof(char));

Cells_Poolsize+= Cells_Segment;
Cells_Segment= Cells_Poolsize/2;
}

/*:16*//*17:*/
#line 370 "lossless.w"


/*:17*//*18:*/
#line 401 "lossless.w"


/*:18*//*24:*/
#line 426 "lossless.w"

cell
atom(cell ncar,
cell ncdr,
char ntag)
{
cell r;
if(null_p(Cells_Free)){
if(ntag&TAG_ACARP)
Tmp_CAR= ncar;
if(ntag&TAG_ACDRP)
Tmp_CDR= ncdr;
if(gc()<=(Cells_Poolsize/2)){
new_cells_segment();
gc();
}
Tmp_CAR= Tmp_CDR= NIL;
}
r= Cells_Free;
Cells_Free= cdr(Cells_Free);
car(r)= ncar;
cdr(r)= ncdr;
tag(r)= ntag;
return r;
}

/*:24*//*29:*/
#line 478 "lossless.w"

void
new_vector_segment(void)
{
cell*new_vector;
new_vector= LL_ALLOCATE(VECTOR,Vectors_Poolsize+Vectors_Segment,
sizeof(cell));
ERR_OOM_P(new_vector);
bzero(new_vector+Vectors_Poolsize,Vectors_Segment*sizeof(cell));
VECTOR= new_vector;
Vectors_Poolsize+= Vectors_Segment;
Vectors_Segment= Vectors_Poolsize/2;
}

/*:29*//*37:*/
#line 540 "lossless.w"

cell
vector_new_imp(int size,
boolean fill_p,
cell fill)
{
int wsize,off,i;
cell r;
wsize= vector_realsize(size);
if(Vectors_Free+wsize>=Vectors_Poolsize){
gc_vectors();
while(Vectors_Free+wsize
>=(Vectors_Poolsize-(Vectors_Poolsize/2)))
new_vector_segment();
}
r= atom(NIL,NIL,FORMAT_VECTOR);
off= Vectors_Free;
Vectors_Free+= wsize;
vector_offset(r)= off+VECTOR_HEAD;
vector_length(r)= size;
vector_cell(r)= r;
vector_index(r)= 0;
if(fill_p)
for(i= 0;i<=size;i++)
vector_ref(r,i)= fill;
return r;
}

/*:37*//*38:*/
#line 568 "lossless.w"

cell
vector_new(int size,
cell fill)
{
if(size==0)
return Zero_Vector;
return vector_new_imp(size,btrue,fill);
}

/*:38*//*39:*/
#line 580 "lossless.w"

cell
vector_new_list(cell list,
int len)
{
cell r;
int i;
r= vector_new(len,0);
for(i= 0;i<len;i++){
vector_ref(r,i)= car(list);
list= cdr(list);
}
return r;
}

/*:39*//*40:*/
#line 599 "lossless.w"

cell
vector_sub(cell src,
int srcfrom,
int srcto,
int dstfrom,
int dstto,
cell fill)
{
cell dst;
int copy,i;
copy= srcto-srcfrom;
if(dstto<0)
dstto= dstfrom+copy;
dst= vector_new_imp(dstto,0,0);
for(i= 0;i<dstfrom;i++)
vector_ref(dst,i)= fill;
for(i= srcfrom;i<srcto;i++)
vector_ref(dst,(dstfrom-srcfrom)+i)= vector_ref(src,i);
for(i= dstfrom+copy;i<dstto;i++)
vector_ref(dst,i)= fill;
return dst;
}

/*:40*//*41:*/
#line 635 "lossless.w"

cell*ROOTS[]= {/*21:*/
#line 416 "lossless.w"

&Tmp_CAR,&Tmp_CDR,

/*:21*//*32:*/
#line 521 "lossless.w"

&Zero_Vector,

/*:32*//*49:*/
#line 849 "lossless.w"

&CTS,&RTS,&VMS,

/*:49*//*58:*/
#line 1053 "lossless.w"

&Symbol_Table,

/*:58*//*95:*/
#line 1641 "lossless.w"

&Acc,&Env,&Prog,&Prog_Main,&Root,

/*:95*//*170:*/
#line 3217 "lossless.w"

&Compilation,

/*:170*//*227:*/
#line 4380 "lossless.w"

#ifdef LL_TEST
&Tmp_Test,
#endif

/*:227*/
#line 636 "lossless.w"
NULL};

/*:41*//*44:*/
#line 647 "lossless.w"

void
mark(cell next)
{
cell parent,prev;
int i;
parent= prev= NIL;
while(1){
if(!(special_p(next)||mark_p(next))){
if(vector_p(next)){
mark_set(next);
vector_cell(next)= next;
if(vector_length(next)> 0){
state_set(next);
vector_index(next)= 0;
prev= vector_ref(next,0);
vector_ref(next,0)= parent;
parent= next;
next= prev;
}
}else if(!acar_p(next)
&&acdr_p(next)){
prev= cdr(next);
cdr(next)= parent;
parent= next;
next= prev;
mark_set(parent);
}else if(acar_p(next)){
prev= car(next);
car(next)= parent;
mark_set(next);
parent= next;
next= prev;
state_set(parent);
}else{
mark_set(next);
}
}else{
if(null_p(parent))
break;
if(vector_p(parent)){
i= vector_index(parent);
if((i+1)<vector_length(parent)){
prev= vector_ref(parent,i+1);
vector_ref(parent,i+1)= vector_ref(parent,i);
vector_ref(parent,i)= next;
next= prev;
vector_index(parent)= i+1;
}else{
state_clear(parent);
prev= parent;
parent= vector_ref(prev,i);
vector_ref(prev,i)= next;
next= prev;
}
}else if(state_p(parent)){
prev= cdr(parent);
cdr(parent)= car(parent);
car(parent)= next;
state_clear(parent);
next= prev;
}else if(acdr_p(parent)){
prev= parent;
parent= cdr(prev);
cdr(prev)= next;
next= prev;
}else{
error(ERR_UNIMPLEMENTED,NIL);
}
}
}
}

int
sweep(void)
{
int count,i;
Cells_Free= NIL;
count= 0;
for(i= 0;i<Cells_Poolsize;i++){
if(!mark_p(i)){
tag(i)= TAG_NONE;
cdr(i)= Cells_Free;
Cells_Free= i;
count++;
}else{
mark_clear(i);
}
}
return count;
}

int
gc(void)
{
int sk,i;
if(!null_p(RTS)){
sk= vector_length(RTS);
vector_length(RTS)= RTSp+1;
}
for(i= 0;ROOTS[i];i++)
mark(*ROOTS[i]);
for(i= SCHAR_MIN;i<=SCHAR_MAX;i++)
mark(Small_Int[(unsigned char)i]);
if(!null_p(RTS))
vector_length(RTS)= sk;
return sweep();
}

/*:44*//*45:*/
#line 761 "lossless.w"

int
gc_vectors(void)
{
int to,from,d,i,r;
/*46:*/
#line 791 "lossless.w"

i= 0;
while(i<Vectors_Free){
VECTOR[i+VECTOR_CELL]= NIL;
i+= vector_realsize(VECTOR[i+VECTOR_SIZE]);
}

/*:46*/
#line 766 "lossless.w"

gc();
from= to= 0;
while(from<Vectors_Free){
d= vector_realsize(VECTOR[from+VECTOR_SIZE]);
if(!null_p(VECTOR[from+VECTOR_CELL])){
if(to!=from){
for(i= 0;i<d;i++)
VECTOR[to+i]= VECTOR[from+i];
vector_offset(VECTOR[to+VECTOR_CELL])
= to+VECTOR_HEAD;
}
to+= d;
}
from+= d;
}
r= Vectors_Free-to;
Vectors_Free= to;
return r;
}

/*:45*//*52:*/
#line 877 "lossless.w"

cell
vms_pop(void)
{
cell r;
CHECK_UNDERFLOW(VMS);
r= car(VMS);
VMS= cdr(VMS);
return r;
}

void
vms_push(cell item)
{
VMS= cons(item,VMS);
}

cell
vms_ref(void)
{
CHECK_UNDERFLOW(VMS);
return car(VMS);
}

void
vms_set(cell item)
{
CHECK_UNDERFLOW(VMS);
car(VMS)= item;
}

/*:52*//*53:*/
#line 914 "lossless.w"

cell
cts_pop()
{
cell r;
CHECK_UNDERFLOW(CTS);
r= car(CTS);
CTS= cdr(CTS);
return r;
}

void
cts_push(cell item)
{
CTS= cons(item,CTS);
}

cell
cts_ref(void)
{
CHECK_UNDERFLOW(CTS);
return car(CTS);
}

void
cts_set(cell item)
{
CHECK_UNDERFLOW(CTS);
car(CTS)= item;
}

/*:53*//*54:*/
#line 950 "lossless.w"

void
rts_prepare(int need)
{
int b,s;
if(RTSp+need>=RTS_Size){
b= RTS_SEGMENT*((need+RTS_SEGMENT)/RTS_SEGMENT);
s= RTS_Size+b;
RTS= vector_sub(RTS,0,RTS_Size,0,s,UNDEFINED);
RTS_Size= s;
}
}

/*:54*//*55:*/
#line 968 "lossless.w"

cell
rts_pop(int count)
{
RTS_UNDERFLOW(RTSp-count);
RTSp-= count;
return vector_ref(RTS,RTSp+1);
}

void
rts_push(cell o)
{
vms_push(o);
rts_prepare(1);
vector_ref(RTS,++RTSp)= vms_pop();
}

cell
rts_ref(int d)
{
RTS_UNDERFLOW(RTSp-d);
RTS_OVERFLOW(RTSp-d);
return vector_ref(RTS,RTSp-d);
}

cell
rts_ref_abs(int d)
{
RTS_UNDERFLOW(d);
RTS_OVERFLOW(d);
return vector_ref(RTS,d);
}

void
rts_set(int d,
cell v)
{
RTS_UNDERFLOW(RTSp-d);
RTS_OVERFLOW(RTSp-d);
vector_ref(RTS,RTSp-d)= v;
}

void
rts_set_abs(int d,
cell v)
{
RTS_UNDERFLOW(d);
RTS_OVERFLOW(d);
vector_ref(RTS,d)= v;
}

/*:55*//*61:*/
#line 1069 "lossless.w"

void
symbol_expand(void)
{
char*new;
new= realloc(SYMBOL,Symbol_Poolsize+HEAP_SEGMENT);
ERR_OOM_P(new);
Symbol_Poolsize+= HEAP_SEGMENT;
SYMBOL= new;
}

/*:61*//*62:*/
#line 1086 "lossless.w"

cell
symbol_steal(char*cstr)
{
cell r;
int len;
len= strlen(cstr);
while(Symbol_Free+len> Symbol_Poolsize)
symbol_expand();
r= atom(len,Symbol_Free,FORMAT_SYMBOL);
memcpy(SYMBOL+Symbol_Free,cstr,len);

return r;
}

/*:62*//*63:*/
#line 1104 "lossless.w"

boolean
symbol_same_p(cell maybe,
cell match)
{
char*pmaybe,*pmatch;
int i,len;
len= symbol_length(match);
if(symbol_length(maybe)!=len)
return bfalse;
pmaybe= symbol_store(maybe);
pmatch= symbol_store(match);
if(maybe==match)
return btrue;
for(i= 0;i<len;i++){
if(pmaybe[i]!=pmatch[i])
return bfalse;
}
return btrue;
}

/*:63*//*64:*/
#line 1125 "lossless.w"

void
symbol_reify(cell s)
{
Symbol_Free+= symbol_length(s);
Symbol_Table= cons(s,Symbol_Table);
}

/*:64*//*65:*/
#line 1133 "lossless.w"

cell
symbol(char*cstr,
boolean permanent_p)
{
cell st,s;
s= symbol_steal(cstr);
st= Symbol_Table;
while(!null_p(st)){
if(symbol_same_p(s,car(st)))
return car(st);
st= cdr(st);
}
if(permanent_p)
symbol_reify(s);
return s;
}

/*:65*//*71:*/
#line 1195 "lossless.w"

cell
int_new_imp(int value,
cell next)
{
if(!null_p(next))
error(ERR_UNIMPLEMENTED,NIL);
return atom((cell)value,next,FORMAT_INTEGER);
}

/*:71*//*72:*/
#line 1205 "lossless.w"

cell
int_new(int value)
{
if(value>=SCHAR_MIN&&value<=SCHAR_MAX)
return Small_Int[(unsigned char)value];
return int_new_imp(value,NIL);
}

/*:72*//*74:*/
#line 1229 "lossless.w"

int
list_length(cell l)
{
int c= 0;
if(null_p(l))
return 0;
for(;pair_p(l);l= cdr(l))
c++;
if(!null_p(l))
c= -(c+1);
return c;
}

/*:74*//*75:*/
#line 1247 "lossless.w"

predicate
list_p(cell o,
predicate improper_p,
cell*sum)
{
int c= 0;
if(null_p(o)){
if(sum!=NULL)
*sum= int_new(0);
return TRUE;
}
while(pair_p(o)){
o= cdr(o);
c++;
}
if(sum!=NULL)
*sum= int_new(c);
if(null_p(o))
return TRUE;
if(sum!=NULL)
*sum= int_new(-(c+1));
return improper_p;
}

/*:75*//*76:*/
#line 1275 "lossless.w"

cell
list_reverse(cell l,
cell*improper,
cell*sum)
{
cell saved,r;
int c;
saved= l;
c= 0;
vms_push(NIL);
while(!null_p(l)){
if(!pair_p(l)){
r= vms_pop();
if(improper!=NULL){
*improper= l;
if(sum!=NULL)
*sum= c;
return r;
}else
error(ERR_IMPROPER_LIST,saved);
}
vms_set(cons(car(l),vms_ref()));
l= cdr(l);
c++;
}
if(sum!=NULL)
*sum= int_new(c);
return vms_pop();
}

/*:76*//*77:*/
#line 1311 "lossless.w"

cell
list_reverse_m(cell l,
boolean error_p)
{
cell m,t,saved;
saved= l;
m= NIL;
while(!null_p(l)){
if(!pair_p(l)){
if(!error_p)
return FALSE;
error(ERR_IMPROPER_LIST,saved);
}
t= cdr(l);
cdr(l)= m;
m= l;
l= t;
}
return m;
}

/*:77*//*82:*/
#line 1388 "lossless.w"

cell
env_search(cell haystack,
cell needle)
{
cell n;
for(;!null_p(haystack);haystack= env_parent(haystack))
for(n= env_layer(haystack);!null_p(n);n= cdr(n))
if(caar(n)==needle)
return cadar(n);
return UNDEFINED;
}

/*:82*//*83:*/
#line 1401 "lossless.w"

cell
env_here(cell haystack,
cell needle)
{
cell n;
for(n= env_layer(haystack);!null_p(n);n= cdr(n))
if(caar(n)==needle)
return cadar(n);
return UNDEFINED;
}

/*:83*//*84:*/
#line 1422 "lossless.w"

void
env_set(cell e,
cell name,
cell value,
boolean new_p)
{
cell ass,t;
ass= cons(name,cons(value,NIL));
vms_push(ass);
if(new_p){/*86:*/
#line 1464 "lossless.w"

if(!undefined_p(env_here(e,name)))
env_set_fail(ERR_BOUND);
env_layer(e)= cons(ass,env_layer(e));
vms_clear();
return;

/*:86*/
#line 1432 "lossless.w"
}
else{/*85:*/
#line 1442 "lossless.w"

if(null_p(env_layer(e)))
env_set_fail(ERR_UNBOUND);
if(caar(env_layer(e))==name){
env_layer(e)= cons(ass,cdr(env_layer(e)));
vms_clear();
return;
}
for(t= env_layer(e);!null_p(cdr(t));t= cdr(t)){
if(caadr(t)==name){
cdr(t)= cddr(t);
env_layer(e)= cons(ass,env_layer(e));
vms_clear();
return;
}
}
env_set_fail(ERR_UNBOUND);

/*:85*/
#line 1433 "lossless.w"
}
}

/*:84*//*87:*/
#line 1474 "lossless.w"

cell
env_lift_stack(cell e,
cell formals)
{
cell ass,name,p,r;
vms_push(p= NIL);
while(!null_p(formals)){
if(pair_p(formals)){
name= car(formals);
formals= cdr(formals);
}else{
name= formals;
formals= NIL;
}
ass= rts_pop(1);
if(symbol_p(name)){
ass= cons(ass,NIL);
ass= cons(name,ass);
p= cons(ass,p);
vms_set(p);
}
}
r= env_extend(e);
env_layer(r)= p;
vms_clear();
return r;
}

/*:87*//*89:*/
#line 1543 "lossless.w"

cell
closure_new_imp(char ntag,
cell formals,
cell env,
cell prog,
cell ip)
{
cell r;
r= cons(int_new(ip),NIL);
r= cons(prog,r);
r= cons(env,r);
return atom(formals,r,ntag);
}

/*:89*//*98:*/
#line 1692 "lossless.w"

void
vm_init_imp(void)
{
cell t;
int i;
primitive*n;
/*15:*/
#line 271 "lossless.w"

free(CAR);
free(CDR);
free(TAG);
CAR= CDR= NULL;
TAG= NULL;
Cells_Free= NIL;
Cells_Poolsize= 0;
Cells_Segment= HEAP_SEGMENT;

/*:15*//*23:*/
#line 422 "lossless.w"

Tmp_CAR= Tmp_CDR= NIL;

/*:23*//*28:*/
#line 472 "lossless.w"

free(VECTOR);
VECTOR= NULL;
Vectors_Free= Vectors_Poolsize= 0;
Vectors_Segment= HEAP_SEGMENT;

/*:28*//*34:*/
#line 527 "lossless.w"

Zero_Vector= NIL;

/*:34*//*50:*/
#line 852 "lossless.w"

CTS= RTS= VMS= NIL;
RTS_Size= 0;
RTSp= -1;

/*:50*//*60:*/
#line 1063 "lossless.w"

free(SYMBOL);
SYMBOL= NULL;
Symbol_Poolsize= Symbol_Free= 0;
Symbol_Table= NIL;

/*:60*//*68:*/
#line 1180 "lossless.w"

for(i= 0;i<256;i++)
Small_Int[i]= NIL;

/*:68*//*96:*/
#line 1644 "lossless.w"

Acc= Env= Prog= Prog_Main= Root= NIL;
Interrupt= Running= Ip= 0;

/*:96*//*171:*/
#line 3220 "lossless.w"

Compilation= NIL;

/*:171*//*228:*/
#line 4385 "lossless.w"

#ifdef LL_TEST
Tmp_Test= NIL;
#endif

/*:228*/
#line 1699 "lossless.w"

/*3:*/
#line 77 "lossless.w"



/*:3*//*33:*/
#line 524 "lossless.w"

Zero_Vector= vector_new_imp(0,0,0);

/*:33*//*69:*/
#line 1184 "lossless.w"

for(i= SCHAR_MIN;i<=SCHAR_MAX;i++)
Small_Int[(unsigned char)i]= int_new_imp(i,NIL);

/*:69*//*80:*/
#line 1367 "lossless.w"

Sym_ERR_BOUND= sym(ERR_BOUND);
Sym_ERR_UNBOUND= sym(ERR_UNBOUND);

/*:80*//*103:*/
#line 1758 "lossless.w"

Fp= -1;

/*:103*//*114:*/
#line 1933 "lossless.w"

Sym_ERR_UNEXPECTED= sym(ERR_UNEXPECTED);
Sym_SYNTAX_DOTTED= sym(SYNTAX_DOTTED);
Sym_SYNTAX_QUASI= sym(SYNTAX_QUASI);
Sym_SYNTAX_QUOTE= sym(SYNTAX_QUOTE);
Sym_SYNTAX_UNQUOTE= sym(SYNTAX_UNQUOTE);
Sym_SYNTAX_UNSPLICE= sym(SYNTAX_UNSPLICE);

/*:114*//*184:*/
#line 3398 "lossless.w"

Sym_ERR_ARITY_EXTRA= sym(ERR_ARITY_EXTRA);
Sym_ERR_ARITY_MISSING= sym(ERR_ARITY_MISSING);
Sym_ERR_ARITY_SYNTAX= sym(ERR_ARITY_SYNTAX);

/*:184*//*197:*/
#line 3699 "lossless.w"

Sym_vov_args= sym("vov/args");
Sym_vov_args_long= sym("vov/arguments");
Sym_vov_cont= sym("vov/cont");
Sym_vov_cont_long= sym("vov/continuation");
Sym_vov_env= sym("vov/env");
Sym_vov_env_long= sym("vov/environment");

/*:197*/
#line 1700 "lossless.w"

Prog_Main= compile_main();
i= 0;
Root= atom(NIL,NIL,FORMAT_ENVIRONMENT);
for(n= COMPILER+i;n->fn!=NULL;n= COMPILER+(++i)){
t= atom(i,NIL,FORMAT_COMPILER);
t= cons(t,NIL);
t= cons(sym(n->name),t);
env_layer(Root)= cons(t,env_layer(Root));
}
Env= Root;
}

/*:98*//*99:*/
#line 1713 "lossless.w"

void
vm_prepare_imp(void)
{
Acc= Prog= NIL;
Env= Root;
rts_reset();
}

/*:99*//*100:*/
#line 1722 "lossless.w"

void
vm_reset(void)
{
Prog= Prog_Main;
Running= Interrupt= Ip= 0;
}

/*:100*//*105:*/
#line 1771 "lossless.w"

void
frame_push(int ipdelta)
{
rts_push(int_new(Ip+ipdelta));
rts_push(Prog);
rts_push(Env);
rts_push(int_new(Fp));
}

/*:105*//*106:*/
#line 1781 "lossless.w"

void
frame_enter(cell e,
cell p,
cell i)
{
Env= e;
Prog= p;
Ip= i;
Fp= RTSp-FRAME_HEAD;
}

/*:106*//*107:*/
#line 1799 "lossless.w"

void
frame_leave(void)
{
int prev;
Ip= int_value(frame_ip(Fp));
Prog= frame_prog(Fp);
Env= frame_env(Fp);
prev= int_value(frame_fp(Fp));
rts_clear(FRAME_HEAD);
Fp= prev;
}

/*:107*//*108:*/
#line 1817 "lossless.w"

void
frame_consume(void)
{
int src,dst,i;
src= Fp;
dst= int_value(frame_fp(src));

frame_set_prog(src,frame_prog(dst));
frame_set_ip(src,frame_ip(dst));
frame_set_fp(src,frame_fp(dst));

for(i= 1;i<=FRAME_HEAD;i++)
rts_set_abs(dst+i,rts_ref_abs(src+i));
rts_clear(src-dst);
Fp-= src-dst;
}

/*:108*//*110:*/
#line 1845 "lossless.w"

void
interpret(void)
{
int ins;
cell tmp;
vm_runtime();
Running= 1;
while(Running&&!Interrupt){
ins= int_value(vector_ref(Prog,Ip));
switch(ins){
/*10:*/
#line 199 "lossless.w"

case OP_ERROR:
error_imp(NULL,Acc,rts_pop(1));
break;

/*:10*//*152:*/
#line 2895 "lossless.w"

case OP_HALT:
Running= 0;
break;
case OP_JUMP:
Ip= int_value(fetch(1));
break;
case OP_JUMP_FALSE:
if(void_p(Acc))
error(ERR_UNEXPECTED,VOID);
else if(false_p(Acc))
Ip= int_value(fetch(1));
else
skip(2);
break;
case OP_JUMP_TRUE:
if(void_p(Acc))
error(ERR_UNEXPECTED,VOID);
else if(true_p(Acc))
Ip= int_value(fetch(1));
else
skip(2);
break;
case OP_NOOP:
skip(1);
break;

/*:152*//*153:*/
#line 2925 "lossless.w"

case OP_QUOTE:
Acc= fetch(1);
skip(2);
break;

/*:153*//*154:*/
#line 2934 "lossless.w"

case OP_CAR:
Acc= car(Acc);
skip(1);
break;
case OP_CDR:
Acc= cdr(Acc);
skip(1);
break;
case OP_NULL_P:
Acc= null_p(Acc)?TRUE:FALSE;
skip(1);
break;
case OP_PAIR_P:
Acc= pair_p(Acc)?TRUE:FALSE;
skip(1);
break;

/*:154*//*155:*/
#line 2955 "lossless.w"

case OP_CONS:
Acc= cons(Acc,rts_pop(1));
skip(1);
break;
case OP_SNOC:
rts_push(cdr(Acc));
Acc= car(Acc);
skip(1);
break;

/*:155*//*156:*/
#line 2967 "lossless.w"

case OP_SET_CAR_M:
car(rts_pop(1))= Acc;
Acc= VOID;
skip(1);
break;
case OP_SET_CDR_M:
cdr(rts_pop(1))= Acc;
Acc= VOID;
skip(1);
break;

/*:156*//*157:*/
#line 2981 "lossless.w"

case OP_LIST_P:
if(!false_p(fetch(2)))
error(ERR_UNIMPLEMENTED,NIL);
Acc= list_p(Acc,fetch(1),NULL);
skip(3);
break;
case OP_LIST_REVERSE:
if(!true_p(fetch(1))||!false_p(fetch(2)))
error(ERR_UNIMPLEMENTED,NIL);
Acc= list_reverse(Acc,NULL,NULL);
skip(3);
break;
case OP_LIST_REVERSE_M:
Acc= list_reverse_m(Acc,btrue);
skip(1);
break;
case OP_SYNTAX:
Acc= atom(fetch(1),Acc,FORMAT_SYNTAX);
skip(2);
break;

/*:157*//*158:*/
#line 3015 "lossless.w"

case OP_CYCLE:
tmp= rts_ref(0);
rts_set(0,rts_ref(1));
rts_set(1,tmp);
skip(1);
break;
case OP_PEEK:
Acc= rts_ref(0);
skip(1);
break;
case OP_POP:
Acc= rts_pop(1);
skip(1);
break;
case OP_PUSH:
rts_push(Acc);
skip(1);
break;
case OP_SWAP:
tmp= Acc;
Acc= rts_ref(0);
rts_set(0,tmp);
skip(1);
break;
case OP_NIL:
rts_push(NIL);
skip(1);
break;

/*:158*//*159:*/
#line 3048 "lossless.w"

case OP_ENVIRONMENT_P:
Acc= environment_p(Acc)?TRUE:FALSE;
skip(1);
break;
case OP_ENV_MUTATE_M:
env_set(rts_pop(1),fetch(1),Acc,true_p(fetch(2)));
Acc= VOID;
skip(3);
break;
case OP_ENV_QUOTE:
Acc= Env;
skip(1);
break;
case OP_ENV_ROOT:
Acc= Root;
skip(1);
break;
case OP_ENV_SET_ROOT_M:
Root= Acc;
skip(1);
break;

/*:159*//*160:*/
#line 3075 "lossless.w"

case OP_LOOKUP:
vms_push(Acc);
Acc= env_search(Env,vms_ref());
if(undefined_p(Acc)){
Acc= vms_pop();
error(ERR_UNBOUND,Acc);
}
vms_pop();
skip(1);
break;

/*:160*//*161:*/
#line 3098 "lossless.w"

case OP_APPLY:
case OP_APPLY_TAIL:
tmp= fetch(1);
vms_push(env_lift_stack(cadr(tmp),car(tmp)));
frame_push(2);
frame_enter(vms_pop(),caddr(tmp),int_value(cadddr(tmp)));
if(ins==OP_APPLY_TAIL)
frame_consume();
break;
case OP_RETURN:
frame_leave();
break;

/*:161*//*162:*/
#line 3116 "lossless.w"

case OP_LAMBDA:
Acc= applicative_new(rts_pop(1),Env,Prog,int_value(fetch(1)));
skip(2);
break;
case OP_VOV:
Acc= operative_new(rts_pop(1),Env,Prog,int_value(fetch(1)));
skip(2);
break;

/*:162*//*164:*/
#line 3130 "lossless.w"

case OP_COMPILE:
Acc= compile(Acc);
skip(1);
break;

/*:164*//*165:*/
#line 3141 "lossless.w"

case OP_RUN:
frame_push(1);
frame_enter(Env,Acc,0);
break;

/*:165*//*166:*/
#line 3151 "lossless.w"

case OP_RUN_THERE:
vms_push(rts_pop(1));
frame_push(1);
frame_enter(vms_pop(),Acc,0);
break;

/*:166*//*525:*/
#line 9913 "lossless.w"

case OP_SYMBOL_P:
Acc= symbol_p(Acc)?TRUE:FALSE;
skip(1);
break;

/*:525*/
#line 1856 "lossless.w"

#ifdef LL_TEST
/*249:*/
#line 4700 "lossless.w"

case OP_TEST_PROBE:
Acc= testing_build_probe(rts_pop(1));
skip(1);
break;

/*:249*/
#line 1858 "lossless.w"

#endif
default:
Interrupt= btrue;
}
}
if(Interrupt)
error(ERR_INTERRUPTED,NIL);
}

/*:110*//*116:*/
#line 1953 "lossless.w"

int
read_byte(void)
{
int r;
if((r= Putback[0])!='\0'){
Putback[0]= Putback[1];
Putback[1]= '\0';
return r;
}
if(Read_Pointer!=NULL){
r= *Read_Pointer;
if(r=='\0')
r= EOF;
Read_Pointer++;
return r;
}
return getchar();
}

void
unread_byte(char c)
{

Putback[1]= Putback[0];
Putback[0]= c;
}

/*:116*//*117:*/
#line 1987 "lossless.w"

cell
read_cstring(char*src)
{
cell r;
Read_Pointer= src;
r= read_form();
Read_Pointer= NULL;
return r;
}

/*:117*//*118:*/
#line 2000 "lossless.w"

int
useful_byte(void)
{
int c;
while(!Interrupt){
c= read_byte();
switch(c){
case' ':
case'\n':
case'\r':
case'\t':
continue;
case';':
c= read_byte();
while(c!='\n'&&!Interrupt){


c= read_byte();
if(c==EOF)
return c;
}
break;
default:
return c;

}
}
return EOF;
}

/*:118*//*119:*/
#line 2034 "lossless.w"

cell
read_sexp(void)
{
cts_clear();
Read_Level= 0;
Putback[0]= Putback[1]= '\0';
return read_form();
}

/*:119*//*120:*/
#line 2048 "lossless.w"

cell
read_form(void)
{
cell r;
int c,n;
if(Interrupt)
return VOID;
if(Read_Level> READER_MAX_DEPTH)
error(ERR_RECURSION,NIL);
c= useful_byte();
switch(c){/*121:*/
#line 2067 "lossless.w"

case EOF:
if(!Read_Level)
return END_OF_FILE;
else
error(ERR_ARITY_SYNTAX,NIL);

/*:121*//*123:*/
#line 2077 "lossless.w"

case'(':
return read_list(READ_CLOSE_PAREN);
case'[':
return read_list(READ_CLOSE_BRACKET);

case')':
case']':


if(!Read_Level)
error(ERR_ARITY_SYNTAX,NIL);
else
return c==')'?READ_CLOSE_PAREN:READ_CLOSE_BRACKET;

/*:123*//*124:*/
#line 2095 "lossless.w"

case'.':
if(!Read_Level)
error(ERR_ARITY_SYNTAX,NIL);
c= useful_byte();
if(c==EOF)
error(ERR_ARITY_SYNTAX,NIL);
unread_byte(c);
return READ_DOT;

/*:124*//*125:*/
#line 2107 "lossless.w"

case'#':
return read_special();

/*:125*//*126:*/
#line 2113 "lossless.w"

case'"':
case'|':
error(ERR_UNIMPLEMENTED,NIL);

/*:126*//*127:*/
#line 2132 "lossless.w"

case'\'':
case'`':
n= useful_byte();
if(n==EOF)
error(ERR_ARITY_SYNTAX,NIL);
unread_byte(n);
if(n==')'||n==']')
error(ERR_ARITY_SYNTAX,NIL);
r= sym(c=='`'?SYNTAX_QUASI:SYNTAX_QUOTE);
return atom(r,read_form(),FORMAT_SYNTAX);

case',':
c= read_byte();
if(c==EOF)
error(ERR_ARITY_SYNTAX,NIL);
if(c==')'||c==']')
error(ERR_ARITY_SYNTAX,NIL);
if(c=='@'){
r= sym(SYNTAX_UNSPLICE);
return atom(r,read_form(),FORMAT_SYNTAX);
}else{
unread_byte(c);
r= sym(SYNTAX_UNQUOTE);
return atom(r,read_form(),FORMAT_SYNTAX);
}

/*:127*//*128:*/
#line 2162 "lossless.w"

default:
if(!isprint(c))
error(ERR_ARITY_SYNTAX,NIL);
unread_byte(c);
if(isdigit(c))
return read_number();
else
return read_symbol();

/*:128*/
#line 2059 "lossless.w"
}
error(ERR_UNEXPECTED,NIL);
}

/*:120*//*129:*/
#line 2180 "lossless.w"

cell
read_list(cell delimiter)
{
cell write,next,r;
int count= 0;
Read_Level++;
write= cons(NIL,NIL);
cts_push(write);
while(1){
if(Interrupt){
cts_pop();
Read_Level--;
return VOID;
}
next= read_form();
if(special_p(next)){


/*130:*/
#line 2220 "lossless.w"

if(eof_p(next))
error(ERR_ARITY_SYNTAX,NIL);
else if(next==READ_CLOSE_BRACKET
||next==READ_CLOSE_PAREN){
if(next!=delimiter)
error(ERR_ARITY_SYNTAX,NIL);
break;
}else if(next==READ_DOT){/*131:*/
#line 2235 "lossless.w"

if(count<1||delimiter!=READ_CLOSE_PAREN)


error(ERR_ARITY_SYNTAX,NIL);
next= read_form();
if(special_p(next)&&next<=READ_SPECIAL)


error(ERR_ARITY_SYNTAX,NIL);
cdr(write)= atom(sym(SYNTAX_DOTTED),next,FORMAT_SYNTAX);
next= read_form();
if(next!=delimiter)

error(ERR_ARITY_SYNTAX,NIL);
break;

/*:131*/
#line 2228 "lossless.w"
}

/*:130*/
#line 2199 "lossless.w"

}
count++;
cdr(write)= cons(NIL,NIL);
write= cdr(write);
car(write)= next;
}
Read_Level--;
r= cdr(cts_pop());
if(delimiter==READ_CLOSE_BRACKET)
return vector_new_list(r,count);
return count?r:NIL;
}

/*:129*//*132:*/
#line 2261 "lossless.w"

cell
read_number(void)
{
char buf[12]= {0};
int c,i;
long r;
i= 0;
while(1){
c= read_byte();
if(c==EOF)

error(ERR_ARITY_SYNTAX,NIL);
if(i==0&&(c=='-'||c=='+'))
buf[i++]= c;
else if(isdigit(c))
buf[i++]= c;
else if(!terminable_p(c))
error(ERR_ARITY_SYNTAX,NIL);
else{
unread_byte(c);
break;
}
if(i> 11)
error(ERR_UNIMPLEMENTED,NIL);
}
r= atol(buf);
if(r> INT_MAX||r<INT_MIN)
error(ERR_UNIMPLEMENTED,NIL);
return int_new(r);
}

/*:132*//*133:*/
#line 2295 "lossless.w"

cell
read_special(void)
{
cell r= NIL;
int c;
c= read_byte();
if(c=='f')
r= FALSE;
else if(c=='t')
r= TRUE;
else
error(ERR_UNIMPLEMENTED,NIL);
c= read_byte();
if(!terminable_p(c))
error(ERR_ARITY_SYNTAX,NIL);
unread_byte(c);
return r;
}

/*:133*//*134:*/
#line 2353 "lossless.w"

cell
read_symbol(void)
{
cell r;
char*buf,*nbuf;
int c,i,s;
c= read_byte();
READSYM_EOF_P;
ERR_OOM_P(buf= malloc(CHUNK_SIZE));
s= CHUNK_SIZE;
/*135:*/
#line 2383 "lossless.w"

buf[0]= c;
i= 1;
if(c=='-'||c=='+'){
c= read_byte();
READSYM_EOF_P;
buf[1]= c;
i++;
if(isdigit(buf[1])){

unread_byte(buf[1]);
unread_byte(buf[0]);
free(buf);
return read_number();
}else if(buf[1]=='.')
warn(WARN_AMBIGUOUS_SYMBOL,NIL);
else if(!isprint(c))
error(ERR_ARITY_SYNTAX,NIL);
}

/*:135*/
#line 2364 "lossless.w"

while(1){/*136:*/
#line 2408 "lossless.w"

c= read_byte();
READSYM_EOF_P;
if(terminable_p(c)){
unread_byte(c);
break;
}
if(!isprint(c))
error(ERR_ARITY_SYNTAX,NIL);
buf[i++]= c;
if(i==s){


nbuf= realloc(buf,s*= 2);
if(nbuf==NULL){
free(buf);
error(ERR_OOM,NIL);
}
buf= nbuf;
}

/*:136*/
#line 2365 "lossless.w"
}
buf[i]= '\0';
r= sym(buf);
free(buf);
return r;
}

/*:134*//*138:*/
#line 2475 "lossless.w"

ssize_t
write_applicative(cell sexp,
char*buf,
ssize_t rem,
int depth ll_unused)
{
ssize_t len= 0;
if(!applicative_p(sexp))
return 0;
append(buf,rem,"#<applicative ...>",len);
return len;
}

ssize_t
write_compiler(cell sexp,
char*buf,
ssize_t rem,
int depth ll_unused)
{
ssize_t len= 0;
if(!compiler_p(sexp))
return 0;
append(buf,rem,"#<compiler ",len);
append(buf,rem,compiler_cname(sexp),len);
if(rem==0)
return-1;
buf[0]= '>';
buf[1]= '\0';
return len+1;
}

ssize_t
write_operative(cell sexp,
char*buf,
ssize_t rem,
int depth ll_unused)
{
ssize_t len= 0;
if(!operative_p(sexp))
return 0;
append(buf,rem,"#<operative ...>",len);
return len;
}

/*:138*//*139:*/
#line 2522 "lossless.w"

ssize_t
write_integer(cell sexp,
char*buf,
ssize_t rem,
int depth ll_unused)
{
ssize_t len= 0;
if(!integer_p(sexp))
return 0;
len= snprintf(buf,rem,"%d",int_value(sexp));
if(len>=rem)
return-1;
return len;
}

ssize_t
write_symbol(cell sexp,
char*buf,
ssize_t rem,
int depth ll_unused)
{
int i;
if(!symbol_p(sexp))
return 0;

if(rem==0)
return-1;
for(i= 0;rem> 0&&i<symbol_length(sexp);i++,rem--)
buf[i]= symbol_store(sexp)[i];
if(i!=symbol_length(sexp)){
buf[i-1]= '\0';
return-i;
}
buf[i]= '\0';
return i;
}

/*:139*//*140:*/
#line 2563 "lossless.w"

ssize_t
write_syntax(cell sexp,
char*buf,
ssize_t rem,
int depth)
{
ssize_t len= 0;
if(!syntax_p(sexp))
return 0;
else if(car(sexp)==sym(SYNTAX_DOTTED))append(buf,rem,". ",len);
else if(car(sexp)==sym(SYNTAX_QUASI))append(buf,rem,"`",len);
else if(car(sexp)==sym(SYNTAX_QUOTE))append(buf,rem,"'",len);
else if(car(sexp)==sym(SYNTAX_UNQUOTE))append(buf,rem,",",len);
else if(car(sexp)==sym(SYNTAX_UNSPLICE))append(buf,rem,",@",len);
append_write(buf,rem,cdr(sexp),depth+1,len);
return len;
}

/*:140*//*141:*/
#line 2585 "lossless.w"

ssize_t
write_environment(cell sexp,
char*buf,
ssize_t rem,
int depth)
{
ssize_t len= 0;
if(!environment_p(sexp))
return 0;
append(buf,rem,"#<environment ",len);
append_write(buf,rem,env_layer(sexp),depth,len);
if(!null_p(env_parent(sexp))){
append(buf,rem," ON ",len);
append_write(buf,rem,env_parent(sexp),depth+1,len);
append(buf,rem,">",len);
}else
append(buf,rem," ROOT>",len);
return len;
}

/*:141*//*142:*/
#line 2609 "lossless.w"

ssize_t
write_exception(cell sexp,
char*buf,
ssize_t rem,
int depth)
{
ssize_t len= 0;
if(!exception_p(sexp))
return 0;
append(buf,rem,"#<EXCEPTION ",len);
append_write(buf,rem,ex_id(sexp),depth,len);
append(buf,rem," ",len);
append_write(buf,rem,ex_detail(sexp),depth+1,len);
append(buf,rem,">",len);
return len;
}

/*:142*//*143:*/
#line 2632 "lossless.w"

ssize_t
write_list(cell sexp,
char*buf,
ssize_t rem,
int depth)
{
ssize_t len= 0;
if(!pair_p(sexp))
return 0;
append(buf,rem,"(",len);
while(pair_p(sexp)){
append_write(buf,rem,car(sexp),depth+1,len);
if(pair_p(cdr(sexp))||syntax_p(cdr(sexp)))
append(buf,rem," ",len);
else if(!null_p(cdr(sexp))
&&!pair_p(cdr(sexp))
&&!syntax_p(cdr(sexp)))
append(buf,rem," . ",len);
sexp= cdr(sexp);
}
if(!null_p(sexp))
append_write(buf,rem,sexp,depth+1,len);
append(buf,rem,")",len);
return len;
}

ssize_t
write_vector(cell sexp,
char*buf,
ssize_t rem,
int depth)
{
int i;
ssize_t len= 0;
if(!vector_p(sexp))
return 0;
append(buf,rem,"[",len);
for(i= 0;i<vector_length(sexp);i++){
append_write(buf,rem,vector_ref(sexp,i),depth+1,len);
if(i+1<vector_length(sexp))
append(buf,rem," ",len);
}
append(buf,rem,"]",len);
return len;
}

/*:143*//*144:*/
#line 2683 "lossless.w"

ssize_t
write_bytecode(cell sexp,
char*buf,
ssize_t rem,
int depth)
{
int arg,ins,op;
ssize_t len= 1;
if(rem<=0)
return-1;
*buf++= '{';
rem--;
op= 0;
while(op<vector_length(sexp)){
if(op)
append(buf,rem," ",len);
ins= int_value(vector_ref(sexp,op));
if(ins>=OPCODE_MAX)
error(ERR_UNEXPECTED,NIL);
append(buf,rem,OP[ins].name,len);
for(arg= 1;arg<=OP[ins].nargs;arg++){
append(buf,rem," ",len);
append_write(buf,rem,vector_ref(sexp,op+arg),depth+1,len);
}
op+= 1+OP[ins].nargs;
}
append(buf,rem,"}",len);
return len;
}


/*:144*//*145:*/
#line 2719 "lossless.w"

ssize_t
write_form(cell sexp,
char*buf,
ssize_t rem,
int depth)
{
ssize_t len= 0;
if(Interrupt){
if(!depth)
append(buf,rem,"... ",len);
return len;
}
if(depth> WRITER_MAX_DEPTH)
error(ERR_RECURSION,NIL);
if(undefined_p(sexp))
append(buf,rem,"#><",len);
else if(eof_p(sexp))
append(buf,rem,"#<eof>",len);
else if(false_p(sexp))
append(buf,rem,"#f",len);
else if(null_p(sexp))
append(buf,rem,"()",len);
else if(true_p(sexp))
append(buf,rem,"#t",len);
else if(void_p(sexp))
append(buf,rem,"#<>",len);
else if((len= write_applicative(sexp,buf,rem,depth)));
else if((len= write_compiler(sexp,buf,rem,depth)));
else if((len= write_environment(sexp,buf,rem,depth)));
else if((len= write_exception(sexp,buf,rem,depth)));
else if((len= write_integer(sexp,buf,rem,depth)));
else if((len= write_list(sexp,buf,rem,depth)));
else if((len= write_operative(sexp,buf,rem,depth)));
else if((len= write_symbol(sexp,buf,rem,depth)));
else if((len= write_syntax(sexp,buf,rem,depth)));
else if((len= write_vector(sexp,buf,rem,depth)));
else append(buf,rem,"#<wtf?>",len);
return len;
}

/*:145*//*172:*/
#line 3223 "lossless.w"

void
emit(cell bc)
{
int l;
l= vector_length(Compilation);
if(Here>=l)
Compilation= vector_sub(Compilation,
0,l,
0,l+COMPILATION_SEGMENT,
OP_HALT);
vector_ref(Compilation,Here++)= bc;
}

/*:172*//*173:*/
#line 3247 "lossless.w"

int
comefrom(void)
{
emit(NIL);
return Here-1;
}

/*:173*//*174:*/
#line 3259 "lossless.w"

cell
compile(cell source)
{
cell r;
Compilation= vector_new(COMPILATION_SEGMENT,int_new(OP_HALT));
Here= 0;
cts_reset();
compile_expression(source,1);
emitop(OP_RETURN);
r= vector_sub(Compilation,0,Here,0,Here,VOID);
Compilation= Zero_Vector;
if(!null_p(CTS))
error(ERR_COMPILE_DIRTY,source);
return r;
}

/*:174*//*175:*/
#line 3280 "lossless.w"

cell
compile_main(void)
{
cell r;
r= vector_new_imp(3,0,0);
vector_ref(r,0)= int_new(OP_COMPILE);
vector_ref(r,1)= int_new(OP_RUN);
vector_ref(r,2)= int_new(OP_HALT);
return r;
}

/*:175*//*176:*/
#line 3296 "lossless.w"

void
compile_expression(cell sexp,
int tail_p)
{
if(!pair_p(sexp)&&!syntax_p(sexp)){
/*177:*/
#line 3312 "lossless.w"

if(symbol_p(sexp)){
emitq(sexp);
emitop(OP_LOOKUP);
}else{
emitq(sexp);
}

/*:177*/
#line 3302 "lossless.w"

}else{
/*178:*/
#line 3325 "lossless.w"

cell args,combiner;
combiner= car(sexp);
args= undot(cdr(sexp));
/*179:*/
#line 3348 "lossless.w"

if(syntax_p(sexp)){
cell c;
c= env_search(Root,combiner);
if(undefined_p(c))
error(ERR_UNBOUND,combiner);
combiner= c;
}

/*:179*/
#line 3329 "lossless.w"

if(compiler_p(combiner)){
/*180:*/
#line 3360 "lossless.w"

compiler_fn(combiner)(combiner,args,tail_p);

/*:180*/
#line 3331 "lossless.w"

}else if(applicative_p(combiner)){
/*191:*/
#line 3595 "lossless.w"

cell collect,direct,formals,a;
int nargs= 0;

formals= applicative_formals(combiner);
cts_push(direct= NIL);
a= undot(args);
/*192:*/
#line 3617 "lossless.w"

while(pair_p(formals)){
if(!pair_p(a)){
if(null_p(a))
arity_error(ERR_ARITY_SYNTAX,combiner,args);
else
arity_error(ERR_ARITY_SYNTAX,combiner,args);
}
direct= cons(car(a),direct);
cts_set(direct);
a= undot(cdr(a));
formals= cdr(formals);
nargs++;
}

/*:192*/
#line 3602 "lossless.w"

/*193:*/
#line 3636 "lossless.w"

if(symbol_p(formals)){
nargs++;
cts_push(collect= NIL);
while(pair_p(a)){
collect= cons(car(a),collect);
cts_set(collect);
a= undot(cdr(a));
}
}

/*:193*/
#line 3603 "lossless.w"

if(pair_p(a))
arity_error(ERR_ARITY_EXTRA,combiner,args);
else if(!null_p(a))
arity_error(ERR_ARITY_SYNTAX,combiner,args);
/*195:*/
#line 3664 "lossless.w"

if(symbol_p(formals)){
emitop(OP_NIL);
while(!null_p(collect)){
compile_expression(car(collect),0);
emitop(OP_CONS);
emitop(OP_PUSH);
collect= cdr(collect);
}
cts_clear();
}

/*:195*/
#line 3608 "lossless.w"

/*194:*/
#line 3651 "lossless.w"

while(!null_p(direct)){
compile_expression(car(direct),0);
emitop(OP_PUSH);
direct= cdr(direct);
}

/*:194*/
#line 3609 "lossless.w"

cts_clear();
emitop(tail_p?OP_APPLY_TAIL:OP_APPLY);
emit(combiner);

/*:191*/
#line 3333 "lossless.w"

}else if(operative_p(combiner)){
/*200:*/
#line 3777 "lossless.w"

cell a,c,e,f;
f= operative_formals(combiner);
a= !null_p(car(f));f= cdr(f);
e= !null_p(car(f));f= cdr(f);
c= !null_p(car(f));f= cdr(f);

if(c)
error(ERR_UNIMPLEMENTED,NIL);
else
emitop(OP_NIL);
if(e){
emitop(OP_ENV_QUOTE);
emitop(OP_PUSH);
}else
emitop(OP_NIL);
if(a){
emitq(args);
emitop(OP_PUSH);
}else
emitop(OP_NIL);

emitop(tail_p?OP_APPLY_TAIL:OP_APPLY);
emit(combiner);

/*:200*/
#line 3335 "lossless.w"

}else if(symbol_p(combiner)||pair_p(combiner)){
/*181:*/
#line 3367 "lossless.w"

emitq(args);
emitop(OP_PUSH);
compile_expression(combiner,0);

emitop(OP_CONS);
emitop(OP_COMPILE);
emitop(OP_RUN);

/*:181*/
#line 3337 "lossless.w"

}else{
error(ERR_UNCOMBINABLE,combiner);
}

/*:178*/
#line 3304 "lossless.w"

}
}

/*:176*//*185:*/
#line 3403 "lossless.w"

cell
arity(cell op,
cell args,
int min,
boolean more_p)
{
cell a= args;
int i= 0;
for(;i<min;i++){
if(null_p(a)){
if(compiler_p(op)||operative_p(op))
arity_error(ERR_ARITY_SYNTAX,op,args);
else
arity_error(ERR_ARITY_MISSING,op,args);
}
if(!pair_p(a))
arity_error(ERR_ARITY_SYNTAX,op,args);
cts_push(car(a));
a= cdr(a);
}
if(min&&!more_p&&!null_p(a)){
if(pair_p(a))
arity_error(ERR_ARITY_EXTRA,op,args);
else
arity_error(ERR_ARITY_SYNTAX,op,args);
}
return a;
}

/*:185*//*186:*/
#line 3438 "lossless.w"

cell
arity_next(cell op,
cell args,
cell more,
boolean required_p,
boolean last_p)
{
if(null_p(more)){
if(required_p)
arity_error(ERR_ARITY_MISSING,op,args);
else{
cts_push(UNDEFINED);
return NIL;
}
}else if(!pair_p(more))
arity_error(ERR_ARITY_SYNTAX,op,args);
else if(last_p&&!null_p(cdr(more))){
if(operative_p(op)&&pair_p(cdr(more)))
arity_error(ERR_ARITY_EXTRA,op,args);
else
arity_error(ERR_ARITY_SYNTAX,op,args);
}
cts_push(car(more));
return cdr(more);
}

/*:186*//*187:*/
#line 3471 "lossless.w"

void
compile_list(cell op,
cell sexp,
boolean tail_p)
{
boolean t;
cell body,next,this;
body= undot(sexp);
t= null_p(body);
if(t){
emitq(VOID);
return;
}
while(!t){
if(!pair_p(body))
arity_error(ERR_ARITY_SYNTAX,op,sexp);
this= car(body);
next= undot(cdr(body));
t= null_p(next);
compile_expression(this,t&&tail_p);
body= next;
}
}

/*:187*//*189:*/
#line 3526 "lossless.w"

void
compile_lambda(cell op,
cell args,
boolean tail_p)
{
cell body,in,formals,f;
int begin_address,comefrom_end;
body= arity(op,args,1,btrue);
body= undot(body);
formals= cts_pop();
formals= undot(formals);
if(!symbol_p(formals)){/*190:*/
#line 3562 "lossless.w"

cts_push(f= cons(NIL,NIL));
in= formals;
while(pair_p(in)){
if(!symbol_p(car(in))&&!false_p(car(in)))
arity_error(ERR_ARITY_SYNTAX,op,args);
find_formal_duplicates(car(in),cdr(cts_ref()));
cdr(f)= cons(car(in),NIL);
f= cdr(f);
in= undot(cdr(in));
}
if(!null_p(in)){
if(!symbol_p(in)&&!false_p(in))
arity_error(ERR_ARITY_SYNTAX,op,args);
find_formal_duplicates(in,cdr(cts_ref()));
cdr(f)= in;
}
formals= cdr(cts_pop());

/*:190*/
#line 3538 "lossless.w"
}
emitq(formals);
emitop(OP_PUSH);
emitop(OP_LAMBDA);
begin_address= comefrom();

emitop(OP_JUMP);
comefrom_end= comefrom();
patch(begin_address,int_new(Here));
compile_list(op,body,tail_p);

emitop(OP_RETURN);
patch(comefrom_end,int_new(Here));
}

/*:189*//*198:*/
#line 3707 "lossless.w"

void
compile_vov(cell op,
cell args,
boolean tail_p)
{
cell body,formals;
int begin_address,comefrom_end;
cell a= NIL;
cell c= NIL;
cell e= NIL;
body= arity(op,args,1,1);
body= undot(body);
formals= cts_pop();
formals= undot(formals);
/*199:*/
#line 3745 "lossless.w"

cell r,s;
if(!pair_p(formals))
arity_error(ERR_ARITY_SYNTAX,op,args);
#define CHECK_AND_ASSIGN(v) {                            \
        if (!null_p(v))                                  \
                arity_error(ERR_ARITY_SYNTAX, op, args); \
        (v) =  s;                                         \
}
while(pair_p(formals)){
arity(op,car(formals),2,0);
r= cts_pop();
s= cts_pop();
if(!symbol_p(s))
arity_error(ERR_ARITY_SYNTAX,op,args);
else if(r==Sym_vov_args||r==Sym_vov_args_long)
CHECK_AND_ASSIGN(a)
else if(r==Sym_vov_env||r==Sym_vov_env_long)
CHECK_AND_ASSIGN(e)
else if(r==Sym_vov_cont||r==Sym_vov_cont_long)
CHECK_AND_ASSIGN(c)
formals= cdr(formals);
}
if(!null_p(formals))
arity_error(ERR_ARITY_SYNTAX,op,args);

/*:199*/
#line 3722 "lossless.w"

emitop(OP_NIL);
emitq(c);emitop(OP_CONS);emitop(OP_PUSH);
emitq(e);emitop(OP_CONS);emitop(OP_PUSH);
emitq(a);emitop(OP_CONS);emitop(OP_PUSH);
emitop(OP_VOV);

begin_address= comefrom();
emitop(OP_JUMP);
comefrom_end= comefrom();
patch(begin_address,int_new(Here));
compile_list(op,body,tail_p);

emitop(OP_RETURN);
patch(comefrom_end,int_new(Here));
}

/*:198*//*201:*/
#line 3808 "lossless.w"

void
compile_conditional(cell op,
cell args,
boolean tail_p)
{
cell alternate,condition,consequent,more;
int jump_false,jump_true;
more= arity(op,args,2,1);
arity_next(op,args,more,0,1);
alternate= cts_pop();
consequent= cts_pop();
condition= cts_pop();
compile_expression(condition,0);
emitop(OP_JUMP_FALSE);
jump_false= comefrom();
compile_expression(consequent,tail_p);
emitop(OP_JUMP);
jump_true= comefrom();
patch(jump_false,int_new(Here));
if(undefined_p(alternate))
emitq(VOID);
else
compile_expression(alternate,tail_p);
patch(jump_true,int_new(Here));
}

/*:201*//*202:*/
#line 3839 "lossless.w"

void
compile_eval(cell op,
cell args,
boolean tail_p ll_unused)
{
cell more,sexp,eenv;
int goto_env_p;
more= arity(op,args,1,btrue);
sexp= cts_pop();
arity_next(op,args,more,bfalse,btrue);
eenv= cts_pop();
if(!undefined_p(eenv)){
compile_expression(eenv,0);
emitop(OP_PUSH);
emitop(OP_ENVIRONMENT_P);
emitop(OP_JUMP_TRUE);
goto_env_p= comefrom();
emitq(Sym_ERR_UNEXPECTED);
emitop(OP_ERROR);
patch(goto_env_p,int_new(Here));
}
compile_expression(sexp,0);
emitop(OP_COMPILE);
emitop(undefined_p(eenv)?OP_RUN:OP_RUN_THERE);
}

/*:202*//*203:*/
#line 3869 "lossless.w"

void
compile_error(cell op,
cell args,
boolean tail_p ll_unused)
{
cell id,more,value;
more= arity(op,args,1,1);
arity_next(op,args,more,0,1);
value= cts_pop();
id= cts_pop();
if(!symbol_p(id))
arity_error(ERR_ARITY_SYNTAX,op,args);
if(undefined_p(value))
emitq(NIL);
else
compile_expression(value,0);
emitop(OP_PUSH);
emitq(id);
emitop(OP_ERROR);
}

/*:203*//*204:*/
#line 3900 "lossless.w"

void
compile_cons(cell op,
cell args,
boolean tail_p ll_unused)
{
cell ncar,ncdr;
arity(op,args,2,0);
ncdr= cts_pop();
ncar= cts_pop();
compile_expression(ncdr,0);
emitop(OP_PUSH);
compile_expression(ncar,0);
emitop(OP_CONS);
}

void
compile_car(cell op,
cell args,
boolean tail_p ll_unused)
{
int comefrom_pair_p;
arity(op,args,1,0);
compile_expression(cts_pop(),0);
emitop(OP_PUSH);
emitop(OP_PAIR_P);
emitop(OP_JUMP_TRUE);
comefrom_pair_p= Here;
emit(NIL);
emitq(Sym_ERR_UNEXPECTED);
emitop(OP_ERROR);
patch(comefrom_pair_p,int_new(Here));
emitop(OP_POP);
emitop(OP_CAR);
}

void
compile_cdr(cell op,
cell args,
boolean tail_p ll_unused)
{
int comefrom_pair_p;
arity(op,args,1,0);
compile_expression(cts_pop(),0);
emitop(OP_PUSH);
emitop(OP_PAIR_P);
emitop(OP_JUMP_TRUE);
comefrom_pair_p= Here;
emit(NIL);
emitq(Sym_ERR_UNEXPECTED);
emitop(OP_ERROR);
patch(comefrom_pair_p,int_new(Here));
emitop(OP_POP);
emitop(OP_CDR);
}

void
compile_null_p(cell op,
cell args,
boolean tail_p ll_unused)
{
arity(op,args,1,0);
compile_expression(cts_pop(),0);
emitop(OP_NULL_P);
}

void
compile_pair_p(cell op,
cell args,
boolean tail_p ll_unused)
{
arity(op,args,1,0);
compile_expression(cts_pop(),0);
emitop(OP_PAIR_P);
}

void
compile_set_car_m(cell op,
cell args,
boolean tail_p ll_unused)
{
cell value,object;
int goto_pair_p;
arity(op,args,2,0);
value= cts_pop();
object= cts_pop();
compile_expression(object,bfalse);
emitop(OP_PUSH);
emitop(OP_PAIR_P);
emitop(OP_JUMP_TRUE);
goto_pair_p= comefrom();
emitq(Sym_ERR_UNEXPECTED);
emitop(OP_ERROR);
patch(goto_pair_p,int_new(Here));
compile_expression(value,bfalse);
emitop(OP_SET_CAR_M);
}

void
compile_set_cdr_m(cell op,
cell args,
boolean tail_p ll_unused)
{
cell value,object;
int goto_pair_p;
arity(op,args,2,0);
value= cts_pop();
object= cts_pop();
compile_expression(object,bfalse);
emitop(OP_PUSH);
emitop(OP_PAIR_P);
emitop(OP_JUMP_TRUE);
goto_pair_p= comefrom();
emitq(Sym_ERR_UNEXPECTED);
emitop(OP_ERROR);
patch(goto_pair_p,int_new(Here));
compile_expression(value,bfalse);
emitop(OP_SET_CDR_M);
}

/*:204*//*205:*/
#line 4023 "lossless.w"

void
compile_set_m(cell op,
cell args,
boolean tail_p ll_unused)
{
cell env,name,value;
int goto_env_p;
arity(op,args,3,bfalse);
value= cts_pop();
name= cts_pop();
env= cts_pop();
if(!symbol_p(name))
error(ERR_ARITY_SYNTAX,NIL);
compile_expression(env,bfalse);
emitop(OP_PUSH);
emitop(OP_ENVIRONMENT_P);
emitop(OP_JUMP_TRUE);
goto_env_p= comefrom();
emitq(Sym_ERR_UNEXPECTED);
emitop(OP_ERROR);
patch(goto_env_p,int_new(Here));
compile_expression(value,bfalse);
emitop(OP_ENV_MUTATE_M);
emit(name);
emit(FALSE);
}

void
compile_define_m(cell op,
cell args,
boolean tail_p ll_unused)
{
cell env,name,value;
int goto_env_p;
arity(op,args,3,bfalse);
value= cts_pop();
name= cts_pop();
env= cts_pop();
if(!symbol_p(name))
error(ERR_ARITY_SYNTAX,NIL);
compile_expression(env,bfalse);
emitop(OP_PUSH);
emitop(OP_ENVIRONMENT_P);
emitop(OP_JUMP_TRUE);
goto_env_p= comefrom();
emitq(Sym_ERR_UNEXPECTED);
emitop(OP_ERROR);
patch(goto_env_p,int_new(Here));
compile_expression(value,bfalse);
emitop(OP_ENV_MUTATE_M);
emit(name);
emit(TRUE);
}

void
compile_env_root(cell op,
cell args,
boolean tail_p ll_unused)
{
arity(op,args,0,bfalse);
emitop(OP_ENV_ROOT);
}

void
compile_env_current(cell op,
cell args,
boolean tail_p ll_unused)
{
arity(op,args,0,bfalse);
emitop(OP_ENV_QUOTE);
}

/*:205*//*206:*/
#line 4100 "lossless.w"

void
compile_quote(cell op ll_unused,
cell args,
boolean tail_p ll_unused)
{
emitq(args);
}

/*:206*//*209:*/
#line 4127 "lossless.w"

void
compile_quasiquote(cell op,
cell args,
boolean tail_p ll_unused)
{
compile_quasicompiler(op,args,args,0,bfalse);
}

/*:209*//*210:*/
#line 4144 "lossless.w"

void
compile_quasicompiler(cell op,
cell oargs,
cell arg,
int depth,
boolean in_list_p)
{
if(pair_p(arg)){
/*211:*/
#line 4177 "lossless.w"

cell todo,tail;
tail= NIL;
todo= list_reverse(arg,&tail,NULL);
compile_quasicompiler(op,oargs,tail,depth,bfalse);
for(;!null_p(todo);todo= cdr(todo)){
emitop(OP_PUSH);
compile_quasicompiler(op,oargs,car(todo),depth,btrue);
}
if(in_list_p)
emitop(OP_CONS);

/*:211*/
#line 4153 "lossless.w"

}else if(vector_p(arg)){
error(ERR_UNIMPLEMENTED,NIL);
}else if(syntax_p(arg)){
/*212:*/
#line 4197 "lossless.w"

int d;
if(car(arg)==Sym_SYNTAX_DOTTED
||car(arg)==Sym_SYNTAX_QUOTE
||car(arg)==Sym_SYNTAX_QUASI){
d= (car(arg)==Sym_SYNTAX_QUASI)?1:0;
compile_quasicompiler(op,oargs,cdr(arg),depth+d,bfalse);
emitop(OP_SYNTAX);
emit(car(arg));
if(in_list_p)
emitop(OP_CONS);
}

/*:212*//*213:*/
#line 4215 "lossless.w"

else if(car(arg)==Sym_SYNTAX_UNQUOTE){
if(depth> 0){
compile_quasicompiler(op,oargs,cdr(arg),depth-1,bfalse);
emitop(OP_SYNTAX);
emit(Sym_SYNTAX_UNQUOTE);
}else
compile_expression(cdr(arg),bfalse);
if(in_list_p)
emitop(OP_CONS);
}

/*:213*//*214:*/
#line 4230 "lossless.w"

else if(car(arg)==Sym_SYNTAX_UNSPLICE){
if(depth> 0){
compile_quasicompiler(op,oargs,cdr(arg),depth-1,bfalse);
emitop(OP_SYNTAX);
emit(Sym_SYNTAX_UNSPLICE);
if(in_list_p)
emitop(OP_CONS);
}else{/*215:*/
#line 4252 "lossless.w"

int goto_inject_iterate,goto_inject_start,goto_finish;
int goto_list_p,goto_null_p,goto_nnull_p;
if(!in_list_p)
error(ERR_UNEXPECTED,arg);
emitop(OP_PEEK);
emitop(OP_NULL_P);
emitop(OP_JUMP_TRUE);
goto_null_p= comefrom();
emitop(OP_PUSH);
emitop(OP_JUMP);
goto_nnull_p= comefrom();
patch(goto_null_p,int_new(Here));
emitop(OP_SWAP);
patch(goto_nnull_p,int_new(Here));

/*:215*//*216:*/
#line 4272 "lossless.w"

compile_expression(cdr(arg),0);
emitop(OP_PUSH);
emitop(OP_LIST_P);
emit(TRUE);
emit(FALSE);
emitop(OP_JUMP_TRUE);
goto_list_p= comefrom();
emitq(Sym_ERR_UNEXPECTED);
emitop(OP_ERROR);

/*:216*//*217:*/
#line 4286 "lossless.w"

patch(goto_list_p,int_new(Here));
emitop(OP_POP);
emitop(OP_SWAP);
emitop(OP_JUMP_TRUE);
goto_finish= comefrom();

/*:217*//*218:*/
#line 4301 "lossless.w"

emitop(OP_POP);
emitop(OP_LIST_REVERSE);
emit(TRUE);
emit(FALSE);
/*219:*/
#line 4308 "lossless.w"

emitop(OP_JUMP);
goto_inject_start= comefrom();

goto_inject_iterate= Here;
emitop(OP_POP);
emitop(OP_SNOC);
emitop(OP_CYCLE);
emitop(OP_CONS);
emitop(OP_SWAP);

/*:219*//*220:*/
#line 4324 "lossless.w"

patch(goto_inject_start,int_new(Here));
emitop(OP_PUSH);
emitop(OP_NULL_P);
emitop(OP_JUMP_FALSE);
emit(int_new(goto_inject_iterate));
emitop(OP_POP);
patch(goto_finish,int_new(Here));
emitop(OP_POP);

/*:220*/
#line 4306 "lossless.w"


/*:218*/
#line 4238 "lossless.w"
}
}else
error(ERR_UNIMPLEMENTED,NIL);

/*:214*/
#line 4157 "lossless.w"

}else{
emitq(arg);
if(in_list_p)
emitop(OP_CONS);
}
}

/*:210*//*231:*/
#line 4423 "lossless.w"

llt_buffer*
llt_alloc_imp(size_t len,
size_t size)
{
llt_buffer*r;
size_t total;
total= (len*size)+sizeof(llt_buffer);
ERR_OOM_P(r= calloc(total,1));
r->len= len;
r->size= size;
return r;
}

/*:231*//*232:*/
#line 4438 "lossless.w"

llt_buffer*
llt_grow_imp(llt_buffer*old,
size_t len)
{
llt_buffer*new;
size_t ntotal;
ntotal= (len*old->size)+sizeof(llt_buffer);
ERR_OOM_P(new= realloc(old,ntotal));
bzero((char*)new+sizeof(llt_buffer)+(new->size*new->len),
new->size*(len-new->len));
new->len= len;
return new;
}

/*:232*//*233:*/
#line 4456 "lossless.w"

llt_buffer*
llt_cat(const char*fmt,
...)
{
llt_buffer*r= llt_alloc(0,char);
int ret= -1;
va_list ap;
va_start(ap,fmt);
while(ret<0||r->data[r->len-1]){
llt_grow(r,BUFFER_SEGMENT);
ret= vsnprintf(r->data,r->len,fmt,ap);
}
va_end(ap);
return r;
}

/*:233*//*236:*/
#line 4493 "lossless.w"

llt_buffer*
llt_serialise(cell obj,
boolean offset_p)
{
int i;
size_t off;
llt_buffer*r;
r= llt_alloc(sizeof(cell),char);
*(cell*)r->data= obj;
off= sizeof(cell);
if(special_p(obj))
return r;
llt_grow(r,sizeof(char)+(sizeof(cell)*2));
bcopy(&tag(obj),r->data+off,sizeof(char));
off+= 1;
if(vector_p(obj))
bzero(r->data+off,sizeof(cell));
else
bcopy(&car(obj),r->data+off,sizeof(cell));
off+= sizeof(cell);
if(vector_p(obj)&&!offset_p)
bzero(r->data+off,sizeof(cell));
else
bcopy(&cdr(obj),r->data+off,sizeof(cell));
off+= sizeof(cell);
if(acar_p(obj))
llt_extend_serial(r,llt_serialise(car(obj),offset_p),off);
if(acdr_p(obj))
llt_extend_serial(r,llt_serialise(cdr(obj),offset_p),off);
if(vector_p(obj)){
llt_grow(r,sizeof(cell)*VECTOR_HEAD);
for(i= 1;i<=VECTOR_HEAD;i++){
bcopy(&vector_ref(obj,-i),r->data+off,
sizeof(cell));
off+= sizeof(cell);
}
for(i= 0;i<vector_length(obj);i++)
llt_extend_serial(r,
llt_serialise(vector_ref(obj,i),offset_p),
off);
}
return r;
}

/*:236*//*237:*/
#line 4538 "lossless.w"

llt_buffer*
llt_copy_refs(cell obj)
{
size_t off= sizeof(cell);
llt_buffer*r= llt_alloc(1,cell);
*(cell*)r->data= obj;
if(acar_p(obj))
llt_extend_serial(r,llt_copy_refs(car(obj)),off);
if(acdr_p(obj))
llt_extend_serial(r,llt_copy_refs(cdr(obj)),off);
return r;
}

/*:237*//*238:*/
#line 4552 "lossless.w"

boolean
llt_compare_serial(llt_buffer*buf1,
cell obj,
boolean offset_p)
{
boolean r;
llt_buffer*buf2;
buf2= llt_serialise(obj,offset_p);
if(buf1->len!=buf2->len){
free(buf2);
return bfalse;
}
r= (bcmp(buf1,buf2,buf1->len)==0)?btrue:bfalse;
free(buf2);
return r;
}

/*:238*//*242:*/
#line 4615 "lossless.w"

void
tap_plan(int plan)
{
if(plan==0){
if(Test_Plan<0)
printf("1..%d\n",Next_Test-1);
else if(Next_Test-1!=Test_Plan){
printf("# Planned %3$d %1$s but ran %2$s%4$d!\n",
(Test_Plan==1?"test":"tests"),
(Next_Test<=Test_Plan?"only ":""),
Test_Plan,Next_Test-1);
Test_Passing= bfalse;
}
return;
}
if(Test_Plan> 0)
error("plan-exists",int_new(Test_Plan));
if(plan<0)
error(ERR_UNEXPECTED,cons(sym("test-plan"),int_new(plan)));
Test_Plan= plan;
printf("1..%d\n",plan);
}

/*:242*//*243:*/
#line 4639 "lossless.w"

boolean
tap_ok(boolean result,
char*message)
{
printf("%s %d %s\n",(result?"ok":"not ok"),Next_Test++,
(message&&*message)?message:"?");
if(result)
return btrue;
return Test_Passing= bfalse;
}

/*:243*//*245:*/
#line 4667 "lossless.w"

char*
test_msgf(char*tmsg,
char*tsrc,
char*fmt,
...)
{

char ttmp[TEST_BUFSIZE]= {0};
int ret;
va_list ap;
va_start(ap,fmt);
ret= vsnprintf(ttmp,TEST_BUFSIZE,fmt,ap);
va_end(ap);
snprintf(tmsg,TEST_BUFSIZE,"%s: %s",tsrc,ttmp);
return tmsg;
}

/*:245*//*251:*/
#line 4716 "lossless.w"

cell
testing_build_probe(cell was_Acc)
{
cell t;
vms_push(NIL);
probe_push("Acc",was_Acc);
probe_push("Args",Acc);
probe_push("Env",Env);
return vms_pop();
}

/*:251*//*252:*/
#line 4728 "lossless.w"

void
compile_testing_probe(cell op ll_unused,
cell args,
boolean tail_p ll_unused)
{
emitop(OP_PUSH);
emitq(args);
emitop(OP_TEST_PROBE);
}

/*:252*//*253:*/
#line 4740 "lossless.w"

void
compile_testing_probe_app(cell op ll_unused,
cell args,
boolean tail_p ll_unused)
{
emitop(OP_PUSH);
cts_push(args= list_reverse(args,NULL,NULL));
emitq(NIL);
for(;pair_p(args);args= cdr(args)){
emitop(OP_PUSH);
compile_expression(car(args),bfalse);
emitop(OP_CONS);
}
cts_pop();
emitop(OP_TEST_PROBE);
}

/*:253*//*254:*/
#line 4784 "lossless.w"

void
test_vm_state(char*prefix,
int flags)
{
char msg[TEST_BUFSIZE]= {0};
if(flags&TEST_VMSTATE_RUNNING)
tap_ok(Running,tmsgf("(== Running 1)"));
else
tap_ok(!Running,tmsgf("(== Running 0)"));
if(flags&TEST_VMSTATE_INTERRUPTED)
tap_ok(Interrupt,tmsgf("(== Interrupt 1)"));
else
tap_ok(!Interrupt,tmsgf("(== Interrupt 0)"));
if(flags&TEST_VMSTATE_VMS)
tap_ok(null_p(VMS),tmsgf("(null? VMS)"));
if(flags&TEST_VMSTATE_CTS)
tap_ok(null_p(CTS),tmsgf("(null? CTS)"));
if(flags&TEST_VMSTATE_RTS)
tap_ok(RTSp==-1,tmsgf("(== RTSp -1)"));
if(flags&TEST_VMSTATE_ENV_ROOT)
tap_ok(Env==Root,tmsgf("(== Env Root)"));
if(flags&TEST_VMSTATE_PROG_MAIN){
tap_ok(Prog==Prog_Main,
tmsgf("Prog_Main is returned to"));
tap_ok(Ip==vector_length(Prog_Main)-1,
tmsgf("Prog_Main is completed"));
}

}

/*:254*//*255:*/
#line 4815 "lossless.w"

int
test_count_free_list(void)
{
int r= 0;
cell c= Cells_Free;
if(!Cells_Poolsize)
return 0;
while(!null_p(c)){
r++;
c= cdr(c);
}
return r;
}

/*:255*//*264:*/
#line 4994 "lossless.w"

boolean
llt_contains_p(cell haystack,
cell needle)
{
for(;pair_p(haystack);haystack= cdr(haystack))
if(needle==haystack||needle==car(haystack))
return btrue;
if(!null_p(haystack))
if(needle==haystack)
return btrue;
return bfalse;
}

/*:264*//*356:*/
#line 6759 "lossless.w"


/*:356*//*520:*/
#line 9857 "lossless.w"

cell
assoc_member(cell alist,
cell needle)
{
if(!symbol_p(needle))
error(ERR_ARITY_SYNTAX,NIL);
if(!list_p(alist,FALSE,NULL))
error(ERR_ARITY_SYNTAX,NIL);
for(;pair_p(alist);alist= cdr(alist))
if(caar(alist)==needle)
return car(alist);
return FALSE;
}

cell
assoc_content(cell alist,
cell needle)
{
cell r;
r= assoc_member(alist,needle);
if(!pair_p(r))
error(ERR_UNEXPECTED,r);
return cdr(r);
}

cell
assoc_value(cell alist,
cell needle)
{
cell r;
r= assoc_member(alist,needle);
if(!pair_p(cdr(r)))
error(ERR_UNEXPECTED,r);
return cadr(r);
}

/*:520*//*522:*/
#line 9897 "lossless.w"


/*:522*//*524:*/
#line 9902 "lossless.w"

void
compile_symbol_p(cell op,
cell args,
boolean tail_p ll_unused)
{
arity(op,args,1,0);
compile_expression(cts_pop(),0);
emitop(OP_SYMBOL_P);
}

/*:524*/
