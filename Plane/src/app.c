#include "app.h"

#include <SDL2/SDL_image.h>

void init_app(App *app, int width, int height) {
    int error_code;
    int inited_loaders;

    app->is_running = false;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0) {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return;
    }

    app->window = SDL_CreateWindow(
            "Plane!",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height,
            SDL_WINDOW_OPENGL);
    if (app->window == NULL) {
        printf("[ERROR] Unable to create the application window!\n");
        return;
    }

    inited_loaders = IMG_Init(IMG_INIT_PNG);
    if (inited_loaders == 0) {
        printf("[ERROR] IMG initialization error: %s\n", IMG_GetError());
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL) {
        printf("[ERROR] Unable to create the OpenGL context!\n");
        return;
    }

    init_opengl();
    reshape(width, height);

    init_camera(&(app->camera));
    init_scene(&(app->scene));
    init_plane(&(app->plane));

    app->is_running = true;
}

void init_opengl() {
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.1, 0.1, 0.1, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void reshape(GLsizei width, GLsizei height) {
    int x, y, w, h;
    double ratio;

    ratio = (double) width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int) ((double) height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    } else {
        w = width;
        h = (int) ((double) width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(
            -.08, .08,
            -.06, .06,
            .1, 30000
    );
}

void handle_app_events(App *app) {
    SDL_Event event;
    static bool is_mouse_down = false;
    static int mouse_x = 0;
    static int mouse_y = 0;
    int x;
    int y;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_ESCAPE:
                        app->is_running = false;
                        break;
                    case SDL_SCANCODE_W:
                        set_camera_speed(&(app->camera), 10);
                        break;
                    case SDL_SCANCODE_S:
                        set_camera_speed(&(app->camera), -10);
                        break;
                    case SDL_SCANCODE_A:
                        set_camera_side_speed(&(app->camera), 10);
                        break;
                    case SDL_SCANCODE_D:
                        set_camera_side_speed(&(app->camera), -10);
                        break;
                    case SDL_SCANCODE_UP:
                        set_plane_speed_x(&(app->plane), 20);
                        app->plane.stateAcceleration = true;
                        break;
                    case SDL_SCANCODE_DOWN:
                        set_plane_speed_x(&(app->plane), 5);
                        app->plane.stateSlowing = true;
                        break;
                    case SDL_SCANCODE_LEFT:
                        set_plane_speed_y(&(app->plane), 5);
                        set_plane_rotation_speed(&(app->plane), -15);
                        break;
                    case SDL_SCANCODE_RIGHT:
                        set_plane_speed_y(&(app->plane), -5);
                        set_plane_rotation_speed(&(app->plane), 15);
                        break;
                    case SDL_SCANCODE_SPACE:
                        set_camera_speed_z(&(app->camera), 10);
                        break;
                    case SDL_SCANCODE_LSHIFT:
                        set_camera_speed_z(&(app->camera), -10);
                        break;
                    case SDL_SCANCODE_F1:
                        setControlState(&(app->scene), !(app->scene.controlOn));
                        break;
                    case SDL_SCANCODE_1:
                        setBrightness(&(app->scene), -0.1f);
                        break;
                    case SDL_SCANCODE_2:
                        setBrightness(&(app->scene), 0.1f);
                        break;
                    case SDL_SCANCODE_0:
                        app->plane.planePosition.x = 0.0f;
                        app->plane.planePosition.y = 0.0f;
                        app->plane.planePosition.z = 0.0f;
                        app->plane.planeSpeed.x = 0.0f;
                        app->camera.position.x = -7.5;
                        app->camera.position.y = 0.0;
                        app->camera.position.z = 2.0;
                        for (int i = 0; i < 12; i++) {
                            app->scene.checkpoint[i].position.z = 0.0;
                            app->scene.checkpoint[i].rotation.z = 0.0;
                            app->scene.checkpoint[i].collided = false;
                        }
                        break;
                    case SDL_SCANCODE_V:
                        app->camera.position.x = app->plane.planePosition.x - 7.5;
                        app->camera.position.y = app->plane.planePosition.y;
                        app->camera.position.z = 2.0;
                        app->camera.rotation.x = -8.0;
                        app->camera.rotation.y = 0.0;
                        app->camera.rotation.z = 0.0;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_W:
                    case SDL_SCANCODE_S:
                        set_camera_speed(&(app->camera), 0);
                        break;
                    case SDL_SCANCODE_A:
                    case SDL_SCANCODE_D:
                        set_camera_side_speed(&(app->camera), 0);
                        break;
                    case SDL_SCANCODE_UP:
                    case SDL_SCANCODE_DOWN:
                        set_plane_speed_x(&(app->plane), 10);
                        app->plane.stateAcceleration = false;
                        app->plane.stateSlowing = false;
                    case SDL_SCANCODE_LEFT:
                    case SDL_SCANCODE_RIGHT:
                        set_plane_speed_y(&(app->plane), 0);
                        set_plane_rotation_speed(&(app->plane), 0);
                    case SDL_SCANCODE_SPACE:
                    case SDL_SCANCODE_LSHIFT:
                        set_camera_speed_z(&(app->camera), 0);
                    case SDL_SCANCODE_1:
                    case SDL_SCANCODE_2:
                        setBrightness(&(app->scene), 0.0f);
                        break;

                    default:
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                is_mouse_down = true;
                break;
            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&x, &y);
                rotate_camera(&(app->camera), mouse_x - x, mouse_y - y);
                mouse_x = x;
                mouse_y = y;
                break;
            case SDL_MOUSEBUTTONUP:
                is_mouse_down = false;
                break;
            case SDL_QUIT:
                app->is_running = false;
                break;
            default:
                break;
        }
    }
}

void update_app(App *app) {
    double current_time;
    double elapsed_time;

    current_time = (double) SDL_GetTicks() / 1000;
    elapsed_time = current_time - app->uptime;
    app->uptime = current_time;

    update_camera(&(app->camera), elapsed_time);
    update_scene(&(app->scene), &(app->plane), &(app->camera), elapsed_time);
    update_plane(&(app->plane), &(app->camera), elapsed_time);
}

void render_app(App *app) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&(app->camera));
    render_scene(&(app->scene));
    render_plane(&(app->plane));
    glPopMatrix();

    if (app->camera.is_preview_visible) {
        show_texture_preview();
    }

    SDL_GL_SwapWindow(app->window);
}

void destroy_app(App *app) {
    if (app->gl_context != NULL) {
        SDL_GL_DeleteContext(app->gl_context);
    }

    if (app->window != NULL) {
        SDL_DestroyWindow(app->window);
    }

    SDL_Quit();
}
