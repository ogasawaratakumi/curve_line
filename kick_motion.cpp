#include <iostream>
#include <cmath>
#include <vector>

#include "../Eigen/Dense"
#include "../matplotlibcpp.h"

using namespace std;
using namespace Eigen;
namespace plt = matplotlibcpp;

double deg2rad( double degree )
{
  return degree*M_PI/180.0f;
}

int main( int argc, char *argv[] ) 
{
  Vector2d p1, p2, p3;
  Vector2d P1, P2, P3;
  Vector2d p;
  Vector2d P;
  vector<double> x1_list, z1_list, x2_list, z2_list;
  vector<double> foot_up_x, foot_up_z;
  double th, t;
  double dt = 0.0;
  double step_time = 0.0;

  p1 << 0.0, 0.06; p2 << 0.07, -0.05; p3 << 0.14, 0.13;
  P1 << 0.14,0.13; P2 << 0.12, 0.04; P3 << 0.0, 0.03;

  for( int degree=0; degree<=90; degree++ ) {
	th = deg2rad( degree );
	t = sin( th );
	p << (1-t)*(1-t)*p1(0) + 2*(1-t)*t*p2(0) + t*t*p3(0),
	  (1-t)*(1-t)*p1(1) + 2*(1-t)*t*p2(1) + t*t*p3(1);

	P << (1-t)*(1-t)*P1(0) + 2*(1-t)*t*P2(0) + t*t*P3(0),
	  (1-t)*(1-t)*P1(1) + 2*(1-t)*t*P2(1) + t*t*P3(1);

	x1_list.push_back( p(0) );
	z1_list.push_back( p(1) );
	x2_list.push_back( P(0) );
	z2_list.push_back( P(1) );
//	std::cout << P(0) << std::endl;
  }

  for( float i=0; i<=0.06; i+= 0.001 ) {
	foot_up_z.push_back( i );
	foot_up_x.push_back( 0 );
  }

  plt::plot( x2_list, z2_list );
  plt::plot( x1_list, z1_list );
  plt::plot( foot_up_x, foot_up_z );
  plt::xlim(-0.01, 0.2);
  plt::ylim(-0.01, 0.2);
  plt::show();
}

