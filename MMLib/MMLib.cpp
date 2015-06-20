//#include "stdafx.h"
#include "afx.h"
#include "MMLib.h"
#include <iostream>
#include <cstddef>
#include <limits>
#include "bestfit.h"
//Support functions
using namespace std;

bool myfnS2L(PixelEl i, PixelEl j) { return i.val<j.val; }
bool myfnL2S(PixelEl i, PixelEl j) { return i.val>j.val; }
bool mySortVectorL2S(Vector3f i, Vector3f j) { return i.z>j.z; }
/*START: Global functions*/
void InitData(vector<vector<int>>& data,int initVal)
{
	for(int x=0;x<data.size(); x++)
		for(int y=0;y<data[0].size(); y++)
			data[x][y]=initVal;
}
void InitData(vector<vector<double>>& data,double initVal)
{
	for(int x=0;x<data.size(); x++)
		for(int y=0;y<data[0].size(); y++)
			data[x][y]=initVal;
}
void AbsData(vector<vector<double>>& data)
{
	for(int x=0;x<data.size(); x++)
		for(int y=0;y<data[0].size(); y++)
			data[x][y]=abs(data[x][y]);
}
void LowHighLimit(vector<vector<double>>& data, double lLim, double hLim)
{
	for(int x=0;x<data.size(); x++)
	{
		for(int y=0;y<data[0].size(); y++)
		{
			if(data[x][y]<lLim)
				data[x][y]=lLim;
			else if(data[x][y]>hLim)
				data[x][y]=hLim;
		}
	}
}
void NormalizeData(vector<vector<double>>& data, double lLim, double hLim)
{
	double maxVal=data[0][0];
	double minVal=data[0][0];

	for(int x=0;x<data.size(); x++)
	{
		for(int y=0;y<data[0].size(); y++)
		{
			if(maxVal<data[x][y])
				maxVal=data[x][y];
			else if(minVal>data[x][y])
				minVal=data[x][y];
		}
	}
	double diff=maxVal-minVal;
	for(int x=0;x<data.size(); x++)
	{
		for(int y=0;y<data[0].size(); y++)
		{
			data[x][y]=(data[x][y]-minVal)/diff;
		}
	}
	
	diff=hLim-lLim;
	for(int x=0;x<data.size(); x++)
	{
		for(int y=0;y<data[0].size(); y++)
		{
			data[x][y]=data[x][y]*diff+lLim;
		}
	}
}
void CropData(vector<vector<double>>& data, double lLim, double hLim)
{
	for(int x=0;x<data.size(); x++)
	{
		for(int y=0;y<data[0].size(); y++)
		{
			if(data[x][y]>hLim)
				data[x][y]=hLim;
			else if(data[x][y]<lLim)
				data[x][y]=lLim;
		}
	}
}
void CropData(vector<vector<int>>& data, int lLim, int hLim)
{
	for(int x=0;x<data.size(); x++)
	{
		for(int y=0;y<data[0].size(); y++)
		{
			if(data[x][y]>hLim)
				data[x][y]=hLim;
			else if(data[x][y]<lLim)
				data[x][y]=lLim;
		}
	}
}
void BComplementData(vector<vector<int>>& data)
{
	for(int x=0;x<data.size(); x++)
	{
		for(int y=0;y<data[0].size(); y++)
		{
			if(data[x][y])
				data[x][y]=0;
			else
				data[x][y]=1;
		}
	}
}
void ComplementData(vector<vector<int>>& data)
{
	int maxEl=data[0][0];	
	int minEl=data[0][0];
	for(int x=0;x<data.size(); x++)
	{
		for(int y=0;y<data[0].size(); y++)
		{
			if(maxEl<data[x][y])
				maxEl=data[x][y];

			if(minEl>data[x][y])
				minEl=data[x][y];
		}
	}

	for(int x=0;x<data.size(); x++)
		for(int y=0;y<data[0].size(); y++)
			data[x][y]=maxEl-(data[x][y]-minEl);
}
void ComplementData(vector<vector<double>>& data)
{
	double maxEl=data[0][0];	
	double minEl=data[0][0];
	for(int x=0;x<data.size(); x++)
	{
		for(int y=0;y<data[0].size(); y++)
		{
			if(maxEl<data[x][y])
				maxEl=data[x][y];

			if(minEl>data[x][y])
				minEl=data[x][y];
		}
	}
	for(int x=0;x<data.size(); x++)
		for(int y=0;y<data[0].size(); y++)
			data[x][y]=maxEl-(data[x][y]-minEl);
}
void InvertData(vector<vector<double>>& data)
{
	for(int x=0;x<data.size();x++)
		for(int y=0;y<data[0].size();y++)
			data[x][y]*=-1;
}
void CondenseData(vector<vector<int>>& data, int maxVal)
{
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			int val=data[x][y]%maxVal;
			if(data[x][y] && !val)
				data[x][y]=maxVal;
			else if(data[x][y])
				data[x][y]=val;
		}
	}
}
void SelectMax(vector<vector<double>>& io_data,vector<vector<double>>& c_data)
{
	for(int x=0;x<io_data.size();x++)
		for(int y=0;y<io_data[0].size();y++)
			io_data[x][y]=max(io_data[x][y],c_data[x][y]);
}
void SelectMax(vector<vector<int>>& io_data, vector<vector<int>>& c_data)
{
	for(int x=0;x<io_data.size();x++)
		for(int y=0;y<io_data[0].size();y++)
			io_data[x][y]=max(io_data[x][y],c_data[x][y]);
}
void Union(vector<vector<int>>& img1, vector<vector<int>>& img2)
{
	for(int x=0;x<img1.size(); x++)
		for(int y=0;y<img1[0].size(); y++)
			img1[x][y]=max(img1[x][y],img2[x][y]);
}
void Union(vector<vector<int>>& img1, vector<vector<int>>& img2, vector<vector<int>>& output)
{
	for(int x=0;x<img1.size(); x++)
		for(int y=0;y<img1[0].size(); y++)
			output[x][y]=max(img1[x][y],img2[x][y]);
}
void Intersection(vector<vector<int>>& img1, vector<vector<int>>& img2, vector<vector<int>>& output)
{
	for(int x=0;x<img1.size(); x++)
		for(int y=0;y<img1[0].size(); y++)
			output[x][y]=min(img1[x][y],img2[x][y]);
}
void AddData(vector<vector<double>>& img1, double val)
{
	for(int x=0;x<img1.size(); x++)
		for(int y=0;y<img1[0].size(); y++)
			img1[x][y]+=val;
}
void AddData(vector<vector<int>>& img1, int val)
{
	for(int x=0;x<img1.size(); x++)
		for(int y=0;y<img1[0].size(); y++)
			img1[x][y]+=val;
}
void AddData(vector<vector<double>>& img1, vector<vector<double>>& img2)
{
	for(int x=0;x<img1.size(); x++)
		for(int y=0;y<img1[0].size(); y++)
			img1[x][y]+=img2[x][y];
}
void AddData(vector<vector<int>>& img1, vector<vector<int>>& img2)
{
	for(int x=0;x<img1.size(); x++)
		for(int y=0;y<img1[0].size(); y++)
			img1[x][y]+=img2[x][y];
}
void AddData(vector<vector<double>>& img1, vector<vector<double>>& img2, vector<vector<double>>& result)
{
	for(int x=0;x<img1.size(); x++)
		for(int y=0;y<img1[0].size(); y++)
			result[x][y]=img1[x][y]+img2[x][y];
}
void AddData(vector<double>& vect1, vector<double>& vect2)
{
	for(int i=0;i<vect1.size();i++)
		vect1[i]+=vect2[i];
}
void AddData(vector<double>& vect1, vector<double>& vect2, vector<double>& result)
{
	for(int i=0;i<vect1.size();i++)
		result[i]=vect1[i]+vect2[i];
}
void SubtractData(vector<vector<int>>& img, int val)
{
	for(int x=0;x<img.size(); x++)
		for(int y=0;y<img[0].size(); y++)
			img[x][y]-=val;
}
void SubtractData(vector<vector<double>>& img, double val)
{
	for(int x=0;x<img.size(); x++)
		for(int y=0;y<img[0].size(); y++)
			img[x][y]-=val;
}
void SubtractData(vector<vector<int>>& img1, vector<vector<int>>& img2)
{
	for(int x=0;x<img1.size(); x++)
		for(int y=0;y<img1[0].size(); y++)
			img1[x][y]-=img2[x][y];
}
void SubtractData(vector<vector<double>>& img1, vector<vector<double>>& img2)
{
	for(int x=0;x<img1.size(); x++)
		for(int y=0;y<img1[0].size(); y++)
			img1[x][y]-=img2[x][y];
}
void SubtractData(vector<vector<double>>& img1, vector<vector<double>>& img2, vector<vector<double>>& result)
{
	for(int x=0;x<img1.size(); x++)
		for(int y=0;y<img1[0].size(); y++)
			result[x][y]=img1[x][y]-img2[x][y];
}
void MultiplyData(vector<vector<double>>& data, double factor)
{
	for(int x=0; x<data.size();x++)
		for(int y=0; y<data[0].size();y++)
			data[x][y]*=factor;
}
void MultiplyData(vector<vector<double>>& data1, vector<vector<double>>& data2)
{
	for(int x=0; x<data1.size();x++)
		for(int y=0; y<data1[0].size();y++)
			data1[x][y]*=data2[x][y];
}
void MultiplyData(vector<vector<double>>& data1, vector<vector<int>>& data2)
{
	for(int x=0; x<data1.size();x++)
		for(int y=0; y<data1[0].size();y++)
			data1[x][y]*=(double)data2[x][y];
}
void MultiplyData(vector<vector<int>>& data, int factor)
{
	for(int x=0; x<data.size();x++)
		for(int y=0; y<data[0].size();y++)
			data[x][y]*=factor;
}
void DrawDisk(vector<vector<int>>& data, int x, int y, int polmer, int color)
{
	int winSize=polmer;
	int sx=max(0,x-winSize);
	int ex=min(data.size()-1,x+winSize);
	int sy=max(0,y-winSize);
	int ey=min(data[0].size()-1,y+winSize);

	for(int _x=sx;_x<=ex;_x++)
	{
		for(int _y=0;_y<=ey;_y++)
		{
			int xDist=_x-x;
			int yDist=_y-y;

			float dist=sqrt((float)(xDist*xDist+yDist*yDist));
			if(dist<polmer+0.5)
				data[_x][_y]=color;
		}
	}
}
void CopyDataToData(vector<vector<int>>& in_data,vector<vector<double>>& out_data)
{
	for(int x=0;x<in_data.size();x++)
		for(int y=0;y<in_data[0].size();y++)
			out_data[x][y]=in_data[x][y];
}
void CopyDataToData(vector<vector<double>>& in_data,vector<vector<int>>& out_data)
{
	for(int x=0;x<in_data.size();x++)
		for(int y=0;y<in_data[0].size();y++)
			out_data[x][y]=in_data[x][y];
}
void CopyVectorToData(vector<vector<Vector3f>>& in_data,vector<vector<double>>& out_data)
{
	for(int x=0;x<in_data.size();x++)
		for(int y=0;y<in_data[0].size();y++)
			out_data[x][y]=in_data[x][y].z;
}
void CopyDataToVector(vector<vector<double>>& in_data,vector<vector<Vector3f>>& out_data)
{
	for(int x=0;x<in_data.size();x++)
		for(int y=0;y<in_data[0].size();y++)
			out_data[x][y].z=in_data[x][y];
}
void CreateLevelImg(vector<vector<double>>& data, vector<vector<double>>& level_img, int noLevels)
{
	/*START: Init data*/
	double maxVal,minVal;
	maxVal=data[0][0];
	minVal=data[0][0];
	/*END: Init data*/
	
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(maxVal<data[x][y])
				maxVal=data[x][y];
			else if(minVal>data[x][y])
				minVal=data[x][y];
		}
	}
	
	double diff=maxVal-minVal;
	double fact=(double)noLevels/diff;

	for(int x=0;x<data.size();x++)
		for(int y=0;y<data[0].size();y++)
			level_img[x][y]=(int)((data[x][y]-minVal)*fact);
}
void GetNormalImage(vector<vector<Vector3f>>& grid, vector<vector<double>>& nImg, int winSize)
{
	int fullWinSize=winSize*2+1;
	Vector3f* vects= new Vector3f[fullWinSize*fullWinSize];
	for(int x=0;x<grid.size();x++)
	{
		for(int y=0;y<grid[0].size();y++)
		{
			int sx=max(0,x-winSize);
			int ex=min(grid.size()-1,x+winSize);
			int sy=max(0,y-winSize);
			int ey=min(grid[0].size()-1,y+winSize);	

			int noVs=0;
			for(int _x=sx;_x<=ex;_x++)
			{
				for(int _y=sy;_y<=ey;_y++)
				{
					if(_x==x && _y==y)
						continue;
					vects[noVs]=grid[_x][_y]-grid[x][y];
					noVs++;
				}
			}
			Vector3f avgV=vects[0].Cross(vects[noVs-1]);
			if(avgV.z<0.0)
				avgV.z*=-1.0;
			for(int i=1;i<noVs;i++)
			{
				Vector3f vct=vects[i-1].Cross(vects[i]);
				if(vct.z<0.0)
					vct.z*=-1.0;
				avgV+=vct;
			}

			avgV.x/=(double)noVs;
			avgV.y/=(double)noVs;
			avgV.z/=(double)noVs;

			avgV.Normalize();
			nImg[x][y]=avgV.z;
		}
	}
	delete[] vects;
}
void GetNormalStack(vector<vector<Vector3f>>& grid, vector<vector<vector<Vector3f>>>& nImg)
{
	vector<vector<vector<Vector3f>>> tmpImg(grid.size(),vector<vector<Vector3f>>(grid[0].size()));
	nImg=tmpImg;

	int winSize=1;
	for(int x=0;x<grid.size();x++)
	{
		for(int y=0;y<grid[0].size();y++)
		{
			int sx=max(0,x-winSize);
			int ex=min(grid.size()-1,x+winSize);
			int sy=max(0,y-winSize);
			int ey=min(grid[0].size()-1,y+winSize);	

			for(int _x=sx;_x<=ex;_x++)
			{
				for(int _y=sy;_y<=ey;_y++)
				{
					if(_x==x && _y==y)
						continue;
					//Vector3f vct=grid[_x][_y]-grid[x][y];
					Vector3f vct=grid[_x][_y].Cross(grid[x][y]);
					if(vct.z<0.0)vct*=-1.0;
					vct.Normalize();
					nImg[x][y].push_back(vct);
				}
			}
		}
	}
}
void GetSlopeAngles(vector<vector<double>>& slope, vector<vector<double>>& aspect, double resolution)
{
	vector<vector<double>> outData=slope;
	int mx=slope.size()-1;
	int my=slope[0].size()-1;
	for(int x=0;x<slope.size();x++)
	{
		for(int y=0;y<slope[0].size();y++)
		{
			double a=slope[x][y];	if(x>0 && y>0)	a=slope[x-1][y-1];
			double b=slope[x][y];	if(x>0)			b=slope[x-1][y];
			double c=slope[x][y];	if(x>0 && y<my)	c=slope[x-1][y+1];
			double d=slope[x][y];	if(y>0)			d=slope[x][y-1];
			double f=slope[x][y];	if(y<my)		f=slope[x][y+1];
			double g=slope[x][y];	if(x<mx && y>0)	g=slope[x+1][y-1];
			double h=slope[x][y];	if(x<mx)		h=slope[x+1][y];
			double i=slope[x][y];	if(x<mx && y<my)i=slope[x+1][y+1];

			double dzdx = ((c + 2.0*f + i) - (a + 2.0*d + g)) / (8.0 * resolution);
			double dzdy = ((g + 2.0*h + i) - (a + 2.0*b + c)) / (8.0 * resolution);
			
			double slope_rad = atan( sqrt( dzdx*dzdx + dzdy*dzdy));
			outData[x][y]=max(slope_rad,0.0);

			double aspect_rad=0.0;
			if(outData[x][y]>0.0)
			{
				aspect_rad= atan2(dzdy,-1.0*dzdx);
				if(aspect_rad < 0.0)
					 aspect_rad = 2.0*PI + aspect_rad;
			}
			else
			{
				if(dzdy > 0.0)
					aspect_rad = PI/2.0;
				else if(dzdy < 0.0)
					aspect_rad = 2.0*PI - PI/2.0;
				else 
					aspect_rad = 0.0;
			}
			aspect[x][y]=aspect_rad;
		}
	}
	slope=outData;
}
double VectorEDistance(vector<double>& vect_a,vector<double>& vect_b)
{
	double dist=0.0;
	for(int i=0;i<vect_a.size();i++)
	{
		double dif=vect_a[i]-vect_b[i];
		dist+=dif*dif;
	}
	dist=sqrt(dist);
	return dist;
}
double VectorWeightedEDistance(vector<double>& vect_a,vector<double>& vect_b,vector<double>& w)
{
	double dist=0.0;
	for(int i=0;i<vect_a.size();i++)
	{
		double dif=(vect_a[i]-vect_b[i])/w[i];
		dist+=dif*dif;
	}
	dist=sqrt(dist);
	return dist;
}
void VectorNormalize(vector<double>& vect)
{
	double sum=0.0;
	for(int i=0;i<vect.size();i++)
		sum+=vect[i];
	for(int i=0;i<vect.size();i++)
		vect[i]/=sum;
}
void MatrixNormalize(vector<vector<double>>& data)
{
	double minV=data[0][0];
	double maxV=data[0][0];

	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(minV>data[x][y])
				minV=data[x][y];
			if(maxV<data[x][y])
				maxV=data[x][y];
		}
	}

	double coef=maxV-minV;
	for(int x=0;x<data.size();x++)
		for(int y=0;y<data[0].size();y++)
			data[x][y]=(data[x][y]-minV)/coef;
}
void SetUnion(vector<vector<int>>& io_data,vector<vector<int>>& data)
{
	for(int x=0;x<data.size();x++)
		for(int y=0;y<data[0].size();y++)
			io_data[x][y]=max(io_data[x][y],data[x][y]);
}
void SetIntersection(vector<vector<int>>& io_data,vector<vector<int>>& data)
{
	for(int x=0;x<data.size();x++)
		for(int y=0;y<data[0].size();y++)
			io_data[x][y]=min(io_data[x][y],data[x][y]);
}
void SetWithout(vector<vector<int>>& io_data,vector<vector<int>>& data)
{
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(data[x][y])
				io_data[x][y]=0;
		}
	}
}
	/*Output/debug functions*/
void OutputValue(int val, const char* title)
{
	CString txt;txt.Format("Value = %d", val);
	MessageBox(0,txt.GetBuffer(),title,MB_OK);
}
void OutputValue(double val, const char* title)
{
	CString txt;txt.Format("Value = %.5f", val);
	MessageBox(0,txt.GetBuffer(),title,MB_OK);
}
void OutputVector(vector<int> vals, const char* title)
{
	CString txt,tmp;txt.Format("Values: \n");
	for(int i=0; i<vals.size();i++)
	{
		tmp.Format("%d: %d\n",i,vals[i]);
		txt+=tmp;
	}
	MessageBox(0,txt.GetBuffer(),title,MB_OK);
}
void OutputVector(vector<PixelEl> vals, const char* title, int lIndex, int hIndex)
{
	CString txt,tmp;txt.Format("Values: \n");
	hIndex=min((int)vals.size()-1,hIndex);
	for(int i=lIndex; i<=hIndex;i++)
	{
		tmp.Format("%d->%d, %d = %.3f\n",i,vals[i].x,vals[i].y,vals[i].val);
		txt+=tmp;
	}
	MessageBox(0,txt.GetBuffer(),title,MB_OK);
}
void OutputMatrix(vector<vector<double>>& vals, const char* title, int minX,int minY, int maxX,int maxY)
{
	if(minX==-1)
		minX=0;
	if(minY==-1)
		minY=0;

	if(maxX==-1)
		maxX=vals.size();
	if(maxY==-1)
		maxY=vals[0].size();

	CString txt,tmp;
	for(int x=minX;x<maxX;x++)
	{
		for(int y=minY;y<maxY;y++)
		{
			tmp.Format("%.3f\t",vals[x][y]);
			txt+=tmp;
		}
		txt.Append("\n");
	}
	MessageBox(0,txt.GetBuffer(),title,MB_OK);
}
void OutputMatrix(vector<vector<int>>& vals, const char* title, int minX,int minY, int maxX,int maxY)
{
	if(minX==-1)
		minX=0;
	if(minY==-1)
		minY=0;

	if(maxX==-1)
		maxX=vals.size();
	if(maxY==-1)
		maxY=vals[0].size();

	CString txt,tmp;
	for(int x=minX;x<maxX;x++)
	{
		for(int y=minY;y<maxY;y++)
		{
			tmp.Format("%d\t",vals[x][y]);
			txt+=tmp;
		}
		txt.Append("\n");
	}
	MessageBox(0,txt.GetBuffer(),title,MB_OK);
}
void OutputVector(vector<double> vals, const char* title, int maxElem)
{
	CString txt,tmp;txt.Format("Values: \n");
	int sz=vals.size();if(maxElem>0)sz=maxElem;
	for(int i=0; i<sz;i++)
	{
		tmp.Format("%d: %.5f\n",i,vals[i]);
		txt+=tmp;
	}
	MessageBox(0,txt.GetBuffer(),title,MB_OK);
}
void OutputValVec(int val, vector<int> vals, const char* title)
{
	CString txt,tmp;txt.Format("Value=%d\nValues: \n",val);
	for(int i=0; i<vals.size();i++)
	{
		tmp.Format("%d: %.5f\n",i,vals[i]);
		txt+=tmp;
	}
	MessageBox(0,txt.GetBuffer(),title,MB_OK);
}
void OutputValVec(double val, vector<double> vals, const char* title)
{
	CString txt,tmp;txt.Format("Value=%.3f\nValues: \n",val);
	for(int i=0; i<vals.size();i++)
	{
		tmp.Format("%d: %.5f\n",i,vals[i]);
		txt+=tmp;
	}
	MessageBox(0,txt.GetBuffer(),title,MB_OK);
}
/*END: Global functions*/

//BINARY
MMLibB2D::MMLibB2D(void)
{

}

MMLibB2D::~MMLibB2D(void)
{
	Clean();
}
void MMLibB2D::Clean()
{
	
}
void MMLibB2D::Init()
{
	Clean();

	vector<vector<int>> tstOrg(data.size(),vector<int>(data[0].size()));
	orgData=tstOrg;

	vector<vector<int>> tstTmp(data.size(),vector<int>(data[0].size()));
	tmpData=tstTmp;

	StoreDataToOrgData();
}
void MMLibB2D::SEBoxBinary(int size)
{
	int premer=size*2+1;
	vector<vector<int>> se(premer,vector<int>(premer,1));
	bW=se;
}
//Help Functions
void MMLibB2D::StoreDataToOrgData()
{
	for(int x=0;x<data.size();x++)
		for(int y=0;y<data[0].size();y++)
			orgData[x][y]=data[x][y];
}
void MMLibB2D::StoreDataToTmpData()
{
	for(int x=0;x<data.size();x++)
		for(int y=0;y<data[0].size();y++)
			tmpData[x][y]=data[x][y];
}
void MMLibB2D::StoreOrgDataToData()
{
	for(int x=0;x<data.size();x++)
		for(int y=0;y<data[0].size();y++)
			data[x][y]=orgData[x][y];
}
void MMLibB2D::StoreTmpDataToData()
{
	for(int x=0;x<data.size();x++)
		for(int y=0;y<data[0].size();y++)
			data[x][y]=tmpData[x][y];
}


// Basic MM Operators
void MMLibB2D::bDilate()
{
	int winSize=bW.size()/2;
	for(int x=0; x<data.size(); x++)
	{
		for(int y=0; y<data[0].size(); y++)
		{
			tmpData[x][y]=data[x][y];
			
			for(int _x=0;_x<bW.size();_x++)
			{
				for(int _y=0;_y<bW[0].size();_y++)
				{
					int cX=x-winSize+_x;
					int cY=y-winSize+_y;

					if(!bW[_x][_y] || cX<0 || cX>=data.size() || cY<0 || cY>=data[0].size())
						continue;

					tmpData[x][y]=max(tmpData[x][y], data[cX][cY]);
				}
			}
		}
	}

	StoreTmpDataToData();	
}
void MMLibB2D::bErode()
{
	int winSize=bW.size()/2;
	for(int x=0; x<data.size(); x++)
	{
		for(int y=0; y<data[0].size(); y++)
		{
			tmpData[x][y]=data[x][y];
			if(!tmpData[x][y])
				continue;

			for(int _x=0;_x<bW.size();_x++)
			{
				for(int _y=0;_y<bW[0].size();_y++)
				{
					int cX=x-winSize+_x;
					int cY=y-winSize+_y;

					if(!bW[_x][_y] || cX<0 || cX>=data.size() || cY<0 || cY>=data[0].size())
						continue;
					
					tmpData[x][y]=min(tmpData[x][y], data[cX][cY]);
				}
			}
		}
	}

	StoreTmpDataToData();
}
void MMLibB2D::bOpen()
{
	bErode();
	bDilate();
}
void MMLibB2D::bClose()
{
	bDilate();
	bErode();
}

void MMLibB2D::FastErode3()
{
	int maxx=data.size()-1;
	int maxy=data[0].size()-1;
	
	for(int x=0; x<=maxx; x++)
	{
		tmpData[x][0]=min(data[x][0],data[x][1]);
		
		int* beg = &(data[x][0]);
		int* end = &(data[x][maxy-1]);
		int *output = &tmpData[x][1];

		for(int y=1; beg != end; ++output, ++beg,y++)
		{
			*output = min(min(*beg,*(beg+1)),*(beg+2));
		}
		

		tmpData[x][maxy]=min(data[x][maxy-1],data[x][maxy]);
	}


	for(int x=0; x<=maxx; x++)
	{
		
		int* row2 = &(tmpData[x][0]);
		int* row1 = x != 0 ? &(tmpData[x-1][0]) : row2;
		int* row3 = x < maxx ? &(tmpData[x+1][0]) : row2;
		int *output = &data[x][0];


		for(int y=0; y<=maxy; y++, ++row1, ++row2, ++row3, ++output)
		{
			*output =min(*row1,min(*row2,*row3));
		}
	}

}
void MMLibB2D::FastErodeC3()
{
	int maxx=data.size()-1;
	int maxy=data[0].size()-1;
	
	for(int x=0; x<=maxx; x++)
	{
		tmpData[x][0]=min(data[x][0],data[x][1]);
		
		int* beg = &(data[x][0]);
		int* end = &(data[x][maxy-1]);
		int *output = &tmpData[x][1];

		for(int y=1; beg != end; ++output, ++beg,y++)
		{
			*output = *min_element(beg, beg+3);
		}
		tmpData[x][maxy]=min(data[x][maxy-1],data[x][maxy]);
	}


	for(int x=0; x<=maxx; x++)
	{
		
		int* row2 = &(tmpData[x][0]);
		int* row1 = x != 0 ? &(data[x-1][0]) : row2;
		int* row3 = x < maxx ? &(data[x+1][0]) : row2;
		int *output = &tmpData[x][0];


		for(int y=0; y<=maxy; y++, ++row1, ++row2, ++row3, ++output)
		{
			*output =min(*row1,min(*row2,*row3));
		}
	}
	data=tmpData;
}
void MMLibB2D::FastDilate3()
{
	int maxx=data.size()-1;
	int maxy=data[0].size()-1;
	
	for(int x=0; x<=maxx; x++)
	{
		tmpData[x][0]=max(data[x][0],data[x][1]);
		
		int* beg = &(data[x][0]);
		int* end = &(data[x][maxy-1]);
		int *output = &tmpData[x][1];

		for(int y=1; beg != end; ++output, ++beg,y++)
		{
			*output = *max_element(beg, beg+3);
		}
		

		tmpData[x][maxy]=max(data[x][maxy-1],data[x][maxy]);
	}


	for(int x=0; x<=maxx; x++)
	{
		
		int* row2 = &(tmpData[x][0]);
		int* row1 = x != 0 ? &(tmpData[x-1][0]) : row2;
		int* row3 = x < maxx ? &(tmpData[x+1][0]) : row2;
		int *output = &data[x][0];


		for(int y=0; y<=maxy; y++, ++row1, ++row2, ++row3, ++output)
		{
			*output =max(*row1,max(*row2,*row3));
		}
	}
}
void MMLibB2D::FastDilateC3()
{
	int maxx=data.size()-1;
	int maxy=data[0].size()-1;
	
	for(int x=0; x<=maxx; x++)
	{
		tmpData[x][0]=max(data[x][0],data[x][1]);
		
		int* beg = &(data[x][0]);
		int* end = &(data[x][maxy-1]);
		int *output = &tmpData[x][1];

		for(int y=1; beg != end; ++output, ++beg,y++)
		{
			*output = *max_element(beg, beg+3);
		}
		

		tmpData[x][maxy]=max(data[x][maxy-1],data[x][maxy]);
	}


	for(int x=0; x<=maxx; x++)
	{
		
		int* row2 = &(tmpData[x][0]);
		int* row1 = x != 0 ? &(data[x-1][0]) : row2;
		int* row3 = x < maxx ? &(data[x+1][0]) : row2;
		int *output = &tmpData[x][0];


		for(int y=0; y<=maxy; y++, ++row1, ++row2, ++row3, ++output)
		{
			*output =max(*row1,max(*row2,*row3));
		}
	}
	data=tmpData;
}
void MMLibB2D::FastErode(int wSize)
{
	for(int i=0;i<wSize;i++)
		FastErode3();
}
void MMLibB2D::FastErodeCross(int wSize)
{
	for(int i=0;i<wSize;i++)
		FastErodeC3();
}
void MMLibB2D::FastErodeOct(int wSize)
{
	for(int i=0;i<wSize;i++)
	{
		if(i%2)	FastErode3();
		else FastErodeC3();
	}
}
void MMLibB2D::FastDilate(int wSize)
{
	for(int i=0;i<wSize;i++)
		FastDilate3();
}
void MMLibB2D::FastDilateCross(int wSize)
{
	for(int i=0;i<wSize;i++)
		FastDilateC3();
}
void MMLibB2D::FastDilateOct(int wSize)
{
	int wSize2=(int)((double)wSize/2.0+0.5);

	for(int i=0;i<wSize2;i++)
		FastDilateC3();
	for(int i=wSize2;i<wSize;i++)
		FastDilate3();
}

