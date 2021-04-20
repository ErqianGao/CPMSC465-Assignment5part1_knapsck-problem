#include <iostream>

using namespace std;


struct interval
{
	int start;
	int termination;
	int weight;
};

interval* sortAndCount(interval*, int);
interval* mergeAndCount(interval*, interval*, int, int);
int binarySearch(interval*, int, int, int);





int main()
{
	int n = 0;
	cin >> n;
	interval* intervals = new interval[n];
	for (int i = 0; i < n; i++)
	{
		cin >> intervals[i].start;
		cin >> intervals[i].termination;
		cin >> intervals[i].weight;
	}

	interval* temp = sortAndCount(intervals, n);
	interval* sorted = new interval[n + 1];
	for (int i = 0; i < n; i++)
	{
		sorted[i + 1] = temp[i];
	}


	int* F = new int[n + 1];
	int* pre = new int[n + 1];
	F[0] = 0;

	for (int i = 1; i <= n; i++)
	{
		pre[i] = binarySearch(sorted, i, 1, i - 1);


		if (F[pre[i]] + sorted[i].weight < F[i-1])
		{
			F[i] = F[i-1];
		}
		else
		{
			F[i] = F[pre[i]] + sorted[i].weight;
		}
	}
	cout << F[n];


	return 0;
}











int binarySearch(interval* A, int k, int a, int b)
 {
	int m = (a + b) / 2;

	if (A[m].termination <= A[k].start && A[k].start <= A[m + 1].termination)
	{
		if (A[k].start == A[m + 1].termination)
		{
			return m + 1;
		}
		return m;
	}
	else if (A[m].termination > A[k].start)
	{
		if (A[k].start < A[1].termination)
		{
			return 0;
		}
		return binarySearch(A, k, a, m);
	}
	else if (A[k].start > A[m + 1].termination)
	{
		return binarySearch(A, k, m + 1, b);
	}
	else
	{
		return 0;
	}
}






interval* sortAndCount(interval* a1, int a1Size)
{
	if (a1Size == 1 || a1Size == 0)
	{
		return a1;
	}
	int frontSize = a1Size / 2;
	int backSize = a1Size - frontSize;

	interval* front = new interval[frontSize];
	interval* back = new interval[backSize];

	for (int i = 0; i < a1Size; i++)
	{
		if (i < frontSize)
		{
			front[i] = a1[i];
		}
		else
		{
			back[i - frontSize] = a1[i];
		}
	}

	return mergeAndCount(sortAndCount(front, frontSize), sortAndCount(back, backSize), frontSize, backSize);
}


interval* mergeAndCount(interval* a1, interval* a2, int a1Size, int a2Size)
{

	if (a1Size == 0)
	{
		return a2;
	}
	if (a2Size == 0)
	{
		return a1;
	}

	interval* finalArray = new interval[a1Size + a2Size];

	if (a1[0].termination <= a2[0].termination)
	{
		finalArray[0] = a1[0];
		interval* newA1 = new interval[a1Size - 1];
		for (int i = 0; i < a1Size - 1; i++)
		{
			newA1[i] = a1[i + 1];
		}

		interval* result = mergeAndCount(newA1, a2, a1Size - 1, a2Size);
		for (int i = 0; i < a1Size + a2Size - 1; i++)
		{
			finalArray[i + 1] = result[i];
		}

		delete[] result;

		return finalArray;
	}
	else
	{
		finalArray[0] = a2[0];
		interval* newA2 = new interval[a2Size - 1];
		for (int i = 0; i < a2Size - 1; i++)
		{
			newA2[i] = a2[i + 1];
		}

		interval* result = mergeAndCount(a1, newA2, a1Size, a2Size - 1);
		for (int i = 0; i < a1Size + a2Size - 1; i++)
		{
			finalArray[i + 1] = result[i];
		}

		delete[] result;

		return finalArray;
	}
	return finalArray;
}