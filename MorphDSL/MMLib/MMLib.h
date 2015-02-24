#pragma once
#include <vector>
#include <math.h>
#include <algorithm>
#include "FQDT.h"
#include "max_tree.h"
#include "bestfit.h"
#include <queue>
using namespace std;


#define EPSILON			0.000001
#define PI				3.1415926535897932384626433832795f
#define SPEEDOFLIGHT	300000000
#define PICO_SECOND		1.0e-12

#define DEG2RAD(degree) ((PI / 180.0f) * (degree))   //!< Makro, ki pretvori stopinje v radiane.
#define RAD2DEG(radian) ((180.0f / PI) * (radian))  //!< Makro, ki pretvori radiane v stopinje.

#define MAX(a, b) (a >= b ? a : b)
#define MIN(a, b) (a < b ? a : b)

#define SIGN(num) (num > 0 ? 1 : (num < 0 ? -1 : 0))

#define VAL2RGB(valR, valG, valB) RGB(valR * 255, valG *255, valB * 255)
#define SPEED_DISTANCE(time) (SPEEDOFLIGHT * time)

typedef long long int int64;

//Structs
struct Vector2f
{
	float x, y;
	///Konstruktorji
	Vector2f()
	{	
		x = y = 0.0f;
	}
	Vector2f(float x, float y)
	{	
		this->x = x;	this->y = y;
	}
	
	//Operatorji
	//Prirejanje vectorja
	void operator = (const Vector2f &v)
	{
		x = v.x; y = v.y;
	}
	bool operator == (const Vector2f &v)
	{
		return ((x == v.x) && (y == v.y));
	}
	//Negacija vectorja
	Vector2f operator - ()
	{
		return Vector2f(-x, -y);
	}
	//Operacije s skalarjem
	Vector2f operator + (float f) const
	{
		return Vector2f(x + f, y + f);
	}
	Vector2f operator - (float f) const
	{
		return Vector2f(x - f, y - f);
	}
	Vector2f operator * (float f) const
	{
		return Vector2f(x * f, y * f);
	}
	Vector2f operator / (float f) const
	{
		return Vector2f(x / f, y / f);
	}
	void operator += (float f)
	{
		x += f;	y += f;
	}
	void operator -= (float f)
	{
		x -= f;	y -= f;
	}
	void operator *= (float f)
	{
		x *= f;	y *= f;
	}
	void operator /= (float f)
	{
		x /= f;	y /= f;
	}
	//Operacije s vektorjem
	Vector2f operator + (const Vector2f &v) const
	{
		return Vector2f(x + v.x, y + v.y);
	}
	Vector2f operator - (const Vector2f &v) const
	{
		return Vector2f(x - v.x, y - v.y);
	}
	void operator += (const Vector2f &v)
	{
		x += v.x;	y += v.y;
	}
	void operator -= (const Vector2f &v)
	{
		x -= v.x;	y -= v.y;
	}
	//Skalarni produkt
	float operator * (const Vector2f &v) const
	{
		return (x * v.x + y * v.y);
	}
	////Vektorski produkt
	//inline Vector2f Cross(const Vector2f &V) const
	//{
	//	return Vector2f(
	//		Y*V.x - x*V.Y,
	//		Z*V.x - x*V.Z);
	//}
	//inline void Cross(const Vector2f &V1, const Vector2f &V2)
	//{
	//	x = V1.Y*V2.Z - V1.Z*V2.Y;
	//	Y =	V1.Z*V2.x - V1.x*V2.Z;
	//}
	//friend inline Vector2f CrossProd(const Vector2f &V1, const Vector2f &V2)
	//{
	//	return Vector3f(
	//		V1.Y*V2.Z - V1.Z*V2.Y,
	//		V1.Z*V2.x - V1.X*V2.Z,
	//		V1.X*V2.Y - V1.Y*V2.x);
	//}
	//Metode
	inline float Lenght() const
	{
		return sqrtf(x*x + y*y);
	}
	friend inline float Lenght(Vector2f &v)
	{
		return sqrtf(v.x*v.x + v.y*v.y);
	}
	inline void Normalize()
	{
		float length = this->Lenght();
		if (length != 0.0f)
		{
			x /= length;	y /= length;
		}
		else
		{
			x = 0.0f;	y = 0.0f;
		}
	}
	friend inline void Normalize(Vector2f &v)
	{
		float length = v.Lenght();
		if (length != 0.0f)
		{
			v.x /= length;	v.y /= length;
		}
		else
		{
			v.x = 0.0f;	v.y = 0.0f;
		}
	}
	float* Get()
	{
		return &x;
	}
};

