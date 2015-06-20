#include "StdAfx.h"
#include <sstream>
#include "CompilerSemanticInterface.h"
#include "MMLib.h"
using namespace std;

CompilerSemanticInterface::CompilerSemanticInterface()
{
	// CONSTRUCTOR
}

void CompilerSemanticInterface::LoadImg(string filePath, vector<vector<double>>& img)
{
	CBitmapEx bmp;	CString test = filePath.c_str();
	bmp.Load(test.GetBuffer());
	
	/*START: Set new window size*/
	int w = bmp.GetWidth(); 
	int h = bmp.GetHeight();

	vector<vector<double>> tmp(bmp.GetWidth(),vector<double>(bmp.GetHeight(),0.0));
	BYTE* buffer=new BYTE[tmp.size()*tmp[0].size()];
	bmp.GetBlueChannel(buffer);
	for(int x=0;x<tmp.size();x++)
	{
		for(int y=0;y<tmp[0].size();y++)
		{
			
			tmp[x][y]=(double)buffer[y*tmp.size()+x];
		}
	}
	img=tmp;
	/*END: Set new window size*/
}
void CompilerSemanticInterface::LoadFile(string filePath, vector<vector<double>>& img)
{
	CString tFile = filePath.c_str();
	FILE* file=fopen(tFile.GetBuffer(),"rb");

	int sizeX=0;	fread(&sizeX,sizeof(int),1,file);
	int sizeY=0;	fread(&sizeY,sizeof(int),1,file);

	vector<vector<double>> nImg(sizeX,vector<double>(sizeY));
	for(int x=0;x<sizeX;x++)
	{
		fread(&nImg[x][0],sizeof(double),sizeY,file);
	}

	img=nImg;
	fclose(file);
}
void CompilerSemanticInterface::LoadFile(string filePath, vector<vector<vector<double>>>& img)
{
	CString tFile = filePath.c_str();
	FILE* file=fopen(tFile.GetBuffer(),"rb");

	int sizeX=0;	fread(&sizeX,sizeof(int),1,file);
	int sizeY=0;	fread(&sizeY,sizeof(int),1,file);
	int sizeZ=0;	fread(&sizeZ,sizeof(int),1,file);

	vector<vector<vector<double>>> nImg(sizeX,vector<vector<double>>(sizeY, vector<double>(sizeZ,0)));
	for(int x=0;x<sizeX;x++)
	{
		for(int y=0;y<sizeY;y++)
		{
			fread(&nImg[x][y][0],sizeof(double),sizeZ,file);
		}
	}

	img=nImg;
	fclose(file);
}

void CompilerSemanticInterface::StoreImg(string filePath, vector<vector<double>>& img)
{
	CBitmapEx bmp;	CString test = filePath.c_str();
	bmp.Create(img.size(),img[0].size());
	
	for(int x=0;x<img.size();x++)
	{
		for(int y=0;y<img[0].size();y++)
		{
			COLORREF color(RGB(img[x][y],img[x][y],img[x][y]));
			bmp.SetPixel(x,img[0].size()-y-1,color);
		}
	}

	bmp.Save(test.GetBuffer());
}

void CompilerSemanticInterface::StoreFile(string filePath, vector<vector<double>>& img)
{
	CString tFile = filePath.c_str();
	FILE* file=fopen(tFile.GetBuffer(),"wb");

	int sizeX=img.size();		fwrite(&sizeX,sizeof(int),1,file);
	int sizeY=img[0].size();	fwrite(&sizeY,sizeof(int),1,file);
	
	for(int x=0;x<sizeX;x++)
	{
		fwrite(&img[x][0],sizeof(double),sizeY,file);
	}

	fclose(file);
}
void CompilerSemanticInterface::StoreFile(string filePath, vector<vector<vector<double>>>& img)
{
	CString tFile = filePath.c_str();
	FILE* file=fopen(tFile.GetBuffer(),"wb");

	int sizeX=img.size();		fwrite(&sizeX,sizeof(int),1,file);
	int sizeY=img[0].size();	fwrite(&sizeY,sizeof(int),1,file);
	int sizeZ=img[0][0].size();	fwrite(&sizeZ,sizeof(int),1,file);
	
	for(int x=0;x<sizeX;x++)
	{
		for(int y=0;y<sizeY;y++)
		{
			fwrite(&img[x][y][0],sizeof(double),sizeZ,file);
		}
	}

	fclose(file);
}
// b = open(BOX(1), a)
void CompilerSemanticInterface::openBOX(double aNumber, string inputFileName, string outputFileName){
	
	printf("INSIDE INTERFACE OPENBOX 1!\n");
	vector<vector<double>> img;
	LoadImg(inputFileName,img);

	MMLibG2D mmg;
	mmg.data=img;
	mmg.Init();
	mmg.FastOpen(aNumber);
	img=mmg.data;
	StoreImg(outputFileName,img);
}

