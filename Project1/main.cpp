#include "DxLib.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <time.h>



#define SCREEN_SIZE_X 640	// ウィンドウの横幅
#define SCREEN_SIZE_Y 480	// ウィンドウの縦幅
#define PLAYER_SIZE_X 32	// 自機の横幅
#define PLAYER_SIZE_Y 32	// 自機の縦幅
#define PLAYER_REVIVE_TIME	180	// 無敵時間
#define PLAYER_HEALTH_MAX	3	// 自機の体力

#define HP_STRING_SIZE_X	48	// 体力の文字列の横幅
#define GAMEOVER_SIZE_X		160	// ゲームオーバーの横幅
#define GAMECLEAR_SIZE_X		160	// ゲームクリアの横幅
#define STRING_SIZE_Y	16	// 文字列の縦幅

#define HEART_SIZE_X	13	// ハートの横幅
#define HEART_SIZE_Y	13	// ハートの縦幅

#define SHOT_SIZE_X   32	// 弾の横幅
#define SHOT_SIZE_Y   32	// 弾の縦幅

#define BG_SIZE_Y     960	// 背景の縦幅

#define ENEMY_SIZE_X  64	// 敵の横幅
#define ENEMY_SIZE_Y  64	// 敵の縦幅
#define ENEMY_HEALTH_MAX  100	// 敵の体力

#define BLAST_SIZE_X  96	// 爆発の横幅 
#define BLAST_SIZE_Y  96	// 爆発の縦幅
#define BLAST_MAX	  20	// 爆発処理のフレーム数

#define SHOT_MAX      50	// 弾の上限


#define FLAG	      0		// 配列の管理用
#define POSITION_X    1
#define POSITION_Y	  2
#define SHOT_CENTER   0
#define SHOT_LEFT	  1
#define SHOT_RIGHT    2

#define TRUE		  1		// intでboolのように見やすくするため
#define FALSE         0

#define SPEED_BOOST	  10


#define RAD45         M_PI/4.0		// ラジアン45度
#define RAD60		  M_PI * 2/ 6	// ラジアン60度
#define RAD30		  M_PI / 6	// ラジアン120度
#define RAD300		  M_PI * 11/6




// 変数の定義
int playerImage;	// 自機の描画登録用変数
double playerPosX;		// 自機を表示するX座標の変数
double playerPosY;		// 自機を表示するY座標の変数
int playerSpeed;	// 自機の移動量
bool playerFlag;		// 自機の生存管理
int playerReviveCount;	// 復活時の無敵時間のカウント
bool playerBoostFrag;	// スピードが増加したかを管理する変数
int playerHealth;		// 自機の体力
int heartImage;			// ハートの描画登録用
bool gameoverFlag;
bool gameclearFlag;

unsigned int string_Color;	// 文字列の色
unsigned int gameover_Color;	// ゲームオーバーの文字列の色



int shotSpeed;		// 弾の速度

int shotImage;		// 弾の描画登録用変数


int bgImage;		// 背景の描画登録用変数
int bgPosX;			// 背景のX座標
int bgPosY[2];		// 背景のY座標
int bgSpeed;		// 背景のスピード

int enemyImage;		// 敵の描画登録用
int enemyPosX;		// 敵のX座標
int enemyPosY;		// 敵のY座標
int enemySpeed;		// 敵のスピード
int enemyHP;		// 敵の体力

int blastImage[20];	// 爆発の画像保管用
int blastCount;
bool blastFlag;

int shot[SHOT_MAX][3][3];	// 弾のフラグ、X座標、Y座標と3方向を管理する配列
int shotCount;
int count;

int chargeLag;			//	弾のチャージ時間
int chargeCount;


bool enemyFlag;		// 敵の状態管理用変数



