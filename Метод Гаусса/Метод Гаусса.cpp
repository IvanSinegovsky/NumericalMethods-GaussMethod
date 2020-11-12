#include <iostream>

void swap(int firstLine, int secondLine, double** pptr);//перестановка указателей на строки массива
double** pointerMemoryAllocation(int nLine, int nColumns);//выделение массива указателей
void arrayFilling(int nLines, int nColumns, double* ptr);//заполнение массива
void arrayReading(int nLines, int nColumns, double** pptr);//вывод массива в консоль
void pointerMemoryDelete(double** pptr, int nLines);//удаление массива
void linesAddition(double** pptr, int counter, int nLines, int nColumns);//прибавление строки к строке

int findLargestElement(double** pptr, int nLines);//поиск наибольшего по модулю элемента


void gaus(double** pptr, int nLines, int nColumns, int counter);
int main()
{
	double** pptr = pointerMemoryAllocation(5, 7);
	arrayReading(5, 7, pptr);
	gaus(pptr, 5, 7, 0);


	pointerMemoryDelete(pptr, 5);
	return 0;
}
void swap(int firstLine, int secondLine, double** pptr)
{
	std::swap(pptr[firstLine], pptr[secondLine]);
}
double** pointerMemoryAllocation(int nLines, int nColumns)
{
	double** pptr = new double* [nLines];
	for (int i = 0; i < nColumns; i++) 
	{
		double* ptr = new double[nColumns];
		pptr[i] = ptr;
		arrayFilling(i, nColumns, ptr);
	}
	return pptr;
}
void arrayFilling(int j, int nColumns, double* ptr)
{
	for (int i = 0; i < nColumns; i++)
	{
		double n = double(i) + double(nColumns * j);
		ptr[i] = n;
	}
}
void arrayReading(int nLines, int nColumns, double** pptr)
{
	for (int i = 0; i < nLines; i++)
	{
		double* ptr = pptr[i];
		for (int j = 0; j < nColumns; j++)
			std::cout << ptr[j] << '\t';
		std::cout << std::endl;
	}
}
void pointerMemoryDelete(double** pptr, int nLines)
{
	for (int i = 0; i < nLines; i++)
	{
		double* ptr = pptr[i];
		delete[] ptr;
	}
	delete[] pptr;
}
int findLargestElement(double** pptr, int nLines)
{
	int maxIndex = 0;
	double* ptr = pptr[0];
	double max = abs(ptr[0]);
	for (int i = 1; i < nLines; i++)
	{
		ptr = pptr[i];
		if (ptr[0] > max)
		{
			max = abs(ptr[i]);
			maxIndex = i;
		}
	}
	return maxIndex;
}
void gaus(double** pptr, int nLines, int nColumns, int counter)
{
	counter++;
	int max = findLargestElement(pptr, nLines);
	if (max != 0)
		swap(max, 0, pptr);
	linesAddition(pptr, counter, nLines, nColumns);
	arrayReading(nLines, nColumns, pptr);
	std::cout << std::endl;
	if (counter == nLines)
	{
		std::cout << pptr[nLines - 1][nColumns - 2];
		return;
	}
	else
		gaus(pptr, nLines, nColumns, counter);
}
void linesAddition(double** pptr, int counter, int nLines, int nColumns)
{
	int coefficient = 0;
	if (pptr[nLines - counter][nColumns - counter + 1] == 0)
		return;
	else
		coefficient = pptr[counter][counter] / pptr[counter - 1][counter];
	for (int i = 0; i < nLines; i++)
		pptr[counter][counter + i] = coefficient * pptr[counter - 1][counter + i] + pptr[counter][counter + i];
}