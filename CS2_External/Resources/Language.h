#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#pragma once
#include "..\Font\IconsFontAwesome5.h"
#include <iostream>
#include <string>
#include <windows.h>

namespace Lang
{
	inline static void GetCountry(std::string& Country)
	{
		LCID lcid = GetUserDefaultLCID();
		wchar_t CountryW[256];
		GetUserDefaultGeoName(CountryW, sizeof(CountryW) / sizeof(CountryW[0]));

		int len = WideCharToMultiByte(CP_UTF8, 0, CountryW, -1, nullptr, 0, nullptr, nullptr);
		char* String = new char[len];
		WideCharToMultiByte(CP_UTF8, 0, CountryW, -1, String, len, nullptr, nullptr);
		std::string utf8String(String);
		Country = String;

		delete[] String;
		return;
	}
	
	inline struct Global
	{
		inline static const char* Date;
		inline static const char* Author;

		inline static const char* SwitchButton;
		inline static const char* FeatureSettings;
	} Global;

	inline struct ESPtext
	{
		inline static const char* Enable;
		inline static const char* Hotkey;
		inline static const char* AlwaysActive;
		inline static const char* FeatureName;
		inline static const char* Box;
		inline static const char* BoxRounding;
		inline static const char* FilledBox;
		inline static const char* FilledAlpha;
		inline static const char* Skeleton;
		inline static const char* HeadBox;
		inline static const char* EyeRay;
		inline static const char* HealthBar;
		inline static const char* Weapon;
		inline static const char* Distance;
		inline static const char* PlayerName;
		inline static const char* SnapLine;
		inline static const char* LinePosList;
		inline static const char* VisCheck;
		inline static const char* Preview;
		inline static const char* CollapseHead;
		inline static const char* Penis;
		inline static const char* PenisLength;
		inline static const char* PenisSize;
		inline static const char* MultiColor;
		inline static const char* MultiColTip;
		inline static const char* Outline;
		inline static const char* BoxType;
		inline static const char* HealthNum;
		inline static const char* Ammo;
		inline static const char* ScopedESP;
		inline static const char* ShowArmorBar;
		inline static const char* ArmorNum;
		inline static const char* RenderDistance;

		inline static const char* BoxType_Normal;
		inline static const char* BoxType_Edge;
		inline static const char* BoxType_Corner;
		inline static const char* BarType_Top;
		inline static const char* BarType_Vertical;
		inline static const char* HeadBoxType_Normal;
		inline static const char* HeadBoxType_Flat;
		inline static const char* LinePos_1;
		inline static const char* LinePos_2;
		inline static const char* LinePos_3;
	} ESPtext;

	inline struct AimbotText
	{
		inline static const char* Enable;
		inline static const char* FeatureName;
		inline static const char* HotKeyList;
		inline static const char* Toggle;
		inline static const char* DrawFov;
		inline static const char* VisCheck;
		inline static const char* JumpCheck;
		inline static const char* FovSlider;
		inline static const char* FovMinSlider;
		inline static const char* SmoothSlider;
		inline static const char* BoneList;
		inline static const char* SprayBoneList;
		inline static const char* Tip;
		inline static const char* ScopeOnly;
		inline static const char* AimLock;
		inline static const char* AutoShot;
		inline static const char* BulletSlider;
		inline static const char* IgnoreFlash;
		inline static const char* Ragebot;

		inline static const char* Bone_1;
		inline static const char* Bone_2;
		inline static const char* Bone_3;
		inline static const char* Bone_4;
	} AimbotText;

	inline struct RCStext
	{
		inline static const char* Toggle;
		inline static const char* Yaw;
		inline static const char* Pitch;
	} RCStext;

	inline struct RadarText
	{
		inline static const char* Toggle;
		inline static const char* FeatureName;
		inline static const char* StyleList;
		inline static const char* CustomCheck;
		inline static const char* CrossLine;
		inline static const char* SizeSlider;
		inline static const char* ProportionSlider;
		inline static const char* RangeSlider;
		inline static const char* AlphaSlider;

		inline static const char* Style_1;
		inline static const char* Style_2;
		inline static const char* Style_3;
	} RadarText;

