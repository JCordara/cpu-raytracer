#ifndef GEN_BMP_H
#define GEN_BMP_H

#include <fstream>

class Bitmap {

    struct BitmapFileHeader {
        char bitmap_signature_bytes[2] = {'B', 'M'};
        uint32_t file_size;
        uint32_t reserved_bytes = 0;
        uint32_t pixel_data_offset = 54;

        BitmapFileHeader (int pixel_data_size);
        void write_to_stream(std::ofstream &fout); 
    };

    struct BitmapInfoHeader {
        uint32_t info_header_size = 40;
        int32_t bitmap_width;
        int32_t bitmap_height;
        uint16_t color_planes = 1;
        uint16_t color_depth = 24;
        uint32_t compression = 0;
        uint32_t bitmap_data_size_raw = 0;
        int32_t horizontal_resolution = 3780; // try 0
        int32_t vertical_resolution = 3780; // try 0
        uint32_t color_table_entries = 0;
        uint32_t important_colors = 0;

        BitmapInfoHeader (int width, int height); 
        void write_to_stream(std::ofstream &fout); 
    };

public:

    static void from_color_array (
        const char* color_array, 
        int width,
        int height,
        const char* filename = "output.bmp");

};

#endif // GEN_BMP_H
