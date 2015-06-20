//The class here contains a n-dimensional template vector
#ifndef NVECTOR_H
#define NVECTOR_H


//#define NVECTOR_VARYING_DIMENSIONS


#define CONCATENATE(arg1, arg2)   arg1##arg2

#define STATIC_ASSERT(expression, message)\
  struct CONCATENATE(__static_assertion_at_line_, __LINE__)\
  {\
    implementation::StaticAssertion<static_cast<bool>((expression))> message;\
  };\
  typedef implementation::StaticAssertionTest<sizeof(CONCATENATE(__static_assertion_at_line_, __LINE__))> CONCATENATE( ___, __LINE__)

  // note that we wrap the non existing type inside a struct to avoid warning
  // messages about unused variables when static assertions are used at function
  // scope
  // the use of sizeof makes sure the assertion error is not ignored by SFINAE

namespace implementation {

  template <bool>
  struct StaticAssertion;

  template <>
  struct StaticAssertion<true>
  {
  }; // StaticAssertion<true>

  template<int i>
  struct StaticAssertionTest
  {
  }; // StaticAssertionTest<int>

} // namespace implementation


#include <cmath>

namespace nVector_aux
{
	//Generic N dimensional vector
	template <typename T>
	class nVector_implementation
	{
	protected:
		void multiply_with_scalar(T* lhs, T const & rhs, int N)
		{

			for ( int i = 0; i < N; i++ )
				lhs[i] *= rhs;

		}
		void divide_with_scalar(T* lhs, T const & rhs, int N)
		{
			for ( int i = 0; i < N; i++ )
				lhs[i] /= rhs;

		}

		T dot_product(T const * const lhs, T const * const rhs, int N) const
		{
			T acc = T();

			for ( int i = 0; i < N; i++ )
				acc += lhs[i]*rhs[i];

			return acc;
		}

		void add_vector(T * const lhs, T const * const rhs, int N) const
		{
			for ( int i = 0; i < N; i++ )
				lhs[i] += rhs[i];
		}

		void subtract_vector(T * const lhs, T const * const rhs, int N) const
		{
			for ( int i = 0; i < N; i++ )
				lhs[i] -= rhs[i];
		}


		void negate_vector(T * const lhs, int N) const
		{
			
			for ( int i = 0; i < N; i++ )
				lhs[i] = -lhs[i];
		}
	};


	template <typename T, unsigned int N>
	class nVector_base
	{
	public:

		T nField[N];

	};

	//Vector specilizations from 2 to 4 dimensions.
	//Enables access though x,y,z,w components
	template <typename T>
	class nVector_base<T, 2>
	{
	public:

		union{
			struct
			{
				T x,y;
			};

			T nField[2];
		};

		nVector_base() : x(0), y(0) {}

		nVector_base(const T& _x, const T& _y) : x(_x), y(_y) {}

	};

	template <typename T>
	class nVector_base<T, 3>
	{
	public:

		union{
			struct
			{
				T x, y, z;
			};

			T nField[3];
		};


		nVector_base() : x(0), y(1), z(0) {}
		nVector_base(const T& _x, const T& _y, const T& _z) : x(_x), y(_y), z(_z) {}
	};


	template <typename T>
	class nVector_base<T, 4>
	{
	public:

		union{
			struct
			{
				T x, y, z, w;
			};

			T nField[4];
		};

		nVector_base() {}
		nVector_base(const T& _x, const T& _y, const T& _z, const T& _w) : x(_x), y(_y), z(_z), w(_w) {}
	};

	template <unsigned int N, unsigned int M>
    struct min_size
	{
		enum { size = (N<M?N:M) };
	};

	template <unsigned int N, unsigned int M>
	struct max_size
	{
		enum { size = (N>M?N:M) };
	};

	template<unsigned int N, unsigned int M>
	struct are
	{
		enum {same_size = (N==M)};
	};

	template <unsigned int N, unsigned int M, bool S = are<N,M>::same_size >
	struct check_if_nVector_mingling_enabled  
	{
		#ifndef NVECTOR_VARYING_DIMENSIONS
				//When S is equal 0 AND different dimension nVector mixing is dissalowed, this will stop compilation
				STATIC_ASSERT(S, ____using_different_dimensions_nVector_together_not_enabled);
		#endif
	};

}



template <typename T, unsigned int N, 
	      typename base = nVector_aux::nVector_base<T, N>, 
		  typename impl = nVector_aux::nVector_implementation<T> 
