#include "computor.hpp"

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
