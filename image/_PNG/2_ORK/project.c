#include "raylib.h"
#include <stdio.h>

#define MAX_FRAMES 10
#define NUM_ANIMATIONS 8

typedef struct {
    char name[20];
    Texture2D frames[MAX_FRAMES];
    int numFrames;
} Animation;

int main(void)
{
    // Window size
    const int winWidth = 800;
    const int winHeight = 600;
    InitWindow(winWidth, winHeight, "Troll/Ork Animation Example");

    // Folder path
    const char *folderPath = "/Users/md.azizulhakimkhanrafid/Downloads/project/image/_PNG/2_ORK";

    // Animation names matching your file prefixes
    const char *animationNames[NUM_ANIMATIONS] = {
        "IDLE", "RUN", "WALK", "ATTAK", "JUMP", "HURT", "DIE", "ORIGINAL"
    };

    Animation animations[NUM_ANIMATIONS];

    // Load all animations with debug prints
    for (int a = 0; a < NUM_ANIMATIONS; a++)
    {
        sprintf(animations[a].name, "%s", animationNames[a]);
        animations[a].numFrames = 0;

        for (int i = 0; i < MAX_FRAMES; i++)
        {
            char filename[300];
            sprintf(filename, "%s/ORK_02_%s_%03d.png", folderPath, animationNames[a], i);

            Texture2D tex = LoadTexture(filename);
            if (tex.id == 0)
            {
                printf("Failed to load: %s\n", filename);
                break; // stop loading further frames if missing
            }
            else
            {
                printf("Loaded: %s\n", filename);
                animations[a].frames[animations[a].numFrames++] = tex;
            }
        }

        printf("%s animation has %d frames loaded.\n", animations[a].name, animations[a].numFrames);
    }

    // Start with IDLE animation
    Animation *currentAnimation = &animations[0];
    int currentFrame = 0;
    float timer = 0.0f;
    float frameTime = 0.2f; // seconds per frame

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        timer += deltaTime;

        if (timer >= frameTime)
        {
            timer = 0;
            currentFrame++;
            if (currentFrame >= currentAnimation->numFrames)
                currentFrame = 0;
        }

        // Switch animations with keys
        if (IsKeyPressed(KEY_I)) currentAnimation = &animations[0];
        if (IsKeyPressed(KEY_R)) currentAnimation = &animations[1];
        if (IsKeyPressed(KEY_W)) currentAnimation = &animations[2];
        if (IsKeyPressed(KEY_A)) currentAnimation = &animations[3];
        if (IsKeyPressed(KEY_J)) currentAnimation = &animations[4];
        if (IsKeyPressed(KEY_H)) currentAnimation = &animations[5];
        if (IsKeyPressed(KEY_D)) currentAnimation = &animations[6];
        if (IsKeyPressed(KEY_O)) currentAnimation = &animations[7];

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (currentAnimation->numFrames > 0)
        {
            // Scale image to fit window
            DrawTexturePro(
                currentAnimation->frames[currentFrame],
                (Rectangle){0, 0, currentAnimation->frames[currentFrame].width, currentAnimation->frames[currentFrame].height}, // source
                (Rectangle){100, 100, 400, 238}, // destination (position + size)
                (Vector2){0, 0}, // origin
                0.0f, // rotation
                WHITE
            );
        }

        EndDrawing();
    }

    // Unload textures
    for (int a = 0; a < NUM_ANIMATIONS; a++)
    {
        for (int i = 0; i < animations[a].numFrames; i++)
            UnloadTexture(animations[a].frames[i]);
    }

    CloseWindow();
    return 0;
}
