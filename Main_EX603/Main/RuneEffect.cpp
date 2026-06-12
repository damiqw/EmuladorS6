#include "stdafx.h"
#include "RuneEffect.h"
#include "Object.h"
#include "Import.h"
#include "Defines.h"
#include "PartyBar.h"
#include "zzzmathlib.h"
#include "Util.h"

RuneEffect gRuneEffect;

RuneEffect::RuneEffect()
{
	this->m_RuneEffectInfo.clear();
}


void RuneEffect::LoadRuneEffect(RuneEffectType * info)
{
	for (int n = 0; n < MAX_TYPE_RUNEEFFECT; n++)
	{
		if (info[n].Index < 0 || info[n].Index >= MAX_TYPE_RUNEEFFECT)
		{
			return;
		}
		this->m_RuneEffectInfo.push_back(info[n]);
	}
}

void RuneEffect::GCRuneEffect(PMSG_CUSTOM_RUNEEFFECT* aRecv)
{
	if (aRecv == NULL)
	{
		return;
	}
	// ---
	this->m_RuneEffect[aRecv->iIndex].m_Level = aRecv->iLevel;
	this->m_RuneEffect[aRecv->iIndex].m_Resets = aRecv->iReset;
	this->m_RuneEffect[aRecv->iIndex].m_MResets = aRecv->iMReset;
	this->m_RuneEffect[aRecv->iIndex].cVip = aRecv->cVip;
	this->m_RuneEffect[aRecv->iIndex].cGM = aRecv->cGM;
	this->m_RuneEffect[aRecv->iIndex].cPK = aRecv->cPK;

	char Testando[200];
	wsprintf(Testando, "Vem Agora %d/%d", this->m_RuneEffect[aRecv->iIndex].cVip, aRecv->cVip);
	//Console.Write(Testando, 0, 0);
}

void RuneEffect::RenderRuneEffect(DWORD ObjectModel, int ID, float Size, float ColorR, float ColorG, float ColorB, float Speed, float FloorDistance)
{
	vec3_t vLight;
	Vector(ColorR, ColorG, ColorB, vLight);
	float fLumi = sinf(WorldTime * 0.0015f) * 0.3f + 0.5f;
	Vector(fLumi * vLight[0], fLumi * vLight[1], fLumi * vLight[2], vLight);
	EnableAlphaBlend();	
	RenderTerrainAlphaBitmap(ID, *(float*)(ObjectModel + 252), *(float*)(ObjectModel + 256), Size, Size, vLight, WorldTime * Speed, 1.0, FloorDistance, 1);
	DisableAlphaBlend();
}

