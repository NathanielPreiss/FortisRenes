
#include "CCursor.h"
#include "DirectX Wrappers/CSGD_DirectInput.h"
#include "DirectX Wrappers/CSGD_Direct3D.h"
#include "CCamera.h"
CCursor::CCursor(void)
{
	SetCoverObject(false);
	SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/Crosshair.png"));

	SetPosX(100.0f);
	SetPosY(100.0f);

	SetLayer(0);
	SetWidth(32);
	SetHeight(32);
}
CCursor::~CCursor(void)
{
}
CCursor* CCursor::GetInstance(void)
{
	static CCursor instance;
	return &instance;
}
void CCursor::Update(float fElapsedTime)
{
	SetType(OBJECT_CURSOR);
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
	SetPosX((float)GetPosX()+(pDI->MouseMovementX()*0.5f));
	SetPosY((float)GetPosY()+(pDI->MouseMovementY()*0.5f));

	if(GetPosX() < 0)
		SetPosX(0);
	else if((unsigned int)GetPosX() > CSGD_Direct3D::GetInstance()->GetPresentParams()->BackBufferWidth)
		SetPosX((float)CSGD_Direct3D::GetInstance()->GetPresentParams()->BackBufferWidth);
	if(GetPosY() < 0)
		SetPosY(0);
	else if((unsigned int)GetPosY() > CSGD_Direct3D::GetInstance()->GetPresentParams()->BackBufferHeight)
		SetPosY((float)CSGD_Direct3D::GetInstance()->GetPresentParams()->BackBufferHeight);
		
}
void CCursor::Render(void)
{
	CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (int)((GetPosX() - GetWidth()/2) ), 
		(int)((GetPosY() - GetHeight()/2)),1, 1, 0,0, 0, 0);	
}
void CCursor::UnloadCursor(void)
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(GetImageID());
}

void CCursor::HandleEvent(CBase* pBase)
{
}