void MMLibB2D::FastOpen(int wSize)
{
	FastErode(wSize);
	FastDilate(wSize);
}
void MMLibB2D::FastClose(int wSize)
{
	FastDilate(wSize);
	FastErode(wSize);
}
void MMLibB2D::FastOpenCross(int wSize)
{
	FastErodeCross(wSize);
	FastDilateCross(wSize);
}
void MMLibB2D::FastCloseCross(int wSize)
{
	FastDilateCross(wSize);
	FastErodeCross(wSize);
}
void MMLibB2D::FastOpenOct(int wSize)
{
	FastErodeOct(wSize);
	FastDilateOct(wSize);
}
void MMLibB2D::FastCloseOct(int wSize)
{
	FastDilateOct(wSize);
	FastErodeOct(wSize);
}
//Connected operators
void MMLibB2D::AreaOpening(int aTh)
{
	
	CFloodFill ff;
	vector<vector<int>> tmp=data;
	int noReg=ff.WRegionColoring(tmp);
	vector<int> hist(noReg,0);
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			hist[tmp[x][y]]++;
		}
	}
	
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(hist[tmp[x][y]] < aTh)
				data[x][y]=0;
		}
	}
}
void MMLibB2D::AreaClosing(int aTh)
{
	CFloodFill ff;
	vector<vector<int>> tmp=data;
	int noReg=ff.BRegionColoring(tmp);
	vector<int> hist(noReg,0);
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			hist[tmp[x][y]]++;
		}
	}
	
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(hist[tmp[x][y]] < aTh)
				data[x][y]=1;
		}
	}
}
void MMLibB2D::ShapeSizeOpening(double shapeTh, double sizeTh)
{
	vector<vector<int>> colData = data;
	vector<vector<int>> dMap = data;
	
	CFloodFill ff;
	int noReg=ff.WRegionColoring(colData);
	
	MMLibB2D mmb;
	mmb.data=data;mmb.Init();
	mmb.bDT(dMap);

	//Attribute estimation
	vector<int> maxSize(noReg,0);
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(!data[x][y])
				continue;
			if(maxSize[colData[x][y]]<dMap[x][y])
				maxSize[colData[x][y]]=dMap[x][y];
		}
	}

	//Threshold regions
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(!data[x][y])
				continue;
			if(maxSize[colData[x][y]]<=sizeTh)
				data[x][y]=0;
		}
	}
}
void MMLibB2D::AttributeOpening(vector<vector<double>> &attributeImg, double aTh)
{
	CFloodFill ff; 
	vector<vector<int>> colData = data;
	int noReg=ff.WRegionColoring(colData);
	
	//Attribute estimation
	vector<double> attributeVal(noReg,0);
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(!data[x][y])
				continue;
			attributeVal[colData[x][y]]+=attributeImg[x][y];
		}
	}
	
	//Threshold regions
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(!data[x][y])
				continue;
			if(attributeVal[colData[x][y]]<aTh)
				data[x][y]=0;
		}
	}
}
void MMLibB2D::AttributeOpening(vector<vector<int>> &attributeImg, int aTh)
{
	CFloodFill ff; 
	vector<vector<int>> colData = data;
	int noReg=ff.WRegionColoring(colData);
	
	//Attribute estimation
	vector<double> attributeVal(noReg,0);
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(!data[x][y])
				continue;
			attributeVal[colData[x][y]]+=attributeImg[x][y];
		}
	}
	
	//Threshold regions
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(!data[x][y])
				continue;
			if(attributeVal[colData[x][y]]<aTh)
				data[x][y]=0;
		}
	}
}
void MMLibB2D::AvgAttributeOpening(vector<vector<double>> &attributeImg, double aTh)
{
	CFloodFill ff; 
	vector<vector<int>> colData = data;
	int noReg=ff.WRegionColoring(colData);
	
	//Attribute estimation
	vector<double> attributeVal(noReg,0);
	vector<int> areaVal(noReg,0);
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(!data[x][y])
				continue;
			attributeVal[colData[x][y]]+=attributeImg[x][y];
			areaVal[colData[x][y]]++;
		}
	}
	/*Averaging*/
	for(int i=0;i<noReg;i++)
	{
		if(areaVal[i])
			attributeVal[i]/=(double)areaVal[i];
		else
			attributeVal[i]=0.0;
	}
	/*Averaging*/

	//Threshold regions
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(!data[x][y])
				continue;
			if(attributeVal[colData[x][y]]<aTh)
				data[x][y]=0;
		}
	}
}
//Algorithms
int  MMLibB2D::bHitMiss(int x, int y, vector<vector<int>> &W)
{
	int winSize=W.size()/2;

	for(int _x=0;_x<W.size();_x++)
	{
		for(int _y=0;_y<W[0].size();_y++)
		{
			if(W[_x][_y]==2)
				continue; // don't care
			
			int i=x+_x-winSize;
			int j=y+_y-winSize;

			if(i<0 || i>=data.size()-1)
				return 0;
			if(j<0 || j>=data[0].size()-1)
				return 0;

			if(W[_x][_y]!=data[i][j])
				return 0;
		}
	}
	return 1;
}
void MMLibB2D::bThining()
{
	vector<vector<vector<int>>> W(8,vector<vector<int>>(3,vector<int>(3)));

	W[0][0][0]=0;	W[0][1][0]=0;	W[0][2][0]=0;
	W[0][0][1]=2;	W[0][1][1]=1;	W[0][2][1]=2;
	W[0][0][2]=1;	W[0][1][2]=1;	W[0][2][2]=1;

	W[1][0][0]=2;	W[1][1][0]=0;	W[1][2][0]=0;
	W[1][0][1]=1;	W[1][1][1]=1;	W[1][2][1]=0;
	W[1][0][2]=1;	W[1][1][2]=1;	W[1][2][2]=2;

	W[2][0][0]=1;	W[2][1][0]=2;	W[2][2][0]=0;
	W[2][0][1]=1;	W[2][1][1]=1;	W[2][2][1]=0;
	W[2][0][2]=1;	W[2][1][2]=2;	W[2][2][2]=0;

	W[3][0][0]=1;	W[3][1][0]=1;	W[3][2][0]=2;
	W[3][0][1]=1;	W[3][1][1]=1;	W[3][2][1]=0;
	W[3][0][2]=2;	W[3][1][2]=0;	W[3][2][2]=0;

	W[4][0][0]=1;	W[4][1][0]=1;	W[4][2][0]=1;
	W[4][0][1]=2;	W[4][1][1]=1;	W[4][2][1]=2;
	W[4][0][2]=0;	W[4][1][2]=0;	W[4][2][2]=0;

	W[5][0][0]=2;	W[5][1][0]=1;	W[5][2][0]=1;
	W[5][0][1]=0;	W[5][1][1]=1;	W[5][2][1]=1;
	W[5][0][2]=0;	W[5][1][2]=0;	W[5][2][2]=2;

	
	W[6][0][0]=0;	W[6][1][0]=2;	W[6][2][0]=1;
	W[6][0][1]=0;	W[6][1][1]=1;	W[6][2][1]=1;
	W[6][0][2]=0;	W[6][1][2]=2;	W[6][2][2]=1;

	W[7][0][0]=0;	W[7][1][0]=0;	W[7][2][0]=2;
	W[7][0][1]=0;	W[7][1][1]=1;	W[7][2][1]=1;
	W[7][0][2]=2;	W[7][1][2]=1;	W[7][2][2]=1;

	int noRem=1;
	while(noRem)
	{
		noRem=0;
		for(int x=0; x<data.size(); x++)
			for(int y=0; y<data[0].size(); y++)
				tmpData[x][y]=0;

		for(int w=0;w<8;w++)
		{
			for(int x=0; x<data.size(); x++)
			{
				for(int y=0; y<data[0].size(); y++)
				{
					if(!data[x][y] || tmpData[x][y])
						continue;
					tmpData[x][y]=bHitMiss(x,y,W[w]);
				}
			}
			for(int x=0; x<data.size(); x++)
			{
				for(int y=0; y<data[0].size(); y++)
				{
					if(tmpData[x][y])
					{
						tmpData[x][y]=0;
						data[x][y]=0;
						noRem++;
					}
				}
			}
		}
	}
}
void MMLibB2D::DetectInternalEdge()
{
	tmpData=data;
	SEBoxBinary(1);
	bErode();
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(!data[x][y] && orgData[x][y])
				data[x][y]=1;
			else
				data[x][y]=0;
		}
	}
}
void MMLibB2D::DetectExternalEdge()
{
	tmpData=data;
	SEBoxBinary(1);
	bDilate();
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(data[x][y] && !orgData[x][y])
				data[x][y]=1;
			else
				data[x][y]=0;
		}
	}	
}
void MMLibB2D::bDT(vector<vector<int>> &dMap)
{
	InitData(dMap,0);
	queue<POINT> fifo;

	/*START: Init - find regions boundary elements*/
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(!data[x][y])
				continue;
			
			int sx=max(0,x-1);
			int ex=min(data.size()-1,x+1);
			int sy=max(0,y-1);
			int ey=min(data[0].size()-1,y+1);
			
			bool isB=false;
			for(int _x=sx;_x<=ex;_x++)
			{
				for(int _y=sy;_y<=ey;_y++)
				{
					if(!data[_x][_y])
						isB=true;
				}
			}	
			if(isB)
			{
				dMap[x][y]=1;
				POINT pnt={x,y};
				fifo.push(pnt);
			}
		}
	}
	/*END: Init - find regions boundary elements*/

	/*START: dt*/
	while(fifo.size())
	{
		POINT start=fifo.front();
		fifo.pop();

		POINT sosedi[8];
		sosedi[0].x=start.x-1;	sosedi[0].y=start.y-1;
		sosedi[1].x=start.x-1;	sosedi[1].y=start.y;
		sosedi[2].x=start.x-1;	sosedi[2].y=start.y+1;
		sosedi[3].x=start.x;	sosedi[3].y=start.y+1;
		sosedi[4].x=start.x+1;	sosedi[4].y=start.y+1;
		sosedi[5].x=start.x+1;	sosedi[5].y=start.y;
		sosedi[6].x=start.x+1;	sosedi[6].y=start.y-1;
		sosedi[7].x=start.x;	sosedi[7].y=start.y-1;

		for(int i=0;i<8;i++)
		{
			if( sosedi[i].x>=0 && sosedi[i].x<data.size() && 
				sosedi[i].y>=0 && sosedi[i].y<data[0].size())
			{
					if(	sosedi[i].x == 308 && 	sosedi[i].y == 585)
						int dm=0;
				if(!dMap[sosedi[i].x][sosedi[i].y] && data[sosedi[i].x][sosedi[i].y])
				{
					dMap[sosedi[i].x][sosedi[i].y]=dMap[start.x][start.y]+1;
					fifo.push(sosedi[i]);
				}
			}
		}
	}
	/*END: dt*/
}


void MMLibB2D::SphericityOpening(vector<vector<int>> &bin_img, double th) {
	vector<vector<int>> tmpData=bin_img;
	vector<vector<int>> dMap(bin_img.size(),vector<int>(bin_img[0].size(),0));
	vector<vector<bool>> data_boundary(bin_img.size(),vector<bool>(bin_img[0].size(),0));

	data=tmpData;
	Init();
	bDT(dMap);

	CFloodFill ff;
	int noRegs=ff.WRegionColoring(tmpData);

	vector<int> num_cells(noRegs, 0);
	vector<int> num_boundary_cells(noRegs, 0);

	for(int x=0;x<bin_img.size(); x++)
		for(int y=0;y<bin_img[0].size(); y++) {

			num_cells[tmpData[x][y]]++;

			if(dMap[x][y]==1)
				for(int ii=max(0, x-1);ii<=min(bin_img.size()-1, x+1);ii++)
					for(int jj=max(0, y-1);jj<=min(bin_img[0].size()-1, y+1);jj++)
						if(tmpData[ii][jj]==0 && data_boundary[ii][jj]==0) {
							data_boundary[x][y]=1;
							num_boundary_cells[tmpData[x][y]]++;
						}		
		}

		vector<double> regAtt_compactness(noRegs, 0);

		vector<double> st_lukenj(noRegs, 0);

		for(unsigned int r=0;r<noRegs;r++)
			regAtt_compactness[r]= 1.46459188763 * 6 * pow(num_cells[r], 0.6666666)/num_boundary_cells[r];

		for(int x=0;x<bin_img.size(); x++)
			for(int y=0;y<bin_img[0].size(); y++) 
				if(regAtt_compactness[tmpData[x][y]] < th) bin_img[x][y]=0;

}
void MMLibB2D::AreaOpening(vector<vector<int>> &bin_img, int th)
{
	vector<vector<int>> tmpData=bin_img;
	CFloodFill ff;
	int noRegs=ff.WRegionColoring(tmpData);
	
	vector<int> num_cells(noRegs, 0);
	for(int x=0;x<bin_img.size(); x++)
	{
		for(int y=0;y<bin_img[0].size(); y++) 
		{
			num_cells[tmpData[x][y]]++;
		}
	}
	for(int x=0;x<bin_img.size(); x++)
	{
		for(int y=0;y<bin_img[0].size(); y++) 
		{
			num_cells[tmpData[x][y]]++;
		}
	}

	for(int x=0;x<bin_img.size(); x++)
	{
		for(int y=0;y<bin_img[0].size(); y++) 
		{
			if(num_cells[tmpData[x][y]]<th)
				bin_img[x][y]=0;
		}
	}
}
void MMLibB2D::CompactnessOpening(double th) 
{
	vector<vector<int>> dMap(data.size(),vector<int>(data[0].size(),0));
	vector<vector<int>> rMap=data;

	MMLibB2D mmb;
	mmb.data=data;mmb.Init();
	mmb.bDT(dMap);

	CFloodFill ff;
	int noReg=ff.WRegionColoring(rMap);

	//Attribute estimation
	vector<double> avgDist(noReg,0);
	vector<double> attr(noReg,0);
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(!data[x][y])
				continue;
			attr[rMap[x][y]]++;
			avgDist[rMap[x][y]]+=dMap[x][y];
		}
	}
	//Compateness estimation
	for(int i=1;i<noReg;i++)
	{
		if(attr[i]<1.0)
			continue;
		avgDist[i]/=attr[i];
		attr[i]/=(9.0*PI*avgDist[i]*avgDist[i]);
	}
	
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(!data[x][y])
				continue;
			else if(attr[rMap[x][y]]<th)
				data[x][y]=0;
		}
	}
}
void MMLibB2D::DispersionOpening(vector<vector<int>> &bin_img, double th)
{
	vector<vector<int>> tmpData=bin_img;
	vector<vector<int>> dMap(bin_img.size(),vector<int>(bin_img[0].size(),0));
	vector<vector<bool>> data_boundary(bin_img.size(),vector<bool>(bin_img[0].size(),0));

	data=tmpData;
	Init();
	bDT(dMap);

	CFloodFill ff;
	int noRegs=ff.WRegionColoring(tmpData);

	vector<int> num_cells(noRegs, 0);
	vector<int> num_boundary_cells(noRegs, 0);

	vector<Vector2f> avgPoint(noRegs,Vector2f(0.0,0.0));
	vector<int> noPoints(noRegs);
	for(int x=0;x<bin_img.size(); x++)
	{
		for(int y=0;y<bin_img[0].size(); y++)
		{
			noPoints[tmpData[x][y]]++;
			avgPoint[tmpData[x][y]].x+=x;
			avgPoint[tmpData[x][y]].y+=y;
		}		
	}
	for(int i=0;i<noRegs;i++)
	{
		avgPoint[i].x=(double)avgPoint[i].x/(double)noPoints[i];
		avgPoint[i].y=(double)avgPoint[i].y/(double)noPoints[i];
	}

	vector<double> regAtt(noRegs, 0.0);
	for(int x=0;x<bin_img.size(); x++)
	{
		for(int y=0;y<bin_img[0].size(); y++)
		{
			double xDiff=(double)x-avgPoint[tmpData[x][y]].x;
			double yDiff=(double)y-avgPoint[tmpData[x][y]].y;
			double dVal=PI*(xDiff*xDiff+yDiff*yDiff)/(double)noPoints[tmpData[x][y]];
			if(regAtt[tmpData[x][y]]<dVal)
				regAtt[tmpData[x][y]]=dVal;
		}		
	}
	
	for(int x=0;x<bin_img.size(); x++)
	{
		for(int y=0;y<bin_img[0].size(); y++)
		{
			if(regAtt[tmpData[x][y]]<th)
				bin_img[x][y]=0;
		}
	}
}
void MMLibB2D::CountNumHoles(vector<vector<int>> &bin_img, int th) {
	vector<vector<int>> bin_img_f=bin_img;
	vector<vector<int>> bin_img_f_inv=bin_img;

	CFloodFill ff;
	int noRegs=ff.WRegionColoring(bin_img_f);

	for(int x=0;x<bin_img.size(); x++)
		for(int y=0;y<bin_img[0].size(); y++) {
			if(bin_img_f[x][y]>0) bin_img_f_inv[x][y]=0;
			else bin_img_f_inv[x][y]=1;
		}

		int noRegs_inv=ff.WRegionColoring(bin_img_f_inv);

		vector<int> holes_num_neigbhours(noRegs_inv, -1);

		for(int x=0;x<bin_img.size(); x++)
			for(int y=0;y<bin_img[0].size(); y++)
				if(bin_img_f_inv[x][y]>0 && holes_num_neigbhours[bin_img_f_inv[x][y]]!=-2)
					for(int ii=max(0, x-1);ii<=min(bin_img.size()-1, x+1);ii++)
						for(int jj=max(0, y-1);jj<=min(bin_img[0].size()-1, y+1);jj++)
							if(bin_img_f[x][y]!=bin_img_f[ii][jj] && bin_img_f[ii][jj]!=0) {
								if(holes_num_neigbhours[bin_img_f_inv[x][y]]>-1 && holes_num_neigbhours[bin_img_f_inv[x][y]]!=bin_img_f[ii][jj]) holes_num_neigbhours[bin_img_f_inv[x][y]]=-2; // vec kot 2 soseda
								else holes_num_neigbhours[bin_img_f_inv[x][y]]=bin_img_f[ii][jj];
								break;
							}

							vector<int> num_holes(noRegs, 0);

							for(unsigned int r=0;r<noRegs_inv;r++) {
								if(holes_num_neigbhours[r]>-1) {
									num_holes[holes_num_neigbhours[r]]++;
								}
							}

							for(int x=0;x<bin_img.size(); x++)
								for(int y=0;y<bin_img[0].size(); y++)
									if(num_holes[bin_img_f[x][y]]>th) bin_img[x][y]=0;
}


//GREY
MMLibG2D::MMLibG2D(void)
{

}

MMLibG2D::~MMLibG2D(void)
{
	Clean();
}
void MMLibG2D::Clean()
{
	
}
void MMLibG2D::Init()
{
	Clean();

	orgData=data;

	tmpData=data;
}
void MMLibG2D::SEDiscBinary(int size)
{
	int premer=size*2+1;
	vector<vector<int>> se(premer,vector<int>(premer,0));
	bW=se;

	for(int x=0;x<premer;x++)
	{
		for(int y=0;y<premer;y++)
		{
			int xDist=x-size;
			int yDist=y-size;
			float dist=sqrt((float)(xDist*xDist+yDist*yDist));
			if(dist<size+0.5)
				bW[x][y]=1;
		}
	}
}
void MMLibG2D::SEBoxBinary(int size)
{
	int premer=size*2+1;
	vector<vector<int>> se(premer,vector<int>(premer,1));
	bW=se;
}
//Help Functions
void MMLibG2D::StoreDataToOrgData()
{
	for(int x=0;x<data.size();x++)
		for(int y=0;y<data[0].size();y++)
			orgData[x][y]=data[x][y];
}
void MMLibG2D::StoreDataToTmpData()
{
	for(int x=0;x<data.size();x++)
		for(int y=0;y<data[0].size();y++)
			tmpData[x][y]=data[x][y];
}
void MMLibG2D::StoreOrgDataToData()
{
	for(int x=0;x<data.size();x++)
		for(int y=0;y<data[0].size();y++)
			data[x][y]=orgData[x][y];
}
void MMLibG2D::StoreTmpDataToData()
{
	for(int x=0;x<data.size();x++)
		for(int y=0;y<data[0].size();y++)
			data[x][y]=tmpData[x][y];
}
int MMLibG2D::FindElement(vector<int>& values, int element)
{
	for(int i=0;i<values.size();i++)
		if(values[i]==element)
			return i;
	return -1;
}
void MMLibG2D::SwapElements(vector<int>& values, int i, int j)
{
	if(j<0)
		j=values.size()-1;
	int tmp=values[i];
	values[i]=values[j];
	values[j]=tmp;
}
void MMLibG2D::SwapElements(vector<double>& values, int i, int j)
{
	if(j<0)
		j=values.size()-1;
	int tmp=values[i];
	values[i]=values[j];
	values[j]=tmp;
}

POINT MMLibG2D::GetRegionNeighbour(vector<vector<int>>& wsRegions, int x, int y)
{
	POINT sosed={-1,-1};
	
	int sx=max(0,x-1);
	int ex=min(wsRegions.size()-1,x+1);
	int sy=max(0,y-1);
	int ey=min(wsRegions[0].size()-1,y+1);
	
	for(int _x=sx;_x<=ex;_x++)
	{
		for(int _y=sy;_y<=ey;_y++)
		{
			if(wsRegions[x][y]!=wsRegions[_x][_y])
			{
				sosed.x=_x;
				sosed.y=_y;
				return sosed;
			}
		}
	}	
	return sosed;
}
void MMLibG2D::GetRegionalMaxima(vector<vector<int>>& maxMap)
{
	MMLibG2D mmg;
	mmg.data=data;
	mmg.Init();
	mmg.OpeningByContrastReconstruction(1.0);

	for(int x=0; x<maxMap.size();x++)
	{
		for(int y=0; y<maxMap[0].size();y++)
		{
			if(data[x][y]-mmg.data[x][y]==1.0)
				maxMap[x][y]=1;
			else
				maxMap[x][y]=0;
		}
	}
}
// Basic MM Operators
void MMLibG2D::bDilate()
{
	int winSize=bW.size()/2;
	for(int x=0; x<data.size(); x++)
	{
		for(int y=0; y<data[0].size(); y++)
		{
			tmpData[x][y]=data[x][y];

			for(int _x=0;_x<bW.size();_x++)
			{
				for(int _y=0;_y<bW[0].size();_y++)
				{
					int cX=x-winSize+_x;
					int cY=y-winSize+_y;

					if(!bW[_x][_y] || cX<0 || cX>=data.size() || cY<0 || cY>=data[0].size())
						continue;

					tmpData[x][y]=max(tmpData[x][y], data[cX][cY]);
				}
			}
		}
	}

	data=tmpData;	
}
void MMLibG2D::bErode()
{
	int winSize=bW.size()/2;
	for(int x=0; x<data.size(); x++)
	{
		for(int y=0; y<data[0].size(); y++)
		{
			tmpData[x][y]=data[x][y];

			for(int _x=0;_x<bW.size();_x++)
			{
				for(int _y=0;_y<bW[0].size();_y++)
				{
					int cX=x-winSize+_x;
					int cY=y-winSize+_y;

					if(!bW[_x][_y] || cX<0 || cX>=data.size() || cY<0 || cY>=data[0].size())
						continue;

					tmpData[x][y]=min(tmpData[x][y], data[cX][cY]);
				}
			}
		}
	}

	data=tmpData;
}
void MMLibG2D::FastErode3()
{
	int maxx=data.size()-1;
	int maxy=data[0].size()-1;
	
	for(int x=0; x<=maxx; x++)
	{
		tmpData[x][0]=min(data[x][0],data[x][1]);
		
		double* beg = &(data[x][0]);
		double* end = &(data[x][maxy-1]);
		double *output = &tmpData[x][1];

		for(int y=1; beg != end; ++output, ++beg,y++)
		{
			*output = min(min(*beg,*(beg+1)),*(beg+2));
		}
		

		tmpData[x][maxy]=min(data[x][maxy-1],data[x][maxy]);
	}


	for(int x=0; x<=maxx; x++)
	{
		
		double* row2 = &(tmpData[x][0]);
		double* row1 = x != 0 ? &(tmpData[x-1][0]) : row2;
		double* row3 = x < maxx ? &(tmpData[x+1][0]) : row2;
		double *output = &data[x][0];


		for(int y=0; y<=maxy; y++, ++row1, ++row2, ++row3, ++output)
		{
			*output =min(*row1,min(*row2,*row3));
		}
	}

}
void MMLibG2D::FastErodeC3()
{
	int maxx=data.size()-1;
	int maxy=data[0].size()-1;
	
	for(int x=0; x<=maxx; x++)
	{
		tmpData[x][0]=min(data[x][0],data[x][1]);
		
		double* beg = &(data[x][0]);
		double* end = &(data[x][maxy-1]);
		double *output = &tmpData[x][1];

		for(int y=1; beg != end; ++output, ++beg,y++)
		{
			*output = *min_element(beg, beg+3);
		}
		tmpData[x][maxy]=min(data[x][maxy-1],data[x][maxy]);
	}


	for(int x=0; x<=maxx; x++)
	{
		
		double* row2 = &(tmpData[x][0]);
		double* row1 = x != 0 ? &(data[x-1][0]) : row2;
		double* row3 = x < maxx ? &(data[x+1][0]) : row2;
		double *output = &tmpData[x][0];


		for(int y=0; y<=maxy; y++, ++row1, ++row2, ++row3, ++output)
		{
			*output =min(*row1,min(*row2,*row3));
		}
	}
	data=tmpData;
}
void MMLibG2D::FastDilate3()
{
	int maxx=data.size()-1;
	int maxy=data[0].size()-1;
	
	for(int x=0; x<=maxx; x++)
	{
		tmpData[x][0]=max(data[x][0],data[x][1]);
		
		double* beg = &(data[x][0]);
		double* end = &(data[x][maxy-1]);
		double *output = &tmpData[x][1];

		for(int y=1; beg != end; ++output, ++beg,y++)
		{
			*output = *max_element(beg, beg+3);
		}
		

		tmpData[x][maxy]=max(data[x][maxy-1],data[x][maxy]);
	}


	for(int x=0; x<=maxx; x++)
	{
		
		double* row2 = &(tmpData[x][0]);
		double* row1 = x != 0 ? &(tmpData[x-1][0]) : row2;
		double* row3 = x < maxx ? &(tmpData[x+1][0]) : row2;
		double *output = &data[x][0];


		for(int y=0; y<=maxy; y++, ++row1, ++row2, ++row3, ++output)
		{
			*output =max(*row1,max(*row2,*row3));
		}
	}
}
void MMLibG2D::FastDilateC3()
{
	int maxx=data.size()-1;
	int maxy=data[0].size()-1;
	
	for(int x=0; x<=maxx; x++)
	{
		tmpData[x][0]=max(data[x][0],data[x][1]);
		
		double* beg = &(data[x][0]);
		double* end = &(data[x][maxy-1]);
		double *output = &tmpData[x][1];

		for(int y=1; beg != end; ++output, ++beg,y++)
		{
			*output = *max_element(beg, beg+3);
		}
		

		tmpData[x][maxy]=max(data[x][maxy-1],data[x][maxy]);
	}


	for(int x=0; x<=maxx; x++)
	{
		
		double* row2 = &(tmpData[x][0]);
		double* row1 = x != 0 ? &(data[x-1][0]) : row2;
		double* row3 = x < maxx ? &(data[x+1][0]) : row2;
		double *output = &tmpData[x][0];


		for(int y=0; y<=maxy; y++, ++row1, ++row2, ++row3, ++output)
		{
			*output =max(*row1,max(*row2,*row3));
		}
	}
	data=tmpData;
}
void MMLibG2D::FastErode(int wSize)
{
	for(int i=0;i<wSize;i++)
		FastErode3();
}
void MMLibG2D::FastErodeCross(int wSize)
{
	for(int i=0;i<wSize;i++)
		FastErodeC3();
}
void MMLibG2D::FastErodeOct(int wSize)
{
	for(int i=0;i<wSize;i++)
	{
		if(i%2)	FastErode3();
		else FastErodeC3();
	}
}
void MMLibG2D::FastDilate(int wSize)
{
	for(int i=0;i<wSize;i++)
		FastDilate3();
}
void MMLibG2D::FastDilateCross(int wSize)
{
	for(int i=0;i<wSize;i++)
		FastDilateC3();
}
void MMLibG2D::FastDilateOct(int wSize)
{
	int wSize2=(int)((double)wSize/2.0+0.5);

	for(int i=0;i<wSize2;i++)
		FastDilateC3();
	for(int i=wSize2;i<wSize;i++)
		FastDilate3();
}
void MMLibG2D::bOpen()
{
	bErode();
	bDilate();
}
void MMLibG2D::bClose()
{
	bDilate();
	bErode();
}
void MMLibG2D::FastOpen(int wSize)
{
	FastErode(wSize);
	FastDilate(wSize);
}
void MMLibG2D::FastClose(int wSize)
{
	FastDilate(wSize);
	FastErode(wSize);
}
void MMLibG2D::FastLevelingOpen(int wSize)
{
	for(int w=wSize;w>0;w--)
	{
		FastOpen(w);
		FastClose(w);
	}
}
void MMLibG2D::FastLevelingClose(int wSize)
{
	for(int w=wSize;w>0;w--)
	{
		FastClose(w);
		FastOpen(w);
	}
}
void MMLibG2D::FastOpenCross(int wSize)
{
	FastErodeCross(wSize);
	FastDilateCross(wSize);
}
void MMLibG2D::FastCloseCross(int wSize)
{
	FastDilateCross(wSize);
	FastErodeCross(wSize);
}
void MMLibG2D::FastOpenOct(int wSize)
{
	FastErodeOct(wSize);
	FastDilateOct(wSize);
}
void MMLibG2D::FastCloseOct(int wSize)
{
	FastDilateOct(wSize);
	FastErodeOct(wSize);
}
void MMLibG2D::WTopHat()
{
	orgData=data;
	bOpen();
	for(int x=0;x<data.size();x++)
		for(int y=0;y<data[0].size();y++)
			data[x][y]=orgData[x][y]-data[x][y];
}
void MMLibG2D::BTopHat()
{
	orgData=data;
	bClose();
	for(int x=0;x<data.size();x++)
		for(int y=0;y<data[0].size();y++)
			data[x][y]=data[x][y]-orgData[x][y];
}

