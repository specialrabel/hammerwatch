#include "stdafx.h"
#include "collision.h"
#include "mapTool.h"

//�浹�� �䱸�ϴ� ��ü
#include "player.h"
#include "npcManager.h"
#include "enemyManager.h"
#include "Ui.h"

HRESULT collision::init(image* stage)
{
	return S_OK;
}

void collision::release()
{
}

void collision::update()
{
	// �ش� �浹ó�� ������ �Ϸ���, �Ʒ��� �Լ��� Ŭ���ϰ� F12�� �̵��սô�.

	//�÷��̾� 4���� (�����¿� Ÿ���浹 �����Լ�)
	player_AND_CrossTiles();

	//�÷��̾� �밢�� ���� Ÿ���浹 �����Լ�
	player_AND_diagonalTiles();

	player_AND_enemy();

	player_AND_item();

	player_AND_NPC();

	player_AND_blackSmith();

	player_AND_Inn();

	enemy_AND_CrossTiles();

	enemy_AND_diagonalTiles();

	//�÷��̾� ȭ��� �浹ó�� �Լ�
	playerBullet_AND_Anything();

	inventory_AND_item();

}

void collision::render()
{

}

/********************************************************** 4 ���� �浹 *******************************************************************/

void collision::player_AND_CrossTiles()
{
	D2D1_RECT_F collision;

	int tileIndex[2];	//Ÿ�� ���⿡ �ʿ��� �ε���
	int tileX, tileY;	//�÷��̾ ��� �ִ� Ÿ���� �ε���

	//������ ������Ʈ�� ���� ��Ʈ�� ����������
	collision = D2D1::RectF(_player->get_playerInfo().rc.left,
		_player->get_playerInfo().rc.top,
		_player->get_playerInfo().rc.right,
		_player->get_playerInfo().rc.bottom);

	tileX = collision.left / TILESIZE;
	tileY = collision.top / TILESIZE;

	switch (_player->get_playerInfo().moving_direction)
	{
	case Player_Direction::TOP:
		tileIndex[0] = tileX + tileY * TILEX;
		tileIndex[1] = (tileX + 1) + tileY * TILEX;
		break;
	case Player_Direction::BOTTOM:
		tileIndex[0] = (tileX + tileY * TILEX) + TILEX;
		tileIndex[1] = (tileX + 1 + tileY * TILEX) + TILEX;
		break;
	case Player_Direction::LEFT:
		tileIndex[0] = tileX + (tileY * TILEX);
		tileIndex[1] = tileX + (tileY + 1) * TILEX;
		break;
	case Player_Direction::RIGHT:
		tileIndex[0] = (tileX + tileY * TILEX) + 1;
		tileIndex[1] = (tileX + (tileY + 1) * TILEX) + 1;
		break;
	default:
		tileIndex[0] = NULL;
		tileIndex[1] = NULL;
		break;
	}

	for (int i = 0; i < 2; ++i)
	{
		if (tileIndex[i] == NULL) break;

		D2D1_RECT_F rc;
		D2D1_RECT_F tile = _mapTool->getTile()[tileIndex[i]].rc;

		DWORD temp = _mapTool->getObj(tileIndex[i]);

		if (((_mapTool->getTileAttribute()[tileIndex[i]] & ATTR_UNMOVE) == ATTR_UNMOVE) && INTERSECTION_RECT(rc, tile, collision))
		{
			rc = collision;
			_player->set_hit(true);
			switch (_player->get_playerInfo().moving_direction)
			{
			case Player_Direction::LEFT:
				rc.left = tile.right;
				rc.right = rc.left + _player->get_playerInfo().width;

				_player->set_x((rc.left + rc.right) / 2);
				break;

			case Player_Direction::TOP:
				rc.top = tile.bottom;
				rc.bottom = rc.top + _player->get_playerInfo().height;

				_player->set_y((rc.top + rc.bottom) / 2);

				break;
			case Player_Direction::RIGHT:
				rc.right = tile.left;
				rc.left = rc.right - _player->get_playerInfo().width;

				_player->set_x((rc.left + rc.right) / 2);
				break;

			case Player_Direction::BOTTOM:
				rc.bottom = tile.top;
				rc.top = rc.bottom - _player->get_playerInfo().height;

				_player->set_y((rc.top + rc.bottom) / 2);
				break;
			}
			return;
		}
		else
			_player->set_hit(false);
	}
	_player->set_rect();
}


