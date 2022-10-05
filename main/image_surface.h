#ifndef IMAGE_SURFACE_H
#define IMAGE_SURFACE_H

#include "../lib/vex3d.h"

/**
 * Image surface objects are constructed by the camera object. The image surface 
 * object generates and stores the locations of each pixel of the image in 3D 
 * space, relative to the camera. Height of the image is dependant on field of 
 * view. Pixel locations are dependant on image resolution (horizontal and 
 * vertical) and field of view, and are regenerated any time one of those fields
 * changes.
 */
class ImageSurface {
private:
    
    float _fov;
    int _h_res;
    int _v_res;

    mat4 _transform;
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
    void set_transform(const mat4& new_transform);

    float fov() const;
    int h_res() const;
    int v_res() const;
    mat4 transform() const;
    int pixel_count() const;

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
