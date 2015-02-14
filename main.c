/* 
 * File:   main.c
 * Author: medlan
 *
 * Created on February 14, 2015, 8:52 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "png_wrapper.h"

#ifndef NDEBUG
#define assert(X) printf("%s:%d returns %d\n", __FUNCTION__, __LINE__, X)
#else
#define assert(X) X
#endif
/*
 * 
 */
int main(int argc, char** argv) {
    assert(load_png("/home/medlan/Desktop/linux.png"));
    return (EXIT_SUCCESS);
}

