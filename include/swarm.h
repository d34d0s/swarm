#pragma once

#define SWARM_ENTITY_MAX ((1U << 16) - 1)

typedef unsigned int swarm_entity;
typedef struct swarm_component swarm_component;
typedef struct swarm_scene swarm_scene;

typedef void (*_add_component_ptr)(swarm_scene* scene);
typedef void (*_rem_component_ptr)(swarm_scene* scene);
typedef void (*_set_component_ptr)(swarm_scene* scene);
typedef swarm_component (*_get_component_ptr)(swarm_scene* scene);

/* COMPONENT-DATA STRUCTURES */
typedef struct swarm_mesh_component {
    unsigned char active[SWARM_ENTITY_MAX];
} swarm_mesh_component;

typedef struct swarm_texture_component {
    unsigned char active[SWARM_ENTITY_MAX];
} swarm_texture_component;

typedef struct swarm_transform_component {
    unsigned char active[SWARM_ENTITY_MAX];
} swarm_transform_component;

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
    swarm_mesh_component mesh_component;
    swarm_texture_component texture_component;
    swarm_transform_component transform_component;
} swarm_component_data;

// tagged component union
struct swarm_component {
    swarm_component_data data;
    swarm_component_type type;
};

typedef struct swarm_component_handler {
    _add_component_ptr add_component;
    _rem_component_ptr rem_component;
    _set_component_ptr set_component;
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

typedef struct swarm_entity_manager {
    unsigned short next;
    unsigned short count;
    unsigned char alive[SWARM_ENTITY_MAX];
} swarm_entity_manager;

typedef struct swarm_scene_info {
    char* tag;
} swarm_scene_info;

struct swarm_scene {
    swarm_scene_info info;
    swarm_entity_manager entity_manager;
    swarm_component_manager component_manager;
};

swarm_entity swarm_make_entity(swarm_scene* scene);
unsigned char swarm_kill_entity(swarm_scene* scene, swarm_entity entity);

unsigned char swarm_register_component(
    swarm_scene* scene,
    swarm_component_type type,
    void* data,
    _add_component_ptr add_component,
    _rem_component_ptr rem_component,
    _set_component_ptr set_component,
    _get_component_ptr get_component
);
unsigned char swarm_unregister_component(swarm_scene* scene, swarm_component_type type);
