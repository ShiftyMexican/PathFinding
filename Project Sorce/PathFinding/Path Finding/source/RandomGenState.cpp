#include "Mathlib.h"
#include "Texture.h"
#include "Game.h"
#include "StaticSprite.h"
#include "Node.h"
#include "SpriteBatch.h"
#include "Tile.h"
#include "RandomGenState.h"
#include <iostream>
#include "PhysicsObject.h"

RandomGenState::RandomGenState(GameStateManager *pGameStateManager) : IGameState(pGameStateManager)
{
	m_pGame = pGameStateManager->GetGame();
	m_spriteBatch = SpriteBatch::Create( m_gameStateManager->GetGame(), SpriteBatch::NON_IMIDIATE);

	m_tileTexture = new Texture("laserBlue03.png");
	m_aiTexture = new Texture("ufoRed.png");
	m_ai = nullptr;
	m_mouseClicked		= false;
	m_rightClicked		= false;
	m_colourSelected	= false;
	m_startSelected		= false;
	m_endSelected		= false;
	m_tilesOnScreen		= false;
	m_pathFound			= false;
	m_leftShiftPressed	= false;
	m_endFound			= false;
	m_started			= false;
	m_firstStart		= false;
	m_aStarSearch		= false;
	m_newRightClick		= false;
	m_dijkstrasDone		= false;

	m_howManyTiles = 0;
	m_howManyEndTiles = 0.0f;
	m_coolDown = 0.2f;

	/// Randomly generating nodes on the screen
	if( m_tilesOnScreen == false )
	{
		Generate();
	}	

	m_ai = new AI(m_aiTexture);	
	m_ai->Transform()->Translate(Vec2(m_tiles.front()->GetLocalTransform().GetTranslation()));
	m_ai->GetPhysics()->SetPosition(m_tiles.front()->GetLocalTransform().GetTranslation());
}

RandomGenState::~RandomGenState()
{
	for(unsigned int i = 0; i < m_tiles.size(); i++)
	{
		if( m_tiles[i] != nullptr)
		{
			m_tiles[i] = nullptr;
			delete m_tiles[i];
		}
	}
}