//f = treshold(10, e)
void CompilerSemanticInterface::treshold(double aNumber, string inputFileName, string outputFileName){
	
	vector<vector<double>> img;
	LoadImg(inputFileName,img);
	vector<vector<int>> bImg(img.size(),vector<int>(img[0].size(),0));

	CThresholding th;
	th.CostantThreshold(img,bImg,aNumber);

	CopyDataToData(bImg,img);
	StoreImg(outputFileName,img);
}

// c = close(BOX(1), b)
void CompilerSemanticInterface::closeBOX(double aNumber, string inputFileName, string outputFileName)
{
	vector<vector<double>> img;
	LoadImg(inputFileName,img);

	MMLibG2D mmg;
	mmg.data=img;
	mmg.Init();
	mmg.FastClose(aNumber);
	img=mmg.data;

	StoreImg(outputFileName,img);
}

// d = open(AREA, 250, c)
void CompilerSemanticInterface::openAREA(double aNumber, string inputFileName, string outputFileName)
{
	vector<vector<double>> img;
	LoadImg(inputFileName,img);

	MaxTree tree(img);
	tree.AreaOpening(aNumber);
	tree.Height2Img(img);

	StoreImg(outputFileName,img);
}

void CompilerSemanticInterface::negate(string inputFileName, string outputFileName)
{
	vector<vector<double>> img;
	LoadImg(inputFileName,img);

	MultiplyData(img,-1);
	NormalizeData(img,0.0,255.0);

	StoreImg(outputFileName,img);
}

void CompilerSemanticInterface::normalize(string inputFileName, string outputFileName)
{
	vector<vector<double>> img;
	LoadImg(inputFileName,img);
	
	NormalizeData(img,0.0,255.0);
	
	StoreImg(outputFileName,img);

}

void CompilerSemanticInterface::multiply(string inputFileName, double aNumber, string outputFileName)
{
	vector<vector<double>> img;
	LoadImg(inputFileName,img);
	
	MultiplyData(img,aNumber); //POPRAVLJENO

	StoreImg(outputFileName,img);
}

void CompilerSemanticInterface::multiply(double aNumber , string inputFileName, string outputFileName)
{
	vector<vector<double>> img;
	LoadImg(inputFileName,img);

	MultiplyData(img,aNumber);

	StoreImg(outputFileName,img);

}
void CompilerSemanticInterface::multiply(string inputFileName1, string inputFileName2, string outputFileName)
{
	vector<vector<double>> img1;
	LoadImg(inputFileName1,img1);

	vector<vector<double>> img2;
	LoadImg(inputFileName2,img2);

	MultiplyData(img1,img2);

	StoreImg(outputFileName,img1);
}
void CompilerSemanticInterface::crop(string inputFileName, double lowNumber , double upNumber, string outputFileName)
{
	vector<vector<double>> img;
	LoadImg(inputFileName,img);
	
	CropData(img,lowNumber,upNumber);

	StoreImg(outputFileName,img);

}

// e = subtract (d,c)
void CompilerSemanticInterface::subtract(string inputFileName1, string inputFileName2, string outputFileName)
{
	vector<vector<double>> img1;
	vector<vector<double>> img2;
	LoadImg(inputFileName1,img1);
	LoadImg(inputFileName2,img2);

	SubtractData(img1,img2);

	StoreImg(outputFileName,img1);
}

void CompilerSemanticInterface::erodeBOX(double aNumber, string inputFileName, string outputFileName)     
{
	vector<vector<double>> img;
	LoadImg(inputFileName,img);

	MMLibG2D mmg;
	mmg.data=img;
	mmg.Init();
	mmg.FastErode(aNumber);
	img=mmg.data;

	StoreImg(outputFileName,img);
}

