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
	printf("1 поток - %d, 2 поток - %d", *a, *(a+1));

	for (size_t i = 0; i < 2 ; i++)
	{
		CloseHandle(hThread[i]);
	}

	return 0;*/
}


VOID tm(int cntrl) //часы
{
	
	int start, end;
	int ms = 0;
	int ns = 0;
	int sec = 0;
	int min = 0;
	start = clock();

	
	//printf("Число: ");
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
		/*print_s("Введите количество минут");
		scanf_s("%d", &min);
		print_s("Введите количество секунд");
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

VOID control() //управление часами
{
	int command;
	
	while (TRUE)
	{
		printf_s(" 1 - режим секундомера;\n 2 - пауза;\n 3 - снять с паузы;\n 4 - запуск таймера;\n");
		printf("Введите номер управления: ");
	}
	
	scanf_s("%d", &command);

	switch (command)
	{
	case 1:
		printf("запуск секундомера");
	    hThread[1] = CreateThread(NULL, 0, tm, NULL, 0, 0);
		WaitForMultipleObjects(3, hThread, TRUE, INFINITE);
		break;
	case 2:
		printf("Поток поставлена на паузу");
		SuspendThread(hThread[1]);
		break;
	case 3:
		printf("Поток снят с паузы");
		ResumeThread(hThread[1]);
		break;
	case 4:
		printf("Режим таймера");
		break;
	default:
		printf("Ничего не изменилось");
		break;
	}
}