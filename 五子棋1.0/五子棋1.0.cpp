#define _CRT_SECURE_NO_WARNINGS 1

#define ROW 15 //行
#define COL 15 //列

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

void title();//标题
void game();
void initialization(char arr[ROW][COL]);//初始化数组
void checkerboard(char arr[ROW][COL]);//棋盘
int judgment(char arr[ROW][COL]);//判断输赢
void ai(char arr[ROW][COL], int row, int col);//电脑下棋
int Subscript_x(char arr[ROW][COL], char* h);//求二维数组某一元素下标行
int Subscript_y(char arr[ROW][COL], char* h);//求二维数组某一元素下标列
char* horizontal(char arr[ROW][COL], int a);//寻找横方向多连子
char* vertical(char arr[ROW][COL], int a);//寻找竖方向多连子
char* lefttilt(char arr[ROW][COL], int a);//寻找'\'方向多连子
char* righttilt(char arr[ROW][COL], int a);//寻找'/'方向多连子
void move_horizontal(char arr[ROW][COL], int i, int j, int a);//连上横方向连子 - #
void move_vertical(char arr[ROW][COL], int i, int j, int a);//连上竖方向连子 - #
void move_lefttilt(char arr[ROW][COL], int i, int j, int a);//连上'\'方向连子 - #
void move_righttilt(char arr[ROW][COL], int i, int j, int a);//连上'/'方向连子 - #

int main()
{
	int a;
	srand((unsigned int)time(NULL));
	do
	{
		title();//标题
		printf("\n请输入'1'或'0'\n");
		scanf("%d", &a);
		printf("\n");
		switch (a)
		{
		case 1:
			game();//游戏
			break;
		case 0:
			printf("\n退出游戏\n");
			break;
		default:
			printf("\n输入错误！请重新输入\n");
			break;
		}
	} while (a);
	return 0;
}

void title()//标题
{
	printf("**************************\n");
	printf("******** 五 子 棋 ********\n");
	printf("**** 1 开始 ** 0 退出 ****\n");
	printf("**************************\n");
}

void game()//游戏
{
	int round;//回合
	int row, col, sy, zf = 1;
	char arr[ROW][COL] = { 0 };
	round = 1;//回合数
	initialization(arr);//初始化数组
	checkerboard(arr);//棋盘
	printf("\t**第%d回合**\n", round);
	while (1)
	{
		if (1 == zf)
		{
			while (1)
			{
				printf("\n* 玩家走（输入棋盘坐标,“行 列”用空格隔开,输入后敲回车）：\n");
				scanf("%d%d", &row, &col);
				if ((row<1 || row>ROW) || (col<1 || col>COL))
					printf("\n输入非法，请重新输入\n");
				else if (arr[row - 1][col - 1] != ' ')
					printf("\n该位置已占用，请重新输入\n");
				else
					break;
			}
			arr[row - 1][col - 1] = '*';
			checkerboard(arr);
			printf("\t**第%d回合**\n", round);
			sy = judgment(arr);//判断输赢
		}
		else
		{
			printf("\n# 电脑走（思考中...）\n");
			ai(arr, row - 1, col - 1);
			round++;//回合数加1
			checkerboard(arr);
			printf("\t**第%d回合**\n", round);
			sy = judgment(arr);
		}
		switch (sy)
		{
		case 1:
			printf("\n  *** 玩家赢！***\n\n");
			return;
		case 2:
			printf("\n  ### 电脑赢！###\n\n");
			return;
		case 3:
			printf("\n  === 平局！===\n\n");
			return;
		case 0:
			zf = -zf;
			break;
		}
	}
}

void initialization(char arr[ROW][COL])
{
	int i, j, x = 0;
	for (i = 0; i < ROW; i++)//初始化数组
	{
		for (j = 0; j < COL; j++)
		{
			arr[i][j] = ' ';
		}
	}
}