void CompilerSemanticInterface::dilateBOX( double aNumber, string inputFileName, string outputFileName)
{
	vector<vector<double>> img;
	LoadImg(inputFileName,img);

	// MISLIM DA JE TUKAJ ISTI BUG, KOT SVA GA ŽE IMELA
	
	MMLibG2D mmg;
	mmg.data=img;
	mmg.Init();
	mmg.FastDilate(aNumber);
	img=mmg.data;

	StoreImg(outputFileName,img);
}

void CompilerSemanticInterface::closeAREA(double aNumber, string inputFileName, string outputFileName)
{
	printf("INSIDE INTERFACE CLOSEAREA 1!\n");
	vector<vector<double>> img;
	LoadImg(inputFileName,img);
	printf("INSIDE INTERFACE CLOSEAREA 2!\n");
	
	vector<vector<double>> invData=img;
	InvertData(invData);

	printf("INSIDE INTERFACE CLOSEAREA 3!\n");
	MaxTree tree(invData);
	printf("INSIDE INTERFACE CLOSEAREA 4!\n");
	tree.AreaOpening(aNumber);
	printf("INSIDE INTERFACE CLOSEAREA 5!\n");
	tree.Height2Img(invData);
	printf("INSIDE INTERFACE CLOSEAREA 6!\n");
	InvertData(invData);

	img=invData;

	printf("BEFORE STORE!\n");
	StoreImg(outputFileName,img);
	printf("AFTER STORE!\n");
}

void CompilerSemanticInterface::complement(string inputFileName, string outputFileName)
{
	vector<vector<double>> img;
	LoadImg(inputFileName,img);
	
	vector<vector<int>> iImg(img.size(),vector<int>(img[0].size(),0));
	CopyDataToData(img,iImg);

	BComplementData(iImg);
	
	CopyDataToData(iImg,img);

	StoreImg(outputFileName,img);
}

void CompilerSemanticInterface::unionBB(string inputFileName1, string inputFileName2, string outputFileName)
{
	vector<vector<double>> img1,img2;
	LoadImg(inputFileName1,img1);
	LoadImg(inputFileName2,img2);
	
	vector<vector<int>> iImg1(img1.size(),vector<int>(img1[0].size(),0));
	vector<vector<int>> iImg2(img2.size(),vector<int>(img2[0].size(),0));
	CopyDataToData(img1,iImg1);
	CopyDataToData(img2,iImg2);

	SetUnion(iImg1,iImg2);
	
	CopyDataToData(iImg1,img1);
	StoreImg(outputFileName,img1);
}

void CompilerSemanticInterface::intersection(string inputFileName1, string inputFileName2, string outputFileName)
{	
	vector<vector<double>> img1,img2;
	LoadImg(inputFileName1,img1);
	LoadImg(inputFileName2,img2);
	
	vector<vector<int>> iImg1(img1.size(),vector<int>(img1[0].size(),0));
	vector<vector<int>> iImg2(img2.size(),vector<int>(img2[0].size(),0));
	CopyDataToData(img1,iImg1);
	CopyDataToData(img2,iImg2);

	SetIntersection(iImg1,iImg2);
	
	CopyDataToData(iImg1,img1);
	StoreImg(outputFileName,img1);
}

void CompilerSemanticInterface::without(string inputFileName1, string inputFileName2, string outputFileName)
{
	vector<vector<double>> img1,img2;
	LoadImg(inputFileName1,img1);
	LoadImg(inputFileName2,img2);
	
	vector<vector<int>> iImg1(img1.size(),vector<int>(img1[0].size(),0));
	vector<vector<int>> iImg2(img2.size(),vector<int>(img2[0].size(),0));
	CopyDataToData(img1,iImg1);
	CopyDataToData(img2,iImg2);

	SetWithout(iImg1,iImg2);
	
	CopyDataToData(iImg1,img1);
	StoreImg(outputFileName,img1);
}

void CompilerSemanticInterface::hitmiss(string inputFileName1, string inputFileName2, string outputFileName)
{
	vector<vector<double>> img;
	LoadImg(inputFileName1,img);
	// DOMEN - your code goes here ;-)

	StoreImg(outputFileName,img);
}

void CompilerSemanticInterface::boundary(string inputFileName, string outputFileName)
{
	vector<vector<double>> img;
	LoadImg(inputFileName,img);
	// DOMEN - your code goes here ;-)

	StoreImg(outputFileName,img);
}

void CompilerSemanticInterface::gradientINTERNAL(string inputFileName, string outputFileName)     
{
	vector<vector<double>> img;
	LoadImg(inputFileName,img);
	
	EdgeDetection ed;
	ed.InternalMGradient(img);

	vector<vector<double>> tImg;

	StoreImg(outputFileName,img);
}

