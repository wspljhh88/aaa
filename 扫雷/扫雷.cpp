#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>

void setColor(unsigned short ForeColor, unsigned short BackGroundColor);//设置字体颜色
void title(int t);//标题
void** parr(int x, int y);//创建一个根据难度不同而大小不同的二维数组
void game(int** arr, int x, int y, int Landmine);//游戏
void initialization(int** arr, int x, int y, int Landmine);//初始化
void distributed(int** arr, int x, int y, int a, int b);//设置雷周围数字分布
void distributed_Landmine(int** arr, int x, int y, int a, int b);//一个空格周围雷的数量
void checkerboard(int** arr, int x, int y, int Remaining, int operating);//打印棋盘
int judgment(int** arr, int x, int y);//判断输赢

int g_round;//回合
int g_cursor_x, g_cursor_y;//光标

int main()
{
	char Key_value = 75;//记录键值
	char input = 75;//保存键值
	srand((unsigned int)time(NULL));
	SetConsoleTitle(L"扫雷");//改标题栏名字
	system("color E0");//设置窗口颜色(背景，字体)
	do
	{
		system("mode con cols=38 lines=14");//设置窗口大小
		title(input);
		input = _getch();
		//printf("%d\n", input);//上72， 下80， 左75， 右77， 回车13， 空格32， 退格8
		switch (input)
		{
		case 77://右
			Key_value = input;
			title(input);
			break;
		case 75://左
			Key_value = input;
			title(input);
			break;
		case 13://回车
			if (75 == Key_value)
			{
				int ret = 0;
				title(ret);
				do
				{
					input = _getch();
					switch (input)//难度选择 0：简单  1：普通  2：困难
					{
					case 80://下
						ret++;
						if (ret > 2)
							ret = 0;
						title(ret);
						break;
					case 72://上
						ret--;
						if (ret < 0)
							ret = 2;
						title(ret);
						break;
					case 13:
						if (0 == ret)
						{
							system("mode con cols=40 lines=23");
							game((int**)parr(9, 9), 9, 9, 10);//二维数组地址，9行，9列，10颗雷
						}
						else if (1 == ret)
						{
							system("mode con cols=67 lines=35");
							game((int**)parr(16, 16), 16, 16, 40);
						}
						else if(2 == ret)
						{
							system("mode con cols=125 lines=35");
							game((int**)parr(16, 30), 16, 30, 99);
						}
						else
						{
							printf("未添加自定义\n");//未添加自定义
						}
						break;
					case 8://退格
						input = 0;
						break;
					}
				} while (input);
				input = 75;//防止退出游戏
				title(input);
			}
			else
			{
				input = 0;
			}
			break;
		}
	} while (input);
	system("cls");
	printf("\n * 按任意键退出\n");
	_getch();
	return 0;
}

void setColor(unsigned short ForeColor = 7, unsigned short BackGroundColor = 0)//设置字体颜色(字颜色，背景颜色)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//获取当前窗口句柄
	SetConsoleTextAttribute(handle, ForeColor + BackGroundColor * 0x10);//设置颜色
}


