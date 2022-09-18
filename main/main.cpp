#include "../lib/gen_bmp.h"
#include "../lib/vex3d.h"

#ifdef _DEBUG
    #include <iostream>
    #define cout std::cout

    void print_vec3(const vec3& v, bool newline = true) {
        cout << "(" << v.x << ", " << v.y << ", " << v.z << ") ";
        if (newline) {
            cout << "\n";
        }
    }

    void print_mat3(const mat3& m, bool newline = true) {
        cout << "| " << m[0][0] << ", " << m[0][1] << ", " << m[0][2];
        cout << (newline ? " |\n" : ", ");
        cout << "| " << m[1][0] << ", " << m[1][1] << ", " << m[1][2];
        cout << (newline ? " |\n" : ", ");
        cout << "| " << m[2][0] << ", " << m[2][1] << ", " << m[2][2];
        cout << (newline ? " |\n" : " ");
    }

#else
    #define cout //
    void print_vec3(const vec3& v, bool newline = true) {}
#endif


class Ray {
private:
    vec3 _direction_normalized;
public:
    vec3 origin;
    vec3 direction;

    Ray(const vec3& origin, const vec3& direction) {
        this->origin = origin;
        this->direction = direction;
        this->_direction_normalized = vec3(0);
    }

    vec3 normalized_dir() {
        if (_direction_normalized == vec3(0)) {
            _direction_normalized = _direction_normalized.normalize();
        }
        return _direction_normalized;
    }
};

class Intersection {
public:
    bool valid;
    vec3 normal;
    vec3 color;
    vec3 point;

    Intersection() = default;
    Intersection(const Intersection& other) = default;
    Intersection& operator=(const Intersection& rhs) = default;

    Intersection(vec3 point, vec3 normal, vec3 color) : 
        point(point),
        normal(normal), 
        color(color), 
        valid(true) 
    {}

    static Intersection none() {
        Intersection empty_intersection;
        empty_intersection.valid = false;
        return empty_intersection;
    }
};

class Sphere {
public:
    vec3 origin;
    float radius;
    float radius_sqr;
    vec3 color;

    Sphere() = default;
    Sphere(const Sphere& other) = default;
    Sphere& operator=(const Sphere& rhs) = default;

    Sphere(const vec3& origin, float radius, const vec3& color) {
        this->origin = origin;
        this->radius = radius;
        this->radius_sqr = radius * radius;
        this->color = color;
    }

    Intersection check_intersection(const Ray& ray) const {
        vec3 v = ray.origin - origin;
        float a = ray.direction.dot(ray.direction);
        float b = 2.0f * ray.direction.dot(v);
        float c = v.dot(v) - radius_sqr;
        float disc = (b * b) - (4 * a * c);

        if (disc < 0) { // No collision
            return Intersection::none();
        }

        float disc_sqrt = sqrt(disc);
        float t0 = (-b + disc_sqrt) / (2 * a);
        float t1 = (-b - disc_sqrt) / (2 * a);
        
        if (t0 < 0 && t1 < 0) { // Collision is behind camera
            return Intersection::none();
        }

        float t = 0;
        if (t0 < t1 && t0 >= 0) t = t0;
        else t = t1;

        vec3 intersection_point = ray.origin + (ray.direction * t);
        vec3 normal = intersection_point - origin;
        normal = normal.normalize();
        return Intersection(intersection_point, normal, color);
    }
};

class Scene {
public:
    int _shape_count;
    Sphere* _shapes;
    
    Scene() : _shape_count(0), _shapes(nullptr) {}
    
    void add_sphere(const Sphere& s) {
        Sphere* tmp_shapes = new Sphere[_shape_count + 1];
        for (int i = 0; i < _shape_count; i++) {
            tmp_shapes[i] = _shapes[i];
        }
        delete[] _shapes;
        _shapes = tmp_shapes;
        _shapes[_shape_count] = s;
        _shape_count += 1;
    }

    void add_sphere(const vec3& origin, float radius, const vec3& color) {
        this->add_sphere(Sphere(origin, radius, color));
    }

    ~Scene() {
        delete[] _shapes;
    }

    class Iterator {
    private:
        Sphere* m_ptr;

