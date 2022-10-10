/**
 * Program entry point.
 * Currently defines a demo scene and generates a bitmap image. 
 */

#include "debug.h"

#include "scene.h"
#include "shapes.h"
#include "camera.h"
#include "raytracer.h"

#include "../lib/gen_bmp.h"
#include "../lib/vex3d.h"


int main(int argc, char **argv) {
    // Create scene
    Scene scene;
    scene.add_shape(new Sphere(
        vec3(0.0f, -90.0f, -60.0f),
        100.0f,
        vec3(50, 50, 50)
    ));
    scene.add_shape(new Sphere(
        vec3(0.0f, 0.0f, -12.0f),
        3.0f,
        vec3(10, 0, 230)
    ));
    scene.add_shape(new Sphere(
        vec3(3.0f, -1.0f, -9.0f),
        0.5f,
        vec3(75, 255, 150)
    ));
    scene.add_shape(new Sphere(
        vec3(-2.5f, 1.5f, -10.0f),
        1.0f,
        vec3(100, 40, 30)
    ));
    
    float aspect_ratio = 16.0f / 9.0f;
    float fov = radians(80.0f);
    int vertical_resolution = 1080;

    // Camera
    Camera camera(aspect_ratio, fov, vertical_resolution);
    camera.set_pos(vec3(0.0f, -0.75f, 3.0f));

    // Raytracer
    Raytracer raytracer(&camera, &scene);
    raytracer.set_num_bounces(4);

    // Generate image
    const unsigned char* framebuffer = raytracer.trace_scene();
    Bitmap::from_color_array(framebuffer, camera.h_res(), camera.v_res());

    return 0;
}