void title(int t)
{
	int a = rand() % 16;
	system("cls");
	setColor(rand() % 16, 14);
	printf("**************************************\n");
	setColor(a, 14);
	printf("**************");
	setColor(rand() % 16, 14);
	printf("  扫  雷  ");
	setColor(a, 14);
	printf("**************\n");
	setColor(rand() % 16, 14);
	printf("**************************************\n");
	setColor(0, 14);
	printf("\n");
	switch (t)
	{
	case 75:
		setColor(5, 3);
		printf("\t╔═══════╗ \n");
		printf("\t║ -开始-║ ");
		setColor(0, 14);
		printf("   -退出-\n");
		setColor(5, 3);
		printf("\t╚═══════╝ \n");
		setColor(0, 14);
		printf("\n\n\n\n\n * 使用键盘左右键选择，回车键确定\n");
		break;
	case 77:
		printf("\t\t   ");
		setColor(5, 3);
		printf("╔═══════╗ \n");
		setColor(0, 14);
		printf("\t  -开始-   ");
		setColor(5, 3);
		printf("║ -退出-║ \n");
		setColor(0, 14);
		printf("\t\t   ");
		setColor(5, 3);
		printf("╚═══════╝ \n");
		setColor(0, 14);
		printf("\n\n\n\n\n * 使用键盘左右键选择，回车键确定\n");
		break;
	case 0:
		setColor(5, 3);
		printf("\t\t简单\n");
		setColor(0, 14);
		printf("\n\t\t普通\n");
		printf("\n\t\t困难\n");
		printf("\n * 请选择难度\n * 使用键盘上下键选择，回车键确定\n * 退格键返回主菜单\n");
		break;
	case 1:
		printf("\t\t简单\n");
		setColor(5, 3);
		printf("\n\t\t普通\n");
		setColor(0, 14);
		printf("\n\t\t困难\n");
		printf("\n * 请选择难度\n * 使用键盘上下键选择，回车键确定\n * 退格键返回主菜单\n");
		break;
	case 2:
		printf("\t\t简单\n");
		printf("\n\t\t普通\n");
		setColor(5, 3);
		printf("\n\t\t困难\n");
		setColor(0, 14);
		printf("\n * 请选择难度\n * 使用键盘上下键选择，回车键确定\n * 退格键返回主菜单\n");
		break;
	}
	
}

void game(int** arr,int x,int y, int Landmine)
{
	int Remaining = Landmine;//剩余雷数
	int operating = 0;//操作步数
	initialization(arr, x, y, Landmine);//初始化
	do
	{
		checkerboard(arr, x, y, Remaining, operating);//打印棋盘
		char c = _getch();
		switch (c)
		{
		case 72://上
			g_cursor_x--;
			if (g_cursor_x < 0)
				g_cursor_x = x - 1;
			break;
		case 80://下
			g_cursor_x++;
			if (g_cursor_x > x - 1)
				g_cursor_x = 0;
			break;
		case 75://左
			g_cursor_y--;
			if(g_cursor_y < 0)
				g_cursor_y = y - 1;
			break;
		case 77://右
			g_cursor_y++;
			if (g_cursor_y > y - 1)
				g_cursor_y = 0;
			break;
		case 32://空格插旗（+20）/取消插旗（-20）
			if ((arr[g_cursor_x][g_cursor_y] >= 10) && (arr[g_cursor_x][g_cursor_y] < 30) && Remaining > 0)
			{
				arr[g_cursor_x][g_cursor_y] += 20;
				Remaining--;
				operating++;
			}
			else if (arr[g_cursor_x][g_cursor_y] >= 30)
			{
				arr[g_cursor_x][g_cursor_y] -= 20;
				Remaining++;
				operating++;
			}
			break;
		case 13://回车挖雷（-10）
			if ((arr[g_cursor_x][g_cursor_y] < 20) && (arr[g_cursor_x][g_cursor_y] >= 10))
			{
				arr[g_cursor_x][g_cursor_y] -= 10;
				operating++;
			}
			break;
		}
		if (!judgment(arr, x, y))//判断输赢，返回0输，返回非零继续
			goto jump;
	} while (1);
jump:
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			if (arr[i][j] >= 30)
				arr[i][j] -= 20;
			else if (arr[i][j] < 20 && arr[i][j] >= 10)
				arr[i][j] -= 10;
		}
	}
	checkerboard(arr, x, y, Remaining, operating);
	printf("\n你输了！！！按任意键继续\n");
	_getch();
}

void** parr(int x, int y)//创建一个根据难度不同而大小不同的二维数组
{
	int** arr = (int**)calloc(x, sizeof(int*));
	for (int i = 0; i < x; i++)
	{
		*(arr + i) = (int*)calloc(y, sizeof(int));
	}
	return (void**)arr;
}

