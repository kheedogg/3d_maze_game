#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 화면 크기 상수
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

// 게임 페이지 열거형
typedef enum {
    START_PAGE,
    MENU_SELECT_PAGE,
    CUSTOM_MENU_PAGE,
    GAMEPLAY_MODE1_PAGE,
    GAMEPLAY_MODE2_PAGE,
    GAMEPLAY_CUSTOM_PAGE,
    GAME_STATUS_PAGE,
    FINISH_GAME_PAGE
} GamePage;

// 게임 상태 구조체
typedef struct {
    GamePage currentPage;
    GamePage previousPage;
    float pageTimer;
    bool gameRunning;
    Camera3D camera;
    Vector3 playerPosition;
    Vector3 exitPosition;
    int mazeWidth;
    int mazeHeight;
    char **maze;
    bool gameWon;
    bool gamePaused;
    int selectedMenuButton;
    bool mousePressedLastFrame;
} GameState;

// 커스텀 게임 구조체
typedef struct {
    int id;
    int width;
    int height;
    Vector2 startPoint;
    Vector2 endPoint;
    Vector2 *walls;
    int wallCount;
} CustomGame;

// 전역 변수
GameState gameState = {0};

// 함수 선언
void InitGame(void);
void UpdateGame(void);
void DrawGame(void);
void CleanupGame(void);
void CreateMaze(int width, int height);
void FreeMaze(void);
CustomGame LoadRandomCustomGame(void);
void DrawStartPage(void);
void DrawMenuSelectPage(void);
void DrawCustomMenuPage(void);
void DrawGamePlayMode1Page(void);
void DrawGamePlayMode2Page(void);
void DrawGamePlayCustomPage(void);
void DrawGameStatusPage(void);
void DrawFinishGamePage(void);
void UpdateStartPage(void);
void UpdateMenuSelectPage(void);
void UpdateCustomMenuPage(void);
void UpdateGamePlayMode1Page(void);
void UpdateGamePlayMode2Page(void);
void UpdateGamePlayCustomPage(void);
void UpdateGameStatusPage(void);
void UpdateFinishGamePage(void);

// 메인 함수
int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "DoMazeGame - 3D Maze Adventure");
    SetTargetFPS(60);
    
    InitGame();
    
    while (!WindowShouldClose() && gameState.gameRunning) {
        UpdateGame();
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawGame();
        EndDrawing();
    }
    
    CleanupGame();
    CloseWindow();
    
    return 0;
}

// 게임 초기화
void InitGame(void) {
    gameState.currentPage = START_PAGE;
    gameState.previousPage = START_PAGE;
    gameState.pageTimer = 0.0f;
    gameState.gameRunning = true;
    gameState.gameWon = false;
    gameState.gamePaused = false;
    gameState.selectedMenuButton = 0;
    gameState.mousePressedLastFrame = false;
    
    // 카메라 초기화
    gameState.camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
    gameState.camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    gameState.camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    gameState.camera.fovy = 45.0f;
    gameState.camera.projection = CAMERA_PERSPECTIVE;
    
    // 플레이어 위치 초기화
    gameState.playerPosition = (Vector3){ 1.0f, 0.5f, 1.0f };
    gameState.exitPosition = (Vector3){ 13.0f, 0.5f, 13.0f };
    
    CreateMaze(15, 15);
    
    srand(time(NULL));
}

// 하드코딩된 커스텀 게임 데이터
CustomGame customGames[3] = {
    {1, 15, 15, {1, 1}, {13, 13}, NULL, 0},
    {2, 20, 20, {2, 2}, {18, 18}, NULL, 0},
    {3, 10, 10, {1, 1}, {8, 8}, NULL, 0}
};

// 미로 생성
void CreateMaze(int width, int height) {
    gameState.mazeWidth = width;
    gameState.mazeHeight = height;
    
    // 기존 미로 해제
    FreeMaze();
    
    // 새 미로 할당
    gameState.maze = (char **)malloc(height * sizeof(char *));
    for (int i = 0; i < height; i++) {
        gameState.maze[i] = (char *)malloc(width * sizeof(char));
        for (int j = 0; j < width; j++) {
            // 외곽은 벽, 내부는 기본적으로 통로
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                gameState.maze[i][j] = '#';
            } else {
                gameState.maze[i][j] = (rand() % 4 == 0) ? '#' : '.';
            }
        }
    }
    
    // 시작점과 출구는 통로로 설정
    gameState.maze[1][1] = '.';
    gameState.maze[height-2][width-2] = '.';
}

