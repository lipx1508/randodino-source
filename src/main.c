// Libraries
#include <consts.h>
#include <dino.h>
#include <world.h>
#include <font.h>

#include <raylib.h>
#include <raymath.h>

#if defined(WEB)
    #include <emscripten/emscripten.h>
#endif

// Main
bool menu = true;

Shader        fb_shader;
RenderTexture fb;

static void loop() {
    world_update();
    dino_update();

    BeginDrawing();
        BeginTextureMode(fb);
            ClearBackground((Color){ 23, 17, 26, 255 });
            world_draw();
            dino_draw();
        EndTextureMode();

        BeginShaderMode(fb_shader);
            DrawTexturePro(fb.texture, (Rectangle){ 0, 0, FB_WIDTH, -FB_HEIGHT }, 
                                       (Rectangle){ 0, 0, WIDTH,     HEIGHT    }, Vector2Zero(), 0, WHITE);
        EndShaderMode();
    EndDrawing();
}

int main(int argc, char * argv[]) {
    InitWindow(WIDTH, HEIGHT, "randodino");
    InitAudioDevice();
    
    fb = LoadRenderTexture(FB_WIDTH, FB_HEIGHT);
    fb_shader = LoadShader("assets/shader.vs", "assets/shader.fs");

    float palette[] = {
        0.09f,  0.067f, 0.102f, 
        0.216f, 0.145f, 0.22f, 
        0.478f, 0.129f, 0.227f, 
        0.882f, 0.255f, 0.255f, 
        1.0f,   0.627f, 0.439f, 
        0.769f, 0.302f, 0.161f, 
        1.0f,   0.749f, 0.212f, 
        1.0f,   0.949f, 0.459f, 
        0.459f, 0.224f, 0.224f, 
        0.812f, 0.475f, 0.341f, 
        1.0f,   0.82f,  0.671f, 
        0.224f, 0.522f, 0.353f, 
        0.514f, 0.878f, 0.298f, 
        0.863f, 1.0f,   0.439f, 
        0.141f, 0.231f, 0.38f, 
        0.22f,  0.596f, 1.0f, 
        0.431f, 0.933f, 1.0f, 
        0.408f, 0.169f, 0.51f, 
        0.749f, 0.247f, 0.702f, 
        1.0f,   0.502f, 0.667f, 
        0.243f, 0.216f, 0.361f, 
        0.471f, 0.518f, 0.671f, 
        0.698f, 0.737f, 0.761f, 
        1.0f,   1.0f,   1.0f, 
    };
    SetShaderValueV(fb_shader, GetShaderLocation(fb_shader, "palette"), palette, SHADER_UNIFORM_VEC3, 24);

    dino_init();
    world_init();

#if defined(WEB)
    emscripten_set_main_loop(loop, 0, 1);
#else
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        loop();
    }
#endif

    CloseAudioDevice();
    CloseWindow();

    return 0;
}