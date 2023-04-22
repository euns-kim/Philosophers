#include <stdio.h>

#define NC "\e[0m"
#define BLACK "\e[1;30m"
#define RED "\e[1;31m"
#define GREEN "\e[1;32m"
#define BLUE "\e[1;34m"
#define CYAN "\e[1;36m"

int main(void)
{
	unsigned int i = 0;

	while (i < 4)
	{
		if (i == 0)
			printf("%sphilosopher #%u is thinking%s\n", \
			GREEN, i, NC);
		else if (i == 1)
			printf("%sphilosopher #%u has taken a fork%s\n", \
			BLACK, i, NC);
		else if (i == 2)
			printf("%sphilosopher #%u is eating\n%s", \
			CYAN, i, NC);
		else if (i == 3)
			printf("%sphilosopher #%u is sleeping\n%s", \
			BLUE, i, NC);
		i++;
	}
	i++;
}