>
class nVector : public base, private impl
{
public:
	typedef nVector<T,N, base> type;
	typedef T type_value;

	
	enum { array_size = N };

//  ____                _                   _                 
// / ___|___  _ __  ___| |_ _ __ _   _  ___| |_ ___  _ __ ___ 
//| |   / _ \| '_ \/ __| __| '__| | | |/ __| __/ _ \| '__/ __|
//| |__| (_) | | | \__ \ |_| |  | |_| | (__| || (_) | |  \__ \
// \____\___/|_| |_|___/\__|_|   \__,_|\___|\__\___/|_|  |___/

	//constructors by value
    nVector() : base() {}
    nVector(const T& x, const T& y) : base(x, y) {}
    nVector(const T& x, const T& y, const T& z) : base(x, y, z) {}
    nVector(const T& x, const T& y, const T& z, const T& w) : base(x, y, z, w) {}
	

   //constructors from other types
   //different types, different sizes and different bases are all accepted
   template <typename T2, unsigned int M, typename base2>
   nVector(const nVector<T2, M, base2>& mVec)
   {
	   const unsigned int size = nVector_aux::min_size<N,M>::size;

	   //copy values and static cast them to our type them
	   for(unsigned int i=0; i < size; i++)
	   {
          this->nField[i] = static_cast<T>( mVec.nField[i] );
	   }

	   //if any remaining values remain, fill them with the default constructor for that type
	   for(unsigned int i = size; i < N; i++)
	   {
           this->nField[i] = T();
	   }

   }

   //get data from array
   nVector(T const (&data)[N])
   {
	   for(unsigned int i=0; i < N; i++)
	   {
           this->nField[i] = data[i];
	   }
   
   }

//     _            _                                  _       
//    / \   ___ ___(_) __ _ _ __  _ __ ___   ___ _ __ | |_ ___ 
//   / _ \ / __/ __| |/ _` | '_ \| '_ ` _ \ / _ \ '_ \| __/ __|
//  / ___ \\__ \__ \ | (_| | | | | | | | | |  __/ | | | |_\__ \
// /_/   \_\___/___/_|\__, |_| |_|_| |_| |_|\___|_| |_|\__|___/
//                    |___/                     

   
   //C++11 version
   //assignment operator from other nvector - using copy and swap idiom
   /*nVector& operator=(nVector&& rhs) //rhs -> moved or value copied nvector
   {
	   for(unsigned int i=0; i < N; i++)
	   {
		   this->nField[i] = rhs.nField[i];
	   }

	   return *this;
   }*/

   //C++03 version
   template <typename T2, unsigned int M, typename base2>
   type& operator=(const nVector<T2,M,base2&> rhs) //rhs - right hand side
   {

       const unsigned int size = nVector_aux::min_size<N,M>::size;
	   //copy values and cast them
	   for(unsigned int i=0; i < size; i++)
	   {
           base::nField[i] = static_cast<T>( rhs.nField[i] );

	   }

	   //if any remaining values remain, fill them with the default value for that type
	   for(unsigned int i= size; i < N; i++)
	   {
           base::nField[i] = T();
	   }
      
	   return *this;
   }
   

   //get data from array of size N
   template<class T2>
   nVector& operator=(const T2 (&data)[N])
   {
	   for(unsigned int i=0; i < N; i++)
	   {
           base::nField[i] = static_cast<T>( data[i] );
	   }

	   return *this;
   }



//  ___                       _                 
// / _ \ _ __   ___ _ __ __ _| |_ ___  _ __ ___ 
//| | | | '_ \ / _ \ '__/ _` | __/ _ \| '__/ __|
//| |_| | |_) |  __/ | | (_| | || (_) | |  \__ \
// \___/| .__/ \___|_|  \__,_|\__\___/|_|  |___/
//      |_|                                     
   const T& operator [] ( const unsigned int idx ) const
   {

      // assert( 0 <= idx && idx < N );	// assert in debug code
       return base::nField[ idx ];
   }

   T& operator [] ( const unsigned int idx )
   {

//       assert( 0 <= idx && idx < N );	// assert in debug code
       return base::nField[ idx ];
   }

   size_t size()
   {
	   return N;
   }

	//negation
	nVector operator - () const
	{
		nVector result(*this);

		negate_vector(result.nField, N);

        return result;
	}

	//add
	template <typename T2, unsigned int M, typename base2>
    nVector& operator+=(const nVector<T2, M, base2>& rhs) //rhs - right hand side
    {
		nVector_aux::check_if_nVector_mingling_enabled<N,M>();

		const unsigned int size = nVector_aux::min_size<N,M>::size;

		add_vector(this->nField, rhs.nField, size);

		return *this;
	}

    template <typename TT, unsigned int NN, unsigned int MM>
	struct return_type
	{
        typedef nVector<TT,nVector_aux::max_size<NN,MM>::size> return_typ;
	};
	
