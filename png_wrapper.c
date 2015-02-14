#include "png_wrapper.h"
#include <stdio.h>
#include <stdint.h>
#include <png.h>

static long height = -1, width = -1;
static png_infop png_info_ptr;
static png_structp png_ptr;;

static void readpng_version_info(){
    fprintf(stderr, "   Compiled with libpng %s; using libpng %s.\n",
                PNG_LIBPNG_VER_STRING, png_libpng_ver);
    fprintf(stderr, "   Compiled with zlib %s; using zlib %s.\n",
                ZLIB_VERSION, zlib_version);
}

long get_height(){
    return height;
}

long get_width(){
    return width;
}

int load_png(char* filename){
    readpng_version_info();
    uint8_t sig[8];
    FILE* infile = fopen(filename, "rb");
    if(infile == NULL)
        return -2;
    if(fread(sig, 1, 8, infile) != 8){
        fclose(infile);
        return -4;
    }
    if(!png_check_sig(sig, 8)){
        fclose(infile);
        return -1;
    }
    
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(png_ptr == NULL){
        fclose(infile);
        return -3;
    }
    
    png_info_ptr = png_create_info_struct(png_ptr);
    if(png_info_ptr == NULL){
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        fclose(infile);
        return -4;
    }
    
    
    
    png_destroy_read_struct(&png_ptr, &png_info_ptr, NULL);
    fclose(infile);
    return 7;
    
}

int load_raw_data(void** buffer){
    //write into buffer raw data 0th byte to (width*length*sizeof(pixel)-1)th byte
    return -1;
}

int unload_png(){
    //TODO: free memory
}
