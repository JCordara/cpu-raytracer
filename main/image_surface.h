#ifndef IMAGE_SURFACE_H
#define IMAGE_SURFACE_H

#include "../lib/vex3d.h"

class ImageSurface {
private:
    
    float _fov;
    int _h_res;
    int _v_res;

    const float _radius = 1.0f;
    float _height;

    vec3 *_pixels; // heap allocated
    int _arr_size = 0;

public:

    ImageSurface(int h_res, int v_res, float fov);
    ~ImageSurface();

    void set_fov(float new_fov);
    void set_h_res(int new_h_res);
    void set_v_res(int new_v_res);

    float get_fov() const;
    int get_h_res() const;
    int get_v_res() const;
    int get_pixel_count() const;

    /**
     * Internal function for generating curved image surface given fov and 
     * aspect ratio
     */
    void _generate_surface();

    /**
     * Forward read-only iterator to pixel locations in 3D space.
     * Iterates left to right, top to bottom.
     */
    class PixelIterator {
    private:
        vec3* m_ptr;

    public:
        PixelIterator(vec3* ptr);
        const vec3& operator*() const;
        const vec3* operator->() const;

        PixelIterator& operator++();

        friend bool operator== (const PixelIterator& a, const PixelIterator& b);
        friend bool operator!= (const PixelIterator& a, const PixelIterator& b);
    };

    PixelIterator begin() const;
    PixelIterator end() const;
};

#endif // IMAGE_SURFACE_H
