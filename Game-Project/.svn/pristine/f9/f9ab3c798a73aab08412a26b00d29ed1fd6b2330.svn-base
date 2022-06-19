#include "SceneManager.h"


SceneManager * SceneManager::ms_pInstance = NULL;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{

}

void SceneManager::SceneLoading()
{
	FILE* pFile;
	int ID, a_number;
	int count = 0;
	pFile = fopen("../Resources/Managers/SM.txt", "r");
	//Loading objects
	fscanf(pFile, "#Objects: %d\n", &ObjectCount);
	for (int c = 0; c < ObjectCount; c++)
	{
		Sprite* NewObject = new Sprite;
		fscanf(pFile, "ID %d\n", &NewObject->ID);
		fscanf(pFile, "TYPE %s\n", &NewObject->type);
		fscanf(pFile, "MODEL %d\n", &NewObject->ModelID);
		fscanf(pFile, "TEXTURES %d\n", &NewObject->TexturesCount);
		for (int TexCount = 0; TexCount < NewObject->TexturesCount; TexCount++) {
			fscanf(pFile, "TEXTURE %d\n", &a_number);
			NewObject->Texturelist.push_back(a_number);
		}
		fscanf(pFile, "COORDS %d %d %d %d \n", &NewObject->spriteX, &NewObject->spriteY, &NewObject->spriteW, &NewObject->spriteH);
		fscanf(pFile, "SHADER %d\n", &NewObject->ShaderID);
		NewObject->theShader = *ResourceManager::GetInstance()->ShadersList.at(NewObject->ShaderID);
		NewObject->theShader.Init(NewObject->theShader.fileVS, NewObject->theShader.fileFS);
		fscanf(pFile, "POSITION %f %f %f\n", &NewObject->Pos.x, &NewObject->Pos.y, &NewObject->Pos.z);
		fscanf(pFile, "ROTATION %f %f %f\n", &NewObject->Rot.x, &NewObject->Rot.y, &NewObject->Rot.z);
		fscanf(pFile, "SCALE %f %f %f\n", &NewObject->Scale.x, &NewObject->Scale.y, &NewObject->Scale.z);
		fscanf(pFile, "\n");
		Objects.push_back(NewObject);
	}
	fscanf(pFile, "#Buttons: %d\n", &ButtonCount);
	for (int c = 0; c < ButtonCount; c++)
	{
		CButton* NewButton = new CButton;
		fscanf(pFile, "ID %d\n", &NewButton->ID);
		fscanf(pFile, "TYPE %s\n", &NewButton->type);
		fscanf(pFile, "NAME %s\n", &NewButton->m_name);
		fscanf(pFile, "MODEL %d\n", &NewButton->ModelID);
		fscanf(pFile, "TEXTURES %d\n", &NewButton->TexturesCount);
		for (int TexCount = 0; TexCount < NewButton->TexturesCount; TexCount++) {
			fscanf(pFile, "TEXTURE %d\n", &a_number);
			NewButton->Texturelist.push_back(a_number);
		}
		fscanf(pFile, "SHADER %d\n", &NewButton->ShaderID);
		NewButton->theShader = *ResourceManager::GetInstance()->ShadersList.at(NewButton->ShaderID);
		NewButton->theShader.Init(NewButton->theShader.fileVS, NewButton->theShader.fileFS);
		fscanf(pFile, "POSITION %f %f %f\n", &NewButton->Pos.x, &NewButton->Pos.y, &NewButton->Pos.z);
		fscanf(pFile, "ROTATION %f %f %f\n", &NewButton->Rot.x, &NewButton->Rot.y, &NewButton->Rot.z);
		fscanf(pFile, "SCALE %f %f %f\n", &NewButton->Scale.x, &NewButton->Scale.y, &NewButton->Scale.z);
		fscanf(pFile, "\n");
		CButtons.push_back(NewButton);
	}
	fclose(pFile);

}


Object* SceneManager::GetObjwID(int ID)
{
	for (int i = 0; i < ObjectCount; i++) if (Objects.at(i)->ID == ID) return Objects.at(i);
	return 0;
}
CButton* SceneManager::GetButtonID(int ID)
{
	for (int i = 0; i < ButtonCount; i++) if (CButtons.at(i)->ID == ID) return CButtons.at(i);
	std::cout << "Can't find such button!" << std::endl;
	return 0;
}
void SceneManager::Draws()
{
}

void SceneManager::Update(float deltaTime)
{
	 GetObjwID(1)->InputUpdate(deltaTime);
}

void SceneManager::CleanUp()
{
	for (int i = 0; i < ObjectCount; i++)
	{
		RELEASE(Objects.at(i));
	}
	for (int i = 0; i < LightsCount; i++)
	{
		RELEASE(Light.at(i));
	}
	for (int i = 0; i < ButtonCount; i++)
	{
		RELEASE(CButtons.at(i));
	}
	DestroyInstance();
}


