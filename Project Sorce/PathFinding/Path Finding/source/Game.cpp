#include "Game.h"
#include "GameStateManager.h"
#include "GLFW\glfw3.h"
#include "Node.h"
#include "SpriteBatch.h"
#include "MenuState.h"
#include "RandomGenState.h"


// constructor
Game::Game(unsigned int windowWidth, unsigned int windowHeight, const char *windowTitle, bool fullscreen)
{

	glfwWindowHint(GLFW_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_VERSION_MINOR, 0);

	glfwInit();

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	windowWidth = (fullscreen) ? mode->width : windowWidth;
	windowHeight = (fullscreen) ? mode->height : windowHeight;


	m_pWindow = glfwCreateWindow(windowWidth, windowHeight, windowTitle, (fullscreen) ? glfwGetPrimaryMonitor() : NULL, NULL);

	glfwMakeContextCurrent(m_pWindow);

	//----------------------------------------------------------------------------

	m_gameOver		= false;
	m_windowWidth	= windowWidth;
	m_windowHeight	= windowHeight;
	m_currentTime	= glfwGetTime();
	m_lastTime		= m_currentTime;
	m_deltaTime		= 0.0f;

	m_gameStateManager = new GameStateManager(this);
	m_spriteBatch = SpriteBatch::Create( m_gameStateManager->GetGame(), SpriteBatch::NON_IMIDIATE);

	auto menuState		= new MenuState		(m_gameStateManager);
	auto randomGenState = new RandomGenState(m_gameStateManager);

	// store for destruction later
	m_CreatedGameStates.push_back(menuState);
	m_CreatedGameStates.push_back(randomGenState);

	m_gameStateManager->SetState("MenuState", menuState );
	m_gameStateManager->SetState("RandomGenState", randomGenState);
	m_gameStateManager->PushState( "MenuState" );
}

// destructor
Game::~Game()
{


	delete m_gameStateManager;

	for(auto i = m_CreatedGameStates.begin(); i != m_CreatedGameStates.end(); ++i)
	{
		delete *i;
	}

	m_CreatedGameStates.clear();

	glfwTerminate();
}

void Game::Load()
{

}
	
void Game::UnLoad()
{

}

// returns when the main game loop has finished
void Game::RunGame()
{
	
	//Load();

	while( !m_gameOver )
	{
		
		// calculate deltaTime
		m_lastTime		= m_currentTime;
		m_currentTime	= glfwGetTime();
		m_deltaTime		= (float)m_currentTime - (float)m_lastTime;

		if( m_deltaTime > 1.0f / 60.0f )
			m_deltaTime = 1.0f / 60.0f;

		// clears the back buffer to the value set with glClearColor(...);
		glClear(GL_COLOR_BUFFER_BIT);

		Update(m_deltaTime);
		Draw();

		// swaps the front and back buffers
		glfwSwapBuffers( m_pWindow );

		// handles window events, and calls aproprate callback
		// that have been provided to glfw, eg keyboard or mouse callback functions
		glfwPollEvents();

		m_gameOver = m_gameOver | glfwWindowShouldClose(m_pWindow);

		if( glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE))
			Quit();
	}

	UnLoad();

	
}

// called each frame from within RunGame()
void Game::Update(float deltaTime)
{
	m_gameStateManager->UpdateGameStates(deltaTime);
}

// called each frame from within RunGame()
void Game::Draw()
{
	m_gameStateManager->DrawGameStates();
}