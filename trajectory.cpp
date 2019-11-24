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
	Vector2d pp0, pp1, pp2;
	Vector2d bb1, bb2, bb12;
	Vector2d Bb12;
	vector<double> x1_list, y1_list, x2_list, y2_list, x3_list, y3_list;
	vector<double> foot_up_x, foot_up_z;
	double th,t;
  public:
	Bezier() {
	  P0 << 0.0,  0.1; P1 <<  -0.05, 0.13; P2 <<  -0.1, 0.17;
	  p0 << -0.1, 0.17; p1 << 0.0, 0.09; p2 << 0.15, 0.05;
	  pp0 << 0.15, 0.05; pp1 << 0.1, 0.03; pp2 << 0.0, 0.1;
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

	bb1 << (1-t)*pp0(0) + t*pp1(0),
	      (1-t)*pp0(1) + t*pp1(1);

	bb2 << (1-t)*pp0(0) + t*pp2(0),
	      (1-t)*pp0(1) + t*pp2(1);

	bb12 << (1-t)*bb1(0) + t*bb2(0),
		   (1-t)*bb1(1) + t*bb2(1);

	Bb12 << (1-t)*B12(0) + t*b12(0),
		    (1-t)*B12(1) + t*b12(1);

	x1_list.push_back( B12(0) );
	y1_list.push_back( B12(1) );
	x2_list.push_back( b12(0) );
	y2_list.push_back( b12(1) );
	x3_list.push_back( bb12(0) );
	y3_list.push_back( bb12(1) );
	//cout << B12.transpose() << endl;
  }
  for( float i=0; i<=0.1; i+=0.01 ) {
	foot_up_z.push_back( i );
	foot_up_x.push_back( 0 );
  }
  plt::named_plot( "1. foot up", foot_up_x, foot_up_z );
  plt::named_plot( "2. back foot", x1_list, y1_list );
  plt::named_plot( "3. impact", x2_list, y2_list );
  plt::plot( x3_list, y3_list );
  plt::legend();

}

int main( int argc, char *argv[] )
{
  Bezier bezier;
  bezier.analyze();
  //plt::xlim(-2.5,5.0);
  plt::xlim( -0.25, 0.25 );
  plt::ylim( -0.25, 0.25 );
  //plt::ylim(-2.5,5.0);
  plt::show();

  return 0;
}
