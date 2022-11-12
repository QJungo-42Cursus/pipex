
#include "../libft.h"

void	test_printf()
{
	long	l = INT_MAX;
	l++;
	ft_printf("INT : %d\n", -50);
	ft_printf("UNSIGNED : %u\n", -50);
	ft_printf("POINTER : %p\n", "");
	ft_printf("STRING : %s\n", "'salut !'");

	// TODO le float coupe tout ce qu'il a apres le %f...
	ft_printf("FLOAT : %f yaa \n", 10.1f);
	// TODO ne fonctionne tout simplement pas...
	ft_printf("LONG: %ld\n", l);
}