/********************************************************** �밢�� �浹 *******************************************************************/

void collision::player_AND_diagonalTiles()
{
	D2D1_RECT_F collision;

	int tileIndex[3];	//Ÿ�� ���⿡ �ʿ��� �ε���
	int tileX, tileY;	//�÷��̾ ��� �ִ� Ÿ���� �ε���

	//������ ������Ʈ�� ���� ��Ʈ�� ����������
	collision = D2D1::RectF(_player->get_playerInfo().rc.left,
		_player->get_playerInfo().rc.top,
		_player->get_playerInfo().rc.right,
		_player->get_playerInfo().rc.bottom);

	tileX = collision.left / TILESIZE;
	tileY = collision.top / TILESIZE;

	switch (_player->get_playerInfo().moving_direction)
	{
	case Player_Direction::LEFT_TOP:
		tileIndex[0] = tileX + (tileY * TILEX);
		tileIndex[2] = tileX + (tileY + 1) * TILEX;
		tileIndex[1] = (tileX + 1) + tileY * TILEX;
		break;
	case Player_Direction::RIGHT_TOP:
		tileIndex[0] = (tileX + tileY * TILEX) + 1;
		tileIndex[2] = (tileX + (tileY + 1) * TILEX) + 1;
		tileIndex[1] = (tileX)+ tileY * TILEX;
		break;
	case Player_Direction::LEFT_BOTTOM:
		tileIndex[0] = tileX + (tileY * TILEX);
		tileIndex[1] = tileX + (tileY + 1) * TILEX;
		tileIndex[2] = (tileX + 1) + (tileY + 1) * TILEX;
		break;
	case Player_Direction::RIGHT_BOTTOM:
		tileIndex[0] = (tileX + tileY * TILEX) + 1;
		tileIndex[1] = (tileX + (tileY + 1) * TILEX) + 1;
		tileIndex[2] = (tileX)+(tileY + 1) * TILEX;
		break;
	default:
		tileIndex[0] = NULL;
		tileIndex[1] = NULL;
		tileIndex[2] = NULL;
		break;
	}

	for (int i = 0; i < 3; ++i)
	{
		if (tileIndex[i] == NULL) break;

		D2D1_RECT_F temp;
		D2D1_RECT_F tile = _mapTool->getTile()[tileIndex[i]].rc;

		if (((_mapTool->getTileAttribute()[tileIndex[i]] & ATTR_UNMOVE) == ATTR_UNMOVE) && INTERSECTION_RECT(temp, tile, collision))
		{
			_player->set_hit(true);
			switch (_player->get_playerInfo().moving_direction)
			{
			case Player_Direction::LEFT_TOP:

				if (((_mapTool->getTileAttribute()[tileIndex[2]] & ATTR_UNMOVE) == ATTR_UNMOVE))
				{
					if (((_mapTool->getTileAttribute()[tileIndex[1]] & ATTR_UNMOVE) == ATTR_UNMOVE))
					{
						D2D1_RECT_F tile = _mapTool->getTile()[tileIndex[0]].rc;

						collision.left = tile.right;
						collision.right = collision.left + _player->get_playerInfo().width;

						collision.top = tile.bottom;
						collision.bottom = collision.top + _player->get_playerInfo().height;

						_player->set_y((collision.top + collision.bottom) / 2);
					}
					else
					{
						collision.left = tile.right;
						collision.right = collision.left + _player->get_playerInfo().width;
					}
					_player->set_x((collision.left + collision.right) / 2);
				}
				else if (((_mapTool->getTileAttribute()[tileIndex[1]] & ATTR_UNMOVE) == ATTR_UNMOVE))
				{
					collision.top = tile.bottom;
					collision.bottom = collision.top + _player->get_playerInfo().height;

					_player->set_y((collision.top + collision.bottom) / 2);
				}
				else if (temp.right - temp.left > temp.bottom - temp.top)
				{
					collision.top = tile.bottom;
					collision.bottom = collision.top + _player->get_playerInfo().height;

					_player->set_y((collision.top + collision.bottom) / 2);
				}
				else if (temp.right - temp.left < temp.bottom - temp.top)
				{
					collision.left = tile.right;
					collision.right = collision.left + _player->get_playerInfo().width;

					_player->set_x((collision.left + collision.right) / 2);
				}
				break;

			case Player_Direction::RIGHT_TOP:

				if (((_mapTool->getTileAttribute()[tileIndex[2]] & ATTR_UNMOVE) == ATTR_UNMOVE))
				{
					if (((_mapTool->getTileAttribute()[tileIndex[1]] & ATTR_UNMOVE) == ATTR_UNMOVE))
					{
						D2D1_RECT_F tile = _mapTool->getTile()[tileIndex[0]].rc;

						collision.right = tile.left;
						collision.left = collision.right - _player->get_playerInfo().width;

						collision.top = tile.bottom;
						collision.bottom = collision.top + _player->get_playerInfo().height;

						_player->set_y((collision.top + collision.bottom) / 2);

					}
					else
					{
						collision.right = tile.left;
						collision.left = collision.right - _player->get_playerInfo().width;
					}

					_player->set_x((collision.left + collision.right) / 2);
				}
				else if (((_mapTool->getTileAttribute()[tileIndex[1]] & ATTR_UNMOVE) == ATTR_UNMOVE))
				{
					collision.top = tile.bottom;
					collision.bottom = collision.top + _player->get_playerInfo().height;

					_player->set_y((collision.top + collision.bottom) / 2);
				}
				else if (temp.right - temp.left > temp.bottom - temp.top)
				{
					collision.top = tile.bottom;
					collision.bottom = collision.top + _player->get_playerInfo().height;

					_player->set_y((collision.top + collision.bottom) / 2);
				}
				else
				{
					collision.right = tile.left;
					collision.left = collision.right - _player->get_playerInfo().width;

					_player->set_x((collision.left + collision.right) / 2);
				}

				break;
			case Player_Direction::LEFT_BOTTOM:
				if (i == 0)
				{
					collision.left = tile.right;
					collision.right = collision.left + _player->get_playerInfo().width;

					_player->set_x((collision.left + collision.right) / 2);
				}
				else
				{
					collision.bottom = tile.top;
					collision.top = collision.bottom - _player->get_playerInfo().height;

					_player->set_y((collision.top + collision.bottom) / 2);
				}
				break;

			case Player_Direction::RIGHT_BOTTOM:
				if (i == 0)
				{
					collision.right = tile.left;
					collision.left = collision.right - _player->get_playerInfo().width;

					_player->set_x((collision.left + collision.right) / 2);

				}
				else
				{
					collision.bottom = tile.top;
					collision.top = collision.bottom - _player->get_playerInfo().height;

					_player->set_y((collision.top + collision.bottom) / 2);
				}
				break;
			}
		}
		else
			_player->set_hit(false);
	}
	_player->set_rect();
}