void MMLibG2D::BlurMinimumEdge()
{
	vector<vector<double>> erodeData;
	vector<vector<double>> openData;
	vector<vector<double>> dilateData;
	vector<vector<double>> closeData;

	/*Erode and Open*/
	bErode();
	erodeData=data;

	bDilate();
	openData=data;

	/*Dilate and Close*/
	data=orgData;

	bDilate();
	dilateData=data;

	bErode();
	closeData=data;
	
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			data[x][y]=min(openData[x][y]-erodeData[x][y] , dilateData[x][y]-closeData[x][y]);
		}
	}
}
//Advance MM
void MMLibG2D::UltimateOpening(vector<vector<double>>& rData,vector<vector<int>>& sData, int maxSize)
{
	for(int x=0;x<rData.size();x++)
		for(int y=0;y<rData[0].size();y++)
			rData[x][y]=0;
	vector<vector<double>> tData=orgData;

	for(int wSize=1;wSize<=maxSize;wSize++)
	{
		data=orgData;
		FastOpen(wSize);
		
		for(int x=0;x<rData.size();x++)
		{
			for(int y=0;y<rData[0].size();y++)
			{
				double diff=tData[x][y]-data[x][y];
				if(rData[x][y]<diff)
				{
					rData[x][y]=diff;
					sData[x][y]=wSize;
				}
			}
		}
		tData=data;
	}
}
void MMLibG2D::ErosionOnQDT(vector<vector<int>>& dMap)
{
	vector<vector<double>>	hMap=data;
	for(int x=0;x<dMap.size();x++)
	{
		for(int y=0;y<dMap[0].size();y++)
		{
			int winSize=dMap[x][y]+1;
			int sx=max(0,x-winSize);
			int ex=min(data.size()-winSize,x+winSize);
			int sy=max(0,y-winSize);
			int ey=min(data[0].size()-winSize,y+winSize);

			double minVal=data[x][y];
			for(int _x=sx;_x<=ex;_x++)
				for(int _y=sy;_y<=ey;_y++)
					if(minVal>data[_x][_y])
						minVal=data[_x][_y];
			hMap[x][y]=minVal;
		}
	}
	data=hMap;
}
void MMLibG2D::ErosionOnQDT(vector<vector<int>>& dMap, vector<vector<int>>& controlMap)
{
	vector<vector<double>>	hMap=data;
	for(int x=0;x<dMap.size();x++)
	{
		for(int y=0;y<dMap[0].size();y++)
		{
			hMap[x][y]=data[x][y];
			if(!controlMap[x][y])
				continue;

			int winSize=dMap[x][y]+1;
			int sx=max(0,x-winSize);
			int ex=min(data.size()-winSize,x+winSize);
			int sy=max(0,y-winSize);
			int ey=min(data[0].size()-winSize,y+winSize);

			double minVal=data[x][y];
			for(int _x=sx;_x<=ex;_x++)
				for(int _y=sy;_y<=ey;_y++)
					if(minVal>data[_x][_y])
						minVal=data[_x][_y];
			hMap[x][y]=minVal;
		}
	}
	data=hMap;
}
void MMLibG2D::ReconstructionByDilation(vector<vector<double>>& mask)
{
	CFloodFill ff;
	vector<vector<int>> tmpGrid(mask.size(),vector<int>(mask[0].size(),0));
	vector<PixelEl> queue;
	queue.reserve(mask.size()*mask[0].size());
	/*START: get local maxima*/
		//get connected components
	int noRegs=1;
	for(int x=0;x<mask.size();x++)
	{
		for(int y=0;y<mask[0].size();y++)
		{
			if(!tmpGrid[x][y])
			{
				POINT pnt={x,y};
				ff.GSFloodFill(data,pnt,tmpGrid,noRegs);
				noRegs++;
			}
		}
	}
		//remove non-maxima components
	for(int x=0;x<mask.size();x++)
	{
		for(int y=0;y<mask[0].size();y++)
		{
			if(!tmpGrid[x][y])
				continue;

			int sx=max(0,x-1);
			int ex=min(mask.size()-1,x+1);
			int sy=max(0,y-1);
			int ey=min(mask[0].size()-1,y+1);
			
			bool isH=true;
			for(int _x=sx;_x<=ex;_x++)
			{
				for(int _y=sy;_y<=ey;_y++)
				{
					if(data[_x][_y]>data[x][y])
						isH=false;
				}
			}
			if(!isH)
			{
				POINT pnt={x,y};
				ff.ChangeRegionIndex8(tmpGrid,pnt,0);
			}
		}
	}
	/*END: get local maxima*/
	
	/*START: init queue*/
	for(int x=0;x<mask.size();x++)
	{
		for(int y=0;y<mask[0].size();y++)
		{
			if(!tmpGrid[x][y])
				continue;

			int sx=max(0,x-1);
			int ex=min(mask.size()-1,x+1);
			int sy=max(0,y-1);
			int ey=min(mask[0].size()-1,y+1);
			
			bool isAlone=false;
			for(int _x=sx;_x<=ex;_x++)
			{
				for(int _y=sy;_y<=ey;_y++)
				{
					if(!tmpGrid[_x][_y])
						isAlone=true;
				}
			}
			if(isAlone)
			{
				PixelEl pEl;
				pEl.x=x;
				pEl.y=y;
				pEl.val=data[x][y];
				queue.push_back(pEl);
			}
		}
	}
	/*END: init queue*/
	
	for(int x=0;x<mask.size();x++)
		for(int y=0;y<mask[0].size();y++)
			tmpGrid[x][y]=0;

	make_heap(queue.begin(),queue.end(),myfnS2L);
	while(queue.size())
	{
		PixelEl maxEl=queue.front();		
		
		pop_heap(queue.begin(),queue.end(),myfnS2L); 
		queue.pop_back();
		
		tmpGrid[maxEl.x][maxEl.y]=1;
		
		int sx=max(0,maxEl.x-1);
		int ex=min(mask.size()-1,maxEl.x+1);
		int sy=max(0,maxEl.y-1);
		int ey=min(mask[0].size()-1,maxEl.y+1);
		
		bool isAlone=false;
		for(int _x=sx;_x<=ex;_x++)
		{
			for(int _y=sy;_y<=ey;_y++)
			{
				if(tmpGrid[_x][_y])
					continue;
				if(maxEl.val>data[_x][_y])
					data[_x][_y]=min(maxEl.val,mask[_x][_y]);

				PixelEl newEl;
				newEl.x=_x;
				newEl.y=_y;
				newEl.val=data[_x][_y];

				queue.push_back(newEl);
				push_heap(queue.begin(),queue.end(),myfnS2L);

				tmpGrid[_x][_y]=1;
			}
		}
	}
}
void MMLibG2D::OpeningByReconstruction(int wSize)
{
	FastErode(wSize);
	ReconstructionByDilation(orgData);
}
void MMLibG2D::OpeningByContrastReconstruction(double val)
{
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			data[x][y]-=val;
		}
	}
	tmpData=data;
	ReconstructionByDilation(orgData);
}
void MMLibG2D::ClosingByContrastReconstruction(double val)
{
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			data[x][y]+=val;
		}
	}
	MultiplyData(data,-1.0);
	MultiplyData(orgData,-1.0);
	tmpData=data;
	ReconstructionByDilation(orgData);
	MultiplyData(data,-1.0);
	MultiplyData(orgData,-1.0);
}
void MMLibG2D::ClosingByReconstruction(int wSize)
{
	MultiplyData(data,-1.0);
	MultiplyData(orgData,-1.0);
	OpeningByReconstruction(wSize);
	MultiplyData(data,-1.0);
	MultiplyData(orgData,-1.0);
}
int MMLibG2D::Watershed(vector<vector<int>>& output)
{
	/*START: brišem podatke, ker imam notri shranjeno klasifikacijo low outlierjev*/
	for(int x=0;x<data.size();x++)
		for(int y=0;y<data[0].size();y++)
			output[x][y]=0;
	/*END: brišem podatke, ker imam notri shranjeno klasifikacijo low outlierjev*/

	vector<vector<int>> pMap(output.size(),vector<int>(output[0].size(),0));
	vector<vector<int>> gMap(output.size(),vector<int>(output[0].size(),0));
	vector<vector<int>> tmp(output.size(),vector<int>(output[0].size(),0));
	tmpMap=gMap;
	
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			double minVal=data[x][y];
			gMap[x][y]=GetMinValDirection(x,y,minVal,pMap[x][y]); // doloèim gradient			
		}
	}
	
	/*START: flood fill nad platoji*/
	int noReg=1;
	vector<POINT> innerPoints;innerPoints.reserve(100);
	vector<POINT> outerPoints;outerPoints.reserve(100);
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(gMap[x][y] || output[x][y])
				continue;

			innerPoints.clear();
			outerPoints.clear();
			
			GetInnerOuterLists(x,y,innerPoints,outerPoints,gMap,pMap);

			if(outerPoints.size())
			{//plato, ki ga je potrebno odpraviti
				DilatePoints(outerPoints,gMap,pMap);
			}
			else
			{//Lokalni minumum
				for(int i=0;i<innerPoints.size();i++)
				{
					output[innerPoints[i].x][innerPoints[i].y]=noReg;
				}
				noReg++;
			}
		}
	}
	_Watershed(gMap,output);
	/*END: flood fill nad platoji*/
	return noReg;
}


int MMLibG2D::WatershedOnMarkers(vector<vector<int>>& markerImg, vector<vector<int>>& output)
{
	InvertData(data);
	CDataStatistics stat;
	double minVal=stat.GetMinVal(data);
	double maxVal=stat.GetMaxVal(data);

	MMLibG2D mmg;
	mmg.data=data;
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(markerImg[x][y])
				mmg.data[x][y]=maxVal;
			else
				mmg.data[x][y]=minVal;
		}
	}
	mmg.Init();
	mmg.ReconstructionByDilation(data);
	InvertData(mmg.data);
	mmg.Init();
	
	InvertData(data);
	return mmg.Watershed(output);
}
void MMLibG2D::GetInnerOuterLists(int x, int y, vector<POINT> &innerPoints, vector<POINT> & outerPoints, vector<vector<int>>& gMap, vector<vector<int>> &pMap)
{
	POINT sPoint={x,y};
	candidates.push_back(sPoint);

	POINT sosedi[8];
	while(candidates.size())
	{
		POINT start=candidates.back();
		candidates.pop_back();
		
		tmpMap[start.x][start.y]=1;
		if(gMap[start.x][start.y])
			outerPoints.push_back(start);
		else
			innerPoints.push_back(start);
		
		sosedi[0].x=start.x-1;	sosedi[0].y=start.y-1;
		sosedi[1].x=start.x-1;	sosedi[1].y=start.y;
		sosedi[2].x=start.x-1;	sosedi[2].y=start.y+1;
		sosedi[3].x=start.x;	sosedi[3].y=start.y+1;
		sosedi[4].x=start.x+1;	sosedi[4].y=start.y+1;
		sosedi[5].x=start.x+1;	sosedi[5].y=start.y;
		sosedi[6].x=start.x+1;	sosedi[6].y=start.y-1;
		sosedi[7].x=start.x;	sosedi[7].y=start.y-1;
		
		for(int i=0;i<8;i++)
		{
			if( sosedi[i].x>=0 && sosedi[i].x<data.size() && 
				sosedi[i].y>=0 && sosedi[i].y<data[0].size()&&
				data[start.x][start.y]==data[sosedi[i].x][sosedi[i].y])
			{
				if(!tmpMap[sosedi[i].x][sosedi[i].y])
				{
					tmpMap[sosedi[i].x][sosedi[i].y]=1;
					candidates.push_back(sosedi[i]);
				}
			}
		}
	}
	candidates.clear();
}
void MMLibG2D::DilatePoints(vector<POINT> & outerPoints, vector<vector<int>>& gMap, vector<vector<int>> &pMap)
{
	vector<POINT> tmpPoints=outerPoints;
	POINT sosedi[8];
	while(outerPoints.size())
	{
		tmpPoints=outerPoints;
		outerPoints.clear();
		for(int i=0;i<tmpPoints.size();i++)
		{//grem skozi vse outerpoints in jih razširim... v outerpoints dodam nove razširitve
			
			POINT start=tmpPoints[i];
			int x=start.x;		int y=start.y;

			sosedi[0].x=x-1;	sosedi[0].y=y-1;
			sosedi[1].x=x-1;	sosedi[1].y=y;
			sosedi[2].x=x-1;	sosedi[2].y=y+1;
			sosedi[3].x=x;		sosedi[3].y=y+1;
			sosedi[4].x=x+1;	sosedi[4].y=y+1;
			sosedi[5].x=x+1;	sosedi[5].y=y;
			sosedi[6].x=x+1;	sosedi[6].y=y-1;
			sosedi[7].x=x;		sosedi[7].y=y-1;
			
			for(int i=0;i<8;i++)
			{
				if( sosedi[i].x>=0 && sosedi[i].x<data.size() && 
					sosedi[i].y>=0 && sosedi[i].y<data[0].size())
				{
					if( !gMap[sosedi[i].x][sosedi[i].y] && data[x][y]==data[sosedi[i].x][sosedi[i].y])
					{
						gMap[sosedi[i].x][sosedi[i].y]=(i+4)%8 + 1;
						outerPoints.push_back(sosedi[i]);
					}
				}
			}
		}
	}
}

int MMLibG2D::GetMinValDirection(int x, int y, double& val)
{
	int winSize=1;
	int sx=max(0,x-winSize);
	int ex=min(data.size()-1,x+winSize);
	int sy=max(0,y-winSize);
	int ey=min(data[0].size()-1,y+winSize);
	
	val=data[x][y];
	int direction=0;
	
	for(int _x=sx;_x<=ex;_x++)
	{
		for(int _y=sy;_y<=ey;_y++)
		{
			if(val>data[_x][_y])
			{
				val=data[_x][_y];
				if(_x==x-1 && _y==y-1)
					direction=1;
				else if( _x==x-1 && _y==y)
					direction=2;
				else if( _x==x-1 && _y==y+1)
					direction=3;
				else if( _x==x && _y==y+1)
					direction=4;
				else if( _x==x+1 && _y==y+1)
					direction=5;
				else if( _x==x+1 && _y==y)
					direction=6;
				else if( _x==x+1 && _y==y-1)
					direction=7;
				else if( _x==x && _y==y-1)
					direction=8;
			}
		}
	}
	return direction;
}
int MMLibG2D::GetMinValDirection(int x, int y, double& val, int& pVal)
{
	int winSize=1;
	int sx=max(0,x-winSize);
	int ex=min(data.size()-1,x+winSize);
	int sy=max(0,y-winSize);
	int ey=min(data[0].size()-1,y+winSize);
	
	int direction=0;
	
	for(int _x=sx;_x<=ex;_x++)
	{
		for(int _y=sy;_y<=ey;_y++)
		{
			if(x==_x && y==_y)
				continue;
			if(data[_x][_y]==data[x][y])
				pVal=1;
			if(val>data[_x][_y])
			{
				val=data[_x][_y];
				if(_x==x-1 && _y==y-1)
					direction=1;
				else if( _x==x-1 && _y==y)
					direction=2;
				else if( _x==x-1 && _y==y+1)
					direction=3;
				else if( _x==x && _y==y+1)
					direction=4;
				else if( _x==x+1 && _y==y+1)
					direction=5;
				else if( _x==x+1 && _y==y)
					direction=6;
				else if( _x==x+1 && _y==y-1)
					direction=7;
				else if( _x==x && _y==y-1)
					direction=8;
			}
		}
	}
	return direction;
}
void MMLibG2D::_Watershed(vector<vector<int>>& gradDirection, vector<vector<int>>& output)
{
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(output[x][y])
				continue;
			output[x][y]=_Watershed(gradDirection,output,x,y);
		}
	}
}
int MMLibG2D::_Watershed(vector<vector<int>>& gradDirection, vector<vector<int>>& output, int x, int y)
{
	//Èe smo našli celico z doloèeno regijo, lahko to regijo vrnemo
	if(output[x][y])
		return output[x][y];

	//Èe ne išèemo v smeri naklona dalje
	if(gradDirection[x][y]==1)
		 output[x][y]=_Watershed(gradDirection,output,x-1,y-1);
	else if(gradDirection[x][y]==2)
		 output[x][y]=_Watershed(gradDirection,output,x-1,y);
	else if(gradDirection[x][y]==3)
		 output[x][y]=_Watershed(gradDirection,output,x-1,y+1);
	else if(gradDirection[x][y]==4)
		 output[x][y]=_Watershed(gradDirection,output,x,y+1);
	else if(gradDirection[x][y]==5)
		 output[x][y]=_Watershed(gradDirection,output,x+1,y+1);
	else if(gradDirection[x][y]==6)
		 output[x][y]=_Watershed(gradDirection,output,x+1,y);
	else if(gradDirection[x][y]==7)
		 output[x][y]=_Watershed(gradDirection,output,x+1,y-1);
	else if(gradDirection[x][y]==8)
		 output[x][y]=_Watershed(gradDirection,output,x,y-1);

	return output[x][y];
}
void MMLibG2D::ErosionProfiles(vector<vector<double>>& f_line, vector<vector<int>>& f_dot, vector<int> wVec)
{
	MMLibG2D mmg; InitData(f_line,0.0);
	vector<vector<double>> pImg=data;
	vector<vector<double>> f_dif(f_line.size(), vector<double>(f_line[0].size(),0.0));
	
	for(int w=1;w<wVec.size();w++)
	{
		mmg.data=pImg;
		mmg.Init();
		for(int i=wVec[w-1]; i<wVec[w];i++)
			mmg.FastErode3();

		SubtractData(pImg,mmg.data,f_dif);
		for(int x=0;x<pImg.size();x++)
		{
			for(int y=0;y<pImg[0].size();y++)
			{
				if(f_dif[x][y]>f_line[x][y])
				{
					f_line[x][y]=f_dif[x][y];
					f_dot[x][y]=w;
				}
			}
		}
		pImg=mmg.data;
	}
}
void MMLibG2D::FastDMP(vector<vector<double>>& f_line, vector<vector<int>>& f_dot, vector<int> wVec)
{
	MMLibG2D mmg; InitData(f_line,0.0);
	vector<vector<double>> pImg=data;
	vector<vector<double>> eImg=data;
	vector<vector<double>> f_dif(f_line.size(), vector<double>(f_line[0].size(),0.0));
	
	for(int w=1;w<wVec.size();w++)
	{
		mmg.data=eImg;
		mmg.Init();
		for(int i=wVec[w-1]; i<wVec[w];i++)
			mmg.FastErode3();
		
		eImg=mmg.data;

		for(int i=0; i<wVec[w];i++)
			mmg.FastDilate3();

		SubtractData(pImg,mmg.data,f_dif);
		for(int x=0;x<pImg.size();x++)
		{
			for(int y=0;y<pImg[0].size();y++)
			{
				if(f_dif[x][y]>f_line[x][y])
				{
					f_line[x][y]=f_dif[x][y];
					f_dot[x][y]=w;
				}
			}
		}
		pImg=mmg.data;
	}
}
void MMLibG2D::FastDMP(vector<vector<vector<double>>>& f_stack, vector<int> wVec)
{
	MMLibG2D mmg;
	vector<vector<double>> pImg=data;
	vector<vector<double>> eImg=data;
	vector<vector<double>> f_dif(data.size(), vector<double>(data[0].size(),0.0));
	
	for(int w=1;w<wVec.size();w++)
	{
		mmg.data=eImg;
		mmg.Init();
		for(int i=wVec[w-1]; i<wVec[w];i++)
			mmg.FastErode3();
		
		eImg=mmg.data;

		for(int i=0; i<wVec[w];i++)
			mmg.FastDilate3();

		SubtractData(pImg,mmg.data,f_dif);
		
		f_stack.push_back(f_dif);
		
		pImg=mmg.data;
	}
}
void MMLibG2D::FastDMP(vector<vector<vector<double>>>& f_stack, vector<vector<double>>& r_img, vector<int> wVec)
{
	MMLibG2D mmg;
	vector<vector<double>> pImg=data;
	vector<vector<double>> eImg=data;
	vector<vector<double>> f_dif(data.size(), vector<double>(data[0].size(),0.0));
	
	for(int w=1;w<wVec.size();w++)
	{
		mmg.data=eImg;
		mmg.Init();
		for(int i=wVec[w-1]; i<wVec[w];i++)
			mmg.FastErode3();
		
		eImg=mmg.data;

		for(int i=0; i<wVec[w];i++)
			mmg.FastDilate3();

		SubtractData(pImg,mmg.data,f_dif);
		
		f_stack.push_back(f_dif);
		
		pImg=mmg.data;
	}
	r_img=pImg;
}
void MMLibG2D::FastDMP_Oct(vector<vector<double>>& f_line, vector<vector<int>>& f_dot, vector<int> wVec)
{
	MMLibG2D mmg; InitData(f_line,0.0);InitData(f_dot,wVec[wVec.size()-1]);
	vector<vector<double>> pImg=data;
	vector<vector<double>> eImg=data;
	vector<vector<double>> f_dif(f_line.size(), vector<double>(f_line[0].size(),0.0));
	
	for(int w=1;w<wVec.size();w++)
	{
		mmg.data=eImg;
		mmg.Init();
		for(int i=wVec[w-1]; i<wVec[w];i++)
		{
			if(i%2)
				mmg.FastErode3();
			else
				mmg.FastErodeC3();
		}
		
		eImg=mmg.data;
		mmg.FastDilateOct(wVec[w]);
		
		SubtractData(pImg,mmg.data,f_dif);
		for(int x=0;x<pImg.size();x++)
		{
			for(int y=0;y<pImg[0].size();y++)
			{
				if(f_dif[x][y]>f_line[x][y])
				{
					f_line[x][y]=f_dif[x][y];
					f_dot[x][y]=w;
				}
			}
		}
		pImg=mmg.data;
	}
}
void MMLibG2D::FastDMP_Oct(vector<vector<vector<double>>>& f_stack, vector<int> wVec)
{
	MMLibG2D mmg; f_stack.clear();
	vector<vector<double>> pImg=data;
	vector<vector<double>> eImg=data;
	vector<vector<double>> f_dif(data.size(), vector<double>(data[0].size(),0.0));
	
	for(int w=1;w<wVec.size();w++)
	{
		mmg.data=eImg;
		mmg.Init();
		for(int i=wVec[w-1]; i<wVec[w];i++)
		{
			if(i%2)
				mmg.FastErode3();
			else
				mmg.FastErodeC3();
		}
		eImg=mmg.data;
		mmg.FastDilateOct(wVec[w]);
		
		SubtractData(pImg,mmg.data,f_dif);
		
		f_stack.push_back(f_dif);
		
		pImg=mmg.data;
	}
}
void MMLibG2D::FastDMP_Oct(vector<vector<vector<double>>>& f_stack, vector<vector<double>>& r_img, vector<int> wVec)
{
	MMLibG2D mmg; f_stack.clear();
	vector<vector<double>> pImg=data;
	vector<vector<double>> eImg=data;
	vector<vector<double>> f_dif(data.size(), vector<double>(data[0].size(),0.0));
	
	for(int w=1;w<wVec.size();w++)
	{
		mmg.data=eImg;
		mmg.Init();
		for(int i=wVec[w-1]; i<wVec[w];i++)
		{
			if(i%2)
				mmg.FastErode3();
			else
				mmg.FastErodeC3();
		}
		eImg=mmg.data;
		mmg.FastDilateOct(wVec[w]);
		
		SubtractData(pImg,mmg.data,f_dif);
		
		f_stack.push_back(f_dif);
		
		pImg=mmg.data;
	}
	r_img=pImg;
}
void MMLibG2D::FastSMRF_Oct(vector<vector<vector<double>>>& f_stack, vector<int> wVec)
{
	MMLibG2D mmg; f_stack.clear();
	vector<vector<double>> pImg=data;
	vector<vector<double>> eImg=data;
	vector<vector<double>> f_dif(data.size(), vector<double>(data[0].size(),0.0));
	for(int w=1;w<wVec.size();w++)
	{
		mmg.data=eImg;
		mmg.Init();
		for(int i=wVec[w-1]; i<wVec[w];i++)
		{
			if(i%2)
				mmg.FastErode3();
			else
				mmg.FastErodeC3();
		}
		eImg=mmg.data;
		mmg.FastDilateOct(wVec[w]);
		
		SubtractData(data,mmg.data,f_dif);
		
		f_stack.push_back(f_dif);
		
		pImg=mmg.data;
	}
}
void MMLibG2D::DMP(vector<vector<double>>& f_line, vector<vector<int>>& f_dot, vector<int> wVec, bool ignoreFirst)
{
	MMLibG2D mmgP; InitData(f_line,0.0);
	
	int startI=1;
	vector<vector<double>> imgP=data;
	if(ignoreFirst)
	{
		mmgP.data=imgP;
		mmgP.Init();
		mmgP.FastOpen(wVec[1]);
		imgP=mmgP.data;
		startI=2;
	}

	vector<vector<double>> f_dif(f_line.size(), vector<double>(f_line[0].size(),0.0));
	for(int w=startI;w<wVec.size();w++)
	{
		mmgP.data=imgP;
		mmgP.Init();
		mmgP.FastOpen(wVec[w]);

		SubtractData(imgP,mmgP.data,f_dif);
		for(int x=0;x<imgP.size();x++)
		{
			for(int y=0;y<imgP[0].size();y++)
			{
				if(f_dif[x][y]>f_line[x][y])
				{
					f_line[x][y]=f_dif[x][y];
					f_dot[x][y]=w;
				}
			}
		}
		imgP=mmgP.data;
	}
}
void MMLibG2D::DMP(vector<vector<vector<double>>>& f_stack, vector<int> wVec, bool ignoreFirst)
{
	MMLibG2D mmgP;
	
	int startI=1;
	vector<vector<double>> imgP=data;
	vector<vector<double>> iDiff=data;
	if(ignoreFirst)
	{
		mmgP.data=imgP;
		mmgP.Init();
		mmgP.FastOpen(wVec[1]);
		imgP=mmgP.data;
		startI=2;
	}

	for(int w=startI;w<wVec.size();w++)
	{
		mmgP.data=imgP;
		mmgP.Init();
		mmgP.FastOpen(wVec[w]);

		SubtractData(imgP,mmgP.data,iDiff);
		f_stack.push_back(iDiff);

		imgP=mmgP.data;
	}
}
void MMLibG2D::DMP(vector<vector<double>>& f_line, vector<vector<int>>& f_dot, vector<vector<double>>& f_level, vector<int> wVec, bool ignoreFirst)
{
	MMLibG2D mmgP; InitData(f_line,0.0);
	
	int startI=1;
	vector<vector<double>> imgP=data;
	if(ignoreFirst)
	{
		mmgP.data=imgP;
		mmgP.Init();
		mmgP.FastOpen(wVec[1]);
		imgP=mmgP.data;
		startI=2;
	}
	
	for(int w=startI;w<wVec.size();w++)
	{
		mmgP.data=imgP;
		mmgP.Init();
		mmgP.FastOpen(wVec[w]);

		for(int x=0;x<imgP.size();x++)
		{
			for(int y=0;y<imgP[0].size();y++)
			{
				double pDiff=imgP[x][y]-mmgP.data[x][y];
				if(pDiff>f_line[x][y])
				{
					f_line[x][y]=pDiff;
					f_dot[x][y]=w;
					f_level[x][y]=imgP[x][y];
				}
			}
		}
		imgP=mmgP.data;
	}
}
void MMLibG2D::DMPOnReconstruction(vector<vector<double>>& f_line, vector<vector<int>>& f_dot, vector<int> wVec)
{
	MMLibG2D mmgP; InitData(f_line,0.0);
	vector<vector<double>> imgP=data;
	
	for(int w=1;w<wVec.size();w++)
	{
		mmgP.data=imgP;
		mmgP.Init();
		mmgP.OpeningByReconstruction(wVec[w]);

		for(int x=0;x<imgP.size();x++)
		{
			for(int y=0;y<imgP[0].size();y++)
			{
				double pDiff=imgP[x][y]-mmgP.data[x][y];
				if(pDiff>f_line[x][y])
				{
					f_line[x][y]=pDiff;
					f_dot[x][y]=w;
				}
			}
		}
		imgP=mmgP.data;
	}
}
void MMLibG2D::MSLSSegmentation(vector<vector<double>>& f_line, vector<vector<double>>& f_dot, vector<vector<double>>& f_class, vector<int> wVec)
{
	MMLibG2D mmgP,mmgN; 
	vector<vector<double>> imgP=data;
	vector<vector<double>> imgN=data;MultiplyData(imgN,-1.0);
	vector<vector<double>> pMax(data.size(),vector<double>(data[0].size(),0.0));
	vector<vector<double>> pScale(data.size(),vector<double>(data[0].size(),0.0));
	vector<vector<double>> nMax(data.size(),vector<double>(data[0].size(),0.0));
	vector<vector<double>> nScale(data.size(),vector<double>(data[0].size(),0.0));

	for(int w=1;w<wVec.size();w++)
	{
		mmgP.data=imgP;
		mmgP.Init();
		mmgP.FastOpen(wVec[w]);

		mmgN.data=imgN;
		mmgN.Init();
		mmgN.FastOpen(wVec[w]);
		
		for(int x=0;x<imgP.size();x++)
		{
			for(int y=0;y<imgP[0].size();y++)
			{
				double pDiff=imgP[x][y]-mmgP.data[x][y];
				double nDiff=imgN[x][y]-mmgN.data[x][y];

				if(pDiff>pMax[x][y])
				{
					pMax[x][y]=pDiff;
					pScale[x][y]=wVec[w];
				}
				if(nDiff>nMax[x][y])
				{
					nMax[x][y]=nDiff;
					nScale[x][y]=wVec[w];
				}
			}
		}
		imgP=mmgP.data;
		imgN=mmgN.data;
	}
	
	/*START: Segmentation*/
	for(int x=0;x<f_line.size();x++)
	{
		for(int y=0;y<f_line[0].size();y++)
		{
			if(pMax[x][y]>nMax[x][y])
			{
				f_line[x][y]=pMax[x][y];
				f_dot[x][y]=pScale[x][y];
				f_class[x][y]=2.0;
			}
			else if(pMax[x][y]<nMax[x][y])
			{
				f_line[x][y]=nMax[x][y];
				f_dot[x][y]=nScale[x][y];
				f_class[x][y]=1.0;
			}
			else
			{
				f_line[x][y]=pMax[x][y];
				f_dot[x][y]=pScale[x][y];
				f_class[x][y]=0.0;
			}
		}
	}
	/*END: Segmentation*/
}
void MMLibG2D::MSLSSegmentation(vector<vector<double>>& f_line, vector<vector<double>>& f_dot, vector<vector<double>>& f_class, vector<vector<double>>& f_level, vector<int> wVec)
{
	MMLibG2D mmgP,mmgN; 
	vector<vector<double>> imgP=data;
	vector<vector<double>> imgN=data;MultiplyData(imgN,-1.0);
	vector<vector<double>> pMax(data.size(),vector<double>(data[0].size(),0.0));
	vector<vector<double>> pScale(data.size(),vector<double>(data[0].size(),0.0));
	vector<vector<double>> pLevel(data.size(),vector<double>(data[0].size(),0.0));
	vector<vector<double>> nMax(data.size(),vector<double>(data[0].size(),0.0));
	vector<vector<double>> nScale(data.size(),vector<double>(data[0].size(),0.0));
	vector<vector<double>> nLevel(data.size(),vector<double>(data[0].size(),0.0));

	for(int w=1;w<wVec.size();w++)
	{
		mmgP.data=imgP;
		mmgP.Init();
		mmgP.FastOpen(wVec[w]);

		mmgN.data=imgN;
		mmgN.Init();
		mmgN.FastOpen(wVec[w]);
		
		for(int x=0;x<imgP.size();x++)
		{
			for(int y=0;y<imgP[0].size();y++)
			{
				double pDiff=imgP[x][y]-mmgP.data[x][y];
				double nDiff=imgN[x][y]-mmgN.data[x][y];

				if(pDiff>pMax[x][y])
				{
					pMax[x][y]=pDiff;
					pScale[x][y]=wVec[w];
					pLevel[x][y]=mmgP.data[x][y];
				}
				if(nDiff>nMax[x][y])
				{
					nMax[x][y]=nDiff;
					nScale[x][y]=wVec[w];
					nLevel[x][y]=mmgN.data[x][y];
				}
			}
		}
		imgP=mmgP.data;
		imgN=mmgN.data;
	}
	
	/*START: Segmentation*/
	for(int x=0;x<f_line.size();x++)
	{
		for(int y=0;y<f_line[0].size();y++)
		{
			if(pMax[x][y]>nMax[x][y])
			{
				f_line[x][y]=pMax[x][y];
				f_dot[x][y]=pScale[x][y];
				f_level[x][y]=pLevel[x][y];
				f_class[x][y]=2.0;
			}
			else if(pMax[x][y]<nMax[x][y])
			{
				f_line[x][y]=nMax[x][y];
				f_dot[x][y]=nScale[x][y];
				f_level[x][y]=nLevel[x][y];
				f_class[x][y]=1.0;
			}
			else
			{
				f_line[x][y]=pMax[x][y];
				f_dot[x][y]=pScale[x][y];
				f_level[x][y]=pLevel[x][y];
				f_class[x][y]=0.0;
			}
		}
	}
	/*END: Segmentation*/
}

