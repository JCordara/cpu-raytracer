#include "scene.h"
#include "sphere.h"

using Iterator = Scene::Iterator;

Scene::Scene() : _entity_count(0), _entities(nullptr) {}

Entity* Scene::add_shape(Entity* s) {
    Entity** tmp_entities = new Entity*[_entity_count + 1];
    for (int i = 0; i < _entity_count; i++) {
        tmp_entities[i] = _entities[i];
    }
    delete[] _entities;
    _entities = tmp_entities;
    _entities[_entity_count] = s;
    _entity_count += 1;
    return s;
}

Scene::~Scene() {
    delete[] _entities;
}

Iterator::Iterator(Entity** ptr): m_ptr(ptr) {}

const Entity& Iterator::operator*() const {
    return **m_ptr;
}

const Entity* Iterator::operator->() const {
    return *m_ptr;
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
    return Iterator(&_entities[0]);
}

Iterator Scene::end() const {
    return Iterator(&_entities[_entity_count]);
}
