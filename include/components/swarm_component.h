#pragma once

#include "../defines.h"

#include "swarm_mesh.h"
typedef struct swarm_component swarm_component;

#define SWARM_COMPONENT_TYPE(t) t##_COMPONENT
/* user defined components should have IDs <= 255 */
typedef enum swarm_component_type {
    SWARM_COMPONENT_TYPE(SWARM_MESH),
    SWARM_COMPONENT_TYPE(SWARM_TEXTURE),
    SWARM_COMPONENT_TYPE(SWARM_TRANSFORM),
    SWARM_COMPONENT_TYPES,
    SWARM_COMPONENT_MAX = ((1U << 8) - 1)
} swarm_component_type;

typedef union swarm_component_data {
    swarm_mesh_data mesh_data;
} swarm_component_data;

// tagged component union
struct swarm_component {
    swarm_component_data data;
    swarm_component_type type;
};

typedef void (*_add_component_ptr)(void* component_data, swarm_entity entity);
typedef void (*_rem_component_ptr)(void* component_data, swarm_entity entity);
typedef swarm_component (*_get_component_ptr)(void* component_data);

typedef struct swarm_component_handler {
    _add_component_ptr add_component;
    _rem_component_ptr rem_component;
    _get_component_ptr get_component;
} swarm_component_handler;

typedef struct swarm_component_register {
    void* data;
    unsigned char active[SWARM_ENTITY_MAX];
} swarm_component_register;

typedef struct swarm_component_manager {
    swarm_component_handler component_handler[SWARM_COMPONENT_TYPES];
    swarm_component_register component_register[SWARM_COMPONENT_TYPES];
} swarm_component_manager;