/********************************************************** ���ʹ� �浹 *******************************************************************/

void collision::player_AND_enemy()
{
	D2D1_RECT_F player = _player->get_playerInfo().rc;
	for (int i = 0; i < _enemy->get_enemy().size(); i++)
	{
		if (_enemy->get_enemy()[i]->get_kind() == enemy_kind::MAGGOT) continue;

		D2D1_RECT_F enemy = _enemy->get_enemy()[i]->get_hitBox();

		if (INTERSECTION_RECT(temp, player, enemy))
		{
			_enemy->get_enemy()[i]->delete_hitBox();
			_player->set_hp(-8.0f);
			break;
		}
	}

	for (int i = 0; i < _enemy->get_enemy().size(); i++)
	{
		if (_enemy->get_enemy()[i]->get_kind() != enemy_kind::MAGGOT) continue;

		for (int j = 0; j < _enemy->get_enemy()[i]->get_bullet()->getVBullet().size(); j++)
		{
			D2D1_RECT_F maggot_bullet = _enemy->get_enemy()[i]->get_bullet()->getVBullet()[j].rc;

			if (INTERSECTION_RECT(temp, player, maggot_bullet))
			{
				_enemy->get_enemy()[i]->get_bullet()->removeBullet(j);
				_player->set_hp(-8.0f);
				break;
			}
		}
	}
}

