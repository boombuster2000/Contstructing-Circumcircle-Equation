#include <iostream>
#include <string>
#include <vector>

struct Coords
{
	float x, y;
};

std::vector<Coords> GetPointsOfTriangle()
{
	std::vector<Coords> pointsOfTriangle;

	for (int i = 0; i < 3; i++) // Loops 3 times to get 3 points.
	{
		// Get coordinates from user input.
		std::string userInputedCoords;
		std::cout << "Coordinate " << i + 1 << " {x,y}: ";
		std::cin >> userInputedCoords;

		// Split string into two parts seperated by comma.
		int commaIndex = userInputedCoords.find(',');
		std::string xOrdinate = userInputedCoords.substr(0, commaIndex);
		std::string yOrdinate = userInputedCoords.substr(commaIndex + 1);

		std::cout << "X-Ordinate: " << xOrdinate << std::endl;
		std::cout << "Y-Ordinate: " << yOrdinate << std::endl;

		//Convert to float and append to vector.
		pointsOfTriangle.push_back({ std::stof(xOrdinate), std::stof(xOrdinate) });
	}

	return pointsOfTriangle;
}

int main()
{
	std::vector<Coords> pointsOfTriangle = GetPointsOfTriangle();


	return 0;
}
