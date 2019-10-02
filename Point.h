#pragma once
#include <SDL.h>

struct PointVals {
	double x = 0;
	double y = 0;
};

class Point {
public: 
	double x, y;
	Point(const Point& oldPoint);
	Point(double x, double y);
	Point();
			/// <summary>
			/// Converts a given angle in degrees to radians.
			/// </summary>
			/// <param name="angle">An angle in degrees</param>
			/// <returns>The given angle, in Radians</returns>
	static double toRadians(double degrees);
	/// <summary>
	/// Converts a given angle in radians to degrees.
	/// </summary>
	/// <param name="angle">An angle in degrees</param>
	/// <returns>The given angle, in Radians</returns>
	static double toDegrees(double radians);
			 /// <summary>
			 /// Sets the x and y values of this point to the given x and y values.
			 /// </summary>
			 /// <param name="x"></param>
			 /// <param name="y"></param>
	void setPoint(double x, double y);
			/// <summary>
			/// Sets this points values to match the given point, while keeping this point independant.
			/// </summary>
			/// <param name="p"></param>
	void setPoint(Point* p);
			/// <summary>
			/// Sets this points values to match the given point, while keeping this point independant.
			/// </summary>
			/// <param name="p"></param>
	void setPoint(PointVals p);
			/// <summary>
			/// Adds the given x and y values to this points x and y values.
			/// </summary>
			/// <param name="x"></param>
			/// <param name="y"></param>
	void add(double x, double y);

	void add(Point* p);

	double getX();

	double getY();

	SDL_Point getAsSDLPoint();
			/// <summary>
			/// Gets the direct, straight line distance between 2 points, ignoring anything between them.
			/// </summary>
			/// <param name="p"></param>
			/// <returns></returns>
	double getDistance(Point* p);
			/// <summary>
			/// <para>Gets the angle between this point and a given point. </para>
			/// This angle is what you get if you drew a line straight up from this point, and another from this to the given point.
			/// </summary>
			/// <param name="p"></param>
			/// <returns></returns>
	double getAngle(Point* p);
	double getAngle(SDL_Point p);
	static PointVals setAccelToPoint(Point* source, SDL_Point target, double speed);
	static PointVals setAccelToPoint(SDL_Point source, SDL_Point target, double speed);
	void moveInDirection(int distance, double angle);
};