//─ ┼ │ ╔ ═ ║ ╗ ╚  ╝ ╟ ╢ ╤ ╧
void checkerboard(char arr[ROW][COL])//棋盘
{
	int i, j;
	system("cls");//清屏
	for (i = 1; i <= COL; i++)//横坐标
	{
		if (i == 1)
			printf("   ");
		printf("%2d ", i);
		if (i < COL)
			printf("│");
	}
	printf("\n");
	for (i = 0; i < COL; i++)//棋盘上横框
	{
		if (i == 0)
			printf("  ╔");
		printf("═══");
		if (i != COL - 1)
			printf("╤");
		if (i == COL - 1)
			printf("╗");
	}
	printf("\n");
	for (i = 0; i < ROW; i++)//打印棋盘
	{
		printf("%-2d", i + 1);//纵坐标
		printf("║");//棋盘左纵框
		for (j = 0; j < COL; j++)
		{
			printf(" %c ", arr[i][j]);
			if (j < COL - 1)
				printf("│");
			if (j == COL - 1)
				printf("║");//棋盘右纵框
		}
		printf("\n");
		if (i < ROW - 1)
		{
			printf("─ ╟");//棋盘左纵框
			for (j = 0; j < COL; j++)
			{
				printf("───");
				if (j < COL - 1)
					printf("┼");
				if (j == COL - 1)
					printf("╢");//棋盘右纵框
			}
			printf("\n");
		}
	}
	for (i = 0; i < COL; i++)//棋盘下横框
	{
		if (i == 0)
			printf("  ╚");
		printf("═══");
		if (i != COL - 1)
			printf("╧");
		if (i == COL - 1)
			printf("╝");
	}
	printf("\n");
}

int judgment(char arr[ROW][COL])//判断输赢，玩家赢：1，电脑赢：2，平局：3，继续：0
{
	char* h = NULL;
	int connect = 5;//5连子
	h = horizontal(arr, connect);//寻找横向5连子
	if (NULL != h)
	{
		if ('*' == *h)
			return 1;
		else if ('#' == *h)
			return 2;
	}
	h = vertical(arr, connect);//寻找竖方向5连子
	if (NULL != h)
	{
		if ('*' == *h)
			return 1;
		else if ('#' == *h)
			return 2;
	}
	h = lefttilt(arr, connect);//寻找'\'方向5连子
	if (NULL != h)
	{
		if ('*' == *h)
			return 1;
		else if ('#' == *h)
			return 2;
	}
	h = righttilt(arr, connect);//寻找'/'方向5连子
	if (NULL != h)
	{
		if ('*' == *h)
			return 1;
		else if ('#' == *h)
			return 2;
	}
	for (int i = 0; i < ROW; i++)//判断是否继续
	{
		for (int j = 0; j < COL; j++)
		{
			if (arr[i][j] == ' ')
				return 0;
		}
	}
	return 3;//平局
}