struct Vector3f
{
	float x, y, z;
	///Konstruktorji
	Vector3f()
	{	
		x = y = z = 0.0f;
	}
	Vector3f(float x, float y, float z)
	{	
		this->x = x;	this->y = y;	this->z = z;
	}
	Vector3f(const Vector3f& v)
	{	
		x = v.x;	y = v.y;	z = v.z;
	}	
	//Operatorji
	//Prirejanje vectorja
	void operator = (const Vector3f &v)
	{
		x = v.x; y = v.y; z = v.z;
	}
	bool operator == (const Vector3f &v)
	{
		return ((x == v.x) && (y == v.y) && (z == v.z));
	}
	bool operator != (const Vector3f &v)
	{
		return ((x != v.x) && (y != v.y) && (z != v.z));
	}
	//Negacija vectorja
	Vector3f operator - ()
	{
		return Vector3f(-x, -y, -z);
	}
	//Operacije s skalarjem
	Vector3f operator + (float f) const
	{
		return Vector3f(x + f, y + f, z + f);
	}
	Vector3f operator - (float f) const
	{
		return Vector3f(x - f, y - f, z - f);
	}
	Vector3f operator * (float f) const
	{
		return Vector3f(x * f, y * f, z * f);
	}
	Vector3f operator / (float f) const
	{
		return Vector3f(x / f, y / f, z / f);
	}
	void operator += (float f)
	{
		x += f;	y += f;	z += f;
	}
	void operator -= (float f)
	{
		x -= f;	y -= f;	z -= f;
	}
	void operator *= (float f)
	{
		x *= f;	y *= f;	z *= f;
	}
	void operator /= (float f)
	{
		x /= f;	y /= f;	z /= f;
	}
	//Operacije s vektorjem
	Vector3f operator + (const Vector3f &v) const
	{
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}
	Vector3f operator - (const Vector3f &v) const
	{
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}
	void operator += (const Vector3f &v)
	{
		x += v.x;	y += v.y;	z += v.z;
	}
	void operator -= (const Vector3f &v)
	{
		x -= v.x;	y -= v.y;	z -= v.z;
	}
	void operator *= (const Vector3f &v)
	{
		x *= v.x;	y *= v.y;	z *= v.z;
	}
	void operator /= (const Vector3f &v)
	{
		x /= v.x;	y /= v.y;	z /= v.z;
	}
	//Skalarni produkt
	inline float Dot(const Vector3f &v) const
	{
		return (x * v.x + y * v.y + z * v.z);
	}
	friend inline float DotProd(const Vector3f &V1, const Vector3f &V2)
	{
		return (V2.x * V1.x + V2.y * V1.y + V2.z * V1.z);
	}
	//Vektorski produkt
	inline Vector3f Cross(const Vector3f &V) const
	{
		return Vector3f(
			y*V.z - z*V.y,
			z*V.x - x*V.z,
			x*V.y - y*V.x);
	}
	friend inline Vector3f CrossProd(const Vector3f &V1, const Vector3f &V2)
	{
		return Vector3f(
			V1.y*V2.z - V1.z*V2.y,
			V1.z*V2.x - V1.x*V2.z,
			V1.x*V2.y - V1.y*V2.x);
	}
	//Operacije
	bool operator % (const Vector3f &v)
	{		
		return ((SIGN(x) == SIGN(v.x)) && (SIGN(y) == SIGN(v.y)) && (SIGN(z) == SIGN(v.z)));
	}
	//Metode
	inline float Length() const
	{
		return sqrtf(x*x + y*y + z*z);
	}
	friend inline float Lenght(Vector3f &v)
	{
		return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
	}
	inline void Normalize()
	{
		float length = this->Length();
		if (length != 0.0f)
		{
			x /= length;	y /= length;	z /= length;
		}
		else
		{
			x = 0.0f;	y = 0.0f;	z = 0.0f;
		}
	}
	friend inline void Normalize(Vector3f &v)
	{
		float length = v.Length();
		if (length != 0.0f)
		{
			v.x /= length;	v.y /= length;	v.z /= length;
		}
		else
		{
			v.x = 0.0f;	v.y = 0.0f;	v.z = 0.0f;
		}
	}
	inline Vector3f RotateZ(double Gama)
	{
		double dx = cos(Gama) * (double)x - sin(Gama) * (double)y;
		double dy = sin(Gama) * (double)x + cos(Gama) * (double)y ;
		return Vector3f((float)dx, (float)dy, z);
	}
	float* Pointer()
	{
		return &x;
	}
	inline Vector3f AnglesXYZ()
	{
		float len = this->Length();
		Vector3f Angles = Vector3f();
		Angles.x = this->x / len;
		Angles.y = this->y / len;
		Angles.z = this->z / len;
		return Angles;
	}
};

class PixelEl
{
public:
	int x;
	int y;
	double val;
};

