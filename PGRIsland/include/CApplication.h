//----------------------------------------------------------------------------------------
/**
 * \file       CApplication.h
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief      Class representing an application with functions for GLUT window 
 *
 * GLUT functions are need for initialization and handling of a window events
 *
*/
//----------------------------------------------------------------------------------------
#pragma once

#include "pgr.h"

#include "CGameState.h"

#include "CCatmulRomSpline.h"

/** 
 * Display function callback for GLUT's glutDisplayFunc
 * 
 * clears color, depth and stencil buffer so 
 * draws each object to screen and also writes an identifier of 
 * drawn object for mouse picking purposes
 */
void Draw();

/** 
 * Timer function callback for GLUT's glutTimerFunc
 * 
 * calculates current frame time and time delta for fluid animations
 * updates each objects time member variable
 * 
 * Checks key map if any key is pressed. If yes, make an corresponding action.
 * 
 * If current scene view is set to flight or boat ride, set player's position.
 * 
 * Calls Timer function using glutTimerFunc and redisplays content of screen.
 * 
 * \param int value - integer passed by GLUT's glutTimerFunc
 */
void Timer(int value);

/** 
 * Windows reshape function for GLUT's glutReshapeFunc
 * 
 * changes viewport to accomodate the whole available windows space,
 * called whenever window is resized
 *  
 * \param int newWidth - new width for viewport
 * \param int newHeight - new height for viewport
 */
void Reshape(int newWidth, int newHeight);

/** 
 * Key press callback function for GLUT's glutKeyboardFunc
 * 
 * registers standard keys and reads mouse
 * x, y coordinate in windows space
 * 
 * for keys respond with action:
 * ESC - exits the application
 *   w - sets w's key map to true
 *   s - sets s's key map to true
 *   a - sets a's key map to true
 *   d - sets d's key map to true
 *   c - switches on/off mouse control of tilt/pan
 *   f - switches between 5 views
 *   r - switches between day/night light
 * 
 * \param unsigned char keyPressed - key indentifier
 * \param           int mouseX     - mouse cursor X coordinate in window space
 * \param           int mouseY     - mouse cursor Y coordinate in window space 
 */
void KeyPressed(unsigned char keyPressed, int mouseX, int mouseY);

/** 
 * Key release callback function for GLUT's glutKeyboardUpFunc 
 *     
 * called whenever a standard key is released. Inverse operation of 
 * function KeyPressed
 * @see KeyPressed(unsigned char keyPressed, int mouseX, int mouseY)
 * 
 * for keys repond with action:
 *	 w - sets w's key map to false
 *	 s - sets s's key map to false
 *	 a - sets a's key map to false
 *	 d - sets d's key map to false
 * 
 * \param unsigned char keyReleased - key indentifier 
 * \param           int mouseX      - mouse cursor X coordinate in window space
 * \param           int mouseY      - mouse cursor Y coordinate in window space
 */
void KeyReleased(unsigned char keyReleased, int mouseX, int mouseY);

/** 
 * Special key press callback for GLUT's glutSpecialFunc
 * 
 * handles callback for special keys (arrow keys). 
 * 
 * for keys respond with action:
 *     up arrow - sets up arrow's key map to true
 *   down arrow - sets down arrow's key map to true
 *   left arrow - sets left arrow's key map to true
 *  right arrow - sets right arrow's key map to true
 * 
 * \param specKeyPressed - key indentifier
 * \param         mouseX - mouse cursor X coordinate in window space
 * \param		  mouseY - mouse cursor Y coordinate in window space
 */
void SpecialKeyPressed(int specKeyPressed, int mouseX, int mouseY);

/** 
 * Special key release callback for GLUT's glutSpecialUpFunc
 * 
 * handles callback for special keys (arrow keys) release. 
 * 
 * for keys respond with action:
 *     up arrow - sets up arrow's key map to false
 *   down arrow - sets down arrow's key map to false
 *   left arrow - sets left arrow's key map to false
 *  right arrow - sets right arrow's key map to false
 * 
 * \param specKeyReleased - key indentifier
 * \param          mouseX - mouse cursor X coordinate in window space
 * \param          mouseY - mouse cursor Y coordinate in window space
 */
void SpecialKeyReleased(int specKeyReleased, int mouseX, int mouseY);

/** 
 * Mouse button press callback for GLUT's glutMouseFunc
 * 
 * handles event of mouse click button, check if user left clicked.
 * Reads object's identifier when left click is registered.
 * 
 * Check if the item that was clicked is interactible. If so, handle
 * event with corresponding action.
 * 
 * \param button - mouse button indentifier
 * \param  state - mouse button event (release/press)
 * \param mouseX - mouse cursor X coordinate in window space
 * \param mouseY - mouse cursor Y coordinate in window space
 */
void MousePressed(int button, int state, int mouseX, int mouseY);

/** 
 * Passive mouse motion callback for GLUT's glutPassiveMotionFunc
 * 
 * Checks if mouse cursor is not in the center of screen. Is so, calculate
 * delta in x and y axis. For x delta pan the camera and y delta tilt the camera.
 * 
 * After all mouse movement events were handled, recenter the mouse cursor to window center.
 * \param mouseX - mouse cursor X coordinate in window space
 * \param mouseY - mouse cursor Y coordinate in window space
 */
void MouseMotion(int mouseX, int mouseY);

/** 
 * Application class
 * 
 * initializes window and game content for user,
 * handles user input through GLUT's interface
 */
class CApplication {
private:
	/** 
	 * OpenGL and game content initialize  function 
	 * 
	 * initilizes OpenGL and game content
	 */
	void ApplicationInit();
public:
	/** 
	 * Window initilize function
	 * 
	 * initializes glut context and register function for user interaction,
	 * creates window
	 * 
	 * \param argc - argc given from main function that runs the application 
	 * \param argv - argv given from main function that runs the application
	 * \return zero on success and non-zero on failure
	 */
	int WindowInit(int argc, char* argv[]);
};

