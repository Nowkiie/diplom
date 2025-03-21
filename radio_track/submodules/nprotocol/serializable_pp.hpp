#pragma once


//макросы для цикла на уровне препроцессора

#define PP_CALC(X) X

#define __VA_NARG__(...) \
             PP_NARG_(__VA_ARGS__, PP_RSEQ_N())
#define PP_NARG_(...) \
             PP_CALC(PP_ARG_N(__VA_ARGS__))
#define PP_ARG_N( \
                  _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
                 _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
                 _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
                 _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
                 _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
                 _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
                 _61,_62,_63,N,...) N

#define PP_RSEQ_N() \
             63,62,61,60,                   \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0 


#define PP_CAT_I(A, B) A ## B
#define PP_CAT(A, B) PP_CAT_I(A, B)

#define PP_SEQ_EXPAND(...) __VA_ARGS__

#define PP_EXPAND_CALL_V(MACRO, ...) PP_CAT(MACRO, __VA_ARGS__)
#define PP_EXPAND_CALL(MACRO, SEQ) PP_CALC(PP_EXPAND_CALL_V(MACRO SEQ))


#define PP_FOREACH(MACRO, SEQ) PP_FOREACH_I(MACRO, PP_SEQ_EXPAND SEQ)
#define PP_FOREACH_I(MACRO, ...) PP_CALC(PP_CAT(PP_FOREACH_, __VA_NARG__(__VA_ARGS__))(MACRO, __VA_ARGS__))


#define PP_FOREACH_1(M, S) M(S)
#define PP_FOREACH_2(M, S, ... ) M(S) PP_CALC(PP_FOREACH_1(M, __VA_ARGS__))
#define PP_FOREACH_3(M, S, ... ) M(S) PP_CALC(PP_FOREACH_2(M, __VA_ARGS__))
#define PP_FOREACH_4(M, S, ... ) M(S) PP_CALC(PP_FOREACH_3(M, __VA_ARGS__))
#define PP_FOREACH_5(M, S, ... ) M(S) PP_CALC(PP_FOREACH_4(M, __VA_ARGS__))
#define PP_FOREACH_6(M, S, ... ) M(S) PP_CALC(PP_FOREACH_5(M, __VA_ARGS__))
#define PP_FOREACH_7(M, S, ... ) M(S) PP_CALC(PP_FOREACH_6(M, __VA_ARGS__))
#define PP_FOREACH_8(M, S, ... ) M(S) PP_CALC(PP_FOREACH_7(M, __VA_ARGS__))
#define PP_FOREACH_9(M, S, ... ) M(S) PP_CALC(PP_FOREACH_8(M, __VA_ARGS__))
#define PP_FOREACH_10(M, S, ... ) M(S) PP_CALC(PP_FOREACH_9(M, __VA_ARGS__))
#define PP_FOREACH_11(M, S, ... ) M(S) PP_CALC(PP_FOREACH_10(M, __VA_ARGS__))
#define PP_FOREACH_12(M, S, ... ) M(S) PP_CALC(PP_FOREACH_11(M, __VA_ARGS__))
#define PP_FOREACH_13(M, S, ... ) M(S) PP_CALC(PP_FOREACH_12(M, __VA_ARGS__))
#define PP_FOREACH_14(M, S, ... ) M(S) PP_CALC(PP_FOREACH_13(M, __VA_ARGS__))
#define PP_FOREACH_15(M, S, ... ) M(S) PP_CALC(PP_FOREACH_14(M, __VA_ARGS__))
#define PP_FOREACH_16(M, S, ... ) M(S) PP_CALC(PP_FOREACH_15(M, __VA_ARGS__))
#define PP_FOREACH_17(M, S, ... ) M(S) PP_CALC(PP_FOREACH_16(M, __VA_ARGS__))
#define PP_FOREACH_18(M, S, ... ) M(S) PP_CALC(PP_FOREACH_17(M, __VA_ARGS__))
#define PP_FOREACH_19(M, S, ... ) M(S) PP_CALC(PP_FOREACH_18(M, __VA_ARGS__))
#define PP_FOREACH_20(M, S, ... ) M(S) PP_CALC(PP_FOREACH_19(M, __VA_ARGS__))
#define PP_FOREACH_21(M, S, ... ) M(S) PP_CALC(PP_FOREACH_20(M, __VA_ARGS__))
#define PP_FOREACH_22(M, S, ... ) M(S) PP_CALC(PP_FOREACH_21(M, __VA_ARGS__))
#define PP_FOREACH_23(M, S, ... ) M(S) PP_CALC(PP_FOREACH_22(M, __VA_ARGS__))
#define PP_FOREACH_24(M, S, ... ) M(S) PP_CALC(PP_FOREACH_23(M, __VA_ARGS__))
#define PP_FOREACH_25(M, S, ... ) M(S) PP_CALC(PP_FOREACH_24(M, __VA_ARGS__))
#define PP_FOREACH_26(M, S, ... ) M(S) PP_CALC(PP_FOREACH_25(M, __VA_ARGS__))
#define PP_FOREACH_27(M, S, ... ) M(S) PP_CALC(PP_FOREACH_26(M, __VA_ARGS__))
#define PP_FOREACH_28(M, S, ... ) M(S) PP_CALC(PP_FOREACH_27(M, __VA_ARGS__))
#define PP_FOREACH_29(M, S, ... ) M(S) PP_CALC(PP_FOREACH_28(M, __VA_ARGS__))
#define PP_FOREACH_30(M, S, ... ) M(S) PP_CALC(PP_FOREACH_29(M, __VA_ARGS__))
#define PP_FOREACH_31(M, S, ... ) M(S) PP_CALC(PP_FOREACH_30(M, __VA_ARGS__))
#define PP_FOREACH_32(M, S, ... ) M(S) PP_CALC(PP_FOREACH_31(M, __VA_ARGS__))
