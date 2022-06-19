#ifndef __DEFINE_H__
#define __DEFINE_H__

#define SCREEN_W			1280
#define SCREEN_H			950
#define SCREEN_CENTER_W		(1280/2)
#define SCREEN_CENTER_H		(950/2)
#define LIMIT_FPS			60
#define SPF					0.05
#define MaxParticles		10000
#define PARTICLE_SIZE		7
	// define variable
#define MAX_LENGTH			255

	// Macro
#define KeyUpMove (1<<0)
#define KeyDownMove (1<<1)
#define KeyRightMove (1<<2)
#define KeyLeftMove (1<<3)
#define KeyUpRota (1<<4)
#define KeyDownRota (1<<5)
#define KeyRightRota (1<<6)
#define KeyLeftRota (1<<7)
#define KeyBom (1<<8)
#define KeyTransform (1<<9)
#define PI					3.14159265359f
#define HALFPI				(PI/2.0f)
#define DEG_2_RAD(a)		a * PI / 180.0f
#define RAD_2_DEG(a)		a * 180.0f / PI
#define X2GAME(x)			((1.0f*x - SCREEN_CENTER_W)/SCREEN_CENTER_W)
#define Y2GAME(y)			(-1.0f*(1.0f*y - SCREEN_CENTER_H)/SCREEN_CENTER_H)
#define IN_RANGE( value, min, max ) ( ((value) >= (min) && (value) <= (max)) ? 1 : 0 )
#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )
#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )
#define TO_BOOL( a )  ( (a != 0) ? true : false )

//delete a ptr
#define RELEASE( x ) \
    {                        \
    if( x != NULL )        \
	    {                      \
      delete x;            \
	  x = NULL;              \
	    }                      \
    }
//delete an array of ptrs
#define RELEASE_ARRAY( x ) \
    {                              \
    if( x != NULL )              \
	    {                            \
      delete[] x;                \
	  x = NULL;                    \
	    }                            \
                              \
    }

typedef struct GL_COLOR
{
	float r;
	float g;
	float b;
	float a;
}  GL_COLOR;

typedef struct SPRITE_RECT
{
	int x, y;
	int w, h;
} SPRITE_RECT;

typedef enum
{
	ADDITIVE,
	NONE,
} OPENGL_BLENDMODE;

typedef unsigned int uint;
typedef unsigned __int8 uint8;
typedef unsigned __int32 uint32;
typedef unsigned __int64 uint64;
typedef unsigned char uchar;
enum EmitterType
{
	EMITTER_TYPE_NONE = -1,
	EMITTER_TYPE_FIRE,
	EMITTER_TYPE_BURST,
	EMITTER_TYPE_WAVE_1,
	EMITTER_TYPE_WAVE_2,
	EMITTER_TYPE_BOSS_ENTRANCE,
	EMITTER_TYPE_BOSS_DEATH,
	EMITTER_TYPE_SHIELD,
	EMITTER_TYPE_MAIN_DEATH,
	EMITTER_TYPE_ROCKET_EXPLODED,
	EMITTER_TYPE_LASER,
	EMITTER_TYPE_BULLET,
	EMITTER_TYPE_EXHAUST,
	EMITTER_TYPE_MID_EXPLOSION
};
#define MAX_NUM_EMITTERS_TYPE 20
#endif