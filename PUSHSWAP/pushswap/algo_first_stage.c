#include "push_swap.h"

// Initializes first second last (fsl) (values of the fsl indexes of the list)
static int	*init_fsl(t_list **head)
{
	static int	fsl[4];

	fsl[0] = get_i_value(nth_node(head, 0));
	fsl[1] = get_i_value(nth_node(head, 1));
	fsl[2] = get_i_value(last_node(head));
	fsl[3] = 0;
	return (fsl);
}
// First Second Last check: Checks which of the 3 is the biggest
// and arranges them in descending order
// the values in ret[4] will be an according order of: f, s, l
static char	*fsl_order(t_list **head, const char *fsl_arr)
{
	static char	ret[4];
	int			*fsl;
	int			i;
	int			j;
	int			place;

	i = 0;
	if (list_len(head) <= 3)
		return (err);
	fsl = init_fsl(head);
	while (i < 3)
	{
		place = 0;
		j = 0;
		while (j < 3)
		{
			if (fsl[i] < fsl[j])
				place++;
			j++;
		}
		ret[place] = fsl_arr[i];
		i++;
	}
	ret[3] = '\0';
	return (ret);
}

// Chooses action to take based on fsl-a
// ra, sa or rra (before pb in algo_swap_push)
static short	first_s_a(t_list **head, const short *arr, const char *fsl_arr)
{
	const char	*fsl_a = fsl_order(head, fsl_arr);

	if (fsl_a[0] == 's' && fsl_a[2] == 'f')
		return (ra);
	if (fsl_a[0] == 's')
		return (sa);
	if (fsl_a[0] == 'l')
		return (rra);
	return (inert);
}

// Determines if double-stack-action is applicable based on action-a and fsl-b
// It tries to sort b in an descending order
static short	first_s_b(t_list **head, short act_a, const short *arr, \
		const char *fsl_arr)
{
	const char	*fsl_b = fsl_order(head, fsl_arr);

	if (act_a == ra)
	{
		if (fsl_b[2] == 'f')
			return (rr);
	}
	if (act_a == sa)
	{
		if (fsl_b[2] == 'f')
			return (ss);
	}
	if (act_a == rra)
	{
		if (fsl_b[0] == 'l')
			return (rrr);
	}
	return (act_a);
}

// Determines the actions based on fsl_order,
// the smallest gets pushed to b and tries to sort b (invertedly)
short	first_stage(t_list **head_a, t_list **head_b, t_sort *s, \
	const short *arr)
{
	const char	fsla[] = "fsl";

	while (check_sort(head_a) == err && list_len(head_a) > 3)
	{
		s->ret_a = first_s_b(head_b, first_s_a(head_a, arr, fsla), arr, fsla);
		if (s->ret_a == err)
			return (err);
		if (s->ret_a >= 0)
			do_actions(head_a, head_b, 2, s->ret_a, pb);
		else
			do_action(head_a, head_b, pb);
	}
	return (ok);
}
