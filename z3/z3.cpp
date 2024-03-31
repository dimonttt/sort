// z3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

void sortSimpleSort(vector<int> arr, int n, int& countElement, int& countAll, int& countPermutations);
void sortSimpleExchange(vector<int> arr, int n, int& countElement, int& countAll, int& countPermutations);
void sortSimpleLastExchange(vector<int> arr, int n, int& countElement, int& countAll, int& countPermutations);
void sortShaker(vector<int> arr, int n, int& countElement, int& countAll, int& countPermutations);
void sortSimpleInsert(vector<int> arr, int n, int& countElement, int& countAll, int& countPermutations);
void sortSimpleInsertBarrier(vector<int> arr, int n, int& countElement, int& countAll, int& countPermutations);
void SL(vector<int> arr, int left, int mid, int right, int& countElement, int& countAll, int& countPermutations);
void sortSL(vector<int> arr, int left, int right, int& countElement, int& countAll, int& countPermutations);
void quick_sort(vector<int> arr, int first, int last, int& countElement, int& countAll, int& countPermutations);

void callingFunction(ofstream& fout, vector<int>& arr, vector<int>& arr2, vector<int>& arr3, int n, int& countElement, int& countAll, int& countPermutations);
//void outputFile(ofstream& fout, int& countElement, int& countAll, int& countPermutations);

int main()
{
	setlocale(LC_ALL, "rus");
	int countElement(0), countAll(0), countPermutations(0), n, m;
	vector<string> str;

	ifstream fin("C:\\inSort.txt");
	ofstream fout("C:\\outSort.txt");	
	
	vector<int> arr = { 1, 2, 4, 4, 4, 5, 6, 20, 21, 34 };
	vector<int> arr2 = { 45, 44, 22, 21, 21, 15, 13, 11, 11, 1 };
	vector<int> arr3 = { 23, 43, 11, 28, 4, 23, 4, 98, 1, 11 };

	n = arr2.size();
	for (int i = 0; i < n; i++)
		cout << arr2[i] << " ";
	sortSimpleInsert(arr2, n, countElement, countAll, countPermutations);
	cout << "\nОтсортированный массив:\n";
	for (int i = 0; i < n; i++)
		cout << arr2[i] << " ";
	cout << "\n" << countElement << " " << countAll << " " << countPermutations;



	fout << "№" << "\t\t" << "По неубыванию" << "\t\t\t\t" << "По невозрастанию" << "\t\t\t\t" << "Случайным образом" << "\n";
	for (int i = 0; i < 3; i++)
	{
		fout << " " << "С элементом" << "\t" << "Все" << "\t" << "Перестановки" << "\t\t";
	}
	fout << "\n";
	callingFunction(fout, arr, arr2, arr3, n, countElement, countAll, countPermutations);

	fin.close();
	fout.close();
	return 0;	
}



//void outputFile(ofstream& fout, vector<int>& arr, vector<int>& arr2, vector<int>& arr3, int n, int& countElement, int& countAll, int& countPermutations)
//{
//	/*vector<int> arr_now(n);
//	for (int i = 0; i < 3; i++)
//	{
//		arr_now = arr;
//		sortSimpleExchange(arr[i], n, countElement, countAll, countPermutations);
//	}*/
//	fout << "\t" << countElement << "\t" << countAll << "\t" << countPermutations << "\t\t\t";
//}



//алгоритм простого выбора
void sortSimpleSort(vector<int> arr, int n, int& countElement, int& countAll, int& countPermutations)
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
void sortSimpleExchange(vector<int> arr, int n, int& countElement, int& countAll, int& countPermutations)
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
			countAll += 2;
		}
		countAll++;
	}
}

//улучшенный алгоритм простого обмена (учет факта последнего обмена и его места)
void sortSimpleLastExchange(vector<int> arr, int n, int& countElement, int& countAll, int& countPermutations)
{
	int m(0), t(0);
	countElement = 0;
	countAll = 0;
	countPermutations = 0;
}