void RandomGenState::Update( float deltaTime )
{
	m_coolDown -= deltaTime;

	if(!m_tilesOnScreen)
		Generate();

	double xPosMouse, yPosMouse;
	glfwGetCursorPos(m_pGame->GetWindow(), &xPosMouse, &yPosMouse);

	/// Returns true on mouse click and on left shift press--------------------
	if( glfwGetMouseButton(m_pGame->GetWindow(), GLFW_MOUSE_BUTTON_1))
		m_mouseClicked = true;
	else
		m_mouseClicked = false;

	if( glfwGetMouseButton(m_pGame->GetWindow(), GLFW_MOUSE_BUTTON_RIGHT))
	{
		m_rightClicked = true;
		//m_newRightClick = true;
	}
	else
		m_rightClicked = false;

	if( glfwGetKey(m_pGame->GetWindow(), GLFW_KEY_LEFT_SHIFT))
	{
		m_leftShiftPressed = true;
	}
	
	/// Update for tiles-------------------------------------------------------
	for(auto itr = m_tiles.begin(); itr < m_tiles.end(); itr++)
	{
		(*itr)->Update( deltaTime );
	}

	/// Code for clicking on tiles to create start points----------------------
	for(auto itr = m_tiles.begin(); itr < m_tiles.end(); itr++)
	{
		if(TileClicked((*itr), Vec2((float)xPosMouse, (float)yPosMouse)))
		{
			(*itr)->m_pressed = true;
		}
		else
		{
			(*itr)->m_pressed = false;
		}

		if((*itr)->m_pressed == true && m_rightClicked == true && m_coolDown < 0.0f)
		{
			dijksraPoints.clear();
			m_possibleEnds.clear();

			for(int i = 0; i != m_tiles.size(); i++)
				{
					m_tiles[i]->ChangeColour(1.0f, 1.0f, 1.0f);
				}
			PopulateDijkstras();

			m_end = (*itr);
			m_possibleEnds.push_back( (*itr) );
			(*itr)->ChangeColour(0.0f, 1.0f, 1.0f);
			std::cout << "End Node Is: " << (*itr)->GetId() << std::endl;
			m_howManyEndTiles += 1;
			m_endSelected  = true;
			m_coolDown = 0.2f;
			outPath.clear();
			m_dijkstrasDone = false;
			m_endFound = false;
			SetNewStart();
			AStarPath(m_start, m_end, outPath );
			m_aStarSearch = true;

		}
	}
	

	/// Adding forces
	Tile* tempStart = nullptr;
	if(outPath.size() != 0)
	{
		{
		
			Vec2 velocity = m_ai->GetPhysics()->GetVelocity();
			velocity.Normalize();

			Vec2 headingPos = m_ai->GetPhysics()->GetPosition() + (velocity * 5.0f);

			Vec2 dir = outPath.back()->GetLocalTransform().GetTranslation() - headingPos;
			dir.Normalize();

			m_ai->AddForce(dir * 100);
		
			if(  m_ai->GetLocalTransform().GetTranslation().x <= outPath.back()->GetLocalTransform().GetTranslation().x + 10 &&
				 m_ai->GetLocalTransform().GetTranslation().x >= outPath.back()->GetLocalTransform().GetTranslation().x - 10 &&
				 m_ai->GetLocalTransform().GetTranslation().y <= outPath.back()->GetLocalTransform().GetTranslation().y + 10 &&
				 m_ai->GetLocalTransform().GetTranslation().y >= outPath.back()->GetLocalTransform().GetTranslation().y - 10 )
			{
				outPath.pop_back();
			}
		}
	
		if( outPath.size() == 0)
		{
			m_endFound = true;
			m_end->Transform()->SetScale(0.2f, 0.2f);
			m_end->ChangeColour(1.0f, 1.0f, 1.0f);
			m_start->ChangeColour(1.0f, 1.0f, 1.0f);
			m_endSelected = false;
			m_possibleEnds.clear();
			for(int i = 0; i < m_tiles.size(); i++)
			{
				m_tiles[i]->SetParent(nullptr);
			}
			
			if(m_dijkstrasDone == false)
			{
				SetNewStart();
				Dijkstraspath(m_start, outPath );
				m_aStarSearch = true;
				m_endFound = false;
				m_dijkstrasDone = true;
			
			}

			if(m_endFound == true)
			{
				if(m_dijkstrasDone)
				{
					SetNewStart();
					AStarPath(m_start, m_tiles[rand() % (m_tiles.size() - 1)], outPath);
					m_aStarSearch = false;
					dijksraPoints.clear();
					for(int i = 0; i != m_tiles.size(); i++)
					{
						m_tiles[i]->ChangeColour(1.0f, 1.0f, 1.0f);
					}
				}				
			}	
		}
	}

	if(m_ai != nullptr)
		m_ai->Update( deltaTime );	

	SetNewStart();

	m_rShiftPressed = glfwGetKey(m_pGame->GetWindow(), GLFW_KEY_RIGHT_SHIFT);

}

