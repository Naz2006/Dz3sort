#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funk.h"
#define LEN 80000

// 112 �������� �����
// ����� ����������� ���������, ����������� ������ �� ��������
// � ������� �������� � qsort, � ������������ ����� ����������
int main(void) {
	char generfile[120];		//  ���� � ����� � ��������������� ��������
	char sortfile[120];			//  ���� � ����� � ��������������� ��������
	int n = 5000;				//  ���������� ��������� �������
	double mas[LEN];			//  ������
	clock_t  start, end;		//  �-�� ����� � ������� ������� ���������
	int i, j;					//  �������
	float bubtime, qtime;		//  ����� ���������� �������� � qsort
	float myqtime;				//  ����� ���������� ���������� qsort
	FILE* file;					//  ��������� �� ����

	for (j = 0; j < 5; j++) {							//  ��������� ����������� 5 ��� ��� n, 2n, 4n, 8n � 16n
														//  ������ ��� �����, ���� ����������� ������
		printf("Enter the path to the file to store the generated array:\n");
		scanf("%s", generfile);

		if (gener_mas(generfile, n)) {					//  ���������� ������ � ����
			printf("Error opening file\n");				//  ���� �� ������� ������� ���� ������� ����������
			return 1;
		}

		if (read_file(generfile, mas, n)) {				//  �������� ��������������� ������ �� ����� � ������ mas
			printf("Could not open file\n");			//  ���� �� ������� ������� ���� ������� ����������
			return 1;
		}
		
		start = clock();								//  � start ������ ���������� ����� �� ����������
		bubblesort(mas, n);								//  ��������� ������ � ������� ��������
		end = clock();									//  � end ������ ���������� ����� ����� ����������
		bubtime = (float)(end - start) / CLK_TCK;		//  ���������� ����� ���������� ��������
		if (sort_check(mas, n)) {						//  ���������, ������������ �� ������
			printf("Array was not bubble sorted\n");	//  ���� ���, ������� �����������
			return 1;									//  � ��������� ������
		}
		else printf("Array was bubble sorted\n");		//  ���� ��, ����������

		if (read_file(generfile, mas, n)) {				//  �������� ��������������� ������ �� ����� � ������ mas
			printf("Could not open file\n");			//  ���� �� ������� ������� ���� ������� ����������
			return 1;
		}
		
		start = clock();								//  � start ������ ���������� ����� �� ����������
														//  ��������� qsort
		qsort(mas, n, sizeof(double), (int(*)(const void*, const void*))compare);
		end = clock();									//  � end ������ ���������� ����� ����� ����������
		qtime = (float)(end - start) / CLK_TCK;			//  ���������� ����� ���������� qsort
		if (sort_check(mas, n)) {						//  ���������, ������������ �� ������
			printf("Array was not quick sorted\n");		//  ���� ���, ������� �����������
			return 1;									//  � ��������� ������
		}
		else printf("Array was quick sorted\n");		//  ���� ��, ����������

		if (read_file(generfile, mas, n)) {				//  �������� ��������������� ������ �� ����� � ������ mas
			printf("Could not open file\n");			//  ���� �� ������� ������� ���� ������� ����������
			return 1;
		}

		start = clock();								//  � start ������ ���������� ����� �� ����������
		qsort_no_rec(mas, 0, n - 1);					//  ��������� ���������� qsort
		end = clock();									//  � end ������ ���������� ����� ����� ����������
		myqtime = (float)(end - start) / CLK_TCK;		//  ���������� ����� ���������� ���������� qsort
		if (sort_check(mas, n)) {						//  ���������, ������������ �� ������
			printf("Array was not quick sorted\n");		//  ���� ���, ������� �����������
			return 1;									//  � ��������� ������
		}
		else printf("Array was quick sorted\n");		//  ���� ��, ����������

														//  ������ ��� �����, ���� ��������� ��������������� ������
		printf("Enter the file path to store the sorted array:\n");
		scanf("%s", sortfile);
		if ((file = fopen(sortfile, "w")) == 0) {		//  ��������� ���� ��� ������ ���������������� �������
			printf("Error opening file\n");				//  ���� �� ������� ������� ���� ������� ����������
			return 1;
		}

		for (i = 0; i < n; i++) {
			fprintf(file, "%lf ", mas[i]);
			if ((i + 1) % 10 == 0) fprintf(file, "%c", '\n');	//  ������ ������ ����� ������ 10 ���������
		}
		fclose(file);

		printf("Number of array elements: %d\n", n);
		printf("Bubble sort time(sec): %.3f\n", bubtime);
		printf("Q-sort sort time(sec): %.3f\n", qtime);
		printf("Handwritten q-sort sort time(sec): %.3f\n\n", qtime);

		n *= 2;											//  ����������� ���������� ��������� ��� ���������� ������
	}

	return 0;
}