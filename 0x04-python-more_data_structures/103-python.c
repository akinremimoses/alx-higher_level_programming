#include <stdio.h>
#include <stdlib.h>
#include <Python.h>

void print_python_bytes(PyObject *p)
{
    printf("[.] bytes object info\n");
    
    if (!PyBytes_Check(p))
    {
        printf("  [ERROR] Invalid Bytes Object\n");
        return;
    }

    Py_ssize_t size = PyBytes_Size(p);
    char *str = PyBytes_AsString(p);

    printf("  size: %zd\n", size);
    printf("  trying string: %s\n", str);

    printf("  first 10 bytes: ");
    for (Py_ssize_t i = 0; i < 10 && i < size; i++)
    {
        printf("%02x ", (unsigned char)str[i]);
    }
    printf("\n");
}

void print_python_list(PyObject *p)
{
    printf("[*] Python list info\n");

    Py_ssize_t size = PyList_Size(p);
    printf("[*] Size of the Python List = %zd\n", size);
    
    Py_ssize_t allocated = ((PyListObject *)p)->allocated;
    printf("[*] Allocated = %zd\n", allocated);

    for (Py_ssize_t i = 0; i < size; i++)
    {
        PyObject *elem = PyList_GetItem(p, i);
        printf("Element %zd: %s\n", i, Py_TYPE(elem)->tp_name);
        
        if (PyBytes_Check(elem))
        {
            print_python_bytes(elem);
        }
    }
}

int main(void)
{
    PyObject *s, *b, *l;

    Py_Initialize();

    s = PyBytes_FromString("Hello");
    b = PyBytes_FromString("\xff\xf8\x00\x00\x00\x00\x00\x00");
    l = PyList_New(2);
    PyList_SetItem(l, 0, s);
    PyList_SetItem(l, 1, b);

    print_python_bytes(s);
    print_python_bytes(b);
    print_python_list(l);

    Py_XDECREF(s);
    Py_XDECREF(b);
    Py_XDECREF(l);

    Py_Finalize();

    return (0);
}