/*START: Global functions*/
bool mySortVectorL2S(Vector3f i, Vector3f j);
void InitData(vector<vector<int>>& data,int initVal=0);
void InitData(vector<vector<double>>& data,double initVal=0.0);
void AbsData(vector<vector<double>>& data);
void LowHighLimit(vector<vector<double>>& data, double lLim, double hLim);
void NormalizeData(vector<vector<double>>& data, double lLim, double hLim);
void CropData(vector<vector<double>>& data, double lLim, double hLim);
void CropData(vector<vector<int>>& data, int lLim, int hLim);
void BComplementData(vector<vector<int>>& data);
void ComplementData(vector<vector<int>>& data);
void ComplementData(vector<vector<double>>& data);
void InvertData(vector<vector<double>>& data);
void CondenseData(vector<vector<int>>& data, int maxVal);
void SelectMax(vector<vector<double>>& io_data,vector<vector<double>>& c_data);
void SelectMax(vector<vector<int>>& io_data, vector<vector<int>>& c_data);
void Union(vector<vector<int>>& img1, vector<vector<int>>& img2);
void Union(vector<vector<int>>& img1, vector<vector<int>>& img2, vector<vector<int>>& output);
void Intersection(vector<vector<int>>& img1, vector<vector<int>>& img2, vector<vector<int>>& output);
void AddData(vector<vector<double>>& img1, double val);
void AddData(vector<vector<int>>& img1, int val);
void AddData(vector<vector<double>>& img1, vector<vector<double>>& img2);
void AddData(vector<vector<int>>& img1, vector<vector<int>>& img2);
void AddData(vector<vector<double>>& img1, vector<vector<double>>& img2, vector<vector<double>>& result);
void AddData(vector<double>& vect1, vector<double>& vect2);
void AddData(vector<double>& vect1, vector<double>& vect2, vector<double>& result);
void SubtractData(vector<vector<int>>& img, int val);
void SubtractData(vector<vector<double>>& img, double val);
void SubtractData(vector<vector<int>>& img1, vector<vector<int>>& img2);
void SubtractData(vector<vector<double>>& img1, vector<vector<double>>& img2);
void SubtractData(vector<vector<double>>& img1, vector<vector<double>>& img2, vector<vector<double>>& result);
void MultiplyData(vector<vector<double>>& data, double factor);
void MultiplyData(vector<vector<double>>& data1, vector<vector<double>>& data2);
void MultiplyData(vector<vector<double>>& data1, vector<vector<int>>& data2);
void MultiplyData(vector<vector<int>>& data, int factor);
void DrawDisk(vector<vector<int>>& data, int x, int y, int polmer, int color);
void CopyDataToData(vector<vector<int>>& in_data,vector<vector<double>>& out_data);
void CopyDataToData(vector<vector<double>>& in_data,vector<vector<int>>& out_data);
void CopyVectorToData(vector<vector<Vector3f>>& in_data,vector<vector<double>>& out_data);
void CopyDataToVector(vector<vector<double>>& in_data,vector<vector<Vector3f>>& out_data);
void CreateLevelImg(vector<vector<double>>& data, vector<vector<double>>& level_img, int noLevels);
void GetNormalImage(vector<vector<Vector3f>>& grid, vector<vector<double>>& nImg, int winSize=1);
void GetNormalStack(vector<vector<Vector3f>>& grid, vector<vector<vector<Vector3f>>>& nImg);
void GetSlopeAngles(vector<vector<double>>& slope, vector<vector<double>>& aspect, double resolution);
double VectorEDistance(vector<double>& vect_a,vector<double>& vect_b);
void VectorNormalize(vector<double>& vect);
void MatrixNormalize(vector<vector<double>>& data);
void SetUnion(vector<vector<int>>& io_data,vector<vector<int>>& data);
void SetIntersection(vector<vector<int>>& io_data,vector<vector<int>>& data);
void SetWithout(vector<vector<int>>& io_data,vector<vector<int>>& data);

	/*Output/debug functions*/
void OutputValue(int val, const char* title=NULL);
void OutputValue(double val, const char* title=NULL);
void OutputVector(vector<int> vals, const char* title=NULL);
void OutputVector(vector<PixelEl> vals, const char* title=NULL, int lIndex=0, int hIndex=30);
void OutputVector(vector<double> vals, const char* title=NULL, int maxElem=-1);
void OutputValVec(vector<double> vals, const char* title=NULL);
void OutputValVec(int val, vector<int> vals, const char* title=NULL);
void OutputValVec(double val, vector<double> vals, const char* title=NULL);
void OutputMatrix(vector<vector<double>>& vals, const char* title=NULL, int minX=-1,int minY=-1, int maxX=-1,int maxY=-1);
void OutputMatrix(vector<vector<int>>& vals, const char* title=NULL, int minX=-1,int minY=-1, int maxX=-1,int maxY=-1);
/*END: Global functions*/

struct CPOINT
{
	int x;
	int y;
};

class CBBox
{
public:
	CPOINT min;
	CPOINT max;

	CBBox()
	{
		min.x=-1;
		min.y=-1;
		max.x=-1;
		max.y=-1;
	}
	CBBox(int minX, int minY, int maxX, int maxY)
	{
		min.x=minX;
		min.y=minY;
		max.x=maxX;
		max.y=maxY;
	}
};
class CGraphElement
{
public:
	POINT minPoint;
	vector<int> neighbours;
	vector<int> tBoundary;
	vector<double> edgeMinStrength;
	vector<double> edgeMaxStrength;
	
	/*Stat data*/
	double minEdgeVal;
	int noRegPoints;
	CGraphElement()
	{
		noRegPoints=0;
		minPoint.x=-1;
		minPoint.y=-1;
		minEdgeVal=0.0;
	}
};

class CStatElement
{
public:
	
	double dVal;
	int iVal;
	int noElements;
	
	vector<int> neighbours;
	vector<int> biValue;
	vector<double> bdValue;
	
	POINT minPnt;
	CStatElement()
	{
		neighbours.reserve(10);
		biValue.reserve(10);
		bdValue.reserve(10);
		
		dVal=0.0;
		iVal=0;
		noElements=0;

		minPnt.x=-1;
		minPnt.y=-1;
	}
};

class MMLibB2D
{
private:
	//Data

	//Functions
	void Clean();

	void StoreDataToOrgData();
	void StoreDataToTmpData();
	void StoreOrgDataToData();
	void StoreTmpDataToData();

	/*START: Fast erosion functions*/
	void FastErode3();
	void FastErodeC3();

	void FastDilate3();
	void FastDilateC3();
public:
	
	vector<vector<int>> data;
	vector<vector<int>> orgData;
	vector<vector<int>> tmpData;

	vector<vector<int>> bW;
	vector<vector<double>> gW;

	
	MMLibB2D(void);
	~MMLibB2D(void);

	//Functions
	void Init();
	void SEBoxBinary(int size);
	
	//Basic MM Operators
	void bDilate();
	void bErode();
	void bOpen();
	void bClose();

	//Speed-up basic MM operators
	void FastErode(int wSize);
	void FastErodeCross(int wSize);
	void FastErodeOct(int wSize);
	void FastDilate(int wSize);
	void FastDilateCross(int wSize);
	void FastDilateOct(int wSize);

