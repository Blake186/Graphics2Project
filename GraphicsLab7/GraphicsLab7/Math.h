#include <iostream> // cin / cout
#include <Windows.h>
//#include "RasterSurface.h" // Raster Wrapper
#include "XTime.h" // timer class 
#include <assert.h> // Debugging Purposes
#include <random>
#include <math.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
//#include "defines.h"






struct Line
{
	// variables 
	float StartX;
	float StartY;
	float EndX;
	float EndY;
	UINT XY;
	UINT AB;
	UINT Testx;
	UINT TestY;

	// Coord Struct 
	COORD Start;
	COORD End;
	COORD Test;
	UINT XY_Equation(UINT _x1, UINT _y1, UINT _x2, UINT _y2);
	UINT AB_Equation(UINT _x1, UINT _y1, UINT _x2, UINT _y2);
	//UINT Slope(UINT _x1, UINT _y1, UINT _x2, UINT _y2);

	//UINT ImplicitLineEquation(UINT _x1, UINT _y1, UINT _x2, UINT _y2, UINT _testx, UINT _testy);

	int ImplicitLineEquation(UINT _x1, UINT _y1, UINT _x2, UINT _y2, float _testx, float _testy)
	{
		int temp;
		int temp1 = int((int)(_y1 - _y2) * _testx);
		int temp2 = (int)(_x2 - _x1) * _testy;
		int  temp3 = int((_x1 * _y2) - (_y1 * _x2));
		temp = temp1 + temp2 + temp3;
		return temp;


	}
	int ImplicitLineEquation(float _x1, float _y1, float _x2, float _y2, float _testx, float _testy)
	{
		int temp;
		int temp1 = (int)(_y1 - _y2) * _testx;
		int temp2 = (int)(_x2 - _x1) * _testy;
		int  temp3 = int((_x1 * _y2) - (_y1 * _x2));
		temp = temp1 + temp2 + temp3;
		return temp;


	}
	static float ImplicitLineEquation(Line line, float _testx, float _testy)
	{
		float temp;
		float temp1 = (line.StartY - line.EndY) * _testx;
		float temp2 = (line.EndX - line.StartX) * _testy;
		float  temp3 = ((line.StartX * line.EndY) - (line.StartY * line.EndX));
		temp = temp1 + temp2 + temp3;
		return temp;
	}

	float Slope(UINT _x1, UINT _y1, UINT _x2, UINT _y2)
	{
		float temp;
		temp = (float)(_y2 - _y1) / ((_x2 - _x1));
		return temp;

	}

	float SlopeEX(UINT _x1, UINT _x2)
	{
		float temp;
		temp = (float)((int)_x2 - (int)_x1) + FLT_EPSILON;
		return temp;

	}

	float SlopeEY(UINT _y1, UINT _y2)
	{
		float temp;
		temp = (float)((int)_y2 - (int)_y1) + FLT_EPSILON;
		return temp;

	}

	float SlopeInverse(UINT _x1, UINT _y1, UINT _x2, UINT _y2)
	{
		float temp;
		temp = (float)(_x2 - _x1) / (_y2 - _y1);
		return temp;

	}

	float DeltaX(UINT _x1, UINT _x2)
	{
		return float((int)_x2 - (int)_x1);
	}

	float DeltaY(UINT _y1, UINT _y2)
	{
		return float((int)_y2 - (int)_y1);
	}

	float Ratio(UINT _testX, UINT _startX, UINT _x1, UINT _x2)
	{
		return (_testX - _startX) / DeltaX(_x1, _x2);

	}

	float Lerp(UINT _x, UINT _y, float _ratio)
	{
		return (float)_x + (_ratio *((float)_y - (float)_x));

	}




};


struct MY_Vertex
{
	float m_xyz[4];
	float _color[4];
	float U;
	float V;
	/*MY_Vertex(float _x = 0, float _y = 0, float _z = 0, float _w = 1, unsigned int color = 0xFFFFFFFF, float _u = 0, float _v = 0)
	{
		m_xyz[0] = _x;
		m_xyz[1] = _y;
		m_xyz[2] = _z;
		m_xyz[3] = _w;
		_color = color;
		U = _u;
		V = _v;
	}*/



	void setVertex(float _x, float _y, float _z, float _w)
	{
		m_xyz[0] = _x;
		m_xyz[1] = _y;
		m_xyz[2] = _z;
		m_xyz[3] = _w;


	}

};


struct MY_Matrix
{

	/*union
	{

		struct Matrix
		{
			float a11, a12, a13, a21, a22, a23, a31, a32, a33;

			void SetMatrix3x3(float _a11, float _a12, float _a13, float _a21, float _a22, float _a23, float _a31, float _a32, float _a33)
			{


				a11 = _a11;
				a12 = _a12;
				a13 = _a13;
				a21 = _a21;
				a22 = _a22;
				a23 = _a23;
				a31 = _a31;
				a32 = _a32;
				a33 = _a33;
			}
		};
		Matrix m_Matrix1D[9];
		Matrix m_Matrix2D[3][3];



	};*/
	float m_matrix3x3[9];
	
	union
	{ float m_matrix4x4[16];
	float m_matrix4x42D[4][4];
		struct
		{
			float _a11, _a12, _a13, _a14,
				_a21, _a22, _a23, _a24,
				_a31, _a32, _a33, _a34,
				_a41, _a42, _a43, _a44;

		};
	};
 
