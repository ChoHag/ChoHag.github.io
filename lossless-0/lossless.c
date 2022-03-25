/*2:*/
#line 101 "lossless.w"

/*1:*/
#line 83 "lossless.w"

#include <assert.h> 
#include <ctype.h> 
#include <limits.h> 
#include <setjmp.h> 
#include <stdarg.h> 
#include <stdbool.h> 
#include <stdint.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/types.h> 
#include <unistd.h> 

/*:1*/
#line 102 "lossless.w"

/*322:*/
#line 7519 "lossless.w"

#ifdef __GNUC__ 
#       define Lunused __attribute__ ((__unused__))
#else
#       define Lunused 
#endif

#ifdef __GNUC__ 
#       define Lnoreturn __attribute__ ((__noreturn__))
#else
#       ifdef _Noreturn
#               define Lnoreturn _Noreturn
#       else
#               define Lnoreturn 
#       endif
#endif

#ifdef LDEBUG
#       define LDEBUG_P true
#else
#       define LDEBUG_P false
#endif

#if EOF == -1
#       define FAIL -2
#else
#       define FAIL -1
#endif

#define ckd_add(r,x,y) __builtin_add_overflow((x), (y), (r))
#define ckd_sub(r,x,y) __builtin_sub_overflow((x), (y), (r))
#define ckd_mul(r,x,y) __builtin_mul_overflow((x), (y), (r))

/*:322*/
#line 103 "lossless.w"

#define PTR_TAG_SHIFT 56
#define PTR_ADDRESS(p) ((intptr_t(p) ) &((1ull<<PTR_TAG_SHIFT) -1) ) 
#define PTR_TAG_MASK(p) ((intptr_t(p) ) &~((1ull<<PTR_TAG_SHIFT) -1) ) 
#define PTR_TAG(p) (PTR_TAG_MASK(p) >>PTR_TAG_SHIFT) 
#define PTR_SET_TAG(p,s) ((p) = (((p) &PTR_ADDRESS(p) ) |((s) <<PTR_TAG_SHIFT) ) )  \

#define shared 
#define unique __thread \

#define failure_p(O) ((O) !=LERR_NONE) 
#define unwind(J,E,T,S) do{ \
assert((E) !=LERR_NONE) ; \
if(T) Tmp_ier= NIL; \
if(S) stack_clear(S) ; \
siglongjmp(*(J) ,(E) ) ; \
}while(0) 
#define NIL ((cell) 0) 
#define LFALSE ((cell) 1) 
#define LTRUE ((cell) 3) 
#define VOID ((cell) 5)  \

#define LEOF ((cell) 7)  \

#define UNDEFINED ((cell) 13) 
#define FIXED ((cell) 15)  \

#define null_p(O) ((intptr_t) (O) ==0) 
#define special_p(O) (null_p(O) ||((intptr_t) (O) ) &1) 
#define boolean_p(O) ((O) ==LFALSE||(O) ==LTRUE) 
#define false_p(O) ((O) ==LFALSE) 
#define true_p(O) ((O) ==LTRUE) 
#define void_p(O) ((O) ==VOID) 
#define eof_p(O) ((O) ==LEOF) 
#define undefined_p(O) ((O) ==UNDEFINED) 
#define fix_p(O) (((O) &FIXED) ==FIXED) 
#define defined_p(O) (!undefined_p(O) )  \

#define predicate(O) ((O) ?LTRUE:LFALSE)  \

#define LTAG_LIVE 0x80
#define LTAG_DONE 0x40
#define LTAG_DSIN 0x20
#define LTAG_DDEX 0x10
#define LTAG_BOTH (LTAG_DSIN|LTAG_DDEX) 
#define LTAG_FORM (LTAG_BOTH|0x0f) 
#define LTAG_TDEX 0x02
#define LTAG_TSIN 0x01
#define LTAG_NONE 0x00 \

#define TAG(O) (ATOM_TO_TAG((O) ) ) 
#define TAG_SET_M(O,V) (ATOM_TO_TAG((O) ) = (V) )  \

#define ATOM_LIVE_P(O) (TAG(O) &LTAG_LIVE) 
#define ATOM_CLEAR_LIVE_M(O) (TAG_SET_M((O) ,TAG(O) &~LTAG_LIVE) ) 
#define ATOM_SET_LIVE_M(O) (TAG_SET_M((O) ,TAG(O) |LTAG_LIVE) ) 
#define ATOM_MORE_P(O) (TAG(O) &LTAG_DONE) 
#define ATOM_CLEAR_MORE_M(O) (TAG_SET_M((O) ,TAG(O) &~LTAG_DONE) ) 
#define ATOM_SET_MORE_M(O) (TAG_SET_M((O) ,TAG(O) |LTAG_DONE) ) 
#define ATOM_FORM(O) (TAG(O) &LTAG_FORM) 
#define ATOM_SIN_DATUM_P(O) (TAG(O) &LTAG_DSIN) 
#define ATOM_DEX_DATUM_P(O) (TAG(O) &LTAG_DDEX) 
#define ATOM_SIN_THREADABLE_P(O) (TAG(O) &LTAG_TSIN) 
#define ATOM_DEX_THREADABLE_P(O) (TAG(O) &LTAG_TDEX) 
#define FORM_NONE (LTAG_NONE|0x00) 
#define FORM_ARRAY (LTAG_NONE|0x01) 
#define FORM_COLLECTED (LTAG_NONE|0x02) 
#define FORM_FIX (LTAG_NONE|0x03) 
#define FORM_HEAP (LTAG_NONE|0x04) 
#define FORM_KEYTABLE (LTAG_NONE|0x05) 
#define FORM_RECORD (LTAG_NONE|0x06) 
#define FORM_RUNE (LTAG_NONE|0x07) 
#define FORM_SEGMENT_INTERN (LTAG_NONE|0x08) 
#define FORM_SYMBOL (LTAG_NONE|0x09) 
#define FORM_SYMBOL_INTERN (LTAG_NONE|0x0a)  \

#define FORM_PRIMITIVE (LTAG_DDEX|0x00) 
#define FORM_SEGMENT (LTAG_DDEX|0x01)  \

#define FORM_PAIR (LTAG_BOTH|0x00) 
#define FORM_APPLICATIVE (LTAG_BOTH|0x01) 
#define FORM_ENVIRONMENT (LTAG_BOTH|0x02) 
#define FORM_NOTE (LTAG_BOTH|0x03) 
#define FORM_OPERATIVE (LTAG_BOTH|0x04)  \

#define FORM_ROPE (LTAG_BOTH|0x08) 
#define FORM_TROPE_SIN (LTAG_BOTH|0x09) 
#define FORM_TROPE_DEX (LTAG_BOTH|0x0a) 
#define FORM_TROPE_BOTH (LTAG_BOTH|0x0b) 
#define FORM_TREE (LTAG_BOTH|0x0c) 
#define FORM_TTREE_SIN (LTAG_BOTH|0x0d) 
#define FORM_TTREE_DEX (LTAG_BOTH|0x0e) 
#define FORM_TTREE_BOTH (LTAG_BOTH|0x0f)  \

#define form(O) (TAG(O) &LTAG_FORM) 
#define form_p(O,F) (!special_p(O) &&form(O) ==FORM_##F) 
#define pair_p(O) (form_p((O) ,PAIR) ) 
#define array_p(O) (form_p((O) ,ARRAY) ) 
#define null_array_p(O) ((O) ==Null_Array) 
#define collected_p(O) (form_p((O) ,COLLECTED) ) 
#define environment_p(O) (form_p((O) ,ENVIRONMENT) ) 
#define keytable_p(O) (form_p((O) ,KEYTABLE) ||null_array_p(O) ) 
#define note_p(O) (form_p((O) ,NOTE) ) 
#define record_p(O) (form_p((O) ,RECORD) ) 
#define rune_p(O) (form_p((O) ,RUNE) )  \

#define segment_intern_p(O) (form_p((O) ,SEGMENT_INTERN) ) 
#define segment_stored_p(O) (form_p((O) ,SEGMENT) ) 
#define segment_p(O) (segment_intern_p(O) ||segment_stored_p(O) ) 
#define symbol_intern_p(O) (form_p((O) ,SYMBOL_INTERN) ) 
#define symbol_stored_p(O) (form_p((O) ,SYMBOL) ) 
#define symbol_p(O) (symbol_intern_p(O) ||symbol_stored_p(O) )  \

#define character_p(O) (eof_p(O) ||rune_p(O) ) 
#define arraylike_p(O) (array_p(O) ||keytable_p(O) ||record_p(O) ) 
#define pointer_p(O) (segment_stored_p(O) ||arraylike_p(O) ||form_p((O) ,HEAP) )  \

#define primitive_p(O) (form_p((O) ,PRIMITIVE) ) 
#define closure_p(O) (form_p((O) ,APPLICATIVE) ||form_p((O) ,OPERATIVE) ) 
#define program_p(O) (closure_p(O) ||primitive_p(O) ) 
#define applicative_p(O) ((closure_p(O) &&form_p((O) ,APPLICATIVE) ) || \
primitive_applicative_p(O) ) 
#define operative_p(O) ((closure_p(O) &&form_p((O) ,OPERATIVE) ) || \
primitive_operative_p(O) )  \

#define RECORD_ROPE_ITERATOR -1
#define RECORD_ENVIRONMENT_ITERATOR -2
#define RECORD_LEXEME -3
#define RECORD_LEXAR -4
#define RECORD_SYNTAX -5 \

#define rope_iter_p(O) (form_p((O) ,RECORD) &&record_id(O)  \
==fix(RECORD_ROPE_ITERATOR) ) 
#define lexeme_p(O) (form_p((O) ,RECORD) &&record_id(O)  \
==fix(RECORD_LEXEME) ) 
#define lexar_p(O) (form_p((O) ,RECORD) &&record_id(O)  \
==fix(RECORD_LEXAR) ) 
#define syntax_p(O) (form_p((O) ,RECORD) &&record_id(O)  \
==fix(RECORD_SYNTAX) )  \

#define fix_value(O) ((fixed) ((O) >>FIX_SHIFT) ) 
#define HEAP_CHUNK 0x1000
#define HEAP_MASK 0x0fff
#define HEAP_BOOKEND (sizeof(Osegment) +sizeof(Oheap) ) 
#define HEAP_LEFTOVER ((HEAP_CHUNK-HEAP_BOOKEND) /(TAG_BYTES+WIDE_BYTES) ) 
#define HEAP_LENGTH ((int) HEAP_LEFTOVER) 
#define HEAP_HEADER ((HEAP_CHUNK/WIDE_BYTES) -HEAP_LENGTH)  \

#define ATOM_TO_ATOM(O) ((Oatom*) (O) ) 
#define ATOM_TO_HEAP(O) (SEGMENT_TO_HEAP(ATOM_TO_SEGMENT(O) ) ) 
#define ATOM_TO_INDEX(O) (((((intptr_t) (O) ) &HEAP_MASK) >>CELL_SHIFT) -HEAP_HEADER) 
#define ATOM_TO_SEGMENT(O) ((Osegment*) (((intptr_t) (O) ) &~HEAP_MASK) ) 
#define HEAP_TO_SEGMENT(O) (ATOM_TO_SEGMENT(O) ) 
#define SEGMENT_TO_HEAP(O) ((Oheap*) (O) ->address) 
#define HEAP_TO_LAST(O) ((Oatom*) (((intptr_t) HEAP_TO_SEGMENT(O) ) +HEAP_CHUNK) )  \

#define ATOM_TO_TAG(O) (ATOM_TO_HEAP(O) ->tag[ATOM_TO_INDEX(O) ]) 
#define cons(A,D,F) (atom(Theap,(A) ,(D) ,FORM_PAIR,(F) ) ) 
#define lcaar(O) (lcar(lcar(O) ) ) 
#define lcadr(O) (lcar(lcdr(O) ) ) 
#define lcdar(O) (lcdr(lcar(O) ) ) 
#define lcddr(O) (lcdr(lcdr(O) ) ) 
#define lcaaar(O) (lcar(lcar(lcar(O) ) ) ) 
#define lcaadr(O) (lcar(lcar(lcdr(O) ) ) ) 
#define lcadar(O) (lcar(lcdr(lcar(O) ) ) ) 
#define lcaddr(O) (lcar(lcdr(lcdr(O) ) ) ) 
#define lcdaar(O) (lcdr(lcar(lcar(O) ) ) ) 
#define lcdadr(O) (lcdr(lcar(lcdr(O) ) ) ) 
#define lcddar(O) (lcdr(lcdr(lcar(O) ) ) ) 
#define lcdddr(O) (lcdr(lcdr(lcdr(O) ) ) ) 
#define lcaaaar(O) (lcar(lcar(lcar(lcar(O) ) ) ) ) 
#define lcaaadr(O) (lcar(lcar(lcar(lcdr(O) ) ) ) ) 
#define lcaadar(O) (lcar(lcar(lcdr(lcar(O) ) ) ) ) 
#define lcaaddr(O) (lcar(lcar(lcdr(lcdr(O) ) ) ) ) 
#define lcadaar(O) (lcar(lcdr(lcar(lcar(O) ) ) ) ) 
#define lcadadr(O) (lcar(lcdr(lcar(lcdr(O) ) ) ) ) 
#define lcaddar(O) (lcar(lcdr(lcdr(lcar(O) ) ) ) ) 
#define lcadddr(O) (lcar(lcdr(lcdr(lcdr(O) ) ) ) ) 
#define lcdaaar(O) (lcdr(lcar(lcar(lcar(O) ) ) ) ) 
#define lcdaadr(O) (lcdr(lcar(lcar(lcdr(O) ) ) ) ) 
#define lcdadar(O) (lcdr(lcar(lcdr(lcar(O) ) ) ) ) 
#define lcdaddr(O) (lcdr(lcar(lcdr(lcdr(O) ) ) ) ) 
#define lcddaar(O) (lcdr(lcdr(lcar(lcar(O) ) ) ) ) 
#define lcddadr(O) (lcdr(lcdr(lcar(lcdr(O) ) ) ) ) 
#define lcdddar(O) (lcdr(lcdr(lcdr(lcar(O) ) ) ) ) 
#define lcddddr(O) (lcdr(lcdr(lcdr(lcdr(O) ) ) ) )  \

#define pointer(O) ((void*) lcar(O) ) 
#define pointer_datum(O) (lcdr(O) ) 
#define pointer_erase_m(O) (lcar_set_m((O) ,(cell) NULL) ) 
#define pointer_set_datum_m(O,D)  \
(lcdr_set_m((O) ,(cell) (D) ) ) 
#define pointer_set_m(O,D) (lcar_set_m((O) ,(cell) (D) ) )  \

#define segint_p(O) (segment_intern_p(O) ) 
#define segint_address(O) (segint_base(O) ->buffer) 
#define segint_base(O) ((Ointern*) (O) ) 
#define segint_header(O) ((long) 0) 
#define segint_length(O) ((long) segint_base(O) ->length) 
#define segint_set_length_m(O,V)  \
(segint_base(O) ->length= (V) ) 
#define segint_owner(O) (O) 
#define segint_stride(O) ((long) 1)  \

#define segbuf_base(O) ((Osegment*) pointer(O) ) 
#define segbuf_address(O) (segbuf_base(O) ->address) 
#define segbuf_header(O) (segbuf_base(O) ->header) 
#define segbuf_length(O) (segbuf_base(O) ->length) 
#define segbuf_next(O) (segbuf_base(O) ->next) 
#define segbuf_owner(O) (segbuf_base(O) ->owner) 
#define segbuf_prev(O) (segbuf_base(O) ->prev) 
#define segbuf_stride(O) (segbuf_base(O) ->stride?segbuf_base(O) ->stride:1)  \

#define segment_address(O) (segint_p(O) ?segint_address(O) :segbuf_address(O) ) 
#define segment_base(O) (segint_p(O) ?segint_base(O) :segbuf_base(O) ) 
#define segment_header(O) (segint_p(O) ?segint_header(O) :segbuf_header(O) ) 
#define segment_length(O) (segint_p(O) ?segint_length(O) :segbuf_length(O) ) 
#define segment_owner(O) (segint_p(O) ?segint_owner(O) :segbuf_owner(O) ) 
#define segment_stride(O) (segint_p(O) ?segint_stride(O) :segbuf_stride(O) )  \

#define segment_set_owner_m(O,N) do{ \
assert(pointer_p(O) ) ; \
segbuf_owner(O) = (N) ; \
}while(0) 
#define segment_alloc(H,L,S,A,F) segment_alloc_imp(NULL,(H) ,(L) ,(S) ,(A) ,(F) ) 
#define segment_new(H,L,S,A,F) segment_new_imp(Theap,(H) ,(L) ,(S) ,(A) , \
FORM_SEGMENT,(F) ) 
#define collected_datum(O) (lcar(O) ) 
#define collected_set_datum_m(O,V) (lcar_set_m((O) ,(V) ) ) 
#define atom_saved_p(O) (ATOM_TO_HEAP(O) ->pair==NULL) 
#define array_progress(O) (fix_value(pointer_datum(O) ) ) 
#define array_set_progress_m(O,V) (pointer_set_datum_m((O) ,fix(V) ) ) 
#define array_length(O) (segment_length(O) ) 
#define array_address(O) ((cell*) segment_address(O) ) 
#define array_new(L,F) ((L) ==0?Null_Array: \
array_new_imp((L) ,NIL,FORM_ARRAY,(F) ) ) 
#define KEYTABLE_MINLENGTH 8
#define KEYTABLE_MAXLENGTH (INT_MAX>>1)  \

#define keytable_free(O) (null_array_p(O) ?0: \
fix_value(array_ref((O) ,array_length(O) -1) ) ) 
#define keytable_free_p(O) (keytable_free(O) > 0) 
#define keytable_length(O) (null_array_p(O) ?(long) 0:array_length(O) -1) 
#define keytable_ref(O,I) (array_ref((O) ,(I) ) ) 
#define keytable_set_free_m(O,V) (array_set_m((O) ,array_length(O) -1,fix(V) ) ) 
#define SYMBOL_CHUNK 0x1000
#define SYMBOL_MAX INT_MAX
#define SYMBOL_BUFFER_MAX LONG_MAX
#define Symbol_Buffer_Length (segment_length(Symbol_Buffer) ) 
#define Symbol_Buffer_Base ((char*) segment_address(Symbol_Buffer) ) 
#define Symbol_Table_Length (keytable_length(Symbol_Table) ) 
#define Symbol_Table_ref(i) (keytable_ref(Symbol_Table,(i) ) )  \

#define symint_p(O) (symbol_intern_p(O) ) 
#define symint_length(O) (((Ointern*) (O) ) ->length) 
#define symint_buffer(O) (((Ointern*) (O) ) ->buffer) 
#define symint_hash(O) (hash_buffer(symint_buffer(O) , \
symint_length(O) ,NULL) )  \

#define symbuf_length(O) ((long) lcar(O) ) 
#define symbuf_set_length_m(O,V) (lcar_set_m((O) ,(V) ) ) 
#define symbuf_offset(O) ((long) lcdr(O) ) 
#define symbuf_set_offset_m(O,V) (lcdr_set_m((O) ,(V) ) ) 
#define symbuf_store(O) ((Osymbol*) (Symbol_Buffer_Base+symbuf_offset(O) ) ) 
#define symbuf_buffer(O) (symbuf_store(O) ->buffer) 
#define symbuf_hash(O) (symbuf_store(O) ->hash)  \

#define symbol_length(O) (symint_p(O) ?symint_length(O) :symbuf_length(O) ) 
#define symbol_buffer(O) (symint_p(O) ?symint_buffer(O) :symbuf_buffer(O) ) 
#define symbol_hash(O) (symint_p(O) ?symint_hash(O) :symbuf_hash(O) ) 
#define symbol_new_segment(O,F) (symbol_new_buffer(segment_address(O) , \
segment_length(O) ,(F) ) ) 
#define symbol_new_const(O) (symbol_new_buffer((O) ,0,NULL) ) 
#define dryad_datum(O) (lcar(O) ) 
#define dryad_link(O) (lcdr(O) ) 
#define dryad_sin(O) (lcadr(O) ) 
#define dryad_dex(O) (lcddr(O) ) 
#define dryad_sin_p(O) (!null_p(dryad_sin(O) ) ) 
#define dryad_dex_p(O) (!null_p(dryad_dex(O) ) ) 
#define dryad_set_sin_m(O,V) (lcar_set_m(lcdr(O) ,(V) ) ) 
#define dryad_set_dex_m(O,V) (lcdr_set_m(lcdr(O) ,(V) ) )  \

#define dryadic_p(O) (!special_p(O) && \
(form(O) &FORM_ROPE) ==FORM_ROPE) 
#define dlist_p(O) (dryadic_p(O) &&pair_p(dryad_link(O) ) ) 
#define treeish_p(O) (dryadic_p(O) &&!dlist_p(O) ) 
#define tree_p(O) (treeish_p(O) && \
(form(O) &FORM_TREE) ==FORM_TREE) 
#define plain_tree_p(O) (treeish_p(O) &&form_p((O) ,TREE) ) 
#define rope_p(O) (treeish_p(O) && \
(form(O) &FORM_TREE) ==FORM_ROPE) 
#define plain_rope_p(O) (treeish_p(O) &&form_p((O) ,ROPE) )  \

#define treeish_sin_threadable_p(O) (treeish_p(O) &&(form(O) &LTAG_TSIN) ) 
#define treeish_dex_threadable_p(O) (treeish_p(O) &&(form(O) &LTAG_TDEX) ) 
#define tree_sin_threadable_p(O) (tree_p(O) &&treeish_sin_threadable_p(O) ) 
#define tree_dex_threadable_p(O) (tree_p(O) &&treeish_dex_threadable_p(O) ) 
#define tree_threadable_p(O) (tree_sin_threadable_p(O) &&tree_dex_threadable_p(O) ) 
#define rope_sin_threadable_p(O) (rope_p(O) &&treeish_sin_threadable_p(O) ) 
#define rope_dex_threadable_p(O) (rope_p(O) &&treeish_dex_threadable_p(O) ) 
#define rope_threadable_p(O) (rope_sin_threadable_p(O) &&rope_dex_threadable_p(O) )  \

#define treeish_sin_has_thread_p(O) (treeish_sin_threadable_p(O) &&dryad_sin_p(O) && \
(form(dryad_link(O) ) &LTAG_TSIN) ) 
#define treeish_dex_has_thread_p(O) (treeish_dex_threadable_p(O) &&dryad_dex_p(O) && \
(form(dryad_link(O) ) &LTAG_TDEX) ) 
#define tree_sin_has_thread_p(O) (tree_p(O) &&treeish_sin_has_thread_p(O) ) 
#define tree_dex_has_thread_p(O) (tree_p(O) &&treeish_dex_has_thread_p(O) ) 
#define rope_sin_has_thread_p(O) (rope_p(O) &&treeish_sin_has_thread_p(O) ) 
#define rope_dex_has_thread_p(O) (rope_p(O) &&treeish_dex_has_thread_p(O) )  \

#define tree_thread_set_sin_thread_m(O) (TAG_SET_M(dryad_link(O) , \
form(dryad_link(O) |LTAG_TSIN) ) ) 
#define tree_thread_set_sin_live_m(O) (TAG_SET_M(dryad_link(O) , \
form(dryad_link(O) &~LTAG_TSIN) ) ) 
#define tree_thread_set_dex_thread_m(O) (TAG_SET_M(dryad_link(O) , \
form(dryad_link(O) |LTAG_TDEX) ) ) 
#define tree_thread_set_dex_live_m(O) (TAG_SET_M(dryad_link(O) , \
form(dryad_link(O) &~LTAG_TDEX) ) )  \

#define tree_thread_live_sin(O) (treeish_sin_has_thread_p(O) ?NIL:dryad_sin(O) ) 
#define tree_thread_live_dex(O) (treeish_dex_has_thread_p(O) ?NIL:dryad_dex(O) ) 
#define tree_thread_next_sin(O,F) (anytree_next_sin((O) ,(F) ) ) 
#define tree_thread_next_dex(O,F) (anytree_next_dex((O) ,(F) ) )  \

#define treeish_sinmost(O,F) treeish_edge_imp((O) ,true,(F) ) 
#define treeish_dexmost(O,F) treeish_edge_imp((O) ,false,(F) ) 
#define anytree_next_imp(IN,OTHER)  \
cell \
anytree_next_##IN(cell o, \
sigjmp_buf*failure)  \
{ \
cell r; \
 \
assert(dryadic_p(o) ) ; \
r= dryad_##IN(o) ; \
if(!treeish_##IN##_threadable_p(o) || \
!treeish_##IN##_has_thread_p(o) )  \
return r; \
return treeish_##OTHER##most(r,failure) ; \
}
#define dlist_datum(o) (dryad_datum(o) ) 
#define dlist_prev(o) (dryad_sin(o) ) 
#define dlist_next(o) (dryad_dex(o) ) 
#define dlist_set(DIRECTION,YIN,YANG)  \
void \
dlist_set_##DIRECTION##_m(cell hither, \
cell yon)  \
{ \
assert(dlist_p(hither) ) ; \
assert(dlist_p(yon) ) ; \
YIN##_set_m(dryad_link(hither) ,yon) ; \
YANG##_set_m(dryad_link(yon) ,hither) ; \
}
#define dlist_prepend_m(O,L) dlist_append_m(dlist_prev(O) ,(L) ) 
#define dlist_prepend_datum_m(O,D,F) dlist_append_datum_m(dlist_prev(O) ,(D) ,(F) ) 
#define RECORD_MAXLENGTH (INT_MAX>>1) 
#define record_next(O) (array_ref((O) ,0) ) 
#define record_next_p(O) (segment_p(record_next(O) ) ) 
#define record_id(O) (record_next_p(O) ?pointer_datum(record_next(O) ) : \
record_next(O) ) 
#define record_base(O) (record_next_p(O) ?segment_address(record_next(O) ) : \
(char*) NULL) 
#define record_offset(O) (record_next_p(O) ?1:0) 
#define record_cell(O,I) (array_ref((O) ,(I) +1) ) 
#define record_set_cell_m(O,I,D)  \
(array_set_m((O) ,(I) +1,(D) ) ) 
#define record_object(T,O,A) (((T) record_base(O) ) ->A) 
#define record_set_object_m(T,O,A,D)  \
(record_object((T) ,(O) ,(A) ) = (D) ) 
#define UCP_MAX 0x10ffff
#define UCP_SURROGATE_MIN 0xd800
#define UCP_SURROGATE_MAX 0xe000
#define UCP_NONBMP_MIN 0xfdd0
#define UCP_NONBMP_MAX 0xfdef
#define UCP_REPLACEMENT 0xfffd
#define UCP_REPLACEMENT_LENGTH 3
#define UCP_NONCHAR_MASK 0xfffe
#define utfio_noncharacter_p(C) (utfio_nonplane_p(C) ||utfio_nonrange_p(C) ) 
#define utfio_nonplane_p(C) (((C) ->value&UCP_NONCHAR_MASK) ==UCP_NONCHAR_MASK) 
#define utfio_nonrange_p(C) ((C) ->value>=UCP_NONBMP_MIN&& \
(C) ->value<=UCP_NONBMP_MAX) 
#define utfio_overlong_p(C) ((C) ->value<=UTFIO[(C) ->offset-1].max) 
#define utfio_surrogate_p(C) ((C) ->value>=UCP_SURROGATE_MIN&& \
(C) ->value<=UCP_SURROGATE_MAX) 
#define utfio_too_large_p(C) ((C) ->value> UCP_MAX) 
#define UCPVAL(V) (((V) &0x001fffff) ) 
#define UCPLEN(V) (((V) &0x00e00000) >>21) 
#define UCPFAIL(V) (((V) &0xff000000) >>24)  \