	void FastOpen(int wSize);
	void FastClose(int wSize);
	void FastOpenCross(int wSize);
	void FastCloseCross(int wSize);
	void FastOpenOct(int wSize);
	void FastCloseOct(int wSize);

	//Connected operators
	void AreaOpening(int aTh);
	void AreaClosing(int aTh);
	void ShapeSizeOpening(double shapeTh, double sizeTh);
	void AttributeOpening(vector<vector<double>> &attributeImg, double aTh);
	void AttributeOpening(vector<vector<int>> &attributeImg, int aTh);
	void AvgAttributeOpening(vector<vector<double>> &attributeImg, double aTh);
	

	//Algorithms
	int bHitMiss(int x, int y, vector<vector<int>> &W);
	void bThining();
	/*Distance Transformation */
	void DetectInternalEdge();
	void DetectExternalEdge();
	void bDT(vector<vector<int>> &dMap);

	void AreaOpening(vector<vector<int>> &bin_img, int th);
	void CompactnessOpening(double th);
	void DispersionOpening(vector<vector<int>> &bin_img, double th);
	void SphericityOpening(vector<vector<int>> &bin_img, double th);
	void CountNumHoles(vector<vector<int>> &bin_img, int th);
};

class MMLibG2D
{
private:
	//Data
	vector<POINT> candidates;
	vector<vector<int>> tmpMap;
	//Functions
	void Clean();

	//Help functions
	void StoreDataToOrgData();
	void StoreDataToTmpData();
	void StoreOrgDataToData();
	void StoreTmpDataToData();
public:
	int FindElement(vector<int>& values, int element);
	void SwapElements(vector<int>& values, int i, int j=-1);
	void SwapElements(vector<double>& values, int i, int j=-1);
	void GetRegionalMaxima(vector<vector<int>>& maxMap);
private:
	//Support Fuctions
	void _Watershed(vector<vector<int>>& gradDirection, vector<vector<int>>& output);
	int _Watershed(vector<vector<int>>& gradDirection, vector<vector<int>>& output, int x, int y);
	void GetInnerOuterLists(int x, int y, vector<POINT> &innerPoints, vector<POINT> & outerPoints, vector<vector<int>>& gMap, vector<vector<int>> &pMap);
	void DilatePoints(vector<POINT> & outerPoints, vector<vector<int>>& gMap, vector<vector<int>> &pMap);
	int GetMinValDirection(int x, int y, double& val);
	int GetMinValDirection(int x, int y, double& val, int& pVal);
	POINT GetRegionNeighbour(vector<vector<int>>& wsRegions,int x, int y);

	/*START: Fast erosion functions*/
	void FastErode3();
	void FastErodeC3();

	void FastDilate3();
	void FastDilateC3();
	
	
public:
	
	vector<vector<double>> data;
	vector<vector<double>> orgData;
	vector<vector<double>> tmpData;

	vector<vector<int>> bW;
	vector<vector<double>> gW;

	
	MMLibG2D(void);
	~MMLibG2D(void);

	//Functions
	void Init();
	void SEDiscBinary(int size);
	void SEBoxBinary(int size);
	//Basic MM Operators
	void bDilate();
	void bErode();

	void FastErode(int wSize);
	void FastErodeCross(int wSize);
	void FastErodeOct(int wSize);
	void FastDilate(int wSize);
	void FastDilateCross(int wSize);
	void FastDilateOct(int wSize);

	void bOpen();
	void bClose();
	void FastOpen(int wSize);
	void FastClose(int wSize);
	void FastLevelingOpen(int wSize);
	void FastLevelingClose(int wSize);
	void FastOpenCross(int wSize);
	void FastCloseCross(int wSize);
	void FastOpenOct(int wSize);
	void FastCloseOct(int wSize);

	//MM operators
	void WTopHat();
	void BTopHat();

	//Edge detection
	void BlurMinimumEdge();

	//Advance MM
	void UltimateOpening(vector<vector<double>>& rData,vector<vector<int>>& sData, int maxSize=10);
	void ErosionOnQDT(vector<vector<int>>& dMap);
	void ErosionOnQDT(vector<vector<int>>& dMap, vector<vector<int>>& controlMap);
	void ReconstructionByDilation(vector<vector<double>>& mask);
	void OpeningByReconstruction(int wSize);
	void OpeningByContrastReconstruction(double val);
	void ClosingByContrastReconstruction(double val);
	void ClosingByReconstruction(int wSize);
	int Watershed(vector<vector<int>>& output);
	int WatershedOnMarkers(vector<vector<int>>& markerImg, vector<vector<int>>& output);
	void ErosionProfiles(vector<vector<double>>& f_line, vector<vector<int>>& f_dot, vector<int> wVec);
	void FastDMP(vector<vector<double>>& f_line, vector<vector<int>>& f_dot, vector<int> wVec);
	void FastDMP(vector<vector<vector<double>>>& f_stack, vector<int> wVec);
	void FastDMP(vector<vector<vector<double>>>& f_stack, vector<vector<double>>& r_img, vector<int> wVec);
	void FastDMP_Oct(vector<vector<double>>& f_line, vector<vector<int>>& f_dot, vector<int> wVec);
	void FastDMP_Oct(vector<vector<vector<double>>>& f_stack, vector<int> wVec);
	void FastDMP_Oct(vector<vector<vector<double>>>& f_stack, vector<vector<double>>& r_img, vector<int> wVec);
	void FastSMRF_Oct(vector<vector<vector<double>>>& f_stack, vector<int> wVec);
	void DMP(vector<vector<double>>& f_line, vector<vector<int>>& f_dot, vector<int> wVec, bool ignoreFirst=false);
	void DMP(vector<vector<vector<double>>>& f_stack, vector<int> wVec, bool ignoreFirst=false);
	void DMP(vector<vector<double>>& f_line, vector<vector<int>>& f_dot, vector<vector<double>>& f_level, vector<int> wVec, bool ignoreFirst=false);
	void DMPOnReconstruction(vector<vector<double>>& f_line, vector<vector<int>>& f_dot, vector<int> wVec);
	void MSLSSegmentation(vector<vector<double>>& f_line, vector<vector<double>>& f_dot, vector<vector<double>>& f_class, vector<int> wVec);
	void MSLSSegmentation(vector<vector<double>>& f_line, vector<vector<double>>& f_dot, vector<vector<double>>& f_class, vector<vector<double>>& f_level, vector<int> wVec);
	void MSLSSegmentationDAP(vector<vector<double>>& f_line, vector<vector<double>>& f_dot, vector<vector<double>>& f_class, vector<double> lambda);
	void MSLSSegmentationDAP(vector<vector<double>>& f_line, vector<vector<double>>& f_dot, vector<vector<double>>& f_class, vector<vector<double>>& f_level, vector<double> lambda);
};
class MMLibG3D
{
private:
	vector<vector<vector<double>>> tmpData;
public:
	vector<vector<vector<double>>> data;
	
