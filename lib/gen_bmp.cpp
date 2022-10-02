#include "gen_bmp.h"

Bitmap::BitmapFileHeader::BitmapFileHeader (int pixel_data_size) {
   this->file_size = 
       pixel_data_offset + static_cast<unsigned int>(pixel_data_size); 
}

void Bitmap::BitmapFileHeader::write_to_stream(FILE* p_file) {
    fwrite(bitmap_signature_bytes, sizeof(unsigned char), 2, p_file); 
    fwrite(&file_size, sizeof(unsigned int), 1, p_file); 
    fwrite(&reserved_bytes, sizeof(unsigned int), 1, p_file); 
    fwrite(&pixel_data_offset, sizeof(unsigned int), 1, p_file); 
}


Bitmap::BitmapInfoHeader::BitmapInfoHeader (int width, int height) {
    this->bitmap_width = static_cast<int>(width);
    this->bitmap_height = static_cast<int>(height);
}

void Bitmap::BitmapInfoHeader::write_to_stream(FILE* p_file) {
    fwrite(&info_header_size, sizeof(unsigned int), 1, p_file);
    fwrite(&bitmap_width, sizeof(int), 1, p_file);
    fwrite(&bitmap_height, sizeof(int), 1, p_file);
    fwrite(&color_planes, sizeof(unsigned short), 1, p_file);
    fwrite(&color_depth, sizeof(unsigned short), 1, p_file);
    fwrite(&compression, sizeof(unsigned int), 1, p_file);
    fwrite(&bitmap_data_size_raw, sizeof(unsigned int), 1, p_file);
    fwrite(&horizontal_resolution, sizeof(int), 1, p_file);
    fwrite(&vertical_resolution, sizeof(int), 1, p_file);
    fwrite(&color_table_entries, sizeof(unsigned int), 1, p_file);
    fwrite(&important_colors, sizeof(unsigned int), 1, p_file);
}


const byte* Bitmap::reorder_rgb(const byte* color_array, int size) {
    byte* arr = new byte[size];
    for (int i = 0; i < size; i += 3) {
        arr[ i ] = color_array[i+2];
        arr[i+1] = color_array[i+1];
        arr[i+2] = color_array[ i ];
    }
    return arr;
}

void Bitmap::from_color_array (
    const byte* color_array, 
    int width,
    int height,
    const char* filename) 
{
    int array_size = width * height * 3 * sizeof(byte);
    const byte* reordered_color_array = reorder_rgb(color_array, array_size);
    BitmapFileHeader file_header(array_size);
    BitmapInfoHeader info_header(width,  height);

    FILE* p_file = fopen(filename,"wb");
    if(p_file == NULL) return;

    file_header.write_to_stream(p_file);
    info_header.write_to_stream(p_file);
    fwrite(reordered_color_array, sizeof(byte), array_size, p_file);
    fclose(p_file);

    delete[] reordered_color_array;
}

