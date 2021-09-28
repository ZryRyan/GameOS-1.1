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
	loadimage(&wall, L"墙.jpg", 75, 75);
	loadimage(&kd, L"空地.jpg", 75, 75);
	loadimage(&box, L"箱子.jpg", 75, 75);
	loadimage(&player, L"人.jpg", 75, 75);
	loadimage(&end, L"目的地.jpg", 75, 75);
	loadimage(&star, L"目的地+箱子.jpg", 75, 75);
}
void showMap()
{
	//init();//操作介绍
		   //遍历数组，打印形状
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 9; ++j)
			switch (map[k][i][j])
			{
			case 0:
				putimage(i * 75, j * 75, &kd);//空地0
				break;
			case 1:
				putimage(i * 75, j * 75, &wall);//墙1
				break;
			case 2:
				putimage(i * 75, j * 75, &box);//箱子2
				break;
			case 3:
				putimage(i * 75, j * 75, &player);//人3
				break;
			case 4:
				putimage(i * 75, j * 75, &end);//目的地4
				break;
				//case 5:
				//	printf("●");//
				//	break;
			case 6:
				putimage(i * 75, j * 75, &star);//箱子+目的地 2+4=6
				break;
			case 7:
				putimage(i * 75, j * 75, &player); //人+目的地7 3+4=7
				break;
			default:
				break;
			}
		//printf("\n");
	}
}
//游戏规则
//向上
void playGameUp()
{
	//如果向上是墙1，不可以走
	if (map[k][row - 1][col] == 1)
		return;
	//如果向上是箱子，并且箱子上面是墙或者是箱子，不可以走
	if (map[k][row - 1][col] == 2 && (map[k][row - 2][col] == 1 || map[k][row - 2][col] == 2))
		return;
	//下面是可以走的情形
	//（1）如果向上走是空地0，可以走
	if (map[k][row - 1][col] == 0 || map[k][row - 1][col] == 4)
	{
		map[k][row][col] -= 3;
		map[k][row - 1][col] += 3;
	}
	//（2）如果上走是目的地
	/*if (map[row - 1][col] == 4)
	{
	map[row][col] -= 3;
	map[row - 1][col] = 7;
	}*/
	//发现上面俩段代码可以合到一起
	//下面俩段代码也可以合到一起
	//(3)如果向上是箱子（箱子包含（空地+箱子）或者（目的地+箱子）），并且箱子上面是(3)空地或者(4)目的地，人和箱子同时走
	if ((map[k][row - 1][col] == 2 || map[k][row - 1][col] == 6) && (map[k][row - 2][col] == 0 || map[k][row - 2][col] == 4))
	{
		map[k][row][col] -= 3;
		map[k][row - 1][col] += 1;
		map[k][row - 2][col] += 2;
	}
	row--;

}
//接下来，向下走，左走，右走，代码基本差不多
//向下走
void playGameDown()
{
	//如果向下是墙，不可以走
	if (map[k][row + 1][col] == 1)
		return;
	//如果向下是箱子，并且箱子下面是墙或者是箱子，不可以走
	if (map[k][row + 1][col] == 2 && (map[k][row + 2][col] == 1 || map[k][row + 2][col] == 2))
		return;
	//（1）如果向下走是空地0，可以走 （2）如果向下走是目的地
	if (map[k][row + 1][col] == 0 || map[k][row + 1][col] == 4)
	{
		map[k][row][col] -= 3;
		map[k][row + 1][col] += 3;
	}

	//(3)如果向下是箱子（箱子包含（空地+箱子）或者（目的地+箱子）），并且箱子下面是(3)空地或者(4)目的地，人和箱子同时走
	if ((map[k][row + 1][col] == 2 || map[k][row + 1][col] == 6) && (map[k][row + 2][col] == 0 || map[k][row + 2][col] == 4))
	{
		map[k][row][col] -= 3;
		map[k][row + 1][col] += 1;
		map[k][row + 2][col] += 2;
	}
	row++;
}
//向左走
void playGameLeft()
{
	//如果向左是墙，不可以走
	if (map[k][row][col - 1] == 1)
		return;
	//如果向左是箱子，并且箱子左面是墙或者是箱子，不可以走
	if (map[k][row][col - 1] == 2 && (map[k][row][col - 2] == 1 || map[k][row][col - 2] == 2))
		return;
	//（1）如果向左走是空地0，可以走（2）如果向左走是目的地
	if (map[k][row][col - 1] == 0 || map[k][row][col - 1] == 4)
	{
		map[k][row][col] -= 3;
		map[k][row][col - 1] += 3;
	}

	//(3)如果向左是箱子（箱子包含（空地+箱子）或者（目的地+箱子）），并且箱子左面是(3)空地或者(4)目的地，人和箱子同时走
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
	//如果向右是墙1，不可以走
	if (map[k][row][col + 1] == 1)
		return;
	//如果向右是箱子，但是箱子右面是墙或者是箱子，不可以走
	if (map[k][row][col + 1] == 2 && (map[k][row][col + 2] == 1 || map[k][row][col + 2] == 2))
		return;
	//（1）如果向右走是空地0，可以走（2）如果右走是目的地
	if (map[k][row][col + 1] == 0 || map[k][row][col + 1] == 4)
	{
		map[k][row][col] -= 3;
		map[k][row][col + 1] += 3;
	}

	//(3)如果向右是箱子（箱子包含（空地+箱子）或者（目的地+箱子）），并且箱子右面是(3)空地或者(4)目的地，人和箱子同时走
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
		//是否全堵通关的标志
		//	bool all = false; //假设没有全部通关
		showMap();
		//获取人的位置
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
		//获取目的的坐标点
		for (int i = 0; i < 8; ++i)
			for (int j = 0; j < 9; ++j)
				if (map[k][i][j] == 4)
					dest[i][j] = 4;
		while (1)
		{
			//进入手动推箱子
			getOpCh();
			showMap();
			//判断一下是否过关
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

			//判断一下,是否过关
			if (next)
			{
				k++;
				memset(dest, 0, sizeof(dest));
				//关卡只有2个，当k==2，表示全部通关
				if (k == 2)
				{
					if (MessageBox(GetForegroundWindow(), _T("是否退出"), _T("游戏结束"), MB_YESNO) == IDYES)
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
					MessageBox(NULL, TEXT("您已通关"), TEXT("真棒！！！"), MB_OK);
					break;
				}
			}
		}
	}
	return ;
}