void CompilerSemanticInterface::gradientEXTERNAL(string inputFileName, string outputFileName)  
{
	vector<vector<double>> img;
	LoadImg(inputFileName,img);
	
	EdgeDetection ed;
	ed.ExternalMGradient(img);

	StoreImg(outputFileName,img);
}

void CompilerSemanticInterface::diferentialProfilesMORPHOLOGICAL (string inputFileName, vector<double> values, string outputFileNamePartially)
{
	vector<vector<double>> img;
	LoadImg(inputFileName,img);

	vector<vector<vector<double>>> f_stack;
	vector<int> wVec; for(int i=0;i<values.size();i++)wVec.push_back(values[i]);

	MMLibG2D mmg;
	mmg.data=img;
	mmg.Init();
	mmg.DMP(f_stack,wVec);

	outputFileNamePartially+=".wtf";

	StoreFile(outputFileNamePartially,f_stack);
}

void CompilerSemanticInterface::diferentialProfilesATTRIBUTE (string inputFileName, vector<double> values, string outputFileNamePartially)    
{
	vector<vector<double>> img;
	LoadImg(inputFileName,img);

	vector<vector<vector<double>>> f_stack;
	
	/*START: DAP*/
	vector<vector<double>> levelImg(img.size(),vector<double>(img[0].size(),0.0));

	vector<vector<double>> dap_line=levelImg;
	vector<vector<double>> dap_dot=levelImg;
	/*START: Get DAP*/
	int noLevels=2000;
	CreateLevelImg(img,levelImg,noLevels);
	MaxTree tree(levelImg,img,noLevels+1);
	tree.SetAreaAttribute();
	tree.DAP(values,false);
	tree.Parameter2Img(dap_line); CropData(dap_line,0.0,10.0);
	tree.NodeParameter2Img(dap_dot);
	/*END: Get DAP*//*END: DAP*/

	outputFileNamePartially+=".wtf";

	f_stack.push_back(dap_line);
	f_stack.push_back(dap_dot);
	StoreFile(outputFileNamePartially,f_stack);
}

void CompilerSemanticInterface::mappingDMP(string inputFileName, vector<double> values, string outputFileNamePartially)   
{
	vector<vector<double>> img;
	LoadImg(inputFileName,img);

	vector<vector<vector<double>>> f_stack;
	vector<vector<double>> f_line(img.size(), vector<double>(img[0].size(),0.0));
	vector<vector<int>>    f_dot(img.size(), vector<int>(img[0].size(),0.0));
	vector<int> wVec; for(int i=0;i<values.size();i++)wVec.push_back(values[i]);

	MMLibG2D mmg;
	mmg.data=img;
	mmg.Init();
	mmg.DMP(f_line,f_dot,wVec);

	outputFileNamePartially+=".wtf";

	f_stack.push_back(f_line);
	f_stack.push_back(f_line);
	CopyDataToData(f_dot,f_stack[1]);

	StoreFile(outputFileNamePartially,f_stack);
}

void CompilerSemanticInterface::mappingDAP(string inputFileName, vector<double> values, string outputFileNamePartially)    
{
	vector<vector<double>> img;
	LoadImg(inputFileName,img);

	vector<vector<vector<double>>> f_stack;
	
	/*START: DAP*/
	vector<vector<double>> levelImg(img.size(),vector<double>(img[0].size(),0.0));

	vector<vector<double>> dap_line=levelImg;
	vector<vector<double>> dap_dot=levelImg;
	/*START: Get DAP*/
	int noLevels=2000;
	CreateLevelImg(img,levelImg,noLevels);
	MaxTree tree(levelImg,img,noLevels+1);
	tree.SetAreaAttribute();
	tree.DAP(values,false);
	tree.Parameter2Img(dap_line); CropData(dap_line,0.0,10.0);
	tree.NodeParameter2Img(dap_dot);
	/*END: Get DAP*//*END: DAP*/

	outputFileNamePartially+=".wtf";

	f_stack.push_back(dap_line);
	f_stack.push_back(dap_dot);
	StoreFile(outputFileNamePartially,f_stack);
}

void CompilerSemanticInterface::segmentationMSLS (string inputFileName1, vector<double> values, string outputFileName)
{
	vector<vector<double>> img;
	LoadImg(inputFileName1,img);
	// TOMAŽ: Tukaj notri dobimo vektor attributnih vrednosti

	StoreImg(outputFileName,img);
}

