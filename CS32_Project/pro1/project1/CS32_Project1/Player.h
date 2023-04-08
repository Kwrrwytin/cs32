//
//  Player.h
//  CS32_project1
//
//  Created by wy24iiiiiii on 2022/6/27.
//
#include<string>
#ifndef Player_h
#define Player_h

#include "globals.h"
class Arena;
class Player
{
  public:
        // Constructor
    Player(Arena *ap, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;

        // Mutators
    std::string takeComputerChosenTurn();
    void   stand();
    void   move(int dir);
    bool   shoot(int dir);
    void   setDead();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_age;
    bool   m_dead;

    int    computeDanger(int r, int c) const;
};
#endif /* Player_h */
