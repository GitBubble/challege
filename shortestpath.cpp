// n^3 - (n-1)^3 + k*n + i  ( k[0,5], i[1,6] )

#include <iostream>
#include <algorithm>
#include <vector>
#include <initializer_list>

typedef struct point_t
{
	int x;
	int y;
	int z;
}point;

typedef enum plane_t
{
   xy=0,
   yz=1,
   zx=2,
   diagx=3,
   diagy=4,
   diagz=5
}plane;

auto transform(int n, int i)
{
   //assert(n>i); 
   std::vector<point> m;
   m= { {n, i, 0}, {n-i, n ,0}, {0,n,i}, {0,n-i,n}, {i,0,n}, {n,0,n-i} };
   return m;
}

auto compute(int target)
{
  auto n = 1;
  do 
  {
    if ( target <= ((n*n*n) - (n-1)*(n-1)*(n-1)) ) 
	 break;
  }while(++n);

  n = (n-1)?(n-1):1;   

  auto residual = target - ((n*n*n) - (n-1)*(n-1)*(n-1)) ;

  auto k = residual / n;
  auto i = residual % n;

  if(target==1) { n = 0; i = 0; }

  auto cordinate = transform(n,i);

  k = k % 6;

  std::cout<< cordinate[k].x << "  " << cordinate[k].y << "  " << cordinate[k].z << std::endl;
  return cordinate[k];

}

auto determine_plane(point& pt)
{
    if( !pt.x && !pt.y )    return diagz;
    if( !pt.y && !pt.z )    return diagx;
    if( !pt.z && !pt.x)    return diagy;
    if( !pt.z && pt.x && pt.y ) return xy;
    if( !pt.x && pt.y && pt.z ) return yz;
    if( !pt.y && pt.z && pt.x ) return zx;
}

auto determin(point& a, point& b)
{
   auto a_pos = determine_plane(a);
   auto b_pos = determine_plane(b);
   
   if( (  a_pos == xy ) && ( b_pos == diagz || b_pos == zx ) )
   {
      b.y = -b.z; 
      b.z = 0;    
   }
   else if( ( b_pos == xy ) && ( a_pos == diagz || a_pos == zx ) )
   {
      a.y = -a.z;
      a.z = 0;     
   }
   else if( ( a_pos == diagx || a_pos == xy ) && ( b_pos == diagz || b_pos == yz ) )
   {
      b.x = -b.z;
      b.z = 0;     
   }
   else if( ( b_pos == diagx || b_pos == xy ) && ( a_pos == diagz || a_pos == yz ) )
   {
      a.x = -a.z;
      b.z = 0;    
   }
   else if( ( a_pos == diagy || a_pos == yz ) && ( b_pos == diagx || b_pos == zx ) )
   {

      b.y = -b.x; 
      b.x = 0;    
   }
   else if( ( b_pos == diagy || b_pos == yz ) && ( a_pos == diagx || a_pos == zx ) )
   {
     

      a.y = -a.x;
      a.x = 0;     
   }
   else if(a_pos == diagz && b_pos == diagy)
   {
      a.y = -a.z;
   }
   else if(b_pos == diagz && a_pos == diagy)
   {
      b.y = -b.z;
   }

   return std::max({std::abs(a.x-b.x),std::abs(a.y-b.y),std::abs(a.z-b.z)}) ; 
}

void test(unsigned int src, unsigned int dest, unsigned int expected)
{

  auto a = compute(src);
  auto b = compute(dest);
  auto result = determin(a,b);
  std::cout<< src << "-->" << dest<< ",shortest step is : " << result 
      <<" expected: "<< expected << ".result: "<< ((result == expected)?("TRUE"):("FALSE")) << std::endl;
}
int main()
{
   test(1,19,2);
   test(1,22,3);
   test(19,18,1);
   test(5,11,3);
   test(20,13,5);
   test(13,20,5);
   test(17,9,4);
   test(11,18,4);
   test(12,16,3);
   return 0; 
}
