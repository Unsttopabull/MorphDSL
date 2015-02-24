#pragma once
#include "../stdafx.h"
#include <string>
#include <vector>
#include "..\BMP\BitmapEx.h"

using namespace std;

class CompilerSemanticInterface {
	public:
	CompilerSemanticInterface();
	
	//Help functions
	void LoadImg(string filePath, vector<vector<double>>& img);														//DONE
	void LoadFile(string filePath, vector<vector<double>>& img);													//DONE
	void LoadFile(string filePath, vector<vector<vector<double>>>& img);											//DONE
	void StoreImg(string filePath, vector<vector<double>>& img);													//DONE
	void StoreFile(string filePath, vector<vector<double>>& img);													//DONE
	void StoreFile(string filePath, vector<vector<vector<double>>>& img);											//DONE
	
	//operatorsBB
	void complement(string inputFileName, string outputFileName);													//DONE
	void unionBB(string inputFileName1, string inputFileName2, string outputFileName);								//DONE
	void intersection(string inputFileName1, string inputFileName2, string outputFileName);							//DONE
	void without(string inputFileName1, string inputFileName2, string outputFileName);								//DONE
	void hitmiss(string inputFileName1, string inputFileName2, string outputFileName);										//TODO
	void boundary(string inputFileName, string outputFileName);																//TODO

	//operatorsGG
	void negate(string inputFileName, string outputFileName);														//DONE
	void normalize(string inputFileName, string outputFileName);													//DONE
	void multiply(string inputFileName, double aNumber, string outputFileName);										//DONE
	void multiply(double aNumber , string inputFileName, string outputFileName);									//DONE
	void multiply(string inputFileName1, string inputFileName2, string outputFileName);								//DONE
	void crop(string inputFileName, double lowNumber , double upNumber, string outputFileName);						//DONE
	void subtract(string inputFileName1, string inputFileName2, string outputFileName);								//DONE
	void gradientINTERNAL(string inputFileName, string outputFileName);												//DONE   
	void gradientEXTERNAL(string inputFileName, string outputFileName);												//DONE
	void diferentialProfilesMORPHOLOGICAL (string inputFileName, vector<double> values, string outputFileNamePartially); //DONE
	void diferentialProfilesATTRIBUTE (string inputFileName, vector<double> values, string outputFileNamePartially);//DONE
	void mappingDMP(string inputFileName, vector<double> values, string outputFileNamePartially);					//DONE 
	void mappingDAP(string inputFileName, vector<double> values, string outputFileNamePartially);					//DONE 
	void segmentationMSLS (string inputFileName, vector<double> values, string outputFileName);								//TODO 
	void segmentationWATHERSHADE(string inputFileName, string outputFileName);										//DONE 
	void segmentationWATHERSHADE(string inputFileName1, string inputFileName2, string outputFileName);				//DONE 
//  brisano pusti, ker še nisem zbrisal iz jezika...
//	void segmentationWATHERSHADE(double aNumber, string inputFileName, string outputFileName);						//BRIŠI

	//operatorsBOX
	void erodeBOX(double aNumber, string inputFileName, string outputFileName);										// DONE  
	void dilateBOX( double aNumber, string inputFileName, string outputFileName);   								// DONE 
	void openBOX(double aNumber, string inputFileName, string outputFileName);      								// DONE   
	void closeBOX(double aNumber, string inputFileName, string outputFileName);     								// DONE

	//operatorsRECONSTRUCTION
	void erodeRECONSTRUCTION(string inputFileName1, string inputFileName2, string outputFileName); 					//DONE
//	void erodeRECONSTRUCTION(double aNumber, string inputFileName, string outputFileName);  						//BRIŠI
	void dilateRECONSTRUCTION(string inputFileName1, string inputFileName2, string outputFileName); 				//DONE
//	void dilateRECONSTRUCTION(double aNumber, string inputFileName, string outputFileName); 						//BRIŠI
	void openRECONSTRUCTION_BOX(double aNumber, string inputFileName, string outputFileName); 						//DONE
	void closeRECONSTRUCTION_BOX(double aNumber, string inputFileName, string outputFileName); 						//DONE

	//operatorsAREA
	void openAREA(double aNumber, string inputFileName, string outputFileName);										// DONE
	void closeAREA(double aNumber, string inputFileName, string outputFileName);									// DONE

	//operatorsATTRIBUTE
	void open(string attributeName, double aNumber, string inputFileName, string outputFileName); 							//TODO
	void close(string attributeName, double aNumber, string inputFileName, string outputFileName); 							//TODO

	//operatorsBG
	void distanceTransform(string inputFileName, string outputFileName); 													//TODO

	//operatorsGB
	void treshold(double aNumber, string inputFileName, string outputFileName);										// DONE
};