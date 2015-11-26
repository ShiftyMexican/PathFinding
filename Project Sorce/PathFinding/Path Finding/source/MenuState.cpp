#include "MenuState.h"
#include "MathLib.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include "Game.h"
#include "StaticSprite.h"

MenuState::MenuState(GameStateManager *pGameStateManager) : IGameState(pGameStateManager)
{
	m_pGame = pGameStateManager->GetGame();
	Load();

	m_clickCoolDown = 0.1f;
}

MenuState::~MenuState()
{  
	delete m_title;
	delete m_randomGen;
	delete m_MakeYourOwn;
}

void MenuState::Load()
{
	/// Title
	m_titleTexture = new Texture("Title for pathfinding game2.png");
	m_title = new StaticSprite(m_titleTexture);
	m_title->m_position = Vec2(m_pGame->GetWindowWidth() / 2.0f, m_pGame->GetWindowHeight() / 4.4f);
	m_title->Update(0);

	/// Random Generation button
	m_randomGenTexture = new Texture("Random gen button2.png");
	m_randomGen = new StaticSprite(m_randomGenTexture);
	m_randomGen->m_position = Vec2(m_pGame->GetWindowWidth() / 2.0f, m_pGame->GetWindowHeight() / 1.9f);
	m_randomGen->Update(0);

	/// Make Your own button
	m_makeYourOwnTexture = new Texture("Instuctions.png");
	m_MakeYourOwn = new StaticSprite(m_makeYourOwnTexture);
	m_MakeYourOwn->m_position = Vec2(m_pGame->GetWindowWidth() / 2.0f, m_pGame->GetWindowHeight() / 1.15f);
	m_MakeYourOwn->Transform()->Scale(Vec2(0.5f, 0.5f));
	m_MakeYourOwn->Update(0);
}

void MenuState::UnLoad()
{

}

void MenuState::Update( float dt )
{
	m_clickCoolDown -= dt;

	double xPosCursor, yPosCursor;
	glfwGetCursorPos(m_pGame->GetWindow(), &xPosCursor, &yPosCursor);

	/// Collisions for mouseover each button
	//-------------------------------------------------------------------------------------------
	cursorOverTopButton = false;
	if( xPosCursor > m_randomGen->m_position.x - m_randomGenTexture->GetWidth()		/ 2 && 
		xPosCursor < m_randomGen->m_position.x + m_randomGenTexture->GetWidth()		/ 2 &&
		yPosCursor > m_randomGen->m_position.y - m_randomGenTexture->GetHeight()	/ 2 &&
		yPosCursor < m_randomGen->m_position.y + m_randomGenTexture->GetHeight()	/ 2		)
	{
		cursorOverTopButton = true;
	}

	cursorOverBottomButton = false;
	if( xPosCursor > m_MakeYourOwn->m_position.x - m_makeYourOwnTexture->GetWidth()		/ 2 && 
		xPosCursor < m_MakeYourOwn->m_position.x + m_makeYourOwnTexture->GetWidth()		/ 2 &&
		yPosCursor > m_MakeYourOwn->m_position.y - m_makeYourOwnTexture->GetHeight()	/ 2 &&
		yPosCursor < m_MakeYourOwn->m_position.y + m_makeYourOwnTexture->GetHeight()	/ 2		)
	{
		cursorOverBottomButton = true;
	}
	//-------------------------------------------------------------------------------------------
	/// Making buttins bigger with mouse over
	//-------------------------------------------------------------------------------------------
	if(cursorOverTopButton == true)
	{
		m_randomGen->m_scale = Vec2( 1.1f, 1.1f );
		m_randomGen->Update(dt);
	}
	else if( cursorOverTopButton == false)
	{
		m_randomGen->m_scale = Vec2( 1.0f, 1.0f );
		m_randomGen->Update(dt);
	}
	//-------------------------------------------------------------------------------------------
	/// Sending to the next state if button is pressed
	//-------------------------------------------------------------------------------------------
	if(cursorOverTopButton == true && m_clickCoolDown <= 0 && glfwGetMouseButton(m_pGame->GetWindow(), GLFW_MOUSE_BUTTON_1))
	{
		m_gameStateManager->PopState();
		m_gameStateManager->PushState("RandomGenState");
		m_clickCoolDown = 0.5f;
	}

	//-------------------------------------------------------------------------------------------
}

void MenuState::Draw()
{

	m_pGame->GetSpriteBatch()->Begin();

	m_title->Draw(m_pGame->GetSpriteBatch());
	m_randomGen->Draw(m_pGame->GetSpriteBatch());
	m_MakeYourOwn->Draw(m_pGame->GetSpriteBatch());

	m_pGame->GetSpriteBatch()->End();
}