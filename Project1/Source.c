#include <Windows.h>
#include <stdio.h>
#include <time.h>

VOID control();
VOID tm(int cntrl);
HANDLE hThread[2];
int n = 0;

int main()
{
	system("chcp 1251>nul");

	hThread[0] = CreateThread(NULL, 0, control, NULL, 0, 0);
	hThread[1] = CreateThread(NULL, 0, tm, NULL, 0, 0);
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

	/*int a[2];
	GetExitCodeThread(hThread[0],a);
	GetExitCodeThread(hThread[1], a+1);
	printf("1 ����� - %d, 2 ����� - %d", *a, *(a+1));

	for (size_t i = 0; i < 2 ; i++)
	{
		CloseHandle(hThread[i]);
	}

	return 0;*/
}


VOID tm(int cntrl) //����
{
	
	int start, end;
	int ms = 0;
	int ns = 0;
	int sec = 0;
	int min = 0;
	start = clock();

	
	//printf("�����: ");
	//scanf_s("%d", &cntl);
	switch (cntrl)
	{
	case 1:
		while (1)
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
		/*print_s("������� ���������� �����");
		scanf_s("%d", &min);
		print_s("������� ���������� ������");
		scanf_s("%d", &sec);
			
		start = clock();
		ns = start - end;
		ms = ns * 10;
		
		if (ms < 0)
		{
			sec = sec - 1;
			ms = ms + 100;
			end = start;
		}
		if (sec < 0)
		{
			min = min - 1;
			sec = 0;
		}

		printf("%d:%d.%d\r", min, sec, ms);*/
		break;
	}

	
}

VOID control() //���������� ������
{
	int command;
	
	while (TRUE)
	{
		printf_s(" 1 - ����� �����������;\n 2 - �����;\n 3 - ����� � �����;\n 4 - ������ �������;\n");
		printf("������� ����� ����������: ");
	}
	
	scanf_s("%d", &command);

	switch (command)
	{
	case 1:
		printf("������ �����������");
	    hThread[1] = CreateThread(NULL, 0, tm, NULL, 0, 0);
		WaitForMultipleObjects(3, hThread, TRUE, INFINITE);
		break;
	case 2:
		printf("����� ���������� �� �����");
		SuspendThread(hThread[1]);
		break;
	case 3:
		printf("����� ���� � �����");
		ResumeThread(hThread[1]);
		break;
	case 4:
		printf("����� �������");
		break;
	default:
		printf("������ �� ����������");
		break;
	}
}