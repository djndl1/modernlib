#ifndef COLLECTION_H_
#define COLLECTION_H_

#include <stddef.h>
#include "interface.h"

struct collection_obj;

typedef struct collection_itf {
    size_t (*count)(const struct collection_obj*);
} collection_itf;

typedef struct collection_obj {
    const interface_base base;
    const collection_itf *itf;
} collection_obj;

#endif // COLLECTION_H_
