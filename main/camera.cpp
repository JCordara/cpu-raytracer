#include "camera.h"

Camera::Camera(float aspect_ratio, float fov):
    _aspect_ratio(aspect_ratio),
    _fov(fov),
    _image_surface(1080 * aspect_ratio, 1080, fov)
{}

Camera::Camera(float aspect_ratio, float fov, int vertical_resolution):
    _aspect_ratio(aspect_ratio),
    _fov(fov),
    _image_surface(
        vertical_resolution * aspect_ratio, 
        vertical_resolution, 
        fov
    )
{}

void Camera::set_pos(const vec3& new_pos) {
    _pos = new_pos;
}

void Camera::set_h_res(int new_h_res) {
    _image_surface.set_h_res(new_h_res);
}

void Camera::set_v_res(int new_v_res) {
    _image_surface.set_v_res(new_v_res);
}

vec3 Camera::pos() const {
    return _pos;
}

float Camera::apsect_ratio() const {
    return _aspect_ratio;
}

float Camera::fov() const {
    return _fov;
}

const ImageSurface& Camera::image_surface() const {
    return _image_surface;
}

int Camera::h_res() const {
    return _image_surface.h_res();
}

int Camera::v_res() const {
    return _image_surface.v_res();
}

int Camera::pixel_count() const {
    return _image_surface.pixel_count();
}
