// z3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
using namespace std;

void sortSimpleSort(vector<int>& arr, int n, int& countElement, int& countAll, int& countPermutations);
void sortSimpleExchange(vector<int>& arr, int n, int& countElement, int& countAll, int& countPermutations);

void sortShaker(vector<int>& arr, int n, int& countElement, int& countAll, int& countPermutations);
void sortSimpleInsert(vector<int>& arr, int n, int& countElement, int& countAll, int& countPermutations);
void sortSimpleInsertBarrier(vector<int>& arr, int n, int& countElement, int& countAll, int& countPermutations);
void SL(vector<int>& arr, int left, int mid, int right, int& countElement, int& countAll, int& countPermutations);
void sortSL(vector<int>& arr, int left, int right, int& countElement, int& countAll, int& countPermutations);
void quick_sort(vector<int>& arr, int first, int last, int& countElement, int& countAll, int& countPermutations);

int main()
{
	int countElement(0), countAll(0), countPermutations(0);
	setlocale(LC_ALL, "rus");
	vector<int> arr = { 4, 3, 2, 8, 3, 8, 1 };
	int n = arr.size();

	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";

	//sortSimpleSort(arr, n, countElement, countAll, countPermutations);
	//sortSimpleExchange(arr, n, countElement, countAll, countPermutations);
	//sortShaker(arr, n, countElement, countAll, countPermutations);
	//sortSimpleInsert(arr, n, countElement, countAll, countPermutations);
	sortSimpleInsertBarrier(arr, n, countElement, countAll, countPermutations);
	//sortSL(arr, 0, arr.size() - 1, countElement, countAll, countPermutations);
	//quick_sort(arr, 0, arr.size() - 1, countElement, countAll, countPermutations);

	cout << "\nОтсортированный массив:\n";
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << "\n" << countElement << " " << countAll << " " << countPermutations;
	return 0;
}

//алгоритм простого выбора
void sortSimpleSort(vector<int>& arr, int n, int& countElement, int& countAll, int& countPermutations)
{
	int k(0), m(0);
	countElement = 0;
	countAll = 0;
	countPermutations = 0;

	for (int i = n - 1; i > 0; i--) // Поиск с конца массива
	{
		k = i; // Индекс последнего элемента
		m = arr[i]; // Значение последнего

		for (int j = 0; j < i; j++) // Поиск с начала массива до рассматриваемого элемента
		{
			if (arr[j] > m) // Если первый элемент > последнего - фиксация большего элемента
			{
				k = j; 
				m = arr[k];
				
				countPermutations++;
			}
			countElement++;
			countAll += 2;
		}
		if (k != i) 
		{
			arr[k] = arr[i]; // Установка максимального элемента в конец
			arr[i] = m;
			countElement++;
			countPermutations++;
		}
		countAll += 2;
	}
}

//алгоритм простого обмена
void sortSimpleExchange(vector<int>& arr, int n, int& countElement, int& countAll, int& countPermutations)
{
	int m(0), t(0);
	countElement = 0;
	countAll = 0;
	countPermutations = 0;

	for (int k = 0; k < n - 1; k++)
	{
		for (int i = 0; i < n - k - 1; i++)
		{
			if (arr[i] > arr[i + 1]) // Если предыдущий элемент > следующего - смена
			{
				t = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = t;
				countPermutations++;
			}
			countElement++;
		}
		countAll += 3;
	}
}

//улучшенный алгоритм простого обмена (учет факта последнего обмена и его места)
void sortSimpleLastExchange(vector<int>& arr, int n, int& countElement, int& countAll, int& countPermutations)
{

}


//улучшенный алгоритм простого обмена – шейкер-сортировка (учет факта последнего обмена и чередование направлений просмотра элементов)
void sortShaker(vector<int>& arr, int n, int& countElement, int& countAll, int& countPermutations)
{
	bool flag = true;
	int start = 0;
	int end = n - 1;
	int lastSwapped = 0;
	countElement = 0;
	countAll = 0;
	countPermutations = 0;

	while (flag)
	{
		flag = false;
		for (int i = start; i < end; ++i) {
			if (arr[i] > arr[i + 1]) {
				swap(arr[i], arr[i + 1]);
				flag = true;
				lastSwapped = i;
			}
		}

		if (!flag) 
			break;

		end = lastSwapped;
		flag = false;

		for (int i = end; i > start; --i) {
			if (arr[i] < arr[i - 1]) {
				swap(arr[i], arr[i - 1]);
				flag = true;
				lastSwapped = i;
			}
		}

		start = lastSwapped;
	}
}

