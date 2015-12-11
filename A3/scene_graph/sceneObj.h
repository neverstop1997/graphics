#ifndef __SCENEOBJ_H__	//guard against cyclic dependancy
#define __SCENEOBJ_H__

#include <windows.h>
#include <stdio.h>
#include "structs.h"
#include "node.cpp"
#include "nodeTransform.cpp"
#include "nodeModel.cpp"
#include "nodeMaterial.cpp"
#include "nodeLight.cpp"
//#include "boundingBox.h"

//scene object class
class SceneObj{
public:
	//constructor
	SceneObj();
	SceneObj(int ID, NodeTransform *transNode, NodeTransform *scaleNode, NodeTransform *rotNode, NodeMaterial *matNode, NodeModel *modelNode);
	//lighting constructor
	SceneObj(int ID, NodeTransform *transNode, NodeLight *lightNode, NodeModel *modelNode);

	//instance variables (add bounding box!)
	int ID;
	NodeTransform *transNode;
	NodeTransform *scaleNode;
	NodeTransform *rotNode;
	NodeMaterial *matNode;
	NodeModel *modelNode;
	NodeLight *lightNode;
	//BoundingBox * box;

	//bounding box???
	
	//public methods
	void translate(float x, float y, float z);
	void scale(float x, float y, float z);
	void rotate(float x, float y, float z);
	void changeMaterial(Material m);

};

#endif