void ai(char arr[ROW][COL], int row, int col)//电脑走
{
	char* h = NULL;
	Sleep(1000);//延迟1秒，假装电脑在思考
	for (int connect = 4; connect >= 3; connect--)//阻止玩家连子
	{
		h = horizontal(arr, connect);//寻找玩家横向连子 - *
		if ((NULL != h) && ('*' == *h))
		{
			move_horizontal(arr, Subscript_x(arr, h), Subscript_y(arr, h), connect);//阻止横方向连子
			return;
		}
		h = vertical(arr, connect);//寻找玩家竖方向连子 - *
		if ((NULL != h) && ('*' == *h))
		{
			move_vertical(arr, Subscript_x(arr, h), Subscript_y(arr, h), connect);//阻止竖方向连子
			return;
		}
		h = lefttilt(arr, connect);//寻找玩家'\'方向连子 - *
		if ((NULL != h) && ('*' == *h))
		{
			move_lefttilt(arr, Subscript_x(arr, h), Subscript_y(arr, h), connect);//阻止'\'方向连子
			return;
		}
		h = righttilt(arr, connect);//寻找玩家'/'方向连子 - *
		if ((NULL != h) && ('*' == *h))
		{
			move_righttilt(arr, Subscript_x(arr, h), Subscript_y(arr, h), connect);//阻止'/'方向连子
			return;
		}
	}
	for (int connect = 4; connect >= 2; connect--)//连上自己连子
	{
		h = horizontal(arr, connect);//寻找自己横向连子 - #
		if ((NULL != h) && ('#' == *h))
		{
			move_horizontal(arr, Subscript_x(arr, h), Subscript_y(arr, h), connect);//连上横方向连子
			return;
		}
		h = vertical(arr, connect);//寻找自己竖方向连子 - #
		if ((NULL != h) && ('#' == *h))
		{
			move_vertical(arr, Subscript_x(arr, h), Subscript_y(arr, h), connect);//连上竖方向连子
			return;
		}
		h = lefttilt(arr, connect);//寻找自己'\'方向连子 - #
		if ((NULL != h) && ('#' == *h))
		{
			move_lefttilt(arr, Subscript_x(arr, h), Subscript_y(arr, h), connect);//连上'\'方向连子
			return;
		}
		h = righttilt(arr, connect);//寻找玩家'/'方向连子 - #
		if ((NULL != h) && ('#' == *h))
		{
			move_righttilt(arr, Subscript_x(arr, h), Subscript_y(arr, h), connect);//连上'/'方向连子
			return;
		}
	}
	//一颗子周围8子分布情况
	//-1   -1       -1   0       -1   +1
	// 0   -1      【0   0】      0   +1
	//+1   -1       +1   0       +1   +1

	//没有发现连子，电脑自己下子
	switch (0)
	{
	case 0:
		if ((row > 0 && col > 0) && arr[row - 1][col - 1] == ' ')
		{
			goto z;
		}
	case 1:
		if (row > 0 && arr[row - 1][col] == ' ')
		{
			goto z;
		}
	case 2:
		if ((row > 0 && col < COL - 1) && arr[row - 1][col + 1] == ' ')
		{
			goto z;
		}
	case 3:
		if (col < COL - 1 && arr[row][col + 1] == ' ')
		{
			goto z;
		}
	case 4:
		if ((row < ROW - 1 && col < COL - 1) && arr[row + 1][col + 1] == ' ')
		{
			goto z;
		}
	case 5:
		if (row < ROW - 1 && arr[row + 1][col] == ' ')
		{
			goto z;
		}
	case 6:
		if ((row < ROW - 1 && col > 0) && arr[row + 1][col - 1] == ' ')
		{
			goto z;
		}
	case 7:
		if (col > 0 && arr[row][col - 1] == ' ')
		{
			goto z;
		}
	}
z:
	while (1)
	{
		switch (rand() % 8)
		{
		case 0:
			if ((row > 0 && col > 0) && arr[row - 1][col - 1] == ' ')
			{
				arr[row - 1][col - 1] = '#';
				return;
			}
		case 1:
			if (row > 0 && arr[col - 1][col] == ' ')
			{
				arr[row - 1][col] = '#';
				return;
			}
		case 2:
			if ((row > 0 && col < COL - 1) && arr[row - 1][col + 1] == ' ')
			{
				arr[row - 1][col + 1] = '#';
				return;
			}
		case 3:
			if (col < COL - 1 && arr[row][col + 1] == ' ')
			{
				arr[row][col + 1] = '#';
				return;
			}
		case 4:
			if ((row < ROW - 1 && col < COL - 1) && arr[row + 1][col + 1] == ' ')
			{
				arr[row + 1][col + 1] = '#';
				return;
			}
		case 5:
			if (row < ROW - 1 && arr[row + 1][col] == ' ')
			{
				arr[row + 1][col] = '#';
				return;
			}
		case 6:
			if ((row < ROW - 1 && col>0) && arr[row + 1][col - 1] == ' ')
			{
				arr[row + 1][col - 1] = '#';
				return;
			}
		case 7:
			if (row > 0 && arr[row][col - 1] == ' ')
			{
				arr[row][col - 1] = '#';
				return;
			}
		}
	}
}

int Subscript_x(char arr[ROW][COL], char* h)//求二维数组某一元素下标行
{
	if ((h - &arr[0][0]) < COL)
		return 0;
	else
		return (h - &arr[0][0]) / COL;
}

int Subscript_y(char arr[ROW][COL], char* h)//求二维数组某一元素下标列
{
	return (h - &arr[0][0]) % COL;
}

char* horizontal(char arr[ROW][COL], int a)//寻找横方向多连子
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL - 3; j++)
		{
			if (arr[i][j] != ' ')
			{
				for (int z = 1; z < a; z++)
				{
					if (arr[i][j] != arr[i][j + z])
						break;
					else if (a == (z + 1))
					{
						if ((j > 0 && arr[i][j - 1] == ' ') || (j < COL - 1 && arr[i][j + a] == ' '))
							return &arr[i][j];
					}
				}
			}

		}
	}
	return NULL;
}

char* vertical(char arr[ROW][COL], int a)//寻找竖方向多连子
{
	for (int j = 0; j < COL; j++)
	{
		for (int i = 0; i < ROW - 3; i++)
		{
			if (arr[i][j] != ' ')
			{
				for (int z = 1; z < a; z++)
				{
					if (arr[i][j] != arr[i + z][j])
						break;
					else if (a == (z + 1))
					{
						if ((i > 0 && arr[i - 1][j] == ' ') || (i < ROW - 1 && arr[i + a][j] == ' '))
							return &arr[i][j];
					}
				}
			}
		}
	}
	return NULL;
}

