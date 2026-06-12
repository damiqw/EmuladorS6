#include "stdafx.h"
#include "SmoothCamera.h"
#include "Util.h"
#include "Import.h"
#include "Interface.h"
#include "Defines.h"
#include "TMemory.h"

cSmoothCamera SmoothCamera;


void cSmoothCamera::RotateDmg(float& X, float& Y, float D)
{
	float curX1 = *(float*)0x087933D8;
	const float Rad = 0.01745329f;
	float sinTh = sin(Rad * (curX1));
	float cosTh = cos(Rad * (curX1));

	X += D / 0.7071067f * cosTh / 2;
	Y -= D / 0.7071067f * sinTh / 2;
}

void __declspec(naked) cSmoothCamera::RotateFix()
{
	static DWORD jmpBack = 0x0063752D;

	_asm
	{
		Lea Eax, [Ebp - 0x38];
		Lea Ecx, [Ebp - 0x3C];
		Push Dword Ptr[Ebp + 0x18];
		Push Eax;
		Push Ecx;
		Call RotateDmg;
		Add Esp, 0xC;
		jmp[jmpBack];
	}
}
//21-11
cSmoothCamera::cSmoothCamera()
{
	this->enable = false;

	this->StackZoom = 0;

	this->StackX = 0;

	this->StackY = 0;

	this->isHold = false;

	this->Default.Zoom = *(float*)oCam_Zoom;
	this->Default.RotationY = *(float*)oCam_RotY;
	this->Default.RotationZ = *(float*)oCam_RotZDef;
	this->Default.PositionZ = *(float*)oCam_PosZDef;
	this->Default.ClipX = *(double*)oCam_ClipX;
	this->Default.ClipY = *(float*)oCam_ClipY;
	this->Default.ClipZ = *(double*)oCam_ClipZ;
	this->Default.ClipX2 = *(double*)oCam_ClipX2;
	this->Default.ClipY2 = *(float*)oCam_ClipY2;
	this->Default.ClipZ2 = *(float*)oCam_ClipZ2;
	this->Default.ClipGL = *(float*)oCam_ClipGL;
	this->ZoomPercent = this->Default.Zoom / (MAX_CAMERA_ZOOM / 100.0f);

	SetCompleteHook(0xE9, 0x0063764C, &RotateFix);
	SetCompleteHook(0xE9, 0x005DB322, 0x5DB408); //-> Fix 3D Cam in Santa Village
}

cSmoothCamera::~cSmoothCamera()
{
}

bool cSmoothCamera::getEnabled()
{
	return this->enable != 0;
}

void cSmoothCamera::Toggle() // OK
{
	if (*(DWORD*)(0x00E609E8) == 5)
	{
		this->enable ^= 1;
	}
}

void cSmoothCamera::Restore() // OK
{
	if (*(DWORD*)(0x00E609E8) == 5)
	{
		this->SetDefaultValue();
	}
}

void cSmoothCamera::SetCurrentValue() // OK
{
	if (pPlayerState != GameProcess)
	{
		return;
	}

	if (pMapNumber == 30)
	{
		SetDouble(0x00D2C848, (4190.0f + (abs(((*(double*)0x00D255A0) - 150.0f))*3.0f)));

		SetDouble(0x00D2C898, (4190.0f + (abs(((*(double*)0x00D255A0) - 150.0f))*3.0f)));

		SetFloat(0x00D2C894, (5400.0f + (((float)abs(((*(double*)0x00D255A0) - 150.0f)))*3.0f)));

		SetFloat(0x00D2C8A8, (5400.0f + (((float)abs(((*(double*)0x00D255A0) - 150.0f)))*3.0f)));

		SetFloat(0x00D2570C, (2100.0f + (((float)abs(((*(double*)0x00D255A0) - 150.0f)))*3.0f)));
	}
	else
	{
		this->ZoomPercent = *(float*)oCam_Zoom / (MAX_CAMERA_ZOOM / 100.0f);
		SetDouble((LPVOID)oCam_ClipX, PERCF(PERCF(this->Default.ClipX, 500), this->ZoomPercent));
		SetFloat((LPVOID)oCam_ClipY, PERCF(PERCF(this->Default.ClipY, 285), this->ZoomPercent));
		SetDouble((LPVOID)oCam_ClipZ, PERCF(PERCF(this->Default.ClipZ, -395), this->ZoomPercent));
		SetDouble((LPVOID)oCam_ClipX2, PERCF(PERCF(this->Default.ClipX2, 235), this->ZoomPercent));
		SetFloat((LPVOID)oCam_ClipY2, PERCF(PERCF(this->Default.ClipY2, 195), this->ZoomPercent));
		SetFloat((LPVOID)oCam_ClipZ2, PERCF(PERCF(this->Default.ClipZ2, -4000), this->ZoomPercent));
		SetFloat((LPVOID)oCam_ClipGL, PERCF(PERCF(this->Default.ClipGL, 200), this->ZoomPercent));
	}

}


