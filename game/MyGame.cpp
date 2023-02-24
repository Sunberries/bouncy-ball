#include "stdafx.h"
#include "MyGame.h"

CMyGame::CMyGame(void) : 
	ball(100, 300, 50, 50, CColor::DarkMagenta(), 0), rect(400, 300, 300, 100, CColor::DarkGreen(),0)
	// to initialise more sprites here use a comma-separated list
{
	// TODO: add initialisation here
}

CMyGame::~CMyGame(void)
{
	// TODO: add destruction code here
}

/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)

void CMyGame::OnUpdate()
{
	Uint32 t = GetTime();

	// TODO: add the game update code here
	ball.Update(t);
	rect.Update(t);

	if (ball.GetX() >= GetWidth() - ball.GetWidth()/2 || ball.GetX() <= 0 + ball.GetWidth()/2)
	{
		ball.SetXVelocity((ball.GetXVelocity() * -1)*0.64);
		if (ball.GetX() >= GetWidth() - ball.GetWidth() / 2) ball.SetX(GetWidth() - ball.GetWidth()/2 -1);
		if (ball.GetX() <= 0 + ball.GetWidth() / 2) ball.SetX(0 + ball.GetWidth() / 2 + 1);
	}

	if (ball.GetY() >= GetHeight() - ball.GetHeight() / 2 || ball.GetY() <= 0 + ball.GetHeight() / 2)
	{
		ball.SetYVelocity((ball.GetYVelocity() * -1)*0.64);
		if (ball.GetY() >= GetHeight() - ball.GetHeight() / 2) ball.SetY(GetHeight() - ball.GetHeight() / 2 - 1);
		if (ball.GetY() <= 0 + ball.GetHeight() / 2) 
		{
			ball.SetY(0 + ball.GetHeight() / 2 + 1); 
			ball.SetXVelocity(ball.GetXVelocity()*0.64);
		}
	}

	ball.Accelerate(CVector(0, -10));

	CVector v = ball.GetVelocity() * GetDeltaTime() / 1000.f;
	CVector c = rect.GetPos() - ball.GetPos();
	int R = ball.GetWidth() / 2;
	int Y = rect.GetHeight() / 2;
	int X = rect.GetWidth() / 2;
	float f1;
	float f2;

	if (v.m_y < 0)
	{
		f1 = (c.m_y +Y + R) / v.m_y;
		f2 = (c.m_x - v.m_x * f1) / (X + R);
		if (f1 >= 0 && f1 <= 1 && f2 >= -1 && f2 <= 1)
		{
			ball.SetVelocity(0.64 * Reflect(ball.GetVelocity(), CVector(0, 1)));
		}
	}	

	if (v.m_y > 0)
	{
		f1 = (c.m_y - Y - R) / v.m_y;
		f2 = (c.m_x + v.m_x * f1) / (X + R);
		if (f1 >= 0 && f1 <= 1 && f2 >= -1 && f2 <= 1)
		{
			ball.SetVelocity(0.64 * Reflect(ball.GetVelocity(), CVector(0, -1)));
		}
	}

	if (v.m_x < 0)
	{
		f1 = (c.m_x + X + R) / v.m_x;
		f2 = (c.m_y - v.m_y * f1) / (Y + R);
		if (f1 >= 0 && f1 <= 1 && f2 >= -1 && f2 <= 1)
		{
			ball.SetVelocity(0.64 * Reflect(ball.GetVelocity(), CVector(1, 0)));
		}
	}

	if (v.m_x > 0)
	{
		f1 = (c.m_x - X - R) / v.m_x;
		f2 = (c.m_y + v.m_y * f1) / (Y + R);
		if (f1 >= 0 && f1 <= 1 && f2 >= -1 && f2 <= 1)
		{
			ball.SetVelocity(0.64 * Reflect(ball.GetVelocity(), CVector(-1, 0)));
		}
	}

	/*
	if (ball.HitTest(&rect))
	{
		if (ball.GetX() - R < rect.GetX() + X && ball.GetX() + R > rect.GetX() - X && ball.GetY() - R < rect.GetY() + Y && ball.GetY() + R > rect.GetY() - Y)
		{
			static CVector p = ball.GetPos();
			ball.SetPosition(p);
		}
	}
	*/
	

}

void CMyGame::OnDraw(CGraphics* g)
{
	// TODO: add drawing code here
	ball.Draw(g);
	rect.Draw(g);

	// this will print the game time
	*g << bottom << left << "Time elapsed: " << timetext(GetTime());
}

/////////////////////////////////////////////////////
// Game Life Cycle

// one time initialisation
void CMyGame::OnInitialize()
{
}

// called when a new game is requested (e.g. when F2 pressed)
// use this function to prepare a menu or a welcome screen
void CMyGame::OnDisplayMenu()
{
	StartGame();	// exits the menu mode and starts the game mode
}

// called when a new game is started
// as a second phase after a menu or a welcome screen
void CMyGame::OnStartGame()
{
	/*
	for (int i = 0; i <= rand() % 10; i++)
	{
		CSprite* baller = new CSprite;
		baller = ball.Clone();
		balls.push_back(baller);
	}
	*/
}

// called when a new level started - first call for nLevel = 1
void CMyGame::OnStartLevel(Sint16 nLevel)
{
}

// called when the game is over
void CMyGame::OnGameOver()
{
}

// one time termination code
void CMyGame::OnTerminate()
{
}

/////////////////////////////////////////////////////
// Keyboard Event Handlers

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_F4 && (mod & (KMOD_LALT | KMOD_RALT)))
		StopGame();
	if (sym == SDLK_SPACE)
		PauseGame();
	if (sym == SDLK_F2)
		NewGame();
}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
}


/////////////////////////////////////////////////////
// Mouse Events Handlers

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{
	ball.Accelerate(CVector(x - ball.GetX(), y - ball.GetY()));
}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y)
{
}