	//	0 1 2        0 1 2
	//  4 5 6  X     3  4 5
	//  7 8 9        6 7  8
	void SetMatrix3x3(float _a11, float _a12, float _a13, float _a21, float _a22, float _a23, float _a31, float _a32, float _a33)
	{


		m_matrix3x3[0] = _a11;
		m_matrix3x3[1] = _a12;
		m_matrix3x3[2] = _a13;
		m_matrix3x3[3] = _a21;
		m_matrix3x3[4] = _a22;
		m_matrix3x3[5] = _a23;
		m_matrix3x3[6] = _a31;
		m_matrix3x3[7] = _a32;
		m_matrix3x3[8] = _a33;

	}

	void SetMatrix4X4(float _a11, float _a12, float _a13, float _a14, float _a21, float _a22, float _a23, float _a24, float _a31,
		float _a32, float _a33, float _a34, float _a41, float _a42, float _a43, float _a44)
	{

		m_matrix4x4[0] = _a11;
		m_matrix4x4[1] = _a12;
		m_matrix4x4[2] = _a13;
		m_matrix4x4[3] = _a14;

		m_matrix4x4[4] = _a21;
		m_matrix4x4[5] = _a22;
		m_matrix4x4[6] = _a23;
		m_matrix4x4[7] = _a24;

		m_matrix4x4[8] = _a31;
		m_matrix4x4[9] = _a32;
		m_matrix4x4[10] = _a33;
		m_matrix4x4[11] = _a34;

		m_matrix4x4[12] = _a41;
		m_matrix4x4[13] = _a42;
		m_matrix4x4[14] = _a43;
		m_matrix4x4[15] = _a44;




	}


};





MY_Matrix Matrix3x3Multiplication(MY_Matrix* _Matrix1, MY_Matrix* _Matrix2)
{
	MY_Matrix NewMatrix;
	NewMatrix.m_matrix3x3[0] = (_Matrix1->m_matrix3x3[0] * _Matrix2->m_matrix3x3[0]) + (_Matrix1->m_matrix3x3[1] * _Matrix2->m_matrix3x3[3]) + (_Matrix1->m_matrix3x3[2] * _Matrix2->m_matrix3x3[6]);
	NewMatrix.m_matrix3x3[1] = (_Matrix1->m_matrix3x3[0] * _Matrix2->m_matrix3x3[1]) + (_Matrix1->m_matrix3x3[1] * _Matrix2->m_matrix3x3[4]) + (_Matrix1->m_matrix3x3[2] * _Matrix2->m_matrix3x3[7]);
	NewMatrix.m_matrix3x3[2] = (_Matrix1->m_matrix3x3[0] * _Matrix2->m_matrix3x3[2]) + (_Matrix1->m_matrix3x3[1] * _Matrix2->m_matrix3x3[5]) + (_Matrix1->m_matrix3x3[2] * _Matrix2->m_matrix3x3[8]);
	NewMatrix.m_matrix3x3[3] = (_Matrix1->m_matrix3x3[4] * _Matrix2->m_matrix3x3[0]) + (_Matrix1->m_matrix3x3[5] * _Matrix2->m_matrix3x3[3]) + (_Matrix1->m_matrix3x3[6] * _Matrix2->m_matrix3x3[6]);
	NewMatrix.m_matrix3x3[4] = (_Matrix1->m_matrix3x3[4] * _Matrix2->m_matrix3x3[1]) + (_Matrix1->m_matrix3x3[5] * _Matrix2->m_matrix3x3[4]) + (_Matrix1->m_matrix3x3[6] * _Matrix2->m_matrix3x3[7]);
	NewMatrix.m_matrix3x3[5] = (_Matrix1->m_matrix3x3[4] * _Matrix2->m_matrix3x3[2]) + (_Matrix1->m_matrix3x3[5] * _Matrix2->m_matrix3x3[5]) + (_Matrix1->m_matrix3x3[6] * _Matrix2->m_matrix3x3[8]);
	NewMatrix.m_matrix3x3[6] = (_Matrix1->m_matrix3x3[7] * _Matrix2->m_matrix3x3[0]) + (_Matrix1->m_matrix3x3[8] * _Matrix2->m_matrix3x3[3]) + (_Matrix1->m_matrix3x3[9] * _Matrix2->m_matrix3x3[6]);
	NewMatrix.m_matrix3x3[7] = (_Matrix1->m_matrix3x3[7] * _Matrix2->m_matrix3x3[1]) + (_Matrix1->m_matrix3x3[8] * _Matrix2->m_matrix3x3[4]) + (_Matrix1->m_matrix3x3[9] * _Matrix2->m_matrix3x3[7]);
	NewMatrix.m_matrix3x3[8] = (_Matrix1->m_matrix3x3[7] * _Matrix2->m_matrix3x3[2]) + (_Matrix1->m_matrix3x3[8] * _Matrix2->m_matrix3x3[5]) + (_Matrix1->m_matrix3x3[9] * _Matrix2->m_matrix3x3[8]);




	return NewMatrix;
}


MY_Vertex Vector3_Multipliction_Matrix3x3(MY_Vertex* _Vertex, MY_Matrix* _Matrix)
{
	MY_Vertex New_Vetex_vector;

	New_Vetex_vector.m_xyz[0] = (_Vertex->m_xyz[0] * _Matrix->m_matrix3x3[0]) + (_Vertex->m_xyz[1] * _Matrix->m_matrix3x3[3]) + (_Vertex->m_xyz[2] * _Matrix->m_matrix3x3[6]);
	New_Vetex_vector.m_xyz[1] = (_Vertex->m_xyz[0] * _Matrix->m_matrix3x3[1]) + (_Vertex->m_xyz[1] * _Matrix->m_matrix3x3[4]) + (_Vertex->m_xyz[2] * _Matrix->m_matrix3x3[7]);
	New_Vetex_vector.m_xyz[2] = (_Vertex->m_xyz[0] * _Matrix->m_matrix3x3[2]) + (_Vertex->m_xyz[1] * _Matrix->m_matrix3x3[5]) + (_Vertex->m_xyz[2] * _Matrix->m_matrix3x3[8]);
	New_Vetex_vector.m_xyz[3] = 1;


	return  New_Vetex_vector;
}


