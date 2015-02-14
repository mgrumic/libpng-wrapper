#include "png_wrapper.h"
#include <stdlib.h>
//#include <stdint.h>
//#include <png.h>
//#include <pngconf.h>

static png_uint_32 height = 0, width = 0;
static int bit_depth = -1;
static png_infop png_info_ptr = NULL;
static png_structp png_ptr = NULL;
static png_bytep* pData;
static int color_type = -1;
static png_FILE_p infile = NULL;
static png_byte channels = 0;
static png_bytepp row_ptrs = NULL;
static void readpng_version_info(){
    fprintf(stderr, "   Compiled with libpng %s; using libpng %s.\n",
                PNG_LIBPNG_VER_STRING, png_libpng_ver);
    fprintf(stderr, "   Compiled with zlib %s; using zlib %s.\n",
                ZLIB_VERSION, zlib_version);
}

png_uint_32 get_height(){
    return height;
}

png_uint_32 get_width(){
    return width;
}

png_byte get_channels(){
    return channels;
}

int get_bit_depth(){
    return bit_depth;
}

int load_png(char* filename){
    readpng_version_info();
    png_byte sig[8];
    png_FILE_p infile = fopen(filename, "rb");
    if(infile == NULL)
        return -2;//Poslije cemo postaviti enume za error kodove, posto ce mi   
                  //trebati za ponedeljak ova biblioteka i smislicemo malo bolji
                  //nacin za ovo
    if(fread(sig, 1, PNG_SIGSIZE, infile) != PNG_SIGSIZE){
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
    
    if(setjmp(png_ptr->jmpbuf)){
        png_destroy_read_struct(&png_ptr, &png_info_ptr, NULL);
        return -5;
    }
    
    png_init_io(png_ptr, infile);
    png_set_sig_bytes(png_ptr, PNG_SIGSIZE);
    png_read_info(png_ptr, png_info_ptr);
    channels = png_get_channels(png_ptr, png_info_ptr);
    png_get_IHDR(png_ptr, png_info_ptr, &width, &height, &bit_depth, &color_type,
                NULL, NULL, NULL);
    
    
    return 7;
    
}

int load_raw_data(void** buffer){
    //write into buffer raw data 0th byte to (width*length*sizeof(pixel)-1)th byte
    *buffer = malloc(width * height * bit_depth * channels / 8);
    if(*buffer == NULL)
        return -1;
    
    row_ptrs = (png_bytepp)malloc(sizeof(png_bytep)*height);
    if(row_ptrs == NULL){
        free(buffer);
        return -2;
    }
    const unsigned stride = width * bit_depth * channels / 8;
    size_t i;
    for(i = 0; i < height; i++){
        png_uint_32 q = (height - i - 1) * stride;
        row_ptrs[i] = (png_bytep)*buffer + q;
    }
    
    png_read_image(png_ptr, row_ptrs);
    return 0;
}

void unload_png(){
    //TODO: free memory
    if(infile)
        fclose(infile);
    if(row_ptrs)
        free(row_ptrs);
    (&png_ptr, &png_info_ptr, NULL);
}
