#pragma once

#include "swarm_component.h"

typedef struct swarm_mesh_itf {
    unsigned int vbo;
    unsigned int ebo;
    unsigned int vao;
} swarm_mesh_itf;

typedef struct swarm_mesh_data {
    unsigned int* vbo;
    unsigned int* ebo;
    unsigned int* vao;
    unsigned char* active;
} swarm_mesh_data;

unsigned char swarm_init_mesh_data(swarm_mesh_data* data);

void swarm_add_mesh(void* data, swarm_entity entity);
void swarm_rem_mesh(void* data, swarm_entity entity);
swarm_component swarm_get_mesh(void* data, swarm_entity entity);
