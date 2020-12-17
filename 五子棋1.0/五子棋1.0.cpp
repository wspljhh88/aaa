#define _CRT_SECURE_NO_WARNINGS 1

#define ROW 15 //��
#define COL 15 //��

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

void title();//����
void game();
void initialization(char arr[ROW][COL]);//��ʼ������
void checkerboard(char arr[ROW][COL]);//����
int judgment(char arr[ROW][COL]);//�ж���Ӯ
void ai(char arr[ROW][COL], int row, int col);//��������
int Subscript_x(char arr[ROW][COL], char* h);//���ά����ĳһԪ���±���
int Subscript_y(char arr[ROW][COL], char* h);//���ά����ĳһԪ���±���
char* horizontal(char arr[ROW][COL], int a);//Ѱ�Һ᷽�������
char* vertical(char arr[ROW][COL], int a);//Ѱ�������������
char* lefttilt(char arr[ROW][COL], int a);//Ѱ��'\'���������
char* righttilt(char arr[ROW][COL], int a);//Ѱ��'/'���������
void move_horizontal(char arr[ROW][COL], int i, int j, int a);//���Ϻ᷽������ - #
void move_vertical(char arr[ROW][COL], int i, int j, int a);//�������������� - #
void move_lefttilt(char arr[ROW][COL], int i, int j, int a);//����'\'�������� - #
void move_righttilt(char arr[ROW][COL], int i, int j, int a);//����'/'�������� - #

int main()
{
	int a;
	srand((unsigned int)time(NULL));
	do
	{
		title();//����
		printf("\n������'1'��'0'\n");
		scanf("%d", &a);
		printf("\n");
		switch (a)
		{
		case 1:
			game();//��Ϸ
			break;
		case 0:
			printf("\n�˳���Ϸ\n");
			break;
		default:
			printf("\n�����������������\n");
			break;
		}
	} while (a);
	return 0;
}

void title()//����
{
	printf("**************************\n");
	printf("******** �� �� �� ********\n");
	printf("**** 1 ��ʼ ** 0 �˳� ****\n");
	printf("**************************\n");
}