void collision::player_AND_item()
{
	Player_Info _player_Info_collision = _player->get_playerInfo();

	int num = ITEMMANAGER->getAllItemNum();
	int j = 0;

	//������ �����۵� ������ Ȯ��
	for (int i = 0; i < num; i++)
	{
		float x = ITEMMANAGER->getItemX(i);
		float y = ITEMMANAGER->getItemY(i);

		float distance = getDistance(_player_Info_collision.x, _player_Info_collision.y, x, y);

		//�����۰��� �Ÿ��� ���������
		if (distance < 32)
		{
			//�÷��̾� �ڵ� ���� ����
			bool check = _player->check_and_aoto_pickup_item(ITEMMANAGER->getItemData(i));
			//�������� ���
			if (check)
			{
				ITEMMANAGER->deletItem(i);
				break;
			}

			//�ֿ�� �ִ� �������� ���
			if (ITEMMANAGER->getItemData(i).kind == HAVING)
			{
				//������ ���� ����� ����
				j++;
				//��ȣ�ۿ� �̹���
				ITEMMANAGER->setInteractionItem(_player_Info_collision.x - 8, _player_Info_collision.y - 48, 3);

				//������ ���� Ű��
				ITEMMANAGER->setDescription(
					_player_Info_collision.x - 100,
					_player_Info_collision.y - 150,
					ITEMMANAGER->getItemData(i)
				);
				//������ �ݱ�
				if (KEYMANAGER->isOnceKeyDown('F'))
				{
					_player->set_item(ITEMMANAGER->getItemData(i));
					ITEMMANAGER->deletItem(i);
					break;
				}
			}
			
		}
	}
	if (j == 0)
	{
		ITEMMANAGER->setInteractionItem();
		ITEMMANAGER->setDescription();
	}
}


void collision::player_AND_NPC()
{
	Player_Info _player_Info_collision = _player->get_playerInfo();

	float playerX = _player_Info_collision.x;
	float playerY = _player_Info_collision.y;
	D2D1_RECT_F playerRc = _player_Info_collision.rc;

	int num = _npcManager->getNpcNum();

	//��ȣ�ۿ� �̹��� off
	int j = 0;

	for (int i = 0; i < num; i++)
	{
		D2D1_RECT_F NpcRc = _npcManager->getNpcRc(i);
		float npcX = _npcManager->getNpcX(i);
		float npcY = _npcManager->getNpcY(i);

		float distance = getDistance(playerX, playerY, npcX, npcY);



		if (distance < 64)
		{
			//��ó�� ������ ��� ��ȣ�ۿ� �̹���
			ITEMMANAGER->setInteractionNpc(playerX - 8, playerY - 48, 0);
			j++;
			//�浹
			if (INTERSECTION_RECT(temp, playerRc, NpcRc))
			{
				//����, �¿� �浹 Ȯ��
				if ((temp.bottom - temp.top) <= (temp.right - temp.left))
				{
					if (NpcRc.top > playerRc.top)
					{
						playerY = NpcRc.top - 16;
						_player->set_y(playerY);
						break;
					}
					if (NpcRc.bottom < playerRc.bottom)
					{
						playerY = NpcRc.bottom + 16;
						_player->set_y(playerY);
						break;
					}
				}
				if ((temp.bottom - temp.top) > (temp.right - temp.left))
				{
					if (NpcRc.left > playerRc.left)
					{
						playerX = NpcRc.left - 16;
						_player->set_x(playerX);
						break;
					}
					if (NpcRc.right < playerRc.right)
					{
						playerX = NpcRc.right + 16;
						_player->set_x(playerX);
						break;
					}
				}
			}
			//��ȣ�ۿ��� �Ұ��
			if (KEYMANAGER->isOnceKeyDown('F'))
			{
				//���� ������ 0 �̻��ϰ�� ���� â ����, ���߿� �� NCP�� ����â�� ���� �ְ� ���� �ʿ�
				if (_npcManager->getNpcLevel(i) > 0)
				{
					_npcManager->setInteraction(i, true);
					switch (_npcManager->getNpcKind(i))
					{
					case BLACKSMITH:
						_ui->setIsBlackSmithUi(true);
						_boolBlackSmith = true;
						_npcManager->setPlayerGold(_player->get_playerResource().gold);
						break;
					case TOWNHALL:
						_ui->setIsInnUi(true);
						_boolInn = true;
						_npcManager->setPlayerOre(_player->get_playerResource().ore);

						break;
					case SKILL:
						break;
					}

				}
				else
				{
					_npcManager->setChat(i);
				}
			}
			//����Ǿ��� ���
			if (!_boolBlackSmith && !_boolInn)
			{
				_npcManager->setInteraction(i);
			}
		}

	}
	if (j == 0) ITEMMANAGER->setInteractionNpc();
}