//алгоритм прямого включения(простыми вставками)
void sortSimpleInsert(vector<int>& arr, int n, int& countElement, int& countAll, int& countPermutations)
{
	int w(0), j(0);
	countElement = 0;
	countAll = 0;
	countPermutations = 0;

	for (int i = 1; i < n; i++)
	{
		w = arr[i];
		j = i - 1;

		while (j > -1 && w < arr[j]) // Подбор места в отсортированном массиве для выбранного элемента  
		{
			if (w < arr[j])
				countElement++;
			arr[j + 1] = arr[j];
			j--;
			countPermutations++;
			countAll += 2;;
		}
		arr[j + 1] = w;
		countAll++;
	}
}

//улучшенный алгоритм прямого включения(добавить барьерный элемент)
void sortSimpleInsertBarrier(vector<int>& arr, int n, int& countElement, int& countAll, int& countPermutations)
{
	countElement = 0;
	countAll = 0;
	countPermutations = 0;

	// Находим наименьший элемент и помещаем его в начало массива
	int minIdx = 0;
	for (int i = 1; i < n; ++i) {
		if (arr[i] < arr[minIdx])
		{
			minIdx = i;
			countElement++;
		}
		countAll += 2;
	}
	swap(arr[0], arr[minIdx]);
	countPermutations++;

	for (int i = 2; i < n; ++i) 
	{
		int j = i;
		int tmp = arr[j];

		// Перемещаем барьерный элемент на позицию j
		if (tmp < arr[0]) {
			while (j > 0 && tmp < arr[j - 1]) {
				arr[j] = arr[j - 1];
				--j;
				countPermutations++;
				countAll++;
			}
			arr[j] = tmp;
			countPermutations++;
			countElement++;
			countAll++;
		}
		countAll++;
	}
}


//алгоритм сортировки слияниями
void SL(vector<int>& arr, int left, int mid, int right, int& countElement, int& countAll, int& countPermutations) {
	int n1 = mid - left + 1;
	int n2 = right - mid;

	vector<int> L(n1), R(n2);

	for (int i = 0; i < n1; i++) {
		L[i] = arr[left + i];
	}
	for (int j = 0; j < n2; j++) {
		R[j] = arr[mid + 1 + j];
	}

	int i = 0, j = 0, k = left;

	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
			countElement++;
			countPermutations++;
		}
		else {
			arr[k] = R[j];
			j++;
			countPermutations++;
		}
		k++;
		countAll += 3;
	}

	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
		countPermutations++;
		countAll++;
	}

	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
		countPermutations++;
		countAll++;
	}
}

void sortSL(vector<int>& arr, int left, int right, int& countElement, int& countAll, int& countPermutations) {
	
	countElement = 0;
	countAll = 0;
	countPermutations = 0;

	if (left < right) 
	{
		int mid = left + (right - left) / 2;

		sortSL(arr, left, mid, countElement, countAll, countPermutations);
		sortSL(arr, mid + 1, right, countElement, countAll, countPermutations);

		SL(arr, left, mid, right, countElement, countAll, countPermutations);
	}
}

//быстрая сортировка Хоара
void quick_sort(vector<int>& arr, int first, int last, int& countElement, int& countAll, int& countPermutations)
{
	countElement = 0;
	countAll = 0;
	countPermutations = 0;

	int i = first, j = last, w = 0,
		x = arr[(first + last) / 2];
	while (i <= j)
	{
		while (arr[i] < x)
		{
			i++;
			countAll++;
		}
		while (arr[j] > x)
		{
			j--;
			countAll++;
		}

		if (i <= j)
		{
			w = arr[i];
			arr[i] = arr[j];
			arr[j] = w;
			i++;
			j--;
			countElement++;
			countPermutations++;
		}
		countAll += 2;
	}
	if (first < j)
		quick_sort(arr, first, j, countElement, countAll, countPermutations);
	if (i < last)
		quick_sort(arr, i, last, countElement, countAll, countPermutations);
}