void MMLibG2D::MSLSSegmentationDAP(vector<vector<double>>& f_line, vector<vector<double>>& f_dot, vector<vector<double>>& f_class, vector<double> lambda)
{
	int noLevels=2000;
	vector<vector<double>> hImg=data;
	vector<vector<double>> lImg=data;InvertData(lImg);
	vector<vector<double>> hLImg(data.size(),vector<double>(data[0].size(),0.0));CreateLevelImg(hImg,hLImg,noLevels);
	vector<vector<double>> lLImg=hLImg;InvertData(lLImg);

	MaxTree hTree(hLImg,hImg,noLevels+1);
	MaxTree lTree(lLImg,lImg,noLevels+1);

	/*START: Heigh DAP*/
	hTree.SetAreaAttribute();
	hTree.DAP(lambda,false);
	hTree.PropagateMaxResponse(0);

	hTree.Parameter2Img(hImg);
	hTree.NodeParameter2Img(hLImg);
	/*END: Heigh DAP*/

	/*START: Low DAP*/
	lTree.SetAreaAttribute();
	lTree.DAP(lambda,false);
	lTree.PropagateMaxResponse(0);
	
	lTree.Parameter2Img(lImg);
	lTree.NodeParameter2Img(lLImg);
	/*END: Low DAP*/
	
	/*START: Segmentation*/
	for(int x=0;x<f_line.size();x++)
	{
		for(int y=0;y<f_line[0].size();y++)
		{
			//hImg[x][y]*=2.0;
			if(hImg[x][y]>lImg[x][y])
			{
				f_line[x][y]=hImg[x][y];
				f_dot[x][y]=hLImg[x][y];
				f_class[x][y]=2.0;
			}
			else if(hImg[x][y]<lImg[x][y])
			{
				f_line[x][y]=lImg[x][y];
				f_dot[x][y]=lLImg[x][y];
				f_class[x][y]=1.0;
			}
			else
			{
				f_line[x][y]=lImg[x][y];
				f_dot[x][y]=hLImg[x][y];
				f_class[x][y]=0.0;
			}
		}
	}
	/*END: Segmentation*/
}
void MMLibG2D::MSLSSegmentationDAP(vector<vector<double>>& f_line, vector<vector<double>>& f_dot, vector<vector<double>>& f_class, vector<vector<double>>& f_level, vector<double> lambda)
{
	int noLevels=2000;
	vector<vector<double>> hImg=data;
	vector<vector<double>> lImg=data;InvertData(lImg);
	vector<vector<double>> hLImg(data.size(),vector<double>(data[0].size(),0.0));CreateLevelImg(hImg,hLImg,noLevels);
	vector<vector<double>> lLImg=hLImg;InvertData(lLImg);
	vector<vector<double>> hLevelImg(data.size(),vector<double>(data[0].size(),0.0));
	vector<vector<double>> lLevelImg(data.size(),vector<double>(data[0].size(),0.0));

	MaxTree hTree(hLImg,hImg,noLevels+1);
	MaxTree lTree(lLImg,lImg,noLevels+1);

	/*START: Heigh DAP*/
	hTree.SetAreaAttribute();
	hTree.DAP(lambda,false);
	hTree.PropagateMaxResponse(0);

	hTree.Parameter2Img(hImg);
	hTree.NodeParameter2Img(hLImg);
	hTree.NodeAttribute2Img(hLevelImg);
	/*END: Heigh DAP*/

	/*START: Low DAP*/
	lTree.SetAreaAttribute();
	lTree.DAP(lambda,false);
	lTree.PropagateMaxResponse(0);
	
	lTree.Parameter2Img(lImg);
	lTree.NodeParameter2Img(lLImg);
	lTree.NodeAttribute2Img(lLevelImg);
	/*END: Low DAP*/
	
	/*START: Segmentation*/
	for(int x=0;x<f_line.size();x++)
	{
		for(int y=0;y<f_line[0].size();y++)
		{
			if(hImg[x][y]>lImg[x][y])
			{
				f_line[x][y]=hImg[x][y];
				f_dot[x][y]=hLImg[x][y];
				f_class[x][y]=2.0;
				f_level[x][y]=hLevelImg[x][y];
			}
			else if(hImg[x][y]<lImg[x][y])
			{
				f_line[x][y]=lImg[x][y];
				f_dot[x][y]=lLImg[x][y];
				f_class[x][y]=1.0;
				f_level[x][y]=-1.0*lLevelImg[x][y];
			}
			else
			{
				f_line[x][y]=lImg[x][y];
				f_dot[x][y]=hLImg[x][y];
				f_class[x][y]=0.0;
				f_level[x][y]=hLevelImg[x][y];
			}
		}
	}
	/*END: Segmentation*/
}
void MMLibG3D::Init()
{
	tmpData=data;
}
void MMLibG3D::FastErode3()
{
	MMLibG2D mmg;
	for(int i=0;i<data.size();i++)
	{
		mmg.data=data[i];
		mmg.Init();
		mmg.FastErode(1);
		data[i]=mmg.data;
	}

	tmpData=data;
	int maxi=data.size()-1;
	for(int i=1;i<maxi;i++)
	{
		for(int x=0;x<data[0].size();x++)
			for(int y=0;y<data[0][0].size();y++)
				data[i][x][y]=min(min(tmpData[i-1][x][y],tmpData[i][x][y]),tmpData[i+1][x][y]);
	}
}
void MMLibG3D::FastDilate3()
{
	MMLibG2D mmg;
	for(int i=0;i<data.size();i++)
	{
		mmg.data=data[i];
		mmg.Init();
		mmg.FastDilate(1);
		data[i]=mmg.data;
	}

	tmpData=data;
	int maxi=data.size()-1;
	for(int i=1;i<maxi;i++)
	{
		for(int x=0;x<data[0].size();x++)
			for(int y=0;y<data[0][0].size();y++)
				data[i][x][y]=max(max(tmpData[i-1][x][y],tmpData[i][x][y]),tmpData[i+1][x][y]);
	}
}

//CONVOLUTION
Convolution::Convolution(void)
{

}

Convolution::~Convolution(void)
{
	Clean();
}
void Convolution::Clean()
{
	
}
void Convolution::ExpandForConvolution()
{
	double polmer=K.size()/2;
	vector<vector<double>> exData(data.size()+K.size()-1, vector<double>(data[0].size()+K.size()-1,0));
	for(int x=0;x<exData.size();x++)
	{
		for(int y=0;y<exData[0].size();y++)
		{
			int _x=min(max(x-polmer,0),data.size()-1);
			int _y=min(max(y-polmer,0),data[0].size()-1);
			exData[x][y]=data[_x][_y];
		}
	}
	data=exData;
	tmpData=exData;
}
void Convolution::CollapseForConvolution()
{
	double polmer=K.size()/2;
	vector<vector<double>> exData(data.size()-K.size()+1, vector<double>(data[0].size()-K.size()+1,0));
	for(int x=0;x<exData.size();x++)
		for(int y=0;y<exData[0].size();y++)
			exData[x][y]=data[x+polmer][y+polmer];
	data=exData;
	tmpData=exData;
}
void Convolution::KAverage(int polmer)
{
	int premer=polmer*2+1;
	vector<vector<double>> se(premer,vector<double>(premer,1.0/(double)(premer*premer)));
	K=se;
}
void Convolution::KGauss(int polmer, double std)
{
	double pi = 3.14159265;
	int premer=polmer*2+1;
	vector<vector<double>> se(premer,vector<double>(premer,0.0));
	K=se;

	double std2=std*std;
	double fact=1.0/(2*pi*std2);
	double sum=0.0;

	for(int x=0;x<premer;x++)
	{
		for(int y=0;y<premer;y++)
		{
			double xDist=x-polmer;
			double yDist=y-polmer;

			double dist2=xDist*xDist+yDist*yDist;

			double eExp=exp(-1.0*dist2/(2.0*std2));
			
			K[x][y]=fact*eExp;
			sum+=K[x][y];
		}	
	}
	/*START: normalization*/
	sum=1.0/sum;
	for(int kx=0;	kx<premer;	kx++)	for(int ky=0;	ky<premer; ky++)
		K[kx][ky]*=sum;
	/*END: normalization*/
}
void Convolution::KLoG(int polmer, double std)
{
	double pi = 3.14159265;
	int premer=polmer*2+1;
	vector<vector<double>> se(premer,vector<double>(premer,0.0));
	K=se;

	double std2=std*std;
	double fact=-1.0/(pi*std2*std2);

	for(int x=0;x<premer;x++)
	{
		for(int y=0;y<premer;y++)
		{
			double xDist=x-polmer;
			double yDist=y-polmer;

			double dist2=xDist*xDist+yDist*yDist;

			double oklepaj=1.0-(dist2/(2.0*std2));

			double eExp=exp(-1.0*dist2/(2.0*std2));
			
			K[x][y]=fact*oklepaj*eExp;
		}
	}
}
void Convolution::GaborWave(int polmer, double waveLength, double angle, double phase, double gEnvelope, double elipsity)
{
	double pi = 3.14159265;
	int premer=polmer*2+1;
	vector<vector<double>> se(premer,vector<double>(premer,0.0));
	K=se;

	double theta=angle;
	double lambda=waveLength;

	double phi=phase;
	if(gEnvelope<0.0)
		gEnvelope=waveLength;
	double std=gEnvelope;
	double gamma=elipsity;

	double gamma2=gamma*gamma;
	double std2=std*std;
	for(int x=0;x<premer;x++)
	{
		for(int y=0;y<premer;y++)
		{
			double xD=x-polmer;
			double yD=y-polmer;

			double x2=x*x;
			double y2=y*y;
			double x_line=xD*cos(theta)+yD*sin(theta);
			double x_line2=x_line*x_line;
			double y_line=-1.0*xD*sin(theta)+yD*cos(theta);
			double y_line2=y_line*y_line;

			double exp1=-1.0*(x_line2+gamma2*y_line2);
			exp1=exp(exp1/(2*std2));

			double exp2=2.0*pi*(x_line/lambda)+phi;
			exp2=cos(exp2);
			K[x][y]=exp1*exp2;
		}
	}
	double sum=0.0;
	for(int x=0;x<premer;x++)
		for(int y=0;y<premer;y++)
			sum+=K[x][y];
	sum/=(double)(premer*premer);
	for(int x=0;x<premer;x++)
		for(int y=0;y<premer;y++)
			K[x][y]-=sum;
}
void Convolution::StoreDataToTmpData()
{
	for(int x=0;x<data.size();x++)
		for(int y=0;y<data[0].size();y++)
			tmpData[x][y]=data[x][y];
}
void Convolution::StoreTmpDataToData()
{
	for(int x=0;x<data.size();x++)
		for(int y=0;y<data[0].size();y++)
			data[x][y]=tmpData[x][y];
}

void Convolution::Init()
{
	Clean();
	vector<vector<double>> tstTmp(data.size(),vector<double>(data[0].size()));
	tmpData=tstTmp;
}
void Convolution::Convolve()
{
	int winSize=K.size()/2;
	for(int x=0; x<data.size(); x++)
	{
		for(int y=0; y<data[0].size(); y++)
		{
			double fact=0.0;
			double sum=0.0;

			for(int _x=0;_x<K.size();_x++)
			{
				for(int _y=0;_y<K[0].size();_y++)
				{
					int cX=x-winSize+_x;
					int cY=y-winSize+_y;

					if(cX<0 || cX>=data.size() || cY<0 || cY>=data[0].size())
						continue;
					
					sum+=data[cX][cY]*K[_x][_y];
					fact+=K[_x][_y];
				}
			}
			tmpData[x][y]=sum/fact;
		}
	}

	StoreTmpDataToData();
}
void Convolution::ConvolveGaborRotSeries(int polmer, double waveLength, int noAngles, double phase, double gEnvelope, double elipsity)
{
	/*START: InitData*/
	if(gEnvelope<0.0)
		gEnvelope=waveLength;

	vector<vector<vector<double>>> K_series;
	double aStep=PI/(double)noAngles;

	for(int k=0;k<noAngles;k++)
	{
		K.clear();
		double angle=(double)k*aStep;
		GaborWave(polmer,waveLength,angle,phase,gEnvelope,elipsity);
		K_series.push_back(K);
	}
	ExpandForConvolution();
	Init();
	/*END: InitData*/


	double* in=new double[data.size()*data[0].size()];
	double* out=new double[data.size()*data[0].size()];
	double* kern= new double[K_series[0].size()*K_series[0][0].size()];
	
	int i=0;
	for(int y=0;y<data[0].size();y++)
	{
		for(int x=0;x<data.size();x++)
		{
			in[i]=data[x][y];
			i++;
		}
	}

	InitData(tmpData,-2.0);
	for(int k=0;k<noAngles;k++)
	{
		int i=0;
		for(int x=0;x<K_series[k].size();x++)
		{
			for(int y=0;y<K_series[k][0].size();y++)
			{
				kern[i]=K_series[k][x][y];
				i++;
			}
		}
		//convolve2DFast(in,out,data.size(),data[0].size(),kern,K.size(),K[0].size());
		
		i=0;
		for(int y=0;y<data[0].size();y++)
		{
			for(int x=0;x<data.size();x++)
			{
				if(tmpData[x][y]<out[i])
					tmpData[x][y]=out[i];
				i++;
			}
		}
	}
	data=tmpData;
	/*START: Finalization*/
	delete [] in; 
	delete [] out; 
	delete [] kern; 
	CollapseForConvolution();
	NormalizeData(data,0.0,1.0);
	/*END: Finalization*/
}
void Convolution::ConvolveGaborScaleSeries(int polmer, int minWL,int maxWL, int noAngles, double phase, double gEnvelope, double elipsity)
{
	vector<vector<double>> orgData=data;
	for(int wl=minWL;wl<=maxWL;wl++)
	{
		data=orgData;
		ConvolveGaborRotSeries(polmer,wl,noAngles,phase,gEnvelope,elipsity);
		CropData(data,-2.0,2.0);
		dataStack.push_back(data);
	}
}
void Convolution::FastAverage(int winSize)
{
	int maxx=data.size()-1; int maxy=data[0].size()-1;
	int fullSize=winSize*2+1;
	vector<double> vals(fullSize,0.0);
	
	/*START: SumPoStolpcih*/
	for(int x=0;x<data.size();x++)
	{
		double sum=0.0;
		int cIndex=0;
		for(int y=0;y<fullSize;y++)
		{
			vals[cIndex]=data[x][max(y-winSize,0)];
			sum+=vals[cIndex++];
		}
		cIndex=0;
		for(int y=0;y<data[0].size();y++)
		{	
			sum-=vals[cIndex];
			vals[cIndex]=data[x][min(y+winSize,maxy)];
			sum+=vals[cIndex];
			tmpData[x][y]=sum;
			cIndex=(++cIndex)%fullSize;
		}
	}
	/*START: SumPoStolpcih*/

	/*START: SumPoVrsticah*/
	double coef=fullSize*fullSize;
	for(int y=0;y<data[0].size();y++)
	{
		double sum=0.0;
		int cIndex=0;
		for(int x=0;x<fullSize;x++)
		{
			vals[cIndex]=tmpData[max(x-winSize,0)][y];
			sum+=vals[cIndex++];
		}
		cIndex=0;
		for(int x=0;x<data.size();x++)
		{	
			sum-=vals[cIndex];
			vals[cIndex]=tmpData[min(x+winSize,maxx)][y];
			sum+=vals[cIndex];
			data[x][y]=sum/coef;
			cIndex=(++cIndex)%fullSize;
		}
	}
	/*START: SumPoVrsticah*/
}
//EDGE FILTERS
EdgeDetection::EdgeDetection(void)
{
}
EdgeDetection::~EdgeDetection(void)
{
}
void EdgeDetection::Sobel(vector<vector<double>> &data)
{
	double Wx[3][3]={-1.0, 0.0, 1.0,
					 -2.0, 0.0, 2.0,
					 -1.0, 0.0, 1.0};
	double Wy[3][3]={-1.0, -2.0, -1.0,
					  0.0,  0.0,  0.0,
					  1.0,  2.0,  0.0};
	
	vector<vector<double>> temp(data.size(),vector<double>(data[0].size(),0.0));
	
	for(int x=1;x<data.size()-1;x++)
	{
		for(int y=1;y<data[0].size()-1;y++)
		{
			double sumX=0.0;
			double sumY=0.0;

			for(int _x=0;_x<3;_x++)
			{
				for(int _y=0;_y<3;_y++)
				{
					int cX=x-1+_x;
					int cY=y-1+_y;

					sumX+=data[cX][cY]*Wx[_x][_y];
					sumY+=data[cX][cY]*Wy[_x][_y];
				}
			}
			temp[x][y]=sqrt(sumX*sumX+sumY*sumY);
		}
	}
	for(int x=0;x<data.size();x++)
		for(int y=0;y<data[0].size();y++)
			data[x][y]=min(abs(temp[x][y]-data[x][y]),25.0);

	for(int x=0;x<data.size();x++)
	{
		data[x][0]=data[x][1];
		data[x][data[0].size()-1]=data[x][data[0].size()-2];
	}
	for(int y=0;y<data[0].size();y++)
	{
		data[0][y]=data[1][y];
		data[data.size()-1][y]=data[data.size()-2][y];
	}
}
void EdgeDetection::Laplace(vector<vector<double>> &data, double tVal)
{
	double W[3][3]={  0.5, 1.0, 0.5,
					  1.0,-6.0, 1.0,
					  0.5, 1.0, 0.5};
	vector<vector<double>> temp(data.size(),vector<double>(data[0].size(),0.0));
	
	for(int x=1;x<data.size()-1;x++)
	{
		for(int y=1;y<data[0].size()-1;y++)
		{
			double sum=0.0;
			for(int _x=0;_x<3;_x++)
			{
				for(int _y=0;_y<3;_y++)
				{
					int cX=x-1+_x;
					int cY=y-1+_y;

					sum+=data[cX][cY]*W[_x][_y];
				}
			}
			temp[x][y]=sum;
		}
	}
	for(int x=0;x<data.size();x++)
		for(int y=0;y<data[0].size();y++)
			data[x][y]=temp[x][y];

	for(int x=0;x<data.size();x++)
	{
		data[x][0]=data[x][1];
		data[x][data[0].size()-1]=data[x][data[0].size()-2];
	}
	for(int y=0;y<data[0].size();y++)
	{
		data[0][y]=data[1][y];
		data[data.size()-1][y]=data[data.size()-2][y];
	}

	/*START: Obrezovanje divjih vrednosti*/
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(data[x][y]>tVal)
				data[x][y]=tVal;
			else if(data[x][y]<-1.0*tVal)
				data[x][y]=-1.0*tVal;
		}
	}
	/*END: Obrezovanje divjih vrednosti*/
}
void EdgeDetection::BlurMinimum(vector<vector<double>> &data)
{
	vector<vector<int>> K(3,vector<int>(3,1));
	MMLibG2D mm;
	
	mm.data=data;
	mm.bW=K;
	mm.Init();
	mm.BlurMinimumEdge();

	for(int x=0;x<data.size();x++)
		for(int y=0;y<data[0].size();y++)
			data[x][y]=mm.data[x][y];
}
void EdgeDetection::Compass(vector<vector<double>> &data, vector<vector<int>> &gradDirection, double tVal)
{
	/*
		y-1	 y	y+1
		---|---|----
	x-1| 1	 2	 3
	x  | 8	 0	 4
	x+1| 7	 6	 5

	*/
	double W1[3][3]={ 2.0, 1.0, 0.0,
					  1.0, 0.0,-1.0,
					  0.0,-1.0,-2.0};
	double W2[3][3]={ 1.0, 2.0, 1.0,
					  0.0, 0.0, 0.0,
					 -1.0,-2.0,-1.0};
	double W3[3][3]={ 0.0, 1.0, 2.0, 
					 -1.0, 0.0, 1.0,
					 -2.0,-1.0, 0.0};
	double W4[3][3]={-1.0, 0.0, 1.0, 
					 -2.0, 0.0, 2.0,
					 -1.0, 0.0, 1.0};
	double W5[3][3]={-2.0,-1.0, 0.0,
					 -1.0, 0.0, 1.0,
					  0.0, 1.0, 2.0};
	double W6[3][3]={-1.0,-2.0,-1.0,
					  0.0, 0.0, 0.0,
					  1.0, 2.0, 1.0};
	double W7[3][3]={ 0.0,-1.0,-2.0, 
					  1.0, 0.0,-1.0,
					  2.0, 1.0, 0.0};
	double W8[3][3]={ 1.0, 0.0,-1.0, 
					  2.0, 0.0,-2.0,
					  1.0, 0.0,-1.0};
	
	vector<vector<double>> temp(data.size(),vector<double>(data[0].size(),0.0));
	
	for(int x=1;x<data.size()-1;x++)
	{
		for(int y=1;y<data[0].size()-1;y++)
		{
			double sum1=0.0;
			double sum2=0.0;
			double sum3=0.0;
			double sum4=0.0;
			double sum5=0.0;
			double sum6=0.0;
			double sum7=0.0;
			double sum8=0.0;

			for(int _x=0;_x<3;_x++)
			{
				for(int _y=0;_y<3;_y++)
				{
					int cX=x-1+_x;
					int cY=y-1+_y;

					sum1+=data[cX][cY]*W1[_x][_y];
					sum2+=data[cX][cY]*W2[_x][_y];
					sum3+=data[cX][cY]*W3[_x][_y];
					sum4+=data[cX][cY]*W4[_x][_y];
					sum5+=data[cX][cY]*W5[_x][_y];
					sum6+=data[cX][cY]*W6[_x][_y];
					sum7+=data[cX][cY]*W7[_x][_y];
					sum8+=data[cX][cY]*W8[_x][_y];
				}
			}
			if(sum1>sum2)
			{
				temp[x][y]=sum1;
				gradDirection[x][y]=1;
			}
			else
			{
				temp[x][y]=sum2;
				gradDirection[x][y]=2;
			}
			if(temp[x][y]<sum3)
			{
				temp[x][y]=sum3;
				gradDirection[x][y]=3;
			}
			if(temp[x][y]<sum4)
			{
				temp[x][y]=sum4;
				gradDirection[x][y]=4;
			}
			if(temp[x][y]<sum5)
			{
				temp[x][y]=sum5;
				gradDirection[x][y]=5;
			}
			if(temp[x][y]<sum6)
			{
				temp[x][y]=sum6;
				gradDirection[x][y]=6;
			}
			if(temp[x][y]<sum7)
			{
				temp[x][y]=sum7;
				gradDirection[x][y]=7;
			}
			if(temp[x][y]<sum8)
			{
				temp[x][y]=sum8;
				gradDirection[x][y]=8;
			}
		}
	}
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(temp[x][y]<tVal)
				data[x][y]=temp[x][y];
			else
				data[x][y]=tVal;
		}
	}

	for(int x=0;x<data.size();x++)
	{
		data[x][0]=data[x][1];
		data[x][data[0].size()-1]=data[x][data[0].size()-2];
	}
	for(int y=0;y<data[0].size();y++)
	{
		data[0][y]=data[1][y];
		data[data.size()-1][y]=data[data.size()-2][y];
	}
}
void EdgeDetection::MorphologicalGradient(vector<vector<double>> &data, vector<vector<int>> &gradDirection)
{
	vector<vector<double>> output=data;
	
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			double val=0.0;
			gradDirection[x][y]=GetMinValDirection(x,y,data,val);
			output[x][y]=min(data[x][y]-val,5.0);
		}
	}
	data=output;
}
void EdgeDetection::MorphologicalGradient(vector<vector<double>> &data)
{
	vector<vector<double>> output=data;
	
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			output[x][y]=0.0;
			int sx=max(0,x-1);
			int ex=min(data.size()-1,x+1);
			int sy=max(0,y-1);
			int ey=min(data[0].size()-1,y+1);
			
			for(int _x=sx;_x<=ex;_x++)
				for(int _y=sy;_y<=ey;_y++)
					output[x][y]=max(output[x][y],data[x][y]-data[_x][_y]);
		}
	}
	data=output;
}

void EdgeDetection::InternalMGradient(vector<vector<double>> &data)
{
	MMLibG2D mm;
	mm.data=data;
	mm.Init();
	mm.FastErode(1);
	SubtractData(data,mm.data);
}
void EdgeDetection::ExternalMGradient(vector<vector<double>> &data)
{
	MMLibG2D mm;
	mm.data=data;
	mm.Init();
	mm.FastDilate(1);
	SubtractData(mm.data,data);
	data=mm.data;
}