// 미로 메모리 해제
void FreeMaze(void) {
    if (gameState.maze) {
        for (int i = 0; i < gameState.mazeHeight; i++) {
            free(gameState.maze[i]);
        }
        free(gameState.maze);
        gameState.maze = NULL;
    }
}

// 랜덤 커스텀 게임 로드
CustomGame LoadRandomCustomGame(void) {
    int randomIndex = rand() % 3;
    return customGames[randomIndex];
}

// 게임 업데이트
void UpdateGame(void) {
    gameState.pageTimer += GetFrameTime();
    
    switch (gameState.currentPage) {
        case START_PAGE:
            UpdateStartPage();
            break;
        case MENU_SELECT_PAGE:
            UpdateMenuSelectPage();
            break;
        case CUSTOM_MENU_PAGE:
            UpdateCustomMenuPage();
            break;
        case GAMEPLAY_MODE1_PAGE:
            UpdateGamePlayMode1Page();
            break;
        case GAMEPLAY_MODE2_PAGE:
            UpdateGamePlayMode2Page();
            break;
        case GAMEPLAY_CUSTOM_PAGE:
            UpdateGamePlayCustomPage();
            break;
        case GAME_STATUS_PAGE:
            UpdateGameStatusPage();
            break;
        case FINISH_GAME_PAGE:
            UpdateFinishGamePage();
            break;
    }
}

// 게임 그리기
void DrawGame(void) {
    switch (gameState.currentPage) {
        case START_PAGE:
            DrawStartPage();
            break;
        case MENU_SELECT_PAGE:
            DrawMenuSelectPage();
            break;
        case CUSTOM_MENU_PAGE:
            DrawCustomMenuPage();
            break;
        case GAMEPLAY_MODE1_PAGE:
            DrawGamePlayMode1Page();
            break;
        case GAMEPLAY_MODE2_PAGE:
            DrawGamePlayMode2Page();
            break;
        case GAMEPLAY_CUSTOM_PAGE:
            DrawGamePlayCustomPage();
            break;
        case GAME_STATUS_PAGE:
            DrawGameStatusPage();
            break;
        case FINISH_GAME_PAGE:
            DrawFinishGamePage();
            break;
    }
}

// 시작 페이지 업데이트
void UpdateStartPage(void) {
    // 3초 후 자동으로 메뉴 선택 페이지로 이동
    if (gameState.pageTimer >= 3.0f) {
        gameState.currentPage = MENU_SELECT_PAGE;
        gameState.pageTimer = 0.0f;
    }
}

// 시작 페이지 그리기
void DrawStartPage(void) {
    BeginMode3D(gameState.camera);
    
    // 3D 블록에 "DoMazeGame" 텍스트 표시
    DrawCube((Vector3){ 0, 0, 0 }, 6.0f, 2.0f, 1.0f, BLUE);
    DrawCubeWires((Vector3){ 0, 0, 0 }, 6.0f, 2.0f, 1.0f, DARKBLUE);
    
    EndMode3D();
    
    // 2D 텍스트 오버레이
    DrawText("DoMazeGame", SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2 - 50, 80, WHITE);
    DrawText("Loading...", SCREEN_WIDTH/2 - 60, SCREEN_HEIGHT/2 + 50, 30, GRAY);
    
    // 진행 바
    float progress = gameState.pageTimer / 3.0f;
    DrawRectangle(SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2 + 100, (int)(400 * progress), 10, GREEN);
    DrawRectangleLines(SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2 + 100, 400, 10, BLACK);
}

// 메뉴 선택 페이지 업데이트
void UpdateMenuSelectPage(void) {
    Vector2 mousePos = GetMousePosition();
    
    // 버튼 영역 정의 (3개 버튼)
    Rectangle button1 = { SCREEN_WIDTH/2 - 100, 200, 200, 60 };
    Rectangle button2 = { SCREEN_WIDTH/2 - 100, 300, 200, 60 };
    Rectangle button3 = { SCREEN_WIDTH/2 - 100, 400, 200, 60 };
    
    gameState.selectedMenuButton = -1;
    
    if (CheckCollisionPointRec(mousePos, button1)) {
        gameState.selectedMenuButton = 0;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            gameState.currentPage = GAMEPLAY_MODE1_PAGE;
            gameState.pageTimer = 0.0f;
        }
    } else if (CheckCollisionPointRec(mousePos, button2)) {
        gameState.selectedMenuButton = 1;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            gameState.currentPage = GAMEPLAY_MODE2_PAGE;
            gameState.pageTimer = 0.0f;
        }
    } else if (CheckCollisionPointRec(mousePos, button3)) {
        gameState.selectedMenuButton = 2;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            gameState.currentPage = GAMEPLAY_CUSTOM_PAGE;
            gameState.pageTimer = 0.0f;
        }
    }
}