	inline struct TriggerText
	{
		inline static const char* Enable;
		inline static const char* FeatureName;
		inline static const char* HotKeyList;
		inline static const char* Toggle;
		inline static const char* ScopeOnly;
		inline static const char* IgnoreFlash;
		inline static const char* DelaySlider;
		inline static const char* FakeShotSlider;
	} TriggerText;

	inline struct CrosshairsText
	{
		inline static const char* Toggle;
		inline static const char* FeatureName;
		inline static const char* PresetList;
		inline static const char* ColorEditor;
		inline static const char* Dot;
		inline static const char* DotSizeSlider;
		inline static const char* Outline;
		inline static const char* Crossline;
		inline static const char* hLengthSlider;
		inline static const char* vLengthSilder;
		inline static const char* GapSlider;
		inline static const char* ThicknessSlider;
		inline static const char* tStyle;
		inline static const char* Circle;
		inline static const char* RadiusSlider;
		inline static const char* TargetCheck;
		inline static const char* TeamCheck;
	} CrosshairsText;

	inline struct MiscText
	{
		inline static const char* FeatureName;
		inline static const char* ThemeList;
		inline static const char* StyleList;
		inline static const char* HeadshotLine;
		inline static const char* SpecCheck;
		inline static const char* NoFlash;
		inline static const char* FastStop;
		inline static const char* HitSound;
		inline static const char* bmbTimer;
		inline static const char* SpecList;
		inline static const char* Bhop;
		inline static const char* Watermark;
		inline static const char* CheatList;
		inline static const char* TeamCheck;
		inline static const char* AntiRecord;
		inline static const char* MoneyService;
		inline static const char* ShowCashSpent;
		inline static const char* EnemySensor;
		inline static const char* RadarHack;
		inline static const char* NoSmoke;
		inline static const char* SmokeColor;
		inline static const char* fovchanger;
		inline static const char* ForceScope;
		inline static const char* FlashImmunity;
		inline static const char* NightMode;
		inline static const char* Alpha;
		inline static const char* JumpThrow;
		
		inline static const char* FakeDuck;

		inline static const char* LanguageList;

		inline static const char* VisCheckDisable;
	} MiscText;

	inline struct ConfigText
	{
		inline static const char* FeatureName;
		inline static const char* Load;
		inline static const char* Save;
		inline static const char* Delete;
		inline static const char* Reset;
		inline static const char* Create;
		inline static const char* OpenFolder;
		inline static const char* SeparateLine;
		inline static const char* MyConfigs;
		inline static const char* AuthorName;
		inline static const char* ConfigName;

		inline static const char* SafeMode;
		inline static const char* fpsCap;
		inline static const char* SafeModeHoveredTip;
	} ConfigText;

	inline struct ReadMeText
	{
		inline static const char* FeatureName;
		inline static const char* LastUpdate;
		inline static const char* SourceButton;
		inline static const char* DiscordButton;
		inline static const char* OffsetsTitle;
	} ReadMeText;