#define rune_raw(O) ((CELL_BITS>=32) ?(int32_t) lcar(O) : \
((((int32_t) lcar(O) &0xffff) <<16) |((int32_t) lcdr(O) &0xffff) ) ) 
#define rune_failure_p(O) (!!UCPFAIL(rune_raw(O) ) ) 
#define rune_failure(O) (UCPFAIL(rune_raw(O) ) ) 
#define rune_parsed(O) (UCPLEN(rune_raw(O) ) ) 
#define rune(O) (rune_failure_p(O) ?UCP_REPLACEMENT: \
UCPVAL(rune_raw(O) ) )  \

#define rune_new_value(V,F) (rune_new_utfio(utfio_write(V) ,(F) ) ) 
#define rope_segment(O) (dryad_datum(O) ) 
#define rope_base(O) ((Orope*) segment_address(rope_segment(O) ) ) 
#define rope_blength(O) ((long) segment_length(rope_segment(O) ) -1) 
#define rope_cplength(O) (rope_base(O) ->cplength) 
#define rope_glength(O) (rope_base(O) ->glength) 
#define rope_buffer(O) (rope_base(O) ->buffer) 
#define rope_first(O,F) (treeish_sinmost((O) ,(F) ) ) 
#define rope_last(O,F) (treeish_dexmost((O) ,(F) ) ) 
#define rope_next(O,F) (anytree_next_dex((O) ,(F) ) ) 
#define rope_prev(O,F) (anytree_next_sin((O) ,(F) ) ) 
#define rope_byte(O,B) (rope_buffer(O) [(B) ]) 
#define rope_node_new_empty(S,D,F) rope_node_new_length((S) ,(D) ,0,NIL,NIL,(F) ) 
#define rope_new_length(S,D,L,F) rope_node_new_length((S) ,(D) ,(L) ,NIL,NIL,(F) ) 
#define ROPE_ITER_TWINE 0
#define ROPE_ITER_LENGTH 1 \

#define rope_iter(O) ((Orope_iter*) record_base(O) ) 
#define rope_iter_twine(O) (record_cell((O) ,ROPE_ITER_TWINE) ) 
#define rope_iter_set_twine_m(O,D) (record_set_cell_m((O) ,ROPE_ITER_TWINE,(D) ) ) 
#define STACK_CHUNK 0x100
#define stack_clear(O) stack_pop((O) ,NULL) 
#define SO(O) stack_ref((O) ,NULL) 
#define SS(O,D) stack_set_m((O) ,(D) ,NULL) 
#define env_layer(O) (lcdr(O) ) 
#define env_previous(O) (lcar(O) ) 
#define env_replace_layer_m(O,E) (lcdr_set_m((O) ,(E) ) ) 
#define env_root_p(O) (environment_p(O) &&null_p(env_previous(O) ) ) 
#define env_empty(F) (env_new_imp(NIL,(F) ) ) 
#define env_look(H,N,F) env_search((H) ,(N) ,false,(F) ) 
#define LLF_NONE 0x00
#define LLF_HORIZONTAL 0x01
#define LLF_VERTICAL 0x02 \

#define LLF_BASE2 0x02
#define LLF_BASE8 0x08
#define LLF_BASE16 0x0a
#define LLF_BASE(O) flag2base(O)  \

#define LLF_COMPLEXI 0x01
#define LLF_COMPLEXJ 0x04
#define LLF_COMPLEXK 0x05
#define LLF_COMPLEX_P(O) ((O) &0x05) 
#define LLF_COMPLEXITY(O) (((O) &1) |(LLF_COMPLEX_P(O) >>1) )  \

#define LLF_IMAGINATE(O) (((O) &~2) |(((O) &2) <<1) )  \
 \

#define LLF_NEGATIVE 0x10
#define LLF_POSITIVE 0x20
#define LLF_SIGN 0x30 \

#define LLF_DOT 0x40
#define LLF_SLASH 0x80
#define LLF_RATIO 0xc0 \

#define LEXEME_TWINE 0
#define LEXEME_LENGTH 1 \

#define lexeme(O) ((Olexeme*) record_base(O) ) 
#define lexeme_twine(O) (record_cell((O) ,LEXEME_TWINE) ) 
#define lexeme_set_twine_m(O,D) (record_set_cell_m((O) ,LEXEME_TWINE,(D) ) ) 
#define lexeme_byte(O,I) (rope_byte(lexeme_twine(O) , \
lexeme(O) ->tboffset+(I) ) ) 
#define SYNTAX_DATUM 0
#define SYNTAX_NOTE 1
#define SYNTAX_START 2
#define SYNTAX_END 3
#define SYNTAX_VALID 4
#define SYNTAX_LENGTH 5 \

#define syntax_datum(O) (record_cell((O) ,SYNTAX_DATUM) ) 
#define syntax_end(O) (record_cell((O) ,SYNTAX_END) ) 
#define syntax_note(O) (record_cell((O) ,SYNTAX_NOTE) ) 
#define syntax_start(O) (record_cell((O) ,SYNTAX_START) ) 
#define syntax_valid(O) (record_cell((O) ,SYNTAX_VALID) )  \

#define syntax_new(D,S,E,F) syntax_new_imp((D) ,NIL,(S) ,(E) ,true,(F) ) 
#define syntax_invalid(D,S,E,F) syntax_new_imp((D) ,NIL,(S) ,(E) ,false,(F) ) 
#define Sym_APPLICATIVE (symbol_new_const("APPLICATIVE") ) 
#define Sym_COMBINE_APPLY (symbol_new_const("COMBINE-APPLY") ) 
#define Sym_COMBINE_BUILD (symbol_new_const("COMBINE-BUILD") ) 
#define Sym_COMBINE_DISPATCH (symbol_new_const("COMBINE-DISPATCH") ) 
#define Sym_COMBINE_FINISH (symbol_new_const("COMBINE-FINISH") ) 
#define Sym_COMBINE_OPERATE (symbol_new_const("COMBINE-OPERATE") ) 
#define Sym_CONDITIONAL (symbol_new_const("CONDITIONAL") ) 
#define Sym_DEFINITION (symbol_new_const("DEFINITION") ) 
#define Sym_EVALUATE_DISPATCH (symbol_new_const("EVALUATE-DISPATCH") ) 
#define Sym_SAVE_AND_EVALUATE (symbol_new_const("SAVE-ENVIRONMENT-AND-EVALUATE") ) 
#define Sym_ENVIRONMENT_P (symbol_new_const("ENVIRONMENT?") ) 
#define Sym_ENVIRONMENT_M (symbol_new_const("ENVIRONMENT!") ) 
#define Sym_EVALUATE (symbol_new_const("EVALUATE") ) 
#define Sym_OPERATIVE (symbol_new_const("OPERATIVE") ) 
#define note(O) (lcar(O) ) 
#define note_pair(O) (lcdr(O) ) 
#define note_car(O) (lcar(note_pair(O) ) ) 
#define note_cdr(O) (lcdr(note_pair(O) ) ) 
#define note_set_car_m(O,V) (lcar_set_m(note_pair(O) ,(V) ) ) 
#define note_set_cdr_m(O,V) (lcdr_set_m(note_pair(O) ,(V) ) ) 
#define closure_formals(O) (lcar(O) ) 
#define closure_environment(O) (lcadr(O) ) 
#define closure_body(O) (lcaddr(O) ) 
#define primitive(O) (fix_value(lcar(O) ) ) 
#define primitive_label(O) (lcdr(O) ) 
#define primitive_base(O) (&Iprimitive[primitive(O) ]) 
#define primitive_applicative_p(O) (primitive_p(O) &&primitive_base(O) ->applicative) 
#define primitive_operative_p(O) (primitive_p(O) &&!primitive_base(O) ->applicative) 
#define LEXAR_STARTER 0
#define LEXAR_ITERATOR 1
#define LEXAR_PEEKED_TWINE 2
#define LEXAR_PEEKED_RUNE 3
#define LEXAR_BACKPUT_TWINE 4
#define LEXAR_BACKPUT_RUNE 5
#define LEXAR_LENGTH 6 \

#define lexar(O) ((Olexical_analyser*) record_base(O) ) 
#define lexar_starter(O) (record_cell((O) ,LEXAR_STARTER) ) 
#define lexar_iterator(O) (record_cell((O) ,LEXAR_ITERATOR) ) 
#define lexar_peeked_rune(O) (record_cell((O) ,LEXAR_PEEKED_RUNE) ) 
#define lexar_peeked_twine(O) (record_cell((O) ,LEXAR_PEEKED_TWINE) ) 
#define lexar_backput_rune(O) (record_cell((O) ,LEXAR_BACKPUT_RUNE) ) 
#define lexar_backput_twine(O) (record_cell((O) ,LEXAR_BACKPUT_TWINE) )  \

#define lexar_set_starter_m(O,D) (record_set_cell_m((O) ,LEXAR_STARTER,(D) ) ) 
#define lexar_set_iterator_m(O,D) (record_set_cell_m((O) ,LEXAR_ITERATOR,(D) ) ) 
#define lexar_set_peeked_rune_m(O,D)  \
(record_set_cell_m((O) ,LEXAR_PEEKED_RUNE,(D) ) ) 
#define lexar_set_peeked_twine_m(O,D)  \
(record_set_cell_m((O) ,LEXAR_PEEKED_TWINE,(D) ) ) 
#define lexar_set_backput_rune_m(O,D)  \
(record_set_cell_m((O) ,LEXAR_BACKPUT_RUNE,(D) ) ) 
#define lexar_set_backput_twine_m(O,D)  \
(record_set_cell_m((O) ,LEXAR_BACKPUT_TWINE,(D) ) ) 
#define lexar_reset(L,R) do{ \
lexar_set_starter_m((L) ,rope_iter_twine((R) ) ) ; \
lexar(L) ->tbstart= rope_iter(R) ->tboffset; \
lexar(L) ->cpstart= rope_iter(R) ->cpoffset; \
}while(0) 
#define RIS(O,V) (rune(O) ==(V) ) 
#define CIS(O,V) (lexeme(O) ->cat==(V) )  \

#define lexar_space_p(O) (!rune_failure_p(O) && \
(RIS((O) ,' ') ||RIS((O) ,'\t') || \
RIS((O) ,'\r') ||RIS((O) ,'\n') ) ) 
#define lexar_opening_p(O) (!rune_failure_p(O) && \
(RIS((O) ,'(') ||RIS((O) ,'{') ||RIS((O) ,'[') ) ) 
#define lexar_closing_p(O) (!rune_failure_p(O) && \
(RIS((O) ,')') ||RIS((O) ,'}') ||RIS((O) ,']') ) ) 
#define lexar_terminator_p(O) (eof_p(O) || \
lexar_space_p(O) ||lexar_opening_p(O) ||lexar_closing_p(O) )  \

#define lexeme_terminator_p(O) (CIS((O) ,LEXICAT_END) || \
CIS((O) ,LEXICAT_OPEN) ||CIS((O) ,LEXICAT_CLOSE) || \
CIS((O) ,LEXICAT_SPACE) ) 
#define lexar_another(V,I,T,A,L,R,F) do{ \
 \
 \
(V) = lexar_peek((I) ,(F) ) ; \
if(eof_p(V) )  \
goto L; \
else if(!(A) &&rune_failure_p(V) )  \
return lexar_append((I) ,(R) ,LEXICAT_INVALID,LLF_NONE,(F) ) ; \
else if(T)  \
(V) = lexar_take((I) ,(F) ) ; \
}while(0) 
#define lexar_detect_octal(V,I,C,R,F) { \
lexar_another((V) ,(I) ,true,true,LEXAR_premature_eof,(R) ,(F) ) ; \
if(!rune_failure_p(V) && \
rune(V) >='0'&&rune(V) <='7') { \
lexar_take((I) ,(F) ) ; \
continue; \
} \
(C) = LEXICAT_INVALID; \
break; \
} \

#define lexar_detect_hexadecimal(V,I,C,R,F) { \
int32_t v; \
lexar_another((V) ,(I) ,true,true,LEXAR_premature_eof,(R) ,(F) ) ; \
v= rune(V) ; \
if(!rune_failure_p(V) &&((v>='0'&&v<='9') || \
(v>='a'&&v<='f') ||(v>='A'&&v<='F') ) ) { \
lexar_take((I) ,(F) ) ; \
continue; \
} \
(C) = LEXICAT_INVALID; \
break; \
}
#define UCP_INFINITY 0x211e
#define UCP_NAN_0 0x2116
#define UCP_NAN_1 0x20e0
#define CANNOT -1
#define CAN 0
#define MUST 1 \

#define parse_fail(S,E,L,F) do{ \
cell _x= cons(fix((E) ) ,(L) ,(F) ) ; \
SS((S) ,cons(_x,SO(S) ,(F) ) ) ; \
(L) = lcdr(lcar(SO(S) ) ) ; \
}while(0) 
#define hexscii_to_int(O) (((O) >='a') ?(O) -'a': \
((O) >='A') ?(O) -'A':(O) -'0') 
#define int_to_hexscii(O,C) ((O) <10?(O) +'0':((C) ?(O) +'A':(O) +'a') ) 
#define ACC Accumulator
#define ARGS Arguments
#define CLINK Control_Link
#define ENV Environment
#define EXPR Expression
#define evaluate_desyntax(O) (syntax_p(O) ?syntax_datum(O) :(O) ) 
#define evaluate_incompatible(L,F) do{ \
lprint("incompatibility at line %d\n",(L) ) ; \
siglongjmp(*(F) ,LERR_INCOMPATIBLE) ; \
}while(0) 
#define LOG(cmd) cmd
#define DONTLOG(cmd) do{printf("%s\n",#cmd) ;cmd;}while(0)  \

#define Sym_VOV_ARGS (symbol_new_const("vov/args") ) 
#define Sym_VOV_ARGUMENTS (symbol_new_const("vov/arguments") ) 
#define Sym_VOV_CONT (symbol_new_const("vov/cont") ) 
#define Sym_VOV_CONTINUATION (symbol_new_const("vov/continuation") ) 
#define Sym_VOV_ENV (symbol_new_const("vov/env") ) 
#define Sym_VOV_ENVIRONMENT (symbol_new_const("vov/environment") )  \

#define save_vov_informal(O,S) do{ \
if(!null_p(SO(S) ) )  \
evaluate_incompatible(__LINE__,failure) ; \
else \
LOG(SS((S) ,(O) ) ) ; \
}while(0) 
#define primitive_predicate(O) do{ \
ACC= lcar(ARGS) ; \
ARGS= lcdr(ARGS) ; \
assert(null_p(ARGS) ) ; \
ACC= predicate(O(ACC) ) ; \
}while(0) ;break
#define validated_argument(VAR,ARGS,NULLABLE,PREDICATE,FAILURE) do{ \
(VAR) = lcar(ARGS) ; \
(ARGS) = lcdr(ARGS) ; \
if((!(NULLABLE) &&null_p(VAR) ) ||!PREDICATE(VAR) )  \
evaluate_incompatible(__LINE__,(FAILURE) ) ; \
}while(0)  \

#define serial_printable_p(O) ((O) >=' '&&(O) <0x7f) 
#define SERIAL_SILENT 0
#define SERIAL_HUMAN 1
#define SERIAL_ROUND 2
#define SERIAL_DETAIL 3
#define serial_append(B,C,L,F) do{ \
if(LDEBUG_P&&null_p(B) )  \
for(int _i= 0;_i<(L) ;_i++)  \
lput((C) [_i]) ; \
else \
serial_append_imp((B) ,(C) ,(L) ,(F) ) ; \
}while(0) 
#define WARN() fprintf(stderr,"WARNING: You probably don't want to do that.\n") ;

#line 104 "lossless.w"

/*6:*/
#line 141 "lossless.w"

typedef intptr_t cell;
typedef uintptr_t digit;

#if SIZE_MAX <= 0xfffful
/*10:*/
#line 243 "lossless.w"

#define CELL_BITS  16
#define CELL_BYTES 2
#define CELL_SHIFT 2
#define WIDE_BITS  32
#define WIDE_BYTES 4
#define FIX_MIN    (-0x7f - 1) 
#define FIX_MAX    0x7f
#define FIX_MASK   0xff
#define FIX_SHIFT  8
#define FIX_BASE2  8
#define FIX_BASE8  3
#define FIX_BASE10 3
#define FIX_BASE16 2
typedef union{
struct{
cell low;
cell high;
};
int64_t value;
}wide;
typedef int8_t fixed;
typedef int8_t half;

/*:10*/
#line 146 "lossless.w"

#elif SIZE_MAX <= 0xfffffffful
/*9:*/
#line 216 "lossless.w"

#define CELL_BITS  32
#define CELL_BYTES 4
#define CELL_SHIFT 3
#define WIDE_BITS  64
#define WIDE_BYTES 8
#define FIX_MIN    (-0x7fffffl - 1) 
#define FIX_MAX    0x7fffffl
#define FIX_MASK   0xffffffl
#define FIX_SHIFT  8
#define FIX_BASE2  24
#define FIX_BASE8  8
#define FIX_BASE10 8
#define FIX_BASE16 6
typedef union{
struct{
cell low;
cell high;
};
int64_t value;
}wide;
typedef int32_t fixed;
typedef int16_t half;

/*:9*/
#line 148 "lossless.w"

#elif SIZE_MAX <= 0xfffffffffffffffful
/*8:*/
#line 186 "lossless.w"

#define CELL_BITS  64
#define CELL_BYTES 8
#define CELL_SHIFT 4
#define WIDE_BITS  128
#define WIDE_BYTES 16
#define FIX_MIN    (-0x7fffffffll - 1) 
#define FIX_MAX    0x7fffffffll
#define FIX_MASK   0xffffffffll
#define FIX_SHIFT  32
#define FIX_BASE2  32
#define FIX_BASE8  11
#define FIX_BASE10 10
#define FIX_BASE16 8
typedef union{
struct{
cell low;
cell high;
};
struct{
char b[16];
}value;
}wide;
typedef int32_t fixed;
typedef int32_t half;

/*:8*/
#line 150 "lossless.w"

#else
#error Tiny computer.
#endif


/*:6*//*7:*/
#line 160 "lossless.w"

#define CELL_MASK (~(WIDE_BYTES - 1))

#define BYTE_BITS    8
#define BYTE_BYTES   1
#define BYTE         0xff
#define TAG_BYTES    1

#define DIGIT_MAX    UINTPTR_MAX
#define HALF_MIN     (INTPTR_MIN / 2)
#define HALF_MAX     (INTPTR_MAX / 2)
#define INTERN_BYTES (WIDE_BYTES - 1)


typedef intptr_t cell;
typedef uintptr_t digit;
typedef struct{
char buffer[INTERN_BYTES];
unsigned char length;
}Ointern;

/*:7*//*13:*/
#line 295 "lossless.w"

typedef enum{
LERR_NONE,
LERR_AMBIGUOUS,
LERR_DOUBLE_TAIL,
LERR_EMPTY_TAIL,
LERR_EOF,
LERR_EXISTS,
LERR_HEAVY_TAIL,
LERR_IMPROPER,
LERR_INCOMPATIBLE,
LERR_INTERNAL,
LERR_INTERRUPT,
LERR_LIMIT,
LERR_LISTLESS_TAIL,
LERR_MISMATCH,
LERR_MISSING,
LERR_NONCHARACTER,
LERR_OOM,
LERR_OVERFLOW,
LERR_SYNTAX,
LERR_UNCLOSED_OPEN,
LERR_UNCOMBINABLE,
LERR_UNDERFLOW,
LERR_UNIMPLEMENTED,
LERR_UNOPENED_CLOSE,
LERR_UNPRINTABLE,
LERR_UNSCANNABLE,
LERR_LENGTH
}Verror;

/*:13*//*14:*/
#line 330 "lossless.w"

typedef struct{
char*message;
}Oerror;

/*:14*//*25:*/
#line 610 "lossless.w"

typedef unsigned char Otag;
typedef struct{
cell sin,dex;
}Oatom;

/*:25*//*31:*/
#line 802 "lossless.w"

struct Oheap{
Oatom*free;
struct Oheap*next,*pair;
Otag tag[];
};
typedef struct Oheap Oheap;

/*:31*//*44:*/
#line 1224 "lossless.w"

struct Osegment{
struct Osegment*next,*prev;
half length,stride;
cell owner;

char address[];

};
typedef struct Osegment Osegment;

/*:44*//*53:*/
#line 1474 "lossless.w"

enum{
LGCR_TMPSIN,LGCR_TMPDEX,LGCR_TMPIER,
LGCR_NULL,
LGCR_SYMBUFFER,LGCR_SYMTABLE,
LGCR_STACK,
LGCR_PROTECT_0,LGCR_PROTECT_1,LGCR_PROTECT_2,LGCR_PROTECT_3,
LGCR_EXPRESSION,LGCR_ENVIRONMENT,LGCR_ACCUMULATOR,LGCR_ARGUMENTS,
LGCR_CLINK,
LGCR_OPERATORS,
LGCR_USER,
LGCR_COUNT
};

/*:53*//*84:*/
#line 2032 "lossless.w"

typedef uint32_t Vhash;

/*:84*//*97:*/
#line 2279 "lossless.w"

typedef struct{
Vhash hash;
char buffer[];
}Osymbol;

typedef struct{
char*buf;
int length;
}Osymbol_compare;

/*:97*//*125:*/
#line 2894 "lossless.w"

typedef enum{
UTFIO_COMPLETE,
UTFIO_INVALID,
UTFIO_BAD_CONTINUATION,

UTFIO_BAD_STARTER,

UTFIO_OVERLONG,
UTFIO_SURROGATE,
UTFIO_PROGRESS,

UTFIO_EOF
}Vutfio_parse;

/*:125*//*126:*/
#line 2930 "lossless.w"

typedef struct{
int32_t value;
char offset,remaining;
char buf[4];
Vutfio_parse status;
}Outfio;

/*:126*//*134:*/
#line 3124 "lossless.w"

typedef struct{
long cplength;
long glength;
char buffer[];
}Orope;

/*:134*//*141:*/
#line 3261 "lossless.w"

typedef struct{
int bvalue;
long tboffset;
long boffset;
long cpoffset;
Outfio cp;
}Orope_iter;

/*:141*//*178:*/
#line 3815 "lossless.w"

typedef enum{
LEXICAT_NONE,
LEXICAT_CLOSE,
LEXICAT_CONSTANT,
LEXICAT_CURIOUS,
LEXICAT_DELIMITER,
LEXICAT_DOT,
LEXICAT_END,
LEXICAT_ESCAPED_STRING,
LEXICAT_ESCAPED_SYMBOL,
LEXICAT_NUMBER,
LEXICAT_OPEN,
LEXICAT_RAW_STRING,
LEXICAT_RAW_SYMBOL,
LEXICAT_RECURSE_HERE,
LEXICAT_RECURSE_IS,
LEXICAT_SPACE,
LEXICAT_SYMBOL,
LEXICAT_INVALID
}Vlexicat;

/*:178*//*179:*/
#line 3848 "lossless.w"

typedef struct{
long tboffset;
long cpstart;
long blength,cplength;
char flags;
Vlexicat cat;
}Olexeme;

/*:179*//*186:*/
#line 4083 "lossless.w"

typedef enum{
/*274:*/
#line 6424 "lossless.w"

PRIMITIVE_BREAK,
PRIMITIVE_CAR,
PRIMITIVE_CDR,
PRIMITIVE_CONS,
PRIMITIVE_CURRENT_ENVIRONMENT,
PRIMITIVE_DEFINE_M,
PRIMITIVE_DO,
PRIMITIVE_DUMP,
PRIMITIVE_EVAL,
PRIMITIVE_IF,
PRIMITIVE_LAMBDA,
PRIMITIVE_NULL_P,
PRIMITIVE_PAIR_P,
PRIMITIVE_ROOT_ENVIRONMENT,
PRIMITIVE_SET_M,
PRIMITIVE_VOV,

/*:274*//*287:*/
#line 6663 "lossless.w"

PRIMITIVE_NEW_TREE_PLAIN_NODE,
PRIMITIVE_NEW_TREE_BIWARD_NODE,
PRIMITIVE_NEW_TREE_SINWARD_NODE,
PRIMITIVE_NEW_TREE_DEXWARD_NODE,
PRIMITIVE_TREE_SIN_HAS_THREAD_P,
PRIMITIVE_TREE_DEX_HAS_THREAD_P,
PRIMITIVE_TREE_DEX_IS_LIVE_P,
PRIMITIVE_TREE_SIN_IS_LIVE_P,
PRIMITIVE_TREE_P,
PRIMITIVE_TREE_PLAIN_P,
PRIMITIVE_TREE_RETHREAD_M,
PRIMITIVE_TREE_SIN_THREADABLE_P,
PRIMITIVE_TREE_DEX_THREADABLE_P,
PRIMITIVE_TREE_DATUM,

PRIMITIVE_NEW_ROPE_PLAIN_NODE,
PRIMITIVE_ROPE_P,
PRIMITIVE_ROPE_PLAIN_P,
PRIMITIVE_ROPE_SIN_THREADABLE_P,
PRIMITIVE_ROPE_DEX_THREADABLE_P,
PRIMITIVE_ROPE_SEGMENT,

/*:287*/
#line 4085 "lossless.w"

PRIMITIVE_LENGTH
}Vprimitive;

typedef struct{
char*label;
cell box;
bool applicative;
char min,max;
}Oprimitive;


#if 0 

[PRIMITIVE_FOO]= {&Sym_FOO,NIL,...},
shared Osegment Sym_FOO= {.address= "foo"};
#endif

/*:186*//*190:*/
#line 4183 "lossless.w"

typedef struct{
long tbstart;
long blength;
long cpstart;
long cplength;
}Olexical_analyser;

/*:190*/
#line 105 "lossless.w"

/*21:*/
#line 445 "lossless.w"

void*mem_alloc(void*,size_t,size_t,sigjmp_buf*);

/*:21*//*29:*/
#line 735 "lossless.w"

cell fix(intmax_t);

/*:29*//*34:*/
#line 829 "lossless.w"

cell lcar(cell);
cell lcdr(cell);
Otag ltag(cell);
void lcar_set_m(cell,cell);
void lcdr_set_m(cell,cell);
void heap_init_sweeping(Oheap*,Oheap*);
void heap_init_compacting(Oheap*,Oheap*,Oheap*);
Oheap*heap_enlarge(Oheap*,sigjmp_buf*);
cell heap_alloc(Oheap*,sigjmp_buf*);
cell atom(Oheap*,cell,cell,Otag,sigjmp_buf*);

/*:34*//*46:*/
#line 1244 "lossless.w"

Osegment*segment_alloc_imp(Osegment*,long,long,long,long,sigjmp_buf*);
cell segment_init(Osegment*,cell);
cell segment_new_imp(Oheap*,long,long,long,long,Otag,sigjmp_buf*);
void segment_release_imp(Osegment*,bool);
void segment_release_m(cell,bool);
cell segment_resize_m(cell,long,long,sigjmp_buf*);

/*:46*//*56:*/
#line 1531 "lossless.w"

size_t gc_compacting(Oheap*,bool);
void gc_disown_segments(Oheap*);
cell gc_mark(Oheap*,cell,bool,cell*,size_t*);
size_t gc_reclaim_heap(Oheap*);
void gc_release_segments(Oheap*);
size_t gc_sweeping(Oheap*,bool);

/*:56*//*78:*/
#line 1896 "lossless.w"

cell array_new_imp(long,cell,Otag,sigjmp_buf*);
cell array_grow(cell,long,cell,sigjmp_buf*);
cell array_grow_m(cell,long,cell,sigjmp_buf*);
cell array_ref(cell,long);
void array_set_m(cell,long,cell);

/*:78*//*85:*/
#line 2035 "lossless.w"

Vhash hash_cstr(char*,long*,sigjmp_buf*);
Vhash hash_buffer(char*,long,sigjmp_buf*);

/*:85*//*88:*/
#line 2089 "lossless.w"