void collision::playerBullet_AND_Anything()
{
	// �÷��̾� : ������ ȭ��� �浹�ϴ� ���͵�
	for (int j = 0; j < _player->get_arrow()->getVBullet().size(); j++)
	{
		D2D1_RECT_F rc;
		D2D1_RECT_F arrow = D2DMANAGER->RectMake(_player->get_arrow()->getVBullet()[j].rc.left, _player->get_arrow()->getVBullet()[j].rc.top, _player->get_arrow()->getVBullet()[j].height, _player->get_arrow()->getVBullet()[j].height);
		//�ʰ� �浹
		for (int i = 0; i < TILEX* TILEY; ++i)
		{
			D2D1_RECT_F tile = _mapTool->getTile()[i].rc;

			if (((_mapTool->getTileAttribute()[i] & ATTR_UNMOVE) == ATTR_UNMOVE) &&
				INTERSECTION_RECT(rc, tile, arrow))
			{
				_player->get_arrow()->removeBullet(j);
				EFFECTMANAGER->play("arrow", arrow.left, arrow.top);
				break;
			}
		}

		for (int  i = 0; i <_enemy->get_enemy().size(); i++)
		{
			D2D1_RECT_F enemy = _enemy->get_enemy()[i]->get_rect();

			if (INTERSECTION_RECT(rc, arrow, enemy))
			{
				_player->get_arrow()->removeBullet(j);
				_enemy->get_enemy()[i]->set_hp(-_player->get_playerStatus().damage);
				EFFECTMANAGER->play("arrow", arrow.left, arrow.top);
				break;
			}
		}
	}

	// �÷��̾� ��Ʈ�ڽ��� ���ʹ� �浹
	for (int i = 0; i < _enemy->get_enemy().size(); i++)
	{
		if (_player->get_playerStatus().player_class == Player_Class::Ranger) continue;

		D2D1_RECT_F enemy = _enemy->get_enemy()[i]->get_rect();

		for (int j = 0; j < _player->get_hitBox()->getVBullet().size(); j++)
		{
			D2D1_RECT_F hitBox = _player->get_hitBox()->getVBullet()[j].rc;

			if (INTERSECTION_RECT(temp, enemy, hitBox))
			{
				_player->get_hitBox()->removeBullet(j);
				_enemy->get_enemy()[i]->set_hp(-_player->get_playerStatus().damage);
				break;
			}
		}
	}
}

/********************************************************** ���ʹ� Ÿ�� �浹 *******************************************************************/

void collision::enemy_AND_CrossTiles()
{
	for (int i = 0; i < _enemy->get_enemy().size(); i++)
	{
		if (_enemy->get_enemy()[i]->get_kind() == enemy_kind::BATS) continue;

		D2D1_RECT_F collision;

		int tileIndex[2];	//Ÿ�� ���⿡ �ʿ��� �ε���
		int tileX, tileY;	//�÷��̾ ��� �ִ� Ÿ���� �ε���

		//������ ������Ʈ�� ���� ��Ʈ�� ����������
		collision = _enemy->get_enemy()[i]->get_rect();

		tileX = collision.left / TILESIZE;
		tileY = collision.top / TILESIZE;

		switch (_enemy->get_enemy()[i]->get_direction())
		{
		case enemy_direction::TOP:
			tileIndex[0] = tileX + tileY * TILEX;
			tileIndex[1] = (tileX + 1) + tileY * TILEX;
			break;
		case enemy_direction::BOTTOM:
			tileIndex[0] = (tileX + tileY * TILEX) + TILEX;
			tileIndex[1] = (tileX + 1 + tileY * TILEX) + TILEX;
			break;
		case enemy_direction::LEFT:
			tileIndex[0] = tileX + (tileY * TILEX);
			tileIndex[1] = tileX + (tileY + 1) * TILEX;
			break;
		case enemy_direction::RIGHT:
			tileIndex[0] = (tileX + tileY * TILEX) + 1;
			tileIndex[1] = (tileX + (tileY + 1) * TILEX) + 1;
			break;

		default:
			tileIndex[0] = NULL;
			tileIndex[1] = NULL;
			break;
		}

		for (int j = 0; j < 2; ++j)
		{
			if (tileIndex[j] == NULL) break;

			D2D1_RECT_F rc;
			D2D1_RECT_F tile = _mapTool->getTile()[tileIndex[j]].rc;

			if (((_mapTool->getTileAttribute()[tileIndex[j]] & ATTR_UNMOVE) == ATTR_UNMOVE) && INTERSECTION_RECT(rc, tile, collision))
			{
				rc = collision;
				float width = collision.right - collision.left;
				float height = collision.bottom - collision.top;

				switch (_enemy->get_enemy()[i]->get_direction())
				{
				case enemy_direction::LEFT:
					rc.left = tile.right;
					rc.right = rc.left + width;

					_enemy->get_enemy()[i]->set_left(tile.right);
					break;

				case enemy_direction::TOP:
					rc.top = tile.bottom;
					rc.bottom = rc.top + height;

					_enemy->get_enemy()[i]->set_top(tile.bottom);

					break;
				case enemy_direction::RIGHT:
					rc.right = tile.left;
					rc.left = rc.right - width;

					_enemy->get_enemy()[i]->set_right(tile.left);
					break;

				case enemy_direction::BOTTOM:
					rc.bottom = tile.top;
					rc.top = rc.bottom - height;

					_enemy->get_enemy()[i]->set_bottom(tile.top);
					break;
				}
			}
		}
	}
}


