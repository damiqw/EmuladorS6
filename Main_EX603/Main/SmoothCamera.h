#pragma once

#define MAX_CAMERA_ZOOM		55
#define MIN_CAMERA_ZOOM		25
#define PERCF(x, y)		((float)x / 100.0f * (float)y)

#define pIsKeyNone				((bool(__cdecl*)(int)) 0x791030)
#define pIsKeyRelease			((bool(__cdecl*)(int)) 0x791050)
#define pIsKeyPress				((bool(__cdecl*)(int)) 0x791070)
#define pIsKeyRepeat			((bool(__cdecl*)(int)) 0x791090)

typedef struct{
	float	Zoom;
	float	RotationY;
	float	RotationZ;
	float	PositionZ;
	double	ClipX;
	float	ClipY;
	double	ClipZ;
	double	ClipX2;
	float	ClipY2;
	float	ClipZ2;
	float	ClipGL;
} DefaultData, *lpDefData;


class cSmoothCamera
{
public:
	cSmoothCamera();
	~cSmoothCamera();
	void SetState(bool s);
	void Toggle();
	void Restore();
	void SetCurrentValue();
	void SetDefaultValue();
	void Camera();
	bool getEnabled();
	float		ZoomPercent;
	static void RotateDmg(float& X, float& Y, float D);
	static void RotateFix();
	DefaultData Default;
private:
	BOOL  enable;
	float Temp_Zoom_Value;
	float Temp_Zoom_ValueX;
	float StackZoom;
	float StackX;
	float StackY;
	bool  isHold;
	short MouseStore[2];
	int   NonPK;
	int	  AnimationID;

};

extern cSmoothCamera SmoothCamera;
