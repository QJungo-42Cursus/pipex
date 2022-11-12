#include "../libft.h"
#include "tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	test_sprintf()
{
	long	l = INT_MAX;
	l++;

	char	*test;
	test = NULL;
	test = ft_sprintf("sans flag");
	printf("%s\n", test);
	free(test);
	test = ft_sprintf("INT : %d\n", -50);
	printf("%s\n", test);
	free(test);
	test = ft_sprintf("UNSIGNED : %u\n", -50);
	printf("%s\n", test);
	free(test);
	test = ft_sprintf("POINTER : %p\n", "");
	printf("%s\n", test);
	free(test);
	test = ft_sprintf("STRING : %s\n", "'salut !'");
	printf("%s\n", test);
	free(test);
	test = ft_sprintf("%% %%", "'salut !'");
	printf("%s\n", test);
	free(test);

	// TODO le float coupe tout ce qu'il a apres le %f...
	//test = ft_sprintf("FLOAT : %f yaa \n", 10.1f);
	//printf("%s\n", test);
	// TODO ne fonctionne tout simplement pas...
	//test = ft_sprintf("LONG: %ld\n", l);
	//printf("%s\n", test);


}