// 메뉴 선택 페이지 그리기
void DrawMenuSelectPage(void) {
    BeginMode3D(gameState.camera);
    
    // 3D 캐릭터 (간단한 캡슐로 표현)
    DrawCapsule((Vector3){ 0, 0, 0 }, (Vector3){ 0, 2, 0 }, 0.5f, 8, 8, BROWN);
    
    // 버튼들을 3D 큐브로 표현
    float shakeOffset = (gameState.selectedMenuButton == 0) ? sin(gameState.pageTimer * 10) * 0.1f : 0;
    DrawCube((Vector3){ -3, 1.5f + shakeOffset, -2 }, 2.0f, 0.5f, 0.3f, RED);
    
    shakeOffset = (gameState.selectedMenuButton == 1) ? sin(gameState.pageTimer * 10) * 0.1f : 0;
    DrawCube((Vector3){ 0, 1.5f + shakeOffset, -2 }, 2.0f, 0.5f, 0.3f, GREEN);
    
    shakeOffset = (gameState.selectedMenuButton == 2) ? sin(gameState.pageTimer * 10) * 0.1f : 0;
    DrawCube((Vector3){ 3, 1.5f + shakeOffset, -2 }, 2.0f, 0.5f, 0.3f, BLUE);
    
    EndMode3D();
    
    // 2D UI 오버레이
    DrawText("게임 모드를 선택하세요", SCREEN_WIDTH/2 - 150, 100, 30, BLACK);
    
    // 버튼 텍스트 (2D)
    Color button1Color = (gameState.selectedMenuButton == 0) ? YELLOW : WHITE;
    Color button2Color = (gameState.selectedMenuButton == 1) ? YELLOW : WHITE;
    Color button3Color = (gameState.selectedMenuButton == 2) ? YELLOW : WHITE;
    
    DrawText("1인칭 모드", SCREEN_WIDTH/2 - 200, 200, 20, button1Color);
    DrawText("3인칭 모드", SCREEN_WIDTH/2 - 50, 200, 20, button2Color);
    DrawText("커스텀 모드", SCREEN_WIDTH/2 + 100, 200, 20, button3Color);
}

// 나머지 페이지들의 기본 구현
void UpdateCustomMenuPage(void) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        gameState.currentPage = MENU_SELECT_PAGE;
        gameState.pageTimer = 0.0f;
    }
}

void DrawCustomMenuPage(void) {
    DrawText("커스텀 메뉴 페이지", SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT/2, 30, BLACK);
    DrawText("ESC: 뒤로가기", 20, SCREEN_HEIGHT - 40, 20, GRAY);
}

void UpdateGamePlayMode1Page(void) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        gameState.currentPage = GAME_STATUS_PAGE;
        gameState.previousPage = GAMEPLAY_MODE1_PAGE;
        gameState.pageTimer = 0.0f;
    }
    
    // 1인칭 시점 이동
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        gameState.playerPosition.z -= 0.1f;
    }
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        gameState.playerPosition.z += 0.1f;
    }
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        gameState.playerPosition.x -= 0.1f;
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        gameState.playerPosition.x += 0.1f;
    }
    
    // 승리 조건 체크
    if (Vector3Distance(gameState.playerPosition, gameState.exitPosition) < 1.0f) {
        gameState.gameWon = true;
        gameState.currentPage = FINISH_GAME_PAGE;
        gameState.pageTimer = 0.0f;
    }
}

