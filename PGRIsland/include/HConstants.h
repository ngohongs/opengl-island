//----------------------------------------------------------------------------------------
/**
 * \file       HConstants.h
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief      File holding all constants used throughout C++ application
 *
 * Holds paths to files, initialization parameters of classes and struct in C++ application
 *
*/
//----------------------------------------------------------------------------------------
#pragma once

#include "pgr.h"

#include "CLight.h"

/**
 * Initial window height
 */
const int WINDOW_HEIGHT = 720;

/**
 * Initial window width
 */
const int WINDOW_WIDTH = 1280;

/**
 * Initial window title
 */
const std::string WINDOW_TITLE = "Island";

/**
 * Recognized key input
 */
enum { KEY_LOWER_W, KEY_LOWER_S, KEY_LOWER_A, KEY_LOWER_D, KEY_LEFT_ARROW, KEY_RIGHT_ARROW,
	  KEY_UP_ARROW, KEY_DOWN_ARROW, KEY_SPACE, KEYS_COUNT };

/**
 * Camera movement restriction in XZ plane
 */
const float XZ_RESTRICTION = 250.0f;

/**
 * Floor restriction in Y axis
 */
const float Y_BOTTOM_RESTRICTION = 4.0f;

/**
 * Top restriction in Y axis;
 */
const float Y_CEIL_RESTRICTION = 100.0f;

/**
 * Skybox change slow coefficient for animation
 */
const float SKYBOX_CHANGE_SLOW = 1.0f;

/**
 * Skybox offset
 */
const glm::vec3 SKYBOX_OFFSET = glm::vec3(0.0f, 100.0f, 0.0f);

/**
 * Island model path
 */
const std::string ISLAND_PATH = "models/island/island.obj";

/**
 * Island position
 */
const glm::vec3 ISLAND_POSITION = glm::vec3(-25.0f, 70.0f, -10.0f);

/**
 * Island size
 */
const glm::vec3 ISLAND_SIZE = glm::vec3(500.0f);

/**
 * Fish texture path
 */
const std::string FISH_PATH = "models/fish/fish.png";

/**
 * Fish size
 */
const glm::vec3 FISH_SIZE = glm::vec3(3.0f);

/**
 * Fish slow coefficient for animation 
 */
const float FISH_CHANGE_SLOW = 10.0f;

/**
 * Ship slow coefficient for animation
 */
const float SHIP_CHANGE_SLOW = 10.0f;

/**
 * Ship model path
 */
const std::string SHIP_PATH = "models/pirateship/scene.obj";

/**
 * Ship size
 */
const glm::vec3 SHIP_SIZE = glm::vec3(20.0f);

/**
 * Water plane position
 */
const glm::vec3 WATER_POSITION = glm::vec3(-1000.0f, 2.3f, -1000.0f);

/**
 * Water size
 */
const glm::vec3 WATER_SIZE = glm::vec3(10.0f);

/**
 * Campfire model path
 */
const std::string CAMPFIRE_PATH = "models/campfire/scene.obj";

/**
 * Campfire position
 */
const glm::vec3 CAMPFIRE_POSITION = glm::vec3(-123.005f, 17.005f, -9.06963f);

/**
 * Campfire size
 */
const glm::vec3 CAMPFIRE_SIZE = glm::vec3(2.0f);

/**
 * Sun position.
 */
const glm::vec3 SUN_POSITION = glm::vec3(0.0f, 500.0f, 0.0f);

/**
 * Sun size
 */
const glm::vec3 SUN_SIZE = glm::vec3(100.0f);

/**
 * Bucket model path
 */
const std::string BUCKET_PATH = "models/bucket/scene.obj";

/**
 * Bucket position
 */
const glm::vec3 BUCKET_POSITION = glm::vec3(-121.643f, 17.2506f, -14.4402f);

/**
 * Bucket size
 */
const glm::vec3 BUCKET_SIZE = glm::vec3(0.4f);

/**
 * Cannon model path
 */
const std::string CANNON_PATH = "models/cannon/scene.obj";

/**
 * Cannon position
 */
const glm::vec3 CANNON_POSITION = glm::vec3(-131.29f, 18.1978f, -13.4456f);

/**
 * Cannon facing direction
 */
const glm::vec3 CANNON_DIRECTION = glm::vec3(-0.511949f, 0.148042f, 0.846174f);

