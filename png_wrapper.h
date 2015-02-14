/* 
 * File:   png_wrapper.h
 * Author: medlan
 *
 * Created on February 14, 2015, 9:01 AM
 */

#ifndef PNG_WRAPPER_H
#define	PNG_WRAPPER_H

#include <png.h>

#ifdef	__cplusplus
extern "C" {
#endif
    long get_height();
    long get_width();
    int load_png(char* filename);
    int load_raw_data(void** buffer);
    int unload_png();
#ifdef	__cplusplus
}
#endif

#endif	/* PNG_WRAPPER_H */

