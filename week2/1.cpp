/*

Elections are on for the Siruseri Town Council. Elections in Siruseri work in a rather odd manner. Each candidate is assigned a unique identification number. The town is divided into five zones and each zone proposes a list of candidates, in some arbitrary order, that it would like to nominate to the Council. Any candidate who is proposed by three or more zones is elected. There is no lower limit or upper limit on the size of the Council.

Your task is to to calculate how many candidates are elected to the Council, given the lists proposed by the five zones.

*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
#define ll long long

void merge(ll a[],int beg,int mid,int end)
{
	int n1 = mid - beg;
	int n2 = end - mid;
	ll b[n1+1],c[n2+1];

	int i,j,k;
	for(k = beg,i = 0;i < n1; i++,k++)
		b[i] = a[k];
	b[n1] = INT_MAX;

	for(j = 0;j < n2; j++,k++)
		c[j] = a[k];
	c[n2] = INT_MAX;

	i = j = 0;
	for(k = beg;k < end; k++)
		a[k] = (b[i] < c[j])?b[i++]:c[j++];
}
void merge_sort(ll a[],int beg,int end)
{
	if(end - beg <= 1)
		return;
	int mid = (beg + end) / 2;
	merge_sort(a,beg,mid);
	merge_sort(a,mid,end);
	merge(a,beg,mid,end);
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

	merge_sort(arr1, 0, n1);
	merge_sort(arr2, 0, n2);
	merge_sort(arr3, 0, n3);
	merge_sort(arr4, 0, n4);
	merge_sort(arr5, 0, n5);


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