//
//  Game.h
//  CS32_project1
//
//  Created by wy24iiiiiii on 2022/6/27.
//

#ifndef Game_h
#define Game_h
class Arena;
class Game
{
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nRobots);
    ~Game();

        // Mutators
    void play();

  private:
    Arena* m_arena;
};
#endif /* Game_h */
