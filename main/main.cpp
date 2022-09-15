#include "../lib/gen_bmp.h"
#include "../lib/vec3f.h"

#ifdef _DEBUG
    #include <iostream>
    #define cout std::cout
#else
    #define cout //
#endif

class Raytracer {
public:
    vec3 trace(const vec3& origin, const vec3& direction) {
        vec3 d = direction.normalize();
        vec3 color = ((d * 0.5f) + 0.5f) * 255;
        return color;
    }
    void set_num_bounces(int n) {}
};

class Canvas {
private:
    vec3 *pixels;
    int arr_size = 0;

public:
    Canvas(
        int width, int height,
        /* vec3& direction = vec3(0, 0, -1), UNUSED */
        // TODO: Allow for camera rotation using rotation matrix
        const vec3& camera_pos = vec3(), 
        float distance = 1.0f) 
    {
        // Initialize canvas as grid of pixel coordinates in 3D space
        arr_size = width * height;
        pixels = new vec3[arr_size];

        int half_width = width / 2;
        int half_height = height / 2;
        vec3 canvas_normal = vec3(0, 0, -1);
        vec3 canvas_origin = canvas_normal * distance;

        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                unsigned int index = (row * width) + col;
                pixels[index] = canvas_origin + 
                    vec3(row - half_height, col - half_width, 0);
            }
        }
    }

    ~Canvas() {
        delete[] pixels;
    }

    vec3* begin() {return pixels;}
    vec3* end() {return pixels + arr_size;}
};


int main(int argc, char **argv) {
    
    int image_width = 600;
    int image_height = 400;

    Raytracer raytracer;
    raytracer.set_num_bounces(3);

    vec3 camera_pos = vec3(0);
    Canvas canvas(image_width, image_height, camera_pos, 1.0f);

    unsigned char* framebuffer = new unsigned char[image_width * image_height * 3];
    int fb_index = 0;
    for (vec3& pixel : canvas) {
        vec3 color = raytracer.trace(camera_pos, pixel - camera_pos);
        framebuffer[fb_index++] = static_cast<unsigned char>(color.x);
        framebuffer[fb_index++] = static_cast<unsigned char>(color.y);
        framebuffer[fb_index++] = static_cast<unsigned char>(color.z);
    }

    Bitmap::from_color_array(framebuffer, image_width, image_height);

    delete[] framebuffer;
    return 0;
}