//улучшенный алгоритм простого обмена – шейкер-сортировка (учет факта последнего обмена и чередование направлений просмотра элементов)
void sortShaker(vector<int> arr, int n, int& countElement, int& countAll, int& countPermutations)
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
			if (arr[i] > arr[i + 1]) { // Если предыдущий > следующего - смена
				swap(arr[i], arr[i + 1]);
				flag = true;
				lastSwapped = i;
				countPermutations++;
				countElement++;
			}
			countAll += 2;
		}
		if (!flag) 
			break;
		end = lastSwapped;
		flag = false;

		for (int i = end; i > start; --i) {
			if (arr[i] < arr[i - 1]) { // Если следующий < предыдущего - смена
				swap(arr[i], arr[i - 1]);
				flag = true;
				lastSwapped = i;
				countPermutations++;
				countElement++;
			}
			countAll += 2;
		}

		start = lastSwapped;
	}
}

//алгоритм прямого включения(простыми вставками)
void sortSimpleInsert(vector<int> arr, int n, int& countElement, int& countAll, int& countPermutations)
{
	countElement = 0;
	countAll = 0;
	countPermutations = 0;
	int i, key, j;

	for (i = 1; i < n; i++) {
		key = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j] > key) { //Переместить элементы, которые больше, чем key, на одну позицию перед их текущей позицией
			if (arr[j] > key)
			{
				countElement++;
			}
			arr[j + 1] = arr[j];
			j = j - 1;			
			
			countPermutations++;
			countAll += 2;
		}
		arr[j + 1] = key;
		countAll++;
	}

}

