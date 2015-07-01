#pragma once
#include <vector>

using namespace std;

class CompilerSemanticInterface {
	public:
	CompilerSemanticInterface();
	
	//Help functions
	void LoadImg(const string& filePath, vector<vector<double>>& img) const;												          //DONE
    void LoadFile(const string& filePath, vector<vector<double>>& img) const;													      //DONE
    void LoadFile(const string& filePath, vector<vector<vector<double>>>& img) const;											      //DONE
    void StoreImg(const string& filePath, vector<vector<double>>& img) const;													      //DONE
    void StoreFile(const string& filePath, vector<vector<double>>& img) const;													      //DONE
    void StoreFile(const string& filePath, vector<vector<vector<double>>>& img) const;											      //DONE
	                                                                                                                                  
	//operatorsBB                                                                                                                     
    void complement(const string& inputFileName, const string& outputFileName) const;												  //DONE
    void unionBB(const string& inputFileName1, const string& inputFileName2, const string& outputFileName) const;				      //DONE
    void intersection(const string& inputFileName1, const string& inputFileName2, const string& outputFileName) const;			      //DONE
    void without(const string& inputFileName1, const string& inputFileName2, const string& outputFileName) const;				      //DONE
    void hitmiss(const string& inputFileName1, const string& inputFileName2, const string& outputFileName) const;				      //TODO
    void boundary(const string& inputFileName, const string& outputFileName) const;												      //TODO
                                                                                                                                      
	//operatorsGG                                                                                                                     
    void negate(const string& inputFileName, const string& outputFileName) const;												      //DONE
    void normalize(const string& inputFileName, const string& outputFileName) const;											      //DONE
    void multiply(const string& inputFileName, double aNumber, const string& outputFileName) const;								      //DONE
    void multiply(double aNumber, const string& inputFileName, const string& outputFileName) const;								      //DONE
    void multiply(const string& inputFileName1, const string& inputFileName2, const string& outputFileName) const;				      //DONE
    void crop(const string& inputFileName, double lowNumber, double upNumber, const string& outputFileName) const;				      //DONE
    void subtract(const string& inputFileName1, const string& inputFileName2, const string& outputFileName) const;				      //DONE
    void gradientINTERNAL(const string& inputFileName, const string& outputFileName) const;										      //DONE   
    void gradientEXTERNAL(const string& inputFileName, const string& outputFileName) const;										      //DONE
    void diferentialProfilesMORPHOLOGICAL(const string& inputFileName, const vector<double>& values, string& outputFileNamePartially) const; //DONE
    void diferentialProfilesATTRIBUTE(const string& inputFileName, const vector<double>& values, string& outputFileNamePartially) const;     //DONE
    void mappingDMP(const string& inputFileName, const vector<double>& values, string& outputFileNamePartially) const;					     //DONE 
    void mappingDAP(const string& inputFileName, const vector<double>& values, string& outputFileNamePartially) const;					     //DONE 
    void segmentationMSLS(const string& inputFileName, vector<double> values, const string& outputFileName) const;				      //TODO 
    void segmentationWATHERSHADE(const string& inputFileName, const string& outputFileName) const;								      //DONE 
    void segmentationWATHERSHADE(const string& inputFileName1, const string& inputFileName2, const string& outputFileName) const;     //DONE 
//  brisano pusti, ker še nisem zbrisal iz jezika...                                                                                  
//	void segmentationWATHERSHADE(double aNumber, string inputFileName, string outputFileName);						//BRIŠI           
                                                                                                                                      
	//operatorsBOX                                                                                                                    
    void erodeBOX(double aNumber, const string& inputFileName, const string& outputFileName) const;									  // DONE  
    void dilateBOX(double aNumber, const string& inputFileName, const string& outputFileName) const;   								  // DONE 
    void openBOX(double aNumber, const string& inputFileName, const string& outputFileName) const;      							  // DONE   
    void closeBOX(double aNumber, const string& inputFileName, const string& outputFileName) const;     							  // DONE

	//operatorsRECONSTRUCTION
    void erodeRECONSTRUCTION(const string& inputFileName1, const string& inputFileName2, const string& outputFileName) const; 		  //DONE
//	void erodeRECONSTRUCTION(double aNumber, string inputFileName, string outputFileName);  						                  //BRIŠI
    void dilateRECONSTRUCTION(const string& inputFileName1, const string& inputFileName2, const string& outputFileName) const; 	      //DONE
//	void dilateRECONSTRUCTION(double aNumber, string inputFileName, string outputFileName); 						                  //BRIŠI
    void openRECONSTRUCTION_BOX(double aNumber, const string& inputFileName, const string& outputFileName) const; 				      //DONE
    void closeRECONSTRUCTION_BOX(double aNumber, const string& inputFileName, const string& outputFileName) const; 				      //DONE
                                                                                                                                      
	//operatorsAREA                                                                                                                   
    void openAREA(double aNumber, const string& inputFileName, const string& outputFileName) const;								      // DONE
    void closeAREA(double aNumber, const string& inputFileName, const string& outputFileName) const;							      // DONE
                                                                                                                                      
	//operatorsATTRIBUTE                                                                                                              
    void open(string attributeName, double aNumber, const string& inputFileName, const string& outputFileName) const; 			      //TODO
    void close(string attributeName, double aNumber, const string& inputFileName, const string& outputFileName) const; 			      //TODO
                                                                                                                                      
	//operatorsBG                                                                                                                     
    void distanceTransform(const string& inputFileName, const string& outputFileName) const; 									      //TODO
                                                                                                                                      
	//operatorsGB                                                                                                                     
    void treshold(double aNumber, const string& inputFileName, const string& outputFileName) const;								      // DONE
};