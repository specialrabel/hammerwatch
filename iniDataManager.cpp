#include "stdafx.h"
#include "iniDataManager.h"

iniDataManager::iniDataManager()
{
}

iniDataManager::~iniDataManager()
{
}

HRESULT iniDataManager::init()
{
	_listNum = 0;

	return S_OK;
}

void iniDataManager::release()
{
}

int iniDataManager::listNum()
{
	//listNum�Լ��� ���ö����� �ϴ� ������ �����ְ� ����.
	vLoadIniData.clear();

	char str[256];
	char dir[256];

	_listNum = 0;

	for (int i = 0; i < 100; i++)
	{
		//�ߺ�Ȯ�� 45 ~ 53
		//�����̸�
		sprintf_s(dir, "\\%s%d.ini", "saveDATA", i);

		//���ϰ�� ���
		GetCurrentDirectory(256, str);

		//"���ϰ�� + �����̸�"���� ��ġ��
		strncat_s(str, 256, dir, 254);

		//������ ������ Ȯ�����ִ� �Լ�
		GetFileAttributes(str);

		//���ϸ��� ���� ������ �����Ѵٸ�
		if (INVALID_FILE_ATTRIBUTES != GetFileAttributes(str) || GetLastError() != ERROR_FILE_NOT_FOUND)
		{
			vLoadIniData.push_back(str);
		}
	}

	//Ǫ�ù�� �����ŭ ����Ʈ ����.

	for (int i = 0; i < vLoadIniData.size(); i++)
	{
		_listNum += 1;
	}


	//Ǫ�ù�� ������ ���� ��Ʈ������ ��ȯ.
	return _listNum;
}

float iniDataManager::readData(int num, const char* title)
{
	char playerInfo[256];
	char file[256];

	//ini���� ���� ����(��ȣ)
	sprintf_s(playerInfo, "�÷��̾� ����");

	//listNum�Լ����� Ǫ�ù�� ��� �� num��°�� �ִ� ���ϸ��� ������.
	sprintf_s(file, "%s", vLoadIniData[num].c_str());

	//�Է��� num��°�� ini������ ���� ��, �Է��� title�� �ش��ϴ� ���� ��ȯ��.
	char data[256] = {};
	char *pos = NULL;
	float value = 0;
	bool isTrue = false;

	isTrue = GetPrivateProfileString(playerInfo, title, "", data, 256, file);

	if (!isTrue) return 0;
	else if (isTrue)
	{
		value = strtof(data, &pos);

		return value;
	}
}

void iniDataManager::addData(const char * title, const char * value)
{
	tagIniData iniData;
	iniData.title = title;
	iniData.value = value;

	arrIniData vIniData;
	vIniData.push_back(iniData);

	_vIniData.push_back(vIniData);
}

void iniDataManager::iniSave()
{
	char str1[256];
	char dir1[256];

	ZeroMemory(dir1, sizeof(dir1));

	for (int i = 0; i < 100; i++)
	{
		char str2[256];
		char dir2[256];
		char playerInfo[256];
		sprintf_s(playerInfo, "�÷��̾� ����");

		//�ߺ�Ȯ�� 45 ~ 53
		sprintf_s(dir2, "\\%s%d.ini", "saveDATA", i);
		GetCurrentDirectory(256, str2);
		strncat_s(str2, 256, dir2, 254);

		GetFileAttributes(str2);

		//�����̸��� ������ �ִٸ� continue,
		if (INVALID_FILE_ATTRIBUTES != GetFileAttributes(str2)) continue;

		//���̺����� ���� 55 ~ 69
		sprintf_s(dir1, "\\%s%d.ini", "saveDATA", i);

		GetCurrentDirectory(256, str1);
		strncat_s(str1, 256, dir1, 254);

		for (int j = 0; j < _vIniData.size(); ++j)
		{

			arrIniData vData = _vIniData[j];
			WritePrivateProfileString(playerInfo, vData[0].title, vData[0].value, str1);

			vData.clear();
		}

		break;
	}

	_vIniData.clear();
}

void iniDataManager::soltData()
{
	for (int i = 0; i < 5; i++)
	{
		char str1[256];
		char dir1[256];
		char str2[256];
		char dir2[256];
		char str3[256];
		char dir3[256];

		//�ߺ�Ȯ��
		sprintf_s(dir1, "\\%s%d.ini", "saveDATA", i);
		sprintf_s(dir3, "\\%s%d.ini", "saveDATA", i + 1);
		sprintf_s(dir2, "\\%s%d.ini", "saveDATA", i + 2);
		GetCurrentDirectory(256, str1);
		strncat_s(str1, 256, dir1, 254);
		GetCurrentDirectory(256, str3);
		strncat_s(str3, 256, dir3, 254);
		GetCurrentDirectory(256, str2);
		strncat_s(str2, 256, dir2, 254);

		GetFileAttributes(str1);
		GetFileAttributes(str3);
		GetFileAttributes(str2);

		if (i == 0 && INVALID_FILE_ATTRIBUTES == GetFileAttributes(str1) && INVALID_FILE_ATTRIBUTES != GetFileAttributes(str3))
		{
			ifstream in(str3);
			ofstream out(str1);
			out << in.rdbuf();
			out.close();
			in.close();

			remove(str3);
		}

		//n��° ���ϰ� n+2��° ���� ���̿� ������ ������ continue, ������ n+2��° ������ ������ ������ �ٿ��ְ� n+2��° ������ ����.
		if (INVALID_FILE_ATTRIBUTES != GetFileAttributes(str1) &&
			INVALID_FILE_ATTRIBUTES == GetFileAttributes(str3) &&
			INVALID_FILE_ATTRIBUTES != GetFileAttributes(str2))
		{
			ifstream in(str2);
			ofstream out(str3);
			out << in.rdbuf();
			out.close();
			in.close();

			remove(str2);

			break;
		}

	}
}

void iniDataManager::deleteData(int num)
{
	char dir[256];
	char str[256];

	sprintf_s(dir, "\\%s%d.ini", "saveDATA", num);

	//���ϰ�� ���
	GetCurrentDirectory(256, str);

	//"���ϰ�� + �����̸�"���� ��ġ��
	strncat_s(str, 256, dir, 254);

	remove(str);
}

//�ֱ� ������ ������ ���.
void iniDataManager::currentData(int num)
{
	currentFileNum = num;

	//char str[256];

	//sprintf_s(str, "\\%s%d.ini", "saveDATA", num);

	//GetCurrentDirectory(256, currentFile);
	//strncat_s(currentFile, 256, str, 254);
}

void iniDataManager::updateData(int currentNum, const char * title, float value)
{
	char str[256];
	char dir[256];
	char section[256];
	char valueNum[256];

	sprintf_s(section, "�÷��̾� ����");
	sprintf_s(valueNum, "%f", value);

	sprintf_s(dir, "\\%s%d.ini", "saveDATA", currentNum);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	WritePrivateProfileString(section, title, valueNum, str);
}

char* iniDataManager::loadDataString(const char * fileName, const char * subject, const char * title)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	char data[64] = {};
	GetPrivateProfileString(subject, title, "", data, 64, str);

	return data;
}

int iniDataManager::loadDataInterger(const char * fileName, const char * subject, const char * title)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	return GetPrivateProfileInt(subject, title, 0, str);
}
