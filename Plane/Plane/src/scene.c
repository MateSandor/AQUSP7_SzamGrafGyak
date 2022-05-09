#include "scene.h"

#include <SDL2/SDL.h>
#include <obj/load.h>
#include <obj/draw.h>
#include <math.h>

void init_scene(Scene* scene)
{
    //Modellek - textúrák betöltése
    load_model(&(scene->plane), "assets/models/plane_body.obj");
    scene->planeTexture = load_texture("assets/textures/plane.jpg");

    load_model(&(scene->window), "assets/models/window.obj");

    load_model(&(scene->rotor), "assets/models/rotor.obj");

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

    scene->planePosition.x = 0.0;
    scene->planePosition.y = 0.0;
    scene->planePosition.z = 0.0;

    scene->planeSpeed.x = 0.0;
    scene->planeSpeed.y = 0.0;
    scene->planeSpeed.z = 0.0;

    scene->planeRotation.x = 0.0;
    scene->planeRotation.y = 0.0;
    scene->planeRotation.z = 0.0;

    scene->planeRotationSpeed = 0.0;

    scene->rotorRotation.x = 0.0;

    scene->rotorSpeed = 0.0;

    scene->controlOn = false;

    scene->diffuse[0] = 1.0f;
    scene->diffuse[1] = 1.0f;
    scene->diffuse[2] = 1.0f;
    scene->diffuse[3] = 1.0f;

    scene->brightness = 0.0f;
}