void EdgeDetection::MGradient(vector<vector<double>> &data)
{
	vector<vector<double>> exData=data;
	ExternalMGradient(exData);
	InternalMGradient(data);
	AddData(data,exData);
}
void EdgeDetection::LoGEdges(vector<vector<double>> &data)
{
	vector<vector<double>> tmpData=data;
	
	Convolution conv;
	
	conv.data=data;
	conv.Init();
	conv.KLoG(5,3);
	conv.Convolve();

	SubtractData(tmpData,conv.data,data);
}
void EdgeDetection::MeanSquareDifff(vector<vector<double>> &data)
{
	
}
void EdgeDetection::BlobDetection(vector<vector<double>> data, vector<vector<int>>& regions, int noLevels)
{
	vector<vector<vector<double>>> levels(noLevels,vector<vector<double>>(data.size(),vector<double>(data[0].size(),0.0)));
	Convolution conv;
	conv.data=data;
	conv.Init();
	
	/*START: Blob detection*/
	for(int level=0;level<noLevels;level++)
	{
		double lStd=1.0*(double)level+1.0;
		conv.KGauss(noLevels,lStd);
		//conv.KLoG(5,lStd);
		conv.Convolve();

		SubtractData(data,conv.data,levels[level]);
		MultiplyData(levels[level],lStd);
		data=conv.data;
	}
	/*START: Blob detection*/
	
	vector<POINT> maxList;
	vector<int> premer;
	int winSize=1;
	for(int level=1;level<noLevels-1;level++)
	{
		for(int x=1;x<levels[0].size()-1;x++)
		{
			for(int y=1;y<levels[0][0].size()-1;y++)
			{
				int sl=max(0,level-winSize);
				int el=min(levels.size()-1,level+winSize);
				int sx=max(0,x-winSize);
				int ex=min(levels[0].size()-1,x+winSize);
				int sy=max(0,y-winSize);
				int ey=min(levels[0][0].size()-1,y+winSize);
				
				bool isMax=true;
				for(int _l=sl;_l<=el;_l++)
				{
					for(int _x=sx;_x<=ex;_x++)
					{
						for(int _y=sy;_y<=ey;_y++)
						{
							if(levels[_l][_x][_y] > levels[level][x][y])
								isMax=false;
						}
					}
				}
				if(isMax)
				{
					DrawDisk(regions,x,y,level+1,level+1);
				}
			}
		}
	}
}
int  EdgeDetection::GetMinValDirection(int x, int y, vector<vector<double>>& data,double& val)
{
	int winSize=1;
	int sx=max(0,x-winSize);
	int ex=min(data.size()-1,x+winSize);
	int sy=max(0,y-winSize);
	int ey=min(data[0].size()-1,y+winSize);
	
	val=data[x][y];
	int direction=0;
	
	for(int _x=sx;_x<=ex;_x++)
	{
		for(int _y=sy;_y<=ey;_y++)
		{
			if(val>data[_x][_y])
			{
				val=data[_x][_y];
				if(_x==x-1 && _y==y-1)
					direction=1;
				else if( _x==x-1 && _y==y)
					direction=2;
				else if( _x==x-1 && _y==y+1)
					direction=3;
				else if( _x==x && _y==y+1)
					direction=4;
				else if( _x==x+1 && _y==y+1)
					direction=5;
				else if( _x==x+1 && _y==y)
					direction=6;
				else if( _x==x+1 && _y==y-1)
					direction=7;
				else if( _x==x && _y==y-1)
					direction=8;
			}
		}
	}
	return direction;
}
void EdgeDetection::LinearRegression(vector<vector<Vector3f>> &grid, vector<vector<double>> &data, int winSize)
{
	vector<vector<vector<double>>> resStack(data.size(),vector<vector<double>>(data[0].size(),vector<double>(8,DBL_MAX)));
	int fullWSize=winSize*2+1;
	int noPnts=fullWSize*fullWSize;
	int minx=0;
	int maxx=data.size()-1;
	int miny=0;
	int maxy=data[0].size()-1;
	
	double plane[4];
	double* pnts=new double[noPnts*3];

	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{	
			int sx=max(0,x-winSize);
			int ex=min(data.size()-1,x+winSize);
			int sy=max(0,y-winSize);
			int ey=min(data[0].size()-1,y+winSize);
			
			int i=0;
			for(int _x=sx;_x<=ex;_x++)
			{
				for(int _y=sy;_y<=ey;_y++)
				{
					pnts[i++]=grid[_x][_y].x;
					pnts[i++]=grid[_x][_y].y;
					pnts[i++]=grid[_x][_y].z;
				}
			}
			getBestFitPlane(i/3,pnts,sizeof(double)*3,NULL,0,plane);
			Vector3f norm(plane[0],plane[1],plane[2]);norm.Normalize();
			data[x][y]=abs(norm.z);
		}
	}
	delete[] pnts;
}
void EdgeDetection::ImageEnhancement(vector<vector<double>> &data, int winSize)
{
	vector<vector<double>> tData=data;
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			double tVal=0;
			int noElem=0;

			int sx=max(0,x-winSize);
			int ex=min(data.size()-1,x+winSize);
			int sy=max(0,y-winSize);
			int ey=min(data[0].size()-1,y+winSize);
			
			for(int _x=sx;_x<=ex;_x++)
			{
				for(int _y=sy;_y<=ey;_y++)
				{
					if(x==_x && y==_y)
						continue;
					tVal+=tData[_x][_y];
					noElem++;
				}
			}
			//data[x][y]=(double)noElem*tData[x][y]-tVal;
			data[x][y]=tVal/(double)noElem-tData[x][y];
		}
	}
	CropData(data,-10.0,10.0);
}
void EdgeDetection::ImageCompassEnhancement(vector<vector<double>> &data, int winSize)
{
	vector<vector<double>> orgData=data;
	//vector<vector<vector<double>>> rStack(data.size(),vector<vector<>>(data[0].size()));
	InitData(data);
	for(int x=1;x<data.size()-1;x++)
	{
		for(int y=1;y<data[0].size()-1;y++)
		{
			double tVal=0;
			data[x][y]=2*orgData[x][y]-(orgData[x-1][y-1]+orgData[x+1][y+1]);
			data[x][y]=min(2*orgData[x][y]-(orgData[x-1][y]+orgData[x+1][y]),data[x][y]);
			data[x][y]=min(2*orgData[x][y]-(orgData[x-1][y+1]+orgData[x+1][y-1]),data[x][y]);
			data[x][y]=min(2*orgData[x][y]-(orgData[x][y-1]+orgData[x][y+1]),data[x][y]);
		}
	}
}
void EdgeDetection::HighPassFilter(vector<vector<double>> &data, int winSize)
{
	vector<vector<double>> outData=data;
	vector<vector<double>> kern(winSize*2+1,vector<double>(winSize*2+1,0.0));
	double sum=0.0;
	
	for(int x=-winSize;x<=winSize;x++)
	{
		for(int y=-winSize;y<=winSize;y++)
		{
			if(!x && !y)
				continue;
			kern[x+winSize][y+winSize]=-1.0/sqrt((double)(x*x+y*y));
			kern[winSize][winSize]+=abs(kern[x+winSize][y+winSize]);
		}
	}
	
	int maxx=data.size()-1;
	int maxy=data[0].size()-1;
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			int kx=0;
			double val=0.0;
			for(int _x=x-winSize;_x<=x+winSize;_x++,kx++)
			{
				int ky=0;
				for(int _y=y-winSize;_y<=y+winSize;_y++,ky++)
				{
					int ox=max(min(_x,maxx),0);
					int oy=max(min(_y,maxy),0);
					val+=(outData[ox][oy]*kern[kx][ky]);
				}
			}
			data[x][y]=val;
		}
	}
}
void EdgeDetection::_BFPGetPntListTop(int& noPnts, double* pnts, vector<vector<Vector3f>>& grid, int x, int y, int winSize)
{
	noPnts=0;
	if(x==0)//V zgornji vrstici ni top viewja
		return;
	int sx=max(0,x-winSize);
	int ex=x;
	int sy=max(0,y-winSize);
	int ey=min(grid[0].size()-1,y+winSize);
	
	for(int _x=sx;_x<=ex;_x++)
	{
		for(int _y=sy;_y<=ey;_y++)
		{
			pnts[noPnts++]=grid[_x][_y].x;
			pnts[noPnts++]=grid[_x][_y].y;
			pnts[noPnts++]=grid[_x][_y].z;
		}
	}
}
void EdgeDetection::_BFPGetPntListBot(int& noPnts, double* pnts, vector<vector<Vector3f>>& grid, int x, int y, int winSize)
{
	noPnts=0;
	if(x==grid.size()-1)//V spodnji vrstici ni bottom viewja
		return;
	int sx=x;
	int ex=min(grid.size()-1,x+winSize);
	int sy=max(0,y-winSize);
	int ey=min(grid[0].size()-1,y+winSize);
	
	for(int _x=sx;_x<=ex;_x++)
	{
		for(int _y=sy;_y<=ey;_y++)
		{
			pnts[noPnts++]=grid[_x][_y].x;
			pnts[noPnts++]=grid[_x][_y].y;
			pnts[noPnts++]=grid[_x][_y].z;
		}
	}
}
double EdgeDetection::_BFPErrorEstimation(int noPnts, double* pnts)
{
	if(noPnts<4)
		return DBL_MAX;

	double outData=0.0;
	double plane[4];
	getBestFitPlane(noPnts,pnts,sizeof(double)*3,NULL,0,plane);
	for(int i=0;i<noPnts;i++)
	{
		double error=pnts[i*3+0]*plane[0]+pnts[i*3+1]*plane[1]+pnts[i*3+2]*plane[2]+plane[3];
		outData+=(error*error);
	}
	return outData;
}
double EdgeDetection::_BFPErrorEstimation(int noPnts, double* pnts, double* plane)
{
	if(noPnts<4)
		return DBL_MAX;

	double outData=0.0;
	getBestFitPlane(noPnts,pnts,sizeof(double)*3,NULL,0,plane);
	for(int i=0;i<noPnts;i++)
	{
		double error=pnts[i*3+0]*plane[0]+pnts[i*3+1]*plane[1]+pnts[i*3+2]*plane[2]+plane[3];
		outData+=(error*error);
	}
	return outData;
}
double EdgeDetection::_BFPErrorEstimation(vector<vector<Vector3f>>& grid, int x, int y, vector<double>& plane, int winSize)
{
	double outData=0.0;

	int sx=max(0,x-winSize);
	int ex=min(grid.size()-1,x+winSize);
	int sy=max(0,y-winSize);
	int ey=min(grid[0].size()-1,y+winSize);
	
	for(int _x=sx;_x<=ex;_x++)
	{
		for(int _y=sy;_y<=ey;_y++)
		{
			double error=plane[0]*grid[_x][_y].x+
						 plane[1]*grid[_x][_y].y+
						 plane[2]*grid[_x][_y].z+
						 plane[3];
			outData+=(error*error);
		}
	}
	return outData;
}
void EdgeDetection::BFPlanes(vector<vector<Vector3f>>& grid, vector<vector<vector<double>>>& data, vector<vector<double>>& errorData, int winSize)
{
	vector<vector<vector<double>>> resStack(data.size(),vector<vector<double>>(data[0].size(),vector<double>(8,DBL_MAX)));
	int fullWSize=winSize*2+1;
	int noPnts=fullWSize*fullWSize;
	int minx=0;
	int maxx=data.size()-1;
	int miny=0;
	int maxy=data[0].size()-1;

	double plane[4];
	double* pnts=new double[noPnts*3];

	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{	
			int sx=max(0,x-winSize);
			int ex=min(data.size()-1,x+winSize);
			int sy=max(0,y-winSize);
			int ey=min(data[0].size()-1,y+winSize);
			
			int i=0;
			for(int _x=sx;_x<=ex;_x++)
			{
				for(int _y=sy;_y<=ey;_y++)
				{
					pnts[i++]=grid[_x][_y].x;
					pnts[i++]=grid[_x][_y].y;
					pnts[i++]=grid[_x][_y].z;
				}
			}
			errorData[x][y]=_BFPErrorEstimation(i/3,pnts,&plane[0]);
			data[x][y][0]=plane[0];
			data[x][y][1]=plane[1];
			data[x][y][2]=plane[2];
			data[x][y][3]=plane[3];
			errorData[x][y]=_BFPErrorEstimation(grid,x,y,data[x][y],winSize);
		}
	}
	delete[] pnts;
}
void EdgeDetection::BFPFiltering8(vector<vector<Vector3f>> &grid, vector<vector<double>> &data, int winSize)
{
	vector<vector<vector<double>>> resStack(data.size(),vector<vector<double>>(data[0].size(),vector<double>(8,DBL_MAX)));
	int fullWSize=winSize*2+1;
	int noPnts=fullWSize*fullWSize;
	int minx=0;
	int maxx=data.size()-1;
	int miny=0;
	int maxy=data[0].size()-1;

	double plane[4];
	double* pnts=new double[noPnts*3];

	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{	
			int sx=max(0,x-winSize);
			int ex=min(data.size()-1,x+winSize);
			int sy=max(0,y-winSize);
			int ey=min(data[0].size()-1,y+winSize);
			
			int i=0;
			for(int _x=sx;_x<=ex;_x++)
			{
				for(int _y=sy;_y<=ey;_y++)
				{
					pnts[i++]=grid[_x][_y].x;
					pnts[i++]=grid[_x][_y].y;
					pnts[i++]=grid[_x][_y].z;
				}
			}
			double response=_BFPErrorEstimation(i/3,pnts);
			//Assign top response
			if(x>minx)				resStack[x-1][y][0]=response;
			//Assign top-right response
			if(x>minx && y<maxy)	resStack[x-1][y+1][1]=response;
			//Assign right response
			if(y<maxy)				resStack[x][y+1][2]=response;
			//Assign bottom-right response
			if(x<maxx && y<maxy)	resStack[x+1][y+1][3]=response;
			//Assign bottom response
			if(x<maxx)				resStack[x+1][y][4]=response;
			//Assign bottom-left response
			if(x<maxx && y>miny)	resStack[x+1][y-1][5]=response;
			//Assign left response
			if(y>miny)				resStack[x][y-1][6]=response;
			//Assign top-left response
			if(x>minx && y>miny)	resStack[x-1][y-1][7]=response;
		}
	}
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			data[x][y]=(double)*min_element(resStack[x][y].begin(),resStack[x][y].end());
		}
	}
	delete[] pnts;
}
void EdgeDetection::BFPFiltering4(vector<vector<Vector3f>> &grid, vector<vector<double>> &data, int winSize)
{
	/*START: Init support data*/
	vector<vector<vector<double>>> resStack(data.size(),vector<vector<double>>(data[0].size(),vector<double>(4,DBL_MAX)));
	int fullWSize=winSize*2+1;
	int noPnts=fullWSize*fullWSize-1;
	int minx=0;
	int maxx=data.size()-1;
	int miny=0;
	int maxy=data[0].size()-1;
	/*END: Init support data*/

	double plane[4];
	double* pnts=new double[noPnts*3];

	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{	
			int sx=max(0,x-winSize);
			int ex=min(data.size()-1,x+winSize);
			int sy=max(0,y-winSize);
			int ey=min(data[0].size()-1,y+winSize);
			
			int i=0;
			for(int _x=sx;_x<=ex;_x++)
			{
				for(int _y=sy;_y<=ey;_y++)
				{
					int cDist=abs(x-_x)+abs(y-_y);
					if(cDist>winSize)	
						continue;
					pnts[i++]=grid[_x][_y].x;
					pnts[i++]=grid[_x][_y].y;
					pnts[i++]=grid[_x][_y].z;
				}
			}
			double response=_BFPErrorEstimation(i/3,pnts);
			//Assign top response
			if(x-winSize>=minx)		resStack[x-winSize][y][0]=response;
			//Assign right response
			if(y+winSize<=maxy)		resStack[x][y+winSize][1]=response;
			//Assign bottom response
			if(x+winSize<=maxx)		resStack[x+winSize][y][2]=response;
			//Assign left response
			if(y-winSize>=miny)		resStack[x][y-winSize][3]=response;
		}
	}
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			data[x][y]=(double)*min_element(resStack[x][y].begin(),resStack[x][y].end());
		}
	}
	delete[] pnts;
}
void EdgeDetection::BFPFiltering4(vector<vector<Vector3f>>& grid, vector<vector<vector<double>>>& fStack, int winSize)
{
	/*START: Init support data*/
	vector<vector<vector<double>>> resStack(grid.size(),vector<vector<double>>(grid[0].size(),vector<double>(4,DBL_MAX)));
	int fullWSize=winSize*2+1;
	int noPnts=fullWSize*fullWSize-1;
	int minx=0;
	int maxx=grid.size()-1;
	int miny=0;
	int maxy=grid[0].size()-1;
	/*END: Init support data*/

	double plane[4];
	double* pnts=new double[noPnts*3];

	for(int x=0;x<grid.size();x++)
	{
		for(int y=0;y<grid[0].size();y++)
		{	
			int sx=max(0,x-winSize);
			int ex=min(grid.size()-1,x+winSize);
			int sy=max(0,y-winSize);
			int ey=min(grid[0].size()-1,y+winSize);
			
			int i=0;
			for(int _x=sx;_x<=ex;_x++)
			{
				for(int _y=sy;_y<=ey;_y++)
				{
					int cDist=abs(x-_x)+abs(y-_y);
					if(cDist>winSize)	
						continue;
					pnts[i++]=grid[_x][_y].x;
					pnts[i++]=grid[_x][_y].y;
					pnts[i++]=grid[_x][_y].z;
				}
			}
			double response=_BFPErrorEstimation(i/3,pnts);
			//Assign top response
			if(x-winSize>=minx)		resStack[x-winSize][y][0]=response;
			//Assign right response
			if(y+winSize<=maxy)		resStack[x][y+winSize][1]=response;
			//Assign bottom response
			if(x+winSize<=maxx)		resStack[x+winSize][y][2]=response;
			//Assign left response
			if(y-winSize>=miny)		resStack[x][y-winSize][3]=response;
		}
	}
	fStack=resStack;
}
void EdgeDetection::BFPFiltering4(vector<vector<Vector3f>> &grid, vector<vector<double>> &data, vector<vector<int>>& oImg, int winSize)
{
	/*START: Init support data*/
	vector<vector<vector<double>>> resStack(data.size(),vector<vector<double>>(data[0].size(),vector<double>(4,DBL_MAX)));
	int fullWSize=winSize*2+1;
	int noPnts=fullWSize*fullWSize-1;
	int minx=0;
	int maxx=data.size()-1;
	int miny=0;
	int maxy=data[0].size()-1;
	/*END: Init support data*/

	double plane[4];
	double* pnts=new double[noPnts*3];

	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{	
			int sx=max(0,x-winSize);
			int ex=min(data.size()-1,x+winSize);
			int sy=max(0,y-winSize);
			int ey=min(data[0].size()-1,y+winSize);
			
			int i=0;
			for(int _x=sx;_x<=ex;_x++)
			{
				for(int _y=sy;_y<=ey;_y++)
				{
					int cDist=(int)abs((double)x-(double)_x)+abs((double)y-(double)_y);
					if(cDist>winSize)	
						continue;
					pnts[i++]=grid[_x][_y].x;
					pnts[i++]=grid[_x][_y].y;
					pnts[i++]=grid[_x][_y].z;
				}
			}
			double response=_BFPErrorEstimation(i/3,pnts);
			//Assign top response
			if(x-winSize>=minx)		resStack[x-winSize][y][0]=response;
			//Assign right response
			if(y+winSize<=maxy)		resStack[x][y+winSize][1]=response;
			//Assign bottom response
			if(x+winSize<=maxx)		resStack[x+winSize][y][2]=response;
			//Assign left response
			if(y-winSize>=miny)		resStack[x][y-winSize][3]=response;
		}
	}
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			std::vector<double>::iterator it=min_element(resStack[x][y].begin(),resStack[x][y].end());
			data[x][y]=*it;
			oImg[x][y]=it-resStack[x][y].begin()+1;
		}
	}
	delete[] pnts;
}
void EdgeDetection::MyPlaneDetection(vector<vector<Vector3f>>& grid, vector<vector<double>>& data)
{
	/*START: Generating window*/
	int winSize=3;
	int fulWinSize=winSize*2+1;
	vector<vector<double>> dWin(fulWinSize,vector<double>(fulWinSize,0.0));
	for(int x=0;x<fulWinSize;x++)
	{
		for(int y=0;y<fulWinSize;y++)
		{
			double dX=x-winSize;
			double dY=y-winSize;
			dWin[x][y]=sqrt(dX*dX+dY*dY);
		}
	}
	/*END: Generating window*/
	int kSteps=40;
	double kMin=0.0;
	double kMax=2.0;
	double kStep=(kMax-kMin)/(double)kSteps;
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			data[x][y]=0.0;
			if(x==0 || x==data.size()-1 || y==0 || y==data[0].size()-1)
				continue;

			data[x][y]+=grid[x-1][y].z-grid[x+1][y].z;
			data[x][y]+=grid[x][y-1].z-grid[x][y+1].z;
		}
	}
}
//Thresholds
void CThresholding::CostantThreshold(vector<vector<double>> &data, vector<vector<int>> &regions, double tVal)
{
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(data[x][y]>tVal)
				regions[x][y]=1;
			else
				regions[x][y]=0;
		}
	}
}
void CThresholding::CostantThreshold(vector<vector<int>> &data, vector<vector<int>> &regions, double tVal)
{
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(data[x][y]>tVal)
				regions[x][y]=1;
			else
				regions[x][y]=0;
		}
	}
}
void CThresholding::CostantBandPassThreshold(vector<vector<double>> &data, vector<vector<int>> &regions, double tLow, double tHigh)
{
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(data[x][y]>=tLow && data[x][y]<=tHigh)
				regions[x][y]=1;
			else
				regions[x][y]=0;
		}
	}
}
void CThresholding::CostantThresholdBackground(vector<vector<double>> &data, vector<vector<int>> &regions, double tVal)
{
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(data[x][y]<tVal)
				regions[x][y]=0;
		}
	}
}
void CThresholding::CostantThresholdBackground(vector<vector<double>> &data, double tVal)
{
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(data[x][y]<tVal)
				data[x][y]=0.0;
		}
	}
}
void CThresholding::AdaptiveThreshold(vector<vector<double>> &data, vector<vector<int>> &regions, double addVal, int winSize)
{
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			double tVal=0;
			int noElem=0;

			int sx=max(0,x-winSize);
			int ex=min(data.size()-1,x+winSize);
			int sy=max(0,y-winSize);
			int ey=min(data[0].size()-1,y+winSize);
			
			for(int _x=sx;_x<=ex;_x++)
			{
				for(int _y=sy;_y<=ey;_y++)
				{
					tVal+=data[_x][_y];
					noElem++;
				}
			}	

			tVal=tVal/(double)noElem;
			tVal+=addVal;

			if(data[x][y]>tVal)
				regions[x][y]=1;
			else
				regions[x][y]=0;
		}
	}
}
void CThresholding::AutomaticDMThreshold(vector<vector<double>> &data, vector<vector<int>> &regions, double devFactor, double addVal)
{
	/*START: izraèunamo povpreèje*/
	double avg=0.0;
	int sz=0;
		
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			avg+=data[x][y];
			sz++;
		}
	}
	avg/=(double)sz;
	/*END: izraèunamo povpreèje*/
		
	/*START: izraèun deviacije*/
	double dev2=0.0;
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			double clen=data[x][y]-avg;
			dev2+=(clen*clen);
		}
	}
	dev2/=(double)sz;
	double dev=sqrt(dev2);
	double tVal=avg+devFactor*dev+addVal;
	
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(data[x][y]>tVal)
				regions[x][y]=1;
			else
				regions[x][y]=0;
		}
	}
}
void CThresholding::AdaptiveAutomaticDMThreshold(vector<vector<double>> &data, vector<vector<int>> &regions, int winSize)
{
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			int sx=max(0,x-winSize);
			int ex=min(data.size()-1,x+winSize);
			int sy=max(0,y-winSize);
			int ey=min(data[0].size()-1,y+winSize);

			/*START: izraèunamo povpreèje*/
			double avg=0.0;
			int sz=0;
				
			for(int x=sx;x<=ex;x++)
			{
				for(int y=sy;y<=ey;y++)
				{
					avg+=data[x][y];
					sz++;
				}
			}
			avg/=(double)sz;
			/*END: izraèunamo povpreèje*/
				
			/*START: izraèun deviacije*/
			double dev2=0.0;
			for(int x=sx;x<=ex;x++)
			{
				for(int y=sy;y<=ey;y++)
				{
					double clen=data[x][y]-avg;
					dev2+=(clen*clen);
				}
			}
			dev2/=(double)sz;
			double dev=sqrt(dev2);
			/*START: izraèun deviacije*/

			double tVal=avg+3*dev;
			
			if(data[x][y]>tVal)
				regions[x][y]=1;
			else
				regions[x][y]=0;
		}
	}
}
void CThresholding::AlphaTrimmedMean(vector<vector<double>> &data, int winSize, int noTrimmedValues, vector<vector<double>> &output)
{
	vector<double> valueList;

	valueList.reserve((winSize*2+1)*(winSize*2+1));
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			valueList.clear();

			int sx=max(0,x-winSize);
			int ex=min(data.size()-1,x+winSize);
			int sy=max(0,y-winSize);
			int ey=min(data[0].size()-1,y+winSize);
			
			for(int _x=sx;_x<=ex;_x++)
				for(int _y=sy;_y<=ey;_y++)
					valueList.push_back(data[_x][_y]);
			
			sort(valueList.begin(),valueList.end());

			double mean=0.0;
			int del=0;
			int end=valueList.size()-noTrimmedValues;
			for(int i=noTrimmedValues; i<end;i++)
			{
				mean+=valueList[i];
				del++;
			}
			output[x][y]=mean/(double)del;	
		}
	}
}
//Flood Fill
CFloodFill::CFloodFill()
{
	
}
void CFloodFill::_ChangeRegionIndex(vector<vector<int>> &inData,vector<vector<int>> &outData, POINT sPoint, int newIndex)
{
	int inIndex=inData[sPoint.x][sPoint.y];
	outData[sPoint.x][sPoint.y]=newIndex;
	candidates.push_back(sPoint);

	while(candidates.size())
	{
		POINT start=candidates.back();
		candidates.pop_back();

		POINT sosedi[4];
		
		sosedi[0].x=start.x-1;
		sosedi[0].y=start.y;
		sosedi[1].x=start.x+1;
		sosedi[1].y=start.y;
		
		sosedi[2].x=start.x;
		sosedi[2].y=start.y-1;
		sosedi[3].x=start.x;
		sosedi[3].y=start.y+1;
		
		for(int i=0;i<4;i++)
		{
			if( sosedi[i].x>=0 && sosedi[i].x<inData.size() && 
				sosedi[i].y>=0 && sosedi[i].y<inData[0].size())
			{
				if(inData[sosedi[i].x][sosedi[i].y] == inIndex && !outData[sosedi[i].x][sosedi[i].y])
				{
					outData[sosedi[i].x][sosedi[i].y]=newIndex;
					candidates.push_back(sosedi[i]);
				}
			}
		}
	}
	candidates.clear();
}
int CFloodFill::_FindElement(vector<int>& values, int element)
{	
	for(int i=0;i<values.size();i++)
		if(values[i]==element)
			return i;
	return -1;
}
bool CFloodFill::_FFLimitedOnBB(vector<vector<int>> &output, POINT sPoint, int regIndex, vector<vector<int>> &borderMap, CBBox bbox)
{
	bool retVal=true;
	
	candidates.push_back(sPoint);
	output[sPoint.x][sPoint.y]=regIndex;

	while(candidates.size())
	{
		POINT start=candidates.back();
		candidates.pop_back();
		
		int x=start.x;		int y=start.y;
		POINT sosedi[8];	
		sosedi[0].x=x-1;	sosedi[0].y=y-1;
		sosedi[1].x=x-1;	sosedi[1].y=y;
		sosedi[2].x=x-1;	sosedi[2].y=y+1;
		sosedi[3].x=x;		sosedi[3].y=y+1;
		sosedi[4].x=x+1;	sosedi[4].y=y+1;
		sosedi[5].x=x+1;	sosedi[5].y=y;
		sosedi[6].x=x+1;	sosedi[6].y=y-1;
		sosedi[7].x=x;		sosedi[7].y=y-1;
		
		output[x][y]=regIndex;
		for(int i=0;i<8;i++)
		{
			if( sosedi[i].x>=0 && sosedi[i].x<output.size() && 
				sosedi[i].y>=0 && sosedi[i].y<output[0].size())
			{
				if( sosedi[i].x>bbox.max.x || sosedi[i].y>bbox.max.y ||
					sosedi[i].x<bbox.min.x || sosedi[i].y<bbox.min.y )
				{
					retVal=false;
				}
				else if(!output[sosedi[i].x][sosedi[i].y] && !borderMap[sosedi[i].x][sosedi[i].y])
				{
					output[sosedi[i].x][sosedi[i].y]=regIndex;
					candidates.push_back(sosedi[i]);
				}
			}
			if(!retVal)
				break;
		}
		if(!retVal)
			break;
	}
	candidates.clear();
	return retVal;
}
void CFloodFill::Flood(vector<vector<int>> &data, POINT sPoint, int regIndex, int restrictionRegion)
{
	candidates.push_back(sPoint);
	
	while(candidates.size())
	{
		POINT start=candidates.back();
		candidates.pop_back();
		data[start.x][start.y]=regIndex;
		
		int x=start.x;int y=start.y;
		POINT sosedi[8];	
		sosedi[0].x=x-1;	sosedi[0].y=y-1;
		sosedi[1].x=x-1;	sosedi[1].y=y;
		sosedi[2].x=x-1;	sosedi[2].y=y+1;
		sosedi[3].x=x;		sosedi[3].y=y+1;
		sosedi[4].x=x+1;	sosedi[4].y=y+1;
		sosedi[5].x=x+1;	sosedi[5].y=y;
		sosedi[6].x=x+1;	sosedi[6].y=y-1;
		sosedi[7].x=x;		sosedi[7].y=y-1;
		
		for(int i=0;i<8;i++)
		{
			if( sosedi[i].x>=0 && sosedi[i].x<data.size() && 
				sosedi[i].y>=0 && sosedi[i].y<data[0].size())
			{
				if(data[sosedi[i].x][sosedi[i].y]!= restrictionRegion && data[sosedi[i].x][sosedi[i].y]!=regIndex)
					candidates.push_back(sosedi[i]);
			}
		}
	}
	candidates.clear();
}
void CFloodFill::Flood2(vector<vector<int>> &data, vector<vector<int>> &data_out, POINT sPoint, int regIndex_out, int regIndex, int restrictionRegion)
{
	candidates.push_back(sPoint);

	while(candidates.size())
	{
		POINT start=candidates.back();
		candidates.pop_back();
		data_out[start.x][start.y]=regIndex_out;
		data[start.x][start.y]=0;
		int x=start.x;int y=start.y;
		POINT sosedi[8];	
		sosedi[0].x=x-1;	sosedi[0].y=y-1;
		sosedi[1].x=x-1;	sosedi[1].y=y;
		sosedi[2].x=x-1;	sosedi[2].y=y+1;
		sosedi[3].x=x;		sosedi[3].y=y+1;
		sosedi[4].x=x+1;	sosedi[4].y=y+1;
		sosedi[5].x=x+1;	sosedi[5].y=y;
		sosedi[6].x=x+1;	sosedi[6].y=y-1;
		sosedi[7].x=x;		sosedi[7].y=y-1;

		for(int i=0;i<8;i++)
		{
			if( sosedi[i].x>=0 && sosedi[i].x<data.size() && 
				sosedi[i].y>=0 && sosedi[i].y<data[0].size())
			{
				if(data[sosedi[i].x][sosedi[i].y]!= restrictionRegion && data[sosedi[i].x][sosedi[i].y]==regIndex)
					candidates.push_back(sosedi[i]);
			}
		}
	}
	candidates.clear();
}
int CFloodFill::CondenseRegions(vector<vector<int>> &data)
{
	vector<vector<int>> tmpData(data.size(),vector<int>(data[0].size(),0));
	int noReg=1;

	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(!tmpData[x][y] && data[x][y])
			{
				POINT sPoint={x,y};
				_ChangeRegionIndex(data,tmpData,sPoint,noReg);
				noReg++;
			}
		}
	}
	data=tmpData;
	return noReg;
}
void CFloodFill::ChangeRegionIndex(vector<vector<int>> &data, int x, int y, int newIndex)
{
	POINT pnt={x,y};
	ChangeRegionIndex(data, pnt, newIndex);
}
void CFloodFill::ChangeRegionIndex(vector<vector<int>> &data, POINT sPoint, int newIndex)
{
	candidates.push_back(sPoint);
	int inIndex=data[sPoint.x][sPoint.y];
	data[sPoint.x][sPoint.y]=newIndex;

	while(candidates.size())
	{
		POINT start=candidates.back();
		candidates.pop_back();

		POINT sosedi[4];

		sosedi[0].x=start.x-1;
		sosedi[0].y=start.y;
		sosedi[1].x=start.x+1;
		sosedi[1].y=start.y;
		
		sosedi[2].x=start.x;
		sosedi[2].y=start.y-1;
		sosedi[3].x=start.x;
		sosedi[3].y=start.y+1;
		
		for(int i=0;i<4;i++)
		{
			if( sosedi[i].x>=0 && sosedi[i].x<data.size() && 
				sosedi[i].y>=0 && sosedi[i].y<data[0].size())
			{
				if(data[sosedi[i].x][sosedi[i].y] == inIndex)
				{
					data[sosedi[i].x][sosedi[i].y]=newIndex;
					candidates.push_back(sosedi[i]);
				}
			}
		}
	}
	candidates.clear();
}
void CFloodFill::ChangeRegionIndex8(vector<vector<int>> &data, POINT sPoint, int newIndex)
{
	candidates.push_back(sPoint);
	int inIndex=data[sPoint.x][sPoint.y];
	data[sPoint.x][sPoint.y]=newIndex;

	while(candidates.size())
	{
		POINT start=candidates.back();
		candidates.pop_back();

		POINT sosedi[8];
		int x=start.x;		int y=start.y;
		sosedi[0].x=x-1;	sosedi[0].y=y-1;
		sosedi[1].x=x-1;	sosedi[1].y=y;
		sosedi[2].x=x-1;	sosedi[2].y=y+1;
		sosedi[3].x=x;		sosedi[3].y=y+1;
		sosedi[4].x=x+1;	sosedi[4].y=y+1;
		sosedi[5].x=x+1;	sosedi[5].y=y;
		sosedi[6].x=x+1;	sosedi[6].y=y-1;
		sosedi[7].x=x;		sosedi[7].y=y-1;
		
		for(int i=0;i<8;i++)
		{
			if( sosedi[i].x>=0 && sosedi[i].x<data.size() && 
				sosedi[i].y>=0 && sosedi[i].y<data[0].size())
			{
				if(data[sosedi[i].x][sosedi[i].y] == inIndex)
				{
					data[sosedi[i].x][sosedi[i].y]=newIndex;
					candidates.push_back(sosedi[i]);
				}
			}
		}
	}
	candidates.clear();
}
/*Pobarva bele regije, ki so oznaèene z 1 in loèene z 0*/
int CFloodFill::WRegionColoring(vector<vector<int>> &input)
{
	int noReg=2;

	for(int x=0;x<input.size();x++)
	{
		for(int y=0;y<input[0].size();y++)
		{
			if(input[x][y]==1)
			{
				POINT pnt;pnt.x=x;pnt.y=y;
				Flood(input,pnt,noReg,0);
				noReg++;
			}
		}
	}
	for(int x=0;x<input.size();x++)
		for(int y=0;y<input[0].size();y++)
			if(input[x][y])
				input[x][y]--;
	return noReg-1;
}
int CFloodFill::RegionColoring(vector<vector<int>> &input)
{
	vector<vector<int>> input2(input.size(),vector<int>(input[0].size(),0));
	int noReg=2;

	for(int x=0;x<input.size();x++)
	{
		for(int y=0;y<input[0].size();y++)
		{
			if(input[x][y]!=0)
			{
				POINT pnt;pnt.x=x;pnt.y=y;
				Flood2(input,input2,pnt,noReg,input[x][y],0);
				noReg++;
			}
		}
	}

	input=input2;

	for(int x=0;x<input.size();x++)
		for(int y=0;y<input[0].size();y++)
			if(input[x][y])
				input[x][y]--;
	return noReg-1;
}
/*Pobarva èrne prazne prostore oznaèene z 0 in loèene z 1*/
int CFloodFill::BRegionColoring(vector<vector<int>> &input)
{
	int noReg=2;

	for(int x=0;x<input.size();x++)
	{
		for(int y=0;y<input[0].size();y++)
		{
			if(input[x][y]==0)
			{
				POINT pnt;pnt.x=x;pnt.y=y;
				Flood(input,pnt,noReg,1);
				noReg++;
			}
		}
	}
	return noReg;
}

