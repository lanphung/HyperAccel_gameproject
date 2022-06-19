#pragma once
#include "Vertex.h"
#include "Shaders.h"

class Model
{
public:
	Model();
	~Model();
	Vertex* Vertices = new Vertex[__MAX_VERTICES];
	GLint* Idx = new GLint[__MAX_INDICES];
	int ID;
	int VerticesCount;
	int IndicesCount;
	GLuint  vboId;
	GLuint  iboId;
	void Model::ModelInit()
	{
		glGenBuffers(1, &vboId);
		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*VerticesCount, Vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glGenBuffers(1, &iboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint)*IndicesCount, Idx, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}
	void Model::ModelDraw(Shaders *theShader)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
		if (theShader->positionAttribute != -1)
		{
			glEnableVertexAttribArray(theShader->positionAttribute);
			glVertexAttribPointer(theShader->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), POS_OFFSET);
		}
		if (theShader->uvAttribute != -1)
		{

			glEnableVertexAttribArray(theShader->uvAttribute);
			glVertexAttribPointer(theShader->uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), POS_OFFSET + UV_OFFSET);
		}
		glDrawElements(GL_TRIANGLES, IndicesCount, GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
};
