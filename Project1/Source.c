#include <Windows.h>
#include <stdio.h>
#include <time.h>

HANDLE hThread[2];

int tm(int cntrl) //����
{
	
	int start, end; //��� �����������
	int ms = 0;
	int ns = 0;
	int sec = 0;
	int min = 0;
	start = clock();

	int min2, sec2; //��� �������
	if (cntrl == 2)
	{
		printf("������� ���������� �����: ");
		scanf_s("%i", &min2);

		printf("������� ���������� ������: ");
		scanf_s("%i", &sec2);
	}

	switch (cntrl)
	{
	case 1:
		while (GetAsyncKeyState(VK_ESCAPE) == 0)
		{
			end = clock();
			ns = end - start;
			ms = ns / 10;
			if (ms > 100)
			{
				sec = sec + 1;
				ms = ms - 100;
				start = end;
			}
			if (sec > 59)
			{
				min = min + 1;
				sec = 0;
			}
			printf("%d:%d.%d\r", min, sec, ms);
		}
		
		break;
	case 2:
		while (GetAsyncKeyState(VK_ESCAPE) == 0)
		{
			Sleep(970); // 970 + 30 = 1 ������� (30 �� ���������)

			if (sec2>0)
			{
				sec2--;
				printf("%d:%d\r", min2, sec2);
			}
			else if (sec2 == 0 && min2 > 0)
			{
				sec2 = 59;
				min2--;
				printf("%d:%d\r", min2, sec2);
			}
			else if (sec2 == 0 && min2 == 0)
			{
				printf("������ ��������\n");
				printf("%d:%d\r", min2, sec2);
			}	
		}
		break;
	}
	
	system("cls");
	control();
	//ExitThread(0);
	
}

int control() //���������� ������
{
	printf_s(" 1 - ����� �����������;\n 2 - �����;\n 3 - ����� � �����;\n 4 - ������ �������;\n");
	int command;
	printf("������� ����� ����������: ");
	scanf_s("%d", &command);
	printf("\n");

	switch (command)
	{
	case 1:
		printf("������ �����������\n");
		hThread[1] = CreateThread(NULL, 0, tm, 1, 0, 0);
		
		control();
	//WaitForMultipleObjects(3, hThread, TRUE, INFINITE);
		break;
	case 2:
		printf("����� ���������� �� �����\n");
		SuspendThread(hThread[1]);
		break;
	case 3:
		printf("����� ���� � �����\n");
		ResumeThread(hThread[1]);
		break;
	case 4:
		printf("����� �������\n");
		hThread[1] = CreateThread(NULL, 0, tm, 2, 0, 0);
		break;
	default:
		printf("������ �� ����������\n");
		break;
	}
	ExitThread(0);
}

int main()
{
	system("chcp 1251>nul");
	control();
}