void RenderCharacter(ObjectPreview* a4, OBJECT* a5, int Select)
{
	for (std::vector<RuneEffectType>::iterator it = gRuneEffect.m_RuneEffectInfo.begin(); it != gRuneEffect.m_RuneEffectInfo.end(); it++)
	{
		//char Testando[200];
		//wsprintf(Testando, "Carregado: %d/%d/%d/%d/%d/%d/%d", it->Index,it->Type,it->TextureIndex,it->Size,it->ColorR,it->ColorG,it->ColorB);
		//Console.Write(Testando, 0, 0);
	}

	int v3; // eax@4
	int result; // eax@51
	int v5; // [sp+0h] [bp-Ch]@4
	int v55; // [sp+0h] [bp-Ch]@4
	int v6; // [sp+4h] [bp-8h]@4
	signed int i; // [sp+8h] [bp-4h]@1

	for (i = 0; i < 400; ++i)
	{
		v6 = pGetPreviewStruct(pPreviewThis(), i);
		v5 = v6 + 776;
		v55 = Hero + 776; //Nova Variavel

		if (v6 == *(DWORD*)0x7BC4F04 || /*sub_8CB0E0() != 1 ||*/ !sub_4C8640((DWORD*)(v6 + 1260), 18))
			goto LABEL_38;
		if (*(BYTE*)(*(DWORD*)0x7BC4F04 + 23) == 9 || *(BYTE*)(*(DWORD*)0x7BC4F04 + 23) == 6)
		{
			if (*(BYTE*)(v6 + 23) != 9 && *(BYTE*)(v6 + 23) != 6)
			{
				if (*(WORD*)(*(DWORD*)0x7BC4F04 + 128) == *(WORD*)(v6 + 126))
					*(WORD*)(*(DWORD*)0x7BC4F04 + 128) = -1;
				continue;
			}
		LABEL_38:
			if (v6 == *(DWORD*)0x7BC4F04 && *(BYTE*)(*(DWORD*)0x7BC4F04 + 21) & 4 && *(DWORD*)0xE609E8 == 5)
			{
				*(float*)(v6 + 1200) = 1000.0;
				*(float*)(v6 + 1244) = 1.0;
				*(float*)(v6 + 1228) = 1.0;
				*(float*)(v6 + 1212) = 1.0;
			}
			else if (*(BYTE*)(v6 + 780) && *(BYTE*)(v6 + 788))
			{
				if (i == *(DWORD*)0xE61730 || i == *(DWORD*)0xE6172C)
					pDrawViewPort(v6, v5, 1);
				else
					pDrawViewPort(v6, v5, 0);

				if (*(DWORD*)(v6 + 824) == MODEL_PLAYER)
				{
					CreateBattleCastleCharacter_Visual(v6, v5);

					for (int n = 0; n < 400; ++n)
					{
						DWORD ViewPortAddr = pGetPreviewStruct(pPreviewThis(), n);

						DWORD ViewportAddress = ((DWORD(__thiscall*)(void*, DWORD))0x0096A4C0)(((void* (*)())0x00402BC0)(), n);

						ObjectPreview* Object = &*(ObjectPreview*)(ViewportAddress);

						if (!ViewportAddress)
						{
							continue;
						}

						if (*(BYTE*)(ViewportAddress + 0x30C) == 0)
						{
							continue;
						}

						if (ViewPortAddr)
						{
							if (*(BYTE*)(ViewPortAddr + 0x30C) == 0)
							{
								continue;
							}

							if (*(BYTE*)(ViewPortAddr + 0x320) == 1) //Check User
							{
								int index = *(WORD*)(ViewportAddress + 0x7E);

								char* name = (char*)(ViewportAddress + 0x38);

								lpViewObj MuunMount = &*(ObjectPreview*)(oUserPreviewStruct);

								if (!pCheckEffectPlayer((DWORD*)(ViewportAddress + 0x4EC), 28))
								{
									if (pPlayerState > 4)
									{
										for (std::vector<RuneEffectType>::iterator it = gRuneEffect.m_RuneEffectInfo.begin(); it != gRuneEffect.m_RuneEffectInfo.end(); it++)
										{
											if (gRuneEffect.m_RuneEffect[index].cGM != 32)
											{
												if (*(BYTE*)(ViewportAddress + 32) == 3) //pk
												{
													if (it->Index == 0) //FREE
													{
														if (gRuneEffect.m_RuneEffect[index].cVip == 0 && it->Type == 1)
														{
															gRuneEffect.RenderRuneEffect((int)&Object->m_Model, it->TextureIndex, it->Size, it->ColorR, it->ColorG, it->ColorB, it->Speed, it->FloorDistance);
														}
													}

													if (it->Index == 1) //VIP AL1
													{
														if (gRuneEffect.m_RuneEffect[index].cVip == 1 && it->Type == 1)
														{
															gRuneEffect.RenderRuneEffect((int)&Object->m_Model, it->TextureIndex, it->Size, it->ColorR, it->ColorG, it->ColorB, it->Speed, it->FloorDistance);
														}
													}

													if (it->Index == 2) //VIP AL2
													{
														if (gRuneEffect.m_RuneEffect[index].cVip == 2 && it->Type == 1)
														{
															gRuneEffect.RenderRuneEffect((int)&Object->m_Model, it->TextureIndex, it->Size, it->ColorR, it->ColorG, it->ColorB, it->Speed, it->FloorDistance);
														}
													}

													if (it->Index == 3) //VIP AL3
													{
														if (gRuneEffect.m_RuneEffect[index].cVip == 3 && it->Type == 1)
														{
															gRuneEffect.RenderRuneEffect((int)&Object->m_Model, it->TextureIndex, it->Size, it->ColorR, it->ColorG, it->ColorB, it->Speed, it->FloorDistance);
														}
													}
												}
												else
												{
													if (it->Index == 4) //PKLEVEL 6
													{
														if (*(BYTE*)(ViewportAddress + 32) == 6 && it->Type == 1)
														{
															gRuneEffect.RenderRuneEffect((int)&Object->m_Model, it->TextureIndex, it->Size, it->ColorR, it->ColorG, it->ColorB, it->Speed, it->FloorDistance);
														}
													}
												}
											}
										}
									}
								}
								else
								{
									if (pPlayerState > 4)
									{
										for (std::vector<RuneEffectType>::iterator it = gRuneEffect.m_RuneEffectInfo.begin(); it != gRuneEffect.m_RuneEffectInfo.end(); it++)
										{
											if (it->Index == 5) //GAME MASTER
											{
												if (it->Type == 1)
												{
													gRuneEffect.RenderRuneEffect((int)&Object->m_Model, it->TextureIndex, it->Size, it->ColorR, it->ColorG, it->ColorB, it->Speed, it->FloorDistance);
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			continue;
		}
		if (*(BYTE*)(*(DWORD*)0x7BC4F04 + 23) != 10 && *(BYTE*)(*(DWORD*)0x7BC4F04 + 23) != 7)
		{
			if (*(BYTE*)(*(DWORD*)0x7BC4F04 + 23) != 11 && *(BYTE*)(*(DWORD*)0x7BC4F04 + 23) != 8)
			{
				if (*(BYTE*)(*(DWORD*)0x7BC4F04 + 23) != 13 && *(BYTE*)(*(DWORD*)0x7BC4F04 + 23) != 12
					|| *(BYTE*)(v6 + 23) == 13
					|| *(BYTE*)(v6 + 23) == 12)
				{
					goto LABEL_38;
				}
				if (*(WORD*)(*(DWORD*)0x7BC4F04 + 128) == *(WORD*)(v6 + 126))
					*(WORD*)(*(DWORD*)0x7BC4F04 + 128) = -1;
			}
			else
			{
				if (*(BYTE*)(v6 + 23) == 11 || *(BYTE*)(v6 + 23) == 8)
					goto LABEL_38;
				if (*(WORD*)(*(DWORD*)0x7BC4F04 + 128) == *(WORD*)(v6 + 126))
					*(WORD*)(*(DWORD*)0x7BC4F04 + 128) = -1;
			}
		}
		else
		{
			if (*(BYTE*)(v6 + 23) == 10 || *(BYTE*)(v6 + 23) == 7)
				goto LABEL_38;
			if (*(WORD*)(*(DWORD*)0x7BC4F04 + 128) == *(WORD*)(v6 + 126))
				*(WORD*)(*(DWORD*)0x7BC4F04 + 128) = -1;
		}
	}

	if (sub_4DB0E0(*(DWORD*)0xE61E18) || *(DWORD*)0xE61E18 == 31)
	{
		battleCastleInitEtcSetting();
	}
}

void RuneEffect::Init()
{
	SetCompleteHook(0xE9, 0x57D260, &RenderCharacter);
}