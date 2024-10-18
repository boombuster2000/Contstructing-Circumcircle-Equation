#include <iostream>
#include <string>
#include <vector>

#define DEBUG_OUTPUT true

struct Coords
{
	float x, y;
};

typedef std::vector<Coords> CoordsVector;

CoordsVector GetPointsOfTriangle()
{
	CoordsVector pointsOfTriangle;

	for (int i = 0; i < 3; i++) // Loops 3 times to get 3 points.
	{
		// Get coordinates from user input.
		std::string userInputedCoords;
		std::cout << "Coordinate " << i + 1 << " {x,y}: ";
		std::cin >> userInputedCoords;

		// Split string into two parts seperated by comma.
		size_t commaIndex = userInputedCoords.find(',');
		std::string xOrdinate = userInputedCoords.substr(0, commaIndex);
		std::string yOrdinate = userInputedCoords.substr(commaIndex + 1);

		//Convert to float and append to vector.
		pointsOfTriangle.push_back({ std::stof(xOrdinate), std::stof(yOrdinate) });
	}

	if (DEBUG_OUTPUT) for (int i = 0; i < 3; i++) std::cout << "Point " << i << ": " << pointsOfTriangle[i].x << " " << pointsOfTriangle[i].y << std::endl;

	return pointsOfTriangle;
}

Coords CalculateMidpoint(Coords pointA, Coords pointB)
{
	Coords midpoint;

	midpoint.x = pointA.x - pointB.x;
	midpoint.x /= 2;
	midpoint.x = midpoint.x * (-1 * (midpoint.x<0)); // To get absolute value (non-negative)
	midpoint.x += pointA.x;

	midpoint.y = pointA.y - pointB.y;
	midpoint.y /= 2;
	midpoint.y = midpoint.y * (-1 * (midpoint.y < 0)); // To get absolute value (non-negative)
	midpoint.y += pointA.y;

	return midpoint;
}

CoordsVector GetMidpointsBetweenfPointsOfTriangle(CoordsVector pointsOfTriangle)
{
	CoordsVector midpoints;

	midpoints.push_back(CalculateMidpoint(pointsOfTriangle[0], pointsOfTriangle[1]));
	midpoints.push_back(CalculateMidpoint(pointsOfTriangle[0], pointsOfTriangle[2]));
	midpoints.push_back(CalculateMidpoint(pointsOfTriangle[1], pointsOfTriangle[2]));

	if (DEBUG_OUTPUT) for (int i = 0; i<3; i++) std::cout << "Midpoint " << i << ": " << midpoints[i].x << " " << midpoints[i].y << std::endl;

	return midpoints;
}

int main()
{
	CoordsVector pointsOfTriangle = GetPointsOfTriangle();
	CoordsVector midpointsOfTriangle = GetMidpointsBetweenfPointsOfTriangle(pointsOfTriangle);

	return 0;
}
