#include <iostream>
#include <vector>
#include "../Eigen/Dense"
#include "../matplotlibcpp.h"

using namespace std;
using namespace Eigen;
namespace plt = matplotlibcpp;

int main( int argc, char *argv[] )
{
  Vector2d pos1, pos2, pos3;
  Vector2d Pos;
  vector<double> x_list, y_list;

  pos1 << 1, 1;
  pos2 << 2, 5;
  pos3 << 4, 2;

  for( float t=0; t<=1; t+=0.01) {
	Pos << ( (1-t)*(1-t) )*pos1(0) + 2*t*(1-t)*pos2(0) + t*t*pos3(0),
		   ( (1-t)*(1-t) )*pos1(1) + 2*t*(1-t)*pos2(1) + t*t*pos3(1);
	
	x_list.push_back(Pos(0));
	y_list.push_back(Pos(1));
  }

  plt::plot( x_list, y_list );
  plt::xlim(0, 5 );
  plt::ylim( 0, 4);
  plt::show();

    
  return 0;
}
