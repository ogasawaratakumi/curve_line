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

class Bezier {
  private:
	Vector2d P0, P1, P2;
	Vector2d B1, B2, B12;
	Vector2d p0, p1, p2;
	Vector2d b1, b2, b12;
	Vector2d Bb12;
	vector<double> x1_list, y1_list, x2_list, y2_list, x3_list, y3_list;
	double th,t;
  public:
	Bezier() {
	  P0 << -1.0,  1.0; P1 <<  1.0, -1.0; P2 <<  1.0, -0.5;
	  p0 << -2.0, -0.5; p1 << -3.0, -1.5; p2 << -1.0, -3.0;
	}
	void analyze();
};

void Bezier::analyze()
{
  for( int degree=0; degree<=90; degree++ ) {
	th = deg2rad( degree );
	t  = sin( th );

	B1 << (1-t)*P0(0) + t*P1(0),
	  	  (1-t)*P0(1) + t*P1(1);

	B2 << (1-t)*P1(0) + t*P2(0),
	   	  (1-t)*P1(1) + t*P2(1);

	B12 << (1-t)*B1(0) + t*B2(0),
		   (1-t)*B1(1) + t*B2(1);

	b1 << (1-t)*p0(0) + t*p1(0),
	      (1-t)*p0(1) + t*p1(1);

	b2 << (1-t)*p0(0) + t*p2(0),
	      (1-t)*p0(1) + t*p2(1);

	b12 << (1-t)*b1(0) + t*b2(0),
		   (1-t)*b1(1) + t*b2(1);

	Bb12 << (1-t)*B12(0) + t*b12(0),
		    (1-t)*B12(1) + t*b12(1);

	x1_list.push_back( B12(0) );
	y1_list.push_back( B12(1) );
	x2_list.push_back( b12(0) );
	y2_list.push_back( b12(1) );
	x3_list.push_back( Bb12(0) );
	y3_list.push_back( Bb12(1) );
  }
  plt::plot( x1_list, y1_list );
  plt::plot( x2_list, y2_list );
  plt::plot( x3_list, y3_list );

}

int main( int argc, char *argv[] )
{
  Bezier bezier;
  bezier.analyze();
  plt::xlim( -1.5, 1.5 );
  plt::ylim( -1.5, 1.5 );
  plt::show();

  return 0;
}
