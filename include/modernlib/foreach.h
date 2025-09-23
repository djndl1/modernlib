#ifndef MODERNLIB_FOREACH_H_
#define MODERNLIB_FOREACH_H_

#define iterator_typename(iterable_type) CONCAT(iterable_type, _iter)
#define iterator_funcname(iterable_type, func) CONCAT(iterator_typename(iterable_type), CONCAT(_, func))

#define icurrent(iter) (*iter.value)

#define iterator_begin(iterable_type) iterator_funcname(iterable_type, begin)
#define iterator_end(iterable_type) iterator_funcname(iterable_type, end)

#define iterator_rbegin(iterable_type) iterator_funcname(iterable_type, rbegin)
#define iterator_rend(iterable_type) iterator_funcname(iterable_type, rend)

#define iterator_stopped(iterable_type) iterator_funcname(iterable_type, stopped)

// normal iterator
#define iterator_next(iterable_type) iterator_funcname(iterable_type, next)

// reverse iterator
#define iterator_rev_next(iterable_type) iterator_funcname(iterable_type, rev_next)

#define foreach_iter(typname, iterable, iter_var) \
    for (iterator_typename(typname) iter_var = iterator_begin(typname)(&iterable), \
						INTERNAL_VAR(_it_) = iterator_end(typname)(&iterable); !iterator_stopped(typname)(iter_var, INTERNAL_VAR(_it_)); \
            iterator_next(typname)(&iter_var))

#define foreach_iter_rev(typname, iterable, iter_var) \
    for (iterator_typename(typname) iter_var = iterator_rbegin(typname)(&iterable), \
						INTERNAL_VAR(_it_) = iterator_rend(typname)(&iterable); !iterator_stopped(typname)(iter_var, INTERNAL_VAR(_it_)); \
            iterator_rev_next(typname)(&iter_var))

#define foreach_next(typname, begin, end, iter_var, next_func) \
    for (iterator_typename(typname) iter_var = begin; \
						!iterator_stopped(typname)(iter_var, end); \
            iterator_funcname(typname, next_func)(&iter_var))

#define foreach_begin_end(typname, begin, end, iter_var) \
		foreach_next(typname, begin, end, iter_var, next) 

#define array_begin(arr) (arr + 0)
#define array_end(arr) (arr + array_size(arr))

#define array_rbegin(arr) (arr + array_size(arr) - 1) 
#define array_rend(arr) (arr - 1)

#define foreach_array(arr, iter_var) \
    for (auto iter_var = array_begin(arr); iter_var != array_end(arr); iter_var++)
#define foreach_array_rev(arr, iter_var) \
    for (auto iter_var = array_rbegin(arr); iter_var != array_rend(arr); iter_var--)
#define acurrent(iter) (*iter)

#endif /* ifndef MODERNLIB_FOREACH_H_ */