/**
 * Cannon size
 */
const glm::vec3 CANNON_SIZE = glm::vec3(1.5f);

/**
 * Torch model path
 */
const std::string TORCH_PATH = "models/torch/scene.obj";

/**
 * Torch position
 */
const glm::vec3 TORCH_POSITION = glm::vec3(-113.058f, 17.8056f, -10.1744f);

/**
 * Torch size
 */
const glm::vec3 TORCH_SIZE = glm::vec3(1.5f);

/**
 * Fire texture path
 */
const std::string FIRE_PATH = "models/fire/fire.png";

/**
 * Fire position
 */
const glm::vec3 FIRE_POSITION = glm::vec3(-123.148f, 19.4021f, -9.02837f);

/**
 * Fire size
 */
const glm::vec3 FIRE_SIZE = glm::vec3(3.0f);

/**
 * Explosion texture path
 */
const std::string EXPLOSION_PATH = "models/explosion/explosion.png";

/**
 * Explosion position.
 */
const glm::vec3 EXPLOSION_POSITION = glm::vec3(-133.141f, 19.0006f, -14.6989f);

/**
 * Explosion duration
 */
const float EXPLOSION_DURATION = 1.5f;

/**
 * General vertex shader source path
 */
const std::string GENERAL_VERTEX_SHADER = "shaders/SVertexShader.vert";

/**
 * General fragment shader source path
 */
const std::string GENERAL_FRAGMENT_SHADER = "shaders/SFragmentShader.frag";

/**
 * Skybox vertex shader source path
 */
const std::string SKYBOX_VERTEX_SHADER = "shaders/SSkyboxVertexShader.vert";

/**
 * Skybox fragment shader source path
 */
const std::string SKYBOX_FRAGMENT_SHADER = "shaders/SSkyboxFragmentShader.frag";

/**
 * Water vertex shader source path
 */
const std::string WATER_VERTEX_SHADER = "shaders/SWaterVertexShader.vert";

/**
 * Water geometry shader source path
 */
const std::string WATER_GEOMETRY_SHADER = "shaders/SWaterGeometryShader.geom";

/**
 * Water fragment shader source path
 */
const std::string WATER_FRAGMENT_SHADER = "shaders/SWaterFragmentShader.frag";

/**
 * Texture fragment shader source path
 */
const std::string TEXTURE_FRAGMENT_SHADER = "shaders/STextureFragmentShader.frag";

/**
 * Fire fragment shader source path
 */
const std::string FIRE_FRAGMENT_SHADER = "shaders/SFireFragmentShader.frag";

/**
 * Light fragment shader source path
 */
const std::string LIGHT_FRAGMENT_SHADER = "shaders/SLightFragmentShader.frag";

/**
 * Banner fragment shader source path
 */
const std::string BANNER_FRAGMENT_SHADER = "shaders/SBannerFragmentShader.frag";

/**
 * Camera spawn location
 */
const glm::vec3 CAMERA_SPAWN_EYE = glm::vec3(-131.163f, 47.0685f, 69.6766f);

/**
 * Camera spawn facing direction
 */
const glm::vec3 CAMERA_SPAWN_DIR = glm::vec3(0.198601f, -0.248533f, -0.948051f);

/**
 * Camera spawn up vector
 */
const glm::vec3 CAMERA_SPAWN_UP = glm::vec3(0.0178161f, 0.968071f, -0.250049f);

/**
 * Static view #1 camera location 
 */
const glm::vec3 STATIC_VIEW_ONE_EYE = glm::vec3(-116.919f, 22.7344f, 9.08381f);

/**
 * Static view #1 camera viewing direction
 */
const glm::vec3 STATIC_VIEW_ONE_DIR = glm::vec3(-0.24736f, 0.0198368f, -0.968752f);

/**
 * Static view #1 camera up vector
 */
const glm::vec3 STATIC_VIEW_ONE_UP = glm::vec3(-0.0290579f, 0.999202f, 0.0278784f);

/**
 * Static view #2 camera location
 */
const glm::vec3 STATIC_VIEW_TWO_EYE = glm::vec3(-210.966f, 12.8f, 110.2f);

/**
 * Static view #2 camera viewing direction
 */
const glm::vec3 STATIC_VIEW_TWO_DIR = glm::vec3(-0.561264f, -0.288765f, 0.775679f);