/*Pobarvam samo zaprte regije (0-prazna regija, 1-rob)*/
int CFloodFill::CloseRegionsColoring(vector<vector<int>> &input)
{
	/*START: pridobim bboxse regij*/
	vector<vector<int>> edgeMap=input;
	int noEdges=WRegionColoring(edgeMap);

	/*START: set bboxes*/
	vector<CBBox> bbs(noEdges,CBBox(edgeMap.size()-1,edgeMap[0].size()-1,0,0));
	for(int x=0;x<edgeMap.size();x++)
	{
		for(int y=0;y<edgeMap[0].size();y++)
		{
			input[x][y]=0;
			if(!edgeMap[x][y])
				continue;

			if(bbs[edgeMap[x][y]].min.x>x)
				bbs[edgeMap[x][y]].min.x=x;
			if(bbs[edgeMap[x][y]].min.y>y)
				bbs[edgeMap[x][y]].min.y=y;
			if(bbs[edgeMap[x][y]].max.x<x)
				bbs[edgeMap[x][y]].max.x=x;
			if(bbs[edgeMap[x][y]].max.y<y)
				bbs[edgeMap[x][y]].max.y=y;
		}
	}
	/*END: set bboxes*/

	/*START: barvaj regije sosedno od robov*/
	int noRegs=1;
	vector<int> remRegIndex;
	remRegIndex.reserve(noEdges);
	for(int x=0;x<edgeMap.size();x++)
	{
		for(int y=0;y<edgeMap[0].size();y++)
		{
			if(!edgeMap[x][y] || input[x][y])
				continue;

			int sx=max(0,x-1);
			int ex=min(edgeMap.size()-1,x+1);
			int sy=max(0,y-1);
			int ey=min(edgeMap[0].size()-1,y+1);
			
			POINT sPnt={-1,-1};

			for(int _x=sx;_x<=ex;_x++)
			{
				for(int _y=sy;_y<=ey;_y++)
				{
					if(!edgeMap[_x][_y] && !input[_x][_y])
					{
						sPnt.x=_x;
						sPnt.y=_y;
					}
				}
			}
			if(sPnt.x!=-1)
			{
				if(!_FFLimitedOnBB(input,sPnt,noRegs,edgeMap,bbs[edgeMap[x][y]]))
					remRegIndex.push_back(noRegs);
				noRegs++;
			}
		}
	}
	
	for(int x=0;x<edgeMap.size();x++)
	{
		for(int y=0;y<edgeMap[0].size();y++)
		{
			if(!input[x][y])
				continue;
			int rem=_FindElement(remRegIndex,input[x][y]);
			if(rem!=-1)
			{
				POINT pnt={x,y};
				ChangeRegionIndex(input,pnt,0);
			}
		}
	}
	/*END: barvaj regije sosedno od robov*/
	//input=edgeMap;
	return noRegs;	
}
/*Flood fill na grey scale value - zaèetna toèka ki doloèa GS vrednost*/
void CFloodFill::GSFloodFill(vector<vector<double>> &data, POINT sPoint, vector<vector<int>> &output, int regIndex)
{
	candidates.push_back(sPoint);
	output[sPoint.x][sPoint.y]=regIndex;

	while(candidates.size())
	{
		POINT start=candidates.back();
		candidates.pop_back();
		
		int x=start.x;		int y=start.y;
		POINT sosedi[8];	
		sosedi[0].x=x-1;	sosedi[0].y=y-1;
		sosedi[1].x=x-1;	sosedi[1].y=y;
		sosedi[2].x=x-1;	sosedi[2].y=y+1;
		sosedi[3].x=x;		sosedi[3].y=y+1;
		sosedi[4].x=x+1;	sosedi[4].y=y+1;
		sosedi[5].x=x+1;	sosedi[5].y=y;
		sosedi[6].x=x+1;	sosedi[6].y=y-1;
		sosedi[7].x=x;		sosedi[7].y=y-1;
		
		for(int i=0;i<8;i++)
		{
			if( sosedi[i].x>=0 && sosedi[i].x<data.size() && 
				sosedi[i].y>=0 && sosedi[i].y<data[0].size())
			{
				if(	data[sosedi[i].x][sosedi[i].y] == data[sPoint.x][sPoint.y] && 
					output[sosedi[i].x][sosedi[i].y]!=regIndex)
				{
					output[sosedi[i].x][sosedi[i].y]=regIndex;
					candidates.push_back(sosedi[i]);
				}
			}
		}
	}
	candidates.clear();
}
/*GS Flood fill na grey scale value - tVal doloèa najveèjo razliko s sosednjim pikslom, da zadevo še pridružimo*/
void CFloodFill::GSRegionGrowing(vector<vector<double>> &data, POINT sPoint, vector<vector<int>> &output, int regIndex, double tVal)
{
	candidates.push_back(sPoint);
	output[sPoint.x][sPoint.y]=regIndex;

	while(candidates.size())
	{
		POINT start=candidates.back();
		candidates.pop_back();
		
		int x=start.x;		int y=start.y;
		POINT sosedi[8];	
		sosedi[0].x=x-1;	sosedi[0].y=y-1;
		sosedi[1].x=x-1;	sosedi[1].y=y;
		sosedi[2].x=x-1;	sosedi[2].y=y+1;
		sosedi[3].x=x;		sosedi[3].y=y+1;
		sosedi[4].x=x+1;	sosedi[4].y=y+1;
		sosedi[5].x=x+1;	sosedi[5].y=y;
		sosedi[6].x=x+1;	sosedi[6].y=y-1;
		sosedi[7].x=x;		sosedi[7].y=y-1;
		
		for(int i=0;i<8;i++)
		{
			if( sosedi[i].x>=0 && sosedi[i].x<data.size() && 
				sosedi[i].y>=0 && sosedi[i].y<data[0].size())
			{
				if(	abs(data[sosedi[i].x][sosedi[i].y] - data[sPoint.x][sPoint.y])<tVal && 
					!output[sosedi[i].x][sosedi[i].y])
				{
					output[sosedi[i].x][sosedi[i].y]=regIndex;
					candidates.push_back(sosedi[i]);
				}
			}
		}
	}
	candidates.clear();
}
/*GS sliko segmentiramo v regije toèk, ki imajo najveè tVal razliko do sosedov*/
int CFloodFill::SegmentOnRegionGrowing(vector<vector<double>> &data, vector<vector<int>> &output, double tVal)
{
	int noReg=1;
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(output[x][y])
				continue;

			POINT pnt={x,y};
			GSRegionGrowing(data,pnt,output,noReg,tVal);
			noReg++;
		}
	}

	return noReg;
}
/*Flood fill na grey scale (vse manjše od tVal skupaj) value - zaèetna toèka ki doloèa GS vrednost*/
void CFloodFill::GSFloodFill(vector<vector<double>> &data, POINT sPoint, vector<vector<int>> &output, int regIndex, double tVal)
{
	candidates.push_back(sPoint);
	
	output[sPoint.x][sPoint.y]=regIndex;
	while(candidates.size())
	{
		POINT start=candidates.back();
		candidates.pop_back();
		
		int x=start.x;		int y=start.y;
		POINT sosedi[8];	
		sosedi[0].x=x-1;	sosedi[0].y=y-1;
		sosedi[1].x=x-1;	sosedi[1].y=y;
		sosedi[2].x=x-1;	sosedi[2].y=y+1;
		sosedi[3].x=x;		sosedi[3].y=y+1;
		sosedi[4].x=x+1;	sosedi[4].y=y+1;
		sosedi[5].x=x+1;	sosedi[5].y=y;
		sosedi[6].x=x+1;	sosedi[6].y=y-1;
		sosedi[7].x=x;		sosedi[7].y=y-1;
		
		output[x][y]=regIndex;
		for(int i=0;i<8;i++)
		{
			if( sosedi[i].x>=0 && sosedi[i].x<data.size() && 
				sosedi[i].y>=0 && sosedi[i].y<data[0].size())
			{
				if(	data[sosedi[i].x][sosedi[i].y] < tVal && 
					!output[sosedi[i].x][sosedi[i].y])
				{// -1 = pending znak
					output[sosedi[i].x][sosedi[i].y]=regIndex;
					candidates.push_back(sosedi[i]);
				}
			}
		}
	}
	candidates.clear();
}
/*Odstrani bele regije, ki imajo manj kot tVal elementov*/
void CFloodFill::RemoveSmallWRegions(vector<vector<int>> &input, int tVal)
{
	vector<vector<int>> tmpGrid=input;
	int noReg=WRegionColoring(tmpGrid);
	vector<int> regGram(noReg,0);
	
	for(int x=0;x<tmpGrid.size();x++)
		for(int y=0;y<tmpGrid[0].size();y++)
			regGram[tmpGrid[x][y]]++;

	for(int x=0;x<tmpGrid.size();x++)
		for(int y=0;y<tmpGrid[0].size();y++)
			if(input[x][y] && regGram[tmpGrid[x][y]]<tVal)
				input[x][y]=0;
}
void CFloodFill::RemoveLargeWRegions(vector<vector<int>> &input, int tVal)
{
	vector<vector<int>> tmpGrid=input;
	int noReg=WRegionColoring(tmpGrid);
	vector<int> regGram(noReg,0);
	
	for(int x=0;x<tmpGrid.size();x++)
		for(int y=0;y<tmpGrid[0].size();y++)
			regGram[tmpGrid[x][y]]++;

	for(int x=0;x<tmpGrid.size();x++)
		for(int y=0;y<tmpGrid[0].size();y++)
			if(input[x][y] && regGram[tmpGrid[x][y]]>tVal)
				input[x][y]=0;
}

// REGION GROWING ALGORITHMS
void CRegionGrowing::GetInOutNeighbours(int x, int y, vector<POINT>& inNeighbours, vector<POINT>& outNeighbours, vector<vector<int>> &rImg)
{
	int sx=max(0,x-1);
	int ex=min(rImg.size()-1,x+1);
	int sy=max(0,y-1);
	int ey=min(rImg[0].size()-1,y+1);
	
	int i=0;
	for(int _x=sx;_x<=ex;_x++)
	{
		for(int _y=sy;_y<=ey;_y++)
		{
			POINT pnt; pnt.x=_x;pnt.y=_y;
			if(rImg[pnt.x][pnt.y])
				inNeighbours.push_back(pnt);
			else if(!rImg[pnt.x][pnt.y])
				outNeighbours.push_back(pnt);
		}
	}
}
void CRegionGrowing::GetBoundary(vector<vector<int>> &rImg, queue<POINT>& Q)
{
	for(int x=0;x<rImg.size();x++)
	{
		for(int y=0;y<rImg[0].size();y++)
		{
			if(!rImg[x][y])
				continue;

			int sx=max(0,x-1);
			int ex=min(rImg.size()-1,x+1);
			int sy=max(0,y-1);
			int ey=min(rImg[0].size()-1,y+1);
			
			bool isEdge=false;
			for(int _x=sx;_x<=ex ;_x++)
			{
				for(int _y=sy;_y<=ey;_y++)
				{
					if(!rImg[_x][_y])
						isEdge=true;
				}
			}
			if(!isEdge)
				continue;

			POINT pnt;pnt.x=x;pnt.y=y;
			Q.push(pnt);
		}
	}
}
bool CRegionGrowing::GetPlaneFromPoints(vector<vector<Vector3f>>& grid, vector<POINT>& pnts, double* plane)
{
	if(pnts.size()<3)
		return false;
	
	double* pntList= new double[pnts.size()*3];
	for(int i=0;i<pnts.size();i++)
	{
		pntList[i*3+0]=grid[pnts[i].x][pnts[i].y].x;
		pntList[i*3+1]=grid[pnts[i].x][pnts[i].y].y;
		pntList[i*3+2]=grid[pnts[i].x][pnts[i].y].z;
	}

	getBestFitPlane(pnts.size(),pntList,sizeof(double)*3,NULL,0,plane);

	delete[] pntList;
	return true;
}

void CRegionGrowing::GrowRegionOnBFPlanes(vector<vector<Vector3f>> &grid, vector<vector<int>> &rImg, double growTh)
{
	int minx=0;	int maxx=grid.size()-1;	int miny=0;	int maxy=grid[0].size()-1; int winSize=1;
	vector<vector<int>>				marker=rImg;
	queue<POINT>					q;
	
	GetBoundary(rImg,q);
	vector<POINT> inN; vector<POINT> outN;
	double plane[4];
	while(q.size())
	{
		POINT pnt=q.front();q.pop();
		int x=pnt.x; int y=pnt.y;
		
		inN.clear();outN.clear();
		GetInOutNeighbours(x,y,inN,outN,rImg);
		if(!GetPlaneFromPoints(grid,inN,plane))
			continue;
		
		for(int i=0;i<outN.size();i++)
		{
			if(rImg[outN[i].x][outN[i].y])
				continue;
			
			double val=abs(plane[0]*grid[outN[i].x][outN[i].y].x+plane[1]*grid[outN[i].x][outN[i].y].y+plane[2]*grid[outN[i].x][outN[i].y].z+plane[3]);
			if(val<growTh)
			{
				rImg[outN[i].x][outN[i].y]=6;
				q.push(outN[i]);
			}
		}
	}
}

// DATA STATISTICS
double CDataStatistics::GetMinVal(vector<double>& values)
{
	double val=values[0];
	for(int x=0;x<values.size();x++)
		val=min(val,values[x]);
	return val;
}
double CDataStatistics::GetMinVal(vector<vector<double>>& values)
{
	double val=values[0][0];
	for(int x=0;x<values.size();x++)
		for(int y=0;y<values[0].size();y++)
			val=min(val,values[x][y]);
	return val;
}
double CDataStatistics::GetMaxVal(vector<double>& values)
{
	double val=values[0];
	for(int x=0;x<values.size();x++)
		val=max(val,values[x]);
	return val;
}
double CDataStatistics::GetMaxVal(vector<vector<double>>& values)
{
	double val=values[0][0];
	for(int x=0;x<values.size();x++)
		for(int y=0;y<values[0].size();y++)
			val=max(val,values[x][y]);
	return val;
}
void CDataStatistics::GetMinMaxVal(vector<double>& values, double& minVal, double& maxVal)
{
	minVal=values[0];
	maxVal=values[0];
	for(int x=0;x<values.size();x++)
	{
		minVal=min(minVal,values[x]);
		maxVal=max(maxVal,values[x]);
	}
}
void CDataStatistics::GetMinMaxVal(vector<int>& values, int& minVal, int& maxVal)
{
	minVal=values[0];
	maxVal=values[0];
	for(int x=0;x<values.size();x++)
	{
		minVal=min(minVal,values[x]);
		maxVal=max(maxVal,values[x]);
	}
}
void CDataStatistics::GetMinMaxVal(vector<vector<double>>& values, double& minVal, double& maxVal)
{
	minVal=values[0][0];
	maxVal=values[0][0];
	for(int x=0;x<values.size();x++)
	{
		for(int y=0;y<values[0].size();y++)
		{
			minVal=min(minVal,values[x][y]);
			maxVal=max(maxVal,values[x][y]);
		}
	}
}
void CDataStatistics::GetMinMaxVal(vector<vector<int>>& values, int& minVal, int& maxVal)
{
	minVal=values[0][0];
	maxVal=values[0][0];
	for(int x=0;x<values.size();x++)
	{
		for(int y=0;y<values[0].size();y++)
		{
			minVal=min(minVal,values[x][y]);
			maxVal=max(maxVal,values[x][y]);
		}
	}
}
double CDataStatistics::GetAvgVal(vector<double>& values)
{
	double val=0.0;
	for(int i=0;i<values.size();i++)
		val+=values[i];
	val/=(double)values.size();
	return val;
}
double CDataStatistics::GetAvgVal(vector<vector<double>>& values)
{
	double val=0.0;
	for(int x=0;x<values.size();x++)
	{
		for(int y=0;y<values[0].size();y++)
		{
			val+=values[x][y];
		}
	}
	val/=(double)(values.size()*values[0].size());
	return val;
}
void CDataStatistics::GetAvgVal(vector<vector<double>>& values, vector<vector<int>>& regs, vector<double>& avg)
{
	vector<int> noElem(avg.size(),0);
	N=noElem;

	for(int x=0;x<regs.size();x++)
	{
		for(int y=0;y<regs[0].size();y++)
		{
			avg[regs[x][y]]+=values[x][y];
			N[regs[x][y]]++;
		}
	}
	for(int i=0;i<N.size();i++)
		if(N[i])
			avg[i]/=(double)N[i];
}
void CDataStatistics::GetAvgStdVal(vector<double>& values, double& avg, double& std)
{
	double sum=0.0;

	avg=GetAvgVal(values);
	
	for(int i=0;i<values.size();i++)
	{
		double diff=values[i]-avg;
		sum=sum+(diff*diff);
	}
	
	double fact=1.0/(double)(values.size());
	sum=sum*fact;
	std=sqrt(sum);
}
void CDataStatistics::GetAvgStdVal(vector<vector<double>>& values, double& avg, double& std)
{
	double sum=0.0;

	avg=GetAvgVal(values);
	
	for(int x=0;x<values.size();x++)
	{
		for(int y=0;y<values[0].size();y++)
		{
			double diff=values[x][y]-avg;
			sum=sum+(diff*diff);
		}
	}
	
	double fact=1.0/(double)(values.size()*values[0].size());
	sum=sum*fact;
	std=sqrt(sum);
}
void CDataStatistics::GetAvgStdVal(vector<vector<double>>& values, vector<vector<int>>& regs, vector<double>& avg, vector<double>& std)
{
	GetAvgVal(values,regs,avg);
	for(int x=0;x<regs.size();x++)
	{
		for(int y=0;y<regs[0].size();y++)
		{
			double diff=values[x][y]-avg[regs[x][y]];
			std[regs[x][y]]+=diff*diff;
		}
	}
	for(int i=0;i<N.size();i++)
	{
		if(N[i])
		{
			double fact=1.0/(double)N[i];
			std[i]=std[i]*fact;
		}
	}
	for(int i=0;i<N.size();i++)
		if(N[i])
			std[i]=sqrt(std[i]);
}
void CDataStatistics::GetSkewnessKurtosis(vector<double>& values, double& avg, double& std, double& sk, double& ku)
{
	GetAvgStdVal(values,avg,std);
	
	double variance=std*std;

	double sumS=0.0;
	double sumK=0.0;
	for(int i=0;i<values.size();i++)
	{
		double v=values[i]-avg;
		sumS+=v*v*v;
		sumK+=v*v*v*v;
	}
	sumS/=(double)values.size();
	sumK/=(double)values.size();

	sk=sumS/pow(variance,1.5); 
	
	ku=sumK/(variance*variance)-3.0;
}

void CDataStatistics::GetHistogram(vector<double>& hGram, vector<vector<double>>& data, vector<vector<int>>& classData, int testClass, double minVal, double maxVal, int noSteps)
{
	CropData(data,minVal,maxVal);
	double stepVal=(maxVal-minVal)/(double)noSteps;
	vector<double> tGram(noSteps+1,0.0);

	hGram=tGram;
	int noClassElem=0;
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			if(classData[x][y]!=testClass)
				continue;

			int elIndex=(int)((data[x][y]-minVal)/stepVal);
			hGram[elIndex]++;
			noClassElem++;
		}
	}

	for(int i=0;i<hGram.size();i++)
	{
		hGram[i]/=(double)noClassElem;
	}
}
void CDataStatistics::GetHistomatrix(vector<vector<double>>& hMat, vector<vector<double>>& dataX, vector<vector<double>>& dataY, vector<vector<int>>& classData, int testClass, Vector2f minVal, Vector2f maxVal, POINT noSteps)
{
	CropData(dataX,minVal.x,maxVal.x);
	CropData(dataY,minVal.y,maxVal.y);
	Vector2f stepVal((maxVal.x-minVal.x)/(double)noSteps.x, (maxVal.y-minVal.y)/(double)noSteps.y);

	vector<vector<double>> tMat(noSteps.x+1,vector<double>(noSteps.y+1,0.0));
	hMat=tMat;

	int noClassElem=0;
	for(int x=0;x<dataX.size();x++)
	{
		for(int y=0;y<dataX[0].size();y++)
		{
			if(classData[x][y]!=testClass)
				continue;

			int xIndex=(int)((dataX[x][y]-minVal.x)/stepVal.x);
			int yIndex=(int)((dataY[x][y]-minVal.y)/stepVal.y);
			hMat[xIndex][yIndex]++;
			noClassElem++;
		}
	}
	
	CString txt,tmp;
	for(int x=0;x<hMat.size();x++)
	{
		for(int y=0;y<hMat[0].size();y++)
		{
			hMat[x][y]/=(double)noClassElem;
			tmp.Format("%.5f\t",hMat[x][y]);
			txt+=tmp;
		}
		txt+="\n";
	}
	FILE* file=fopen("Output.txt","w");
	fwrite(txt.GetBuffer(),sizeof(char),txt.GetLength(),file);
	fclose(file);
}
void CDataStatistics::_GetBFP(int noPnts, double* pnts, double* plane)
{
	if(noPnts<3)
		return;
	//(Ax+By+Cz+D)
	getBestFitPlane(noPnts,pnts,sizeof(double)*3,NULL,0,plane);
}
void CDataStatistics::PearsonsCorrelation(vector<vector<double>>& data_x, vector<vector<double>>& data_y, vector<vector<int>>& classData, int testClass)
{
	double mx=0.0;
	double my=0.0;
	int noTestSamples=0;
	for(int x=0;x<data_x.size();x++)
	{
		for(int y=0;y<data_x[0].size();y++)
		{
			if(classData[x][y]!= testClass)
				continue;
			noTestSamples++;
			mx+=data_x[x][y];
			my+=data_y[x][y];
		}
	}
	mx/=(double)noTestSamples;
	my/=(double)noTestSamples;

	double rxy_top=0.0;
	double rxy_l=0.0;
	double rxy_r=0.0;
	
	for(int x=0;x<data_x.size();x++)
	{
		for(int y=0;y<data_x[0].size();y++)
		{
			if(classData[x][y]!= testClass)
				continue;
			rxy_top+=((data_x[x][y]-mx)*(data_y[x][y]-my));
			rxy_l+=((data_x[x][y]-mx)*(data_x[x][y]-mx));
			rxy_r+=((data_y[x][y]-my)*(data_y[x][y]-my));
		}
	}
	double rxy=rxy_top/sqrt(rxy_l*rxy_r);
	CString txt;
	txt.Format("Correlation is equal to: %.3f",rxy);
	MessageBox(0,txt.GetBuffer(),"",MB_OK);
}
void CDataStatistics::LinearRegresion1D(vector<Vector2f>& data, double &a, double &b)
{//Oblika: y=a+bx;
	double n=data.size();
	double sumX=0.0;
	double sumY=0.0;
	double sumXY=0.0;
	double sumX2=0.0;
	double sumY2=0.0;
	vector<double> dataXY(data.size());
	vector<double> dataX2(data.size());
	vector<double> dataY2(data.size());
	
	for(int i=0; i<data.size();i++)
	{
		dataXY[i]=data[i].x*data[i].y;
		dataX2[i]=data[i].x*data[i].x;
		dataY2[i]=data[i].y*data[i].y;

		sumX+=data[i].x;
		sumY+=data[i].y;
		sumXY+=dataXY[i];
		sumX2+=dataX2[i];
		sumY2+=dataY2[i];
	}

	b=(n*sumXY-sumX*sumY)/(n*sumX2-(sumX*sumX));
	a=(sumY-b*sumX)/n;
}
void CDataStatistics::LinearRegresion1D(vector<Vector2f>& data, double &a, double &b, double &avgError, double &stdError)
{
	double n=data.size();
	double sumX=0.0;
	double sumY=0.0;
	double sumXY=0.0;
	double sumX2=0.0;
	double sumY2=0.0;
	vector<double> dataXY(data.size());
	vector<double> dataX2(data.size());
	vector<double> dataY2(data.size());
	
	for(int i=0; i<data.size();i++)
	{
		dataXY[i]=data[i].x*data[i].y;
		dataX2[i]=data[i].x*data[i].x;
		dataY2[i]=data[i].y*data[i].y;

		sumX+=data[i].x;
		sumY+=data[i].y;
		sumXY+=dataXY[i];
		sumX2+=dataX2[i];
		sumY2+=dataY2[i];
	}

	b=(n*sumXY-sumX*sumY)/(n*sumX2-(sumX*sumX));
	a=(sumY-b*sumX)/n;
	
	/*START: Estimate error*/
	for(int i=0; i<data.size();i++)
		dataY2[i]=data[i].y-a-b*data[i].x;
	GetAvgStdVal(dataY2,avgError,stdError);
	/*END: Estimate error*/
}
void CDataStatistics::LinearRegresion1D(vector<vector<double>>& dataX, vector<vector<double>>& dataY, vector<vector<int>>& classData, int testClass,  double &a, double &b)
{//Oblika: a+bx
	vector<Vector2f> data;data.reserve(dataX.size()*dataX[0].size());
	for(int x=0;x<dataX.size();x++)
	{
		for(int y=0;y<dataX[0].size();y++)
		{
			if(classData[x][y]!=testClass)
				continue;
			Vector2f pnt(dataX[x][y],dataY[x][y]);
			data.push_back(pnt);
		}
	}
	
	LinearRegresion1D(data,a,b);
}
void CDataStatistics::LinearRegresion1D(vector<vector<double>>& dataX, vector<vector<double>>& dataY, vector<vector<int>>& classData, int testClass,  double &a, double &b, double &avgError, double &stdError)
{//Oblika: a+bx
	vector<Vector2f> data;data.reserve(dataX.size()*dataX[0].size());
	for(int x=0;x<dataX.size();x++)
	{
		for(int y=0;y<dataX[0].size();y++)
		{
			if(classData[x][y]!=testClass)
				continue;
			Vector2f pnt(dataX[x][y],dataY[x][y]);
			data.push_back(pnt);
		}
	}
	
	LinearRegresion1D(data,a,b,avgError,stdError);
}
void CDataStatistics::ExponentialRegresion1D(vector<vector<double>>& dataX, vector<vector<double>>& dataY, vector<vector<int>>& classData, int testClass, double &a, double &b, double &avgError, double &stdError)
{//Oblika: a*b^x
	vector<vector<double>>& Y=dataY;
	for(int x=0;x<dataX.size();x++)
		for(int y=0;y<dataX[0].size();y++)
			Y[x][y]=log(dataY[x][y]);
	
	//oblika a+bx
	double rega,regb;
	LinearRegresion1D(dataX,Y,classData,testClass,rega,regb, avgError, stdError);
	
	a=pow(10.0,rega);
	b=pow(10.0,regb);
}
void CDataStatistics::LinearRegresion2D(vector<Vector3f>& data, double &a, double &b, double &c)
{
	double* pnts=new double[data.size()*3];
	double plane[4];
	for(int i=0;i<data.size();i++)
	{
		pnts[3*i+0]=data[i].x;
		pnts[3*i+1]=data[i].y;
		pnts[3*i+2]=data[i].z;
	}
	getBestFitPlane(data.size(),pnts,sizeof(double)*3,NULL,0,plane);

	a=-1.0*plane[0]/plane[2];
	b=-1.0*plane[1]/plane[2];
	c=-1.0*plane[3]/plane[2];
	delete[] pnts;
}
void CDataStatistics::LinearRegresion2D(vector<vector<double>>& dataX, vector<vector<double>>& dataY, vector<vector<double>>& dataZ, vector<vector<int>>& classData, int testClass, double &a, double &b, double &c)
{//oblika z=a*x+b*y+c
	vector<Vector3f> data;data.reserve(dataX.size()*dataX[0].size());
	for(int x=0;x<dataX.size();x++)
	{
		for(int y=0;y<dataX[0].size();y++)
		{
			if(classData[x][y]!=testClass)
				continue;
			Vector3f pnt(dataX[x][y],dataY[x][y],dataZ[x][y]);
			data.push_back(pnt);
		}
	}
	LinearRegresion2D(data,a,b,c);
}
void CDataStatistics::LogisticRegresion1D(vector<vector<double>>& data, vector<vector<int>>& classData, int testClass, double minVal, double maxVal, int noSteps, double &a, double &b)
{
	double stepSize=(maxVal-minVal)/(double) noSteps;
	vector<vector<int>> cData=classData;
	for(int x=0;x<data.size();x++)
		for(int y=0;y<data[0].size();y++)
			if(cData[x][y] && cData[x][y]!=testClass)cData[x][y]=testClass+1;
	
	vector<double> hGramC,hGramNC;
	GetHistogram(hGramC,data,cData,testClass,minVal,maxVal,noSteps);
	GetHistogram(hGramNC,data,cData,testClass+1,minVal,maxVal,noSteps);

	vector<double> cOdds=hGramC;
	vector<Vector2f> oddsData(hGramC.size());
	for(int i=0;i<cOdds.size();i++)
	{
		if(hGramNC[i]<0.00001)
			hGramNC[i]=0.00001;
		cOdds[i]/=hGramNC[i];
		cOdds[i]=log(cOdds[i]);
		oddsData[i].x=i;
		oddsData[i].y=cOdds[i];
	}
	LinearRegresion1D(oddsData,a,b);//oblika a+b*x
	a=a-(b*minVal)/stepSize;
	b=b/stepSize;

	/*START: Print out*/
	/*CString txt,tmp;
	for(int i=0;i<cOdds.size();i++)
	{
		tmp.Format("%.5f\t",cOdds[i]);
		txt+=tmp;
	}
	CString filename;
	filename.Format("Output_%d.txt",testClass);
	FILE* file=fopen(filename.GetBuffer(),"w");
	fwrite(txt.GetBuffer(),sizeof(char),txt.GetLength(),file);
	fclose(file);*/
	/*END: Print out*/
}
//Blues
//MAX TREE
//Public
MaxTree::MaxTree(vector<vector<double>>& img) : tree(img)
{
	tree.build_tree(256);
	SetNodeData(img);
}
MaxTree::MaxTree(vector<vector<double>>& img, vector<vector<double>>& orgImg, int no_levels) : tree(img)
{
	tree.build_tree(no_levels);
	SetNodeData(orgImg);
}

