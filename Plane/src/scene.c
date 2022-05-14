#include "scene.h"

#include <SDL2/SDL.h>
#include <obj/load.h>
#include <obj/draw.h>
#include <math.h>

void init_scene(Scene *scene) {
    //Modellek - textúrák betöltése
    scene->skyTexture = load_texture("assets/textures/sky.jpg");

    load_model(&(scene->checkpointModel), "assets/models/checkpoint.obj");

    load_model(&(scene->mountain), "assets/models/mountain2.obj");
    scene->mountainTexture = load_texture("assets/textures/mountain.jpg");

    scene->controlTexture = load_texture("assets/textures/control.jpg");

    //Random távolságban kerülnek elhelyezésre minden programindításkor a checkpointok
    float currentPosition = 150;
    for (int i = 0; i < 12; i++) {
        scene->checkpoint[i].texture = load_texture("assets/textures/mountain.jpg");
        scene->checkpoint[i].position.x = currentPosition;
        currentPosition = scene->checkpoint[i].position.x + (rand() % (100 + 1 - 50) + 50);
        scene->checkpoint[i].position.y = rand() % 50 - 20;
        scene->checkpoint[i].position.z = 0.0;
        scene->checkpoint[i].rotation.z = 0.0;
        scene->checkpoint[i].collided = false;
    }

    //Inicializációs értékek
    scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;

    scene->controlOn = false;

    scene->diffuse[0] = 1.0f;
    scene->diffuse[1] = 1.0f;
    scene->diffuse[2] = 1.0f;
    scene->diffuse[3] = 1.0f;

    scene->brightness = 0.0f;
}