cell keytable_new(long,sigjmp_buf*);
cell keytable_enlarge_m(cell,Vhash(*)(cell,sigjmp_buf*),sigjmp_buf*);
void keytable_remove_m(cell,long);
void keytable_save_m(cell,long,cell);
int keytable_search(cell,Vhash,int(*)(cell,void*,sigjmp_buf*),void*,sigjmp_buf*);

/*:88*//*96:*/
#line 2255 "lossless.w"

int symbol_table_cmp(cell,void*,sigjmp_buf*);
long symbol_table_search(Vhash,Osymbol_compare,sigjmp_buf*);
Vhash symbol_table_rehash(cell s,sigjmp_buf*);
cell symbol_new_buffer(char*,long,sigjmp_buf*);
cell symbol_new_imp(Vhash,char*,long,sigjmp_buf*);

/*:96*//*107:*/
#line 2514 "lossless.w"

cell anytree_next_sin(cell,sigjmp_buf*);
cell anytree_next_dex(cell,sigjmp_buf*);
cell dryad_node_new(bool,bool,bool,cell,cell,cell,sigjmp_buf*);
cell treeish_clone(cell,sigjmp_buf*failure);
cell treeish_edge_imp(cell,bool,sigjmp_buf*);

/*:107*//*111:*/
#line 2601 "lossless.w"

void treeish_rethread_imp(cell,cell,Otag,cell);
cell treeish_rethread_m(cell,bool,bool,sigjmp_buf*);

/*:111*//*114:*/
#line 2688 "lossless.w"

cell dlist_new(cell,sigjmp_buf*);
cell dlist_append_datum_m(cell,cell,sigjmp_buf*);
cell dlist_append_m(cell,cell);
cell dlist_clone(cell,sigjmp_buf*);
cell dlist_insert_datum_imp(cell,cell,bool,sigjmp_buf*);
cell dlist_insert_imp(cell,cell,bool,sigjmp_buf*);
cell dlist_remove_m(cell);
void dlist_set_next_m(cell,cell);
void dlist_set_prev_m(cell,cell);

/*:114*//*121:*/
#line 2830 "lossless.w"

cell record_new(cell,int,int,sigjmp_buf*);

/*:121*//*127:*/
#line 2938 "lossless.w"

Vutfio_parse utfio_read(Outfio*,char);
Vutfio_parse utfio_reread(Outfio*,char);
Outfio utfio_scan_start(void);
Outfio utfio_write(int32_t);

/*:127*//*132:*/
#line 3065 "lossless.w"

cell rune_new_utfio(Outfio,sigjmp_buf*);

/*:132*//*135:*/
#line 3131 "lossless.w"

cell rope_node_new_clone(bool,bool,cell,cell,cell,sigjmp_buf*);
cell rope_node_new_length(bool,bool,long,cell,cell,sigjmp_buf*);
cell rope_new_ascii(bool,bool,char*,long,sigjmp_buf*);
cell rope_new_buffer(bool,bool,const char*,long,sigjmp_buf*);
cell rope_new_utfo(bool,bool,char*,long,sigjmp_buf*);

/*:135*//*142:*/
#line 3270 "lossless.w"

cell rope_iterate_start(cell,long,sigjmp_buf*);
int rope_iterate_next_byte(cell,sigjmp_buf*);
cell rope_iterate_next_utfo(cell,sigjmp_buf*);

/*:142*//*147:*/
#line 3372 "lossless.w"

void stack_push(cell,sigjmp_buf*);
cell stack_pop(long,sigjmp_buf*);
cell stack_ref(long,sigjmp_buf*);
void stack_set_m(long,cell,sigjmp_buf*);
cell stack_ref_abs(long,sigjmp_buf*);
void stack_reserve(int,sigjmp_buf*);
void stack_protect(int,...);

/*:147*//*161:*/
#line 3535 "lossless.w"

Vhash env_rehash(cell,sigjmp_buf*);
void env_clear(cell,cell,sigjmp_buf*);
cell env_define(cell,cell,cell,sigjmp_buf*);
cell env_extend(cell,sigjmp_buf*);
cell env_here(cell,cell,sigjmp_buf*);
int env_match(cell,void*,sigjmp_buf*);
cell env_new_imp(cell,sigjmp_buf*);
cell env_search(cell,cell,bool,sigjmp_buf*);
cell env_set(cell,cell,cell,sigjmp_buf*);
cell env_set_imp(cell,cell,cell,bool,sigjmp_buf*);
cell env_unset(cell,cell,sigjmp_buf*);

/*:161*//*184:*/
#line 4030 "lossless.w"

cell closure_new(bool,cell,cell,cell,sigjmp_buf*);

/*:184*//*191:*/
#line 4191 "lossless.w"

cell lexar_append(int,int,Vlexicat,int,sigjmp_buf*);
cell lexar_clone(cell,sigjmp_buf*);
cell lexar_peek(int,sigjmp_buf*);
void lexar_putback(int);
cell lexar_start(cell,sigjmp_buf*);
cell lexar_take(int,sigjmp_buf*);
cell lex_rope(cell,sigjmp_buf*);
cell lexar_token(int,int,sigjmp_buf*);

/*:191*//*228:*/
#line 5195 "lossless.w"

cell parse(cell,bool*,sigjmp_buf*);
cell transform_lexeme_segment(cell,long,long,bool,int,bool*,
sigjmp_buf*);
char parse_ascii_hex(cell,sigjmp_buf*);

/*:228*//*248:*/
#line 5789 "lossless.w"

void evaluate(cell,sigjmp_buf*);
void evaluate_program(cell,sigjmp_buf*);
void combine(sigjmp_buf*);
void validate_formals(bool,sigjmp_buf*);
void validate_arguments(sigjmp_buf*);
void validate_operative(sigjmp_buf*);
void validate_primitive(sigjmp_buf*);

/*:248*//*281:*/
#line 6572 "lossless.w"

void breakpoint(void);

/*:281*//*295:*/
#line 6854 "lossless.w"

void gc_serial(cell,cell);
void serial(cell,int,int,cell,cell*,sigjmp_buf*);
void serial_append_imp(cell,char*,int,sigjmp_buf*);
int serial_cycle(cell,cell);
char*serial_deduplicate(cell,int,cell,cell,sigjmp_buf*);
void serial_escape(char*,int,cell,sigjmp_buf*);
void serial_imp(cell,int,int,bool,cell,cell,sigjmp_buf*);
void serial_rope(cell,int,int,cell,cell,sigjmp_buf*);

/*:295*//*320:*/
#line 7504 "lossless.w"

int high_bit(digit);

/*:320*//*331:*/
#line 7716 "lossless.w"

cell lapi_Accumulator(cell);
cell lapi_User_Register(cell);

/*:331*//*335:*/
#line 7781 "lossless.w"

void mem_init(void);
int lprint(char*,...);
int lput(int);

/*:335*/
#line 106 "lossless.w"

/*15:*/
#line 337 "lossless.w"

Oerror Ierror[LERR_LENGTH]= {
[LERR_AMBIGUOUS]= {"ambiguous-syntax"},
[LERR_EXISTS]= {"binding-conflict"},
[LERR_DOUBLE_TAIL]= {"double-tail"},
[LERR_EOF]= {"end-of-file"},
[LERR_IMPROPER]= {"improper-list"},
[LERR_INCOMPATIBLE]= {"incompatible-operand"},
[LERR_INTERRUPT]= {"interrupted"},
[LERR_INTERNAL]= {"lossless-error"},
[LERR_MISMATCH]= {"mismatched-brackets"},
[LERR_MISSING]= {"missing"},
[LERR_NONCHARACTER]= {"noncharacter"},
[LERR_NONE]= {"no-error"},
[LERR_LISTLESS_TAIL]= {"non-list-tail"},
[LERR_OOM]= {"out-of-memory"},
[LERR_OVERFLOW]= {"overflow"},
[LERR_LIMIT]= {"software-limit"},
[LERR_SYNTAX]= {"syntax-error"},
[LERR_HEAVY_TAIL]= {"tail-mid-list"},
[LERR_UNCLOSED_OPEN]= {"unclosed-brackets"},
[LERR_UNCOMBINABLE]= {"uncombinable"},
[LERR_UNDERFLOW]= {"underflow"},
[LERR_UNIMPLEMENTED]= {"unimplemented"},
[LERR_UNOPENED_CLOSE]= {"unopened-brackets"},
[LERR_UNPRINTABLE]= {"unprintable"},
[LERR_UNSCANNABLE]= {"unscannable-lexeme"},
[LERR_EMPTY_TAIL]= {"unterminated-tail"},
};

/*:15*//*19:*/
#line 426 "lossless.w"

unique bool Interrupt= false;

/*:19*//*32:*/
#line 817 "lossless.w"

shared Oheap*Sheap= NULL;
unique Oheap*Theap= NULL;

/*:32*//*40:*/
#line 1051 "lossless.w"

unique cell Tmp_SIN= NIL;
unique cell Tmp_DEX= NIL;
unique cell Tmp_ier= NIL;

/*:40*//*45:*/
#line 1241 "lossless.w"

shared Osegment*Allocations= NULL;

/*:45*//*54:*/
#line 1492 "lossless.w"

unique cell*Registers[LGCR_COUNT];
shared cell User_Register= NIL;

/*:54*//*75:*/
#line 1882 "lossless.w"

shared cell Null_Array= NIL;

/*:75*//*94:*/
#line 2244 "lossless.w"

shared cell Symbol_Buffer= NIL;
shared cell Symbol_Table= NIL;
shared int Symbol_Buffer_Free= 0,Symbol_Table_Free= 0;

/*:94*//*124:*/
#line 2877 "lossless.w"

struct{
char size;
uint8_t data;
uint8_t lead;
int32_t max;
}UTFIO[]= {
{6,0x3f,0x80,0x000000},
{7,0x7f,0x00,0x00007f},
{5,0x1f,0xc0,0x0007ff},
{4,0x0f,0xe0,0x00ffff},
{3,0x07,0xf0,0x10ffff},
};

/*:124*//*148:*/
#line 3381 "lossless.w"

unique cell Stack= NIL;
unique long StackP= -1;
unique cell Stack_Tmp= NIL;

/*:148*//*158:*/
#line 3496 "lossless.w"

unique cell Protect[4];

/*:158*//*187:*/
#line 4109 "lossless.w"

Oprimitive Iprimitive[]= {
/*275:*/
#line 6442 "lossless.w"

[PRIMITIVE_BREAK]= {"break",NIL,false,-1,0,},
[PRIMITIVE_CURRENT_ENVIRONMENT]= {"current-environment",
NIL,false,-1,0,},
[PRIMITIVE_DO]= {"do",NIL,false,0,0,},
[PRIMITIVE_DEFINE_M]= {"define!",NIL,false,0,0,},
[PRIMITIVE_IF]= {"if",NIL,false,-1,3,},
[PRIMITIVE_LAMBDA]= {"lambda",NIL,false,0,0,},
[PRIMITIVE_ROOT_ENVIRONMENT]= {"root-environment",
NIL,false,-1,0,},
[PRIMITIVE_SET_M]= {"set!",NIL,false,0,0,},
[PRIMITIVE_VOV]= {"vov",NIL,false,0,0,},

[PRIMITIVE_CAR]= {"car",NIL,true,1,1,},
[PRIMITIVE_CDR]= {"cdr",NIL,true,1,1,},
[PRIMITIVE_CONS]= {"cons",NIL,true,2,2,},
[PRIMITIVE_DUMP]= {"dump",NIL,true,1,1,},
[PRIMITIVE_EVAL]= {"eval",NIL,true,1,2,},
[PRIMITIVE_NULL_P]= {"null?",NIL,true,1,1,},
[PRIMITIVE_PAIR_P]= {"pair?",NIL,true,1,1,},

/*:275*//*288:*/
#line 6686 "lossless.w"

[PRIMITIVE_NEW_TREE_PLAIN_NODE]= {"new-tree%plain-node",
NIL,true,3,3,},
[PRIMITIVE_NEW_TREE_BIWARD_NODE]= {"new-tree%bi-threadable-node",
NIL,true,3,3,},
[PRIMITIVE_NEW_TREE_DEXWARD_NODE]= {"new-tree%sin-threadable-node",
NIL,true,3,3,},
[PRIMITIVE_NEW_TREE_SINWARD_NODE]= {"new-tree%dex-threadable-node",
NIL,true,3,3,},
[PRIMITIVE_TREE_SIN_HAS_THREAD_P]= {"tree/sin-has-thread?",
NIL,true,1,1,},
[PRIMITIVE_TREE_DEX_HAS_THREAD_P]= {"tree/dex-has-thread?",
NIL,true,1,1,},
[PRIMITIVE_TREE_SIN_IS_LIVE_P]= {"tree/live-sin",
NIL,true,1,1,},
[PRIMITIVE_TREE_DEX_IS_LIVE_P]= {"tree/live-dex",
NIL,true,1,1,},
[PRIMITIVE_TREE_P]= {"tree?",
NIL,true,1,1,},
[PRIMITIVE_TREE_PLAIN_P]= {"tree%plain?",
NIL,true,1,1,},
[PRIMITIVE_TREE_RETHREAD_M]= {"tree/rethread!",
NIL,true,3,3,},
[PRIMITIVE_TREE_SIN_THREADABLE_P]= {"tree%sin-threadable?",
NIL,true,1,1,},
[PRIMITIVE_TREE_DEX_THREADABLE_P]= {"tree%dex-threadable?",
NIL,true,1,1,},
[PRIMITIVE_TREE_DATUM]= {"tree/datum",
NIL,true,1,1,},

[PRIMITIVE_ROPE_P]= {"rope?",
NIL,true,1,1,},
[PRIMITIVE_ROPE_PLAIN_P]= {"rope%plain?",
NIL,true,1,1,},
[PRIMITIVE_ROPE_SIN_THREADABLE_P]= {"rope%sin-threadable?",
NIL,true,1,1,},
[PRIMITIVE_ROPE_DEX_THREADABLE_P]= {"rope%dex-threadable?",
NIL,true,1,1,},
[PRIMITIVE_NEW_ROPE_PLAIN_NODE]= {"new-rope%plain-node",
NIL,true,1,3,},
[PRIMITIVE_ROPE_SEGMENT]= {"rope/segment",
NIL,true,1,1,},

/*:288*/
#line 4111 "lossless.w"

};

shared cell Root= NIL;

/*:187*//*246:*/
#line 5770 "lossless.w"

unique cell Accumulator= NIL;
unique cell Arguments= NIL;
unique cell Control_Link= NIL;
unique cell Environment= NIL;
unique cell Expression= NIL;

/*:246*/
#line 107 "lossless.w"


/*:2*//*17:*/
#line 400 "lossless.w"

#if 0
void
example(sigjmp_buf*failure)
{
sigjmp_buf cleanup;

Verror reason= LERR_NONE;

obtain_resources(failure);

if(failure_p(reason= sigsetjmp(cleanup,1)))

unwind(failure,reason,false,n);
use_resources(&cleanup);
free_resources();

}
#endif

/*:17*//*22:*/
#line 448 "lossless.w"

void*
mem_alloc(void*old,
size_t length,
size_t align,
sigjmp_buf*failure)
{
void*r;

if(!align)
r= realloc(old,length);
else{
assert(old==NULL);
if(((align-1)&align)!=0||align==0)
siglongjmp(*failure,LERR_INCOMPATIBLE);
if((length&(align-1))!=0)
siglongjmp(*failure,LERR_INCOMPATIBLE);
r= aligned_alloc(align,length);
}
if(r==NULL)
siglongjmp(*failure,LERR_OOM);
return r;
}

/*:22*//*30:*/
#line 738 "lossless.w"

cell
fix(intmax_t val)
{
cell r;

assert(val>=FIX_MIN&&val<=FIX_MAX);
r= FIXED;
r|= val<<FIX_SHIFT;
return r;
}

/*:30*//*36:*/
#line 873 "lossless.w"

void
heap_init_compacting(Oheap*heap,
Oheap*prev,
Oheap*pair)
{
int i;

heap->pair= pair;
heap->free= (Oatom*)(((intptr_t)HEAP_TO_SEGMENT(heap))+HEAP_CHUNK);
pair->free= (Oatom*)(((intptr_t)HEAP_TO_SEGMENT(pair))+HEAP_CHUNK);
for(i= 0;i<HEAP_LENGTH;i++){
heap->free--;
ATOM_TO_TAG(heap->free)= FORM_NONE;
pair->free--;
ATOM_TO_TAG(pair->free)= FORM_NONE;
heap->free->sin= heap->free->dex= NIL;
pair->free->sin= pair->free->dex= NIL;
}
heap->pair= pair;
pair->pair= heap;
if(prev==NULL){
heap->next= pair->next= NULL;
}else{
if((heap->next= prev->next)!=NULL){
assert(heap->next->pair->next==prev->pair);
heap->next->pair->next= heap->pair;
}
pair->next= prev->pair;
prev->next= heap;
}
}

/*:36*//*37:*/
#line 914 "lossless.w"

void
heap_init_sweeping(Oheap*heap,
Oheap*prev)
{
int i;

heap->pair= NULL;
heap->free= HEAP_TO_LAST(heap)-1;
ATOM_TO_TAG(heap->free)= FORM_NONE;
heap->free->sin= heap->free->dex= NIL;
for(i= 1;i<HEAP_LENGTH;i++){
heap->free--;
ATOM_TO_TAG(heap->free)= FORM_NONE;
heap->free->sin= NIL;
heap->free->dex= (cell)(heap->free+1);
}
if(prev==NULL)
heap->next= NULL;
else{
heap->next= prev->next;
prev->next= heap;
}
}

/*:37*//*38:*/
#line 945 "lossless.w"

Oheap*
heap_enlarge(Oheap*heap,
sigjmp_buf*failure)
{
Oheap*new,*pair;
Osegment*snew,*spair;
cell owner;

if(heap->pair==NULL){
snew= segment_alloc(-1,HEAP_CHUNK,1,HEAP_CHUNK,failure);
new= SEGMENT_TO_HEAP(snew);
heap_init_sweeping(new,heap);
owner= heap_alloc(new,failure);
ATOM_TO_TAG(owner)= FORM_HEAP;
pointer_set_m(owner,snew);
segment_set_owner_m(owner,owner);
}else{
snew= segment_alloc(-1,HEAP_CHUNK,1,HEAP_CHUNK,failure);
spair= segment_alloc(-1,HEAP_CHUNK,1,HEAP_CHUNK,failure);
new= SEGMENT_TO_HEAP(snew);
pair= SEGMENT_TO_HEAP(spair);
heap_init_compacting(new,heap,pair);
owner= heap_alloc(new,failure);
ATOM_TO_TAG(owner)= FORM_HEAP;
pointer_set_m(owner,snew);
segment_set_owner_m(owner,owner);
owner= heap_alloc(new,failure);
ATOM_TO_TAG(owner)= FORM_HEAP;
pointer_set_m(owner,spair);
segment_set_owner_m(owner,owner);
}
return new;
}

/*:38*//*39:*/
#line 992 "lossless.w"

cell
heap_alloc(Oheap*heap,
sigjmp_buf*failure)
{
Oheap*h,*next;
cell r;

next= heap;
if(heap->pair!=NULL){
allocate_incrementing:
while(next!=NULL){
h= next;
if(ATOM_TO_HEAP(h->free)==heap)
return(cell)h->free++;
next= h->next;
}
assert(failure!=NULL);

if(gc_compacting(heap,true)> 0)
next= heap;
else
next= heap_enlarge(h,failure);

goto allocate_incrementing;
}else{
allocate_listwise:
while(next!=NULL){
h= next;
if(!null_p(h->free)){
r= (cell)h->free;
h->free= (Oatom*)h->free->dex;
((Oatom*)r)->dex= NIL;
return r;
}
next= h->next;
}
assert(failure!=NULL);

if(gc_sweeping(heap,true)> 0)
next= heap;
else
next= heap_enlarge(h,failure);

goto allocate_listwise;
}
}

/*:39*//*41:*/
#line 1060 "lossless.w"

cell
atom(Oheap*heap,
cell nsin,
cell ndex,
Otag ntag,
sigjmp_buf*failure)
{
cell r;
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

assert(ntag!=FORM_NONE);
if(ntag&LTAG_DSIN)
Tmp_SIN= nsin;
if(ntag&LTAG_DDEX)
Tmp_DEX= ndex;
if(failure_p(reason= sigsetjmp(cleanup,1)))
goto fail;
r= heap_alloc(heap,&cleanup);
TAG_SET_M(r,ntag);
((Oatom*)r)->sin= (ntag&LTAG_DSIN)?Tmp_SIN:nsin;
((Oatom*)r)->dex= (ntag&LTAG_DDEX)?Tmp_DEX:ndex;
Tmp_SIN= Tmp_DEX= NIL;
return r;
fail:
Tmp_SIN= Tmp_DEX= NIL;
siglongjmp(*failure,reason);
}

/*:41*//*42:*/
#line 1096 "lossless.w"

Otag
ltag(cell o)
{
assert(!special_p(o));
return TAG(o);
}

cell
lcar(cell o)
{
assert(!special_p(o));
return((Oatom*)o)->sin;
}

cell
lcdr(cell o)
{
assert(!special_p(o));
return((Oatom*)o)->dex;
}

void
lcar_set_m(cell o,
cell datum)
{
assert(!special_p(o));
assert(!ATOM_SIN_DATUM_P(o)||defined_p(datum));
((Oatom*)o)->sin= datum;
}

void
lcdr_set_m(cell o,
cell datum)
{
assert(!special_p(o));
assert(!ATOM_DEX_DATUM_P(o)||defined_p(datum));
((Oatom*)o)->dex= datum;
}

/*:42*//*47:*/
#line 1278 "lossless.w"

Osegment*
segment_alloc_imp(Osegment*old,
long header,
long length,
long stride,
long align,
sigjmp_buf*failure)
{
long cstride;
size_t size;
Osegment*r;

assert(header>=-1&&length>=0&&stride>=0);
if(header==-1)
header= -sizeof(Osegment);
assert(old==NULL||stride==old->stride);
assert(align==0||old==NULL);
cstride= stride?stride:1;
if(length> HALF_MAX||stride> HALF_MAX||
ckd_mul(&size,length,cstride)||
ckd_add(&size,size,header)||
ckd_add(&size,size,sizeof(Osegment)))
siglongjmp(*failure,LERR_OOM);
r= mem_alloc(old,size,align,failure);
r->length= length;
if(old==NULL){
r->stride= stride;
r->owner= NIL;
}
if(Allocations==NULL)
Allocations= r->next= r->prev= r;
else{
r->next= Allocations;
r->prev= Allocations->prev;
Allocations->prev->next= r;
Allocations->prev= r;
}
return r;
}

/*:47*//*48:*/
#line 1328 "lossless.w"

cell
segment_new_imp(Oheap*heap,
long header,
long length,
long stride,
long align,
Otag ntag,
sigjmp_buf*failure)
{
cell r;
long total;
Osegment*s;

assert(stride>=0);
assert(ntag!=FORM_NONE);
if(ckd_add(&total,header,length))
siglongjmp(*failure,LERR_LIMIT);
if(stride==0&&total<=INTERN_BYTES){
assert(ntag==FORM_SEGMENT);
r= atom(heap,NIL,NIL,FORM_SEGMENT_INTERN,failure);
segint_set_length_m(r,length);
return r;
}
Tmp_ier= atom(heap,NIL,NIL,FORM_PAIR,failure);
s= segment_alloc(header,length,stride,align,failure);
TAG_SET_M(Tmp_ier,ntag);
ATOM_TO_ATOM(Tmp_ier)->sin= (cell)s;
s->owner= Tmp_ier;
Tmp_ier= NIL;
return s->owner;
}

/*:48*//*49:*/
#line 1366 "lossless.w"

cell
segment_init(Osegment*seg,
cell container)
{
assert(!special_p(container));
seg->owner= container;
ATOM_TO_TAG(container)= FORM_HEAP;
ATOM_TO_ATOM(container)->sin= (cell)seg;
ATOM_TO_ATOM(container)->dex= NIL;
return container;
}

/*:49*//*50:*/
#line 1387 "lossless.w"

cell
segment_resize_m(cell o,
long header,
long delta,
sigjmp_buf*failure)
{
Osegment*new,*old;
long i,nlength,nstride;
cell r= NIL;
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

assert(segment_p(o)||arraylike_p(o));
assert(delta>=-segment_length(o));
if(ckd_add(&nlength,segment_length(o),delta))
siglongjmp(*failure,LERR_OOM);
if(segment_intern_p(o)&&nlength<=INTERN_BYTES){
segint_set_length_m(o,nlength);
return o;
}else if((arraylike_p(o)||segment_stored_p(o))&&
(segbuf_base(o)->stride||nlength> INTERN_BYTES)){
old= segbuf_base(o);
nstride= segment_stride(o);
segment_release_m(o,false);
new= segment_alloc_imp(old,header,nlength,nstride,0,
failure);
pointer_set_m(o,new);
return o;
}
assert(header==0);
assert(segment_stride(o)==0);
assert(null_p(Tmp_ier));
Tmp_ier= o;
if(failure_p(reason= sigsetjmp(cleanup,1)))
unwind(failure,reason,true,0);
r= segment_new(0,nlength,0,0,&cleanup);
if(segment_length(Tmp_ier)<nlength)
nlength= segment_length(Tmp_ier);
for(i= 0;i<nlength;i++)
segment_address(r)[i]= segment_address(Tmp_ier)[i];
Tmp_ier= NIL;
return r;
}

/*:50*//*51:*/
#line 1436 "lossless.w"

void
segment_release_m(cell o,
bool reclaim)
{
assert(pointer_p(o));
segment_release_imp(pointer(o),reclaim);
pointer_erase_m(o);
}

/*:51*//*52:*/
#line 1451 "lossless.w"

void
segment_release_imp(Osegment*o,
bool reclaim)
{
if(o==Allocations)
Allocations= o->next;
if(o->next==o)
Allocations= NULL;
else
o->prev->next= o->next,
o->next->prev= o->prev;
o->next= o->prev= o;
if(reclaim)
free(o);
}

/*:52*//*57:*/
#line 1541 "lossless.w"

size_t
gc_sweeping(Oheap*heap,
bool segments)
{
size_t count,remain;
int i;
Oatom*a;
Oheap*p;

assert((heap==Theap)||((Sheap!=NIL)&&(heap==Sheap)));
count= remain= 0;
p= heap;
while(p!=NULL){
remain+= HEAP_LENGTH;
p= p->next;
}
if(segments)
gc_disown_segments(heap);
for(i= 0;i<LGCR_COUNT;i++)
if(!special_p(*Registers[i]))
*Registers[i]= gc_mark(heap,*Registers[i],
false,NULL,&count);
p= heap;
while(p!=NULL){
a= HEAP_TO_LAST(p);
p->free= (Oatom*)NIL;
for(i= 0;i<HEAP_LENGTH;i++){
a--;
if(ATOM_LIVE_P(a))
ATOM_CLEAR_LIVE_M(a);
else{
ATOM_TO_TAG(a)= FORM_NONE;
a->sin= NIL;
a->dex= (cell)p->free;
p->free= a;
}
}
p= p->next;
}
count+= gc_reclaim_heap(heap);
if(segments)
gc_release_segments(heap);
return remain-count;
}

/*:57*//*58:*/
#line 1590 "lossless.w"