void game()//��Ϸ
{
	int round;//�غ�
	int row, col, sy, zf = 1;
	char arr[ROW][COL] = { 0 };
	round = 1;//�غ���
	initialization(arr);//��ʼ������
	checkerboard(arr);//����
	printf("\t**��%d�غ�**\n", round);
	while (1)
	{
		if (1 == zf)
		{
			while (1)
			{
				printf("\n* ����ߣ�������������,���� �С��ÿո����,������ûس�����\n");
				scanf("%d%d", &row, &col);
				if ((row<1 || row>ROW) || (col<1 || col>COL))
					printf("\n����Ƿ�������������\n");
				else if (arr[row - 1][col - 1] != ' ')
					printf("\n��λ����ռ�ã�����������\n");
				else
					break;
			}
			arr[row - 1][col - 1] = '*';
			checkerboard(arr);
			printf("\t**��%d�غ�**\n", round);
			sy = judgment(arr);//�ж���Ӯ
		}
		else
		{
			printf("\n# �����ߣ�˼����...��\n");
			ai(arr, row - 1, col - 1);
			round++;//�غ�����1
			checkerboard(arr);
			printf("\t**��%d�غ�**\n", round);
			sy = judgment(arr);
		}
		switch (sy)
		{
		case 1:
			printf("\n  *** ���Ӯ��***\n\n");
			return;
		case 2:
			printf("\n  ### ����Ӯ��###\n\n");
			return;
		case 3:
			printf("\n  === ƽ�֣�===\n\n");
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
	for (i = 0; i < ROW; i++)//��ʼ������
	{
		for (j = 0; j < COL; j++)
		{
			arr[i][j] = ' ';
		}
	}
}

//�� �� �� �X �T �U �[ �^  �a �c �f �h �k
void checkerboard(char arr[ROW][COL])//����
{
	int i, j;
	system("cls");//����
	for (i = 1; i <= COL; i++)//������
	{
		if (i == 1)
			printf("   ");
		printf("%2d ", i);
		if (i < COL)
			printf("��");
	}
	printf("\n");
	for (i = 0; i < COL; i++)//�����Ϻ��
	{
		if (i == 0)
			printf("  �X");
		printf("�T�T�T");
		if (i != COL - 1)
			printf("�h");
		if (i == COL - 1)
			printf("�[");
	}
	printf("\n");
	for (i = 0; i < ROW; i++)//��ӡ����
	{
		printf("%-2d", i + 1);//������
		printf("�U");//�������ݿ�
		for (j = 0; j < COL; j++)
		{
			printf(" %c ", arr[i][j]);
			if (j < COL - 1)
				printf("��");
			if (j == COL - 1)
				printf("�U");//�������ݿ�
		}
		printf("\n");
		if (i < ROW - 1)
		{
			printf("�� �c");//�������ݿ�
			for (j = 0; j < COL; j++)
			{
				printf("������");
				if (j < COL - 1)
					printf("��");
				if (j == COL - 1)
					printf("�f");//�������ݿ�
			}
			printf("\n");
		}
	}
	for (i = 0; i < COL; i++)//�����º��
	{
		if (i == 0)
			printf("  �^");
		printf("�T�T�T");
		if (i != COL - 1)
			printf("�k");
		if (i == COL - 1)
			printf("�a");
	}
	printf("\n");
}

int judgment(char arr[ROW][COL])//�ж���Ӯ�����Ӯ��1������Ӯ��2��ƽ�֣�3��������0
{
	char* h = NULL;
	int connect = 5;//5����
	h = horizontal(arr, connect);//Ѱ�Һ���5����
	if (NULL != h)
	{
		if ('*' == *h)
			return 1;
		else if ('#' == *h)
			return 2;
	}
	h = vertical(arr, connect);//Ѱ��������5����
	if (NULL != h)
	{
		if ('*' == *h)
			return 1;
		else if ('#' == *h)
			return 2;
	}
	h = lefttilt(arr, connect);//Ѱ��'\'����5����
	if (NULL != h)
	{
		if ('*' == *h)
			return 1;
		else if ('#' == *h)
			return 2;
	}
	h = righttilt(arr, connect);//Ѱ��'/'����5����
	if (NULL != h)
	{
		if ('*' == *h)
			return 1;
		else if ('#' == *h)
			return 2;
	}
	for (int i = 0; i < ROW; i++)//�ж��Ƿ����
	{
		for (int j = 0; j < COL; j++)
		{
			if (arr[i][j] == ' ')
				return 0;
		}
	}
	return 3;//ƽ��
}

void ai(char arr[ROW][COL], int row, int col)//������
{
	char* h = NULL;
	Sleep(1000);//�ӳ�1�룬��װ������˼��
	for (int connect = 4; connect >= 3; connect--)//��ֹ�������
	{
		h = horizontal(arr, connect);//Ѱ����Һ������� - *
		if ((NULL != h) && ('*' == *h))
		{
			move_horizontal(arr, Subscript_x(arr, h), Subscript_y(arr, h), connect);//��ֹ�᷽������
			return;
		}
		h = vertical(arr, connect);//Ѱ��������������� - *
		if ((NULL != h) && ('*' == *h))
		{
			move_vertical(arr, Subscript_x(arr, h), Subscript_y(arr, h), connect);//��ֹ����������
			return;
		}
		h = lefttilt(arr, connect);//Ѱ�����'\'�������� - *
		if ((NULL != h) && ('*' == *h))
		{
			move_lefttilt(arr, Subscript_x(arr, h), Subscript_y(arr, h), connect);//��ֹ'\'��������
			return;
		}
		h = righttilt(arr, connect);//Ѱ�����'/'�������� - *
		if ((NULL != h) && ('*' == *h))
		{
			move_righttilt(arr, Subscript_x(arr, h), Subscript_y(arr, h), connect);//��ֹ'/'��������
			return;
		}
	}
	for (int connect = 4; connect >= 2; connect--)//�����Լ�����
	{
		h = horizontal(arr, connect);//Ѱ���Լ��������� - #
		if ((NULL != h) && ('#' == *h))
		{
			move_horizontal(arr, Subscript_x(arr, h), Subscript_y(arr, h), connect);//���Ϻ᷽������
			return;
		}
		h = vertical(arr, connect);//Ѱ���Լ����������� - #
		if ((NULL != h) && ('#' == *h))
		{
			move_vertical(arr, Subscript_x(arr, h), Subscript_y(arr, h), connect);//��������������
			return;
		}
		h = lefttilt(arr, connect);//Ѱ���Լ�'\'�������� - #
		if ((NULL != h) && ('#' == *h))
		{
			move_lefttilt(arr, Subscript_x(arr, h), Subscript_y(arr, h), connect);//����'\'��������
			return;
		}
		h = righttilt(arr, connect);//Ѱ�����'/'�������� - #
		if ((NULL != h) && ('#' == *h))
		{
			move_righttilt(arr, Subscript_x(arr, h), Subscript_y(arr, h), connect);//����'/'��������
			return;
		}
	}
	//һ������Χ8�ӷֲ����
	//-1   -1       -1   0       -1   +1
	// 0   -1      ��0   0��      0   +1
	//+1   -1       +1   0       +1   +1

	//û�з������ӣ������Լ�����
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

int Subscript_x(char arr[ROW][COL], char* h)//���ά����ĳһԪ���±���
{
	if ((h - &arr[0][0]) < COL)
		return 0;
	else
		return (h - &arr[0][0]) / COL;
}

int Subscript_y(char arr[ROW][COL], char* h)//���ά����ĳһԪ���±���
{
	return (h - &arr[0][0]) % COL;
}

char* horizontal(char arr[ROW][COL], int a)//Ѱ�Һ᷽�������
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

char* vertical(char arr[ROW][COL], int a)//Ѱ�������������
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

char* lefttilt(char arr[ROW][COL], int a)//Ѱ��'\'���������
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

char* righttilt(char arr[ROW][COL], int a)//Ѱ��'/'���������
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

void move_horizontal(char arr[ROW][COL], int i, int j, int a)//���Ϻ᷽������ - #
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

void move_vertical(char arr[ROW][COL], int i, int j, int a)//�������������� - #
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

void move_lefttilt(char arr[ROW][COL], int i, int j, int a)//����'\'�������� - #
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

void move_righttilt(char arr[ROW][COL], int i, int j, int a)//����'/'�������� - #
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