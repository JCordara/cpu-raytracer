#ifndef CAMERA_H
#define CAMERA_H

#include "../lib/vex3d.h"
#include "image_surface.h"

class Camera {
private:
    vec3 _pos;
    // TODO: Add orientation
    // vec3 _up;

    float _aspect_ratio;
    float _fov;

    ImageSurface _image_surface;

public:

    Camera(float aspect_ratio, float fov);

    // Only vertical resolution is needed. ex. 1080 => 1920x1080
    Camera(float aspect_ratio, float fov, int vertical_resolution);

    void set_pos(const vec3& new_pos);
    // void look_at(const vec3& target);
    // void look_dir(const vec3& direction);

    void set_h_res(int new_h_res);
    void set_v_res(int new_v_res);

    vec3 get_pos() const;
    float apsect_ratio() const;
    float fov() const;

    // Read-only reference to the underlying image surface for pixel iteration
    const ImageSurface& image_surface() const;

    int get_h_res() const;
    int get_v_res() const;
    int get_pixel_count() const;

};

#endif // CAMERA_H
