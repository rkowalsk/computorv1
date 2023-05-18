#include "computor.hpp"

double	sqrt(double input)
{
	double	root = input / 4;
	size_t	i = 0;

	while (i < 32)
	{
		root = (root + (input / root)) / 2;
		i++;
	}
	return (root);
}


std::string	second_degree(std::vector<float> const &equation)
{
	std::ostringstream	oss;

	float	discriminant;
	discriminant = equation[1] * equation[1] - 4 * equation[0] * equation[2];
	oss << "Discriminant: " << discriminant << std::endl;
	if (discriminant > 0)
	{
		oss << "Discriminant is strictly positive, the two solutions are:" << std::endl;
		oss << (-equation[1] + sqrt(discriminant)) / (2 * equation[2]) << std::endl;
		oss << (-equation[1] - sqrt(discriminant)) / (2 * equation[2]);
	}
	else if (discriminant == 0)
	{
		oss << "Discriminant is null, the solution is:" << std::endl;
		oss << (-equation[1] / (equation[2] * 2));
	}
	else
	{
		oss << "Discriminant is negative, the two solutions are:" << std::endl;
		oss << ((-equation[1]) / (2 * equation[2]));
		oss << " + " << (sqrt(-discriminant)/(2 * equation[2])) << 'i' << std::endl;
		oss << ((-equation[1]) / (2 * equation[2]));
		oss << " - " << (sqrt(-discriminant)/(2 * equation[2])) << 'i';

		// unsimplified version
		// oss << '(' << -equation[1] << " + i√" << -discriminant << ") / ";
		// oss << (2 * equation[2]) << std::endl;
		// oss << '(' << -equation[1] << " - i√" << -discriminant << ") / ";
		// oss << (2 * equation[2]);
	}
	return (oss.str());
}

std::string	first_degree(std::vector<float> const &equation)
{
	float				right_side = 0;
	std::ostringstream	oss;

	right_side -= equation[0];
	right_side /= equation[1];
	oss << "The solution is: ";
	oss << right_side;
	return (oss.str());
}

std::string	solve_equation(std::vector<float> equation)
{
	std::string	solution;

	if (equation.size() > 3)
		solution = "The polynomial degree is stricly greater than 2, I can't solve.";
	else if (equation.size() == 3)
	{
		solution = second_degree(equation);
	}
	else if (equation.size() == 2)
	{
		solution = first_degree(equation);
	}
	else if (equation.size() == 1)
	{
		if (equation[0] != 0)
			solution = "There is no solution";
		else
			solution = "The solution is: [-∞:+∞]";
	}
	else
		solution = "The solution is: [-∞:+∞]";
	return (solution);
}
