//Max tree implementation
//Source:
//Fast Implementation of the Ultimate Opening
//By Jonathan Fabrizio and Beatriz Marcotegui
//http://cmm.ensmp.fr/~marcoteg/cv/publi_pdf/jonathan/fabrizio_marcotegui_ismm09_published.pdf

#ifndef MAX_TREE_H
#define MAX_TREE_H


#include <deque>
#include <vector>
#include "nVector.h"
#include "priority_queue.h"

using std::vector;
using std::deque;

struct attributes
{
	/*Init general attributes*/
	double area;
	double node_area;
	double height;
	double rHeight;
	nVector<int, 2> bbMin, bbMax;

	/*User defined attributes*/
	double attribute;
	double node_attribute;
	double parameter;
	double node_parameter;
	double linker;
	
	double attribute1; //število odbojev
	double attribute2; //bbox max dimension
	double attribute3; //diagonala
	double attribute4; //volumen
	double attribute5; // f_line
	double attribute6; // f_dot
	double attribute7; // Classification

	/*Statistical attributes*/
	double n;
	double avg;
	double m2;
	double std;

	//initial value of attributes
	attributes(): 
		bbMin(INT_MAX,INT_MAX), bbMax(INT_MIN,INT_MIN),
		area(0),
		height(0),
		rHeight(0),
		node_area(0),
		attribute(0),
		node_attribute(0),
		n(0),
		avg(0),
		m2(0),
		std(0),
		parameter(0),
		node_parameter(0),
		linker(0),
		attribute1(0),
		attribute2(0),
		attribute3(0),
		attribute4(0),
		attribute5(0),
		attribute6(0),
		attribute7(0)
	{}
};

struct node
{
	size_t brother;
	size_t child;
	size_t parent;

	double level;

	attributes atr;

	node(): brother(-1), child(-1), parent(-1), level(-1)
	{}
};


class max_tree
{
	struct stack_offload{
		int dir;
		nVector<int,2> pos;
		nVector<int,2> p_next;
		double p_val;

		stack_offload()
		{
			dir = 0;
			p_val = 0;
		}
	}; 

	vector<stack_offload> heap_stack;

	priority_queue queue;

	int next_label;

	vector<vector<double>> img;
	vector<vector<double>> transform, transform_associate;

	vector<double> transform_LUT;
	vector<double> associate_LUT;
	std::vector<int> labs_branch;


public:


	vector<vector<double>> lab_img;
	std::deque<node> nodes;

	static const int NO_CHILD = -1;

	max_tree(vector<vector<double>>& input) : img(input)
	{

		lab_img = vector<vector<double>>(img.size(), vector<double>(img[0].size(), -1));
		transform = vector<vector<double>>(img.size(), vector<double>(img[0].size(), -1));
		transform_associate = vector<vector<double>>(img.size(), vector<double>(img[0].size(), -1));
		next_label = 0;
	}

	nVector<int,2> find_start_point()
	{
		nVector<int,2> start(-1,-1);
		double min_value = INT_MAX;

		for (size_t y =  0; y < img.size(); y++)
		{
			for (size_t x = 0; x < img[0].size(); x++)
			{
				if (img[y][x] < min_value)
				{
					min_value = img[y][x];

					start.x = x;
					start.y = y;
				}
			}
		}	

		return start;
	}

	void build_tree(int noLevels)
	{	
		nVector<int,2> min_pt = find_start_point();	

		double level = img[min_pt.y][min_pt.x];
		
		//assure that the lowest pixel is zero
		{
			for (int y=0; y< img.size(); y++)
			{
				for (int x=0; x< img[0].size(); x++)
				{
					img[y][x] -= level;
				}
			}
		}

		level = img[min_pt.y][min_pt.x];

		//init queue
		{
			queue.add_entry( 
					queue_entry( min_pt.x, min_pt.y, level) 
				);
		}

		//init first node
		{
			double level = img[min_pt.y][min_pt.x];

			node beg;

			beg.level = level;

			//no children or brothers yet
			beg.brother = NO_CHILD;
			beg.child = NO_CHILD;
			beg.parent = NO_CHILD;

			//init any attributes
			beg.atr.area = 1;
			//beg.y_max = beg.y_min = level;

			nodes.push_back(beg);
		}

		//init labeled image
		lab_img[min_pt.y][min_pt.x] = 0;

		//init empty branch lookup table
		labs_branch = std::vector<int>(noLevels*10, 0);

		//reserve a bit of space
		//will generally resize a few times due to iteration depth
		heap_stack = std::vector<stack_offload>(noLevels);

		//parent node @ index 0 added, next_node will be stored as index 1
		next_label = 1;

		//recursively flood higher regions
		flood( queue.top_priority());


		//tree is stored in nodes deque!
	}

