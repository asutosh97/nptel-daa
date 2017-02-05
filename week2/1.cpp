/*

Elections are on for the Siruseri Town Council. Elections in Siruseri work in a rather odd manner. Each candidate is assigned a unique identification number. The town is divided into five zones and each zone proposes a list of candidates, in some arbitrary order, that it would like to nominate to the Council. Any candidate who is proposed by three or more zones is elected. There is no lower limit or upper limit on the size of the Council.

Your task is to to calculate how many candidates are elected to the Council, given the lists proposed by the five zones.

*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#define ll long long

int partition(ll a[],int beg,int end)
{
	srand((unsigned)time(NULL));
	int random_pivot = beg + rand() % (end - beg);
	std::swap(a[random_pivot],a[beg]);
	int x = a[beg];
	int i = beg,j;
	for(j = beg + 1;j < end; j++)
		if(a[j] < x)
			std::swap(a[++i],a[j]);
	std::swap(a[beg],a[i]);
	return i;
}
void quick_sort(ll a[],int beg,int end)
{
	if(end - beg <= 1)
		return;
	int q = partition(a,beg,end);
	quick_sort(a,beg,q);
	quick_sort(a,q+1,end);
}
void mergeArray(ll A[], int m, ll B[], int n, ll C[], int totalSize)
{
	int i, j, k;
	i = j = k = 0;
	while(k < totalSize)
	{
		if((j == n) || A[i] <= B[j])
			C[k++] = A[i++];
		if((i == m) || A[i] > B[j])
			C[k++] = B[j++];
	}
}
int main()
{
	ll n1, n2, n3, n4, n5;
	std::cin >> n1 >> n2 >> n3 >> n4 >> n5;
	ll arr1[n1], arr2[n2], arr3[n3], arr4[n4], arr5[n5];

	for(int i = 0; i < n1; i++)
		std::cin >> arr1[i];
	
	for(int i = 0; i < n2; i++)
		std::cin >> arr2[i];

	for(int i = 0; i < n3; i++)
		std::cin >> arr3[i];

	for(int i = 0; i < n4; i++)
		std::cin >> arr4[i];

	for(int i = 0; i < n5; i++)
		std::cin >> arr5[i];

	quick_sort(arr1, 0, n1);
	quick_sort(arr2, 0, n2);
	quick_sort(arr3, 0, n3);
	quick_sort(arr4, 0, n4);
	quick_sort(arr5, 0, n5);


	int n12 = n1 + n2;
	ll arr12[n12];
	mergeArray(arr1, n1, arr2, n2, arr12, n12);


	int n123 = n12 + n3;
	ll arr123[n123];
	mergeArray(arr12, n12, arr3, n3, arr123, n123);



	int n1234 = n123 + n4;
	ll arr1234[n1234];
	mergeArray(arr123, n123, arr4, n4, arr1234, n1234);


	int totalSize = n1234 + n5;
	ll finalArray[totalSize];
	mergeArray(arr1234, n1234, arr5, n5, finalArray, totalSize);



	int prevElement = finalArray[0];
	int ans = 0;
	int count = 1;
	for(int i = 1;i < totalSize; i++)
	{
		if(prevElement == finalArray[i])
		{
			count++;
			if(count == 3)
				ans++;
		}
		else
		{
			count = 1;
		}
		prevElement = finalArray[i];
	}
	std::cout<<ans<<std::endl;
	return 0;
}