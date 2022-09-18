#include "scene.h"
#include "sphere.h"

using Iterator = Scene::Iterator;

Scene::Scene() : _shape_count(0), _shapes(nullptr) {}

void Scene::add_sphere(const Sphere& s) {
    Sphere* tmp_shapes = new Sphere[_shape_count + 1];
    for (int i = 0; i < _shape_count; i++) {
        tmp_shapes[i] = _shapes[i];
    }
    delete[] _shapes;
    _shapes = tmp_shapes;
    _shapes[_shape_count] = s;
    _shape_count += 1;
}

void Scene::add_sphere(const vec3& origin, float radius, const vec3& color) {
    this->add_sphere(Sphere(origin, radius, color));
}

Scene::~Scene() {
    delete[] _shapes;
}

Iterator::Iterator(Sphere* ptr): m_ptr(ptr) {}
const Sphere& Iterator::operator*() const {
    return *m_ptr;
}

const Sphere* Iterator::operator->() const {
    return m_ptr;
}

Iterator& Iterator::operator++() {
    m_ptr++;
    return *this;
}

bool operator== (const Iterator& a, const Iterator& b) {
    return a.m_ptr == b.m_ptr;
}

bool operator!= (const Iterator& a, const Iterator& b) {
    return a.m_ptr != b.m_ptr;
}

Iterator Scene::begin() const {
    return Iterator(&_shapes[0]);
}

Iterator Scene::end() const {
    return Iterator(&_shapes[_shape_count]);
}
