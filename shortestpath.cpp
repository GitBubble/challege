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

std::vector<point> transform(int n, int i)
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
    if ( n*n*n >= target ) 
	 break;
  }while(++n);

  n = (n-1)?(n-1):1;   
 
  auto residual = target - ((n*n*n) - (n-1)*(n-1)*(n-1)) ;
  auto k = residual / n;
  auto i = residual % n;
 
  auto cordinate = transform(n,i);

  k = k % 6;

  std::cout<< cordinate[k].x << "  " << cordinate[k].y << "  " << cordinate[k].z << std::endl;
  return cordinate[k];

}

static bool abs_(int a, int b)
{
  return (std::abs(a) < std::abs(b));
}

int main()
{
  unsigned int src,dest;
  std::cin >> src >> dest;
  //unsigned int src = 19;
  //unsigned int dest = 30; 
  std::cout<< src << " " <<dest<<std::endl;
  auto a = compute(src);
  auto b = compute(dest);
  //std::cout<< "shortest steps is : " << std::abs(a.x-b.x)+std::abs(a.y-b.y)+std::abs(a.z-b.z)-1 <<std::endl;
  std::cout << " shortest steps is : "<< std::max({std::abs(a.x-b.x),std::abs(a.y-b.y),std::abs(a.z-b.z)})
	      + std::min({std::abs(a.x-b.x),std::abs(a.y-b.y),std::abs(a.z-b.z)}) <<std::endl;
  return 0; 
}
