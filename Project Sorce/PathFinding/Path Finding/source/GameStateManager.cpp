#include "GameStateManager.h"


//IGameState
//-----------------------------------------------------------------------------
IGameState::IGameState( GameStateManager *pGameStateManger )
{
	m_gameStateManager = pGameStateManger;
}
IGameState::~IGameState()
{
	// left blank
}
void IGameState::Update( float dt )
{
	// left blank
}
void IGameState::Draw()
{
	// left blank
}
bool IGameState::UpdateBlocking()
{
		return false;
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//Game State Manager
//-----------------------------------------------------------------------------

// Constructor
GameStateManager::GameStateManager(Game* pGame)
	: m_pGame(pGame)
{
	
}

// Destructor
GameStateManager::~GameStateManager()
{
	
}

// Should be called each frame by the "Game" class
void GameStateManager::UpdateGameStates( float dt )
{
	ProcessCommands();

	for(unsigned int i = 0; i < m_gameStateStack.size(); i++)
	{
		bool UpdateBlocking = false;

		for(unsigned int j=i+1; j<m_gameStateStack.size(); j++)
		{
			if(m_gameStateStack[j]->UpdateBlocking() == true)
			{
				UpdateBlocking = true;
				break;
			}
		}

		if(UpdateBlocking == false)
		{
			m_gameStateStack[i]->Update( dt );
		}
		
	}
}

void GameStateManager::DrawGameStates()
{
	for(unsigned int i = 0; i < m_gameStateStack.size(); i++)
	{
		m_gameStateStack[i]->Draw();
	}
}

void GameStateManager::ProcessCommands()
{
	for(unsigned int i=0; i<m_commands.size(); i++)
	{
		if( m_commands[i].cmd == E_PUSH )
		{
			// Process the "Push" command
			//-------------------------------------------------------
			auto iter = m_availableStates.find( m_commands[i].name );
			if( iter != m_availableStates.end() )
			{
				m_gameStateStack.push_back( iter->second );
			}
			//-------------------------------------------------------
		}
		else if( m_commands[i].cmd == E_POP )
		{
			if( m_gameStateStack.size() > 0 )
			m_gameStateStack.pop_back();
		}
	}

	// now that all commands have been processed, clear the list for the next frame
	m_commands.clear();
}

// Used to manipulate the game state stack
void GameStateManager::SetState ( const char *name, IGameState *pState)
{
	auto iter = m_availableStates.find( name );
	if( iter != m_availableStates.end() )
	{
		delete iter->second;
	}

	m_availableStates[ name ] = pState;
}

void GameStateManager::PushState( const char *name )
{
	SCommand command;
	command.name = name;
	command.cmd = E_PUSH;

	m_commands.push_back( command );

}

void GameStateManager::PopState()
{
	SCommand command;
	command.cmd = E_POP;

	m_commands.push_back( command );
}