	void Init();
	void FastErode3();
	void FastDilate3();
};
//Konvolucija
class Convolution
{
private:
	void Clean();
	void StoreDataToTmpData();
	void StoreTmpDataToData();

public:
	vector<vector<double>> data;
	vector<vector<vector<double>>> dataStack;
	vector<vector<double>> tmpData;

	vector<vector<double>> K;

	Convolution();
	~Convolution();

	void Init();
	void Convolve();

	//Special Functions
	void ConvolveGaborRotSeries(int polmer, double waveLength, int noAngles, double phase=0.0, double gEnvelope=-1.0, double elipsity=1.0);
	void ConvolveGaborScaleSeries(int polmer, int minWL,int maxWL, int noAngles, double phase=0.0, double gEnvelope=-1.0, double elipsity=1.0);
	void FastAverage(int winSize=1);
	//Help Functions
	void ExpandForConvolution();
	void CollapseForConvolution();

	//Kernel functions
	void KAverage(int polmer);
	void KGauss(int polmer, double std=1.0);
	void KLoG(int polmer, double std=1.0);
	void GaborWave(int polmer, double waveLength, double angle, double phase=0.0, double gEnvelope=-1.0, double elipsity=1.0);
};

//Edge detection filters
class EdgeDetection
{
private:
	int GetMinValDirection(int x, int y, vector<vector<double>>& data,double& val);
public:

	EdgeDetection(void);
	~EdgeDetection(void);

	void Sobel(vector<vector<double>> &data);
	void Laplace(vector<vector<double>> &data, double tVal=25.0);
	void BlurMinimum(vector<vector<double>> &data);
	void Compass(vector<vector<double>> &data, vector<vector<int>> &gradDirection, double tVal=10.0);
	void MorphologicalGradient(vector<vector<double>> &data, vector<vector<int>> &gradDirection);
	void MorphologicalGradient(vector<vector<double>> &data);
	void InternalMGradient(vector<vector<double>> &data);
	void ExternalMGradient(vector<vector<double>> &data);
	void MGradient(vector<vector<double>> &data);
	void LoGEdges(vector<vector<double>> &data);
	void MeanSquareDifff(vector<vector<double>> &data);
	void BlobDetection(vector<vector<double>> data, vector<vector<int>>& regions, int noLevels=10);
	
	//testing
	void LinearRegression(vector<vector<Vector3f>> &grid, vector<vector<double>> &data, int winSize=1);
	void ImageEnhancement(vector<vector<double>> &data, int winSize=1);
	void ImageCompassEnhancement(vector<vector<double>> &data, int winSize=1);
	void HighPassFilter(vector<vector<double>> &data, int winSize=1);
	void _BFPGetPntListTop(int& noPnts, double* pnts, vector<vector<Vector3f>>& grid, int x, int y, int winSize=1);
	void _BFPGetPntListBot(int& noPnts, double* pnts, vector<vector<Vector3f>>& grid, int x, int y, int winSize=1);
	double _BFPErrorEstimation(int noPnts, double* pnts);
	double _BFPErrorEstimation(int noPnts, double* pnts, double* plane);
	double _BFPErrorEstimation(vector<vector<Vector3f>>& grid, int x, int y, vector<double>& plane, int winSize);
	void BFPlanes(vector<vector<Vector3f>>& grid, vector<vector<vector<double>>>& data, vector<vector<double>>& errorData, int winSize=1);
	void BFPFiltering8(vector<vector<Vector3f>>& grid, vector<vector<double>>& data, int winSize=1);
	void BFPFiltering4(vector<vector<Vector3f>>& grid, vector<vector<double>>& data, int winSize=1);
	void BFPFiltering4(vector<vector<Vector3f>>& grid, vector<vector<vector<double>>>& fStack, int winSize=1);
	void BFPFiltering4(vector<vector<Vector3f>>& grid, vector<vector<double>>& data, vector<vector<int>>& oImg, int winSize=1);
	void MyPlaneDetection(vector<vector<Vector3f>>& grid, vector<vector<double>>& data);
};

//Thresholds
class CThresholding
{
public:
	CThresholding(){}