//MM Operators
void MaxTree::AreaOpening(double a_th, int p)
{
	//Calculate area opening
	if(tree.nodes[p].atr.area>a_th || !p)
		tree.nodes[p].atr.height=tree.nodes[p].atr.height;
	else
		tree.nodes[p].atr.height=tree.nodes[tree.nodes[p].parent].atr.height;

	//Propaget
	int s=tree.nodes[p].child;
	while(s>=0)
	{
		AreaOpening(a_th, s);
		s=tree.nodes[s].brother;
	}
}
void MaxTree::AttributeOpening(double a_th, int p)
{
	//Calculate area opening
	if(tree.nodes[p].atr.attribute<a_th && p)
		tree.nodes[p].atr.height=tree.nodes[tree.nodes[p].parent].atr.height;

	//Propagate
	int s=tree.nodes[p].child;
	while(s>=0)
	{
		AttributeOpening(a_th, s);
		s=tree.nodes[s].brother;
	}
}
void MaxTree::AttributeOpeningWithAreaConstrain(double a_th, double areaLim, double hTh, double aTh, int p, bool prune)
{
	//Calculate area opening
	if(prune)
		tree.nodes[p].atr.height=tree.nodes[tree.nodes[p].parent].atr.height;
	else if(tree.nodes[p].atr.attribute<a_th && p)
	{
		double hDiff=tree.nodes[p].atr.height-tree.nodes[tree.nodes[p].parent].atr.height;
		
		if(hDiff>hTh)
		{
			tree.nodes[p].atr.height=tree.nodes[tree.nodes[p].parent].atr.height;
			prune=true;
		}
	}

	//Propagate
	int s=tree.nodes[p].child;
	while(s>=0)
	{
		AttributeOpeningWithAreaConstrain(a_th,areaLim,hTh,aTh,s, prune);
		s=tree.nodes[s].brother;
	}
}
/*OPIS: Vrednosti, ki glede na katere želimo izdelati DAP shranimo v Attribut, na outputu dobimo parameter*/
void MaxTree::DAP(vector<double> lambda, bool ignoreFirst)
{
	//Attribut je tisto na kar delamo profile
	//n je attribute zone
	//parameter=output max response
	//node_parameter=outputMaxScale
	//node_attribute=MaxScale node-index
	for(int i=0;i<tree.nodes.size();i++)
	{
		/*START: Assign Attribute Zones*/
		tree.nodes[i].atr.n=lambda.size();
		for(int j=1; j<lambda.size(); j++)
		{
			if(tree.nodes[i].atr.attribute<lambda[j])
			{
				tree.nodes[i].atr.n=j;
				break;
			}
		}
		/*END: Assign Attribute Zones*/
		tree.nodes[i].atr.parameter=0.0;
		tree.nodes[i].atr.node_parameter=lambda.size();
		tree.nodes[i].atr.node_attribute=i;
	}
	
	//Calculate DAP
	int s=tree.nodes[0].child;
	while(s>=0)
	{
		_DAP(s,tree.nodes[0].atr.height,tree.nodes[0].atr.n);
		s=tree.nodes[s].brother;
	}
	//Propagate max response
	s=tree.nodes[0].child;
	while(s>=0)
	{
		_PropagetMaxDAP(s, ignoreFirst);
		s=tree.nodes[s].brother;
	}
}
void MaxTree::_DAP(int p, double prevH, double maxN)
{
	if(tree.nodes[p].atr.n < maxN)
	{
		if(tree.nodes[tree.nodes[p].parent].atr.n!=tree.nodes[p].atr.n)
		{
			prevH=tree.nodes[tree.nodes[p].parent].atr.height;
		}

		tree.nodes[p].atr.parameter=tree.nodes[p].atr.height-prevH;
		tree.nodes[p].atr.node_parameter=tree.nodes[p].atr.n;
		tree.nodes[p].atr.node_attribute=p;
	}
	
	//Propagation
	int s=tree.nodes[p].child;
	while(s>=0)
	{
		_DAP(s,prevH,maxN);
		s=tree.nodes[s].brother;
	}
}
void MaxTree::_PropagetMaxDAP(int p, bool ignoreFirst)
{
	if(tree.nodes[p].atr.parameter<tree.nodes[tree.nodes[p].parent].atr.parameter || (ignoreFirst && tree.nodes[p].atr.node_parameter==1.0))
	{
		tree.nodes[p].atr.parameter=tree.nodes[tree.nodes[p].parent].atr.parameter;
		tree.nodes[p].atr.node_parameter=tree.nodes[tree.nodes[p].parent].atr.node_parameter;
		tree.nodes[p].atr.node_attribute=tree.nodes[tree.nodes[p].parent].atr.node_attribute;
	}

	//Propagation
	int s=tree.nodes[p].child;
	while(s>=0)
	{
		_PropagetMaxDAP(s,ignoreFirst);
		s=tree.nodes[s].brother;
	}
}
void MaxTree::MSLSSegmentation(vector<double> lambda, bool ignoreFirst)
{
	
}
/*OPIS: Attribute - attribut na katerem izvajamo DAP, Parameter - Residual image, Node_Parameter - Associated function*/
void MaxTree::ContrastOpeningOnDAP(double z, double rTh, vector<double> lambda)
{
	DAP(lambda);
	PropagateMaxResponse(0);

	int s=tree.nodes[0].child;
	while(s>=0)
	{
		_ContrastOpeningOnDAP(s,z,rTh);
		s=tree.nodes[s].brother;
	}
}
void MaxTree::_ContrastOpeningOnDAP(int p, double z, double rTh)
{
	double rt=1.0;
	int newRegH=0.0;

	/*START: Calc reg height*/
	int s=tree.nodes[p].child;
	while(s>=0)
	{
		_ContrastOpeningOnDAP(s,z,rTh);
		
		/*START: Update regHeight*/
		if(newRegH<tree.nodes[s].atr.height-tree.nodes[p].atr.height+tree.nodes[s].atr.rHeight)
			newRegH=tree.nodes[s].atr.height-tree.nodes[p].atr.height+tree.nodes[s].atr.rHeight;
		/*END: Update regHeight*/
		s=tree.nodes[s].brother;
	}
	tree.nodes[p].atr.rHeight=newRegH;
	/*END: Calc reg height*/
	
	if(tree.nodes[tree.nodes[p].parent].atr.node_parameter!=tree.nodes[p].atr.node_parameter)
	{
		rt=_RTFunction(p);
		if(rt<z && tree.nodes[p].atr.parameter>rTh)
		{
			MarkSubnodes(p,tree.nodes[tree.nodes[p].parent].atr.height);
		}
	}
}
void MaxTree::GenDTMOnContrastOpening(double z, double rTh, double refNumTh, vector<double> lambda)
{
	DAP(lambda);
	PropagateMaxResponse(0);
	
	int s=tree.nodes[0].child;
	while(s>=0)
	{
		_GenDTMOnContrastOpening(s,z,rTh,refNumTh);
		s=tree.nodes[s].brother;
	}
}
void MaxTree::_GenDTMOnContrastOpening(int p, double z, double rTh, double refNumTh)
{
	int newRegH=0.0;
	/*START: Calc reg height*/
	int s=tree.nodes[p].child;
	while(s>=0)
	{
		_GenDTMOnContrastOpening(s,z,rTh,refNumTh);
		
		/*START: Update regHeight*/
		if(newRegH<tree.nodes[s].atr.height-tree.nodes[p].atr.height+tree.nodes[s].atr.rHeight)
			newRegH=tree.nodes[s].atr.height-tree.nodes[p].atr.height+tree.nodes[s].atr.rHeight;
		/*END: Update regHeight*/
		s=tree.nodes[s].brother;
	}
	tree.nodes[p].atr.rHeight=newRegH;
	/*END: Calc reg height*/
	
	if(tree.nodes[tree.nodes[p].parent].atr.node_parameter!=tree.nodes[p].atr.node_parameter)
	{
		double rt=_RTFunction(p);
		double refNumVal=tree.nodes[p].atr.attribute1;

		if(rt<z && tree.nodes[p].atr.parameter>rTh && refNumVal<refNumTh)
		{
			MarkSubnodes(p,tree.nodes[tree.nodes[p].parent].atr.height);
		}
	}
}
void MaxTree::SetAreaAttribute()
{
	for(int i=0;i<tree.nodes.size();i++)
	{
		tree.nodes[i].atr.attribute=tree.nodes[i].atr.area;
	}
}
void MaxTree::SetMinBBAttribute()
{
	for(int i=0;i<tree.nodes.size();i++)
	{
		tree.nodes[i].atr.attribute=max(tree.nodes[i].atr.bbMax.x-tree.nodes[i].atr.bbMin.x,tree.nodes[i].atr.bbMax.y-tree.nodes[i].atr.bbMin.y);
	}
}
void MaxTree::SetMaxBBAttribute()
{
	for(int i=0;i<tree.nodes.size();i++)
	{
		tree.nodes[i].atr.attribute=min(tree.nodes[i].atr.bbMax.x-tree.nodes[i].atr.bbMin.x,tree.nodes[i].atr.bbMax.y-tree.nodes[i].atr.bbMin.y);
	}
}
void MaxTree::DivideAttributeByArea()
{
	for(int i=0;i<tree.nodes.size();i++)
	{
		tree.nodes[i].atr.attribute/=tree.nodes[i].atr.area;
	}
}
void MaxTree::SetAttributeImageForOpening(vector<vector<double>>& atrImg, bool propagation)
{
	for(int i=0;i<tree.nodes.size();i++)
		tree.nodes[i].atr.attribute=0.0;

	for(int x=0;x<atrImg.size();x++)
	{
		for(int y=0;y<atrImg[0].size();y++)
		{
			tree.nodes[tree.lab_img[x][y]].atr.attribute+=atrImg[x][y];
		}
	}
	if(propagation)
	{
		_PropagateAttributeForOpening();
	}
}
void MaxTree::_PropagateAttributeForOpening(int p)
{
	int s=tree.nodes[p].child;
	while(s>=0)
	{
		_PropagateAttributeForOpening(s);
		tree.nodes[p].atr.attribute+=tree.nodes[s].atr.attribute;
		s=tree.nodes[s].brother;
	}
}
void MaxTree::PropagateMaxResponse(int p)
{
	int s=tree.nodes[p].child;
	while(s>=0)
	{
		if(tree.nodes[p].atr.node_parameter==tree.nodes[s].atr.node_parameter)
		{
			if(tree.nodes[p].atr.parameter>tree.nodes[s].atr.parameter)
				tree.nodes[s].atr.parameter=tree.nodes[p].atr.parameter;
		}

		PropagateMaxResponse(s);
		
		if(tree.nodes[p].atr.node_parameter==tree.nodes[s].atr.node_parameter)
		{
			if(tree.nodes[p].atr.parameter<tree.nodes[s].atr.parameter)
				tree.nodes[p].atr.parameter=tree.nodes[s].atr.parameter;
		}

		s=tree.nodes[s].brother;
	}
}
void MaxTree::PropagateMaxAttribute(int p)
{
	if(p)
	{
		tree.nodes[p].atr.attribute=max(tree.nodes[p].atr.attribute,tree.nodes[tree.nodes[p].parent].atr.attribute);
	}
	
	int s=tree.nodes[p].child;
	while(s>=0)
	{
		PropagateMaxAttribute(s);
		s=tree.nodes[s].brother;
	}
}
void MaxTree::PropagateMinAttribute(int p)
{
	if(p)
	{
		tree.nodes[p].atr.attribute=min(tree.nodes[p].atr.attribute,tree.nodes[tree.nodes[p].parent].atr.attribute);
	}
	
	int s=tree.nodes[p].child;
	while(s>=0)
	{
		PropagateMinAttribute(s);
		s=tree.nodes[s].brother;
	}
}
void MaxTree::ContrastOpening(double ratio, double maxSize)
{
	/*START: Init values*/
	tree.nodes[0].atr.parameter = 0.0;
	tree.nodes[0].atr.attribute = 255;
	/*END: Init values*/
	
	int s=tree.nodes[0].child;
	while(s>=0)
	{
		_ContrastOpening(ratio,s);
		s=tree.nodes[s].brother;
	}
}
void MaxTree::_ContrastOpening(double ratio, int p, double maxSize)
{
	int fReg=0;
	int f=tree.nodes[p].parent;
	double Wp=min(tree.nodes[p].atr.bbMax[0]-tree.nodes[p].atr.bbMin[0],tree.nodes[p].atr.bbMax[1]-tree.nodes[p].atr.bbMin[1]);
	double Wf=min(tree.nodes[f].atr.bbMax[0]-tree.nodes[f].atr.bbMin[0],tree.nodes[f].atr.bbMax[1]-tree.nodes[f].atr.bbMin[1]);
		
	if(Wp<maxSize)
	{
		/*START: Išèi pravega oèeta*/
		int step=0;
		while(tree.nodes[f].parent!=-1 && Wf==Wp && step<255)
		{
			f=tree.nodes[f].parent;
			Wf=min(tree.nodes[f].atr.bbMax[0]-tree.nodes[f].atr.bbMin[0],tree.nodes[f].atr.bbMax[1]-tree.nodes[f].atr.bbMin[1]);
			step++;
		}
		/*END: Išèi pravega oèeta*/
		
		tree.nodes[p].atr.parameter = tree.nodes[p].atr.height-tree.nodes[f].atr.height;
		if( tree.nodes[p].atr.parameter <= tree.nodes[tree.nodes[p].parent].atr.parameter)
		{
			tree.nodes[p].atr.parameter = tree.nodes[tree.nodes[p].parent].atr.parameter;
		}
		else
			fReg=1;
	}
	else
	{
		tree.nodes[p].atr.parameter = tree.nodes[tree.nodes[p].parent].atr.parameter;
	}
	
	/*START: Contrast Opening*/
	double rt=_RTFunction(p);
	if(rt<=ratio && fReg)
	{
		MarkSubnodes(p,tree.nodes[tree.nodes[p].parent].atr.height);
		return;
	}
	/*END: Contrast Opening*/

	/*START: Propagation*/
	int s=tree.nodes[p].child;
	int newRegH=0.0;
	while(s>=0)
	{
		_ContrastOpening(ratio,s);
		if(newRegH<tree.nodes[s].atr.height-tree.nodes[p].atr.height+tree.nodes[s].atr.rHeight)
			newRegH=tree.nodes[s].atr.height-tree.nodes[p].atr.height+tree.nodes[s].atr.rHeight;
		s=tree.nodes[s].brother;
	}
	/*END: Propagation*/
	
	/*START:Back repair*/
	tree.nodes[p].atr.rHeight=newRegH;
	
	rt=_RTFunction(p);
	if(rt<=ratio && fReg && Wp<maxSize)
	{	
		MarkSubnodes(p,tree.nodes[tree.nodes[p].parent].atr.height);
	}
	/*END:Back repair*/
}
double MaxTree::_RTFunction(int p)
{
	double f=tree.nodes[p].atr.rHeight;
	double b=tree.nodes[p].atr.rHeight+tree.nodes[p].atr.parameter;
	
	if(f<0.000001)
		return 0.0;

	double rt=f/b;
	return rt;
}
void MaxTree::MarkSubnodes(int p, double param)
{
	tree.nodes[p].atr.height=param;
	tree.nodes[p].atr.rHeight=0.0;
	tree.nodes[p].atr.n=1.0;
	
	int s=tree.nodes[p].child;
	while(s>=0)
	{
		MarkSubnodes(s,param);
		s=tree.nodes[s].brother;
	}
}
void MaxTree::UltimateAreaOpening(double addArea, double maxArea)
{
	/*START: Init values*/
	if(maxArea==0)
		maxArea=tree.nodes[0].atr.area-1.0;
	tree.nodes[0].atr.parameter = 0.0;
	tree.nodes[0].atr.attribute = tree.nodes[0].atr.area;
	/*END: Init values*/
	
	int s=tree.nodes[0].child;
	while(s>=0)
	{
		UltimateAreaOpening(s,addArea,maxArea);
		s=tree.nodes[s].brother;
	}
}

void MaxTree::UltimateAreaOpening(int p, double addArea, double maxArea)
{
	if(tree.nodes[p].atr.area<maxArea)
	{
		/*START: Išèi pravega oèeta*/
		int f=tree.nodes[p].parent;
		while(tree.nodes[f].parent!=-1 && tree.nodes[f].atr.area<tree.nodes[p].atr.area+addArea)
		{
			f=tree.nodes[f].parent;
		}
		/*END: Išèi pravega oèeta*/
		
		tree.nodes[p].atr.parameter = tree.nodes[p].atr.height-tree.nodes[f].atr.height;
		tree.nodes[p].atr.attribute = tree.nodes[tree.nodes[p].parent].atr.area;
		
		if( tree.nodes[p].atr.parameter < tree.nodes[tree.nodes[p].parent].atr.parameter)
		{
			tree.nodes[p].atr.parameter = tree.nodes[tree.nodes[p].parent].atr.parameter;
			tree.nodes[p].atr.attribute = tree.nodes[tree.nodes[p].parent].atr.attribute;
		}
	}
	else
	{
		tree.nodes[p].atr.parameter = tree.nodes[tree.nodes[p].parent].atr.parameter;
		tree.nodes[p].atr.attribute = tree.nodes[p].atr.height;
	}

	//Propagation
	int s=tree.nodes[p].child;
	while(s>=0)
	{
		UltimateAreaOpening(s,addArea,maxArea);
		s=tree.nodes[s].brother;
	}
}
void MaxTree::UltimateQOpening(double maxSize)
{
	/*START: Init values*/
	if(maxSize==0)
		maxSize=min(tree.lab_img.size(),tree.lab_img[0].size())-1;
	tree.nodes[0].atr.parameter = 0.0;
	tree.nodes[0].atr.attribute = maxSize;
	/*END: Init values*/
	
	int s=tree.nodes[0].child;
	while(s>=0)
	{
		UltimateQOpening(s,maxSize);
		s=tree.nodes[s].brother;
	}
}
void MaxTree::UltimateQOpening(int p, double maxSize)
{
	int f=tree.nodes[p].parent;
	double Wp=min(tree.nodes[p].atr.bbMax[0]-tree.nodes[p].atr.bbMin[0],tree.nodes[p].atr.bbMax[1]-tree.nodes[p].atr.bbMin[1]);
	double Wf=min(tree.nodes[f].atr.bbMax[0]-tree.nodes[f].atr.bbMin[0],tree.nodes[f].atr.bbMax[1]-tree.nodes[f].atr.bbMin[1]);
		
	if(Wp<maxSize)
	{
		/*START: Išèi pravega oèeta*/
		int step=0;
		while(tree.nodes[f].parent!=-1 && Wf==Wp && step<255)
		{
			f=tree.nodes[f].parent;
			Wf=min(tree.nodes[f].atr.bbMax[0]-tree.nodes[f].atr.bbMin[0],tree.nodes[f].atr.bbMax[1]-tree.nodes[f].atr.bbMin[1]);
			step++;
		}
		/*END: Išèi pravega oèeta*/
		
		tree.nodes[p].atr.parameter = tree.nodes[p].atr.height-tree.nodes[f].atr.height;
		tree.nodes[p].atr.attribute = Wp;
		
		if( tree.nodes[p].atr.parameter < tree.nodes[tree.nodes[p].parent].atr.parameter)
		{
			tree.nodes[p].atr.parameter = tree.nodes[tree.nodes[p].parent].atr.parameter;
			tree.nodes[p].atr.attribute = tree.nodes[tree.nodes[p].parent].atr.attribute;
		}
	}
	else
	{
		tree.nodes[p].atr.parameter = tree.nodes[tree.nodes[p].parent].atr.parameter;
		tree.nodes[p].atr.attribute = tree.nodes[p].atr.height;
	}

	//Propagation
	int s=tree.nodes[p].child;
	while(s>=0)
	{
		UltimateQOpening(s,maxSize);
		s=tree.nodes[s].brother;
	}
}
void MaxTree::UltimateAreaStdOpening(double maxArea, double maxStd, double addArea)
{
	/*START: Init values*/
	if(maxArea==0)
		maxArea=tree.nodes[0].atr.area-1.0;
	if(maxStd==0)
		maxArea=tree.nodes[0].atr.std-0.1;
	if(addArea==0)
		addArea=tree.nodes[0].atr.area*0.001;

	tree.nodes[0].atr.node_parameter=tree.nodes[0].atr.height;
	tree.nodes[0].atr.attribute = maxArea;
	tree.nodes[0].atr.node_attribute = maxStd;
	/*END: Init values*/
	
	int s=tree.nodes[0].child;
	while(s>=0)
	{
		UltimateAreaStdOpening(s,maxArea,maxStd,addArea);
		s=tree.nodes[s].brother;
	}
}
void MaxTree::UltimateAreaStdOpening(int p, double maxArea,  double maxStd, double addArea)
{
	if(tree.nodes[p].atr.area<maxArea && tree.nodes[p].atr.std<maxStd)
	{
		/*START: Išèi pravega oèeta*/
		int f=tree.nodes[p].parent;
		addArea=tree.nodes[p].atr.area*0.05;
		
		while(tree.nodes[f].parent!=-1 && tree.nodes[f].atr.area<tree.nodes[p].atr.area+addArea)
		{
			f=tree.nodes[f].parent;
		}
		/*END: Išèi pravega oèeta*/
		
		tree.nodes[p].atr.parameter = tree.nodes[p].atr.height-tree.nodes[f].atr.height;
		tree.nodes[p].atr.node_parameter = tree.nodes[f].atr.height;
		tree.nodes[p].atr.attribute = tree.nodes[p].atr.area;
		tree.nodes[p].atr.node_attribute = tree.nodes[p].atr.std;
		
		if( tree.nodes[p].atr.parameter < tree.nodes[tree.nodes[p].parent].atr.parameter)
		{
			tree.nodes[p].atr.parameter = tree.nodes[tree.nodes[p].parent].atr.parameter;
			tree.nodes[p].atr.node_parameter = tree.nodes[tree.nodes[p].parent].atr.node_parameter;
			tree.nodes[p].atr.attribute = tree.nodes[tree.nodes[p].parent].atr.attribute;
			tree.nodes[p].atr.node_attribute = tree.nodes[tree.nodes[p].parent].atr.node_attribute;
		}
	}
	else
	{
		tree.nodes[p].atr.parameter = tree.nodes[tree.nodes[p].parent].atr.parameter;
		tree.nodes[p].atr.node_parameter = tree.nodes[tree.nodes[p].parent].atr.node_parameter;
		tree.nodes[p].atr.attribute = maxArea;
		tree.nodes[p].atr.node_attribute = maxStd;
	}

	//Propagation
	int s=tree.nodes[p].child;
	while(s>=0)
	{
		UltimateAreaStdOpening(s,maxArea,maxStd, addArea);
		s=tree.nodes[s].brother;
	}
}
// Divji operatorji
void MaxTree::SetAttributeOnHRegs(int p)
{
	if(p)
	{
		if(tree.nodes[p].atr.node_parameter==tree.nodes[tree.nodes[p].parent].atr.node_parameter)
			tree.nodes[p].atr.attribute=tree.nodes[tree.nodes[p].parent].atr.attribute;
	}
	
	int s=tree.nodes[p].child;
	while(s>=0)
	{
		SetAttributeOnHRegs(s);
		s=tree.nodes[s].brother;
	}
}
void MaxTree::AttributeOpeningOnHReg()
{
	SetAttributeOnHRegs();
}
void MaxTree::QWatershed(double minAttr, double maxAttr, double minSize, double maxSize)
{
	int wr_index=1;
	int s=tree.nodes[0].child;
	while(s>=0)
	{
		_QWatershed(minAttr, maxAttr, minSize, maxSize, wr_index, s);
		s=tree.nodes[s].brother;
	}	
}
void MaxTree::_QWatershed(double minAttr, double maxAttr, double minSize, double maxSize, int &wr_index, int p)
{
	if(tree.nodes[p].atr.area <= maxAttr)
	{
		int par=tree.nodes[p].parent;
		if(tree.nodes[p].atr.parameter == tree.nodes[par].atr.parameter && tree.nodes[p].atr.area >= minAttr)
		{
			tree.nodes[p].atr.parameter=wr_index;
			wr_index++;
		}
		else
			tree.nodes[p].atr.parameter = tree.nodes[par].atr.parameter;
	}
	int s=tree.nodes[p].child;
	while(s>=0)
	{
		_QWatershed(minAttr, maxAttr, minSize, maxSize, wr_index, s);
		s=tree.nodes[s].brother;
	}	
}
//IO Functions
void MaxTree::SetNodeStatData(vector<vector<double>>& data)
{
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			int i=tree.lab_img[x][y];
			double n	=	tree.nodes[i].atr.n;
			double avg	=	tree.nodes[i].atr.avg;
			double sigm	=	data[x][y]-avg;
			double m2	=	tree.nodes[i].atr.m2;
			
			tree.nodes[i].atr.n+=1.0;
			tree.nodes[i].atr.avg=avg+(data[x][y]-avg)/(tree.nodes[i].atr.n);
			tree.nodes[i].atr.m2=m2+(data[x][y]-tree.nodes[i].atr.avg)*(data[x][y]-avg);
			tree.nodes[i].atr.std=tree.nodes[i].atr.m2/(tree.nodes[i].atr.n);
		}
	}
	PropagateNodeStatData(0);
}
void MaxTree::SetDataM2(vector<vector<int>>& data) //Hacking function
{
	for(int i=0;i<tree.nodes.size();i++)
		tree.nodes[i].atr.m2=0;

	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			tree.nodes[tree.lab_img[x][y]].atr.m2+=(data[x][y]-1);
		}
	}

}
void MaxTree::PropagateNodeStatData(int p)
{
	int s=tree.nodes[p].child;
	while(s>=0)
	{
		PropagateNodeStatData(s);
		
		double nA=tree.nodes[p].atr.n;
		double nB=tree.nodes[s].atr.n;
		
		double avgA=tree.nodes[p].atr.avg;
		double avgB=tree.nodes[s].atr.avg;
		double sigm=avgB-avgA;

		double m2A=tree.nodes[p].atr.m2;
		double m2B=tree.nodes[s].atr.m2;
		
		//Storing results
		tree.nodes[p].atr.n		+=nB;double nX=tree.nodes[p].atr.n;						//no elements
		tree.nodes[p].atr.avg	= avgA+sigm*nB/tree.nodes[p].atr.n;						//avg val
		tree.nodes[p].atr.m2	= m2A + m2B + sigm*sigm*nA*nB/nX;						//2nd momen
		tree.nodes[p].atr.std	= sqrt(tree.nodes[p].atr.m2/nX);						//std
		s=tree.nodes[s].brother;
	}
}
void MaxTree::rHeight2Img(vector<vector<double>>& img)
{
	for(int x=0;x<img.size();x++)
	{
		for(int y=0;y<img[0].size();y++)
		{
			img[x][y]=tree.nodes[tree.lab_img[x][y]].atr.rHeight;
		}
	}
}
void MaxTree::Height2Img(vector<vector<double>>& img)
{
	for(int x=0;x<img.size();x++)
	{
		for(int y=0;y<img[0].size();y++)
		{
			img[x][y]=tree.nodes[tree.lab_img[x][y]].atr.height;
		}
	}
}
void MaxTree::Height2Img(vector<vector<double>>& img, vector<vector<int>>& regs)
{
	for(int x=0;x<img.size();x++)
	{
		for(int y=0;y<img[0].size();y++)
		{
			if(regs[x][y])
				img[x][y]=tree.nodes[tree.lab_img[x][y]].atr.height;
		}
	}
}
void MaxTree::Attribute2Img(vector<vector<double>>& img)
{
	for(int x=0;x<img.size();x++)
	{
		for(int y=0;y<img[0].size();y++)
		{
			img[x][y]=tree.nodes[tree.lab_img[x][y]].atr.attribute;
		}
	}
}
void MaxTree::Parameter2Img(vector<vector<double>>& img)
{
	for(int x=0;x<img.size();x++)
	{
		for(int y=0;y<img[0].size();y++)
		{
			img[x][y]=tree.nodes[tree.lab_img[x][y]].atr.parameter;
		}
	}
}
void MaxTree::ParameterTopHat(vector<vector<double>>& img)
{
	for(int x=0;x<img.size();x++)
	{
		for(int y=0;y<img[0].size();y++)
		{
			img[x][y]-=tree.nodes[tree.lab_img[x][y]].atr.parameter;
		}
	}
}
void MaxTree::NodeAttribute2Img(vector<vector<double>>& img)
{
	for(int x=0;x<img.size();x++)
	{
		for(int y=0;y<img[0].size();y++)
		{
			img[x][y]=tree.nodes[tree.lab_img[x][y]].atr.node_attribute;
		}
	}
}
void MaxTree::NodeParameter2Img(vector<vector<double>>& img)
{
	for(int x=0;x<img.size();x++)
	{
		for(int y=0;y<img[0].size();y++)
		{
			img[x][y]=tree.nodes[tree.lab_img[x][y]].atr.node_parameter;
		}
	}
}
void MaxTree::MoveAttribute2A1()
{
	for(int i=0;i<tree.nodes.size();i++)
		tree.nodes[i].atr.attribute1=tree.nodes[i].atr.attribute;
}
//Thresholds
void MaxTree::AdaptiveAreaStdThreshold(vector<vector<int>>& regs, double res, double maxArea, double maxStd, double mRefNumber)
{
	for(int i=0;i<tree.nodes.size();i++)
		tree.nodes[i].atr.n=0.0;

	int s=tree.nodes[0].child;
	while(s>=0)
	{
		_AdaptiveAreaStdThreshold(s,res,maxArea,maxStd, mRefNumber);
		s=tree.nodes[s].brother;
	}

	for(int x=0;x<regs.size();x++)
	{
		for(int y=0;y<regs[0].size();y++)
		{
			if(tree.nodes[tree.lab_img[x][y]].atr.n>0.5)
				regs[x][y]=1;
			else
				regs[x][y]=0;
		}
	}
}
int MaxTree::_AdaptiveAreaStdThreshold(int p, double res, double maxArea, double maxStd, double mRefNumber)
{
	double tFact=0.05;
	double tMin=0.25;
	double tVal= max(tree.nodes[p].atr.rHeight*tFact,tMin);
	if(tree.nodes[p].atr.parameter != tree.nodes[tree.nodes[p].parent].atr.parameter && tree.nodes[p].atr.m2<mRefNumber)
	{
		if(tree.nodes[p].atr.parameter>tVal)
		{
			_MarkBranch(p);
			return 1;
		}
	}

	int noTh=0; //števec thresholdanih sinov
	int s=tree.nodes[p].child;
	while(s>=0)
	{
		noTh+=_AdaptiveAreaStdThreshold(s,res,maxArea,maxStd, mRefNumber);
		s=tree.nodes[s].brother;
	}
	if(!noTh) //èe thresholdanih sinov ni, vrnemo 0
		return 0;

	//Moramo doloèiti novo višino veje
	node* np=&tree.nodes[p];
	node* nperent=&tree.nodes[tree.nodes[p].parent];

	tree.nodes[p].atr.rHeight=0.0;
	s=tree.nodes[p].child;
	while(s>=0)
	{
		double bHeight=tree.nodes[s].atr.rHeight+tree.nodes[s].atr.height-tree.nodes[p].atr.height;
		tree.nodes[p].atr.rHeight=max(tree.nodes[p].atr.rHeight,bHeight);
		s=tree.nodes[s].brother;
	}
	if(tree.nodes[p].atr.parameter != tree.nodes[tree.nodes[p].parent].atr.parameter && tree.nodes[p].atr.m2<mRefNumber)
	{
		tVal= max(tree.nodes[p].atr.rHeight*tFact,tMin);
		if(tree.nodes[p].atr.parameter>tVal)
		{
			_MarkBranch(p);
		}
	}
	return 1;
}
void MaxTree::_MarkBranch(int p)
{
	tree.nodes[p].atr.height=tree.nodes[tree.nodes[p].parent].atr.height;
	tree.nodes[p].atr.rHeight=0.0;
	tree.nodes[p].atr.n=1.0;
	
	int s=tree.nodes[p].child;
	while(s>=0)
	{
		_MarkBranch(s);
		s=tree.nodes[s].brother;
	}
}
void MaxTree::ThresholdingOnAttribute1(double tVal)
{
	for(int i=0;i<tree.nodes.size();i++)
		tree.nodes[i].atr.n=0.0;

	int s=tree.nodes[0].child;
	while(s>=0)
	{
		_ThresholdingOnAttribute1(tVal,s);
		s=tree.nodes[s].brother;
	}
}
void MaxTree::_ThresholdingOnAttribute1(double tVal, int p)
{
	if(tree.nodes[p].atr.attribute1<tVal)
		tree.nodes[p].atr.n=1.0;
	else if(tree.nodes[tree.nodes[p].parent].atr.n==1.0)
		tree.nodes[p].atr.n=1.0;

	int s=tree.nodes[p].child;
	while(s>=0)
	{
		_ThresholdingOnAttribute1(tVal,s);
		s=tree.nodes[s].brother;
	}
}
//Private
void MaxTree::SetNodeData(vector<vector<double>>& img)
{
	/*START: init*/
	for(int i=0;i<tree.nodes.size();i++)
	{
		/*Init general attributes*/
		tree.nodes[i].atr.height=0.0;
		tree.nodes[i].atr.rHeight=0.0;

		tree.nodes[i].atr.area=0;
		tree.nodes[i].atr.node_area=0;

		tree.nodes[i].atr.bbMin[0]=img.size();
		tree.nodes[i].atr.bbMin[1]=img[0].size();
		tree.nodes[i].atr.bbMax[0]=0;
		tree.nodes[i].atr.bbMax[1]=0;
		
		/*User defined attributes*/
		tree.nodes[i].atr.attribute=0.0;
		tree.nodes[i].atr.node_attribute=0.0;
		tree.nodes[i].atr.parameter=0.0;
		tree.nodes[i].atr.node_parameter=0.0;
		tree.nodes[i].atr.linker=0.0;

		/*Statistical attributes*/
		tree.nodes[i].atr.n=0.0;
		tree.nodes[i].atr.avg=0.0;
		tree.nodes[i].atr.m2=0.0;
		tree.nodes[i].atr.std=0.0;
	}
	/*END: init*/

	/*START: Flat-zone attributes*/
	for(int x=0;x<img.size();x++)
	{
		for(int y=0;y<img[0].size();y++)
		{
			tree.nodes[tree.lab_img[x][y]].atr.height=img[x][y];
			tree.nodes[tree.lab_img[x][y]].atr.rHeight=img[x][y];
			tree.nodes[tree.lab_img[x][y]].atr.node_area+=1.0;
			
			if(tree.nodes[tree.lab_img[x][y]].atr.bbMin[0]>x)
				tree.nodes[tree.lab_img[x][y]].atr.bbMin[0]=x;
			if(tree.nodes[tree.lab_img[x][y]].atr.bbMin[1]>y)
				tree.nodes[tree.lab_img[x][y]].atr.bbMin[1]=y;

			if(tree.nodes[tree.lab_img[x][y]].atr.bbMax[0]<x)
				tree.nodes[tree.lab_img[x][y]].atr.bbMax[0]=x;
			if(tree.nodes[tree.lab_img[x][y]].atr.bbMax[1]<y)
				tree.nodes[tree.lab_img[x][y]].atr.bbMax[1]=y;
		}
	}
	/*END: Flat-zone attributes*/
	PropagateNodeData(0);
	PostPropagateNodeData(0);

}
void MaxTree::PropagateDataM2(int p) //Hacking function
{
	int s=tree.nodes[p].child;
	while(s>=0)
	{
		PropagateDataM2(s);
		tree.nodes[p].atr.m2+=tree.nodes[s].atr.m2;
		s=tree.nodes[s].brother;
	}
}
void MaxTree::PropagateNodeData(int p)
{
	//Init propagation values
	tree.nodes[p].atr.area=tree.nodes[p].atr.node_area;
	
	//Propagations
	int s=tree.nodes[p].child;
	while(s>=0)
	{
		PropagateNodeData(s);
		
		tree.nodes[p].atr.area+=tree.nodes[s].atr.area;
		tree.nodes[p].atr.rHeight=max(tree.nodes[p].atr.rHeight,tree.nodes[s].atr.rHeight);

		if(tree.nodes[p].atr.bbMin[0]>tree.nodes[s].atr.bbMin[0])
			tree.nodes[p].atr.bbMin[0]=tree.nodes[s].atr.bbMin[0];
		if(tree.nodes[p].atr.bbMin[1]>tree.nodes[s].atr.bbMin[1])
			tree.nodes[p].atr.bbMin[1]=tree.nodes[s].atr.bbMin[1];

		if(tree.nodes[p].atr.bbMax[0]<tree.nodes[s].atr.bbMax[0])
			tree.nodes[p].atr.bbMax[0]=tree.nodes[s].atr.bbMax[0];
		if(tree.nodes[p].atr.bbMax[1]<tree.nodes[s].atr.bbMax[1])
			tree.nodes[p].atr.bbMax[1]=tree.nodes[s].atr.bbMax[1];

		s=tree.nodes[s].brother;
	}
}
void MaxTree::PostPropagateNodeData(int p)
{
	tree.nodes[p].atr.rHeight=tree.nodes[p].atr.rHeight-tree.nodes[p].atr.height;
	//Propagations
	int s=tree.nodes[p].child;
	while(s>=0)
	{
		PostPropagateNodeData(s);
		s=tree.nodes[s].brother;
	}
}

