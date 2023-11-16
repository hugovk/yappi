#include "tls.h"
#include "mem.h"

tls_key_t *
create_tls_key()
{

    tls_key_t* key;
    YPY_KEY_TYPE py_key;

    key = ymalloc(sizeof(tls_key_t));
    if(!key) {
        return NULL;
    }

    py_key = PyThread_tss_alloc();
    if (!py_key) {
        goto error;
    }

    if (PyThread_tss_create(py_key) != 0) {
        PyThread_tss_free(py_key);
        goto error;
    }

    key->_key = py_key;
    return key;

error:
    yfree(key);
    return NULL;
}

int
set_tls_key_value(tls_key_t* key, void* value)
{
    return PyThread_tss_set(key->_key, value);
}

void*
get_tls_key_value(tls_key_t* key)
{
    void* res;
    res = PyThread_tss_get(key->_key);
    return res;
}

void
delete_tls_key(tls_key_t* key)
{
    PyThread_tss_delete(key->_key);
    PyThread_tss_free(key->_key);
    yfree(key);
}