void initialization(int** arr, int x, int y, int Landmine)//初始化
{
	g_round = 0;
	g_cursor_x = g_cursor_y = x / 2;
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			arr[i][j] = 10;
		}
	}
	for (int i = 0; i < Landmine; )//埋雷
	{
		int a = rand() % x, b = rand() % y;
		if (10 == arr[a][b])
		{
			arr[a][b] = 19;
			distributed(arr, x, y, a, b);//设置雷周围数字分布
			i++;
		}
	}
}

void distributed(int** arr, int x, int y, int a, int b)//设置雷周围数字分布
{
	if (a > 0 && b > 0 && arr[a - 1][b - 1] != 19)
		distributed_Landmine(arr, x, y, a - 1, b - 1);
	if (a > 0 && arr[a - 1][b] != 19)
		distributed_Landmine(arr, x, y, a - 1, b);
	if (a > 0 && b < y - 1 && arr[a - 1][b + 1] != 19)
		distributed_Landmine(arr, x, y, a - 1, b + 1);
	if (b < y - 1 && arr[a][b + 1] != 19)
		distributed_Landmine(arr, x, y, a, b + 1);
	if (b < y - 1 && a < x - 1 && arr[a + 1][b + 1] != 19)
		distributed_Landmine(arr, x, y, a + 1, b + 1);
	if (a < x - 1 && arr[a + 1][b] != 19)
		distributed_Landmine(arr, x, y, a + 1, b);
	if (a < x - 1 && b > 0 && arr[a + 1][b - 1] != 19)
		distributed_Landmine(arr, x, y, a + 1, b - 1);
	if (b > 0 && arr[a][b - 1] != 19)
		distributed_Landmine(arr, x, y, a, b - 1);
}

void distributed_Landmine(int** arr, int x, int y, int a, int b)//一个空格周围雷的数量
{
	int count = 10;
	if (a > 0 && b > 0 && arr[a - 1][b - 1] == 19)
		count++;
	if (a > 0 && arr[a - 1][b] == 19)
		count++;
	if (a > 0 && b < y - 1 && arr[a - 1][b + 1] == 19)
		count++;
	if (b < y - 1 && arr[a][b + 1] == 19)
		count++;
	if (b < y - 1 && a < x - 1 && arr[a + 1][b + 1] == 19)
		count++;
	if (a < x - 1 && arr[a + 1][b] == 19)
		count++;
	if (a < x - 1 && b > 0 && arr[a + 1][b - 1] == 19)
		count++;
	if (b > 0 && arr[a][b - 1] == 19)
		count++;
	arr[a][b] = count;
}

void checkerboard(int** arr, int x, int y, int Remaining, int operating)//打印棋盘
{
	system("cls");
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			if (g_cursor_x == i && g_cursor_y == j)
			{
				setColor(0, 12);
				printf(" ");
				setColor(0, 15);
				printf("□");
				setColor(0, 12);
				printf(" ");
				setColor(0, 14);
			}
			else if (arr[i][j] >= 30)
			{
				printf(" ");
				setColor(0, 10);
				printf("⊙");
				setColor(0, 14);
				printf(" ");
			}
			else if (arr[i][j] < 9 && arr[i][j] > 0)
			{
				printf(" ");
				printf("%-2d", arr[i][j]);
				printf(" ");
			}
			else if (0 == arr[i][j])
			{
				printf("    ");
			}
			else if (9 == arr[i][j])
			{
				printf(" ");
				setColor(0, 4);
				printf("*");
				setColor(0, 14);
				printf("  ");
			}
			else
			{
				printf(" ");
				setColor(0, 11);
				printf("□");
				setColor(0, 14);
				printf(" ");
			}
		}
		printf("\n\n");
	}
	printf("步数：%d         剩余地雷：%d\n", operating, Remaining);
}

int judgment(int** arr, int x, int y)//判断输赢
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			if (9 == arr[i][j])
				return 0;
		}
	}
	return 1;
}