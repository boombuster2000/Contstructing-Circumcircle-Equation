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
	// ay= bx + c
	float a, b, c;
};

typedef std::vector<Coords> CoordsVector;
typedef std::vector<LinearLine> LinearLinesVector;

void PrintLine(LinearLine line)
{
	std::cout << line.a << "y = " << line.b << "x + " << line.c << std::endl;
}

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

float GetIntercept(LinearLine line, Coords pointA)
{
	return (line.a * pointA.y) - (line.b * pointA.x);
}

LinearLine GetLinearLineEquationBetweenTwoPoints(Coords pointA, Coords pointB)
{
	LinearLine line;
	
	line.a = 1;
	line.b = (pointA.y - pointB.y) / (pointA.x - pointB.x);

	if (isinf(line.b))
	{
		line.b = 1;
		line.a = (pointA.x - pointB.x) / (pointA.y - pointB.y);
	}

	line.c = GetIntercept(line, pointA);

	if (DEBUG_OUTPUT) PrintLine(line);

	return line;
}

LinearLine GetPerpendicularLinearEquation(LinearLine line, Coords pointA)
{
	LinearLine perpendicularLine;
	perpendicularLine.a = line.b;
	perpendicularLine.b = line.a;

	perpendicularLine.c = GetIntercept(perpendicularLine, pointA);

	if (DEBUG_OUTPUT) PrintLine(perpendicularLine);

	return perpendicularLine;
}

Coords GetIntersectionOfTwoLinearLines(LinearLine lineA, LinearLine lineB)
{
	Coords intersection;

	intersection.x = (lineA.b > lineB.b) * (lineA.b - lineB.b) + (lineB.b > lineA.b) * (lineB.b - lineA.b);
	intersection.x = (lineA.b > lineB.b) * ((lineB.c-lineA.c)/intersection.x) + (lineB.b > lineA.b)* ((lineA.c - lineB.c) / intersection.x);

	intersection.y = (lineA.b * intersection.x) + lineA.c;

	if (DEBUG_OUTPUT) std::cout << "(" << intersection.x << "," << intersection.y << ")" << std::endl;
	return intersection;
}

int main()
{
	// -4, 2
	// -5, 3
	// -2, 6
	CoordsVector pointsOfTriangle = GetPointsOfTriangle();
	if (DEBUG_OUTPUT) std::cout << "\n";

	CoordsVector midpointsOfTriangle = GetMidpointsBetweenfPointsOfTriangle(pointsOfTriangle);

	if (DEBUG_OUTPUT) std::cout << "\n";


	LinearLinesVector edgesOfTriangle;
	edgesOfTriangle.push_back(GetLinearLineEquationBetweenTwoPoints(pointsOfTriangle[0], pointsOfTriangle[1]));
	edgesOfTriangle.push_back(GetLinearLineEquationBetweenTwoPoints(pointsOfTriangle[0], pointsOfTriangle[2]));
	edgesOfTriangle.push_back(GetLinearLineEquationBetweenTwoPoints(pointsOfTriangle[1], pointsOfTriangle[2]));


	if (DEBUG_OUTPUT) std::cout << "\n";

	LinearLinesVector perpendicularBisectorsOfTriangle;
	perpendicularBisectorsOfTriangle.push_back(GetPerpendicularLinearEquation(edgesOfTriangle[0], midpointsOfTriangle[1]));
	perpendicularBisectorsOfTriangle.push_back(GetPerpendicularLinearEquation(edgesOfTriangle[0], midpointsOfTriangle[2]));
	perpendicularBisectorsOfTriangle.push_back(GetPerpendicularLinearEquation(edgesOfTriangle[1], midpointsOfTriangle[2]));


	return 0;
	if (DEBUG_OUTPUT) std::cout << "\n";

	CoordsVector intersections;
	intersections.push_back(GetIntersectionOfTwoLinearLines(perpendicularBisectorsOfTriangle[0], perpendicularBisectorsOfTriangle[1]));
	intersections.push_back(GetIntersectionOfTwoLinearLines(perpendicularBisectorsOfTriangle[0], perpendicularBisectorsOfTriangle[2]));
	intersections.push_back(GetIntersectionOfTwoLinearLines(perpendicularBisectorsOfTriangle[1], perpendicularBisectorsOfTriangle[2]));



	return 0;
}
