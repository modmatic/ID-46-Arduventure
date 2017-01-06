#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "globals.h"
#include "player.h"
#include "text.h"

void stateMenuIntro()
{
  globalCounter++;
  sprites.drawSelfMasked(34, 4, T_arg, 0);
  if (globalCounter > 180) gameState = STATE_MENU_MAIN;
}

void stateMenuMain()
{
  if (!TIMSK4) ATM.play(titleSong);                                                   // IF NOT PLAYING A SONG, START NOW
  sprites.drawSelfMasked(36, 3, aTeamArgGame, 0);
  sprites.drawSelfMasked(10, 10, titleScreen, 0);
  drawWord(1, 40, 37, WHITE, ALIGN_LEFT);
  drawSentence(0, 40, 46, WHITE, ALIGN_LEFT);
  if (arduboy.audio.enabled()) drawSentence(2, 40, 55, WHITE, ALIGN_LEFT);            // SHOW SND ON
  else drawSentence(1, 40, 55, WHITE, ALIGN_LEFT);                                    // SHOW SND OFF
  sprites.drawSelfMasked( 32, 37 + (menuSelection - 2) * 9, font, 44);
  sprites.drawSelfMasked( 90, 37 + (menuSelection - 2) * 9, font, 45);

  if (arduboy.justPressed(UP_BUTTON) && (menuSelection > 2)) menuSelection--;
  else if (arduboy.justPressed(DOWN_BUTTON) && (menuSelection < 4)) menuSelection++;
  else if (arduboy.justPressed(B_BUTTON)) gameState = menuSelection;
}

void stateMenuContinue()
{
  ATM.stop();
  gameState = STATE_GAME_PLAYING;
}

void stateMenuNew()
{
  setPlayer();
  clearDynamicTextbox();
  gameState = STATE_GAME_NEW;
}

void stateMenuSound()
{
  // if sound is not enabled, put it ON, otherwise put it OFF
  if (!arduboy.audio.enabled()) arduboy.audio.on();
  else arduboy.audio.off();
  arduboy.audio.saveOnOff();
  gameState = STATE_MENU_MAIN;
}


#endif
