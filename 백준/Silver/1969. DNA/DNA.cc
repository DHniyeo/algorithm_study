#include<stdio.h>
#include<algorithm>
#include<vector>

char word[] = { 'A', 'C','G','T' };
char find_max(int memory[]) {
	int max = -1;
	char max_index;
	for (int i = 0; i < 4; i++) {
		if (max < memory[word[i]]) {
			max = memory[word[i]];
			max_index = word[i];
		}
	}
	return max_index;
}
int main()
{
	char arr[1000][50];
	int n, m;
	
	char result_word[50] = {0};
	int result_sum = 0;
	scanf("%d %d", &n, &m);
	getchar();

	for (int i = 0; i < n; i++) {
		scanf("%s", arr[i]);
		getchar();
	}

	for (int i = 0; i < m; i++) {
		int memory[255] = {0}; // 빈도수 체크
		for (int j = 0; j < n; j++) {
			memory[arr[j][i]]++;
		}
		result_word[i] = find_max(memory);
		result_sum += n - memory[result_word[i]];
	}
	result_word[m] = '\0';

	printf("%s\n", result_word);
	printf("%d\n", result_sum);
	


}