UINT Convert2Dto1D(const UINT _x, const UINT _Y, const UINT _width)
{
	// The Algorithem to Convert a 2D position into a 1D position



	return _Y * _width + _x;
}

float DeltaX(const MY_Vertex* _Vertex, const MY_Vertex* _Vertex2)
{
	return float((int)_Vertex->m_xyz[0] - (int)_Vertex2->m_xyz[0]);
}

float DeltaY(const MY_Vertex* _Vertex, const MY_Vertex* _Vertex2)
{
	return float((float)_Vertex->m_xyz[1] - (float)_Vertex2->m_xyz[1]);
}


float LerpX(const MY_Vertex* _Vertex, const MY_Vertex* _Vertex2, float _ratio)
{
	return (float)_Vertex->m_xyz[0] + (_ratio *((float)_Vertex2->m_xyz[0] - (float)_Vertex->m_xyz[0]));

}

float LerpY(const MY_Vertex* _Vertex, const MY_Vertex* _Vertex2, const float _ratio)
{
	return (float)_Vertex->m_xyz[1] + (_ratio *((float)_Vertex2->m_xyz[1] - (float)_Vertex->m_xyz[1]));
}

static float ImplicitLineEquation(MY_Vertex _Start, MY_Vertex _end, MY_Vertex Position)
{
	//float temp;
	//float temp1 = (_Start.m_xyz[1] - _end.m_xyz[1]) * Position.m_xyz[0];
	//float temp2 = (_end.m_xyz[0] - _Start.m_xyz[0]) * Position.m_xyz[1];
	//float  temp3 = ((_Start.m_xyz[0] * _end.m_xyz[1]) - (_Start.m_xyz[1] * _end.m_xyz[0]));
	//temp = temp1 + temp2 + temp3;
	//return temp;

	return ((_Start.m_xyz[1] - _end.m_xyz[1])*Position.m_xyz[0]) + ((_end.m_xyz[0] - _Start.m_xyz[0])*Position.m_xyz[1]) + (_Start.m_xyz[0] * _end.m_xyz[1]) - (_end.m_xyz[0] * _Start.m_xyz[1]);
}

float LerpZ(const MY_Vertex* _Vertex, const MY_Vertex* _Vertex2, const float _ratio)
{
	return (float)_Vertex->m_xyz[2] + (_ratio *((float)_Vertex2->m_xyz[2] - (float)_Vertex->m_xyz[2]));
}


// Matrix Math Functions 

//MY_Matrix RotationOnZAxis(float _rad)
//{
//	MY_Matrix _Matrix;
//	_Matrix.MatrixRotationZ[0] = cos(_rad);
//
//	_Matrix.MatrixRotationZ[1] = -sin(_rad);
//
//	_Matrix.MatrixRotationZ[2] = 0;
//
//	_Matrix.MatrixRotationZ[3] = sin(_rad);
//
//	_Matrix.MatrixRotationZ[4] = cos(_rad);
//
//	_Matrix.MatrixRotationZ[5] = 0;
//
//	_Matrix.MatrixRotationZ[6] = 0;
//
//	_Matrix.MatrixRotationZ[7] = 0;
//
//	_Matrix.MatrixRotationZ[8] = 1;
//
//
//
//	return _Matrix;
//
//
//}