void cSmoothCamera::SetDefaultValue() // OK
{
	this->StackZoom = 0;

	this->StackX = 0;

	this->StackY = 0;

	this->isHold = false;
	if (pMapNumber == 30)
	{
		SetFloat(0x00D27BFC, 35);
		SetFloat(0x087933D8, -45);
		SetFloat(0x00D27B88, -48.5);
		SetDouble(0x00D255A0, 150);

		//for what?
		SetDouble(0x00D2C848, 1190);
		SetDouble(0x00D2C898, 580);
		SetFloat(0x00D2C894, 2400);
		SetFloat(0x00D2C8A8, 3300);
		SetFloat(0x00D2570C, 2000);
	}
	else
	{

		SetFloat((LPVOID)oCam_Zoom, this->Default.Zoom);
		SetFloat((LPVOID)oCam_RotY, this->Default.RotationY);
		SetFloat((LPVOID)oCam_RotZ, this->Default.RotationZ);
		SetDouble((LPVOID)oCam_PosZ, this->Default.PositionZ);
		SetDouble((LPVOID)oCam_ClipX, this->Default.ClipX + 500);
		SetFloat((LPVOID)oCam_ClipGL, this->Default.ClipGL + 200);
		SetFloat((LPVOID)oCam_ClipY, this->Default.ClipY);
		SetDouble((LPVOID)oCam_ClipZ, this->Default.ClipZ);
		SetDouble((LPVOID)oCam_ClipX2, this->Default.ClipX2);
		SetFloat((LPVOID)oCam_ClipY2, this->Default.ClipY2);
		SetFloat((LPVOID)oCam_ClipZ2, this->Default.ClipZ2);
		this->ZoomPercent = *(float*)oCam_Zoom / (MAX_CAMERA_ZOOM / 100.0f);
	}
}