/**
 * Static view #2 camera up vector
 */
const glm::vec3 STATIC_VIEW_TWO_UP = glm::vec3(-0.150414f, 0.95716f, 0.247493f);

/**
 * Static view #3 camera location
 */
const glm::vec3 STATIC_VIEW_THREE_EYE = glm::vec3(-35.2999f, 34.6821f, 144.558f);

/**
 * Static view #3 camera viewing direction
 */
const glm::vec3 STATIC_VIEW_THREE_DIR = glm::vec3(0.577926f, -0.0947738f, -0.81062f);

/**
 * Static view #3 camera up vector
 */
const glm::vec3 STATIC_VIEW_THREE_UP = glm::vec3(0.154813f, 0.987948f, -0.00513706f);

/**
 * Camera panning angle
 */
const float PAN_ANGLE = 2.0f;

/**
 * Camera tilting angle
 */
const float TILT_ANGLE = 2.0f;

/**
 * Camera forward and backward coefficient of the directional vector
 * 
 * used for moving back and forward
 */
const float FRONT_BACK_MOVEMENT_COEF = 1.0f;

/**
 * Camera right and left coefficient of the right vector
 * 
 * used for moving right and left
 */
const float RIGHT_LEFT_MOVEMENT_COEF = 1.0f;

/**
 * Camera slow coefficient of flight view
 */
const float CAMERA_FLIGHT_SLOW = 5.0f;

/**
 * Ship spline control points
 */
const std::vector<glm::vec3> SHIP_CONTROL_POINTS = { 
    {-400.127f, 12.65037f, 75.8268f},
    {-337.941f, 13.6033f, 259.16f},
    {-138.231f, 12.46767f, 355.782f},
    {87.3974f, 11.69915f, 384.983f},
    {303.514f, 12.5696f, 187.291f},
    {328.052f, 13.18407f, -153.569f},
    {222.669f, 12.8382f, -232.16f},
    {31.4992f, 11.92106f, -308.382f},
    {-118.098f, 13.23047f, -307.097f},
    {-295.312f, 12.58597f, -194.083f}
};

///**
// * Flight view spline control points
// */
//const std::vector<glm::vec3> FLIGHT_CONTROL_POINTS = {
//    {-241.79f, 85.7793f, 166.546f},
//    {-172.665f, 93.2223f, 185.604f},
//    {-71.7901f, 107.688f, 219.351f},
//    {7.26213f, 102.262f, 209.702f},
//    {114.022f, 95.7524f, 176.375f},
//    {184.36f, 120.642f, 94.5228f},
//    {185.972f, 106.819f, -94.2811f},
//    {-36.3041f, 80.2945f, -245.268f},
//    {-214.308f, 69.1942f, -106.019f}
//};

/**
 * Swimming fishes #1 control points
 */
const std::vector<glm::vec3> FISH_ONE_CONTROL_POINTS = {
    {-417.819f, -14.7591f, -9.73431f},
    {-427.808f, -19.9882f, -94.4084f},
    {-397.9f, -24.2524f, -215.268f},
    {-307.883f, -25.1613f, -357.093f},
    {-161.606f, -12.7359f, -359.94f},
    {-28.4068f, -6.25666f, -341.886f},
    {82.1323f, -4.56573f, -283.058f},
    {196.769f, -3.77956f, -214.276f},
    {247.85f, -4.90409f, -91.8833f},
    {276.335f, -7.37768f, 48.089f},
    {182.649f, -8.84303f, 246.538f},
    {6.86475f, -8.46821f, 317.319f},
    {-142.738f, -1.73929f, 288.446f},
    {-297.599f, -8.03653f, 169.015f},
    {-382.282f, -9.11705f, -19.6118f}
};

/**
 * Swimming fishes #2 control points
 */
const std::vector<glm::vec3> FISH_TWO_CONTROL_POINTS = {
    {-413.131f, -26.4548f, 195.296f},
    {-354.962f, -29.4481f, 279.437f},
    {-270.003f, -18.5083f, 265.941f},
    {-364.249f, -11.9931f, 166.4f}
};

/**
 * Swimming fishes #3 control points
 */
