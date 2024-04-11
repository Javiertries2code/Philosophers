#include "../philo.h"
#include "stdlib.h"

void ft_bzero(void *s, size_t n)
{
	unsigned int i;
	char *str;

	str = (char *)s;
	i = 0;
	while (i < n)
		str[i++] = '\0';
}

void *ft_calloc(size_t count, size_t size)
{
	void *ptr;

	ptr = (void *)malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

/**
 * @brief Counts the lenght of an String, number of characters, excluded
 *  the closing chracter. "HOLA" returns 4
 *
 * @param s
 * @return size_t  the number of caracters
 */

size_t ft_strlen(const char *s)
{
	unsigned int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}



// float funcion_proporcional(float input) {
//     // Definir los límites de la función
//     float input_min = 0;
//     float input_max = 1;
//     float output_min = 0.7;
//     float output_max = 0.95;
    
//     // Asegurarse de que el input esté dentro del rango permitido
//     input = (input < input_min) ? input_min : ((input > input_max) ? input_max : input);
    
//     // Calcular el valor de retorno usando una interpolación lineal
//     float output = ((input - input_min) / (input_max - input_min)) * (output_max - output_min) + output_min;
    
//     return output;
// }
