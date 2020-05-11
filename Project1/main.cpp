#include "DxLib.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <time.h>



#define SCREEN_SIZE_X 640	// �E�B���h�E�̉���
#define SCREEN_SIZE_Y 480	// �E�B���h�E�̏c��
#define PLAYER_SIZE_X 32	// ���@�̉���
#define PLAYER_SIZE_Y 32	// ���@�̏c��
#define PLAYER_REVIVE_TIME	180	// ���G����
#define PLAYER_HEALTH_MAX	3	// ���@�̗̑�

#define HP_STRING_SIZE_X	48	// �̗͂̕�����̉���
#define GAMEOVER_SIZE_X		160	// �Q�[���I�[�o�[�̉���
#define GAMECLEAR_SIZE_X		160	// �Q�[���N���A�̉���
#define STRING_SIZE_Y	16	// ������̏c��

#define HEART_SIZE_X	13	// �n�[�g�̉���
#define HEART_SIZE_Y	13	// �n�[�g�̏c��

#define SHOT_SIZE_X   32	// �e�̉���
#define SHOT_SIZE_Y   32	// �e�̏c��

#define BG_SIZE_Y     960	// �w�i�̏c��

#define ENEMY_SIZE_X  64	// �G�̉���
#define ENEMY_SIZE_Y  64	// �G�̏c��
#define ENEMY_HEALTH_MAX  100	// �G�̗̑�

#define BLAST_SIZE_X  96	// �����̉��� 
#define BLAST_SIZE_Y  96	// �����̏c��
#define BLAST_MAX	  20	// ���������̃t���[����

#define SHOT_MAX      50	// �e�̏��


#define FLAG	      0		// �z��̊Ǘ��p
#define POSITION_X    1
#define POSITION_Y	  2
#define SHOT_CENTER   0
#define SHOT_LEFT	  1
#define SHOT_RIGHT    2

#define TRUE		  1		// int��bool�̂悤�Ɍ��₷�����邽��
#define FALSE         0

#define SPEED_BOOST	  10


#define RAD45         M_PI/4.0		// ���W�A��45�x
#define RAD60		  M_PI * 2/ 6	// ���W�A��60�x
#define RAD30		  M_PI / 6	// ���W�A��120�x
#define RAD300		  M_PI * 11/6




// �ϐ��̒�`
int playerImage;	// ���@�̕`��o�^�p�ϐ�
double playerPosX;		// ���@��\������X���W�̕ϐ�
double playerPosY;		// ���@��\������Y���W�̕ϐ�
int playerSpeed;	// ���@�̈ړ���
bool playerFlag;		// ���@�̐����Ǘ�
int playerReviveCount;	// �������̖��G���Ԃ̃J�E���g
bool playerBoostFrag;	// �X�s�[�h���������������Ǘ�����ϐ�
int playerHealth;		// ���@�̗̑�
int heartImage;			// �n�[�g�̕`��o�^�p
bool gameoverFlag;
bool gameclearFlag;

unsigned int string_Color;	// ������̐F
unsigned int gameover_Color;	// �Q�[���I�[�o�[�̕�����̐F



int shotSpeed;		// �e�̑��x

int shotImage;		// �e�̕`��o�^�p�ϐ�


int bgImage;		// �w�i�̕`��o�^�p�ϐ�
int bgPosX;			// �w�i��X���W
int bgPosY[2];		// �w�i��Y���W
int bgSpeed;		// �w�i�̃X�s�[�h

int enemyImage;		// �G�̕`��o�^�p
int enemyPosX;		// �G��X���W
int enemyPosY;		// �G��Y���W
int enemySpeed;		// �G�̃X�s�[�h
int enemyHP;		// �G�̗̑�

int blastImage[20];	// �����̉摜�ۊǗp
int blastCount;
bool blastFlag;

int shot[SHOT_MAX][3][3];	// �e�̃t���O�AX���W�AY���W��3�������Ǘ�����z��
int shotCount;
int count;

int chargeLag;			//	�e�̃`���[�W����
int chargeCount;


bool enemyFlag;		// �G�̏�ԊǗ��p�ϐ�



