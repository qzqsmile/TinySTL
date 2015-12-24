#ifndef STL_CONFIG_H
#define STL_CONFIG_H

#define __STL_TEMPLATE_NULL template<>  

# ifdef __STL_EXPLICIT_FUNCTION_TMPL_ARGS  
#   define __STL_NULL_TMPL_ARGS <>  
# else  
#   define __STL_NULL_TMPL_ARGS  
# endif  

#endif