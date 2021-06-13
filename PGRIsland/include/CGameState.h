//----------------------------------------------------------------------------------------
/**
 * \file       CGameState.h
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief      Struct holding all necessary application data for drawing/interaction 
 *
 * Initializes shaders, objects and holds logic variables
 *
*/
//----------------------------------------------------------------------------------------
#pragma once

#include "pgr.h"

#include "HConstants.h"
#include "CCamera.h"
#include "CLight.h"
#include "CCatmulRomSpline.h"

#include "sphere.h"
#include "plane.h"
#include "planeOrtho.h"

#include "CSceneNode.h"
#include "CWaterPlaneSceneNode.h"
#include "CSkyboxSceneNode.h"
#include "CSplineSceneNode.h"
#include "CBillboardSceneNode.h"

/**
 * Game state struct
 * 
 * handles all models initializations and shader program initializations
 * and overall classes that help in drawing a scene
 * 
 */
struct CGameState
{
private:
	/**
	 * Help method initializing a skybox model to the scene
	 */
	void InitializeSkybox();

	/**
	 * Help method initializing an island model to the scene
	 */
	void InitializeIsland();

	/**
	 * Help method initializing fishes to the scene
	 */
	void InitializeFishes();

	/**
	 * Help method initializing a ship to the scene
	 */
	void InitializeShip();

	/**
	 * Help method initializing a water plane to the scene
	 */
	void InitializeWater();

	/**
	 * Help method initializing a campfire to the scene
	 */
	void InitializeCampfire();

	/**
	 * Help method initializing a sun to the scene
	 */
	void InitializeSun();

	/**
	 * Help method initializing a bucket to the scene
	 */
	void InitializeBucket();

	/**
	 * Help method initializing a cannon to the scene
	 */
	void InitializeCannon();

	/**
	 * Help method initializing a torch to the scene
	 */
	void InitializeTorch();

	/**
	 * Help method initializing a fire to the scene
	 */
	void InitializeFire();

	/**
	 * Help method initializing an explosion the scene
	 */
	void InitializeExplosion();

	/**
	 * Shader program for drawing generic objects
	 */
	CShaderProgram MShader;

	/**
	 * Shader program for drawing skybox
	 */
	CShaderProgram MSkyboxShader; 

	/**
	 * Shader program for drawing 2D texture objects
	 */
	CShaderProgram MTextureShader; 

	/**
	 * Shader program for drawing a water plane
	 */
	CShaderProgram MWaterShader; 

	/**
	 * Shader program for drawing fire
	 */
	CShaderProgram MFireShader;

	/**
	 * Shader program for drawing light source
	 */
	CShaderProgram MLightShader; 

	/**
	 * Shader program for drawing banners
	 */
	CShaderProgram MBannerShader;
public:
	/**
	 * Default constructor
	 * 
	 * initializes key map and setups camera to spawn position 
	 */
	CGameState();

	/**
	 * Initializes shaders and models
	 * 
	 * models are setup for the scene rendering
	 */
	void InitializeGame();

	/**
	 * Boolean representing if it is day or night
	 */
	bool MDay = true;

	/**
	 * Light of the campfire
	 */
	CLight light = CAMPFIRE_LIGHT;

	/**
	 * Light of the directional light
	 */
	CLight dirLight = DAY_LIGHT;

	/**
	 * View switch variable
	 * 
	 * used for switching between views
	 * 
	 * values:
	 *  -1 - spawn position, can be accessed only at the start of the game
	 *   0 - static view #1
	 *   1 - static view #2
	 *   2 - static view #3
	 *	 3 - flight view
	 *   4 - boat view
	 */
	int MView = -1;

	/**
	 * Help variable for counting time delta.
	 */
	int MLastFrameTime = 0;

	/**
	 * Current time delta
	 */
	float MTimeDelta = 0.0f;

	/**
	 * Camera of the scene
	 */
	CCamera MCamera;
	
	/**
	 * Key map for keyboard input handling
	 */
	bool MKeyMap[KEYS_COUNT];
	
	/**
	 * Item which is being hold
	 * 
	 * -1 - none
	 * 
	 * depends on initialization of the models
	 */
	int MHolding = -1;

	/**
	 * Windows width
	 */
	int MWindowWidth;

	/**
	 * Window height
	 */
	int MWindowHeight;
	
	/**
	 * Boolean wheter camera can be rotated by mouse movements
	 * if  true - yes
	 * if false - noe
	 */
	bool MFreeCamera = false;

	/**
	 * Boolean representing if the player is in control of the camera
	 * if  true - yes
	 * if false - no
	 */
	bool MCameraControl = true;

	/**
	 * Spline for the flight view
	 * 
	 * \see CCatmulRomSpline
	 */
	CCatmulRomSpline MCameraSpline = CCatmulRomSpline(CAMERA_CONTROL_POINTS);

	/**
	 * Time for controling position of the camera during flight view
	 */
	float MSplineTime = 0.0f;

	/**
	 * Getter for view matrix
	 * 
	 * \see CCamera
	 * 
	 * \return view matrix according to camera
	 */
	glm::mat4 GetViewMatrix() { return MCamera.GetViewMatrix(); }

	/**
	 * Getter for projection matrix
	 * 
	 * \return projection matrix
	 */
	glm::mat4 GetProjectionMatrix();

	/**
	 * Root scene node
	 * 
	 * holds all models for drawing
	 */
	std::shared_ptr<CSceneNode> MRoot = std::make_shared<CSceneNode>();

	/**
	 * Ship pointer
	 * 
	 * used for calculating position of the camera during ship view
	 */
	std::shared_ptr<CSceneNode> MShip = nullptr;
};

/**
 * Games state that can be accessed through the whole project
 */
extern CGameState gameState;