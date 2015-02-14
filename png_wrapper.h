/* 
 * File:   png_wrapper.h
 * Author: medlan
 *
 * Created on February 14, 2015, 9:01 AM
 */

#ifndef PNG_WRAPPER_H
#define	PNG_WRAPPER_H

#include <png.h>
#define PNG_SIGSIZE 8

#ifdef	__cplusplus
extern "C" {
#endif
    png_uint_32 get_height();
    png_uint_32 get_width();
    png_byte get_channels();
    int get_bit_depth();
    int load_png(char* filename);
    int load_raw_data(void** buffer);
    void unload_png();
#ifdef	__cplusplus
}
#endif

#endif	/* PNG_WRAPPER_H */

