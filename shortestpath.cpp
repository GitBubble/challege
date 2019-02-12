#include <cmath>
#include <iostream>

static unsigned int g_maxvalue = 100000;   
static unsigned int passed = 0;
static unsigned int failed = 0; 
 
void transform(int seq_num,int *x,int *y,int *z)
{
	int cycle_num = 0;   
	int current_seq_num =1;  
 

	while(current_seq_num < seq_num)
	{
		cycle_num++;
		current_seq_num = current_seq_num + cycle_num * 6; 
	}
 
	if(cycle_num == 0)
	{
		*x = 0;
		*y = 0;
		*z = 0;
		return ;
	}
 
	int side_num = (current_seq_num - seq_num) / cycle_num + 1;
 
	int side_pos = (current_seq_num - seq_num) % cycle_num;
	
	switch(side_num)
	{
	case 1:
		*x = cycle_num;
		*y = -cycle_num + side_pos;
		*z = side_pos;
		break;
	case 2:
		*x = cycle_num - side_pos;
		*y = side_pos;
		*z = cycle_num;
		break;
	case 3:
		*x = -side_pos;
		*y = cycle_num; 
		*z = cycle_num - side_pos;
		break;
	case 4:
		*x = -cycle_num;
		*y = cycle_num - side_pos;
		*z = - side_pos;
		break;
	case 5:
		*x = -cycle_num + side_pos;
		*y = -side_pos;
		*z = -cycle_num;
		break;
	case 6:
		*x = side_pos;
		*y = -cycle_num;
		*z = -cycle_num + side_pos;
		break;
	}
}

int determin(int iFirstValue, int iSecondValue)
{
	if(iFirstValue > g_maxvalue || iFirstValue < 1 || iSecondValue > g_maxvalue || iSecondValue < 1)
	{
		return -1;
	}
 
	int x_1 = 0;
	int y_1 = 0;
	int z_1 = 0;
	int x_2 = 0;
	int y_2 = 0;
	int z_2 = 0;
	transform(iFirstValue,&x_1,&y_1,&z_1);  
	transform(iSecondValue,&x_2,&y_2,&z_2);
 
	int distance_x = (x_1 > x_2)? (x_1 - x_2):(x_2 - x_1);
	int distance_y = (y_1 > y_2)? (y_1 - y_2):(y_2 - y_1);
	int distance_z = (z_1 > z_2)? (z_1 - z_2):(z_2 - z_1);
 
	int shortest_distance = distance_x > distance_y? distance_x:distance_y;
	shortest_distance = shortest_distance > distance_z? shortest_distance:distance_z;
 
	return shortest_distance;
}
 
void test(unsigned int src, unsigned int dest, unsigned int expected)
{
  
  auto result = determin(src,dest);
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
   std::cout<<std::endl;
    int a,b;   
    while(1)
   {
        std::cin >>a;
        std::cin >>b;
        test(a,b,0);
      
   }

   std::cout<< "\ntest cases total: "<< passed + failed << std::endl;
   std::cout <<std::endl<<"\033[1;32m"<<passed << " cases passed!"<<"\033[1;31m\n"<<failed << " cases failed!\033[0m "<<std::endl;
   return 0; 
}
