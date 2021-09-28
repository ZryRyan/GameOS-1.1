#include <iostream>
#include <cstdio>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <graphics.h>
#include <easyx.h>
int row, col;
int k = 0;
int dest[8][9] = { 0 };
IMAGE wall, player, box, end, kd, star;
int map[10][8][9] = { {
	{ 0, 0, 0, 1, 1, 1, 0, 0, 0 },
{ 0, 0, 0, 1, 4, 1, 0, 0, 0 },
{ 1, 1, 1, 1, 2, 1, 0, 0, 0 },
{ 1, 4, 0, 2, 3, 1, 1, 1, 0 },
{ 1, 1, 1, 2, 0, 2, 4, 1, 0 },
{ 0, 0, 1, 0, 1, 1, 1, 1, 0 },
{ 0, 0, 1, 4, 1, 1, 1, 1, 0 },
{ 0, 0, 1, 1, 1, 0, 0, 0, 0 }
	},
{
{ 1, 1, 1, 1, 1, 1, 1, 1,},
{ 1, 4, 0, 0, 1, 0, 0, 1,},
{ 1, 0, 3, 0, 0, 2, 0, 1,},
{ 1, 1, 0, 1, 0, 0, 0, 1,},
{ 1, 4, 0, 0, 0, 2, 0, 1,},
{ 1, 1, 0, 0, 1, 0, 0, 1,},
{ 1, 4, 0, 0, 2, 0, 0, 1,},
{ 1, 1, 1, 1, 1, 1, 1, 1,}
} };

void loadImg() {
	loadimage(&wall, L"ǽ.jpg", 75, 75);
	loadimage(&kd, L"�յ�.jpg", 75, 75);
	loadimage(&box, L"����.jpg", 75, 75);
	loadimage(&player, L"��.jpg", 75, 75);
	loadimage(&end, L"Ŀ�ĵ�.jpg", 75, 75);
	loadimage(&star, L"Ŀ�ĵ�+����.jpg", 75, 75);
}
void showMap()
{
	//init();//��������
		   //�������飬��ӡ��״
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 9; ++j)
			switch (map[k][i][j])
			{
			case 0:
				putimage(i * 75, j * 75, &kd);//�յ�0
				break;
			case 1:
				putimage(i * 75, j * 75, &wall);//ǽ1
				break;
			case 2:
				putimage(i * 75, j * 75, &box);//����2
				break;
			case 3:
				putimage(i * 75, j * 75, &player);//��3
				break;
			case 4:
				putimage(i * 75, j * 75, &end);//Ŀ�ĵ�4
				break;
				//case 5:
				//	printf("��");//
				//	break;
			case 6:
				putimage(i * 75, j * 75, &star);//����+Ŀ�ĵ� 2+4=6
				break;
			case 7:
				putimage(i * 75, j * 75, &player); //��+Ŀ�ĵ�7 3+4=7
				break;
			default:
				break;
			}
		//printf("\n");
	}
}
//��Ϸ����
//����
void playGameUp()
{
	//���������ǽ1����������
	if (map[k][row - 1][col] == 1)
		return;
	//������������ӣ���������������ǽ���������ӣ���������
	if (map[k][row - 1][col] == 2 && (map[k][row - 2][col] == 1 || map[k][row - 2][col] == 2))
		return;
	//�����ǿ����ߵ�����
	//��1������������ǿյ�0��������
	if (map[k][row - 1][col] == 0 || map[k][row - 1][col] == 4)
	{
		map[k][row][col] -= 3;
		map[k][row - 1][col] += 3;
	}
	//��2�����������Ŀ�ĵ�
	/*if (map[row - 1][col] == 4)
	{
	map[row][col] -= 3;
	map[row - 1][col] = 7;
	}*/
	//�����������δ�����Ժϵ�һ��
	//�������δ���Ҳ���Ժϵ�һ��
	//(3)������������ӣ����Ӱ������յ�+���ӣ����ߣ�Ŀ�ĵ�+���ӣ�������������������(3)�յػ���(4)Ŀ�ĵأ��˺�����ͬʱ��
	if ((map[k][row - 1][col] == 2 || map[k][row - 1][col] == 6) && (map[k][row - 2][col] == 0 || map[k][row - 2][col] == 4))
	{
		map[k][row][col] -= 3;
		map[k][row - 1][col] += 1;
		map[k][row - 2][col] += 2;
	}
	row--;

}
//�������������ߣ����ߣ����ߣ�����������
//������
void playGameDown()
{
	//���������ǽ����������
	if (map[k][row + 1][col] == 1)
		return;
	//������������ӣ���������������ǽ���������ӣ���������
	if (map[k][row + 1][col] == 2 && (map[k][row + 2][col] == 1 || map[k][row + 2][col] == 2))
		return;
	//��1������������ǿյ�0�������� ��2�������������Ŀ�ĵ�
	if (map[k][row + 1][col] == 0 || map[k][row + 1][col] == 4)
	{
		map[k][row][col] -= 3;
		map[k][row + 1][col] += 3;
	}

	//(3)������������ӣ����Ӱ������յ�+���ӣ����ߣ�Ŀ�ĵ�+���ӣ�������������������(3)�յػ���(4)Ŀ�ĵأ��˺�����ͬʱ��
	if ((map[k][row + 1][col] == 2 || map[k][row + 1][col] == 6) && (map[k][row + 2][col] == 0 || map[k][row + 2][col] == 4))
	{
		map[k][row][col] -= 3;
		map[k][row + 1][col] += 1;
		map[k][row + 2][col] += 2;
	}
	row++;
}
//������
void playGameLeft()
{
	//���������ǽ����������
	if (map[k][row][col - 1] == 1)
		return;
	//������������ӣ���������������ǽ���������ӣ���������
	if (map[k][row][col - 1] == 2 && (map[k][row][col - 2] == 1 || map[k][row][col - 2] == 2))
		return;
	//��1������������ǿյ�0�������ߣ�2�������������Ŀ�ĵ�
	if (map[k][row][col - 1] == 0 || map[k][row][col - 1] == 4)
	{
		map[k][row][col] -= 3;
		map[k][row][col - 1] += 3;
	}

	//(3)������������ӣ����Ӱ������յ�+���ӣ����ߣ�Ŀ�ĵ�+���ӣ�������������������(3)�յػ���(4)Ŀ�ĵأ��˺�����ͬʱ��
	if ((map[k][row][col - 1] == 2 || map[k][row][col - 1] == 6) && (map[k][row][col - 2] == 0 || map[k][row][col - 2] == 4))
	{
		map[k][row][col] -= 3;
		map[k][row][col - 1] += 1;
		map[k][row][col - 2] += 2;
	}
	col--;
}
void playGameRight()
{
	//���������ǽ1����������
	if (map[k][row][col + 1] == 1)
		return;
	//������������ӣ���������������ǽ���������ӣ���������
	if (map[k][row][col + 1] == 2 && (map[k][row][col + 2] == 1 || map[k][row][col + 2] == 2))
		return;
	//��1������������ǿյ�0�������ߣ�2�����������Ŀ�ĵ�
	if (map[k][row][col + 1] == 0 || map[k][row][col + 1] == 4)
	{
		map[k][row][col] -= 3;
		map[k][row][col + 1] += 3;
	}

	//(3)������������ӣ����Ӱ������յ�+���ӣ����ߣ�Ŀ�ĵ�+���ӣ�������������������(3)�յػ���(4)Ŀ�ĵأ��˺�����ͬʱ��
	if ((map[k][row][col + 1] == 2 || map[k][row][col + 1] == 6) && (map[k][row][col + 2] == 0 || map[k][row][col + 2] == 4))
	{
		map[k][row][col] -= 3;
		map[k][row][col + 1] += 1;
		map[k][row][col + 2] += 2;
	}
	col++;
}
void getOpCh()
{
	char op;
	op = _getch();

	switch (op)
	{
	case 'a':
		playGameUp();
		break;
	case 'd':
		playGameDown();
		break;
	case 'w':
		playGameLeft();
		break;
	case 's':
		playGameRight();
		break;

	default:
		break;
	}
}