MY_Matrix Matrix4X4Multiplication(MY_Matrix* _matrix1, MY_Matrix* _matrix2)
{
	//   0    1    2      3       //  0   1    2    3 
	//   4    5    6      7       //  4   5    6    7 
	//   8    9   10     11      //   8   9    10   11
	//   12  13   14     15      //  12   13   14   15
	MY_Matrix NewMatrix;

	// 0123 X 04812
	NewMatrix.m_matrix4x4[0] = (_matrix1->m_matrix4x4[0] * _matrix2->m_matrix4x4[0]) + (_matrix1->m_matrix4x4[1] * _matrix2->m_matrix4x4[4]) +
		(_matrix1->m_matrix4x4[2] * _matrix2->m_matrix4x4[8]) + (_matrix1->m_matrix4x4[3] * _matrix2->m_matrix4x4[12]);

	NewMatrix.m_matrix4x4[1] = (_matrix1->m_matrix4x4[0] * _matrix2->m_matrix4x4[1]) + (_matrix1->m_matrix4x4[1] * _matrix2->m_matrix4x4[5]) +
		(_matrix1->m_matrix4x4[2] * _matrix2->m_matrix4x4[9]) + (_matrix1->m_matrix4x4[3] * _matrix2->m_matrix4x4[13]);

	NewMatrix.m_matrix4x4[2] = (_matrix1->m_matrix4x4[0] * _matrix2->m_matrix4x4[2]) + (_matrix1->m_matrix4x4[1] * _matrix2->m_matrix4x4[6]) +
		(_matrix1->m_matrix4x4[2] * _matrix2->m_matrix4x4[10]) + (_matrix1->m_matrix4x4[3] * _matrix2->m_matrix4x4[14]);


	NewMatrix.m_matrix4x4[3] = (_matrix1->m_matrix4x4[0] * _matrix2->m_matrix4x4[3]) + (_matrix1->m_matrix4x4[1] * _matrix2->m_matrix4x4[7]) +
		(_matrix1->m_matrix4x4[2] * _matrix2->m_matrix4x4[11]) + (_matrix1->m_matrix4x4[3] * _matrix2->m_matrix4x4[15]);


	NewMatrix.m_matrix4x4[4] = (_matrix1->m_matrix4x4[4] * _matrix2->m_matrix4x4[0]) + (_matrix1->m_matrix4x4[5] * _matrix2->m_matrix4x4[4]) +
		(_matrix1->m_matrix4x4[6] * _matrix2->m_matrix4x4[8]) + (_matrix1->m_matrix4x4[7] * _matrix2->m_matrix4x4[12]);



	NewMatrix.m_matrix4x4[5] = (_matrix1->m_matrix4x4[4] * _matrix2->m_matrix4x4[1]) + (_matrix1->m_matrix4x4[5] * _matrix2->m_matrix4x4[5]) +
		(_matrix1->m_matrix4x4[6] * _matrix2->m_matrix4x4[9]) + (_matrix1->m_matrix4x4[7] * _matrix2->m_matrix4x4[13]);


	NewMatrix.m_matrix4x4[6] = (_matrix1->m_matrix4x4[4] * _matrix2->m_matrix4x4[2]) + (_matrix1->m_matrix4x4[5] * _matrix2->m_matrix4x4[6]) +
		(_matrix1->m_matrix4x4[6] * _matrix2->m_matrix4x4[10]) + (_matrix1->m_matrix4x4[7] * _matrix2->m_matrix4x4[14]);


	NewMatrix.m_matrix4x4[7] = (_matrix1->m_matrix4x4[4] * _matrix2->m_matrix4x4[3]) + (_matrix1->m_matrix4x4[5] * _matrix2->m_matrix4x4[7]) +
		(_matrix1->m_matrix4x4[6] * _matrix2->m_matrix4x4[11]) + (_matrix1->m_matrix4x4[7] * _matrix2->m_matrix4x4[15]);



	//   0    1    2      3       //  0   1    2    3 
	//   4    5    6      7       //  4   5    6    7 
	//   8    9   10     11      //   8   9    10   11
	//   12  13   14     15      //  12   13   14   15



	NewMatrix.m_matrix4x4[8] = (_matrix1->m_matrix4x4[8] * _matrix2->m_matrix4x4[0]) + (_matrix1->m_matrix4x4[9] * _matrix2->m_matrix4x4[4]) +
		(_matrix1->m_matrix4x4[10] * _matrix2->m_matrix4x4[8]) + (_matrix1->m_matrix4x4[11] * _matrix2->m_matrix4x4[12]);

	NewMatrix.m_matrix4x4[9] = (_matrix1->m_matrix4x4[8] * _matrix2->m_matrix4x4[1]) + (_matrix1->m_matrix4x4[9] * _matrix2->m_matrix4x4[5]) +
		(_matrix1->m_matrix4x4[10] * _matrix2->m_matrix4x4[9]) + (_matrix1->m_matrix4x4[11] * _matrix2->m_matrix4x4[13]);


	NewMatrix.m_matrix4x4[10] = (_matrix1->m_matrix4x4[8] * _matrix2->m_matrix4x4[2]) + (_matrix1->m_matrix4x4[9] * _matrix2->m_matrix4x4[6]) +
		(_matrix1->m_matrix4x4[10] * _matrix2->m_matrix4x4[10]) + (_matrix1->m_matrix4x4[11] * _matrix2->m_matrix4x4[14]);

	NewMatrix.m_matrix4x4[11] = (_matrix1->m_matrix4x4[8] * _matrix2->m_matrix4x4[3]) + (_matrix1->m_matrix4x4[9] * _matrix2->m_matrix4x4[7]) +
		(_matrix1->m_matrix4x4[10] * _matrix2->m_matrix4x4[11]) + (_matrix1->m_matrix4x4[11] * _matrix2->m_matrix4x4[15]);



	NewMatrix.m_matrix4x4[12] = (_matrix1->m_matrix4x4[12] * _matrix2->m_matrix4x4[0]) + (_matrix1->m_matrix4x4[13] * _matrix2->m_matrix4x4[4]) +
		(_matrix1->m_matrix4x4[14] * _matrix2->m_matrix4x4[8]) + (_matrix1->m_matrix4x4[15] * _matrix2->m_matrix4x4[12]);

	NewMatrix.m_matrix4x4[13] = (_matrix1->m_matrix4x4[12] * _matrix2->m_matrix4x4[1]) + (_matrix1->m_matrix4x4[13] * _matrix2->m_matrix4x4[5]) +
		(_matrix1->m_matrix4x4[14] * _matrix2->m_matrix4x4[9]) + (_matrix1->m_matrix4x4[15] * _matrix2->m_matrix4x4[13]);

	NewMatrix.m_matrix4x4[14] = (_matrix1->m_matrix4x4[12] * _matrix2->m_matrix4x4[2]) + (_matrix1->m_matrix4x4[13] * _matrix2->m_matrix4x4[6]) +
		(_matrix1->m_matrix4x4[14] * _matrix2->m_matrix4x4[10]) + (_matrix1->m_matrix4x4[15] * _matrix2->m_matrix4x4[14]);

	NewMatrix.m_matrix4x4[15] = (_matrix1->m_matrix4x4[12] * _matrix2->m_matrix4x4[3]) + (_matrix1->m_matrix4x4[13] * _matrix2->m_matrix4x4[7]) +
		(_matrix1->m_matrix4x4[14] * _matrix2->m_matrix4x4[11]) + (_matrix1->m_matrix4x4[15] * _matrix2->m_matrix4x4[15]);




	return NewMatrix;



}