size_t
gc_compacting(Oheap*heap,
bool segments)
{
size_t count,remain;
int i;
Oheap*last,*p;

assert((heap==Theap)||((Sheap!=NIL)&&(heap==Sheap)));
count= remain= 0;
p= heap;
while(p!=NULL){
last= p;
remain+= HEAP_LENGTH;
p->pair->pair= NULL;
p= p->next;
}
if(segments)
gc_disown_segments(heap);
for(i= 0;i<LGCR_COUNT;i++)
if(!special_p(Registers[i]))
*Registers[i]= gc_mark(last,*Registers[i],
true,NULL,&count);
count+= gc_reclaim_heap(heap);
if(segments)
gc_release_segments(heap);
p= last;
while(p!=NULL){
p->pair->free= HEAP_TO_LAST(p->pair);
for(i= 0;i<HEAP_LENGTH;i--){
ATOM_TO_TAG(--p->pair->free)= FORM_NONE;

p->pair->free->sin= p->pair->free->dex= NIL;
}
p->pair->pair= p;
heap= p;
p= p->next;
}
if(heap==Theap)
Theap= last;
else
Sheap= last;
return remain-count;
}

/*:58*//*59:*/
#line 1636 "lossless.w"

size_t
gc_reclaim_heap(Oheap*heap)
{
size_t count= 0;
Oheap*h;

do{
h= heap;
while(1){
segment_init(HEAP_TO_SEGMENT(h),heap_alloc(heap,NULL));
count++;
if(h->next==NULL)
break;
h= h->next;
}
}while(h->pair!=NULL&&(h==Theap||h==Sheap));
return count;
}

/*:59*//*60:*/
#line 1659 "lossless.w"

void
gc_disown_segments(Oheap*heap Lunused)
{
Osegment*s;

s= Allocations;
while(1){
if(!null_p(s->owner)&&
(ATOM_TO_HEAP(s->owner)->pair==NULL||
ATOM_TO_HEAP(s->owner)->pair->pair==NULL))
s->owner= NIL;
if((s= s->next)==Allocations)
break;
}
}

/*:60*//*61:*/
#line 1679 "lossless.w"

void
gc_release_segments(Oheap*heap Lunused)
{
Osegment*s,*n;

s= Allocations;
while(1){
n= s->next;
if(null_p(s->owner))
segment_release_imp(s,true);
if(n==Allocations)
break;
s= n;
}
}

/*:61*//*62:*/
#line 1697 "lossless.w"

cell
gc_mark(Oheap*heap,
cell next,
bool compacting,
cell*cycles,
size_t*remain)
{
bool remember;
cell copied,parent,tmp;
long i;

remember= (cycles!=NULL&&!null_p(*cycles));
parent= tmp= NIL;
while(1){
if(!special_p(next)&&!ATOM_LIVE_P(next)){
(*remain)++;
ATOM_SET_LIVE_M(next);
if(!compacting)
copied= next;
else{
/*63:*/
#line 1766 "lossless.w"

copied= heap_alloc(heap,NULL);
*ATOM_TO_ATOM(copied)= *ATOM_TO_ATOM(next);
TAG_SET_M(copied,form(next));
collected_set_datum_m(next,copied);
TAG_SET_M(next,FORM_COLLECTED);

/*:63*/
#line 1718 "lossless.w"

}
if(pointer_p(next))
segment_set_owner_m(next,copied);
else if(primitive_p(next))
Iprimitive[primitive(next)].box= next;
next= copied;

if(ATOM_SIN_DATUM_P(next)&&
ATOM_DEX_DATUM_P(next)){
/*68:*/
#line 1805 "lossless.w"

ATOM_SET_MORE_M(next);
tmp= ATOM_TO_ATOM(next)->sin;
if(remember&&!special_p(tmp)&&ATOM_LIVE_P(tmp))
gc_serial(*cycles,tmp);
ATOM_TO_ATOM(next)->sin= parent;
parent= next;
next= tmp;

/*:68*/
#line 1728 "lossless.w"

}else if(ATOM_SIN_DATUM_P(next)){
/*64:*/
#line 1773 "lossless.w"

tmp= ATOM_TO_ATOM(next)->sin;
if(remember&&!special_p(tmp)&&ATOM_LIVE_P(tmp))
gc_serial(*cycles,tmp);
ATOM_TO_ATOM(next)->sin= parent;
parent= next;
next= tmp;

/*:64*/
#line 1730 "lossless.w"

}else if(ATOM_DEX_DATUM_P(next)){
/*66:*/
#line 1789 "lossless.w"

tmp= ATOM_TO_ATOM(next)->dex;
if(remember&&!special_p(tmp)&&ATOM_LIVE_P(tmp))
gc_serial(*cycles,tmp);
ATOM_TO_ATOM(next)->dex= parent;
parent= next;
next= tmp;

/*:66*/
#line 1732 "lossless.w"

}else if(arraylike_p(next)){
/*71:*/
#line 1836 "lossless.w"

i= 0;
if(array_length(next)> 0){
ATOM_SET_MORE_M(next);
array_set_progress_m(next,i);
tmp= array_ref(next,i);
if(remember&&!special_p(tmp)&&ATOM_LIVE_P(tmp))
gc_serial(*cycles,tmp);
array_set_m(next,i,parent);
parent= next;
next= tmp;
}

/*:71*/
#line 1734 "lossless.w"

}
}

else if(special_p(parent))
break;

else if(ATOM_SIN_DATUM_P(parent)&&ATOM_DEX_DATUM_P(parent)){
if(ATOM_MORE_P(parent)){
/*69:*/
#line 1817 "lossless.w"

ATOM_CLEAR_MORE_M(parent);
tmp= ATOM_TO_ATOM(parent)->dex;
if(remember&&!special_p(tmp)&&ATOM_LIVE_P(tmp))
gc_serial(*cycles,tmp);
ATOM_TO_ATOM(parent)->dex= ATOM_TO_ATOM(parent)->sin;
if(collected_p(next))
next= collected_datum(next);
ATOM_TO_ATOM(parent)->sin= next;
next= tmp;

/*:69*/
#line 1743 "lossless.w"

}else{
/*70:*/
#line 1828 "lossless.w"

tmp= ATOM_TO_ATOM(parent)->dex;
if(collected_p(next))
next= collected_datum(next);
ATOM_TO_ATOM(parent)->dex= next;
next= parent;
parent= tmp;

/*:70*/
#line 1745 "lossless.w"

}
}else if(ATOM_SIN_DATUM_P(parent)){
/*65:*/
#line 1781 "lossless.w"

tmp= parent;
parent= ATOM_TO_ATOM(tmp)->sin;
if(collected_p(next))
next= collected_datum(next);
ATOM_TO_ATOM(tmp)->sin= next;
next= tmp;

/*:65*/
#line 1748 "lossless.w"

}else if(ATOM_DEX_DATUM_P(parent)){
/*67:*/
#line 1797 "lossless.w"

tmp= parent;
parent= ATOM_TO_ATOM(tmp)->dex;
if(collected_p(next))
next= collected_datum(next);
ATOM_TO_ATOM(tmp)->dex= next;
next= tmp;

/*:67*/
#line 1750 "lossless.w"

}else if(arraylike_p(parent)){
i= array_progress(parent);
if(i<array_length(parent)-1){
/*72:*/
#line 1849 "lossless.w"

assert(ATOM_MORE_P(parent));
i++;
tmp= array_ref(parent,i);
if(remember&&!special_p(tmp)&&ATOM_LIVE_P(tmp))
gc_serial(*cycles,tmp);
array_set_m(parent,i,array_ref(parent,i-1));
if(collected_p(next))
next= collected_datum(next);
array_set_m(parent,i-1,next);
next= tmp;
array_set_progress_m(parent,i);

/*:72*/
#line 1754 "lossless.w"

}else{
/*73:*/
#line 1862 "lossless.w"

ATOM_CLEAR_MORE_M(parent);
tmp= array_ref(parent,i);
if(collected_p(next))
next= collected_datum(next);
array_set_m(parent,i,next);
next= parent;
parent= tmp;

/*:73*/
#line 1756 "lossless.w"

}
}else
next= parent;
}
if(collected_p(next))
next= collected_datum(next);
return next;
}

/*:62*//*79:*/
#line 1905 "lossless.w"

cell
array_new_imp(long length,
cell fill,
Otag ntag,
sigjmp_buf*failure)
{
cell r;
long i;
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

assert(length>=0);
assert(null_p(Tmp_ier));
if(failure_p(reason= sigsetjmp(cleanup,1)))
unwind(failure,reason,true,0);
Tmp_ier= fill;
r= segment_new_imp(Theap,0,length,sizeof(cell),
sizeof(cell),ntag,&cleanup);
if(defined_p(Tmp_ier)&&length> 0){
array_set_m(r,0,Tmp_ier);
for(i= 1;i<length;i++)
array_address(r)[i]= array_address(r)[0];
}
Tmp_ier= NIL;
return r;
}

/*:79*//*80:*/
#line 1936 "lossless.w"

cell
array_grow(cell o,
long delta,
cell fill,
sigjmp_buf*failure)
{
static int Sobject= 1,Sfill= 0;
long i,j,nlength,slength;
cell r;
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

assert(arraylike_p(o)&&o!=Stack);
assert(delta&&delta>=-array_length(o));
if(ckd_add(&nlength,array_length(o),delta))
siglongjmp(*failure,LERR_OOM);

stack_protect(1,fill,failure);
if(failure_p(reason= sigsetjmp(cleanup,1)))
unwind(failure,reason,false,1);
r= array_new_imp(nlength,UNDEFINED,FORM_ARRAY,&cleanup);
slength= delta>=0?array_length(SO(Sobject)):nlength;
for(i= 0;i<slength;i++)
array_set_m(r,i,array_ref(SO(Sobject),i));
if(defined_p(fill)){
if(i<nlength)
array_set_m(r,i,SO(Sfill));
for(j= i+1;j<nlength;j++)
array_address(r)[j]= array_address(r)[i];
}
stack_clear(1);
return r;
}

/*:80*//*81:*/
#line 1971 "lossless.w"

cell
array_grow_m(cell o,
long delta,
cell fill,
sigjmp_buf*failure)
{
static int Sfill= 0;
bool isstack;
cell r;
long i,slength;
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

assert(arraylike_p(o));
assert(delta&&delta>=-array_length(o));
assert(null_p(Tmp_ier));
Tmp_ier= o;
if(!(isstack= (o==Stack)))
stack_protect(1,fill,failure);
if(failure_p(reason= sigsetjmp(cleanup,1)))
unwind(failure,reason,true,isstack?1:0);
slength= array_length(Tmp_ier);
r= segment_resize_m(Tmp_ier,sizeof(cell),delta,&cleanup);
if(!isstack&&delta> 0&&defined_p(SO(Sfill))){
for(i= slength;i<array_length(r);i++)
if(i==slength)
array_set_m(r,i,SO(Sfill));
else
array_address(r)[i]= array_address(r)[slength];
}
Tmp_ier= NIL;
if(!isstack)
stack_clear(1);
return r;
}

/*:81*//*82:*/
#line 2008 "lossless.w"

cell
array_ref(cell o,
long idx)
{
assert(arraylike_p(o));
assert(idx>=0&&idx<array_length(o));
return array_address(o)[idx];
}

/*:82*//*83:*/
#line 2018 "lossless.w"

void
array_set_m(cell o,
long idx,
cell d)
{
assert(arraylike_p(o));
assert(idx>=0&&idx<array_length(o));
assert(defined_p(d));
array_address(o)[idx]= d;
}

/*:83*//*86:*/
#line 2039 "lossless.w"

Vhash
hash_cstr(char*buf,
long*length,
sigjmp_buf*failure)
{
Vhash r= 0;
char*p= buf;

while(*p!='\0')
if(Interrupt)
siglongjmp(*failure,LERR_INTERRUPT);
else
r= 33*r+(unsigned char)(*p++);
*length= p-buf;
return r;
}

/*:86*//*87:*/
#line 2060 "lossless.w"

Vhash
hash_buffer(char*buf,
long length,
sigjmp_buf*failure)
{
Vhash r= 0;
long i;

assert(length>=0);
for(i= 0;i<length;i++)
if(Interrupt&&failure!=NULL)
siglongjmp(*failure,LERR_INTERRUPT);
else
r= 33*r+(unsigned char)(*buf++);
return r;
}

/*:87*//*89:*/
#line 2096 "lossless.w"

cell
keytable_new(long length,
sigjmp_buf*failure)
{
cell r;
long f;

assert(length>=0);
if(length>=KEYTABLE_MAXLENGTH)
siglongjmp(*failure,LERR_LIMIT);
else if(length==0)
f= 0;
else if(length<=KEYTABLE_MINLENGTH)
f= (length= KEYTABLE_MINLENGTH)-1;
else
f= (7*(length= 1<<(high_bit(length)-1)))/10;
if(length==0)
return Null_Array;
r= array_new_imp(length+1,NIL,FORM_KEYTABLE,failure);
keytable_set_free_m(r,f);
return r;
}

/*:89*//*90:*/
#line 2120 "lossless.w"

cell
keytable_enlarge_m(cell o,
Vhash(*hashfn)(cell,sigjmp_buf*),
sigjmp_buf*failure)
{
static int Sobject= 1,Sret= 0;
cell r= NIL,s;
long i,j,nlength;
long nfree;
Vhash nhash;
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

assert(keytable_p(o));
nlength= keytable_length(o);
if(nlength>=(INT_MAX>>2))
siglongjmp(*failure,LERR_LIMIT);
if(nlength==0)
nlength= KEYTABLE_MINLENGTH;
else
nlength<<= 1;
stack_protect(2,o,NIL,failure);
if(failure_p(reason= sigsetjmp(cleanup,1)))
unwind(failure,reason,false,2);
SS(Sret,r= keytable_new(nlength,&cleanup));
nfree= (7*nlength)/10;
for(i= 0;i<keytable_length(SO(Sobject));i++)
if(Interrupt)
siglongjmp(cleanup,LERR_INTERRUPT);
else if(!null_p((s= array_ref(SO(Sobject),i)))){
nhash= hashfn(s,&cleanup);
for(j= nhash%nlength;
!null_p(keytable_ref(r,j));
j--)
if(j==0)
j= nlength-1;
array_set_m(r,j,s);
nfree--;
}
r= SO(Sret);
keytable_set_free_m(r,nfree);
stack_clear(2);
return r;
}

/*:90*//*91:*/
#line 2166 "lossless.w"

void
keytable_save_m(cell o,
long idx,
cell datum)
{
assert(keytable_p(o));
assert(idx>=0&&idx<keytable_length(o));
assert(keytable_free_p(o));
assert(null_p(keytable_ref(o,idx)));
array_set_m(o,idx,datum);
keytable_set_free_m(o,keytable_free(o)-1);
}

/*:91*//*92:*/
#line 2180 "lossless.w"

void
keytable_remove_m(cell o,
long idx)
{
int i,j;

assert(keytable_p(o));
assert(idx>=0&&idx<keytable_length(o));
assert(!null_p(keytable_ref(o,idx)));
i= idx;
while(1){
j= i-1;
if(j==0)
j= keytable_length(o)-1;
array_set_m(o,i,array_ref(o,j));
if(null_p(keytable_ref(o,i)))
break;
i= j;
}
keytable_set_free_m(o,keytable_free(o)+1);
}

/*:92*//*93:*/
#line 2206 "lossless.w"

int
keytable_search(cell o,
Vhash hash,
int(*match)(cell,void*,sigjmp_buf*),
void*ctx,
sigjmp_buf*failure)
{
int p,r;

assert(keytable_p(o));
if(null_array_p(o))
return FAIL;
for(r= hash%keytable_length(o);
!null_p(keytable_ref(o,r));
r--){
p= match(keytable_ref(o,r),ctx,failure);
if(p==0)
return r;
if(r==0)
r= keytable_length(o)-1;
}
return r;
}

/*:93*//*98:*/
#line 2292 "lossless.w"

int
symbol_table_cmp(cell sym,
void*ctx,
sigjmp_buf*failure)
{
Osymbol_compare*scmp= ctx;
int i;

assert(symbol_p(sym));
if(symbol_length(sym)> scmp->length)
return 1;
if(symbol_length(sym)<scmp->length)
return 1;
for(i= 0;i<scmp->length;i++){
if(Interrupt)
siglongjmp(*failure,LERR_INTERRUPT);
if(symbol_buffer(sym)[i]> scmp->buf[i])
return 1;
if(symbol_buffer(sym)[i]<scmp->buf[i])
return 1;
}
return 0;
}

/*:98*//*99:*/
#line 2317 "lossless.w"

long
symbol_table_search(Vhash hash,
Osymbol_compare scmp,
sigjmp_buf*failure)
{
return keytable_search(Symbol_Table,hash,symbol_table_cmp,&scmp,failure);
}

/*:99*//*100:*/
#line 2326 "lossless.w"

Vhash
symbol_table_rehash(cell s,
sigjmp_buf*failure Lunused)
{
Vhash r;

assert(symbol_p(s));
r= symbol_hash(s);
return r;
}

/*:100*//*101:*/
#line 2341 "lossless.w"

cell
symbol_new_buffer(char*buf,
long length,
sigjmp_buf*failure)
{
Vhash hash;

assert(length>=0);
if(length==0)
hash= hash_cstr(buf,&length,failure);
else
hash= hash_buffer(buf,length,failure);
if(length> SYMBOL_MAX)
siglongjmp(*failure,LERR_LIMIT);
return symbol_new_imp(hash,buf,length,failure);
}

/*:101*//*102:*/
#line 2359 "lossless.w"

cell
symbol_new_imp(Vhash hash,
char*buf,
long length,
sigjmp_buf*failure)
{
static int Sret= 0;
cell new,r= NIL;
int boff,i,size,idx;
Osymbol_compare scmp= {buf,length};
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

assert(length>=0);
search:
idx= symbol_table_search(hash,scmp,failure);
if(idx==FAIL||(null_p(keytable_ref(Symbol_Table,idx))&&
!keytable_free_p(Symbol_Table))){
new= keytable_enlarge_m(Symbol_Table,symbol_table_rehash,failure);
Symbol_Table= new;
goto search;
}
if(!null_p(keytable_ref(Symbol_Table,idx)))
return keytable_ref(Symbol_Table,idx);

stack_reserve(1,failure);
if(failure_p(reason= sigsetjmp(cleanup,1)))
unwind(failure,reason,false,1);
if(length<=WIDE_BYTES-1){
/*103:*/
#line 2398 "lossless.w"

SS(Sret,r= atom(Theap,NIL,NIL,FORM_SYMBOL_INTERN,&cleanup));
symint_length(r)= length;
for(i= 0;i<length;i++)
symbol_buffer(r)[i]= buf[i];

/*:103*/
#line 2389 "lossless.w"

}else{
/*104:*/
#line 2404 "lossless.w"

if(ckd_add(&size,sizeof(Osymbol),length))
siglongjmp(*failure,LERR_LIMIT);
while(size> Symbol_Buffer_Length||
Symbol_Buffer_Length-size<Symbol_Buffer_Free){
if(Symbol_Buffer_Length>=SYMBOL_BUFFER_MAX)
siglongjmp(*failure,LERR_LIMIT);
new= segment_resize_m(Symbol_Buffer,0,SYMBOL_CHUNK,&cleanup);
Symbol_Buffer= new;
}
boff= Symbol_Buffer_Free;
Symbol_Buffer_Free+= sizeof(Osymbol)+length;
SS(Sret,r= atom(Theap,NIL,NIL,FORM_SYMBOL,&cleanup));
symbuf_set_offset_m(r,boff);
symbuf_set_length_m(r,length);
symbuf_hash(r)= hash;
for(i= 0;i<length;i++)
symbol_buffer(r)[i]= buf[i];

/*:104*/
#line 2391 "lossless.w"

}
keytable_save_m(Symbol_Table,idx,r);
stack_clear(1);
return r;
}

/*:102*//*108:*/
#line 2523 "lossless.w"

cell
dryad_node_new(bool tree,
bool sinward,
bool dexward,
cell datum,
cell nsin,
cell ndex,
sigjmp_buf*failure)
{
static int Sdatum= 2,Snsin= 1,Sndex= 0;
Otag ntag;
cell r;
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

ntag= tree?FORM_TREE:FORM_ROPE;
if(sinward)
ntag|= LTAG_TSIN;
if(dexward)
ntag|= LTAG_TDEX;
assert(null_p(nsin)||form(nsin)==ntag);
assert(null_p(ndex)||form(ndex)==ntag);
stack_protect(3,datum,nsin,ndex,failure);
if(failure_p(reason= sigsetjmp(cleanup,2)))
unwind(failure,reason,false,3);
r= atom(Theap,SO(Snsin),SO(Sndex),FORM_TREE,&cleanup);
r= atom(Theap,SO(Sdatum),r,ntag,&cleanup);
stack_clear(3);
return r;
}

/*:108*//*109:*/
#line 2561 "lossless.w"

cell
treeish_edge_imp(cell o,
bool sinward,
sigjmp_buf*failure)
{
cell r;

assert(treeish_p(o));
r= o;
while(sinward?dryad_sin_p(r):dryad_dex_p(r))
if(Interrupt)
siglongjmp(*failure,LERR_INTERRUPT);
else if(null_p((o= sinward?dryad_sin(r):dryad_dex(r))))
return r;
else
r= o;
return r;
}

/*:109*//*110:*/
#line 2595 "lossless.w"



anytree_next_imp(sin,dex)
anytree_next_imp(dex,sin)

/*:110*//*112:*/
#line 2605 "lossless.w"

cell
treeish_rethread_m(cell o,
bool sinward,
bool dexward,
sigjmp_buf*failure)
{
cell head,next,prev,remember;
Otag ntag;

assert(treeish_p(o));
ntag= form(o)&FORM_TREE;
head= dryad_node_new(ntag==FORM_TREE,treeish_sin_threadable_p(o),
treeish_dex_threadable_p(o),NIL,o,NIL,failure);
if(sinward)
ntag|= LTAG_TSIN;
if(dexward)
ntag|= LTAG_TDEX;

next= head;
remember= NIL;
while(1){
if(null_p(next))
break;
prev= tree_thread_live_sin(next);
if(!null_p(prev)){
while(!(prev==remember||null_p(tree_thread_live_dex(prev))))
prev= tree_thread_live_dex(prev);
if(prev!=remember){
dryad_set_dex_m(prev,next);
tree_thread_set_dex_live_m(prev);
next= tree_thread_live_sin(next);
continue;
}else{
dryad_set_dex_m(prev,NIL);
tree_thread_set_dex_live_m(prev);
}
}
if(treeish_sin_has_thread_p(next)){
dryad_set_sin_m(next,NIL);
tree_thread_set_sin_live_m(next);
}
treeish_rethread_imp(next,prev,ntag,head);
remember= next;
next= tree_thread_live_dex(next);
}
return dryad_sin(head);
}

/*:112*//*113:*/
#line 2654 "lossless.w"

void
treeish_rethread_imp(cell current,
cell previous,
Otag ntag,
cell head)
{
TAG_SET_M(current,ntag);
if(null_p(previous)){
dryad_set_sin_m(current,NIL);
tree_thread_set_sin_live_m(current);
}else if(current==head){
dryad_set_dex_m(previous,NIL);
tree_thread_set_dex_live_m(previous);
}else{
if(ntag&LTAG_TSIN&&!dryad_sin_p(current)){
dryad_set_sin_m(current,previous);
tree_thread_set_sin_thread_m(current);
}
if(ntag&LTAG_TDEX&&!dryad_dex_p(previous)){
dryad_set_dex_m(previous,current);
tree_thread_set_dex_thread_m(previous);
}
}
}

/*:113*//*115:*/
#line 2699 "lossless.w"

cell
dlist_new(cell datum,
sigjmp_buf*failure)
{
cell r;

r= dryad_node_new(true,false,false,datum,NIL,NIL,failure);
TAG_SET_M(dryad_link(r),FORM_PAIR);
dryad_set_sin_m(r,r);
dryad_set_dex_m(r,r);
return r;
}

/*:115*//*116:*/
#line 2713 "lossless.w"

void
dlist_set_m(cell o,
cell datum)
{
assert(dlist_p(o));
lcar_set_m(o,datum);
}

/*:116*//*117:*/
#line 2732 "lossless.w"



dlist_set(next,lcdr,lcar)
dlist_set(prev,lcar,lcdr)

/*:117*//*118:*/
#line 2739 "lossless.w"

cell
dlist_append_m(cell o,
cell l)
{
cell after,before;

assert(dlist_p(o));
assert(dlist_p(l));
after= dlist_next(o);
before= dlist_prev(l);
dlist_set_next_m(o,l);
dlist_set_prev_m(after,before);
return l;
}

/*:118*//*119:*/
#line 2756 "lossless.w"

cell
dlist_append_datum_m(cell o,
cell d,
sigjmp_buf*failure)
{
static int Sobject= 1,Sdatum= 0;
cell r= NIL;
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

assert(dlist_p(o));
assert(defined_p(d));
stack_protect(2,o,d,failure);
if(failure_p(reason= sigsetjmp(cleanup,1)))
unwind(failure,reason,false,2);
r= dlist_new(SO(Sdatum),&cleanup);
r= dlist_append_m(SO(Sobject),r);
stack_clear(2);
return r;
}

/*:119*//*120:*/
#line 2778 "lossless.w"

cell
dlist_remove_m(cell o)
{
cell next,prev;

assert(dlist_p(o));
prev= dlist_prev(o);
next= dlist_next(o);
if(prev==next)
return NIL;
dlist_set_next_m(prev,next);
return next;
}

/*:120*//*122:*/
#line 2833 "lossless.w"

cell
record_new(cell record_form,
int array_length,
int segment_length,
sigjmp_buf*failure)

{
static int Sform= 1,Sret= 0;
cell r= NIL,tmp;
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

assert(symbol_p(record_form)||fix_p(record_form));
assert(array_length>=0);
if(array_length>=RECORD_MAXLENGTH)
siglongjmp(*failure,LERR_LIMIT);
stack_protect(2,record_form,NIL,failure);
if(failure_p(reason= sigsetjmp(cleanup,1)))
unwind(failure,reason,false,2);
if(segment_length> 0)
array_length++;
r= array_new_imp(array_length+1,NIL,FORM_RECORD,&cleanup);
if(segment_length> 0){
SS(Sret,r);
tmp= segment_new(0,segment_length,1,0,&cleanup);
pointer_set_datum_m(tmp,SO(Sform));
r= SO(Sret);
array_set_m(r,0,tmp);
}else
array_set_m(r,0,SO(Sform));
stack_clear(2);
return r;
}

/*:122*//*128:*/
#line 2944 "lossless.w"

Outfio
utfio_scan_start(void)
{
Outfio r= {0};
return r;
}

/*:128*//*129:*/
#line 2952 "lossless.w"

Vutfio_parse
utfio_read(Outfio*ctx,
char byte)
{
int32_t vbyte= byte;
int i;

for(i= 0;i<4;i++){
if((byte&~UTFIO[i].data)!=UTFIO[i].lead)
continue;
else if(i==0){
if(ctx->remaining)
ctx->remaining--;
else
return ctx->status= UTFIO_BAD_CONTINUATION;
}else{
if(ctx->remaining)
return ctx->status= UTFIO_BAD_STARTER;
else
ctx->remaining= i-1;
}
ctx->buf[(int)ctx->offset++]= byte;
ctx->value|= (vbyte&UTFIO[i].data)<<(6*ctx->remaining);
if(ctx->remaining)
return ctx->status= UTFIO_PROGRESS;
else if(utfio_too_large_p(ctx)||utfio_noncharacter_p(ctx))
return ctx->status= UTFIO_INVALID;
else if(utfio_surrogate_p(ctx))
return ctx->status= UTFIO_SURROGATE;
else if(utfio_overlong_p(ctx))
return ctx->status= UTFIO_OVERLONG;
else
return ctx->status= UTFIO_COMPLETE;
}
return ctx->status= UTFIO_INVALID;
}

/*:129*//*130:*/
#line 2992 "lossless.w"

