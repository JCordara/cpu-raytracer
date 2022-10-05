#include "image_surface.h"
#include "debug.h"

using PixelIterator = ImageSurface::PixelIterator;

ImageSurface::ImageSurface(int h_res, int v_res, float fov):
    _h_res(h_res),
    _v_res(v_res),
    _fov(fov),
    _transform(1.0f)
{
    _arr_size = _h_res * _v_res;
    _pixels = new vec3[_arr_size];
    float aspect_ratio = static_cast<float>(_h_res) / static_cast<float>(_v_res);
    _height = _fov / aspect_ratio;
    _generate_surface();
}

ImageSurface::~ImageSurface() {
    delete[] _pixels;
}

void ImageSurface::set_fov(float new_fov) {
    _fov = new_fov;
    _generate_surface();
}

void ImageSurface::set_h_res(int new_h_res) {
    delete[] _pixels;
    _h_res = new_h_res;
    _arr_size = _h_res * _v_res;
    _pixels = new vec3[_arr_size];
    _generate_surface();
}

void ImageSurface::set_v_res(int new_v_res) {
    delete[] _pixels;
    _v_res = new_v_res;
    _arr_size = _h_res * _v_res;
    _pixels = new vec3[_arr_size];
    _generate_surface();
}

void ImageSurface::set_transform(const mat4& new_transform) {
    _transform = new_transform;
    _generate_surface();
}

float ImageSurface::fov() const {
    return _fov;
}

int ImageSurface::h_res() const {
    return _h_res;
}

int ImageSurface::v_res() const {
    return _v_res;
}

mat4 ImageSurface::transform() const {
    return _transform;
}

int ImageSurface::pixel_count() const {
    return _arr_size;
}

void ImageSurface::_generate_surface() {
    for (int row = 0; row < _v_res; row++) {
        for (int col = 0; col < _h_res; col++) {
            unsigned int index = (row * _h_res) + col;
            float theta = (static_cast<float>(col) / static_cast<float>(_h_res));
            theta = (theta * _fov) - (_fov / 2.0f);
            float y = (static_cast<float>(row) / static_cast<float>(_v_res));
            y = (y * _height) - (_height / 2.0f);
            vec3 pixel_coord = vec3(0.0f, 0.0f, -_radius);
            pixel_coord = mat3::rot_y(-theta) * pixel_coord;
            pixel_coord = pixel_coord + vec3(0.0f, y, 0.0f);
            _pixels[index] = _transform * pixel_coord;
        }
    }
}

PixelIterator::PixelIterator(vec3* ptr): m_ptr(ptr) {}
const vec3& PixelIterator::operator*() const {
    return *m_ptr;
}
const vec3* PixelIterator::operator->() const {
    return m_ptr;
}

PixelIterator& PixelIterator::operator++() {
    m_ptr++;
    return *this;
}

bool operator== (const PixelIterator& a, const PixelIterator& b) {
    return a.m_ptr == b.m_ptr;
}

bool operator!= (const PixelIterator& a, const PixelIterator& b) {
    return a.m_ptr != b.m_ptr;
}

PixelIterator ImageSurface::begin() const {
    return PixelIterator(&_pixels[0]);
}

PixelIterator ImageSurface::end() const {
    return PixelIterator(&_pixels[_arr_size]);
}
