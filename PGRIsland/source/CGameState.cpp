//----------------------------------------------------------------------------------------
/**
 * \file       CGameState.cpp
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief      Struct holding all necessary application data for drawing/interaction
 *
 * Initializes shaders, objects and holds logic variables
 *
*/
//----------------------------------------------------------------------------------------
#include "../include/CGameState.h"

CGameState::CGameState()
{
	for (auto & key : MKeyMap)
		key = false;

    gameState.MCamera.SetCamera(CAMERA_SPAWN_EYE, CAMERA_SPAWN_DIR, CAMERA_SPAWN_UP);
}

void CGameState::InitializeGame()
{
    MShader = CShaderProgram(GENERAL_VERTEX_SHADER, GENERAL_FRAGMENT_SHADER);
    MSkyboxShader = CShaderProgram(SKYBOX_VERTEX_SHADER, SKYBOX_FRAGMENT_SHADER);
    MTextureShader = CShaderProgram(GENERAL_VERTEX_SHADER, TEXTURE_FRAGMENT_SHADER);
    MWaterShader = CShaderProgram(WATER_VERTEX_SHADER, WATER_GEOMETRY_SHADER, WATER_FRAGMENT_SHADER);
    MFireShader = CShaderProgram(GENERAL_VERTEX_SHADER, FIRE_FRAGMENT_SHADER);
    MLightShader = CShaderProgram(GENERAL_VERTEX_SHADER, LIGHT_FRAGMENT_SHADER);
    MBannerShader = CShaderProgram(GENERAL_VERTEX_SHADER, BANNER_FRAGMENT_SHADER);

    // SKYBOX 1
    InitializeSkybox();

    // ISLAND 2
    InitializeIsland();

    // FISH 3, 4, 5, 6
    InitializeFishes();

    // SHIP 7
    InitializeShip();

    // WATER 8
    InitializeWater();

    // CAMPFIRE 9
    InitializeCampfire();

    // LIGHT 10
    InitializeSun();

    // BUCKET 11
    InitializeBucket();

    // CANNON 12
    InitializeCannon();

    // TORCH 13
    InitializeTorch();

    // FIRE 14
    InitializeFire();

    //EXPLOSION 15
    InitializeExplosion();
}

void CGameState::InitializeSkybox()
{
    std::shared_ptr<CSkyboxSceneNode> skybox = std::make_shared<CSkyboxSceneNode>(MSkyboxShader, SKYBOX_CHANGE_SLOW);
    skybox->SetPosition(SKYBOX_OFFSET);
    MRoot->PushSceneNode(skybox);
}

void CGameState::InitializeIsland()
{
    std::shared_ptr<CSceneNode> island = std::make_shared<CSceneNode>(MShader);
    island->LoadSceneNode(ISLAND_PATH);
    island->SetPosition(ISLAND_POSITION);
    island->SetSize(ISLAND_SIZE);
    MRoot->PushSceneNode(island);
}

void CGameState::InitializeFishes()
{
    // FISH 3
    // Fish banner 
    std::shared_ptr<CSceneNode> fishBanner = std::make_shared<CSceneNode>(MBannerShader);
    fishBanner->LoadSceneNode(planeOrthoNAttribsPerVertex, planeOrthoNVertices, planeOrthoNTriangles, planeOrthoBannerVertices, planeOrthoTriangles);
    fishBanner->LoadTextureSceneNode(FISH_PATH, GL_TEXTURE_2D, true);
    fishBanner->SetPosition(FISH_BANNER_POSITION);
    fishBanner->SetDirection(FISH_BANNER_DIRECTION);
    fishBanner->SetSize(FISH_BANNER_SIZE);
    MRoot->PushSceneNode(fishBanner);

    // FISH 4
    std::shared_ptr<CSplineSceneNode> fish = std::make_shared<CSplineSceneNode>(MTextureShader, FISH_ONE_CONTROL_POINTS, FISH_CHANGE_SLOW);
    fish->LoadSceneNode(planeOrthoNAttribsPerVertex, planeOrthoNVertices, planeOrthoNTriangles, planeOrthoVertices, planeOrthoTriangles);
    fish->LoadTextureSceneNode(FISH_PATH, GL_TEXTURE_2D);
    fish->SetSize(FISH_SIZE);
    MRoot->PushSceneNode(fish);

    // FISH 5
    std::shared_ptr<CSplineSceneNode> fish1 = std::make_shared<CSplineSceneNode>(MTextureShader, FISH_TWO_CONTROL_POINTS, FISH_CHANGE_SLOW);
    fish1->LoadSceneNode(planeOrthoNAttribsPerVertex, planeOrthoNVertices, planeOrthoNTriangles, planeOrthoVertices, planeOrthoTriangles);
    fish1->LoadTextureSceneNode(FISH_PATH, GL_TEXTURE_2D);
    fish1->SetSize(FISH_SIZE);
    MRoot->PushSceneNode(fish1);

    // FISH 6
    std::shared_ptr<CSplineSceneNode> fish2 = std::make_shared<CSplineSceneNode>(MTextureShader, FISH_THREE_CONTROL_POINTS, FISH_CHANGE_SLOW);
    fish2->LoadSceneNode(planeOrthoNAttribsPerVertex, planeOrthoNVertices, planeOrthoNTriangles, planeOrthoVertices, planeOrthoTriangles);
    fish2->LoadTextureSceneNode(FISH_PATH, GL_TEXTURE_2D);
    fish2->SetSize(FISH_SIZE);
    MRoot->PushSceneNode(fish2);
}

