#ifndef GEN_BMP_H
#define GEN_BMP_H

#include <cstdio>

typedef unsigned char byte;

class Bitmap {

    struct BitmapFileHeader {
        char bitmap_signature_bytes[2] = {'B', 'M'};
        unsigned int file_size;
        unsigned int reserved_bytes = 0;
        unsigned int pixel_data_offset = 54;

        BitmapFileHeader (int pixel_data_size);
        void write_to_stream(FILE* fout); 
    };

    struct BitmapInfoHeader {
        unsigned int info_header_size = 40;
        int bitmap_width;
        int bitmap_height;
        unsigned short color_planes = 1;
        unsigned short color_depth = 24;
        unsigned int compression = 0;
        unsigned int bitmap_data_size_raw = 0;
        int horizontal_resolution = 0;
        int vertical_resolution = 0;
        unsigned int color_table_entries = 0;
        unsigned int important_colors = 0;

        BitmapInfoHeader (int width, int height); 
        void write_to_stream(FILE* fout); 
    };

    // Bitmap format stores colors as BGR instead of RGB
    static const byte* reorder_rgb(const byte* color_array, int size);

public:

    static void from_color_array (
        const byte* color_array, 
        int width,
        int height,
        const char* filename = "output.bmp");

};

#endif // GEN_BMP_H
