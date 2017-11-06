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


/*!
	* @fn CompHP::HP(int tot, bool show_HP, bool show_damage, float damage_CD)
	* @brief Constructor Method for component HP
	* @param int tot, bool show_HP, bool show_damage, float damage_CD
*/

CompHP::CompHP(int total, bool show_HP, bool show_damage, float damage_CD)
   :total{total}, current{total}, show_HP{show_HP}, show_damage{show_damage}, cooldown{damage_CD} {
    LOG_METHOD_START('CompHP::CompHP');
   	LOG_VARIABLE("CompHP::CompHP", total, show_HP, show_damage, damage_CD);

   	assert(total >= 0);
    assert(show_HP >= 0);
    assert(show_damage) >= 0);
    assert(damage_CD >= 0);


   	LOG_METHOD_CLOSE('CompHP::CompHP', "constructor");
   }
/*!
	* @fn CompHP::CompHP(int tot,int cur,bool showHP,bool showDMG,float dmgCD)
 	* @brief Constructor Method for component HP
 	* @param int tot, bool show_HP, bool show_damage, float damage_CD
*/

CompHP::CompHP(int total, int current, bool show_HP,bool show_damage,float damage_CD)
   :total{total},current{current},show_HP{show_HP},show_damage{show_damage}, cooldown{damage_CD} {
     LOG_METHOD_START('CompHP::CompHP');
     LOG_VARIABLE("CompHP::CompHP", total, current, show_HP, show_damage, damage_CD);

     assert(total >= 0);
     assert(current >= 0);
     assert(show_HP >= 0);
     assert(show_damage) >= 0);
     assert(damage_CD >= 0);

     LOG_METHOD_CLOSE('CompHP::CompHP', "constructor");
   }

/*!
  * @fn CompHP::~CompHP()
  * @brief No params destructor method
  * @param No params
*/

CompHP::~CompHP() {
  LOG_METHOD_START('CompHP::~CompHP');

  LOG_METHOD_CLOSE('CompHP::~CompHP', "destructor");
}

/*!
  * @fn CompHP::Damage(int damage)
  * @brief Updates the player HP value based on the damage inflicted, has current damage inflicted as param
  * @param int damage
*/

void CompHP::damage(int damage) {
  LOG_METHOD_START('CompHP::damage');
  LOG_VARIABLE("CompHP::damage", damage);

  assert(damage >= 0);

	//! Verifies if current damage value bigger than the current value
	if(damageCoolDown.Get() > cooldown){
		damageCoolDown.Restart();
		current = current - damage; //!< Decrements the value of the current life value according to the damage inflicted
		//! TODO: Renderizes damage value
		if(show_damage){
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
  LOG_METHOD_CLOSE('CompHP::damage', "void");
}

/*!
  * @fn CompHP::update(float time)
  * @brief Updates HP value according to time param
  * @param float time
*/

void CompHP::update(float time) {
  LOG_METHOD_START('CompHP::update');
  LOG_VARIABLE("CompHP::update", "time");

  assert(time >= 0);

	//! Verifies if element is in the 'dead' state
	if(current <= 0) {
    GO(entity)->dead = true;
  }
  else {
    // Nothing to Do
  }
	dmgCoolDown.add_time(time);
  LOG_METHOD_CLOSE('CompHP::update', "void");
}

/*!
  * @fn CompHP::~CompHP()
  * @brief Renders on screen the HP value
  * @param No params
*/

void CompHP::render() {
  LOG_METHOD_START('CompHP::render');

	//! Shows HP on screen if it's set player and bigget than zero
	if(SETTINGS.showHP && showHP && current>0) {
		Rect box{0,-GO(entity)->Box().w/5.0f - GO(entity)->Box().w/10.0f,GO(entity)->Box().w,GO(entity)->Box().w/5.0f};
		box = box + GO(entity)->Box().corner();

		box = box.renderBox();

		SDL_SetRenderDrawColor(GAMERENDER, 0, 0, 0, 255);
		SDL_Rect rect = box.sdlRect();
		SDL_RenderDrawRect(GAMERENDER, &rect);

		SDL_SetRenderDrawColor(GAMERENDER, 255, 0, 0, 255);
		rect.w = rect.w * current;
		rect.w = rect.w / total;
		rect.x ++;
		rect.y ++;
		rect.w = rect.w - 2;
		rect.h = rect.h - 2;
		SDL_RenderFillRect(GAMERENDER, &rect);
	}
  else {
    // Nothing to Do
  }
  LOG_METHOD_CLOSE('CompHP::render', "void");
}

/*!
  * @fn Component::type CompHP::GetType()
  * @brief Returns if the component is if the 'HP' type
  * @param No params
*/

Component::type CompHP::get_type() const {
  LOG_METHOD_START('CompHP::get_type');

  LOG_METHOD_CLOSE('CompHP::get_type', t_hp.to_string());
	return Component::type::t_hp;
}