char* lefttilt(char arr[ROW][COL], int a)//寻找'\'方向多连子
{
	for (int i = 0; i < ROW - 3; i++)
	{
		for (int j = 0; j < COL - 3; j++)
		{
			if (arr[i][j] != ' ')
			{
				for (int z = 1; z < a; z++)
				{
					if (arr[i][j] != arr[i + z][j + z])
						break;
					else if (a == (z + 1))
					{
						if (((i > 0 && j > 0) && (arr[i - 1][j - 1] == ' ')) || ((i < ROW - 1 && j < COL - 1) && (arr[i + a][j + a] == ' ')))
							return &arr[i][j];
					}
				}
			}
		}
	}
	return NULL;
}

char* righttilt(char arr[ROW][COL], int a)//寻找'/'方向多连子
{
	for (int i = 0; i < ROW - 3; i++)
	{
		for (int j = COL - 1; j > 2; j--)
		{
			if (arr[i][j] != ' ')
			{
				for (int z = 1; z < a; z++)
				{
					if (arr[i][j] != arr[i + z][j - z])
						break;
					else if (a == (z + 1))
					{
						if (((i > 0 && j < COL - 1) && (arr[i - 1][j + 1] == ' ')) || ((i < ROW - 1 && j > 0) && (arr[i + a][j - a] == ' ')))
							return &arr[i][j];
					}
				}
			}
		}
	}
	return NULL;
}

void move_horizontal(char arr[ROW][COL], int i, int j, int a)//连上横方向连子 - #
{
	if ((j > 0 && arr[i][j - 1] == ' ') && (j < COL - 1 && arr[i][j + a] == ' '))
	{
		if (0 == (rand() % 2))
		{
			arr[i][j - 1] = '#';
			return;
		}
		else
		{
			arr[i][j + a] = '#';
			return;
		}
	}
	else if (j > 0 && arr[i][j - 1] == ' ')
	{
		arr[i][j - 1] = '#';
		return;
	}
	else if (j < COL - 1 && arr[i][j + a] == ' ')
	{
		arr[i][j + a] = '#';
		return;
	}
}

void move_vertical(char arr[ROW][COL], int i, int j, int a)//连上竖方向连子 - #
{
	if ((i > 0 && arr[i - 1][j] == ' ') && (i < ROW - 1 && arr[i + a][j] == ' '))
	{
		if (0 == rand() % 2)
		{
			arr[i - 1][j] = '#';
			return;
		}
		else
		{
			arr[i + a][j] = '#';
			return;
		}
	}
	else if (i > 0 && arr[i - 1][j] == ' ')
	{
		arr[i - 1][j] = '#';
		return;
	}
	else if (i < ROW - 1 && arr[i + a][j] == ' ')
	{
		arr[i + a][j] = '#';
		return;
	}
}

void move_lefttilt(char arr[ROW][COL], int i, int j, int a)//连上'\'方向连子 - #
{
	if ((i > 0 && j > 0) && (arr[i - 1][j - 1] == ' ') && (i < ROW - 1 && j < COL - 1) && (arr[i + a][j + a] == ' '))
	{
		if (0 == rand() % 2)
		{
			arr[i - 1][j - 1] = '#';
			return;
		}
		else
		{
			arr[i + a][j + a] = '#';
			return;
		}
	}
	else if ((i > 0 && j > 0) && arr[i - 1][j - 1] == ' ')
	{
		arr[i - 1][j - 1] = '#';
		return;
	}
	else if ((i < ROW - 1 && j < COL - 1) && arr[i + a][j + a] == ' ')
	{
		arr[i + a][j + a] = '#';
		return;
	}
}

void move_righttilt(char arr[ROW][COL], int i, int j, int a)//连上'/'方向连子 - #
{
	if ((i > 0 && j < COL - 1) && (arr[i - 1][j + 1] == ' ') && (i < ROW - 1 && j > 0) && (arr[i + a][j - a] == ' '))
	{
		if (rand() % 2 == 0)
		{
			arr[i - 1][j + 1] = '#';
			return;
		}
		else
		{
			arr[i + a][j - a] = '#';
			return;
		}
	}
	else if ((i > 0 && j < COL - 1) && arr[i - 1][j + 1] == ' ')
	{
		arr[i - 1][j + 1] = '#';
		return;
	}
	else if ((i < ROW - 1 && j > 0) && arr[i + a][j - a] == ' ')
	{
		arr[i + a][j - a] = '#';
		return;
	}
}