void set_lighting(Scene *scene) {
    //Elsődleges fényforrás
    float ambient_light[] = {0.0f, 0.0f, 0.0f, 1.0};
    float diffuse_light[] = {scene->diffuse[0], scene->diffuse[1], scene->diffuse[2], 1.0f};
    float specular_light[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float position[] = {0.0f, 0.0f, 50.0f, 0.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_lighting2(Scene *scene) {
    //Másodlagos fényforrás, jelen pillanatban kikapcsolva, tesztelgetve volt
    glEnable(GL_LIGHT1);
    //float ambient_light[] = {1.5f, 1.5f, 1.5f, 1.0};
    float diffuse_light[] = {1.0f, 1.0f, 1.0f, 1.0f};
    //float specular_light[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float position[] = {1000.0f, 0.0f, -100.0f, 1.0f};

    //glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_light);
    //glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT1, GL_POSITION, position);
}

void set_material(const Material *material) {
    float ambient_material_color[] = {
            material->ambient.red,
            material->ambient.green,
            material->ambient.blue
    };

    float diffuse_material_color[] = {
            material->diffuse.red,
            material->diffuse.green,
            material->diffuse.blue
    };

    float specular_material_color[] = {
            material->specular.red,
            material->specular.green,
            material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene *scene, Plane *plane, Camera *camera, double time) {
    //Diffúz fények állítása
    scene->diffuse[0] += scene->brightness * time;
    scene->diffuse[1] += scene->brightness * time;
    scene->diffuse[2] += scene->brightness * time;
    scene->diffuse[3] += scene->brightness * time;

    //Checkpointok ütközésvizsgálata
    //Amikor hozzáérünk egy checkpointhoz az adott intervallumban, akkor 100 egységgel feljebb kerül
    for (int i = 0; i < 12; i++) {
        if (scene->checkpoint[i].position.y + 10 >= plane->planePosition.y &&
            plane->planePosition.y + 6 >= scene->checkpoint[i].position.y
            && scene->checkpoint[i].position.x + 3 >= plane->planePosition.x &&
            plane->planePosition.x + 10 >= scene->checkpoint[i].position.x) {
            scene->checkpoint[i].position.z += 100 * time;
            scene->checkpoint[i].collided = true;
        }
    }

    for (int i = 0; i < 12; i++) {
        if (scene->checkpoint[i].collided) {
            scene->checkpoint[i].rotation.z += 20;
        }
    }

    //Amikor elértünk az utolsó checkpoint vonalába, akkor újraindul a játék
    if (plane->planePosition.x >= scene->checkpoint[11].position.x) {
        plane->planePosition.x = 0.0f;
        plane->planePosition.y = 0.0f;
        plane->planePosition.z = 0.0f;
        plane->planeSpeed.x = 0.0f;
        camera->position.x = -7.5;
        camera->position.y = 0.0;
        camera->position.z = 2.0;
        for (int i = 0; i < 12; i++) {
            scene->checkpoint[i].position.z = 0.0;
            scene->checkpoint[i].rotation.z = 0.0;
            scene->checkpoint[i].collided = false;
        }
    }
}

void render_scene(const Scene *scene) {

    //Fények és anyag renderelése
    set_material(&(scene->material));
    set_lighting(scene);
    //set_lighting2(scene);

    //Hegy renderelése
    //Kellett egyet scale-elni, hogy nagyobb legyen, mert a Blender valamiért elsötétítette az egész képet
    renderMountain(scene);

    //Skybox renderelése
    renderSkybox(scene);

    //Checkpointok renderelése
    renderCheckpoint(scene);

    //Control képernyőre rajzolása állapottól függően
    if (scene->controlOn) {
        loadControl(scene->controlTexture);
    }
}

void renderMountain(const Scene *scene) {
    glPushMatrix();
    glScalef(30.0f, 30.0f, 10.0f);
    glTranslatef(0, 0, -300);
    glBindTexture(GL_TEXTURE_2D, scene->mountainTexture);
    draw_model(&(scene->mountain));
    glPopMatrix();
}

void renderSkybox(const Scene *scene) {
    glPushMatrix();
    glRotatef(180, 0, 0, 1);
    glBindTexture(GL_TEXTURE_2D, scene->skyTexture);
    loadSkybox(*scene);
    glPopMatrix();
}

void renderCheckpoint(const Scene *scene) {
    //Azért vannak 90 fokkal rotate-elve, mert alapból nem szemben lennének
    for (int i = 0; i < 12; i++) {
        glPushMatrix();
        glEnable(GL_BLEND);
        glDepthMask(GL_FALSE);
        glBlendFunc(GL_SRC_ALPHA + 1, GL_ONE_MINUS_SRC_ALPHA);
        glTranslatef(scene->checkpoint[i].position.x, scene->checkpoint[i].position.y, scene->checkpoint[i].position.z);
        glRotatef(90, 0, 0, 1);
        glRotatef(scene->checkpoint[i].rotation.z, 0, 0, 1);
        //glBindTexture(GL_TEXTURE_2D, scene->checkpoint[i].texture);
        draw_model(&(scene->checkpointModel));
        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);
        glPopMatrix();
    }
}

void draw_origin() {
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

void loadSkybox(Scene scene) {
    double theta, phi1, phi2;
    double x1, y1, z1;
    double x2, y2, z2;
    double u, v1, v2;
    int n_slices, n_stacks;
    double radius;
    int i, k;
    n_slices = 60;
    n_stacks = 60;
    radius = 5000;

    glPushMatrix();

    glScaled(radius, radius, radius);

    glColor3f(1, 1, 1);

    glBegin(GL_TRIANGLE_STRIP);

    for (i = 0; i < n_stacks; ++i) {
        v1 = (double) i / n_stacks;
        v2 = (double) (i + 1) / n_stacks;
        phi1 = v1 * M_PI / 2.0;
        phi2 = v2 * M_PI / 2.0;
        for (k = 0; k <= n_slices; ++k) {
            u = (double) k / n_slices;
            theta = u * 2.0 * M_PI;
            x1 = cos(theta) * cos(phi1);
            y1 = sin(theta) * cos(phi1);
            z1 = sin(phi1) - 0.25;
            x2 = cos(theta) * cos(phi2);
            y2 = sin(theta) * cos(phi2);
            z2 = sin(phi2) - 0.25;
            glTexCoord2d(u, 1.0 - v1);
            glVertex3d(x1, y1, z1);
            glTexCoord2d(u, 1.0 - v2);
            glVertex3d(x2, y2, z2);
        }
    }

    glEnd();

    glPopMatrix();
}

void loadControl(GLuint control) {
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, control);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(-4, 3, -5);

    glTexCoord2f(1, 0);
    glVertex3d(4, 3, -5);

    glTexCoord2f(1, 1);
    glVertex3d(4, -3, -5);

    glTexCoord2f(0, 1);
    glVertex3d(-4, -3, -5);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void setControlState(Scene *scene, bool state) {
    scene->controlOn = state;
}

void setBrightness(Scene *scene, double brightness) {
    scene->brightness = brightness;
}