void CGameState::InitializeShip()
{
    std::shared_ptr<CSplineSceneNode> ship = std::make_shared<CSplineSceneNode>(MShader, CCatmulRomSpline(SHIP_CONTROL_POINTS), SHIP_CHANGE_SLOW);
    ship->LoadSceneNode(SHIP_PATH);
    ship->SetSize(SHIP_SIZE);
    gameState.MShip = ship;
    MRoot->PushSceneNode(ship);
}

void CGameState::InitializeCampfire()
{
    std::shared_ptr<CSceneNode> campfire = std::make_shared<CSceneNode>(MShader);
    campfire->LoadSceneNode(CAMPFIRE_PATH);
    campfire->SetPosition(CAMPFIRE_POSITION);
    campfire->SetSize(CAMPFIRE_SIZE);
    MRoot->PushSceneNode(campfire);
}

void CGameState::InitializeSun()
{
    std::shared_ptr<CSceneNode> sun = std::make_shared<CSceneNode>(MLightShader);
    sun->LoadSceneNode(sphereNAttribsPerVertex,
        sphereNVertices, sphereNTriangles,
        sphereVertices, sphereTriangles);
    sun->SetSize(SUN_SIZE);
    sun->SetPosition(SUN_POSITION);
    MRoot->PushSceneNode(sun);
}

void CGameState::InitializeBucket()
{
    std::shared_ptr<CSceneNode> bucket = std::make_shared<CSceneNode>(MShader);
    bucket->LoadSceneNode(BUCKET_PATH);
    bucket->SetPickable(true);
    bucket->SetSize(BUCKET_SIZE);
    bucket->SetPosition(BUCKET_POSITION);
    MRoot->PushSceneNode(bucket);
}

void CGameState::InitializeCannon()
{
    std::shared_ptr<CSceneNode> cannon = std::make_shared<CSceneNode>(MShader);
    cannon->LoadSceneNode(CANNON_PATH);
    cannon->SetSize(CANNON_SIZE);
    cannon->SetPosition(CANNON_POSITION);
    cannon->SetDirection(CANNON_DIRECTION);
    cannon->SetCollision(true);
    MRoot->PushSceneNode(cannon);
}

void CGameState::InitializeTorch()
{
    std::shared_ptr<CSceneNode> torch = std::make_shared<CSceneNode>(MShader);
    torch->LoadSceneNode(TORCH_PATH);
    torch->SetSize(TORCH_SIZE);
    torch->SetPosition(TORCH_POSITION);
    torch->SetPickable(true);
    MRoot->PushSceneNode(torch);
}

void CGameState::InitializeFire()
{
    std::shared_ptr<CSceneNode> fire = std::make_shared<CSceneNode>(MFireShader);
    fire->LoadSceneNode(planeNAttribsPerVertex, planeNVertices, planeNTriangles, planeVertices, planeTriangles);
    fire->LoadTextureSceneNode(FIRE_PATH, GL_TEXTURE_2D);
    fire->SetSize(FIRE_SIZE);
    fire->SetPosition(FIRE_POSITION);
    fire->SetCollision(true);
    MRoot->PushSceneNode(fire);
}

void CGameState::InitializeExplosion()
{
    std::shared_ptr<CBillboardSceneNode> explosion = std::make_shared<CBillboardSceneNode>(MFireShader);
    explosion->LoadSceneNode(planeNAttribsPerVertex, planeNVertices, planeNTriangles, planeVertices, planeTriangles);
    explosion->LoadTextureSceneNode(EXPLOSION_PATH, GL_TEXTURE_2D);
    explosion->SetPosition(EXPLOSION_POSITION);
    explosion->SetOn(false);
    explosion->SetCollision(true);
    MRoot->PushSceneNode(explosion);
}

void CGameState::InitializeWater()
{
    std::shared_ptr<CWaterPlaneSceneNode> plane = std::make_shared<CWaterPlaneSceneNode>(MWaterShader);
    plane->SetPosition(WATER_POSITION);
    plane->SetSize(WATER_SIZE);
    MRoot->PushSceneNode(plane);
}

glm::mat4 CGameState::GetProjectionMatrix()
{
	return glm::perspective(glm::radians(VIEW_ANGLE), (float) MWindowWidth / (float)MWindowHeight, NEAR_PLANE, FAR_PLANE);
}

CGameState gameState;
