/*
*  File: componentHP.cpp
*
*  Description:  Implements componentHP class
*/

#include <componentHP.hpp>
#include <componentMemory.hpp>
#include <componentAI.hpp>
#include <gameObject.hpp>
#include <game.hpp>
#include <camera.hpp>

CompHP::CompHP(int tot,bool showHP,bool showDMG,float dmgCD)
   :total{tot},current{tot},showHP{showHP},showDMG{showDMG},cooldown{dmgCD}{}

CompHP::CompHP(int tot,int cur,bool showHP,bool showDMG,float dmgCD)
   :total{tot},current{cur},showHP{showHP},showDMG{showDMG},cooldown{dmgCD}{}

/*!
  * @fn CompHP::~CompHP()
  * @brief No params destructor method
  * @param No params
*/

CompHP::~CompHP() {
}

/*!
  * @fn CompHP::Damage(int damage)
  * @brief Updates the player HP value based on the damage inflicted, has current damage inflicted as param
  * @param int damage
*/

void CompHP::damage(int damage) {
	//! Verifies if current damage value bigger than the current value
	if(damageCoolDown.Get()>cooldown){
		damageCoolDown.Restart();
		current-=damage; //!< Decrements the value of the current life value according to the damage inflicted
		//! TODO: Renderizes damage value
		if(showDMG){
		}
    else {
      // Nothing to Do
    }

    //! Checks if element has 'memory' type and increases 'hit' value
    if(GO(entity)->HasComponent(Component::type::t_memory)) {
      COMPMEMORYp(GO(entity))->ints["hit"]++;
    }
    else {
    	// Nothing to Do
    }
	}
  else {
    // Nothing to Do
  }
}

/*!
  * @fn CompHP::update(float time)
  * @brief Updates HP value according to time param
  * @param float time
*/

void CompHP::update(float time) {
	//! Verifies if element is in the 'dead' state
	if(current <= 0) {
    GO(entity)->dead = true;
  }
  else {
    // Nothing to Do
  }
	dmgCoolDown.add_time(time);
}

/*!
  * @fn CompHP::~CompHP()
  * @brief Renders on screen the HP value
  * @param No params
*/

void CompHP::render() {
	//! Shows HP on screen if it's set player and bigget than zero
	//! TODO: Refactorate decision structures
	if(SETTINGS.showHP && showHP && current>0) {
		Rect box{0,-GO(entity)->Box().w/5.0f - GO(entity)->Box().w/10.0f,GO(entity)->Box().w,GO(entity)->Box().w/5.0f};
		box+=GO(entity)->Box().corner();

		box = box.renderBox();

		SDL_SetRenderDrawColor(GAMERENDER, 0, 0, 0, 255);
		SDL_Rect rect=box.sdlRect();
		SDL_RenderDrawRect(GAMERENDER,&rect);

		SDL_SetRenderDrawColor(GAMERENDER, 255, 0, 0, 255);
		rect.w *= current;
		rect.w /= total;
		rect.x ++;
		rect.y ++;
		rect.w -= 2;
		rect.h -= 2;
		SDL_RenderFillRect(GAMERENDER,&rect);
	}
  else {
    // Nothing to Do
  }
}

/*!
  * @fn Component::type CompHP::GetType()
  * @brief Returns if the component is if the 'HP' type
  * @param No params
*/

Component::type CompHP::get_type() const {
	return Component::type::t_hp;
}
