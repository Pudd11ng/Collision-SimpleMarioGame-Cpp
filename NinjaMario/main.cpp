#include<iostream>
#include <graphics.h>
#include <conio.h>
#include <cstdlib>
#include "screen.hpp"
#include "block.hpp"
#include "coin.hpp"
#include "mario.hpp"
#include "spike.hpp"
#include "lifebar.hpp"
#include "object.hpp"
#define OBJECTCOUNT 27
using  namespace std;

 int main()
 {
  int screenWidth = getmaxwidth();
	int screenHeight = getmaxheight();

	initwindow(screenWidth, screenHeight);
  Object* objects[OBJECTCOUNT];
  Screen screen(0, 0, screenWidth, screenHeight, 0);
  screen.draw();

  readimagefile("menu.jpg", 0.2*screenWidth, 0.2*screenHeight, 0.8*screenWidth, 0.8* screenHeight);
  getch();
  setfillstyle(SOLID_FILL, BLACK);
  setcolor(BLACK);
  bar(0, 0,screenWidth,screenHeight);

  Mario mario(screenWidth/10, screenHeight-100, WHITE, 60, 10, 10 );
  mario.setImage();
   
  Block blocks[BLOCKMAX] = { Block(screenWidth/1.4, screenHeight-80 , 50, 80,  CYAN),
                             Block(550, screenHeight-160 , 700, 80,  CYAN),
                             Block(1000, screenHeight-350 , 400, 80,  CYAN),
                             Block(50, screenHeight-350 , 400, 80,  CYAN),
                             Block(300, screenHeight-540, 1000, 80,  CYAN)
                           };

  Spike spikes[SPIKEMAX] = { Spike(screenWidth/4, screenHeight-40, RED, 60, 40),
                             Spike(1050, screenHeight-200, RED, 60, 40),
                             Spike(1110, screenHeight-200, RED, 60, 40),
                             Spike(90, screenHeight-390, RED, 60, 40),
                             Spike(150, screenHeight-390, RED, 60, 40),
                             Spike(1300, screenHeight-390, RED, 60, 40),
                             Spike(1360, screenHeight-390, RED, 60, 40),
                             Spike(600, screenHeight-580, RED, 60, 40),
                             Spike(660, screenHeight-580, RED, 60, 40),
                             Spike(720, screenHeight-580, RED, 60, 40),
                           };
                              
  Lifebar lifebar(5 * screenWidth/8, screenHeight/20, LIGHTGRAY, 400, 25);
  Endpoint endpoint(screenWidth/1.2, screenHeight-90, BLACK, 60, 90);

  Coin coins[COINMAX] = { Coin(960, screenHeight-30, 25, YELLOW),
                          Coin(1040, screenHeight-30, 25, YELLOW),
                          Coin(600, screenHeight-190, 25, YELLOW),
                          Coin(680, screenHeight-190, 25, YELLOW),
                          Coin(1050, screenHeight-380, 25, YELLOW),
                          Coin(1130, screenHeight-380, 25, YELLOW),
                          Coin(1210, screenHeight-380, 25, YELLOW),
                          Coin(800, screenHeight-570, 25, YELLOW),
                          Coin(880, screenHeight-570, 25, YELLOW),
                          Coin(960, screenHeight-570, 25, YELLOW),
                        };

  Enemy enemys[ENEMYMAX] = { Enemy(1450, screenHeight-80, BLACK, 80, 80),
                             Enemy(1000, screenHeight-620, BLACK, 80, 80),
                           };

  int objectscount = 0;
  for (int i = 0; i < SPIKEMAX; i++)
    {
      objects[objectscount] = &spikes[i];
      mario.setSpike(&spikes[i]);
      objectscount++;
    }

  for (int i = 0; i < ENEMYMAX; i++)
    {
      objects[objectscount] = &enemys[i];
      mario.setEnemy(&enemys[i]);
      objectscount++;

    }

  for (int i = 0; i < BLOCKMAX; i++)
    {
      objects[objectscount] = &blocks[i];
      mario.setBlock(&blocks[i]);
      objectscount++;
    }

  for (int i = 0; i < COINMAX; i++)
    {
      objects[objectscount] = &coins[i];
      mario.setCoin(&coins[i]);
      objectscount++;
    }

  for (int i = 0; i < objectscount; i++)
  {
    objects[i]->draw();
  }

  endpoint.draw();
  mario.setEndpoint(&endpoint);

  mario.setLifebar(&lifebar);

  int key = 0;

  while (key != 27)
  {
    
    lifebar.draw();
    mario.undraw();
    if (kbhit())
    {
      key = mario.handleMario();
    }

    mario.update();
    mario.spikeCollision();
    mario.blockCollision();
    mario.coinCollision();
    mario.enemyCollision();
    mario.endpointCollision();

    mario.draw();

    delay(35);
  }

  return 0;
    
}