    public:
        Iterator(Sphere* ptr): m_ptr(ptr) {}
        const Sphere& operator*() const { return *m_ptr; }
        const Sphere* operator->() const { return m_ptr; }

        Iterator& operator++() {
            m_ptr++;
            return *this;
        }

        friend bool operator== (const Iterator& a, const Iterator& b) {
            return a.m_ptr == b.m_ptr;
        }

        friend bool operator!= (const Iterator& a, const Iterator& b) {
            return a.m_ptr != b.m_ptr;
        }
    };

    Iterator begin() const { return Iterator(&_shapes[0]); }
    Iterator end() const { return Iterator(&_shapes[_shape_count]); }
};

class ImageSurface {
private:
    vec3 *_pixels;
    float _fov;
    int _h_res;
    int _v_res;
    int _arr_size = 0;

    const float _radius = 1.0f;
    float _height = _radius * _fov;

public:
    ImageSurface(int h_res, int v_res, float fov):
        _h_res(h_res),
        _v_res(v_res),
        _fov(fov)
    {
        _arr_size = _h_res * _v_res;
        _pixels = new vec3[_arr_size];
        float aspect_ratio = static_cast<float>(_h_res) / static_cast<float>(_v_res);
        _height = _fov / aspect_ratio;
        _generate_surface();
    }

    ~ImageSurface() {
        delete[] _pixels;
    }

    void set_fov(float new_fov) {
        _fov = new_fov;
        _generate_surface();
    }

    void set_h_res(int new_h_res) {
        delete[] _pixels;
        _h_res = new_h_res;
        _arr_size = _h_res * _v_res;
        _pixels = new vec3[_arr_size];
        _generate_surface();
    }

    void set_v_res(int new_v_res) {
        delete[] _pixels;
        _v_res = new_v_res;
        _arr_size = _h_res * _v_res;
        _pixels = new vec3[_arr_size];
        _generate_surface();
    }

    float get_fov() const { return _fov; }
    int get_h_res() const { return _h_res; }
    int get_v_res() const { return _v_res; }
    int get_pixel_count() const { return _arr_size; }

    void _generate_surface() {
        vec3 origin = vec3(0);
        for (int row = 0; row < _v_res; row++) {
            for (int col = 0; col < _h_res; col++) {
                unsigned int index = (row * _h_res) + col;
                float theta = (static_cast<float>(col) / static_cast<float>(_h_res));
                theta = (theta * _fov) - (_fov / 2.0f);
                float y = (static_cast<float>(row) / static_cast<float>(_v_res));
                y = (y * _height) - (_height / 2.0f);
                vec3 focal = vec3(0.0f, 0.0f, -_radius);
                focal = mat3::rot_y(-theta) * focal;
                _pixels[index] = focal + vec3(0.0f, y, 0.0f);
            }
        }
    }

    class PixelIterator {
    private:
        vec3* m_ptr;

    public:
        PixelIterator(vec3* ptr): m_ptr(ptr) {}
        const vec3& operator*() const { return *m_ptr; }
        const vec3* operator->() const { return m_ptr; }

        PixelIterator& operator++() {
            m_ptr++;
            return *this;
        }

        friend bool operator== (const PixelIterator& a, const PixelIterator& b) {
            return a.m_ptr == b.m_ptr;
        }

        friend bool operator!= (const PixelIterator& a, const PixelIterator& b) {
            return a.m_ptr != b.m_ptr;
        }
    };

    PixelIterator begin() const { return PixelIterator(&_pixels[0]); }
    PixelIterator end() const { return PixelIterator(&_pixels[_arr_size]); }
};

class Camera {
private:
    vec3 _pos;
    // TODO: Add orientation
    // vec3 _up;
    float _aspect_ratio;
    float _fov;
    ImageSurface _image_surface;

public:

    Camera(float aspect_ratio, float fov):
        _aspect_ratio(aspect_ratio),
        _fov(fov),
        _image_surface(1080 * aspect_ratio, 1080, fov)
    {}
    
    Camera(float aspect_ratio, float fov, int vertical_resolution):
        _aspect_ratio(aspect_ratio),
        _fov(fov),
        _image_surface(
            vertical_resolution * aspect_ratio, 
            vertical_resolution, 
            fov
        )
    {}