int  WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{ 
	// �V�X�e������
	SetWindowText("1916037_�p���B�@�E�s�@���T�C�A�X");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);			// 640*480�h�b�g�A65536�F���[�h�ɐݒ�
	ChangeWindowMode(true);				// true:window false:�t���X�N���[��
	if (DxLib_Init() == -1)				// Dx���C�u�����̏�����
	{			
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);		// �`�����o�b�N�o�b�t�@�ɐݒ�


	srand((unsigned)time(NULL));



	// �O���t�B�b�N�̓o�^
	playerImage = LoadGraph("image/player 2.png"); 
	shotImage   = LoadGraph("image/shot.png");
	bgImage     = LoadGraph("image/haikei.png");
	enemyImage  = LoadGraph("image/enemy2.png");
	heartImage  = LoadGraph("image/heart.png");
	LoadDivGraph("image/blast.png", 20, 6, 4, BLAST_SIZE_X, BLAST_SIZE_Y,blastImage);

	// �ϐ��̏�����
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


	chargeLag   = 5;		// �`���[�W��
	chargeCount = 0;		// �`���[�W�̏�����

	

	for (shotCount = 0; shotCount < SHOT_MAX; shotCount++) {
		shot[shotCount][FLAG][SHOT_CENTER] = FALSE;
		shot[shotCount][FLAG][SHOT_LEFT] = FALSE;
		shot[shotCount][FLAG][SHOT_RIGHT] = FALSE;
	}

	shotCount = 0;

	// �Q�[�����[�v
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
			// �����Ȃ�
		}

		if (gameoverFlag == false)
		{

			chargeCount++;	// �e�̃`���[�W����

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
				// �Ȃɂ��Ȃ�
			}



			if (CheckHitKey(KEY_INPUT_SPACE) == 1)
			{
				playerSpeed *= SPEED_BOOST;
				playerBoostFrag = true;
			}


			// �����������ǂ������� 
			if (CheckHitKey(KEY_INPUT_NUMPAD6) == 1 && CheckHitKey(KEY_INPUT_NUMPAD8) == 1)			// �E��
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
			else if (CheckHitKey(KEY_INPUT_NUMPAD6) == 1 && CheckHitKey(KEY_INPUT_NUMPAD2) == 1)	// �E��	
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
			else if (CheckHitKey(KEY_INPUT_NUMPAD4) == 1 && CheckHitKey(KEY_INPUT_NUMPAD2) == 1)	// ����
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
			else if (CheckHitKey(KEY_INPUT_NUMPAD4) == 1 && CheckHitKey(KEY_INPUT_NUMPAD8) == 1)	// ����
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
			// �P�������̂Ƃ�
			else if (CheckHitKey(KEY_INPUT_NUMPAD6) == 1)			// �E
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
			else if (CheckHitKey(KEY_INPUT_NUMPAD4) == 1)		// ��
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
			else if (CheckHitKey(KEY_INPUT_NUMPAD8) == 1)		// ��
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
			else if (CheckHitKey(KEY_INPUT_NUMPAD2) == 1)		// ��
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
				// �Ȃɂ��Ȃ�
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
		

		

		

		// �w�i�̈ʒu��߂�

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
			// �e�ƓG�̓����蔻��
			if (enemyFlag == true)
			{																			// �G�����邩�ǂ���
				for (count = 0; count < SHOT_MAX; count++)
				{
					if (shot[count][FLAG][SHOT_CENTER] == TRUE)
					{															// ���ꂼ��̋���flag�������Ă邩�ǂ���
						if ((shot[count][POSITION_X][SHOT_CENTER] < enemyPosX + ENEMY_SIZE_X * 7 / 8) &&						// �����蔻��
							(shot[count][POSITION_X][SHOT_CENTER] + SHOT_SIZE_X >= enemyPosX + ENEMY_SIZE_X / 8) &&
							(shot[count][POSITION_Y][SHOT_CENTER] < enemyPosY + ENEMY_SIZE_Y * 3 / 4) &&
							(shot[count][POSITION_Y][SHOT_CENTER] + SHOT_SIZE_Y >= enemyPosY + ENEMY_SIZE_Y / 4))
						{
							shot[count][FLAG][SHOT_CENTER] = FALSE;
							enemyHP--;
						}
					}
					if (shot[count][FLAG][SHOT_LEFT] == TRUE)
					{															// ���ꂼ��̋���flag�������Ă邩�ǂ���
						if ((shot[count][POSITION_X][SHOT_LEFT] < enemyPosX + ENEMY_SIZE_X * 7 / 8) &&						// �����蔻��
							(shot[count][POSITION_X][SHOT_LEFT] + SHOT_SIZE_X >= enemyPosX + ENEMY_SIZE_X / 8) &&
							(shot[count][POSITION_Y][SHOT_LEFT] < enemyPosY + ENEMY_SIZE_Y * 3 / 4) &&
							(shot[count][POSITION_Y][SHOT_LEFT] + SHOT_SIZE_Y >= enemyPosY + ENEMY_SIZE_Y / 4))
						{
							shot[count][FLAG][SHOT_LEFT] = FALSE;
							enemyHP--;
						}
					}
					if (shot[count][FLAG][SHOT_RIGHT] == TRUE)
					{															// ���ꂼ��̋���flag�������Ă邩�ǂ���
						if ((shot[count][POSITION_X][SHOT_RIGHT] < enemyPosX + ENEMY_SIZE_X * 7 / 8) &&						// �����蔻��
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

			// �G�Ǝ��@�̓����蔻��

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
		


		ClsDrawScreen();				// ��ʂ̏���
	
		//�`�揈��

		DrawGraph(bgPosX, bgPosY[0], bgImage, false);
		DrawGraph(bgPosX, bgPosY[1], bgImage, false);
		
		//�e�̕`��
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
		
		//���@�̕`��
		if (gameoverFlag == false)
		{
			DrawGraph(playerPosX, playerPosY, playerImage, true);
		}
		else
		{
			DrawFormatString((SCREEN_SIZE_X / 2) - (GAMEOVER_SIZE_X / 2), (SCREEN_SIZE_Y / 2) - (STRING_SIZE_Y / 2), string_Color, "     GAMEOVER     \npress R to restart");
		}
		// �G�̕`��


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


		// �n�[�g�̕`��
		DrawFormatString((SCREEN_SIZE_X * 3 / 4) - HP_STRING_SIZE_X, SCREEN_SIZE_Y - STRING_SIZE_Y,string_Color,"�c�@:");
		for (count = 0; count < playerHealth; count++)
		{
			DrawGraph((SCREEN_SIZE_X * 3 / 4) + (count * HEART_SIZE_X), SCREEN_SIZE_Y - HEART_SIZE_Y, heartImage, true);
		}
		

		ScreenFlip();					// �t�����g�o�b�t�@�ƃo�b�N�o�b�t�@�̐؂�ւ�

	}
	DxLib_End();
	return 0;
}