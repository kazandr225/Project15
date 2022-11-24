#include <Windows.h>
#include <stdio.h>
#include <time.h>

HANDLE hThread[2];

int tm(int cntrl) //часы
{
	
	int start, end; //для секундомера
	int ms = 0;
	int ns = 0;
	int sec = 0;
	int min = 0;
	start = clock();

	int min2, sec2; //для таймера
	if (cntrl == 2)
	{
		printf("Введите количество минут: ");
		scanf_s("%i", &min2);

		printf("Введите количество секунд: ");
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
		control();
		break;
	case 2:
		while (GetAsyncKeyState(VK_ESCAPE) == 0)
		{
			Sleep(970); // 970 + 30 = 1 секунда (30 от обработки)

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
				printf("Отсчет закончен\n");
				printf("%d:%d\r", min2, sec2);
				control();
			}	
		}
		break;
	}
	
	system("cls");
	//control();
}

int control() //управление часами
{
	printf_s(" 1 - режим секундомера;\n 2 - пауза, снять с паузы;\n 3 - запуск таймера;\n");
	int command;
	printf("Введите номер управления: ");
	scanf_s("%d", &command);
	printf("\n");

	switch (command)
	{
	case 1:
		printf("запуск секундомера\n");
		hThread[1] = CreateThread(NULL, 0, tm, 1, 0, 0);
		break;
	case 2:
		while (GetAsyncKeyState(VK_ESCAPE) == 0)
		{
			if (ResumeThread(hThread[1]) != 0)
			{
				printf("Работа потока возобновлена\n");
				control();
				ResumeThread(hThread[1]);
			}
			else
			{
				printf("Поток поставлен на паузу\n");
				control();
				SuspendThread(hThread[1]);
			}
		}
		break;
	case 3:
		printf("Режим таймера\n");
		hThread[1] = CreateThread(NULL, 0, tm, 2, 0, 0);
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