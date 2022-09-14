#include "gen_bmp.h"


Bitmap::BitmapFileHeader::BitmapFileHeader (int pixel_data_size) {
   this->file_size = 
       pixel_data_offset + static_cast<uint32_t>(pixel_data_size); 
}

void Bitmap::BitmapFileHeader::write_to_stream(std::ofstream &fout) {
    fout.write((char*)&this->bitmap_signature_bytes, 2); 
    fout.write((char*)&this->file_size, sizeof(uint32_t)); 
    fout.write((char*)&this->reserved_bytes, sizeof(uint32_t)); 
    fout.write((char*)&this->pixel_data_offset, sizeof(uint32_t)); 
}


Bitmap::BitmapInfoHeader::BitmapInfoHeader (int width, int height) {
    this->bitmap_width = static_cast<int32_t>(width);
    this->bitmap_height = static_cast<int32_t>(height);
}

void Bitmap::BitmapInfoHeader::write_to_stream(std::ofstream &fout) {
    fout.write((char*)&this->info_header_size, sizeof(uint32_t));
    fout.write((char*)&this->bitmap_width, sizeof(int32_t));
    fout.write((char*)&this->bitmap_height, sizeof(int32_t));
    fout.write((char*)&this->color_planes, sizeof(uint16_t));
    fout.write((char*)&this->color_depth, sizeof(uint16_t));
    fout.write((char*)&this->compression, sizeof(uint32_t));
    fout.write((char*)&this->bitmap_data_size_raw, sizeof(uint32_t));
    fout.write((char*)&this->horizontal_resolution, sizeof(int32_t));
    fout.write((char*)&this->vertical_resolution, sizeof(int32_t));
    fout.write((char*)&this->color_table_entries, sizeof(uint32_t));
    fout.write((char*)&this->important_colors, sizeof(uint32_t));
}

void Bitmap::from_color_array (
    const char* color_array, 
    int width,
    int height,
    const char* filename) 
{
    int array_size = width * height * 3 * sizeof(char);

    BitmapFileHeader file_header(array_size);
    BitmapInfoHeader info_header(width,  height);

    std::ofstream output_file(filename, std::ios::binary);

    file_header.write_to_stream(output_file);
    info_header.write_to_stream(output_file);
    output_file.write(color_array, array_size);

    output_file.close();
}

