#include "../includes/ft_printf.h"

const t_type g_dispatch_table[] = {
	{'s', convert_string},
	// {'S', },
	// {'p', },
	{'d', convert_int},
	// {'D', },
	{'i', convert_int},
	// {'o', },
	// {'O', },
	// {'u', },
	// {'U', },
	// {'x', },
	// {'X', },
	{'c', convert_char},
	// {'C', },
};

int print_info(t_printf *flags)
{
	printf("\nPRINT_INFO:\nprec: %i\nwidth: %i\nspec: %c\ntype: %i\nis_short: %i\nis_char: %i\nis_long: %i\nis_longlong: %i\nis_sizet: %i\nintmax: %i\nalt: %i\nspace: %i\nleft: %i\nshowsign: %i\nwide: %i\npad: %i\n", 
		flags->prec, flags->width, flags->spec, flags->type, flags->is_short,
		flags->is_char, flags->is_long, flags->is_longlong, flags->is_sizet, flags->intmax,
		flags->alt, flags->space, flags->left, flags->showsign, flags->wide,
		flags->pad);
	return 1;
}

int print_string(char *s, va_list args)
{
	while (*s)
	{
		ft_putchar(*s);
		s++;
	}
	return 1;
}

int print_char(char c, va_list args)
{
	ft_putchar(c);
	return 1;
}

int print_int(int n, va_list args)
{
	ft_putnbr(n);
	return 1;
}

int convert_int(t_printf *flags, va_list args)
{
	int n;

	n = va_arg(args, int);
	return (print_int(n, args));	
}

int convert_string(t_printf *flags, va_list args)
{
	char *s;

	s = va_arg(args, char *);
	return (print_string(s, args));
}

int convert_char(t_printf *flags, va_list args)
{
	int c;

	c = va_arg(args, int);
	return (print_char(c, args));
}

t_printf *init_flags()
{
	t_printf *flags;

	if ((flags = (t_printf *)malloc(sizeof(t_printf))) == NULL)
		return NULL;
	flags->prec = 0;
	flags->width = 0;
	flags->spec = '0';
	flags->type = 0;
	flags->is_short = 0;
	flags->is_char = 0;
	flags->is_long = 0;
	flags->is_longlong = 0;
	flags->is_sizet = 0;
	flags->intmax = 0;
	flags->alt = 0;
	flags->space = 0;
	flags->left = 0;
	flags->showsign = 0;
	flags->wide = 0;
	flags->pad = 0;
	return flags;
}

int do_conversion(const char **f, t_printf *flags, va_list args)
{
	int i;

	i = 0;
	while (i < 13)
	{
		if (flags->spec == g_dispatch_table[i].spec)
		{
			g_dispatch_table[i].func(flags, args);
			break ;
		}
		i++;
	}
	return 1;
}

int set_spec(const char **f, t_printf *flags, va_list args)
{
	if (**f == 's' || **f == 'S' || **f == 'p' || **f == 'd' || **f == 'D' || 
		**f == 'i' || **f == 'o' || **f == 'O' || **f == 'u' || **f == 'U' || 
		**f == 'x' || **f == 'X' || **f == 'c' || **f == 'C')
		flags->spec = **f;
	(*f)++;
	return (do_conversion(f, flags, args));
}

int set_length(const char **f, t_printf *flags, va_list args)
{
	if (**f == 'h' || **f == 'l' || **f == 'j' || **f == 'z')
	{
		if (**f == 'h' && *(*f + 1) == 'h')
			flags->is_char = 1;
		else if (**f == 'l' && *(*f + 1) == 'l')
			flags->is_longlong = 1;
		else if (**f == 'j')
			flags->intmax = 1;
		else if (**f == 'z')
			flags->is_sizet = 1;
		else if (**f == 'h')
			flags->is_short = 1;
		else if (**f == 'l')
			flags->is_long = 1;
	}
	if (flags->is_short == 1 || flags->is_long == 1 || flags->intmax == 1 ||
		flags->is_sizet == 1)
		(*f)++;
	else if (flags->is_char == 1 || flags->is_longlong == 1)
		(*f) += 2;
	return (set_spec(f, flags, args));
}

int set_prec(const char **f, t_printf *flags, va_list args)
{
	if (**f == '.')
	{
		(*f)++;
		if (ft_isdigit(**f))
		{
			flags->prec = ft_atoi(*f);
			while (ft_isdigit(**f))
				(*f)++;
		}
	}
	return (set_length(f, flags, args));
}

int set_width(const char **f, t_printf *flags, va_list args)
{
	if (ft_isdigit(**f))
	{
		flags->width = ft_atoi(*f);
		while (ft_isdigit(**f))
			(*f)++;
	}
	return (set_prec(f, flags, args));
}

int set_flags(const char **f, va_list args)
{
	t_printf *flags;
	
	if (**f == '%')
	{
		write(1, (*f)++, 1);
		return 1;
	}
	if ((flags = init_flags()) == NULL)
		return -1;
	while (**f == '#' || **f == '-' || **f == '+' || **f == ' ' || **f == '0')
	{
		if (**f == '#')
			flags->alt = 1;
		else if (**f == '-')
			flags->left = 1;
		else if (**f == ' ')
			flags->space = 1;
		else if (**f == '+')
			flags->showsign = 1;
		else if (**f == '0')
			flags->pad = 1;
		(*f)++;
	}
	return (set_width(f, flags, args));
}

int vprintf(const char *f, va_list args)
{
	while (*f)
	{
		if (*f == '%')
		{
			f++;
			if (set_flags(&f, args) == -1)
				return -1;
			// print();
		}
		else
		{
			ft_putchar(*f);
			f++;
		}
	}
	return 1;
}

int ft_printf(const char *f, ...)
{
	int done;
	va_list args;

	va_start(args, f);
	done = vprintf(f, args);
	va_end(args);
	return done;
}

int main(int argc, char **argv)
{
	char c = argv[2][0];
	char *s = argv[1];
	int n = -10;
	//printf("The best programming language is... %c\n", c);
	ft_printf("The best programming language is... %%\n%s\n%c\n%i\n%d\n", s, c, n, n);
	return 1;
}