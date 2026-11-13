
#include <stdio.h>

/**
 * main - Simple calculator with a menu
 *
 * Return: Always 0
 */
int main(void)
{
	int choice = 1;
	int a, b;
	int result;
/* Loop to display the menu */
	while (choice != 0)
	{
		printf("Simple Calculator\n");
		printf("1) Add\n");
		printf("2) Subtract\n");
		printf("3) Multiply\n");
		printf("4) Divide\n");
		printf("0) Quit\n");

		printf("Choice: ");
		scanf("%d", &choice);
/* If choice is invalid */
		if (choice > 4 || choice < 0)
		{
			printf("Invalid choice\n");
		}
/* If choice is add */
		if (choice == 1)
		{
			printf("A: ");
			scanf("%d", &a);

			printf("B: ");
			scanf("%d", &b);

			result = a + b;

			printf("Result: %d\n", result);
		}
/* If choice is subtract */
		else if (choice == 2)
		{
			result = a - b;

			printf("Result: %d\n", result);
		}
	}
/* If choice is 0 */
	printf("Bye!\n");

	return (0);
}
