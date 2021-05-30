/*253:*/
#line 4780 "lossless.w"

#ifndef LLT_H
#define LLT_H
/*254:*/
#line 4806 "lossless.w"

#define LLT_FIXTURE_HEADER  \
        char *name;         \
        char *suffix;       \
        int id;             \
        llt_thunk prepare;  \
        llt_thunk act;      \
        llt_case test;      \
        llt_thunk destroy;  \
        boolean skip_gc_p 

/*:254*/
#line 4783 "lossless.w"

typedef struct llt_Fixture llt_Fixture;
typedef void(*llt_thunk)(llt_Fixture*);
typedef boolean(*llt_case)(llt_Fixture*);
typedef llt_buffer*(*llt_fixture)(void);
extern llt_fixture Test_Fixtures[];

#define fmsgf(...) test_msgf(buf, fix.name, __VA_ARGS__)
#define fpmsgf(...) test_msgf(buf, fix->name, __VA_ARGS__)

#define llt_fix_append(o,d) ((o) == NULL    \
        ? (o) =  llt_alloc((d), llt_Fixture) \
        : llt_grow_by((o), (d)))

boolean llt_main(size_t,llt_Fixture*);
llt_buffer*llt_prepare(void);

#endif 

/*:253*/