MY_Matrix Matrix4x4Identity()
{
	MY_Matrix m_Identity4x4;

	m_Identity4x4.m_matrix4x4[0] = 1;
	m_Identity4x4.m_matrix4x4[1] = 0;
	m_Identity4x4.m_matrix4x4[2] = 0;
	m_Identity4x4.m_matrix4x4[3] = 0;

	m_Identity4x4.m_matrix4x4[4] = 0;
	m_Identity4x4.m_matrix4x4[5] = 1;
	m_Identity4x4.m_matrix4x4[6] = 0;
	m_Identity4x4.m_matrix4x4[7] = 0;



	m_Identity4x4.m_matrix4x4[8] = 0;
	m_Identity4x4.m_matrix4x4[9] = 0;
	m_Identity4x4.m_matrix4x4[10] = 1;
	m_Identity4x4.m_matrix4x4[11] = 0;


	m_Identity4x4.m_matrix4x4[12] = 0;
	m_Identity4x4.m_matrix4x4[13] = 0;
	m_Identity4x4.m_matrix4x4[14] = 0;
	m_Identity4x4.m_matrix4x4[15] = 1;


	return m_Identity4x4;


}


MY_Matrix Matrix4x4Addition(MY_Matrix* _matrix1, MY_Matrix* _matrix2)
{
	MY_Matrix NewMatrixAddition;
	NewMatrixAddition.m_matrix4x4[0] = _matrix1->m_matrix4x4[0] + _matrix2->m_matrix4x4[0];
	NewMatrixAddition.m_matrix4x4[1] = _matrix1->m_matrix4x4[1] + _matrix2->m_matrix4x4[1];
	NewMatrixAddition.m_matrix4x4[2] = _matrix1->m_matrix4x4[2] + _matrix2->m_matrix4x4[2];
	NewMatrixAddition.m_matrix4x4[3] = _matrix1->m_matrix4x4[3] + _matrix2->m_matrix4x4[3];

	NewMatrixAddition.m_matrix4x4[4] = _matrix1->m_matrix4x4[4] + _matrix2->m_matrix4x4[4];
	NewMatrixAddition.m_matrix4x4[5] = _matrix1->m_matrix4x4[5] + _matrix2->m_matrix4x4[5];
	NewMatrixAddition.m_matrix4x4[6] = _matrix1->m_matrix4x4[6] + _matrix2->m_matrix4x4[6];
	NewMatrixAddition.m_matrix4x4[7] = _matrix1->m_matrix4x4[7] + _matrix2->m_matrix4x4[7];


	NewMatrixAddition.m_matrix4x4[8] = _matrix1->m_matrix4x4[8] + _matrix2->m_matrix4x4[8];
	NewMatrixAddition.m_matrix4x4[9] = _matrix1->m_matrix4x4[9] + _matrix2->m_matrix4x4[9];
	NewMatrixAddition.m_matrix4x4[10] = _matrix1->m_matrix4x4[10] + _matrix2->m_matrix4x4[10];
	NewMatrixAddition.m_matrix4x4[11] = _matrix1->m_matrix4x4[11] + _matrix2->m_matrix4x4[11];


	NewMatrixAddition.m_matrix4x4[12] = _matrix1->m_matrix4x4[12] + _matrix2->m_matrix4x4[12];
	NewMatrixAddition.m_matrix4x4[13] = _matrix1->m_matrix4x4[13] + _matrix2->m_matrix4x4[13];
	NewMatrixAddition.m_matrix4x4[14] = _matrix1->m_matrix4x4[14] + _matrix2->m_matrix4x4[14];
	NewMatrixAddition.m_matrix4x4[15] = _matrix1->m_matrix4x4[15] + _matrix2->m_matrix4x4[15];


	return NewMatrixAddition;
}

MY_Matrix Matrix4x4Subtraction(MY_Matrix* _matrix1, MY_Matrix* _matrix2)
{
	MY_Matrix NewMatrixAddition;
	NewMatrixAddition.m_matrix4x4[0] = _matrix1->m_matrix4x4[0] - _matrix2->m_matrix4x4[0];
	NewMatrixAddition.m_matrix4x4[1] = _matrix1->m_matrix4x4[1] - _matrix2->m_matrix4x4[1];
	NewMatrixAddition.m_matrix4x4[2] = _matrix1->m_matrix4x4[2] - _matrix2->m_matrix4x4[2];
	NewMatrixAddition.m_matrix4x4[3] = _matrix1->m_matrix4x4[3] - _matrix2->m_matrix4x4[3];

	NewMatrixAddition.m_matrix4x4[4] = _matrix1->m_matrix4x4[4] - _matrix2->m_matrix4x4[4];
	NewMatrixAddition.m_matrix4x4[5] = _matrix1->m_matrix4x4[5] - _matrix2->m_matrix4x4[5];
	NewMatrixAddition.m_matrix4x4[6] = _matrix1->m_matrix4x4[6] - _matrix2->m_matrix4x4[6];
	NewMatrixAddition.m_matrix4x4[7] = _matrix1->m_matrix4x4[7] - _matrix2->m_matrix4x4[7];


	NewMatrixAddition.m_matrix4x4[8] = _matrix1->m_matrix4x4[8] - _matrix2->m_matrix4x4[8];
	NewMatrixAddition.m_matrix4x4[9] = _matrix1->m_matrix4x4[9] - _matrix2->m_matrix4x4[9];
	NewMatrixAddition.m_matrix4x4[10] = _matrix1->m_matrix4x4[10] - _matrix2->m_matrix4x4[10];
	NewMatrixAddition.m_matrix4x4[11] = _matrix1->m_matrix4x4[11] - _matrix2->m_matrix4x4[11];


	NewMatrixAddition.m_matrix4x4[12] = _matrix1->m_matrix4x4[12] - _matrix2->m_matrix4x4[12];
	NewMatrixAddition.m_matrix4x4[13] = _matrix1->m_matrix4x4[13] - _matrix2->m_matrix4x4[13];
	NewMatrixAddition.m_matrix4x4[14] = _matrix1->m_matrix4x4[14] - _matrix2->m_matrix4x4[14];
	NewMatrixAddition.m_matrix4x4[15] = _matrix1->m_matrix4x4[15] - _matrix2->m_matrix4x4[15];

	return NewMatrixAddition;
}