Vutfio_parse
utfio_reread(Outfio*ctx,
char byte)
{
int32_t vbyte= byte;
int i;

for(i= 0;i<4;i++)
if((byte&~UTFIO[i].data)!=UTFIO[i].lead)
continue;
else{
if(ctx->remaining)
ctx->remaining--;
else
ctx->remaining= i-1;
ctx->buf[(int)ctx->offset++]= byte;
ctx->value= (vbyte&UTFIO[i].data)<<(6*ctx->remaining);
ctx->status= ctx->remaining?UTFIO_PROGRESS:UTFIO_COMPLETE;
return ctx->status;
}
abort();
}

/*:130*//*131:*/
#line 3016 "lossless.w"

Outfio
utfio_write(int32_t c)
{
int i;
int32_t mask,next;
Outfio r= {0};

assert(c>=0&&c<=UCP_MAX);
r.status= UTFIO_PROGRESS;
r.value= c;
if(utfio_surrogate_p(&r))
r.status= UTFIO_SURROGATE;
else if(r.value<0||utfio_noncharacter_p(&r))
r.status= UTFIO_INVALID;
else if(utfio_too_large_p(&r))
r.status= UTFIO_OVERLONG;
if(r.status==UTFIO_PROGRESS)
r.status= UTFIO_COMPLETE;
else
c= UCP_REPLACEMENT;
if(c<=UTFIO[1].max)
r.buf[(int)r.offset++]= c;
else{
if(c<=UTFIO[2].max)
r.remaining= i= 2;
else if(c<=UTFIO[3].max)
r.remaining= i= 3;
else
r.remaining= i= 4;
for(;r.remaining;r.remaining--){
mask= UTFIO[r.remaining==i?i:0].data;
mask<<= 6*(r.remaining-1);
next= c&mask;
next>>= 6*(r.remaining-1);
next|= UTFIO[r.remaining==i?i:0].lead;
r.buf[(int)r.offset++]= next;
}
}
return r;
}

/*:131*//*133:*/
#line 3089 "lossless.w"

cell
rune_new_utfio(Outfio ctx,
sigjmp_buf*failure)
{
Oatom packed;

ctx.value|= (ctx.offset<<21);
ctx.value|= (ctx.status<<24);
if(CELL_BITS>=32){
packed.sin= (cell)ctx.value;
packed.dex= NIL;
}else{
packed.sin= (cell)((ctx.value&0xffff0000ll)>>16);
packed.dex= (cell)((ctx.value&0x0000ffffll)>>0);
}
return atom(Theap,packed.sin,packed.dex,FORM_RUNE,failure);
}

/*:133*//*136:*/
#line 3144 "lossless.w"

cell
rope_node_new_length(bool sinward,
bool dexward,
long length,
cell nsin,
cell ndex,
sigjmp_buf*failure)
{
static int Snsin= 1,Sndex= 0;
cell r;
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

assert(null_p(nsin)||rope_p(nsin));
assert(null_p(nsin)||rope_p(ndex));
if(ckd_add(&length,length,1))
siglongjmp(*failure,LERR_LIMIT);
stack_protect(2,nsin,ndex,failure);
if(failure_p(reason= sigsetjmp(cleanup,1)))
unwind(failure,reason,false,2);
r= segment_new(sizeof(Orope),length,0,0,&cleanup);
r= dryad_node_new(false,sinward,dexward,r,SO(Snsin),
SO(Sndex),&cleanup);
rope_cplength(r)= rope_glength(r)= -1;
rope_buffer(r)[length-1]= '\0';
stack_clear(2);
return r;
}

/*:136*//*137:*/
#line 3174 "lossless.w"

cell
rope_node_new_clone(bool sinward,
bool dexward,
cell o,
cell nsin,
cell ndex,
sigjmp_buf*failure)
{
static int Sobject= 2,Snsin= 1,Sndex= 0;
cell r;
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

assert(rope_p(o));
assert(null_p(nsin)||rope_p(nsin));
assert(null_p(nsin)||rope_p(ndex));
stack_protect(3,o,nsin,ndex,failure);
if(failure_p(reason= sigsetjmp(cleanup,1)))
unwind(failure,reason,false,3);
r= dryad_node_new(false,sinward,dexward,rope_segment(SO(Sobject)),
SO(Snsin),SO(Sndex),&cleanup);
rope_buffer(r)[segment_length(rope_segment(SO(Sobject)))]= '\0';
stack_clear(3);
return r;
}

/*:137*//*138:*/
#line 3205 "lossless.w"

cell
rope_new_buffer(bool thread_sin,
bool thread_dex,
const char*buffer,
long length,
sigjmp_buf*failure)
{
char*dst;
cell r;
int i;

r= rope_new_length(thread_sin,thread_dex,length,failure);
dst= rope_buffer(r);
for(i= 0;i<length;i++)
dst[i]= buffer[i];
return r;
}

/*:138*//*139:*/
#line 3227 "lossless.w"

cell
rope_new_ascii(bool thread_sin,
bool thread_dex,
char*buffer,
long length,
sigjmp_buf*failure)
{
cell r;

r= rope_new_buffer(thread_sin,thread_dex,buffer,length,failure);
rope_cplength(r)= length;
return r;
}

/*:139*//*140:*/
#line 3242 "lossless.w"

cell
rope_new_utfo(bool thread_sin Lunused,
bool thread_dex Lunused,
char*buffer Lunused,
long length Lunused,
sigjmp_buf*failure Lunused)
{
siglongjmp(*failure,LERR_UNIMPLEMENTED);
}

/*:140*//*143:*/
#line 3275 "lossless.w"

cell
rope_iterate_start(cell o,
long begin,
sigjmp_buf*failure)
{
static int Sobject= 0;
cell r= NIL,twine;
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

assert(rope_p(o));
stack_protect(1,o,failure);
if(failure_p(reason= sigsetjmp(cleanup,1)))
unwind(failure,reason,false,1);
r= record_new(fix(RECORD_ROPE_ITERATOR),ROPE_ITER_LENGTH,
sizeof(Orope_iter),&cleanup);
twine= SO(Sobject);
if(begin<0){
twine= rope_first(twine,&cleanup);
begin= 0;
}
rope_iter_set_twine_m(r,twine);
rope_iter(r)->bvalue= rope_iter(r)->cpoffset= 0;
rope_iter(r)->tboffset= rope_iter(r)->boffset= begin;
stack_clear(1);
return r;
}

/*:143*//*144:*/
#line 3304 "lossless.w"

int
rope_iterate_next_byte(cell o,
sigjmp_buf*failure)
{
cell twine;

assert(rope_iter_p(o));
twine= rope_iter_twine(o);
if(null_p(twine))
siglongjmp(*failure,LERR_EOF);
while(rope_iter(o)->tboffset==rope_blength(twine)){
twine= rope_next(twine,failure);
rope_iter_set_twine_m(o,twine);
rope_iter(o)->tboffset= 0;
if(null_p(twine))
return EOF;
}
rope_iter(o)->bvalue= rope_buffer(twine)[rope_iter(o)->tboffset++];
rope_iter(o)->boffset++;
return rope_iter(o)->bvalue;
}

/*:144*//*145:*/
#line 3331 "lossless.w"

cell
rope_iterate_next_utfo(cell o,
sigjmp_buf*failure)
{
int c;
cell r,start,twine;
Vutfio_parse res,(*readchar)(Outfio*,char);

assert(rope_iter_p(o));
twine= rope_iter_twine(o);
if(rope_p(twine)&&rope_cplength(twine)>=0)
readchar= utfio_reread;
else
readchar= utfio_read;
start= twine;
rope_iter(o)->cp= utfio_scan_start();
r= VOID;
while(void_p(r)){
c= rope_iter(o)->bvalue= rope_iterate_next_byte(o,failure);
if(c==EOF){
rope_iter(o)->cp.status= UTFIO_EOF;
if(!rope_iter(o)->cp.remaining)
return LEOF;
break;
}
res= readchar(&rope_iter(o)->cp,c);
if(res==UTFIO_COMPLETE||res!=UTFIO_PROGRESS)
break;
}
if(rope_iter_twine(o)!=start)
rope_iter(o)->cp.status= UTFIO_PROGRESS;
rope_iter(o)->cpoffset++;
return rune_new_utfio(rope_iter(o)->cp,failure);
}

/*:145*//*151:*/
#line 3392 "lossless.w"

void
stack_push(cell o,
sigjmp_buf*failure)
{
if(StackP==array_length(Stack)){
Stack_Tmp= o;
Stack= array_grow_m(Stack,STACK_CHUNK,NIL,failure);
o= Stack_Tmp;
Stack_Tmp= NIL;
}
array_set_m(Stack,++StackP,o);
}

/*:151*//*152:*/
#line 3407 "lossless.w"

cell
stack_pop(long num,
sigjmp_buf*failure)
{
cell r;

assert(num>=1);
r= stack_ref(num-1,failure);
StackP-= num;
return r;
}

/*:152*//*153:*/
#line 3421 "lossless.w"

cell
stack_ref(long offset,
sigjmp_buf*failure)
{
cell r= NIL;

assert(offset>=0);
assert(failure!=NULL||StackP>=offset);
if(StackP<offset)
siglongjmp(*failure,LERR_UNDERFLOW);
else
r= array_ref(Stack,StackP-offset);
return r;
}

/*:153*//*154:*/
#line 3438 "lossless.w"

void
stack_set_m(long offset,
cell datum,
sigjmp_buf*failure)
{
assert(offset>=0);
assert(failure!=NULL||StackP>=offset);
if(StackP<offset)
siglongjmp(*failure,LERR_UNDERFLOW);
else
array_set_m(Stack,StackP-offset,datum);
}

/*:154*//*155:*/
#line 3452 "lossless.w"

cell
stack_ref_abs(long offset,
sigjmp_buf*failure)
{
cell r= NIL;

assert(offset>=0);
assert(failure!=NULL||StackP>=offset);
if(StackP<offset)
siglongjmp(*failure,LERR_UNDERFLOW);
else
r= array_ref(Stack,offset);
return r;
}

/*:155*//*156:*/
#line 3468 "lossless.w"

void
stack_set_abs_m(long offset,
cell datum,
sigjmp_buf*failure)
{
assert(offset>=0);
assert(failure!=NULL||StackP>=offset);
if(StackP<offset)
siglongjmp(*failure,LERR_UNDERFLOW);
else
array_set_m(Stack,offset,datum);
}

/*:156*//*157:*/
#line 3482 "lossless.w"

void
stack_reserve(int delta,
sigjmp_buf*failure)
{
int i;

while(array_length(Stack)-(StackP+1)<delta)
Stack= array_grow_m(Stack,STACK_CHUNK,NIL,failure);
StackP+= delta;
for(i= 0;i<delta;i++)
array_set_m(Stack,StackP-i,NIL);
}

/*:157*//*159:*/
#line 3499 "lossless.w"

void
stack_protect(int num,
...)
{
va_list ap;
int i;
sigjmp_buf cleanup,*failure;
Verror reason= LERR_NONE;

assert(num> 0&&num<=4);
va_start(ap,num);
for(i= 0;i<num;i++)
Protect[i]= va_arg(ap,cell);
failure= va_arg(ap,sigjmp_buf*);
va_end(ap);
if(failure_p(reason= sigsetjmp(cleanup,1)))
goto fail;
stack_reserve(num,&cleanup);
for(i= 0;i<num;i++){
SS(num-(i+1),Protect[i]);
Protect[i]= NIL;
}
return;
fail:
for(i= 0;i<num;i++)
Protect[i]= NIL;
siglongjmp(*failure,reason);
}

/*:159*//*162:*/
#line 3549 "lossless.w"

cell
env_new_imp(cell o,
sigjmp_buf*failure)
{
static int Sobject= 0;
cell r= NIL;
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

stack_protect(1,o,failure);
if(failure_p(reason= sigsetjmp(cleanup,1)))
unwind(failure,reason,false,1);
r= keytable_new(0,&cleanup);
r= atom(Theap,SO(Sobject),r,FORM_ENVIRONMENT,&cleanup);
stack_clear(1);
return r;
}

/*:162*//*163:*/
#line 3568 "lossless.w"

cell
env_extend(cell o,
sigjmp_buf*failure)
{
assert(environment_p(o));
return env_new_imp(o,failure);
}

/*:163*//*164:*/
#line 3577 "lossless.w"

Vhash
env_rehash(cell o,
sigjmp_buf*failure Lunused)
{
assert(pair_p(o)&&symbol_p(lcar(o)));
return symbol_hash(lcar(o));
}

/*:164*//*165:*/
#line 3586 "lossless.w"

int
env_match(cell binding,
void*ctx,
sigjmp_buf*failure Lunused)
{
cell maybe= (cell)ctx;

assert(symbol_p(maybe));
assert(pair_p(binding));
assert(symbol_p(lcar(binding)));
return lcar(binding)==maybe?0:-1;
}

/*:165*//*166:*/
#line 3600 "lossless.w"

cell
env_set_imp(cell where,
cell label,
cell datum,
bool new_p,
sigjmp_buf*failure)
{
static int Swhere= 3,Slabel= 2,Sdatum= 1,Stable= 0;
cell table,r= NIL;
Vhash hash;
long idx;
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

assert(environment_p(where));
assert(symbol_p(label));

stack_protect(4,where,label,datum,NIL,failure);
if(failure_p(reason= sigsetjmp(cleanup,1)))
unwind(failure,reason,false,4);
hash= symbol_hash(SO(Slabel));
again:
SS(Stable,(table= env_layer(SO(Swhere))));
idx= keytable_search(table,hash,env_match,(void*)SO(Slabel),&cleanup);
if(idx==FAIL||null_p(keytable_ref(table,idx))){
if(!new_p)
siglongjmp(*failure,LERR_MISSING);
if(!keytable_free_p(table)){
table= keytable_enlarge_m(table,env_rehash,&cleanup);
env_replace_layer_m(SO(Swhere),table);
goto again;
}
}else if(new_p)
siglongjmp(*failure,LERR_EXISTS);
r= cons(SO(Slabel),SO(Sdatum),&cleanup);
keytable_save_m(SO(Stable),idx,r);
r= keytable_ref(SO(Stable),idx);
stack_clear(4);
return r;
}

/*:166*//*167:*/
#line 3642 "lossless.w"

cell
env_define(cell where,
cell label,
cell datum,
sigjmp_buf*failure)
{
assert(defined_p(datum));
return env_set_imp(where,label,datum,true,failure);
}

/*:167*//*168:*/
#line 3653 "lossless.w"

cell
env_set(cell where,
cell label,
cell datum,
sigjmp_buf*failure)
{
assert(defined_p(datum));
return env_set_imp(where,label,datum,false,failure);
}

/*:168*//*169:*/
#line 3664 "lossless.w"

cell
env_unset(cell where,
cell label,
sigjmp_buf*failure)
{
return env_set_imp(where,label,UNDEFINED,false,failure);
}

/*:169*//*170:*/
#line 3673 "lossless.w"

void
env_clear(cell where,
cell label,
sigjmp_buf*failure)
{
cell table;
Vhash hash;
long idx;

assert(environment_p(where));
assert(symbol_p(label));
hash= symbol_hash(label);
table= env_layer(where);
idx= keytable_search(table,hash,env_match,(void*)label,failure);
if(idx!=FAIL&&!null_p(keytable_ref(table,idx)))
keytable_remove_m(table,idx);
}

/*:170*//*171:*/
#line 3692 "lossless.w"

cell
env_here(cell haystack,
cell needle,
sigjmp_buf*failure)
{
cell r= NIL;
long idx;

assert(environment_p(haystack));
assert(symbol_p(needle));
idx= keytable_search(env_layer(haystack),symbol_hash(needle),
env_match,(void*)needle,failure);
if(idx==FAIL)
return NIL;
r= keytable_ref(env_layer(haystack),idx);
if(null_p(r)||undefined_p(lcdr(r)))
return NIL;
else
return r;
}

/*:171*//*172:*/
#line 3715 "lossless.w"

cell
env_search(cell haystack,
cell needle,
bool ascend,
sigjmp_buf*failure)
{
cell r;

assert(environment_p(haystack));
assert(symbol_p(needle));
for(;!null_p(haystack);haystack= env_previous(haystack)){
r= env_here(haystack,needle,failure);
if(!null_p(r))
return lcdr(r);
else if(!ascend)
break;
}
return UNDEFINED;
}

/*:172*//*174:*/
#line 3759 "lossless.w"

int
flag2base(int f)
{
f|= 5;
f++;
f= (f&~2)|(((f&8)>>2)^(f&2));
f= (f&~8)|((f&4)<<1);
return f&26;
}

/*:174*//*175:*/
#line 3773 "lossless.w"

int
base2flag(int b)
{
if(b==10)
return 0;
else if(b==16)
return 10;
else
return b;
}

/*:175*//*180:*/
#line 3857 "lossless.w"

cell
lexeme_new(Vlexicat cat,
char flags,
cell twine,
long tboffset,
long blength,
long cpstart,
long cplength,
sigjmp_buf*failure)
{
static int Stwine= 0;
cell r;
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

assert(null_p(twine)||rope_p(twine));
stack_protect(1,twine,failure);
if(failure_p(reason= sigsetjmp(cleanup,1)))
unwind(failure,reason,false,1);
r= record_new(fix(RECORD_LEXEME),LEXEME_LENGTH,sizeof(Olexeme),
&cleanup);
lexeme_set_twine_m(r,SO(Stwine));
lexeme(r)->cat= cat;
lexeme(r)->flags= flags;
lexeme(r)->tboffset= tboffset;
lexeme(r)->blength= blength;
lexeme(r)->cpstart= cpstart;
lexeme(r)->cplength= cplength;
stack_clear(1);
return r;
}

/*:180*//*181:*/
#line 3913 "lossless.w"

cell
syntax_new_imp(cell datum,
cell note,
cell start,
cell end,
bool valid,
sigjmp_buf*failure)
{
static int Sdatum= 3,Snote= 2,Sstart= 1,Send= 0;
cell r= NIL;
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

assert(defined_p(datum));
assert(null_p(note)||symbol_p(note));
assert(dlist_p(start)&&lexeme_p(dlist_datum(start)));
assert(dlist_p(end)&&lexeme_p(dlist_datum(end)));

stack_protect(4,datum,note,start,end,failure);
if(failure_p(reason= sigsetjmp(cleanup,1)))
unwind(failure,reason,false,4);
r= record_new(fix(RECORD_SYNTAX),SYNTAX_LENGTH,0,&cleanup);
record_set_cell_m(r,SYNTAX_VALID,predicate(valid));
record_set_cell_m(r,SYNTAX_NOTE,SO(Snote));
record_set_cell_m(r,SYNTAX_DATUM,SO(Sdatum));
record_set_cell_m(r,SYNTAX_START,SO(Sstart));
record_set_cell_m(r,SYNTAX_END,SO(Send));
stack_clear(4);
return r;
}

/*:181*//*183:*/
#line 3984 "lossless.w"

cell
note_new(cell label,
cell ncar,
cell ncdr,
sigjmp_buf*failure)
{
static int Slabel= 3,Sncar= 2,Sncdr= 1,Stmp= 0;
cell r;
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

assert(symbol_p(label));
assert(defined_p(ncar)&&defined_p(ncdr));
stack_protect(4,label,ncar,ncdr,NIL,failure);
if(failure_p(reason= sigsetjmp(cleanup,1)))
unwind(failure,reason,false,4);
SS(Stmp,cons(SO(Sncar),SO(Sncdr),&cleanup));
r= atom(Theap,SO(Slabel),SO(Stmp),FORM_NOTE,&cleanup);
stack_clear(4);
return r;
}

/*:183*//*185:*/
#line 4036 "lossless.w"

cell
closure_new(bool is_applicative,
cell formals,
cell environment,
cell body,
sigjmp_buf*failure)
{
static int Sformals= 3,Senv= 2,Sbody= 1,Sret= 0;
cell r;
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

stack_protect(4,formals,environment,body,NIL,failure);
if(failure_p(reason= sigsetjmp(cleanup,1)))
unwind(failure,reason,false,4);
SS(Sret,cons(SO(Sbody),SO(Sret),&cleanup));
SS(Sret,cons(SO(Senv),SO(Sret),&cleanup));
SS(Sret,atom(Theap,SO(Sformals),SO(Sret),
is_applicative?FORM_APPLICATIVE:FORM_OPERATIVE,&cleanup));
r= SO(Sret);
stack_clear(4);
return r;
}

/*:185*//*192:*/
#line 4205 "lossless.w"

cell
lexar_start(cell o,
sigjmp_buf*failure)
{
static int Srope= 1,Sret= 0;
cell r;
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

assert(rope_p(o));
stack_protect(2,o,NIL,failure);
if(failure_p(reason= sigsetjmp(cleanup,1)))
unwind(failure,reason,false,2);
SS(Sret,record_new(fix(RECORD_LEXAR),LEXAR_LENGTH,
sizeof(Olexical_analyser),&cleanup));
lexar_set_iterator_m(SO(Sret),rope_iterate_start(SO(Srope),-1,
&cleanup));
lexar_set_starter_m(SO(Sret),NIL);
lexar_set_peeked_twine_m(SO(Sret),VOID);
lexar_set_backput_twine_m(SO(Sret),VOID);
r= SO(Sret);
lexar(r)->tbstart= lexar(r)->blength= 
lexar(r)->cpstart= lexar(r)->cplength= 0;
stack_clear(2);
return r;
}

/*:192*//*193:*/
#line 4237 "lossless.w"

cell
lexar_clone(cell o,
sigjmp_buf*failure)
{
static int Slexar= 1,Sret= 0;
cell r,tmp;
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

assert(lexar_p(o));
stack_protect(2,o,NIL,failure);
if(failure_p(reason= sigsetjmp(cleanup,1)))
unwind(failure,reason,false,2);
SS(Sret,r= record_new(fix(RECORD_LEXAR),LEXAR_LENGTH,
sizeof(Olexical_analyser),&cleanup));
tmp= lexar_starter(SO(Slexar));
lexar_set_starter_m(r,tmp);
tmp= rope_iterate_start(tmp,lexar(SO(Slexar))->tbstart,&cleanup);
r= SO(Sret);
lexar_set_iterator_m(r,tmp);
lexar_set_peeked_twine_m(r,VOID);
lexar_set_backput_twine_m(r,VOID);
*lexar(r)= *lexar(SO(Slexar));
stack_clear(2);
return r;
}

/*:193*//*194:*/
#line 4282 "lossless.w"

cell
lexar_peek(int Silex,
sigjmp_buf*failure)
{
cell irope,ilex,r,tmp;

assert(lexar_p(SO(Silex)));
ilex= SO(Silex);
irope= lexar_iterator(ilex);
if(null_p(lexar_starter(ilex)))
lexar_reset(ilex,irope);
if(!void_p(lexar_backput_twine(ilex))){
assert(void_p(lexar_peeked_twine(ilex)));
if(!eof_p(lexar_backput_rune(ilex))){
lexar(ilex)->tbstart-= rune_parsed(lexar_backput_rune(ilex));
lexar(ilex)->cpstart-= 1;
}
lexar_set_peeked_twine_m(ilex,lexar_backput_twine(ilex));
lexar_set_peeked_rune_m(ilex,lexar_backput_rune(ilex));
lexar_set_backput_twine_m(ilex,VOID);
}else if(void_p(lexar_peeked_twine(ilex))){
tmp= rope_iterate_next_utfo(irope,failure);
lexar_set_peeked_rune_m(SO(Silex),tmp);
lexar_set_peeked_twine_m(SO(Silex),rope_iter_twine(irope));
}else
return lexar_peeked_rune(ilex);

r= lexar_peeked_rune(ilex);
if(!eof_p(r)){
lexar(ilex)->cplength++;
lexar(ilex)->blength+= rune_parsed(r);
}
return r;
}

/*:194*//*195:*/
#line 4321 "lossless.w"

cell
lexar_take(int Silex,
sigjmp_buf*failure)
{
cell r;

assert(lexar_p(SO(Silex)));
assert(void_p(lexar_backput_twine(SO(Silex))));
r= lexar_peek(Silex,failure);
lexar_set_peeked_twine_m(SO(Silex),VOID);
return r;
}

/*:195*//*196:*/
#line 4340 "lossless.w"

void
lexar_putback(int Silex)
{
cell tmp;

assert(lexar_p(SO(Silex)));
assert(!void_p(lexar_peeked_twine(SO(Silex))));
assert(void_p(lexar_backput_twine(SO(Silex))));
tmp= lexar_peeked_rune(SO(Silex));
if(!eof_p(tmp)){
lexar(SO(Silex))->cplength--;
lexar(SO(Silex))->blength-= rune_parsed(tmp);
}
lexar_set_backput_rune_m(SO(Silex),tmp);
lexar_set_backput_twine_m(SO(Silex),lexar_peeked_twine(SO(Silex)));
lexar_set_peeked_twine_m(SO(Silex),VOID);
}

/*:196*//*197:*/
#line 4368 "lossless.w"

cell
lexar_append(int Silex,
int Sret,
Vlexicat cat,
int flags,
sigjmp_buf*failure)
{
cell r= NIL,tmp;
Olexical_analyser*l;

assert(lexar_p(SO(Silex)));
if((cat==LEXICAT_SPACE||cat==LEXICAT_INVALID)&&
(tmp= dlist_datum(SO(Sret)),lexeme_p(tmp))&&
lexeme(tmp)->cat==cat&&lexeme(tmp)->flags==flags){
lexeme(tmp)->blength+= lexar(SO(Silex))->blength;
lexeme(tmp)->cplength+= lexar(SO(Silex))->cplength;
r= SO(Sret);
}else{
l= lexar(SO(Silex));
tmp= lexeme_new(cat,flags,lexar_starter(SO(Silex)),
l->tbstart,l->blength,l->cpstart,l->cplength,failure);
r= dlist_append_datum_m(SO(Sret),tmp,failure);
SS(Sret,r);
}
l= lexar(SO(Silex));
if(!void_p(lexar_peeked_twine(SO(Silex))))
lexar_take(Silex,failure);
l->blength= l->cplength= 0;
lexar_set_starter_m(SO(Silex),NIL);
return dlist_datum(r);
}

/*:197*//*198:*/
#line 4424 "lossless.w"

