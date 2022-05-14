#ifndef PLANE_H
#define PLANE_H

#include "camera.h"
#include "texture.h"
#include <SDL2/SDL.h>

#include <obj/model.h>

typedef struct Rotor {
    Model model;
    vec3 rotation;
    float speed;
    float dynamicSpeed;
} Rotor;

typedef struct Window {
    Model model;
} Window;

typedef struct Plane {
    Model model;
    Rotor rotor;
    Window window;

    vec3 planePosition;
    vec3 planeSpeed;
    vec3 planeRotation;
    float planeRotationSpeed;

    bool stateAcceleration;
    bool stateSlowing;

    GLuint planeTexture;
} Plane;

void init_plane(Plane *plane);

void update_plane(Plane *plane, Camera *camera, double time);

void render_plane(const Plane *plane);

void render_window(const Plane *plane);

void render_rotor(const Plane *plane);

void set_plane_speed_x(Plane *plane, double speed);

void set_plane_speed_y(Plane *plane, double speed);

void set_plane_speed_z(Plane *plane, double speed);

void set_plane_rotation_speed(Plane *plane, double speed);

#endif //PLANE_H