void RandomGenState::Draw()
{
	m_pGame->GetSpriteBatch()->Begin();

	/// Drawing the lines between tiles.
	for(auto itr = m_tiles.begin(); itr < m_tiles.end(); itr++)
	{
		/// Pretty Colours
		if( m_colourSelected == false)
		{
			m_lineRed	= rand() % 100 / 100.0f;
			m_lineGreen = rand() % 100 / 100.0f;
			m_lineBlue	= rand() % 100 / 100.0f;
			m_colourSelected = true;
		}
		
		for(auto iter = (*itr)->m_neighbours.begin(); iter != (*itr)->m_neighbours.end(); iter++)
		{
			if((*itr)->m_neighbours.size() < 5 && (*itr)->m_neighbours.size() > 0 )
			{
				m_spriteBatch->DrawLine((*itr)->Transform()->GetTranslation(), 
										(*iter)->Transform()->GetTranslation(),
										m_lineRed, m_lineGreen, m_lineBlue);
			}
			
			if( (*itr)->m_active == true )
			{
				m_spriteBatch->DrawLine((*itr)->Transform()->GetTranslation(), 
										(*iter)->Transform()->GetTranslation(),
										0.0f, 1.0f, 0.0f);
			}
		}
	}
	
	for(auto itr = m_tiles.begin(); itr < m_tiles.end(); itr++)
	{
		if((*itr) != nullptr)
			(*itr)->Draw( m_spriteBatch );
	}

	if( m_aStarSearch == true )
	{
		for(unsigned int i=0; i<outPath.size()-1 && outPath.size() > 1; i++)
		{
			Vec2 p1 = outPath[i]->Transform()->GetTranslation();
			Vec2 p2 = outPath[i+1]->Transform()->GetTranslation();
			m_spriteBatch->DrawLine( p1, p2, 1.0f, 0.0f, 0.0f );
		
		}
	}

	m_ai->Draw( m_spriteBatch );

	m_pGame->GetSpriteBatch()->End();
}

void RandomGenState::AddTile(float xPos, float yPos)
{
	Tile *tile = new Tile(m_tileTexture, m_howManyTiles, 5.0f, 5.0f);
	tile->Transform()->Translate(Vec2(xPos, yPos));
	m_tiles.push_back( tile );
	m_howManyTiles += 1;
}

bool RandomGenState::TileClicked(Tile* _tile, const Vec2& _pos)
{
	if(	_pos.x > _tile->Transform()->GetTranslation().x - 5 &&
		_pos.x < _tile->Transform()->GetTranslation().x + 5 &&
		_pos.y > _tile->Transform()->GetTranslation().y - 5 &&
		_pos.y < _tile->Transform()->GetTranslation().y + 5 )
		return true;
	else
		return false;

}

void RandomGenState::Generate()
{
	for(int x = 0; x < TILE_X_RAND; x++)
	{
		for(int y = 0; y < TILE_Y_RAND; y++)
		{
			m_xOffset = rand() % 40;
			m_yOffset = rand() % 40;
	
			float xPos = x * (((float)m_pGame->GetWindowWidth()  - 30)/ TILE_X_RAND) + m_xOffset;
			float yPos = y * (((float)m_pGame->GetWindowHeight() - 30)/ TILE_Y_RAND) + m_yOffset;
	
			AddTile(xPos + 25, yPos + 20);
		}
	}

	/// Adds Tiles to the neighbours list.
	for(unsigned int i = 0; i < m_tiles.size(); i++)
	{
		for(unsigned int j = 0; j < m_tiles.size(); j++)
		{
			Vec2 lengthBetween = m_tiles[j]->Transform()->GetTranslation();
			lengthBetween.x -= m_tiles[i]->Transform()->GetTranslation().x;
			lengthBetween.y -= m_tiles[i]->Transform()->GetTranslation().y;

			if(j != i)
			{
				if(m_tiles[i]->m_neighbours.size() < 4)
				{
					if(m_tiles[j]->m_neighbours.size() < 4)
					{
						if(lengthBetween.Len() < 90.0f)
						{
							m_tiles[j]->m_neighbours.push_back(m_tiles[i]);
							m_tiles[i]->m_neighbours.push_back(m_tiles[j]);
						}
					}
				}
			}
		}
	}

	m_tilesOnScreen = true;
	m_startSelected = false;
	m_endSelected = false;
	m_colourSelected = false;
}

