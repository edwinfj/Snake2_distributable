#include "SnakeGame.h"


SnakeGame::SnakeGame(HINSTANCE hInstance, HWND hWindow)
{
	m_hInstance = hInstance;
	m_hWindow = hWindow;
}

SnakeGame::~SnakeGame(void)
{
	//do nothing
}

void SnakeGame::Init (void)
{
	m_kScreen.Init(m_hWindow);
	m_kGame.Start(m_hInstance, m_hWindow);
}

vnBool32 SnakeGame::Frame(void)
{
	/* Start rendering */
	m_kScreen.StartFrame ();

	/* Process and render game */
	if (m_kScreen.GetFPS () != 0)
	{
		if (vnFalse == m_kGame.Process (1 / (vnReal32)m_kScreen.GetFPS ()))
		{
			return vnFalse;
		}
		m_kGame.Render ();
	}

	/* Render particle system and end frame */
	m_kScreen.EndFrame ();

	return vnTrue;
}