void CompilerSemanticInterface::segmentationWATHERSHADE(string inputFileName, string outputFileName)
{
	vector<vector<double>> img;
	LoadImg(inputFileName,img);

	vector<vector<int>> iImg(img.size(),vector<int>(img[0].size()));
	MMLibG2D mmg;
	mmg.data=img;
	mmg.Init();
	mmg.Watershed(iImg);

	CopyDataToData(iImg,img);

	StoreFile(outputFileName,img);
}

void CompilerSemanticInterface::segmentationWATHERSHADE(string inputFileName1, string inputFileName2, string outputFileName)
{
	vector<vector<double>> img1;
	LoadImg(inputFileName1,img1);
	vector<vector<double>> img2;
	LoadImg(inputFileName2,img2);
/*
	vector<vector<int>> iImg(img1.size(),vector<int>(img1[0].size()));
	vector<vector<int>> mImg(img1.size(),vector<int>(img1[0].size())); CopyDataToData(iImg2,mImg);
	MMLibG2D mmg;
	mmg.data=img;
	mmg.Init();
	mmg.WatershedOnMarkers(mImg,iImg);

	CopyDataToData(iImg,img1);
	StoreFile(outputFileName,img1);
*/
}


void CompilerSemanticInterface::erodeRECONSTRUCTION(string inputFileName1, string inputFileName2, string outputFileName)
{
	vector<vector<double>> img;
	LoadImg(inputFileName1,img);
	InvertData(img);
	
	MMLibG2D mmg;LoadImg(inputFileName2,mmg.data);
	InvertData(mmg.data);
	mmg.Init();
	mmg.ReconstructionByDilation(img);

	InvertData(mmg.data);

	StoreImg(outputFileName,mmg.data);
}
/*
void CompilerSemanticInterface::erodeRECONSTRUCTION(double aNumber, string inputFileName, string outputFileName)
{
	//BRISANJE
	vector<vector<double>> img;
	LoadImg(inputFileName,img);

	InvertData(img);
	
	MMLibG2D mmg;
	mmg.data=img;
	mmg.Init();
	mmg.ReconstructionByDilation(img);

	img=mmg.data;
	InvertData(img);

	StoreImg(outputFileName,img);
}
*/

void CompilerSemanticInterface::dilateRECONSTRUCTION(string inputFileName1, string inputFileName2, string outputFileName)
{
	vector<vector<double>> img;
	LoadImg(inputFileName1,img);
	
	MMLibG2D mmg;LoadImg(inputFileName2,mmg.data);
	mmg.Init();
	mmg.ReconstructionByDilation(img);
	
	StoreImg(outputFileName,mmg.data);
}

void CompilerSemanticInterface::openRECONSTRUCTION_BOX(double aNumber, string inputFileName, string outputFileName)
{
	vector<vector<double>> img;
	LoadImg(inputFileName,img);
	
	MMLibG2D mmg;
	mmg.data=img;
	mmg.Init();
	mmg.OpeningByReconstruction(aNumber);
	img=mmg.data;

	StoreImg(outputFileName,img);
}
void CompilerSemanticInterface::closeRECONSTRUCTION_BOX(double aNumber, string inputFileName, string outputFileName)
{
	vector<vector<double>> img;
	LoadImg(inputFileName,img);
	
	MMLibG2D mmg;
	mmg.data=img;InvertData(mmg.data);
	mmg.Init();
	mmg.OpeningByReconstruction(aNumber);
	img=mmg.data;

	InvertData(img);
	StoreImg(outputFileName,img);
}

void CompilerSemanticInterface::open(string attributeName, double aNumber, string inputFileName, string outputFileName)
{
	vector<vector<double>> img;
	LoadImg(inputFileName,img);
	// DOMEN - your code goes here ;-)

	StoreImg(outputFileName,img);
}

void CompilerSemanticInterface::close(string attributeName, double aNumber, string inputFileName, string outputFileName)
{
	vector<vector<double>> img;
	LoadImg(inputFileName,img);
	// DOMEN - your code goes here ;-)

	StoreImg(outputFileName,img);
}

void CompilerSemanticInterface::distanceTransform(string inputFileName, string outputFileName)
{
	vector<vector<double>> img;
	LoadImg(inputFileName,img);
	// DOMEN - your code goes here ;-)

	StoreImg(outputFileName,img);
}