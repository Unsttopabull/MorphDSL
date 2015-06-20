#include <cmath>
#include <vector>

#ifdef FQDT_DEBUG
#include <fstream>
#endif


using namespace std;
class FQDT
{

public: 

	FQDT();

	void FastQuasiDistanceTransformation(const vector<vector<double>>& input, vector<vector<int>>& output, int maxSize);

private:
	enum dir
	{
	   top_left = 0,
	   top,
	   top_right,
	   right,
	   bottom_right,
	   bottom,
	   bottom_left,
	   left
	};
	
	int window_to;

	typedef double base_type;

	vector<vector<base_type>> lists_curr;
	vector<vector<base_type>> lists_prev;
	
	int lookup[4][8];
	
	int height;
	int width;

	int padding;
	
	static const int img_padding = INT_MAX;
	
	vector<double> img_1d;
	vector<double*> img;

	vector<base_type> eGradient;

	void init_data(const vector<vector<base_type>>& input);

	void link(vector<base_type*>& dat, vector<base_type>& dat_1d, int width);


void quasi_distance_transform(vector<vector<int>>& output);
void increment_lists(base_type* center, int next_item, int next_row ,int window_to, int lookup[8]);
void process_line(base_type* start, int increment, int w, int left ,int mid, int right);
void find_solution(int x, int y, vector<vector<int>> &output, vector<vector<base_type>>& lists_curr);

void correct_quasi_distance(vector<vector<int>>& output);

#ifdef FQDT_DEBUG

vector<double> data_1d;
vector<double*> data;

ofstream bench;
ofstream data_dump;

void load_image(std::string str = "image9.bmp");
void save_image(vector<vector<int>>& output, std::string img_file = "output.bmp");
void random_image();

void QuasiDistanceTransformationE(vector<vector<int>>& output, int maxSize);

void write_solution(int x, int y, ofstream& dat);
#endif


};


