#include "stdafx.h"
#include "data.h"

void Data::createCharacter(string job)
{
	string createCharacter = job;

	if (createCharacter == "�ȶ��")
	{
		//����
		INIDATA->addData("CLASS", "0");

		//����
		INIDATA->addData("LEVEL", "1");

		//ü��
		INIDATA->addData("MAX HP", "50");
		INIDATA->addData("HP", "50");

		//����
		INIDATA->addData("MAX MP", "50");
		INIDATA->addData("MP", "50");

		//����ġ
		INIDATA->addData("MAX EXP", "100");
		INIDATA->addData("EXP", "0");

		//��ġ
		INIDATA->addData("X coordinate", "600");
		INIDATA->addData("Y coordinate", "400");

		//��ų
		INIDATA->addData("SKILL POINT", "0");

		//ġ����
		INIDATA->addData("HP REGEN", "0");
		INIDATA->addData("MP REGEN", "0.50");

		//������
		INIDATA->addData("DAMAGE", "10");
		INIDATA->addData("ATTACK DAMAGE", "0");
		INIDATA->addData("ABILITY POWER", "0");

		//���� �� ���׷�
		INIDATA->addData("ARMOR", "10");
		INIDATA->addData("MAGIC RESIST", "10");

		//ũ��Ƽ��
		INIDATA->addData("CRITICAL", "0");

		//���ǵ�
		INIDATA->addData("MOVE SPEED", "2");
		INIDATA->addData("DASH SPEED", "3");

		//ȸ�Ƿ�
		INIDATA->addData("EVASION", "0");

		//����
		INIDATA->addData("RESISTANCE", "0");

		//���
		INIDATA->addData("LUCK", "0");

		//���� ���
		INIDATA->addData("GOLD", "10000");

		//���� ����
		INIDATA->addData("ORE", "0");

		//����
		INIDATA->addData("POTION MAX", "1");
		INIDATA->addData("POTION", "1");

		//���� ����
		INIDATA->addData("bronzeKey", "0");
		INIDATA->addData("silverKey", "0");
		INIDATA->addData("goldKey", "0");
		INIDATA->addData("redKey", "0");

		//�÷���Ÿ��
		INIDATA->addData("PLAY TIME", "0");
	}
	else if (createCharacter == "�ü�")
	{
		//����
		INIDATA->addData("CLASS", "1");

		//����
		INIDATA->addData("LEVEL", "1");

		//ü��
		INIDATA->addData("MAX HP", "50");
		INIDATA->addData("HP", "50");

		//����
		INIDATA->addData("MAX MP", "50");
		INIDATA->addData("MP", "50");

		//����ġ
		INIDATA->addData("MAX EXP", "100");
		INIDATA->addData("EXP", "0");

		//��ġ
		INIDATA->addData("X coordinate", "600");
		INIDATA->addData("Y coordinate", "400");

		//��ų
		INIDATA->addData("SKILL POINT", "0");

		//ġ����
		INIDATA->addData("HP REGEN", "0");
		INIDATA->addData("MP REGEN", "0.50");

		//������
		INIDATA->addData("DAMAGE", "10");
		INIDATA->addData("ATTACK DAMAGE", "0");
		INIDATA->addData("ABILITY POWER", "0");

		//���� �� ���׷�
		INIDATA->addData("ARMOR", "10");
		INIDATA->addData("MAGIC RESIST", "10");

		//ũ��Ƽ��
		INIDATA->addData("CRITICAL", "0");

		//���ǵ�
		INIDATA->addData("MOVE SPEED", "2");
		INIDATA->addData("DASH SPEED", "3");

		//ȸ�Ƿ�
		INIDATA->addData("EVASION", "0");

		//����
		INIDATA->addData("RESISTANCE", "0");

		//���
		INIDATA->addData("LUCK", "0");

		//���� ���
		INIDATA->addData("GOLD", "10000");

		//���� ����
		INIDATA->addData("ORE", "200");

		//����
		INIDATA->addData("POTION MAX", "1");
		INIDATA->addData("POTION", "1");

		//���� ����
		INIDATA->addData("bronzeKey", "0");
		INIDATA->addData("silverKey", "0");
		INIDATA->addData("goldKey", "0");
		INIDATA->addData("redKey", "0");

		//�÷���Ÿ��
		INIDATA->addData("PLAY TIME", "0");
	}

	INIDATA->iniSave();
	INIDATA->listNum();
}
