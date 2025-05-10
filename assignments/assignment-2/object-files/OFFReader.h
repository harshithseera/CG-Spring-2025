#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Vt {
	float x,y,z;
	Vector3f normal;
	int numIcidentTri;
}Vertex;

typedef struct Pgn {
	int noSides;
	int *v;
}Polygon;

typedef struct offmodel {
	Vertex *vertices;
	Polygon *polygons;
	int numberOfVertices;
 	int numberOfPolygons;
	float minX, minY, minZ, maxX, maxY, maxZ;
	float extent;
}OffModel;

OffModel* readOffFile(char * OffFile) {
	FILE * input;
	char type[3]; 
	int noEdges;
	int i,j;
	float x,y,z;
	int n, v;
	int nv, np;
	OffModel *model;


	input = fopen(OffFile, "r");
	fscanf(input, "%s", type);
	/* First line should be OFF */
	if(strcmp(type,"OFF")) {
		printf("Not a OFF file");
		exit(1);
	}
	/* Read the no. of vertices, faces and edges */
	fscanf(input, "%d", &nv);
	fscanf(input, "%d", &np);
	fscanf(input, "%d", &noEdges);

	model = (OffModel*)malloc(sizeof(OffModel));
	model->numberOfVertices = nv;
	model->numberOfPolygons = np;
	
	
	/* allocate required data */
	model->vertices = (Vertex *) malloc(nv * sizeof(Vertex));
	model->polygons = (Polygon *) malloc(np * sizeof(Polygon));
	

	/* Read the vertices' location*/	
	for(i = 0;i < nv;i ++) {
		fscanf(input, "%f %f %f", &x,&y,&z);
		(model->vertices[i]).x = x;
		(model->vertices[i]).y = y;
		(model->vertices[i]).z = z;
		(model->vertices[i]).numIcidentTri = 0;
		if (i==0){
			model->minX = model->maxX = x; 
			model->minY = model->maxY = y; 
			model->minZ = model->maxZ = z; 
		} else {
			if (x < model->minX) model->minX = x;
			else if (x > model->maxX) model->maxX = x;
			if (y < model->minY) model->minY = y;
			else if (y > model->maxY) model->maxY = y;
			if (z < model->minZ) model->minZ = z;
			else if (z > model->maxZ) model->maxZ = z;
		}
	}

	/* Read the Polygons */	
	for(i = 0;i < np;i ++) {
		/* No. of sides of the polygon (Eg. 3 => a triangle) */
		fscanf(input, "%d", &n);
		
		(model->polygons[i]).noSides = n;
		(model->polygons[i]).v = (int *) malloc(n * sizeof(int));
		/* read the vertices that make up the polygon */
		for(j = 0;j < n;j ++) {
			fscanf(input, "%d", &v);
			(model->polygons[i]).v[j] = v;
		}
	
	float extentX = model->maxX - model->minX;
	float extentY = model->maxY - model->minY;
	float extentZ = model->maxZ - model->minZ;
	model->extent = (extentX > extentY) ? ((extentX > extentZ) ? extentX : extentZ) : ((extentY > extentZ) ? extentY : extentZ);

	fclose(input);
	return model;
}

int FreeOffModel(OffModel *model)
{
	int i,j;
	if( model == NULL )
		return 0;
	free(model->vertices);
	for( i = 0; i < model->numberOfPolygons; ++i )
	{
		if( (model->polygons[i]).v )
		{
			free((model->polygons[i]).v);
		}
	}
	free(model->polygons);
	free(model);
	return 1;
}