	void CostantThreshold(vector<vector<double>> &data, vector<vector<int>> &regions, double tVal=1.0);
	void CostantThreshold(vector<vector<int>> &data, vector<vector<int>> &regions, double tVal=1.0);
	void CostantBandPassThreshold(vector<vector<double>> &data, vector<vector<int>> &regions, double tLow=0.0, double tHigh=1.0);
	void CostantThresholdBackground(vector<vector<double>> &data, vector<vector<int>> &regions, double tVal=1.0);
	void CostantThresholdBackground(vector<vector<double>> &data, double tVal=1.0);
	void AdaptiveThreshold(vector<vector<double>> &data, vector<vector<int>> &regions, double addVal=1.0, int winSize=5);
	void AutomaticDMThreshold(vector<vector<double>> &data, vector<vector<int>> &regions, double devFactor=3.0, double addVal=0.0);
	void AdaptiveAutomaticDMThreshold(vector<vector<double>> &data, vector<vector<int>> &regions, int winSize);
	void AlphaTrimmedMean(vector<vector<double>> &data, int winSize, int noTrimmedValues, vector<vector<double>> &output);
};
//Flood Filling
class CFloodFill
{
private:
	vector<POINT> candidates;

	void _ChangeRegionIndex(vector<vector<int>> &inData,vector<vector<int>> &outData, POINT sPoint, int newIndex);
	bool _FFLimitedOnBB(vector<vector<int>> &output, POINT sPoint, int regIndex, vector<vector<int>> &borderMap, CBBox bbox);
	int _FindElement(vector<int>& values, int element);

public:
	CFloodFill();

	//My Functions
	/*Bobarvamo vse znotraj omejujoèih pikslov, podanih s restrictionRegion*/
	void Flood(vector<vector<int>> &data, POINT sPoint, int regIndex, int restrictionRegion);
	void Flood2(vector<vector<int>> &data, vector<vector<int>> &data_out, POINT sPoint, int regIndex_out, int regIndex, int restrictionRegion);
	/*Izloèimo regije, ki nimajo elementov*/
	int CondenseRegions(vector<vector<int>> &data);
	/*Zamenjamo indeks regije s toèko sPoint v newIndex*/
	void ChangeRegionIndex(vector<vector<int>> &data, int x, int y, int newIndex);
	void ChangeRegionIndex(vector<vector<int>> &data, POINT sPoint, int newIndex);
	/*Zamenjamo indeks regije s toèko sPoint v newIndex (8 sosešèina)*/
	void ChangeRegionIndex8(vector<vector<int>> &data, POINT sPoint, int newIndex);
	/*Pobarva bele regije, ki so oznaèene z 1 in loèene z 0*/
	int WRegionColoring(vector<vector<int>> &input);
	int RegionColoring(vector<vector<int>> &input);
	/*Pobarva èrne prazne prostore oznaèene z 0 in loèene z 1*/
	int BRegionColoring(vector<vector<int>> &input);
	/*Pobarvam samo zaprte regije (0-prazna regija, 1-rob)*/
	int CloseRegionsColoring(vector<vector<int>> &input);
	/*Flood fill na grey scale value - zaèetna toèka ki doloèa GS vrednost*/
	void GSFloodFill(vector<vector<double>> &data, POINT sPoint, vector<vector<int>> &output, int regIndex=1);
	/*GS Flood fill na grey scale value - tVal doloèa najveèjo razliko s sosednjim pikslom, da zadevo še pridružimo*/
	void GSRegionGrowing(vector<vector<double>> &data, POINT sPoint, vector<vector<int>> &output, int regIndex=1, double tVal=0.1);
	/*GS sliko segmentiramo v regije toèk, ki imajo najveè tVal razliko do sosedov*/
	int SegmentOnRegionGrowing(vector<vector<double>> &data, vector<vector<int>> &output, double tVal=0.1);
	/*Flood fill na grey scale (vse manjše od tVal skupaj) value - zaèetna toèka ki doloèa GS vrednost*/
	void GSFloodFill(vector<vector<double>> &data, POINT sPoint, vector<vector<int>> &output, int regIndex, double tVal);
	/*Odstrani bele regije, ki imajo manj kot tVal elementov*/
	void RemoveSmallWRegions(vector<vector<int>> &input, int tVal);
	/*Odstrani bele regije, ki imajo veè kot tVal elementov*/
	void RemoveLargeWRegions(vector<vector<int>> &input, int tVal);
};

//Region growing algorithms
class CRegionGrowing{
private:
	void GetInOutNeighbours(int x, int y, vector<POINT>& inNeighbours, vector<POINT>& outNeighbours, vector<vector<int>> &rImg);
	void GetBoundary(vector<vector<int>> &rImg, queue<POINT>& Q);
	bool GetPlaneFromPoints(vector<vector<Vector3f>>& grid, vector<POINT>& pnts, double* plane);
public:
	void GrowRegionOnBFPlanes(vector<vector<Vector3f>> &grid, vector<vector<int>> &rImg, double growTh);
};

//Calc Statistical data
class CDataStatistics{
private:
	vector<int> N;

	/*HELP Functios*/
	void _GetBFP(int noPnts, double* pnts, double* plane);

public:
	
	CDataStatistics(){}
	double GetMinVal(vector<double>& values);
	double GetMinVal(vector<vector<double>>& values);
	double GetMaxVal(vector<double>& values);
	double GetMaxVal(vector<vector<double>>& values);
	void GetMinMaxVal(vector<int>& values, int& minVal, int& maxVal);
	void GetMinMaxVal(vector<double>& values, double& minVal, double& maxVal);
	void GetMinMaxVal(vector<vector<int>>& values, int& minVal, int& maxVal);
	void GetMinMaxVal(vector<vector<double>>& values, double& minVal, double& maxVal);