cell
lexar_token(int Silex,
int Sret,
sigjmp_buf*failure)
{
static int Ssdelim= 3;

static int Sedelim= 2;
static int Srdelim= 1;

static int Sditer= 0;

cell c;
int32_t d,v;

int base= 10;
int has_imagination= 0;
int has_sign= 0;

int has_ratio= 0;
int flags= 0;
int want_digit= MUST;
Vlexicat cat= LEXICAT_NONE;
Orope_iter*irope,*idelim;

sigjmp_buf cleanup;
Verror reason= LERR_NONE;
cell r,tmp;
int i;

/*199:*/
#line 4475 "lossless.w"

c= lexar_peek(Silex,failure);
if(eof_p(c))
return lexar_append(Silex,Sret,LEXICAT_END,LLF_NONE,failure);
else if(rune_failure(c)==UTFIO_EOF)
goto LEXAR_premature_eof;
else if(rune_failure_p(c))
return lexar_append(Silex,Sret,LEXICAT_INVALID,LLF_NONE,failure);
else
switch(rune(c)){
/*200:*/
#line 4508 "lossless.w"

case' ':
case'\t':
return lexar_append(Silex,Sret,LEXICAT_SPACE,LLF_HORIZONTAL,failure);
case'\r':
case'\n':
return lexar_append(Silex,Sret,LEXICAT_SPACE,LLF_VERTICAL,failure);

/*:200*/
#line 4485 "lossless.w"

/*201:*/
#line 4520 "lossless.w"

case'(':
case'[':
case'{':
return lexar_append(Silex,Sret,LEXICAT_OPEN,LLF_NONE,failure);
case'.':
return lexar_append(Silex,Sret,LEXICAT_DOT,LLF_NONE,failure);
case')':
case']':
case'}':
return lexar_append(Silex,Sret,LEXICAT_CLOSE,LLF_NONE,failure);

/*:201*/
#line 4486 "lossless.w"

/*202:*/
#line 4544 "lossless.w"

default:
while(1){
if(Interrupt)
siglongjmp(*failure,LERR_INTERRUPT);
lexar_take(Silex,failure);
symbol:
tmp= lexar_peek(Silex,failure);
if(lexar_terminator_p(tmp)){
lexar_putback(Silex);
return lexar_append(Silex,Sret,LEXICAT_SYMBOL,
LLF_NONE,failure);
}
}
break;

/*:202*/
#line 4487 "lossless.w"

/*203:*/
#line 4569 "lossless.w"

case'\'':
case'"':
return lexar_append(Silex,Silex,LEXICAT_INVALID,LLF_NONE,failure);
case'|':
cat= LEXICAT_ESCAPED_STRING;
string:

lexar_take(Silex,failure);
while(1){
if(Interrupt)
siglongjmp(*failure,LERR_INTERRUPT);
lexar_another(c,Silex,true,true,LEXAR_premature_eof,Sret,failure);
if(rune(c)=='|')
return lexar_append(Silex,Sret,cat,LLF_NONE,failure);
else if(rune(c)=='#'){
lexar_another(c,Silex,true,true,LEXAR_premature_eof,Sret,failure);
switch(rune(c)){
/*204:*/
#line 4631 "lossless.w"

case'#':case'|':
break;
case'o':case'O':
for(i= 0;i<3;i++)
lexar_detect_octal(c,Silex,cat,Sret,failure);
break;
case'x':case'X':
for(i= 0;i<2;i++)
lexar_detect_hexadecimal(c,Silex,cat,Sret,failure);
break;
case'u':case'U':
for(i= 0;i<4;i++)
lexar_detect_hexadecimal(c,Silex,cat,Sret,failure);
break;
case'(':
lexar_detect_hexadecimal(c,Silex,cat,Sret,failure);
for(i= 5;i;i--)
lexar_another(c,Silex,true,true,
LEXAR_premature_eof,Sret,failure);
if(rune(c)==')')
break;
else
lexar_detect_hexadecimal(c,Silex,cat,
Sret,failure);
if(!i&&cat!=LEXICAT_INVALID)
lexar_another(c,Silex,true,true,
LEXAR_premature_eof,Sret,failure);
if(rune(c)!=')')
cat= LEXICAT_INVALID;
break;
default:
cat= LEXICAT_INVALID;
break;

/*:204*/
#line 4587 "lossless.w"

}
}
}
break;

/*:203*//*205:*/
#line 4679 "lossless.w"

case'$':
cat= LEXICAT_RAW_STRING;
delimiter:
/*206:*/
#line 4700 "lossless.w"

lexar_take(Silex,failure);
while(1){
if(Interrupt)
siglongjmp(*failure,LERR_INTERRUPT);
lexar_another(c,Silex,true,false,LEXAR_premature_eof,Sret,failure);
v= rune(c);
if(v=='$')
break;
else if(!((v>='a'&&v<='z')||(v>='A'&&v<='Z')||
(v>='0'&&v<='9')||v=='_'||v=='-'))
return lexar_append(Silex,Sret,LEXICAT_INVALID,LLF_NONE,failure);
}

/*:206*/
#line 4683 "lossless.w"

stack_reserve(4,failure);
if(failure_p(reason= sigsetjmp(cleanup,1)))
unwind(failure,reason,false,4);
Silex+= 4;
Sret+= 4;
tmp= lexar_append(Silex,Sret,LEXICAT_DELIMITER,LLF_NONE,&cleanup);
lexar_reset(SO(Silex),lexar_iterator(SO(Silex)));
SS(Ssdelim,tmp);
/*207:*/
#line 4719 "lossless.w"

lexar(SO(Silex))->tbstart= rope_iter(lexar_iterator(SO(Silex)))->tboffset;
while(1){
if(Interrupt)
siglongjmp(cleanup,LERR_INTERRUPT);
tmp= lexar_clone(SO(Silex),&cleanup);

SS(Sedelim,tmp);
v= rope_iterate_next_byte(lexar_iterator(SO(Silex)),&cleanup);
lexar(SO(Silex))->blength++;
if(v==EOF)
goto LEXAR_raw_eof;
else if(v!='$')
continue;
redelimiter:
/*208:*/
#line 4755 "lossless.w"

tmp= rope_iterate_start(lexeme_twine(SO(Ssdelim)),
lexeme(SO(Ssdelim))->tboffset,&cleanup);
SS(Sditer,tmp);
rope_iterate_next_byte(tmp,failure);

while(1){
if(Interrupt)
siglongjmp(cleanup,LERR_INTERRUPT);
SS(Srdelim,lexar_clone(SO(Silex),&cleanup));

v= rope_iterate_next_byte(lexar_iterator(SO(Silex)),failure);
if(v==EOF)
goto LEXAR_raw_eof;
else{
lexar(SO(Silex))->cplength++;
d= rope_iterate_next_byte(SO(Sditer),&cleanup);
if(v!=d){
if(v=='$'){
SS(Sedelim,SO(Srdelim));
lexar(SO(Silex))->blength+= lexar(SO(Silex))->cplength;
lexar(SO(Silex))->cplength= 0;
goto redelimiter;
}else
break;
}else if(v=='$')
goto delimited;
}
}
lexar(SO(Silex))->blength+= lexar(SO(Silex))->cplength;
lexar(SO(Silex))->cplength= 0;

/*:208*/
#line 4734 "lossless.w"

}
delimited:
/*209:*/
#line 4795 "lossless.w"

irope= rope_iter(lexar_iterator(SO(Silex)));
idelim= rope_iter(lexar_iterator(SO(Sedelim)));
lexar(SO(Silex))->cplength++;
lexar(SO(Silex))->blength= lexar(SO(Silex))->cplength;
lexar(SO(Silex))->tbstart+= lexar(SO(Sedelim))->blength;
lexar(SO(Sedelim))->cplength= 0;
lexar_append(Sedelim,Sret,cat,LLF_NONE,&cleanup);
r= lexar_append(Silex,Sret,LEXICAT_DELIMITER,LLF_NONE,&cleanup);
stack_clear(4);
return r;

/*:209*/
#line 4737 "lossless.w"


/*:207*/
#line 4692 "lossless.w"


/*:205*/
#line 4488 "lossless.w"

/*210:*/
#line 4834 "lossless.w"

case'#':
lexar_take(Silex,failure);
lexar_another(c,Silex,true,false,LEXAR_premature_eof,Sret,
failure);
switch(rune(c)){
/*214:*/
#line 4931 "lossless.w"

case'b':case'B':
if(1)base= 2;
else
case'd':case'D':
if(1)base= 10;
else
case'o':case'O':
if(1)base= 8;
else
case'x':case'X':
if(1)base= 16;
flags= has_sign|base2flag(base);
lexar_append(Silex,Sret,LEXICAT_CURIOUS,flags,failure);
want_digit= MUST;
goto number;

/*:214*/
#line 4840 "lossless.w"

case'f':case'F':
case't':case'T':
return lexar_append(Silex,Sret,LEXICAT_CONSTANT,
LLF_NONE,failure);
case'=':
return lexar_append(Silex,Sret,LEXICAT_RECURSE_IS,
LLF_NONE,failure);
case'#':
return lexar_append(Silex,Sret,LEXICAT_RECURSE_HERE,
LLF_NONE,failure);
case'$':
cat= LEXICAT_RAW_SYMBOL;
goto delimiter;
case'|':
cat= LEXICAT_ESCAPED_SYMBOL;
goto string;
default:
return lexar_append(Silex,Sret,LEXICAT_INVALID,
LLF_NONE,failure);
}
break;

/*:210*/
#line 4489 "lossless.w"

/*211:*/
#line 4875 "lossless.w"

case'-':
case'+':
has_sign= (c=='-')?LLF_NEGATIVE:LLF_POSITIVE;
lexar_take(Silex,failure);
lexar_another(c,Silex,false,false,false_symbol,Sret,
failure);
switch(rune(c)){
/*212:*/
#line 4889 "lossless.w"

case'0':case'1':case'2':case'3':case'4':
case'5':case'6':case'7':case'8':case'9':
want_digit= CAN;
goto number;

/*:212*//*213:*/
#line 4899 "lossless.w"

case'#':
lexar_take(Silex,failure);
lexar_another(c,Silex,true,false,LEXAR_premature_eof,Sret,failure);
switch(rune(c)){
/*214:*/
#line 4931 "lossless.w"

case'b':case'B':
if(1)base= 2;
else
case'd':case'D':
if(1)base= 10;
else
case'o':case'O':
if(1)base= 8;
else
case'x':case'X':
if(1)base= 16;
flags= has_sign|base2flag(base);
lexar_append(Silex,Sret,LEXICAT_CURIOUS,flags,failure);
want_digit= MUST;
goto number;

/*:214*/
#line 4904 "lossless.w"

}
return lexar_append(Silex,Sret,LEXICAT_INVALID,LLF_NONE,failure);
case'.':
lexar_take(Silex,failure);
has_ratio= LLF_DOT;
want_digit= MUST;
lexar_another(c,Silex,false,false,noisy_false_symbol,Sret,failure);
v= rune(c);
if(v>='0'&&v<='9')
goto number;
goto noisy_false_symbol;
WARN();

/*:213*//*215:*/
#line 4952 "lossless.w"

case'i':case'I':
lexar_take(Silex,failure);
lexar_another(c,Silex,false,false,noisy_false_symbol,Sret,
failure);
v= rune(c);
if(v=='n'||v=='N'){
lexar_take(Silex,failure);
lexar_another(c,Silex,false,false,false_symbol,Sret,
failure);
v= rune(c);
if(v=='f'||v=='F')
goto infinity;
}
goto false_symbol;
case UCP_INFINITY:
goto infinity;

/*:215*//*216:*/
#line 4974 "lossless.w"

case'n':case'N':
lexar_take(Silex,failure);
lexar_another(c,Silex,false,false,noisy_false_symbol,Sret,
failure);
v= rune(c);
if(v=='a'||v=='A'){
lexar_take(Silex,failure);
lexar_another(c,Silex,false,false,false_symbol,Sret,
failure);
v= rune(c);
if(v=='n'||v=='N')
goto nan;
}
goto false_symbol;
case UCP_NAN_0:
lexar_take(Silex,failure);
lexar_another(c,Silex,false,false,noisy_false_symbol,Sret,
failure);
if(rune(c)==UCP_NAN_1)
goto nan;
goto noisy_false_symbol;

/*:216*//*217:*/
#line 5005 "lossless.w"

noisy_false_symbol:
WARN();
default:
false_symbol:
lexar_putback(Silex);
goto symbol;

/*:217*/
#line 4883 "lossless.w"

}

/*:211*//*219:*/
#line 5031 "lossless.w"

case UCP_NAN_0:
lexar_take(Silex,failure);
lexar_another(c,Silex,false,false,false_symbol,Sret,failure);
if(rune(c)!=UCP_NAN_1)
goto noisy_false_symbol;
nan:
lexar_take(Silex,failure);
lexar_another(c,Silex,false,false,LEXAR_premature_eof,Sret,
failure);
if(rune(c)=='.')
has_ratio= LLF_DOT;
else
cat= LEXICAT_INVALID;
want_digit= MUST;
goto number;

/*:219*//*220:*/
#line 5050 "lossless.w"

case UCP_INFINITY:
infinity:
lexar_take(Silex,failure);
has_ratio= LLF_RATIO;
want_digit= CANNOT;
goto number;

/*:220*//*221:*/
#line 5062 "lossless.w"

case'0':case'1':case'2':case'3':case'4':
case'5':case'6':case'7':case'8':case'9':
want_digit= CAN;
number:
lexar_take(Silex,failure);
while(1){
if(Interrupt)
siglongjmp(*failure,LERR_INTERRUPT);
lexar_another(c,Silex,false,false,finish,Sret,failure);
switch((v= rune(c))){
/*222:*/
#line 5093 "lossless.w"

case'a':case'b':case'c':case'd':case'e':case'f':
case'A':case'B':case'C':case'D':case'E':case'F':
if(base<16)cat= LEXICAT_INVALID;
case'9':case'8':
if(base<10)cat= LEXICAT_INVALID;
case'7':case'6':case'5':
case'4':case'3':case'2':
if(base<8)cat= LEXICAT_INVALID;
case'1':case'0':
lexar_take(Silex,failure);
if(want_digit<CAN)cat= LEXICAT_INVALID;
want_digit= CAN;
break;
case'_':
lexar_take(Silex,failure);
if(want_digit!=CAN)cat= LEXICAT_INVALID;
want_digit= MUST;
break;

/*:222*//*223:*/
#line 5117 "lossless.w"

case'/':
if(has_ratio)
cat= LEXICAT_INVALID;
else if(1)
has_ratio= LLF_SLASH;
else
case'.':
if(has_ratio)
cat= LEXICAT_INVALID;
else if(1)
has_ratio= LLF_DOT;
lexar_take(Silex,failure);
want_digit= MUST;
break;

/*:223*//*224:*/
#line 5140 "lossless.w"

case'i':
case'j':
case'k':
lexar_take(Silex,failure);
has_imagination= LLF_IMAGINATE(v-'i');
goto finish;

/*:224*//*226:*/
#line 5152 "lossless.w"

default:
lexar_putback(Silex);
if(!lexar_terminator_p(c))
cat= LEXICAT_INVALID;
goto finish;

/*:226*/
#line 5073 "lossless.w"

}
}
finish:
if(want_digit==MUST)
cat= LEXICAT_INVALID;
else if(cat==LEXICAT_NONE)
cat= LEXICAT_NUMBER;
flags= has_sign|base2flag(base)|has_imagination;
lexar_append(Silex,Sret,cat,flags,failure);
if(eof_p(c)){
lexar_reset(SO(Silex),lexar_iterator(SO(Silex)));
return lexar_append(Silex,Sret,LEXICAT_END,LLF_NONE,failure);
}
return dlist_datum(SO(Sret));

/*:221*/
#line 4490 "lossless.w"

}
abort();

LEXAR_raw_eof:
stack_clear(4);
Silex-= 4;
Sret-= 4;

LEXAR_premature_eof:
lexar_append(Silex,Sret,LEXICAT_INVALID,LLF_NONE,failure);
tmp= rope_iter_twine(lexar_iterator(SO(Silex)));
lexar_set_starter_m(SO(Silex),tmp);
return lexar_append(Silex,Sret,LEXICAT_END,LLF_NONE,failure);

/*:199*/
#line 4455 "lossless.w"

}

/*:198*//*227:*/
#line 5162 "lossless.w"

cell
lex_rope(cell src,
sigjmp_buf*failure)
{
static int Ssource= 3,Siter= 2,Snext= 1,Sret= 0;
cell r= NIL,tmp;
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

assert(rope_p(src));
stack_protect(4,src,NIL,NIL,NIL,failure);
if(failure_p(reason= sigsetjmp(cleanup,1)))
unwind(failure,reason,false,4);
SS(Siter,tmp= lexar_start(SO(Ssource),&cleanup));
SS(Sret,tmp= dlist_new(NIL,&cleanup));
SS(Snext,tmp);
while(1){
tmp= lexar_token(Siter,Snext,&cleanup);
assert(lexeme_p(tmp));
if(lexeme(tmp)->cat==LEXICAT_END)
break;
}
r= dlist_remove_m(SO(Sret));
stack_clear(4);
return r;
}

/*:227*//*229:*/
#line 5225 "lossless.w"

cell
parse(cell llex,
bool*valid,
sigjmp_buf*failure)
{
static int Sstart= 6;
static int Sllex= 5;
static int Senv= 4;

static int Swork= 3;
static int Sbuild= 2;
static int Stmp= 1;
static int Sfail= 0;
cell r,lex,x,y,z;

Vlexicat cat= LEXICAT_NONE;
Verror pfail= LERR_NONE;
char*buf= NULL;
bool has_tail= false,m;

long offset= 0,a,b,c,i;
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

assert(dlist_p(llex));
lex= dlist_datum(dlist_prev(llex));
assert(lexeme_p(lex));
assert(lexeme(lex)->cat==LEXICAT_END);
stack_protect(2,llex,llex,failure);
if(failure_p(reason= sigsetjmp(cleanup,1)))
unwind(failure,reason,false,2);
stack_reserve(5,&cleanup);
if(failure_p(reason= sigsetjmp(cleanup,1)))
unwind(failure,reason,false,7);
SS(Senv,env_empty(&cleanup));
llex= SO(Sllex);
/*230:*/
#line 5275 "lossless.w"

while(cat!=LEXICAT_END){
if(Interrupt)
siglongjmp(*failure,LERR_INTERRUPT);
lex= dlist_datum(llex);
assert(lexeme_p(lex));
cat= lexeme(lex)->cat;
switch(cat){/*231:*/
#line 5304 "lossless.w"

case LEXICAT_SPACE:
break;

case LEXICAT_INVALID:
default:
x= syntax_invalid(lex,llex,llex,&cleanup);
if(cat==LEXICAT_INVALID)
parse_fail(Sfail,LERR_UNSCANNABLE,x,&cleanup);
else
parse_fail(Sfail,LERR_INTERNAL,x,&cleanup);
SS(Swork,cons(x,SO(Swork),&cleanup));
break;

/*:231*//*232:*/
#line 5322 "lossless.w"

case LEXICAT_CONSTANT:
a= lexeme_byte(lex,1);
x= predicate(a=='t'||a=='T');
y= dlist_datum(dlist_next(llex));
if(!lexeme_terminator_p(y)){
z= syntax_invalid(x,llex,llex,&cleanup);
parse_fail(Sfail,LERR_AMBIGUOUS,z,&cleanup);
}else
z= syntax_new(x,llex,llex,&cleanup);
SS(Swork,cons(z,SO(Swork),&cleanup));
break;

/*:232*//*233:*/
#line 5347 "lossless.w"

case LEXICAT_OPEN:
case LEXICAT_DOT:
SS(Swork,cons(llex,SO(Swork),&cleanup));
break;
case LEXICAT_END:
assert(dlist_next(llex)==SO(Sstart));
case LEXICAT_CLOSE:
pfail= LERR_NONE;
has_tail= false;
SS(Sbuild,NIL);
c= 0;
while(1){
/*234:*/
#line 5382 "lossless.w"

c++;
if(Interrupt)
siglongjmp(cleanup,LERR_INTERRUPT);
llex= SO(Sllex);
if(null_p(SO(Swork))){
if(cat!=LEXICAT_END)
parse_fail(Sfail,pfail= LERR_UNOPENED_CLOSE,
llex,&cleanup);
SS(Stmp,SO(Sstart));
break;
}
x= lcar(SO(Swork));
if(!syntax_p(x)){
/*235:*/
#line 5405 "lossless.w"

assert(dlist_p(x)&&lexeme_p(dlist_datum(x)));
x= dlist_datum(x);
if(lexeme(x)->cat==LEXICAT_DOT){
if(lexeme(lex)->cat!=LEXICAT_CLOSE||
lexeme_byte(lex,0)!=')')
parse_fail(Sfail,pfail= LERR_LISTLESS_TAIL,
llex,&cleanup);
else if(has_tail)
parse_fail(Sfail,pfail= LERR_DOUBLE_TAIL,
llex,&cleanup);
else{
has_tail= true;
if(null_p(SO(Sbuild)))
parse_fail(Sfail,pfail= LERR_EMPTY_TAIL,
llex,&cleanup);
else if(!null_p(lcdr(SO(Sbuild))))
parse_fail(Sfail,pfail= LERR_HEAVY_TAIL,
llex,&cleanup);
else{
SS(Sbuild,lcar(SO(Sbuild)));
SS(Swork,lcdr(SO(Swork)));
continue;
}
}
}else{
if(cat==LEXICAT_END)
parse_fail(Sfail,pfail= LERR_UNCLOSED_OPEN,
llex,&cleanup);
else{
/*236:*/
#line 5450 "lossless.w"

lex= dlist_datum(SO(Sllex));
assert(rope_p(lexeme_twine(lex)));
a= lexeme_byte(x,0);
a= ((a+1)&~1)+1;
if(cat==LEXICAT_END)
b= '\0';
else
b= lexeme_byte(lex,0);
if(a!=b)
parse_fail(Sfail,pfail= LERR_MISMATCH,llex,&cleanup);
else if(a==']'){
x= array_new_imp(c,UNDEFINED,FORM_ARRAY,&cleanup);
y= SO(Sbuild);
for(i= 0;i<c;i++,y= lcdr(y))
array_set_m(x,i,lcar(y));
SS(Sbuild,x);
}else if(a=='}')
parse_fail(Sfail,pfail= LERR_UNIMPLEMENTED,llex,&cleanup);

/*:236*/
#line 5435 "lossless.w"

}
SS(Stmp,lcar(SO(Swork)));
SS(Swork,lcdr(SO(Swork)));
break;
}

/*:235*/
#line 5396 "lossless.w"

}
SS(Sbuild,cons(lcar(SO(Swork)),SO(Sbuild),&cleanup));
SS(Swork,lcdr(SO(Swork)));

/*:234*/
#line 5360 "lossless.w"

}
x= SO(Sbuild);
y= SO(Stmp);
z= SO(Sllex);
if(pfail!=LERR_NONE){
SS(Sbuild,syntax_invalid(x,y,z,&cleanup));
x= SO(Sbuild);
parse_fail(Sfail,LERR_SYNTAX,x,&cleanup);
}else
SS(Sbuild,syntax_new(x,y,z,&cleanup));
if(cat!=LEXICAT_END)

SS(Swork,cons(SO(Sbuild),SO(Swork),&cleanup));
break;

/*:233*//*237:*/
#line 5473 "lossless.w"

case LEXICAT_SYMBOL:
y= dlist_datum(dlist_next(SO(Sllex)));
if(!lexeme_terminator_p(y)){
z= syntax_invalid(lex,llex,llex,&cleanup);
parse_fail(Sfail,LERR_AMBIGUOUS,z,&cleanup);
}else{
a= lexeme(lex)->blength;
SS(Sbuild,x= segment_new(0,a,0,0,&cleanup));
buf= segment_address(x);
lex= dlist_datum(SO(Sllex));
x= rope_iterate_start(lexeme_twine(lex),
lexeme(lex)->tboffset,&cleanup);
for(i= 0;i<a;i++)
buf[i]= rope_iterate_next_byte(x,&cleanup);
y= symbol_new_buffer(buf,a,&cleanup);
z= syntax_new(y,SO(Sllex),SO(Sllex),&cleanup);
buf= NULL;
}
SS(Swork,cons(z,SO(Swork),&cleanup));
break;

/*:237*//*238:*/
#line 5505 "lossless.w"

case LEXICAT_ESCAPED_SYMBOL:
offset++;
case LEXICAT_ESCAPED_STRING:
offset++;
SS(Stmp,llex);
case LEXICAT_DELIMITER:
if(cat==LEXICAT_DELIMITER){
/*239:*/
#line 5554 "lossless.w"

SS(Sbuild,x= dlist_next(llex));
SS(Stmp,y= dlist_next(x));
lex= dlist_datum(x);
cat= lexeme(lex)->cat;
if(cat==LEXICAT_INVALID){
z= syntax_invalid(lex,SO(Sllex),SO(Sbuild),&cleanup);
parse_fail(Sfail,LERR_UNSCANNABLE,z,&cleanup);
SS(Stmp,SO(Sbuild));
lex= NIL;
}else{
assert(cat==LEXICAT_RAW_STRING||cat==LEXICAT_RAW_SYMBOL);
z= dlist_next(y);
assert(lexeme(dlist_datum(y))->cat==LEXICAT_DELIMITER);
if(!lexeme_terminator_p(dlist_datum(z))){
z= syntax_invalid(lex,lcar(SO(Swork)),SO(Stmp),&cleanup);
parse_fail(Sfail,LERR_AMBIGUOUS,z,&cleanup);
lex= NIL;
}
}

/*:239*/
#line 5513 "lossless.w"

}
if(null_p(lex))
SS(Sbuild,z);
else{
m= true;
x= transform_lexeme_segment(lex,offset,lexeme(lex)->blength,
(offset!=0),Sfail,&m,&cleanup);
SS(Sbuild,x);
if(!m)
SS(Sbuild,syntax_invalid(SO(Sbuild),SO(Sllex),
SO(Stmp),&cleanup));
else{
if(cat==LEXICAT_RAW_STRING||
cat==LEXICAT_ESCAPED_STRING)
y= rope_new_buffer(true,true,
segment_address(x),segment_length(x),
&cleanup);
else
y= symbol_new_segment(x,&cleanup);
SS(Sbuild,syntax_new(y,SO(Sllex),
SO(Stmp),&cleanup));
}
}
SS(Swork,cons(SO(Sbuild),SO(Swork),&cleanup));
if(cat!=LEXICAT_ESCAPED_SYMBOL&&cat!=LEXICAT_ESCAPED_STRING)
SS(Sllex,SO(Stmp));
offset= 0;
break;

/*:238*//*245:*/
#line 5737 "lossless.w"

case LEXICAT_CURIOUS:
case LEXICAT_NUMBER:

case LEXICAT_RECURSE_HERE:
case LEXICAT_RECURSE_IS:
z= syntax_invalid(lex,llex,llex,&cleanup);
parse_fail(Sfail,LERR_UNIMPLEMENTED,z,&cleanup);
SS(Swork,cons(z,SO(Swork),&cleanup));
break;

/*:245*/
#line 5282 "lossless.w"
}
SS(Sllex,llex= dlist_next(SO(Sllex)));
}
assert(null_p(SO(Swork)));
if(!null_p(SO(Swork))){
SS(Stmp,SO(Sbuild));
SS(Sbuild,NIL);
while(!null_p(SO(Swork))){
SS(Sbuild,cons(lcar(SO(Swork)),SO(Sbuild),&cleanup));
SS(Swork,lcdr(SO(Swork)));
}
x= syntax_invalid(SO(Sbuild),SO(Sstart),SO(Sllex),&cleanup);
parse_fail(Sfail,LERR_SYNTAX,x,&cleanup);
SS(Sbuild,cons(x,SO(Stmp),&cleanup));
}
if(!null_p(SO(Sfail)))
*valid= false;

/*:230*/
#line 5262 "lossless.w"

r= SO(Sbuild);
if(!*valid)
r= cons(r,SO(Sfail),&cleanup);
stack_clear(7);
return r;
}

/*:229*//*240:*/
#line 5587 "lossless.w"

