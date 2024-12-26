#include "swarm_mesh.h"

unsigned char swarm_init_mesh_data(swarm_mesh_data* data) {
    data->active = (unsigned char*)malloc(sizeof(unsigned char) * 100);
    if (!data->active) {
        return 1;
    }

    data->vbo = (unsigned int*)malloc(sizeof(unsigned int) * 100);
    if (!data->vbo) {
        free(data->active);
        return 1;
    }

    data->ebo = (unsigned int*)malloc(sizeof(unsigned int) * 100);
    if (!data->ebo) {
        free(data->active);
        free(data->vbo);
        return 1;
    }

    data->vao = (unsigned int*)malloc(sizeof(unsigned int) * 100);
    if (!data->vao) {
        free(data->active);
        free(data->vbo);
        free(data->ebo);
        return 1;
    }

    return 0;
}

void swarm_add_mesh(void* data, swarm_entity entity) {
    if (entity > SWARM_ENTITY_MAX) return 1;
    swarm_mesh_data* mesh_data = (swarm_mesh_data*)data;
    mesh_data->active[entity] = 1;
}

void swarm_rem_mesh(void* data, swarm_entity entity) {
    if (entity > SWARM_ENTITY_MAX) return 1;
    swarm_mesh_data* mesh_data = (swarm_mesh_data*)data;
    mesh_data->active[entity] = 0;
}

swarm_component swarm_get_mesh(void* data, swarm_entity entity) {
    if (entity > SWARM_ENTITY_MAX) return (swarm_component){ .type = -1, .data = (void*)0 };
    swarm_mesh_data* mesh_data = (swarm_mesh_data*)data;
    return (swarm_component){ .type = SWARM_MESH_COMPONENT, .data = &((swarm_mesh_itf){666, 420, 69})};
}