void RandomGenState::Dijkstraspath( Tile* start, std::vector< Tile* > &outPath )
{
	m_start = start;
	
	bool endFoundHere = false;
	
	m_priorityList.clear();
	m_closedList.clear();
	for(auto itr = m_tiles.begin(); itr != m_tiles.end(); itr++)
	{
		(*itr)->SetParent(nullptr);
		(*itr)->SetGScore(999999.0f);
	}
	
	Tile* currentTile = start;
	m_priorityList.push_back( currentTile );
	currentTile->SetParent(currentTile);
	currentTile->SetGScore(0.0f);
	
	while(m_priorityList.empty() != true)
	{
		currentTile = m_priorityList.back();
		m_priorityList.pop_back();
		m_closedList.push_back( currentTile );
	
		/// Processing of Current nodes.
		for(auto itr = currentTile->m_neighbours.begin(); itr != currentTile->m_neighbours.end(); itr++)
		{
			bool canAddNode = true;
	
			///Checking for node on closed list
			for(auto iter2 = m_closedList.begin(); iter2 != m_closedList.end(); iter2++)
			{
				if( (*itr) == (*iter2))
				{
					canAddNode = false;
					break;
				}
			}
	
			///Checking for node on open list
			for(auto iter2 = m_priorityList.begin(); iter2 != m_priorityList.end(); iter2++)
			{
				if( (*itr) == (*iter2))
				{
					canAddNode = false;
					break;
				}
			}
	
			if( canAddNode )
			{
				m_priorityList.push_back((*itr));
			}
		}
	
		currentTile->m_active = true;
	
		for(auto itr = currentTile->m_neighbours.begin(); itr != currentTile->m_neighbours.end(); itr++)
		{
			if((*itr)->m_active == true )
				continue;
	
	
			/// Calculation for G Score
			float distanceBetweenTiles =  Vec2(currentTile->Transform()->GetTranslation().x - (*itr)->Transform()->GetTranslation().x, 
											   currentTile->Transform()->GetTranslation().y - (*itr)->Transform()->GetTranslation().y).Len();
	
			float tempGValue = currentTile->GetGScore() + distanceBetweenTiles;
	
			(*itr)->SetGScore(tempGValue);
	
			(*itr)->SetParent(currentTile);
	
			//If end node is found--------------------------------------------
			bool foundAnEndNode = false;
			for(unsigned int i=0; i<dijksraPoints.size(); i++)
			{
				if((*itr) == dijksraPoints[i])
				{
					foundAnEndNode = true;
					break;
				}
			}
			if(foundAnEndNode)
			{
		
				endFoundHere = true;

				Tile* current = (*itr);
			
				while( current != start )
				{	
					outPath.push_back( current );
					current = current->GetParent();
				}

				break;
			}
			//-----------------------------------------------------------------


			(*itr)->m_active = true;

			m_priorityList.sort( [](Tile* const a, Tile* const b)
			{
				if(a->GetGScore() == b->GetGScore() )
					return a->GetId() > b->GetId();

				return a->GetGScore() > b->GetGScore();
			});

		}

		if(endFoundHere == true)
			break;
	}
		return;
}

