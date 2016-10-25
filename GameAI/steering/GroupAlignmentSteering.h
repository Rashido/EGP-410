#ifndef GROUP_ALIGNMENT_STEERING
#define GROUP_ALIGNMENT_STEERING

#include "Steering.h"
#include <map>

/************************************************
					(                             
   (              )\ )                          
 ( )\ (   (  (   (()/(                       )  
 )((_))\  )\))(   /(_)) (   `  )   `  )   ( /(  
((_)_((_)((_))\  (_))   )\  /(/(   /(/(   )(_)) 
 | _ )(_) (()(_) | _ \ ((_)((_)_\ ((_)_\ ((_)_  
 | _ \| |/ _` |  |  _// _ \| '_ \)| '_ \)/ _` | 
 |___/|_|\__, |  |_|  \___/| .__/ | .__/ \__,_| 
         |___/             |_|    |_|           
***************************************************/

class KinematicUnit;

class GroupAlignmentSteering :public Steering
{
public:
	GroupAlignmentSteering(KinematicUnit* pMover, std::map<std::string, KinematicUnit*>* unitList);
	~GroupAlignmentSteering();

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;
	std::map<std::string, KinematicUnit*>* mpUnitList;
	
	Steering* mpAlignment;
	Steering* mpSeperation;
	Steering* mpCohesion;
};

#endif
