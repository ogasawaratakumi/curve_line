#include <iostream>
#include <vector>

#include "../Eigen/Dense"
#include "../matplotlibcpp.h"

using namespace std;
using namespace Eigen;
namespace plt = matplotlibcpp;

class ViaPoint
{
  private:
	double t_via, t_fin;
	Vector3d q_ini, q_via, q_fin, q_vel;
	Vector3d a3, a4, a5, pi1, pi2;
	Matrix<double, 3, 1> q;
	Matrix<double, 5, 3> oga;
	Matrix<double, 5, 3> parameter;
	vector<double> x_list, z_list;
  public:
	ViaPoint( double t_via, double t_fin, Vector3d q_ini, Vector3d q_via, Vector3d q_fin, Vector3d q_vel );
	void set();
	void calculate();
};

ViaPoint::ViaPoint( double t_via, double t_fin, Vector3d q_ini, Vector3d q_via, Vector3d q_fin, Vector3d q_vel )
{
  this->t_via = t_via;
  this->t_fin = t_fin;
  this->q_ini = q_ini;
  this->q_via = q_via;
  this->q_fin = q_fin;
  this->q_vel = q_vel;
}

void ViaPoint::set()
{
  Matrix<double, 5, 5> A;

  oga << q_via(0)-q_ini(0), q_via(1)-q_ini(1), q_via(2)-q_ini(2),
	  q_fin(0)-q_ini(0), q_fin(1)-q_ini(1), q_fin(2)-q_ini(2),
	  q_vel(0), q_vel(1), q_vel(2),
	  0, 0, 0,
	  0, 0, 0;

  A << pow(t_via,3), pow(t_via,4), pow(t_via,5), 0, 0,
	pow(t_fin,3), pow(t_fin,3), pow(t_fin,3), (pow((t_fin-t_via),4))/24, (pow((t_fin-t_via),5))/120,
	3*pow(t_via,2), 4*pow(t_via,3), 5*pow(t_via,4), 0, 0,
	3*pow(t_fin,2), 4*pow(t_fin,3), 5*pow(t_fin,4), (pow((t_fin-t_via),3))/6, (pow((t_fin-t_via),4))/24,
	6*pow(t_fin,2), 12*pow(t_fin,3), 20*pow(t_fin,4), (pow((t_fin-t_via),2))/2, (pow((t_fin-t_via),3))/6;

  parameter = A.inverse()*oga;
  cout << parameter << endl;
  a3 = parameter.row(0); a4 = parameter.row(1); a5 = parameter.row(2);
  pi1 = parameter.row(3); pi2 = parameter.row(4);
}

void ViaPoint::calculate()
{
  for( double t_now=0; t_now<=t_fin; t_now+=0.01 ) {
	if( t_now>=0 && t_now<=t_via ) {
	  q << a5(0)*pow(t_now,5) + a4(0)*pow(t_now,4) + a3(0)*pow(t_now,3) + q_ini(0),
		0,
		a5(2)*pow(t_now,5) + a4(2)*pow(t_now,4) + a3(2)*pow(t_now,3) + q_ini(2);
	  x_list.push_back( q(0) );
	  z_list.push_back( q(2) );
	}
	else if( t_now>t_via && t_now<= t_fin ) {
	  q << a5(0)*pow(t_now,5) + a4(0)*pow(t_now,4) + a3(0)*pow(t_now,3) + q_ini(0) + (pi1(0)/24)*pow(t_now-t_via,4) + (pi2(0)/120)*pow(t_now-t_via,5),
		0,
		a5(2)*pow(t_now,5) + a4(2)*pow(t_now,4) + a3(2)*pow(t_now,3) + q_ini(2) + (pi1(2)/24)*pow(t_now-t_via,4) + (pi2(2)/120)*pow(t_now-t_via,5);
	  x_list.push_back( q(0) );
	  z_list.push_back( q(2) );
	}
  }
  plt::plot( x_list, z_list );
  plt::show();
}

int main()
{
  Vector3d q_ini, q_via, q_fin, q_vel;
  q_ini << 0, 0, 0; q_via << 1.5, 0, 1; q_fin << 0, 0, 0; q_vel << 2, 0, -3;
  //q_fin = q_ini;

  ViaPoint viapoint( 0.8, 1.5, q_ini, q_via, q_fin, q_vel );
  viapoint.set();
  viapoint.calculate();

  return 0;
}
