#include "AIE.h"
#include <iostream>
#include "math.h"

using namespace std;

int p1HS;
int p2HS;

bool isGameRunning = true;

const int screenWidth = 672;
const int screenHeight = 780;
unsigned int menu;
unsigned int scoreBoard;
unsigned int background;

int HighScore;

int paddle1;
int paddle2;
int ball;
int Score1 = 0; 
int Score2 = 0;

enum GAMESTATES
{
	eMAIN_MENU,
	eGAMEPLAY,
	eHIGHSCORES,
	eEND
};

//Paddles
//=========================================


struct PlayerOne
{
	const int paddleWidth = 20;
	const int paddleHeight = 80;
	float fPlayerX = 80.f;
	float fPlayerY = screenHeight * 0.5f;
	float p1topLeftX;
	float p1topRightX;
	float p1lowLeftX;
	float p1lowRightX;
	float p1topLeftY;
	float p1topRightY;
	float p1lowLeftY;
	float p1lowRightY;
};
PlayerOne p1;

struct PlayerTwo
{
	const int paddle2Width = 20;
	const int paddle2Height = 80;
	float fPlayer2X = 592.f;
	float fPlayer2Y = screenHeight * 0.5f;
	float p2topLeftX;
	float p2topRightX;
	float p2lowLeftX;
	float p2topLeftY;
	float p2topRightY;
	float p2lowLeftY;
	float p2lowRightY;
	float p2lowRightX;
};
PlayerTwo p2;
//=========================================

//Ball dimensions and position(s)
//........................................
struct Balle
{
	const int ballWidth = 32;//32
	const int ballHeight = 32;//32

	float fBallX;// = 256.f;
	float fBallY;//= screenHeight * 0.5f
	float ballSpeedX;//= 1.f
	float ballSpeedY;//= 1.f
	float ballDirection;
	float radius = 16;

	float topLeftY;
	float topLeftX;
	float topRightX;
	float topRightY;
	float lowLeftX;
	float lowLeftY;
	float lowRightX;
	float lowRightY;
};
//........................................
Balle balle;

//Player Paddle Floats (placement)
//=========================================



//=========================================

int score;

void UpdateMainMenu()
{
	if (IsKeyDown('Q'))
	{
		isGameRunning = false;
	}
	DrawSprite(menu);
	menu = CreateSprite("./images/iPong.png", screenWidth, screenHeight, true);
	MoveSprite(menu, screenWidth * 0.5f, screenHeight * 0.5f);
}
void UpdateScoreBoard()
{
	DrawSprite(scoreBoard);
	//DrawString(pkInsertCoins, iScreenWidth * 0.37f, iScreenHeight * 0.5f, 0.75f);
	//DrawString(pkCredit, iScreenWidth * 0.25f, iScreenHeight * 0.4f, 0.7f);
	scoreBoard = CreateSprite("./images/HighPongs.png", screenWidth, screenHeight, true);
	MoveSprite(scoreBoard, screenWidth * 0.5f, screenHeight * 0.5f);
}

