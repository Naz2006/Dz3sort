#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define M 10000

// 112 Кузнецов Назар
// Функция возвращает разность чисел (сравнение для qsort)
// На вход подаются два числа, на выходе - знак ввиде 1, 0 и -1
int compare(const double* i, const double* j) {
	if (*j > *i) return 1;
	if (*j < *i) return -1;
	return 0;
}

// 112 Кузнецов Назар
// Функция проверяет массив на отсортированность
// На вход подается массив и его длина
int sort_check(double a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		if (a[i] < a[i + 1]) return 1;
	}
	return 0;
}

// 112 Кузнецов Назар
// Сортировка пузырьком
// На вход подается массив и его длина
void bubblesort(double a[], int n) {
	int i, j;
	double tmp;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n - i - 1; j++) {
			if (a[j] < a[j + 1]) {
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
		}
	}
}

// 112 Кузнецов Назар
// Функция копирует массив из файла в данный массив
// На вход подается имя файла, массив и его длина
int read_file(char filename[], double a[], int n) {
	FILE* file;
	if ((file = fopen(filename, "r")) == 0) return 1;
	for (int i = 0; i < n; i++) {
		fscanf(file, "%lf", &a[i]);
	}
	fclose(file);
	return 0;
}

// 112 Кузнецов Назар
// Функция генерирует массив заданной длины
// И кладет его в файл filename
// На вход подается имя файла и массив
int gener_mas(char filename[], int n) {
	FILE* file;
	if ((file = fopen(filename, "w")) == 0) return 1;
	srand(time(NULL));									//  Иницилизируем переменную функции rand
	for (int i = 0; i < n; i++) {
		fprintf(file, "%lf ", ((double)rand() / RAND_MAX) * 20 - 10.0);
		if ((i + 1) % 10 == 0) fprintf(file, "%c", '\n');
	}
	fclose(file);
	return 0;
}

// 112 Кузнецов Назар
// Функция меняет местами элементы массива
// На вход подаются два числа
void swap(double* a, double* b) {
    double t = *a;
    *a = *b;
    *b = t;
}

// 112 Кузнецов Назар
// Функция сортирует часть массива (который лежит между l и r)
// На вход подается массив, и его границы l и r, возвращает индекс последнего элемента
int partition(double arr[], int l, int h) {
	double x = arr[h];
    int i = (l - 1);

    for (int j = l; j <= h - 1; j++) {
        if (arr[j] >= x) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[h]);
    return (i + 1);
}

// 112 Кузнецов Назар
// Функция сортирует часть массива
// На вход подается массив, и его границы, по которым будет проходить сортировка
void qsort_no_rec(double arr[], int l, int h) {
    int stack[M];           // Создаем мини-стек
    int top = -1;           // Вершина мини-стека
    stack[++top] = l;       // Кладем в стек левую границу
    stack[++top] = h;       // Кладем в стек правую границу

    while (top >= 0) {      // Сортируем, пока стек не пуст
        h = stack[top--];
        l = stack[top--];

        int p = partition(arr, l, h);

        if (p - 1 > l) {
            stack[++top] = l;
            stack[++top] = p - 1;
        }

        if (p + 1 < h) {
            stack[++top] = p + 1;
            stack[++top] = h;
        }
    }
}