void RandomGenState::AStarPath( Tile* start, Tile* end, std::vector< Tile* > &outPath )
{
	m_start = start;
	m_end = end;

	bool endFound = false;

	m_closedList.clear();
	m_priorityList.clear();
	if( outPath.size() != 0)
		outPath.clear();

	for(auto itr = m_tiles.begin(); itr != m_tiles.end(); itr++)
	{
		(*itr)->SetParent(nullptr);
		(*itr)->SetGScore(999999.0f);
		(*itr)->SetHScore(999999.0f);
		(*itr)->SetFScore(999999.0f);
	}

	Tile* currentTile = start;
	m_priorityList.push_back( currentTile );
	currentTile->SetParent(currentTile);
	currentTile->SetGScore(0.0f);

	while(m_priorityList.empty() != true)
	{
		currentTile = m_priorityList.back();
		m_priorityList.pop_back();
		m_closedList.push_back( currentTile );

		if(currentTile == end)
		{
			//endFound = true;
		
			Tile* current = end;
			
			while( current->GetParent() != start)
			{	
				outPath.push_back( current );
				current = current->GetParent();
			}

			outPath.push_back( current );
			outPath.push_back( current->GetParent() );
			break;
		}
		//-----------------------------------------------------------------

		/// Processing of Current nodes.
		for(auto itr = currentTile->m_neighbours.begin(); itr != currentTile->m_neighbours.end(); itr++)
		{
			bool canAddNode = true;

			float distanceBetweenTiles	=  Vec2(currentTile->Transform()->GetTranslation().x - (*itr)->Transform()->GetTranslation().x, 
												currentTile->Transform()->GetTranslation().y - (*itr)->Transform()->GetTranslation().y).Len();

			/// Calculations for H Score
			float heuristic				= Vec2(currentTile->Transform()->GetTranslation().x - end->Transform()->GetTranslation().x, 
											   currentTile->Transform()->GetTranslation().y - end->Transform()->GetTranslation().y).Len();

			heuristic = heuristic * heuristic;

			float tempGValue = currentTile->GetGScore() + distanceBetweenTiles;
			float tempHeuristic = tempGValue + heuristic;

			///Checking for node on closed list
			for(auto iter2 = m_closedList.begin(); iter2 != m_closedList.end(); iter2++)
			{
				if( (*itr) == (*iter2))
				{
					canAddNode = false;
					break;
				}
			}

			///Checking for node on open list
			for(auto iter2 = m_priorityList.begin(); iter2 != m_priorityList.end(); iter2++)
			{
				if( (*itr) == (*iter2))
				{
					canAddNode = false;
					break;
				}
			}

			if( canAddNode )
			{
				m_priorityList.push_back((*itr));
				(*itr)->SetGScore( tempGValue );
				(*itr)->SetHScore( heuristic );
				(*itr)->SetFScore( tempGValue + heuristic );
				(*itr)->SetParent( currentTile );
			}
			
		}

	    //currentTile->m_active = true;

		m_priorityList.sort( [](Tile* const a, Tile* const b)
		{
			if(a->GetFScore() == b->GetFScore())
				return a->GetId() > b->GetId();
		
			return a->GetFScore() > b->GetFScore();
		});
	}

	return;
}

void RandomGenState::ResetState()
{
	//for(auto itr = m_tiles.begin(); itr < m_tiles.end(); itr++)
	//	{
	//		(*itr)->m_neighbours.clear();
	//		m_tilesOnScreen = false;
	//	}
	//	m_tiles.clear();
		m_howManyTiles = 0;
		outPath.clear();
		m_howManyEndTiles = 0;
		m_possibleEnds.clear();
		m_startSelected = false;
		m_endSelected = false;
		m_leftShiftPressed = false;
}

void RandomGenState::SetNewStart()
{
	for(unsigned int i = 0; i < m_tiles.size(); i++)
	{
		m_tiles[i]->m_active = false;

		if(  m_ai->GetLocalTransform().GetTranslation().x <= m_tiles[i]->GetLocalTransform().GetTranslation().x + 10 &&
			 m_ai->GetLocalTransform().GetTranslation().x >= m_tiles[i]->GetLocalTransform().GetTranslation().x - 10 &&
			 m_ai->GetLocalTransform().GetTranslation().y <= m_tiles[i]->GetLocalTransform().GetTranslation().y + 10 &&
			 m_ai->GetLocalTransform().GetTranslation().y >= m_tiles[i]->GetLocalTransform().GetTranslation().y - 10 )
		{
			m_start = m_tiles[i];
			std::cout << m_start->GetId() << std::endl;
			m_startSelected = true;
		}
	}
}

void RandomGenState::PopulateDijkstras()
{
	if(dijksraPoints.size() < 2)
	{
		for(int i = 0; i < 3; i++)
		{
			Tile* dijkstrasEnds;
			dijkstrasEnds = m_tiles[rand() % (m_tiles.size() - 1)];
			dijksraPoints.push_back(dijkstrasEnds);
			dijkstrasEnds->ChangeColour(0.0f, 1.0f, 1.0f);
		}
	}
}