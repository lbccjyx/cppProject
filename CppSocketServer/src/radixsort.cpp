#include "radixsort.h"

static int abc = 0;
int getDigit(int maxA)
{
	int i = 1;
	while (maxA / 10 > 0)
	{
		i++;
		maxA /= 10;
	}
	return i;

}

std::vector<int> RadixSort(std::vector<int>& arr)
{
	if (arr.size() <= 0)
		return {};
	auto maxElement = std::max_element(arr.begin(), arr.end());
	int maxA = *maxElement;

	INT64 maxDigit = std::pow(10, getDigit(maxA));  // �趨һ���㹻��ĳ�ʼֵ
	std::vector<int> arrOut;
	recursiveRadixSort(arr, arrOut, maxDigit);
	std::cout << " run " << abc << " times " << std::endl;
	return arrOut;
}

// ��������ĵݹ麯��
void recursiveRadixSort(std::vector<int>& arrIn, std::vector<int>& arrOut, int nDigit) {
	// �ݹ���ֹ�������Ѿ�����������λ��
	if (nDigit == 0 || arrIn.size() <= 1) {
		arrOut.insert(arrOut.end(), arrIn.begin(), arrIn.end());
		return;
	}

	// ��ʼ��Ͱ
	std::vector<std::vector<int>> buckets(10);

	// �����ְ���ǰλ������Ͱ��
	for (int num : arrIn) {
		int digit = (num / nDigit) % 10;
		buckets[digit].push_back(num);
		abc++;
	}

	// �ݹ鴦��ÿ��Ͱ�е�����
	for (int i = 0; i < 10; ++i) {
		recursiveRadixSort(buckets[i], arrOut, nDigit / 10);
	}
}

//{ 170, 171, 45, 75, 90, 802, 24, 24, 2, 595 };
//(170 / 10000000) % 10 = 0
//buckets[0] = { 170, 171, 45, 75, 90, 802, 24, 24, 2, 595 };
//
//(170 / 100) % 10 =  1
//buckets[8] = { 802 };
//buckets[5] = { 595 };
//buckets[1] = { 170, 171};
//buckets[0] = { 45, 75, 90,24, 24, 2};

//buckets[2] = { 24, 24};
//buckets[4] = { 45,};
//buckets[7] = { 75};