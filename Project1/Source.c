#include <Windows.h>
#include <stdio.h>
#include <time.h>

int n = 0;
HANDLE hThread[2];

void tm(int cntrl) //����
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
		print_s("������� ���������� �����");
		scanf_s("%d", &min);
		print_s("������� ���������� ������");
		scanf_s("%d", &sec);
		
		start = clpck(0);

		break;
	}

	
}

void control() //���������� ������
{
	int command;
	
	printf_s(" 1 - ������ �������;\n 2 - �����;\n 3 - ����� � �����;\n 4 - ����� �����������\n");
	//WaitForMultipleObjects(3, hThread, TRUE, INFINITE);
	//Sleep(1000);

	printf("������� ����� ����������: ");
	scanf_s("%d", &command);
	control(command);


	switch (command)
	{
	case 1:
		printf("� ��������� 1");
		//hThread[1] = CreateThread(NULL, 0, time, NULL, 0, 0);
		//WaitForMultipleObjects(3, hThread, TRUE, INFINITE);
		break;
	case 2:
		printf("� ��������� 2");
		SuspendThread(hThread[1]);
		
		break;
	case 3:
		printf("� ��������� 3");
		break;
	case 4:
		printf("� ��������� 4");
		break;
	}
	
}

int main(int controlnum)
{
	system("chcp 1251>nul");
	
	//tm(1);
	hThread[0] = CreateThread(NULL, 0, control, NULL, 0, 0);
	hThread[1] = CreateThread(NULL, 0, time, NULL, 0, 0);
	//control();
	WaitForSingleObject(hThread, 100);

	



}