#include "line.hpp"
#include<list>

class Particle{

public:
  double x,y,theta,weight;

  void set(double x,double y,double theta);

  void likelihood(const std::list<Line>& lines);
};