MY_Matrix Matrix4x4Transpose(MY_Matrix* _matrix1)
{
	MY_Matrix NewMatrixTranspose;

	//   0    1    2      3       //  0   4    8     12 
	//   4    5    6      7       //  1   5    9     13 
	//   8    9   10     11      //   2   6    10    14
	//   12  13   14     15      //   3   7    11    15

	NewMatrixTranspose.m_matrix4x4[0] = _matrix1->m_matrix4x4[0];
	NewMatrixTranspose.m_matrix4x4[1] = _matrix1->m_matrix4x4[4];
	NewMatrixTranspose.m_matrix4x4[2] = _matrix1->m_matrix4x4[8];
	NewMatrixTranspose.m_matrix4x4[3] = _matrix1->m_matrix4x4[12];

	NewMatrixTranspose.m_matrix4x4[4] = _matrix1->m_matrix4x4[1];
	NewMatrixTranspose.m_matrix4x4[5] = _matrix1->m_matrix4x4[5];
	NewMatrixTranspose.m_matrix4x4[6] = _matrix1->m_matrix4x4[9];
	NewMatrixTranspose.m_matrix4x4[7] = _matrix1->m_matrix4x4[13];

	NewMatrixTranspose.m_matrix4x4[8] = _matrix1->m_matrix4x4[2];
	NewMatrixTranspose.m_matrix4x4[9] = _matrix1->m_matrix4x4[6];
	NewMatrixTranspose.m_matrix4x4[10] = _matrix1->m_matrix4x4[10];
	NewMatrixTranspose.m_matrix4x4[11] = _matrix1->m_matrix4x4[14];


	NewMatrixTranspose.m_matrix4x4[12] = _matrix1->m_matrix4x4[3];
	NewMatrixTranspose.m_matrix4x4[13] = _matrix1->m_matrix4x4[7];
	NewMatrixTranspose.m_matrix4x4[14] = _matrix1->m_matrix4x4[11];
	NewMatrixTranspose.m_matrix4x4[15] = _matrix1->m_matrix4x4[15];



	return NewMatrixTranspose;



}

MY_Vertex Vector4_Multiplication_Matrix4x4(MY_Vertex* _vertex, MY_Matrix* _Matrix4x4)
{
	//   0    1    2      3                               //  0   1    2    3 
	//   4    5    6      7                              //  4   5    6    7 
	//   8    9   10     11                            //   8   9    10   11
	//   12  13   14     15                            //  12   13   14   15
	MY_Vertex NewConvertedVertex;

	NewConvertedVertex.m_xyz[0] = (_vertex->m_xyz[0] * _Matrix4x4->m_matrix4x4[0]) +
		(_vertex->m_xyz[1] * _Matrix4x4->m_matrix4x4[4]) +
		(_vertex->m_xyz[2] * _Matrix4x4->m_matrix4x4[8]) +
		(_vertex->m_xyz[3] * _Matrix4x4->m_matrix4x4[12]);

	NewConvertedVertex.m_xyz[1] = (_vertex->m_xyz[0] * _Matrix4x4->m_matrix4x4[1]) +
		(_vertex->m_xyz[1] * _Matrix4x4->m_matrix4x4[5]) +
		(_vertex->m_xyz[2] * _Matrix4x4->m_matrix4x4[9]) +
		(_vertex->m_xyz[3] * _Matrix4x4->m_matrix4x4[13]);

	NewConvertedVertex.m_xyz[2] = (_vertex->m_xyz[0] * _Matrix4x4->m_matrix4x4[2]) +
		(_vertex->m_xyz[1] * _Matrix4x4->m_matrix4x4[6]) +
		(_vertex->m_xyz[2] * _Matrix4x4->m_matrix4x4[10]) +
		(_vertex->m_xyz[3] * _Matrix4x4->m_matrix4x4[14]);

	NewConvertedVertex.m_xyz[3] = (_vertex->m_xyz[0] * _Matrix4x4->m_matrix4x4[3]) +
		(_vertex->m_xyz[1] * _Matrix4x4->m_matrix4x4[7]) +
		(_vertex->m_xyz[2] * _Matrix4x4->m_matrix4x4[11]) +
		(_vertex->m_xyz[3] * _Matrix4x4->m_matrix4x4[15]);


	return NewConvertedVertex;

}

