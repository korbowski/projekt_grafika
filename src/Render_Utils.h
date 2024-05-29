#pragma once

#include "objload.h"

namespace Core
{
	
	/*void DrawVertexArray(const float * vertexArray, int numVertices, int elementSize);

	void DrawVertexArrayIndexed(const float * vertexArray, const int * indexArray, int numIndexes, int elementSize);*/


	struct VertexAttribute
	{
		const void * Pointer;
		int Size;
	};

	struct VertexData
	{
		static const int MAX_ATTRIBS = 8;
		VertexAttribute Attribs[MAX_ATTRIBS];
		int NumActiveAttribs;
		int NumVertices;
	};

	/*void DrawVertexArray(const VertexData & data);*/

	void DrawModel(obj::Model * model);
}