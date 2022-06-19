#include "ResourceManager.h"
ResourceManager * ResourceManager::ms_pInstance = NULL;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

ResourceManager & ResourceManager::ResourceLoading()
{
	
	FILE* pFile;
	FILE* pModelFile;
	char File[100];
	int ID;
	int count = 0;
	pFile = fopen("../Resources/Managers/RM.txt", "r");
	//Loading models
	fscanf(pFile, "#Models: %d\n", &ModelCount);

	for (int c = 0; c < ModelCount; c++)
	{
		Model* NewModel = new Model();
		fscanf(pFile, "ID %d\n", &NewModel->ID);
		fscanf(pFile, "FILE %s\n", File);
		pModelFile = fopen(File, "r");
		fscanf(pModelFile, "NrVertices: %d\n", &NewModel->VerticesCount);
		for (int i = 0; i < NewModel->VerticesCount; i++)
		{
			fscanf(pModelFile, "   %d. ", &ID);
			fscanf(pModelFile, "pos:[%f, %f, %f]; ", &NewModel->Vertices[i].pos.x, &NewModel->Vertices[i].pos.y, &NewModel->Vertices[i].pos.z);
			fscanf(pModelFile, "uv:[%f, %f];\n", &NewModel->Vertices[i].uv.x, &NewModel->Vertices[i].uv.y);
		}
		fscanf(pModelFile, "NrIndices: %d\n", &NewModel->IndicesCount);
		count = 0;
		while (count < NewModel->IndicesCount)
		{
			fscanf(pModelFile, "%d. %d, %d, %d\n; ", &ID, &NewModel->Idx[count], &NewModel->Idx[count + 1], &NewModel->Idx[count + 2]);
			count += 3;
		}
		Models.push_back(NewModel);
		Models.at(c)->ModelInit();
	}

	fscanf(pFile, "\n");
	//Loading textures
	fscanf(pFile, "#2D Textures: %d\n", &TwoDTexturesCount);
	for (int c = 0; c < TwoDTexturesCount; c++)
	{
		Texture* NewTexture = new Texture();
		fscanf(pFile, "ID %d\n", &NewTexture->ID);
		fscanf(pFile, "FILE %s\n", &NewTexture->Tex);
		Textures.push_back(NewTexture);
		Textures.at(c)->TextureInit();
	}

	fscanf(pFile, "\n");	
	//Loading shaders
	fscanf(pFile, "#Shaders: %d\n", &ShadersCount);
	char state[20];
	for (int c = 0; c < ShadersCount; c++)
	{
		Shaders* NewShader = new Shaders();
		ShadersList.push_back(NewShader);
		fscanf(pFile, "ID %d\n", &ShadersList.at(c)->ID);
		fscanf(pFile, "VS %s\n", &ShadersList.at(c)->fileVS);
		fscanf(pFile, "FS %s\n", &ShadersList.at(c)->fileFS);
	}
	fclose(pFile);
	fclose(pModelFile);
	return *this;
}

Texture* ResourceManager::getTexture(int ID)
{
	//return Textures.at(ID);
	for (int i = 0; i < TwoDTexturesCount; i++)
		if (Textures.at(i)->ID == ID) return Textures.at(i);
	std::cout << "Found no such texture!\n";
	return NULL;
}

void ResourceManager::CleanUp()
{
	for (int i = 0; i < ModelCount; i++)
	{
		glDeleteBuffers(1, &Models.at(i)->vboId);
		glDeleteBuffers(1, &Models.at(i)->iboId);
		RELEASE_ARRAY(Models.at(i)->Vertices);

		RELEASE_ARRAY(Models.at(i)->Idx);

		RELEASE(Models.at(i));
	}
	for (int i = 0; i < TwoDTexturesCount; i++)
	{
		RELEASE(Textures.at(i));
	}

	for (int i = 0; i < ShadersCount; i++)
	{
		RELEASE(ShadersList.at(i));
	}
	DestroyInstance();
}
