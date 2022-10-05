#include "camera.h"

Camera::Camera(float aspect_ratio, float fov, int vertical_resolution):
    _aspect_ratio(aspect_ratio),
    _fov(fov),
    _image_surface(
        vertical_resolution * aspect_ratio, 
        vertical_resolution, 
        fov
    ),
    _transform(1.0f)
{}

void Camera::set_pos(const vec3& new_pos) {
    _pos = new_pos;
    _transform = mat4(
        _transform[0][0], _transform[0][1], _transform[0][2], _pos.x,
        _transform[1][0], _transform[1][1], _transform[1][2], _pos.y,
        _transform[2][0], _transform[2][1], _transform[2][2], _pos.z,
        _transform[3][0], _transform[3][1], _transform[3][2],  1.0f
    );
    _image_surface.set_transform(_transform);
}

void Camera::set_h_res(int new_h_res) {
    _image_surface.set_h_res(new_h_res);
}

void Camera::set_v_res(int new_v_res) {
    _image_surface.set_v_res(new_v_res);
}

const vec3& Camera::pos() const {
    return _pos;
}

const mat4& Camera::transform() const {
    return _transform;
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
