#include "stdafx.h"
#include "..\..\Util\CCRC32.H"
#include "CustomGloves.h"
#include "CustomItem.h"
#include "CustomJewel.h"
#include "CustomMessage.h"
#include "CustomMonster.h"
#include "CustomNpcName.h"
#include "CustomWing.h"
#include "CustomWIngEffect.h"
#include "CustomEffectDynamic.h"
#include "SmokeEffect.h"
#include "ThemidaSDK.h"
#include "CustomFog.h" 
#include "CustomCrossBow.h"
#include "CustomBuffIcon.h"
#include "CustomCloak.h"
#include "CustomEarthQuakeSkill.h"
#include "CustomMonsterEffect.h"
#include "CustomMonsterGlow.h"
#include "CustomPet.h"
#include "CustomPetEffect.h"
#include "CustomPetEffectDynamic.h"
#include "CustomPetGlow.h"
#include "CustomRemoveExcGlow.h"
#include "ItemManager.h"
#include "ItemTooltip.h"
#include "CustomItemPosition.h"
#include "CustomModelEffect.h"
#include "EventEntryLevel.h"
#include "CustomServerInfo.h"
#include "CustomMap.h"
#include "RuneEffect.h"
#include "ItemPrice.h"
#include "CustomEventTimeText.h"
#include "CustomCommandInfo.h"
#include "CustomFlag.h"

struct MAIN_FILE_INFO
{
	BYTE LauncherType; 
	char LauncherName[32];
	char CustomerName[32];
	char IpAddress[32];
	WORD IpAddressPort;
	char ClientVersion[8];
	char ClientSerial[17];
	char WindowName[32];
	char ScreenShotPath[50];
	char ClientName[32];
	char PluginName[32];
	char PluginName2[32];
	char PluginName3[32];
	char PluginName4[32];
	char PluginName5[32];
	DWORD ClientCRC32;
	DWORD PluginCRC32;
	DWORD Plugin2CRC32;
	DWORD Plugin3CRC32;
	DWORD Plugin4CRC32;
	DWORD Plugin5CRC32;
	DWORD HelperActiveAlert;
	DWORD HelperActiveLevel;
	DWORD DWMaxAttackSpeed;
	DWORD DKMaxAttackSpeed;
	DWORD FEMaxAttackSpeed;
	DWORD MGMaxAttackSpeed;
	DWORD DLMaxAttackSpeed;
	DWORD SUMaxAttackSpeed;
	DWORD RFMaxAttackSpeed;
	DWORD ReconnectTime;
	DWORD Language;
	DWORD ReduceMemory;
	DWORD SystemFPS;
	DWORD CameraType;
	DWORD ServerTime;
	DWORD MaxPartyMembers;
	DWORD ShowInfoWindowedMode;
	DWORD ShowInfoWindowedModeType;
	DWORD RemoveClass;
	DWORD RankUserType; 
	DWORD CsSkill; 
	DWORD PrintLogo;
	DWORD CustomStoreEnableJoB;
	DWORD CustomStoreEnableJoS;
	DWORD CustomStoreEnableJoC;
	DWORD CustomStoreEnableCoin1;
	DWORD CustomStoreEnableCoin2;
	DWORD CustomStoreEnableCoin3;
	DWORD CustomOffStoreEnable;
	DWORD DisablePartyHpBar;
	DWORD RankUserShowOverHead;
	DWORD RankUserOnlyOnSafeZone;
	DWORD RankUserShowReset;
	DWORD RankUserShowMasterReset;
	DWORD RankUserNeedAltKey;
	DWORD ActiveInvasion;
	DWORD CustomOptionPanel;
	DWORD ItemTooltipDrop;
	DWORD ItemTooltipDropType;
	DWORD AlwaysPlayerShowName;
	DWORD PlayerShowGuildLogo;
	DWORD RuneEffect;
	DWORD ItemTooltipUpgrade;
	DWORD InventoryUpgrade;
	DWORD CustomInterfaceType;
	DWORD ScaleWidescreen;
	DWORD ScaleItem;
	DWORD SelectServerType;
	DWORD SelectCharacterType;
	DWORD SelectCharacterSystem;
	DWORD SelectCharacterAnimation;
	DWORD DisableCustomClaws;
	DWORD DisableCustomBow;
	DWORD DisableCustomCloack;
	DWORD DisableCustomPosition;
	DWORD DisableCustomPet;
	DWORD DisableAdvance;

