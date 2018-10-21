#ifndef MAP_INCLUDED
#define MAP_INCLUDED

#include<vector>
#include<list>
#include<algorithm>
#include"line.hpp"
#include"particle.hpp"


class Map{
  /*マップの直線の傾き*/
  std::vector<double> map = {M_PI/2,0,M_PI/2};

public:
  void matching(const Particle& position,const std::list<Line>& lines,std::vector<int>& label);

};

#endif