//улучшенный алгоритм прямого включения(добавить барьерный элемент)
void sortSimpleInsertBarrier(vector<int> arr, int n, int& countElement, int& countAll, int& countPermutations)
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
void SL(vector<int> arr, int left, int mid, int right, int& countElement, int& countAll, int& countPermutations) {
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

void sortSL(vector<int> arr, int left, int right, int& countElement, int& countAll, int& countPermutations) {
	
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
void quick_sort(vector<int> arr, int first, int last, int& countElement, int& countAll, int& countPermutations)
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













// Вывод в файл
void callingFunction(ofstream& fout, vector<int>& arr, vector<int>& arr2, vector<int>& arr3, int n, int& countElement, int& countAll, int& countPermutations)
{
	vector<int> arr_new, arr_new2, arr_new3;
	arr_new = arr;
	arr_new2 = arr2;
	arr_new3 = arr3;
	/////
	int number(1);
	fout << number;
	sortSimpleSort(arr_new, n, countElement, countAll, countPermutations);
	fout << "\t" << countElement << "\t" << countAll << "\t" << countPermutations << "\t\t\t";

	sortSimpleSort(arr_new2, n, countElement, countAll, countPermutations);
	fout << "\t" << countElement << "\t" << countAll << "\t" << countPermutations << "\t\t\t";

	sortSimpleSort(arr_new3, n, countElement, countAll, countPermutations);
	fout << "\t" << countElement << "\t" << countAll << "\t" << countPermutations << "\t\t\t";
	//outputFile(fout, countElement, countAll, countPermutations);
	number++;

	/////
	fout << "\n" << number;
	sortSimpleExchange(arr_new, n, countElement, countAll, countPermutations);
	fout << "\t" << countElement << "\t" << countAll << "\t" << countPermutations << "\t\t\t";

	sortSimpleExchange(arr_new2, n, countElement, countAll, countPermutations);
	fout << "\t" << countElement << "\t" << countAll << "\t" << countPermutations << "\t\t\t";

	sortSimpleExchange(arr_new3, n, countElement, countAll, countPermutations);
	fout << "\t" << countElement << "\t" << countAll << "\t" << countPermutations << "\t\t\t";
	number++;

	/////
	fout << "\n" << number;
	sortSimpleLastExchange(arr_new, n, countElement, countAll, countPermutations);
	fout << "\t" << countElement << "\t" << countAll << "\t" << countPermutations << "\t\t\t";
	sortSimpleLastExchange(arr_new2, n, countElement, countAll, countPermutations);
	fout << "\t" << countElement << "\t" << countAll << "\t" << countPermutations << "\t\t\t";
	sortSimpleLastExchange(arr_new3, n, countElement, countAll, countPermutations);
	fout << "\t" << countElement << "\t" << countAll << "\t" << countPermutations << "\t\t\t";
	number++;

	/////
	fout << "\n" << number;
	sortShaker(arr_new, n, countElement, countAll, countPermutations);
	fout << "\t" << countElement << "\t" << countAll << "\t" << countPermutations << "\t\t\t";

	sortShaker(arr_new2, n, countElement, countAll, countPermutations);
	fout << "\t" << countElement << "\t" << countAll << "\t" << countPermutations << "\t\t\t";

	sortShaker(arr_new3, n, countElement, countAll, countPermutations);
	fout << "\t" << countElement << "\t" << countAll << "\t" << countPermutations << "\t\t\t";
	number++;

	/////
	fout << "\n" << number;
	sortSimpleInsert(arr_new, n, countElement, countAll, countPermutations);
	fout << "\t" << countElement << "\t" << countAll << "\t" << countPermutations << "\t\t\t";
	sortSimpleInsert(arr_new2, n, countElement, countAll, countPermutations);
	fout << "\t" << countElement << "\t" << countAll << "\t" << countPermutations << "\t\t\t";
	sortSimpleInsert(arr_new3, n, countElement, countAll, countPermutations);
	fout << "\t" << countElement << "\t" << countAll << "\t" << countPermutations << "\t\t\t";
	number++;

	/////
	fout << "\n" << number;
	sortSimpleInsertBarrier(arr_new, n, countElement, countAll, countPermutations);
	fout << "\t" << countElement << "\t" << countAll << "\t" << countPermutations << "\t\t\t";
	sortSimpleInsertBarrier(arr_new2, n, countElement, countAll, countPermutations);
	fout << "\t" << countElement << "\t" << countAll << "\t" << countPermutations << "\t\t\t";
	sortSimpleInsertBarrier(arr_new3, n, countElement, countAll, countPermutations);
	fout << "\t" << countElement << "\t" << countAll << "\t" << countPermutations << "\t\t\t";
	number++;

	/////
	fout << "\n" << number;
	sortSL(arr_new, 0, arr_new.size() - 1, countElement, countAll, countPermutations);
	fout << "\t" << countElement << "\t" << countAll << "\t" << countPermutations << "\t\t\t";
	sortSL(arr_new2, 0, arr_new2.size() - 1, countElement, countAll, countPermutations);
	fout << "\t" << countElement << "\t" << countAll << "\t" << countPermutations << "\t\t\t";
	sortSL(arr_new3, 0, arr_new3.size() - 1, countElement, countAll, countPermutations);
	fout << "\t" << countElement << "\t" << countAll << "\t" << countPermutations << "\t\t\t";
	number++;

	/////
	fout << "\n" << number;
	quick_sort(arr_new, 0, arr_new.size() - 1, countElement, countAll, countPermutations);
	fout << "\t" << countElement << "\t" << countAll << "\t" << countPermutations << "\t\t\t";
	quick_sort(arr_new2, 0, arr_new2.size() - 1, countElement, countAll, countPermutations);
	fout << "\t" << countElement << "\t" << countAll << "\t" << countPermutations << "\t\t\t";
	quick_sort(arr_new3, 0, arr_new3.size() - 1, countElement, countAll, countPermutations);
	fout << "\t" << countElement << "\t" << countAll << "\t" << countPermutations << "\t\t\t";
	number++;


}