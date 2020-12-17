#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>

void setColor(unsigned short ForeColor, unsigned short BackGroundColor);//����������ɫ
void title(int t);//����
void** parr(int x, int y);//����һ�������ѶȲ�ͬ����С��ͬ�Ķ�ά����
void game(int** arr, int x, int y, int Landmine);//��Ϸ
void initialization(int** arr, int x, int y, int Landmine);//��ʼ��
void distributed(int** arr, int x, int y, int a, int b);//��������Χ���ֲַ�
void distributed_Landmine(int** arr, int x, int y, int a, int b);//һ���ո���Χ�׵�����
void checkerboard(int** arr, int x, int y, int Remaining, int operating);//��ӡ����
int judgment(int** arr, int x, int y);//�ж���Ӯ

int g_round;//�غ�
int g_cursor_x, g_cursor_y;//���

int main()
{
	char Key_value = 75;//��¼��ֵ
	char input = 75;//�����ֵ
	srand((unsigned int)time(NULL));
	SetConsoleTitle(L"ɨ��");//�ı���������
	system("color E0");//���ô�����ɫ(����������)
	do
	{
		system("mode con cols=38 lines=14");//���ô��ڴ�С
		title(input);
		input = _getch();
		//printf("%d\n", input);//��72�� ��80�� ��75�� ��77�� �س�13�� �ո�32�� �˸�8
		switch (input)
		{
		case 77://��
			Key_value = input;
			title(input);
			break;
		case 75://��
			Key_value = input;
			title(input);
			break;
		case 13://�س�
			if (75 == Key_value)
			{
				int ret = 0;
				title(ret);
				do
				{
					input = _getch();
					switch (input)//�Ѷ�ѡ�� 0����  1����ͨ  2������
					{
					case 80://��
						ret++;
						if (ret > 2)
							ret = 0;
						title(ret);
						break;
					case 72://��
						ret--;
						if (ret < 0)
							ret = 2;
						title(ret);
						break;
					case 13:
						if (0 == ret)
						{
							system("mode con cols=40 lines=23");
							game((int**)parr(9, 9), 9, 9, 10);//��ά�����ַ��9�У�9�У�10����
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
							printf("δ����Զ���\n");//δ����Զ���
						}
						break;
					case 8://�˸�
						input = 0;
						break;
					}
				} while (input);
				input = 75;//��ֹ�˳���Ϸ
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
	printf("\n * ��������˳�\n");
	_getch();
	return 0;
}

void setColor(unsigned short ForeColor = 7, unsigned short BackGroundColor = 0)//����������ɫ(����ɫ��������ɫ)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ��ǰ���ھ��
	SetConsoleTextAttribute(handle, ForeColor + BackGroundColor * 0x10);//������ɫ
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
	printf("  ɨ  ��  ");
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
		printf("\t�X�T�T�T�T�T�T�T�[ \n");
		printf("\t�U -��ʼ-�U ");
		setColor(0, 14);
		printf("   -�˳�-\n");
		setColor(5, 3);
		printf("\t�^�T�T�T�T�T�T�T�a \n");
		setColor(0, 14);
		printf("\n\n\n\n\n * ʹ�ü������Ҽ�ѡ�񣬻س���ȷ��\n");
		break;
	case 77:
		printf("\t\t   ");
		setColor(5, 3);
		printf("�X�T�T�T�T�T�T�T�[ \n");
		setColor(0, 14);
		printf("\t  -��ʼ-   ");
		setColor(5, 3);
		printf("�U -�˳�-�U \n");
		setColor(0, 14);
		printf("\t\t   ");
		setColor(5, 3);
		printf("�^�T�T�T�T�T�T�T�a \n");
		setColor(0, 14);
		printf("\n\n\n\n\n * ʹ�ü������Ҽ�ѡ�񣬻س���ȷ��\n");
		break;
	case 0:
		setColor(5, 3);
		printf("\t\t��\n");
		setColor(0, 14);
		printf("\n\t\t��ͨ\n");
		printf("\n\t\t����\n");
		printf("\n * ��ѡ���Ѷ�\n * ʹ�ü������¼�ѡ�񣬻س���ȷ��\n * �˸���������˵�\n");
		break;
	case 1:
		printf("\t\t��\n");
		setColor(5, 3);
		printf("\n\t\t��ͨ\n");
		setColor(0, 14);
		printf("\n\t\t����\n");
		printf("\n * ��ѡ���Ѷ�\n * ʹ�ü������¼�ѡ�񣬻س���ȷ��\n * �˸���������˵�\n");
		break;
	case 2:
		printf("\t\t��\n");
		printf("\n\t\t��ͨ\n");
		setColor(5, 3);
		printf("\n\t\t����\n");
		setColor(0, 14);
		printf("\n * ��ѡ���Ѷ�\n * ʹ�ü������¼�ѡ�񣬻س���ȷ��\n * �˸���������˵�\n");
		break;
	}
	
}

void game(int** arr,int x,int y, int Landmine)
{
	int Remaining = Landmine;//ʣ������
	int operating = 0;//��������
	initialization(arr, x, y, Landmine);//��ʼ��
	do
	{
		checkerboard(arr, x, y, Remaining, operating);//��ӡ����
		char c = _getch();
		switch (c)
		{
		case 72://��
			g_cursor_x--;
			if (g_cursor_x < 0)
				g_cursor_x = x - 1;
			break;
		case 80://��
			g_cursor_x++;
			if (g_cursor_x > x - 1)
				g_cursor_x = 0;
			break;
		case 75://��
			g_cursor_y--;
			if(g_cursor_y < 0)
				g_cursor_y = y - 1;
			break;
		case 77://��
			g_cursor_y++;
			if (g_cursor_y > y - 1)
				g_cursor_y = 0;
			break;
		case 32://�ո���죨+20��/ȡ�����죨-20��
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
		case 13://�س����ף�-10��
			if ((arr[g_cursor_x][g_cursor_y] < 20) && (arr[g_cursor_x][g_cursor_y] >= 10))
			{
				arr[g_cursor_x][g_cursor_y] -= 10;
				operating++;
			}
			break;
		}
		if (!judgment(arr, x, y))//�ж���Ӯ������0�䣬���ط������
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
	printf("\n�����ˣ����������������\n");
	_getch();
}

void** parr(int x, int y)//����һ�������ѶȲ�ͬ����С��ͬ�Ķ�ά����
{
	int** arr = (int**)calloc(x, sizeof(int*));
	for (int i = 0; i < x; i++)
	{
		*(arr + i) = (int*)calloc(y, sizeof(int));
	}
	return (void**)arr;
}

void initialization(int** arr, int x, int y, int Landmine)//��ʼ��
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
	for (int i = 0; i < Landmine; )//����
	{
		int a = rand() % x, b = rand() % y;
		if (10 == arr[a][b])
		{
			arr[a][b] = 19;
			distributed(arr, x, y, a, b);//��������Χ���ֲַ�
			i++;
		}
	}
}

void distributed(int** arr, int x, int y, int a, int b)//��������Χ���ֲַ�
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

void distributed_Landmine(int** arr, int x, int y, int a, int b)//һ���ո���Χ�׵�����
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

void checkerboard(int** arr, int x, int y, int Remaining, int operating)//��ӡ����
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
				printf("��");
				setColor(0, 12);
				printf(" ");
				setColor(0, 14);
			}
			else if (arr[i][j] >= 30)
			{
				printf(" ");
				setColor(0, 10);
				printf("��");
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
				printf("��");
				setColor(0, 14);
				printf(" ");
			}
		}
		printf("\n\n");
	}
	printf("������%d         ʣ����ף�%d\n", operating, Remaining);
}

int judgment(int** arr, int x, int y)//�ж���Ӯ
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