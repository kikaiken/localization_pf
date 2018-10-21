#ifndef PARTICLE_FILTER_INCLUDED
#define PARTICLE_FILTER_INCLUDED

#define _USE_MATH_DEFINES
#include "particle.hpp"
#include "line.hpp"
#include <vector>
#include <random>
#include <cmath>
#include <iostream>
#include <list>

class ParticleFilter{
  const static size_t PF_SIZE = 1000;/*粒子の数*/
  Particle particles[PF_SIZE];

  
  std::random_device rnd;
  /*これはコンパイルできなかった
  std::mt19937 mt = std::mt19937(rnd());
  
  std::uniform_real_distribution<double> rand0to1(0,1);
  std::uniform_real_distribution<double> randX(0, 99);
  std::uniform_real_distribution<double> randY(0, 99);
  std::uniform_real_distribution<double> randRad(0, 2*M_PI);
  */
  
public:
  ParticleFilter(const std::list<Line>& lines);

  void predictPos(const std::list<Line>& lines,Particle& resultParticle);
  
private:
  /*はじめにparticleをばらまく*/
  void initialize(const std::list<Line>& lines);

  /*particleを更新する*/
  void resample();

  /*ランダムなparticleを作成*/
  void randomPos(double* x, double* y,double* rad);

  /*particlesを動かす*/
  void predict();

  /*重みつき平均で位置を返す*/
  void measure(Particle& resultParticle);

  /*直線郡をもとに重みを計算*/
  void weight(const std::list<Line>& lines);
};

#endif