cell
transform_lexeme_segment(cell o,
long offset,
long length,
bool escape,
int Sfail,
bool*valid,
sigjmp_buf*failure)
{
static int Ssrc= 2,Sdst= 1,Siter= 0;
cell r= NIL,tmp;
char*buf,b;
long i,j,k;
int32_t cp;
Outfio ucp;
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

assert(lexeme_p(o));
assert(offset>=0&&offset<lexeme(o)->blength);
assert(length>=1&&lexeme(o)->blength-offset<=length);
stack_protect(3,o,NIL,NIL,failure);
if(failure_p(reason= sigsetjmp(cleanup,1)))
unwind(failure,reason,false,3);
Sfail+= 3;
SS(Siter,rope_iterate_start(lexeme_twine(SO(Ssrc)),
lexeme(SO(Ssrc))->tboffset,&cleanup));
if(offset)
length-= offset+1;
while(offset--)
rope_iterate_next_byte(SO(Siter),&cleanup);
SS(Sdst,segment_new(0,length,0,0,&cleanup));
buf= segment_address(SO(Sdst));
/*241:*/
#line 5632 "lossless.w"

if(!escape)
for(i= 0;i<length;i++)
buf[i]= rope_iterate_next_byte(SO(Siter),&cleanup);
else{
j= 0;
for(i= 0;i<length;i++){
b= rope_iterate_next_byte(SO(Siter),&cleanup);
if(b!='#')
buf[j++]= b;
else{
i++;
b= rope_iterate_next_byte(SO(Siter),&cleanup);
switch(b){
/*243:*/
#line 5678 "lossless.w"

case'#':
case'|':
buf[j++]= b;
break;
case'o':
case'O':
buf[j]= (rope_iterate_next_byte(SO(Siter),&cleanup)-'0')<<6;
buf[j]|= (rope_iterate_next_byte(SO(Siter),&cleanup)-'0')<<3;
buf[j]|= (rope_iterate_next_byte(SO(Siter),&cleanup)-'0');
i+= 3;
j++;
break;
case'x':
case'X':
i+= 2;
buf[j++]= parse_ascii_hex(SO(Siter),&cleanup);
break;

/*:243*//*244:*/
#line 5704 "lossless.w"

case'u':
case'U':
cp= 0;
cp= parse_ascii_hex(SO(Siter),&cleanup)<<8;
cp|= parse_ascii_hex(SO(Siter),&cleanup);
i+= 4;
goto escaped_rune;
case'(':
cp= 0;
rope_iterate_next_byte(SO(Siter),&cleanup);
while((b= rope_iterate_next_byte(SO(Siter),&cleanup))!=')'){
i++;
cp<<= 4;
cp|= hexscii_to_int(b);
}
i+= 2;
escaped_rune:
ucp= utfio_write(cp);
tmp= rune_new_utfio(ucp,&cleanup);
if(rune_failure_p(tmp)){
*valid= false;
tmp= fix(j);
parse_fail(Sfail,LERR_NONCHARACTER,tmp,&cleanup);
ucp= utfio_write(UCP_REPLACEMENT);
tmp= rune_new_utfio(ucp,&cleanup);
}
for(k= 0;k<rune_parsed(tmp);k++)
buf[j++]= ucp.buf[k];

/*:244*/
#line 5646 "lossless.w"

}
}
}
if(i!=j)
SS(Sdst,segment_resize_m(SO(Sdst),0,j-i,&cleanup));
}

/*:241*/
#line 5621 "lossless.w"

r= SO(Sdst);
stack_clear(3);
return r;
}

/*:240*//*242:*/
#line 5660 "lossless.w"

char
parse_ascii_hex(cell o,
sigjmp_buf*failure)
{
int b,r;

assert(rope_iter(o));
b= rope_iterate_next_byte(o,failure);
r= hexscii_to_int(b)<<4;
b= rope_iterate_next_byte(o,failure);
r|= hexscii_to_int(b);
return(char)r;
}

/*:242*//*249:*/
#line 5829 "lossless.w"

void
evaluate(cell o,
sigjmp_buf*failure)
{

assert(null_p(CLINK)&&null_p(ARGS));
assert(environment_p(ENV));

EXPR= o;
LOG(ACC= VOID);
Begin:
EXPR= evaluate_desyntax(EXPR);
if(pair_p(EXPR))goto Combine_Start;
else if(!symbol_p(EXPR))goto Finish;
LOG(ACC= env_search(ENV,EXPR,true,failure));
if(undefined_p(ACC)){
lprint("looking for ");
serial(EXPR,SERIAL_ROUND,1,NIL,NULL,failure);
lprint("\n");
LOG(ACC= VOID);
siglongjmp(*failure,LERR_MISSING);
}
goto Return;

Evaluate:
LOG(EXPR= note_car(CLINK));
LOG(CLINK= note_cdr(CLINK));
goto Begin;

/*252:*/
#line 5930 "lossless.w"

Combine_Start:

LOG(CLINK= cons(ARGS,CLINK,failure));
LOG(CLINK= cons(ENV,CLINK,failure));
LOG(ARGS= lcdr(EXPR));
LOG(CLINK= note_new(Sym_COMBINE_DISPATCH,ARGS,CLINK,failure));
LOG(EXPR= lcar(EXPR));
goto Begin;

Combine_Dispatch:

LOG(ARGS= note_car(CLINK));
LOG(CLINK= note_cdr(CLINK));
if(operative_p(ACC))goto Combine_Operate;
else if(applicative_p(ACC))goto Applicative_Start;
else siglongjmp(*failure,LERR_UNCOMBINABLE);

/*:252*//*253:*/
#line 5952 "lossless.w"

Combine_Finish:

LOG(EXPR= note_car(CLINK));
LOG(CLINK= note_cdr(CLINK));
LOG(ENV= lcar(CLINK));
LOG(CLINK= lcdr(CLINK));
LOG(ARGS= lcar(CLINK));
LOG(CLINK= lcdr(CLINK));
goto Return;

/*:253*//*254:*/
#line 5970 "lossless.w"

Applicative_Start:

LOG(CLINK= note_new(Sym_COMBINE_APPLY,ACC,CLINK,failure));
LOG(EXPR= NIL);
Reverse_Arguments:
if(pair_p(ARGS)){
LOG(ACC= lcar(ARGS));
LOG(EXPR= cons(ACC,EXPR,failure));
LOG(ARGS= lcdr(ARGS));
goto Reverse_Arguments;
}else if(!null_p(ARGS))
siglongjmp(*failure,LERR_IMPROPER);
Applicative_Dispatch:
if(pair_p(EXPR))goto Applicative_Pair;
else goto Combine_Apply;

/*:254*//*255:*/
#line 5992 "lossless.w"

Applicative_Pair:
LOG(ACC= lcdr(EXPR));
LOG(CLINK= note_new(Sym_COMBINE_BUILD,ACC,CLINK,failure));
LOG(EXPR= lcar(EXPR));
goto Begin;

/*:255*//*256:*/
#line 6008 "lossless.w"

Applicative_Build:

LOG(ARGS= cons(ACC,ARGS,failure));
LOG(EXPR= note_car(CLINK));
LOG(CLINK= note_cdr(CLINK));
goto Applicative_Dispatch;

/*:256*//*257:*/
#line 6023 "lossless.w"

Combine_Apply:
LOG(ACC= note_car(CLINK));
LOG(CLINK= note_cdr(CLINK));
Combine_Operate:
LOG(CLINK= note_new(Sym_COMBINE_FINISH,EXPR,CLINK,failure));
combine(failure);
goto Return;

/*:257*//*258:*/
#line 6035 "lossless.w"

Conditional:

LOG(EXPR= note_car(CLINK));
LOG(CLINK= note_cdr(CLINK));
LOG(EXPR= false_p(ACC)?lcdr(EXPR):lcar(EXPR));
goto Begin;

/*:258*//*259:*/
#line 6043 "lossless.w"

Validate_Environment:
if(!environment_p(ACC))
evaluate_incompatible(__LINE__,failure);
LOG(EXPR= note_car(CLINK));
LOG(CLINK= note_cdr(CLINK));
#if 0 
if(!null_p(EXPR))
if(!environment_can_p(ACC,true_p(lcar(EXPR)),lcdr(EXPR)))
evaluate_incompatible(__LINE__,failure);
#endif
goto Return;

/*:259*//*260:*/
#line 6056 "lossless.w"

Save_And_Evaluate:
LOG(EXPR= note_car(CLINK));
LOG(CLINK= note_cdr(CLINK));
LOG(CLINK= note_new(Sym_ENVIRONMENT_M,ACC,CLINK,failure));
goto Begin;
Restore_Environment:
LOG(ENV= note_car(CLINK));
LOG(CLINK= note_cdr(CLINK));
goto Return;

/*:260*//*261:*/
#line 6067 "lossless.w"

Mutate_Environment:
LOG(EXPR= note_car(CLINK));
LOG(CLINK= note_cdr(CLINK));
LOG(ARGS= lcar(EXPR));
LOG(EXPR= lcdr(EXPR));
if(true_p(ARGS))
LOG(env_define(ENV,EXPR,ACC,failure));
else
LOG(env_set(ENV,EXPR,ACC,failure));
goto Return;

/*:261*//*262:*/
#line 6079 "lossless.w"

Evaluate_Dispatch:
LOG(EXPR= note_cdr(CLINK));
assert(note_p(EXPR)&&note(EXPR)==Sym_COMBINE_FINISH);
LOG(ENV= ACC);
goto Evaluate;

/*:262*//*266:*/
#line 6161 "lossless.w"

Operative_Closure:
LOG(EXPR= note_car(CLINK));
LOG(CLINK= note_cdr(CLINK));
LOG(ACC= lcar(EXPR));
LOG(ARGS= cons(ACC,ARGS,failure));
LOG(EXPR= lcdr(EXPR));
LOG(ACC= ENV);
LOG(ENV= lcar(EXPR));
LOG(EXPR= lcdr(EXPR));
LOG(ENV= env_extend(ENV,failure));
LOG(EXPR= lcar(EXPR));
LOG(validate_operative(failure));
goto Begin;

Applicative_Closure:
LOG(EXPR= note_car(CLINK));
LOG(CLINK= note_cdr(CLINK));
LOG(ACC= lcar(EXPR));
LOG(EXPR= lcdr(EXPR));
LOG(ENV= lcar(EXPR));
LOG(EXPR= lcdr(EXPR));
LOG(ENV= env_extend(ENV,failure));
LOG(EXPR= lcar(EXPR));
LOG(validate_arguments(failure));
goto Begin;

/*:266*/
#line 5859 "lossless.w"


Finish:
LOG(ACC= EXPR);
Return:
if(null_p(CLINK))
return;
else if(!note_p(CLINK))siglongjmp(*failure,LERR_INTERNAL);
else if(note(CLINK)==Sym_EVALUATE)goto Evaluate;
else if(note(CLINK)==Sym_COMBINE_APPLY)goto Combine_Apply;
else if(note(CLINK)==Sym_COMBINE_BUILD)goto Applicative_Build;
else if(note(CLINK)==Sym_COMBINE_DISPATCH)goto Combine_Dispatch;
else if(note(CLINK)==Sym_COMBINE_FINISH)goto Combine_Finish;
else if(note(CLINK)==Sym_COMBINE_OPERATE)goto Combine_Operate;
else if(note(CLINK)==Sym_OPERATIVE)goto Operative_Closure;
else if(note(CLINK)==Sym_APPLICATIVE)goto Applicative_Closure;
else if(note(CLINK)==Sym_CONDITIONAL)goto Conditional;
else if(note(CLINK)==Sym_ENVIRONMENT_P)goto Validate_Environment;
else if(note(CLINK)==Sym_EVALUATE_DISPATCH)goto Evaluate_Dispatch;
else if(note(CLINK)==Sym_SAVE_AND_EVALUATE)goto Save_And_Evaluate;
else if(note(CLINK)==Sym_ENVIRONMENT_M)goto Restore_Environment;
else if(note(CLINK)==Sym_DEFINITION)goto Mutate_Environment;
else
siglongjmp(*failure,LERR_INTERNAL);
}

/*:249*//*250:*/
#line 5885 "lossless.w"

void
evaluate_program(cell o,
sigjmp_buf*failure)
{
static int Sprogram= 0;
cell program;
bool syntactic;
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

stack_protect(1,o,failure);
if(failure_p(reason= sigsetjmp(cleanup,1)))
unwind(failure,reason,false,1);
program= env_search(Root,symbol_new_const("do"),true,&cleanup);
syntactic= syntax_p(SO(Sprogram));
if(syntactic){
program= cons(program,syntax_datum(SO(Sprogram)),&cleanup);
program= syntax_new(program,syntax_start(SO(Sprogram)),
syntax_end(SO(Sprogram)),&cleanup);
}else
program= cons(program,SO(Sprogram),&cleanup);
stack_clear(1);
evaluate(program,failure);
}

/*:250*//*263:*/
#line 6089 "lossless.w"

void
combine(sigjmp_buf*failure)
{
bool flag;
int count;
cell nsin,ndex;
cell value;

if(primitive_p(ACC)){
if(Iprimitive[primitive(ACC)].applicative||
Iprimitive[primitive(ACC)].min==-1)
validate_primitive(failure);
switch(primitive(ACC)){
/*264:*/
#line 6111 "lossless.w"

default:
siglongjmp(*failure,LERR_INTERNAL);

/*:264*//*267:*/
#line 6201 "lossless.w"

case PRIMITIVE_LAMBDA:
case PRIMITIVE_VOV:
flag= (primitive(ACC)==PRIMITIVE_LAMBDA);
if(null_p(ARGS))
evaluate_incompatible(__LINE__,failure);
LOG(ACC= lcar(ARGS));
LOG(EXPR= lcdr(ARGS));
cell lame= symbol_new_const("do");
lame= env_search(Root,lame,true,failure);
LOG(EXPR= cons(lame,EXPR,failure));
LOG(validate_formals(flag,failure));
LOG(ACC= closure_new(flag,ARGS,ENV,EXPR,failure));
break;

/*:267*//*276:*/
#line 6467 "lossless.w"

case PRIMITIVE_CONS:
LOG(Tmp_DEX= lcar(ARGS));
LOG(ARGS= lcdr(ARGS));
LOG(Tmp_SIN= lcar(ARGS));
LOG(ARGS= lcdr(ARGS));
assert(null_p(ARGS));
LOG(ACC= cons(Tmp_SIN,Tmp_DEX,failure));
break;

case PRIMITIVE_CAR:
LOG(EXPR= lcar(ARGS));
LOG(ARGS= lcdr(ARGS));
assert(null_p(ARGS));
if(!pair_p(EXPR))
evaluate_incompatible(__LINE__,failure);
LOG(ACC= lcar(EXPR));
break;

case PRIMITIVE_CDR:
LOG(EXPR= lcar(ARGS));
LOG(ARGS= lcdr(ARGS));
assert(null_p(ARGS));
if(!pair_p(EXPR))
evaluate_incompatible(__LINE__,failure);
LOG(ACC= lcdr(EXPR));
break;

/*:276*//*277:*/
#line 6507 "lossless.w"

case PRIMITIVE_DO:
LOG(EXPR= note_new(Sym_EVALUATE,VOID,NIL,failure));
LOG(ACC= EXPR);
while(!null_p(ARGS)){
if(!pair_p(ARGS))
evaluate_incompatible(__LINE__,failure);
LOG(value= note_new(Sym_EVALUATE,evaluate_desyntax(lcar(ARGS)),NIL,failure));
LOG(note_set_cdr_m(ACC,value));
LOG(ACC= value);
LOG(ARGS= lcdr(ARGS));
ARGS= evaluate_desyntax(ARGS);
}
LOG(note_set_cdr_m(ACC,CLINK));
LOG(CLINK= EXPR);
break;

/*:277*//*278:*/
#line 6524 "lossless.w"

case PRIMITIVE_CURRENT_ENVIRONMENT:
assert(null_p(ARGS));
LOG(ACC= ENV);
break;
case PRIMITIVE_ROOT_ENVIRONMENT:
assert(null_p(ARGS));
LOG(ACC= Root);
break;

/*:278*//*279:*/
#line 6543 "lossless.w"

case PRIMITIVE_IF:
LOG(count= fix_value(lcar(ARGS)));
LOG(ARGS= lcdr(ARGS));
if(count==3)
validated_argument(ACC,ARGS,false,defined_p,failure);
else if(count==1)
LOG(ACC= VOID);
else
evaluate_incompatible(__LINE__,failure);
validated_argument(EXPR,ARGS,false,defined_p,failure);
LOG(EXPR= cons(EXPR,ACC,failure));
validated_argument(ACC,ARGS,false,defined_p,failure);
LOG(CLINK= note_new(Sym_CONDITIONAL,EXPR,CLINK,failure));
LOG(CLINK= note_new(Sym_EVALUATE,ACC,CLINK,failure));
break;

/*:279*//*280:*/
#line 6562 "lossless.w"

case PRIMITIVE_DUMP:
lprint("DUMP ");
ACC= lcar(ARGS);
serial(ACC,SERIAL_DETAIL,42,NIL,NULL,failure);
lprint("\n");
case PRIMITIVE_BREAK:
breakpoint();
break;

/*:280*//*283:*/
#line 6590 "lossless.w"

case PRIMITIVE_DEFINE_M:
case PRIMITIVE_SET_M:
flag= (primitive(ACC)==PRIMITIVE_DEFINE_M);
if(!pair_p(ARGS))
evaluate_incompatible(__LINE__,failure);
LOG(ACC= lcar(ARGS));
ARGS= lcdr(ARGS);
if(!pair_p(ARGS))
evaluate_incompatible(__LINE__,failure);
EXPR= lcar(ARGS);
EXPR= evaluate_desyntax(EXPR);
if(pair_p(EXPR)){
LOG(ARGS= lcdr(ARGS));
LOG(value= lcdr(EXPR));
LOG(EXPR= lcar(EXPR));
EXPR= evaluate_desyntax(EXPR);
LOG(ARGS= cons(value,ARGS,failure));
LOG(ARGS= cons(Iprimitive[PRIMITIVE_LAMBDA].box,ARGS,
failure));
}else if(symbol_p(EXPR)){
LOG(ARGS= lcdr(ARGS));
if(!pair_p(ARGS))
evaluate_incompatible(__LINE__,failure);
LOG(value= lcar(ARGS));
LOG(ARGS= lcdr(ARGS));
if(!null_p(ARGS))
evaluate_incompatible(__LINE__,failure);
LOG(ARGS= value);
}else
evaluate_incompatible(__LINE__,failure);
LOG(EXPR= cons(predicate(flag),EXPR,failure));
LOG(CLINK= note_new(Sym_DEFINITION,EXPR,CLINK,failure));
LOG(CLINK= note_new(Sym_SAVE_AND_EVALUATE,ARGS,CLINK,failure));
LOG(CLINK= note_new(Sym_ENVIRONMENT_P,EXPR,CLINK,failure));
LOG(CLINK= note_new(Sym_EVALUATE,ACC,CLINK,failure));
break;

/*:283*//*284:*/
#line 6634 "lossless.w"

case PRIMITIVE_NULL_P:
primitive_predicate(null_p);
case PRIMITIVE_PAIR_P:
primitive_predicate(pair_p);

/*:284*//*285:*/
#line 6640 "lossless.w"

case PRIMITIVE_EVAL:
LOG(count= fix_value(lcar(ARGS)));
LOG(ARGS= lcdr(ARGS));
if(count==2)
validated_argument(ACC,ARGS,false,environment_p,failure);
else if(count==1)
LOG(ACC= ENV);
else
evaluate_incompatible(__LINE__,failure);
LOG(EXPR= lcar(ARGS));
LOG(CLINK= note_new(Sym_EVALUATE_DISPATCH,EXPR,CLINK,failure));
break;

/*:285*//*289:*/
#line 6729 "lossless.w"

case PRIMITIVE_ROPE_P:
ACC= predicate(rope_p(lcar(ARGS)));
break;
case PRIMITIVE_ROPE_PLAIN_P:
ACC= predicate(plain_rope_p(lcar(ARGS)));
break;
case PRIMITIVE_ROPE_SIN_THREADABLE_P:
ACC= predicate(rope_sin_threadable_p(lcar(ARGS)));
break;
case PRIMITIVE_ROPE_DEX_THREADABLE_P:
ACC= predicate(rope_dex_threadable_p(lcar(ARGS)));
break;

/*:289*//*290:*/
#line 6743 "lossless.w"

case PRIMITIVE_NEW_ROPE_PLAIN_NODE:
count= fix_value(lcar(ARGS));
ARGS= lcdr(ARGS);
if(count==3){
validated_argument(ndex,ARGS,true,plain_rope_p,failure);
validated_argument(nsin,ARGS,true,plain_rope_p,failure);
}else if(count!=1)
evaluate_incompatible(__LINE__,failure);
else
nsin= ndex= NIL;
validated_argument(ACC,ARGS,true,rope_p,failure);
if(null_p(ACC))
ACC= rope_node_new_length(false,false,0,nsin,ndex,failure);
else
ACC= rope_node_new_clone(false,false,ACC,nsin,ndex,
failure);
break;

/*:290*//*291:*/
#line 6762 "lossless.w"

case PRIMITIVE_TREE_P:
ACC= predicate(tree_p(lcar(ARGS)));
break;
case PRIMITIVE_TREE_PLAIN_P:
ACC= predicate(plain_tree_p(lcar(ARGS)));
break;
case PRIMITIVE_TREE_SIN_THREADABLE_P:
ACC= predicate(tree_sin_threadable_p(lcar(ARGS)));
break;
case PRIMITIVE_TREE_DEX_THREADABLE_P:
ACC= predicate(tree_dex_threadable_p(lcar(ARGS)));
break;

/*:291*//*292:*/
#line 6776 "lossless.w"

case PRIMITIVE_TREE_SIN_HAS_THREAD_P:
if(!tree_sin_threadable_p(lcar(ARGS)))
ACC= LFALSE;
else
ACC= tree_sin_has_thread_p(lcar(ARGS));
break;
case PRIMITIVE_TREE_DEX_HAS_THREAD_P:
if(!tree_dex_threadable_p(lcar(ARGS)))
ACC= LFALSE;
else
ACC= tree_dex_has_thread_p(lcar(ARGS));
break;
case PRIMITIVE_TREE_SIN_IS_LIVE_P:
ACC= predicate(dryad_sin_p(lcar(ARGS)));
break;
case PRIMITIVE_TREE_DEX_IS_LIVE_P:
ACC= predicate(dryad_dex_p(lcar(ARGS)));
break;

/*:292*//*293:*/
#line 6796 "lossless.w"

case PRIMITIVE_NEW_TREE_PLAIN_NODE:
validated_argument(ndex,ARGS,true,plain_tree_p,failure);
validated_argument(nsin,ARGS,true,plain_tree_p,failure);
#if 0
ACC= tree_node_new(lcar(ARGS),nsin,ndex,failure);
#endif
break;
case PRIMITIVE_NEW_TREE_BIWARD_NODE:
validated_argument(ndex,ARGS,true,tree_threadable_p,failure);
validated_argument(nsin,ARGS,true,tree_threadable_p,failure);
#if 0
ACC= tree_threadable_node_new(lcar(ARGS),nsin,ndex,failure);
#endif
break;
case PRIMITIVE_NEW_TREE_SINWARD_NODE:
validated_argument(ndex,ARGS,true,tree_sin_threadable_p,failure);
validated_argument(nsin,ARGS,true,tree_sin_threadable_p,failure);
if(tree_dex_threadable_p(nsin)||tree_dex_threadable_p(ndex))
evaluate_incompatible(__LINE__,failure);
#if 0
ACC= tree_sin_threadable_node_new(lcar(ARGS),nsin,ndex,failure);
#endif
break;
case PRIMITIVE_NEW_TREE_DEXWARD_NODE:
validated_argument(ndex,ARGS,true,tree_dex_threadable_p,failure);
validated_argument(nsin,ARGS,true,tree_dex_threadable_p,failure);
if(tree_sin_threadable_p(nsin)||tree_sin_threadable_p(ndex))
evaluate_incompatible(__LINE__,failure);
#if 0
ACC= tree_dex_threadable_node_new(lcar(ARGS),nsin,ndex,failure);
#endif
break;

case PRIMITIVE_TREE_RETHREAD_M:
validated_argument(ndex,ARGS,false,boolean_p,failure);
validated_argument(nsin,ARGS,false,boolean_p,failure);
if(!tree_p(lcar(ARGS)))
evaluate_incompatible(__LINE__,failure);
#if 0
ACC= treeish_rethread_m(lcar(ARGS),true_p(nsin),true_p(ndex),
failure);
#endif
break;

/*:293*//*294:*/
#line 6841 "lossless.w"

case PRIMITIVE_TREE_DATUM:
validated_argument(value,ARGS,false,tree_p,failure);
ACC= dryad_datum(value);
break;

/*:294*/
#line 6103 "lossless.w"

}
}else if(applicative_p(ACC))
LOG(CLINK= note_new(Sym_APPLICATIVE,ACC,CLINK,failure));
else if(operative_p(ACC))
LOG(CLINK= note_new(Sym_OPERATIVE,ACC,CLINK,failure));
}

/*:263*//*265:*/
#line 6123 "lossless.w"

void
validate_primitive(sigjmp_buf*failure)
{
int count;

count= 0;
EXPR= NIL;
while(pair_p(ARGS)){
count++;
if(Iprimitive[primitive(ACC)].max!=0&&
count> Iprimitive[primitive(ACC)].max)
evaluate_incompatible(__LINE__,failure);
EXPR= cons(lcar(ARGS),EXPR,failure);
ARGS= lcdr(ARGS);
}
if(Iprimitive[primitive(ACC)].min>=0&&
count<Iprimitive[primitive(ACC)].min)
evaluate_incompatible(__LINE__,failure);
if(Iprimitive[primitive(ACC)].max&&
Iprimitive[primitive(ACC)].max!=Iprimitive[primitive(ACC)].min)
EXPR= cons(fix(count),EXPR,failure);
ARGS= EXPR;
EXPR= NIL;
}

/*:265*//*268:*/
#line 6223 "lossless.w"

void
validate_formals(bool is_applicative,
sigjmp_buf*failure)
{
static int Svargs= 2,Svenv= 1,Svcont= 0;
cell arg,state;
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

LOG(ARGS= ACC);
LOG(ACC= NIL);
if(is_applicative){
/*269:*/
#line 6252 "lossless.w"

while(pair_p(evaluate_desyntax(ARGS))){
arg= lcar(evaluate_desyntax(ARGS));
LOG(ARGS= lcdr(evaluate_desyntax(ARGS)));
assert(syntax_p(arg));
arg= syntax_datum(arg);
if(!symbol_p(arg))
evaluate_incompatible(__LINE__,failure);
LOG(ACC= cons(arg,ACC,failure));
}
if(symbol_p(evaluate_desyntax(ARGS)))
LOG(ARGS= evaluate_desyntax(ARGS));
else if(!null_p(evaluate_desyntax(ARGS)))
evaluate_incompatible(__LINE__,failure);
while(!null_p(ACC)){
LOG(ARGS= cons(lcar(ACC),ARGS,failure));
LOG(ACC= lcdr(ACC));
}

/*:269*/
#line 6236 "lossless.w"

}else{
/*270:*/
#line 6296 "lossless.w"

stack_reserve(3,failure);
if(failure_p(reason= sigsetjmp(cleanup,1)))
unwind(failure,reason,false,3);
ARGS= evaluate_desyntax(ARGS);
while(pair_p(ARGS)){
arg= lcar(ARGS);
arg= evaluate_desyntax(arg);
if(!pair_p(arg))
evaluate_incompatible(__LINE__,failure);
state= lcdr(arg);
arg= lcar(arg);
arg= evaluate_desyntax(arg);
if(!symbol_p(arg)||!pair_p(state)||!null_p(lcdr(state)))
evaluate_incompatible(__LINE__,failure);
state= lcar(state);
state= evaluate_desyntax(state);
if(state==Sym_VOV_ARGS||state==Sym_VOV_ARGUMENTS)
save_vov_informal(arg,Svargs);
else if(state==Sym_VOV_ENV||state==Sym_VOV_ENVIRONMENT)
save_vov_informal(arg,Svenv);
else if(state==Sym_VOV_CONT||state==Sym_VOV_CONTINUATION)
save_vov_informal(arg,Svcont);
else
evaluate_incompatible(__LINE__,failure);
LOG(ARGS= lcdr(ARGS));
}
if(!null_p(ARGS)||
(null_p(SO(Svargs))&&null_p(SO(Svenv))&&null_p(SO(Svcont))))
evaluate_incompatible(__LINE__,failure);
ARGS= cons(SO(Svcont),ARGS,failure);
ARGS= cons(SO(Svenv),ARGS,failure);
ARGS= cons(SO(Svargs),ARGS,failure);
stack_clear(3);

/*:270*/
#line 6238 "lossless.w"

}
}

/*:268*//*272:*/
#line 6343 "lossless.w"

