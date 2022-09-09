#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

size_t	get_next_word(char *input, std::string &word) // returns the number of characters read
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

//returns the number of characters read
size_t	get_next_variable(char *input, std::vector<float> &equation, int sign) 
{
	float		coeff;
	std::vector<float>::size_type	power;
	std::string	word;
	int			i = 0;

	i += get_next_word(input + i, word);
	coeff = std::stof(word) * sign;
	i += get_next_word(input + i, word);
	word.clear();
	i += get_next_word(input + i, word);
	word.erase(0, 2);
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

std::string	equation_to_s(std::vector<float> eq)
{
	size_t	i = 0;
	size_t	size = eq.size();
	std::string	output;
	std::ostringstream oss;

	while (i < size)
	{
		oss.str("");
		if (i != 0)
		{
			if (eq[i] < 0)
			{
				output += " - ";
				oss << -eq[i];
				output += oss.str();
			}
			else
			{
				output += " + ";
				oss << eq[i];
				output += oss.str();
			}
		}
		else
		{
			oss << eq[i];
			output += oss.str();
		}
		output += " * X^";
		output += std::to_string(i);
		i++;
	}
	if (!size)
		output += "0";
	output += " = 0";
	return (output);
}

void	clear_equation(std::vector<float> &equation)
{
	while (!equation.empty() && equation.back() == 0)
		equation.pop_back();
}

std::string	solve_equation(std::vector<float> equation)
{
	float				right_side = 0;
	std::ostringstream	oss;

	if (equation.size() > 3)
		oss << "The polynomial degree is stricly greater than 2, I can't solve.";
	else if (equation.size() == 3)
	{
		float	discriminant;

		discriminant = equation[1] * equation[1] - 4 * equation[0] * equation[2];
		oss << "Discriminant: " << discriminant << std::endl;
		if (discriminant > 0)
		{
			oss << "Discriminant is strictly positive, the two solutions are:" << std::endl;
			oss << (-equation[1] + std::sqrt(discriminant)) / (2 * equation[2]) << std::endl;
			oss << (-equation[1] - std::sqrt(discriminant)) / (2 * equation[2]);
		}
		else if (discriminant == 0)
		{
			oss << "Discriminant is null, the solution is:" << std::endl;
			oss << (-equation[1] / (equation[2] * 2));
		}
		else
			oss << "Discriminant is negative, there is no solution";
	}
	else if (equation.size() == 2)
	{
		right_side -= equation[0];
		right_side /= equation[1];
		oss << "The solution is: ";
		oss << right_side;
	}
	else if (equation.size() == 1)
	{
		if (equation[0] != 0)
			oss << "There is no solution";
		else
			oss << "The solution is: [-∞:+∞]";
	}
	else
		oss << "The solution is: [-∞:+∞]";
	return (oss.str());
}

int		main(int argc, char **argv)
{
	std::vector<float> equation;
	if (argc != 2)
	{
		std::cerr << "Usage: ./computor \"equation\"" << std::endl;
		return (1);
	}
	equation = pars_input(argv[1]);
	clear_equation(equation);
	std::cout << "Reduced form: " << equation_to_s(equation) << std::endl;
	std::cout << "Polynomial degree: ";
	if (equation.size() != 0)
		std::cout << equation.size() - 1 << std::endl;
	else
		std::cout << "0" << std::endl;
	std::cout << solve_equation(equation) << std::endl;
	return (0);
}
