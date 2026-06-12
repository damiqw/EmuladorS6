#pragma once
#if(FPS_60 == 1)
#pragma once
//#include "SEASON3B.h"
#define PVS_NORMAL						( 0x00)
#define PVS_FIXEDPOS					( 0x01)
#define RATE_SHORT_SHOULDER				( 0.6f)
#define PCT_MASK_SHAPE					( 0x00000003)
#define PCT_FLAT						( 0x00000000)
#define PCT_CURVED						( 0x00000001)
#define PCT_STICKED						( 0x00000002)
#define PCT_MASK_SHAPE_EXT				( 0x0000000C)
#define PCT_SHAPE_NORMAL				( 0x00000000)
#define PCT_SHORT_SHOULDER				( 0x00000004)
#define PCT_CYLINDER					( 0x00000008)
#define PCT_MASK_SHAPE_EXT2				( 0x00000030)
#define PCT_SHAPE_HALLOWEEN				( 0x00000010)
#define PCT_MASK_ELASTIC				( 0x00000300)
#define PCT_COTTON						( 0x00000000)
#define PCT_RUBBER						( 0x00000100)
#define PCT_RUBBER2						( 0x00000200)
#define PCT_MASK_WEIGHT					( 0x00000C00)
#define PCT_NORMAL_THICKNESS			( 0x00000000)
#define PCT_HEAVY						( 0x00000400)
#define PCT_MASK_DRAW					( 0x00003000)
#define PCT_MASK_BLIT					( 0x00000000)
#define PCT_MASK_ALPHA					( 0x00001000)
#define PCT_MASK_BLEND					( 0x00002000)

#define FPS_							*(float*)0x5EF5A18
#define DelTtime						*(float*)0xE61610
#define CameraWalkCut					*(int*)0xE8C83C
#define CurrentCameraCount				*(int*)0xE60AB0
#define CurrentCameraNumber				*(int*)0xE8CB48
#define CurrentCameraWalkType			*(int*)0xE8CB44
#define MoveSceneFrame					*(int*)0xE8CB20
#define s_fInvOfMass					*(float*)0xE614C8
//--


#define listWayPoint_empty				((BOOL(__thiscall*)(void* This)) 0x004DEC50)
#define listWayPoint_size				((int(__thiscall*)(int This)) 0x004DEC30)
#define GetlistWayPoint					((unsigned int (__thiscall*)(int This, unsigned int index)) 0x004DEC70)
#define sub_4DEB00						((int(__thiscall*)(int This)) 0x004DEB00)
#define CreateAngle						((double(__cdecl*)(float a1, float a2, float a3, float a4)) 0x00540C30)
#define absf							((double(__cdecl*)(float a1)) 0x00639050)
#define sub_959B10						((double(__cdecl*)(int This, int v2)) 0x00959B10)
#define MoveCharacterCamera				((void(__cdecl*)(vec3_t Origin,vec3_t Position,vec3_t Angle)) 0x004D66C0)
#define UpdateForce						((void(__thiscall*)(int This, unsigned int iKey, DWORD dwType, float fWind)) 0x0051C890)
#define CPhysicsVertex_Init				((void(__thiscall*)(int This, float fXPos, float fYPos, float fZPos, BOOL bFixed)) 0x0051C850)
#define sub_9CF1C0						((void(__cdecl*)(int a1, int a2, int a3)) 0x009CF1C0)


typedef struct
{
	int     byClass;
	vec3_t  m_vForce;
	vec3_t  m_vVel;
	vec3_t  m_vPos;
	BYTE    m_byState;
	char    sobrante[16];
}PhysicsVertex, *CPhysicsVertex;

class CCameraMove
{
public:
	enum {
		CAMERAWALK_STATE_READY = 0,
		CAMERAWALK_STATE_MOVE,
		CAMERAWALK_STATE_DONE,
	};
	CCameraMove(void);
	virtual ~CCameraMove(void);
	void Init();
	static void CameraTourWay();
	static void __thiscall CPhysicsCloth_InitForces(int This);
	static int __thiscall CPhysicsClothMove2(void* This, float a2, int a3);
	static void __thiscall CPhysicsVertex_Move(CPhysicsVertex This, float fTime);
	static char __thiscall PlayAnimation(int Bis, int a2, int a3, int a4, float a5, int a6, int a7);
};

extern CCameraMove g_CameraWalkInstance;
#endif