/********************************************************** ���ʹ� �밢�� Ÿ�� �浹 *******************************************************************/

void collision::enemy_AND_diagonalTiles()
{
	D2D1_RECT_F collision;

	int tileIndex[3];	//Ÿ�� ���⿡ �ʿ��� �ε���
	int tileX, tileY;	//�÷��̾ ��� �ִ� Ÿ���� �ε���

	for (int i = 0; i < _enemy->get_enemy().size(); i++)
	{
		if (_enemy->get_enemy()[i]->get_kind() == enemy_kind::BATS) continue;

		//������ ������Ʈ�� ���� ��Ʈ�� ����������
		collision = _enemy->get_enemy()[i]->get_rect();

		tileX = collision.left / TILESIZE;
		tileY = collision.top / TILESIZE;

		switch (_enemy->get_enemy()[i]->get_direction())
		{
		case enemy_direction::LEFT_TOP:
			tileIndex[0] = tileX + (tileY * TILEX);
			tileIndex[2] = tileX + (tileY + 1) * TILEX;
			tileIndex[1] = (tileX + 1) + tileY * TILEX;
			break;
		case enemy_direction::RIGHT_TOP:
			tileIndex[0] = (tileX + tileY * TILEX) + 1;
			tileIndex[2] = (tileX + (tileY + 1) * TILEX) + 1;
			tileIndex[1] = (tileX)+tileY * TILEX;
			break;
		case enemy_direction::LEFT_BOTTOM:
			tileIndex[0] = tileX + (tileY * TILEX);
			tileIndex[1] = tileX + (tileY + 1) * TILEX;
			tileIndex[2] = (tileX + 1) + (tileY + 1) * TILEX;
			break;
		case enemy_direction::RIGHT_BOTTOM:
			tileIndex[0] = (tileX + tileY * TILEX) + 1;
			tileIndex[1] = (tileX + (tileY + 1) * TILEX) + 1;
			tileIndex[2] = (tileX)+(tileY + 1) * TILEX;
			break;
		default:
			tileIndex[0] = NULL;
			tileIndex[1] = NULL;
			tileIndex[2] = NULL;
			break;
		}

		for (int j = 0; j < 3; ++j)
		{
			if (tileIndex[j] == NULL) break;

			D2D1_RECT_F temp;
			D2D1_RECT_F tile = _mapTool->getTile()[tileIndex[j]].rc;

			float width = collision.right - collision.left;
			float height = collision.bottom - collision.top;

			if (((_mapTool->getTileAttribute()[tileIndex[j]] & ATTR_UNMOVE) == ATTR_UNMOVE) && INTERSECTION_RECT(temp, tile, collision))
			{
				switch (_enemy->get_enemy()[i]->get_direction())
				{
				case enemy_direction::LEFT_TOP:

					if (((_mapTool->getTileAttribute()[tileIndex[2]] & ATTR_UNMOVE) == ATTR_UNMOVE))
					{
						if (((_mapTool->getTileAttribute()[tileIndex[1]] & ATTR_UNMOVE) == ATTR_UNMOVE))
						{
							D2D1_RECT_F tile = _mapTool->getTile()[tileIndex[0]].rc;

							collision.left = tile.right;
							collision.right = collision.left + width;

							collision.top = tile.bottom;
							collision.bottom = collision.top + height;

							_enemy->get_enemy()[i]->set_top(tile.bottom);
						}
						else
						{
							collision.left = tile.right;
							collision.right = collision.left + width;
						}
						_enemy->get_enemy()[i]->set_left(tile.right);
					}
					else if (((_mapTool->getTileAttribute()[tileIndex[1]] & ATTR_UNMOVE) == ATTR_UNMOVE))
					{
						collision.top = tile.bottom;
						collision.bottom = collision.top + height;

						_enemy->get_enemy()[i]->set_top(tile.bottom);
					}
					else if (temp.right - temp.left > temp.bottom - temp.top)
					{
						collision.top = tile.bottom;
						collision.bottom = collision.top + height;

						_enemy->get_enemy()[i]->set_top(tile.bottom);
					}
					else if (temp.right - temp.left < temp.bottom - temp.top)
					{
						collision.left = tile.right;
						collision.right = collision.left + width;

						_enemy->get_enemy()[i]->set_left(tile.right);
					}
					break;

				case enemy_direction::RIGHT_TOP:

					if (((_mapTool->getTileAttribute()[tileIndex[2]] & ATTR_UNMOVE) == ATTR_UNMOVE))
					{
						if (((_mapTool->getTileAttribute()[tileIndex[1]] & ATTR_UNMOVE) == ATTR_UNMOVE))
						{
							D2D1_RECT_F tile = _mapTool->getTile()[tileIndex[0]].rc;

							collision.right = tile.left;
							collision.left = collision.right - width;

							collision.top = tile.bottom;
							collision.bottom = collision.top + height;

							_enemy->get_enemy()[i]->set_top(tile.bottom);

						}
						else
						{
							collision.right = tile.left;
							collision.left = collision.right - width;
						}

						_enemy->get_enemy()[i]->set_right(tile.left);
					}
					else if (((_mapTool->getTileAttribute()[tileIndex[1]] & ATTR_UNMOVE) == ATTR_UNMOVE))
					{
						collision.top = tile.bottom;
						collision.bottom = collision.top + height;

						_enemy->get_enemy()[i]->set_top(tile.bottom);
					}
					else if (temp.right - temp.left > temp.bottom - temp.top)
					{
						collision.top = tile.bottom;
						collision.bottom = collision.top + height;

						_enemy->get_enemy()[i]->set_top(tile.bottom);
					}
					else
					{
						collision.right = tile.left;
						collision.left = collision.right - width;

						_enemy->get_enemy()[i]->set_right(tile.left);
					}
					break;
				case enemy_direction::LEFT_BOTTOM:
					if (j == 0)
					{
						collision.left = tile.right;
						collision.right = collision.left + width;

						_enemy->get_enemy()[i]->set_left(tile.right);
					}
					else
					{
						collision.bottom = tile.top;
						collision.top = collision.bottom - height;

						_enemy->get_enemy()[i]->set_bottom(tile.top);
					}
					break;

				case enemy_direction::RIGHT_BOTTOM:
					if (j == 0)
					{
						collision.right = tile.left;
						collision.left = collision.right - width;

						_enemy->get_enemy()[i]->set_right(tile.left);

					}
					else
					{
						collision.bottom = tile.top;
						collision.top = collision.bottom - height;

						_enemy->get_enemy()[i]->set_bottom(tile.top);
					}
					break;
				}
			}
		}
	}
}

