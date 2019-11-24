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
	Vector2d P0, P1, P2, P3;
	Vector2d p;
	vector<double> x1_list, y1_list;
	double th,t;
  public:
	Bezier() {
	  P0 << 0.0, 0.0; P1 <<  0.0, 0.06; P2 <<  0.4, 0.06; P3 << 0.2, 0.0;
	}
	void analyze();
};

void Bezier::analyze()
{
  for( int degree=0; degree<=90; degree++ ) {
	th = deg2rad( degree );
	t  = sin( th );

	p <<  (1-t)*(1-t)*(1-t)*P0(0) + 3*(1-t)*(1-t)*t*P1(0) + 3*(1-t)*t*t*P2(0) + t*t*t*P3(0),
	      (1-t)*(1-t)*(1-t)*P0(1) + 3*(1-t)*(1-t)*t*P1(1) + 3*(1-t)*t*t*P2(1) + t*t*t*P3(1);

	cout << "p_x = " << p(0) << endl;
	cout << "p_y = " << p(1) << endl;
	x1_list.push_back( p(0) );
	y1_list.push_back( p(1) );
  }
  plt::plot( x1_list, y1_list );

}

int main( int argc, char *argv[] )
{
  Bezier bezier;
  bezier.analyze();
  plt::xlim( -0.1, 0.3);
  plt::ylim( -0.1, 0.1);
  plt::show();

  return 0;
}