const std::vector<glm::vec3> FISH_THREE_CONTROL_POINTS = {
    {-216.199f, -3.16091f, 144.096f},
    {-251.132f, -5.19142f, 207.076f},
    {-291.518f, -9.6848f, 186.92f},
    {-291.829f, -5.33817f, 132.859f}
};

/**
 * Swimming fishes banner position
 */
const glm::vec3 FISH_BANNER_POSITION = { -189.147f, -1.84893f, 116.02f };

/**
 * Swimming fishes banner size
 */
const glm::vec3 FISH_BANNER_SIZE = { 3.0f, 3.0f, 100.0f };

/**
 * Swimming fishes banner direction.
 */
const glm::vec3 FISH_BANNER_DIRECTION = { 0.612168f, 0.00f, 0.79078f };

/**
 * Camera flight control points 
 */
const std::vector<glm::vec3> CAMERA_CONTROL_POINTS = {
    {-249.783f, 86.3562f, 150.14f},
    {-179.961f, 55.1058f, 27.6329f},
    {-139.094f, 43.0517f, -7.3428f},
    {-86.6631f, 49.238f, 15.167f},
    {-46.1066f, 57.8657f, 87.2511f},
    {3.73056f, 44.9831f, 96.6549f},
    {40.9536f, 48.3868f, 150.618f},
    {-110.391f, 74.184f, 113.613f}
};

/**
 * Daylight skybox faces texture paths
 */
const std::vector<std::string> SKYBOX_FACES =
{
        "models/skybox/right.png",
        "models/skybox/left.png",
        "models/skybox/up.png",
        "models/skybox/down.png",
        "models/skybox/back.png",
        "models/skybox/front.png"

};

/**
 * Midnight skybox faces texture paths
 */
const std::vector<std::string> SKYBOX_MIDNIGHT_FACES =
{
        "models/skybox/midnight/right.png",
        "models/skybox/midnight/left.png",
        "models/skybox/midnight/up.png",
        "models/skybox/midnight/down.png",
        "models/skybox/midnight/back.png",
        "models/skybox/midnight/front.png"

};

/**
 * Skybox size
 */
const glm::vec3 SKYBOX_SIZE = glm::vec3(500.0f);

/**
 * Campfire light
 */
const CLight CAMPFIRE_LIGHT =
{
    {-124.637f, 30.7056f, -10.4889f, 1.0f},
    {0.3f, 0.3f, 0.3f},
    {1.0f, 0.0f, 0.05f},
    {1.0f, 1.0f, 1.0f},
    {1.0f, 0.07f, 0.005f}
};

/**
 * Campfire off light
 */
const CLight NO_CAMPFIRE_LIGHT =
{
    {-124.637f, 30.7056f, -10.4889f, 1.0f},
    {0.01f, 0.01f, 0.01f},
    {0.01f, 0.01f, 0.01f},
    {0.01f, 0.01f, 0.01f},
    {1.0f, 0.07f, 0.005f}
};

/**
 * Day light
 */
const CLight DAY_LIGHT =
{
    {4.781f, -10.005f, -18.325f, 0.0f},
    {0.1f, 0.1f, 0.1f},
    {0.8f, 0.8f, 0.8f},
    {1.0f, 1.0f, 1.0f}
};

/**
 * Night light
 */
const CLight NIGHT_LIGHT =
{
    {4.781f, -10.005f, -18.325f, 0.0f},
    {0.01f, 0.01f, 0.01f},
    {0.001f, 0.001f, 0.001f},
    {0.025f, 0.025f, 0.025f}
};

/**
 * Camera spot light cutoff
 */
const float CAMERA_LIGHT_CUTOFF = glm::cos(glm::radians(12.5f));

/**
 * Camera spot light outer cutoff
 */
const float CAMERA_LIGHT_OUTERCUTOFF = glm::cos(glm::radians(20.0f));

/**
 * Water plane side vertex count
 */
const int WATER_PLANE_SIDE_SIZE = 2000;

/**
 * Water plane vertex gap
 */
const float WATER_PLANE_VERTEX_GAP = 1.0f;

/**
 * Viewing angle
 */
const float VIEW_ANGLE = 35.0f;

/**
 * Near plane of the projection
 */
const float NEAR_PLANE = 0.1f;

/**
 * Far plane of the projection
 */
const float FAR_PLANE = 1250.0f;

/**
 * Size of the player
 */
const glm::vec3 CAMERA_SIZE = glm::vec3(1.0f);
