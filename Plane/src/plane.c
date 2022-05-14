#include "plane.h"

#include <SDL2/SDL.h>
#include <obj/load.h>
#include <obj/draw.h>
#include <math.h>

void init_plane(Plane *plane) {
    load_model(&(plane->model), "assets/models/plane_body.obj");
    plane->planeTexture = load_texture("assets/textures/plane.jpg");

    load_model(&(plane->window.model), "assets/models/window.obj");

    load_model(&(plane->rotor.model), "assets/models/rotor.obj");

    plane->planePosition.x = 0.0;
    plane->planePosition.y = 0.0;
    plane->planePosition.z = 0.0;

    plane->planeSpeed.x = 0.0;
    plane->planeSpeed.y = 0.0;
    plane->planeSpeed.z = 0.0;

    plane->planeRotation.x = 0.0;
    plane->planeRotation.y = 0.0;
    plane->planeRotation.z = 0.0;

    plane->planeRotationSpeed = 0.0;

    plane->rotor.rotation.x = 0.0;

    plane->rotor.speed = 0.0;

    plane->stateAcceleration = false;
    plane->stateSlowing = false;
}

void update_plane(Plane *plane, Camera *camera, double time) {
    //A repülő x-y-z koordinátán történő mozgásának a frissítése
    plane->planePosition.x += plane->planeSpeed.x * time;
    plane->planePosition.y += plane->planeSpeed.y * time;
    plane->planePosition.z += plane->planeSpeed.z * time;

    //A kamera kövesse a repülő mozgását
    camera->position.x += plane->planeSpeed.x * time;
    camera->position.y += plane->planeSpeed.y * time;
    camera->position.z += plane->planeSpeed.z * time;

    //A repülő x-y-z koordinátán történő forgatásának a frissítése
    plane->planeRotation.x += plane->planeRotationSpeed * time;
    plane->planeRotation.y += plane->planeRotationSpeed * time;
    plane->planeRotation.z += plane->planeRotationSpeed * time;


    if (plane->stateAcceleration) {
        plane->rotor.rotation.x += 50;
    } else if (plane->stateSlowing) {
        plane->rotor.rotation.x += 25;
    } else {
        plane->rotor.rotation.x += 30;
    }
}

void render_plane(const Plane *plane) {
    /* Repülő renderelése
    * Külső push-pop mátrixban megadva, hogy a repülő egyes részei milyen irányokat (glTranslatef)
    * és forgást (glRotatef) kövessenek egységesen.
    * A belső push-pop mátrixokban a repülő egyes részei renderelődnek le.*/
    glPushMatrix();
    glTranslatef(plane->planePosition.x, plane->planePosition.y, plane->planePosition.z);
    glRotatef(plane->planeRotation.x, 1, 0, 0);
    glTranslatef(-plane->planePosition.x, -plane->planePosition.y, -plane->planePosition.z);

    glPushMatrix();
    glTranslatef(plane->planePosition.x, plane->planePosition.y, plane->planePosition.z);
    glBindTexture(GL_TEXTURE_2D, plane->planeTexture);
    draw_model(&(plane->model));
    glPopMatrix();

    render_rotor(plane);

    //A repülő ablakának átlátszóságának beállítása
    render_window(plane);
    glPopMatrix();
}

void render_window(const Plane *plane) {
    glPushMatrix();
    glEnable(GL_BLEND);
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA + 4, GL_ONE_MINUS_SRC_ALPHA - 3);
    glTranslatef(plane->planePosition.x, plane->planePosition.y, plane->planePosition.z);
    draw_model(&(plane->window.model));
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glPopMatrix();
}

void render_rotor(const Plane *plane) {
    glPushMatrix();
    glTranslatef(plane->planePosition.x + 2.2, plane->planePosition.y, plane->planePosition.z);
    glRotatef(plane->rotor.rotation.x, 1, 0, 0);
    glBindTexture(GL_TEXTURE_2D, plane->planeTexture);
    draw_model(&(plane->rotor.model));
    glPopMatrix();
}

void set_plane_speed_x(Plane *plane, double speed) {
    plane->planeSpeed.x = speed;
}

void set_plane_speed_y(Plane *plane, double speed) {
    plane->planeSpeed.y = speed;
}

void set_plane_speed_z(Plane *plane, double speed) {
    plane->planeSpeed.z = speed;
}

void set_plane_rotation_speed(Plane *plane, double speed) {
    plane->planeRotationSpeed = speed;
}
