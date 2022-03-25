/*3:*/
#line 113 "lossless.w"

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
#line 114 "lossless.w"

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
#line 115 "lossless.w"

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

#line 116 "lossless.w"

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
#line 117 "lossless.w"

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
#line 118 "lossless.w"

/*16:*/
#line 367 "lossless.w"

extern Oerror Ierror[];

/*:16*//*20:*/
#line 429 "lossless.w"

extern unique bool Interrupt;

/*:20*//*33:*/
#line 821 "lossless.w"

extern shared Oheap*Sheap;
extern unique Oheap*Theap;

/*:33*//*76:*/
#line 1885 "lossless.w"

extern shared cell Null_Array;

/*:76*//*149:*/
#line 3386 "lossless.w"

extern unique long StackP;

/*:149*//*247:*/
#line 5780 "lossless.w"

extern unique cell Accumulator;
extern unique cell Environment;

/*:247*//*325:*/
#line 7559 "lossless.w"

cell lapi_NIL(void);
cell lapi_FALSE(void);
cell lapi_TRUE(void);
cell lapi_VOID(void);
cell lapi_EOF(void);
cell lapi_UNDEFINED(void);

/*:325*//*327:*/
#line 7577 "lossless.w"

bool lapi_null_p(cell);
bool lapi_false_p(cell);
bool lapi_true_p(cell);
bool lapi_pair_p(cell);
bool lapi_symbol_p(cell);

cell lapi_cons(bool,cell,cell,sigjmp_buf*);
cell lapi_car(cell,sigjmp_buf*);
cell lapi_cdr(cell,sigjmp_buf*);
void lapi_set_car_m(cell,cell,sigjmp_buf*);
void lapi_set_cdr_m(cell,cell,sigjmp_buf*);

/*:327*/
#line 119 "lossless.w"


/*:3*/
