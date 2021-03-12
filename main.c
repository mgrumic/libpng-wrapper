/* 
 * File:   main.c
 * Author: medlan
 *
 * Created on February 14, 2015, 8:52 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "png_wrapper.h"

#ifndef NDEBUG
#define assert(X) printf("%s:%d returns %d\n", __FUNCTION__, __LINE__, X)
#else
#define assert(X) X
#endif
/*
 * 
 */

void test()
{
}

void test2()
{
}

void test3()
{
}

void dump_data(unsigned char* ptr, int height, int stride){
    int i, j;
    for(i = 0; i<height; i++){
        printf("row: %d\n", i);
        for(j = 0; j<stride; j+=4){
            printf("Pixel[%d, %d]: ", i, j/4);
            printf("0x%02X", ptr[i*height + j]);
            printf("%02X", ptr[i*height + j+1]);
            printf("%02X", ptr[i*height + j+2]);
            printf("%02X\n", ptr[i*height + j+3]);
        }
    }
}
int main(int argc, char** argv) {
    void* ptr;
    int stride;
    assert(load_png("/home/medlan/Desktop/linux.png"));
    stride = get_width() * get_bit_depth() * get_channels() / 8;
    assert((int)get_width());
    assert((int)get_height());
    assert((int)get_bit_depth());
    assert((int)get_channels());
    assert(load_raw_data(&ptr));
    dump_data(ptr, get_height(), stride);
    FILE* fp = fopen("/home/medlan/Desktop/output.bmp", "wb");
    fwrite(ptr, stride, get_height(), fp);
    fclose(fp);
    free(ptr);
    unload_png();
    return (EXIT_SUCCESS);
}