void set_lighting(Scene *scene)
{
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

void set_lighting2(Scene *scene)
{
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

void set_material(const Material* material)
{
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

void update_scene(Scene* scene, Camera *camera, double time) {
    //A repülő x-y-z koordinátán történő mozgásának a frissítése
    scene->planePosition.x += scene->planeSpeed.x * time;
    scene->planePosition.y += scene->planeSpeed.y * time;
    scene->planePosition.z += scene->planeSpeed.z * time;

    //A kamera kövesse a repülő mozgását
    camera->position.x += scene->planeSpeed.x * time;
    camera->position.y += scene->planeSpeed.y * time;
    camera->position.z += scene->planeSpeed.z * time;

    //A repülő x-y-z koordinátán történő forgatásának a frissítése
    scene->planeRotation.x += scene->planeRotationSpeed * time;
    scene->planeRotation.y += scene->planeRotationSpeed * time;
    scene->planeRotation.z += scene->planeRotationSpeed * time;

    scene->rotorRotation.x += 50;

    //Diffúz fények állítása
    scene->diffuse[0] += scene->brightness * time;
    scene->diffuse[1] += scene->brightness * time;
    scene->diffuse[2] += scene->brightness * time;
    scene->diffuse[3] += scene->brightness * time;

    //Checkpointok ütközésvizsgálata
    //Amikor hozzáérünk egy checkpointhoz az adott intervallumban, akkor 100 egységgel feljebb kerül
    for(int i=0; i<12; i++){
        if(scene->checkpoint[i].position.y + 10 >= scene->planePosition.y && scene->planePosition.y + 6 >= scene->checkpoint[i].position.y
        && scene->checkpoint[i].position.x + 3 >= scene->planePosition.x && scene->planePosition.x + 10 >= scene->checkpoint[i].position.x){
            scene->checkpoint[i].position.z += 100 * time;
        }
    }

    //Amikor elértünk az utolsó checkpoint vonalába, akkor újraindul a játék
    if(scene->planePosition.x >= scene->checkpoint[11].position.x){
        scene->planePosition.x = 0.0f;
        scene->planePosition.y = 0.0f;
        scene->planePosition.z = 0.0f;
        scene->planeSpeed.x = 0.0f;
        camera->position.x = -5.0;
        camera->position.y = 0.0;
        camera->position.z = 2.0;
        for(int i=0; i<12; i++){
            scene->checkpoint[i].position.z = 0.0;
        }
    }
}

void render_scene(const Scene* scene)
{
    //Fények és anyag renderelése
    set_material(&(scene->material));
    set_lighting(scene);
    //set_lighting2(scene);

    //Hegy renderelése
    //Kellett egyet scale-elni, hogy nagyobb legyen, mert a Blender valamiért elsötétítette az egész képet
    glPushMatrix();
    glScalef(30.0f, 30.0f, 10.0f);
    glTranslatef(0, 0, -300);
    glBindTexture(GL_TEXTURE_2D, scene->mountainTexture);
    draw_model(&(scene->mountain));
    glPopMatrix();

    //Skybox renderelése
    glPushMatrix();
	glRotatef(180,0,0,1);
    glBindTexture(GL_TEXTURE_2D, scene->skyTexture);
    loadSkybox(*scene);
    glPopMatrix();

    /* Repülő renderelése
     * Külső push-pop mátrixban megadva, hogy a repülő egyes részei milyen irányokat (glTranslatef)
     * és forgást (glRotatef) kövessenek egységesen.
     * A belső push-pop mátrixokban a repülő egyes részei renderelődnek le.*/
    glPushMatrix();
    glTranslatef(scene->planePosition.x, scene->planePosition.y, scene->planePosition.z);
    glRotatef(scene->planeRotation.x, 1, 0, 0);
    glTranslatef(-scene->planePosition.x, -scene->planePosition.y, -scene->planePosition.z);

    glPushMatrix();
    glTranslatef(scene->planePosition.x, scene->planePosition.y, scene->planePosition.z);
    glBindTexture(GL_TEXTURE_2D, scene->planeTexture);
    draw_model(&(scene->plane));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(scene->planePosition.x+2.2, scene->planePosition.y, scene->planePosition.z);
    glRotatef(scene->rotorRotation.x, 1, 0, 0);
    glBindTexture(GL_TEXTURE_2D, scene->planeTexture);
    draw_model(&(scene->rotor));
    glPopMatrix();

    //A repülő ablakának átlátszóságának beállítása
    glPushMatrix();
    glEnable(GL_BLEND);
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA+4, GL_ONE_MINUS_SRC_ALPHA-3);
    glTranslatef(scene->planePosition.x, scene->planePosition.y, scene->planePosition.z);
    draw_model(&(scene->window));
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glPopMatrix();
    glPopMatrix();

    //Checkpointok renderelése
    renderCheckpoint(scene);

    //Control képernyőre rajzolása állapottól függően
    if(scene->controlOn){
        loadControl(scene->controlTexture);
    }
}

void renderCheckpoint(const Scene *scene) {
    //Azért vannak 90 fokkal rotate-elve, mert alapból nem szemben lennének
    for (int i = 0; i < 12; i++) {
        glPushMatrix();
        glTranslatef(scene->checkpoint[i].position.x, scene->checkpoint[i].position.y, scene->checkpoint[i].position.z);
        glRotatef(90, 0, 0, 1);
        glBindTexture(GL_TEXTURE_2D, scene->checkpoint[i].texture);
        draw_model(&(scene->checkpointModel));
        glPopMatrix();
    }
}

void draw_origin()
{
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
    radius = 10000;

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

void set_plane_speed_x(Scene *scene, double speed){
    scene->planeSpeed.x = speed;
}

void set_plane_speed_y(Scene *scene, double speed){
    scene->planeSpeed.y = speed;
}

void set_plane_speed_z(Scene *scene, double speed){
    scene->planeSpeed.z = speed;
}

void set_plane_rotation_speed(Scene *scene, double speed){
    scene->planeRotationSpeed = speed;
}

void loadControl(GLuint control) {
    //glDisable(GL_CULL_FACE);
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
    //glEnable(GL_CULL_FACE);
}

void setControlState(Scene *scene, bool state){
    scene->controlOn = state;
}

void setBrightness(Scene *scene, double brightness){
    scene->brightness = brightness;
}