MY_Matrix Matrix4x4_Roation_on_X_Axis(float _rad)
{
	MY_Matrix m_rotationOnXaxis;
	m_rotationOnXaxis.m_matrix4x4[0] = 1;
	m_rotationOnXaxis.m_matrix4x4[1] = 0;
	m_rotationOnXaxis.m_matrix4x4[2] = 0;
	m_rotationOnXaxis.m_matrix4x4[3] = 0;

	m_rotationOnXaxis.m_matrix4x4[4] = 0;
	m_rotationOnXaxis.m_matrix4x4[5] = cos(_rad);
	m_rotationOnXaxis.m_matrix4x4[6] = -sin(_rad);
	m_rotationOnXaxis.m_matrix4x4[7] = 0;

	m_rotationOnXaxis.m_matrix4x4[8] = 0;
	m_rotationOnXaxis.m_matrix4x4[9] = sin(_rad);
	m_rotationOnXaxis.m_matrix4x4[10] = cos(_rad);
	m_rotationOnXaxis.m_matrix4x4[11] = 0;

	m_rotationOnXaxis.m_matrix4x4[12] = 0;
	m_rotationOnXaxis.m_matrix4x4[13] = 0;
	m_rotationOnXaxis.m_matrix4x4[14] = 0;
	m_rotationOnXaxis.m_matrix4x4[15] = 1;


	return m_rotationOnXaxis;
}

MY_Matrix Matrix4x4_Roation_on_Y_Axis(float _rad)
{
	MY_Matrix m_rotationOnYaxis;

	m_rotationOnYaxis.m_matrix4x4[0] = cos(_rad);
	m_rotationOnYaxis.m_matrix4x4[1] = 0;
	m_rotationOnYaxis.m_matrix4x4[2] = sin(_rad);
	m_rotationOnYaxis.m_matrix4x4[3] = 0;

	m_rotationOnYaxis.m_matrix4x4[4] = 0;
	m_rotationOnYaxis.m_matrix4x4[5] = 1;
	m_rotationOnYaxis.m_matrix4x4[6] = 0;
	m_rotationOnYaxis.m_matrix4x4[7] = 0;

	m_rotationOnYaxis.m_matrix4x4[8] = -sin(_rad);
	m_rotationOnYaxis.m_matrix4x4[9] = 0;
	m_rotationOnYaxis.m_matrix4x4[10] = cos(_rad);
	m_rotationOnYaxis.m_matrix4x4[11] = 0;

	m_rotationOnYaxis.m_matrix4x4[12] = 0;
	m_rotationOnYaxis.m_matrix4x4[13] = 0;
	m_rotationOnYaxis.m_matrix4x4[14] = 0;
	m_rotationOnYaxis.m_matrix4x4[15] = 1;


	return m_rotationOnYaxis;


}

MY_Matrix Matrix4x4_Roation_on_Z_Axis(float _rad)
{
	MY_Matrix m_rotationOnZaxis;

	m_rotationOnZaxis.m_matrix4x4[0] = cos(_rad);
	m_rotationOnZaxis.m_matrix4x4[0] = -sin(_rad);
	m_rotationOnZaxis.m_matrix4x4[0] = 0;
	m_rotationOnZaxis.m_matrix4x4[0] = 0;

	m_rotationOnZaxis.m_matrix4x4[0] = sin(_rad);
	m_rotationOnZaxis.m_matrix4x4[0] = cos(_rad);
	m_rotationOnZaxis.m_matrix4x4[0] = 0;
	m_rotationOnZaxis.m_matrix4x4[0] = 0;


	m_rotationOnZaxis.m_matrix4x4[0] = 0;
	m_rotationOnZaxis.m_matrix4x4[0] = 0;
	m_rotationOnZaxis.m_matrix4x4[0] = 1;
	m_rotationOnZaxis.m_matrix4x4[0] = 0;


	m_rotationOnZaxis.m_matrix4x4[0] = 0;
	m_rotationOnZaxis.m_matrix4x4[0] = 0;
	m_rotationOnZaxis.m_matrix4x4[0] = 0;
	m_rotationOnZaxis.m_matrix4x4[0] = 1;


	return m_rotationOnZaxis;

}

MY_Matrix operator*(const MY_Matrix& _leftMatrix, const MY_Matrix& _rightMatrix)
{
	MY_Matrix m_result1;
	MY_Matrix m_result2;
	MY_Matrix m_result;
	m_result1 = _leftMatrix;
	m_result2 = _rightMatrix;
	if (m_result1.m_matrix4x4[0] > 0 && m_result2.m_matrix4x4[0] > 0)
	{
		m_result = Matrix4X4Multiplication(&m_result1, &m_result2);
	}
	if (m_result1.m_matrix3x3[0] > 0 && m_result2.m_matrix3x3[0] > 0)
	{
		m_result = Matrix3x3Multiplication(&m_result1, &m_result2);
	}


	return m_result;

}


MY_Vertex operator*(const MY_Vertex& _leftVertex, const MY_Matrix& _RightMatrix)
{
	MY_Vertex m_result1 = _leftVertex;
	MY_Matrix m_result2 = _RightMatrix;
	MY_Vertex m_result;
	if (m_result2.m_matrix3x3[0] > 0 && m_result2.m_matrix4x4[0] < 0 || m_result2.m_matrix3x3[0] < 0 && m_result2.m_matrix4x4[0] < 0)
	{
		m_result = Vector3_Multipliction_Matrix3x3(&m_result1, &m_result2);
	}
	else
	{
		m_result = Vector4_Multiplication_Matrix4x4(&m_result1, &m_result2);
	}









	return m_result;
}

