#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#define LOTUS_ENTITY_MAX ((1U << 16) - 1)
#define LOTUS_COMPONENT_MAX ((1U << 8) - 1)

typedef struct lotus_entity {
    unsigned int id;
} lotus_entity;

typedef struct lotus_component {
    unsigned int type;
    void* interface;
} lotus_component;

typedef void (*_add_component_ptr)(void* component_data, lotus_entity entity);
typedef void (*_rem_component_ptr)(void* component_data, lotus_entity entity);
typedef lotus_component (*_get_component_ptr)(void* component_data);

typedef struct lotus_scene {
    struct info {
        char* tag;
    } info;

    struct state {
        unsigned char running;
    } state;
    
    struct resource {
        struct entity_manager {
            unsigned short next;
            unsigned short count;
            unsigned char alive[LOTUS_ENTITY_MAX];
        } entity_manager;
        
        struct component_register {
            void* component_data;
            unsigned int* active;
            _add_component_ptr add_component;
            _rem_component_ptr rem_component;
            _get_component_ptr get_component;
        } component_register[LOTUS_COMPONENT_MAX];
    } resource;
} lotus_scene;

lotus_entity lotus_entity_create(lotus_scene* scene);
void lotus_entity_destroy(lotus_scene* scene, lotus_entity entity);

void lotus_component_register(lotus_scene* scene, unsigned int type, void* component_data,
    _add_component_ptr add_component,
    _rem_component_ptr rem_component,
    _get_component_ptr get_component
);
void lotus_component_unregister(lotus_scene* scene, unsigned int type);

int main() {

    return 0;
}
