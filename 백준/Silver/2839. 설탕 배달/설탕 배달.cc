#include<stdio.h>

int main()
{
	int sugar;
	scanf("%d", &sugar);
	int result = 0;
	result = 2 * (sugar / 10);
	if (sugar == 1 || sugar == 2 || sugar == 4 || sugar == 7) {
		result = -1;
	}
	else {
		sugar = sugar % 10;

		//11 == 3
		//12 == 4
		//13 == 3
		//14 == 4
		//15 == 3
		//16 == 4
		//17 == 5
		//18 == 4
		//19 == 5
		switch (sugar)
		{
		case 1:
		case 3:
		case 5:
			result += 1;
			break;
		case 2:
		case 4:
		case 6:
		case 8:
			result += 2;
			break;
		case 7:
		case 9:
			result += 3;
			break;
		default:
			break;
		}
	}
	printf("%d\n", result);
}