void cSmoothCamera::Camera()
{
	if (*(bool*)0x00E609E8 != 5)
		return;

	if (pIsKeyRelease(VK_F10))
	{ // on/off
		if (this->enable) {
			this->NonPK = -1;
			this->AnimationID = -1;
		}
	}
	if (pIsKeyRelease(VK_F11))
	{ // restore value
		this->SetDefaultValue();
	}

	if (!this->enable)
	{
		return;
	}


	float curZoom = *(float*)0x00D27BFC;
	float curX = *(float*)0x087933D8;
	float curY = *(float*)0x00D27B88;
	double curZ = *(double*)0x00D255A0;
	float maxY = -45.0f - (MAX_CAMERA_ZOOM - curZoom) / 2;
	float minY = -95.0f - (MAX_CAMERA_ZOOM - curZoom) / 2;
	int mouseWheel = *(int*)0x0879337C;
	if (mouseWheel != 0)
	{
		if ((mouseWheel > 0 && this->StackZoom < 0) || (mouseWheel < 0 && this->StackZoom > 0))
			this->StackZoom = 0;
		this->StackZoom -= mouseWheel * 10.0;
		*(int*)0x0879337C = 0;
	}
	else {
		int curAnimationID = *(WORD*)(*(DWORD*)0x7BC4F04 + 0x31A);
		int curNonPK = *(BYTE*)(*(DWORD*)0x07BC4F04 + 0xE);
		bool zoomin = false;
		bool zoomout = false;
		if (curAnimationID == 233 || //ngoi
			curAnimationID == 237 || //du cay
			curAnimationID == 239) { //dua tuong
			//zoom in
			zoomin = true;
		}
		if (this->AnimationID == 233 || //ngoi
			this->AnimationID == 237 || //du cay
			this->AnimationID == 239) { //dua tuong
			//zoom in
			zoomout = true;
		}

		//gInterface.DrawFormat(-1, 150, 150, 0, 0, "%d %d | %d %d", curAnimationID, this->AnimationID, curNonPK, this->NonPK);

		if (curAnimationID != this->AnimationID)
		{ //uu tien hanh dong truoc
			this->AnimationID = curAnimationID;

			if (zoomin)
			{ //zoom in
				if (curZoom > 30)
				{
					this->StackZoom = floor(curZoom - 30) * -1;
				}
			}
			else if (zoomout)
			{ //zoom out
				if (!curNonPK)
				{
					if (curZoom < MAX_CAMERA_ZOOM)
					{
						this->StackZoom = floor(MAX_CAMERA_ZOOM - curZoom);
					}
				}
				else
				{
					if (curZoom < 50)
					{
						this->StackZoom = floor(50 - curZoom);
					}
					else if (curZoom > 50)
					{
						this->StackZoom = floor(curZoom - 50) * -1;
					}
				}
			}
		}
		//if (!zoomin) 
		//{
		//	if (curNonPK != this->NonPK) 
		//	{
		//		this->NonPK = curNonPK;
		//		//if (!curNonPK)
		//		//{ //zoom out
		//		//	if (curZoom < MAX_CAMERA_ZOOM) 
		//		//	{
		//		//		this->StackZoom = floor(MAX_CAMERA_ZOOM - curZoom);
		//		//	}
		//		//}
		//		//else
		//		//{ //zoom in
		//		//	if (curZoom < 50)
		//		//	{
		//		//		this->StackZoom = floor(50 - curZoom);
		//		//	}
		//		//	else if (curZoom > 50)
		//		//	{
		//		//		this->StackZoom = floor(curZoom - 50) * -1;
		//		//	}
		//		//}
		//	}
		//}
	}

	if (pIsKeyRepeat(VK_MBUTTON)){
		if (this->isHold) //update
		{
			if (pCursorX != this->MouseStore[0])
			{
				this->StackX += (float)(pCursorX - this->MouseStore[0]);
			}
			if (pCursorY != this->MouseStore[1])
			{
				this->StackY += (float)(pCursorY - this->MouseStore[1]);
			}
		}
		else
		{ //create
			this->isHold = true;
		}
		this->MouseStore[0] = pCursorX;
		this->MouseStore[1] = pCursorY;
	}

	if (pIsKeyRelease(VK_MBUTTON))
	{
		this->isHold = false;
	}


	if (curX < -417.0f)
	{
		SetFloat(0x087933D8, -45.0f);
	}

	if ((curY > -45.0f && this->StackY > 0) || (curY < -90.0f && this->StackY < 0))
	{
		this->StackY = 0;
	}

	if ((curZoom >= MAX_CAMERA_ZOOM && this->StackZoom > 0) || (curZoom <= MIN_CAMERA_ZOOM && this->StackZoom < 0)) {
		this->StackZoom = 0;
	}

	float fpsRate = *(float*)0x5EF5A18 / 190.0f; //for unlimited FPS system

	float speedZoom = max(0.25 / fpsRate, abs(this->StackZoom / (65.f * fpsRate)));
	float speedX = max(0.5 / fpsRate, abs(this->StackX / 60.f));
	float speedY = max(0.25 / fpsRate, abs(this->StackY / 160.f));

	if (this->StackZoom > 0)
	{
		SetFloat(0x00D27BFC, curZoom + speedZoom);
		this->StackZoom -= speedZoom;

		//float newzoomY = max(-45.0f - (MAX_CAMERA_ZOOM - (curZoom + speedZoom)), -90.0f);
		//float newzoomZ = min((MAX_CAMERA_ZOOM - (curZoom + speedZoom)) * 18, 1000.f);
		//SetFloat(0x00D27B88, max(curY, newzoomY));
		//SetDouble(0x00D255A0, min(curZ, newzoomZ));

		this->SetCurrentValue();
		if (this->StackZoom < speedZoom) {
			this->StackZoom = 0;
		}
	}
	else if (this->StackZoom < 0)
	{
		SetFloat(0x00D27BFC, curZoom - speedZoom);
		this->StackZoom += speedZoom;

		//float newzoomY = max(-45.0f - (MAX_CAMERA_ZOOM - (curZoom - speedZoom)), -90.0f);
		//float newzoomZ = min((MAX_CAMERA_ZOOM - (curZoom - speedZoom)) * 18, 1000.f);
		//SetFloat(0x00D27B88, min(curY, newzoomY));
		//SetDouble(0x00D255A0, max(curZ, newzoomZ));

		this->SetCurrentValue();
		if (this->StackZoom > speedZoom) {
			this->StackZoom = 0;
		}
	}

	if (this->StackX > 0)
	{
		SetFloat(0x087933D8, curX + speedX);
		this->StackX -= speedX;
		this->SetCurrentValue();
		if (this->StackX < speedX) {
			this->StackX = 0;
		}
	}
	else if (this->StackX < 0)
	{
		SetFloat(0x087933D8, curX - speedX);
		this->StackX += speedX;
		this->SetCurrentValue();
		if (this->StackX > speedX) {
			this->StackX = 0;
		}
	}

	if (this->StackY > 0)
	{
		SetFloat(0x00D27B88, (curY + 2.420f / 5.0));
		SetDouble(0x00D255A0, (curZ - 44.0f / 5.0));
		this->StackY -= speedY;
		this->SetCurrentValue();
		if (this->StackY < speedY)
		{
			this->StackY = 0;
		}
	}
	else if (this->StackY < 0)
	{
		SetFloat(0x00D27B88, (curY - 2.420f / 5.0));
		SetDouble(0x00D255A0, (curZ + 44.0f / 5.0));
		this->StackY += speedY;
		this->SetCurrentValue();
		if (this->StackY > speedY)
		{
			this->StackY = 0;
		}
	}
}
