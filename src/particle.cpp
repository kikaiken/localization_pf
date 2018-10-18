#include"particle.hpp"

void Particle::set(double x,double y,double theta){
  Particle::x = x;
  Particle::y = y;
  Particle::theta = theta;
}
  
void Particle::likelihood(const std::list<Line>& lines){
  weight = 1.0;

}