MY_Matrix Translation(float* _xyz)
{

	MY_Matrix NewTranslate;

	NewTranslate.m_matrix4x4[0] = 1;
	NewTranslate.m_matrix4x4[1] = 0;
	NewTranslate.m_matrix4x4[2] = 0;
	NewTranslate.m_matrix4x4[3] = 0;

	NewTranslate.m_matrix4x4[4] = 0;
	NewTranslate.m_matrix4x4[5] = 1;
	NewTranslate.m_matrix4x4[6] = 0;
	NewTranslate.m_matrix4x4[7] = 0;


	NewTranslate.m_matrix4x4[8] = 0;
	NewTranslate.m_matrix4x4[9] = 0;
	NewTranslate.m_matrix4x4[10] = 1;
	NewTranslate.m_matrix4x4[11] = 0;

	NewTranslate.m_matrix4x4[12] = _xyz[0];
	NewTranslate.m_matrix4x4[13] = _xyz[1];
	NewTranslate.m_matrix4x4[14] = _xyz[2];
	NewTranslate.m_matrix4x4[15] = 1;



	return NewTranslate;




}


MY_Matrix TranslationZ()
{

	MY_Matrix NewTranslate;

	NewTranslate.m_matrix4x4[0] = 1;
	NewTranslate.m_matrix4x4[1] = 0;
	NewTranslate.m_matrix4x4[2] = 0;
	NewTranslate.m_matrix4x4[3] = 0;

	NewTranslate.m_matrix4x4[4] = 0;
	NewTranslate.m_matrix4x4[5] = 1;
	NewTranslate.m_matrix4x4[6] = 0;
	NewTranslate.m_matrix4x4[7] = 0;


	NewTranslate.m_matrix4x4[8] = 0;
	NewTranslate.m_matrix4x4[9] = 0;
	NewTranslate.m_matrix4x4[10] = 1;
	NewTranslate.m_matrix4x4[11] = 0;

	NewTranslate.m_matrix4x4[12] = 0;
	NewTranslate.m_matrix4x4[13] = 0;
	NewTranslate.m_matrix4x4[14] = -1;
	NewTranslate.m_matrix4x4[15] = 1;



	return NewTranslate;




}

MY_Matrix Matrix3x3Transpose(MY_Matrix* _matrix1)
{
	MY_Matrix NewMatrixTranspose;

	// 1 2 3   
	// 4 5 6   
	// 7 8 9   

	NewMatrixTranspose.m_matrix3x3[0] = _matrix1->m_matrix3x3[0];
	NewMatrixTranspose.m_matrix3x3[3] = _matrix1->m_matrix3x3[1];
	NewMatrixTranspose.m_matrix3x3[6] = _matrix1->m_matrix3x3[2];

	NewMatrixTranspose.m_matrix3x3[1] = _matrix1->m_matrix3x3[3];
	NewMatrixTranspose.m_matrix3x3[4] = _matrix1->m_matrix3x3[4];
	NewMatrixTranspose.m_matrix3x3[7] = _matrix1->m_matrix3x3[5];


	NewMatrixTranspose.m_matrix3x3[2] = _matrix1->m_matrix3x3[6];
	NewMatrixTranspose.m_matrix3x3[5] = _matrix1->m_matrix3x3[7];
	NewMatrixTranspose.m_matrix3x3[8] = _matrix1->m_matrix3x3[8];


	return NewMatrixTranspose;



}

MY_Matrix Inverse(MY_Matrix _matrix)
{
	//	MY_Matrix m_matrix3x3;
	MY_Vertex m_vertex;


	//float _xyz[3];
	//My_Vertex NewVertex;

	m_vertex.m_xyz[0] = _matrix.m_matrix4x4[12];
	m_vertex.m_xyz[1] = _matrix.m_matrix4x4[13];
	m_vertex.m_xyz[2] = _matrix.m_matrix4x4[14];
	m_vertex.m_xyz[3] = 1;

	_matrix.m_matrix4x4[12] = 0;
	_matrix.m_matrix4x4[13] = 0;
	_matrix.m_matrix4x4[14] = 0;
	_matrix.m_matrix4x4[15] = 1;


	_matrix = Matrix4x4Transpose(&_matrix);







	m_vertex = Vector4_Multiplication_Matrix4x4(&m_vertex, &_matrix);

	m_vertex.m_xyz[0] = m_vertex.m_xyz[0] * -1;
	m_vertex.m_xyz[1] = m_vertex.m_xyz[1] * -1;
	m_vertex.m_xyz[2] = m_vertex.m_xyz[2] * -1;


	_matrix.m_matrix4x4[12] = m_vertex.m_xyz[0];
	_matrix.m_matrix4x4[13] = m_vertex.m_xyz[1];
	_matrix.m_matrix4x4[14] = m_vertex.m_xyz[2];
	_matrix.m_matrix4x4[15] = 1;

	return _matrix;
}

MY_Matrix  PrespectiveProjection(float Xscale, float Yscale, float ZNear, float zfar)
{
	MY_Matrix NewPrespective;

	NewPrespective.m_matrix4x4[0] = Xscale;
	NewPrespective.m_matrix4x4[1] = 0;
	NewPrespective.m_matrix4x4[2] = 0;
	NewPrespective.m_matrix4x4[3] = 0;



	NewPrespective.m_matrix4x4[4] = 0;
	NewPrespective.m_matrix4x4[5] = Yscale;
	NewPrespective.m_matrix4x4[6] = 0;
	NewPrespective.m_matrix4x4[7] = 0;




	NewPrespective.m_matrix4x4[8] = 0;
	NewPrespective.m_matrix4x4[9] = 0;
	NewPrespective.m_matrix4x4[10] = (zfar / (zfar - ZNear));
	NewPrespective.m_matrix4x4[11] = -1;


	NewPrespective.m_matrix4x4[12] = 0;
	NewPrespective.m_matrix4x4[13] = 0;
	NewPrespective.m_matrix4x4[14] = -(zfar * ZNear) / (zfar - ZNear);
	NewPrespective.m_matrix4x4[15] = 0;


	return NewPrespective;
}

