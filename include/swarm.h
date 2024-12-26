#pragma once

#include "defines.h"

#include "components/swarm_component.h"

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

swarm_scene swarm_make_scene(char* tag);

swarm_entity swarm_make_entity(swarm_scene* scene);
unsigned char swarm_kill_entity(swarm_scene* scene, swarm_entity entity);

unsigned char swarm_register_component(
    swarm_scene* scene,
    swarm_component_type type,
    void* data,
    _add_component_ptr add_component,
    _rem_component_ptr rem_component,
    _get_component_ptr get_component
);
unsigned char swarm_unregister_component(swarm_scene* scene, swarm_component_type type);
