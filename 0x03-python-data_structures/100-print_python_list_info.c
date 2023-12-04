#include <stdlib.h>
#include <stdio.h>
#include <Python.h>

/**
 * print_python_list_info - function that prints some basic info about Python lists
 * @p: python list
 */
void print_python_list_info(PyObject *p)
{
    Py_ssize_t size, elem;

    size = PyList_Size(p);
    printf("[*] Size of the Python List = %zd\n", size);

    printf("[*] Allocated = %zd\n", ((PyListObject *)p)->allocated);
    
    for (elem = 0; elem < size; elem++)
        printf("Element %zd: %s\n", elem, Py_TYPE(PyList_GetItem(p, elem))->tp_name);
}
