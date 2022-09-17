#include "../lib/gen_bmp.h"
#include "../lib/vec3f.h"
#include <math.h>

#ifdef _DEBUG
    #include <iostream>
    #define cout std::cout
#else
    #define cout //
#endif

#define PI 3.14159f

void print_vec3(vec3 v, bool newline = true) {
    cout << "(" << v.x << ", " << v.y << ", " << v.z << ") ";
    if (newline) {
        cout << "\n";
    }
}

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

    Intersection check_intersection(const Ray& ray) {
        vec3 v = ray.origin - origin;
        float a = ray.direction.dot(ray.direction);
        float b = 2.0f * ray.direction.dot(v);
        float c = v.dot(v) - radius_sqr;
        float disc = (b * b) - (4 * a * c);
        
        print_vec3(ray.origin, false);
        cout << ", ";
        print_vec3(origin);

        //cout << disc << "\n";
        
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
    int shape_count;
    Sphere* shapes;
    
    Scene() : shape_count(0), shapes(nullptr) {}
    
    void add_sphere(const Sphere& s) {
        Sphere* tmp_shapes = new Sphere[shape_count + 1];
        for (int i = 0; i < shape_count; i++) {
            tmp_shapes[i] = shapes[i];
        }
        delete[] shapes;
        shapes = tmp_shapes;
        shape_count += 1;
    }

    void add_sphere(const vec3& origin, float radius, const vec3& color) {
        this->add_sphere(Sphere(origin, radius, color));
    }

    ~Scene() {
        delete[] shapes;
    }

    Sphere* begin() {return shapes;}
    Sphere* end() {return shapes + shape_count;}
};

class Canvas {
private:
    vec3 *pixels;
    float width;
    float height;
    int _h_res;
    int _v_res;
    int arr_size = 0;

public:
    Canvas(
        float width, float height,
        int _h_res, int _v_res,
        const vec3& origin) 
    {
        // Initialize canvas as grid of pixel coordinates in 3D space
        arr_size = _h_res * _v_res;
        pixels = new vec3[arr_size];

        float half_width = width / 2.0f;
        float half_height = height / 2.0f;
        vec3 canvas_normal = vec3(0, 0, 1);

        for (int row = 0; row < _v_res; row++) {
            for (int col = 0; col < _h_res; col++) {
                unsigned int index = (row * _h_res) + col;
                float x = (static_cast<float>(col) / static_cast<float>(_h_res));
                x = (x * width) - half_width;
                float y = (static_cast<float>(row) / static_cast<float>(_v_res));
                y = (y * height) - half_height;
                pixels[index] = origin + vec3(x, y, 0.0f);
            }
        }
    }

    ~Canvas() {
        delete[] pixels;
    }

    int get_h_res() {return _h_res;}
    int get_v_res() {return _v_res;}
    int pixel_count() {return arr_size;}

    vec3* begin() {return pixels;}
    vec3* end() {return pixels + arr_size;}
};

class Raytracer {
private:
    Scene* _scene;
    vec3 _empty_color;
    vec3 _camera_pos;
    Canvas* _canvas;
    unsigned char* _framebuffer;

    Intersection* _intersection_pool;
    const int MAX_OBJECTS = 1000;

public:

    Raytracer(const vec3& camera, Canvas& canvas) {
        this->_scene = nullptr;
        this->_camera_pos = camera;
        this->_canvas = &canvas;
        this->_empty_color = vec3(220, 220, 220);
        this->_intersection_pool = new Intersection[MAX_OBJECTS]; // Will change
        this->_framebuffer = new unsigned char[_canvas->pixel_count() * 3];
    }

    void set_scene(Scene& scene) {
        _scene = &scene;
    }

    void set_empty_color(const vec3& color) {
        _empty_color = color;
    }

    unsigned char* trace_scene() {
        int fb_index = 0;
        for (vec3& pixel : *_canvas) {
            vec3 color = trace(_camera_pos, pixel - _camera_pos);
            _framebuffer[fb_index++] = static_cast<unsigned char>(color.x);
            _framebuffer[fb_index++] = static_cast<unsigned char>(color.y);
            _framebuffer[fb_index++] = static_cast<unsigned char>(color.z);
        }
        return _framebuffer;
    }

    vec3 trace(const vec3& origin, const vec3& direction) {
        int list_tail = 0;
        Ray ray(origin, direction);
        cout << "Casting ray:\n";
        for (Sphere& shape : *_scene) {
            cout << "Sphere origin: ";
            print_vec3(shape.origin);
            Intersection i = shape.check_intersection(ray);
            cout << (i.valid ? "valid  " : "invalid"); 
            cout << " - color: ";
            print_vec3(i.color, false);
            cout << ", point: ";
            print_vec3(i.point);
            // TODO: Ordered insertion
            if (i.valid) _intersection_pool[list_tail++] = i;
        }
        cout << "Ray intersections: " << list_tail << "\n";
        // Return just the color of the first sphere for now
        if (list_tail == 0) return _empty_color;
        Intersection& closest_ixn = _intersection_pool[0];
        vec3 init_diff = closest_ixn.point - _camera_pos;
        float min_distance_sqr = init_diff.magnitude2();
        for (int i = 1; i < list_tail; i++) {
            Intersection& ixn = _intersection_pool[i];
            vec3 diff = ixn.point - _camera_pos;
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
    
    int h_res = 19;//1920;
    int v_res = 11;//1080;

    float canvas_width = 3.556f;
    float canvas_height = 2.0f;

    vec3 camera_pos = vec3(0);
    Canvas canvas(canvas_width, canvas_height, h_res, v_res, vec3(0, 0, -1));
    Raytracer raytracer(camera_pos, canvas);
    // raytracer.set_num_bounces(3);

    Scene scene;
    scene.add_sphere(
        vec3(0.0f, 1000.0f, -10.0f),
        0.1f,
        vec3(0, 0, 255)
    );
    // scene.add_sphere(
    //     vec3(1.0f, -1.5f, -12.0f),
    //     2.0f,
    //     vec3(100, 255, 200)
    // );
    // scene.add_sphere(
    //     vec3(-4.0f, 3.0f, -4.0f),
    //     0.75f,
    //     vec3(120, 60, 50)
    // );

    raytracer.set_scene(scene);

// cout << "start\n";
//     const unsigned char* framebuffer = raytracer.trace_scene();
// cout << "end\n";

    raytracer.trace(vec3(), vec3(0, 0, -1));

    // Bitmap::from_color_array(framebuffer, h_res, v_res);

    return 0;
}