	DWORD DisableTree;
	DWORD DisableReflectEffect;
	DWORD DisableEffectPlus15;
	DWORD DisableGens;
	DWORD DisableTabMap;
	DWORD DisableBattleZoneWindow;
	DWORD DisableMoveWindow;
	DWORD DisableBCDSCCMaster;
	DWORD Disable380MixChaosMachine;
	DWORD DisableHelper;
	DWORD DisableClickEffect;
	DWORD DisableCashShopKeyX;
	DWORD DisableWCoinCCashShop;
	DWORD DisableWCoinPCashShop;
	DWORD DisableWCoinGCashShop;
	DWORD DisableSocketInvetory;
	DWORD DisableAncientInventory;
	DWORD DisableRepeirInInventory;
	DWORD DisableButtonOpenStore;
	DWORD DisableButtonInventoryExt;
	DWORD DisableButtonQuestInStats;
	DWORD DisableButtonPetsInStats;
	DWORD DisableButtonSkillMaster;
	DWORD DisableButtonVaultExt;
	DWORD DisableBlueEyeEffect;
	DWORD DisableFlareGlovesEffect;
	DWORD DisableGlowMuSignEffect;
	DWORD DisableWebzenChatCommand;
	DWORD DiscordRPCSwitch;
	DWORD CustomMenuSwitch;
	DWORD CustomMenuType;
	DWORD m_SaveLoginBox;
	DWORD m_CreateAccount;
	DWORD CustomMoveParty;
	DWORD ButtonClearinv;
	DWORD ChangeCharInfo;
	DWORD EnableEventTimeButton;
	DWORD JewelBankSwitch;
	DWORD EnableLuckySpinV2Button;
	DWORD EnableCustomXShopButton;
	DWORD EnableVipShop;
	DWORD VipTypes;
	DWORD EnableVipShopButton;
	DWORD SkillTreeType;
	DWORD QuickMasterButton;
	DWORD EnableCommandButton;
	DWORD EnableAntilagSystemButton;
	DWORD EnableDailyRewardButton;
	DWORD EnableCustomFlagButton;
	DWORD EnableCustomSkinButton;
	DWORD EnableCustomButton1;
	DWORD EnableCustomButton2;
	DWORD EnableCustomRanking;
	DWORD EnableCustomButton3;
	DWORD EnableCustomButton4;
	DWORD EnableCustomButton5;
	DWORD RankingShowItems;
	char APPLICATION_ID[32];
	char state[32];
	char details[32];
	char largeImageKey[32];
	char largeImageText[32];
	char smallImageKey[32];
	char smallImageText[32];
	int m_BloodCastleEntryLevelCommon[7][2];
	int m_BloodCastleEntryLevelSpecial[7][2];
	int m_DevilSquareEntryLevelCommon[6][2];
	int m_DevilSquareEntryLevelSpecial[6][2];
	int m_ChaosCastleEntryLevelCommon[6][2];
	int m_ChaosCastleEntryLevelSpecial[6][2];
	int m_KalimaEntryLevelCommon[7][2];
	int m_KalimaEntryLevelSpecial[7][2];
	int m_IllusionTempleEntryLevelMin[5];
	int m_IllusionTempleEntryLevelMax[5];
	CUSTOM_MESSAGE_INFO EngCustomMessageInfo[MAX_CUSTOM_MESSAGE];
	CUSTOM_MESSAGE_INFO PorCustomMessageInfo[MAX_CUSTOM_MESSAGE];
	CUSTOM_MESSAGE_INFO SpnCustomMessageInfo[MAX_CUSTOM_MESSAGE];
	CUSTOMMONSTER_DATA CustomMonsters[MAX_CUSTOMMONSTER];
	BOSSCLASS_DATA CustomBossClass[MAX_BOSSCLASS];
	NPCNAME_DATA CustomNPCName[MAX_CUSTOM_NPCNAME];
	CUSTOM_ITEM_INFO CustomItemInfo[MAX_CUSTOM_ITEM];
	CUSTOM_JEWEL_INFO CustomJewelInfo[MAX_CUSTOM_JEWEL];
	CUSTOM_WING_INFO CustomWingInfo[MAX_CUSTOM_WING];
	CUSTOM_WING_EFFECT_INFO CustomWingEffectInfo[MAX_CUSTOM_WING_EFFECT];
	DYNAMIC_WING_EFFECT_INFO DynamicWingEffectInfo[MAX_DYNAMIC_WING_EFFECT];
	CUSTOM_SMOKEEFFECT CustomSmokeEffect[MAX_SMOKE_ITEMS];
	CUSTOM_BOW_INFO CustomBowInfo[MAX_CUSTOM_BOW];
	CUSTOM_RF_GLOVES CustomGloves[MAX_CUSTOM_GLOVES];
	RenderTooltipBuff m_TooltipTRSDataEng[256];
	CUSTOMCLOAK_DATA m_CustomCloak[MAX_CUSTOMCLOAK];
	HORSE_EARTH_QUAKE m_EarthQuake[MAX_EARTH_QUAKE];
	xMonsterEffect m_CustomMonsterEffect[MAX_EFFECT_MONSTER];
	CUSTOM_MONSTERGLOW_INFO m_CustomMonsterGlow[MAX_CUSTOM_MONSTERGLOW];
	CUSTOM_GLOW_INFO m_CustomMonsterbrightness[MAX_CUSTOM_MONSTERGLOW];
	CUSTOM_PET_INFO CustomPetInfo[MAX_PET_ITEM];
	PET_EFFECT_CUSTOM m_CustomPetCEffect[MAX_PET_EFFECT_STATIC];
	PET_DYNAMIC_CUSTOM m_DynamicPetEffect[MAX_PET_EFFECT_DYNAMIC];
	RENDER_MESH RenderMeshPet[MAX_PET_GLOW];
	JCItemnoGlow m_JCWRemoveGlow[ MAX_NOGLOW ];
	ITEM_INFO m_ItemInfoEx[MAX_ITEM2];
	nInformation m_TRSTooltipData[MaxLine];
	nText m_TRSTooltipText[MaxLine];
	CUSTOM_POSITION_INFO CustomPosition[MAX_POSITION_ITEM];
	CUSTOM_MODEL_EFFECT_INFO m_CustomModelInfo[MAX_MODEL_EFFECT];
	CUSTOM_FOG_INFO CustomFogInfo[MAX_FOG];
	SERVERINFO_DATA m_ServerInfo[MAX_SERVER_CLASS];
	PathMap m_MapInfo[MAX_CUSTOM_MAP];
	RuneEffectType m_RuneEffect[MAX_TYPE_RUNEEFFECT];
	CUSTOM_ITEMPRICE CustomItemPrice[MAX_ITEMPRICE];
	CUSTOM_EVENT_INFO CustomEventInfo[MAX_EVENTTIME];
	CUSTOM_COMMAND_INFO CustomCommandInfo[MAX_CUSTOM_COMMAND];
	CUSTOM_FLAG_INFO CustomFlagInfo[MAX_CUSTOM_FLAG];
};