	template <unsigned int M, typename base2>
	nVector<T,nVector_aux::max_size<N,M>::size>  operator+(const nVector<T,M,base2>& rhs) const //rhs - right hand side
	{
		nVector_aux::check_if_nVector_mingling_enabled<N,M>();
		nVector<T,nVector_aux::max_size<N,M>::size> result(*this); //copy the class
		
		result += rhs; //add the rhs class

		return result; //return class
	}

	//subtrack
	template <unsigned int M, typename base2>
    nVector& operator-=(const nVector<T,M,base2>& rhs) //rhs - right hand side
    {
		nVector_aux::check_if_nVector_mingling_enabled<N,M>();
		const unsigned int size = nVector_aux::min_size<N,M>::size;

		subtract_vector(this->nField, rhs.nField, size);

		return *this;
	}

	template <unsigned int M, typename base2>
	nVector<T,nVector_aux::max_size<N,M>::size>  operator-(const nVector<T,M,base2>& rhs) const //rhs - right hand side
	{
		nVector_aux::check_if_nVector_mingling_enabled<N,M>();

		const unsigned int size = nVector_aux::max_size<N,M>::size;

		nVector<T,size> result(*this); //copy the class

		result -= rhs;

		return result;
	}

	
	//multiply by scalar
    nVector& operator*=(const T& rhs) //rhs - right hand side
    {
		multiply_with_scalar(this->nField, rhs, N);

		return (*this);
	}

    nVector operator*(const T& rhs) const//rhs - right hand side
    {
		nVector result(*this);
		
		result *= rhs;

		return result;
	}

	
	//divide by scalar
    nVector& operator/=(const T& rhs) //rhs - right hand side
    {
		divide_with_scalar(this->nField, rhs, N);

		return *this;
	}

    nVector operator/(const T& rhs) const//rhs - right hand side
    {
		nVector result(*this);
		
		result /= rhs;

		return result;
	}

	//dot product
	template <unsigned int M, typename base2>
	 T dot(const nVector<T,M,base2>& rhs) const //rhs - right hand side
	 {	
		 //if N != M mindling must be enabled (via define)!
		 nVector_aux::check_if_nVector_mingling_enabled<N,M>();
		 
		 //if N != M, get the smaller size
		 const unsigned int size = nVector_aux::min_size<N,M>::size;
		
		return dot_product(this->nField, rhs.nField, size);
	}

	T lenght_squared()
	{
	    return this->dot(*this);
	}

	double lenght() const
	{
		return std::sqrt( static_cast<double> (  this->dot(*this) ) );
	}

	type& normalize()
	{
		double len = this->lenght();

		(*this) /= len;

		return *this;
	}

	template <typename T2, int M>
	nVector<T2, M> convert_to()
	{

		return nVector<T2, M>(*this);
	}

	template <typename T2>
	nVector<T2, N> convert_to()
	{

		return nVector<T2, N>(*this);
	}
};



//  ____                                           _            _                           _ _ _          _   _             
// / ___|_ __ ___  ___ ___     _ __  _ __ ___   __| |_   _  ___| |_     ___ _ __   ___  ___(_) (_)______ _| |_(_) ___  _ __  
//| |   | '__/ _ \/ __/ __|   | '_ \| '__/ _ \ / _` | | | |/ __| __|   / __| '_ \ / _ \/ __| | | |_  / _` | __| |/ _ \| '_ \ 
//| |___| | | (_) \__ \__ \   | |_) | | | (_) | (_| | |_| | (__| |_    \__ \ |_) |  __/ (__| | | |/ / (_| | |_| | (_) | | | |
// \____|_|  \___/|___/___/   | .__/|_|  \___/ \__,_|\__,_|\___|\__|   |___/ .__/ \___|\___|_|_|_/___\__,_|\__|_|\___/|_| |_|
//                            |_|                                          |_|                                               

template <typename T>
nVector<T, 3> crossProduct(const nVector<T, 3>& lhs, const nVector<T, 3>& rhs)
{
	nVector<T, 3> result;
	result.x = static_cast<T>( lhs.y*rhs.z - lhs.z*rhs.y );
	result.y = static_cast<T>( lhs.z*rhs.x - lhs.x*rhs.z );
	result.z = static_cast<T>( lhs.x*rhs.y - lhs.y*rhs.x );

	return result;
}

//Enable scalar multiplication when on right side

template <typename T, unsigned int N>
nVector<T, N> operator*(typename nVector<T, N>::type_value const &left, nVector<T, N> const &right)
{
	nVector<T, N> result(right);
	result *= left;

	return result;
}




#endif
