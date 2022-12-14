#ifndef CAMERA_H
#define CAMERA_H

#include "../lib/vex3d.h"
#include "image_surface.h"

/**
 * Camera object is used as a constant reference by the ray tracer object.
 * Composed of a position vector and an image surface. Image surface contains
 * the locations of each pixel that makes up the screen. Resolution of the image
 * produced by the raytracer is determined by the camera's resolution, which is
 * stored in the image surface object.
 */
class Camera {
private:
    vec3 _pos;
    // TODO: Add orientation
    // vec3 _up;
    mat4 _transform;

    ImageSurface _image_surface;

    float _aspect_ratio;
    float _fov;

public:

    // Only vertical resolution is needed. ex. 1080 => 1920x1080
    Camera(float aspect_ratio, float fov, int vertical_resolution = 1080);

    void set_pos(const vec3& new_pos);
    // void look_at(const vec3& target);
    // void look_dir(const vec3& direction);

    void set_h_res(int new_h_res);
    void set_v_res(int new_v_res);

    const vec3& pos() const;
    const mat4& transform() const;
    float apsect_ratio() const;
    float fov() const;
    int h_res() const;
    int v_res() const;
    int pixel_count() const;

    // Read-only reference to the underlying image surface for pixel iteration
    const ImageSurface& image_surface() const;
    
};

#endif // CAMERA_H
