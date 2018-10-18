#include"particleFilter.hpp"


ParticleFilter::ParticleFilter(const std::list<Line>& lines){
  initialize(lines);
}


void ParticleFilter::initialize(const std::list<Line>& lines){
  double x,y,rad;
  for(int i=0;i<PF_SIZE;i++){
    randomPos(&x,&y,&rad);
    particles[i].set(x,y,rad);
    particles[i].likelihood(lines);
  }
}

void ParticleFilter::resample(){
  std::vector<double> weights(PF_SIZE);//累積重み
  weights[0] = particles[0].weight;
  for(int i=1;i<PF_SIZE;i++){
    weights[i] = weights[i-1] + particles[i].weight;
  }

  //resampling
  static std::random_device rnd;
  static std::mt19937 mt = std::mt19937(rnd());
  static std::uniform_real_distribution<double> rand0to1(0,1);

  Particle tmpParticles[PF_SIZE];
  for(int i=0;i<PF_SIZE;i++){
    tmpParticles[i] = particles[i];
  }
  
  for(int i=0;i<PF_SIZE;i++){
    const double weight2 = rand0to1(mt)*(*weights.end());
    int n=0;
    while(weights[n]<weight2){
      n++;
    }
    particles[i] = tmpParticles[n];
    particles[i].weight = 1.0;
  }
}



void ParticleFilter::randomPos(double* x,double* y,double* rad){
  static std::mt19937 mt = std::mt19937(rnd());
  static std::uniform_real_distribution<double> randX(0, 99);
  static std::uniform_real_distribution<double> randY(0, 99);
  static std::uniform_real_distribution<double> randRad(0,2*M_PI);

  *x = randX(mt);
  *y = randY(mt);
  *rad = randRad(mt);
}

void ParticleFilter::predict(){
  const static double VARIANCE_XY = 13;/*あとで調整*/
  const static double VARIANCE_THETA = 6/M_PI;
  std::normal_distribution<> gaussDis(0.0,1.0);
  static std::mt19937 mt = std::mt19937(rnd());
  
  for(int i=0;i<PF_SIZE;i++){
    particles[i].x += gaussDis(mt)*VARIANCE_XY;
    particles[i].y += gaussDis(mt)*VARIANCE_XY;
    particles[i].theta += gaussDis(mt)*VARIANCE_THETA;
  }
}

void ParticleFilter::weight(const std::list<Line>& lines){
  double sumWeight = 0;
  //calculate weight of particles
  for(int i=0;i<PF_SIZE;i++){
    particles[i].likelihood(lines);
    sumWeight += particles[i].weight;
  }

  //正規化
  for(int i=0;i<PF_SIZE;i++){
    particles[i].weight = particles[i].weight/sumWeight;
  }
}


void ParticleFilter::measure(Particle& resultParticle){
  double x = 0,y = 0,theta = 0,weight = 0;

  for(int i=0;i<PF_SIZE;i++){
    x += particles[i].x * particles[i].weight;
    y += particles[i].y * particles[i].weight;
    theta += particles[i].theta * particles[i].weight;
    weight += particles[i].weight;
  }

  resultParticle.set(x/weight,y/weight,theta/weight);
}

void ParticleFilter::predictPos(const std::list<Line>& lines,Particle& resultParticle){
  resample();
  predict();
  weight(lines);
  measure(resultParticle);
}