	void transform_bb()
	{

		transform_LUT = vector<double>(nodes.size(), -1);
		associate_LUT = vector<double>(nodes.size(), -1);

		ultimate_BB_opening(0, 0, 0, 0, 0, 0);

		for (size_t y =  0; y < img.size(); y++)
		{
			for (size_t x = 0; x < img[0].size(); x++)
			{
				transform[y][x] = transform_LUT[lab_img[y][x]];
				transform_associate[y][x] = associate_LUT[lab_img[y][x]];
			}
		}	

		

	}
	void transform_tree()
	{
		transform_LUT = vector<double>(nodes.size(), -1);
		associate_LUT = vector<double>(nodes.size(), -1);

		ultimate_opening(0, 0, -1, -1, -1, -1);

		for (size_t y =  0; y < img.size(); y++)
		{
			for (size_t x = 0; x < img[0].size(); x++)
			{
				transform[y][x] = transform_LUT[lab_img[y][x]];
				transform_associate[y][x] = associate_LUT[lab_img[y][x]];
			}
		}	
	}

	//Fakes recursion with a stack on heap and gotos.

	

	void flood(int level, int depth = 0)
	{
		#define HEAP_TOP heap_stack[depth]
		#define HEAP_PREVIOUS heap_stack[(depth!=0?(depth-1):0)]
	

		//init heap stack
		static int cnt =0;
		cnt++;

			
		
		heap_stack.clear();
		heap_stack.push_back(stack_offload());

		//fakes recursion start
		start_rec:
 		
		//4-connected flooding  
		/*const static nVector<int,2> offsets[]= {
									nVector<int,2>(0,-1), 
			nVector<int,2>(-1, 0),						   nVector<int,2>(1, 0),
									nVector<int,2>(0, 1)
		};*/

		
		//8-connected flooding
		const static nVector<int,2> offsets[]= {
			nVector<int,2>(-1,-1), nVector<int,2>(0,-1), nVector<int,2>(1,-1), 
			nVector<int,2>(-1, 0),	                      nVector<int,2>(1, 0),
			nVector<int,2>(-1, 1), nVector<int,2>(0, 1), nVector<int,2>(1,1)
		};


		//any items we can flood?
		while (queue.top_priority() >= HEAP_PREVIOUS.p_val)
		{
			
			HEAP_TOP.pos = queue.pop_entry().pos;
			HEAP_TOP.dir = 0;
			
			//for all neighboring pixels
			for (; HEAP_TOP.dir < sizeof(offsets)/sizeof(nVector<int,2>); HEAP_TOP.dir++)
			{
				
				const nVector<int,2> &pos = HEAP_TOP.pos;

				HEAP_TOP.p_next = pos + offsets[HEAP_TOP.dir];

				const nVector<int,2> &p_next = HEAP_TOP.p_next;

				    //assure coordinates still inside of image
				if (!(p_next.x >= 0 && p_next.x < img[0].size()
					&& p_next.y >= 0 && p_next.y < img.size())
					|| 
					//pixel must also be unprocessed/unlabeled
					lab_img[p_next.y][p_next.x] != -1
					)
					continue;
		
				const double p_val = img[pos.y ][pos.x ];
				HEAP_TOP.p_val = p_val;

				const double p_val_next = update_labels_and_attributes(pos, p_next, labs_branch);

				
				
				if (p_val_next > p_val)
				{
					//prepare next stack level
					heap_stack.push_back(stack_offload());
					++depth;
					//jump back to start of function
					goto start_rec;
					continue_rec:;

				}
					
			}
		}
		//we still have some work to do?
		if (depth > 0)
		{
			//return to previous stack level
			heap_stack.pop_back();
			--depth;
			//and jump back to where we left off
			goto continue_rec;
		}

	}



	double update_labels_and_attributes(const nVector<int,2> &pos,const nVector<int,2> &p_next, std::vector<int> &labs_branch ) 
	{
		
		double p_val	  = img[pos.y   ][pos.x   ];
		double p_val_next = img[p_next.y][p_next.x];

		double index = -1;

		double node_attribute = p_next.y; 

		//CASE A p_next is higher than p
		if ( p_val_next > p_val ) 
		{
			for (int i=p_val+1; i<p_val_next; i++)
				labs_branch[i] = 0;

			index = next_label_higher(p_val, p_val_next, labs_branch, node_attribute);
		}
		//CASE B p_next is lower than p
		else if (p_val_next < p_val && labs_branch[p_val_next] == 0 && p_val_next != 0) 
		{
			index = next_label_lower(p_val_next, labs_branch, node_attribute);
		}
		//CASE C
		else
		{
			index = labs_branch[p_val_next];
		}

		//update labeled image and branch lookup
		lab_img[p_next.y][p_next.x] = labs_branch[p_val_next] = index;

		//Update basic attributes
		{
			attributes& atr = nodes[index].atr;

			atr.bbMax.x = max(atr.bbMax.x, p_next.x);
			atr.bbMax.y = max(atr.bbMax.y, p_next.y);

			atr.bbMin.x = min(atr.bbMin.x, p_next.x);
			atr.bbMin.y = min(atr.bbMin.y, p_next.y);

			atr.area += 1;
		}

		//add pixel to queue
		queue.add_entry(queue_entry(p_next, p_val_next));

		return p_val_next;
	}