int _tmain(int argc,_TCHAR* argv[]) // OK
{
	CLEAR_START

	ENCODE_START

	MAIN_FILE_INFO info;

	memset(&info,0,sizeof(info));

	info.LauncherType = GetPrivateProfileInt("MainInfo","LauncherType",0,".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","LauncherName","XTLauncherExecutable",info.LauncherName,sizeof(info.LauncherName),".\\MainInfo.ini");

	info.IpAddressPort = GetPrivateProfileInt("MainInfo","IpAddressPort",44405,".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","CustomerName","",info.CustomerName,sizeof(info.CustomerName),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","IpAddress","",info.IpAddress,sizeof(info.IpAddress),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","ClientVersion","",info.ClientVersion,sizeof(info.ClientVersion),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","ClientSerial","",info.ClientSerial,sizeof(info.ClientSerial),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","WindowName","",info.WindowName,sizeof(info.WindowName),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","ScreenShotPath","",info.ScreenShotPath,sizeof(info.ScreenShotPath),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","ClientName","",info.ClientName,sizeof(info.ClientName),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","PluginName","",info.PluginName,sizeof(info.PluginName),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","PluginName2","",info.PluginName2,sizeof(info.PluginName2),".\\MainInfo.ini");
	
	GetPrivateProfileString("MainInfo","PluginName3","",info.PluginName3,sizeof(info.PluginName3),".\\MainInfo.ini");
	
	GetPrivateProfileString("MainInfo","PluginName4","",info.PluginName4,sizeof(info.PluginName4),".\\MainInfo.ini");
	
	GetPrivateProfileString("MainInfo","PluginName5","",info.PluginName5,sizeof(info.PluginName5),".\\MainInfo.ini");

	info.HelperActiveAlert = GetPrivateProfileInt("HelperInfo","HelperActiveAlert",0,".\\MainInfo.ini");

	info.HelperActiveLevel = GetPrivateProfileInt("HelperInfo","HelperActiveLevel",80,".\\MainInfo.ini");

	info.DWMaxAttackSpeed = GetPrivateProfileInt("CharacterInfo","DWMaxAttackSpeed",65535,".\\MainInfo.ini");

	info.DKMaxAttackSpeed = GetPrivateProfileInt("CharacterInfo","DKMaxAttackSpeed",65535,".\\MainInfo.ini");

	info.FEMaxAttackSpeed = GetPrivateProfileInt("CharacterInfo","FEMaxAttackSpeed",65535,".\\MainInfo.ini");

	info.MGMaxAttackSpeed = GetPrivateProfileInt("CharacterInfo","MGMaxAttackSpeed",65535,".\\MainInfo.ini");

	info.DLMaxAttackSpeed = GetPrivateProfileInt("CharacterInfo","DLMaxAttackSpeed",65535,".\\MainInfo.ini");

	info.SUMaxAttackSpeed = GetPrivateProfileInt("CharacterInfo","SUMaxAttackSpeed",65535,".\\MainInfo.ini");

	info.RFMaxAttackSpeed = GetPrivateProfileInt("CharacterInfo","RFMaxAttackSpeed",65535,".\\MainInfo.ini");

	info.ReconnectTime = GetPrivateProfileInt("ReconnectInfo","ReconnectTime",0,".\\MainInfo.ini");

	info.Language = GetPrivateProfileInt("Language", "Language", 0, ".\\MainInfo.ini");

	info.ReduceMemory = GetPrivateProfileInt("Custom","ReduceMemory",0,".\\MainInfo.ini");

	info.SystemFPS = GetPrivateProfileInt("Custom","SystemFPS",0,".\\MainInfo.ini");

	info.CameraType = GetPrivateProfileInt("Custom", "CameraType", 0, ".\\MainInfo.ini");

	info.ServerTime = GetPrivateProfileInt("Custom","ServerTime",0,".\\MainInfo.ini");

	info.MaxPartyMembers = GetPrivateProfileInt("Custom","MaxPartyMembers",0,".\\MainInfo.ini");

	info.ShowInfoWindowedMode = GetPrivateProfileInt("Custom","ShowInfoWindowedMode",0,".\\MainInfo.ini");

	info.ShowInfoWindowedModeType = GetPrivateProfileInt("Custom","ShowInfoWindowedModeType",0,".\\MainInfo.ini");

	info.RemoveClass = GetPrivateProfileInt("Custom","RemoveClass",0,".\\MainInfo.ini");

	info.RankUserType = GetPrivateProfileInt("Custom","RankUserType",0,".\\MainInfo.ini");

	info.CsSkill = GetPrivateProfileInt("Custom","EnableCsSkillsAllMaps",0,".\\MainInfo.ini");

	info.RankUserShowOverHead = GetPrivateProfileInt("Custom","RankUserShowOverHead",0,".\\MainInfo.ini");

	info.RankUserOnlyOnSafeZone = GetPrivateProfileInt("Custom","RankUserOnlyOnSafeZone",1,".\\MainInfo.ini");

	info.RankUserShowReset = GetPrivateProfileInt("Custom","RankUserShowReset",1,".\\MainInfo.ini");

	info.RankUserShowMasterReset = GetPrivateProfileInt("Custom","RankUserShowMasterReset",1,".\\MainInfo.ini");

	info.RankUserNeedAltKey = GetPrivateProfileInt("Custom","RankUserNeedAltKey",0,".\\MainInfo.ini");

	info.PrintLogo = GetPrivateProfileInt("Custom","PrintLogo",0,".\\MainInfo.ini");

	info.CustomStoreEnableJoB  = GetPrivateProfileInt("Custom","EnableStoreBlessButtom",0,".\\MainInfo.ini");

	info.CustomStoreEnableJoS  = GetPrivateProfileInt("Custom","EnableStoreSoulButtom",0,".\\MainInfo.ini");

	info.CustomStoreEnableJoC  = GetPrivateProfileInt("Custom","EnableStoreChaosButtom",0,".\\MainInfo.ini");

	info.CustomStoreEnableCoin1  = GetPrivateProfileInt("Custom","EnableStoreCoin1Buttom",0,".\\MainInfo.ini");

	info.CustomStoreEnableCoin2  = GetPrivateProfileInt("Custom","EnableStoreCoin2Buttom",0,".\\MainInfo.ini");

	info.CustomStoreEnableCoin3  = GetPrivateProfileInt("Custom","EnableStoreCoin3Buttom",0,".\\MainInfo.ini");

	info.CustomOffStoreEnable  = GetPrivateProfileInt("Custom","EnableOffStoreButtom",0,".\\MainInfo.ini");

	info.DisablePartyHpBar  = GetPrivateProfileInt("Custom","DisablePartyHpBar",0,".\\MainInfo.ini");

	info.ActiveInvasion = GetPrivateProfileInt("Custom", "ActiveInvasion", 0, ".\\MainInfo.ini");

	info.CustomOptionPanel = GetPrivateProfileInt("Custom", "CustomOptionPanel", 0, ".\\MainInfo.ini");

	info.ItemTooltipDrop = GetPrivateProfileInt("Custom", "ItemTooltipDrop", 0, ".\\MainInfo.ini");

	info.ItemTooltipDropType = GetPrivateProfileInt("Custom", "ItemTooltipDropType", 0, ".\\MainInfo.ini");
	
	info.AlwaysPlayerShowName = GetPrivateProfileInt("Custom", "AlwaysPlayerShowName", 0, ".\\MainInfo.ini");
	
	info.PlayerShowGuildLogo = GetPrivateProfileInt("Custom", "PlayerShowGuildLogo", 0, ".\\MainInfo.ini");

	info.RuneEffect = GetPrivateProfileInt("Custom", "RuneEffect", 0, ".\\MainInfo.ini");

	info.ItemTooltipUpgrade = GetPrivateProfileInt("Custom", "ItemTooltipUpgrade", 0, ".\\MainInfo.ini");

	info.InventoryUpgrade = GetPrivateProfileInt("Custom", "InventoryUpgrade", 0, ".\\MainInfo.ini");

	info.EnableVipShop = GetPrivateProfileInt("Custom", "EnableVipShop", 0, ".\\MainInfo.ini");

	info.VipTypes = GetPrivateProfileInt("Custom", "VipTypes", 3, ".\\MainInfo.ini");

	info.CustomMenuSwitch = GetPrivateProfileInt("Custom", "CustomMenuSwitch", 0, ".\\MainInfo.ini");

	info.CustomMenuType = GetPrivateProfileInt("Custom", "CustomMenuType", 0, ".\\MainInfo.ini");

	info.EnableEventTimeButton = GetPrivateProfileInt("Custom", "EnableEventTimeButton", 0, ".\\MainInfo.ini");

	info.JewelBankSwitch = GetPrivateProfileInt("Custom", "EnableJewelBankButton", 0, ".\\MainInfo.ini");

	info.EnableLuckySpinV2Button = GetPrivateProfileInt("Custom", "EnableLuckySpinButton", 0, ".\\MainInfo.ini");

	info.EnableCustomXShopButton = GetPrivateProfileInt("Custom", "EnableCustomXShopButton", 0, ".\\MainInfo.ini");

	info.EnableVipShopButton = GetPrivateProfileInt("Custom", "EnableVipShopButton", 0, ".\\MainInfo.ini");

	info.EnableCommandButton = GetPrivateProfileInt("Custom", "EnableCommandButton", 0, ".\\MainInfo.ini");

	info.EnableDailyRewardButton = GetPrivateProfileInt("Custom", "EnableDailyRewardButton", 0, ".\\MainInfo.ini");

	info.EnableCustomFlagButton = GetPrivateProfileInt("Custom", "EnableCustomFlagButton", 0, ".\\MainInfo.ini");

	info.EnableCustomSkinButton = GetPrivateProfileInt("Custom", "EnableCustomSkinButton", 0, ".\\MainInfo.ini");

	info.EnableCustomButton1 = GetPrivateProfileInt("Custom", "EnableCustomButton1", 0, ".\\MainInfo.ini");

	info.EnableCustomButton2 = GetPrivateProfileInt("Custom", "EnableCustomButton2", 0, ".\\MainInfo.ini");

	info.EnableCustomRanking = GetPrivateProfileInt("Custom", "EnableCustomRanking", 0, ".\\MainInfo.ini");

	info.EnableCustomButton3 = GetPrivateProfileInt("Custom", "EnableCustomButton3", 0, ".\\MainInfo.ini");

	info.EnableCustomButton4 = GetPrivateProfileInt("Custom", "EnableCustomButton4", 0, ".\\MainInfo.ini");

	info.EnableCustomButton5 = GetPrivateProfileInt("Custom", "EnableCustomButton5", 0, ".\\MainInfo.ini");

	info.RankingShowItems = GetPrivateProfileInt("Custom", "RankingType", 0, ".\\MainInfo.ini");

	info.EnableAntilagSystemButton = GetPrivateProfileInt("Custom", "EnableAntilagSystemButton", 0, ".\\MainInfo.ini");

	info.CustomInterfaceType = GetPrivateProfileInt("Custom", "CustomInterfaceType", 0, ".\\MainInfo.ini");

	info.ScaleWidescreen = GetPrivateProfileInt("Custom", "ScaleWidescreen", 0, ".\\MainInfo.ini");

	info.ScaleItem = GetPrivateProfileInt("Custom", "ScaleItem", 0, ".\\MainInfo.ini");

	info.SelectServerType = GetPrivateProfileInt("Custom", "SelectServerType", 0, ".\\MainInfo.ini");

	info.SelectCharacterType = GetPrivateProfileInt("Custom", "SelectCharacterType", 0, ".\\MainInfo.ini");

	info.SelectCharacterSystem = GetPrivateProfileInt("Custom", "SelectCharacterSystem", 0, ".\\MainInfo.ini");

	info.SelectCharacterAnimation = GetPrivateProfileInt("Custom", "SelectCharacterAnimation", 0, ".\\MainInfo.ini");

	info.m_SaveLoginBox = GetPrivateProfileInt("Custom","SavePassLogin",0,".\\MainInfo.ini");

	info.m_CreateAccount = GetPrivateProfileInt("Custom","CreateAccount",0,".\\MainInfo.ini");

	info.CustomMoveParty = GetPrivateProfileInt("Custom", "CustomMoveParty", 0, ".\\MainInfo.ini");

	info.ButtonClearinv = GetPrivateProfileInt("Custom", "ButtonClearinv", 0, ".\\MainInfo.ini");

	info.ChangeCharInfo = GetPrivateProfileInt("Custom", "ChangeCharInfo", 0, ".\\MainInfo.ini");

	info.SkillTreeType = GetPrivateProfileInt("Custom", "MasterSkillTreeType", 0, ".\\MainInfo.ini");

	info.QuickMasterButton = GetPrivateProfileInt("Custom", "QuickMasterButton", 0, ".\\MainInfo.ini");

	info.DisableCustomClaws = GetPrivateProfileInt("Disable", "DisableCustomClaws", 0, ".\\MainInfo.ini");
	info.DisableCustomBow = GetPrivateProfileInt("Disable", "DisableCustomBow", 0, ".\\MainInfo.ini");
	info.DisableCustomCloack = GetPrivateProfileInt("Disable", "DisableCustomCloack", 0, ".\\MainInfo.ini");
	info.DisableCustomPosition = GetPrivateProfileInt("Disable", "DisableCustomPosition", 0, ".\\MainInfo.ini");
	info.DisableCustomPet = GetPrivateProfileInt("Disable", "DisableCustomPet", 0, ".\\MainInfo.ini");
	info.DisableAdvance = GetPrivateProfileInt("Disable", "DisableAdvanceStatus", 0, ".\\MainInfo.ini");
	info.DisableTree = GetPrivateProfileInt("Disable", "DisableTree", 0, ".\\MainInfo.ini");
	info.DisableReflectEffect = GetPrivateProfileInt("Disable", "DisableReflectEffect", 0, ".\\MainInfo.ini");
	info.DisableEffectPlus15 = GetPrivateProfileInt("Disable", "DisableEffectPlus15", 0, ".\\MainInfo.ini");
	info.DisableGens = GetPrivateProfileInt("Disable", "DisableGens", 0, ".\\MainInfo.ini");
	info.DisableTabMap = GetPrivateProfileInt("Disable", "DisableTabMap", 0, ".\\MainInfo.ini");
	info.DisableBattleZoneWindow = GetPrivateProfileInt("Disable", "DisableBattleZoneWindow", 0, ".\\MainInfo.ini");
	info.DisableMoveWindow = GetPrivateProfileInt("Disable", "DisableMoveWindow", 0, ".\\MainInfo.ini");
	info.DisableBCDSCCMaster = GetPrivateProfileInt("Disable", "DisableBCDSCCMaster", 0, ".\\MainInfo.ini");
	info.Disable380MixChaosMachine = GetPrivateProfileInt("Disable", "Disable380MixChaosMachine", 0, ".\\MainInfo.ini");
	info.DisableHelper = GetPrivateProfileInt("Disable", "DisableHelper", 0, ".\\MainInfo.ini");
	info.DisableClickEffect = GetPrivateProfileInt("Disable", "DisableClickEffect", 0, ".\\MainInfo.ini");
	info.DisableCashShopKeyX = GetPrivateProfileInt("Disable", "DisableCashShopKeyX", 0, ".\\MainInfo.ini");
	info.DisableWCoinCCashShop = GetPrivateProfileInt("Disable", "DisableWCoinCCashShop", 0, ".\\MainInfo.ini");
	info.DisableWCoinPCashShop = GetPrivateProfileInt("Disable", "DisableWCoinPCashShop", 0, ".\\MainInfo.ini");
	info.DisableWCoinGCashShop = GetPrivateProfileInt("Disable", "DisableWCoinGCashShop", 0, ".\\MainInfo.ini");
	info.DisableSocketInvetory = GetPrivateProfileInt("Disable", "DisableSocketInvetory", 0, ".\\MainInfo.ini");
	info.DisableAncientInventory = GetPrivateProfileInt("Disable", "DisableAncientInventory", 0, ".\\MainInfo.ini");
	info.DisableRepeirInInventory = GetPrivateProfileInt("Disable", "DisableRepeirInInventory", 0, ".\\MainInfo.ini");
	info.DisableButtonOpenStore = GetPrivateProfileInt("Disable", "DisableButtonOpenStore", 0, ".\\MainInfo.ini");
	info.DisableButtonInventoryExt = GetPrivateProfileInt("Disable", "DisableButtonInventoryExt", 0, ".\\MainInfo.ini");
	info.DisableButtonQuestInStats = GetPrivateProfileInt("Disable", "DisableButtonQuestInStats", 0, ".\\MainInfo.ini");
	info.DisableButtonPetsInStats = GetPrivateProfileInt("Disable", "DisableButtonPetsInStats", 0, ".\\MainInfo.ini");
	info.DisableButtonSkillMaster = GetPrivateProfileInt("Disable", "DisableButtonSkillMaster", 0, ".\\MainInfo.ini");
	info.DisableButtonVaultExt = GetPrivateProfileInt("Disable", "DisableButtonVaultExt", 0, ".\\MainInfo.ini");

	info.DisableBlueEyeEffect = GetPrivateProfileInt("Disable", "DisableBlueEyeEffect", 0, ".\\MainInfo.ini");
	info.DisableFlareGlovesEffect = GetPrivateProfileInt("Disable", "DisableFlareGlovesEffect", 0, ".\\MainInfo.ini");
	info.DisableGlowMuSignEffect = GetPrivateProfileInt("Disable", "DisableGlowMuSignEffect", 0, ".\\MainInfo.ini");

	info.DisableWebzenChatCommand = GetPrivateProfileInt("Disable", "DisableWebzenChatCommand", 0, ".\\MainInfo.ini");

	info.DiscordRPCSwitch = GetPrivateProfileInt("Discord", "DiscordRPCSwitch", 0, ".\\MainInfo.ini");
	GetPrivateProfileString("Discord", "APPLICATION_ID", "", info.APPLICATION_ID, sizeof(info.APPLICATION_ID), ".\\MainInfo.ini");
	GetPrivateProfileString("Discord", "state", "", info.state, sizeof(info.state), ".\\MainInfo.ini");
	GetPrivateProfileString("Discord", "details", "", info.details, sizeof(info.details), ".\\MainInfo.ini");
	GetPrivateProfileString("Discord", "largeImageKey", "", info.largeImageKey, sizeof(info.largeImageKey), ".\\MainInfo.ini");
	GetPrivateProfileString("Discord", "largeImageText", "", info.largeImageText, sizeof(info.largeImageText), ".\\MainInfo.ini");
	GetPrivateProfileString("Discord", "smallImageKey", "", info.smallImageKey, sizeof(info.smallImageKey), ".\\MainInfo.ini");
	GetPrivateProfileString("Discord", "smallImageText", "", info.smallImageText, sizeof(info.smallImageText), ".\\MainInfo.ini");

	if(gCustomMessage.Load("Message.txt") == 0) { system("pause"); return 0; }
	if(gCustomJewel.Load("Custom/CustomJewel.txt") == 0) { system("pause"); return 0; }
	if(gCustomWing.Load("Custom/CustomWing.txt") == 0) { system("pause"); return 0; }
	if(gCustomItem.Load("Custom/CustomItem.txt") == 0) { system("pause"); return 0; }

	gCustomWingEffect.Load("Custom/CustomEffectStatic.txt");

	gDynamicWingEffect.Load("Custom/CustomEffectDynamic.txt");

	if(gSmokeEffect.Load("Custom/CustomSmokeEffect.txt") == 0) { system("pause"); return 0; }
	if(gCustomCrossBow.Load("Custom/CustomBow.txt") == 0) { system("pause"); return 0; }
	if(gCustomGloves.Load("Custom/CustomGloves.txt") == 0) { system("pause"); return 0; }
	if(gCBuffIcon.Load("Custom/CustomBuffIcon.txt") == 0) { system("pause"); return 0; }
	if(gCustomEarthQuake.Load("Custom/CustomEarthQuakeSkill.txt") == 0) { system("pause"); return 0; }
	if(gCloak.Load("Custom/CustomCloak.txt") == 0) { system("pause"); return 0; }
	if(gCustomModelEffect.Load("Custom/CustomModelEffect.txt") == 0) { system("pause"); return 0; }
	if(JCEffectMonster.Load("Custom/CustomMonsterEffect.txt") == 0) { system("pause"); return 0; }
	if(gCustomMonsterGlow.Load("Custom/CustomMonsterGlow.txt") == 0) { system("pause"); return 0; }
	if(gCustomPet2.Load("Custom/CustomPet.txt") == 0) { system("pause"); return 0; }
	if(gCustomCEffectPet.Load("Custom/CustomPetEffectStatic.txt") == 0) { system("pause"); return 0; }
	if(gCustomCEffectDynamicPet.Load("Custom/CustomPetEffectDynamic.txt") == 0) { system("pause"); return 0; }
	if(cRender.Load("Custom/CustomPetGlow.txt") == 0) { system("pause"); return 0; }
	if(JCRemoveGlow.Load("Custom/CustomRemoveGlowItem.txt") == 0) { system("pause"); return 0; }
	if(gItemManager.Load("Item.txt") == 0) { system("pause"); return 0; }
	if(GInfo.Load("Custom/CustomItemToolTip.txt") == 0) { system("pause"); return 0; }
	if(GInfo.Load2("Custom/CustomItemTooltipText.txt") == 0) { system("pause"); return 0; }
	if(gCustomPosition.Load("Custom/CustomItemPosition.txt") == 0) { system("pause"); return 0; }
	if(gMonsters.Load("Custom/CustomMonster.txt") == 0) { system("pause"); return 0; }
	if(gNPCName.Load("Custom/CustomNPCName.txt") == 0) { system("pause"); return 0; }
	if(gCustomFog.Load("Custom/CustomFog.txt") == 0) { system("pause"); return 0; }
	if(gEventEntryLevel.Load("Custom/CustomEventEntryLevel.txt") == 0) { system("pause"); return 0; }
	if(g_ServerInfo.Load("Custom/CustomServerInfo.txt") == 0) { system("pause"); return 0; }
	if (g_pUIMapName.OpenScritp("Custom/CustomMap.txt") == 0) { system("pause"); return 0; }
	if (gRuneEffect.Load("Custom/CustomRuneEffect.txt") == 0) { system("pause"); return 0; }
	if (gItemPrice.Load("Custom/ItemValue.txt") == 0) { system("pause"); return 0; }
	if (gCustomEventTimeText.Load("Common/CustomEventTimeText.txt") == 0) { system("pause"); return 0; }
	if (gCustomCommandInfo.Load("Common/CustomCommandInfo.txt") == 0) { system("pause"); return 0; }
	gCustomFlag.Load("Custom\\CustomFlag.txt");

	memcpy(info.EngCustomMessageInfo,gCustomMessage.m_EngCustomMessageInfo,sizeof(info.EngCustomMessageInfo));

	memcpy(info.PorCustomMessageInfo,gCustomMessage.m_PorCustomMessageInfo,sizeof(info.PorCustomMessageInfo));

	memcpy(info.SpnCustomMessageInfo,gCustomMessage.m_SpnCustomMessageInfo,sizeof(info.SpnCustomMessageInfo));

	memcpy(info.CustomWingEffectInfo, gCustomWingEffect.m_CustomWingEffectInfo, sizeof(info.CustomWingEffectInfo));

	memcpy(info.DynamicWingEffectInfo, gDynamicWingEffect.m_DynamicWingEffectInfo, sizeof(info.DynamicWingEffectInfo));

	memcpy(info.CustomSmokeEffect, gSmokeEffect.m_CustomSmokeEffect, sizeof(info.CustomSmokeEffect));

	memcpy(info.CustomBowInfo, gCustomCrossBow.m_CustomBowInfo, sizeof(info.CustomBowInfo));

	memcpy(info.CustomGloves, gCustomGloves.m_CustomGlovesInfo, sizeof(info.CustomGloves));

	memcpy(info.m_TooltipTRSDataEng, gCBuffIcon.m_TooltipENG, sizeof(info.m_TooltipTRSDataEng));

	memcpy(info.m_EarthQuake, gCustomEarthQuake.m_EarthQuake, sizeof(info.m_EarthQuake));

	memcpy(info.m_CustomCloak, gCloak.m_Cloak, sizeof(info.m_CustomCloak));

	memcpy(info.m_CustomModelInfo, gCustomModelEffect.m_CustomModelEffectInfo, sizeof(info.m_CustomModelInfo));

	memcpy(info.m_CustomMonsterEffect, JCEffectMonster.m_MonsterEffect, sizeof(info.m_CustomMonsterEffect));

	memcpy(info.m_CustomMonsterGlow, gCustomMonsterGlow.m_CustomGlowInfo, sizeof(info.m_CustomMonsterGlow));

	memcpy(info.m_CustomMonsterbrightness, gCustomMonsterGlow.m_CustombrightnessInfo, sizeof(info.m_CustomMonsterbrightness));

	memcpy(info.CustomPetInfo, gCustomPet2.m_CustomPetInfo, sizeof(info.CustomPetInfo));

	memcpy(info.m_CustomPetCEffect, gCustomCEffectPet.m_PetCEffect, sizeof(info.m_CustomPetCEffect));

	memcpy(info.m_DynamicPetEffect, gCustomCEffectDynamicPet.m_PetDynamicCEffect, sizeof(info.m_DynamicPetEffect));

	memcpy(info.RenderMeshPet, cRender.m_RenderMeshPet, sizeof(info.RenderMeshPet));

	memcpy(info.m_JCWRemoveGlow, JCRemoveGlow.m_JCRemoveGlow, sizeof(info.m_JCWRemoveGlow));

	memcpy(info.m_ItemInfoEx, gItemManager.m_ItemInfo, sizeof(info.m_ItemInfoEx));

	memcpy(info.m_TRSTooltipData, GInfo.n_TRSTooltipData, sizeof(info.m_TRSTooltipData));

	memcpy(info.m_TRSTooltipText, GInfo.n_TRSTooltipText, sizeof(info.m_TRSTooltipText));
	
	memcpy(info.CustomPosition, gCustomPosition.m_CustomPositionInfo, sizeof(info.CustomPosition));
	
	memcpy(info.CustomItemInfo,gCustomItem.m_CustomItemInfo,sizeof(info.CustomItemInfo));
	
	memcpy(info.CustomJewelInfo,gCustomJewel.m_CustomJewelInfo,sizeof(info.CustomJewelInfo));
	
	memcpy(info.CustomMonsters, gMonsters.m_Monsters, sizeof(info.CustomMonsters));
	
	memcpy(info.CustomBossClass, gMonsters.m_BossClass, sizeof(info.CustomBossClass));
	
	memcpy(info.CustomNPCName, gNPCName.m_CustomNpcName, sizeof(info.CustomNPCName));
	
	memcpy(info.CustomWingInfo,gCustomWing.m_CustomWingInfo,sizeof(info.CustomWingInfo));

	memcpy(info.CustomFogInfo, gCustomFog.m_CustomFogInfo, sizeof(info.CustomFogInfo));

	memcpy(info.m_BloodCastleEntryLevelCommon,gEventEntryLevel.m_BloodCastleEntryLevelCommon,sizeof(info.m_BloodCastleEntryLevelCommon));
	
	memcpy(info.m_BloodCastleEntryLevelSpecial,gEventEntryLevel.m_BloodCastleEntryLevelSpecial,sizeof(info.m_BloodCastleEntryLevelSpecial));
	
	memcpy(info.m_DevilSquareEntryLevelCommon,gEventEntryLevel.m_DevilSquareEntryLevelCommon,sizeof(info.m_DevilSquareEntryLevelCommon));
	
	memcpy(info.m_DevilSquareEntryLevelSpecial,gEventEntryLevel.m_DevilSquareEntryLevelSpecial,sizeof(info.m_DevilSquareEntryLevelSpecial));
	
	memcpy(info.m_ChaosCastleEntryLevelCommon,gEventEntryLevel.m_ChaosCastleEntryLevelCommon,sizeof(info.m_ChaosCastleEntryLevelCommon));
	
	memcpy(info.m_ChaosCastleEntryLevelSpecial,gEventEntryLevel.m_ChaosCastleEntryLevelSpecial,sizeof(info.m_ChaosCastleEntryLevelSpecial));
	
	memcpy(info.m_KalimaEntryLevelCommon,gEventEntryLevel.m_KalimaEntryLevelCommon,sizeof(info.m_KalimaEntryLevelCommon));
	
	memcpy(info.m_KalimaEntryLevelSpecial,gEventEntryLevel.m_KalimaEntryLevelSpecial,sizeof(info.m_KalimaEntryLevelSpecial));
	
	memcpy(info.m_IllusionTempleEntryLevelMin,gEventEntryLevel.m_IllusionTempleEntryLevelMin,sizeof(info.m_IllusionTempleEntryLevelMin));
	
	memcpy(info.m_IllusionTempleEntryLevelMax,gEventEntryLevel.m_IllusionTempleEntryLevelMax,sizeof(info.m_IllusionTempleEntryLevelMax));

	memcpy(info.m_ServerInfo, g_ServerInfo.m_data, sizeof(info.m_ServerInfo));

	memcpy(info.m_MapInfo, g_pUIMapName.m_MapInfo, sizeof(info.m_MapInfo));

	memcpy(info.m_RuneEffect, gRuneEffect.m_RuneEffect, sizeof(info.m_RuneEffect));

	memcpy(info.CustomItemPrice, gItemPrice.m_ItemPrice, sizeof(info.CustomItemPrice));

	memcpy(info.CustomEventInfo, gCustomEventTimeText.m_CustomEventInfo, sizeof(info.CustomEventInfo));

	memcpy(info.CustomCommandInfo, gCustomCommandInfo.m_CustomCommandInfo, sizeof(info.CustomCommandInfo));

	memcpy(info.CustomFlagInfo, gCustomFlag.m_CustomFlagInfo, sizeof(info.CustomFlagInfo));

	CCRC32 CRC32;

	if(CRC32.FileCRC(info.ClientName,&info.ClientCRC32,1024) == 0)
	{
		info.ClientCRC32 = 0;
	}

	if(CRC32.FileCRC(info.PluginName,&info.PluginCRC32,1024) == 0)
	{
		info.PluginCRC32 = 0;
	}

	if(CRC32.FileCRC(info.PluginName2,&info.Plugin2CRC32,1024) == 0)
	{
		info.Plugin2CRC32 = 0;
	}

	if(CRC32.FileCRC(info.PluginName3,&info.Plugin3CRC32,1024) == 0)
	{
		info.Plugin3CRC32 = 0;
	}

	if(CRC32.FileCRC(info.PluginName4,&info.Plugin4CRC32,1024) == 0)
	{
		info.Plugin4CRC32 = 0;
	}

	if(CRC32.FileCRC(info.PluginName5,&info.Plugin5CRC32,1024) == 0)
	{
		info.Plugin5CRC32 = 0;
	}

	DWORD MainDllCRC;
	DWORD PlayerBmdCRC;
	DWORD SkillBmdCRC;
	DWORD ItemBmdCRC;

	if(CRC32.FileCRC("Main.dll",&MainDllCRC,1024) == 0)
	{
		MainDllCRC = 0;
	}

	if(CRC32.FileCRC("Player.bmd",&PlayerBmdCRC,1024) == 0)
	{
		PlayerBmdCRC = 0;
	}

	if(CRC32.FileCRC("Skill_Eng.bmd",&SkillBmdCRC,1024) == 0)
	{
		SkillBmdCRC = 0;
	}

	if(CRC32.FileCRC("Item_Eng.bmd",&ItemBmdCRC,1024) == 0)
	{
		ItemBmdCRC = 0;
	}

	std::ofstream fout(".\\CRCInfo.txt", std::ios_base::out | std::ios_base::trunc);

	fout << "AntihackDllCRC = 0x" << std::hex << (DWORD)info.PluginCRC32 <<std::endl;
	fout << "MainDllCRC = 0x" << std::hex << (DWORD)MainDllCRC <<std::endl;
	fout << "MainExeCRC = 0x" << std::hex << (DWORD)info.ClientCRC32 <<std::endl;
	fout << "PlayerBmdCRC = 0x" << std::hex << (DWORD)PlayerBmdCRC <<std::endl;
	fout << "SkillBmdCRC = 0x" << std::hex << (DWORD)SkillBmdCRC <<std::endl;
	fout << "ItemBmdCRC = 0x" << std::hex << (DWORD)ItemBmdCRC <<std::endl;

	fout.close();

	for(int n=0;n < sizeof(MAIN_FILE_INFO);n++)
	{
		((BYTE*)&info)[n] ^= (BYTE)(0xDA^LOBYTE(n));
		((BYTE*)&info)[n] -= (BYTE)(0x95^HIBYTE(n));
	}

	system("mkdir \"Data\\Local\\\"");
	HANDLE file = CreateFile(".\\Data\\Local\\Main.bmd",GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_ARCHIVE,0);

	if(file == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	DWORD OutSize = 0;

	if(WriteFile(file,&info,sizeof(MAIN_FILE_INFO),&OutSize,0) == 0)
	{
		CloseHandle(file);
		return 0;
	}

	puts("Archivos Generados Correctamente!!!");

	system("pause");

	CloseHandle(file);

	ENCODE_END

	CLEAR_END

	return 0;
}