void DrawGamePlayMode1Page(void) {
    // 1인칭 시점 카메라 설정
    Camera3D firstPersonCamera = gameState.camera;
    firstPersonCamera.position = gameState.playerPosition;
    firstPersonCamera.target = (Vector3){ 
        gameState.playerPosition.x, 
        gameState.playerPosition.y, 
        gameState.playerPosition.z - 1.0f 
    };
    
    BeginMode3D(firstPersonCamera);
    
    // 미로 그리기
    for (int i = 0; i < gameState.mazeHeight; i++) {
        for (int j = 0; j < gameState.mazeWidth; j++) {
            if (gameState.maze[i][j] == '#') {
                DrawCube((Vector3){ j, 1, i }, 1.0f, 2.0f, 1.0f, GRAY);
            }
        }
    }
    
    // 출구 표시
    DrawCube(gameState.exitPosition, 1.0f, 0.2f, 1.0f, GREEN);
    
    EndMode3D();
    
    DrawText("1인칭 모드", 20, 20, 20, BLACK);
    DrawText("WASD: 이동, ESC: 메뉴", 20, SCREEN_HEIGHT - 40, 20, GRAY);
}

void UpdateGamePlayMode2Page(void) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        gameState.currentPage = GAME_STATUS_PAGE;
        gameState.previousPage = GAMEPLAY_MODE2_PAGE;
        gameState.pageTimer = 0.0f;
    }
    
    // 3인칭 시점 이동 (동일한 로직)
    UpdateGamePlayMode1Page();
}

void DrawGamePlayMode2Page(void) {
    // 3인칭 시점 카메라 설정
    Camera3D thirdPersonCamera = gameState.camera;
    thirdPersonCamera.position = (Vector3){ 
        gameState.playerPosition.x + 5, 
        gameState.playerPosition.y + 8, 
        gameState.playerPosition.z + 5 
    };
    thirdPersonCamera.target = gameState.playerPosition;
    
    BeginMode3D(thirdPersonCamera);
    
    // 미로 그리기
    for (int i = 0; i < gameState.mazeHeight; i++) {
        for (int j = 0; j < gameState.mazeWidth; j++) {
            if (gameState.maze[i][j] == '#') {
                DrawCube((Vector3){ j, 1, i }, 1.0f, 2.0f, 1.0f, GRAY);
            }
        }
    }
    
    // 플레이어 표시
    DrawCube(gameState.playerPosition, 0.8f, 1.6f, 0.8f, RED);
    
    // 출구 표시
    DrawCube(gameState.exitPosition, 1.0f, 0.2f, 1.0f, GREEN);
    
    EndMode3D();
    
    DrawText("3인칭 모드", 20, 20, 20, BLACK);
    DrawText("WASD: 이동, ESC: 메뉴", 20, SCREEN_HEIGHT - 40, 20, GRAY);
}

void UpdateGamePlayCustomPage(void) {
    UpdateGamePlayMode1Page(); // 기본 로직 재사용
}

void DrawGamePlayCustomPage(void) {
    DrawGamePlayMode1Page(); // 기본 그리기 재사용
    DrawText("커스텀 모드", 20, 20, 20, BLACK);
}

void UpdateGameStatusPage(void) {
    if (IsKeyPressed(KEY_ENTER)) {
        gameState.currentPage = gameState.previousPage;
        gameState.pageTimer = 0.0f;
    } else if (IsKeyPressed(KEY_ESCAPE)) {
        gameState.currentPage = FINISH_GAME_PAGE;
        gameState.pageTimer = 0.0f;
    }
}

void DrawGameStatusPage(void) {
    // 반투명 배경
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){ 0, 0, 0, 128 });
    
    DrawText("게임 일시정지", SCREEN_WIDTH/2 - 120, SCREEN_HEIGHT/2 - 100, 30, WHITE);
    DrawText("ENTER: 이어서 하기", SCREEN_WIDTH/2 - 120, SCREEN_HEIGHT/2 - 20, 20, WHITE);
    DrawText("ESC: 게임 종료", SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 + 20, 20, WHITE);
}

void UpdateFinishGamePage(void) {
    if (gameState.pageTimer >= 2.0f) {
        gameState.currentPage = START_PAGE;
        gameState.pageTimer = 0.0f;
        gameState.gameWon = false;
    }
}

void DrawFinishGamePage(void) {
    if (gameState.gameWon) {
        DrawText("Success!", SCREEN_WIDTH/2 - 80, SCREEN_HEIGHT/2, 50, GREEN);
    } else {
        DrawText("Game Over", SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2, 50, RED);
    }
    
    float progress = gameState.pageTimer / 2.0f;
    DrawRectangle(SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 + 100, (int)(200 * progress), 10, BLUE);
    DrawRectangleLines(SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 + 100, 200, 10, BLACK);
}

// 게임 정리
void CleanupGame(void) {
    FreeMaze();
}