	void ultimate_opening( unsigned int node_id, double max_tr, double max_attribute, double parent_atribute , double parent_value, double previous_value)
	{
		node& current = nodes[node_id];

		double node_attribute = current.atr.area - current.atr.area;
		double node_contrast = (node_attribute == parent_atribute) ? ( current.level - previous_value ) : ( (current.level - parent_value ) );


		max_attribute = parent_atribute;

		if (node_contrast >= max_tr)
		{
			max_tr = node_contrast;
			max_attribute = node_attribute;
		}

		transform_LUT[node_id] = max_tr;
		associate_LUT[node_id] = max_attribute+1;


		unsigned int child = current.child;

		double pv = parent_value;

		if (node_attribute == parent_atribute)
		{
			pv = previous_value;
		}

		while (child != NO_CHILD)
		{
			ultimate_opening(child, max_tr, max_attribute, node_attribute, current.level, pv);
			child = nodes[child].brother;
		}
	}

	void ultimate_BB_opening( unsigned int node_id, double max_tr, double max_attribute, double parent_atribute , double parent_value, double previous_value)
	{
		node& current = nodes[node_id];
 
		nVector<int,2> bbSize = (current.atr.bbMax - current.atr.bbMin) + nVector<int,2>(1,1);
		double bb_size = bbSize.x * bbSize.y;

		double d1 = bb_size - parent_atribute;
		double d2 = bb_size - max_attribute;
		double node_contrast = (d2 < d1) ? ( current.level - previous_value ) : ( (current.level - parent_value ) );

		max_attribute = parent_atribute;

		if (node_contrast >= max_tr)
		{
			max_tr = node_contrast;
			max_attribute = bb_size;
		}

		transform_LUT[node_id] = max_tr;
		associate_LUT[node_id] = max_attribute+1;


		unsigned int child = current.child;

		double pv = parent_value;

		if (bb_size < parent_atribute)
		{
			pv = previous_value;
		}

		while (child != NO_CHILD)
		{
			ultimate_BB_opening(child, max_tr, max_attribute, bb_size, current.level, pv);
			child = nodes[child].brother;
		}
	}


	int next_label_higher( double parent_val, double value, const std::vector<int>& labs_branch, double p_y)
	{
		node current;

		size_t parent_idx = labs_branch[ parent_val ];
		node &parent = nodes[ parent_idx ];

		current.level = value;

		current.parent = parent_idx;

		current.brother = parent.child;

		current.child = NO_CHILD;

		parent.child = next_label;

		nodes.push_back(current);

		return next_label++;
	}


	int next_label_lower( double value,const std::vector<int>& labs_branch, double p_y)
	{
		node current;
		current.level = value;
		
		//find first appropriate parent
		int l = level_of_parent_of(value, labs_branch);

		size_t idx_parent = labs_branch[l];
		node &parent = nodes[ idx_parent ];

		size_t idx_old_son = parent.child ;
		node &old_son = nodes[ idx_old_son ];

		//insert node between existing nodes		
		current.child = parent.child;
		current.parent = 
		parent.child = next_label;
		

		current.parent = old_son.parent;
		old_son.parent = next_label;


		current.brother = NO_CHILD;


		//take the sons brothers 
		if (current.child != NO_CHILD)
		{
			std::swap(current.brother, nodes[current.child].brother);
		}


		//init attribute
		//current.y_max = current.y_min = p_y;

		//current.y_max = std::max(nodes[current.child].y_max, p_y);
 		//current.y_min = std::min(nodes[current.child].y_min, p_y);

		
		
		//add the node to the list of nodes
		nodes.push_back(current);

		return next_label++;
	}


	int level_of_parent_of( int value, const  std::vector<int>& labs_branch )
	{
		for (int i = value-1; i >= 0; i--)
		{
			if (labs_branch[i] != 0)
			{
				return i;
			}
		}
	
		return 0;
	}
};

#endif