void UpdateGameState(float a_fDeltaTime)
{
	DrawSprite(background);
	background = CreateSprite("./images/Gamescreen.png", screenWidth, screenHeight, true);
	MoveSprite(background, screenWidth * 0.5f, screenHeight * 0.5f);
	MoveSprite(paddle1, p1.fPlayerX, p1.fPlayerY);
	MoveSprite(paddle2, p2.fPlayer2X, p2.fPlayer2Y);
	MoveSprite(ball, balle.fBallX, balle.fBallY);
	DrawSprite(paddle1);
	DrawSprite(paddle2);
	DrawSprite(ball);
	//===========================================================
	// Line from Sno Isle for ball movement/direction. May help |
	//direction.X = (float)Game.RNG.NextDouble() * 2 - 1;       |
	//direction.Y = (float)Game.RNG.NextDouble() * 2 - 1;       |     
	//===========================================================

	//Ball points
	//ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
	balle.topLeftX = balle.fBallX - balle.ballWidth * .5f;
	balle.topLeftY = balle.fBallY + balle.ballHeight * .5f;
	//----------------------------------------------------
	balle.topRightX = balle.fBallX + balle.ballWidth * .5f;
	balle.topRightY = balle.fBallY + balle.ballHeight * .5f;
	//-----------------------------------------------------
	balle.lowRightX = balle.fBallX + balle.ballWidth * .5f;
	balle.lowRightY = balle.fBallY - balle.ballHeight * .5f;
	//-----------------------------------------------------
	balle.lowLeftX = balle.fBallX - balle.ballWidth * .5f;
	balle.lowLeftY = balle.fBallY - balle.ballHeight * .5f;
	//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo

	//Paddle points
	//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	p1.p1topLeftX = p1.fPlayerX - p1.paddleWidth * .5f;
	p1.p1topLeftY = p1.fPlayerY + p1.paddleHeight * .5f;
	//----------------------------------------------------
	p1.p1topRightX = p1.fPlayerX + p1.paddleWidth * .5f;
	p1.p1topRightY = p1.fPlayerY + p1.paddleHeight * .5f;
	//-----------------------------------------------------
	p1.p1lowRightX = p1.fPlayerX + p1.paddleWidth * .5f;
	p1.p1lowRightY = p1.fPlayerY - p1.paddleHeight * .5f;
	//-----------------------------------------------------
	p1.p1lowLeftX = p1.fPlayerX - p1.paddleWidth * .5f;
	p1.p1lowLeftY = p1.fPlayerY - p1.paddleHeight * .5f;
	//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

	//Paddle2 points
	//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	p2.p2topLeftX = p2.fPlayer2X - p2.paddle2Width * .5f;
	p2.p2topLeftY = p2.fPlayer2Y + p2.paddle2Height * .5f;
	//----------------------------------------------------
	p2.p2topRightX = p2.fPlayer2X + p2.paddle2Width * .5f;
	p2.p2topRightY = p2.fPlayer2Y + p2.paddle2Height * .5f;
	//-----------------------------------------------------
	p2.p2lowRightX = p2.fPlayer2X + p2.paddle2Width * .5f;
	p2.p2lowRightY = p2.fPlayer2Y - p2.paddle2Height * .5f;
	//-----------------------------------------------------
	p2.p2lowLeftX = p2.fPlayer2X - p2.paddle2Width * .5f;
	p2.p2lowLeftY = p2.fPlayer2Y - p2.paddle2Height * .5f;
	//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

	//Movement Player 1
	if (IsKeyDown('S'))
	{
		p1.fPlayerY -= .8f;
		if (p1.fPlayerY < 40)
		{
			p1.fPlayerY = 40;
		}
	}

	if (IsKeyDown('W'))
	{
		p1.fPlayerY += .8f;
		if (p1.fPlayerY > 740)
		{
			p1.fPlayerY = 740;
		}

	}
	MoveSprite(paddle1, p1.fPlayerX, p1.fPlayerY);

	balle.fBallY += balle.ballSpeedY;
	balle.fBallX += balle.ballSpeedX;

	// bottom
	if (balle.fBallY > 16)
	{
		//fBallY = 764;
		balle.ballSpeedY = -balle.ballSpeedY;
	}
	// top
	if (balle.fBallY < 764)
	{
		//fBallY = 16;
		//fBallY - ballSpeed;
		balle.ballSpeedY = -balle.ballSpeedY;
	}
	if (balle.fBallX < 16)
	{
		Score2 += 1;
		balle.fBallX = screenWidth / 2;
		//balle.ballSpeedX = -balle.ballSpeedX;
	}
	if (balle.fBallX > 642)
	{
		Score1 += 1;
		balle.fBallX = screenWidth / 2;
		//balle.ballSpeedX = -balle.ballSpeedX;
	}

	 //get distance between the ball and the paddle
	
	float Distance = sqrt(pow(balle.fBallX - p1.fPlayerX, 2) + pow(balle.fBallY - p1.fPlayerY, 2));
	 //check if dist < radius of the ball
	
	if (Distance < balle.radius)
	{
		
		balle.ballSpeedX = -balle.ballSpeedX;
	}
	float Distance2 = sqrt(pow(balle.fBallX - p2.fPlayer2X, 2) + pow(balle.fBallY - p2.fPlayer2Y, 2));
	
	 //check if dist < radius of the ball
	
	if (Distance2 < balle.radius)
	{
		
		balle.ballSpeedX = -balle.ballSpeedX;
	}
	
	//AABB attempt
	//if (p1.p1topRightX > balle.topLeftX &&
	//	p1.p1lowRightX > balle.lowLeftX)
	//{
	//	if (p1.p1lowRightY > balle.lowLeftY &&
	//		p1.p1topRightY > balle.topLeftY)
	//	{
	//		//balle.ballSpeedY = -balle.ballSpeedY;
	//		balle.ballSpeedX = -balle.ballSpeedX;
	//	}

	//}
	//if (p1.p1topLeftX > balle.topRightX &&
	//	p1.p1lowLeftX > balle.lowRightX)
	//{
	//	if (p1.p1lowLeftY > balle.lowRightY &&
	//		p1.p1topLeftY > balle.topRightY)
	//	{
	//		//balle.ballSpeedY = -balle.ballSpeedY;
	//		balle.ballSpeedX = -balle.ballSpeedX;
	//	}

	//}
	//if (p1.p1lowLeftX > balle.lowRightX &&
	//	p1.p1topLeftX > balle.topRightX)
	//{
	//	if (p1.p1topLeftY > balle.topRightY &&
	//		p1.p1lowLeftY > balle.lowRightY)
	//	{
	//		//balle.ballSpeedY = -balle.ballSpeedY;
	//		balle.ballSpeedX = -balle.ballSpeedX;
	//	}

	//}
	//if (p2.p2topLeftX < balle.topRightX &&
	//	p2.p2lowLeftX < balle.lowRightX)
	//{
	//	if (p2.p2lowLeftY < balle.lowRightY &&
	//		p2.p2topLeftY < balle.topRightY)
	//	{
	//		//balle.ballSpeedY = -balle.ballSpeedY;
	//		balle.ballSpeedX = -balle.ballSpeedX;
	//	}

	//}


		std::cout << "X = " << balle.fBallX << endl;
	std::cout << "Y = " << balle.fBallY << endl;

	MoveSprite(ball, balle.fBallX, balle.fBallY);
	//Movement Player 2
	if (IsKeyDown('L'))
	{
		p2.fPlayer2Y -= .8f;
		if (p2.fPlayer2Y < 40)
		{
			p2.fPlayer2Y = 40;
		}

	}

	if (IsKeyDown('O'))
	{
		p2.fPlayer2Y += .8f;
		if (p2.fPlayer2Y > 740)
		{
			p2.fPlayer2Y = 740;
		}

	}
	

	MoveSprite(paddle2, p2.fPlayer2X, p2.fPlayer2Y);
	char Scores1[10];
	itoa(Score1, Scores1, 10);
	DrawString(Scores1, screenWidth * 0.025f, screenHeight - 40);
	DrawString("SCORE < 1 >", screenWidth * 0.025f, screenHeight - 2);
	char Scores2[10];
	itoa(Score2, Scores2, 10);
	DrawString(Scores2, screenWidth * 0.7f, screenHeight - 40);
	DrawString("SCORE < 2 >", screenWidth * .7f, screenHeight - 3);

	ClearScreen();
}
char HS1[100];
char HS2[100];
int main( /*int argc, char* argv[]*/ )
{	
    Initialise(screenWidth, screenHeight, false, "Pong");
    //
    SetBackgroundColour(SColour(237, 237, 237, 100));
	
	//ball struct declarations
	//______________________________________
	
	balle.fBallX = 256.f;
	balle.fBallY = screenHeight * 0.5f;
	balle.ballSpeedX = .5f;
	balle.ballSpeedY = .5f;
	balle.radius = balle.ballWidth * 0.5f;
	//______________________________________
	paddle1 = CreateSprite("./images/LPaddle.png", p1.paddleWidth, p1.paddleHeight, true);
	paddle2 = CreateSprite("./images/RPaddle.png", p2.paddle2Width, p2.paddle2Height, true);
	ball = CreateSprite("./images/Ball2.png", balle.ballWidth, balle.ballHeight, true);


	
   
	
    float xPos = 100;
    float yPos = 100;

	
	GAMESTATES eCurrentState = eMAIN_MENU;
	

    //Game Loop
    do
    {
		float fDeltaT = GetDeltaTime();
		switch (eCurrentState)
		{
		case eMAIN_MENU:
			UpdateMainMenu();
			//SetFont(pInvadersFont);
			//DrawString(pkInsertCoins, iScreenWidth * 0.37f, iScreenHeight * 0.5f);
			//DrawString(pkCredit, iScreenWidth * 0.47f, iScreenHeight * 0.4f);
			if (IsKeyDown(' '))
			{
				eCurrentState = eGAMEPLAY;
			}
			if (IsKeyDown('H'))
			{
				eCurrentState = eHIGHSCORES;
			}
			ClearScreen();
			break;
			//Below handles the High Scores board
		case eHIGHSCORES:
		{
							
					UpdateScoreBoard();
					itoa(p1HS, HS1, 10) &&
					itoa(p2HS, HS2, 10);
					DrawString(HS1, screenWidth / 2, (screenHeight / 2) + 45);
					DrawString("Player 1: ", (screenWidth / 2) - 130, (screenHeight / 2) + 45);
					DrawString(HS2, screenWidth / 2, screenHeight / 2);
					DrawString("Player 2: ", (screenWidth / 2) - 130, screenHeight / 2);
					if (IsKeyDown('R'))
					{
						
							eCurrentState = eMAIN_MENU;
					}
					ClearScreen();
					break;
		}
		case eGAMEPLAY:
			UpdateGameState(GetDeltaTime());
			if (IsKeyDown('P'))
			{
				
				eCurrentState = eMAIN_MENU;
			}
			if (Score1 > 10)
			{
				eCurrentState = eMAIN_MENU;
				p1HS = Score1;
				Score1 = 0;
				Score2 = 0;
			}
			if (Score2 > 10)
			{
				eCurrentState = eMAIN_MENU;
				p2HS = Score2;
				Score1 = 0;
				Score2 = 0;
			}
			ClearScreen();
			break;
		default:
			break;
		}
		

    } while(!FrameworkUpdate()&& isGameRunning);
	//system("pause");
	 
	
	


    Shutdown();

    return 0;
}