	double GetAvgVal(vector<double>& values);
	double GetAvgVal(vector<vector<double>>& values);
	void GetAvgVal(vector<vector<double>>& values, vector<vector<int>>& regs, vector<double>& avg);

	void GetAvgStdVal(vector<double>& values, double& avg, double& std);
	void GetAvgStdVal(vector<vector<double>>& values, double& avg, double& std);
	void GetAvgStdVal(vector<vector<double>>& values, vector<vector<int>>& regs, vector<double>& avg, vector<double>& std);

	void GetSkewnessKurtosis(vector<double>& values, double& avg, double& std, double& sk, double& ku);

	/*START: Help functions*/
	void GetHistogram(vector<double>& hGram, vector<vector<double>>& data, vector<vector<int>>& classData, int testClass, double minVal, double maxVal, int noSteps);
	void GetHistomatrix(vector<vector<double>>& hMat, vector<vector<double>>& dataX, vector<vector<double>>& dataY, vector<vector<int>>& classData, int testClass, Vector2f minVal, Vector2f maxVal, POINT noSteps);
	/*END: Help functions*/

	void PearsonsCorrelation(vector<vector<double>>& data_x, vector<vector<double>>& data_y, vector<vector<int>>& classData, int testClass=1);
	void LinearRegresion1D(vector<Vector2f>& data, double &a, double &b);
	void LinearRegresion1D(vector<Vector2f>& data, double &a, double &b, double &avgError, double &stdError);
	void LinearRegresion1D(vector<vector<double>>& dataX, vector<vector<double>>& dataY, vector<vector<int>>& classData, int testClass, double &a, double &b);
	void LinearRegresion1D(vector<vector<double>>& dataX, vector<vector<double>>& dataY, vector<vector<int>>& classData, int testClass, double &a, double &b, double &avgError, double &stdError);
	void ExponentialRegresion1D(vector<vector<double>>& dataX, vector<vector<double>>& dataY, vector<vector<int>>& classData, int testClass, double &a, double &b, double &avgError, double &stdError);
	void LinearRegresion2D(vector<Vector3f>& data, double &a, double &b, double &c);
	void LinearRegresion2D(vector<vector<double>>& dataX, vector<vector<double>>& dataY, vector<vector<double>>& dataZ, vector<vector<int>>& classData, int testClass, double &a, double &b, double &c);
	void LogisticRegresion1D(vector<vector<double>>& data, vector<vector<int>>& classData, int testClass, double minVal, double maxVal, int noSteps, double &a, double &b);
};

//MaxTreeOperations
class MaxTree
{
public:
	max_tree tree;
	MaxTree(vector<vector<double>>& img);
	MaxTree(vector<vector<double>>& img, vector<vector<double>>& orgImg, int no_levels);

//MM Operators
	void AreaOpening(double a_th, int p=0);
	void AttributeOpening(double a_th, int p=0);
	void AttributeOpeningWithAreaConstrain(double a_th, double areaLim, double hTh, double aTh, int p=0, bool prune=false);
	/*OPIS: Vrednosti, ki glede na katere želimo izdelati DAP shranimo v Attribut, na outputu dobimo parameter*/
	void DAP(vector<double> lambda, bool ignoreFirst=false);
	void MSLSSegmentation(vector<double> lambda, bool ignoreFirst=false);
	void ContrastOpening(double ratio, double maxSize=255.0);
	/*OPIS: Attribute - attribut na katerem izvajamo DAP, Parameter - Residual image, Node_Parameter - Associated function*/
	void GenDTMOnContrastOpening(double z, double rTh, double refNumTh, vector<double> lambda);
	void ContrastOpeningOnDAP(double z, double rTh, vector<double> lambda);
	void UltimateAreaOpening(double addArea=0.0, double maxArea=0.0);
	void UltimateQOpening(double maxSize=0.0);
	void UltimateAreaStdOpening(double maxArea=0.0, double maxStd=0.0, double addArea=0.0);
// Divji operatorji
	void SetAttributeOnHRegs(int p=0);
	void AttributeOpeningOnHReg();
	void QWatershed(double minAttr, double maxAttr, double minSize, double maxSize);
	void _QWatershed(double minAttr, double maxAttr, double minSize, double maxSize, int &wr_index, int p);

//IO Functions
	void SetNodeStatData(vector<vector<double>>& data);
	void SetDataM2(vector<vector<int>>& data); //Hacking function
	void rHeight2Img(vector<vector<double>>& img);
	void Height2Img(vector<vector<double>>& img);
	void Height2Img(vector<vector<double>>& img, vector<vector<int>>& regs);
	void Attribute2Img(vector<vector<double>>& img);
	void Parameter2Img(vector<vector<double>>& img);
	void ParameterTopHat(vector<vector<double>>& img);
	void NodeAttribute2Img(vector<vector<double>>& img);
	void NodeParameter2Img(vector<vector<double>>& img);
	void MoveAttribute2A1();
//Thresholds
	void AdaptiveAreaStdThreshold(vector<vector<int>>& regs, double res, double maxArea, double maxStd, double mRefNumber);
	int _AdaptiveAreaStdThreshold(int p, double res, double maxArea, double maxStd, double mRefNumber);
	void _MarkBranch(int p);
	void ThresholdingOnAttribute1(double tVal);
	void _ThresholdingOnAttribute1(double tVal, int p);
//Hacking functions
	void SetAttributeImageForOpening(vector<vector<double>>& atrImg, bool propagation=true);
	void _PropagateAttributeForOpening(int p=0);
	void SetAreaAttribute();
	void SetMinBBAttribute();
	void SetMaxBBAttribute();
	void DivideAttributeByArea();
	void PropagateMaxResponse(int p);
	void PropagateMaxAttribute(int p=0);
	void PropagateMinAttribute(int p=0);

private:
	void SetNodeData(vector<vector<double>>& img);
	void PropagateDataM2(int p); //Hacking function
	void PropagateNodeData(int p);
	void PostPropagateNodeData(int p);
	void PropagateNodeStatData(int p);

