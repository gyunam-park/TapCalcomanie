#ifndef __CONSTANTS_HPP__
#define __CONSTANTS_HPP__

/* SCREEN */
#define PORTRAIT_WIDTH      540
#define PORTRAIT_HEIGHT     960

/* DIFFICULTY */
enum class GAME_DIFFICULTY {
    EASY = 0,
    MEDIUM,
    HARD
};

#define EASY_MIN            3
#define EASY_MAX            7
#define MEDIUM_MIN          7
#define MEDIUM_MAX          14
#define HARD_MIN            9
#define HARD_MAX            18

#define EASY_STAMP_TIME     0.45f
#define MEDIUM_STAMP_TIME   0.4f
#define HARD_STAMP_TIME     0.375f

/* CANVAS */
#define CANVAS_SIZE         128

/* COLOR */
#define DISABLE_COLOR_4B    Color4B(0,0,0,0)
#define DISABLE_COLOR_4F    Color4F(0.0f,0.0f,0.0f,0.0f)

#define BLACK_COLOR_4B      Color4B(50,50,50,255)
#define BLACK_COLOR_3B      Color3B(50,50,50)

#define WHITE_COLOR_4B      Color4B(245,245,245,255)
#define WHITE_COLOR_3B      Color3B(245,245,245)

#define EASY_COLOR          Color4B(249,214,46,255)
#define MEDIUM_COLOR        Color4B(252,145,58, 255)
#define HARD_COLOR          Color4B(255,78,80, 255)

#endif