//INTERPOLATIONS
void CInterpolations::get_boundary_cells(vector<vector<int>>& data, vector<vector<POINT>>& data_out)
{
	//vector < vector <vector<bool> > > data_boundary(data_out.size(), std::vector< std::vector<bool> >(data.size(), std::vector<bool>(data[0].size(), 0)));

	for(int i=0;i<data.size();i++)
	{
		for(int j=0;j<data[i].size();j++)
		{
			if(data[i][j]!=0)
			{
				for(int ii=max(0, i-1);ii<=min(data.size()-1, i+1);ii++)
				{
					for(int jj=max(0, j-1);jj<=min(data[0].size()-1, j+1);jj++)
					{
						if(!data[ii][jj]) 
						{
							POINT t; t.x=ii; t.y=jj;
							data_out[data[i][j]].push_back(t);
						}
					}
				}
			}
		}
	}
}
void CInterpolations::IDWInterpolation(vector<vector<Vector3f>>& grid, vector<vector<int>>& controlMap, Vector3f minPnt, double resolution, bool inplace, int winSize, double smooth)
{
	double addRes=resolution/2.0;
	
	/*START: Get empty-edge points*/
	queue<POINT> Q;
	for(int x=0;x<grid.size();x++)
	{
		for(int y=0;y<grid[0].size();y++)
		{
			if(controlMap[x][y])
				continue;

			int sx=max(0,x-1);
			int ex=min(grid.size()-1,x+1);
			int sy=max(0,y-1);
			int ey=min(grid[0].size()-1,y+1);
			
			for(int _x=sx;_x<=ex && !controlMap[x][y];_x++)
			{
				for(int _y=sy;_y<=ey && !controlMap[x][y];_y++)
				{
					if(controlMap[_x][_y]==1)
					{
						controlMap[x][y]=2; //oznaèim, da je že v queue
						POINT pnt;pnt.x=x;pnt.y=y;
						Q.push(pnt);
					}
				}
			}
		}
	}
	/*END: Get empty-edge points*/

	/*START: Interpolation*/
	while(Q.size())
	{
		POINT pnt=Q.front();Q.pop();
		int x=pnt.x;
		int y=pnt.y;
		
		grid[x][y].x=x*resolution+minPnt.x+addRes;
		grid[x][y].y=y*resolution+minPnt.y+addRes;
		IDWInterpolatePoint(x,y,grid[x][y],winSize,grid,controlMap,smooth);		
		controlMap[x][y]=1;

		int sx=max(0,x-1);
		int ex=min(grid.size()-1,x+1);
		int sy=max(0,y-1);
		int ey=min(grid[0].size()-1,y+1);
		
		for(int _x=sx;_x<=ex;_x++)
		{
			for(int _y=sy;_y<=ey;_y++)
			{
				if(!controlMap[_x][_y])
				{
					controlMap[_x][_y]=2; 
					POINT pnt;pnt.x=_x;pnt.y=_y;
					Q.push(pnt);
				}
			}
		}
	}
	/*END: Interpolation*/
}
void CInterpolations::IDWInterpolationMissingQ(vector<vector<Vector3f>>& grid, vector<vector<int>>& controlMap, Vector3f minPnt, double resolution, double smooth)
{
	BComplementData(controlMap);
	double addRes=resolution/2.0;
	vector<vector<int>> dtMap(controlMap.size(),vector<int>(controlMap[0].size(),0));
	MMLibB2D mmb;
	mmb.data=controlMap;
	mmb.Init();
	mmb.bDT(dtMap);
	BComplementData(controlMap);

	/*START: Get empty-edge points*/
	queue<POINT> Q;
	for(int x=0;x<grid.size();x++)
	{
		for(int y=0;y<grid[0].size();y++)
		{
			if(controlMap[x][y])
				continue;

			int sx=max(0,x-1);
			int ex=min(grid.size()-1,x+1);
			int sy=max(0,y-1);
			int ey=min(grid[0].size()-1,y+1);
			
			for(int _x=sx;_x<=ex && !controlMap[x][y];_x++)
			{
				for(int _y=sy;_y<=ey && !controlMap[x][y];_y++)
				{
					if(controlMap[_x][_y]==1)
					{
						controlMap[x][y]=2; //oznaèim, da je že v queue
						POINT pnt;pnt.x=x;pnt.y=y;
						Q.push(pnt);
					}
				}
			}
		}
	}
	/*END: Get empty-edge points*/

	/*START: Interpolation*/
	while(Q.size())
	{
		POINT pnt=Q.front();Q.pop();
		int x=pnt.x;
		int y=pnt.y;

		double dfX=(double)((double)x*(double)resolution);
		double dfY=(double)((double)y*(double)resolution);
		double valX=(double)dfX+(double)minPnt.x+(double)addRes;
		double valY=(double)dfY+(double)minPnt.y+(double)addRes;
		grid[x][y].x=(float)(valX);
		grid[x][y].y=(float)(valY);
		IDWInterpolatePoint(x,y,grid[x][y],min(dtMap[x][y],3.0),grid,controlMap,smooth);		
		controlMap[x][y]=1;

		int sx=max(0,x-1);
		int ex=min(grid.size()-1,x+1);
		int sy=max(0,y-1);
		int ey=min(grid[0].size()-1,y+1);
		
		for(int _x=sx;_x<=ex;_x++)
		{
			for(int _y=sy;_y<=ey;_y++)
			{
				if(!controlMap[_x][_y])
				{
					controlMap[_x][_y]=2; 
					POINT pnt;pnt.x=_x;pnt.y=_y;
					Q.push(pnt);
				}
			}
		}
	}
	/*END: Interpolation*/
	return;
}
void CInterpolations::IDWMissingPointsFromCenter(vector<vector<Vector3f>>& grid, vector<vector<int>>& controlMap, Vector3f minPnt, double resolution, double smooth)
{
	double addRes=resolution/2.0;
	vector<vector<int>> dtMap(controlMap.size(),vector<int>(controlMap[0].size(),0));
	MMLibB2D mmb;
	mmb.data=controlMap;
	mmb.Init();
	mmb.bDT(dtMap);
	
	BComplementData(controlMap);
	/*START: Get empty-edge points*/
	vector<PixelEl> vrsta;
	for(int x=0;x<dtMap.size();x++)
	{
		for(int y=0;y<dtMap[0].size();y++)
		{
			if(!dtMap[x][y])
				continue;
			PixelEl p;
			p.x=x;
			p.y=y;
			p.val=dtMap[x][y]+1.5;
			vrsta.push_back(p);
		}
	}
	sort(vrsta.begin(),vrsta.end(),myfnL2S);
	/*END: Get empty-edge points*/
	
	/*START: Interpolation*/
	for(int i=0;i<vrsta.size();i++)
	{
		int x=vrsta[i].x;
		int y=vrsta[i].y;

		double dfX=(double)((double)x*(double)resolution);
		double dfY=(double)((double)y*(double)resolution);
		double valX=(double)dfX+(double)minPnt.x+(double)addRes;
		double valY=(double)dfY+(double)minPnt.y+(double)addRes;
		grid[x][y].x=(float)(valX);
		grid[x][y].y=(float)(valY);
		IDWInterpolatePoint(x,y,grid[x][y],dtMap[x][y],grid,controlMap,smooth);		
		//controlMap[x][y]=1;
	}
	BComplementData(controlMap);
	/*END: Interpolation*/
	return;
}
void CInterpolations::IDWRemovedPointsFromCenter(vector<vector<Vector3f>>& grid, vector<vector<int>>& controlMap, double smooth)
{
	vector<vector<int>> dtMap(controlMap.size(),vector<int>(controlMap[0].size(),0));
	MMLibB2D mmb;
	mmb.data=controlMap;
	mmb.Init();
	mmb.bDT(dtMap);
	
	BComplementData(controlMap);
	/*START: Get empty-edge points*/
	vector<PixelEl> vrsta;
	for(int x=0;x<dtMap.size();x++)
	{
		for(int y=0;y<dtMap[0].size();y++)
		{
			if(!dtMap[x][y])
				continue;
			PixelEl p;
			p.x=x;
			p.y=y;
			p.val=dtMap[x][y]+1.5;
			vrsta.push_back(p);
		}
	}
	sort(vrsta.begin(),vrsta.end(),myfnL2S);
	/*END: Get empty-edge points*/
	
	/*START: Interpolation*/
	for(int i=0;i<vrsta.size();i++)
	{
		int x=vrsta[i].x;
		int y=vrsta[i].y;
		IDWInterpolatePoint(x,y,grid[x][y],dtMap[x][y],grid,controlMap,smooth);		
		controlMap[x][y]=1;
	}
	BComplementData(controlMap);
	/*END: Interpolation*/
	return;
}
void CInterpolations::IDWInterpolationRemovedPoints(vector<vector<Vector3f>>& grid, vector<vector<int>>& controlPnts, double smooth)
{
	vector<vector<int>> controlMap=controlPnts;
	MMLibB2D mmb;
	mmb.data=controlMap;InitData(controlMap,0);BComplementData(mmb.data);
	mmb.Init();
	mmb.bDT(controlMap);

	for(int x=0;x<grid.size();x++)
	{
		for(int y=0;y<grid[0].size();y++)
		{
			if(!controlMap[x][y])
				continue;
			IDWInterpolateRemovedPoint(x,y,grid[x][y],controlMap[x][y]+2,grid,controlMap,smooth);
		}
	}
}
void CInterpolations::IDWInterpolationRemovedQ(vector<vector<Vector3f>>& grid, vector<vector<int>>& controlMap, double smooth)
{
	BComplementData(controlMap);
	vector<vector<int>> dtMap(controlMap.size(),vector<int>(controlMap[0].size(),0));
	MMLibB2D mmb;
	mmb.data=controlMap;
	mmb.Init();
	mmb.bDT(dtMap);
	BComplementData(controlMap);
	/*START: Get empty-edge points*/
	queue<POINT> Q;
	for(int x=0;x<grid.size();x++)
	{
		for(int y=0;y<grid[0].size();y++)
		{
			if(controlMap[x][y])
				continue;

			int sx=max(0,x-1);
			int ex=min(grid.size()-1,x+1);
			int sy=max(0,y-1);
			int ey=min(grid[0].size()-1,y+1);
			
			for(int _x=sx;_x<=ex && !controlMap[x][y];_x++)
			{
				for(int _y=sy;_y<=ey && !controlMap[x][y];_y++)
				{
					if(controlMap[_x][_y]==1)
					{
						controlMap[x][y]=2; //oznaèim, da je že v queue
						POINT pnt;pnt.x=x;pnt.y=y;
						Q.push(pnt);
					}
				}
			}
		}
	}
	/*END: Get empty-edge points*/

	/*START: Interpolation*/
	while(Q.size())
	{
		POINT pnt=Q.front();Q.pop();
		int x=pnt.x;
		int y=pnt.y;
		
		IDWInterpolatePoint(x,y,grid[x][y],dtMap[x][y],grid,controlMap,smooth);		
		controlMap[x][y]=1;

		int sx=max(0,x-1);
		int ex=min(grid.size()-1,x+1);
		int sy=max(0,y-1);
		int ey=min(grid[0].size()-1,y+1);
		
		for(int _x=sx;_x<=ex;_x++)
		{
			for(int _y=sy;_y<=ey;_y++)
			{
				if(!controlMap[_x][_y])
				{
					controlMap[_x][_y]=2; 
					POINT pnt;pnt.x=_x;pnt.y=_y;
					Q.push(pnt);
				}
			}
		}
	}
	InitData(controlMap);
	/*END: Interpolation*/
}
void CInterpolations::IDWInterpolationOnEdgePoints(vector<vector<Vector3f>>& grid, vector<vector<int>>& controlMap, double smooth)
{
	CFloodFill ff;
	int noRegs=ff.WRegionColoring(controlMap);
	vector<vector<POINT>> edges(noRegs);
	get_boundary_cells(controlMap,edges);
	
	for(int x=0;x<grid.size();x++)
	{
		for(int y=0;y<grid[0].size();y++)
		{
			if(!controlMap[x][y])
				continue;
			IDWInterpolateOnArray(grid[x][y],grid,edges[controlMap[x][y]],smooth);
			controlMap[x][y]=0;
		}
	}
}
void CInterpolations::IDWInterpolatePoint(int x, int y, Vector3f& pnt, int winSize, vector<vector<Vector3f>>& grid, vector<vector<int>>& controlMap, double smooth)
{
	int sx=max(0,x-winSize);
	int ex=min(grid.size()-1,x+winSize);
	int sy=max(0,y-winSize);
	int ey=min(grid[0].size()-1,y+winSize);

	double u=0.0;
	double sum_wi=0.0;
	for(int _x=sx;_x<=ex;_x++)
	{
		for(int _y=sy;_y<=ey;_y++)
		{
			if(controlMap[_x][_y]!=1)
				continue;

			double wi=W(grid,pnt,_x,_y, smooth);

			u+=(wi*grid[_x][_y].z);
				
			sum_wi+=wi;
		}
	}
	pnt.z=u/sum_wi;
}
double CInterpolations::FindNeighbourMin(int x, int y, vector<vector<Vector3f>>& grid, vector<vector<int>>& controlMap, int winSize)
{
	double minVal=2000000;
	
	int sx=max(0,x-winSize);
	int ex=min(grid.size()-1,x+winSize);
	int sy=max(0,y-winSize);
	int ey=min(grid[0].size()-1,y+winSize);
	
	for(int _x=sx;_x<=ex;_x++)
	{
		for(int _y=sy;_y<=ey;_y++)
		{
			if(!controlMap[_x][_y])
			{
				if(grid[_x][_y].z<minVal)
					minVal=grid[_x][_y].z;
			}
		}
	}
	return minVal;
}
void CInterpolations::ClosestPointAndIDWInterpolation(vector<vector<Vector3f>>& grid, vector<vector<int>>& controlMap, Vector3f minPnt, double resolution, int idwSize)
{
	vector<vector<int>> dtMap(controlMap.size(),vector<int>(controlMap[0].size(),0));
	vector<PixelEl> vrsta;
	
	MMLibB2D mmb;mmb.data=controlMap;mmb.Init();
	mmb.bDT(dtMap);

	for(int x=0;x<controlMap.size();x++)
	{
		for(int y=0;y<controlMap[0].size();y++)
		{
			if(!controlMap[x][y])
				continue;

			PixelEl pnt;
			pnt.x=x;
			pnt.y=y;
			pnt.val=dtMap[x][y];
			vrsta.push_back(pnt);
		}
	}

	std::sort(vrsta.begin(),vrsta.end(),myfnS2L);
	
	/*START: Interpolation*/
	double addRes=resolution/2.0;
	int i=0;
	while(vrsta[i].val<idwSize)
	{

		int x=vrsta[i].x;
		int y=vrsta[i].y;
		
		double dfX=(double)((double)x*(double)resolution);
		double dfY=(double)((double)y*(double)resolution);
		double valX=(double)dfX+(double)minPnt.x+(double)addRes;
		double valY=(double)dfY+(double)minPnt.y+(double)addRes;
		
		grid[x][y].x=(float)(valX);
		grid[x][y].y=(float)(valY);
		
		IDWInterpolateRemovedPoint(x,y,grid[x][y],1,grid,controlMap,2.0);
		controlMap[x][y]=0;
		
		i++;
		if(i==vrsta.size())
			break;
	}

	for(int j=i;j<vrsta.size();j++)
	{
		int x=vrsta[j].x;
		int y=vrsta[j].y;
		
		double dfX=(double)((double)x*(double)resolution);
		double dfY=(double)((double)y*(double)resolution);
		double valX=(double)dfX+(double)minPnt.x+(double)addRes;
		double valY=(double)dfY+(double)minPnt.y+(double)addRes;
		
		grid[x][y].x=(float)(valX);
		grid[x][y].y=(float)(valY);
		grid[x][y].z=(float)FindNeighbourMin(x,y,grid,controlMap);
		controlMap[x][y]=0;
	}
	/*END: Interpolation*/
	return;
}
void CInterpolations::IDWInterpolatePoint(int x, int y, Vector3f& pnt, int winSize, vector<vector<Vector3f>>& grid, double smooth)
{
	int sx=max(0,x-winSize);
	int ex=min(grid.size()-1,x+winSize);
	int sy=max(0,y-winSize);
	int ey=min(grid[0].size()-1,y+winSize);

	double u=0.0;
	double sum_wi=0.0;
	for(int _x=sx;_x<=ex;_x++)
	{
		for(int _y=sy;_y<=ey;_y++)
		{
			double wi=W(grid,pnt,_x,_y, smooth);

			u+=(wi*grid[_x][_y].z);
				
			sum_wi+=wi;
		}
	}
	pnt.z=u/sum_wi;
}
void CInterpolations::IDWInterpolateRemovedPoint(int x, int y, Vector3f& pnt, int winSize, vector<vector<Vector3f>>& grid, vector<vector<int>>& controlMap, double smooth)
{
	int sx=max(0,x-winSize);
	int ex=min(grid.size()-1,x+winSize);
	int sy=max(0,y-winSize);
	int ey=min(grid[0].size()-1,y+winSize);

	double u=0.0;
	double sum_wi=0.0;
	for(int _x=sx;_x<=ex;_x++)
	{
		for(int _y=sy;_y<=ey;_y++)
		{
			if(controlMap[_x][_y])
				continue;

			double wi=W(grid,x,y,_x,_y, smooth);

			u+=(wi*grid[_x][_y].z);
				
			sum_wi+=wi;
		}
	}
	pnt.z=u/sum_wi;
}
void CInterpolations::IDWInterpolateOnArray(Vector3f& pnt, vector<vector<Vector3f>>& grid, vector<POINT>& edges, double smooth)
{
	double u=0.0;
	double sum_wi=0.0;
	for(int i=0;i<edges.size();i++)
	{
		double wi=W(grid,pnt,edges[i].x,edges[i].y,smooth);

		u+=(wi*grid[edges[i].x][edges[i].y].z);
				
		sum_wi+=wi;
	}
	pnt.z=u/sum_wi;
}
void CInterpolations::IDWInterpolatePointForCentering(int x, int y, Vector3f& pnt, int winSize, vector<vector<Vector3f>>& grid, double smooth)
{
	int sx=max(0,x-winSize);
	int ex=min(grid.size()-1,x+winSize);
	int sy=max(0,y-winSize);
	int ey=min(grid[0].size()-1,y+winSize);

	double u=0.0;
	double sum_wi=0.0;
	int noUsedPoints=0;
	for(int _x=sx;_x<=ex;_x++)
	{
		for(int _y=sy;_y<=ey;_y++)
		{
			double wi=W(grid,x,y,_x,_y, smooth);

			u+=(wi*grid[_x][_y].z);
				
			sum_wi+=wi;
			noUsedPoints++;
		}
	}
	pnt.z=u/sum_wi;
}
double CInterpolations::W(vector<vector<Vector3f>>& grid, int x, int y,int xi, int yi, double smooth)
{
	Vector3f pnt=grid[x][y]-grid[xi][yi];

	double dist2=pnt.x*pnt.x+pnt.y*pnt.y;
	
	dist2=pow(dist2,smooth);

	if(dist2==0.0)//hack
		dist2=0.00000000001;
	
	return 1.0/dist2;
}
double CInterpolations::W(vector<vector<Vector3f>>& grid, Vector3f iPnt,int xi, int yi, double smooth)
{
	Vector3f pnt=iPnt-grid[xi][yi];

	double dist2=pnt.x*pnt.x+pnt.y*pnt.y;
	
	dist2=pow(dist2,smooth);

	if(dist2==0.0)//hack
		dist2=0.00000000001;
	
	return 1.0/dist2;
}
		/*HELP FUNCTIONS*/
void CInterpolations::CreateVectorGridFromData(vector<vector<Vector3f>>& grid, vector<vector<double>>& data)
{
	vector<vector<Vector3f>> tGrid(data.size(),vector<Vector3f>(data[0].size()));
	grid=tGrid;
	for(int x=0;x<data.size();x++)
	{
		for(int y=0;y<data[0].size();y++)
		{
			grid[x][y].x=x;
			grid[x][y].y=y;
			grid[x][y].z=data[x][y];
		}
	}
}
//DATA CLASSIFICATION FUNCTIONS
CDataClasiffication::CDataClasiffication()
{
	modelLoaded=false;
}
void CDataClasiffication::GetHistogram(vector<vector<int>>& iImg, vector<vector<int>>& cntImg, vector<int>& hGram, int c)
{
	for(int x=0;x<iImg.size();x++)
	{
		for(int y=0;y<iImg[0].size();y++)
		{
			if(cntImg[x][y]==c)
				hGram[iImg[x][y]]++;
		}
	}
}
void CDataClasiffication::GetHistogram(vector<vector<int>>& iImg, vector<vector<int>>& cntImg, vector<double>& hGram, int c, bool normalize)
{
	int allpnts=0;
	for(int x=0;x<iImg.size();x++)
	{
		for(int y=0;y<iImg[0].size();y++)
		{
			if(cntImg[x][y]==c)
			{
				hGram[iImg[x][y]]++;
				allpnts++;
			}
		}
	}
	if(normalize)
	{
		for(int i=0; i<hGram.size();i++)
			hGram[i]=(double)hGram[i]/(double)allpnts;
	}
}
void CDataClasiffication::GetHistogram(vector<vector<double>>& dImg, vector<vector<int>>& cntImg, vector<double>& hGram, int c, double scale, bool normalize)
{
	int allpnts=0;
	for(int x=0;x<dImg.size();x++)
	{
		for(int y=0;y<dImg[0].size();y++)
		{
			if(cntImg[x][y]==c)
			{
				int index=dImg[x][y]/scale;
				hGram[index]++;
				allpnts++;
			}
		}
	}
	if(normalize)
	{
		for(int i=0; i<hGram.size();i++)
			hGram[i]=(double)hGram[i]/(double)allpnts;
	}
}
void CDataClasiffication::AddClass(int c)
{
	classes.push_back(c);
}
void CDataClasiffication::InitClassProbabilities(vector<vector<int>>& cntImg)
{
	vector<double> tcProbs(classes.size(),0.0);
	cProbs=tcProbs;
	int allPnts=0;
	for(int x=0;x<cntImg.size();x++)
	{
		for(int y=0;y<cntImg[0].size();y++)
		{
			if(!cntImg[x][y])
				continue;
			
			/*START: Search for class index*/
			int index=-1;
			for(int i=0;i<classes.size();i++)
			{
				if(classes[i]==cntImg[x][y])
					index=i;
			}
			/*END: Search for class index*/
			if(index>=0)
			{
				cProbs[index]++;
				allPnts++;
			}
		}
	}
	for(int i=0;i<classes.size();i++)
		cProbs[i]=cProbs[i]/(double)allPnts;
}
void CDataClasiffication::AddStatsToModel(vector<vector<int>>& data, vector<vector<int>>& cntImg, double minVal, double maxVal, int scale, bool normalize)
{
	int hgSize=(maxVal-minVal)/scale+1.5;
	scales.push_back(scale);
	minVals.push_back(minVal);
	maxVals.push_back(maxVal);
	for(int i=0;i<classes.size();i++)
	{
		vector<double> hGramC(hgSize,0.0);
		GetHistogram(data,cntImg,hGramC,classes[i],normalize);
		statModel.push_back(hGramC);
	}
}
void CDataClasiffication::AddStatsToModel(vector<vector<double>>& data, vector<vector<int>>& cntImg, double minVal, double maxVal, double scale, bool normalize)
{
	int hgSize=(maxVal-minVal)/scale+1.5;

	scales.push_back(scale);
	minVals.push_back(minVal);
	maxVals.push_back(maxVal);
	for(int i=0;i<classes.size();i++)
	{
		vector<double> hGramC(hgSize,0.0);
		GetHistogram(data,cntImg,hGramC,classes[i],scale,normalize);
		statModel.push_back(hGramC);
	}
}
double CDataClasiffication::GetUpperFractValue(int c, vector<int>& fIndex)
{
	double val=statModel[c][fIndex[0]];
	for(int i=1;i<fIndex.size();i++)
	{
		int statRow=c+i*classes.size();
		int statCol=fIndex[i];
		val*=statModel[statRow][statCol];
	}
	return val;
}
int CDataClasiffication::ClassifyByBayesLogic(vector<double> featVector)
{
	vector<int> fIndexes(featVector.size());
	for(int i=0;i<featVector.size();i++)
		fIndexes[i]=(featVector[i]-minVals[i])/scales[i];
	
	vector<double> probC=cProbs;
	
	for(int c=0;c<probC.size();c++)
	{
		probC[c]*=GetUpperFractValue(c,fIndexes);
	}

	double maxVal=probC[0];
	int cInd=0;
	for(int c=0;c<probC.size();c++)
	{
		if(maxVal<probC[c])
		{
			maxVal=probC[c];
			cInd=c;	
		}
	}
	
	return classes[cInd];
}
void CDataClasiffication::ClearStatModel()
{
	classes.clear();
	cProbs.clear();
	scales.clear();
	minVals.clear();
	maxVals.clear();
	statModel.clear();
}
void CDataClasiffication::ExportStatModel(CString filePath)
{
	CString txt;
	CString tmp;

	for(int c=0;c<classes.size();c++)
	{
		tmp.Format("%d\t",classes[c]);
		txt+=tmp;
	}
	txt.Append("\n");
	
	for(int c=0;c<classes.size();c++)
	{
		tmp.Format("%.8f\t",cProbs[c]);
		txt+=tmp;
	}
	txt.Append("\n");
	

	for(int s=0;s<scales.size();s++)
	{
		tmp.Format("%.3f\t",scales[s]);
		txt+=tmp;
	}
	txt.Append("\n");

	for(int mv=0;mv<minVals.size();mv++)
	{
		tmp.Format("%.3f\t",minVals[mv]);
		txt+=tmp;
	}
	txt.Append("\n");

	for(int mv=0;mv<maxVals.size();mv++)
	{
		tmp.Format("%.3f\t",maxVals[mv]);
		txt+=tmp;
	}
	txt.Append("\n");

	for(int m=0;m<statModel.size();m++)
	{
		for(int i=0;i<statModel[m].size();i++)
		{
		
			tmp.Format("%.8f\t",statModel[m][i]);
			txt+=tmp;
		}
		txt.Append("\n");
	}
	
	FILE* file=fopen(filePath.GetBuffer(),"w");
	fwrite(txt.GetBuffer(),sizeof(char),txt.GetLength(),file);
	fclose(file);
}

void CDataClasiffication::LoadStatModel(CString filePath)
{
	ClearStatModel();
	/*START: Read whole file*/
	CFile file;
	CString str;
	if(file.Open(filePath, CFile::modeRead))
	{
	  int len = file.GetLength();
	  file.Read(str.GetBuffer(len), len);
	  str.ReleaseBuffer();
	}
	/*END: Read whole file*/

	CString Seperator = "\t";
	CString lineSeparator = "\n";
	int Position = 0;
	int lPos = 0;

	CString token,line;
	line=str.Tokenize(lineSeparator, Position);line.TrimRight(13);line.TrimRight(9);//Trimani so 1. \n in 2.\t
	
	token=line.Tokenize(Seperator,lPos);
	while(!token.IsEmpty())
	{
		int c=atoi(token);
		classes.push_back(c);
		token=line.Tokenize(Seperator,lPos);
	}

	lPos=0;
	line=str.Tokenize(lineSeparator, Position);line.TrimRight(13);line.TrimRight(9);//Trimani so 1. \n in 2.\t
	token=line.Tokenize(Seperator,lPos);
	while(!token.IsEmpty())
	{
		double cp=atof(token);
		cProbs.push_back(cp);
		token=line.Tokenize(Seperator,lPos);
	}

	lPos=0;
	line=str.Tokenize(lineSeparator, Position);line.TrimRight(13);line.TrimRight(9);//Trimani so 1. \n in 2.\t
	token=line.Tokenize(Seperator,lPos);
	while(!token.IsEmpty())
	{
		double s=atof(token);
		scales.push_back(s);
		token=line.Tokenize(Seperator,lPos);
	}

	lPos=0;
	line=str.Tokenize(lineSeparator, Position);line.TrimRight(13);line.TrimRight(9);//Trimani so 1. \n in 2.\t
	token=line.Tokenize(Seperator,lPos);
	while(!token.IsEmpty())
	{
		double s=atof(token);
		minVals.push_back(s);
		token=line.Tokenize(Seperator,lPos);
	}

	lPos=0;
	line=str.Tokenize(lineSeparator, Position);line.TrimRight(13);line.TrimRight(9);//Trimani so 1. \n in 2.\t
	token=line.Tokenize(Seperator,lPos);
	while(!token.IsEmpty())
	{
		double s=atof(token);
		maxVals.push_back(s);
		token=line.Tokenize(Seperator,lPos);
	}
	line=str.Tokenize(lineSeparator, Position);line.TrimRight(13);line.TrimRight(9);//Trimani so 1. \n in 2.\t
	while(!line.IsEmpty())
	{
		lPos=0;
		vector<double> statLine;
		
		token=line.Tokenize(Seperator,lPos);
		while(!token.IsEmpty())
		{
			double stat=atof(token);
			statLine.push_back(stat);
			token=line.Tokenize(Seperator,lPos);
		}

		statModel.push_back(statLine);
		line=str.Tokenize(lineSeparator, Position);line.TrimRight(13);line.TrimRight(9);//Trimani so 1. \n in 2.\t
	} 
	modelLoaded=true;
}