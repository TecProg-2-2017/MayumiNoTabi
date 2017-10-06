/*!
 *  File: main.cpp
 *
 *  Description: Main game file 
 */ 

#include <common.hpp>

#include <game.hpp>
#include <stateTitle.hpp>

Game game(NOMEPROJETO,1024,768);

/*!
 *  @fn int main() 
 *  @brief Main function of the game 
 *  @return integer 
 */
int main() {
	GAMEINST.Push(new StateTitle);
	GAMEINST.Run();
	return 0;
}