	void _DAP(int p, double prevH, double maxN);
	void _PropagetMaxDAP(int p, bool ignoreFirst);
	void _ContrastOpening(double ratio, int p, double maxSize=255.0);
	void _ContrastOpeningOnDAP(int p, double z, double rTh);
	void _GenDTMOnContrastOpening(int p, double z, double rTh, double refNumTh);
	double _RTFunction(int p);
	void MarkSubnodes(int p, double param);
	void UltimateAreaOpening(int p, double addArea, double maxArea);
	void UltimateQOpening(int p, double maxSize);
	void UltimateAreaStdOpening(int p, double maxArea,  double maxStd, double addArea);
};
//Interpolation
class CInterpolations
{
private:
	void get_boundary_cells(vector<vector<int>>& data, vector<vector<POINT>>& data_out);
	void IDWInterpolatePoint(int x, int y, Vector3f& pnt, int winSize, vector<vector<Vector3f>>& grid, vector<vector<int>>& controlMap, double smooth);
	void IDWInterpolateRemovedPoint(int x, int y, Vector3f& pnt, int winSize, vector<vector<Vector3f>>& grid, vector<vector<int>>& controlMap, double smooth);
	void IDWInterpolateOnArray(Vector3f& pnt, vector<vector<Vector3f>>& grid, vector<POINT>& edges, double smooth);
	double W(vector<vector<Vector3f>>& grid, int x, int y,int xi, int yi, double smooth);
	double W(vector<vector<Vector3f>>& grid, Vector3f iPnt,int xi, int yi, double smooth);
	double FindNeighbourMin(int x, int y, vector<vector<Vector3f>>& grid, vector<vector<int>>& controlMap, int winSize=1);
public:
	void ClosestPointAndIDWInterpolation(vector<vector<Vector3f>>& grid, vector<vector<int>>& controlMap, Vector3f minPnt, double resolution, int idwSize=2);
	void IDWInterpolatePoint(int x, int y, Vector3f& pnt, int winSize, vector<vector<Vector3f>>& grid, double smooth);
	void IDWInterpolation(vector<vector<Vector3f>>& grid, vector<vector<int>>& controlMap, Vector3f minPnt, double resolution, bool inplace=false, int winSize=1, double smooth=2.0);
	void IDWInterpolationMissingQ(vector<vector<Vector3f>>& grid, vector<vector<int>>& controlMap, Vector3f minPnt, double resolution, double smooth=2.0);
	void IDWMissingPointsFromCenter(vector<vector<Vector3f>>& grid, vector<vector<int>>& controlMap, Vector3f minPnt, double resolution, double smooth=2.0);
	void IDWRemovedPointsFromCenter(vector<vector<Vector3f>>& grid, vector<vector<int>>& controlMap, double smooth=2.0);
	void IDWInterpolationRemovedPoints(vector<vector<Vector3f>>& grid, vector<vector<int>>& controlPnts, double smooth=2.0);
	void IDWInterpolationRemovedQ(vector<vector<Vector3f>>& grid, vector<vector<int>>& controlMap, double smooth=2.0);
	void IDWInterpolationOnEdgePoints(vector<vector<Vector3f>>& grid, vector<vector<int>>& controlMap, double smooth=2.0);
	void IDWInterpolatePointForCentering(int x, int y, Vector3f& pnt, int winSize, vector<vector<Vector3f>>& grid, double smooth);
	
	/*HELP FUNCTIONS*/
	void CreateVectorGridFromData(vector<vector<Vector3f>>& grid, vector<vector<double>>& data);
};
//Classification functions
class CDataClasiffication
{
private:
	/*DATA*/
	vector<double> c0_vect, c1_vect;
	/*FUNCTIONS*/
	double GetUpperFractValue(int c, vector<int>& fIndex);
	
public:
	/*DATA*/
	bool modelLoaded;

  	vector<int> classes;
	vector<double> cProbs;
	vector<double> scales;
	vector<double> minVals;
	vector<double> maxVals;
	vector<vector<double>> statModel;

	//Constructors
	CDataClasiffication();

	/*FUNCTIONS*/
		//Trening functions
	void GetHistogram(vector<vector<int>>& iImg, vector<vector<int>>& cntImg, vector<int>& hGram, int c);
	void GetHistogram(vector<vector<int>>& iImg, vector<vector<int>>& cntImg, vector<double>& hGram, int c, bool normalize=true);
	void GetHistogram(vector<vector<double>>& dImg, vector<vector<int>>& cntImg, vector<double>& hGram, int c, double scale=1.0, bool normalize=true);

		//My classification functions
	void AddClass(int c);
	void InitClassProbabilities(vector<vector<int>>& cntImg);
	void AddStatsToModel(vector<vector<int>>& data, vector<vector<int>>& cntImg, double minVal, double maxVal, int scale=1, bool normalize=true);
	void AddStatsToModel(vector<vector<double>>& data, vector<vector<int>>& cntImg, double minVal, double maxVal, double scale=1.0, bool normalize=true);
	int ClassifyByBayesLogic(vector<double> featVector);

		//Help functions
	void ClearStatModel();
	void ExportStatModel(CString filePath);
	void LoadStatModel(CString filePath);
};