void collision::inventory_AND_item()
{
	//�κ��丮 ������ Ȯ��
	int num = ITEMMANAGER->getAllItemNumInventory();
	int j = 0;
	//������ �����۵� ������ Ȯ��
	for (int i = 0; i < num; i++)
	{
		float x = ITEMMANAGER->getItemXInventory(i);
		float y = ITEMMANAGER->getItemYInventory(i);

		float distance = getDistance(_ptMouse.x, _ptMouse.y, x, y);

		//�����۰��� �Ÿ��� ���������
		if (distance < 32)
		{

			//������ ���� ����� ����
			j++;

			//������ ���� Ű��
			ITEMMANAGER->setDescriptionInventory(
				_ptMouse.x - 100,
				_ptMouse.y - 150,
				ITEMMANAGER->getItemDataInventory(i)
			);

		}
		if (j == 0)
		{
			ITEMMANAGER->setDescriptionInventory();
		}
	}
	if (num == 0)
	{
		ITEMMANAGER->setDescriptionInventory();
	}
}

void collision::player_AND_blackSmith()
{

	if (_boolBlackSmith)
	{
		//ī�޶� ����
		float cam_x = CAMERAMANAGER->get_camera_x();
		float cam_y = CAMERAMANAGER->get_camera_y();

		//��ư
		RECT rc1 = { 475 + cam_x, 348 + cam_y, 1125 + cam_x, 424 + cam_y };
		RECT rc2 = { 475 + cam_x, 425 + cam_y, 1125 + cam_x, 500 + cam_y };
		RECT rc3 = { 475 + cam_x, 501 + cam_y, 1125 + cam_x, 576 + cam_y };
		RECT rc4 = { 475 + cam_x, 577 + cam_y, 1125 + cam_x, 652 + cam_y };
		RECT rc5 = { 1084 + cam_x, 300 + cam_y, 1120 + cam_x, 335 + cam_y };

		//Ŭ���� ���� �ִٸ� ���׷��̵�
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (PtInRect(&rc1, _ptMouse))
			{
				if (_npcManager->getBlackSmithLevel() >= _npcManager->getBlackSmithUpgardeDataLevel(1))
				{
					if (_player->get_playerResource().gold >= _npcManager->getBlackSmithGold(1))
					{
						_player->set_gold(-(_npcManager->getBlackSmithGold(1)));
						_npcManager->setBlackSmithUpgrade(1);
						_npcManager->setPlayerGold(_player->get_playerResource().gold);
						_player->set_upgrade_attack(_npcManager->getBlackSmithUpgardeData(1));
					}
				}

			}
			if (PtInRect(&rc2, _ptMouse))
			{
				if (_npcManager->getBlackSmithLevel() >= _npcManager->getBlackSmithUpgardeDataLevel(2))
				{
					if (_player->get_playerResource().gold >= _npcManager->getBlackSmithGold(2))
					{
						_player->set_gold(-(_npcManager->getBlackSmithGold(2)));
						_npcManager->setBlackSmithUpgrade(2);
						_npcManager->setPlayerGold(_player->get_playerResource().gold);
						_player->set_upgrade_armor(_npcManager->getBlackSmithUpgardeData(2));
					}
				}

			}
			if (PtInRect(&rc3, _ptMouse))
			{
				if (_npcManager->getBlackSmithLevel() >= _npcManager->getBlackSmithUpgardeDataLevel(3))
				{
					if (_player->get_playerResource().gold >= _npcManager->getBlackSmithGold(3))
					{
						_player->set_gold(-(_npcManager->getBlackSmithGold(3)));
						_npcManager->setBlackSmithUpgrade(3);
						_npcManager->setPlayerGold(_player->get_playerResource().gold);
						_player->set_upgrade_crit(_npcManager->getBlackSmithUpgardeData(3));
					}
				}

			}
			if (PtInRect(&rc4, _ptMouse))
			{
				if (_npcManager->getBlackSmithLevel() >= _npcManager->getBlackSmithUpgardeDataLevel(4))
				{
					if (_player->get_playerResource().gold >= _npcManager->getBlackSmithGold(4))
					{
						_player->set_gold(-(_npcManager->getBlackSmithGold(4)));
						_npcManager->setBlackSmithUpgrade(4);
						_npcManager->setPlayerGold(_player->get_playerResource().gold);
						_player->set_upgrade_speed(_npcManager->getBlackSmithUpgardeData(4));
					}
				}

			}
			if (PtInRect(&rc5, _ptMouse))
			{
				_ui->setIsBlackSmithUi(false);
				_boolBlackSmith = false;
			}
		}
		// ui���� ���� ���� ���
		_boolBlackSmith = _ui->getIsBlackSmithUi();
	}


}

void collision::player_AND_Inn()
{

	if (_boolInn)
	{
		//ī�޶� ����
		float cam_x = CAMERAMANAGER->get_camera_x();
		float cam_y = CAMERAMANAGER->get_camera_y();

		//��ư
		RECT rc1 = { 1242 + cam_x, 242 + cam_y, 1280 + cam_x, 282 + cam_y };
		/*RECT rc2 = { 475, 425, 1125, 500 };
		RECT rc3 = { 475, 501, 1125, 576 };
		RECT rc4 = { 475, 577, 1125, 652 };
		RECT rc5 = { 1084, 300, 1120, 335 };*/

		//Ŭ���� ������ �ִٸ� ���׷��̵�
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (PtInRect(&rc1, _ptMouse))
			{
				_ui->setIsInnUi(false);
				_boolInn = false;
			}

			_npcManager->upgradeCheck();
			_player->set_ore(_npcManager->getPlayerOre());
			_npcManager->setBlackSmithLevel(_npcManager->getBlackSmithLevel());

		}
		// ui���� ���� ���� ���
		_boolInn = _ui->getIsInnUI();
	}

}