int  WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{ 
	// システム処理
	SetWindowText("1916037_パリィ　勇行　メサイアス");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);			// 640*480ドット、65536色モードに設定
	ChangeWindowMode(true);				// true:window false:フルスクリーン
	if (DxLib_Init() == -1)				// Dxライブラリの初期化
	{			
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);		// 描画先をバックバッファに設定


	srand((unsigned)time(NULL));



	// グラフィックの登録
	playerImage = LoadGraph("image/player 2.png"); 
	shotImage   = LoadGraph("image/shot.png");
	bgImage     = LoadGraph("image/haikei.png");
	enemyImage  = LoadGraph("image/enemy2.png");
	heartImage  = LoadGraph("image/heart.png");
	LoadDivGraph("image/blast.png", 20, 6, 4, BLAST_SIZE_X, BLAST_SIZE_Y,blastImage);

	// 変数の初期化
	playerPosX  = (SCREEN_SIZE_X / 2) - (PLAYER_SIZE_X / 2);
	playerPosY  = (SCREEN_SIZE_Y / 4 * 3) - (PLAYER_SIZE_Y / 2);
	playerSpeed = 5;
	playerFlag = false;
	playerReviveCount = 0;
	playerBoostFrag = false;
	playerHealth = PLAYER_HEALTH_MAX;
	gameoverFlag = false;
	gameclearFlag = false;

	string_Color = GetColor(0, 0, 255);
	gameover_Color = GetColor(255, 0, 0);

	shotSpeed = 30;

	blastCount = 0;
	blastFlag = false;

	bgPosX    = 0;
	bgPosY[0] = -SCREEN_SIZE_X; 
	bgPosY[1] = -SCREEN_SIZE_X - BG_SIZE_Y;
	bgSpeed   = 20;

	enemyPosX  = rand() % (SCREEN_SIZE_X - ENEMY_SIZE_X);
	enemyPosY  = -ENEMY_SIZE_Y;
	enemySpeed = 20;
	enemyFlag  =true;
	enemyHP = ENEMY_HEALTH_MAX;


	chargeLag   = 5;		// チャージ量
	chargeCount = 0;		// チャージの初期化

	

	for (shotCount = 0; shotCount < SHOT_MAX; shotCount++) {
		shot[shotCount][FLAG][SHOT_CENTER] = FALSE;
		shot[shotCount][FLAG][SHOT_LEFT] = FALSE;
		shot[shotCount][FLAG][SHOT_RIGHT] = FALSE;
	}

	shotCount = 0;

	// ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) 
	{



		
		if (gameoverFlag == true||gameclearFlag == true)
		{
			if (CheckHitKey(KEY_INPUT_R))
			{
				gameoverFlag = false;
				gameclearFlag = false;
				playerHealth = PLAYER_HEALTH_MAX;
				enemyHP = ENEMY_HEALTH_MAX;
				playerFlag = false;
				playerReviveCount = 0;
			}
		}
		
		

		if (blastFlag == true)
		{
			blastCount++;
			if (blastCount >= BLAST_MAX)
			{
				blastCount = 0;
				blastFlag = false;
			}
		}
		
		else if (enemyFlag == false && gameclearFlag == false)
		{
				enemyPosX = rand() % (SCREEN_SIZE_X - ENEMY_SIZE_X);
				enemyPosY = -ENEMY_SIZE_Y;
				enemyFlag = true;
		}
		else
		{
			// 何もなし
		}

		if (gameoverFlag == false)
		{

			chargeCount++;	// 弾のチャージ時間

			if (playerFlag == false)
			{
				playerReviveCount++;
				if (playerReviveCount > PLAYER_REVIVE_TIME)
				{
					playerFlag = true;
				}
			}

			if (CheckHitKey(KEY_INPUT_LCONTROL))
			{
				if (chargeCount >= chargeLag) 
				{
					chargeCount = 0;
					for (count = 0; count < SHOT_MAX; count++)
					{
						if (shot[count][FLAG][SHOT_CENTER] == FALSE)
						{
							shot[count][POSITION_X][SHOT_CENTER] = playerPosX;
							shot[count][POSITION_Y][SHOT_CENTER] = playerPosY;
							shot[count][FLAG][SHOT_CENTER] = TRUE;
							break;
						}
					}
				}
			}
			else if (CheckHitKey(KEY_INPUT_LSHIFT) || CheckHitKey(KEY_INPUT_B))
			{
				if (chargeCount >= chargeLag)
				{
					chargeCount = 0;
					for (count = 0; count < SHOT_MAX; count++)
					{
						if (shot[count][FLAG][SHOT_CENTER] == FALSE && shot[count][FLAG][SHOT_LEFT] == FALSE && shot[count][FLAG][SHOT_RIGHT] == FALSE)
						{
							shot[count][POSITION_X][SHOT_CENTER] = playerPosX;
							shot[count][POSITION_Y][SHOT_CENTER] = playerPosY;
							shot[count][FLAG][SHOT_CENTER] = TRUE;
							shot[count][POSITION_X][SHOT_LEFT] = playerPosX;
							shot[count][POSITION_Y][SHOT_LEFT] = playerPosY;
							shot[count][FLAG][SHOT_LEFT] = TRUE;
							shot[count][POSITION_X][SHOT_RIGHT] = playerPosX;
							shot[count][POSITION_Y][SHOT_RIGHT] = playerPosY;
							shot[count][FLAG][SHOT_RIGHT] = TRUE;
							break;
						}
					}
				}
			}
			else
			{
				// なにもなし
			}



			if (CheckHitKey(KEY_INPUT_SPACE) == 1)
			{
				playerSpeed *= SPEED_BOOST;
				playerBoostFrag = true;
			}


			// 同時押しかどうか判定 
			if (CheckHitKey(KEY_INPUT_NUMPAD6) == 1 && CheckHitKey(KEY_INPUT_NUMPAD8) == 1)			// 右上
			{
				if (playerPosX + PLAYER_SIZE_X <= SCREEN_SIZE_X - cos(RAD45) * playerSpeed)
				{
					playerPosX = playerPosX + cos(RAD45) * playerSpeed;
				}
				else
				{
					playerPosX = SCREEN_SIZE_X - PLAYER_SIZE_X;
				}
				if (playerPosY >= sin(RAD45) * playerSpeed)
				{
					playerPosY = playerPosY - sin(RAD45) * playerSpeed;
				}
				else
				{
					playerPosY = 0;
				}
			}
			else if (CheckHitKey(KEY_INPUT_NUMPAD6) == 1 && CheckHitKey(KEY_INPUT_NUMPAD2) == 1)	// 右下	
			{
				if (playerPosX + PLAYER_SIZE_X <= SCREEN_SIZE_X - cos(RAD45) * playerSpeed)
				{
					playerPosX = playerPosX + cos(RAD45) * playerSpeed;
				}
				else
				{
					playerPosX = SCREEN_SIZE_X - PLAYER_SIZE_X;
				}
				if (playerPosY + PLAYER_SIZE_Y <= SCREEN_SIZE_Y - sin(RAD45) * playerSpeed)
				{
					playerPosY = playerPosY + sin(RAD45) * playerSpeed;
				}
				else
				{
					playerPosY = SCREEN_SIZE_Y - PLAYER_SIZE_Y;
				}
			}
			else if (CheckHitKey(KEY_INPUT_NUMPAD4) == 1 && CheckHitKey(KEY_INPUT_NUMPAD2) == 1)	// 左下
			{
				if (playerPosX >= cos(RAD45) * playerSpeed)
				{

					playerPosX = playerPosX - cos(RAD45) * playerSpeed;
				}
				else
				{
					playerPosX = 0;
				}
				if (playerPosY + PLAYER_SIZE_Y <= SCREEN_SIZE_Y - sin(RAD45) * playerSpeed)
				{
					playerPosY = playerPosY + sin(RAD45) * playerSpeed;
				}
				else
				{
					playerPosY = SCREEN_SIZE_Y - PLAYER_SIZE_Y;
				}
			}
			else if (CheckHitKey(KEY_INPUT_NUMPAD4) == 1 && CheckHitKey(KEY_INPUT_NUMPAD8) == 1)	// 左上
			{
				if (playerPosX >= cos(RAD45) * playerSpeed)
				{
					playerPosX = playerPosX - cos(RAD45) * playerSpeed;
				}
				else
				{
					playerPosX = 0;
				}
				if (playerPosY >= sin(RAD45) * playerSpeed)
				{
					playerPosY = playerPosY - sin(RAD45) * playerSpeed;
				}
				else
				{
					playerPosY = 0;
				}
			}
			// 単発押しのとき
			else if (CheckHitKey(KEY_INPUT_NUMPAD6) == 1)			// 右
			{
				if (playerPosX <= SCREEN_SIZE_X - PLAYER_SIZE_X - playerSpeed)
				{
					playerPosX = playerPosX + playerSpeed;
				}
				else
				{
					playerPosX = SCREEN_SIZE_X - PLAYER_SIZE_X;
				}
			}
			else if (CheckHitKey(KEY_INPUT_NUMPAD4) == 1)		// 左
			{
				if (playerPosX >= playerSpeed)
				{
					playerPosX = playerPosX - playerSpeed;
				}
				else
				{
					playerPosX = 0;
				}
			}
			else if (CheckHitKey(KEY_INPUT_NUMPAD8) == 1)		// 上
			{
				if (playerPosY >= playerSpeed)
				{
					playerPosY = playerPosY - playerSpeed;
				}
				else
				{
					playerPosY = 0;
				}
			}
			else if (CheckHitKey(KEY_INPUT_NUMPAD2) == 1)		// 下
			{
				if (playerPosY <= SCREEN_SIZE_Y - PLAYER_SIZE_Y - playerSpeed)
				{
					playerPosY = playerPosY + playerSpeed;
				}
				else
				{
					playerPosY = SCREEN_SIZE_Y - PLAYER_SIZE_Y;
				}
			}
			else
			{
				// なにもなし
			}

			if (playerBoostFrag == true)
			{
				playerSpeed /= SPEED_BOOST;
				playerBoostFrag = false;
			}

		}

			for (count = 0; count < SHOT_MAX; count++)
			{
				if (shot[count][POSITION_Y][SHOT_CENTER] >= -SHOT_SIZE_Y)
				{
					shot[count][POSITION_Y][SHOT_CENTER] -= shotSpeed;
				}
				else
				{
					shot[count][FLAG][SHOT_CENTER] = FALSE;
				}
				if (shot[count][POSITION_Y][SHOT_LEFT] >= -SHOT_SIZE_Y)
				{
					shot[count][POSITION_X][SHOT_LEFT] -= cos(RAD60) * shotSpeed;
					shot[count][POSITION_Y][SHOT_LEFT] -= sin(RAD60) * shotSpeed;
				}
				else
				{
					shot[count][FLAG][SHOT_LEFT] = FALSE;
				}
				if (shot[count][POSITION_Y][SHOT_RIGHT] >= -SHOT_SIZE_Y)
				{
					shot[count][POSITION_X][SHOT_RIGHT] += cos(RAD60) * shotSpeed;
					shot[count][POSITION_Y][SHOT_RIGHT] -= sin(RAD60) * shotSpeed;
				}
				else
				{
					shot[count][FLAG][SHOT_RIGHT] = FALSE;
				}
			}


		if (enemyFlag == true)
		{
			if (enemyPosY < SCREEN_SIZE_Y)
			{
				enemyPosY += enemySpeed;
			}
			else
			{
				enemyFlag = false;
			}

		}
		

		

		

		// 背景の位置を戻す

			bgPosY[0] += bgSpeed;
			bgPosY[1] += bgSpeed;
		if (bgPosY[0] >= SCREEN_SIZE_Y)
		{
			bgPosY[0] = bgPosY[1] - BG_SIZE_Y;
		}
		if (bgPosY[1] >= SCREEN_SIZE_Y)
		{
			bgPosY[1] = bgPosY[0] - BG_SIZE_Y;
		}


		if (gameclearFlag == false && gameoverFlag == false)
		{
			// 弾と敵の当たり判定
			if (enemyFlag == true)
			{																			// 敵がいるかどうか
				for (count = 0; count < SHOT_MAX; count++)
				{
					if (shot[count][FLAG][SHOT_CENTER] == TRUE)
					{															// それぞれの球のflagが立ってるかどうか
						if ((shot[count][POSITION_X][SHOT_CENTER] < enemyPosX + ENEMY_SIZE_X * 7 / 8) &&						// 当たり判定
							(shot[count][POSITION_X][SHOT_CENTER] + SHOT_SIZE_X >= enemyPosX + ENEMY_SIZE_X / 8) &&
							(shot[count][POSITION_Y][SHOT_CENTER] < enemyPosY + ENEMY_SIZE_Y * 3 / 4) &&
							(shot[count][POSITION_Y][SHOT_CENTER] + SHOT_SIZE_Y >= enemyPosY + ENEMY_SIZE_Y / 4))
						{
							shot[count][FLAG][SHOT_CENTER] = FALSE;
							enemyHP--;
						}
					}
					if (shot[count][FLAG][SHOT_LEFT] == TRUE)
					{															// それぞれの球のflagが立ってるかどうか
						if ((shot[count][POSITION_X][SHOT_LEFT] < enemyPosX + ENEMY_SIZE_X * 7 / 8) &&						// 当たり判定
							(shot[count][POSITION_X][SHOT_LEFT] + SHOT_SIZE_X >= enemyPosX + ENEMY_SIZE_X / 8) &&
							(shot[count][POSITION_Y][SHOT_LEFT] < enemyPosY + ENEMY_SIZE_Y * 3 / 4) &&
							(shot[count][POSITION_Y][SHOT_LEFT] + SHOT_SIZE_Y >= enemyPosY + ENEMY_SIZE_Y / 4))
						{
							shot[count][FLAG][SHOT_LEFT] = FALSE;
							enemyHP--;
						}
					}
					if (shot[count][FLAG][SHOT_RIGHT] == TRUE)
					{															// それぞれの球のflagが立ってるかどうか
						if ((shot[count][POSITION_X][SHOT_RIGHT] < enemyPosX + ENEMY_SIZE_X * 7 / 8) &&						// 当たり判定
							(shot[count][POSITION_X][SHOT_RIGHT] + SHOT_SIZE_X >= enemyPosX + ENEMY_SIZE_X / 8) &&
							(shot[count][POSITION_Y][SHOT_RIGHT] < enemyPosY + ENEMY_SIZE_Y * 3 / 4) &&
							(shot[count][POSITION_Y][SHOT_RIGHT] + SHOT_SIZE_Y >= enemyPosY + ENEMY_SIZE_Y / 4))
						{
							shot[count][FLAG][SHOT_RIGHT] = FALSE;
							enemyHP--;
						}
					}
				}
			}


			if (enemyHP <= 0)
			{
				enemyFlag = false;
				blastFlag = true;
				gameclearFlag = true;
			}

			// 敵と自機の当たり判定

			if (enemyFlag == true && playerFlag == true)
			{
				if ((playerPosX < enemyPosX + ENEMY_SIZE_X * 7 / 8) &&
					(playerPosX + PLAYER_SIZE_X >= enemyPosX + ENEMY_SIZE_X / 8) &&
					(playerPosY < enemyPosY + ENEMY_SIZE_Y * 3 / 4) &&
					(playerPosY + PLAYER_SIZE_Y >= enemyPosY + ENEMY_SIZE_Y / 4))
				{
					playerFlag = false;
					playerHealth--;
					if (playerHealth <= 0)
					{
						gameoverFlag = true;
					}
					playerReviveCount = 0;
					playerPosX = (SCREEN_SIZE_X / 2) - (PLAYER_SIZE_X / 2);
					playerPosY = (SCREEN_SIZE_Y / 4 * 3) - (PLAYER_SIZE_Y / 2);
				}

			}
		}
		


		ClsDrawScreen();				// 画面の消去
	
		//描画処理

		DrawGraph(bgPosX, bgPosY[0], bgImage, false);
		DrawGraph(bgPosX, bgPosY[1], bgImage, false);
		
		//弾の描画
		for (count = 0; count < SHOT_MAX; count++)
		{
			if (shot[count][FLAG][SHOT_CENTER] == TRUE) 
			{
				DrawGraph(shot[count][POSITION_X][SHOT_CENTER], shot[count][POSITION_Y][SHOT_CENTER], shotImage, true);
			}
			if (shot[count][FLAG][SHOT_LEFT] == TRUE)
			{
				DrawRotaGraph(shot[count][POSITION_X][SHOT_LEFT] + (SHOT_SIZE_X / 2), shot[count][POSITION_Y][SHOT_LEFT] + (SHOT_SIZE_Y / 2), 1.0 , RAD300 , shotImage, true , true);
			}
			if (shot[count][FLAG][SHOT_RIGHT] == TRUE)
			{
				DrawRotaGraph(shot[count][POSITION_X][SHOT_RIGHT] + (SHOT_SIZE_X / 2), shot[count][POSITION_Y][SHOT_RIGHT] + (SHOT_SIZE_Y / 2), 1.0 , RAD30 , shotImage, true , true);
			}
		}
		
		//自機の描画
		if (gameoverFlag == false)
		{
			DrawGraph(playerPosX, playerPosY, playerImage, true);
		}
		else
		{
			DrawFormatString((SCREEN_SIZE_X / 2) - (GAMEOVER_SIZE_X / 2), (SCREEN_SIZE_Y / 2) - (STRING_SIZE_Y / 2), string_Color, "     GAMEOVER     \npress R to restart");
		}
		// 敵の描画


		if (gameclearFlag == true)
		{
			DrawFormatString((SCREEN_SIZE_X / 2) - (GAMECLEAR_SIZE_X / 2), (SCREEN_SIZE_Y / 2) - (STRING_SIZE_Y / 2), string_Color, "     GAMECLEAR     \npress R to restart");
		}
		else if (enemyFlag == true) 
		{
			DrawGraph(enemyPosX, enemyPosY, enemyImage, true);
			DrawFormatString(SCREEN_SIZE_X / 8, 0, string_Color, "ENEMY HP:%d",enemyHP);
		}
		
		
		if(blastFlag == true)
		{
			DrawGraph(enemyPosX - (BLAST_SIZE_X / 2 - ENEMY_SIZE_Y / 2), enemyPosY - (BLAST_SIZE_Y / 2 - ENEMY_SIZE_Y / 2), blastImage[blastCount], true);
		}


		// ハートの描画
		DrawFormatString((SCREEN_SIZE_X * 3 / 4) - HP_STRING_SIZE_X, SCREEN_SIZE_Y - STRING_SIZE_Y,string_Color,"残機:");
		for (count = 0; count < playerHealth; count++)
		{
			DrawGraph((SCREEN_SIZE_X * 3 / 4) + (count * HEART_SIZE_X), SCREEN_SIZE_Y - HEART_SIZE_Y, heartImage, true);
		}
		

		ScreenFlip();					// フロントバッファとバックバッファの切り替え

	}
	DxLib_End();
	return 0;
}