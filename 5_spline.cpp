/* 5次スプライン曲線
 *
 * グラフ(上)　位置
 * グラフ(中)　速度
 * グラフ(下)　加速度 
 */

#include <iostream>
#include <vector>

#include "../Eigen/Dense"
#include "../matplotlibcpp.h"

using namespace Eigen;
using namespace std;
namespace plt = matplotlibcpp;

int main( int argc, char *argv[] )
{
  double A = -0.0023;
  double B = 0.0509;
  double C =  -0.3056;
  double D = 0.5;
  double E = 1;
  double F = 2;
  float time = 0;
  vector<double> Spline, dt_Spline, dt_dt_Spline, time_list;

  for(  time=0; time<6; time+=0.1 ) {
	Spline.push_back( A*pow(time,5)+B*pow(time,4)+C*pow(time,3)+D*pow(time,2)+E*time+F );
	dt_Spline.push_back( 5*A*pow(time,4)+4*B*pow(time,3)+3*C*pow(time,2)+2*D*time+E );
	dt_dt_Spline.push_back( 20*A*pow(time,3)+12*B*pow(time,2)+6*C*time+2*D );
	time_list.push_back( time );
  }

  plt::subplot( 3, 1, 1 );
  plt::plot(time_list, Spline );
  plt::subplot( 3, 1, 2 );
  plt::plot(time_list, dt_Spline );
  plt::subplot( 3, 1, 3 );
  plt::plot(time_list, dt_dt_Spline );

  plt::show();

  return 0;
}
