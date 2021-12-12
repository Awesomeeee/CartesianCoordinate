#include <iostream>
#include <vector>
#include <cmath>


using namespace std;


template<class T>
class Matrix
{
private:
	vector<vector<T>> items;
	size_t width;
	size_t height;

public:
	Matrix(size_t height, size_t width) :
		height(height),
		width(width),
		items(height, vector<T>(width))
	{}

	size_t getHeight() const
	{
		return height;
	}
	size_t getWidth() const
	{
		return width;
	}

	vector<T>& operator[](const size_t index)
	{
		return items[index];
	}
	vector<T> operator[](const size_t index) const
	{
		return items[index];
	}

	Matrix<T> operator+(const Matrix<T>& matrix)
	{
		if ((height != matrix.height) || (width != matrix.width)) {
			throw "Matrices must be the same size.";
		}

		Matrix<T> result(height, width);
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				result[i][j] = (*this)[i][j] + matrix[i][j];
			}
		}

		return result;
	}

	template<class T>
	friend ostream& operator<<(ostream& ost, const Matrix<T>& matrix);
};

template<class T>
ostream& operator<<(ostream& ost, const Matrix<T>& matrix)
{
	for (int i = 0; i < matrix.height; ++i) {
		for (int j = 0; j < matrix.width; ++j) {
			ost << matrix[i][j] << ' ';
		}
		ost << '\n';
	}
	return ost;
}



class PolarCoordinates
{
private:
	double radius;
	double angle;

public:
	PolarCoordinates(double radius = 0, double angle = 0) :
		radius(radius),
		angle(angle)
	{ }

	double getRadius() const
	{
		return radius;
	}
	double getAngle() const
	{
		return angle;
	}

	void setRadius(double newradius)
	{
		radius = newradius;
	}
	void setAngle(double newAngle)
	{
		angle = newAngle;
	}

	PolarCoordinates operator+(const PolarCoordinates& polarCoordinates)
	{
		double x1 = radius * cos(angle);
		double y1 = radius * sin(angle);
		double x2 = polarCoordinates.radius * cos(polarCoordinates.angle);
		double y2 = polarCoordinates.radius * sin(polarCoordinates.angle);

		double resultX = x1 + x2;
		double resultY = y1 + y2;

		return PolarCoordinates(sqrt(pow(resultX, 2) + pow(resultY, 2)), atan(resultY / resultX));
	}

	friend ostream& operator<<(ostream& ost, const PolarCoordinates& polarCoordinates);
};

ostream& operator<<(ostream& ost, const PolarCoordinates& polarCoordinates)
{
	return ost << "(r: " << polarCoordinates.radius << "; a: " << polarCoordinates.angle << ')';
}


class CartesianCoordinates
{
private:
	vector<double> coordinates;

public:
	CartesianCoordinates(vector<double> coordinates = {}) :
		coordinates(coordinates)
	{ }

	double getCoordinate(size_t n) const
	{
		return coordinates[n];
	}
	void setCoordinate(size_t n, double coordinate)
	{
		coordinates[n] = coordinate;
	}

	CartesianCoordinates operator+(const CartesianCoordinates& cartesianCoordinates)
	{
		if (coordinates.size() != cartesianCoordinates.coordinates.size()) {
			throw "It is impossible to add coordinates with different numbers of bases.";
		}

		vector<double> result(coordinates.size());
		for (int i = 0; i < coordinates.size(); ++i) {
			result[i] = coordinates[i] + cartesianCoordinates.coordinates[i];
		}

		return CartesianCoordinates(result);
	}

	friend ostream& operator<<(ostream& ost, const CartesianCoordinates& cartesianCoordinates);
};

ostream& operator<<(ostream& ost, const CartesianCoordinates& cartesianCoordinates)
{
	for (int i = 0; i < cartesianCoordinates.coordinates.size(); ++i) {
		ost << '(' << cartesianCoordinates.coordinates[i];
		if (i + 1 != cartesianCoordinates.coordinates.size()) {
			cout << "; ";
		}
	}
	ost << ')';

	return ost;
}


int main()
{
	const int HEIGHT = 3;
	const int WIDTH = 4;


	Matrix<PolarCoordinates> A(HEIGHT, WIDTH);
	Matrix<PolarCoordinates> B(HEIGHT, WIDTH);
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			A[i][j] = PolarCoordinates(rand() % 10 + 1, rand() % 10 + 1);
			B[i][j] = PolarCoordinates(rand() % 10 + 1, rand() % 10 + 1);
		}
	}

	Matrix<PolarCoordinates> C = A + B;

	cout << "Matrix A:" << endl;
	cout << A << endl;

	cout << "Matrix B:" << endl;
	cout << B << endl;

	cout << "Matrix C = A + B:" << endl;
	cout << C << endl;

	return 0;
}