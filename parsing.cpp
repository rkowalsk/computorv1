#include "computor.hpp"

// returns the number of characters read
size_t	get_next_word(char *input, std::string &word)
{
	int	i = 0;
	int	start;

	while (input[i] != 0 && input[i] == ' ')
		i++;
	if (!input[i])
		return (0);
	start = i;
	while(input[i] != 0 && input[i] != ' ')
		i++;
	word.append(input + start, i - start);
	return (i);
}

// returns the number of characters read
size_t	get_next_variable(char *input, std::vector<float> &equation, int sign)
{
	std::vector<float>::size_type	power = 0;
	float		coeff;
	std::string	word;
	int			i = 0;

	i += get_next_word(input + i, word);
	coeff = std::stof(word) * sign;
	i += get_next_word(input + i, word);
	word.clear();
	i += get_next_word(input + i, word);
	word.erase(0, 2);
	if (!word.empty())
		power = std::stoi(word);
	if (equation.size() <= power)
		equation.resize(power + 1, 0);
	equation[power] += coeff;
	return (i);
}	

std::vector<float>	pars_input(char *input)
{
	int	i = 0;
	std::vector<float>	equation;
	int	sign;
	std::string	word;

	sign = 1;
	do
	{
		word.clear();
		i += get_next_variable(input + i, equation, sign);
		i += get_next_word(input + i, word);
		if (word == "-")
			sign = -1;
		else if (word == "+")
			sign = 1;
	} while (word != "=");
	sign = 1;
	do
	{
		word.clear();
		i += get_next_variable(input + i, equation, -sign);
		i += get_next_word(input + i, word);
		if (word == "-")
			sign = -1;
		else if (word == "+")
			sign = 1;
	} while (!word.empty());
	return (equation);
}
