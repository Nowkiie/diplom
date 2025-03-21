//#include <boost\preprocessor.hpp>
#include "serializable_pp.hpp"



#define PROTOCOL_MESSAGE(MESSAGE) enum { message = MESSAGE }; enum { protocol = CURRENT_PROTOCOL };

#define SERIALIZABLE(...) PP_FOREACH(REFLECT_EACH_DECL, (__VA_ARGS__)) 

#define REFLECT_TYPE(T, _, ...) T
#define REFLECT_NAME(_, N, ...) N
#define REFLECT_INIT(...) PP_CALC(PP_CAT(REFLECT_INIT_, __VA_NARG__(__VA_ARGS__))(__VA_ARGS__))

#define REFLECT_INIT_2(...) {}
#define REFLECT_INIT_3(_1, _2, I) I


#define REFLECT_EACH_DECL(X) PP_EXPAND_CALL(REFLECT_TYPE, X) PP_EXPAND_CALL(REFLECT_NAME, X) PP_EXPAND_CALL(REFLECT_INIT, X);


#define SERIALIZABLE_STRUCT_MESSAGE(STRUCT_NAME, MESSAGE, ...) struct STRUCT_NAME { PP_CALC(PROTOCOL_MESSAGE(MESSAGE))  PP_CALC(SERIALIZABLE(__VA_ARGS__)) }
#define SERIALIZABLE_STRUCT(STRUCT_NAME, ...) struct STRUCT_NAME { PP_CALC(SERIALIZABLE(__VA_ARGS__)) }
