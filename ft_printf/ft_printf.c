#include <unistd.h>
#include <stdarg.h>


int	ft_strlen(char *str)
{
	int i = -1;

	while (str[++i])
		;
	return (i);
}

void	put_string(const char *str, int *ptr_lenth)
{
	if (!str)
		str = "(null)";
	*ptr_lenth += write(1, str, ft_strlen(str));
}

void	put_digit(long long int n, int base, int *ptr_lenth)
{
	char *str;

	str = "0123456789abcdef";
	if (n < 0)
	{
		n *= -1;
		*ptr_lenth += write(1, "-", 1);
	}
	if (n >= base)
		put_digit(n / base, base, ptr_lenth);
	*ptr_lenth += write(1, &str[n % base], 1);
}

int	ft_printf(const char *format, ...)
{
	int lenth = 0;
	va_list	args;

	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && ((*(format + 1)== 'd') || (*(format + 1) == 's') || (*(format + 1) == 'x')))
		{
			format++;
			if (*format == 's')
				put_string(va_arg(args, char *), &lenth);
			else if (*format == 'd')
				put_digit((long long int)va_arg(args, int), 10, &lenth);
			else if (*format == 'x')
				put_digit((long long int)va_arg(args, unsigned int), 16, &lenth);
		}
		else
			lenth += write(1, format, 1);
		format++;
	}
	va_end(args);
	return (lenth);
}