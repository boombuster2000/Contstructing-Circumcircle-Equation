#include <iostream>
#include <string>
#include <vector>

#define DEBUG_OUTPUT true

struct Coords
{
	float x, y;
};

struct LinearLine
{
	float gradient, yIntercept;
};


typedef std::vector<Coords> CoordsVector;
typedef std::vector<LinearLine> LinearLinesVector;

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

LinearLine GetLinearLineEquationBetweenTwoPoints(Coords pointA, Coords pointB)
{
	LinearLine line;

	line.gradient = (pointA.y - pointB.y) / (pointA.x - pointB.x);
	line.yIntercept = pointA.y - (line.gradient * pointA.x);

	if (DEBUG_OUTPUT) std::cout << "Gradient: " << line.gradient << std::endl;
	if (DEBUG_OUTPUT) std::cout << "Y-Intercept: " << line.yIntercept << std::endl;

	return line;
}

LinearLine GetPerpendicularLinearEquation(LinearLine line, Coords pointA)
{
	LinearLine perpendicularLine;
	perpendicularLine.gradient = pow((line.gradient * -1), -1);

	perpendicularLine.yIntercept = pointA.y - (perpendicularLine.gradient * pointA.x);

	if (DEBUG_OUTPUT) std::cout << "Gradient: " << perpendicularLine.gradient << std::endl;
	if (DEBUG_OUTPUT) std::cout << "Y-Intercept: " << perpendicularLine.yIntercept << std::endl;

	return perpendicularLine;
}


int main()
{
	CoordsVector pointsOfTriangle = GetPointsOfTriangle();
	CoordsVector midpointsOfTriangle = GetMidpointsBetweenfPointsOfTriangle(pointsOfTriangle);

	LinearLinesVector edgesOfTriangle;
	edgesOfTriangle.push_back(GetLinearLineEquationBetweenTwoPoints(pointsOfTriangle[0], pointsOfTriangle[1]));
	edgesOfTriangle.push_back(GetLinearLineEquationBetweenTwoPoints(pointsOfTriangle[0], pointsOfTriangle[2]));
	edgesOfTriangle.push_back(GetLinearLineEquationBetweenTwoPoints(pointsOfTriangle[1], pointsOfTriangle[2]));

	LinearLinesVector perpendicularBisectorsOfTriangle;
	perpendicularBisectorsOfTriangle.push_back(GetPerpendicularLinearEquation(edgesOfTriangle[0], midpointsOfTriangle[1]));
	perpendicularBisectorsOfTriangle.push_back(GetPerpendicularLinearEquation(edgesOfTriangle[0], midpointsOfTriangle[2]));
	perpendicularBisectorsOfTriangle.push_back(GetPerpendicularLinearEquation(edgesOfTriangle[1], midpointsOfTriangle[2]));


	return 0;
}