    void set_pos(const vec3& new_pos) { _pos = new_pos; }
    // void look_at(const vec3& target) {}
    // void look_dir(const vec3& direction) {}
    void set_h_res(int new_h_res) { _image_surface.set_h_res(new_h_res); }
    void set_v_res(int new_v_res) { _image_surface.set_v_res(new_v_res); }

    vec3 get_pos() const { return _pos; }
    float apsect_ratio() const { return _aspect_ratio; }
    float fov() const { return _fov; }
    const ImageSurface& image_surface() const { return _image_surface; }

    int get_h_res() const { return _image_surface.get_h_res(); }
    int get_v_res() const { return _image_surface.get_v_res(); }
    int get_pixel_count() const { return _image_surface.get_pixel_count(); }

};

class Raytracer {
private:
    const Scene* _scene;
    const Camera* _camera;
    vec3 _empty_color;
    unsigned char* _framebuffer;

    Intersection* _intersection_pool;
    const int MAX_OBJECTS = 1000;

public:

    Raytracer(const Camera* camera, const Scene* scene) {
        this->_scene = scene;
        this->_camera = camera;
        this->_empty_color = vec3(220, 220, 220);
        this->_intersection_pool = new Intersection[MAX_OBJECTS]; // Will change
        this->_framebuffer = new unsigned char[_camera->get_pixel_count() * 3];
    }

    void set_scene(const Scene* scene) {
        this->_scene = scene;
    }

    void set_empty_color(const vec3& color) {
        this->_empty_color = color;
    }

    unsigned char* trace_scene() {
        int fb_index = 0;
        for (const vec3& pixel : _camera->image_surface()) {
            vec3 color = trace(_camera->get_pos(), pixel - _camera->get_pos());
            _framebuffer[fb_index++] = static_cast<unsigned char>(color.x);
            _framebuffer[fb_index++] = static_cast<unsigned char>(color.y);
            _framebuffer[fb_index++] = static_cast<unsigned char>(color.z);
        }
        return _framebuffer;
    }

    vec3 trace(const vec3& origin, const vec3& direction) {
        int list_tail = 0;
        Ray ray(origin, direction);
        for (const auto& shape : *_scene) {
            Intersection i = shape.check_intersection(ray);
            if (i.valid) _intersection_pool[list_tail++] = i;
        }
        if (list_tail == 0) return _empty_color;
        Intersection& closest_ixn = _intersection_pool[0];
        vec3 init_diff = closest_ixn.point - _camera->get_pos();
        float min_distance_sqr = init_diff.magnitude2();
        for (int i = 1; i < list_tail; i++) {
            Intersection& ixn = _intersection_pool[i];
            vec3 diff = ixn.point - _camera->get_pos();
            float distance_sqr = diff.magnitude2();
            if (distance_sqr < min_distance_sqr) {
                min_distance_sqr = distance_sqr;
                closest_ixn = ixn;
            }
        }
        return closest_ixn.color;
    }
    
    ~Raytracer() {
        delete[] _intersection_pool;
        delete[] _framebuffer;
    }

    // TODO: reflections and stuff
    void set_num_bounces(int n) {}
};


int main(int argc, char **argv) {

    // Scene
    Scene scene;
    scene.add_sphere(
        vec3(0.0f, -100.0f, -102.0f),
        100.0f,
        vec3(50, 50, 50)
    );
    scene.add_sphere(
        vec3(0.0f, 0.0f, -12.0f),
        3.0f,
        vec3(10, 0, 230)
    );
    scene.add_sphere(
        vec3(3.0f, -1.5f, -7.0f),
        0.5f,
        vec3(75, 255, 150)
    );
    scene.add_sphere(
        vec3(-1.75f, 0.5f, -7.0f),
        0.5f,
        vec3(100, 40, 30)
    );

    float aspect_ratio = 16.0f / 9.0f;
    float fov = radians(60.0f);

    // Camera
    Camera camera(16.0f / 9.0f, radians(80.0f), 1080);

    // Raytracer
    Raytracer raytracer(&camera, &scene);
    // raytracer.set_num_bounces(3);

    // Generate image
    const unsigned char* framebuffer = raytracer.trace_scene();
    Bitmap::from_color_array(framebuffer, camera.get_h_res(), camera.get_v_res());
    return 0;
}

