#include"map.hpp"

void Map::matching(const Particle& position,const std::list<Line>& lines,std::vector<int>& label){
  std::vector<double> tmp(map.size());/*傾きによる2乗誤差*/
  const double EPTHLON = (M_PI/18)*(M_PI/18);//あとで調整、10°とした
  int tmpLabel;
  bool flag = false;

  label.clear();
  for(auto i=lines.begin();i!=lines.end();i++){
    for(int j=0;j<map.size();j++){
      tmp[j] = ((position.theta + map[j]) - i->theta)*((position.theta + map[j]) - i->theta);      

      if(flag){ /*２辺目から*/
	if(tmp[j]<EPTHLON && j>=tmpLabel){
	  label.push_back(j);
	  tmpLabel = j;
	  break;
	}
      }else{
	if(tmp[j]<EPTHLON){/*1辺目*/
	  flag = true;
	  label.push_back(j);
	  tmpLabel = j;
	  break;
	}
      }
    }
    
  }
}