	inline void English()
	{
		Global.Date = u8"None";
		Global.Author = u8"None";

		Global.SwitchButton = u8"Enable";
		Global.FeatureSettings = u8"Settings";

		// ESP
		ESPtext.Enable =u8"启用 ESP";
		ESPtext.Hotkey = u8"热键";
		ESPtext.AlwaysActive = u8"总是开启";
		ESPtext.FeatureName = u8" ESP";
		ESPtext.Box = u8"边框";
		ESPtext.BoxRounding = u8"圆角度: ";
		ESPtext.FilledBox = u8"填充方框";
		ESPtext.FilledAlpha = u8"填充方框透明";
		ESPtext.Skeleton = u8"骨骼";
		ESPtext.HeadBox = u8"头部方框";
		ESPtext.EyeRay = u8"视线";
		ESPtext.HealthBar = u8"生命值";
		ESPtext.Weapon = u8"武器";
		ESPtext.Distance = u8"距离";
		ESPtext.PlayerName = u8"玩家名";
		ESPtext.SnapLine = u8"射线";
		ESPtext.LinePosList = u8"射线位置: ";
		ESPtext.VisCheck = u8"可视检查";
		ESPtext.Preview = u8"预览窗口";
		ESPtext.CollapseHead = u8"SexyESP";
		ESPtext.Penis = u8"鸡巴";
		ESPtext.PenisLength = u8"长度";
		ESPtext.PenisSize = u8"大小";
		ESPtext.MultiColor = u8"Multi-Color";
		ESPtext.MultiColTip = u8"Only work when the box has non-rounded corners.";
		ESPtext.Outline = u8"轮廓线";
		ESPtext.BoxType = u8"方框样式:";
		ESPtext.HealthNum = u8"生命值数字";
		ESPtext.Ammo = u8"弹药";
		ESPtext.ScopedESP = u8"开镜状态";
		ESPtext.ShowArmorBar = u8"护甲值";
		ESPtext.ArmorNum = u8"护甲值数字";
		ESPtext.RenderDistance = u8"最大透视距离: ";

		ESPtext.BoxType_Normal = u8"常规";
		ESPtext.BoxType_Edge = u8"动态";
		ESPtext.BoxType_Corner = u8"四角";
		ESPtext.LinePos_1 = u8"顶部";
		ESPtext.LinePos_2 = u8"中心";
		ESPtext.LinePos_3 = u8"底部";

		// Aimbot
		AimbotText.Enable = u8"启用自瞄";
		AimbotText.FeatureName = u8" Aimbot";
		AimbotText.HotKeyList = u8"热键   ";
		AimbotText.Toggle = u8"开关模式";
		AimbotText.DrawFov = u8"绘制FOV";
		AimbotText.VisCheck = u8"仅可视";
		AimbotText.JumpCheck = u8"跳跃检查";
		AimbotText.FovSlider = u8"FOV: ";
		AimbotText.FovMinSlider = u8"最小FOV: ";
		AimbotText.SmoothSlider = u8"平滑度: ";
		AimbotText.BoneList = u8"命中部位";
		AimbotText.SprayBoneList = u8"扩散";
		AimbotText.Tip = u8"Aimbot will not work while the menu is opened";
		AimbotText.ScopeOnly = u8"仅开镜";
		AimbotText.AimLock = u8"锁定瞄准";
		AimbotText.AutoShot = u8"自动射击";
		AimbotText.BulletSlider = u8"起始弹药数: ";
		AimbotText.IgnoreFlash = u8"无视闪光 ";
		AimbotText.Ragebot = u8"Ragebot";

		// RCS
		RCStext.Toggle = u8"后坐控制";
		RCStext.Yaw = u8"水平阈值: ";
		RCStext.Pitch = u8"垂直阈值: ";

		// Radar
		RadarText.Toggle = u8"启用雷达";
		RadarText.FeatureName = u8" Radar";
		RadarText.StyleList = u8"雷达样式";
		RadarText.CustomCheck = u8"自定义参数";
		RadarText.CrossLine = u8"十字线";
		RadarText.SizeSlider = u8"目标大小:";
		RadarText.ProportionSlider = u8"缩放:";
		RadarText.RangeSlider = u8"范围:";
		RadarText.AlphaSlider = u8"Window Background Alpha:";

		// Triggerbot
		TriggerText.Enable = u8"启用扳机";
		TriggerText.FeatureName = u8" Triggerbot";
		TriggerText.HotKeyList = u8"热键   ";
		TriggerText.Toggle = u8"总是开启";
		TriggerText.ScopeOnly = u8"仅开镜";
		TriggerText.IgnoreFlash = u8"无视闪光";
		TriggerText.DelaySlider = u8"射击延迟:";
		TriggerText.FakeShotSlider = u8"射击持续时间:";

		// Crosshairs
		CrosshairsText.Toggle = u8"启用准星";
		CrosshairsText.FeatureName = u8" Crosshairs";
		CrosshairsText.PresetList = u8"预设";
		CrosshairsText.ColorEditor = u8"准星颜色";
		CrosshairsText.Dot = u8"中心点";
		CrosshairsText.DotSizeSlider = u8"中心点大小:";
		CrosshairsText.Outline = u8"轮廓线";
		CrosshairsText.Crossline = u8"十字线";
		CrosshairsText.hLengthSlider = u8"水平长度:";
		CrosshairsText.vLengthSilder =u8"垂直长度:";
		CrosshairsText.GapSlider = u8"间距:";
		CrosshairsText.ThicknessSlider = u8"粗细:";
		CrosshairsText.tStyle = u8"T型准星";
		CrosshairsText.Circle = u8"圆形";
		CrosshairsText.RadiusSlider = u8"圆圈半径:";
		CrosshairsText.TargetCheck = u8"瞄准变色";
		CrosshairsText.TeamCheck = u8"队伍检查";

		// Misc 
		MiscText.FeatureName = u8" Misc";
		MiscText.ThemeList = u8"主题色       ";
		MiscText.StyleList = u8"样式";
		MiscText.HeadshotLine = u8"爆头线";
		MiscText.SpecCheck = u8"死后保持运行";
		MiscText.NoFlash = u8"无视闪光";
		MiscText.FastStop = u8"快速急停";
		MiscText.HitSound = u8"命中音效 ";
		MiscText.bmbTimer = u8"C4信息";
		MiscText.SpecList = u8"观战列表";
		MiscText.Bhop = u8"连跳";
		MiscText.Watermark = u8"水印";
		MiscText.CheatList = u8"作弊列表";
		MiscText.TeamCheck = u8"队伍检查";
		MiscText.AntiRecord = u8"防止截屏";
		MiscText.MoneyService = u8"金钱揭示";
		MiscText.ShowCashSpent = u8"显示花费";
		MiscText.EnemySensor = u8"发光";
		MiscText.RadarHack = u8"雷达透视";
		MiscText.FastStop = u8"急停";
		MiscText.VisCheckDisable = u8"Visible Check DISABLED";
		MiscText.NoSmoke = u8"无视烟雾";
		MiscText.SmokeColor = u8"烟雾颜色";
		MiscText.fovchanger = u8"Fov 修改: ";
		MiscText.ForceScope = u8"强制开镜";
		MiscText.FlashImmunity = u8"闪光免疫: ";
		MiscText.NightMode = u8"夜间模式";
		MiscText.Alpha = u8"透明度: ";
		MiscText.JumpThrow = u8"自动跳投";

		MiscText.FakeDuck = u8"Fake Duck";

		MiscText.LanguageList = u8"Language";

		// Config Menu
		ConfigText.FeatureName = u8"Config Loader";
		ConfigText.MyConfigs = u8"配置列表";
		ConfigText.Load = u8"加载选中";
		ConfigText.Save = u8"保存选中";
		ConfigText.Delete = u8"删除选中";
		ConfigText.Reset = u8"重置配置";
		ConfigText.Create = u8"创建";
		ConfigText.OpenFolder = u8"打开文件夹";
		ConfigText.SeparateLine = u8"创建配置";
		ConfigText.AuthorName = u8"作者信息";
		ConfigText.ConfigName = u8"配置名称";

		ConfigText.SafeMode = u8"Safe Mode";
		ConfigText.fpsCap = u8"帧率限制: ";
		ConfigText.SafeModeHoveredTip = u8"Disable all unsafe functions that modify game's memory";

		// Readme Menu
		ReadMeText.FeatureName = u8" README";
		ReadMeText.LastUpdate = u8"Last update: ";
		ReadMeText.SourceButton = u8"Source Code";
		ReadMeText.DiscordButton = u8"Join Discord";
		ReadMeText.OffsetsTitle = u8"Offsets:";
		return;
	}


}
