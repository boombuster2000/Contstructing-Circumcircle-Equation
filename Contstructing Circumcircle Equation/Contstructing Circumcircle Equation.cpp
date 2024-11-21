#include <iostream>
#include <string>
#include <vector>

#define DEBUG_OUTPUT false

struct Coords
{
	double x, y;
};

struct LinearLine
{
	// ay= bx + c
	double a, b, c;
};

struct TriangleEdge {
	LinearLine line, perpendicularBisector;
	Coords midpoint, pointA, pointB;
};

struct CircleEquation {
	// r^2 = (x - xCoord)^2 + (y - yCoord)^2
	Coords centreOfCircle;
	double radius;

	std::string ToString() {
		return "(x - " + std::to_string(centreOfCircle.x) + ")^2 + (y - " + std::to_string(centreOfCircle.y) + ")^2 = " + std::to_string(pow(radius,2));
	}
};

typedef std::vector<Coords> CoordsVector;

void PrintLine(LinearLine line)
{
	std::cout << line.a << "y = " << line.b << "x + " << line.c << std::endl;
}

Coords GetPointOfTriangleFromUser()
{
	Coords point;

	// Get coordinates from user input.
	std::string userInputedCoords;
	std::cout << "Coordinate {x,y}: ";
	std::cin >> userInputedCoords;

	// Split string into two parts seperated by comma.
	size_t commaIndex = userInputedCoords.find(',');
	std::string xOrdinate = userInputedCoords.substr(0, commaIndex);
	std::string yOrdinate = userInputedCoords.substr(commaIndex + 1);

	//Convert to float and append to vector.
	point = { std::stof(xOrdinate), std::stof(yOrdinate) };

	if (DEBUG_OUTPUT) std::cout << point.x << " " << point.y << std::endl;

	return point;
}

Coords CalculateMidpoint(Coords pointA, Coords pointB)
{
	Coords midpoint;

	midpoint.x = (pointA.x + pointB.x)/2;
	midpoint.y = (pointA.y + pointB.y)/2;

	return midpoint;
}

double GetIntercept(LinearLine line, Coords pointA)
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
	perpendicularLine.b = -line.a;

	perpendicularLine.c = GetIntercept(perpendicularLine, pointA);

	if (DEBUG_OUTPUT) PrintLine(perpendicularLine);

	return perpendicularLine;
}

Coords GetIntersectionOfTwoLinearLines(LinearLine lineA, LinearLine lineB)
{
	Coords intersection;

	double scaleFactor = lineA.a / lineB.a;

	// Finding new coefficients.
	lineB.a *= scaleFactor;
	lineB.b *= scaleFactor;
	lineB.c *= scaleFactor;

	double xCoefficient = lineA.b - lineB.b;
	double c = lineB.c - lineA.c;

	intersection.x = c / xCoefficient;
	intersection.y = ((lineA.b * intersection.x) + lineA.c) / lineA.a;

	if (DEBUG_OUTPUT) std::cout << "(" << intersection.x << "," << intersection.y << ")" << std::endl;
	return intersection;
}

CircleEquation GenerateCircleEquation(Coords centreOfCircle, Coords pointOnCircumference) {
	CircleEquation circleEquation;

	circleEquation.centreOfCircle = centreOfCircle;

	double xDistance = pow((centreOfCircle.x - pointOnCircumference.x), 2);
	double yDistance = pow((centreOfCircle.y - pointOnCircumference.y), 2);
	circleEquation.radius = sqrt(xDistance + yDistance);

	return circleEquation;
}

int main()
{
	// -4, 2
	// -5, 3
	// -2, 6

	std::vector<TriangleEdge> triangleEdges = { TriangleEdge{},  TriangleEdge{}, TriangleEdge{} };

	CoordsVector points;

	for (int i =0; i<3; i++) 
	{
		 points.push_back(GetPointOfTriangleFromUser());
	}

	triangleEdges[0].pointA = points[0];
	triangleEdges[0].pointB = points[1];

	triangleEdges[1].pointA = points[0];
	triangleEdges[1].pointB = points[2];

	triangleEdges[2].pointA = points[1];
	triangleEdges[2].pointB = points[2];

	if (DEBUG_OUTPUT) std::cout << "\n";

	for (int i = 0; i<triangleEdges.size(); i++)
	{
		triangleEdges[i].midpoint = CalculateMidpoint(triangleEdges[i].pointA, triangleEdges[i].pointB);
		triangleEdges[i].line = GetLinearLineEquationBetweenTwoPoints(triangleEdges[i].pointA, triangleEdges[i].pointB);
		triangleEdges[i].perpendicularBisector = GetPerpendicularLinearEquation(triangleEdges[i].line, triangleEdges[i].midpoint);
	}

	if (DEBUG_OUTPUT) std::cout << "\n";

	CoordsVector intersections;

	intersections.push_back(GetIntersectionOfTwoLinearLines(triangleEdges[0].perpendicularBisector, triangleEdges[1].perpendicularBisector));
	intersections.push_back(GetIntersectionOfTwoLinearLines(triangleEdges[0].perpendicularBisector, triangleEdges[2].perpendicularBisector));
	intersections.push_back(GetIntersectionOfTwoLinearLines(triangleEdges[1].perpendicularBisector, triangleEdges[2].perpendicularBisector));

	CircleEquation circleEquation = GenerateCircleEquation(intersections[0], triangleEdges[0].pointA);
	
	std::cout << circleEquation.ToString() << std::endl;
	
	return 0;
}