void
validate_arguments(sigjmp_buf*failure)
{
static int Sname= 1,Sarg= 0;
cell arg,name;
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

stack_reserve(2,failure);
if(failure_p(reason= sigsetjmp(cleanup,1)))
unwind(failure,reason,false,2);
LOG(SS(Sname,evaluate_desyntax(ACC)));
LOG(SS(Sarg,ARGS));
while(pair_p(SO(Sname))){
LOG(name= lcar(SO(Sname)));
LOG(SS(Sname,lcdr(SO(Sname))));
if(null_p(SO(Sarg)))
evaluate_incompatible(__LINE__,failure);
LOG(arg= lcar(SO(Sarg)));
LOG(SS(Sarg,lcdr(SO(Sarg))));
LOG(env_define(ENV,name,arg,failure));
}
if(!null_p(SO(Sname))){
LOG(assert(symbol_p(SO(Sname))));
LOG(env_define(ENV,SO(Sname),SO(Sarg),failure));
}else if(!null_p(SO(Sarg)))
evaluate_incompatible(__LINE__,failure);
stack_clear(2);
}

/*:272*//*273:*/
#line 6384 "lossless.w"

void
validate_operative(sigjmp_buf*failure)
{
static int Sinformal= 0;
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

assert(pair_p(ARGS));
stack_push(lcar(ARGS),failure);
if(failure_p(reason= sigsetjmp(cleanup,1)))
unwind(failure,reason,false,1);
ARGS= lcdr(ARGS);

assert(pair_p(SO(Sinformal)));
if(symbol_p(lcar(SO(Sinformal))))
LOG(env_define(ENV,lcar(SO(Sinformal)),ARGS,failure));
SS(Sinformal,lcdr(SO(Sinformal)));

assert(pair_p(SO(Sinformal)));
if(symbol_p(lcar(SO(Sinformal))))
LOG(env_define(ENV,lcar(SO(Sinformal)),ACC,failure));
SS(Sinformal,lcdr(SO(Sinformal)));

assert(pair_p(SO(Sinformal)));
if(symbol_p(lcar(SO(Sinformal))))
siglongjmp(cleanup,LERR_UNIMPLEMENTED);
assert(null_p(lcdr(SO(Sinformal))));

stack_clear(1);
}

/*:273*//*282:*/
#line 6575 "lossless.w"

void
breakpoint(void)
{
printf("Why did we ever allow GNU?\n");
}

/*:282*//*296:*/
#line 6880 "lossless.w"

void
serial(cell o,
int detail,
int maxdepth,
cell buffer,
cell*cycles,
sigjmp_buf*failure)
{
static int Sobject= 0;
size_t count;
Oheap*h,*heap;
bool compacting;
cell ignored= Null_Array;
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

assert(defined_p(o));
assert(maxdepth>=0);
if(detail)
assert(null_p(buffer));
else
assert((LDEBUG_P&&null_p(buffer))||segment_p(buffer));
if(cycles==NULL)
cycles= &ignored;
stack_protect(1,o,failure);
if(failure_p(reason= sigsetjmp(cleanup,1)))
unwind(failure,reason,false,1);

if(!special_p(o)){
/*297:*/
#line 6919 "lossless.w"

heap= Theap;
h= Sheap;
while(h!=NULL)
if(h==ATOM_TO_HEAP(o)){
heap= Sheap;
break;
}else
h= h->next;

/*:297*/
#line 6910 "lossless.w"

/*298:*/
#line 6929 "lossless.w"

*cycles= array_new_imp(8,LFALSE,FORM_ARRAY,&cleanup);
pointer_set_datum_m(*cycles,fix(0));
compacting= (ATOM_TO_HEAP(o)->pair!=NULL);
count= 0;
*cycles= gc_mark(heap,*cycles,compacting,NULL,&count);
SS(Sobject,gc_mark(heap,SO(Sobject),compacting,cycles,&count));
if(compacting)
gc_compacting(heap,false);
else
gc_sweeping(heap,false);
if(null_p(*cycles))
siglongjmp(cleanup,LERR_OOM);
count= 2*fix_value(pointer_datum(*cycles));
*cycles= array_grow_m(*cycles,count-array_length(*cycles),LFALSE,failure);
count/= 2;
pointer_set_datum_m(*cycles,fix(count));

#if 0
serial_imp(SO(Sobject),SERIAL_SILENT,maxdepth,false,NULL,*cycles,failure);
pointer_set_datum_m(*cycles,fix(0));
for(i= 0;i<count;i++){
j= fix_value(pointer_datum(*cycles));
if(true_p(array_ref(*cycles,i+count))){
if(i!=j)
array_set_m(*cycles,j++,array_ref(*cycles,i));
pointer_set_datum_m(*cycles,fix(j));
}
}
for(;i<j*2;i++)
array_set_m(*cycles,j,LFALSE);
#endif

/*:298*/
#line 6911 "lossless.w"

}
if(detail)
serial_imp(SO(Sobject),detail,maxdepth,true,buffer,
*cycles,failure);
stack_clear(1);
}

/*:296*//*299:*/
#line 6966 "lossless.w"


void
gc_serial(cell cycles,
cell found)
{
int i,len;
sigjmp_buf cleanup;
Verror reason= LERR_NONE;

if(null_p(cycles))
return;
if(failure_p(reason= sigsetjmp(cleanup,1)))
return;
len= fix_value(pointer_datum(cycles));
for(i= 0;i<len;i++)
if(array_ref(cycles,i)==found)
return;
if(len>=array_length(cycles))
array_grow_m(cycles,array_length(cycles),LFALSE,&cleanup);
array_set_m(cycles,len,found);
pointer_set_datum_m(cycles,fix(len+1));
}

/*:299*//*300:*/
#line 6997 "lossless.w"

void
serial_append_imp(cell buffer,
char*content,
int length,
sigjmp_buf*failure)
{
int i,off;

assert(segment_p(buffer));
off= fix_value(pointer_datum(buffer));
i= segment_length(buffer)-off-1;
if(i> length)
i= length;
for(;i>=0;i--)
segment_address(buffer)[off+i]= content[i];
segment_address(buffer)[off+i]= '\0';
pointer_set_datum_m(buffer,fix(off+i));
if(i!=length)
siglongjmp(*failure,LERR_OVERFLOW);
}

/*:300*//*301:*/
#line 7024 "lossless.w"

void
serial_imp(cell o,
int detail,
int maxdepth,
bool prefix,
cell buffer,
cell cycles,
sigjmp_buf*failure)
{
cell p;
int i,length= 0;
char*append= NULL,buf[FIX_BASE10+2];

assert(maxdepth>=0);
assert((LDEBUG_P&&null_p(buffer))||segment_p(buffer));
assert(array_p(cycles));
if(special_p(o)){
/*302:*/
#line 7069 "lossless.w"

if(null_p(o))
append= "\002()";
else if(false_p(o))
append= "\002#f";
else if(true_p(o))
append= "\002#t";
else if(void_p(o)){
if(detail==SERIAL_DETAIL)
append= "\007#<void>";
#if 0
else if(detail!=SERIAL_ROUND)
append= "\000";
#endif
}else if(eof_p(o)){
if(detail==SERIAL_DETAIL)
append= "\021#<schwarzenegger>";
}else if(undefined_p(o)){
if(detail==SERIAL_DETAIL)
append= "\006#<zen>";
}else{
assert(fix_p(o));
i= fix_value(o);
if(!i)
append= "\0010";
else{
if(i<0)
i= -i;
append= buf+FIX_BASE10+2;
*--append= '\0';
*--append= 0;
while(i){
*(append-1)= *(append)+1;
*append--= (i%10)+'0';
i/= 10;
}
}
if(fix_value(o)<0){
*(append-1)= *(append)+1;
*append--= '-';
}
}

/*:302*/
#line 7042 "lossless.w"

}else if(symbol_p(o)){
/*303:*/
#line 7112 "lossless.w"

append= symbol_buffer(o);
length= symbol_length(o);
if(detail&&maxdepth)
for(i= 0;i<length;i++)
if(!serial_printable_p(append[i])){
if(detail){
serial_append(buffer,"#|",2,failure);
serial_escape(append,length,buffer,failure);
serial_append(buffer,"|",1,failure);
}
append= "\0";
length= 0;
break;
}

/*:303*/
#line 7044 "lossless.w"

}else
append= serial_deduplicate(o,detail,buffer,cycles,failure);
if(append==NULL){
/*307:*/
#line 7205 "lossless.w"

if(pair_p(o)){
if(!maxdepth&&detail!=SERIAL_ROUND)
append= "\005(...)";
else if(maxdepth){
if(detail)
serial_append(buffer,"(",1,failure);
serial_imp(lcar(o),detail,maxdepth-1,true,buffer,cycles,
failure);
for(o= lcdr(o);pair_p(o);o= lcdr(o)){
if(detail)
serial_append(buffer," ",1,failure);
serial_imp(lcar(o),detail,maxdepth-1,true,buffer,
cycles,failure);
}
if(!null_p(o)){
if(detail)
serial_append(buffer," . ",1,failure);
serial_imp(o,detail,maxdepth-1,true,buffer,
cycles,failure);
}
if(detail)
serial_append(buffer,")",1,failure);
append= "\0";
}
}

/*:307*//*308:*/
#line 7232 "lossless.w"

else if(array_p(o)){
if(!maxdepth&&detail!=SERIAL_ROUND)
append= "\005[...]";
else if(maxdepth){
if(detail)
serial_append(buffer,"[",1,failure);
for(i= 0;i<array_length(o);i++){
serial_imp(array_ref(o,i),detail,maxdepth-1,
true,buffer,cycles,failure);
if(detail&&i<array_length(o)-1)
serial_append(buffer," ",1,failure);
}
if(detail)
serial_append(buffer,"]",1,failure);
append= "\0";
}
}

/*:308*//*309:*/
#line 7251 "lossless.w"

else if(rope_p(o)){
if(detail==SERIAL_DETAIL){
serial_append(buffer,"“",(int)sizeof("“"),failure);
serial_rope(o,detail,maxdepth,buffer,cycles,failure);
serial_append(buffer,"”",(int)sizeof("”"),failure);
}else{
if(detail)
serial_append(buffer,"|",1,failure);
serial_rope(o,detail,maxdepth,buffer,cycles,failure);
if(detail)
serial_append(buffer,"|",1,failure);
}
append= "\0";
}

/*:309*//*311:*/
#line 7306 "lossless.w"

else if(primitive_p(o)&&detail!=SERIAL_ROUND){
if(detail){
serial_append(buffer,"#{primitive ",13,failure);
serial_append(buffer,Iprimitive[primitive(o)].label,
(int)strlen(Iprimitive[primitive(o)].label),failure);
serial_append(buffer,"}",1,failure);
}
append= "\0";
}

/*:311*//*312:*/
#line 7317 "lossless.w"

else if(environment_p(o)&&detail!=SERIAL_ROUND){
if(!maxdepth)
append= "\015<ENVIRONMENT>";
else{
if(detail)
serial_append(buffer,"#{environment ",14,failure);
serial_imp(env_layer(o),detail,maxdepth-1,true,buffer,
cycles,failure);
if(detail)
serial_append(buffer," on ",4,failure);
serial_imp(env_previous(o),detail,maxdepth-1,true,buffer,
cycles,failure);
if(detail)
serial_append(buffer,"}",1,failure);
append= "\0";
}
}

/*:312*//*313:*/
#line 7338 "lossless.w"

else if(keytable_p(o)&&detail!=SERIAL_ROUND){
if(!maxdepth)
append= "\014#{table ...}";
else{
if(detail)
serial_append(buffer,"#{table ",8,failure);
serial_imp(fix(keytable_free(o)),SERIAL_ROUND,1,true,
buffer,cycles,failure);
if(detail)
serial_append(buffer,"/",1,failure);
serial_imp(fix(keytable_length(o)),SERIAL_ROUND,1,true,
buffer,cycles,failure);
for(i= 0;i<keytable_length(o);i++){
if(!null_p(keytable_ref(o,i))){
if(detail)
serial_append(buffer," (",2,failure);
serial_imp(fix(i),detail,maxdepth-1,true,
buffer,cycles,failure);
if(detail)
serial_append(buffer," . ",3,failure);
serial_imp(keytable_ref(o,i),detail,maxdepth-1,true,
buffer,cycles,failure);
if(detail)
serial_append(buffer,")",1,failure);
}
}
if(detail)
serial_append(buffer,"}",1,failure);
append= "\0";
}
}

/*:313*//*314:*/
#line 7371 "lossless.w"

else if(closure_p(o)&&detail!=SERIAL_ROUND){
if(!maxdepth)
append= "\016#{closure ...}";
else{
if(detail){
serial_append(buffer,"#{",2,failure);
if(applicative_p(o))
serial_append(buffer,"applicative ",12,failure);
else
serial_append(buffer,"operative ",10,failure);
}
serial_imp(closure_formals(o),detail,maxdepth-1,true,
buffer,cycles,failure);
if(detail)
serial_append(buffer," ",1,failure);
serial_imp(closure_body(o),detail,maxdepth-1,true,
buffer,cycles,failure);
if(detail)
serial_append(buffer," in ",4,failure);
serial_imp(closure_environment(o),detail,maxdepth-1,true,
buffer,cycles,failure);
if(detail)
serial_append(buffer,"}",1,failure);
append= "\0";
}
}

/*:314*//*315:*/
#line 7399 "lossless.w"

else if(dlist_p(o)&&detail!=SERIAL_ROUND){
if(!maxdepth)
append= "\006<LIST>";
else{
if(prefix){
if(detail)
serial_append(buffer,"#{dlist ",8,failure);
serial_imp(dlist_datum(o),detail,maxdepth-1,true,
buffer,cycles,failure);
p= dlist_next(o);
while(p!=o){
if(detail)
serial_append(buffer," :: ",4,failure);
serial_imp(p,detail,maxdepth,false,
buffer,cycles,failure);
p= dlist_next(p);
}
if(detail)
serial_append(buffer,"}",1,failure);
}else
serial_imp(dlist_datum(o),detail,maxdepth-1,true,
buffer,cycles,failure);
append= "\0";
}
}

/*:315*//*316:*/
#line 7426 "lossless.w"

else if(note_p(o)&&detail!=SERIAL_ROUND){
if(!maxdepth)
append= "\006<NOTE>";
else{
serial_imp(note(o),detail,maxdepth-1,true,buffer,cycles,
failure);
if(detail)
serial_append(buffer,"ª",(int)sizeof("ª"),failure);
serial_imp(note_car(o),detail,maxdepth-1,true,buffer,
cycles,failure);
if(detail)
serial_append(buffer," ¦ ",(int)sizeof(" ¦ "),failure);
serial_imp(note_cdr(o),detail,maxdepth-1,true,buffer,
cycles,failure);
if(detail)
serial_append(buffer,"º",(int)sizeof("º"),failure);
append= "\0";
}
}

/*:316*//*317:*/
#line 7447 "lossless.w"

else if(syntax_p(o)&&detail!=SERIAL_ROUND){
if(!maxdepth)
append= "\010<SYNTAX>";
else{
if(detail)
serial_append(buffer,"#{syntax ",9,failure);
serial_imp(syntax_datum(o),detail,maxdepth-1,true,buffer,
cycles,failure);
if(detail)
serial_append(buffer," ",1,failure);
serial_imp(syntax_start(o),detail,maxdepth-1,true,buffer,
cycles,failure);
if(detail)
serial_append(buffer," ",1,failure);
serial_imp(syntax_end(o),detail,maxdepth-1,true,buffer,
cycles,failure);
if(detail)
serial_append(buffer,"}",1,failure);
append= "\0";
}
}

/*:317*//*318:*/
#line 7470 "lossless.w"

else if(lexeme_p(o)&&detail!=SERIAL_ROUND){
if(!maxdepth)
append= "\015#{lexeme ...}";
else{
if(detail)
serial_append(buffer,"#{lexeme ",9,failure);
serial_imp(fix(lexeme(o)->cat),SERIAL_ROUND,1,true,
buffer,cycles,failure);
if(detail)
serial_append(buffer," @",2,failure);
serial_imp(fix(lexeme(o)->tboffset),SERIAL_ROUND,1,
true,buffer,cycles,failure);
if(detail)
serial_append(buffer,":",1,failure);
serial_imp(fix(lexeme(o)->blength),SERIAL_ROUND,1,
true,buffer,cycles,failure);
if(detail)
serial_append(buffer," of ",4,failure);
serial_imp(lexeme_twine(o),SERIAL_ROUND,maxdepth-1,
true,buffer,cycles,failure);
if(detail)
serial_append(buffer,"}",1,failure);
append= "\0";
}
}

/*:318*//*319:*/
#line 7497 "lossless.w"

else if(keytable_p(o)){
append= NULL;
}

/*:319*/
#line 7048 "lossless.w"


else
{
lprint("%2x?\n",form(o));
assert(!"unknown type");
}
}

if(append==NULL){
lprint("%p: %x\n",o,special_p(o)?-1:form(o));
siglongjmp(*failure,LERR_UNPRINTABLE);
}
if(!length){
length= append[0];
append++;
}
if(detail)
serial_append(buffer,append,length,failure);
}

/*:301*//*304:*/
#line 7128 "lossless.w"

void
serial_escape(char*append,
int length,
cell buffer,
sigjmp_buf*failure)
{
int i,j;
char ascii[4]= {'#','x','\0','\0'};

for(i= 0;i<length;i++){
if(append[i]=='#')
serial_append(buffer,"##",2,failure);
else if(append[i]=='|')
serial_append(buffer,"#|",2,failure);
else if(append[i]=='\n'||append[i]=='\t'||
serial_printable_p(append[i]))
serial_append(buffer,append+i,1,failure);
else{
j= (append[i]&0xf0)>>4;
ascii[2]= int_to_hexscii(j,false);
j= (append[i]&0x0f)>>0;
ascii[3]= int_to_hexscii(j,false);
serial_append(buffer,ascii,4,failure);
}
}
}

/*:304*//*305:*/
#line 7156 "lossless.w"

int
serial_cycle(cell cycles,
cell candidate)
{
int r;

for(r= 0;r<fix_value(pointer_datum(cycles));r++)
if(array_ref(cycles,r)==candidate)
return r;
return-1;
}

/*:305*//*306:*/
#line 7172 "lossless.w"

char*
serial_deduplicate(cell o,
int detail,
cell buffer,
cell cycles,
sigjmp_buf*failure)
{
int c,i;

assert((LDEBUG_P&&null_p(buffer))||segment_p(buffer));
assert(array_p(cycles));
c= serial_cycle(cycles,o);
if(c==-1)
return NULL;
i= c+fix_value(pointer_datum(cycles));
if(!detail)
array_set_m(cycles,i,LTRUE);
else if(true_p(array_ref(cycles,i))){
serial_append(buffer,"##",2,failure);
serial_imp(fix(c),SERIAL_ROUND,1,true,buffer,cycles,failure);
}else{
serial_append(buffer,"#=",2,failure);
serial_imp(fix(c),SERIAL_ROUND,1,true,buffer,cycles,failure);
serial_append(buffer," ",1,failure);
array_set_m(cycles,i,LTRUE);
return NULL;
}
return"\0";
}

/*:306*//*310:*/
#line 7267 "lossless.w"

void
serial_rope(cell o,
int detail,
int maxdepth,
cell buffer,
cell cycles,
sigjmp_buf*failure)
{
cell p;

assert(rope_p(o));
if(maxdepth<0&&detail==SERIAL_ROUND)
siglongjmp(*failure,LERR_UNPRINTABLE);
else if(maxdepth<0){
if(detail)
serial_append(buffer,"...",3,failure);
}else{
p= rope_prev(o,failure);
if(null_p(p)){
if(detail==SERIAL_DETAIL)
serial_append(buffer,"()",2,failure);
}else if(serial_deduplicate(p,detail,buffer,cycles,failure)==NULL)
serial_rope(p,detail,maxdepth-1,buffer,cycles,failure);
if(detail==SERIAL_DETAIL)
serial_append(buffer," |",2,failure);
if(detail)
serial_escape(rope_buffer(o),rope_blength(o),buffer,failure);
if(detail==SERIAL_DETAIL)
serial_append(buffer,"| ",2,failure);
p= rope_next(o,failure);
if(null_p(p)){
if(detail==SERIAL_DETAIL)
serial_append(buffer,"()",2,failure);
}else if(serial_deduplicate(p,detail,buffer,cycles,failure)==NULL)
serial_rope(p,detail,maxdepth-1,buffer,cycles,failure);
}
}

/*:310*//*321:*/
#line 7507 "lossless.w"

int
high_bit(digit o)
{
int i= CELL_BITS;

while(--i)
if(o&(1ull<<i))
return i+1;
return o;
}

/*:321*//*328:*/
#line 7590 "lossless.w"

bool lapi_null_p(cell o){return null_p(o);}
bool lapi_false_p(cell o){return false_p(o);}
bool lapi_true_p(cell o){return true_p(o);}
bool lapi_pair_p(cell o){return pair_p(o);}
bool lapi_symbol_p(cell o){return symbol_p(o);}

/*:328*//*329:*/
#line 7597 "lossless.w"

cell
lapi_cons(bool share,
cell ncar,
cell ncdr,
sigjmp_buf*failure)
{
if(!defined_p(ncar)||!defined_p(ncdr))
siglongjmp(*failure,LERR_INCOMPATIBLE);
return atom(share?Sheap:Theap,ncar,ncdr,FORM_PAIR,failure);
}

cell
lapi_car(cell o,
sigjmp_buf*failure)
{
if(!pair_p(o))
siglongjmp(*failure,LERR_INCOMPATIBLE);
return lcar(o);
}

cell
lapi_cdr(cell o,
sigjmp_buf*failure)
{
if(!pair_p(o))
siglongjmp(*failure,LERR_INCOMPATIBLE);
return lcdr(o);
}

void
lapi_set_car_m(cell o,
cell value,
sigjmp_buf*failure)
{
if(!pair_p(o)||!defined_p(value))
siglongjmp(*failure,LERR_INCOMPATIBLE);
lcar_set_m(o,value);
}

void
lapi_set_cdr_m(cell o,
cell value,
sigjmp_buf*failure)
{
if(!pair_p(o)||!defined_p(value))
siglongjmp(*failure,LERR_INCOMPATIBLE);
lcdr_set_m(o,value);
}

/*:329*//*330:*/
#line 7647 "lossless.w"

cell
lapi_env_search(cell env,
cell label,
sigjmp_buf*failure)
{
cell r;

if(null_p(env))
env= Environment;
if(!environment_p(env)||!symbol_p(label))
siglongjmp(*failure,LERR_INCOMPATIBLE);
r= env_search(env,label,true,failure);
if(undefined_p(r))
siglongjmp(*failure,LERR_MISSING);
else
return r;
}

void
lapi_env_define(cell env,
cell label,
cell value,
sigjmp_buf*failure)
{
if(null_p(env))
env= Environment;
if(!environment_p(env)||!symbol_p(label)||!defined_p(value))
siglongjmp(*failure,LERR_INCOMPATIBLE);
env_define(env,label,value,failure);
}

void
lapi_env_set(cell env,
cell label,
cell value,
sigjmp_buf*failure)
{
if(null_p(env))
env= Environment;
if(!environment_p(env)||!symbol_p(label)||!defined_p(value))
siglongjmp(*failure,LERR_INCOMPATIBLE);
env_set(env,label,value,failure);
}

void
lapi_env_clear(cell env,
cell label,
sigjmp_buf*failure)
{
if(null_p(env))
env= Environment;
if(!environment_p(env)||!symbol_p(label))
siglongjmp(*failure,LERR_INCOMPATIBLE);
env_clear(env,label,failure);
}

void
lapi_env_unset(cell env,
cell label,
sigjmp_buf*failure)
{
if(null_p(env))
env= Environment;
if(!environment_p(env)||!symbol_p(label))
siglongjmp(*failure,LERR_INCOMPATIBLE);
env_unset(env,label,failure);
}

/*:330*//*332:*/
#line 7720 "lossless.w"

cell
lapi_Accumulator(cell new)
{
if(defined_p(new))
Accumulator= new;
return Accumulator;
}
cell
lapi_User_Register(cell new)
{
if(defined_p(new))
User_Register= new;
return User_Register;
}

/*:332*//*333:*/
#line 7738 "lossless.w"

void
mem_init(void)
{
sigjmp_buf failed,*failure= &failed;
Verror reason= LERR_NONE;
cell x;
int i;

if(failure_p(reason= sigsetjmp(failed,1))){
fprintf(stderr,"FATAL Initialisation error %u: %s.\n",
reason,Ierror[reason].message);
abort();
}
/*55:*/
#line 1500 "lossless.w"

Registers[LGCR_TMPSIN]= &Tmp_SIN;
Registers[LGCR_TMPDEX]= &Tmp_DEX;
Registers[LGCR_TMPIER]= &Tmp_ier;
Registers[LGCR_NULL]= &Null_Array;
Registers[LGCR_SYMBUFFER]= &Symbol_Buffer;
Registers[LGCR_SYMTABLE]= &Symbol_Table;
Registers[LGCR_STACK]= &Stack;
Registers[LGCR_PROTECT_0]= Protect+0;
Registers[LGCR_PROTECT_1]= Protect+1;
Registers[LGCR_PROTECT_2]= Protect+2;
Registers[LGCR_PROTECT_3]= Protect+3;
Registers[LGCR_EXPRESSION]= &Expression;
Registers[LGCR_ENVIRONMENT]= &Environment;
Registers[LGCR_ACCUMULATOR]= &Accumulator;
Registers[LGCR_ARGUMENTS]= &Arguments;
Registers[LGCR_CLINK]= &Control_Link;
Registers[LGCR_OPERATORS]= &Root;
Registers[LGCR_USER]= &User_Register;

/*:55*/
#line 7752 "lossless.w"

/*35:*/
#line 851 "lossless.w"

Theap= SEGMENT_TO_HEAP(segment_alloc(-1,HEAP_CHUNK,1,HEAP_CHUNK,failure));
heap_init_sweeping(Theap,NULL);
segment_init(HEAP_TO_SEGMENT(Theap),heap_alloc(Theap,failure));
Sheap= NULL;

/*:35*//*77:*/
#line 1888 "lossless.w"

Null_Array= array_new_imp(0,NIL,FORM_ARRAY,failure);

/*:77*//*95:*/
#line 2249 "lossless.w"

Symbol_Buffer= segment_new_imp(Theap,0,SYMBOL_CHUNK,sizeof(char),0,
FORM_SEGMENT,failure);
memset(segment_address(Symbol_Buffer),'\0',SYMBOL_CHUNK);
Symbol_Table= keytable_new(0,failure);

/*:95*//*150:*/
#line 3389 "lossless.w"

Stack= array_new(STACK_CHUNK,failure);

/*:150*/
#line 7753 "lossless.w"

/*188:*/
#line 4116 "lossless.w"

Root= env_empty(failure);
for(i= 0;i<PRIMITIVE_LENGTH;i++){
x= symbol_new_const(Iprimitive[i].label);
x= Iprimitive[i].box= atom(Theap,fix(i),x,FORM_PRIMITIVE,failure);
env_define(Root,primitive_label(x),x,failure);
}

/*:188*/
#line 7754 "lossless.w"

/*182:*/
#line 3965 "lossless.w"

(void)Sym_APPLICATIVE;
(void)Sym_COMBINE_APPLY;
(void)Sym_COMBINE_BUILD;
(void)Sym_COMBINE_DISPATCH;
(void)Sym_COMBINE_FINISH;
(void)Sym_COMBINE_OPERATE;
(void)Sym_CONDITIONAL;
(void)Sym_DEFINITION;
(void)Sym_EVALUATE;
(void)Sym_ENVIRONMENT_P;
(void)Sym_OPERATIVE;

/*:182*/
#line 7755 "lossless.w"

ENV= env_extend(Root,failure);
}

/*:333*//*334:*/
#line 7759 "lossless.w"

int
lprint(char*format,
...)
{
va_list args;
int r;

assert(LDEBUG_P);
va_start(args,format);
r= vfprintf(stdout,format,args);
va_end(args);
return r;
}

int
lput(int c)
{
assert(LDEBUG_P);
return putchar(c);
}

/*:334*/
