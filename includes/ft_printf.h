#ifndef FT_PRINTF
#define FT_PRINTF

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <wchar.h>

const char g_hex[] = {'a', 'b', 'c', 'd', 'e', 'f',
	 'A', 'B', 'C', 'D', 'E', 'F'};

typedef struct	s_printf
{
	int prec; /* Precision. */
	unsigned int prec_set:1;
	int width; /* Width. */
	char spec; /* Conversion specifer. */
	char pad_char; /* Padding character. */
	unsigned int is_char:1; /* hh flag. */
	unsigned int is_short:1; /* h flag. */
	unsigned int is_long:1; /* l flag. */
	unsigned int is_longlong:1; /* ll flag. */
	unsigned int is_sizet:1; /* z flag. */
	unsigned int intmax:1; /* j flag. */
	unsigned int alt:1; /* # flag. */
	unsigned int space:1; /* Space flag. */
	unsigned int left:1; /* - flag. */
	unsigned int showsign:1; /* + flag. */
	unsigned int wide:1; /* Nonzero for wide character streams. */
	unsigned int pad:1; /* Padding flag. */
	unsigned int is_int:1;
}				t_printf;

typedef int dispatcher(t_printf *flags, va_list args);

typedef struct	s_type
{
	char spec;
	dispatcher *func;
}				t_type;

int ft_printf(const char *f, ...);
int ft_atoi(const char *str);
int ft_isdigit(int c);
int ft_countdigits(long long int i);
int ft_ucountdigits(unsigned long long int i);
void ft_putchar(int c);
void	ft_uputnbr(unsigned long long int i);
void ft_putnbr(long long int i);
void ft_putstr(char *s);
void ft_putnstr(char *s, int n);
void ft_wputnstr(wchar_t *ws, int n);
int		ft_wstrlen(wchar_t *ws);
int		ft_wclen(wchar_t wc);
int		ft_wputstr(wchar_t *ws);
int		ft_wputchar(wchar_t wc);
size_t	ft_strlen(const char *str);
void ft_itoa_base(unsigned long long int i, int base, int case);

int	ft_printf(const char *f, ...);
int vprintf(const char *f, va_list args);
int print_info(t_printf *flags);
void pad_n(t_printf *flags, int n);
int format_i(t_printf *flags, long long int i);
int format_u(t_printf *flags, unsigned long long int i);
int format_o(t_printf *flags, unsigned long long int i);
int format_x(t_printf *flags, unsigned long long int i);
char set_prefix(t_printf *flags, long long int i);
char set_uprefix(t_printf *flags, unsigned long long int i);
int print_x(t_printf *flags, unsigned long long int i);
int print_o(t_printf *flags, unsigned long long int i);
int print_space(int n);
int print_prefix(char c);
int print_s(t_printf *flags, char *s);
int print_c(t_printf *flags, int c);
int print_i(t_printf *flags, long long int i);
int print_u(t_printf *flags, unsigned long long int u);
int print_wc(t_printf *flags, wchar_t wc);
int convert_p(t_printf *flags, va_list args);
int convert_x(t_printf *flags, va_list args);
int convert_c(t_printf *flags, va_list args);
int convert_s(t_printf *flags, va_list args);
int convert_i(t_printf *flags, va_list args);
int convert_u(t_printf *flags, va_list args);
int convert_wc(t_printf *flags, va_list args);
int convert_ws(t_printf *flags, va_list args);
int do_conversion(t_printf *flags, va_list args);
int set_flags(const char **f, va_list args);
int set_spec(const char **f, t_printf *flags, va_list args);
int set_length(const char **f, t_printf *flags, va_list args);
int set_width(const char **f, t_printf *flags, va_list args);
int set_prec(const char **f, t_printf *flags, va_list args);
t_printf *init_flags();

#endif