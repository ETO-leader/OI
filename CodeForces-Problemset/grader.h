#include<string>

#if not defined(__GRADER_H)

#define __GRADER_H 1

extern void initPos(int r,int c);

extern std::string kingMove();

extern void queenMove(int r,int c);

extern void playChess();

#endif
