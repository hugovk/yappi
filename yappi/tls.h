#ifndef YTLS_H
#define YTLS_H

#include "Python.h"
#include "pythread.h"

#define YPY_KEY_TYPE Py_tss_t*

typedef struct {
    YPY_KEY_TYPE _key;
} tls_key_t;


tls_key_t* create_tls_key(void);
int set_tls_key_value(tls_key_t* key, void* value);
void* get_tls_key_value(tls_key_t* key);
void delete_tls_key(tls_key_t* key);
#endif
