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
    void print_mat3(const mat3& m, bool newline = true) {}
#endif

#include "scene.h"
#include "shapes.h"
#include "camera.h"
#include "raytracer.h"

int main(int argc, char **argv) {

    // Create scene
    Scene scene;
    scene.add_shape(new Sphere(
        vec3(0.0f, -100.0f, -102.0f),
        100.0f,
        vec3(50, 50, 50)
    ));
    scene.add_shape(new Sphere(
        vec3(0.0f, 0.0f, -12.0f),
        3.0f,
        vec3(10, 0, 230)
    ));
    scene.add_shape(new Sphere(
        vec3(3.0f, -1.5f, -7.0f),
        0.5f,
        vec3(75, 255, 150)
    ));
    scene.add_shape(new Sphere(
        vec3(-1.75f, 0.5f, -7.0f),
        0.5f,
        vec3(100, 40, 30)
    ));

    float aspect_ratio = 16.0f / 9.0f;
    float fov = radians(80.0f);
    int vertical_resolution = 1080;

    // Camera
    Camera camera(aspect_ratio, fov, vertical_resolution);

    // Raytracer
    Raytracer raytracer(&camera, &scene);

    // raytracer.set_num_bounces(3); // Unimplemented

    // Generate image
    const unsigned char* framebuffer = raytracer.trace_scene();
    Bitmap::from_color_array(framebuffer, camera.h_res(), camera.v_res());
    
    return 0;
}

