#pragma once
#include <math.h>

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
	Vector2f(Vector2f& v)
	{	
		x = v.x;	y = v.y;
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

struct Color3f
{
	float  r, g, b;

	Color3f()
	{r = 0; g = 0; b = 0;}
	Color3f(float Red, float Green, float Blue)
	{r = Red; g = Green; b = Blue;}
	void operator=(const Color3f &C)
	{r = C.r;	g = C.g;	b = C.b;}
	static Color3f Create(int Red, int Green, int Blue)
	{ return Color3f(Red/255.0f,Green/255.0f,Blue/255.0f);}
};

struct Color4f
{
	float  r, g, b, a;

	Color4f()
	{r = 0; g = 0; b = 0; a = 0;}
	Color4f(float Red, float Green, float Blue, float Alfa)
	{r = Red; g = Green; b = Blue; a =Alfa; }
	Color4f(Color3f C, float Alfa)
	{r = C.r; g = C.g; b = C.b; a =Alfa; }
	void operator=(const Color4f &C)
	{r = C.r;	g = C.g;	b = C.b;	a = C.a; }
	static Color4f Create(int Red, int Green, int Blue, int Alfa)
	{ return Color4f(Red/255.0f, Green/255.0f, Blue/255.0f, Alfa/255.0f);}
};

struct Ray
{
	Vector3f o;	// Zaèetna toèka žarka.
	Vector3f d;	// Smerni vektor žarka
	float	 l; // Dolžina žarka
	// Konstruktorji
	Ray(void)
	{
		this->o = Vector3f();
		this->d = Vector3f();
		this->l = -1;
	}
	Ray(Vector3f O, Vector3f D, float L)
	{
		this->o = O;
		this->d = D;		
		this->l = L;
		d.Normalize();
	}

	// Doloèanje dolžine
	inline void SetLength(float L)
	{	if(L < 0 ) L = -1;	this->l = L;}
	// Izraèunamo razdaljo med toèko in žarkom
	inline float Distance(Vector3f& P)
	{
		Vector3f w = P - o;
		return CrossProd(d, w).Length();
	}
	inline Vector3f GetSecondPoint()
	{
		return o + (d * l);
	}
};

struct Plane
{
	float a, b, c;
	float d;
	Vector3f p; //Toèka na ravnini

	static enum Halfspace
	{
		NEGATIVE = -1,
		ON_PLANE = 0,
		POSITIVE = 1
	};
	///Konstruktorji
	Plane()
	{ a = b = c = d = 0; p = Vector3f();}
	Plane(const float& a, const float& b, const float& c, const float& d)
	{
		this->a = a;	this->b = b;	this->c = c;	this->d = d;	this->p = Vector3f();
	}
	Plane(const Plane& P)
	{
		a = P.a;	b = P.b;	c = P.c;	d = P.d;	p = P.p;
	}
	Plane(const Vector3f& N, const Vector3f& P)
	{
		a = N.x;	b = N.y;	c = N.z; //Normal = n; 
		d = -DotProd(P, N);
		this->p = P;
	}
	Plane(const Vector3f& N, const Vector3f& P, const float D)
	{
		a = N.x;	b = N.y;	c = N.z; //Normal = n; 
		d = D;//-DotProd(p, n);
		p = P;		
	}
	Plane(const Vector3f& A, const Vector3f& B, const Vector3f& C)
	{
		Vector3f N = CrossProd(B-A, C-A); N.Normalize();
		this->a = N.x;	this->b = N.y;	this->c = N.z;
		this->p = A;
		this->d = -DotProd(p, N);
	}
	// 
	Vector3f GetNormal()
	{	
		return Vector3f(a, b, c);	
	}
	// Izraèunamo razdaljo med toèko in ravnino
	friend inline float Distance(const Plane& P, const Vector3f& V)
	{
		return P.a * V.x + P.b * V.y + P.c * V.z + P.d;
	}
	// Izraèunamo razdaljo med toèko in ravnino
	inline float Distance(const Vector3f & P)
	{
		return a * P.x + b * P.y + c * P.z + d;
	}
	//	// Normaliziramo 
	friend inline void Normalize(Plane& plane)
	{
		float mag = sqrt(plane.a * plane.a + plane.b * plane.b + plane.c * plane.c);
		plane.a = plane.a / mag;
		plane.b = plane.b / mag;
		plane.c = plane.c / mag;
		plane.d = plane.d / mag;
	}

	// Normaliziramo 
	inline void Normalize()
	{
		float mag = sqrt(a * a + b * b + c * c);
		a /= mag;
		b /= mag;
		c /= mag;
		d /= mag;
	}
	// Izraèunamo toèko kjer zarek seka ravnino
	friend inline Vector3f Intersects(Plane P, Ray R)
	{	
		float imenovalec= DotProd(P.GetNormal(), R.d);
		float stevec	= DotProd(P.GetNormal(), P.p - R.o);

		if(imenovalec)
		{
			R.l = stevec / imenovalec;
			return  R.GetSecondPoint();
		}
		else
			return Vector3f();
	}
	// Preverimo na kateri strani ravnine je toèka
	inline Halfspace Classify(const Vector3f & P)
	{
		float dist = Distance(P);//this->a * P.x + this->b * P.y + this->c * P.z + this->d;
		if (dist < 0) return NEGATIVE;
		if (dist > 0) return POSITIVE;
		return ON_PLANE;
	}
};

struct BoundingBox
{	
	Vector3f Min, Max, Center;
	// Konstruktorji
	BoundingBox(void)
	{
		Min = Vector3f();
		Max = Vector3f();
		Center = Vector3f();
	}	
	BoundingBox(float MinX, float MinY, float MinZ, float MaxX, float MaxY, float MaxZ)
	{
		Min = Vector3f(MIN(MinX, MaxX), MIN(MinY, MaxY), MIN(MinZ, MaxZ));
		Max = Vector3f(MAX(MinX, MaxX), MAX(MinY, MaxY), MAX(MinZ, MaxZ));
		Center = (Min + Max) / 2.f;
	}
	BoundingBox(const Vector3f& min, const Vector3f& max)
	{
		Min = min;
		Max = max;
		GetCenter();
	}
	BoundingBox(const Vector2f& min, const Vector2f& max)
	{
		Min = Vector3f(min.x, min.y, 0);
		Max = Vector3f(max.x, max.y, 0);
		GetCenter();
	}
	//	
	Vector3f GetBottomBackLeft()	{	return Vector3f(Min.x, Max.y, Min.z);	}
	Vector3f GetBottomBackRight()	{	return Vector3f(Max.x, Max.y, Min.z);	}
	Vector3f GetBottomFrontRight()	{	return Vector3f(Max.x, Min.y, Min.z);	}
	Vector3f GetBottomFrontLeft()	{	return Vector3f(Min.x, Min.y, Min.z);	}
	Vector3f GetTopBackLeft()		{	return Vector3f(Min.x, Max.y, Max.z);	}
	Vector3f GetTopBackRight()		{	return Vector3f(Max.x, Max.y, Max.z);	}
	Vector3f GetTopFrontRight()		{	return Vector3f(Max.x, Min.y, Max.z);	}
	Vector3f GetTopFrontLeft()		{	return Vector3f(Min.x, Min.y, Max.z);	}
	Vector3f GetCenter()			{	Center = (Min + Max) / 2.f; return Center; }
	float GetHeight()				{	return Max.y - Min.y; }
	float GetWidth()				{	return Max.x - Min.x; }
	float GetDepth()				{	return Max.z - Min.z; }
	float Square()					{	return GetHeight() * GetWidth();}
	float Cube()					{	return GetHeight() * GetWidth() * GetDepth();}
	// Metoda preveri ali se toèka nahaja v BB
	bool Contains2D(const Vector3f &v)
	{
		if (v.x <= Min.x) return false;
		if (v.y <= Min.y) return false;
		if (v.x >= Max.x) return false;
		if (v.y >= Max.y) return false;
		return true;
	}
	// Metoda preveri ali se toèka nahaja v BB
	bool Contains(const Vector2f &v)
	{
		if (v.x <= Min.x) return false;
		if (v.y <= Min.y) return false;
		if (v.x >= Max.x) return false;
		if (v.y >= Max.y) return false;
		return true;
	}
	// Metoda preveri ali se toèka nahaja v BB
	bool Contains(const Vector3f &v)
	{
		if (v.x <= Min.x) return false;
		if (v.y <= Min.y) return false;
		if (v.z <= Min.z) return false;
		if (v.x >= Max.x) return false;
		if (v.y >= Max.y) return false;
		if (v.z >= Max.z) return false;
		return true;
	}
	// Metoda preveri ali se toèka nahaja v BB
	bool Contains(const float &X, const float &Z)
	{
		if (X <= Min.x) return false;
		if (Z <= Min.z) return false;
		if (X >= Max.x) return false;
		if (Z >= Max.z) return false;
		return true;
	}
	// Razdelimo BB na kvadrante, podamu mu BB ki ga delimo in kvadrant
	void ConstructQuad(const BoundingBox& BB, int Quad)
	{
		switch (Quad)
		{// bounding box vedno postavimo v spodnji levi kot, potem pa ga bomo transformirali za ustrezen vektor
		case 0: Min = Vector3f(BB.Center.x, BB.Center.y, BB.Min.z);	
			Max = BB.Max; 
			Center = (Min + Max) / 2.0f;	
			break; 
		case 1: Min = Vector3f(BB.Min.x, BB.Center.y, BB.Min.z);	
			Max = Vector3f(BB.Center.x, BB.Max.y, BB.Max.z); 
			Center = (Min + Max) / 2.0f;	
			break; 
		case 2: Min = BB.Min;
			Max = Vector3f(BB.Center.x, BB.Center.y, BB.Max.z); 
			Center = (Min + Max) / 2.0f;	
			break; 
		case 3: Min = Vector3f(BB.Center.x, BB.Min.y, BB.Min.z);	
			Max = Vector3f(BB.Max.x, BB.Center.y, BB.Max.z); 
			Center = (Min + Max) / 2.0f;	
			break; 
		default:break;
		}
	}
	// Razširimo BoundingBox tako da bo vseboval BB
	void Expand(const BoundingBox& BB)
	{
		// preverimo ali je potrebno popraviti minimalne koordinate
		if (BB.Min.x < Min.x)
			Min.x = BB.Min.x;
		if (BB.Min.y < Min.y)
			Min.y = BB.Min.y;
		if (BB.Min.z < Min.z)
			Min.z = BB.Min.z;

		// preverimo ali je potrebno popraviti maksilmalne koordinate
		if (BB.Max.x > Max.x)
			Max.x = BB.Max.x;
		if (BB.Max.y > Max.y)
			Max.y = BB.Max.y;
		if (BB.Max.z > Max.z)
			Max.z = BB.Max.z;


		// sedaj moramo prestaviti središèe
		Center = (Min + Max) / 2.0f;
	} 
	// Premaknemo BB
	void Offset(Vector3f offset)
	{
		Min-= offset;	Max-= offset;	Center-= offset;
	}
	// Metoda preveri ali se BB sekata
	inline bool Intersects(const BoundingBox &BB)
	{
		if ((Min.x > BB.Max.x) || (BB.Min.x > Max.x))
			return false;
		if ((Min.y > BB.Max.y) || (BB.Min.y > Max.y))
			return false;
		if ((Min.z > BB.Max.z) || (BB.Min.z > Max.z))
			return false;
		return true;
	}





	// Metoda preveri ali BB sekata ravnino
	bool Intersects(Plane& P)
	{
		Vector3f min = Vector3f(), 
				 max = Vector3f();
		// Najprej poišèemo ekstremne koordinate glede na normalo ravnine
		if (P.a >= 0.0f){
			min.x = Min.x;
			max.x = Max.x;
		}else{
			min.x = Max.x;
			max.x = Min.x;
		}if (P.b >= 0.0f){
			min.y = Min.y;
			max.y = Max.y;
		}else{
			min.y = Max.y;
			max.y = Min.y;
		}if (P.c >= 0.0f){
			min.z = Min.z;
			max.z = Max.z;
		}else{
			min.z = Max.z;
			max.z = Min.z;
		}

		if ( P.Distance(min) > 0.0f)  // èe minimalna toèka leži pred ravnino potem ravnina ne more sekati omejujoèega kvadra
			return false;
		if ( P.Distance(max) >= 0.0f) //  maksimalna toèka leži pred ravnino (minimalna pa za njo) torej ravnina seka omejujoè kvader
			return true;

		return false; // minimalna in maksimalna toèka ležita za ravnino
	}  


	// Metoda preveri ali BB sekata žarek
	bool Intersects(const Ray& R, Vector3f *HitPoint = NULL)
	{
		bool bInside = true;
		Vector3f MaxT = Vector3f(-1.0f, -1.0f, -1.0f);
		Vector3f vTempIPoint;
		float epsilon = 0.000001f;
		// Poišèemo x componento
		if (R.o.x < Min.x)
		{
			vTempIPoint.x = Min.x;
			bInside = false;
			if (R.d.x != 0.0f)
				MaxT.x = (Min.x - R.o.x) / R.d.x;
		}
		else if (R.o.x > Max.x)
		{
			vTempIPoint.x = Max.x;
			bInside = false;
			if (R.d.x != 0.0f)
				MaxT.x = (Max.x - R.o.x) / R.d.x;
		}
		// poiscemo y komponento
		if (R.o.y < Min.y)
		{
			vTempIPoint.y= Min.y;
			bInside = false;
			if (R.d.y != 0.0f)
				MaxT.y = (Min.y - R.o.y) / R.d.y;
		}
		else if (R.o.y > Max.y)
		{
			vTempIPoint.y = Max.y;
			bInside = false;
			if (R.d.y != 0.0f)
				MaxT.y = (Max.y - R.o.y) / R.d.y;
		}
		// poiscemo z komponento
		if (R.o.z < Min.z)
		{
			vTempIPoint.z = Min.z;
			bInside = false;
			if (R.d.z != 0.0f)
				MaxT.z = (Min.z - R.o.z) / R.d.z;
		}
		else if (R.o.z > Max.z)
		{
			vTempIPoint.z = Max.z;
			bInside = false;
			if (R.d.z != 0.0f)
				MaxT.z = (Max.z - R.o.z) / R.d.z;
		}
		// ali je izhodisce vektorja znotraj BB
		if (bInside)
		{
			if(HitPoint)
			(*HitPoint) = R.o;
			return true;
		}

		// poiscemo najvecjo vrednost MaxT
		int nPlane = 0;
		if (MaxT.y > ((float*)&MaxT)[nPlane]) 
			nPlane = 1;    
		if (MaxT.z > ((float*)&MaxT)[nPlane]) 
			nPlane = 2; 

		if ( ((float*)&MaxT)[nPlane] < 0.0f)
			return false;   

		if (nPlane != 0)
		{
			vTempIPoint.x = R.o.x + ((float*)&MaxT)[nPlane] * R.d.x;
			if (( vTempIPoint.x < Min.x - epsilon) ||
				( vTempIPoint.x > Max.x + epsilon) )
				return false;
		}

		if (nPlane != 1)
		{
			vTempIPoint.y = R.o.y + ((float*)&MaxT)[nPlane] * R.d.y;
			if (( vTempIPoint.y < Min.y - epsilon) ||
				( vTempIPoint.y > Max.y + epsilon) )
				return false;
		}

		if (nPlane != 2)
		{
			vTempIPoint.z = R.o.z + ((float*)&MaxT)[nPlane] * R.d.z;
			if (( vTempIPoint.z < Min.z - epsilon) ||
				( vTempIPoint.z > Max.z + epsilon) )
				return false;
		}
		if(HitPoint)
		(*HitPoint) = vTempIPoint;
		return true;
	}
};

struct Frustum
{	
	Plane m_Planes[6];
	// Ravnine vidne piramide
	static enum Planes{ 
		PN_LEFT = 0, 
		PN_RIGHT, 
		PN_TOP,
		PN_BOTTOM, 
		PN_NEAR, 
		PN_FAR
	};
	// Rezultat Cullinga
	static enum Cull{OUTSIDE, INTERSECT, INSIDE};
	// Culling BB
	Cull CullBox(BoundingBox& BB)
	{		
		Cull result = INSIDE;
		int out, in;
		Vector3f Box[8];
		Box[0] = BB.GetBottomFrontLeft();
		Box[1] = BB.GetBottomFrontRight();
		Box[2] = BB.GetBottomBackLeft();
		Box[3] = BB.GetBottomBackRight();
		Box[4] = BB.GetTopFrontLeft();
		Box[5] = BB.GetTopFrontRight();
		Box[6] = BB.GetTopBackLeft();
		Box[7] = BB.GetTopBackRight();
		// for each plane do ...
		for(int i=0; i < 6; i++)
		{// reset counters for corners in and out
			out=0;in=0;
			// for each corner of the box do ...
			// get out of the cycle as soon as a box as corners
			// both inside and out of the frustum
			for (int k = 0; k < 8 && (in==0 || out==0); k++) 
			{// is the corner outside or inside
				if (m_Planes[i].Classify(Box[k]) == Plane::NEGATIVE)
					out++;
				else
					in++;
			}
			//if all corners are out
			if (!in)
				return OUTSIDE;
			// if some corners are out and others are in	
			else if (out)
				result = INTERSECT;
		}
		return result ;
	}
};

struct Matrix4x4
{
	// The elements of the 4x4 matrix are stored in
	// column-major order (see "OpenGL Programming Guide",
	// 3rd edition, pp 106, glLoadMatrix).
	float _11, _21, _31, _41;
	float _12, _22, _32, _42;
	float _13, _23, _33, _43;
	float _14, _24, _34, _44;

	Matrix4x4()
	{
		_11 = _21 = _31 = _41 =
		_12 = _22 = _32 = _42 = 
		_13 = _23 = _33 = _43 = 
		_14 = _24 = _34 = _44 = 0;
	}
};

struct WaveElement
{
	unsigned int Lenght;
	float Alfa;

	WaveElement()
	{
		Lenght = 0;
		Alfa = 0.0f;
	};
};

struct WaveTube
{
	Ray R;
	Color3f Barva;
	unsigned int Size;
	WaveElement* Elements;

	WaveTube()
	{
		this->Size = 0;
		Elements =  NULL;
	};

	~WaveTube()
	{
		if(Elements)
		{
			delete[] Elements;
			Elements = NULL;
			Size = 0;
		}
	};

	void Create(unsigned int size)
	{
		this->Size = size;
		Elements =  new WaveElement[size];
	};
};