#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "plane.h"
#include "texture.h"
#include <SDL2/SDL.h>

#include <obj/model.h>

typedef struct Checkpoint {
    vec3 position;
    vec3 rotation;
    GLuint texture;
    double front;
    double back;
    bool collided;
} Checkpoint;


typedef struct Scene {
    Plane plane;
    Model checkpointModel;
    Model mountain;

    Checkpoint checkpoint[12];

    float diffuse[4];
    float brightness;

    Material material;

    GLuint mountainTexture;
    GLuint controlTexture;
    GLuint skyTexture;

    bool controlOn;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene *scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting(Scene *scene);

void set_lighting2(Scene *scene);

/**
 * Set the current material.
 */
void set_material(const Material *material);

/**
 * Update the scene.
 */
void update_scene(Scene *scene, Plane *plane, Camera *camera, double time);

/**
 * Render the scene objects.
 */
void render_scene(const Scene *scene);

void renderMountain(const Scene *scene);

void renderSkybox(const Scene *scene);

void renderCheckpoint(const Scene *scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

void loadSkybox(Scene scene);

void loadControl(GLuint control);

void setControlState(Scene *scene, bool state);

void setBrightness(Scene *scene, double brightness);

#endif /* SCENE_H */
