#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
using namespace std;

void bubbleSort(int* array, int size) {
	int temp;
	for (int i = size - 1; i >= 0; i--) {
		for (int j = 1; j <=  i; j++) {
			if (array[j-1] > array[j]) {
				temp = array[j-1];
				array[j-1] = array[j];
				array[j] = temp;
			}
		}
	}
}
double calculateAverage(int *array, int size) {
	double sum = 0;
	for (int i = 0; i < size; i++) {
		sum += array[i];
	}
	return sum / size;
}

double calculateMedian(int* array, int size) {
	bubbleSort(array, size);

	if (size % 2 == 0) {
		return (array[(size - 1)/2] + array[size / 2]) / 2.0;
	} else {
		return array[size / 2];
	}
}

double calculateStandardDeviation(int* array, int size) {
	double mean = calculateAverage(array, size);
	double sum_squares = 0;
	if (size == 1) {
		return 0.00;
	}
	for (int i = 0; i < size; i++) {
		sum_squares += pow(array[i] - mean, 2);
	}
	return pow(sum_squares / (size - 1), 0.5);

}

int main() {
	string filename;
	cout << "Enter filename: ";
	getline(cin, filename);

	ifstream inputFile(filename);
	if(!inputFile) {
		cerr << "Cannot open " <<filename << endl;
		return 1;
	}

	int count = 0;
	int number = 0;
	int* array = new int[1];

	while (inputFile >> number) {
		int* temp = new int[count + 1];
		for (int i = 0; i < count; i++) {
			temp[i] = array[i];
			}
		delete[] array;
		array = temp;
		array[count++] = number;
	}
	inputFile.close();


	if (count == 0) {
		cerr << "No numbers found in the file." << endl; 
		return 1; 
	}

	
	double average = calculateAverage(array, count);
	double median = calculateMedian(array, count);
	double stddev = calculateStandardDeviation(array, count);

	cout << fixed << setprecision(2);
	cout << "Here are some statistics:" << endl;
	cout << "N: " << count <<endl;
	cout << "Average: " << average << endl;
	cout << "Median: " << median << endl;
	cout << "StdDev: " << stddev << endl;

	delete[] array;
	return 0;

}
