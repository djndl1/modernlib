#ifndef MEM_PTR_MACRO_H_
#define MEM_PTR_MACRO_H_

#undef mem_ptr_funcname
#define mem_ptr_funcname(funcname) CONCAT(mem_ptr_typename, _ ## funcname)

#undef mem_ptr_alloc_result
#define mem_ptr_alloc_result CONCAT(mem_ptr_typename, _ ## alloc_result)


#endif /* ifndef MEM_PTR_MACRO_H_

 */
