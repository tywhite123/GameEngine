#include <nclgl\Matrix4.h>
#include <nclgl\Mesh.h>
#include <nclgl\Shader.h>
#include <nclgl\OGLRenderer.h>

#pragma once


//This class was part of the undergrad version of nclgl which was rewritten for use with this project

class RenderObject
{
public:
	RenderObject(void);
	RenderObject(Mesh* m, Shader* s, GLuint t = 0);
	~RenderObject();

	Mesh* GetMesh() const { return mesh; }
	void SetMesh(Mesh* m) { mesh = m; }

	Shader* GetShader() const { return shader; }
	void SetShader(Shader* s) { shader = s; }
	
	void	SetModelMatrix(Matrix4 mat) { modelMatrix = mat; }
	Matrix4 GetModelMatrix()	const { return modelMatrix; }

	virtual void Update(float msec);

	virtual void Draw() const;

	Matrix4 GetWorldTransform() const {
		return worldTransform;
	}

	void	AddChild(RenderObject &child) {
		children.push_back(&child);
		child.parent = this;
	}

	const vector<RenderObject*>& GetChildren() const {
		return children;
	}

protected:
	Mesh* mesh;
	Shader* shader;

	GLuint tex; //Sort this out another time

	Matrix4 modelMatrix;
	Matrix4 worldTransform;

	RenderObject* parent;
	vector<RenderObject*> children;
};

