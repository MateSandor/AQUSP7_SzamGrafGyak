#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include <SDL2/SDL.h>

#include <obj/model.h>

typedef struct Checkpoint{
    vec3 position;
    GLuint texture;
    double front;
    double back;
} Checkpoint;


typedef struct Scene
{
    Model plane;
    Model rotor;
    Model window;
    Model checkpointModel;
    Model mountain;

    Checkpoint checkpoint[12];

    vec3 planePosition;
    vec3 planeSpeed;
    vec3 planeRotation;
    float planeRotationSpeed;
    vec3 rotorRotation;
    float rotorSpeed;

    float diffuse[4];
    float brightness;

    Material material;

    GLuint planeTexture;
    GLuint skyTexture;
    GLuint mountainTexture;
    GLuint controlTexture;

    bool controlOn;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting(Scene *scene);

void set_lighting2(Scene *scene);

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene, Camera *camera, double time);

/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

void loadSkybox(Scene scene);

void set_plane_speed_x(Scene *scene, double speed);

void set_plane_speed_y(Scene *scene, double speed);

void set_plane_speed_z(Scene *scene, double speed);

void set_plane_rotation_speed(Scene *scene, double speed);

void loadControl(GLuint control);

void setControlState(Scene *scene, bool state);

void setBrightness(Scene *scene, double brightness);

#endif /* SCENE_H */