void Box() {
	initgraph(8 * 75, 9 * 75);
	loadImg();
	while (1)
	{
		//�Ƿ�ȫ��ͨ�صı�־
		//	bool all = false; //����û��ȫ��ͨ��
		showMap();
		//��ȡ�˵�λ��
		for (int i = 0; i < 8; ++i)
			for (int j = 0; j < 9; ++j)
			{
				if (map[k][i][j] == 3)
				{
					row = i;
					col = j;
					break;
				}
			}
		//��ȡĿ�ĵ������
		for (int i = 0; i < 8; ++i)
			for (int j = 0; j < 9; ++j)
				if (map[k][i][j] == 4)
					dest[i][j] = 4;
		while (1)
		{
			//�����ֶ�������
			getOpCh();
			showMap();
			//�ж�һ���Ƿ����
			bool next = true;
			for (int i = 0; i < 8; ++i)
				for (int j = 0; j < 9; ++j)
				{
					if (dest[i][j])
					{
						if (map[k][i][j] != 6)
							next = false;
					}
				}

			//�ж�һ��,�Ƿ����
			if (next)
			{
				k++;
				memset(dest, 0, sizeof(dest));
				//�ؿ�ֻ��2������k==2����ʾȫ��ͨ��
				if (k == 2)
				{
					if (MessageBox(GetForegroundWindow(), _T("�Ƿ��˳�"), _T("��Ϸ����"), MB_YESNO) == IDYES)
					{
						closegraph();
						return;
					}
					else {
						closegraph();
						return;
					}
				}
				else
				{
					MessageBox(NULL, TEXT("����ͨ��"), TEXT("���������"), MB_OK);
					break;
				}
			}
		}
	}
	return ;
}