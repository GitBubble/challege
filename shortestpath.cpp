// n^3 - (n-1)^3 + k*n + i  ( k[0,5], i[1,6] )

#include <iostream>
#include <algorithm>
#include <vector>
#include <initializer_list>

static unsigned int passed = 0;
static unsigned int failed = 0;

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
   auto discend = 0;
   auto offsetx = (a.x-b.x)?(a.x-b.x):(1);
   auto offsety = (a.y-b.y)?(a.y-b.y):(1);
   auto offsetz = (a.z-b.z)?(a.z-b.z):(1);
   
   if( (a_pos == b_pos)&& (offsetx*offsety*offsetz < 0))
   {
      return std::abs(a.x-b.x)+std::abs(a.y-b.y)+std::abs(a.z-b.z);
   }
   else
   {
      if( (  a_pos == xy ) && ( b_pos == diagz || b_pos == zx ) )
      {
         discend += b.z;
         b.z = 0;    
      }
      else if( ( b_pos == xy ) && ( a_pos == diagz || a_pos == zx ) )
      {
         discend += a.z;
         a.z = 0;     
      }// scenaro-1:  a(xy) -- b(z, zx) 
      if( (  a_pos == xy ) && ( b_pos == diagz || b_pos == yz ) )
      {
         discend += b.z;
         b.z = 0;    
      }
      else if( ( b_pos == xy ) && ( a_pos == diagz || a_pos == yz ) )
      {
         discend += a.z;
         a.z = 0;     
      }// scenaro-2:  a(xy) -- b(z,yz)
      else if( (a_pos == yz ) && ( b_pos == zx ) )
      {
         b.y = -b.x; 
         b.x = 0;    
      }
      else if( ( b_pos == yz ) && ( a_pos == zx ) )
      {
         a.y = -a.x;
         a.x = 0;     
      }
      else if(a_pos == diagz && b_pos == diagy)
      {
         a.y = -a.z;
         a.z = 0;
      }
      else if(b_pos == diagz && a_pos == diagy)
      {
         b.y = -b.z;
         b.z = 0;
      }

      return std::max({std::abs(a.x-b.x),std::abs(a.y-b.y),std::abs(a.z-b.z)}) + discend ; 
   }
}

void test(unsigned int src, unsigned int dest, unsigned int expected)
{
  auto a = compute(src);
  auto b = compute(dest);
  auto result = determin(a,b);
  std::cout<< src << "-->" << dest<< ",shortest step is : " << result 
      <<" expected: "<< expected << ".result: "<< ((result == expected)?("TRUE"):("FALSE")) << std::endl;
  (result == expected)?(++passed):(++failed);
}
int main()
{
   test(1,19,2);
   test(1,22,3);
   test(19,18,1);
   test(5,11,3);
   test(5,19,3);
   test(15,11,4);
   test(20,13,5);
   test(13,20,5);
   test(17,9,4);
   test(11,18,4);
   test(12,16,3);
   test(19,1,2);
   test(1,11,2);
   test(17,11,4);
   test(10000,2,57);
   test(22,14,5);
   test(14,22,5);
   test(15,9,4);
   test(1,10,2);
   test(37,19,1);
   test(34,11,5);
   test(20,32,5);
   test(20,16,4);
   test(14,20,5);
   test(15,20,5);
   test(21,16,4);
   test(32,18,3);
   test(30,12,3);
   test(20,10,3);
   test(11,15,4);
   test(30,12,3);
   test(49,13,2);
   test(43,64,4);
   test(80,43,8);
   test(28,5,3);
   test(26,30,4);
   // -45 degree
   test(62,9,4);
   // -45 degree
   test(62,22,4);
   test(56,46,7);
   test(54,26,6);
   test(52,18,5);
   test(88,26,8);
   test(86,26,8);
   test(82,26,7);
   test(19,26,5);
   std::cout<< "\ntest cases total: "<< passed + failed << std::endl;
   std::cout <<std::endl<<"\033[1;32m"<<passed << " cases passed!"<<"\033[1;31m\n"<<failed << " cases failed!\033[0m "<<std::endl;
   return 0; 
}
