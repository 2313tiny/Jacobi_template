#include<cassert>
#include<limits>  //for numeric_limits
#include<cstddef> //size_type
#include<fstream>
#include<iostream> 
#include<iomanip> //for setw()

//typedef float value_type;

template<typename value_type, typename size_type>
class Matrix
{
    private:
	size_type mColCount;
	size_type mRowCount;
	value_type * mData;
	
    public:
	void initialize( const size_type r, const size_type c )
	{
		mRowCount = r;
		mColCount = c;
		mData = new value_type[r*c];
	}

	void setvalue( const size_type i, const size_type j,const  value_type  e)
	{
		mData[i* mColCount + j] = e;
	}
	
	value_type & getvalue( const size_type i , const size_type j) const
	{
		return mData[ i * mColCount + j ];
	}

	size_type getCol() const
	{
		return mColCount;
	}

	size_type getRow() const
	{
		return mRowCount;
	}
};

template<typename value_type, typename size_type>
void readMatrix(Matrix<value_type, size_type> & matrix, std::ifstream & like_pipe )
	{
	assert( like_pipe.is_open() );
	size_type r= std::numeric_limits<size_type>::max();
	like_pipe >> r;
	assert(r < std::numeric_limits<value_type>::max() );
	assert(r > 0);
	assert( like_pipe.is_open() );
	size_type c = std::numeric_limits<size_type>::max();
	like_pipe >> c;
	assert(c < std::numeric_limits<value_type>::max() );
	assert(c > 0);
	value_type x = std::numeric_limits<value_type>::max();
	matrix.initialize(r,c);
//	value_type y = sizeof(matrix)/sizeof(matrix.getvalue(0,0));//under construction
	//r = y * matrix.getCol();
	//std::cout << y << std::endl;
	//c = 
	for( size_type i = 0; i < r; ++i)
	{
		for( size_type j=0; j< c; ++j)
		{
			like_pipe>> x; //OK version
			//like_pipe.get();
	//		std::cout << x << " ";
			assert( x < std::numeric_limits<value_type>::max());
			matrix.setvalue(i,j,x);
		}//end for(j;j;j)
			std::cout << std::endl;
	}//end for(i;i;i)
}


template<typename value_type>
value_type myRound( value_type var)
{
	value_type value = (int)(var * 10000);
	return (value_type)value/10000;
}

template<typename value_type, typename size_type>
void writeMatrix(const Matrix<value_type, size_type> & matrix , std::ofstream & like_pipe)
{
	assert(like_pipe.good());
	like_pipe<< matrix.getRow() << " ";
	assert(like_pipe.good());
	like_pipe<< matrix.getCol() << std::endl;

	for(size_type i = 0; i < matrix.getRow(); ++i)
	{
		for( size_type j = 0; j< matrix.getCol(); ++j)
		{
			like_pipe<< matrix.getvalue(i,j); //OK version
		//	like_pipe.put( matrix.getvalue(i,j));	
		}//end for(j;j;j)
		like_pipe << std::endl;
	}//end for(i;i;i)	
}

template<typename value_type, typename size_type>
void jacobiMethod(const Matrix<value_type,size_type> & a,
		  const Matrix<value_type,size_type> & b,
			Matrix<value_type,size_type> & x)
{
	size_type single_col= 0;
	x.initialize(a.getRow(), b.getCol()); //first iteration x(0,0,...0)
	for ( size_type i = 0; i<a.getRow(); ++i){
		x.setvalue(i,single_col,0);
	}//end for(i;i;i)
	size_type count = 0;
	while( count < 50){
	for ( size_type i= 0; i< a.getRow(); ++i){ //finding solution
		value_type sum = 0;
		value_type e = 0;
		assert( e < std::numeric_limits<value_type>::max());	
		for( size_type j =0; j< a.getCol(); ++j){
		 	if( i != j){
				sum += x.getvalue(i,single_col) * a.getvalue(i,j);
			//	assert( sum < std::numeric_limits<value_type>::max());
			}//end if
		}//end for(j;j;j
				e = b.getvalue(i,single_col) - sum;
				e =e/a.getvalue(i,i); //
				e = myRound(e); //under construction
				x.setvalue(i, single_col, e);
			// 	e =-1/a.getvalue(i,i)* (sum - b.getvalue(i,single_col));
			//	e =e/a.getvalue(i,i); //
			//	x.setvalue(i, single_col, e);
			
		}//end for(i;i;i)
	 count++;
	}//end while

}

int main()
{	
	Matrix<float, std::size_t> a;
	Matrix<float, std::size_t> b;
	Matrix<float, std::size_t> x;
	std::ifstream A("A.txt"), B("B.txt");
	std::ofstream X("x.txt");
	readMatrix(a,A); 
	readMatrix(b,B);
	x.initialize(a.getRow(), b.getCol());
	jacobiMethod(a, b, x);
	writeMatrix(x, X);
	return 0;
}
