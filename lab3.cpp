// lab3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
using namespace std;

void countingSort(vector<int>& arr, int n, int m) 
{
	vector<int> count(m + 1, 0);
	int index = 0;

	for (int i = 0; i < n; i++)
		count [arr[i]]++;
		
	for (int i = 0; i <= m; i++)
		while (count[i] > 0) 
		{
			arr[index] = i;
			index++;
			count[i]--;
		}
	
}

int main() 
{
	setlocale(LC_ALL, "rus");
	vector<int> arr = { 4, 2, 2, 8, 3, 3, 1 };
	int n = arr.size();
	int m = 8;
	for (int i = 0; i < n; i++)
		cout << " " << arr[i];

	countingSort(arr, n, m);

	cout << "\nОтсортированный массив:\n";
	for (int i = 0; i < n; i++)
		cout << " " << arr[i];

	return 0;
}