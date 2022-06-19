#ifndef __VIDEO_DRIVER_H__
#define __VIDEO_DRIVER_H__

#include <stdarg.h>
#include <openGLESv2.h>
#include <matrix.h>

class VideoDriver
{
private:
	//Color
	float color[4];
	static VideoDriver* s_Instance;

	void Draw(int x, int y, int width, int height, unsigned int idTexture = 0);
	void DrawVertices(float* vertices, unsigned int numVertices, GLenum mode = GL_TRIANGLES);

public:
	// Constructor
	VideoDriver(void);

	// Destructor
	~VideoDriver(void);

	// Methods
	void Init();
	void FillRect(int x, int y, int width, int height);
	void DrawRect(int x, int y, int width, int height, int weight = 1);
	void DrawCircle(float cx, float cy, float radius);
	void DrawLine(float x1, float y1, float x2, float y2);

	void SetColor(unsigned int color);

	void CleanScreen();

	static VideoDriver* GetInstance();

	// Propertices
	unsigned int program;
};

#endif