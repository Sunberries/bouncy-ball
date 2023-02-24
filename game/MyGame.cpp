#include "stdafx.h"
#include "MyGame.h"

CMyGame::CMyGame(void) :
	ball(100, 300, 50, 50, CColor::DarkMagenta(), 0), rect(400, 300, 200, 75, CColor::DarkGreen(), 0)
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
	for (CSprite* balls : ballList) balls->Update(t);

	if (ball.GetX() >= GetWidth() - ball.GetWidth() / 2 || ball.GetX() <= 0 + ball.GetWidth() / 2)
	{
		ball.SetXVelocity((ball.GetXVelocity() * -1) * 0.64);
		if (ball.GetX() >= GetWidth() - ball.GetWidth() / 2) ball.SetX(GetWidth() - ball.GetWidth() / 2 - 1);
		if (ball.GetX() <= 0 + ball.GetWidth() / 2) ball.SetX(0 + ball.GetWidth() / 2 + 1);
	}

	if (ball.GetY() >= GetHeight() - ball.GetHeight() / 2 || ball.GetY() <= 0 + ball.GetHeight() / 2)
	{
		ball.SetYVelocity((ball.GetYVelocity() * -1) * 0.64);
		if (ball.GetY() >= GetHeight() - ball.GetHeight() / 2) ball.SetY(GetHeight() - ball.GetHeight() / 2 - 1);
		if (ball.GetY() <= 0 + ball.GetHeight() / 2)
		{
			ball.SetY(0 + ball.GetHeight() / 2 + 1);
			ball.SetXVelocity(ball.GetXVelocity() * 0.64);
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
		f1 = (c.m_y + Y + R) / v.m_y;
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

	if (rand() % 30 == 0)
	{
		CSprite* balls = new CSpriteOval(rand() % 750 + 25, rand() % 550 + 25, 50, 50, CColor::DarkCyan(), 0);
		balls->SetDirection(CVector(ball.GetX() - balls->GetX(), ball.GetY() - balls->GetY()));
		balls->SetSpeed(100);
		ballList.push_back(balls);
	}

	for (CSprite* balls : ballList)
	{
		if (balls->GetX() < -50 || balls->GetX() > 850 || balls->GetY() < -50 || balls->GetY() > 650) balls->Delete();

		CVector v2 = balls->GetVelocity() * GetDeltaTime() / 1000.f;
		CVector c2 = rect.GetPos() - balls->GetPos();
		int R2 = balls->GetWidth() / 2;
		int Y2 = rect.GetHeight() / 2;
		int X2 = rect.GetWidth() / 2;
		float f3;
		float f4;

		if (v2.m_y < 0)
		{
			f3 = (c2.m_y + Y2 + R2) / v2.m_y;
			f4 = (c2.m_x - v2.m_x * f3) / (X2 + R2);
			if (f3 >= 0 && f3 <= 1 && f4 >= -1 && f4 <= 1)
			{
				balls->SetVelocity(Reflect(ball.GetVelocity(), CVector(0, 1)));
			}
		}

		if (v2.m_y > 0)
		{
			f3 = (c2.m_y - Y2 - R2) / v2.m_y;
			f4 = (c2.m_x + v2.m_x * f3) / (X2 + R2);
			if (f3 >= 0 && f3 <= 1 && f4 >= -1 && f4 <= 1)
			{
				balls->SetVelocity(Reflect(ball.GetVelocity(), CVector(0, -1)));
			}
		}

		if (v2.m_x < 0)
		{
			f3 = (c2.m_x + Y2 + R2) / v2.m_x;
			f4 = (c2.m_y - v2.m_y * f3) / (X2 + R2);
			if (f3 >= 0 && f3 <= 1 && f4 >= -1 && f4 <= 1)
			{
				balls->SetVelocity(Reflect(ball.GetVelocity(), CVector(1, 0)));
			}
		}

		if (v2.m_x > 0)
		{
			f3 = (c2.m_x - Y2 - R2) / v2.m_x;
			f4 = (c2.m_y + v2.m_y * f3) / (X2 + R2);
			if (f3 >= 0 && f3 <= 1 && f4 >= -1 && f4 <= 1)
			{
				balls->SetVelocity(Reflect(ball.GetVelocity(), CVector(-1, 0)));
			}
		}
	}

	ballList.delete_if(deleted);
}

void CMyGame::OnDraw(CGraphics* g)
{
	// TODO: add drawing code here
	ball.Draw(g);
	rect.Draw(g);
	for (CSprite* balls : ballList) balls->Draw(g);

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

void CMyGame::OnMouseMove(Uint16 x, Uint16 y, Sint16 relx, Sint16 rely, bool bLeft, bool bRight, bool bMiddle)
{
}

void CMyGame::OnLButtonDown(Uint16 x, Uint16 y)
{
	ball.Accelerate(CVector(x - ball.GetX(), y - ball.GetY()));
}

void CMyGame::OnLButtonUp(Uint16 x, Uint16 y)
{
}

void CMyGame::OnRButtonDown(Uint16 x, Uint16 y)
{
}

void CMyGame::OnRButtonUp(Uint16 x, Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x, Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x, Uint16 y)
{
}
