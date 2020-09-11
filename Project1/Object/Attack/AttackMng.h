#pragma once
#include "../Object.h"

#define lpAtkMng AttackMng::GetInstance()


class AttackMng :
	public Object
{
public:
	static AttackMng& GetInstance()
	{
		if (sInstance == nullptr)
		{
			sInstance = new AttackMng();
		}

		return *sInstance;
	}

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}

		sInstance = nullptr;
	}

	void Update(void)override;

	void Draw(void)override;

	std::vector<std::shared_ptr<Object>> GetAttackObjList(void);

	// �Ԗ��@

	// �΂̋�
	// pos:���W			dir:����
	// vec:�ړ��x�N�g��( vec.x > 0 ��dir�����ɁAvec.x < 0 �Ŕ��Α���)
	// time:���Ԏ�		stage:�X�e�[�W
	// target:�ڕW
	void MakeFireBall(Vector2 pos, DIR dir, Vector2 vec, TIME time, int stage, OBJ_TYPE target);
	// ���e����
	// pos:���W			dir:����
	// speed:���x( speed > 0 ��dir�����ɁAspeed < 0 �Ŕ��Α���)
	// vel:������Y����(���ŏ�����A���ŉ�����)
	// time:���Ԏ�		stage:�X�e�[�W
	// target:�ڕW
	void MakeBomb(Vector2 pos, DIR dir, int speed, double vel, TIME time, int stage, OBJ_TYPE target);
	
	// ���@

	// �A�U��
	// pos:���W			time:���Ԏ�
	// stage:�X�e�[�W	target:�ڕW
	void MakeBubble(Vector2 pos, TIME time, int stage, OBJ_TYPE target);
	// �A�j��
	// pos:���W			time:���Ԏ�
	// stage:�X�e�[�W	target:�ڕW
	void MakeBubbleBlast(Vector2 pos, TIME time, int stage, OBJ_TYPE target);

	// �Ζ��@

	// �t���[�c�]����
	// pos:���W			dir:����
	// speed:���x( speed > 0 ��dir�����ɁAspeed < 0 �Ŕ��Α���)
	// time:���Ԏ�		stage:�X�e�[�W
	// target:�ڕW
	void MakeFruit(Vector2 pos, DIR dir, int speed, TIME time, int stage, OBJ_TYPE target);

	// �����@

	// �ł̖�
	// pos:���W			count:��������
	// time:���Ԏ�		stage:�X�e�[�W
	// target:�ڕW
	void MakePoisonFog(Vector2 pos, int count, TIME time, int stage, OBJ_TYPE target);

	// �񕜂����
	// pos:���W			time:���Ԏ�
	// stage:�X�e�[�W	target:�ڕW
	void MakeHealTree(Vector2 pos, TIME time, int stage, OBJ_TYPE target);

	// �u���b�N�z�[��
	// pos:���W			dir:����
	// vec:�ړ��x�N�g��( vec.x > 0 ��dir�����ɁAvec.x < 0 �Ŕ��Α���)
	// lifetime:��������
	// time:���Ԏ�		stage:�X�e�[�W
	// target:�ڕW
	void MakeBlackHole(Vector2 pos, DIR dir, Vector2 vec, int lifetime, TIME time, int stage, OBJ_TYPE target);

	// ���F���@

	// �X�̋�
	// owner:���L��
	// pos:���W			dir:����
	// vec:�ړ��x�N�g��( vec.x > 0 ��dir�����ɁAvec.x < 0 �Ŕ��Α���)
	// time:���Ԏ�		stage:�X�e�[�W
	// target:�ڕW
	void MakeIceShot(std::shared_ptr<Object> owner, Vector2 offset, DIR dir, Vector2 vec, TIME time, int stage, OBJ_TYPE target);

	// �X�̕�
	// pos:���W			time:���Ԏ�
	// stage:�X�e�[�W	target:�ڕW
	void MakeIceWall(Vector2 pos, TIME time, int stage, OBJ_TYPE target);

	// �X���C��
	// pos:���W		dir::����
	// target:�W�I�̎��
	void MakeSlime(const Vector2& pos, DIR dir, int stage, OBJ_TYPE target);

	// ���F���@

	// ���_
	// pos:���W				dir:����
	// speed:���x( speed > 0 ��dir�����ɁAspeed < 0 �Ŕ��Α���)
	// count:���Ƃ����̐�	dur:���̊Ԋu(�t���[����)
	// time:���Ԏ�			stage:�X�e�[�W
	// target:�ڕW
	void MakeThunderCloud(Vector2 pos, DIR dir, int speed, int count, int dur, TIME time, int stage, OBJ_TYPE target);

	// ��
	// pos1:�n�_���W		pos2:�I�_���W
	// useRef:refPos���Q�Ƃ��邩(refPos�̈ړ��ɍ��킹�ē����悤�ɂȂ�)
	// refPos:�Q�ƂɎg�����W
	// damage:�_���[�W		time:���Ԏ�
	// stage:�X�e�[�W		target:�ڕW	
	void MakeThunder(Vector2 pos1, Vector2 pos2, bool useRef, Vector2* refPos, int damage, TIME time, int stage, OBJ_TYPE target);

	// �M��
	// pos:���W			time:���Ԏ�
	// stage:�X�e�[�W	target:�ڕW
	void MakeFlash(Vector2* pos, TIME time, int stage, OBJ_TYPE target);

	// �X�p�[�N
	// pos:���W			time:���Ԏ�
	// stage:�X�e�[�W	target:�ڕW
	void MakeSpark(Vector2* pos, TIME time, int stage, OBJ_TYPE target);

	// �����@

	// ���̒�
	// pos:���W			time:���Ԏ�
	// stage:�X�e�[�W	target:�ڕW
	int MakeHolyJudge(Vector2 pos, TIME time, int stage, OBJ_TYPE target);

	// �G
	
	// �ǔ��e
	// ePos:�G�̍��W		pPos:�U�����_�ł̃v���C���[�̍��W
	// time:���Ԏ�		stage:�X�e�[�W
	// target:�ڕW
	void MakeTrackingBall(Vector2 ePos, Vector2 pPos, TIME time, int stage, OBJ_TYPE target);

	// demon���U��
	// pos:�G�̍��W
	// dir:�����Ă������
	// time:���Ԏ�		stage:�X�e�[�W
	// target:�ڕW
	void MakeSpearAttack(Vector2 pos, DIR dir, TIME time, int stage, OBJ_TYPE target);
	void MakeThunderAttack(Vector2 pos, DIR dir, TIME time, int stage, OBJ_TYPE target);
	void MakeCaneAttack(Vector2 pos, DIR dir, TIME time, int stage, OBJ_TYPE target);

	void DeleteAll(void);

private:
	static AttackMng* sInstance;

	std::vector<std::shared_ptr<Object>> _attackObj;
	std::vector<std::shared_ptr<Object>> _tmpObj;		// �C�e���[�g���̗v�f�ǉ���	

	bool _canAddObj;

	AttackMng();
	AttackMng(const AttackMng&) = delete;
	AttackMng operator=(const AttackMng&) = delete;
	~AttackMng();
};

