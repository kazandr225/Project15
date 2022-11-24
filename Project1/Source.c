#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <time.h>

time_t time(time_t* ttime);
HANDLE hThread[2];

int tm(int cntrl) //����
{
	
	int start, end; //��� �����������
	int ms = 0;
	int ns = 0;
	int sec = 0;
	int min = 0;
	int hr = 0;
	start = clock();

	int hr2, min2, sec2; //��� �������
	if (cntrl == 2)
	{
		printf("������� ���������� �����: ");
		scanf_s("%i", &hr2);

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
			if (min > 59)
			{
				hr = hr + 1;
				min = 0;
			}
			printf("%d:%d:%d.%d\r", hr, min, sec, ms);
		}
		control();
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
			else if (sec2 == 0 && min2 == 0 && hr > 0)
			{
				sec2 = 59;
				min2 = 59;
				hr--;
				printf("%d:%d:%d\r", hr, min2, sec2);
			}
			else if (sec2 == 0 && min2 == 0 && hr == 0)
			{
				printf("������ ��������\r");
				printf("%d:%d:%d\r", hr, min2, sec2);
				control();
			}	
		}
		break;
	case 3:
		printf("���� ��������\n");
		while (GetAsyncKeyState(VK_ESCAPE) == 0)
		{
			SYSTEMTIME st;
			GetLocalTime(&st);
			printf("%d:%d:%d\r", st.wHour, st.wMinute, st.wSecond);
			Sleep(970);
		}
		system("cls");
		control();
		break;
	}
	
	system("cls");
	//control();
}

int control() //���������� ������
{
	printf_s(" 1 - ����� �����������;\n 2 - �����; 3 - ����� � �����;\n 4 - ������ �������;\n 5 - ������ �����;\n");
	int command;
	printf("������� ����� ����������: ");
	scanf_s("%d", &command);
	printf("\n");

	switch (command)
	{
	case 1:
		printf("������ �����������\n");
		hThread[1] = CreateThread(NULL, 0, tm, 1, 0, 0);
		break;
	case 2:
		printf("����� ��������� �� �����\n");
		hThread[1] = SuspendThread(1);
		//SuspendThread(hThread[1]);
		control();
		break;
	case 3:
		printf("������ ������ ������������\n");
		hThread[1] = ResumeThread(1);
		//ResumeThread(hThread[1]);
		control();
		break;
	case 4:
		printf("����� �������\n");
		hThread[1] = CreateThread(NULL, 0, tm, 2, 0, 0);
		break;
	case 5:
		printf("����� �����\n");
		hThread[1] = CreateThread(NULL, 0, tm, 3, 0, 0);
		break;
	default:
		CloseHandle(hThread[0]);
		CloseHandle(hThread[1]);
		break;
	}
	ExitThread(0);
}

int main()
{
	system("chcp 1251>nul");
	control();
}