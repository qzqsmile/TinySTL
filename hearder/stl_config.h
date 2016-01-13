#ifndef STL_CONFIG_H
#define STL_CONFIG_H

#define __STL_TEMPLATE_NULL template<>  
#define __STL_USE_EXCEPTIONS

# ifdef __STL_EXPLICIT_FUNCTION_TMPL_ARGS  
#   define __STL_NULL_TMPL_ARGS <>  
# else  
#   define __STL_NULL_TMPL_ARGS  
# endif  


#ifdef __STL_USE_EXCEPTIONS
#define __STL_TRY   try
#define __STL_UNWIND(action)   catch(...) { action; throw; }
#else
#define __STL_TRY
#define __STL_UNWIND(action)
#endif

#endif