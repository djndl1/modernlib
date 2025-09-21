#ifndef MODERNLIB_FOREACH_H_
#define MODERNLIB_FOREACH_H_

#define iterator_typename(iterable_type) CONCAT(iterable_type, _iter)
#define iterator_funcname(iterable_type, func) CONCAT(iterator_typename(iterable_type), _ ## func)

#define icurrent(iter) (*iter.current)
#define iterator_new(iterable_type) iterator_funcname(iterable_type, new)
#define iterator_new_from(iterable_type) iterator_funcname(iterable_type, new_from)
#define iterator_stopped(iterable_type) iterator_funcname(iterable_type, stopped)
#define iterator_next(iterable_type) iterator_funcname(iterable_type, next)

#define foreach_iter(typname, iterable, iter_var) \
    for (auto iter_var = iterator_new(typname)(iterable); \
            !iterator_stopped(typname)(iter_var); \
            iterator_next(typname)(&iter_var))

#define foreach_begin_end(typname, begin, end, iter_var) \
    for (auto iter_var = iterator_new_from(typname)(begin, end); \
            !iterator_stopped(typname)(iter_var); \
            iterator_next(typname)(&iter_var))


#endif /* ifndef MODERNLIB_FOREACH_H_ */
