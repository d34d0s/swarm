#include "../include/swarm.h"

static swarm_mesh_data mesh_data = {0};

swarm_scene swarm_make_scene(char* tag) {
    swarm_scene scene;
    scene.info.tag = (tag != (void*)0) ? tag : "Swarm Scene";

    // initialize and register component data
    swarm_init_mesh_data(&mesh_data);
    swarm_register_component(&scene, SWARM_MESH_COMPONENT, &mesh_data,
        swarm_add_mesh,
        swarm_rem_mesh,
        swarm_get_mesh
    );

    return scene;
}

swarm_entity swarm_make_entity(swarm_scene* scene) {
    if (scene->entity_manager.count + 1 > SWARM_ENTITY_MAX) return SWARM_ENTITY_MAX + 1;
    swarm_entity entity = scene->entity_manager.next++;
    scene->entity_manager.count++;
    scene->entity_manager.alive[entity] = 1;
    return entity;
}

unsigned char swarm_kill_entity(swarm_scene* scene, swarm_entity entity) {
    if (scene->entity_manager.count - 1 < 0) return 1;
    scene->entity_manager.next--;
    scene->entity_manager.count--;
    scene->entity_manager.alive[entity] = 0;
    return 0;
}

unsigned char swarm_register_component(
    swarm_scene* scene,
    swarm_component_type type,
    void* data,
    _add_component_ptr add_component,
    _rem_component_ptr rem_component,
    _get_component_ptr get_component
){
    scene->component_manager.component_register[type].data = data;
    scene->component_manager.component_handler[type].add_component = add_component;
    scene->component_manager.component_handler[type].rem_component = rem_component;
    scene->component_manager.component_handler[type].get_component = get_component;

    return 0;
}

unsigned char swarm_unregister_component(swarm_scene* scene, swarm_component_type type) {
    scene->component_manager.component_register[type].data = (void*)0;
    scene->component_manager.component_handler[type].add_component = (void*)0;
    scene->component_manager.component_handler[type].rem_component = (void*)0;
    scene->component_manager.component_handler[type].get_component = (void*)0;

    return 0;
}
