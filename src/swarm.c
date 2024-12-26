#include <swarm.h>

swarm_entity swarm_make_entity(swarm_scene* scene) {
    if (scene->entity_manager.count + 1 > SWARM_ENTITY_MAX) return SWARM_ENTITY_MAX + 1;
    swarm_entity entity = scene->entity_manager.next++;
    scene->entity_manager.count++;
    scene->entity_manager.alive[entity] = 1;
    return entity;
}

unsigned char swarm_kill_entity(swarm_scene* scene, swarm_entity entity) {
    if (scene->entity_manager.count - 1 < 0) return SWARM_ENTITY_MAX + 1;
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
    _set_component_ptr set_component,
    _get_component_ptr get_component
){
    scene->component_manager.component_register[type].data = data;
    scene->component_manager.component_handler[type].add_component = add_component;
    scene->component_manager.component_handler[type].rem_component = rem_component;
    scene->component_manager.component_handler[type].get_component = get_component;
    scene->component_manager.component_handler[type].set_component = set_component;

    return 0;
}

unsigned char swarm_unregister_component(swarm_scene* scene, swarm_component_type type) {
    scene->component_manager.component_register[type].data = (void*)0;
    scene->component_manager.component_handler[type].add_component = (void*)0;
    scene->component_manager.component_handler[type].rem_component = (void*)0;
    scene->component_manager.component_handler[type].get_component = (void*)0;
    scene->component_manager.component_handler[type].set_component = (void*)0;

    return 0;
}
