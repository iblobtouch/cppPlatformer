#pragma once
class Point {
	public: double x;
	public: double y;
	public: Point(double x, double y);
	public: Point();
			/// <summary>
			/// Converts a given angle in degrees to radians for use in other functions.
			/// </summary>
			/// <param name="angle">An angle in degrees</param>
			/// <returns>The given angle, in Radians</returns>
	private: double toRadians(double angle);
			 /// <summary>
			 /// Sets the x and y values of this point to the given x and y values.
			 /// </summary>
			 /// <param name="x"></param>
			 /// <param name="y"></param>
	public: void setPoint(double x, double y);
			/// <summary>
			/// Sets this points values to match the given point, while keeping this point independant.
			/// </summary>
			/// <param name="p"></param>
	public: void setPoint(Point* p);
			/// <summary>
			/// Adds the given x and y values to this points x and y values.
			/// </summary>
			/// <param name="x"></param>
			/// <param name="y"></param>
	public: void add(double x, double y);

	public: void add(Point* p);

	public: double getX();

	public: double getY();
			/// <summary>
			/// Gets the direct, straight line distance between 2 points, ignoring anything between them.
			/// </summary>
			/// <param name="p"></param>
			/// <returns></returns>
	public: double getDistance(Point* p);
			/// <summary>
			/// <para>Gets the angle between this point and a given point. </para>
			/// This angle is what you get if you drew a line straight up from this point, and another from this to the given point.
			/// </summary>
			/// <param name="p"></param>
			/// <returns></returns>
	public: double getAngle(Point* p);
};

