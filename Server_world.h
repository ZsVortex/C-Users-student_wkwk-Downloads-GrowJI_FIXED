#pragma once
#include "stdafx.h"
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <locale>
#include <regex>
#include <sstream>
#include <sstream>
#include <stdexcept>
#include <conio.h>
#include <string>
#include <vector>
#include <experimental/filesystem>
#include "json.hpp"
#include "enet/enet.h"
#ifdef _WIN32
#include <windows.h>
typedef __int8 __int8_t;
typedef __int16 __int16_t;
#elif __APPLE__ || __linux__
typedef unsigned int DWORD;
#endif
typedef unsigned char BYTE;

struct Crystal
{
	string name;
	int probability;

	Crystal(const string s, const int p) : name(s), probability(p)
	{
	}
};

struct WorldItem
{
	__int16_t foreground = 0;
	__int16_t background = 0;
	int displayblock = 0;
	int breakLevel = 0;
	long long int breakTime = 0;
	string sign = "";
	int display1 = 0;
	int display2 = 0;
	int display3 = 0;
	int display4 = 0;
	bool water = false;
	bool rotatedLeft = false;
	bool ArtTrue = false;
	bool fire = false;
	bool glue = false;
	bool red = false;
	bool green = false;
	bool flipped = false;
	bool blue = false;
	/*Vip Entrance*/
	bool VipPublic = false;
	int displayBlock = 0;
	int gravity = 100;
	int intdata = 0;
	bool isInverted = false;
	bool isRotating = false;
	string label = "";
	string destWorld = "";
	string destId = "";
	string currId = "";
	string password = "";
	string text = "";
	bool isOpened = false;
	string hmonitor_owner = "";
	bool activated = false;
	string worldinput = "";
	string doorid = "";
	bool activeWeather = false;
	int yellowGems = 0;
	int blueGems = 0;
	int redGems = 0;
	int greenGems = 0;
	int purpleGems = 0;
	bool dropCollectBlocked = false;

	int clothHair = 0;
	int clothHead = 0;
	int clothMask = 0;
	int clothHand = 0;
	int clothNeck = 0;
	int clothShirt = 0;
	int clothPants = 0;
	int clothFeet = 0;
	int clothBack = 0;
	/*magplant*/
	int mid = 0;
	int mc = 0;
	bool rm = false;

	/*vending*/
	bool destroy = false;
	int vdraw = 0;
	int vid = 0;
	int vprice = 0;
	int vcount = 0;
	int breakstate = 0;
	int breakbotstate = 0;
	int placestate = 0;

	/*hmonitor*/
	string monitorname = "";
	bool monitoronline = false;

	/*entrance*/
	bool opened = false;
	/*seedai*/
	bool spliced = false;
	int growtime = 0;
	int fruitcount = 0;
};

struct DroppedItem
{
	int id;
	int uid;
	int count;
	string droppedby;
	float x;
	string madeby;
	float y;
};

struct WorldInfo
{
	int width = 100;
	int height = 60;
	string name = "TEST";
	int ownerID = 0;
	bool areLogsEnabled = false;
	WorldItem* items;

	vector<string> viplist;
	int droppedCount = 0;
	string owner = "";
	int entrylevel = 1;
	float rating = 0;
	string category = "None";
	vector<DroppedItem> droppedItems;
	int droppedItemUid = 0;
	int geigerX = 0;
	int geigerY = 0;
	bool isPublic = false;
	bool allowMod = false;
	bool DisableDrop = false;
	bool isEvent = true;
	bool noclip = false;
	int weather = 4;
	bool allowDropTakeAll = true;
	bool ice = false;
	bool land = false;
	bool vol = false;
	int geiger_locX = 64;
	int geiger_locY = 64;
	vector<string> accessed;
	int openvippublic = 0;
	bool silence = false;
	bool rainbow = false;
	string ownerDisplayName = "";
	string itemsdropped = "";
	bool minimod = false;
	bool isPineappleGuard = false;
	bool isCasino = false;
	bool isNuked = false;
	bool allowNoclip = false;
	bool item_changed = false;
	int stuff_gravity = 50;
	bool stuff_spin = false;
	bool stuff_invert = false;
	int stuffID = 2;
	int bgID = 14;
	int hw_red = 255;
	int hw_green = 128;
	int hw_blue = 64;
	int interactableid = -1;
};

struct AWorld
{
	WorldInfo* ptr;
	WorldInfo info;
	int id;
};

struct TileExtra
{
	int packetType;
	int characterState;
	float objectSpeedX;
	int punchX;
	int punchY;
	int charStat;
	int blockid;
	int visual;
	int signs;
	int backgroundid;
	int displayblock;
	int time;
	int netID;
	int weatherspeed;
	int bpm;
};

struct BlockVisual
{
	int packetType;
	int characterState;
	int punchX;
	int punchY;
	float x;
	float y;
	int plantingTree;
	float XSpeed;
	float YSpeed;
	int charStat;
	int blockid;
	int visual;
	int signs;
	int backgroundid;
	int displayblock;
	int time;
	int netID;
};

inline void decodeName(char* src, const int len, const int itemID, char* dest)
{
	const char key[] = "PBG892FXX982ABC*";
	for (auto i = 0; i < len; i++)
	{
		dest[i] = src[i] ^ key[(i + itemID) % 16];
	}
}

struct itemDataStruct
{
	string name;
	string texturefile;
	string audiofile;
	int id;
	uint8_t editableType;
	uint8_t category;
	uint8_t type;
	uint8_t solid;
	uint16_t rarity;
	uint32_t color1;
	uint32_t color2;
	uint8_t textureX;
	uint8_t textureY;
	uint8_t textureType;
	uint8_t hardness;
	uint16_t audioVol;
	uint32_t texturehash;
	uint32_t audiohash;
	uint8_t seedBase;
	uint8_t seedOverlay;
	uint8_t treeBase;
	uint8_t treeOverlay;
	int punchEffect = 0;
};

enum BlockTypes
{
	FOREGROUND,
	BACKGROUND,
	CONSUMABLE,
	SEED,
	PAIN_BLOCK,
	BEDROCK,
	MAIN_DOOR,
	SIGN,
	DOOR,
	CLOTHING,
	FIST,
	WRENCH,
	CHECKPOINT,
	LOCK,
	PROVIDER,
	GATEWAY,
	VIP,
	TREASURE,
	WEATHER,
	TRAMPOLINE,
	TOGGLE_FOREGROUND,
	CHEMICAL_COMBINER,
	SWITCH_BLOCK,
	SFX_FOREGROUND,
	RANDOM_BLOCK,
	PORTAL,
	PLATFORM,
	MAILBOX,
	MAGIC_EGG,
	CRYSTAL,
	GEMS,
	DEADLY,
	CHEST,
	FACTION,
	BULLETIN_BOARD,
	BOUNCY,
	ANIM_FOREGROUND,
	COMPONENT,
	SUCKER,
	FISH,
	STEAM,
	GROUND_BLOCK,
	DISPLAY,
	STORAGE,
	VENDING,
	DONATION,
	PHONE,
	SEWINGMACHINE,
	CRIME_VILLAIN,
	UNKNOWN
};

#define Property_Zero 0
#define Property_NoSeed 1
#define Property_Dropless 2
#define Property_Beta 4
#define Property_Mod 8
#define Property_Chemical 12
#define Property_Untradable 16
#define Property_Wrenchable 32
#define Property_MultiFacing 64
#define Property_Permanent 128
#define Property_AutoPickup 256
#define Property_WorldLock 512
#define Property_NoSelf 1024
#define Property_RandomGrow 2048
#define Property_Public 4096
#define Property_Foreground 8192

class WorldDB
{
public:
	WorldInfo get(string name);
	AWorld get2(string name);
	static void flush(WorldInfo info);
	void saveAll();
	void saveRedundant();
	void remove2(string name);
	vector<WorldInfo> getRandomWorlds();
	WorldDB();
private:
	vector<WorldInfo> worlds;
};

inline WorldDB::WorldDB()
{
}

// cave blast by tianvan
WorldInfo GenerateGrowCaveLikeWorlds(string name, int width, int height) {

	WorldInfo world;
	world.name = name;
	world.width = width;
	world.height = height;
	world.items = new WorldItem[world.width * world.height];
	vector<int> a = { 3580,3582,3584 };
	int wdp = rand() % 100;
	for (int i = 0; i < width * height; i++)
	{
		world.items[i].foreground = 0;
		if (rand() % 1001 == 0 && i > 3000)
		{
			world.items[i].foreground = 3604;
			world.items[i].background = 3556; //3556
		}
		if (i > 99 && i < 5500 && world.items[i].foreground == 0)
		{
			world.items[i].foreground = rand() % 51 == 0 ? a[rand() % 3] : rand() % 11 == 0 ? 3568 : 3564;
			if (rand() % 36 == 0)
			{
				world.items[i].foreground = 0;
			}
			world.items[i].background = 3556; //3556
		}
		else if (i >= 5000 && i < 5500 && world.items[i].foreground == 0)
		{
			int num = rand() % 76;
			world.items[i].foreground = num > 20 ? 2 : (num > 4 ? 4 : a[rand() % 3]);
			world.items[i].background = 14;
		}
		else if (i >= 5500 && world.items[i].foreground == 0)
		{
			world.items[i].foreground = 8;
			world.items[i].background = 14;
		}
	}
	world.items[wdp].foreground = 6;
	world.items[wdp + 100].foreground = 8;
	world.items[wdp + 100].background = 0;
	if (wdp != 0)
		world.items[wdp - 1].foreground = 242;
	else
		world.items[wdp + 1].foreground = 242;
	return world;
}

inline void GenerateGrowaloneLikeWorld(WorldInfo* world, const int width, const int height, const int dirtType = 2, const int lavaType = 4, const int mainDoorType = 6, const int bedrockType = 8, const int rockType = 10, const int caveBackgroundType = 14, const int wmachineid = 0, const int deco1Id = 0, const int deco2Id = 0, const int id = 0)
{
	//SendConsole("Generating new world (GenerateGrowaloneLikeWorld) details: width(" + to_string(width) + ") height(" + to_string(height) + ") dirtType(" + to_string(dirtType) + ") lavaType(" + to_string(lavaType) + ") mainDoorType(" + to_string(mainDoorType) + ") bedrockType(" + to_string(bedrockType) + ") rockType(" + to_string(rockType) + ") caveBackgroundType(" + to_string(caveBackgroundType) + ") wmachineid(" + to_string(wmachineid) + ") deco1Id(" + to_string(deco1Id) + ") deco2Id(" + to_string(deco2Id) + ") id(" + to_string(id) + ")", "INFO");
	world->weather = wmachineid;
	for (auto i = 0; i < world->width * world->height; i++)
	{
		world->items[i].foreground = 0;
	}
	const auto offset = new int[width];
	const auto offset2 = new int[width];
	offset[0] = (height - 60 < 0) ? -10 : height - 60;
	offset2[0] = offset[0] < 0 ? -10 : offset[0];
	auto settile = [](WorldInfo* w, const int x, const int y, const int id)
	{
		if (x < w->width && x >= 0 && y < w->height && y >= 0)
			w->items[x + y * w->width].foreground = id;
	};
	auto settilebg = [](WorldInfo* w, const int x, const int y, const int id)
	{
		if (x < w->width && x >= 0 && y < w->height && y >= 0)
			w->items[x + y * w->width].background = id;
	};
	auto gettile = [](WorldInfo* w, const int x, const int y)
	{
		if (x < w->width && x >= 0 && y < w->height && y >= 0)
			return w->items[x + y * w->width].foreground;
		return static_cast<short>(0);
	};
	for (auto i = 1; i < width; i++)
	{
		offset[i] = (height - 60 < 0) ? -10 : height - 60;
		const auto rnd = rand() % 30 - 10;
		if (rnd < -2)
			offset[i] = offset[i - 1] - 1; // rise
		else if (rnd > 11)
			offset[i] = offset[i - 1] + 1; // fall
		else
			offset[i] = offset[i - 1]; // no change
		offset2[i] = offset[i] < 0 ? -10 : offset[i];
	}
	for (auto j = 0; j < width; j++)
	{
		for (auto k = 26 + offset[j]; k < height - 5; k++)
		{
			settile(world, j, k, dirtType);
			settilebg(world, j, k, caveBackgroundType);
			const auto renrnd = rand() % 12;
			if (renrnd > 10)
				settile(world, j, k, rockType);
		}
		settile(world, j, 26 + offset[j], dirtType);
		settilebg(world, j, 26 + offset[j], caveBackgroundType);
		settile(world, j, height - 6, bedrockType);
		settile(world, j, height - 5, bedrockType);
		settile(world, j, height - 4, bedrockType);
		settile(world, j, height - 3, bedrockType);
		settile(world, j, height - 2, bedrockType);
		settile(world, j, height - 1, bedrockType);
		settilebg(world, j, height - 6, caveBackgroundType);
		settilebg(world, j, height - 5, caveBackgroundType);
		settilebg(world, j, height - 4, caveBackgroundType);
		settilebg(world, j, height - 3, caveBackgroundType);
		settilebg(world, j, height - 2, caveBackgroundType);
		settilebg(world, j, height - 1, caveBackgroundType);
	}
	for (auto srg = height - 10; srg < height - 6; srg++)
	{
		for (auto dhk = 0; dhk < width; dhk++)
		{
			const auto djkf = rand() % 2;
			if (djkf == 1)
			{
				settile(world, dhk, srg, lavaType);
			}
		}
	}
	if (id & BlastProperties_WaterLevelD2)
	{
		for (auto i = 0; i < width; i++)
		{
			for (auto j = deco2Id; j < height; j++)
			{
				if (gettile(world, i, j) == 0)
				{
					if (i < world->width && i >= 0 && j < world->height && j >= 0)
						world->items[i + j * world->width].water = true;
				}
			}
		}
	}
	else if (id & BlastProperties_RandomDeco1)
	{
		const auto deco1Count = rand() % 25 + 3;
		for (auto i = 0; i < deco1Count; i++)
		{
			const auto a = rand() % width;
			settile(world, a, 25 + offset[a], deco1Id);
		}
	}
	else if (id & BlastProperties_RandomDeco2)
	{
		const auto deco2Count = rand() % 25 + 3;
		for (auto i = 0; i < deco2Count; i++)
		{
			const auto a = rand() % width;
			settile(world, a, 25 + offset[a], deco2Id);
		}
	}
regenerate:
	const auto mainDoorX = (rand() % (width - 4)) + 2;
	auto f = 25 + offset[mainDoorX];
	while (gettile(world, mainDoorX, f) != 0)
	{
		f--;
		if (f < 0) goto regenerate;
	}
	settile(world, mainDoorX, f, mainDoorType);
	settile(world, mainDoorX, f + 1, bedrockType);
	delete offset;
	delete offset2;
}

inline void GenerateRegularWorld(WorldInfo* world, const int width, const int height, const int dirtType = 2, const int lavaType = 4, const int mainDoorType = 6, const int bedrockType = 8, const int rockType = 10, const int caveBackgroundType = 14, const int machineId = 0)
{
	//SendConsole("Generating new world (GenerateRegularWorld) details: width(" + to_string(width) + ") height(" + to_string(height) + ") dirtType(" + to_string(dirtType) + ") lavaType(" + to_string(lavaType) + ") mainDoorType(" + to_string(mainDoorType) + ") bedrockType(" + to_string(bedrockType) + ") rockType(" + to_string(rockType) + ") caveBackgroundType(" + to_string(caveBackgroundType) + ") machineId(" + to_string(machineId) + ")", "INFO");
	world->weather = machineId;
	const auto mainDoorX = (rand() % (world->width - 4)) + 2;
	for (auto i = 0; i < world->width * world->height; i++)
	{
		world->items[i].foreground = 0;
	}
	for (auto i = 0; i < world->width * world->height; i++)
	{
		if (i >= 3800 && i < 5400 && !(rand() % 50))
		{
			world->items[i].foreground = rockType;
		}
		else if (i >= 3700 && i < 5400)
		{
			if (i > 5000)
			{
				const auto m = rand() % 8;
				if (m < 3)
				{
					world->items[i].foreground = lavaType;
				}
				else
				{
					world->items[i].foreground = dirtType;
				}
			}
			else
			{
				world->items[i].foreground = dirtType;
			}
		}
		else if (i >= 5400)
		{
			world->items[i].foreground = bedrockType;
		}
		if (i == 3600 + mainDoorX)
		{
			world->items[i].foreground = mainDoorType;
		}
		if (i == 3700 + mainDoorX)
		{
			world->items[i].foreground = bedrockType;
		}
		if (i >= 3700)
		{
			world->items[i].background = caveBackgroundType;
		}
	}
}

inline WorldInfo generateUranusWorld(const string name, const int width, const int height)
{
	//SendConsole("Generating new world (GenerateUranusWorld) details: width(" + to_string(width) + ") height(" + to_string(height) + ")", "INFO");
	WorldInfo world;
	world.name = name;
	world.isNuked = false;
	world.width = width;
	world.height = height;
	const auto mainDoorX = (rand() % (world.width - 4)) + 2;
	world.items = new WorldItem[world.width * world.height];
	const auto treasure = (rand() % 4400);
	for (auto i = 0; i < world.width * world.height; i++)
	{
		if (i >= 100 && i < 4470 && !(rand() % 99))
		{
			world.items[i].foreground = 9440;
		}
		else if (i == treasure)
		{
			world.items[i].foreground = 7628;
		}
		else if (i > 1200 && i < 4470 && !(rand() % 99))
		{
			world.items[i].foreground = 9442;
		}
		else if (i > 2500 && i < 4470 && !(rand() % 99))
		{
			world.items[i].foreground = 7960;
		}
		else if (i >= 0 && i < 4500)
		{
			world.items[i].foreground = 1132;
		}
		if (i >= 0 && i <= 29)
		{
			world.items[i].foreground = 8;
		}
		if (i >= 0)
		{
			world.items[i].background = 9438;
		}
		if (i == 550 + mainDoorX)
		{
			world.items[i].foreground = 6;
		}
		if (i >= 1000 && i <= 1030)
		{
			world.items[i].foreground = 9444;
		}
		if (i >= 4470)
		{
			world.items[i].foreground = 8;
		}
	}
	return world;
}

WorldInfo generateWorld(string name, int width, int height)
{
	WorldInfo world;
	world.name = name;
	world.width = width;
	world.height = height;
	world.items = new WorldItem[world.width * world.height];
	int randMB = (rand() % 100);
	for (int i = 0; i < world.width * world.height; i++)
	{
		if (i >= 3700)
			world.items[i].background = 14;
		if (i >= 3700)
			world.items[i].foreground = 2;
		if (i == 3600 + randMB)
			world.items[i].foreground = 6;
		else if (i >= 3600 && i < 3700)
			world.items[i].foreground = 0;
		if (i == 3700 + randMB)
			world.items[i].foreground = 8;
		if (i >= 3800 && i < 5400 && !(rand() % 48)) { world.items[i].foreground = 10; }
		if (i >= 5000 && i < 5400 && !(rand() % 6)) { world.items[i].foreground = 4; }
		else if (i >= 5400) { world.items[i].foreground = 8; }
	}
	return world;
}

inline int PlayerDB::guildRegister(ENetPeer* peer, string guildName, string guildStatement, string guildFlagfg, string guildFlagbg)
{
	SendConsole("Registering new guild (guildRegister) details: guildName(" + guildName + ") guildStatement(" + guildStatement + ") guildFlagfg(" + guildFlagfg + ") guildFlagbg(" + guildFlagbg + ")", "INFO");
	auto uname = guildName;
	if (guildName.find(" ") != string::npos || guildName.find(".") != string::npos || guildName.find(",") != string::npos || guildName.find("?") != string::npos || guildName.find("@") != string::npos || guildName.find("[") != string::npos || guildName.find("]") != string::npos || guildName.find("#") != string::npos || guildName.find("<") != string::npos || guildName.find(">") != string::npos || guildName.find(":") != string::npos || guildName.find("{") != string::npos || guildName.find("}") != string::npos || guildName.find("|") != string::npos || guildName.find("+") != string::npos || guildName.find("_") != string::npos || guildName.find("~") != string::npos || guildName.find("-") != string::npos || guildName.find("!") != string::npos || guildName.find("$") != string::npos || guildName.find("%") != string::npos || guildName.find("^") != string::npos || guildName.find("&") != string::npos || guildName.find("`") != string::npos || guildName.find("*") != string::npos || guildName.find("(") != string::npos || guildName.find(")") != string::npos || guildName.find("=") != string::npos || guildName.find("'") != string::npos || guildName.find(";") != string::npos || guildName.find("/") != string::npos)
	{
		return -1;
	}
	if (guildName == "prn" || guildName == "con" || guildName == "aux" || guildName == "nul" || guildName == "com1" || guildName == "com2" || guildName == "com3" || guildName == "com4" || guildName == "com5" || guildName == "com6" || guildName == "com7" || guildName == "com8" || guildName == "com9" || guildName == "lpt1" || guildName == "lpt2" || guildName == "lpt3" || guildName == "lpt4" || guildName == "lpt5" || guildName == "lpt6" || guildName == "lpt7" || guildName == "lpt8" || guildName == "lpt9")
	{
		return -1;
	}
	toUpperCase(uname);
	if (guildName.length() < 3)
	{
		return -2;
	}
	if (guildName.length() > 15)
	{
		return -3;
	}
	if (guildFlagfg.size() > 5 || guildFlagfg.size() < 0 || guildFlagbg.size() > 5 || guildFlagbg.size() < 0)
	{
		autoBan(peer, true, 99999, "tried to crash with guild reg things");
		return -1;
	}
	int fg;
	int bg;
	try
	{
		fg = stoi(guildFlagfg);
	}
	catch (...)
	{
		return -6;
	}
	try
	{
		bg = stoi(guildFlagbg);
	}
	catch (...)
	{
		return -5;
	}
	if (fg > maxItems || bg > maxItems)
	{
		return -1;
	}
	auto fixedguildName = PlayerDB::getProperName(guildName);
	std::ifstream ifs("guilds/" + fixedguildName + ".json");
	if (ifs.is_open())
	{
		return -4;
	}
	return 1;
}


// ReSharper disable once CppNonInlineFunctionDefinitionInHeaderFile
AWorld WorldDB::get2(string name)
{
	if (worlds.size() > 200) {
#ifdef TOTAL_LOG
		cout << "[!] Saving redundant worlds!" << endl;
#endif
		saveRedundant();
#ifdef TOTAL_LOG
		cout << "[!] Redundant worlds are saved!" << endl;
#endif
	}
	AWorld ret;
	if (name == "exit" || name == "prn" || name == "con" || name == "aux" || name == "nul" || name == "com1" || name == "com2" || name == "com3" || name == "com4" || name == "com5" || name == "com6" || name == "com7" || name == "com8" || name == "com9" || name == "lpt1" || name == "lpt2" || name == "lpt3" || name == "lpt4" || name == "lpt5" || name == "lpt6" || name == "lpt7" || name == "lpt8" || name == "lpt9")
	{
		throw 3;
	}
	name = getStrUpper(name);
	if (name == "") throw 1;
	if (name.length() < 1) throw 1;
	for (auto c : name)
	{
		if ((c < 'A' || c > 'Z') && (c < '0' || c > '9'))
		{
			throw 2;
		}
	}
	for (auto i = 0; i < worlds.size(); i++)
	{
		if (worlds.at(i).name == name)
		{
			ret.id = i;
			ret.info = worlds.at(i);
			ret.ptr = &worlds.at(i);
			return ret;
		}
	}
	try
	{

		ifstream ifs("worlds/_" + name + ".json");
		if (ifs.is_open())
		{
			json j;
			ifs >> j;
			WorldInfo info;
			for (auto i = 0; i < j["accessworld"].size(); i++) {
				info.accessed.push_back(j["accessworld"][i]);
			}
			for (int i = 0; i < j["VipAcc"].size(); i++) {
				info.viplist.push_back(j["VipAcc"][i]);
			}
			info.name = j["name"].get<string>();
			info.width = j["width"].get<int>();
			info.height = j["height"].get<int>();
			info.owner = j["owner"].get<string>();
			info.category = j["category"].get<string>();
			info.ownerDisplayName = j["dname"].get<string>();
			info.weather = j["weather"].get<int>();
			info.isPublic = j["isPublic"];
			info.rainbow = j["rbg"];
			info.silence = j["sil"];
			info.isNuked = j["nuked"];
			info.rating = j["rating"];
			info.entrylevel = j["wlevel"];
			info.stuffID = j["sid"].get<int>();
			info.stuff_invert = j["si"].get<bool>();
			info.minimod = j["minimod"].get<bool>();
			info.stuff_gravity = j["sg"].get<int>();
			info.stuff_spin = j["ss"].get<bool>();
			info.bgID = j["bid"].get<int>();
			info.hw_red = j["hwr"].get<int>();
			info.hw_green = j["hwg"].get<int>();
			info.hw_blue = j["hwb"].get<int>();
			info.droppedCount = j["dc"].get<int>();
			info.droppedItemUid = j["droppedItemUid"].get<int>();
			json droppedobjects = j["dropped"];
			for (int i = 0; i < info.droppedCount; i++) {
				DroppedItem di;
				di.count = droppedobjects[i]["c"].get<byte>();
				di.id = droppedobjects[i]["id"].get<short>();
				di.x = droppedobjects[i]["x"].get<int>();
				di.y = droppedobjects[i]["y"].get<int>();
				di.uid = droppedobjects[i]["uid"].get<int>();
				info.droppedItems.push_back(di);
			}
			auto tiles = j["tiles"];
			auto square = info.width * info.height;
			info.items = new WorldItem[square];
			for (int i = 0; i < square; i++) {
				info.items[i].foreground = tiles[i]["fg"].get<int>();
				info.items[i].background = tiles[i]["bg"].get<int>();
				info.items[i].flipped = tiles[i]["r"].get<bool>();
				info.items[i].sign = tiles[i]["s"].get<string>();
				info.items[i].intdata = tiles[i]["int"].get<int>();
				info.items[i].label = tiles[i]["l"].get<string>();
				info.items[i].destWorld = tiles[i]["d"].get<string>();
				info.items[i].destId = tiles[i]["did"].get<string>();
				info.items[i].currId = tiles[i]["crid"].get<string>();
				info.items[i].password = tiles[i]["p"].get<string>();
				info.items[i].mid = tiles[i]["mid"].get<int>();
				info.items[i].mc = tiles[i]["mc"].get<int>();
				info.items[i].rm = tiles[i]["rm"].get<bool>();
				info.items[i].opened = tiles[i]["open"].get<bool>();
				info.items[i].vcount = tiles[i]["vc"].get<int>();
				info.items[i].vdraw = tiles[i]["vd"].get<int>();
				info.items[i].vid = tiles[i]["vid"].get<int>();
				info.items[i].vprice = tiles[i]["vp"].get<int>();
				info.items[i].monitorname = tiles[i]["how"].get<string>();
				info.items[i].monitoronline = tiles[i]["mon"].get<bool>();
				info.items[i].spliced = tiles[i]["spl"].get<bool>();
				info.items[i].activated = tiles[i]["a"].get<bool>();
				info.items[i].growtime = tiles[i]["sgt"].get<int>();
				info.items[i].fruitcount = tiles[i]["sfc"].get<int>();
				info.items[i].water = tiles[i]["w"].get<bool>();
				info.items[i].fire = tiles[i]["f"].get<bool>();
				info.items[i].red = tiles[i]["red"].get<int>();
				info.items[i].green = tiles[i]["gre"].get<int>();
				info.items[i].blue = tiles[i]["blu"].get<int>();
				info.items[i].display1 = tiles[i]["ds1"].get<int>();
				info.items[i].display2 = tiles[i]["ds2"].get<int>();
				info.items[i].display3 = tiles[i]["ds3"].get<int>();
				info.items[i].display4 = tiles[i]["ds4"].get<int>();
				info.items[i].VipPublic = tiles[i]["VipPublic"].get<bool>();
				info.items[i].water = tiles[i]["water"].get<bool>();
				info.items[i].fire = tiles[i]["fire"].get<bool>();
				info.items[i].glue = tiles[i]["glue"].get<bool>();
			}
			worlds.push_back(info);
			ret.id = worlds.size() - 1;
			ret.info = info;
			ret.ptr = &worlds.at(worlds.size() - 1);
			return ret;
		}
		else
		{
			if (useduranusblast == true)
			{
				useduranusblast = false;
				WorldInfo info = GenerateGrowCaveLikeWorlds(name, 100, 60);
				worlds.push_back(info);
				ret.id = worlds.size() - 1;
				ret.info = info;
				ret.ptr = &worlds.at(worlds.size() - 1);
				return ret;
			}
			else
			{
				WorldInfo info = generateWorld(name, 100, 60);

				worlds.push_back(info);
				ret.id = worlds.size() - 1;
				ret.info = info;
				ret.ptr = &worlds.at(worlds.size() - 1);
				return ret;
			}
		}
	}
	catch (std::exception& e)
	{
		SendConsole("WorldDB get2 Failed to Execute! details: name(" + name + ")", "ERROR");
		cerr << e.what() << endl;

		WorldInfo info = generateWorld(name, 100, 60);
		worlds.push_back(info);
		ret.id = worlds.size() - 1;
		ret.info = info;
		ret.ptr = &worlds.at(worlds.size() - 1);
		return ret;

		/*auto info = CriticalError();
		worlds.push_back(info);
		ret.id = worlds.size() - 1;
		ret.info = info;
		ret.ptr = &worlds.at(worlds.size() - 1);
		return ret;*/
	}
}

inline WorldInfo WorldDB::get(const string name)
{
	return this->get2(name).info;
}

void WorldDB::remove2(string name)
{
	// ReSharper disable once CppUseAuto
	for (int i = 0; i < worlds.size(); i++)
	{
		// ReSharper disable once CppUseAuto
		// ReSharper disable once CppLocalVariableMayBeConst
		WorldInfo w = worlds.at(i);
		if (getStrLower(name) == getStrLower(w.name))
		{
			worlds.erase(worlds.begin() + i);
		}
	}
}

inline void WorldDB::flush(WorldInfo info)
{
	std::ofstream o("worlds/_" + info.name + ".json");
	if (!o.is_open()) {
		cout << GetLastError() << endl;
	}
	json j;
	j["name"] = info.name;
	j["width"] = info.width;
	j["height"] = info.height;
	j["owner"] = info.owner;
	j["VipAcc"] = info.viplist;
	j["category"] = info.category;
	j["minimod"] = info.minimod;
	j["rating"] = info.rating;
	j["wlevel"] = info.entrylevel;
	j["dname"] = info.ownerDisplayName;
	j["isPublic"] = info.isPublic;
	j["weather"] = info.weather;
	j["sid"] = info.stuffID;
	j["sil"] = info.silence;
	j["rbg"] = info.rainbow;
	j["sg"] = info.stuff_gravity;
	j["si"] = info.stuff_invert;
	j["ss"] = info.stuff_spin;
	j["bid"] = info.bgID;
	j["hwr"] = info.hw_red;
	j["hwg"] = info.hw_green;
	j["hwb"] = info.hw_blue;
	j["dc"] = info.droppedItems.size();
	j["droppedItemUid"] = info.droppedItemUid;
	j["nuked"] = info.isNuked;
	json WorldDropped = json::array();
	const int square = info.width * info.height;
	for (int i = 0; i < info.droppedItems.size(); i++) {
		json droppedJ;
		droppedJ["c"] = static_cast<BYTE>(info.droppedItems[i].count);
		droppedJ["id"] = static_cast<short>(info.droppedItems[i].id);
		droppedJ["x"] = info.droppedItems[i].x;
		droppedJ["y"] = info.droppedItems[i].y;
		droppedJ["uid"] = info.droppedItems[i].uid;
		WorldDropped.push_back(droppedJ);
	}
	j["dropped"] = WorldDropped;
	json WorldTiles = json::array();
	for (int i = 0; i < square; i++) {
		json tile;
		tile["fg"] = info.items[i].foreground;
		tile["bg"] = info.items[i].background;
		tile["s"] = info.items[i].sign;
		tile["r"] = info.items[i].flipped;
		tile["int"] = info.items[i].intdata;
		tile["l"] = info.items[i].label;
		tile["d"] = info.items[i].destWorld;
		tile["did"] = info.items[i].destId;
		tile["crid"] = info.items[i].currId;
		tile["p"] = info.items[i].password;
		tile["mid"] = info.items[i].mid;
		tile["mc"] = info.items[i].mc;
		tile["rm"] = info.items[i].rm;
		tile["open"] = info.items[i].opened;
		tile["vc"] = info.items[i].vcount;
		tile["vd"] = info.items[i].vdraw;
		tile["vid"] = info.items[i].vid;
		tile["vp"] = info.items[i].vprice;
		tile["how"] = info.items[i].monitorname;
		tile["mon"] = info.items[i].monitoronline;
		tile["spl"] = info.items[i].spliced;
		tile["a"] = info.items[i].activated;
		tile["sgt"] = info.items[i].growtime;
		tile["sfc"] = info.items[i].fruitcount;
		tile["w"] = info.items[i].water;
		tile["f"] = info.items[i].fire;
		tile["red"] = info.items[i].red;
		tile["gre"] = info.items[i].green;
		tile["blu"] = info.items[i].blue;
		tile["ds1"] = info.items[i].display1;
		tile["ds2"] = info.items[i].display2;
		tile["ds3"] = info.items[i].display3;
		tile["ds4"] = info.items[i].display4;
		tile["water"] = info.items[i].water;
		tile["fire"] = info.items[i].fire;
		tile["glue"] = info.items[i].glue;
		tile["VipPublic"] = info.items[i].VipPublic;
		WorldTiles.push_back(tile);
	}
	j["tiles"] = WorldTiles;
	o << j << std::endl;
}

void WorldDB::saveAll()
{
	for (int i = 0; i < worlds.size(); i++) {
		flush(worlds.at(i));
	}
	worlds.clear();
}

vector<WorldInfo> WorldDB::getRandomWorlds() {
	vector<WorldInfo> ret;
	for (int i = 0; i < ((worlds.size() < 10) ? worlds.size() : 10); i++)
	{ // load first four worlds, it is excepted that they are special
		ret.push_back(worlds.at(i));
	}
	// and lets get up to 6 random
	if (worlds.size() > 4) {
		for (int j = 0; j < 6; j++)
		{
			bool isPossible = true;
			WorldInfo world = worlds.at(rand() % (worlds.size() - 4));
			for (int i = 0; i < ret.size(); i++)
			{
				if (world.name == ret.at(i).name || world.name == "EXIT")
				{
					isPossible = false;
				}
			}
			if (isPossible)
				ret.push_back(world);
		}
	}
	return ret;
}

void WorldDB::saveRedundant()
{
	for (int i = 4; i < worlds.size(); i++) {
		bool canBeFree = true;
		ENetPeer* currentPeer;

		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			if (((PlayerInfo*)(currentPeer->data))->currentWorld == worlds.at(i).name)
				canBeFree = false;
		}
		if (canBeFree)
		{
			flush(worlds.at(i));
			delete worlds.at(i).items;
			worlds.erase(worlds.begin() + i);
			i--;
		}
	}
}

WorldDB worldDB;

inline bool isHereSave(ENetPeer* peer, ENetPeer* peer2)
{
	return static_cast<PlayerInfo*>(peer->data)->currentWorld == static_cast<PlayerInfo*>(peer2->data)->currentWorld;
}

inline int getPlayersCountInWorldSave(const string name)
{
	auto count = 0;
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (static_cast<PlayerInfo*>(currentPeer->data)->isinv == false && !static_cast<PlayerInfo*>(currentPeer->data)->Console)
		{
			if (static_cast<PlayerInfo*>(currentPeer->data)->currentWorld == name)
			{
				count++;
			}
		}
	}
	return count;
}

inline void sendPlayerLeaveSave(ENetPeer* peer, PlayerInfo* player)
{
	if (static_cast<PlayerInfo*>(peer->data)->currentWorld == "EXIT") return;
	auto p = packetEnd(appendString(appendString(createPacket(), "OnRemove"), "netID|" + std::to_string(static_cast<PlayerInfo*>(peer->data)->netID) + "\n"));
	auto p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`5<`w" + static_cast<PlayerInfo*>(peer->data)->displayName + "`` `5left, `w" + std::to_string(getPlayersCountInWorldSave(static_cast<PlayerInfo*>(peer->data)->currentWorld)) + "`` `5others here>```w"));
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (static_cast<PlayerInfo*>(currentPeer->data)->currentWorld == "EXIT") continue;
		if (static_cast<PlayerInfo*>(currentPeer->data)->isIn == false) continue;
		if (isHereSave(peer, currentPeer))
		{
			{
				const auto packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet);
				{
					const auto net_packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
					enet_peer_send(currentPeer, 0, net_packet);
				}
			}
			{
			}
		}
	}
	delete p.data;
	delete p2.data;
}

void saveAllWorlds() // atexit hack plz fix
{
	cout << "Saving worlds..." << endl;

	worldDB.saveAll();
	cout << "Worlds saved!" << endl;
}

inline WorldInfo* getPlyersWorld(ENetPeer* peer)
{
	if (serverIsFrozen == false && static_cast<PlayerInfo*>(peer->data)->currentWorld != "EXIT")
	{
		if (peer != nullptr)
		{
			try
			{
				return worldDB.get2(static_cast<PlayerInfo*>(peer->data)->currentWorld).ptr;
			}
			catch (...)
			{
				SendConsole("Failed returning value (getPlyersWorld)", "WARNING");
			}
		}
	}
	return nullptr;
}

inline WorldInfo* getWorldInfoByName(string worldname)
{
	try
	{
		return worldDB.get2(worldname).ptr;
	}
	catch (...)
	{
		SendConsole("Failed returning value (getPlyersWorld)", "WARNING");
	}
	return nullptr;
}

struct ItemDefinition
{
	int id;
	string name;
	int rarity;
	int breakHits;
	int growTime;
	ClothTypes clothType;
	BlockTypes blockType;
	string description = "This item has no description.";
	string MultiFacing = "This item can be placed in both directions.";
	int properties;
	int price;
};

vector<ItemDefinition> itemDefs;
vector<DroppedItem> droppedItems;

inline ItemDefinition getItemDef(const int id)
{
	if (id < itemDefs.size() && id > 0 && id <= maxItems)
	{
		return itemDefs.at(id);
	}
	return itemDefs.at(0);
}

inline void craftItemDescriptions()
{
	SendConsole("Loading item descriptions (craftItemDescriptions)", "INFO");
	ifstream infile("Descriptions.txt");
	for (string line; getline(infile, line);)
	{
		if (line.length() > 3 && line[0] != '/' && line[1] != '/')
		{
			auto ex = explode("|", line);
			if (atoi(ex[0].c_str()) + 1 < itemDefs.size())
			{
				itemDefs.at(atoi(ex[0].c_str())).description = ex[1];
				if (!(atoi(ex[0].c_str()) % 2))
				{
					itemDefs.at(atoi(ex[0].c_str()) + 1).description = "This is a tree.";
				}
			}
		}
	}
}

inline void buildItemsDatabase()
{
	SendConsole("Building item database (buildItemsDatabase)", "INFO");
	auto current = -1;
	ifstream infile("CoreData.txt");
	for (string line; getline(infile, line);)
	{
		if (line.length() > 8 && line[0] != '/' && line[1] != '/')
		{
			auto ex = explode("|", line);
			ItemDefinition def;
			def.id = atoi(ex[0].c_str());
			def.name = ex[1];
			def.rarity = atoi(ex[2].c_str());
			def.price = atoi(ex[2].c_str());
			def.breakHits = atoi(ex[7].c_str());
			auto properties = explode(",", ex[3]);
			def.properties = Property_Zero;
			for (auto& prop : properties)
			{
				if (prop == "NoSeed")
				{
					def.properties += Property_NoSeed;
				}
				if (prop == "Dropless")
				{
					def.properties += Property_Dropless;
				}
				if (prop == "Beta")
				{
					def.properties += Property_Beta;
				}
				if (prop == "Mod")
				{
					def.properties += Property_Mod;
				}
				if (prop == "Untradable")
				{
					def.properties += Property_Untradable;
				}
				if (prop == "Wrenchable")
				{
					def.properties += Property_Wrenchable;
				}
				if (prop == "MultiFacing")
				{
					def.properties += Property_MultiFacing;
				}
				if (prop == "Permanent")
				{
					def.properties += Property_Permanent;
				}
				if (prop == "AutoPickup")
				{
					def.properties += Property_AutoPickup;
				}
				if (prop == "WorldLock")
				{
					def.properties += Property_WorldLock;
				}
				if (prop == "NoSelf")
				{
					def.properties += Property_NoSelf;
				}
				if (prop == "RandomGrow")
				{
					def.properties += Property_RandomGrow;
				}
				if (prop == "Public")
				{
					def.properties += Property_Public;
				}
				if (prop == "Foreground")
				{
					def.properties += Property_Foreground;
				}
				if (prop == "OnlyCombiner")
				{
					def.properties += Property_Chemical;
				}
			}
			auto bt = ex[4];
			if (bt == "Foreground_Block")
			{
				def.blockType = BlockTypes::FOREGROUND;
			}
			else if (bt == "Background_Block")
			{
				def.blockType = BlockTypes::BACKGROUND;
			}
			else if (bt == "Seed")
			{
				def.blockType = BlockTypes::SEED;
			}
			else if (bt == "Consummable")
			{
				def.blockType = BlockTypes::CONSUMABLE;
			}
			else if (bt == "Pain_Block")
			{
				def.blockType = BlockTypes::PAIN_BLOCK;
			}
			else if (bt == "Main_Door")
			{
				def.blockType = BlockTypes::MAIN_DOOR;
			}
			else if (bt == "Bedrock")
			{
				def.blockType = BlockTypes::BEDROCK;
			}
			else if (bt == "Door")
			{
				def.blockType = BlockTypes::DOOR;
			}
			else if (bt == "Fist")
			{
				def.blockType = BlockTypes::FIST;
			}
			else if (bt == "Sign")
			{
				def.blockType = BlockTypes::SIGN;
			}
			else if (bt == "Back")
			{
				def.blockType = BlockTypes::BACKGROUND;
			}
			else if (bt == "Sheet_Music")
			{
				def.blockType = BlockTypes::BACKGROUND;
			}
			else if (bt == "Wrench")
			{
				def.blockType = BlockTypes::WRENCH;
			}
			else if (bt == "Checkpoint")
			{
				def.blockType = BlockTypes::CHECKPOINT;
			}
			else if (bt == "Lock")
			{
				def.blockType = BlockTypes::LOCK;
			}
			else if (bt == "Provider")
			{
				def.blockType = BlockTypes::PROVIDER;
			}
			else if (bt == "Gateway")
			{
				def.blockType = BlockTypes::GATEWAY;
			}
			else if (bt == "Clothing")
			{
				def.blockType = BlockTypes::CLOTHING;
			}
			else if (bt == "Platform")
			{
				def.blockType = BlockTypes::PLATFORM;
			}
			else if (bt == "SFX_Foreground")
			{
				def.blockType = BlockTypes::SFX_FOREGROUND;
			}
			else if (bt == "Gems")
			{
				def.blockType = BlockTypes::GEMS;
			}
			else if (bt == "Toggleable_Foreground")
			{
				def.blockType = BlockTypes::TOGGLE_FOREGROUND;
			}
			else if (bt == "Chemical_Combiner")
			{
				def.blockType = BlockTypes::CHEMICAL_COMBINER;
			}
			else if (bt == "Treasure")
			{
				def.blockType = BlockTypes::TREASURE;
			}
			else if (bt == "VIP")
			{
				def.blockType = BlockTypes::VIP;
			}
			else if (bt == "Deadly_Block")
			{
				def.blockType = BlockTypes::DEADLY;
			}
			else if (bt == "Trampoline_Block")
			{
				def.blockType = BlockTypes::TRAMPOLINE;
			}
			else if (bt == "Animated_Foreground_Block")
			{
				def.blockType = BlockTypes::ANIM_FOREGROUND;
			}
			else if (bt == "Portal")
			{
				def.blockType = BlockTypes::PORTAL;
			}
			else if (bt == "Random_Block")
			{
				def.blockType = BlockTypes::RANDOM_BLOCK;
			}
			else if (bt == "Bouncy")
			{
				def.blockType = BlockTypes::BOUNCY;
			}
			else if (bt == "Chest")
			{
				def.blockType = BlockTypes::CHEST;
			}
			else if (bt == "Switch_Block")
			{
				def.blockType = BlockTypes::SWITCH_BLOCK;
			}
			else if (bt == "Magic_Egg")
			{
				def.blockType = BlockTypes::MAGIC_EGG;
			}
			else if (bt == "Crystal")
			{
				def.blockType = BlockTypes::CRYSTAL;
			}
			else if (bt == "Mailbox")
			{
				def.blockType = BlockTypes::MAILBOX;
			}
			else if (bt == "Bulletin_Board")
			{
				def.blockType = BlockTypes::BULLETIN_BOARD;
			}
			else if (bt == "Faction")
			{
				def.blockType = BlockTypes::FACTION;
			}
			else if (bt == "Component")
			{
				def.blockType = BlockTypes::COMPONENT;
			}
			else if (bt == "Weather_Machine")
			{
				def.blockType = BlockTypes::WEATHER;
			}
			else if (bt == "ItemSucker")
			{
				def.blockType = BlockTypes::SUCKER;
			}
			else if (bt == "Fish_Tank_Port")
			{
				def.blockType = BlockTypes::FISH;
			}
			else if (bt == "Steam_Block")
			{
				def.blockType = BlockTypes::STEAM;
			}
			else if (bt == "ground_Block")
			{
				def.blockType = BlockTypes::GROUND_BLOCK;
			}
			else if (bt == "Display")
			{
				def.blockType = BlockTypes::DISPLAY;
			}
			else if (bt == "Untrade_A_Box" || bt == "Safe_Vault")
			{
				def.blockType = BlockTypes::STORAGE;
			}
			else if (bt == "Vending")
			{
				def.blockType = BlockTypes::VENDING;
			}
			else if (bt == "Donation_Box")
			{
				def.blockType = BlockTypes::DONATION;
			}
			else if (bt == "Phone_Booth")
			{
				def.blockType = BlockTypes::PHONE;
			}
			else if (bt == "Sewing_Machine")
			{
				def.blockType = BlockTypes::SEWINGMACHINE;
			}
			else if (bt == "Crime_Villain")
			{
				def.blockType = BlockTypes::CRIME_VILLAIN;
			}
			else
			{
				def.blockType = BlockTypes::UNKNOWN;
			}
			def.breakHits = atoi(ex[7].c_str());
			def.growTime = atoi(ex[8].c_str());
			auto cl = ex[9];
			if (def.blockType == BlockTypes::CLOTHING)
			{
				if (cl == "None")
				{
					def.clothType = ClothTypes::NONE;
				}
				else if (cl == "Hat")
				{
					def.clothType = ClothTypes::HAIR;
				}
				else if (cl == "Shirt")
				{
					def.clothType = ClothTypes::SHIRT;
				}
				else if (cl == "Pants")
				{
					def.clothType = ClothTypes::PANTS;
				}
				else if (cl == "Feet")
				{
					def.clothType = ClothTypes::FEET;
				}
				else if (cl == "Face")
				{
					def.clothType = ClothTypes::FACE;
				}
				else if (cl == "Hand")
				{
					def.clothType = ClothTypes::HAND;
				}
				else if (cl == "Back")
				{
					def.clothType = ClothTypes::BACK;
				}
				else if (cl == "Hair")
				{
					def.clothType = ClothTypes::MASK;
				}
				else if (cl == "Chest")
				{
					def.clothType = ClothTypes::NECKLACE;
				}
				else
				{
					def.clothType = ClothTypes::NONE;
				}
			}
			else
			{
				def.clothType = ClothTypes::NONE;
			}
			if (++current != def.id)
			{
				SendConsole("Unordered database at item " + std::to_string(current) + "/" + std::to_string(def.id), "ERROR");
			}
			maxItems = def.id;
			itemDefs.push_back(def);
		}
	}
	craftItemDescriptions();
}

inline BYTE* packBlockVisual(TileExtra* dataStruct)
{
	const auto data = new BYTE[104];
	for (auto i = 0; i < 100; i++)
	{
		data[i] = 0;
	}
	memcpy(data, &dataStruct->packetType, 4);
	memcpy(data + 8, &dataStruct->netID, 4);
	memcpy(data + 12, &dataStruct->characterState, 4);
	memcpy(data + 16, &dataStruct->objectSpeedX, 4);
	memcpy(data + 44, &dataStruct->punchX, 4);
	memcpy(data + 48, &dataStruct->punchY, 4);
	memcpy(data + 52, &dataStruct->charStat, 4);
	memcpy(data + 56, &dataStruct->blockid, 2);
	memcpy(data + 58, &dataStruct->backgroundid, 2);
	memcpy(data + 60, &dataStruct->visual, 4);
	memcpy(data + 64, &dataStruct->displayblock, 4);
	return data;
}

inline BYTE* packBlockVisual(BlockVisual* dataStruct)
{
	const auto data = new BYTE[72];
	for (auto i = 0; i < 72; i++)
	{
		data[i] = 0;
	}
	memcpy(data, &dataStruct->packetType, 4);
	memcpy(data + 8, &dataStruct->netID, 4);
	memcpy(data + 12, &dataStruct->characterState, 4);
	memcpy(data + 44, &dataStruct->punchX, 4);
	memcpy(data + 48, &dataStruct->punchY, 4);
	memcpy(data + 52, &dataStruct->charStat, 4);
	memcpy(data + 56, &dataStruct->blockid, 4);
	memcpy(data + 60, &dataStruct->visual, 4);
	memcpy(data + 64, &dataStruct->displayblock, 4);
	return data;
}

inline BYTE* packStuffVisual(TileExtra* dataStruct, int options, int gravity)
{
	const auto data = new BYTE[102];
	for (auto i = 0; i < 102; i++)
	{
		data[i] = 0;
	}
	memcpy(data, &dataStruct->packetType, 4);
	memcpy(data + 8, &dataStruct->netID, 4);
	memcpy(data + 12, &dataStruct->characterState, 4);
	memcpy(data + 44, &dataStruct->punchX, 4);
	memcpy(data + 48, &dataStruct->punchY, 4);
	memcpy(data + 52, &dataStruct->charStat, 4);
	memcpy(data + 56, &dataStruct->blockid, 2);
	memcpy(data + 58, &dataStruct->backgroundid, 2);
	memcpy(data + 60, &dataStruct->visual, 4);
	memcpy(data + 64, &dataStruct->displayblock, 4);
	memcpy(data + 68, &gravity, 4);
	memcpy(data + 70, &options, 4);
	return data;
}

inline BYTE* packStuffVisual333(TileExtra* dataStruct)
{
	const auto data = new BYTE[102];
	for (auto i = 0; i < 102; i++)
	{
		data[i] = 0;
	}
	memcpy(data, &dataStruct->packetType, 4);
	memcpy(data + 8, &dataStruct->netID, 4);
	memcpy(data + 12, &dataStruct->characterState, 4);
	memcpy(data + 44, &dataStruct->punchX, 4);
	memcpy(data + 48, &dataStruct->punchY, 4);
	memcpy(data + 52, &dataStruct->charStat, 4);
	memcpy(data + 56, &dataStruct->blockid, 2);
	memcpy(data + 58, &dataStruct->backgroundid, 2);
	memcpy(data + 60, &dataStruct->visual, 4);
	memcpy(data + 64, &dataStruct->displayblock, 4);
	return data;
}

void SendPacketRaw3(int a1, void* packetData, size_t packetDataSize, void* a4, ENetPeer* peer, int packetFlag)
{
	ENetPacket* p;

	if (peer) // check if we have it setup
	{
		p = enet_packet_create(0, packetDataSize + 5, packetFlag);
		memcpy(p->data, &a1, 4);
		memcpy((char*)p->data + 4, packetData, packetDataSize);
		enet_peer_send(peer, 0, p);
	}
}

inline void SendPacketRaw2(int a1, void* packetData, const size_t packetDataSize, void* a4, ENetPeer* peer, const int packetFlag)
{
	ENetPacket* p;
	if (peer)
	{
		if (a1 == 4 && *(static_cast<BYTE*>(packetData) + 12) & 8)
		{
			p = enet_packet_create(nullptr, packetDataSize + *(static_cast<DWORD*>(packetData) + 13) + 5, packetFlag);
			auto four = 4;
			memcpy(p->data, &four, 4);
			memcpy(reinterpret_cast<char*>(p->data) + 4, packetData, packetDataSize);
			memcpy(reinterpret_cast<char*>(p->data) + packetDataSize + 4, a4, *(static_cast<DWORD*>(packetData) + 13));
			enet_peer_send(peer, 0, p);
		}
		else
		{
			if (a1 == 192)
			{
				a1 = 4;
				p = enet_packet_create(nullptr, packetDataSize + 5, packetFlag);
				memcpy(p->data, &a1, 4);
				memcpy(reinterpret_cast<char*>(p->data) + 4, packetData, packetDataSize);
				enet_peer_send(peer, 0, p);
			}
			else
			{
				p = enet_packet_create(nullptr, packetDataSize + 5, packetFlag);
				memcpy(p->data, &a1, 4);
				memcpy(reinterpret_cast<char*>(p->data) + 4, packetData, packetDataSize);
				enet_peer_send(peer, 0, p);
			}
		}
	}
	// ReSharper disable once CppDeletingVoidPointer
	delete packetData;
}

inline void updatetile(ENetPeer* peer, const int netID, const int x, const int y)
{
	BlockVisual data3;
	data3.packetType = 0x5;
	data3.characterState = 8;
	data3.charStat = 8;
	data3.blockid = 2;
	data3.backgroundid = 2;
	data3.visual = 0x03000000;
	data3.punchX = x;
	data3.punchY = y;
	data3.netID = netID;
	SendPacketRaw2(192, packBlockVisual(&data3), 100, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
}

string EntranceTiles(int visual, uint32_t owner) {
	string data;
	//data.resize(4 + 2 + 4 + 4 + 4 + 8);
	data.resize(4 + 2 + 4 + 4 + 4 + 8);
	data[2] = 0x01;
	data[4] = 3;
	data[5] = visual; // or 0x02
	STRINT(data, 6) = owner;
	//data[14] = 1;
	return data;
}
string EntranceTilesLocked(int visual, uint32_t owner) {
	string data;
	data.resize(4 + 2 + 4 + 4 + 4 + 8);
	data[2] = 0x01;
	data[5] = visual;
	STRINT(data, 6) = owner;
	return data;
}


inline void updateGuild(ENetPeer* peer)
{
	SendConsole("Function (updateGuild) Called details: guildname(" + static_cast<PlayerInfo*>(peer->data)->guild + ") playername(" + static_cast<PlayerInfo*>(peer->data)->rawName + ")", "INFO");
	const auto guildname = PlayerDB::getProperName(static_cast<PlayerInfo*>(peer->data)->guild);
	if (guildname != "")
	{
		try
		{
			std::ifstream ifff("guilds/" + guildname + ".json");
			if (ifff.fail())
			{
				ifff.close();
				SendConsole("Failed loading guild (updateGuild) From " + static_cast<PlayerInfo*>(peer->data)->displayName, "ERROR");
				static_cast<PlayerInfo*>(peer->data)->guild = "";
			}
			else
			{
				json j;
				ifff >> j;
				vector<string> gmembers;
				const int gfbg = j["backgroundflag"];
				const int gffg = j["foregroundflag"];
				const auto gstatement = j["GuildStatement"].get<std::string>();
				const auto gleader = j["Leader"].get<std::string>();
				const int glevel = j["GuildLevel"];
				for (auto i = 0; i < j["Member"].size(); i++)
				{
					gmembers.push_back(j["Member"][i]);
				}
				if (find(gmembers.begin(), gmembers.end(), static_cast<PlayerInfo*>(peer->data)->rawName) == gmembers.end())
				{
					static_cast<PlayerInfo*>(peer->data)->guild = "";
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->guildBg = gfbg;
					static_cast<PlayerInfo*>(peer->data)->guildFg = gffg;
					static_cast<PlayerInfo*>(peer->data)->guildStatement = gstatement;
					static_cast<PlayerInfo*>(peer->data)->guildLeader = gleader;
					static_cast<PlayerInfo*>(peer->data)->guildMembers = gmembers;
					static_cast<PlayerInfo*>(peer->data)->guildlevel = glevel;
				}
			}
			ifff.close();
		}
		catch (std::exception&)
		{
			SendConsole("updateGuild Critical error details: rawName(" + static_cast<PlayerInfo*>(peer->data)->rawName + ")", "ERROR");
			enet_peer_disconnect_now(peer, 0);
		}
		catch (std::runtime_error&)
		{
			SendConsole("updateGuild Critical error details: name(" + static_cast<PlayerInfo*>(peer->data)->rawName + ")", "ERROR");
			enet_peer_disconnect_now(peer, 0);
		}
		catch (...)
		{
			SendConsole("updateGuild Critical error details: name(" + static_cast<PlayerInfo*>(peer->data)->rawName + ")", "ERROR");
			enet_peer_disconnect_now(peer, 0);
		}
	}
}

void updateEntrance(ENetPeer* peer, int foreground, int x, int y, bool open, int bg, bool updateall) {
	BYTE* data = new BYTE[69];// memset(data, 0, 69);
	for (int i = 0; i < 69; i++) data[i] = 0;
	int four = 4; int five = 5; int eight = 8;
	int huhed = (65536 * bg) + foreground; int loled = 128;

	memcpy(data, &four, 4);
	memcpy(data + 4, &five, 4);
	memcpy(data + 16, &eight, 4);
	memcpy(data + 48, &x, 4);
	memcpy(data + 52, &y, 4);
	memcpy(data + 56, &eight, 4);
	memcpy(data + 60, &foreground, 4);
	memcpy(data + 62, &bg, 4);

	if (open) {
		int state = 0;
		memcpy(data + 66, &loled, 4);
		memcpy(data + 68, &state, 4);
	}
	else {
		int state = 100;
		int yeetus = 25600;
		memcpy(data + 67, &yeetus, 5);
		memcpy(data + 68, &state, 4);
	}
	ENetPacket* p = enet_packet_create(data, 69, ENET_PACKET_FLAG_RELIABLE);

	if (updateall)
	{
		ENetPeer* currentPeer;
		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			if (isHere(peer, currentPeer)) {
				enet_peer_send(currentPeer, 0, p);
			}
		}
	}
	else
	{
		enet_peer_send(peer, 0, p);
	}
	delete data;
}

inline void updatepeffect(ENetPeer* peer)
{
	if (static_cast<PlayerInfo*>(peer->data)->haveGrowId)
	{
		int puncheffect;
		ifstream WorldSys("misc/effect/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
		WorldSys >> puncheffect;
		WorldSys.close();
		static_cast<PlayerInfo*>(peer->data)->effect = puncheffect;
		sendPuncheffectpeer(peer, puncheffect);
	}
}

inline void changetile(ENetPeer* peer, const int x, const int y)
{
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			BlockVisual data3;
			data3.packetType = 0x5;
			data3.characterState = 8;
			data3.charStat = 8;
			data3.blockid = 260;
			data3.backgroundid = 260;
			data3.visual = 0x00400000;
			data3.punchX = x;
			data3.punchY = y;
			data3.netID = static_cast<PlayerInfo*>(peer->data)->netID;
			SendPacketRaw2(192, packBlockVisual(&data3), 100, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
}

inline int getPlayersCountInWorld(const string name)
{
	auto count = 0;
	for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (static_cast<PlayerInfo*>(currentPeer->data)->isinv == false && !static_cast<PlayerInfo*>(currentPeer->data)->Console)
		{
			if (static_cast<PlayerInfo*>(currentPeer->data)->currentWorld == name)
			{
				count++;
			}
		}
	}
	return count;
}

inline void sendPData(ENetPeer* peer, PlayerMoving* data)
{
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (peer != currentPeer)
		{
			if (isHere(peer, currentPeer))
			{
				data->netID = static_cast<PlayerInfo*>(peer->data)->netID;
				SendPacketRaw(4, packPlayerMoving(data), 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
			}
		}
	}
}

inline void sendArrow(ENetPeer* peer, const uint16_t itemid, const bool droppeditem)
{
	SendConsole("Function (sendArrow) Called details: itemid(" + to_string(itemid) + ") droppeditem(" + to_string(droppeditem) + ")", "INFO");
	PlayerMoving pmov;
	memset(&pmov, 0, sizeof(PlayerMoving));
	*reinterpret_cast<uint32_t*>(&pmov) = 37 | (droppeditem << 8);
	pmov.netID = itemid;
	const auto pmovpacked = packPlayerMoving(&pmov);
	const auto packet = new uint8_t[4 + 56];
	memset(packet, 0, 4 + 56);
	packet[0] = 4;
	memcpy(packet + 4, pmovpacked, sizeof(PlayerMoving));
	const auto epacket = enet_packet_create(packet, 4 + 56, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, epacket);
	delete pmovpacked;
	delete packet;
}
void InitializePacketWithMannequin(BYTE* raw)
{
	int i = 0;
	raw[i] = 0x05; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x08; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x09; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x17; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x22; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x8c; i++;
	raw[i] = 0x05; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x01; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x0e; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
}
inline void updateMannequin(
	ENetPeer* peer, int foreground, int x, int y, int background, string text,
	int clothHair, int clothHead, int clothMask,
	int clothHand, int clothNeck, int clothShirt,
	int clothPants, int clothFeet, int clothBack, bool sendPacketToEveryone = true, int blockState = 0)
{
	PlayerMoving sign;
	sign.packetType = 0x3;
	sign.characterState = 0x0;
	sign.x = x;
	sign.y = y;
	sign.punchX = x;
	sign.punchY = y;
	sign.XSpeed = 0;
	sign.YSpeed = 0;
	sign.netID = -1;
	sign.plantingTree = foreground;
	SendPacketRaw(4, packPlayerMoving(&sign), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);

	short textLen = text.size();
	int plength = 95 + textLen;
	BYTE* raw = new BYTE[plength];
	memset(raw, 0, plength);
	InitializePacketWithMannequin(raw);
	int negativeOne = -1;
	int adjhasdjk = 0xfdfdfdfd;
	int visor = 138;

	memcpy(raw + 44, &x, sizeof(int));
	memcpy(raw + 48, &y, sizeof(int));
	memcpy(raw + 56, &foreground, sizeof(short));
	memcpy(raw + 58, &background, sizeof(short));
	memcpy(raw + 60, &blockState, sizeof(short));
	memcpy(raw + 65, &textLen, sizeof(short));
	memcpy(raw + 67, text.c_str(), textLen);
	memcpy(raw + 68 + textLen, &negativeOne, sizeof(int));
	memcpy(raw + 72 + textLen, &clothHead, sizeof(short));
	memcpy(raw + 74 + textLen, &clothShirt, sizeof(short));
	memcpy(raw + 76 + textLen, &clothPants, sizeof(short));
	memcpy(raw + 78 + textLen, &clothFeet, sizeof(short));
	memcpy(raw + 80 + textLen, &clothMask, sizeof(short));
	memcpy(raw + 82 + textLen, &clothHand, sizeof(short));
	memcpy(raw + 84 + textLen, &clothBack, sizeof(short));
	memcpy(raw + 86 + textLen, &clothHair, sizeof(short));
	memcpy(raw + 88 + textLen, &clothNeck, sizeof(short));
	memcpy(raw + 91 + textLen, &adjhasdjk, sizeof(short));

	ENetPacket* p = enet_packet_create(0, plength + 4, ENET_PACKET_FLAG_RELIABLE);
	int four = 4;
	memcpy(p->data, &four, sizeof(int));
	memcpy((char*)p->data + 4, raw, plength);

	if (sendPacketToEveryone)
	{
		ENetPeer* currentPeer;
		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			if (isHere(peer, currentPeer)) {
				enet_peer_send(currentPeer, 0, p);
			}
		}
		delete raw;
	}
	else
	{
		enet_peer_send(peer, 0, p);
		delete raw;
	}
}
inline void updateStuffWeather(ENetPeer* peer, int x, int y, int tile, int bg, int gravity, bool isInverted, bool isSpinning)
{
	SendConsole("Function (updateStuffWeather) Called details: x(" + to_string(x) + ") y(" + to_string(y) + ") tile(" + to_string(tile) + ") bg(" + to_string(bg) + ") gravity(" + to_string(gravity) + ") isInverted(" + to_string(isInverted) + ") isSpinning(" + to_string(isSpinning) + ")", "INFO");
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			TileExtra data;
			data.packetType = 0x5;
			data.characterState = 8;
			data.punchX = x;
			data.punchY = y;
			data.charStat = 18;
			data.blockid = 3832;
			data.backgroundid = bg;
			data.visual = 0;
			auto n = tile;
			string hex = "";
			{
				std::stringstream ss;
				ss << std::hex << n;
				auto res(ss.str());
				hex = res + "31";
			}
			auto gravi = gravity;
			string hexg = "";
			{
				auto temp = gravi;
				if (gravi < 0) temp = -gravi;
				stringstream ss;
				ss << std::hex << temp;
				auto res(ss.str());
				hexg = res + "00";
			}
			auto xx = 0;
			stringstream ss;
			ss << std::hex << hex;
			if (!ss.fail())
			{
				ss >> xx;
			}
			data.displayblock = xx;
			auto xxs = 0;
			stringstream sss;
			sss << std::hex << hexg;
			if (!sss.fail())
			{
				sss >> xxs;
			}
			if (gravi < 0) xxs = -xxs;
			if (gravi < 0)
			{
				SendPacketRaw2(192, packStuffVisual(&data, 0x03FFFFFF, xxs), 102, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
			}
			else
			{
				SendPacketRaw2(192, packStuffVisual(&data, 0x02000000, xxs), 102, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
			}
			auto p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), 29));
			auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(currentPeer, 0, packet2);
			delete p2.data;
		}
	}
}

void sendStuffweather(ENetPeer* peer, int x, int y, uint16_t itemid, uint16_t gravity, bool spin, bool invert)
{
	PlayerMoving pmov;
	pmov.packetType = 5;
	pmov.characterState = 8;
	pmov.punchX = x;
	pmov.punchY = y;
	pmov.netID = -1;
	uint8_t* pmovpacked = packPlayerMoving(&pmov);
	*(uint32_t*)(pmovpacked + 52) = 10 + 8;
	uint8_t* packet = new uint8_t[4 + 56 + 10 + 8];
	memset(packet, 0, 4 + 56 + 10 + 8);
	packet[0] = 4;
	memcpy(packet + 4, pmovpacked, 56);
	*(uint16_t*)(packet + 4 + 56) = 3832; // bg machine id
	*(uint16_t*)(packet + 4 + 56 + 6) = 1;
	*(uint8_t*)(packet + 4 + 56 + 8) = 0x31;
	*(uint32_t*)(packet + 4 + 56 + 9) = itemid;
	*(uint32_t*)(packet + 4 + 56 + 13) = gravity;
	*(uint8_t*)(packet + 4 + 56 + 17) = spin | (invert << 1);
	ENetPacket* epacket = enet_packet_create(packet, 4 + 56 + 8 + 10, ENET_PACKET_FLAG_RELIABLE);

	enet_peer_send(peer, 0, epacket);

	delete pmovpacked;
	delete packet;
}
void sendBackground(ENetPeer* peer, int x, int y, uint16_t itemid)
{
	PlayerMoving pmov;
	pmov.packetType = 5;
	pmov.characterState = 8;
	pmov.punchX = x;
	pmov.punchY = y;
	pmov.netID = -1;
	uint8_t* pmovpacked = packPlayerMoving(&pmov);
	*(uint32_t*)(pmovpacked + 52) = 5 + 8;
	uint8_t* packet = new uint8_t[4 + 56 + 5 + 8];
	memset(packet, 0, 4 + 56 + 5 + 8);
	packet[0] = 4;
	memcpy(packet + 4, pmovpacked, 56);
	*(uint16_t*)(packet + 4 + 56) = 5000; // bg machine id
	*(uint16_t*)(packet + 4 + 56 + 6) = 1;
	*(uint8_t*)(packet + 4 + 56 + 8) = 0x28;
	*(uint16_t*)(packet + 4 + 56 + 9) = itemid;
	ENetPacket* epacket = enet_packet_create(packet, 4 + 56 + 8 + 5, ENET_PACKET_FLAG_RELIABLE);

	enet_peer_send(peer, 0, epacket);

	delete pmovpacked;
	delete packet;
}

inline void restoreplayernick(ENetPeer* peer)
{
	if (serverIsFrozen) return;
	if (static_cast<PlayerInfo*>(peer->data)->currentWorld == "EXIT") return;
	if (static_cast<PlayerInfo*>(peer->data)->isIn == false) return;
	if (static_cast<PlayerInfo*>(peer->data)->isNicked) return;
	if (static_cast<PlayerInfo*>(peer->data)->haveGrowId)
	{
		if (static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 0)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`cGrowZS`w] "+static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". `2" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`cGrowZS`w] `2" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
		else
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 0)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`cGrowZS`w] "+static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`cGrowZS`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
	}
	else
	{
		if (static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 0)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`cGrowZS`w] "+static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". `2" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`cGrowZS`w] `2" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
		else
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 0)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`cGrowZS`w] "+static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`cGrowZS`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
	}
	if (static_cast<PlayerInfo*>(peer->data)->haveGrowId)
	{
		if (static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 1)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`1VIP`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". `2" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`1VIP`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
		else
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 1)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`1VIP`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`1VIP`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
	}
	else
	{
		if (static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 1)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`1VIP`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". `2" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`1VIP`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
		else
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 1)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`1VIP`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`1VIP`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
	}

	if (static_cast<PlayerInfo*>(peer->data)->haveGrowId)
	{
		if (static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 2)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4You`wTube] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". `2" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4You`wTube] `2" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
		else
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 2)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4You`wTube] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4You`wTube] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
	}
	else
	{
		if (static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 2)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4You`wTube] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". `2" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4You`wTube] `2" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
		else
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 2)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4You`wTube] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4You`wTube] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
	}

	if (static_cast<PlayerInfo*>(peer->data)->haveGrowId)
	{
		if (static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 3)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`#Mods`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". `2" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`#Mods`w] `2" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
		else
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 3)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`#Mods`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`#Mods`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
	}
	else
	{
		if (static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 3)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`#Mods`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". `2" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`#Mods`w] `2" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
		else
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 3)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`#Mods`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`#Mods`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
	}

	if (static_cast<PlayerInfo*>(peer->data)->haveGrowId)
	{
		if (static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 4)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4Adm`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". `2" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4Adm`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
		else
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 4)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4Adm`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4Adm`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
	}
	else
	{
		if (static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 4)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4Adm`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". `2" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4Adm`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
		else
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 4)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4Adm`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4Adm`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
	}

	if (static_cast<PlayerInfo*>(peer->data)->haveGrowId)
	{
		if (static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 5)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`rGOD`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". `2" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`rGOD`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
		else
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 5)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`rGOD`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`rGOD`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
	}
	else
	{
		if (static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 5)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`rGOD`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". `2" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`rGOD`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
		else
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 5)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`rGOD`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`rGOD`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
	}

	if (static_cast<PlayerInfo*>(peer->data)->haveGrowId)
	{
		if (static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 6)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`6Manager`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". `2" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`6Manager`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
		else
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 6)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`6Manager`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`6Manager`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
	}
	else
	{
		if (static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 6)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`6Manager`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". `2" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`6Manager`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
		else
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 6)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`6Manager`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`6Manager`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
	}

	if (static_cast<PlayerInfo*>(peer->data)->haveGrowId)
	{
		if (static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 7)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4SCO`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". `2" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4SCO`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
		else
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 7)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4SCO`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4SCO`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
	}
	else
	{
		if (static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 7)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4SCO`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". `2" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4SCO`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
		else
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 7)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4SCO`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4SCO`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
	}

	if (static_cast<PlayerInfo*>(peer->data)->haveGrowId)
	{
		if (static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 8)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`cOwner`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". `2" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`cOwner`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
		else
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 8)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`cOwner`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`cOwner`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
	}
	else
	{
		if (static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 8)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`cOwner`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". `2" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`cOwner`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
		else
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 8)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`cOwner`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`cOwner`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
	}

	if (static_cast<PlayerInfo*>(peer->data)->haveGrowId)
	{
		if (static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 9)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4Server-Creator`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". `2" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4Server-Creator`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
		else
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 9)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4Server-Creator`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4Server-Creator`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
	}
	else
	{
		if (static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 9)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4Server-Creator`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". `2" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4Server-Creator`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
		else
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 9)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4Server-Creator`w] " + static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`w[`4Server-Creator`w] " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
	}
}

inline void updateplayer(ENetPeer* peer)
{
	const auto item = static_cast<PlayerInfo*>(peer->data)->cloth_back;
	if (item == 8552)
	{
		static_cast<PlayerInfo*>(peer->data)->isDr = true;
		static_cast<PlayerInfo*>(peer->data)->canDoubleJump = true;
	}
	else if (item == 1784 || item == 1674 || item == 9434 || item == 9006 || item == 1958 || getItemDef(item).name.find("Aura") != string::npos || getItemDef(item).name.find("Wings") != string::npos || getItemDef(item).name.find("Cape") != string::npos || item == 8580 || item == 9410 || item == 9306 || item == 10020 || item == 10012 || item == 10032 || item == 9466 || item == 10016 || item == 5136 || item == 9760 || item == 10022 || item == 9478 || item == 9506 || item == 9476 || item == 1970 || item == 8286 || item == 156 || item == 9434 || item == 8552 || item == 362 || item == 678 || item == 736 || item == 7734 || item == 7762 || item == 818 || item == 1206 || item == 1460 || item == 1550 || item == 1574 || item == 1668 || item == 1672 || item == 1824 || item == 1936 || item == 1938 || item == 2254 || item == 2256 || item == 2258 || item == 2260 || item == 2262 || item == 2264 || item == 2390 || item == 2392 || item == 3120 || item == 3308 || item == 3512 || item == 4534 || item == 4986 || item == 5754 || item == 6144 || item == 6334 || item == 6694 || item == 6818 || item == 6842 || item == 1934 || item == 3134 || item == 6004 || item == 1780 || item == 2158 || item == 2160 || item == 2162 || item == 2164 || item == 2166 || item == 2168 || item == 2438 || item == 2538 || item == 2778 || item == 3858 || item == 350 || item == 998 || item == 1738 || item == 2642 || item == 2982 || item == 3104 || item == 3144 || item == 5738 || item == 3112 || item == 2722 || item == 3114 || item == 4970 || item == 4972 || item == 5020 || item == 6284 || item == 4184 || item == 4628 || item == 5322 || item == 4112 || item == 4114 || item == 3442 || item == 9466 || item == 5136 || item == 9416 || item == 9356)
	{
		static_cast<PlayerInfo*>(peer->data)->canDoubleJump = true;
	}
	updatepeffect(peer);
}

inline void send_state(ENetPeer* peer)
{
	if (static_cast<PlayerInfo*>(peer->data)->currentWorld == "EXIT")
	{
		return;
	}
	const auto info = static_cast<PlayerInfo*>(peer->data);
	const auto netID = info->netID;
	const auto state = getState(info);
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			PlayerMoving data;
			auto water = 125.0f;
			data.packetType = 0x14;
			data.characterState = static_cast<PlayerInfo*>(peer->data)->characterState;
			data.x = 1000;
			if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 366)
			{
				data.y = -400;
			}
			else
			{
				data.y = 400;
			}
			data.punchX = 0;
			data.punchY = 0;
			data.XSpeed = 300;
			if (static_cast<PlayerInfo*>(peer->data)->cloth_back == 9472)
			{
				data.YSpeed = 600;
			}
			else
			{
				data.YSpeed = 1000;
			}
			data.netID = netID;
			data.plantingTree = state;
			const auto raw = packPlayerMoving(&data);
			auto var = 0x818100;
			memcpy(raw + 1, &var, 3);
			memcpy(raw + 16, &water, 4);
			SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
	restoreplayernick(peer);
	Player::OnNameChanged(peer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->displayName);
	if (static_cast<PlayerInfo*>(peer->data)->skill == "Farmer")
	{
		auto p2 = packetEnd(appendIntx(appendIntx(appendIntx(appendIntx(appendString(createPacket(), "OnGuildDataChanged"), 1), 2), 7064), 0));
		memcpy(p2.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
		const auto packet3 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
		for (auto currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				enet_peer_send(currentPeer, 0, packet3);
			}
		}
		delete p2.data;
	}
	if (static_cast<PlayerInfo*>(peer->data)->skill == "Miner")
	{
		auto p2 = packetEnd(appendIntx(appendIntx(appendIntx(appendIntx(appendString(createPacket(), "OnGuildDataChanged"), 1), 2), 98), 0));
		memcpy(p2.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
		const auto packet3 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
		for (auto currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				enet_peer_send(currentPeer, 0, packet3);
			}
		}
		delete p2.data;
	}
	updateplayer(peer);
	if (static_cast<PlayerInfo*>(peer->data)->isZombie == true || static_cast<PlayerInfo*>(peer->data)->cloth_feet == 898 || static_cast<PlayerInfo*>(peer->data)->cloth_feet == 1830 || static_cast<PlayerInfo*>(peer->data)->cloth_feet == 1966)
	{
		playerconfig(peer, 1150, 130, 0x14);
	}
}
void sendEffectToWorld(ENetPeer* peer)
{
	send_state(peer); //here
	sendPuncheffectpeer(peer, ((PlayerInfo*)(peer->data))->effect);
	sendPuncheffect(peer, ((PlayerInfo*)(peer->data))->effect);

}

inline void end_surgery(ENetPeer* peer, bool Fail)
{

	if (Fail)
	{
		WorldInfo* world = getPlyersWorld(peer);
		Player::OnConsoleMessage(peer, "You couldn't save them!");
		Player::OnConsoleMessage(peer, "You are not allowed to perform surgery for a while! (`$Malpractice`` mod added, `$1 hour`` left)");
		ENetPeer* currentPeer;
		for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				Player::PlayAudio(currentPeer, "audio/metal_destroy.wav", 0);
			}
		}
		if (static_cast<PlayerInfo*>(peer->data)->lastPunchX >= 0 && static_cast<PlayerInfo*>(peer->data)->lastPunchY >= 0)
		{
			world->items[static_cast<PlayerInfo*>(peer->data)->lastPunchX + (static_cast<PlayerInfo*>(peer->data)->lastPunchY * world->width)].foreground = 0;
			PlayerMoving data3;
			data3.packetType = 0x3;
			data3.characterState = 0x0;
			data3.x = static_cast<PlayerInfo*>(peer->data)->lastPunchX;
			data3.y = static_cast<PlayerInfo*>(peer->data)->lastPunchY;
			data3.punchX = static_cast<PlayerInfo*>(peer->data)->lastPunchX;
			data3.punchY = static_cast<PlayerInfo*>(peer->data)->lastPunchY;
			data3.XSpeed = 0;
			data3.YSpeed = 0;
			data3.netID = -1;
			data3.plantingTree = 0;
			for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
			{
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
				if (isHere(peer, currentPeer))
				{
					auto raw = packPlayerMoving(&data3);
					raw[2] = 0;
					raw[3] = 0;
					SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
					Player::OnParticleEffect(currentPeer, 57, static_cast<PlayerInfo*>(peer->data)->lastPunchX * 32, static_cast<PlayerInfo*>(peer->data)->lastPunchY * 32, 0);
				}
			}
		}
		ofstream surgery("buffs/surgery/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
		surgery << (GetCurrentTimeInternalSeconds() + (60 * 60)) << endl;
		surgery.close();
		static_cast<PlayerInfo*>(peer->data)->SurgeryTime = (GetCurrentTimeInternalSeconds() + (60 * 60));
	}
	else
	{
		if (SurgeryDay)
		{
			ofstream surgery("buffs/surgery/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
			surgery << (GetCurrentTimeInternalSeconds() + (30 * 60)) << endl;
			surgery.close();
			static_cast<PlayerInfo*>(peer->data)->SurgeryTime = (GetCurrentTimeInternalSeconds() + (30 * 60));
		}
		else
		{
			ofstream surgery("buffs/surgery/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
			surgery << (GetCurrentTimeInternalSeconds() + (20 * 60)) << endl;
			surgery.close();
			static_cast<PlayerInfo*>(peer->data)->SurgeryTime = (GetCurrentTimeInternalSeconds() + (20 * 60));
		}
	}

	static_cast<PlayerInfo*>(peer->data)->PatientDiagnosis = "";
	static_cast<PlayerInfo*>(peer->data)->PatientPulse = "";
	static_cast<PlayerInfo*>(peer->data)->PatientStatus = "";
	static_cast<PlayerInfo*>(peer->data)->PatientTemperature = 0;
	static_cast<PlayerInfo*>(peer->data)->OperationSite = "";
	static_cast<PlayerInfo*>(peer->data)->PatientIncisions = 0;
	static_cast<PlayerInfo*>(peer->data)->PerformingSurgery = false;
	static_cast<PlayerInfo*>(peer->data)->HardToSee = false;
	static_cast<PlayerInfo*>(peer->data)->PatientLosingBlood = false;
	static_cast<PlayerInfo*>(peer->data)->TempColor = "";
	static_cast<PlayerInfo*>(peer->data)->UnlockedAntibiotic = false;
	static_cast<PlayerInfo*>(peer->data)->PatientHeartStopped = false;
	static_cast<PlayerInfo*>(peer->data)->SurgeryCooldown = true;
	static_cast<PlayerInfo*>(peer->data)->PatientTemperatureRise = 0;
	static_cast<PlayerInfo*>(peer->data)->IncisionsColor = "";
	static_cast<PlayerInfo*>(peer->data)->FixIt = false;
	static_cast<PlayerInfo*>(peer->data)->Ultrasound = 0;



	static_cast<PlayerInfo*>(peer->data)->SurgItem1 = 4320;
	static_cast<PlayerInfo*>(peer->data)->SurgItem2 = 4320;
	static_cast<PlayerInfo*>(peer->data)->SurgItem3 = 4320;
	static_cast<PlayerInfo*>(peer->data)->SurgItem4 = 4320;
	static_cast<PlayerInfo*>(peer->data)->SurgItem5 = 4320;
	static_cast<PlayerInfo*>(peer->data)->SurgItem6 = 4320;
	static_cast<PlayerInfo*>(peer->data)->SurgItem7 = 4320;
	static_cast<PlayerInfo*>(peer->data)->SurgItem8 = 4320;
	static_cast<PlayerInfo*>(peer->data)->SurgItem9 = 4320;
	static_cast<PlayerInfo*>(peer->data)->SurgItem10 = 4320;
	static_cast<PlayerInfo*>(peer->data)->SurgItem11 = 4320;
	static_cast<PlayerInfo*>(peer->data)->SurgItem12 = 4320;
	static_cast<PlayerInfo*>(peer->data)->SurgItem13 = 4320;
}

void sendHeatwave(ENetPeer* peer, int x, int y, uint8_t red, uint8_t green, uint8_t blue)
{
	PlayerMoving pmov;
	pmov.packetType = 5;
	pmov.characterState = 8;
	pmov.punchX = x;
	pmov.punchY = y;
	pmov.netID = -1;
	uint8_t* pmovpacked = packPlayerMoving(&pmov);
	*(uint32_t*)(pmovpacked + 52) = 5 + 8;
	uint8_t* packet = new uint8_t[4 + 56 + 5 + 8];
	memset(packet, 0, 4 + 56 + 5 + 8);
	packet[0] = 4;
	memcpy(packet + 4, pmovpacked, 56);
	*(uint16_t*)(packet + 4 + 56) = 3694; // heatwave id
	*(uint16_t*)(packet + 4 + 56 + 6) = 1;
	*(uint8_t*)(packet + 4 + 56 + 8) = 0x28;
	*(uint32_t*)(packet + 4 + 56 + 9) = (blue << 24) | (green << 16) | (red << 8);
	ENetPacket* epacket = enet_packet_create(packet, 4 + 56 + 8 + 5, ENET_PACKET_FLAG_RELIABLE);

	enet_peer_send(peer, 0, epacket);

	delete pmovpacked;
	delete packet;

}

inline void sendPlayerLeave(ENetPeer* peer, PlayerInfo* player)
{
	if (serverIsFrozen) return;
	((PlayerInfo*)(peer->data))->checky = 0;
	((PlayerInfo*)(peer->data))->checkx = 0;
	((PlayerInfo*)(peer->data))->ischeck = false;
	((PlayerInfo*)(peer->data))->isUsed = false;
	if (game1status == true && static_cast<PlayerInfo*>(peer->data)->currentWorld == "GAME1")
	{
		static_cast<PlayerInfo*>(peer->data)->currentWorld = "START";
		int players = getPlayersCountInWorld("GAME1");
		if (players <= 1)
		{
			ENetPeer* currentPeer2;
			for (currentPeer2 = server->peers;
				currentPeer2 < &server->peers[server->peerCount];
				++currentPeer2)
			{
				if (currentPeer2->state != ENET_PEER_STATE_CONNECTED) continue;
				if (static_cast<PlayerInfo*>(currentPeer2->data)->isinv == false && !static_cast<PlayerInfo*>(currentPeer2->data)->Console)
				{
					if (static_cast<PlayerInfo*>(currentPeer2->data)->currentWorld == "GAME1")
					{
						int currentgems = 0;
						ifstream fs("gemdb/" + static_cast<PlayerInfo*>(currentPeer2->data)->rawName + ".txt");
						fs >> currentgems;
						fs.close();

						currentgems += betamount;
						GamePacket psa = packetEnd(appendInt(appendString(createPacket(), "OnSetBux"), currentgems));
						ENetPacket* packetsa = enet_packet_create(psa.data, psa.len, ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer2, 0, packetsa);
						ofstream of("gemdb/" + static_cast<PlayerInfo*>(currentPeer2->data)->rawName + ".txt");
						of << currentgems;
						of.close();


						Player::OnConsoleMessage(currentPeer2, "`oYou won `$" + to_string(betamount) + "`o gems!");
						string text = "action|play_sfx\nfile|audio/success.wav\ndelayMS|0\n";
						BYTE* data = new BYTE[5 + text.length()];
						BYTE zero = 0;
						int type = 3;
						memcpy(data, &type, 4);
						memcpy(data + 4, text.c_str(), text.length());
						memcpy(data + 4 + text.length(), &zero, 1);

						ENetPacket* packet2 = enet_packet_create(data,
							5 + text.length(),
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer2, 0, packet2);
						delete data;

						ENetPeer* currentPeer3;
						for (currentPeer3 = server->peers;
							currentPeer3 < &server->peers[server->peerCount];
							++currentPeer3)
						{
							if (currentPeer3->state != ENET_PEER_STATE_CONNECTED) continue;
							if (static_cast<PlayerInfo*>(currentPeer3->data)->isinv == false && !static_cast<PlayerInfo*>(currentPeer3->data)->Console)
							{
								static_cast<PlayerInfo*>(currentPeer3->data)->game1bet = false;
								Player::OnConsoleMessage(currentPeer3, "`oThe GAME1 is over! The winner `$" + static_cast<PlayerInfo*>(currentPeer2->data)->rawName + " `owins `$" + to_string(betamount) + " `ogems.");
							}
						}

						break;
					}
				}
			}
			auto world2 = worldDB.get2("GAME1BACKUP").ptr;
			getWorldInfoByName("GAME1")->items = world2->items;
			worldDB.remove2("GAME1BACKUP");

			betamount = 0;
			game1status = false;
		}
	}

	if (game2status == true && static_cast<PlayerInfo*>(peer->data)->currentWorld == "GAME2")
	{
		static_cast<PlayerInfo*>(peer->data)->currentWorld = "START";
		int players = getPlayersCountInWorld("GAME2");
		if (players <= 1)
		{
			ENetPeer* currentPeer2;
			for (currentPeer2 = server->peers;
				currentPeer2 < &server->peers[server->peerCount];
				++currentPeer2)
			{
				if (currentPeer2->state != ENET_PEER_STATE_CONNECTED) continue;
				if (static_cast<PlayerInfo*>(currentPeer2->data)->isinv == false && !static_cast<PlayerInfo*>(currentPeer2->data)->Console)
				{
					if (static_cast<PlayerInfo*>(currentPeer2->data)->currentWorld == "GAME2")
					{
						int currentgems = 0;
						ifstream fs("gemdb/" + static_cast<PlayerInfo*>(currentPeer2->data)->rawName + ".txt");
						fs >> currentgems;
						fs.close();

						currentgems += bet2amount;
						GamePacket psa = packetEnd(appendInt(appendString(createPacket(), "OnSetBux"), currentgems));
						ENetPacket* packetsa = enet_packet_create(psa.data, psa.len, ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer2, 0, packetsa);
						ofstream of("gemdb/" + static_cast<PlayerInfo*>(currentPeer2->data)->rawName + ".txt");
						of << currentgems;
						of.close();


						Player::OnConsoleMessage(currentPeer2, "`oYou won `$" + to_string(bet2amount) + "`o gems!");
						string text = "action|play_sfx\nfile|audio/success.wav\ndelayMS|0\n";
						BYTE* data = new BYTE[5 + text.length()];
						BYTE zero = 0;
						int type = 3;
						memcpy(data, &type, 4);
						memcpy(data + 4, text.c_str(), text.length());
						memcpy(data + 4 + text.length(), &zero, 1);

						ENetPacket* packet2 = enet_packet_create(data,
							5 + text.length(),
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer2, 0, packet2);
						delete data;

						ENetPeer* currentPeer3;
						for (currentPeer3 = server->peers;
							currentPeer3 < &server->peers[server->peerCount];
							++currentPeer3)
						{
							if (currentPeer3->state != ENET_PEER_STATE_CONNECTED) continue;
							if (static_cast<PlayerInfo*>(currentPeer3->data)->isinv == false && !static_cast<PlayerInfo*>(currentPeer3->data)->Console)
							{
								static_cast<PlayerInfo*>(currentPeer3->data)->game2bet = false;
								Player::OnConsoleMessage(currentPeer3, "`oThe GAME2 is over! The winner `$" + static_cast<PlayerInfo*>(currentPeer2->data)->rawName + " `owins `$" + to_string(bet2amount) + " `ogems.");
							}
						}

						break;
					}
				}
			}
			bet2amount = 0;
			game2status = false;
		}
	}

	if (static_cast<PlayerInfo*>(peer->data)->Fishing)
	{
		static_cast<PlayerInfo*>(peer->data)->TriggerFish = false;
		static_cast<PlayerInfo*>(peer->data)->FishPosX = 0;
		static_cast<PlayerInfo*>(peer->data)->FishPosY = 0;
		static_cast<PlayerInfo*>(peer->data)->Fishing = false;
		send_state(peer);
	}
	if (static_cast<PlayerInfo*>(peer->data)->PerformingSurgery)
	{
		end_surgery(peer, true);
	}
	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	if (static_cast<PlayerInfo*>(peer->data)->haveGrowId && static_cast<PlayerInfo*>(peer->data)->isIn == true)
	{
		ifstream fg("players/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".json");
		json j;
		fg >> j;
		fg.close();

		j["xp"] = static_cast<PlayerInfo*>(peer->data)->xp;

		ofstream fs("players/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".json");
		fs << j;
		fs.close();
	}
	static_cast<PlayerInfo*>(peer->data)->cpY = 0;
	static_cast<PlayerInfo*>(peer->data)->cpY = 0;
	static_cast<PlayerInfo*>(peer->data)->usedCP = false;
	if (find(static_cast<PlayerInfo*>(peer->data)->lastworlds.begin(), static_cast<PlayerInfo*>(peer->data)->lastworlds.end(), static_cast<PlayerInfo*>(peer->data)->currentWorld) != static_cast<PlayerInfo*>(peer->data)->lastworlds.end())
	{
	}
	else
	{
		static_cast<PlayerInfo*>(peer->data)->lastworlds.push_back(static_cast<PlayerInfo*>(peer->data)->currentWorld);
	}
	static_cast<PlayerInfo*>(peer->data)->ischeck = false;
	auto p = packetEnd(appendString(appendString(createPacket(), "OnRemove"), "netID|" + std::to_string(static_cast<PlayerInfo*>(peer->data)->netID) + "\n"));
	auto p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`5<`w" + static_cast<PlayerInfo*>(peer->data)->displayName + "`` `5left, `w" + std::to_string(getPlayersCountInWorld(static_cast<PlayerInfo*>(peer->data)->currentWorld) - 1) + "`` `5others here>```w"));
	const string text = "action|play_sfx\nfile|audio/door_shut.wav\ndelayMS|0\n";
	const auto data = new BYTE[5 + text.length()];
	BYTE zero = 0;
	auto type = 3;
	memcpy(data, &type, 4);
	memcpy(data + 4, text.c_str(), text.length());
	memcpy(data + 4 + text.length(), &zero, 1);
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (static_cast<PlayerInfo*>(currentPeer->data)->currentWorld == "EXIT") continue;
		if (static_cast<PlayerInfo*>(currentPeer->data)->isIn == false) continue;
		if (isHere(peer, currentPeer))
		{
			const auto packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet);
			{
				const auto net_packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, net_packet);
				const auto packet3 = enet_packet_create(data, 5 + text.length(), ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet3);
			}
			if (static_cast<PlayerInfo*>(peer->data)->isinv == false && !static_cast<PlayerInfo*>(peer->data)->Console)
			{
				const auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2);
				auto p4 = packetEnd(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), static_cast<PlayerInfo*>(peer->data)->netID), "`5<`w" + static_cast<PlayerInfo*>(peer->data)->displayName + "`` `5left, `w" + std::to_string(getPlayersCountInWorld(static_cast<PlayerInfo*>(peer->data)->currentWorld) - 1) + "`` `5others here>```w"));
				const auto packet4 = enet_packet_create(p4.data, p4.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet4);
				delete p4.data;
			}
		}
	}
	delete p.data;
	delete p2.data;
	delete[] data;
}

inline void sendRoulete(ENetPeer* peer)
{
	using namespace std::chrono;
	if (static_cast<PlayerInfo*>(peer->data)->lastSPIN + 1500 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count())
	{
		static_cast<PlayerInfo*>(peer->data)->lastSPIN = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
	}
	else
	{
		return;
	}
	const auto val = rand() % 36;
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			auto name = static_cast<PlayerInfo*>(peer->data)->displayName;
			if (val == 1 || val == 3 || val == 5 || val == 7 || val == 9 || val == 12 || val == 14 || val == 16 || val == 18 || val == 19 || val == 21 || val == 23 || val == 25 || val == 27 || val == 30 || val == 32 || val == 34 || val == 36)
			{
				auto p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), static_cast<PlayerInfo*>(peer->data)->netID), "`w[" + name + " `wspun the wheel and got `4" + std::to_string(val) + "`w!]"), 0));
				auto respawnTimeout = 2000;
				auto deathFlag = 0x19;
				memcpy(p2.data + 24, &respawnTimeout, 4);
				memcpy(p2.data + 56, &deathFlag, 4);
				const auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2);
				delete p2.data;
				auto p2s = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`7[`w" + name + " `ospun the wheel and got `4" + std::to_string(val) + "`o!`7]"));
				memcpy(p2s.data + 24, &respawnTimeout, 4);
				memcpy(p2s.data + 56, &deathFlag, 4);
				const auto packet2s = enet_packet_create(p2s.data, p2s.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2s);
				delete p2s.data;
			}
			else if (val == 2 || val == 4 || val == 6 || val == 8 || val == 10 || val == 11 || val == 13 || val == 15 || val == 17 || val == 20 || val == 22 || val == 24 || val == 26 || val == 28 || val == 29 || val == 31 || val == 33 || val == 35)
			{
				auto p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), static_cast<PlayerInfo*>(peer->data)->netID), "`w[" + name + " `wspun the wheel and got `b" + std::to_string(val) + "`w!]"), 0));
				auto respawnTimeout = 2000;
				auto deathFlag = 0x19;
				memcpy(p2.data + 24, &respawnTimeout, 4);
				memcpy(p2.data + 56, &deathFlag, 4);
				const auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2);
				delete p2.data;
				auto p2s = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`7[`w" + name + " `ospun the wheel and got `b" + std::to_string(val) + "`o!`7]"));
				memcpy(p2s.data + 24, &respawnTimeout, 4);
				memcpy(p2s.data + 56, &deathFlag, 4);
				const auto packet2s = enet_packet_create(p2s.data, p2s.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2s);
				delete p2s.data;
			}
			else if (val == 0 || val == 37)
			{
				auto p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), static_cast<PlayerInfo*>(peer->data)->netID), "`w[" + name + " `wspun the wheel and got `20`w!]"), 0));
				auto respawnTimeout = 2000;
				auto deathFlag = 0x19;
				memcpy(p2.data + 24, &respawnTimeout, 4);
				memcpy(p2.data + 56, &deathFlag, 4);
				const auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2);
				delete p2.data;
				auto p2s = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`7[`w" + name + " `ospun the wheel and got `20`o!`7]"));
				memcpy(p2s.data + 24, &respawnTimeout, 4);
				memcpy(p2s.data + 56, &deathFlag, 4);
				const auto packet2s = enet_packet_create(p2s.data, p2s.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2s);
				delete p2s.data;
			}
		}
	}
}

#include "packet_initialize/display_block.h"

void updateDoor(ENetPeer* peer, int foreground, int x, int y, int background, string text, bool locked, bool sendPacketToEveryone = true, int visuals = 0) {
	PlayerMoving sign;
	sign.packetType = 0x3;
	sign.characterState = 0x0;
	sign.x = 0x56;
	sign.y = 0x15;
	sign.punchX = 0x56;
	sign.punchY = 0x15;
	sign.XSpeed = 0;
	sign.YSpeed = 0;
	sign.netID = -1;
	sign.plantingTree = 0x0b82;
	SendPacketRaw(4, packPlayerMoving(&sign), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
	BYTE a;
	BYTE b;
	if (!locked) a = 0x00; // 0x08 for locked
	else a = 0x08;
	if (!locked) b = 0xeb; // 0x98 for locked
	else b = 0x98;
	uint32_t c = 0xfdfdfdfd;
	short textLen = (short)text.size();
	int plength = 73 + textLen;
	BYTE* raw = new BYTE[plength];
	memset(raw, 0, plength);
	InitializePacketWithUnlockedDoor(raw);
	memcpy(raw + 44, &x, sizeof(int));
	memcpy(raw + 48, &y, sizeof(int));
	memcpy(raw + 56, &foreground, sizeof(short));
	memcpy(raw + 58, &background, sizeof(short));
	memcpy(raw + 60, &visuals, sizeof(int));
	memcpy(raw + 65, &textLen, sizeof(short));
	memcpy(raw + 67, text.c_str(), textLen);
	memcpy(raw + 67 + textLen, &a, 1);
	memcpy(raw + 68 + textLen, &b, 1);
	memcpy(raw + 69 + textLen, &c, 4);
	ENetPacket* p = enet_packet_create(0, plength + 4, ENET_PACKET_FLAG_RELIABLE);
	int four = 4;
	memcpy(p->data, &four, sizeof(int));
	memcpy((char*)p->data + 4, raw, plength);
	if (sendPacketToEveryone) {
		ENetPeer* currentPeer;
		for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer)) {
				enet_peer_send(currentPeer, 0, p);
			}
		}
		delete raw;
	}
	else {
		enet_peer_send(peer, 0, p);
		delete raw;
	}
}

inline void UpdateDisplayVisuals(ENetPeer* peer, int foreground, int x, int y, int background, int itemid, bool sendPacketToEveryone = true)
{
	SendConsole("Function (UpdateDisplayVisuals) Called details: foreground(" + to_string(foreground) + ") x(" + to_string(x) + ") y(" + to_string(y) + ") background(" + to_string(background) + ") itemid(" + to_string(itemid) + ") sendPacketToEveryone(" + to_string(sendPacketToEveryone) + ")", "INFO");
	PlayerMoving sign;
	sign.packetType = 0x3;
	sign.characterState = 0x0;
	sign.x = 0x56;
	sign.y = 0x15;
	sign.punchX = 0x56;
	sign.punchY = 0x15;
	sign.XSpeed = 0;
	sign.YSpeed = 0;
	sign.netID = -1;
	sign.plantingTree = 0x0b82;
	SendPacketRaw(4, packPlayerMoving(&sign), 56, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
	const auto plength = 73;
	const auto raw = new BYTE[plength];
	memset(raw, 0, plength);
	InitializePacketWithDisplayBlock(raw);
	memcpy(raw + 44, &x, sizeof(int));
	memcpy(raw + 48, &y, sizeof(int));
	memcpy(raw + 56, &foreground, sizeof(short));
	memcpy(raw + 58, &background, sizeof(short));
	memcpy(raw + 65, &itemid, sizeof(int));
	const auto p = enet_packet_create(nullptr, plength + 4, ENET_PACKET_FLAG_RELIABLE);
	auto four = 4;
	memcpy(p->data, &four, sizeof(int));
	memcpy(reinterpret_cast<char*>(p->data) + 4, raw, plength);
	if (sendPacketToEveryone)
	{
		for (auto currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				enet_peer_send(currentPeer, 0, p);
			}
		}
		delete raw;
	}
	else
	{
		enet_peer_send(peer, 0, p);
		delete raw;
	}
}

void updateSignSound(ENetPeer* peer, int foreground, int x, int y, string text, int background)
{
	int hmm = 8, wot = text.length(), lol = 0, wut = 5;
	int yeh = hmm + 3 + 1, idk = 15 + wot, lmao = -1, yey = 2; //idk = text_len + 15, wut = type(?), wot = text_len, yey = len of text_len
	int ok = 52 + idk;
	int kek = ok + 4, yup = ok - 8 - idk;
	int thonk = 4, magic = 56, wew = ok + 5 + 4;
	int wow = magic + 4 + 5;
	BYTE* data = new BYTE[kek];
	ENetPacket* p = enet_packet_create(0, wew, ENET_PACKET_FLAG_RELIABLE);
	for (int i = 0; i < kek; i++) data[i] = 0;
	memcpy(data, &wut, thonk);
	memcpy(data + yeh, &hmm, thonk); //read discord
	memcpy(data + yup, &x, 4);
	memcpy(data + yup + 4, &y, 4);
	memcpy(data + 4 + yup + 4, &idk, thonk);
	memcpy(data + magic, &foreground, yey);
	memcpy(data + magic + 2, &background, yey); //p100 fix by the one and only lapada
	memcpy(data + thonk + magic, &lol, thonk);
	memcpy(data + magic + 4 + thonk, &yey, 1);
	memcpy(data + wow, &wot, yey); //data + wow = text_len
	memcpy(data + yey + wow, text.c_str(), wot); //data + text_len_len + text_len_offs = text
	memcpy(data + ok, &lmao, thonk); //end ?
	memcpy(p->data, &thonk, thonk);
	memcpy((char*)p->data + thonk, data, kek); //kek = data_len
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer)) {
			enet_peer_send(currentPeer, 0, p);
		}
	}
	delete data;
}

inline void UpdateTreeVisuals(ENetPeer* peer, int foreground, int x, int y, int background, int fruitCount, int timeIntoGrowth, bool forEveryone, int blockStateFlags)
{
	auto hmm = 8;
	auto packetType = 5;
	const auto yeh = hmm + 3 + 1;
	auto idk = 15 + 4;
	auto blockState = blockStateFlags;
	auto bubble_type = 4;
	const auto ok = 52 + idk;
	const auto packetSize = ok + 4;
	const auto yup = ok - 8 - idk;
	auto four = 4;
	const auto magic = 56;
	const auto wew = ok + 5 + 4;
	auto fc = static_cast<short>(fruitCount);
	auto time = static_cast<int>(timeIntoGrowth);
	blockState |= 0x100000;
	const auto data = new BYTE[packetSize];
	const auto p = enet_packet_create(nullptr, wew, ENET_PACKET_FLAG_RELIABLE);
	memset(data, 0, packetSize);
	memcpy(data, &packetType, sizeof(int));
	memcpy(data + yeh, &hmm, sizeof(int));
	memcpy(data + yup, &x, sizeof(int));
	memcpy(data + yup + 4, &y, sizeof(int));
	memcpy(data + 4 + yup + 4, &idk, sizeof(int));
	memcpy(data + magic, &foreground, sizeof(short));
	memcpy(data + magic + 2, &background, sizeof(short));
	memcpy(data + magic + 4, &blockState, sizeof(int));
	memcpy(data + magic + 8, &bubble_type, sizeof(BYTE));
	memcpy(data + magic + 9 + 0, &time, 4);
	memcpy(data + magic + 9 + 4, &fc, 1);
	memcpy(data + ok, &blockState, sizeof(int));
	memcpy(p->data, &four, four);
	memcpy(reinterpret_cast<char*>(p->data) + four, data, packetSize);
	if (forEveryone)
	{
		for (auto currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				enet_peer_send(currentPeer, 0, p);
			}
		}
		delete data;
	}
	else
	{
		enet_peer_send(peer, 0, p);
		delete data;
	}
}

inline void UpdateMessageVisuals(ENetPeer* peer, int foreground, int x, int y, const string text, int background, const int bubbleType_ = 2, const bool sendPacketToEveryone = true, int blockState = 0)
{
	if (text.size() > 100) return;
	PlayerMoving sign;
	sign.packetType = 0x3;
	sign.characterState = 0x0;
	sign.x = x;
	sign.y = y;
	sign.punchX = x;
	sign.punchY = y;
	sign.XSpeed = 0;
	sign.YSpeed = 0;
	sign.netID = -1;
	sign.plantingTree = foreground;
	SendPacketRaw(4, packPlayerMoving(&sign), 56, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
	int hmm = 8, textLen = text.size(), PacketType = 5;
	const auto yeh = hmm + 3 + 1, idk = 15 + textLen, endMarker = -1, sizeofshort = 2;
	auto bubbleType = bubbleType_;
	const auto ok = 52 + idk;
	const auto kek = ok + 4, yup = ok - 8 - idk;
	const auto sizeofint = 4, magic = 56, wew = ok + 5 + 4;
	const auto wow = magic + 4 + 5;
	const auto data = new BYTE[kek];
	const auto p = enet_packet_create(nullptr, wew, ENET_PACKET_FLAG_RELIABLE);
	for (auto i = 0; i < kek; i++) data[i] = 0;
	memcpy(data, &PacketType, sizeof(int));
	memcpy(data + yeh, &hmm, sizeof(int));
	memcpy(data + yup, &x, sizeof(int));
	memcpy(data + yup + 4, &y, sizeof(int));
	memcpy(data + 4 + yup + 4, &idk, sizeof(int));
	memcpy(data + magic, &foreground, sizeof(short));
	memcpy(data + magic + 2, &background, sizeof(short));
	memcpy(data + sizeofint + magic, &blockState, sizeof(int));
	memcpy(data + magic + 4 + sizeofint, &bubbleType, sizeof(BYTE));
	memcpy(data + wow, &textLen, sizeof(short));
	memcpy(data + sizeofshort + wow, text.c_str(), textLen);
	memcpy(data + ok, &endMarker, sizeof(int));
	memcpy(p->data, &sizeofint, sizeof(int));
	memcpy(reinterpret_cast<char*>(p->data) + sizeofint, data, kek);
	if (sendPacketToEveryone)
	{
		for (auto currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				enet_peer_send(currentPeer, 0, p);
			}
		}
		delete data;
	}
	else
	{
		enet_peer_send(peer, 0, p);
		delete data;
	}
}

inline void UpdateUnlockedDoorVisuals(ENetPeer* peer, int foreground, int x, int y, int background, const string text, const bool sendPacketToEveryone = true, int visuals = 0)
{
	PlayerMoving sign;
	sign.packetType = 0x3;
	sign.characterState = 0x0;
	sign.x = 0x56;
	sign.y = 0x15;
	sign.punchX = 0x56;
	sign.punchY = 0x15;
	sign.XSpeed = 0;
	sign.YSpeed = 0;
	sign.netID = -1;
	sign.plantingTree = 0x0b82;
	SendPacketRaw(4, packPlayerMoving(&sign), 56, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
	BYTE a = 0x00;
	BYTE b = 0xeb;
	auto c = 0xfdfdfdfd;
	auto textLen = static_cast<short>(text.size());
	const auto plength = 73 + textLen;
	const auto raw = new BYTE[plength];
	memset(raw, 0, plength);
	InitializePacketWithUnlockedDoor(raw);
	memcpy(raw + 44, &x, sizeof(int));
	memcpy(raw + 48, &y, sizeof(int));
	memcpy(raw + 56, &foreground, sizeof(short));
	memcpy(raw + 58, &background, sizeof(short));
	memcpy(raw + 60, &visuals, sizeof(int));
	memcpy(raw + 65, &textLen, sizeof(short));
	memcpy(raw + 67, text.c_str(), textLen);
	memcpy(raw + 67 + textLen, &a, 1);
	memcpy(raw + 68 + textLen, &b, 1);
	memcpy(raw + 69 + textLen, &c, 4);
	const auto p = enet_packet_create(nullptr, plength + 4, ENET_PACKET_FLAG_RELIABLE);
	auto four = 4;
	memcpy(p->data, &four, sizeof(int));
	memcpy(reinterpret_cast<char*>(p->data) + 4, raw, plength);
	if (sendPacketToEveryone)
	{
		for (auto currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			if (isHere(peer, currentPeer))
			{
				enet_peer_send(currentPeer, 0, p);
			}
		}
		delete raw;
	}
	else
	{
		enet_peer_send(peer, 0, p);
		delete raw;
	}
}

inline void sendblockstate(ENetPeer* peer, int x, int y, int state)
{
	BlockVisual data;
	data.packetType = 0x5;
	data.characterState = 8;
	data.charStat = 8;
	data.blockid = 0;
	data.backgroundid = 0;
	data.visual = state;
	data.punchX = x;
	data.punchY = y;
	data.netID = static_cast<PlayerInfo*>(peer->data)->netID;
	SendPacketRaw2(192, packBlockVisual(&data), 100, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
}

inline void UpdateVisualsForBlock(ENetPeer* peer, const bool forEveryone, const int x, const int y, WorldInfo* worldInfo, bool useLockId = true)
{
	if (!worldInfo) return;
	const auto i = y * worldInfo->width + x;
	auto blockStateFlags = 0;
	if (worldInfo->items[i].flipped)
	{
		blockStateFlags |= 0x00200000;
	}
	if (worldInfo->items[i].water)
	{
		blockStateFlags |= 0x04000000;
	}
	if (worldInfo->items[i].glue)
	{
		blockStateFlags |= 0x08000000;
	}
	if (worldInfo->items[i].fire)
	{
		blockStateFlags |= 0x10000000;
	}
	if (worldInfo->items[i].red)
	{
		blockStateFlags |= 0x20000000;
	}
	if (worldInfo->items[i].green)
	{
		blockStateFlags |= 0x40000000;
	}
	if (worldInfo->items[i].blue)
	{
		// ReSharper disable once CppAssignedValueIsNeverUsed
		blockStateFlags |= 0x80000000;
	}
	else if (getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::MAIN_DOOR)
	{
		UpdateUnlockedDoorVisuals(peer, worldInfo->items[i].foreground, x, y, worldInfo->items[i].background, "EXIT", forEveryone, blockStateFlags);
	}
	else if (worldInfo->items[i].foreground == 2946)
	{
		UpdateDisplayVisuals(peer, worldInfo->items[i].foreground, x, y, worldInfo->items[i].background, worldInfo->items[i].intdata);
	}
	else if (worldInfo->items[i].foreground % 2 == 1)
	{
		UpdateTreeVisuals(peer, worldInfo->items[i].foreground, x, y, worldInfo->items[i].background, 3, 59, true, 0);
	}
	else if (blockStateFlags != 0)
	{
		UpdateMessageVisuals(peer, worldInfo->items[i].foreground, x, y, "", worldInfo->items[i].background, 0, forEveryone, blockStateFlags);
	}
}

inline void UpdateBlockState(ENetPeer* peer, const int x, const int y, bool forEveryone, WorldInfo* worldInfo)
{
	if (!worldInfo) return;
	const auto i = y * worldInfo->width + x;
	auto blockStateFlags = 0;
	if (worldInfo->items[i].flipped)
		blockStateFlags |= 0x00200000;
	if (worldInfo->items[i].water)
		blockStateFlags |= 0x04000000;
	if (worldInfo->items[i].glue)
		blockStateFlags |= 0x08000000;
	if (worldInfo->items[i].fire)
		blockStateFlags |= 0x10000000;
	if (worldInfo->items[i].red)
		blockStateFlags |= 0x20000000;
	if (worldInfo->items[i].green)
		blockStateFlags |= 0x40000000;
	if (worldInfo->items[i].blue)
		blockStateFlags |= 0x80000000;
	if (worldInfo->items[i].activated)
		blockStateFlags |= 0x00400000;
	if (blockStateFlags != 0)
	{
		TileExtra data;
		data.packetType = 0x5;
		data.characterState = 8;
		data.charStat = 8;
		data.blockid = worldInfo->items[i].foreground;
		data.backgroundid = worldInfo->items[i].background;
		data.visual = blockStateFlags;
		data.punchX = x;
		data.punchY = y;
		for (auto currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				SendPacketRaw2(192, packBlockVisual(&data), 100, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
			}
		}
	}
	else
	{
		TileExtra data;
		data.packetType = 0x5;
		data.characterState = 8;
		data.charStat = 8;
		data.blockid = worldInfo->items[i].foreground;
		data.backgroundid = worldInfo->items[i].background;
		data.visual = blockStateFlags;
		data.punchX = x;
		data.punchY = y;
		for (auto currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				SendPacketRaw2(192, packBlockVisual(&data), 100, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
			}
		}
	}
}

inline int GetPlayerCountServer()
{
	auto count = 0;
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		count++;
	}
	return count;
}

inline uint8_t* SuckerTileData(const uint16_t itemid, const uint16_t itemamount, const uint8_t magnet_on, const uint8_t remote_on)
{
	const auto data = new uint8_t[15];
	memset(data, 0, 15);
	data[0] = 0x3E;
	*reinterpret_cast<uint16_t*>(data + 1) = itemid;
	*reinterpret_cast<uint16_t*>(data + 5) = itemamount;
	*static_cast<uint8_t*>(data + 9) = magnet_on;
	*static_cast<uint8_t*>(data + 10) = remote_on;
	*static_cast<uint8_t*>(data + 12) = 1;
	return data;
}

inline void SendItemSucker(ENetPeer* peer, const int blockid, const int x, const int y, const uint16_t itemid, const uint16_t itemamount, const uint8_t magneton, const uint8_t remoteon)
{
	PlayerMoving pmov;
	pmov.packetType = 5;
	pmov.characterState = 8;
	pmov.punchX = x;
	pmov.punchY = y;
	pmov.netID = -1;
	const auto pmovpacked = packPlayerMoving(&pmov);
	*reinterpret_cast<uint32_t*>(pmovpacked + 52) = 15 + 8;
	const auto packet = new uint8_t[4 + 56 + 15 + 8];
	memset(packet, 0, 4 + 56 + 15 + 8);
	packet[0] = 4;
	memcpy(packet + 4, pmovpacked, 56);
	*reinterpret_cast<uint16_t*>(packet + 4 + 56) = blockid;
	*reinterpret_cast<uint16_t*>(packet + 4 + 56 + 6) = 1;
	const auto tiledata = SuckerTileData(itemid, itemamount, magneton, remoteon);
	memcpy(packet + 4 + 56 + 8, tiledata, 15);
	const auto epacket = enet_packet_create(packet, 4 + 56 + 8 + 15, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, epacket);
	delete pmovpacked;
	delete packet;
	delete tiledata;
}

inline void SendDonateData(ENetPeer* peer, short fg, short bg, const int x, const int y, int item)
{
	const auto ExtendedData = new BYTE[15];
	//auto state = 0x0010000;
	//auto zero = 0;
	auto extendedLen = 15;
	//auto stt = 65;
	PlayerMoving pmov;
	pmov.packetType = 0x5;
	pmov.characterState = 0x8;
	pmov.punchX = x;
	pmov.punchY = y;
	const auto raw = new BYTE[56 + 15];
	memcpy(raw, packPlayerMoving(&pmov), 56);
	memcpy(raw + 52, &extendedLen, 4);
	memcpy(ExtendedData, &fg, 2);
	memcpy(ExtendedData + 2, &bg, 2);
	ExtendedData[4] = 0;
	ExtendedData[5] = 0;
	ExtendedData[6] = 65;
	ExtendedData[7] = 0;
	memcpy(raw + 56, ExtendedData, extendedLen);
	SendPacketRaw3(4, raw, 56 + 15, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
}

inline void RemoveItemPacket(ENetPeer* peer, short fg, short bg, const int x, const int y, int item)
{
	const auto ExtendedData = new BYTE[15];
	//auto state = 0x0010000;
	//auto zero = 0;
	auto extendedLen = 15;
	//auto stt = 65;
	PlayerMoving pmov;
	pmov.packetType = 0x5;
	pmov.characterState = 0x8;
	pmov.punchX = x;
	pmov.punchY = y;
	const auto raw = new BYTE[56 + 15];
	memcpy(raw, packPlayerMoving(&pmov), 56);
	memcpy(raw + 52, &extendedLen, 4);
	memcpy(ExtendedData, &fg, 2);
	memcpy(ExtendedData + 2, &bg, 2);
	ExtendedData[4] = 0;
	ExtendedData[5] = 0;
	ExtendedData[6] = 0;
	ExtendedData[7] = 0;
	memcpy(raw + 56, ExtendedData, extendedLen);
	SendPacketRaw3(4, raw, 56 + 15, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
}

inline void SendItemPacket(ENetPeer* peer, short fg, short bg, const int x, const int y, int item)
{
	const auto ExtendedData = new BYTE[15];
	//auto state = 0x0010000;
	//auto zero = 0;
	auto extendedLen = 15;
	//auto stt = 65;
	PlayerMoving pmov;
	pmov.packetType = 0x5;
	pmov.characterState = 0x8;
	pmov.punchX = x;
	pmov.punchY = y;
	const auto raw = new BYTE[56 + 15];
	memcpy(raw, packPlayerMoving(&pmov), 56);
	memcpy(raw + 52, &extendedLen, 4);
	memcpy(ExtendedData, &fg, 2);
	memcpy(ExtendedData + 2, &bg, 2);
	ExtendedData[4] = 0;
	ExtendedData[5] = 0;
	ExtendedData[6] = 65;
	ExtendedData[7] = 0;
	memcpy(raw + 56, ExtendedData, extendedLen);
	SendPacketRaw3(4, raw, 56 + 15, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
}

bool isEmptyAir(WorldInfo* world, int x, int y)
{
	if (world->items[x + (world->width * y)].foreground != 0 || world->items[x + (world->width * y)].background != 0)
	{
		return true;
	}
	return false;
}
uint8_t* lockTileData(uint32_t owner, uint32_t adminLength, uint32_t* admins) {
	uint8_t* data = new uint8_t[4 + 2 + 4 + 4 + adminLength * 4 + 8];
	memset(data, 0, 4 + 2 + 4 + 4 + adminLength * 4 + 8);
	data[2] = 0x1;
	data[4] = 3;
	*(uint32_t*)(data + 6) = owner;

	*(uint32_t*)(data + 10) = adminLength;
	for (uint32_t i = 0; i < adminLength; i++) {
		*(uint32_t*)(data + 14 + i * 4) = admins[i];
	}
	return data;
}
void sendLock(ENetPeer* peer, int x, int y, int lockid, uint32_t owner, uint32_t adminsize, uint32_t* admins)
{
	PlayerMoving pmov;
	pmov.packetType = 5;
	pmov.punchX = x;
	pmov.punchY = y;
	pmov.netID = -1;
	uint8_t* pmovpacked = packPlayerMoving(&pmov);
	*(uint32_t*)(pmovpacked + 52) = 4 + 22 + adminsize * 4;
	uint8_t* packet = new uint8_t[4 + 56 + 4 + 22 + adminsize * 4];
	memset(packet, 0, 4 + 56 + 4 + 22 + adminsize * 4);
	packet[0] = 4;
	memcpy(packet + 4, pmovpacked, 56);
	*(uint16_t*)(packet + 56 + 4) = lockid;
	uint8_t* tiledata = lockTileData(owner, adminsize, admins);
	memcpy(packet + 60 + 4, tiledata, 22 + adminsize + 4);
	ENetPacket* epacket = enet_packet_create(packet, 4 + 56 + 4 + 22 + adminsize * 4, ENET_PACKET_FLAG_RELIABLE);

	enet_peer_send(peer, 0, epacket);

	delete pmovpacked;
	delete packet;
	delete tiledata;
}

void SendLockTile(ENetPeer* peer, int x, int y, int id, int locksize, int lockowner, WorldInfo* world) {



	PlayerInfo* player = (PlayerInfo*)(peer->data);

	PlayerMoving pmov;
	pmov.packetType = 0xf;
	pmov.characterState = 0;
	pmov.x = 0;
	pmov.y = 0;
	pmov.XSpeed = 0;
	pmov.YSpeed = 0;
	pmov.plantingTree = id;
	pmov.punchX = x;
	pmov.punchY = y;
	pmov.netID = lockowner;
	byte* pmovp = packPlayerMoving(&pmov);
	byte* packet = new byte[64 + locksize * 2];
	memset(packet, 0, 64 + locksize * 2);
	packet[0] = 4;
	memcpy(packet + 4, pmovp, 56);
	delete pmovp;
	packet[12] = locksize;
	packet[16] = 8;
	int locksz = locksize * 2;
	memcpy(packet + 56, &locksz, 4);
	for (int i = 0; i < locksize; i++)
	{
		int fml;
		fml = y * 100 + x - i;
		memcpy(packet + 60 + i * 2, &fml, 2);
	}
	ENetPacket* packetenet = enet_packet_create(packet, 64 + locksize * 2, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packetenet);
	//delete packet;

}

inline void updateVendMsg(ENetPeer* peer, int foreground, int x, int y, string text)
{



	int hmm = 8;
	int text_len = text.length();
	int lol = 0;
	int wut = 5;
	int yeh = hmm + 3 + 1;
	int idk = 15 + text_len;
	int is_locked = 0;
	int bubble_type = 21;
	int ok = 52 + idk;
	int kek = ok + 4;
	int yup = ok - 8 - idk;
	int four = 4;
	int magic = 56;
	int wew = ok + 5 + 4;
	int wow = magic + 4 + 5;

	BYTE* data = new BYTE[kek];
	ENetPacket* p = enet_packet_create(0, wew, ENET_PACKET_FLAG_RELIABLE);
	for (auto i = 0; i < kek; i++) data[i] = 0;
	memcpy(data, &wut, four);
	memcpy(data + yeh, &hmm, four);
	memcpy(data + yup, &x, 4);
	memcpy(data + yup + 4, &y, 4);
	memcpy(data + 4 + yup + 4, &idk, four);
	memcpy(data + magic, &foreground, 2);
	memcpy(data + four + magic, &lol, four);
	memcpy(data + magic + 4 + four, &bubble_type, 1);
	memcpy(data + wow, &text_len, 2);
	memcpy(data + 2 + wow, text.c_str(), text_len);
	memcpy(data + ok, &is_locked, four);
	memcpy(p->data, &four, four);
	memcpy(reinterpret_cast<char*>(p->data) + four, data, kek);
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			enet_peer_send(currentPeer, 0, p);
		}
	}
	delete data;
}
void sendHMonitor(ENetPeer* peer, int x, int y, string name, bool online, const int background) {
	size_t pos;
	while ((pos = name.find("`2")) != string::npos) {
		name.replace(pos, 2, "");
	}
	PlayerMoving pmov;
	pmov.packetType = 5;
	pmov.characterState = 8;
	pmov.punchX = x;
	pmov.punchY = y;
	pmov.netID = -1;
	int len = 7 + name.length();
	uint8_t* pmovpacked = packPlayerMoving(&pmov);
	*(uint32_t*)(pmovpacked + 52) = 8 + len;
	uint8_t* packet = new uint8_t[4 + 56 + 8 + len];
	memset(packet, 0, 4 + 56 + 8 + len);
	packet[0] = 4;
	memcpy(packet + 4, pmovpacked, 56);
	*(uint16_t*)(packet + 4 + 56) = 0x4D8;
	*(uint16_t*)(packet + 4 + 56 + 6) = 1 | (online ? 0x40 : 0);
	*(uint16_t*)(packet + 6 + 56) = background;
	*(uint8_t*)(packet + 4 + 56 + 8) = 0x0B;
	*(uint16_t*)(packet + 4 + 56 + 13) = name.length();
	memcpy(packet + 4 + 56 + 15, name.data(), name.length());
	ENetPacket* epacket = enet_packet_create(packet, 4 + 56 + 8 + len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, epacket);
	delete pmovpacked;
	delete packet;
}
inline void UpdateVend(ENetPeer* peer, int x, int y, int id, bool locks, int price, int background, bool isPer = false) {
	if (price == 0) id = 0;
	auto options321 = 0;
	if (price >= 256 && price < 512) options321 = 1;
	else if (price >= 512 && price < 768) options321 = 2;
	else if (price >= 768 && price < 1024) options321 = 3;
	else if (price >= 1024 && price < 1280) options321 = 4;
	else if (price >= 1280 && price < 1536) options321 = 5;
	else if (price >= 1536 && price < 1792) options321 = 6;
	else if (price >= 1792 && price < 2048) options321 = 7;
	else if (price >= 2048 && price < 2304) options321 = 8;
	else if (price >= 2304 && price < 2560) options321 = 9;
	else if (price >= 2560 && price < 2816) options321 = 10;
	else if (price >= 2816 && price < 3072) options321 = 11;
	else if (price >= 3072 && price < 3328) options321 = 12;
	else if (price >= 3328 && price < 3584) options321 = 13;
	else if (price >= 3584 && price < 3840) options321 = 14;
	else if (price >= 3840 && price < 4096) options321 = 15;
	else if (price >= 4096 && price < 4352) options321 = 16;
	else if (price >= 4352 && price < 4608) options321 = 17;
	else if (price >= 4608 && price < 4864) options321 = 18;
	else if (price >= 4864 && price < 5120) options321 = 19;
	else if (price >= 5120 && price < 5376) options321 = 20;
	else if (price >= 5376 && price < 5632) options321 = 21;
	else if (price >= 5632 && price < 5888) options321 = 22;
	else if (price >= 5888 && price < 6144) options321 = 23;
	else if (price >= 6144 && price < 6400) options321 = 24;
	else if (price >= 6400 && price < 6656) options321 = 25;
	else if (price >= 6656 && price < 6912) options321 = 26;
	else if (price >= 6912 && price < 7168) options321 = 27;
	else if (price >= 7168 && price < 7424) options321 = 28;
	else if (price >= 7424 && price < 7680) options321 = 29;
	else if (price >= 7680 && price < 7936) options321 = 30;
	else if (price >= 7936 && price < 8192) options321 = 31;
	else if (price >= 8192 && price < 8448) options321 = 32;
	else if (price >= 8448 && price < 8704) options321 = 33;
	else if (price >= 8704 && price < 8960) options321 = 34;
	else if (price >= 8960 && price < 9216) options321 = 35;
	else if (price >= 9216 && price < 9472) options321 = 36;
	else if (price >= 9472 && price < 9728) options321 = 37;
	else if (price >= 9728 && price < 9984) options321 = 38;
	else if (price >= 9984 && price < 10240) options321 = 39;
	else if (price >= 10240 && price < 10496) options321 = 40;
	else if (price >= 10496 && price < 10752) options321 = 41;
	else if (price >= 10752 && price < 11008) options321 = 42;
	else if (price >= 11008 && price < 11264) options321 = 43;
	else if (price >= 11264 && price < 11520) options321 = 44;
	else if (price >= 11520 && price < 11776) options321 = 45;
	else if (price >= 11776 && price < 12032) options321 = 46;
	else if (price >= 12032 && price < 12288) options321 = 47;
	else if (price >= 12288 && price < 12544) options321 = 48;
	else if (price >= 12544 && price < 12800) options321 = 49;
	else if (price >= 12800 && price < 13056) options321 = 50;
	else if (price >= 13056 && price < 13312) options321 = 51;
	else if (price >= 13312 && price < 13568) options321 = 52;
	else if (price >= 13568 && price < 13824) options321 = 53;
	else if (price >= 13824 && price < 14080) options321 = 54;
	else if (price >= 14080 && price < 14336) options321 = 55;
	else if (price >= 14336 && price < 14592) options321 = 56;
	else if (price >= 14592 && price < 14848) options321 = 57;
	else if (price >= 14848 && price < 15104) options321 = 58;
	else if (price >= 15104 && price < 15360) options321 = 59;
	else if (price >= 15360 && price < 15616) options321 = 60;
	else if (price >= 15616 && price < 15872) options321 = 61;
	else if (price >= 15872 && price < 16128) options321 = 62;
	else if (price >= 16128 && price < 16384) options321 = 63;
	else if (price >= 16384 && price < 16640) options321 = 64;
	else if (price >= 16640 && price < 16896) options321 = 65;
	else if (price >= 16896 && price < 17152) options321 = 66;
	else if (price >= 17152 && price < 17408) options321 = 67;
	else if (price >= 17408 && price < 17664) options321 = 68;
	else if (price >= 17664 && price < 17920) options321 = 69;
	else if (price >= 17920 && price < 18176) options321 = 70;
	else if (price >= 18176 && price < 18432) options321 = 71;
	else if (price >= 18432 && price < 18688) options321 = 72;
	else if (price >= 18688 && price < 18944) options321 = 73;
	else if (price >= 18944 && price < 19200) options321 = 74;
	else if (price >= 19200 && price < 19456) options321 = 75;
	else if (price >= 19456 && price < 19712) options321 = 76;
	else if (price >= 19712 && price < 19968) options321 = 77;
	else if (price >= 19968 && price <= 20000) options321 = 78;
	price -= 256 * options321;
	TileExtra data;
	data.packetType = 0x5;
	data.characterState = 8;
	data.punchX = x;
	data.punchY = y;
	data.charStat = 13;
	data.blockid = 2978;
	data.backgroundid = background;
	data.visual = 0x00410000;
	if (locks == true) data.visual = 0x02410000;
	auto n = id;
	string hex = "";
	{
		std::stringstream ss;
		ss << std::hex << n;
		string res(ss.str());
		hex = res + "18";
	}
	int xx;
	std::stringstream ss;
	ss << std::hex << hex;
	ss >> xx;
	data.displayblock = xx;
	int xes;
	{
		int wl = price;
		string basic_string = "";
		{
			std::stringstream stringstream;
			stringstream << std::hex << wl;
			string res(stringstream.str());
			basic_string = res + "00";
		}
		int i;
		std::stringstream basic_stringstream;
		basic_stringstream << std::hex << basic_string;
		basic_stringstream >> i;
		xes = i;
	}
	BYTE* raw = nullptr;
	if (isPer) {
		raw = packStuffVisual(&data, 16777215, -xes);
	}
	else {
		raw = packStuffVisual(&data, options321, xes);
	}
	SendPacketRaw2(192, raw, 102, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
	raw = nullptr;
}
string lockTileDatas(int visual, uint32_t owner, uint32_t adminLength, uint32_t* admins, bool isPublic = false, uint8_t bpm = 0) {
	string data;
	data.resize(4 + 2 + 4 + 4 + adminLength * 4 + 8);
	if (bpm) data.resize(data.length() + 4);
	data[2] = 0x01;
	if (isPublic) data[2] |= 0x80;
	data[4] = 3;
	data[5] = visual; // or 0x02
	STRINT(data, 6) = owner;
	//data[14] = 1;
	STRINT(data, 10) = adminLength;
	for (uint32_t i = 0; i < adminLength; i++) {
		STRINT(data, 14 + i * 4) = admins[i];
	}

	if (bpm) {
		STRINT(data, 10)++;
		STRINT(data, 14 + adminLength * 4) = -bpm;
	}
	return data;
}

void sendTileData(ENetPeer* peer, int x, int y, int visual, uint16_t fgblock, uint16_t bgblock, string tiledata) {
	PlayerMoving pmov;
	pmov.packetType = 5;
	pmov.characterState = 0;
	pmov.x = 0;
	pmov.y = 0;
	pmov.XSpeed = 0;
	pmov.YSpeed = 0;
	pmov.plantingTree = 0;
	pmov.punchX = x;
	pmov.punchY = y;
	pmov.netID = 0;
	string packetstr;
	packetstr.resize(4);
	packetstr[0] = 4;
	packetstr += packPlayerMoving2(&pmov);
	packetstr[16] = 8;
	packetstr.resize(packetstr.size() + 4);
	STRINT(packetstr, 52 + 4) = tiledata.size() + 4;
	STR16(packetstr, 56 + 4) = fgblock;
	STR16(packetstr, 58 + 4) = bgblock;
	packetstr += tiledata;
	ENetPacket* packet = enet_packet_create(&packetstr[0],
		packetstr.length(),
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
}
inline bool isWorldOwner(ENetPeer* peer, WorldInfo* world)
{
	return static_cast<PlayerInfo*>(peer->data)->rawName == world->owner;
}

void updateRotatedItem(ENetPeer* peer, int foreground, int x, int y, string text, int background)
{
	PlayerMoving sign;
	sign.packetType = 0x3;
	sign.characterState = 0x0;
	sign.x = x;
	sign.y = y;
	sign.punchX = x;
	sign.punchY = y;
	sign.XSpeed = 0;
	sign.YSpeed = 0;
	sign.netID = -1;
	sign.plantingTree = foreground;
	SendPacketRaw(4, packPlayerMoving(&sign), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
	int hmm = 8, wot = text.length(), lol = 0x00200000, wut = 5;
	int yeh = hmm + 3 + 1, idk = 15 + wot, lmao = -1, yey = 2; //idk = text_len + 15, wut = type(?), wot = text_len, yey = len of text_len
	int ok = 52 + idk;
	int kek = ok + 4, yup = ok - 8 - idk;
	int thonk = 4, magic = 56, wew = ok + 5 + 4;
	int wow = magic + 4 + 5;
	BYTE* data = new BYTE[kek];
	ENetPacket* p = enet_packet_create(0, wew, ENET_PACKET_FLAG_RELIABLE);
	for (int i = 0; i < kek; i++) data[i] = 0;
	memcpy(data, &wut, thonk);
	memcpy(data + yeh, &hmm, thonk); //read discord
	memcpy(data + yup, &x, 4);
	memcpy(data + yup + 4, &y, 4);
	memcpy(data + 4 + yup + 4, &idk, thonk);
	memcpy(data + magic, &foreground, yey);
	memcpy(data + magic + 2, &background, yey); // gai?
	memcpy(data + thonk + magic, &lol, thonk);
	memcpy(data + magic + 4 + thonk, &yey, 1);
	memcpy(data + wow, &wot, yey); //data + wow = text_len
	memcpy(data + yey + wow, text.c_str(), wot); //data + text_len_len + text_len_offs = text
	memcpy(data + ok, &lmao, thonk); //end ?
	memcpy(p->data, &thonk, thonk);
	memcpy((char*)p->data + thonk, data, kek); //kek = data_len
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer)) {
			enet_peer_send(currentPeer, 0, p);
		}
	}
	delete data;
}


bool RestrictedArea_check(WorldInfo* world, const int x, const int y) {
	bool scan_area = false;
	int where_lock_x = -1;
	int where_lock_y = -1;
	bool is_public = false;
	bool can_interact = false;
	for (int i = 0; i < world->width * world->height; i++) {
		if (world->items[i].foreground == 202 || world->items[i].foreground == 204 || world->items[i].foreground == 206 || world->items[i].foreground == 4994) {
			where_lock_x = i % world->width;
			where_lock_y = i / world->width;
			scan_area = true;
			if (x == where_lock_x + 1 && where_lock_y == y) can_interact = true;
			if (x == where_lock_x + 2 && where_lock_y == y) can_interact = true;
			if (x == where_lock_x - 1 && where_lock_y == y) can_interact = true;
			if (x == where_lock_x - 2 && where_lock_y == y) can_interact = true;
			if (y == where_lock_y + 1 && where_lock_x == x) can_interact = true;
			if (y == where_lock_y + 2 && where_lock_x == x) can_interact = true;
			if (y == where_lock_y - 1 && where_lock_x == x) can_interact = true;
			if (y == where_lock_y - 2 && where_lock_x == x) can_interact = true;
			if (x == where_lock_x + 1 && where_lock_y + 1 == y) can_interact = true;
			if (x == where_lock_x + 2 && where_lock_y + 2 == y) can_interact = true;
			if (x == where_lock_x - 1 && where_lock_y - 1 == y) can_interact = true;
			if (x == where_lock_x - 2 && where_lock_y - 2 == y) can_interact = true;
			if (y == where_lock_y + 1 && where_lock_x + 1 == x) can_interact = true;
			if (y == where_lock_y + 2 && where_lock_x + 2 == x) can_interact = true;
			if (y == where_lock_y - 1 && where_lock_x - 1 == x) can_interact = true;
			if (y == where_lock_y - 2 && where_lock_x - 2 == x) can_interact = true;
			if (x == where_lock_x + 1 && where_lock_y - 1 == y) can_interact = true;
			if (x == where_lock_x + 2 && where_lock_y - 2 == y) can_interact = true;
			if (x == where_lock_x - 1 && where_lock_y + 1 == y) can_interact = true;
			if (x == where_lock_x - 2 && where_lock_y + 2 == y) can_interact = true;
			if (y == where_lock_y + 1 && where_lock_x - 1 == x) can_interact = true;
			if (y == where_lock_y + 2 && where_lock_x - 2 == x) can_interact = true;
			if (y == where_lock_y - 1 && where_lock_x + 1 == x) can_interact = true;
			if (y == where_lock_y - 2 && where_lock_x + 2 == x) can_interact = true;
			if (x == where_lock_x + 2 && where_lock_y + 1 == y) can_interact = true;
			if (x == where_lock_x - 2 && where_lock_y - 1 == y) can_interact = true;
			if (x == where_lock_x + 1 && where_lock_y + 2 == y) can_interact = true;
			if (x == where_lock_x - 1 && where_lock_y - 2 == y) can_interact = true;
			if (x == where_lock_x - 1 && where_lock_y + 2 == y) can_interact = true;
			if (x == where_lock_x + 1 && where_lock_y - 2 == y) can_interact = true;
			if (x == where_lock_x + 2 && where_lock_y - 1 == y) can_interact = true;
			if (x == where_lock_x + 2 && where_lock_y + 1 == y) can_interact = true;
			if (x == where_lock_x - 2 && where_lock_y + 1 == y) can_interact = true;
		}
	}
	if (!scan_area) return true;
	if (!can_interact) return true;
	return false;
}

bool RestrictedArea(ENetPeer* peer, WorldInfo* world, const int x, const int y) {
	bool scan_area = false;
	int where_lock_x = 0;
	int where_lock_y = 0;
	bool is_public = false;
	bool can_interact = false;
	bool bound_area = false;
	for (int i = 0; i < world->width * world->height; i++) {
		if (world->items[i].foreground == 202 || world->items[i].foreground == 204 || world->items[i].foreground == 206 || world->items[i].foreground == 4994) {
			scan_area = true;
			if (world->items[i].opened || world->items[i].monitorname == static_cast<PlayerInfo*>(peer->data)->rawName) {
				where_lock_x = i % world->width;
				where_lock_y = i / world->width;
				if (x == where_lock_x + 1 && where_lock_y == y) can_interact = true;
				if (x == where_lock_x + 2 && where_lock_y == y) can_interact = true;
				if (x == where_lock_x - 1 && where_lock_y == y) can_interact = true;
				if (x == where_lock_x - 2 && where_lock_y == y) can_interact = true;
				if (y == where_lock_y + 1 && where_lock_x == x) can_interact = true;
				if (y == where_lock_y + 2 && where_lock_x == x) can_interact = true;
				if (y == where_lock_y - 1 && where_lock_x == x) can_interact = true;
				if (y == where_lock_y - 2 && where_lock_x == x) can_interact = true;
				if (x == where_lock_x + 1 && where_lock_y + 1 == y) can_interact = true;
				if (x == where_lock_x + 2 && where_lock_y + 2 == y) can_interact = true;
				if (x == where_lock_x - 1 && where_lock_y - 1 == y) can_interact = true;
				if (x == where_lock_x - 2 && where_lock_y - 2 == y) can_interact = true;
				if (y == where_lock_y + 1 && where_lock_x + 1 == x) can_interact = true;
				if (y == where_lock_y + 2 && where_lock_x + 2 == x) can_interact = true;
				if (y == where_lock_y - 1 && where_lock_x - 1 == x) can_interact = true;
				if (y == where_lock_y - 2 && where_lock_x - 2 == x) can_interact = true;
				if (x == where_lock_x + 1 && where_lock_y - 1 == y) can_interact = true;
				if (x == where_lock_x + 2 && where_lock_y - 2 == y) can_interact = true;
				if (x == where_lock_x - 1 && where_lock_y + 1 == y) can_interact = true;
				if (x == where_lock_x - 2 && where_lock_y + 2 == y) can_interact = true;
				if (y == where_lock_y + 1 && where_lock_x - 1 == x) can_interact = true;
				if (y == where_lock_y + 2 && where_lock_x - 2 == x) can_interact = true;
				if (y == where_lock_y - 1 && where_lock_x + 1 == x) can_interact = true;
				if (y == where_lock_y - 2 && where_lock_x + 2 == x) can_interact = true;
				if (x == where_lock_x + 2 && where_lock_y + 1 == y) can_interact = true;
				if (x == where_lock_x - 2 && where_lock_y - 1 == y) can_interact = true;
				if (x == where_lock_x + 1 && where_lock_y + 2 == y) can_interact = true;
				if (x == where_lock_x - 1 && where_lock_y - 2 == y) can_interact = true;
				if (x == where_lock_x - 1 && where_lock_y + 2 == y) can_interact = true;
				if (x == where_lock_x + 1 && where_lock_y - 2 == y) can_interact = true;
				if (x == where_lock_x + 2 && where_lock_y - 1 == y) can_interact = true;
				if (x == where_lock_x + 2 && where_lock_y + 1 == y) can_interact = true;
				if (x == where_lock_x - 2 && where_lock_y + 1 == y) can_interact = true;
			}
			else if (world->owner == "") {
				where_lock_x = i % world->width;
				where_lock_y = i / world->width;
				if (x == where_lock_x + 1 && where_lock_y == y) bound_area = true;
				if (x == where_lock_x + 2 && where_lock_y == y) bound_area = true;
				if (x == where_lock_x - 1 && where_lock_y == y) bound_area = true;
				if (x == where_lock_x - 2 && where_lock_y == y) bound_area = true;
				if (y == where_lock_y + 1 && where_lock_x == x) bound_area = true;
				if (y == where_lock_y + 2 && where_lock_x == x) bound_area = true;
				if (y == where_lock_y - 1 && where_lock_x == x) bound_area = true;
				if (y == where_lock_y - 2 && where_lock_x == x) bound_area = true;
				if (x == where_lock_x + 1 && where_lock_y + 1 == y) bound_area = true;
				if (x == where_lock_x + 2 && where_lock_y + 2 == y) bound_area = true;
				if (x == where_lock_x - 1 && where_lock_y - 1 == y) bound_area = true;
				if (x == where_lock_x - 2 && where_lock_y - 2 == y) bound_area = true;
				if (y == where_lock_y + 1 && where_lock_x + 1 == x) bound_area = true;
				if (y == where_lock_y + 2 && where_lock_x + 2 == x) bound_area = true;
				if (y == where_lock_y - 1 && where_lock_x - 1 == x) bound_area = true;
				if (y == where_lock_y - 2 && where_lock_x - 2 == x) bound_area = true;
				if (x == where_lock_x + 1 && where_lock_y - 1 == y) bound_area = true;
				if (x == where_lock_x + 2 && where_lock_y - 2 == y) bound_area = true;
				if (x == where_lock_x - 1 && where_lock_y + 1 == y) bound_area = true;
				if (x == where_lock_x - 2 && where_lock_y + 2 == y) bound_area = true;
				if (y == where_lock_y + 1 && where_lock_x - 1 == x) bound_area = true;
				if (y == where_lock_y + 2 && where_lock_x - 2 == x) bound_area = true;
				if (y == where_lock_y - 1 && where_lock_x + 1 == x) bound_area = true;
				if (y == where_lock_y - 2 && where_lock_x + 2 == x) bound_area = true;
				if (x == where_lock_x + 2 && where_lock_y + 1 == y) bound_area = true;
				if (x == where_lock_x - 2 && where_lock_y - 1 == y) bound_area = true;
				if (x == where_lock_x + 1 && where_lock_y + 2 == y) bound_area = true;
				if (x == where_lock_x - 1 && where_lock_y - 2 == y) bound_area = true;
				if (x == where_lock_x - 1 && where_lock_y + 2 == y) bound_area = true;
				if (x == where_lock_x + 1 && where_lock_y - 2 == y) bound_area = true;
				if (x == where_lock_x + 2 && where_lock_y - 1 == y) bound_area = true;
				if (x == where_lock_x + 2 && where_lock_y + 1 == y) bound_area = true;
				if (x == where_lock_x - 2 && where_lock_y + 1 == y) bound_area = true;
			}
		}
	}
	if (!can_interact && world->owner == "" && !bound_area || isWorldOwner(peer, world)) return false;
	else if (!scan_area) return true;
	else if (!can_interact) return true;
	else if (can_interact) return false;
}

void ApplyLockPacket(WorldInfo* world, ENetPeer* peer, int x, int y, int id, int lockowner) {
	if (lockowner == -3) {
		lockowner = static_cast<PlayerInfo*>(peer->data)->netID;
	}
	int locksize = 0;
	if (id == 202) locksize = 25;
	if (id == 4994) locksize = 55;
	PlayerMoving pmov;
	pmov.packetType = 0xf;
	pmov.characterState = 0;
	pmov.x = 0;
	pmov.y = 0;
	pmov.XSpeed = 0;
	pmov.YSpeed = 0;
	pmov.plantingTree = id;
	pmov.punchX = x;
	pmov.punchY = y;
	pmov.netID = lockowner;
	byte* pmovp = packPlayerMoving(&pmov);
	byte* packet = new byte[64 + locksize * 2];
	memset(packet, 0, 64 + locksize * 2);
	packet[0] = 4;
	memcpy(packet + 4, pmovp, 56);
	delete pmovp;
	packet[12] = locksize;
	packet[16] = 8;
	int locksz = locksize * 2;
	memcpy(packet + 56, &locksz, 4);
	bool lock_above = false;
	bool mid_lock = false;
	bool mid_low = false;
	bool mid_lowest = false;
	int vidur_ten = 2;
	int vidur = 2;
	int vidur_cia = 2;
	int lock_above_lock = 2;
	int lock_lowers_lock = 2;
	for (int i = 0; i < locksize; i++) {
		if (!lock_above) {
			int fml = y * world->width - 200 + x - 4 + lock_above_lock;
			memcpy(packet + world->height + i * 2, &fml, 2);
			lock_above_lock++;
			if (lock_above_lock >= 7) lock_above = true;
			continue;
		}
		if (mid_lowest) {
			int fml = y * world->width + 200 + x - 4 + lock_lowers_lock;
			memcpy(packet + world->height + i * 2, &fml, 2);
			lock_lowers_lock++;
		}
		else if (mid_low) {
			int fml = y * world->width + 100 + x - 4 + vidur_cia;
			memcpy(packet + world->height + i * 2, &fml, 2);
			vidur_cia++;
			if (vidur_cia >= 7) mid_lowest = true;
		}
		else if (mid_lock) {
			int fml = y * world->width + x - 4 + vidur;
			memcpy(packet + world->height + i * 2, &fml, 2);
			vidur++;
			if (vidur >= 7) mid_low = true;
		}
		else if (lock_above) {
			int fml = y * world->width - 100 + x - 4 + vidur_ten;
			memcpy(packet + world->height + i * 2, &fml, 2);
			vidur_ten++;
			if (vidur_ten >= 7) mid_lock = true;
		}
	}
	ENetPacket* packetenet = enet_packet_create(packet, 64 + locksize * 2, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packetenet);
	delete packet;
}

inline bool isWorldAdmin(ENetPeer* peer, WorldInfo* world)
{
	const auto uid = static_cast<PlayerInfo*>(peer->data)->rawName;
	for (const auto i = 0; world->accessed.size();)
	{
		const auto x = world->accessed.at(i);
		if (uid == x.substr(0, x.find("|")))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}
void SendRainbowShitData(ENetPeer* peer, short fg, short bg, int x, int y, bool rainbow, int netid) {
	byte* ExtendedData = new byte[26];
	int state = 0x0010000;
	int extendedLen = 26;
	PlayerMoving pmov;
	pmov.packetType = 0x5;
	pmov.characterState = 0x8;
	pmov.punchX = x;
	pmov.punchY = y;
	int NetID = netid;
	byte* raw = new byte[56 + 26];
	memcpy(raw, packPlayerMoving(&pmov), 56);
	memcpy(raw + 52, &extendedLen, 4);
	memcpy(ExtendedData, &fg, 2);
	memcpy(ExtendedData + 2, &bg, 2);
	memcpy(ExtendedData + 4, &state, 4);
	ExtendedData[8] = 0x3;
	int flags = 0;
	if (rainbow) {
		flags = 128;
	}
	else {
		flags = 0;
	}
	ExtendedData[9] = flags;
	memcpy(ExtendedData + 10, &NetID, 4);
	ExtendedData[15] = 0;
	ExtendedData[16] = 0;
	ExtendedData[17] = 0;
	ExtendedData[18] = 0;
	ExtendedData[19] = 1;
	ExtendedData[20] = 0;
	ExtendedData[21] = 0;
	ExtendedData[22] = 0;
	ExtendedData[23] = 0;
	ExtendedData[24] = 0;
	ExtendedData[25] = 0;
	ExtendedData[26] = 0;
	memcpy(raw + 56, ExtendedData, extendedLen);
	SendPacketRaw3(4, raw, 56 + 26, 0, peer, ENET_PACKET_FLAG_RELIABLE);
	delete[] ExtendedData;

}

void SendCanvasData(ENetPeer* peer, short fg, short bg, int x, int y, int item, string text) {
	byte* ExtendedData = new byte[15 + item + text.length()];
	int state = 0x0010000;
	int extendedLen = 15 + item + text.length();
	int TextLen = text.length();
	PlayerMoving pmov;
	pmov.packetType = 0x5;
	pmov.characterState = 0x8;
	pmov.punchX = x;
	pmov.punchY = y;
	byte* raw = new byte[56 + 15 + item + TextLen];
	memcpy(raw, packPlayerMoving(&pmov), 56);
	memcpy(raw + 52, &extendedLen, 4);
	memcpy(ExtendedData, &fg, 2);
	memcpy(ExtendedData + 2, &bg, 2);
	memcpy(ExtendedData + 4, &state, 4);
	ExtendedData[8] = 0x23;
	memcpy(ExtendedData + 9, &item, 4);
	memcpy(ExtendedData + 13, &TextLen, 2);
	memcpy(ExtendedData + 15, text.data(), TextLen);
	memcpy(raw + 56, ExtendedData, extendedLen);
	SendPacketRaw3(4, raw, 56 + 15 + item + TextLen, 0, peer, ENET_PACKET_FLAG_RELIABLE);
	delete[] ExtendedData; // fix memleak by playingo
}
inline void SendGScan(ENetPeer* peer, WorldInfo* world, int x, int y) {
	string EditableDialog = "";
	string ButtonDialog = "";
	string allowFloat = "0";
	string allowDrop = "0";
	string endDialog = "";
	if (world->items[x + (y * world->width)].rm) allowFloat = "1";
	if (world->items[x + (y * world->width)].opened) allowDrop = "1";
	if (isWorldOwner(peer, world) || isMod(peer)) {
		endDialog = "\nend_dialog|statsblock|Cancel|Apply|";
		ButtonDialog = "\nadd_textbox|`wWhich stats would you like to view?|left\nadd_button|worldBlocks|World Blocks|noflags|0|0|\nadd_button|floatingItems|Floating Items|noflags|0|0|";
		EditableDialog = "\nadd_textbox|`wYou can set the stats to be usable by the public.|left\nadd_checkbox|isStatsWorldBlockUsableByPublic|World blocks is usable by public|" + allowDrop + "\nadd_checkbox|isStatsFloatingItemsUsableByPublic|Floating items is usable by public|" + allowFloat + "\nadd_spacer|small|";
	}
	else if (world->items[x + (y * world->width)].rm && world->items[x + (y * world->width)].opened) {
		endDialog = "\nend_dialog|statsblock|Cancel||";
		ButtonDialog = "\nadd_textbox|`wWhich stats would you like to view?|left\nadd_button|worldBlocks|World Blocks|noflags|0|0|\nadd_button|floatingItems|Floating Items|noflags|0|0|";
	}
	else if (world->items[x + (y * world->width)].rm) {
		endDialog = "\nend_dialog|statsblock|Cancel||";
		ButtonDialog = "\nadd_textbox|`wWhich stats would you like to view?|left\nadd_button|floatingItems|Floating Items|noflags|0|0|";
	}
	else if (world->items[x + (y * world->width)].opened) {
		endDialog = "\nend_dialog|statsblock|Cancel||";
		ButtonDialog = "\nadd_textbox|`wWhich stats would you like to view?|left\nadd_button|worldBlocks|World Blocks|noflags|0|0|";
	}
	else {
		endDialog = "\nend_dialog|statsblock|Cancel||";
		ButtonDialog = "\nadd_textbox|`wThis growscan options are set to private!|left";
	}
	Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wWorld Stats``|left|6016|\nadd_spacer|small|\nadd_textbox|`wThis amazing block can show the stats for the whole world!|left\nadd_spacer|small|" + ButtonDialog + "\nadd_spacer|small|" + EditableDialog + "" + endDialog + "");
}

void sendDShelf(ENetPeer* peer, int x, int y, int item1, int item2, int item3, int item4)
{
	PlayerMoving pmov;
	pmov.packetType = 5;
	pmov.characterState = 8;
	pmov.punchX = x;
	pmov.punchY = y;
	pmov.netID = -1;
	uint8_t* pmovpacked = packPlayerMoving(&pmov);
	*(uint32_t*)(pmovpacked + 52) = 8 + 16;
	uint8_t* packet = new uint8_t[4 + 56 + 8 + 16];
	memset(packet, 0, 4 + 56 + 8 + 16);
	packet[0] = 4;
	memcpy(packet + 4, pmovpacked, 56);
	*(uint16_t*)(packet + 4 + 56) = 3794; // display shelf id
	*(uint16_t*)(packet + 4 + 56 + 6) = 1;
	*(uint8_t*)(packet + 4 + 56 + 8) = 0x2B;
	*(int*)(packet + 4 + 56 + 9 + 0 * 4) = item1;
	*(int*)(packet + 4 + 56 + 9 + 1 * 4) = item2;
	*(int*)(packet + 4 + 56 + 9 + 2 * 4) = item3;
	*(int*)(packet + 4 + 56 + 9 + 3 * 4) = item4;
	ENetPacket* epacket = enet_packet_create(packet, 4 + 56 + 8 + 16, ENET_PACKET_FLAG_RELIABLE);

	enet_peer_send(peer, 0, epacket);

	delete pmovpacked;
	delete packet;
}

inline void AutoBreak(ENetPeer* peer, int x, int y) {
	while (true)
	{
		Sleep(3000);
		{
			if (serverIsFrozen) return;
			auto world = getPlyersWorld(peer);
			if (!world) return;
			if (world->items[x + (y * world->width)].foreground == 0) {
				return;
			}
			world->items[x + (y * world->width)].foreground = 0;
			PlayerMoving data3;
			data3.packetType = 0x3;
			data3.characterState = 0x0;
			data3.x = x;
			data3.y = y;
			data3.punchX = x;
			data3.punchY = y;
			data3.XSpeed = 0;
			data3.YSpeed = 0;
			data3.netID = -1;
			data3.plantingTree = 0;
			ENetPeer* currentPeer;
			for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
			{
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
				if (isHere(peer, currentPeer))
				{
					auto raw = packPlayerMoving(&data3);
					raw[2] = 0;
					raw[3] = 0;
					SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
					Player::OnParticleEffect(currentPeer, 229, x * 32, y * 32, 0);
					Player::PlayAudio(currentPeer, "audio/metal_destroy.wav", 0);
				}
			}
		}
	}
}

inline void sendDrop(ENetPeer* peer, int netID, int x, int y, int item, int count, BYTE specialEffect)
{
	if (item > maxItems) return;
	if (item < 0) return;
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			PlayerMoving data;
			data.packetType = 14;
			data.x = x;
			data.y = y;
			data.netID = netID;
			data.plantingTree = item;
			float val = count;
			auto val2 = specialEffect;
			const auto raw = packPlayerMoving(&data);
			memcpy(raw + 16, &val, 4);
			memcpy(raw + 1, &val2, 1);
			SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
}

inline void RemoveDroppedItem(ENetPeer* peer, const int obj_id, WorldInfo* world)
{
	if (!world) return;
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			const auto b = new BYTE[56];
			memset(b, 0, 56);
			*reinterpret_cast<int*>(&b[0]) = 0xe;
			*reinterpret_cast<int*>(&b[4]) = -2;
			*reinterpret_cast<int*>(&b[8]) = -1;
			*reinterpret_cast<int*>(&b[20]) = obj_id + 1;
			SendPacketRaw(4, b, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
}

inline auto processTakeServer(ENetPeer* peer, const int itemIdx)
{
	auto world = getPlyersWorld(peer);
	if (!world) return -1;
	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	auto legit = true;
	auto atik = -1;
	for (auto i = 0; i < world->droppedItems.size(); i++)
	{
		if (world->droppedItems.at(i).uid == itemIdx)
		{
			atik = i;
			break;
		}
	}
	legit = atik != -1;
	if (legit)
	{
		try
		{
			//const auto droppedItem = world->droppedItems.at(atik);
			world->droppedItems.erase(world->droppedItems.begin() + atik);
		}
		catch (...)
		{
			return -1;
		}
	}
	return 0;
}

inline void SendThrowEffect(ENetPeer* peer, int id, int netIDsrc, int netIDdst, int timeMs, BYTE type, int x, int y)
{
	PlayerMoving data;
	data.packetType = 0x13;
	data.punchX = id;
	data.punchY = id;
	data.x = x;
	data.y = y;
	const auto raw = packPlayerMoving(&data);
	auto netIdSrc = netIDsrc;
	auto netIdDst = netIDdst;
	auto n1 = timeMs;
	memcpy(raw + 3, &type, 1);
	memcpy(raw + 4, &netIdDst, 4);
	memcpy(raw + 8, &netIdSrc, 4);
	memcpy(raw + 20, &n1, 4);
	for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			const auto raw2 = new BYTE[56];
			memcpy(raw2, raw, 56);
			SendPacketRaw(4, raw2, 56, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
	delete raw;
}

inline void DropItem(ENetPeer* peer, int netID, int x, int y, int item, int count, BYTE specialEffect, string history = "No Data")
{
	if (serverIsFrozen) return;
	auto world = getPlyersWorld(peer);
	if (!world) return;
	if (item < 0) return;
	if (x == 0 || y == 0) return;
	if (static_cast<PlayerInfo*>(peer->data)->currentWorld == "EXIT") return;
	auto blockX = x / 32;
	auto blockY = y / 32;
	if (blockX < 0 || blockY < 0 || blockX > world->width || blockY > world->height) return;
	auto hasmag = false;
	for (auto i = 0; i < world->width * world->height; i++)
	{
		if (world->items[i].foreground == 5638 || world->items[i].foreground == 6946 || world->items[i].foreground == 6948)
		{
			string Sucker = "";
			if (world->items[i].foreground == 5638) Sucker = "magplant";
			else if (world->items[i].foreground == 6946) Sucker = "gaiabeacon";
			else if (world->items[i].foreground == 6948) Sucker = "unstabletesseract";
			auto ismag = std::experimental::filesystem::exists(Sucker + "/storeditem/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(i) + ".txt");
			if (ismag)
			{
				auto currentworld = static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(i);
				auto itemid = 0;
				ifstream fdss(Sucker + "/storeditem/" + currentworld + ".txt");
				fdss >> itemid;
				fdss.close();
				auto scount = 0;
				ifstream fdss3(Sucker + "/count/" + currentworld + ".txt");
				fdss3 >> scount;
				fdss3.close();
				if (item == itemid && scount <= 5000)
				{
					auto xx = i % world->width, yy = i / world->width;
					hasmag = true;
					scount += count;
					ofstream fdss9(Sucker + "/count/" + currentworld + ".txt");
					fdss9 << scount;
					fdss9.close();
					ENetPeer* currentPeer;
					for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
					{
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, currentPeer))
						{
							SendThrowEffect(currentPeer, item, static_cast<PlayerInfo*>(peer->data)->netID, -1, 150, 0, xx * 32 + 16, yy * 32 + 16);
							//SendThrowEffect(currentPeer, item, static_cast<PlayerInfo*>(peer->data)->netID, -1, 300, 0, xx * 32, yy * 32);
							if (scount <= 0)
							{
								SendItemSucker(currentPeer, world->items[i].foreground, xx, yy, itemid, 0, true, true);
							}
							else if (scount >= 5000)
							{
								SendItemSucker(currentPeer, world->items[i].foreground, xx, yy, itemid, -1, true, true);
							}
							else
							{
								SendItemSucker(currentPeer, world->items[i].foreground, xx, yy, itemid, 1, true, true);
							}
						}
					}
				}
				else
				{
				}
			}
		}
	}
	if (hasmag == true)
	{
		return;
	}
	try
	{
		if (item == 112)
		{
			if (count == 1) world->items[blockX + (blockY * world->width)].yellowGems++;
			if (count == 5) world->items[blockX + (blockY * world->width)].blueGems++;
			if (count == 10) world->items[blockX + (blockY * world->width)].redGems++;
			if (count == 50) world->items[blockX + (blockY * world->width)].greenGems++;
			if (count == 100) world->items[blockX + (blockY * world->width)].purpleGems++;
			vector<int> idstoremove;
			if (world->items[blockX + (blockY * world->width)].yellowGems > 4)
			{
				for (auto i = 0; i < world->droppedItems.size(); i++)
				{
					if (blockX == static_cast<int>(world->droppedItems.at(i).x / 32) && blockY == static_cast<int>(world->droppedItems.at(i).y / 32))
					{
						if (world->droppedItems.at(i).count == 1)
						{
							RemoveDroppedItem(peer, world->droppedItems.at(i).uid, world);
							idstoremove.push_back(world->droppedItems.at(i).uid);
						}
					}
				}
				world->items[blockX + (blockY * world->width)].yellowGems = 0;
				world->items[blockX + (blockY * world->width)].blueGems++;
				count = 5;
			}
			if (world->items[blockX + (blockY * world->width)].blueGems > 1)
			{
				for (auto i = 0; i < world->droppedItems.size(); i++)
				{
					if (blockX == static_cast<int>(world->droppedItems.at(i).x / 32) && blockY == static_cast<int>(world->droppedItems.at(i).y / 32))
					{
						if (world->droppedItems.at(i).count == 5)
						{
							RemoveDroppedItem(peer, world->droppedItems.at(i).uid, world);
							idstoremove.push_back(world->droppedItems.at(i).uid);
						}
					}
				}
				world->items[blockX + (blockY * world->width)].blueGems = 0;
				world->items[blockX + (blockY * world->width)].redGems++;
				count = 10;
			}
			if (world->items[blockX + (blockY * world->width)].redGems > 4)
			{
				for (auto i = 0; i < world->droppedItems.size(); i++)
				{
					if (blockX == static_cast<int>(world->droppedItems.at(i).x / 32) && blockY == static_cast<int>(world->droppedItems.at(i).y / 32))
					{
						if (world->droppedItems.at(i).count == 10)
						{
							RemoveDroppedItem(peer, world->droppedItems.at(i).uid, world);
							idstoremove.push_back(world->droppedItems.at(i).uid);
						}
					}
				}
				world->items[blockX + (blockY * world->width)].redGems = 0;
				world->items[blockX + (blockY * world->width)].greenGems++;
				count = 50;
			}
			if (world->items[blockX + (blockY * world->width)].greenGems > 1)
			{
				for (auto i = 0; i < world->droppedItems.size(); i++)
				{
					if (blockX == static_cast<int>(world->droppedItems.at(i).x / 32) && blockY == static_cast<int>(world->droppedItems.at(i).y / 32))
					{
						if (world->droppedItems.at(i).count == 50)
						{
							RemoveDroppedItem(peer, world->droppedItems.at(i).uid, world);
							idstoremove.push_back(world->droppedItems.at(i).uid);
						}
					}
				}
				world->items[blockX + (blockY * world->width)].greenGems = 0;
				world->items[blockX + (blockY * world->width)].purpleGems++;
				count = 100;
			}
			for (auto i = 0; i < idstoremove.size(); i++) processTakeServer(peer, idstoremove.at(i));
		}



		DroppedItem itemDropped;
		itemDropped.id = item;
		itemDropped.count = count;
		itemDropped.x = x;
		itemDropped.y = y;
		itemDropped.droppedby = static_cast<PlayerInfo*>(peer->data)->rawName;
		world->droppedCount++;
		itemDropped.uid = world->droppedCount;
		itemDropped.madeby = history;
		world->droppedItems.push_back(itemDropped);
		sendDrop(peer, netID, x, y, item, count, specialEffect);
		return;
	}
	catch (...)
	{
		return;
	}
}

inline void sendCollect(ENetPeer* peer, int netID, int x, int y, int uid)
{
	if (uid >= 2147480000) return;
	if (uid < 0) return;
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer))
		{
			PlayerMoving data;
			data.packetType = 14;
			data.x = x;
			data.y = y;
			data.netID = netID;
			data.plantingTree = uid;
			SendPacketRaw(4, packPlayerMoving(&data), 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
			SendInventory(peer, static_cast<PlayerInfo*>(peer->data)->inventory);
		}
	}
}

inline void SaveDroppedItem(int fItemid, int fQuantity, ENetPeer* peer, bool& success, string madeBy, string history)
{


	madeBy += history;
	//madeBy += " at " + static_cast<PlayerInfo*>(peer->data)->currentWorld + " count " + to_string(fQuantity);
	size_t invsizee = static_cast<PlayerInfo*>(peer->data)->currentInventorySize;
	auto alreadyhave = false;
	if (static_cast<PlayerInfo*>(peer->data)->inventory.items.size() == invsizee && CheckItemExists(peer, fItemid) == false) alreadyhave = true;
	auto isFullStock = false;
	auto isInInv = false;
	for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
	{
		if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == fItemid && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount + fQuantity > 200) isFullStock = true;
		if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == fItemid && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount <= 200) isInInv = true;
	}
	if (isFullStock == true || alreadyhave == true)
	{
		success = false;
	}
	else
	{
		success = true;
		if (isInInv == false)
		{
			static_cast<PlayerInfo*>(peer->data)->needsaveinventory = true;
			InventoryItem item;
			item.itemID = fItemid;
			item.itemCount = fQuantity;
			item.madeBy = madeBy;
			static_cast<PlayerInfo*>(peer->data)->inventory.items.push_back(item);
			SendInventory(peer, static_cast<PlayerInfo*>(peer->data)->inventory);
		}
		else
		{
			for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
			{
				if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == fItemid)
				{
					static_cast<PlayerInfo*>(peer->data)->needsaveinventory = true;
					static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount += fQuantity;
					if (madeBy != "") static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).madeBy += " " + madeBy;
					SendInventory(peer, static_cast<PlayerInfo*>(peer->data)->inventory);
					break;
				}
			}
		}
	}
	const auto p3 = packetEnd(appendFloat(appendIntx(appendFloat(appendFloat(appendFloat(appendString(createPacket(), "OnSetClothing"), (static_cast<PlayerInfo*>(peer->data))->cloth_hair, (static_cast<PlayerInfo*>(peer->data))->cloth_shirt, (static_cast<PlayerInfo*>(peer->data))->cloth_pants), (static_cast<PlayerInfo*>(peer->data))->cloth_feet, (static_cast<PlayerInfo*>(peer->data))->cloth_face, (static_cast<PlayerInfo*>(peer->data))->cloth_hand), (static_cast<PlayerInfo*>(peer->data))->cloth_back, (static_cast<PlayerInfo*>(peer->data))->cloth_mask, (static_cast<PlayerInfo*>(peer->data))->cloth_necklace), (static_cast<PlayerInfo*>(peer->data))->skinColor), (static_cast<PlayerInfo*>(peer->data))->cloth_ances, 0.0f, 0.0f));
	memcpy(p3.data + 8, &((static_cast<PlayerInfo*>(peer->data))->netID), 4);
	const auto packet = enet_packet_create(p3.data, p3.len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
}

void sendInventory(ENetPeer* peer, PlayerInventory inventory)
{
	string asdf2 = "0400000009A7379237BB2509E8E0EC04F8720B050000000000000000FBBB0000010000007D920100FDFDFDFD04000000040000000000000000000000000000000000";
	int inventoryLen = inventory.items.size();
	int packetLen = (asdf2.length() / 2) + (inventoryLen * 4) + 4;
	BYTE* data2 = new BYTE[packetLen];
	for (int i = 0; i < asdf2.length(); i += 2)
	{
		char x = ch2n(asdf2[i]);
		x = x << 4;
		x += ch2n(asdf2[i + 1]);
		memcpy(data2 + (i / 2), &x, 1);
	}
	int endianInvVal = _byteswap_ulong(inventoryLen);
	memcpy(data2 + (asdf2.length() / 2) - 4, &endianInvVal, 4);
	endianInvVal = _byteswap_ulong(((PlayerInfo*)(peer->data))->currentInventorySize);
	memcpy(data2 + (asdf2.length() / 2) - 8, &endianInvVal, 4);
	int val = 0;
	for (int i = 0; i < inventoryLen; i++)
	{
		val = 0;
		val |= inventory.items.at(i).itemID;
		val |= inventory.items.at(i).itemCount << 16;
		val &= 0x00FFFFFF;
		val |= 0x00 << 24;
		memcpy(data2 + (i * 4) + (asdf2.length() / 2), &val, 4);
	}
	ENetPacket* packet3 = enet_packet_create(data2,
		packetLen,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet3);
	delete data2;
	//enet_host_flush(server);
}

void PlayAudioWorld(ENetPeer* peer, string audioFile)
{
	string text = "action|play_sfx\nfile|" + audioFile + "\ndelayMS|0\n";
	BYTE* data = new BYTE[5 + text.length()];
	BYTE zero = 0;
	int type = 3;
	memcpy(data, &type, 4);
	memcpy(data + 4, text.c_str(), text.length());
	memcpy(data + 4 + text.length(), &zero, 1);
	ENetPeer* currentPeer;

	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer))
		{
			ENetPacket* packet2 = enet_packet_create(data,
				5 + text.length(),
				ENET_PACKET_FLAG_RELIABLE);

			enet_peer_send(currentPeer, 0, packet2);

			//enet_host_flush(server);
		}
	}
	delete data;
}

void RemoveInventoryItem(int fItemid, int fQuantity, ENetPeer* peer)
{
	std::ifstream iffff("inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");

	json jj;

	if (iffff.fail()) {
		iffff.close();
		cout << "[!]  RemoveInventoryItem funkcijoje (ofstream dalyje) error: itemid - " << fItemid << ", kiekis - " << fQuantity << endl;

	}
	if (iffff.is_open()) {


	}

	iffff >> jj; //load


	std::ofstream oo("inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
	if (!oo.is_open()) {
		cout << GetLastError() << " RemoveInventoryItem funkcijoje (ofstream dalyje) error: itemid - " << fItemid << ", kiekis - " << fQuantity << endl;
		_getch();
	}

	//jj["items"][aposition]["aposition"] = aposition;


	for (int i = 0; i < ((PlayerInfo*)(peer->data))->currentInventorySize; i++)
	{
		int itemid = jj["items"][i]["itemid"];
		int quantity = jj["items"][i]["quantity"];
		if (itemid == fItemid)
		{
			if (quantity - fQuantity == 0)
			{
				jj["items"][i]["itemid"] = 0;
				jj["items"][i]["quantity"] = 0;
			}
			else
			{
				jj["items"][i]["itemid"] = itemid;
				jj["items"][i]["quantity"] = quantity - fQuantity;
			}

			break;
		}

	}
	oo << jj << std::endl;

	for (int i = 0; i < ((PlayerInfo*)(peer->data))->inventory.items.size(); i++)
	{
		if (((PlayerInfo*)(peer->data))->inventory.items.at(i).itemID == fItemid)
		{
			if ((unsigned int)((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount > fQuantity && (unsigned int)((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount != fQuantity)
			{
				((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount -= fQuantity;
			}
			else
			{
				((PlayerInfo*)(peer->data))->inventory.items.erase(((PlayerInfo*)(peer->data))->inventory.items.begin() + i);
			}
			sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);
		}
	}


}

void SaveShopsItemMoreTimer(int fItemid, int fQuantity, ENetPeer* peer, bool& success)
{
	size_t invsizee = ((PlayerInfo*)(peer->data))->currentInventorySize;
	bool invfull = false;
	bool alreadyhave = false;

	if (((PlayerInfo*)(peer->data))->inventory.items.size() == invsizee) {


		GamePacket ps = packetEnd(appendString(appendString(createPacket(), "OnTextOverley"), "Sorry You're Inventory is Full"));
		ENetPacket* packet = enet_packet_create(ps.data,
			ps.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete ps.data;


		alreadyhave = true;
	}


	if (((PlayerInfo*)(peer->data))->inventory.items.size() == invsizee) {


		GamePacket ps = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "add_label_with_icon|big|`4Whoops!|left|1048|\nadd_spacer|small|\nadd_textbox|`oSoory! Your inventory is full! You can purchase an inventory upgrade in the shop.|\nadd_spacer|small|\nadd_button|close|`5Close|0|0|"));
		ENetPacket* packet = enet_packet_create(ps.data,
			ps.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete ps.data;


		alreadyhave = true;
	}

	bool isFullStock = false;
	bool isInInv = false;
	for (int i = 0; i < ((PlayerInfo*)(peer->data))->inventory.items.size(); i++)
	{

		if (((PlayerInfo*)(peer->data))->inventory.items.at(i).itemID == fItemid && ((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount >= 200) {


			GamePacket ps = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "add_label_with_icon|big|`4Whoops!|left|1048|\nadd_spacer|small|\nadd_textbox|`oSorry! You already have full stock of this item!|\nadd_spacer|small|\nadd_button|close|`5Close|0|0|"));
			ENetPacket* packet = enet_packet_create(ps.data,
				ps.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet);
			delete ps.data;


			isFullStock = true;
		}

		if (((PlayerInfo*)(peer->data))->inventory.items.at(i).itemID == fItemid && ((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount < 200)	isInInv = true;

	}

	if (isFullStock == true || alreadyhave == true)
	{
		success = false;
	}
	else
	{
		success = true;

		std::ifstream iffff("inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");

		json jj;

		if (iffff.fail()) {
			iffff.close();


		}
		if (iffff.is_open()) {


		}

		iffff >> jj; //load


		std::ofstream oo("inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
		if (!oo.is_open()) {
			cout << GetLastError() << endl;
			_getch();
		}

		//jj["items"][aposition]["aposition"] = aposition;

		if (isInInv == false)
		{

			for (int i = 0; i < ((PlayerInfo*)(peer->data))->currentInventorySize; i++)
			{
				int itemid = jj["items"][i]["itemid"];
				int quantity = jj["items"][i]["quantity"];

				if (itemid == 0 && quantity == 0)
				{
					jj["items"][i]["itemid"] = fItemid;
					jj["items"][i]["quantity"] = fQuantity;
					break;
				}

			}
			oo << jj << std::endl;


			InventoryItem item;
			item.itemID = fItemid;
			item.itemCount = fQuantity;
			((PlayerInfo*)(peer->data))->inventory.items.push_back(item);

			sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);
		}
		else
		{
			for (int i = 0; i < ((PlayerInfo*)(peer->data))->currentInventorySize; i++)
			{
				int itemid = jj["items"][i]["itemid"];
				int quantity = jj["items"][i]["quantity"];

				if (itemid == fItemid)
				{
					jj["items"][i]["quantity"] = quantity + fQuantity;
					break;
				}

			}
			oo << jj << std::endl;


			for (int i = 0; i < ((PlayerInfo*)(peer->data))->inventory.items.size(); i++)
			{
				if (((PlayerInfo*)(peer->data))->inventory.items.at(i).itemID == fItemid)
				{
					((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount += fQuantity;
					sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);
				}
			}

		}
	}
}

inline void SaveItemMoreTimer(int fItemid, int fQuantity, ENetPeer* peer, bool& success, string madeby = "") {
	size_t invsizee = static_cast<PlayerInfo*>(peer->data)->currentInventorySize;
	auto alreadyhave = false;
	if (static_cast<PlayerInfo*>(peer->data)->inventory.items.size() == invsizee && CheckItemExists(peer, fItemid) == false) {
		DropItem(peer, -1, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y + rand() % 16, fItemid, fQuantity, 0);
		alreadyhave = true;
	}
	auto isFullStock = false;
	auto isInInv = false;
	for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++) {
		if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == fItemid && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 250) {
			Player::OnDialogRequest(peer, "add_label_with_icon|big|`4Whoops!|left|1048|\nadd_spacer|small|\nadd_textbox|`oSoory! You already have full stock of this item!|\nadd_spacer|small|\nadd_button|close|`5Close|0|0|");
			isFullStock = true;
		}
		if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == fItemid && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount < 250) isInInv = true;
	}
	if (isFullStock == true || alreadyhave == true) {
		success = false;
	}
	else {
		success = true;
		if (isInInv == false) {
			static_cast<PlayerInfo*>(peer->data)->needsaveinventory = true;
			InventoryItem item;
			item.itemID = fItemid;
			item.itemCount = fQuantity;
			static_cast<PlayerInfo*>(peer->data)->inventory.items.push_back(item);
			SendInventory(peer, static_cast<PlayerInfo*>(peer->data)->inventory);
		}
		else {
			for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++) {
				if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == fItemid) {
					static_cast<PlayerInfo*>(peer->data)->needsaveinventory = true;
					static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount += fQuantity;
					SendInventory(peer, static_cast<PlayerInfo*>(peer->data)->inventory);
					break;
				}
			}
		}
		const auto p3 = packetEnd(appendFloat(appendIntx(appendFloat(appendFloat(appendFloat(appendString(createPacket(), "OnSetClothing"), (static_cast<PlayerInfo*>(peer->data))->cloth_hair, (static_cast<PlayerInfo*>(peer->data))->cloth_shirt, (static_cast<PlayerInfo*>(peer->data))->cloth_pants), (static_cast<PlayerInfo*>(peer->data))->cloth_feet, (static_cast<PlayerInfo*>(peer->data))->cloth_face, (static_cast<PlayerInfo*>(peer->data))->cloth_hand), (static_cast<PlayerInfo*>(peer->data))->cloth_back, (static_cast<PlayerInfo*>(peer->data))->cloth_mask, (static_cast<PlayerInfo*>(peer->data))->cloth_necklace), (static_cast<PlayerInfo*>(peer->data))->skinColor), (static_cast<PlayerInfo*>(peer->data))->cloth_ances, 0.0f, 0.0f));
		memcpy(p3.data + 8, &((static_cast<PlayerInfo*>(peer->data))->netID), 4);
		const auto packet = enet_packet_create(p3.data, p3.len, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
	}
}

inline void SaveItemMoreTimes(int fItemid, int fQuantity, ENetPeer* peer, bool& success, string madeBy)
{

	madeBy += " at " + static_cast<PlayerInfo*>(peer->data)->currentWorld + " count " + to_string(fQuantity);
	size_t invsizee = static_cast<PlayerInfo*>(peer->data)->currentInventorySize;
	auto alreadyhave = false;
	if (static_cast<PlayerInfo*>(peer->data)->inventory.items.size() == invsizee && CheckItemExists(peer, fItemid) == false)
	{
		auto xx = static_cast<PlayerInfo*>(peer->data)->x;
		auto netid = -1;
		auto yy = static_cast<PlayerInfo*>(peer->data)->y;
		DropItem(peer, netid, xx, yy, fItemid, fQuantity, 0);
		alreadyhave = true;
	}
	auto isFullStock = false;
	auto isInInv = false;
	for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
	{
		if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == fItemid && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 200)
		{
			Player::OnDialogRequest(peer, "add_label_with_icon|big|`4Whoops!|left|1048|\nadd_spacer|small|\nadd_textbox|`oSoory! You already have full stock of this item!|\nadd_spacer|small|\nadd_button|close|`5Close|0|0|");
			isFullStock = true;
		}
		if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == fItemid && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount < 200) isInInv = true;
	}
	if (isFullStock == true || alreadyhave == true)
	{
		success = false;
	}
	else
	{
		success = true;
		if (isInInv == false)
		{
			static_cast<PlayerInfo*>(peer->data)->needsaveinventory = true;
			InventoryItem item;
			item.itemID = fItemid;
			item.itemCount = fQuantity;
			item.madeBy = madeBy;
			static_cast<PlayerInfo*>(peer->data)->inventory.items.push_back(item);
			SendInventory(peer, static_cast<PlayerInfo*>(peer->data)->inventory);
		}
		else
		{
			for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
			{
				if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == fItemid)
				{
					static_cast<PlayerInfo*>(peer->data)->needsaveinventory = true;
					static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount += fQuantity;
					static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).madeBy += " " + madeBy;
					SendInventory(peer, static_cast<PlayerInfo*>(peer->data)->inventory);
					break;
				}
			}
		}
		// update items
		const auto p3 = packetEnd(appendFloat(appendIntx(appendFloat(appendFloat(appendFloat(appendString(createPacket(), "OnSetClothing"), (static_cast<PlayerInfo*>(peer->data))->cloth_hair, (static_cast<PlayerInfo*>(peer->data))->cloth_shirt, (static_cast<PlayerInfo*>(peer->data))->cloth_pants), (static_cast<PlayerInfo*>(peer->data))->cloth_feet, (static_cast<PlayerInfo*>(peer->data))->cloth_face, (static_cast<PlayerInfo*>(peer->data))->cloth_hand), (static_cast<PlayerInfo*>(peer->data))->cloth_back, (static_cast<PlayerInfo*>(peer->data))->cloth_mask, (static_cast<PlayerInfo*>(peer->data))->cloth_necklace), (static_cast<PlayerInfo*>(peer->data))->skinColor), (static_cast<PlayerInfo*>(peer->data))->cloth_ances, 0.0f, 0.0f));
		memcpy(p3.data + 8, &((static_cast<PlayerInfo*>(peer->data))->netID), 4);
		const auto packet = enet_packet_create(p3.data, p3.len, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
	}
}

inline int getGemCount(const int item)
{
	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	auto count = 0;
	try
	{
		const auto rarity = getItemDef(item).rarity;
		if (rarity == 0) return 0;
		if (rarity > 13)
		{
			count = rarity / 13;
		}
		else
		{
			const auto ran = rand() % 2;
			switch (ran)
			{
			case 1:
				count = 1;
				break;
			case 2:
				count = 2;
				break;
			default:
				count = 0;
				break;
			}
		}
	}
	catch (...)
	{
		return 0;
	}
	return count;
}

inline void send_item(ENetPeer* peer, const int itemid, const int item_amount, const int kindofchest)
{
	auto success = false;
	SaveItemMoreTimes(itemid, item_amount, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(kindofchest).name + "");
	Player::OnConsoleMessage(peer, "`oYou have obtained `$" + getItemDef(itemid).name + "`o");
}

inline void DailyRewardCheck(ENetPeer* peer)
{
	if (static_cast<PlayerInfo*>(peer->data)->lastdailyGems <= GetCurrentTimeInternalSeconds() / 60)
	{
		static_cast<PlayerInfo*>(peer->data)->lastdailyGems = (GetCurrentTimeInternalSeconds() / 60) + 1440;
		bool success = true;
		if (static_cast<PlayerInfo*>(peer->data)->Subscriber && static_cast<PlayerInfo*>(peer->data)->SubscribtionEndDay - 1 >= 1)
		{
			SaveItemMoreTimes(1360, 2, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from daily reward");
			Player::OnConsoleMessage(peer, "`oYou have received 2 daily gifts");
		}
		else
		{
			SaveItemMoreTimes(1360, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from daily reward");
			Player::OnConsoleMessage(peer, "`oYou have received daily gift");
		}
		Player::OnConsoleMessage(peer, "`bHello Player GrowZS, Welcome To This Server. You Got `^505.000k `bGems And `^5 Blue Game Lock!");
		Player::onGiveGems(peer, 5000);


		ifstream fg("players/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".json");
		json j;
		fg >> j;
		fg.close();

		if (static_cast<PlayerInfo*>(peer->data)->Subscriber)
		{
			static_cast<PlayerInfo*>(peer->data)->SubscribtionEndDay -= 1;
			if (static_cast<PlayerInfo*>(peer->data)->SubscribtionEndDay <= 0)
			{
				j["subtype"] = "";
				j["subdate"] = "";
			}
			else
			{
				j["subdate"] = to_string(static_cast<PlayerInfo*>(peer->data)->SubscribtionEndDay);
			}
		}
		j["dailyrewards"] = static_cast<PlayerInfo*>(peer->data)->lastdailyGems;

		ofstream fs("players/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".json");
		fs << j;
		fs.close();

		if (static_cast<PlayerInfo*>(peer->data)->SubscribtionEndDay == 0)
		{
			static_cast<PlayerInfo*>(peer->data)->Subscriber = false;
			static_cast<PlayerInfo*>(peer->data)->haveSuperSupporterName = false;
			static_cast<PlayerInfo*>(peer->data)->chatcolor = "";
			static_cast<PlayerInfo*>(peer->data)->NickPrefix = "";
			static_cast<PlayerInfo*>(peer->data)->SubscribtionEndDay = 0;
			auto iscontains = false;
			SearchInventoryItem(peer, 6260, 1, iscontains);
			if (iscontains)
			{
				RemoveInventoryItem(6260, 1, peer, true);
			}
			LoadPlayerData(peer);
			if (static_cast<PlayerInfo*>(peer->data)->isinv)
			{
				static_cast<PlayerInfo*>(peer->data)->isinv = false;
				Player::OnInvis(peer, 0, static_cast<PlayerInfo*>(peer->data)->netID);
			}
			send_state(peer);
			if (static_cast<PlayerInfo*>(peer->data)->cloth_necklace == 6260)
			{
				static_cast<PlayerInfo*>(peer->data)->cloth_necklace = 0;
				static_cast<PlayerInfo*>(peer->data)->effect = 8421376;
				ofstream WorldSys("misc/effect/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
				WorldSys << 8421376;
				WorldSys.close();
				sendPuncheffect(peer, static_cast<PlayerInfo*>(peer->data)->effect);
				ifstream fgg("players/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".json");
				json js;
				fgg >> js;
				fgg.close();

				js["ClothNeck"] = 0;
				js["effect"] = 8421376;

				ofstream fss("players/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".json");
				fss << js;
				fss.close();
			}
			sendClothes(peer);
		}
	}

	if (static_cast<PlayerInfo*>(peer->data)->startkit == false)
	{
		ifstream fg("players/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".json");
		json j;
		fg >> j;
		fg.close();

		j["startkit"] = true;

		ofstream fs("players/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".json");
		fs << j;
		fs.close();
		bool success = false;
		SaveItemMoreTimes(954, 150, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from start kit");
		SaveItemMoreTimes(5666, 70, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from start kit");
		SaveItemMoreTimes(340, 30, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from start kit");
		SaveItemMoreTimes(98, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from start kit");
		SaveItemMoreTimes(7188, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from start kit");
		Player::onGiveGems(peer, 500000);
		static_cast<PlayerInfo*>(peer->data)->startkit = true;
		Player::OnConsoleMessage(peer, "`bWelcome To GrowZS, You Get `^505.000K Gems `bAnd More `^5 Blue Game Lock!");
	}
}

inline bool isWorldAdmin2(ENetPeer* peer, WorldInfo world)
{
	const auto uid = static_cast<PlayerInfo*>(peer->data)->rawName;
	for (const auto i = 0; world.accessed.size();)
	{
		const auto x = world.accessed.at(i);
		if (uid == x.substr(0, x.find("|")))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}


inline void PerformPacketCheck(ENetPeer* peer)
{
	using namespace std::chrono;
	if (static_cast<PlayerInfo*>(peer->data)->packetsec + 1000 > (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count())
	{
		if (static_cast<PlayerInfo*>(peer->data)->packetinsec >= 50)
		{
			if (!static_cast<PlayerInfo*>(peer->data)->Console) enet_peer_reset(peer);
		}
		else
		{
			static_cast<PlayerInfo*>(peer->data)->packetinsec = static_cast<PlayerInfo*>(peer->data)->packetinsec + 1;
		}
	}
	else
	{
		static_cast<PlayerInfo*>(peer->data)->packetsec = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
		static_cast<PlayerInfo*>(peer->data)->packetinsec = 0;
	}
}

inline void SendBreakPacket(ENetPeer* peer, const int x, const int y)
{
	PlayerMoving data;
	// ReSharper disable once CppAssignedValueIsNeverUsed
	data.netID = static_cast<PlayerInfo*>(peer->data)->netID;
	data.packetType = 0x8;
	data.plantingTree = 0;
	data.netID = -1;
	data.x = x;
	data.y = y;
	data.punchX = x;
	data.punchY = y;
	SendPacketRaw(4, packPlayerMoving(&data), 56, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
}


inline void sendFrozenState(ENetPeer* peer)
{
	const auto info = static_cast<PlayerInfo*>(peer->data);
	const auto netID = info->netID;
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			PlayerMoving data;
			data.packetType = 0x14;
			data.characterState = 0;
			data.x = 1000;
			data.y = 100;
			data.punchX = 0;
			data.punchY = 0;
			data.XSpeed = 300;
			data.YSpeed = 600;
			data.netID = netID;
			data.plantingTree = 2048;
			const auto raw = packPlayerMoving(&data);
			auto var = info->effect;
			memcpy(raw + 1, &var, 3);
			SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
}

inline void SendFishingState(ENetPeer* peer)
{
	const auto info = static_cast<PlayerInfo*>(peer->data);
	const auto netID = info->netID;
	const auto state = getState(info);
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			PlayerMoving data;
			data.packetType = 0x14;
			data.characterState = static_cast<PlayerInfo*>(peer->data)->characterState;
			data.x = 0;
			data.y = 900000000;
			data.punchX = 0;
			data.punchY = 0;
			data.XSpeed = 0;
			data.YSpeed = 900000000;
			data.netID = netID;
			data.plantingTree = state;
			const auto raw = packPlayerMoving(&data);
			auto var = info->effect;
			memcpy(raw + 1, &var, 3);
			SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
}

inline void sendWorldOffers(ENetPeer* peer)
{

	if (!static_cast<PlayerInfo*>(peer->data)->isIn) return;
	auto worlds = worldDB.getRandomWorlds();
	string worldOffers = "default|";
	if (worlds.size() > 0)
	{
		if (static_cast<PlayerInfo*>(peer->data)->isIn && static_cast<PlayerInfo*>(peer->data)->haveGrowId)
		{
			string lastworld = "EXIT";
			ifstream of("lastnormalworld/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
			of >> lastworld;
			of.close();
			if (lastworld != "EXIT" && lastworld != "") worldOffers += lastworld;
			else worldOffers += "START";
		}
		else
		{
			worldOffers += worlds[0].name;
		}
	}

	/*
	default|UNLIBAITS
add_button|Showing: `wRandom Worlds``|_catselect_|0.6|3529161471|
add_floater|CSN5ZUG2888|9|0.67|3529161471
add_floater|CSN10BANK9616|8|0.64|3529161471
add_floater|CSN5MERGE1209|8|0.64|3529161471
add_floater|FH10CSN4906|5|0.55|3529161471
add_floater|GROWGANOTH183|2|0.46|3529161471
add_floater|WINGROADTODL|1|0.43|3529161471
add_floater|CSN10BANK9616XTUCFGKYUHI|1|0.43|3529161471
add_floater|UNLIBAITS|0|0.5|3417414143
add_floater|VAIOT|0|0.5|3417414143
add_floater|VAIOT2|0|0.5|3417414143
add_floater|BUYSURGE|2|0.46|3417414143
add_floater|MRWOKES|0|0.5|3417414143
add_floater|BUYBRIEF|0|0.5|3417414143
add_floater|BUYLEGALBREIFS|0|0.5|3417414143
add_floater|START|0|1|3529161471*/
	worldOffers += "\nadd_button|Showing: `wRandom Worlds``|_catselect_|0.6|3529161471|\n";
	//worldOffers += "\nadd_floater|START|START|0.55|3629161471|\n";
	//if (GrowganothEvent) worldOffers += "\nadd_floater|GROWGANOTH|GROWGANOTH|0.55|1029161471|\n";
	//if (!game1status) worldOffers += "\nadd_floater|GAME1|GAME1|0.55|3629161471|\n";
	for (auto i = 0; i < worlds.size(); i++)
	{
		if (getPlayersCountInWorld(worlds[i].name) <= 0) continue;
		if (worlds[i].name == "START" || worlds[i].name == "GROWGANOTH" || worlds[i].name == "GAME1" || worlds[i].name == "GAME2" || worlds[i].isNuked) continue;
		float size = 0.40;
		size += 0.03 * getPlayersCountInWorld(worlds[i].name);
		if (size > 0.75) size = 0.75;
		worldOffers += "add_floater|" + worlds[i].name + "|" + std::to_string(getPlayersCountInWorld(worlds[i].name)) + "|" + to_string(size) + "|3529161471\n";
	}
	for (int i = static_cast<PlayerInfo*>(peer->data)->lastworlds.size() - 1; i >= 0; --i)
	{
		worldOffers += "\nadd_floater|" + static_cast<PlayerInfo*>(peer->data)->lastworlds[i] + "|0|0.5|3417414143|\n";
	}
	auto p3 = packetEnd(appendString(appendString(createPacket(), "OnRequestWorldSelectMenu"), worldOffers));
	const auto packet3 = enet_packet_create(p3.data, p3.len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet3);
	delete p3.data;

	/*if (!static_cast<PlayerInfo*>(peer->data)->isIn) return;
	auto worlds = worldDB.getRandomWorlds();
	string worldOffers = "default|";
	if (worlds.size() > 0)
	{
		worldOffers += worlds[0].name;
	}
	worldOffers += "\nadd_floater|START|START|0.55|3629161471|\n";
	if (GrowganothEvent) worldOffers += "\nadd_floater|GROWGANOTH|GROWGANOTH|0.55|1029161471|\n";
	if (!game1status) worldOffers += "\nadd_floater|GAME1|GAME1|0.55|3629161471|\n";
	for (auto i = 0; i < worlds.size(); i++)
	{
		if (getPlayersCountInWorld(worlds[i].name) <= 0) continue;
		if (worlds[i].name == "START" || worlds[i].name == "GROWGANOTH" || worlds[i].name == "GAME1") continue;
		float size = 0.40;
		size += 0.03 * getPlayersCountInWorld(worlds[i].name);
		if (size > 0.75) size = 0.75;
		worldOffers += "add_floater|" + worlds[i].name + "|" + std::to_string(getPlayersCountInWorld(worlds[i].name)) + "|" + to_string(size) + "|3529161471\n";
	}
	auto p3 = packetEnd(appendString(appendString(createPacket(), "OnRequestWorldSelectMenu"), worldOffers));
	const auto packet3 = enet_packet_create(p3.data, p3.len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet3);
	delete p3.data;*/
}

inline void SendGamePacketEveryoneInWorld(ENetPeer* peer, GamePacket* p)
{
	const auto packet1 = enet_packet_create(p->data, p->len, ENET_PACKET_FLAG_RELIABLE);
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			enet_peer_send(currentPeer, 0, packet1);
		}
	}
	delete p->data;
}

inline void SendChat(ENetPeer* peer, const int netID, string message)
{
	if (serverIsFrozen) return;
	if (static_cast<PlayerInfo*>(peer->data)->currentWorld == "EXIT") return;
	if (static_cast<PlayerInfo*>(peer->data)->isIn == false) return;
	const auto world = getPlyersWorld(peer);
	if (message.length() >= 120) return;
	if (message.length() == 0) return;
	if (message == " ") return;
	if (1 > (message.size() - countSpaces(message))) return;
	if (world->silence == true && !isWorldOwner(peer, world))
	{
		Player::OnTalkBubble(peer, netID, "`1(Peasants must not to talk)", 0, true);
		return;
	}
	removeExtraSpaces(message);
	message = trimString(message);
	if (static_cast<PlayerInfo*>(peer->data)->haveGrowId == true)
	{
		string ccode;
		string chatcode;
		if (isDev(peer))
		{
			ccode = "5";
			chatcode = "5";
		}
		if (isMod(peer))
		{
			ccode = "^";
			chatcode = "^";
		}
		if (isPlayer(peer))
		{
			ccode = "w";
			chatcode = "$";
		}
		if (static_cast<PlayerInfo*>(peer->data)->isNicked)
		{
			ccode = "w";
			chatcode = "$";
		}
		if (static_cast<PlayerInfo*>(peer->data)->Subscriber && static_cast<PlayerInfo*>(peer->data)->chatcolor != "")
		{
			ccode = static_cast<PlayerInfo*>(peer->data)->chatcolor;
			chatcode = static_cast<PlayerInfo*>(peer->data)->chatcolor;
		}
		for (auto c : message)
		{
			if (c < 0x18 || std::all_of(message.begin(), message.end(), static_cast<int(*)(int)>(isspace)))
			{
				return;
			}
		}
		ENetPeer* currentPeer;
		string name = "";
		for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (static_cast<PlayerInfo*>(currentPeer->data)->netID == netID)
			{
				name = static_cast<PlayerInfo*>(currentPeer->data)->displayName;
			}
		}
		auto p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "CP:_PL:0_OID:_CT:[W]_ `6<`w" + name + "`6> `" + chatcode + message));
		auto p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), netID), "`" + ccode + message), 0));
		for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer) || static_cast<PlayerInfo*>(currentPeer->data)->GlobalChat)
			{
				const auto packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet);
				if (message == "" || message == " " || message == "  ") continue;
				const auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2);
			}
		}
		delete p.data;
		delete p2.data;
	}
}

inline void sendWho(ENetPeer* peer)
{
	string whoisinworld = "";
	for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (static_cast<PlayerInfo*>(currentPeer->data)->isInvisible) continue;
		if (isHere(peer, currentPeer) && static_cast<PlayerInfo*>(currentPeer->data)->isinv == false)
		{
			if (static_cast<PlayerInfo*>(currentPeer->data)->Console) continue;
			auto p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), static_cast<PlayerInfo*>(currentPeer->data)->netID), static_cast<PlayerInfo*>(currentPeer->data)->displayName), 1));
			const auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet2);
			delete p2.data;
			whoisinworld += static_cast<PlayerInfo*>(currentPeer->data)->displayName + ", ";

		}
	}
	if (whoisinworld != "")
	{
		Player::OnConsoleMessage(peer, "`wWho's in `9" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "`w: " + whoisinworld);
	}
}

inline void sendAction(ENetPeer* peer, int netID, string action)
{
	auto p2 = packetEnd(appendString(appendString(createPacket(), "OnAction"), action));
	for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			memcpy(p2.data + 8, &netID, 4);
			const auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(currentPeer, 0, packet2);
		}
	}
	delete p2.data;
}

inline void SendTake(ENetPeer* peer, const int netID, const int x, const int y, const int item)
{
	if (item >= 9999) return;
	if (item < 0) return;
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			PlayerMoving data;
			data.packetType = 14;
			data.x = x;
			data.y = y;
			data.netID = netID;
			data.plantingTree = item;
			auto raw = packPlayerMoving(&data);
			SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_EVENT_TYPE_RECEIVE);
			raw = nullptr;
		}
	}
	SendInventory(peer, static_cast<PlayerInfo*>(peer->data)->inventory);
}

inline void sendResetState(ENetPeer* peer)
{
	if (static_cast<PlayerInfo*>(peer->data)->isCursed)
	{
		const auto info = static_cast<PlayerInfo*>(peer->data);
		const auto netID = info->netID;
		for (auto currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				PlayerMoving data;
				data.packetType = 0x14;
				data.characterState = 0;
				data.x = 1000;
				data.y = 100;
				data.punchX = 0;
				data.punchY = 0;
				data.XSpeed = 300;
				data.YSpeed = 600;
				data.netID = netID;
				data.plantingTree = 4096;
				const auto raw = packPlayerMoving(&data);
				auto var = info->effect;
				memcpy(raw + 1, &var, 3);
				SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
			}
			else
			{
				if (static_cast<PlayerInfo*>(peer->data)->isDuctaped)
				{
					const auto player_info = static_cast<PlayerInfo*>(peer->data);
					const auto net_id = player_info->netID;
					for (auto peer2 = server->peers;
						peer2 < &server->peers[server->peerCount];
						++peer2)
					{
						if (peer2->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, peer2))
						{
							PlayerMoving data;
							data.packetType = 0x14;
							data.characterState = 0;
							data.x = 1000;
							data.y = 100;
							data.punchX = 0;
							data.punchY = 0;
							data.XSpeed = 300;
							data.YSpeed = 600;
							data.netID = net_id;
							data.plantingTree = 8192;
							const auto raw = packPlayerMoving(&data);
							auto var = player_info->effect;
							memcpy(raw + 1, &var, 3);
							SendPacketRaw(4, raw, 56, nullptr, peer2, ENET_PACKET_FLAG_RELIABLE);
						}
						else
						{
							PlayerMoving data;
							data.packetType = 0x14;
							data.characterState = 0;
							data.x = 1000;
							data.y = 100;
							data.punchX = 0;
							data.punchY = 0;
							data.XSpeed = 300;
							data.YSpeed = 600;
							data.netID = net_id;
							data.plantingTree = 2;
							const auto raw = packPlayerMoving(&data);
							auto var = player_info->effect;
							memcpy(raw + 1, &var, 3);
							SendPacketRaw(4, raw, 56, nullptr, peer2, ENET_PACKET_FLAG_RELIABLE);
						}
					}
				}
			}
		}
	}
}


inline void SendGamePacket(ENetPeer* peer, GamePacket* p)
{
	const auto packet1 = enet_packet_create(p->data, p->len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet1);
}

void DoCancelTransitionAndTeleport(ENetPeer* peer, int x, int y)
{
	GamePacket p = packetEnd(appendInt(appendString(createPacket(), "OnZoomCamera"), 2));
	SendGamePacket(peer, &p);
	GamePacket p2 = packetEnd(appendIntx(appendString(createPacket(), "OnSetFreezeState"), 0));
	memcpy(p2.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
	SendGamePacket(peer, &p2);
	GamePacket p3 = packetEnd(appendInt(appendString(createPacket(), "OnFailedToEnterWorld"), 1));
	SendGamePacket(peer, &p3);
	GamePacket p4 = packetEnd(appendFloat(appendString(createPacket(), "OnSetPos"), x * 32, y * 32));
	memcpy(p4.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
	SendGamePacket(peer, &p4);
}

inline void DoCancelTransitionAndTeleport(ENetPeer* peer, const int x, const int y, bool entered, bool animations) {
	if (animations) {
		auto respawnTimeout = 200;
		auto deathFlag = 0x19;
		if (!entered) {
			auto p2 = packetEnd(appendFloat(appendString(createPacket(), "OnSetPos"), x * 32, y * 32));
			memcpy(p2.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
			memcpy(p2.data + 24, &respawnTimeout, 4);
			memcpy(p2.data + 56, &deathFlag, 4);
			const auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet2);
			delete p2.data;
		}
		auto p23 = packetEnd(appendIntx(appendFloat(appendString(createPacket(), "OnZoomCamera"), 10000.000000), 1000));
		memcpy(p23.data + 24, &respawnTimeout, 4);
		memcpy(p23.data + 56, &deathFlag, 4);
		const auto packet2 = enet_packet_create(p23.data, p23.len, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet2);
		delete p23.data;

		auto p234 = packetEnd(appendIntx(appendString(createPacket(), "OnSetFreezeState"), 0));
		memcpy(p234.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
		memcpy(p234.data + 24, &respawnTimeout, 4);
		memcpy(p234.data + 56, &deathFlag, 4);
		const auto packet23 = enet_packet_create(p234.data, p234.len, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet23);
		delete p234.data;

		auto p2346 = packetEnd(appendString(appendString(createPacket(), "OnPlayPositioned"), "audio/door_open.wav"));
		memcpy(p2346.data + 24, &respawnTimeout, 4);
		memcpy(p2346.data + 56, &deathFlag, 4);
		const auto packet249 = enet_packet_create(p2346.data, p2346.len, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet249);
		delete p2346.data;
	}
	else {
		if (!entered) {
			GamePacket p4 = packetEnd(appendFloat(appendString(createPacket(), "OnSetPos"), x * 32, y * 32));
			memcpy(p4.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
			SendGamePacket(peer, &p4);
		}
		Player::OnZoomCamera(peer, 10000.000000, 1000);
		auto p2 = packetEnd(appendIntx(appendString(createPacket(), "OnSetFreezeState"), 0));
		memcpy(p2.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
		SendGamePacket(peer, &p2);
		auto psp = packetEnd(appendString(appendString(createPacket(), "OnPlayPositioned"), "audio/door_open.wav"));
		const auto packetd = enet_packet_create(psp.data, psp.len, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packetd);
		delete psp.data;
	}
}


inline void WhiteDoor(const int x, const int y, const int tile, const int causedBy, ENetPeer* peer)
{
	const auto world = getPlyersWorld(peer);
	if (world->items[x + (y * world->width)].foreground == 6)
	{
		if (static_cast<PlayerInfo*>(peer->data)->canExit)
		{
			auto total = 0;
			for (auto currentPeer = server->peers;
				currentPeer < &server->peers[server->peerCount];
				++currentPeer)
			{
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
				if (static_cast<PlayerInfo*>(currentPeer->data)->Console) continue;
				if (static_cast<PlayerInfo*>(currentPeer->data)->isinv) continue;
				total++;
			}
			Player::OnConsoleMessage(peer, "Where would you like to go? (`w" + to_string(total) + " `oonline)");
			sendPlayerLeave(peer, static_cast<PlayerInfo*>(peer->data));
			static_cast<PlayerInfo*>(peer->data)->currentWorld = "EXIT";
			sendWorldOffers(peer);
		}
	}
}

inline void CheckPlayerState()
{
	using namespace std::chrono;
	while (true)
	{
		Sleep(1000);
		for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
		{
			if (currentPeer->data == nullptr) continue;
			if (static_cast<PlayerInfo*>(currentPeer->data)->currentWorld == "EXIT") continue;
			if (!static_cast<PlayerInfo*>(currentPeer->data)->isIn) continue;
			if (!static_cast<PlayerInfo*>(currentPeer->data)->haveGrowId) continue;
			if (static_cast<PlayerInfo*>(currentPeer->data)->isCursed == true)
			{
				auto cooldownleft = calcBanDuration(static_cast<PlayerInfo*>(currentPeer->data)->lastCursed);
				if (cooldownleft < 1)
				{
					Player::OnTextOverlay(currentPeer, "`^Your `4Curse `^Has `2Expired, `4Don't `^Break `2Rules `^Anymore!");
					Player::OnConsoleMessage(currentPeer, "`^Your `4Curse `^Has `2Expired, `4Don't `^Break `2Rules `^Anymore!");
					static_cast<PlayerInfo*>(currentPeer->data)->skinColor = 0x8295C3FF;
					sendClothes(currentPeer);
					static_cast<PlayerInfo*>(currentPeer->data)->isCursed = false;
					send_state(currentPeer);
					remove(("cursedplayers/" + static_cast<PlayerInfo*>(currentPeer->data)->rawName + ".txt").c_str());
				}
			}
			if (static_cast<PlayerInfo*>(currentPeer->data)->isDuctaped == true)
			{
				auto cooldownleft = calcBanDuration(static_cast<PlayerInfo*>(currentPeer->data)->lastMuted);
				if (cooldownleft < 1)
				{
					Player::OnTextOverlay(currentPeer, "`^Your `4Mute `^Has `2Expired, `4Don't `^Break `2Rules `^Anymore!");
					Player::OnConsoleMessage(currentPeer, "`^Your `4Mute `^Has `2Expired, `4Don't `^Break `2Rules `^Anymore!");
					static_cast<PlayerInfo*>(currentPeer->data)->taped = false;
					static_cast<PlayerInfo*>(currentPeer->data)->isDuctaped = false;
					static_cast<PlayerInfo*>(currentPeer->data)->cantsay = false;
					send_state(currentPeer);
					sendClothes(currentPeer);
					remove(("timemuted/" + static_cast<PlayerInfo*>(currentPeer->data)->rawName + ".txt").c_str());
				}
			}
			if (static_cast<PlayerInfo*>(currentPeer->data)->SurgeryCooldown)
			{
				auto cooldownleft = calcBanDuration(static_cast<PlayerInfo*>(currentPeer->data)->SurgeryTime);
				if (cooldownleft < 1)
				{

					Player::OnConsoleMessage(currentPeer, "You've paid your debt to society! (`$Malpractice`` mod removed)");
					sendSound(currentPeer, "audio/dialog_confirm.wav");
					static_cast<PlayerInfo*>(currentPeer->data)->SurgeryCooldown = false;
					static_cast<PlayerInfo*>(currentPeer->data)->SurgeryTime = 0;
					remove(("buffs/surgery/" + static_cast<PlayerInfo*>(currentPeer->data)->rawName + ".txt").c_str());
				}

			}
		}
	}
}

void autoSaveWorlds() {
	while (1) {
		Sleep(200000);
		string text = "action|play_sfx\nfile|audio/beep.wav\ndelayMS|0\n";
		BYTE* data = new BYTE[5 + text.length()];
		BYTE zero = 0;
		int type = 3;
		memcpy(data, &type, 4);
		memcpy(data + 4, text.c_str(), text.length());
		memcpy(data + 4 + text.length(), &zero, 1);
		ENetPacket* packet2 = enet_packet_create(data,
			5 + text.length(),
			ENET_PACKET_FLAG_RELIABLE);
		enet_host_broadcast(server, 0, packet2);
		GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`4Saving all worlds `oin `p5 `wseconds`o, you will be timed out for a short amount of time`w! `oDon't punch anything or you may get disconnected!``"));
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_host_broadcast(server, 0, packet);
		delete data;
		delete p.data;
		Sleep(5500);
		saveAllWorlds();
	}
}

inline void Respawn(ENetPeer* peer)
{
	auto x = 3040;
	auto y = 736;
	const auto world = getPlyersWorld(peer);
	if (world)
	{
		for (auto currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				const auto val = static_cast<PlayerInfo*>(peer->data)->x;
				const auto i = static_cast<PlayerInfo*>(peer->data)->y;
				auto psp = packetEnd(appendFloat(appendIntx(appendString(createPacket(), "OnParticleEffect"), 3), val, (i + 8)));
				const auto packetd = enet_packet_create(psp.data, psp.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packetd);
				delete psp.data;
				string text = "action|play_sfx\nfile|audio/male_scream.wav\ndelayMS|0\n";
				const auto data = new BYTE[5 + text.length()];
				BYTE zero = 0;
				auto type = 3;
				memcpy(data, &type, 4);
				memcpy(data + 4, text.c_str(), text.length());
				memcpy(data + 4 + text.length(), &zero, 1);
				{
					const auto packetres = enet_packet_create(data, 5 + text.length(), ENET_PACKET_FLAG_RELIABLE);
					if (isHere(peer, currentPeer))
					{
						enet_peer_send(currentPeer, 0, packetres);
					}
				}
			}
		}
		for (auto i = 0; i < world->width * world->height; i++)
		{
			if (world->items[i].foreground == 6)
			{
				x = (i % world->width) * 32;
				y = (i / world->width) * 32;
			}
		}
		{
			PlayerMoving data;
			data.packetType = 0x0;
			data.characterState = 0x924; // animation
			data.x = x;
			data.y = y;
			data.punchX = -1;
			data.punchY = -1;
			data.XSpeed = 0;
			data.YSpeed = 0;
			data.netID = static_cast<PlayerInfo*>(peer->data)->netID;
			data.plantingTree = 0x0;
			SendPacketRaw(4, packPlayerMoving(&data), 56, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
		}
		{
			auto val = 3040;
			auto val2 = 736;
			for (auto i = 0; i < world->width * world->height; i++)
			{
				if (world->items[i].foreground == 6)
				{
					val = (i % world->width) * 32;
					val2 = (i / world->width) * 32;
				}
			}
			auto p2 = packetEnd(appendFloat(appendString(createPacket(), "OnSetPos"), val, val2));
			memcpy(p2.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
			const auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet2);
			delete p2.data;
		}
		{
			auto p2 = packetEnd(appendIntx(appendString(createPacket(), "OnSetFreezeState"), 0));
			memcpy(p2.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
			const auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet2);
			delete p2.data;
			enet_host_flush(server);
		}
	}
	if (static_cast<PlayerInfo*>(peer->data)->usedCP == false)
	{
		auto p2 = packetEnd(appendFloat(appendString(createPacket(), "OnSetPos"), x, y));
		memcpy(p2.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
		const auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet2);
		delete p2.data;
	}
	else
	{
		auto p2 = packetEnd(appendFloat(appendString(createPacket(), "OnSetPos"), static_cast<PlayerInfo*>(peer->data)->cpX, static_cast<PlayerInfo*>(peer->data)->cpY));
		memcpy(p2.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
		const auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet2);
		delete p2.data;
	}
}

inline void SendParticleEffect(ENetPeer* peer, int x, int y, int size, int id, int delay)
{
	PlayerMoving datx;
	datx.packetType = 0x11;
	datx.x = x;
	datx.y = y;
	datx.YSpeed = id;
	datx.XSpeed = size;
	datx.plantingTree = delay;
	SendPacketRaw(4, packPlayerMoving(&datx), 56, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
}

inline void find_geiger(ENetPeer* peer)
{
	const auto world = getPlyersWorld(peer);
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (world->geigerX == 0 && world->geigerY == 0)
		{
			srand(GetTickCount());
			const auto geigercounterx = rand() % 3000;
			const auto geigercountery = rand() % 1500;
			world->geigerX = geigercounterx;
			world->geigerY = geigercountery;
		}
		if (static_cast<PlayerInfo*>(peer->data)->x >= world->geigerX - 30 && static_cast<PlayerInfo*>(peer->data)->x <= world->geigerX + 30 && static_cast<PlayerInfo*>(peer->data)->y >= world->geigerY - 30 && static_cast<PlayerInfo*>(peer->data)->y <= world->geigerY + 30)
		{
			SendParticleEffect(peer, static_cast<PlayerInfo*>(peer->data)->x + 10, static_cast<PlayerInfo*>(peer->data)->y + 10, 3, 114, 0);
			std::vector<int> list{ 1498, 1500, 2804, 2806, 8270, 8272, 8274, 2242, 2244, 2246, 2248, 9512, 2250 };
			if (ValentineEvent) list.push_back(4426);
			const int index = rand() % list.size();
			const auto value = list[index];
			Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You found " + getItemDef(value).name + "!", 0, true);
			auto success = true;
			SaveItemMoreTimes(value, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from geiger");
			srand(GetTickCount());
			const auto geigercounterx = rand() % 3000;
			const auto geigercountery = rand() % 1500;
			world->geigerX = geigercounterx;
			world->geigerY = geigercountery;
		}
		else
		{
			const auto checkx = world->geigerX - static_cast<PlayerInfo*>(peer->data)->x;
			const auto checky = static_cast<PlayerInfo*>(peer->data)->y - world->geigerY;
			if (checkx > 200 || checkx < -200)
			{
				SendParticleEffect(peer, static_cast<PlayerInfo*>(peer->data)->x + 10, static_cast<PlayerInfo*>(peer->data)->y + 10, 0, 114, 0);
			}
			else if (checky > 200 || checky < -200)
			{
				SendParticleEffect(peer, static_cast<PlayerInfo*>(peer->data)->x + 10, static_cast<PlayerInfo*>(peer->data)->y + 10, 1, 114, 0);
			}
			else
			{
				SendParticleEffect(peer, static_cast<PlayerInfo*>(peer->data)->x + 10, static_cast<PlayerInfo*>(peer->data)->y + 10, 2, 114, 0);
			}
		}
	}
}

inline void updateworldremove(ENetPeer* peer)
{
	if (static_cast<PlayerInfo*>(peer->data)->isNicked && static_cast<PlayerInfo*>(peer->data)->NickPrefix == "") return;
	if (isDev(peer))
	{
		static_cast<PlayerInfo*>(peer->data)->displayName = static_cast<PlayerInfo*>(peer->data)->rawName;
		for (auto currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				Player::OnNameChanged(currentPeer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + static_cast<PlayerInfo*>(peer->data)->rawName);
			}
		}
	}
	else if (isMod(peer))
	{
		static_cast<PlayerInfo*>(peer->data)->displayName = static_cast<PlayerInfo*>(peer->data)->rawName;
		for (auto currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				Player::OnNameChanged(currentPeer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + static_cast<PlayerInfo*>(peer->data)->rawName);
			}
		}
	}
	else if (isPlayer(peer))
	{
		static_cast<PlayerInfo*>(peer->data)->displayName = static_cast<PlayerInfo*>(peer->data)->rawName;
		for (auto currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				Player::OnNameChanged(currentPeer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->rawName);
			}
		}
	}
}

inline void treeModify(ENetPeer* peer, const int x, const int y, const int NetID)
{
	try
	{
		PlayerMoving data_;
		data_.packetType = 0xC;
		data_.x = 0;
		data_.y = 0;
		data_.punchX = x;
		data_.punchY = y;
		data_.XSpeed = 0;
		data_.YSpeed = 0;
		data_.netID = NetID;
		data_.plantingTree = 0;
		const auto raw = packPlayerMoving(&data_);
		memset(raw + 8, 0xFF, 4);
		SendPacketRaw(4, raw, 56, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
	}
	catch (...)
	{
		cout << "Error while replacing the tree..." << endl;
	}
}

inline bool isSeed(const int block)
{
	return block % 2 == 1;
}

inline void accessPlayer(ENetPeer* peer, const string name, WorldInfo* world)
{
	if (!world) return;
	auto retcode = -1;
	string player = "";
	if (static_cast<PlayerInfo*>(peer->data)->haveGrowId == false) return;
	if (world->owner != static_cast<PlayerInfo*>(peer->data)->rawName) return;
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (peer != currentPeer)
		{
			if (isHere(peer, currentPeer))
			{
				if (static_cast<PlayerInfo*>(currentPeer->data)->rawName == name)
				{
					world->accessed.push_back(static_cast<PlayerInfo*>(currentPeer->data)->rawName + "|" + static_cast<PlayerInfo*>(currentPeer->data)->displayName);
					retcode = 0;
					player = static_cast<PlayerInfo*>(currentPeer->data)->displayName;
					break;
				}
			}
		}
	}
	if (retcode == 0)
	{
		Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Successfully given access to " + player, 0, true);
		for (auto currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				Player::PlayAudio(peer, "audio/secret.wav", 250);
			}
		}
	}
}
inline void DropBlock(ENetPeer* peer, const int x, const int y, const int foreground)
{
	if (getItemDef(foreground).properties & Property_Dropless) return;
	DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), foreground, 1, 0);
}

inline void SendDropSeed(ENetPeer* peer, const int x, const int y, const int foreground)
{
	if (getItemDef(foreground).properties & Property_NoSeed || getItemDef(foreground).properties & Property_Dropless) return;
	if (specialdrop != 0)
	{
		if ((rand() % 550) <= 6)
		{
			DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), specialdrop, 1, 0);
		}
	}
	if ((rand() % 90000) <= 3)
	{
		DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5018, 1, 0);
	}
	/*fire chi*/
	if (getItemDef(foreground).blockType == BlockTypes::PAIN_BLOCK)
	{
		if ((rand() % 950) <= 6)
		{
			DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5024, 1, 0);
		}
	}
	/*water chi*/
	if (foreground == 5034 || foreground == 5048 || foreground == 7520 || foreground == 7522 || foreground == 7772 || foreground == 7774 || foreground == 8240 || foreground == 3506 || foreground == 3584)
	{
		if ((rand() % 950) <= 6)
		{
			DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5026, 1, 0);
		}
	}
	/*earth chi*/
	if (getItemDef(foreground).blockType == BlockTypes::FOREGROUND && foreground != 5034 && foreground != 5048 && foreground != 7520 && foreground != 7522 && foreground != 7772 && foreground != 7774 && foreground != 2794 || foreground != 2796 || foreground != 2810 && foreground != 8240 && foreground != 3506 && foreground != 3584)
	{
		if ((rand() % 950) <= 6)
		{
			DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5028, 1, 0);
		}
	}
	/*wind chi*/
	if (foreground == 2794 || foreground == 2796 || foreground == 2810)
	{
		if ((rand() % 950) <= 6)
		{
			DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5030, 1, 0);
		}
	}
	int chance;
	if (getItemDef(foreground).rarity < 25)
	{
		chance = (rand() % 160) + 1;
	}
	else if (getItemDef(foreground).rarity >= 25)
	{
		chance = (rand() % 170) + 1;
	}
	else if (getItemDef(foreground).rarity >= 40)
	{
		chance = (rand() % 180) + 1;
	}
	else if (getItemDef(foreground).rarity >= 60)
	{
		chance = (rand() % 190) + 1;
	}
	else if (getItemDef(foreground).rarity >= 80)
	{
		chance = (rand() % 200) + 1;
	}
	else if (getItemDef(foreground).rarity >= 100)
	{
		chance = (rand() % 600) + 1;
	}
	else
	{
		chance = (rand() % 900) + 1;
	}
	if (chance < 20)
	{
		DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), foreground + 1, 1, 0);
	}
}

inline void SendTradeEffect(ENetPeer* peer, const int id, const int netIDsrc, const int netIDdst, const int timeMs)
{
	PlayerMoving data;
	data.packetType = 0x13;
	data.punchX = id;
	data.punchY = id;
	const auto raw = packPlayerMoving(&data);
	auto netIdSrc = netIDsrc;
	auto netIdDst = netIDdst;
	auto three = 3;
	auto n1 = timeMs;
	memcpy(raw + 3, &three, 1);
	memcpy(raw + 4, &netIdDst, 4);
	memcpy(raw + 8, &netIdSrc, 4);
	memcpy(raw + 20, &n1, 4);
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			const auto raw2 = new BYTE[56];
			memcpy(raw2, raw, 56);
			SendPacketRaw(4, raw2, 56, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
	delete raw;
}

inline void DropGem(ENetPeer* peer, const int x, const int y)
{
	const auto world = getPlyersWorld(peer);
	auto b = getGemCount(world->items[x + (y * world->width)].foreground) + rand() % 1;
	if (b == 0 && static_cast<PlayerInfo*>(peer->data)->GemBuffDrop) b += 1;
	while (b > 0)
	{
		if (b >= 100)
		{
			DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 100, 0);
			b -= 100;
			for (auto i = 0; i < rand() % 1; i++) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 10, 0);
			for (auto i = 0; i < rand() % 4; i++) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
			continue;
		}
		if (b >= 50)
		{
			DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 50, 0);
			b -= 50;
			for (auto i = 0; i < rand() % 1; i++) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 5, 0);
			for (auto i = 0; i < rand() % 3; i++) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
			continue;
		}
		if (b >= 10)
		{
			DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 10, 0);
			b -= 10;
			for (auto i = 0; i < rand() % 4; i++) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
			continue;
		}
		if (b >= 7)
		{
			DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 10, 0);
			b -= 5;
			for (auto i = 0; i < rand() % 2; i++) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
			continue;
		}
		if (b >= 5)
		{
			DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 5, 0);
			b -= 5;
			for (auto i = 0; i < rand() % 2; i++) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
			continue;
		}
		if (b >= 1)
		{
			DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
			b -= 1;
			for (auto i = 0; i < rand() % 1; i++) DropItem(peer, -1, x * 32 + (rand() % 8), y * 32 + (rand() % 16), 112, 1, 0);
			continue;
		}
	}
}

inline void SendXP(ENetPeer* peer, int amount)
{

	if (GrowganothEvent)
	{
		if ((rand() % 3000) <= 5)
		{

			Player::OnConsoleMessage(peer, "`4Growganoth `olikes your work and rewards with `2Gift Of Growganoth`o!");
			Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4Growganoth `wlikes your work and rewards with `2Gift Of Growganoth`w!", 0, false);
			DropItem(peer, -1, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 10386, 1, 0);

		}
	}

	if (static_cast<PlayerInfo*>(peer->data)->level >= 125) return;
	if (static_cast<PlayerInfo*>(peer->data)->cloth_necklace == 9428)
	{
		amount *= 2;
	}
	else if (static_cast<PlayerInfo*>(peer->data)->cloth_back == 9466)
	{
		amount *= 3;
	}
	if (isYellowAnces(peer) || FarmingEvent)
	{
		if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5078 || FarmingEvent)
		{
			const auto chance = (rand() % 100) + 1;
			if (chance <= 5)
			{
				amount *= 2;
				Player::OnParticleEffect(peer, 49, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
			}
		}
		else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5126) /*lvl2*/
		{
			const auto chance = (rand() % 100) + 1;
			if (chance <= 10)
			{
				amount *= 2;
				Player::OnParticleEffect(peer, 49, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
			}
		}
		else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5128) /*lvl3*/
		{
			const auto chance = (rand() % 100) + 1;
			if (chance <= 15)
			{
				amount *= 2;
				Player::OnParticleEffect(peer, 49, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
			}
		}
		else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5130) /*lvl4*/
		{
			const auto chance = (rand() % 100) + 1;
			if (chance <= 20)
			{
				amount *= 2;
				Player::OnParticleEffect(peer, 49, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
			}
		}
		else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5132) /*lvl5*/
		{
			const auto chance = (rand() % 100) + 1;
			if (chance <= 25)
			{
				amount *= 2;
				Player::OnParticleEffect(peer, 49, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
			}
		}
		else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5134) /*lvl6*/
		{
			const auto chance = (rand() % 100) + 1;
			if (chance <= 30)
			{
				amount *= 2;
				Player::OnParticleEffect(peer, 49, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
			}
		}
	}
	static_cast<PlayerInfo*>(peer->data)->xp = static_cast<PlayerInfo*>(peer->data)->xp + amount;
	givequestkatanastep2xp(peer, amount);
}

inline void SendTileData(ENetPeer* peer, const int x, const int y, const int punchX, const int punchY)
{
	/*The Basic Everything*/
	if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9454 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9456 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9458) return;
	const auto world = getPlyersWorld(peer);
	DropGem(peer, x, y);
	if (static_cast<PlayerInfo*>(peer->data)->LuckyClover) /*luckyclover*/
	{
		const auto chance = (rand() % 100) + 1;
		if (chance <= 20)
		{
			static_cast<PlayerInfo*>(peer->data)->GemBuffDrop = true;
			Player::OnParticleEffect(peer, 49, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
			DropGem(peer, x, y);
		}
	}
	if (isRedAnces(peer) || FarmingEvent)
	{
		if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5084 || FarmingEvent)
		{
			const auto chance = (rand() % 100) + 1;
			if (chance <= 5)
			{
				static_cast<PlayerInfo*>(peer->data)->GemBuffDrop = true;
				Player::OnParticleEffect(peer, 29, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
				DropGem(peer, x, y);
			}
		}
		else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5180) /*lvl2*/
		{
			const auto chance = (rand() % 100) + 1;
			if (chance <= 10)
			{
				static_cast<PlayerInfo*>(peer->data)->GemBuffDrop = true;
				Player::OnParticleEffect(peer, 29, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
				DropGem(peer, x, y);
			}
		}
		else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5182) /*lvl3*/
		{
			const auto chance = (rand() % 100) + 1;
			if (chance <= 15)
			{
				static_cast<PlayerInfo*>(peer->data)->GemBuffDrop = true;
				Player::OnParticleEffect(peer, 29, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
				DropGem(peer, x, y);
			}
		}
		else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5184) /*lvl4*/
		{
			const auto chance = (rand() % 100) + 1;
			if (chance <= 20)
			{
				static_cast<PlayerInfo*>(peer->data)->GemBuffDrop = true;
				Player::OnParticleEffect(peer, 29, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
				DropGem(peer, x, y);
			}
		}
		else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5186) /*lvl5*/
		{
			const auto chance = (rand() % 100) + 1;
			if (chance <= 25)
			{
				static_cast<PlayerInfo*>(peer->data)->GemBuffDrop = true;
				Player::OnParticleEffect(peer, 29, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
				DropGem(peer, x, y);
			}
		}
		else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5188) /*lvl6*/
		{
			const auto chance = (rand() % 100) + 1;
			if (chance <= 30)
			{
				static_cast<PlayerInfo*>(peer->data)->GemBuffDrop = true;
				Player::OnParticleEffect(peer, 29, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
				DropGem(peer, x, y);
			}
		}
	}
	else if (isBlueAnces(peer) || FarmingEvent)
	{
		if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5080 || FarmingEvent) /*lvl1*/
		{
			const auto chance = (rand() % 100) + 1;
			if (chance <= 3)
			{
				Player::OnParticleEffect(peer, 374, punchX * 32 + 20, punchY * 32 + 30, 0);
				DropBlock(peer, x, y, world->items[x + (y * world->width)].foreground);
			}
		}
		else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5144) /*lvl2*/
		{
			const auto chance = (rand() % 100) + 1;
			if (chance <= 6)
			{
				Player::OnParticleEffect(peer, 374, punchX * 32 + 20, punchY * 32 + 30, 0);
				DropBlock(peer, x, y, world->items[x + (y * world->width)].foreground);
			}
		}
		else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5146) /*lvl3*/
		{
			const auto chance = (rand() % 100) + 1;
			if (chance <= 9)
			{
				Player::OnParticleEffect(peer, 374, punchX * 32 + 20, punchY * 32 + 30, 0);
				DropBlock(peer, x, y, world->items[x + (y * world->width)].foreground);
			}
		}
		else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5148) /*lvl4*/
		{
			const auto chance = (rand() % 100) + 1;
			if (chance <= 12)
			{
				Player::OnParticleEffect(peer, 374, punchX * 32 + 20, punchY * 32 + 30, 0);
				DropBlock(peer, x, y, world->items[x + (y * world->width)].foreground);
			}
		}
		else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5150) /*lvl5*/
		{
			const auto chance = (rand() % 100) + 1;
			if (chance <= 15)
			{
				Player::OnParticleEffect(peer, 374, punchX * 32 + 20, punchY * 32 + 30, 0);
				DropBlock(peer, x, y, world->items[x + (y * world->width)].foreground);
			}
		}
		else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5152) /*lvl6*/
		{
			const auto chance = (rand() % 100) + 1;
			if (chance <= 18)
			{
				Player::OnParticleEffect(peer, 374, punchX * 32 + 20, punchY * 32 + 30, 0);
				DropBlock(peer, x, y, world->items[x + (y * world->width)].foreground);
			}
		}
	}
	SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
}

inline void SendGuildPoints(ENetPeer* peer, int amount)
{
	if (static_cast<PlayerInfo*>(peer->data)->haveGrowId == false) return;
	if (static_cast<PlayerInfo*>(peer->data)->guild != "")
	{
		try
		{
			auto currentgpoints = 0;
			ifstream guildstream1("guildrewards/guildpoints/" + static_cast<PlayerInfo*>(peer->data)->guild + ".txt");
			guildstream1 >> currentgpoints;
			guildstream1.close();
			if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9508)
			{
				amount *= 2;
				auto newgpoints = currentgpoints + amount;
				ofstream guildstream3("guildrewards/guildpoints/" + static_cast<PlayerInfo*>(peer->data)->guild + ".txt");
				guildstream3 << newgpoints;
				guildstream3.close();
			}
			else
			{
				auto newgpoints = currentgpoints + amount;
				ofstream guildstream3("guildrewards/guildpoints/" + static_cast<PlayerInfo*>(peer->data)->guild + ".txt");
				guildstream3 << newgpoints;
				guildstream3.close();
			}
			// M CONTRIBUTION
			auto currentplayercontribution = 0;
			namespace fs = std::experimental::filesystem;
			if (!fs::is_directory("guildrewards/contribution/" + static_cast<PlayerInfo*>(peer->data)->guild) || !fs::exists("guildrewards / contribution / " + static_cast<PlayerInfo*>(peer->data)->guild))
			{
				fs::create_directory("guildrewards/contribution/" + static_cast<PlayerInfo*>(peer->data)->guild);
				ifstream mcontr("guildrewards/contribution/" + static_cast<PlayerInfo*>(peer->data)->guild + "/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
				mcontr >> currentplayercontribution;
				mcontr.close();
				if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9508)
				{
					amount *= 2;
					auto newcontr = currentplayercontribution + amount;
					ofstream savecon("guildrewards/contribution/" + static_cast<PlayerInfo*>(peer->data)->guild + "/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
					savecon << newcontr;
					savecon.close();
				}
				else
				{
					auto newcontr = currentplayercontribution + amount;
					ofstream savecon("guildrewards/contribution/" + static_cast<PlayerInfo*>(peer->data)->guild + "/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
					savecon << newcontr;
					savecon.close();
				}
			}
			else
			{
				ifstream mcontr("guildrewards/contribution/" + static_cast<PlayerInfo*>(peer->data)->guild + "/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
				mcontr >> currentplayercontribution;
				mcontr.close();
				if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9508)
				{
					amount *= 2;
					auto newcontr = currentplayercontribution + amount;
					ofstream savecon("guildrewards/contribution/" + static_cast<PlayerInfo*>(peer->data)->guild + "/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
					savecon << newcontr;
					savecon.close();
				}
				else
				{
					auto newcontr = currentplayercontribution + amount;
					ofstream savecon("guildrewards/contribution/" + static_cast<PlayerInfo*>(peer->data)->guild + "/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
					savecon << newcontr;
					savecon.close();
				}
			}
		}
		catch (...)
		{
			cout << "SendGuildPoints Function Failed" << endl;
		}
	}
}

inline void SendFarmableDrops(ENetPeer* peer, int chance, int x, int y)
{
	try
	{
		x *= 32;
		y *= 32;
		if (static_cast<PlayerInfo*>(peer->data)->skill == "Farmer") chance += 100;
		auto valgem = rand() % chance;
		if (static_cast<PlayerInfo*>(peer->data)->LuckyClover)
		{
			const auto luckychance = (rand() % 100) + 1;
			if (luckychance <= 20)
			{
				valgem += 100;
				for (auto currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (isHere(peer, currentPeer))
					{
						Player::OnParticleEffect(currentPeer, 49, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
					}
				}
			}
		}

		while (valgem >= 100) {
			valgem -= 100;
			DropItem(peer, -1, x + rand() % 18, y + rand() % 18, 112, 100, 0);
		}

		while (valgem >= 50) {
			valgem -= 50;
			DropItem(peer, -1, x + rand() % 18, y + rand() % 18, 112, 50, 0);
		}

		while (valgem >= 10) {
			valgem -= 10;
			DropItem(peer, -1, x + rand() % 18, y + rand() % 18, 112, 10, 0);
		}
		while (valgem >= 5) {
			valgem -= 5;
			DropItem(peer, -1, x + rand() % 18, y + rand() % 18, 112, 5, 0);
		}

		while (valgem >= 1) {
			valgem -= 1;
			DropItem(peer, -1, x + rand() % 18, y + rand() % 18, 112, 1, 0);
		}

		/*ifstream ifs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
		const string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
		Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`^You found `9" + std::to_string(valgem) + " `2Gems`w!", 0, false);
		const auto gembux = atoi(content.c_str());
		const auto fingembux = gembux + valgem;
		ofstream myfile;
		myfile.open("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
		myfile << fingembux;
		myfile.close();
		const auto gemcalc = gembux + valgem;
		Player::OnSetBux(peer, gemcalc, 0);*/

	}
	catch (...)
	{
		cout << "SendFarmableDrop Function Failed" << endl;
	}
}

inline void SendFarmableDrop(ENetPeer* peer, int chance)
{
	try
	{
		if (static_cast<PlayerInfo*>(peer->data)->skill == "Farmer") chance += 100;
		auto valgem = rand() % chance;
		if (static_cast<PlayerInfo*>(peer->data)->LuckyClover)
		{
			const auto luckychance = (rand() % 100) + 1;
			if (luckychance <= 20)
			{
				valgem += 100;
				for (auto currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (isHere(peer, currentPeer))
					{
						Player::OnParticleEffect(currentPeer, 49, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
					}
				}
			}
		}
		ifstream ifs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
		const string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
		Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`^You found `9" + std::to_string(valgem) + " `2Gems`w!", 0, false);
		const auto gembux = atoi(content.c_str());
		const auto fingembux = gembux + valgem;
		ofstream myfile;
		myfile.open("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
		myfile << fingembux;
		myfile.close();
		const auto gemcalc = gembux + valgem;
		Player::OnSetBux(peer, gemcalc, 0);
	}
	catch (...)
	{
		cout << "SendFarmableDrop Function Failed" << endl;
	}
}
inline void SendFarmableDropCustom(ENetPeer* peer, int chance_start, int chance_end)
{
	try
	{
		if (static_cast<PlayerInfo*>(peer->data)->skill == "Farmer") chance_end += 10;
		auto valgem = rand() % chance_end + chance_start;
		if (static_cast<PlayerInfo*>(peer->data)->LuckyClover)
		{
			const auto luckychance = (rand() % 100) + 1;
			if (luckychance <= 20)
			{
				valgem += 10;
				for (auto currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (isHere(peer, currentPeer))
					{
						Player::OnParticleEffect(currentPeer, 49, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
					}
				}
			}
		}
		ifstream ifs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
		const string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
		Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`^You found `9" + std::to_string(valgem) + " `2Gems`w!", 0, false);
		const auto gembux = atoi(content.c_str());
		const auto fingembux = gembux + valgem;
		ofstream myfile;
		myfile.open("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
		myfile << fingembux;
		myfile.close();
		const auto gemcalc = gembux + valgem;
		Player::OnSetBux(peer, gemcalc, 0);
	}
	catch (...)
	{
		cout << "SendFarmableDrop Function Failed" << endl;
	}
}
inline void SendPlacingEffect(ENetPeer* peer, const int punchX, const int punchY, const int effect)
{
	const float hi = punchX * 32;
	const float hi2 = punchY * 32;
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			Player::OnParticleEffect(currentPeer, effect, hi, hi2, 0);
		}
	}
}

inline void SendHarvestFestivalDrop(ENetPeer* peer, const int x, const int y, const int rarity)
{
	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	auto TargetChance = 0;
	if (rarity <= 15) TargetChance = 6;
	else if (rarity <= 25) TargetChance = 10;
	else if (rarity <= 35) TargetChance = 12;
	else if (rarity <= 45) TargetChance = 14;
	else if (rarity <= 55) TargetChance = 18;
	else if (rarity <= 65) TargetChance = 20;
	else if (rarity <= 75) TargetChance = 23;
	else if (rarity <= 85) TargetChance = 25;
	else if (rarity <= 95) TargetChance = 28;
	else if (rarity <= 115) TargetChance = 30;
	else TargetChance = 30;
	const auto chance = (rand() % 100) + 1;
	if (chance <= TargetChance)
	{
		vector<int> CakeBase{ 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 3870, 7058, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 7058, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1828, 3870, 3870, 7058, 1058, 1094, 1096, 1098, 1058, 1828, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 10030, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1094, 1096, 1098, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1094, 1096, 1098, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1094, 1096, 1098, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098 };
		srand(GetTickCount());
		const int Index = rand() % CakeBase.size();
		const auto ItemID = CakeBase[Index];
		DropItem(peer, -1, x * 32, y * 32, ItemID, 1, 0);
		for (auto currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				Player::OnParticleEffect(currentPeer, 50, x * 32, y * 32, 0);
			}
		}
	}
}

inline void SendCombiner(ENetPeer* peer, const int x, const int y, const int ItemID1, const int ItemID2, const int ItemID3, const int ItemID1Count, const int ItemID2Count, const int ItemID3Count, const int ResultItemID, const bool HarvestFestivalOnly, const int ResultItemCount = 1)
{
	//if (HarvestFestivalOnly && !HarvestEvent) return;
	auto TwoIngredients = false;
	if (ItemID3 == 0) TwoIngredients = true;
	auto world = getPlyersWorld(peer);
	/*auto TotalUid = 0;
	const int itemcount = world->droppedItems.size();
	for (auto i = 0; i < itemcount; i++)
	{
		TotalUid = world->droppedItems[i].uid;
	}
	TotalUid += 1;
	if (world->droppedCount != TotalUid)
	{
		Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "There are too much items floating in this world!", 0, true);
		return;
	}*/
	for (auto i = 0; i < world->droppedItems.size(); i++)
	{
		if (round(world->droppedItems.at(i).x / 32) == x && round(world->droppedItems.at(i).y / 32) == y || round(world->droppedItems.at(i).x / 32) + 1 == x && round(world->droppedItems.at(i).y / 32) == y)
		{
			if (world->droppedItems.at(i).id == ItemID1 && world->droppedItems.at(i).count == ItemID1Count)
			{
				for (auto pos1 = 0; pos1 < world->droppedItems.size(); pos1++)
				{
					if (world->droppedItems.at(pos1).id == ItemID2 && world->droppedItems.at(pos1).count == ItemID2Count)
					{
						for (auto pos = 0; pos < world->droppedItems.size(); pos++)
						{
							if (TwoIngredients)
							{
								vector<int> ItemBase;
								vector<int> ItemBase2;
								RemoveDroppedItem(peer, world->droppedItems.at(i).uid, world);
								RemoveDroppedItem(peer, world->droppedItems.at(pos1).uid, world);
								ItemBase2.push_back(world->droppedItems.at(i).uid);
								ItemBase.push_back(world->droppedItems.at(pos1).uid);
								for (auto ClearItem = 0;
									ClearItem < ItemBase.size(); ClearItem++) processTakeServer(peer, ItemBase.at(ClearItem));
								for (auto ClearItem2 = 0; ClearItem2 < ItemBase2.size(); ClearItem2++) processTakeServer(peer, ItemBase2.at(ClearItem2));
								DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), ResultItemID, ResultItemCount, 0);
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Science!", 0, true);
								break;
							}
							else
							{
								if (world->droppedItems.at(pos).id == ItemID3 && world->droppedItems.at(pos).count == ItemID3Count)
								{
									vector<int> ItemBase;
									vector<int> ItemBase2;
									vector<int> ItemBase3;
									RemoveDroppedItem(peer, world->droppedItems.at(i).uid, world);
									RemoveDroppedItem(peer, world->droppedItems.at(pos1).uid, world);
									RemoveDroppedItem(peer, world->droppedItems.at(pos).uid, world);
									ItemBase2.push_back(world->droppedItems.at(i).uid);
									ItemBase.push_back(world->droppedItems.at(pos1).uid);
									ItemBase3.push_back(world->droppedItems.at(pos).uid);
									for (auto ClearItem = 0; ClearItem < ItemBase.size(); ClearItem++) processTakeServer(peer, ItemBase.at(ClearItem));
									for (auto ClearItem2 = 0; ClearItem2 < ItemBase2.size(); ClearItem2++) processTakeServer(peer, ItemBase2.at(ClearItem2));
									for (auto ClearItem3 = 0; ClearItem3 < ItemBase3.size(); ClearItem3++) processTakeServer(peer, ItemBase3.at(ClearItem3));
									DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), ResultItemID, ResultItemCount, 0);
									Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "SCIENCE!", 0, true);
									break;
								}
							}
						}
						break;
					}
				}
				break;
			}
		}
	}
}

inline void SendFishing(ENetPeer* peer, const int netID, const int x, const int y)
{
	PlayerMoving p;
	p.packetType = 0x1F;
	p.netID = netID;
	p.punchX = x;
	p.punchY = y;
	SendPacketRaw(4, packPlayerMoving(&p), 56, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
}

inline void SendGhost(ENetPeer* peer)
{
	if (static_cast<PlayerInfo*>(peer->data)->canWalkInBlocks == false)
	{
		if (static_cast<PlayerInfo*>(peer->data)->skinColor == 0x8295C3FF || static_cast<PlayerInfo*>(peer->data)->skinColor == 2190853119 || static_cast<PlayerInfo*>(peer->data)->skinColor == 2527912447 || static_cast<PlayerInfo*>(peer->data)->skinColor == 2864971775 || static_cast<PlayerInfo*>(peer->data)->skinColor == 3033464831 || static_cast<PlayerInfo*>(peer->data)->skinColor == 3370516479)
		{
			static_cast<PlayerInfo*>(peer->data)->skinColor = -2450;
			sendClothes(peer);
		}
		static_cast<PlayerInfo*>(peer->data)->canWalkInBlocks = true;
		send_state(peer);
		sendClothes(peer);
		Player::OnConsoleMessage(peer, "`oYour atoms are suddenly aware of quantum tunneling. (`$Ghost in the Shell `omod added)``");
		Player::PlayAudio(peer, "audio/dialog_confirm.wav", 0);
		ifstream fg("players/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".json");
		json j;
		fg >> j;
		fg.close();

		j["ghost"] = true;

		ofstream fs("players/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".json");
		fs << j;
		fs.close();
	}
	else
	{
		if (static_cast<PlayerInfo*>(peer->data)->skinColor == -2450)
		{
			static_cast<PlayerInfo*>(peer->data)->skinColor = 0x8295C3FF;
			sendClothes(peer);
		}
		static_cast<PlayerInfo*>(peer->data)->canWalkInBlocks = false;
		send_state(peer);
		Player::OnConsoleMessage(peer, "`oYour body stops shimmering and returns to normal. (`$Ghost in the Shell `omod removed)``");
		Player::PlayAudio(peer, "audio/dialog_confirm.wav", 0);
		stringstream basic_stringstream;
		ifstream fg("players/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".json");
		json j;
		fg >> j;
		fg.close();

		j["ghost"] = false;

		ofstream fs("players/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".json");
		fs << j;
		fs.close();
	}
}

inline void SendVendDialog(ENetPeer* peer, WorldInfo* world) {
	auto x = static_cast<PlayerInfo*>(peer->data)->lastPunchX;
	auto y = static_cast<PlayerInfo*>(peer->data)->lastPunchY;
	auto squaresign = x + (y * world->width);
	string type = "";
	if (world->items[x + (y * world->width)].rm) {
		type = "\nadd_checkbox|chk_peritem|World Locks per Item|1\nadd_checkbox|chk_perlock|Items per World Lock|0";
	}
	if (world->items[x + (y * world->width)].opened) {
		type = "\nadd_checkbox|chk_peritem|World Locks per Item|0\nadd_checkbox|chk_perlock|Items per World Lock|1";
	}
	if (world->items[x + (y * world->width)].rm && world->items[x + (y * world->width)].opened) {
		type = "\nadd_checkbox|chk_peritem|World Locks per Item|1\nadd_checkbox|chk_perlock|Items per World Lock|1";
	}
	auto currentworld = static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(squaresign);
	string withdrawdialog = "";
	if (world->items[x + (y * world->width)].vdraw > 0) withdrawdialog = "\nadd_smalltext|`oYou have earned " + to_string(world->items[x + (y * world->width)].vdraw) + " World Locks.``|left|\nadd_button|withdraw|Withdraw World Locks|";
	if (world->items[x + (y * world->width)].vid == 0 || world->items[x + (y * world->width)].vcount == 0) {
		Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wVending Machine``|left|2978|\nadd_spacer|small|\nadd_textbox|This machine is empty.|left|\nadd_item_picker|stockitem|`wPut an item in``|Choose an item to put in the machine!|" + withdrawdialog + "|\nend_dialog|vending|Close||");
	}
	else if (world->items[x + (y * world->width)].vcount != 0) {
		string addthemdialog = "";
		auto mtitems = 0;
		for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++) {
			if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == world->items[x + (y * world->width)].vid) {
				mtitems = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
				break;
			}
		}
		if (mtitems != 0) {
			addthemdialog = "\nadd_smalltext|`oYou have " + to_string(mtitems) + " " + getItemDef(world->items[x + (y * world->width)].vid).name + " in your backpack.``|left|\nadd_button|addvend|Add them to the machine|";
		}
		string saledialog = "\nadd_textbox|Not currently for sale!|left|";
		if (world->items[x + (y * world->width)].vprice != 0) {
			if (world->items[x + (y * world->width)].opened) saledialog = "\nadd_textbox|For a cost of:|left|\nadd_label_with_icon|small|1 x `8World Lock``|left|242|\nadd_spacer|small|\nadd_textbox|You will get:|left|\nadd_label_with_icon|small|" + to_string(world->items[x + (y * world->width)].vprice) + " x `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|";
			else saledialog = "\nadd_textbox|For a cost of:|left|\nadd_label_with_icon|small|" + to_string(world->items[x + (y * world->width)].vprice) + " x `8World Lock``|left|242|\nadd_spacer|small|\nadd_textbox|You will get:|left|\nadd_label_with_icon|small|1 x `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|";
		}
		Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wVending Machine``|left|2978|\nadd_spacer|small|\nadd_label_with_icon|sml|The machine contains a total of " + to_string(world->items[x + (y * world->width)].vcount) + " `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``.|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|" + saledialog + "|" + addthemdialog + "|\nadd_button|pullstock|Empty the machine|noflags|0|0|\nadd_smalltext|`5(Vending Machine will not function when price is set to 0)``|left|\nadd_text_input|setprice|Price|" + to_string(world->items[x + (y * world->width)].vprice) + "|5|" + type + "|" + withdrawdialog + "|\nend_dialog|vending|Close|Update|");
	}
	else if (world->items[x + (y * world->width)].vcount != 0 && world->items[x + (y * world->width)].vprice != 0) {
		if (world->items[x + (y * world->width)].opened) Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wVending Machine``|left|2978|\nadd_spacer|small|\nadd_label_with_icon|sml|The machine contains a total of " + to_string(world->items[x + (y * world->width)].vcount) + " `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``.|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|\nadd_textbox|For a cost of:|left|\nadd_label_with_icon|small|1 x `8World Lock``|left|242|\nadd_spacer|small|\nadd_textbox|You will get:|left|\nadd_label_with_icon|small|" + to_string(world->items[x + (y * world->width)].vprice) + " x `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|\nadd_button|pullstock|Empty the machine|noflags|0|0|\nadd_smalltext|`5(Vending Machine will not function when price is set to 0)``|left|\nadd_text_input|setprice|Price|" + to_string(world->items[x + (y * world->width)].vprice) + "|5|" + type + "|" + withdrawdialog + "|\nend_dialog|vending|Close|Update|");
		else Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wVending Machine``|left|2978|\nadd_spacer|small|\nadd_label_with_icon|sml|The machine contains a total of " + to_string(world->items[x + (y * world->width)].vcount) + " `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``.|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|\nadd_textbox|For a cost of:|left|\nadd_label_with_icon|small|" + to_string(world->items[x + (y * world->width)].vprice) + " x `8World Lock``|left|242|\nadd_spacer|small|\nadd_textbox|You will get:|left|\nadd_label_with_icon|small|1 x `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|\nadd_button|pullstock|Empty the machine|noflags|0|0|\nadd_smalltext|`5(Vending Machine will not function when price is set to 0)``|left|\nadd_text_input|setprice|Price|" + to_string(world->items[x + (y * world->width)].vprice) + "|5|" + type + "|" + withdrawdialog + "|\nend_dialog|vending|Close|Update|");
	}
}

inline void SendBuyerVendDialog(ENetPeer* peer, WorldInfo* world) {
	int x = static_cast<PlayerInfo*>(peer->data)->lastPunchX;
	int y = static_cast<PlayerInfo*>(peer->data)->lastPunchY;
	auto squaresign = x + (y * world->width);
	auto currentworld = static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(squaresign);
	if (world->items[x + (y * world->width)].vid == 0 || world->items[x + (y * world->width)].vcount == 0 || world->items[x + (y * world->width)].vprice == 0 || world->items[x + (y * world->width)].vcount < world->items[x + (y * world->width)].vprice && world->items[x + (y * world->width)].opened) {
		Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wVending Machine``|left|2978|\nadd_spacer|small|\nadd_textbox|This machine is out of order.|left|\nend_dialog|vending|Close||");
	}
	else if (world->items[x + (y * world->width)].vcount != 0 && world->items[x + (y * world->width)].vprice == 0) {
		if (world->items[x + (y * world->width)].opened) Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wVending Machine``|left|2978|\nadd_spacer|small|\nadd_label_with_icon|sml|The machine contains a total of " + to_string(world->items[x + (y * world->width)].vcount) + " `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``.|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|\nadd_textbox|For a cost of:|left|\nadd_label_with_icon|small|1 x `8World Lock``|left|242|\nadd_spacer|small|\nadd_textbox|You will get:|left|\nadd_label_with_icon|small|" + to_string(world->items[x + (y * world->width)].vprice) + " x `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|\nadd_textbox|You'll need to wait for the owner to stock up to at least 1 World Lock's worth before you can buy.|left|\nend_dialog|vending|Close||");
		else Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wVending Machine``|left|2978|\nadd_spacer|small|\nadd_label_with_icon|sml|The machine contains a total of " + to_string(world->items[x + (y * world->width)].vcount) + " `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``.|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|\nadd_textbox|For a cost of:|left|\nadd_label_with_icon|small|" + to_string(world->items[x + (y * world->width)].vprice) + " x `8World Lock``|left|242|\nadd_spacer|small|\nadd_textbox|You will get:|left|\nadd_label_with_icon|small|1 x `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|\nadd_textbox|You'll need to wait for the owner to stock up to at least 1 World Lock's worth before you can buy.|left|\nend_dialog|vending|Close||");
	}
	else if (world->items[x + (y * world->width)].vcount != 0) {
		auto worldlocks = 0;
		auto diamondlocks = 0;
		auto locks = 0;
		for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++) {
			if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 242) {
				worldlocks = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
			}
			if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 1796) {
				diamondlocks = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
			}
		}
		if (diamondlocks > 0) {
			locks = diamondlocks * 100;
		}
		locks += worldlocks;
		if (world->items[x + (y * world->width)].opened) Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wVending Machine``|left|2978|\nadd_spacer|small|\nadd_label_with_icon|sml|The machine contains a total of " + to_string(world->items[x + (y * world->width)].vcount) + " `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``.|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|\nadd_textbox|For a cost of:|left|\nadd_label_with_icon|small|1 x `8World Lock``|left|242|\nadd_spacer|small|\nadd_textbox|You will get:|left|\nadd_label_with_icon|small|" + to_string(world->items[x + (y * world->width)].vprice) + " x `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|\nadd_textbox|You have " + to_string(locks) + " World Locks.|left|\nadd_text_input|buycount|How many would you like to buy?|0|3|\nend_dialog|vending|Close|Buy|");
		else Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wVending Machine``|left|2978|\nadd_spacer|small|\nadd_label_with_icon|sml|The machine contains a total of " + to_string(world->items[x + (y * world->width)].vcount) + " `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``.|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|\nadd_textbox|For a cost of:|left|\nadd_label_with_icon|small|" + to_string(world->items[x + (y * world->width)].vprice) + " x `8World Lock``|left|242|\nadd_spacer|small|\nadd_textbox|You will get:|left|\nadd_label_with_icon|small|1 x `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|\nadd_textbox|You have " + to_string(locks) + " World Locks.|left|\nadd_text_input|buycount|How many would you like to buy?|0|3|\nend_dialog|vending|Close|Buy|");
	}
}

inline void SendMergeBook(ENetPeer* peer)
{
	//add_inner_image_label_button|set_online_status|`$Set Online Status``|game/tiles_page14.rttex|1.6|28|23|32|
	Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wMerge Book``|left|10034|\nadd_spacer|small|\nadd_inner_image_label_button|sendMergeBook|`oTile Merging``|game/tiles_page14.rttex|1.6|24|13|32|\nadd_button|close321|`oClose|");
}

inline void SendMergeDialog(ENetPeer* peer, int item1, int item2, int item3, string extralabel)
{

	auto vertevisuitemu = 0;

	auto ItemasT3 = 0;

	//10034

	//|\nadd_label_with_icon|sml|You have totally merged 0 Tiles.|left|2|

	string Button = "";

	if (item1 == 0) item1 = 10036;
	if (item2 == 0) item2 = 10036;
	if (item3 == 0) item3 = 6864;
	if (item1 != 10036 && item2 != 10036 && item3 == 6864)
	{
		if (getItemDef(item1).blockType == BlockTypes::FOREGROUND || getItemDef(item1).blockType == BlockTypes::BACKGROUND || getItemDef(item1).blockType == BlockTypes::PAIN_BLOCK || getItemDef(item1).blockType == BlockTypes::GROUND_BLOCK)
		{
			if (getItemDef(item1).rarity <= 10)
			{
				vertevisuitemu += 1;
			}
			else if (getItemDef(item1).rarity <= 20)
			{
				vertevisuitemu += 5;
			}
			else if (getItemDef(item1).rarity <= 40)
			{
				vertevisuitemu += 15;
			}
			else if (getItemDef(item1).rarity <= 60)
			{
				vertevisuitemu += 20;
			}
			else if (getItemDef(item1).rarity <= 80)
			{
				vertevisuitemu += 25;
			}
			else if (getItemDef(item1).rarity <= 100)
			{
				vertevisuitemu += 30;
			}
			else
			{
				vertevisuitemu += 35;
			}
		}
		if (getItemDef(item2).blockType == BlockTypes::FOREGROUND || getItemDef(item2).blockType == BlockTypes::BACKGROUND || getItemDef(item2).blockType == BlockTypes::PAIN_BLOCK || getItemDef(item2).blockType == BlockTypes::GROUND_BLOCK)
		{
			if (getItemDef(item2).rarity <= 10)
			{
				vertevisuitemu += 1;
			}
			else if (getItemDef(item2).rarity <= 20)
			{
				vertevisuitemu += 5;
			}
			else if (getItemDef(item2).rarity <= 40)
			{
				vertevisuitemu += 15;
			}
			else if (getItemDef(item2).rarity <= 60)
			{
				vertevisuitemu += 20;
			}
			else if (getItemDef(item2).rarity <= 80)
			{
				vertevisuitemu += 25;
			}
			else if (getItemDef(item2).rarity <= 100)
			{
				vertevisuitemu += 30;
			}
			else
			{
				vertevisuitemu += 35;
			}
		}
		bool Found = false;
		while (!Found)
		{
			for (int i = 0; i <= maxItems; i++)
			{
				if (getItemDef(i).blockType == BlockTypes::FOREGROUND || getItemDef(i).blockType == BlockTypes::BACKGROUND || getItemDef(i).blockType == BlockTypes::GROUND_BLOCK)
				{
					if (getItemDef(i).rarity == vertevisuitemu && i != 0)
					{
						ItemasT3 = i;
						Found = true;
						break;
					}
					if (i >= maxItems)
					{
						extralabel = "|\nadd_label_with_icon|small|Those tiles cant be merged!|left|1432|";
						break;
					}
				}
			}
		}
	}
	if (vertevisuitemu != 0) item3 = ItemasT3;
	/*Recipes*/
	string item1name = "Select Item";
	string item2name = "Select Item";
	string item3name = "Result";
	if (item1 != 10036) item1name = getItemDef(item1).name;
	if (item2 != 10036) item2name = getItemDef(item2).name;
	if (item3 != 6864) Button = "|\nadd_spacer|small|\nadd_spacer|small||\nadd_button|completemerge|`oComplete|";
	//static_cast<PlayerInfo*>(peer->data)->MergeItem1 = item1;
	static_cast<PlayerInfo*>(peer->data)->MergeItem3 = to_string(item3);
	//static_cast<PlayerInfo*>(peer->data)->MergeItem2 = item2;
	Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wTile Merging``|left|10034|" + extralabel + "\nadd_spacer|small|\nadd_button_with_icon|putMergeItem_1|" + item1name + "|frame|" + to_string(item1) + "||\nadd_button_with_icon|putMergeItem_2|" + item2name + "|frame|" + to_string(item2) + "||\nadd_button_with_icon|putMergeItem_3|" + item3name + "|frame|" + to_string(item3) + "|\nadd_button_with_icon||END_LIST|noflags|0|0|\nadd_spacer|small|\nend_dialog|merge|Close||" + Button + "");
}

inline void SendMergeEnd(ENetPeer* peer, string extralabel)
{
	Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wTile Merging``|left|10034|" + extralabel + "\nadd_spacer|small|\nadd_button|close321|`oClose|");
}

inline void SendWeather(ENetPeer* peer, int tile, WorldInfo* world, int x, int y)
{
	if (tile == 18)
	{
		if (world->items[x + (y * world->width)].foreground == 1490)
		{
			if (world->weather == 10)
			{
				world->weather = 0;
			}
			else
			{
				world->weather = 10;
			}
			ENetPeer* currentPeer;
			for (currentPeer = server->peers;
				currentPeer < &server->peers[server->peerCount];
				++currentPeer)
			{
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
					continue;
				if (isHere(peer, currentPeer))
				{
					GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
					ENetPacket* packet2 = enet_packet_create(p2.data,
						p2.len,
						ENET_PACKET_FLAG_RELIABLE);
					enet_peer_send(currentPeer, 0, packet2);
					delete p2.data;
					continue;
				}
			}
		}
	}
	if (tile == 18)
	{
		if (world->items[x + (y * world->width)].foreground == 934)
		{
			if (world->weather == 2)
			{
				world->weather = 0;
			}
			else
			{
				world->weather = 2;
			}
			ENetPeer* currentPeer;
			for (currentPeer = server->peers;
				currentPeer < &server->peers[server->peerCount];
				++currentPeer)
			{
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
					continue;
				if (isHere(peer, currentPeer))
				{
					GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
					ENetPacket* packet2 = enet_packet_create(p2.data,
						p2.len,
						ENET_PACKET_FLAG_RELIABLE);
					enet_peer_send(currentPeer, 0, packet2);
					delete p2.data;
					continue;
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 946)
			{
				if (world->weather == 3)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 3;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 1490)
			{
				if (world->weather == 10)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 10;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 932)
			{
				if (world->weather == 4)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 4;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 984)
			{
				if (world->weather == 5)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 5;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 1210)
			{
				if (world->weather == 8)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 8;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 1364)
			{
				if (world->weather == 11)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 11;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 1750)
			{
				if (world->weather == 15)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 15;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 2046)
			{
				if (world->weather == 17)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 17;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 2284)
			{
				if (world->weather == 18)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 18;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 2744)
			{
				if (world->weather == 19)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 19;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 3252)
			{
				if (world->weather == 20)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 20;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 3446)
			{
				if (world->weather == 21)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 21;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 3534)
			{
				if (world->weather == 22)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 22;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 3694)
			{
				if (world->weather == 25)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 25;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 32)
		{
			if (world->items[x + (y * world->width)].foreground == 3832)
			{ // stuff weather dialog
				if (x != 0)
				{
					static_cast<PlayerInfo*>(peer->data)->lastPunchX = x;
				}
				if (y != 0)
				{
					static_cast<PlayerInfo*>(peer->data)->lastPunchY = y;
				}
				GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`wStuff Weather Machine``|left|3832|\nadd_item_picker|stuffitem|Edit Item|Choose any item you want to pick|\nadd_spacer|small|\nadd_text_input|gravity|Gravity Value||4|\nadd_spacer|small|\nadd_quick_exit|\nend_dialog|stuff|Nevermind||"));
				ENetPacket* packet = enet_packet_create(p.data,
					p.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet);
				delete p.data;
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 1490)
			{
				if (world->weather == 10)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 10;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 4242)
			{
				if (world->weather == 30)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 30;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 4486)
			{
				if (world->weather == 31)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 31;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 4776)
			{
				if (world->weather == 32)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 32;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 4892)
			{
				if (world->weather == 33)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 33;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 5000)
			{
				if (world->weather == 34)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 34;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 5112)
			{
				if (world->weather == 35)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 35;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 5654)
			{
				if (world->weather == 36)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 36;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 5716)
			{
				if (world->weather == 37)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 37;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 5958)
			{
				if (world->weather == 38)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 38;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 6854)
			{
				if (world->weather == 42)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 42;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 7644)
			{
				if (world->weather == 44)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 44;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
}

inline void scan_inventory(ENetPeer* peer, const int item_id)
{
	if (!isMod(peer))
	{
		Player::OnConsoleMessage(peer, "`4You cannot perform this action!");
		return;
	}
	using namespace std::chrono;
	int start = (duration_cast<seconds>(system_clock::now().time_since_epoch())).count();
	string path = "inventory/";
	int fun = 0;
	string who = "";
	for (const auto& entry : fs::directory_iterator(path))
	{
		fun++;
		try
		{
			ifstream stream(entry.path());
			if (stream.fail())
			{
				cout << "error scan inv" << endl;
				stream.close();
				continue;
			}
			json my_json;
			stream >> my_json;
			for (auto i = 0; i < 200; i++)
			{
				try
				{
					if (my_json["items"][i]["itemid"] == item_id)
					{
						ostringstream oss;
						oss << entry;
						auto name = oss.str();
						ostringstream osa;
						osa << my_json["items"][i]["quantity"];
						auto quantity = osa.str();
						size_t pos;
						while ((pos = name.find("inventory\\")) != std::string::npos)
						{
							name.replace(pos, 10, "");
						}
						while ((pos = name.find(".json")) != std::string::npos)
						{
							name.replace(pos, 5, "");
						}

						who += name + " " + quantity + " " + getItemDef(item_id).name + "`w\n";
					}
				}
				catch (std::exception&)
				{
					continue; /*tipo jeigu nera*/
				}
			}
		}
		catch (std::exception&)
		{
			continue; /*tipo jeigu nera*/
		}
	}

	int finish = (duration_cast<seconds>(system_clock::now().time_since_epoch())).count();
	auto time = to_string(start - finish);
	size_t pos;
	while ((pos = time.find("-")) != std::string::npos)
	{
		time.replace(pos, 1, "");
	}
	Player::OnConsoleMessage(peer, "-----------Search Results-----------\n" + who + "------------------------------------");
	Player::OnConsoleMessage(peer, "`9Scan completed, took `4" + time + " `9Seconds (scanned `4" + to_string(fun) + " `9inventories)");
}

inline void scan_box(ENetPeer* peer, const int item_id)
{
	if (!isMod(peer))
	{
		Player::OnConsoleMessage(peer, "`4You cannot perform this action!");
		return;
	}
	using namespace std::chrono;
	int start = (duration_cast<seconds>(system_clock::now().time_since_epoch())).count();
	string path = "worlds/";
	int fun = 0;
	string who = "";
	for (const auto& entry : fs::directory_iterator(path))
	{
		ostringstream oss;
		oss << entry;
		auto names = oss.str();
		size_t pos;
		while ((pos = names.find("worlds\\_")) != std::string::npos)
		{
			names.replace(pos, 8, "");
		}
		while ((pos = names.find(".json")) != std::string::npos)
		{
			names.replace(pos, 5, "");
		}
		if (fs::is_directory("storageboxlvl1/" + names + "/"))
		{
			string magic = "";
			for (const auto& p : fs::directory_iterator("storageboxlvl1/" + names + "/"))
			{
				fun++;
				ostringstream basic_ostringstream;
				basic_ostringstream << p;
				magic = basic_ostringstream.str();
				if (std::experimental::filesystem::exists(magic))
				{
					ifstream stream(magic);
					if (stream.fail()) stream.close();
					json my_json;
					stream >> my_json;
					for (auto i = 0; i < 20; i++)
					{
						try
						{
							if (my_json["storage"][i]["itemid"] == item_id)
							{
								ostringstream oss;
								oss << entry;
								auto name = oss.str();
								ostringstream osa;
								osa << my_json["storage"][i]["itemcount"];
								auto quantity = osa.str();

								ostringstream osa4444;
								osa4444 << my_json["storage"][i]["placedby"];
								string placedby = osa4444.str();

								if (placedby == "")
								{
									placedby = "NOT DETECTED";
								}

								while ((pos = name.find("worlds\\_")) != std::string::npos)
								{
									name.replace(pos, 8, "");
								}
								while ((pos = name.find(".json")) != std::string::npos)
								{
									name.replace(pos, 5, "");
								}
								while ((pos = quantity.find(".0")) != std::string::npos)
								{
									quantity.replace(pos, 2, "");
								}
								who += name + " " + quantity + " " + getItemDef(item_id).name + "`w placed by(`$" + placedby + "`w)\n";
							}
						}
						catch (std::exception&)
						{
							continue; /*tipo jeigu nera*/
						}
					}
				}
			}
		}
	}

	for (const auto& entry : fs::directory_iterator(path))
	{
		ostringstream oss;
		oss << entry;
		auto names = oss.str();
		size_t pos;
		while ((pos = names.find("worlds\\_")) != std::string::npos)
		{
			names.replace(pos, 8, "");
		}
		while ((pos = names.find(".json")) != std::string::npos)
		{
			names.replace(pos, 5, "");
		}
		if (fs::is_directory("storageboxlvl2/" + names + "/"))
		{
			string magic = "";
			for (const auto& p : fs::directory_iterator("storageboxlvl2/" + names + "/"))
			{
				fun++;
				ostringstream basic_ostringstream;
				basic_ostringstream << p;
				magic = basic_ostringstream.str();
				if (std::experimental::filesystem::exists(magic))
				{
					ifstream stream(magic);
					if (stream.fail()) stream.close();
					json my_json;
					stream >> my_json;
					for (auto i = 0; i < 40; i++)
					{
						try
						{
							if (my_json["storage"][i]["itemid"] == item_id)
							{
								ostringstream oss;
								oss << entry;
								auto name = oss.str();
								ostringstream osa;
								osa << my_json["storage"][i]["itemcount"];
								auto quantity = osa.str();

								ostringstream osa4444;
								osa4444 << my_json["storage"][i]["placedby"];
								string placedby = osa4444.str();

								if (placedby == "")
								{
									placedby = "NOT DETECTED";
								}

								while ((pos = name.find("worlds\\_")) != std::string::npos)
								{
									name.replace(pos, 8, "");
								}
								while ((pos = name.find(".json")) != std::string::npos)
								{
									name.replace(pos, 5, "");
								}
								while ((pos = quantity.find(".0")) != std::string::npos)
								{
									quantity.replace(pos, 2, "");
								}
								who += name + " " + quantity + " " + getItemDef(item_id).name + "`w placed by(`$" + placedby + "`w)\n";
							}
						}
						catch (std::exception&)
						{
							continue; /*tipo jeigu nera*/
						}
					}
				}
			}
		}
	}

	for (const auto& entry : fs::directory_iterator(path))
	{
		ostringstream oss;
		oss << entry;
		auto names = oss.str();
		size_t pos;
		while ((pos = names.find("worlds\\_")) != std::string::npos)
		{
			names.replace(pos, 8, "");
		}
		while ((pos = names.find(".json")) != std::string::npos)
		{
			names.replace(pos, 5, "");
		}
		if (fs::is_directory("storageboxlvl3/" + names + "/"))
		{
			string magic = "";
			for (const auto& p : fs::directory_iterator("storageboxlvl3/" + names + "/"))
			{
				fun++;
				ostringstream basic_ostringstream;
				basic_ostringstream << p;
				magic = basic_ostringstream.str();
				if (std::experimental::filesystem::exists(magic))
				{
					ifstream stream(magic);
					if (stream.fail()) stream.close();
					json my_json;
					stream >> my_json;
					for (auto i = 0; i < 90; i++)
					{
						try
						{
							if (my_json["storage"][i]["itemid"] == item_id)
							{
								ostringstream oss;
								oss << entry;
								auto name = oss.str();
								ostringstream osa;
								osa << my_json["storage"][i]["itemcount"];
								auto quantity = osa.str();

								ostringstream osa4444;
								osa4444 << my_json["storage"][i]["placedby"];
								string placedby = osa4444.str();

								if (placedby == "")
								{
									placedby = "NOT DETECTED";
								}

								while ((pos = name.find("worlds\\_")) != std::string::npos)
								{
									name.replace(pos, 8, "");
								}
								while ((pos = name.find(".json")) != std::string::npos)
								{
									name.replace(pos, 5, "");
								}
								while ((pos = quantity.find(".0")) != std::string::npos)
								{
									quantity.replace(pos, 2, "");
								}
								who += name + " " + quantity + " " + getItemDef(item_id).name + "`w placed by(`$" + placedby + "`w)\n";
							}
						}
						catch (std::exception&)
						{
							continue; /*tipo jeigu nera*/
						}
					}
				}
			}
		}
	}

	int finish = (duration_cast<seconds>(system_clock::now().time_since_epoch())).count();
	auto time = to_string(start - finish);
	size_t pos;
	while ((pos = time.find("-")) != std::string::npos)
	{
		time.replace(pos, 1, "");
	}
	Player::OnConsoleMessage(peer, "-----------Search Results-----------\n" + who + "------------------------------------");
	Player::OnConsoleMessage(peer, "`9Scan completed, took `4" + time + " `9Seconds (scanned `4" + to_string(fun) + " `9storage boxes)");
}

inline void scan_safe(ENetPeer* peer, const int item_id)
{
	if (!isMod(peer))
	{
		Player::OnConsoleMessage(peer, "`4You cannot perform this action!");
		return;
	}
	using namespace std::chrono;
	int start = (duration_cast<seconds>(system_clock::now().time_since_epoch())).count();
	string path = "worlds/";
	int fun = 0;
	string who = "";
	for (const auto& entry : fs::directory_iterator(path))
	{
		ostringstream oss;
		oss << entry;
		auto names = oss.str();
		size_t pos;
		while ((pos = names.find("worlds\\_")) != std::string::npos)
		{
			names.replace(pos, 8, "");
		}
		while ((pos = names.find(".json")) != std::string::npos)
		{
			names.replace(pos, 5, "");
		}
		if (fs::is_directory("safevault/" + names + "/"))
		{
			string magic = "";
			for (const auto& p : fs::directory_iterator("safevault/" + names + "/"))
			{
				fun++;
				ostringstream basic_ostringstream;
				basic_ostringstream << p;
				magic = basic_ostringstream.str();
				if (std::experimental::filesystem::exists(magic))
				{
					ifstream stream(magic);
					if (stream.fail()) stream.close();
					json my_json;
					stream >> my_json;
					for (auto i = 0; i < 20; i++)
					{
						try
						{
							if (my_json["safe"][i]["itemid"] == item_id)
							{
								ostringstream oss;
								oss << entry;
								auto name = oss.str();
								ostringstream osa;
								osa << my_json["safe"][i]["itemcount"];
								auto quantity = osa.str();
								ostringstream osa333;
								osa333 << my_json["password"];
								string pass = osa333.str();
								if (pass == "") pass = "None";

								ostringstream osa4444;
								osa4444 << my_json["safe"][i]["placedby"];
								string placedby = osa4444.str();

								if (placedby == "")
								{
									placedby = "NOT DETECTED";
								}

								if (isPlayer(peer)) pass = "Hidden";
								while ((pos = name.find("worlds\\_")) != std::string::npos)
								{
									name.replace(pos, 8, "");
								}
								while ((pos = name.find(".json")) != std::string::npos)
								{
									name.replace(pos, 5, "");
								}
								while ((pos = quantity.find(".0")) != std::string::npos)
								{
									quantity.replace(pos, 2, "");
								}
								who += name + " " + quantity + " " + getItemDef(item_id).name + " `wpassword(" + pass + "`w) placed by(`$" + placedby + "`w)\n";
							}
						}
						catch (std::exception&)
						{
							continue; /*tipo jeigu nera*/
						}
					}
				}
			}
		}
	}

	int finish = (duration_cast<seconds>(system_clock::now().time_since_epoch())).count();
	auto time = to_string(start - finish);
	size_t pos;
	while ((pos = time.find("-")) != std::string::npos)
	{
		time.replace(pos, 1, "");
	}
	Player::OnConsoleMessage(peer, "-----------Search Results-----------\n" + who + "------------------------------------");
	Player::OnConsoleMessage(peer, "`9Scan completed, took `4" + time + " `9Seconds (scanned `4" + to_string(fun) + " `9safe vaults)");
}

/*
inline void add_json_box(ENetPeer* peer)
{
	if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 0)
	{
		Player::OnConsoleMessage(peer, "`4You cannot perform this action!");
		return;
	}
	using namespace std::chrono;
	int start = (duration_cast<seconds>(system_clock::now().time_since_epoch())).count();
	string path = "worlds/";
	int fun = 0;
	string who = "";
	for (const auto& entry : fs::directory_iterator(path))
	{
		ostringstream oss;
		oss << entry;
		auto names = oss.str();
		size_t pos;
		while ((pos = names.find("worlds\\_")) != std::string::npos)
		{
			names.replace(pos, 8, "");
		}
		while ((pos = names.find(".json")) != std::string::npos)
		{
			names.replace(pos, 5, "");
		}
		if (fs::is_directory("storageboxlvl1/" + names + "/"))
		{
			string magic = "";
			for (const auto& p : fs::directory_iterator("storageboxlvl1/" + names + "/"))
			{
				fun++;
				ostringstream basic_ostringstream;
				basic_ostringstream << p;
				magic = basic_ostringstream.str();
				if (std::experimental::filesystem::exists(magic))
				{
					ifstream stream(magic);
					if (stream.fail()) stream.close();
					json my_json;
					stream >> my_json;
					ostringstream oss;
					oss << entry;
					auto name = oss.str();

					while ((pos = name.find("worlds\\_")) != std::string::npos)
					{
						name.replace(pos, 8, "");
					}
					while ((pos = name.find(".json")) != std::string::npos)
					{
						name.replace(pos, 5, "");
					}
					for (auto i = 0; i < 20; i++)
					{
						try
						{
							my_json["storage"][i]["placedby"] = "";
						}
						catch (std::exception&)
						{
							continue; //tipo jeigu nera
						}
					}
					ofstream ofs(magic);
					cout << magic << " done" << endl;
					ofs << my_json;
					ofs.close();
				}
			}
		}
	}

	for (const auto& entry : fs::directory_iterator(path))
	{
		ostringstream oss;
		oss << entry;
		auto names = oss.str();
		size_t pos;
		while ((pos = names.find("worlds\\_")) != std::string::npos)
		{
			names.replace(pos, 8, "");
		}
		while ((pos = names.find(".json")) != std::string::npos)
		{
			names.replace(pos, 5, "");
		}
		if (fs::is_directory("storageboxlvl2/" + names + "/"))
		{
			string magic = "";
			for (const auto& p : fs::directory_iterator("storageboxlvl2/" + names + "/"))
			{
				fun++;
				ostringstream basic_ostringstream;
				basic_ostringstream << p;
				magic = basic_ostringstream.str();
				if (std::experimental::filesystem::exists(magic))
				{
					ifstream stream(magic);
					if (stream.fail()) stream.close();
					json my_json;
					stream >> my_json;
					ostringstream oss;
					oss << entry;
					auto name = oss.str();

					while ((pos = name.find("worlds\\_")) != std::string::npos)
					{
						name.replace(pos, 8, "");
					}
					while ((pos = name.find(".json")) != std::string::npos)
					{
						name.replace(pos, 5, "");
					}
					for (auto i = 0; i < 40; i++)
					{
						try
						{
							my_json["storage"][i]["placedby"] = "";
						}
						catch (std::exception&)
						{
							continue; //tipo jeigu nera
						}
					}
					ofstream ofs(magic);
					cout << magic << " done" << endl;
					ofs << my_json;
					ofs.close();
				}
			}
		}
	}

	for (const auto& entry : fs::directory_iterator(path))
	{
		ostringstream oss;
		oss << entry;
		auto names = oss.str();
		size_t pos;
		while ((pos = names.find("worlds\\_")) != std::string::npos)
		{
			names.replace(pos, 8, "");
		}
		while ((pos = names.find(".json")) != std::string::npos)
		{
			names.replace(pos, 5, "");
		}
		if (fs::is_directory("storageboxlvl3/" + names + "/"))
		{
			string magic = "";
			for (const auto& p : fs::directory_iterator("storageboxlvl3/" + names + "/"))
			{
				fun++;
				ostringstream basic_ostringstream;
				basic_ostringstream << p;
				magic = basic_ostringstream.str();
				if (std::experimental::filesystem::exists(magic))
				{
					ifstream stream(magic);
					if (stream.fail()) stream.close();
					json my_json;
					stream >> my_json;
					ostringstream oss;
					oss << entry;
					auto name = oss.str();

					while ((pos = name.find("worlds\\_")) != std::string::npos)
					{
						name.replace(pos, 8, "");
					}
					while ((pos = name.find(".json")) != std::string::npos)
					{
						name.replace(pos, 5, "");
					}
					for (auto i = 0; i < 90; i++)
					{
						try
						{
							my_json["storage"][i]["placedby"] = "";
						}
						catch (std::exception&)
						{
							continue; //tipo jeigu nera
						}
					}
					ofstream ofs(magic);
					cout << magic << " done" << endl;
					ofs << my_json;
					ofs.close();
				}
			}
		}
	}

	int finish = (duration_cast<seconds>(system_clock::now().time_since_epoch())).count();
	auto time = to_string(start - finish);
	size_t pos;
	while ((pos = time.find("-")) != std::string::npos)
	{
		time.replace(pos, 1, "");
	}
	Player::OnConsoleMessage(peer, "-----------Search Results-----------\n" + who + "------------------------------------");
	Player::OnConsoleMessage(peer, "`9Scan completed, took `4" + time + " `9Seconds (scanned `4" + to_string(fun) + " `9storage boxes)");
}
*/

/*
inline void add_json_safevaut(ENetPeer* peer)
{
	if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 0)
	{
		Player::OnConsoleMessage(peer, "`4You cannot perform this action!");
		return;
	}
	using namespace std::chrono;
	int start = (duration_cast<seconds>(system_clock::now().time_since_epoch())).count();
	string path = "worlds/";
	int fun = 0;
	string who = "";
	for (const auto& entry : fs::directory_iterator(path))
	{
		ostringstream oss;
		oss << entry;
		auto names = oss.str();
		size_t pos;
		while ((pos = names.find("worlds\\_")) != std::string::npos)
		{
			names.replace(pos, 8, "");
		}
		while ((pos = names.find(".json")) != std::string::npos)
		{
			names.replace(pos, 5, "");
		}
		if (fs::is_directory("safevault/" + names + "/"))
		{
			string magic = "";
			for (const auto& p : fs::directory_iterator("safevault/" + names + "/"))
			{
				fun++;
				ostringstream basic_ostringstream;
				basic_ostringstream << p;
				magic = basic_ostringstream.str();
				if (std::experimental::filesystem::exists(magic))
				{
					ifstream stream(magic);
					if (stream.fail()) stream.close();
					json my_json;
					stream >> my_json;
					ostringstream oss;
					oss << entry;
					auto name = oss.str();

					while ((pos = name.find("worlds\\_")) != std::string::npos)
					{
						name.replace(pos, 8, "");
					}
					while ((pos = name.find(".json")) != std::string::npos)
					{
						name.replace(pos, 5, "");
					}
					for (auto i = 0; i < 20; i++)
					{
						try
						{
							my_json["safe"][i]["placedby"] = "";
						}
						catch (std::exception&)
						{
							continue; //tipo jeigu nera
						}
					}
					ofstream ofs(magic);
					cout << magic << " done" << endl;
					ofs << my_json;
					ofs.close();
				}
			}
		}
	}

	int finish = (duration_cast<seconds>(system_clock::now().time_since_epoch())).count();
	auto time = to_string(start - finish);
	size_t pos;
	while ((pos = time.find("-")) != std::string::npos)
	{
		time.replace(pos, 1, "");
	}
	Player::OnConsoleMessage(peer, "-----------Search Results-----------\n" + who + "------------------------------------");
	Player::OnConsoleMessage(peer, "`9Scan completed, took `4" + time + " `9Seconds (scanned `4" + to_string(fun) + " `9safe vaults)");
}
*/

/*
inline void add_json_world(ENetPeer* peer)
{

	scanrunning = true;

	cout << "scan is running" << endl;

	Player::OnConsoleMessage(peer, "`4You have selected option to add world new property, this kind of scan might take up to 5 minutes");
	using namespace std::chrono;
	int start = (duration_cast<seconds>(system_clock::now().time_since_epoch())).count();
	string path = "worlds/";
	int fun = 0;
	string who = "";
	for (const auto& entry : fs::directory_iterator(path))
	{
		fun++;
		try
		{
			ifstream stream(entry.path());
			if (stream.fail())
			{
				cout << "error scan inv" << endl;
				stream.close();
				continue;
			}
			json my_json;
			stream >> my_json;

			ostringstream oss;
			oss << entry;
			auto name = oss.str();
			size_t pos;
			while ((pos = name.find("worlds\\_")) != std::string::npos)
			{
				name.replace(pos, 8, "");
			}
			while ((pos = name.find(".json")) != std::string::npos)
			{
				name.replace(pos, 5, "");
			}

			for (auto i = 0; i < my_json["dropped"].size(); i++)
			{
				try
				{

					my_json["dropped"][i]["droppedby"] = "";
				}
				catch (std::exception&)
				{
					continue; //tipo jeigu nera
				}
			}
			ofstream ofs("worlds/_" + name + ".json");
			cout << name << " done" << endl;
			ofs << my_json;
			ofs.close();
		}
		catch (std::exception&)
		{
			continue; //tipo jeigu nera
		}
	}

	int finish = (duration_cast<seconds>(system_clock::now().time_since_epoch())).count();
	auto time = to_string(start - finish);
	size_t pos;
	while ((pos = time.find("-")) != std::string::npos)
	{
		time.replace(pos, 1, "");
	}
	Player::OnConsoleMessage(peer, "-----------Search Results-----------\n" + who + "------------------------------------");
	Player::OnConsoleMessage(peer, "`9Scan completed, took `4" + time + " `9Seconds (scanned `4" + to_string(fun) + " `9worlds)");
}
*/

/*inline void add_json_inventory(ENetPeer* peer)
{

	scanrunning = true;

	cout << "scan is running" << endl;

	Player::OnConsoleMessage(peer, "`4You have selected option to add inventory new property, this kind of scan might take up to 5 minutes");
	using namespace std::chrono;
	int start = (duration_cast<seconds>(system_clock::now().time_since_epoch())).count();
	string path = "inventory/";
	int fun = 0;
	string who = "";
	for (const auto& entry : fs::directory_iterator(path))
	{
		fun++;
		try
		{
			ifstream stream(entry.path());
			if (stream.fail())
			{
				cout << "error scan inv" << endl;
				stream.close();
				continue;
			}
			json my_json;
			stream >> my_json;

			ostringstream oss;
			oss << entry;
			auto name = oss.str();
			size_t pos;
			while ((pos = name.find("inventory\\")) != std::string::npos)
			{
				name.replace(pos, 10, "");
			}
			while ((pos = name.find(".json")) != std::string::npos)
			{
				name.replace(pos, 5, "");
			}

			for (auto i = 0; i < 200; i++)
			{
				try
				{

						my_json["items"][i]["madeby"] = "";
				}
				catch (std::exception&)
				{
					continue; //tipo jeigu nera
				}
			}
			ofstream ofs("inventory/" + name + ".json");
			cout << name << " done" << endl;
			ofs << my_json;
			ofs.close();
		}
		catch (std::exception&)
		{
			continue; //tipo jeigu nera
		}
	}

	int finish = (duration_cast<seconds>(system_clock::now().time_since_epoch())).count();
	auto time = to_string(start - finish);
	size_t pos;
	while ((pos = time.find("-")) != std::string::npos)
	{
		time.replace(pos, 1, "");
	}
	Player::OnConsoleMessage(peer, "-----------Search Results-----------\n" + who + "------------------------------------");
	Player::OnConsoleMessage(peer, "`9Scan completed, took `4" + time + " `9Seconds (scanned `4" + to_string(fun) + " `9inventories)");
}
*/
inline void scan_dbox(ENetPeer* peer, const int item_id)
{
	if (isPlayer(peer))
	{
		Player::OnConsoleMessage(peer, "`4You cannot perform this action!");
		return;
	}
	using namespace std::chrono;
	int start = (duration_cast<seconds>(system_clock::now().time_since_epoch())).count();
	string path = "worlds/";
	int fun = 0;
	string who = "";
	for (const auto& entry : fs::directory_iterator(path))
	{
		ostringstream oss;
		oss << entry;
		auto names = oss.str();
		size_t pos;
		while ((pos = names.find("worlds\\_")) != std::string::npos)
		{
			names.replace(pos, 8, "");
		}
		while ((pos = names.find(".json")) != std::string::npos)
		{
			names.replace(pos, 5, "");
		}
		if (fs::is_directory("donationboxes/" + names + "/"))
		{
			string magic = "";
			for (const auto& p : fs::directory_iterator("donationboxes/" + names + "/"))
			{
				fun++;
				ostringstream basic_ostringstream;
				basic_ostringstream << p;
				magic = basic_ostringstream.str();
				if (std::experimental::filesystem::exists(magic))
				{
					ifstream stream(magic);
					if (stream.fail()) stream.close();
					json my_json;
					stream >> my_json;
					for (auto i = 0; i < 20; i++)
					{
						try
						{
							if (my_json["donatedItems"][i]["itemid"] == item_id)
							{
								ostringstream oss;
								oss << entry;
								auto name = oss.str();
								ostringstream osa;
								osa << my_json["donatedItems"][i]["itemcount"];
								auto quantity = osa.str();

								ostringstream osa4444;
								osa4444 << my_json["donatedItems"][i]["sentBy"];
								string placedby = osa4444.str();

								if (placedby == "")
								{
									placedby = "NOT DETECTED";
								}
								while ((pos = name.find("worlds\\_")) != std::string::npos)
								{
									name.replace(pos, 8, "");
								}
								while ((pos = name.find(".json")) != std::string::npos)
								{
									name.replace(pos, 5, "");
								}
								while ((pos = quantity.find(".0")) != std::string::npos)
								{
									quantity.replace(pos, 2, "");
								}
								who += name + " " + quantity + " " + getItemDef(item_id).name + " placed by(`$" + placedby + "`w)\n";
							}
						}
						catch (std::exception&)
						{
							continue; /*tipo jeigu nera*/
						}
					}
				}
			}
		}
	}

	int finish = (duration_cast<seconds>(system_clock::now().time_since_epoch())).count();
	auto time = to_string(start - finish);
	size_t pos;
	while ((pos = time.find("-")) != std::string::npos)
	{
		time.replace(pos, 1, "");
	}
	Player::OnConsoleMessage(peer, "-----------Search Results-----------\n" + who + "------------------------------------");
	Player::OnConsoleMessage(peer, "`9Scan completed, took `4" + time + " `9Seconds (scanned `4" + to_string(fun) + " `9donation boxes)");
}


inline void scan_owner(ENetPeer* peer, const string oname)
{

	Player::OnTextOverlay(peer, "This feature currently unavailable...");
	/*string path = "worlds/";
	int fun = 0;
	string who = "";
	int worlds = 0;
	for (const auto& entry : fs::directory_iterator(path))
	{
		worlds++;
	}
	for (const auto& entry : fs::directory_iterator(path))
	{
		fun++;
		ifstream stream(entry.path());
		if (stream.fail()) stream.close();
		json my_json;
		stream >> my_json;
		ostringstream oss;
		oss << entry;
		auto name = oss.str();
		size_t pos;
		while ((pos = name.find("worlds\\_")) != std::string::npos)
		{
			name.replace(pos, 8, "");
		}
		while ((pos = name.find(".json")) != std::string::npos)
		{
			name.replace(pos, 5, "");
		}
		try
		{
			ostringstream oss123;
			oss123 << my_json["owner"];
			auto own = oss123.str();

			stringstream ss1;
			ss1 << "INSERT INTO worlds(owner, worlds) VALUES ('" + own + "', '')";
			auto query3 = ss1.str();
			auto q2 = query3.c_str();
			if (mysql_query(conn, q2))
			{
						string ers = mysql_error(conn); if (ers.find("Lost connection") != string::npos) ConnectToDatabase();
				cout << mysql_error(conn) << endl;
				return;
			}
				who += name + " ";
				continue;
		}
		catch (std::exception&)
		{
			continue;
		}
		stream.close();
		cout << fun << endl;

	}



	size_t pos;
	while ((pos = who.find("_")) != std::string::npos)
	{
		who.replace(pos, 1, "");
	}
	string msa = "\nadd_textbox|" + who + "|left|";
	Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label|big|Worlds Locked|left|0|" + msa + "\nadd_button|close|`oClose|0|0|");*/



}

inline void scan_drop(ENetPeer* peer, const int item_id)
{

	//vistiek crash buna
	Player::OnConsoleMessage(peer, "`4You cannot perform this action!");
	return;


	/*scanrunning = true;

	cout << "scan is running" << endl;

	Player::OnConsoleMessage(peer, "`4You have selected option to scan all worlds, this kind of scan might take up to 5 minutes");

	using namespace std::chrono;
	int start = (duration_cast<seconds>(system_clock::now().time_since_epoch())).count();
	string path = "worlds/";
	auto fun = 0;
	string who = "";
	auto sukauptas = 0;
	int last = 0;
	int worlds = 0;
	for (const auto& entry : fs::directory_iterator(path))
	{
		worlds++;
	}
	for (const auto& entry : fs::directory_iterator(path))
	{
		fun++;
		ifstream stream(entry.path());
		if (stream.fail()) stream.close();
		json my_json;
		stream >> my_json;
		ostringstream oss;
		oss << entry;
		auto name = oss.str();
		size_t pos;
		while ((pos = name.find("worlds\\_")) != std::string::npos)
		{
			name.replace(pos, 8, "");
		}
		while ((pos = name.find(".json")) != std::string::npos)
		{
			name.replace(pos, 5, "");
		}
		if (fun % 1000 == 0 && fun != last)
		{
			auto dbr = worlds - fun;
			Player::OnConsoleMessage(peer, "`9World drop scanned `4" + to_string(fun) + "`9 Worlds, scanning `4" + to_string(dbr) + " `9Worlds more...");
		}
		for (auto i = 0; i < my_json["dropped"].size(); i++)
		{
			try
			{
				//cout << "sucess + " + to_string(i) << endl;
				if (my_json["dropped"][i]["id"] == item_id)
				{
					ostringstream osa;
					osa << my_json["dropped"][i]["c"];
					auto quantity = osa.str();
					sukauptas += atoi(quantity.c_str());
					ostringstream osa4444;
					osa4444 << my_json["dropped"][i]["droppedby"];
					string droppedBy = osa4444.str();

					ostringstream osa999;
					osa999 << my_json["nuked"];
					auto nuked = osa999.str();
					ostringstream osa333;
					osa333 << my_json["dname"];
					auto owner = osa333.str();

					if (droppedBy == "") droppedBy = "NOT DETECTED";
					if (nuked == "false") nuked = "`2false";
					if (nuked == "true") nuked = "`4true";
					owner += "`w";
					if (sukauptas != 0) who += name + " " + to_string(sukauptas) + " " + getItemDef(item_id).name + " `wnuked(" + nuked + "`w) world owner(" + owner + ") item dropped by(`$" + droppedBy + "`w)\n";
					sukauptas = 0;
				}
			}
			catch (std::exception&)
			{
				continue;
			}
		}

	}

	int finish = (duration_cast<seconds>(system_clock::now().time_since_epoch())).count();
	auto time = to_string(start - finish);
	size_t pos;
	while ((pos = time.find("-")) != std::string::npos)
	{
		time.replace(pos, 1, "");
	}
	Player::OnConsoleMessage(peer, "-----------Search Results-----------\n" + who + "------------------------------------");
	Player::OnConsoleMessage(peer, "`9Scan completed, took `4" + time + " `9Seconds (scanned `4" + to_string(fun) + " `9worlds)");
	scanrunning = false;

	cout << "scan is finished" << endl;*/

}



inline void complete_surgery(ENetPeer* peer)
{

	if (static_cast<PlayerInfo*>(peer->data)->SurgerySkill < 100) static_cast<PlayerInfo*>(peer->data)->SurgerySkill++;
	vector<int> surg_rewards{ 3172, 1258, 1260, 1262, 1264, 1266, 1268, 1270, 4308, 4310, 4312, 4314, 4316, 4318, 3172, 1258, 1260, 1262, 1264, 1266, 1268, 1270, 4308, 4310, 4312, 4314, 4316, 4318, 4296, 1242, 1244, 1246, 1248, 1282, 1284, 1286, 1290, 1288, 1292, 1294, 1256, 2586, 782, 3536, 764, 4176, 4322, 4080, 2992, 2976, 3790, 4990, 1506, 1274, 9000, 1252, 8284, 8954, 8534, 8478, 8480, 8486, 8484, 8482, 8468, 8494, 8466, 8490, 8456, 8458, 8496, 8472, 6398, 6426, 6340, 6342, 6350, 6818, 8244, 8242, 8240, 8452, 8454, 8488, 8498, 8474, 8476, 8492 };



	if (static_cast<PlayerInfo*>(peer->data)->cloth_face == 312)
	{
		surg_rewards.push_back(5482);
	}
	if (WinterfestEvent)
	{
		surg_rewards.push_back(2240);
		surg_rewards.push_back(3204);
	}
	if (SuperpineappleEvent)
	{
		surg_rewards.push_back(6114);
	}
	if (SurgeryDay)
	{
		surg_rewards.push_back(4328);
		surg_rewards.push_back(4326);
		surg_rewards.push_back(4330);
		surg_rewards.push_back(4324);
		surg_rewards.push_back(4334);
	}

	auto reward_id = surg_rewards[rand() % surg_rewards.size()];

	auto count = 1;

	if (reward_id == 1290) count = 10;
	if (reward_id == 1288) count = 5;
	if (reward_id == 1292) count = 5;
	if (reward_id == 1294) count = 5;

	if (reward_id == 1258) count = 5;
	if (reward_id == 1260) count = 5;
	if (reward_id == 1262) count = 5;
	if (reward_id == 1264) count = 5;
	if (reward_id == 1266) count = 5;
	if (reward_id == 1268) count = 5;
	if (reward_id == 1270) count = 5;
	if (reward_id == 4308) count = 5;
	if (reward_id == 4310) count = 5;
	if (reward_id == 4312) count = 5;
	if (reward_id == 4314) count = 5;
	if (reward_id == 4316) count = 5;
	if (reward_id == 4318) count = 5;
	if (reward_id == 4296) count = 5;



	if (reward_id == 8284)
	{
		if ((rand() % 10000) <= 5) {}
		else reward_id = 1244;
	}
	if (reward_id == 1506)
	{
		if ((rand() % 50) <= 5) {}
		else reward_id = 1242;
	}
	if (reward_id == 8452)
	{
		if ((rand() % 50) <= 5) {}
		else reward_id = 1246;
	}
	if (reward_id == 8488)
	{
		if ((rand() % 50) <= 5) {}
		else reward_id = 1248;
	}
	if (reward_id == 8492)
	{
		if ((rand() % 50) <= 5) {}
		else reward_id = 1242;
	}
	if (reward_id == 8494)
	{
		if ((rand() % 50) <= 5) {}
		else reward_id = 1244;
	}
	if (reward_id == 8496)
	{
		if ((rand() % 50) <= 5) {}
		else reward_id = 1246;
	}
	if (reward_id == 1252)
	{
		if ((rand() % 50) <= 5) {}
		else reward_id = 1248;
	}
	if (reward_id == 8954)
	{
		if ((rand() % 50) <= 5) {}
		else reward_id = 2586;
	}

	auto success = true;
	SaveItemMoreTimes(reward_id, count, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery");
	SaveItemMoreTimes(4298, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery");
	Player::PlayAudio(peer, "audio/double_chance.wav", 0);
	Player::OnConsoleMessage(peer, "`oYou got " + to_string(count) + " `2" + getItemDef(reward_id).name + " `oand a `3Caduceus`o!");
	Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wAfter a surgery like that, you decide you deserve `w" + to_string(count) + " " + getItemDef(reward_id).name + "`w.", 0, true);
	if (SurgeryDay) Player::OnConsoleMessage(peer, "Congratulations on your successful surgery! (`$Recovery`` mod added, `$30 min`` left)");
	else Player::OnConsoleMessage(peer, "Congratulations on your successful surgery! (`$Recovery`` mod added, `$20 min`` left)");
	ENetPeer* currentPeer;
	for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			Player::PlayAudio(currentPeer, "audio/metal_destroy.wav", 0);
		}
	}
	const auto world = getPlyersWorld(peer);
	if (static_cast<PlayerInfo*>(peer->data)->lastPunchX >= 0 && static_cast<PlayerInfo*>(peer->data)->lastPunchY >= 0)
	{
		world->items[static_cast<PlayerInfo*>(peer->data)->lastPunchX + (static_cast<PlayerInfo*>(peer->data)->lastPunchY * world->width)].foreground = 0;
		PlayerMoving data3;
		data3.packetType = 0x3;
		data3.characterState = 0x0;
		data3.x = static_cast<PlayerInfo*>(peer->data)->lastPunchX;
		data3.y = static_cast<PlayerInfo*>(peer->data)->lastPunchY;
		data3.punchX = static_cast<PlayerInfo*>(peer->data)->lastPunchX;
		data3.punchY = static_cast<PlayerInfo*>(peer->data)->lastPunchY;
		data3.XSpeed = 0;
		data3.YSpeed = 0;
		data3.netID = -1;
		data3.plantingTree = 0;
		for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				auto raw = packPlayerMoving(&data3);
				raw[2] = 0;
				raw[3] = 0;
				SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
				Player::OnParticleEffect(currentPeer, 57, static_cast<PlayerInfo*>(peer->data)->lastPunchX * 32, static_cast<PlayerInfo*>(peer->data)->lastPunchY * 32, 0);
			}
		}
	}
	end_surgery(peer, false);

}

inline bool surgery_skill_fail(ENetPeer* peer)
{
	const auto chance = 85 + static_cast<PlayerInfo*>(peer->data)->SurgerySkill;
	if (rand() % 200 < chance) return false; /*nera*/
	else return true;
}

inline void DayTimer()
{
	while (DayTimer)
	{
		Sleep(30000);
		LoadEvents();
		for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (currentPeer->data == nullptr) continue;
			if (static_cast<PlayerInfo*>(currentPeer->data)->currentWorld == "EXIT") continue;
			if (!static_cast<PlayerInfo*>(currentPeer->data)->isIn) continue;
			if (!static_cast<PlayerInfo*>(currentPeer->data)->haveGrowId) continue;
			if (static_cast<PlayerInfo*>(currentPeer->data)->isCursed == true)
			{
				auto cooldownleft = calcBanDuration(static_cast<PlayerInfo*>(currentPeer->data)->lastCursed);
				if (cooldownleft < 1)
				{
					Player::OnTextOverlay(currentPeer, "`^Your `4Curse `^Has `2Expired, `4Don't `^Break `2Rules `^Anymore!");
					Player::OnConsoleMessage(currentPeer, "`^Your `4Curse `^Has `2Expired, `4Don't `^Break `2Rules `^Anymore!");
					static_cast<PlayerInfo*>(currentPeer->data)->skinColor = 0x8295C3FF;
					sendClothes(currentPeer);
					static_cast<PlayerInfo*>(currentPeer->data)->isCursed = false;
					send_state(currentPeer);
					remove(("cursedplayers/" + static_cast<PlayerInfo*>(currentPeer->data)->rawName + ".txt").c_str());
				}
			}
			if (static_cast<PlayerInfo*>(currentPeer->data)->isDuctaped == true)
			{
				auto cooldownleft = calcBanDuration(static_cast<PlayerInfo*>(currentPeer->data)->lastMuted);
				if (cooldownleft < 1)
				{
					Player::OnTextOverlay(currentPeer, "`^Your `4Mute `^Has `2Expired, `4Don't `^Break `2Rules `^Anymore!");
					Player::OnConsoleMessage(currentPeer, "`^Your `4Mute `^Has `2Expired, `4Don't `^Break `2Rules `^Anymore!");
					static_cast<PlayerInfo*>(currentPeer->data)->taped = false;
					static_cast<PlayerInfo*>(currentPeer->data)->isDuctaped = false;
					static_cast<PlayerInfo*>(currentPeer->data)->cantsay = false;
					send_state(currentPeer);
					sendClothes(currentPeer);
					remove(("timemuted/" + static_cast<PlayerInfo*>(currentPeer->data)->rawName + ".txt").c_str());
				}
			}
			if (static_cast<PlayerInfo*>(currentPeer->data)->Fishing && !static_cast<PlayerInfo*>(currentPeer->data)->TriggerFish && static_cast<PlayerInfo*>(currentPeer->data)->FishPosX != 0 && static_cast<PlayerInfo*>(currentPeer->data)->FishPosY != 0) {
				if (rand() % 100 <= 50) {
					static_cast<PlayerInfo*>(currentPeer->data)->TriggerFish = true;
					for (auto currentPeers = server->peers; currentPeers < &server->peers[server->peerCount]; ++currentPeers) {
						if (currentPeers->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(currentPeer, currentPeers)) {
							Player::OnParticleEffect(currentPeers, 36, static_cast<PlayerInfo*>(currentPeer->data)->FishPosX, static_cast<PlayerInfo*>(currentPeer->data)->FishPosY, 0);
							Player::PlayAudio(currentPeers, "audio/splash.wav", 0);
						}
					}
				}
			}
			if (static_cast<PlayerInfo*>(currentPeer->data)->SurgeryCooldown)
			{
				auto cooldownleft = calcBanDuration(static_cast<PlayerInfo*>(currentPeer->data)->SurgeryTime);
				if (cooldownleft < 1)
				{

					Player::OnConsoleMessage(currentPeer, "You've paid your debt to society! (`$Malpractice`` mod removed)");
					sendSound(currentPeer, "audio/dialog_confirm.wav");
					static_cast<PlayerInfo*>(currentPeer->data)->SurgeryCooldown = false;
					static_cast<PlayerInfo*>(currentPeer->data)->SurgeryTime = 0;
					remove(("buffs/surgery/" + static_cast<PlayerInfo*>(currentPeer->data)->rawName + ".txt").c_str());
				}

			}
			if (static_cast<PlayerInfo*>(currentPeer->data)->needsaveinventory)
			{

				json items;
				auto jjall = json::array();
				json jj;
				auto invsize = static_cast<PlayerInfo*>(currentPeer->data)->inventory.items.size();
				try
				{
					ofstream ofs("inventory/" + static_cast<PlayerInfo*>(currentPeer->data)->rawName + ".json");
					for (auto i = 0; i < 200; i++)
					{

						if (i < invsize)
						{
							jj["aposition"] = i + 1;
							jj["itemid"] = static_cast<PlayerInfo*>(currentPeer->data)->inventory.items.at(i).itemID;
							jj["quantity"] = static_cast<PlayerInfo*>(currentPeer->data)->inventory.items.at(i).itemCount;
							jj["madeby"] = static_cast<PlayerInfo*>(currentPeer->data)->inventory.items.at(i).madeBy;
							jjall.push_back(jj);
						}
						else
						{
							jj["aposition"] = i + 1;
							jj["itemid"] = 0;
							jj["quantity"] = 0;
							jj["madeby"] = "";
							jjall.push_back(jj);
						}
					}
					items["items"] = jjall;
					ofs << items << std::endl;
					ofs.close();
				}
				catch (std::exception& e)
				{
					cerr << e.what() << endl;
					SendConsole("SavesTimer (exception) caused by " + static_cast<PlayerInfo*>(currentPeer->data)->rawName + "", "ERROR");
					enet_peer_disconnect_now(currentPeer, 0);
				}
				catch (std::runtime_error&)
				{
					SendConsole("SavesTimer (runtime) caused by " + static_cast<PlayerInfo*>(currentPeer->data)->rawName + "", "ERROR");
					enet_peer_disconnect_now(currentPeer, 0);
				}
				catch (...)
				{
					SendConsole("SavesTimer (...) caused by " + static_cast<PlayerInfo*>(currentPeer->data)->rawName + "", "ERROR");
					enet_peer_disconnect_now(currentPeer, 0);
				}
				static_cast<PlayerInfo*>(currentPeer->data)->needsaveinventory = false;
			}
		}
	}
}

inline void TradeMainMenu(ENetPeer* peer)
{
	string user = static_cast<PlayerInfo*>(peer->data)->lastTradeGrowid;
	if (user == "") return;
	bool isonline = false;

	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (static_cast<PlayerInfo*>(currentPeer->data)->rawName == PlayerDB::getProperName(user))
		{
			isonline = true;
			GTDialog tradedialog;
			tradedialog.addLabelWithIcon("`wTrade with `$" + user, 1434, LABEL_SMALL);

			tradedialog.addSpacer(SPACER_SMALL);
			tradedialog.addSmallText("`$Add items that you want to sell.");
			tradedialog.addSmallText("`$(click on the boxes below)");
			tradedialog.addSpacer(SPACER_SMALL);

			if (static_cast<PlayerInfo*>(peer->data)->mySellingItem1 == "3308" || static_cast<PlayerInfo*>(peer->data)->mySellingItem1Count == "0")
			{
				tradedialog.addStaticBlueFrameWithIdCountText("10036", "0", "empty", "putMySellingItem_1", false);
			}
			else
			{
				tradedialog.addStaticBlueFrameWithIdCountText(static_cast<PlayerInfo*>(peer->data)->mySellingItem1, static_cast<PlayerInfo*>(peer->data)->mySellingItem1Count, getItemDef(atoi(static_cast<PlayerInfo*>(peer->data)->mySellingItem1.c_str())).name, "putMySellingItem_1", false);
			}

			if (static_cast<PlayerInfo*>(peer->data)->mySellingItem2 == "3308" || static_cast<PlayerInfo*>(peer->data)->mySellingItem2Count == "0")
			{
				tradedialog.addStaticBlueFrameWithIdCountText("10036", "0", "empty", "putMySellingItem_2", false);
			}
			else
			{
				tradedialog.addStaticBlueFrameWithIdCountText(static_cast<PlayerInfo*>(peer->data)->mySellingItem2, static_cast<PlayerInfo*>(peer->data)->mySellingItem2Count, getItemDef(atoi(static_cast<PlayerInfo*>(peer->data)->mySellingItem2.c_str())).name, "putMySellingItem_2", false);
			}

			if (static_cast<PlayerInfo*>(peer->data)->mySellingItem3 == "3308" || static_cast<PlayerInfo*>(peer->data)->mySellingItem3Count == "0")
			{
				tradedialog.addStaticBlueFrameWithIdCountText("10036", "0", "empty", "putMySellingItem_3", false);
			}
			else
			{
				tradedialog.addStaticBlueFrameWithIdCountText(static_cast<PlayerInfo*>(peer->data)->mySellingItem3, static_cast<PlayerInfo*>(peer->data)->mySellingItem3Count, getItemDef(atoi(static_cast<PlayerInfo*>(peer->data)->mySellingItem3.c_str())).name, "putMySellingItem_3", false);
			}

			if (static_cast<PlayerInfo*>(peer->data)->mySellingItem4 == "3308" || static_cast<PlayerInfo*>(peer->data)->mySellingItem4Count == "0")
			{
				tradedialog.addStaticBlueFrameWithIdCountText("10036", "0", "empty", "putMySellingItem_4", false);
			}
			else
			{
				tradedialog.addStaticBlueFrameWithIdCountText(static_cast<PlayerInfo*>(peer->data)->mySellingItem4, static_cast<PlayerInfo*>(peer->data)->mySellingItem4Count, getItemDef(atoi(static_cast<PlayerInfo*>(peer->data)->mySellingItem4.c_str())).name, "putMySellingItem_4", false);
			}
			tradedialog.addNewLineAfterFrame();

			tradedialog.addSpacer(SPACER_SMALL);
			tradedialog.addSpacer(SPACER_SMALL);
			tradedialog.addSpacer(SPACER_SMALL);
			tradedialog.addSmallText("`$Add items that you want to get.");
			tradedialog.addSmallText("`$(click on the boxes below)");
			tradedialog.addSpacer(SPACER_SMALL);

			if (static_cast<PlayerInfo*>(peer->data)->hisSellingItem1 == "3308" || static_cast<PlayerInfo*>(peer->data)->hisSellingItem1Count == "0")
			{
				tradedialog.addStaticBlueFrameWithIdCountText("10036", "0", "empty", "putHisSellingItem_1", false);
			}
			else
			{
				tradedialog.addStaticBlueFrameWithIdCountText(static_cast<PlayerInfo*>(peer->data)->hisSellingItem1, static_cast<PlayerInfo*>(peer->data)->hisSellingItem1Count, getItemDef(atoi(static_cast<PlayerInfo*>(peer->data)->hisSellingItem1.c_str())).name, "putHisSellingItem_1", false);
			}

			if (static_cast<PlayerInfo*>(peer->data)->hisSellingItem2 == "3308" || static_cast<PlayerInfo*>(peer->data)->hisSellingItem2Count == "0")
			{
				tradedialog.addStaticBlueFrameWithIdCountText("10036", "0", "empty", "putHisSellingItem_2", false);
			}
			else
			{
				tradedialog.addStaticBlueFrameWithIdCountText(static_cast<PlayerInfo*>(peer->data)->hisSellingItem2, static_cast<PlayerInfo*>(peer->data)->hisSellingItem2Count, getItemDef(atoi(static_cast<PlayerInfo*>(peer->data)->hisSellingItem2.c_str())).name, "putHisSellingItem_2", false);
			}

			if (static_cast<PlayerInfo*>(peer->data)->hisSellingItem3 == "3308" || static_cast<PlayerInfo*>(peer->data)->hisSellingItem3Count == "0")
			{
				tradedialog.addStaticBlueFrameWithIdCountText("10036", "0", "empty", "putHisSellingItem_3", false);
			}
			else
			{
				tradedialog.addStaticBlueFrameWithIdCountText(static_cast<PlayerInfo*>(peer->data)->hisSellingItem3, static_cast<PlayerInfo*>(peer->data)->hisSellingItem3Count, getItemDef(atoi(static_cast<PlayerInfo*>(peer->data)->hisSellingItem3.c_str())).name, "putHisSellingItem_3", false);
			}

			if (static_cast<PlayerInfo*>(peer->data)->hisSellingItem4 == "3308" || static_cast<PlayerInfo*>(peer->data)->hisSellingItem4Count == "0")
			{
				tradedialog.addStaticBlueFrameWithIdCountText("10036", "0", "empty", "putHisSellingItem_4", false);
			}
			else
			{
				tradedialog.addStaticBlueFrameWithIdCountText(static_cast<PlayerInfo*>(peer->data)->hisSellingItem4, static_cast<PlayerInfo*>(peer->data)->hisSellingItem4Count, getItemDef(atoi(static_cast<PlayerInfo*>(peer->data)->hisSellingItem4.c_str())).name, "putHisSellingItem_4", false);
			}
			tradedialog.addNewLineAfterFrame();

			tradedialog.addSpacer(SPACER_SMALL);
			tradedialog.addSpacer(SPACER_SMALL);
			tradedialog.addButton("sendtrade", "`2Send Trade Request.");
			tradedialog.addSpacer(SPACER_SMALL);
			tradedialog.addSpacer(SPACER_SMALL);
			tradedialog.addButton("closetrade", "Cancel Trade.");
			tradedialog.addQuickExit();
			tradedialog.endDialog("", "", "");
			Player::OnDialogRequest(peer, tradedialog.finishDialog());
		}
	}
	if (!isonline)
	{
		Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4This player is not online.", 0, true);
	}
}

vector<itemDataStruct> items;
void serializeItems();

itemDataStruct getItem(int id)
{
	if (itemsDat == nullptr)
	{
		itemDataStruct ret;
		ret.id = -1;
		return ret;
	}
	auto itemsPtr = itemsDat + 60;
	itemsPtr += 4;
	while (true)
	{
		itemsPtr += *reinterpret_cast<uint16_t*>(itemsPtr) + 2;
		if (*reinterpret_cast<uint16_t*>(itemsPtr) == id)
		{
			itemDataStruct item;
			item.id = *reinterpret_cast<uint16_t*>(itemsPtr);
			itemsPtr += 2;
			itemsPtr += 2;
			item.editableType = *static_cast<uint8_t*>(itemsPtr++);
			item.category = *static_cast<uint8_t*>(itemsPtr++);
			item.type = *static_cast<uint8_t*>(itemsPtr++);
			itemsPtr++;
			int nameLen = *reinterpret_cast<uint16_t*>(itemsPtr);
			itemsPtr += 2;
			string name;
			name.resize(nameLen);
			decodeName(reinterpret_cast<char*>(itemsPtr), nameLen, id, &name[0]);
			item.name = name;
			itemsPtr += nameLen;
			int textureLen = *reinterpret_cast<uint16_t*>(itemsPtr);
			itemsPtr += 2;
			string texturefile;
			texturefile.resize(textureLen);
			memcpy(&texturefile[0], itemsPtr, textureLen);
			item.texturefile = texturefile;
			itemsPtr += textureLen;
			item.texturehash = *reinterpret_cast<uint32_t*>(itemsPtr);
			itemsPtr += 4;
			itemsPtr += 5;
			item.textureX = *static_cast<uint8_t*>(itemsPtr++);
			item.textureY = *static_cast<uint8_t*>(itemsPtr++);
			item.textureType = *static_cast<uint8_t*>(itemsPtr);
			itemsPtr += 2;
			item.solid = *static_cast<uint8_t*>(itemsPtr++);
			item.hardness = *static_cast<uint8_t*>(itemsPtr++);
			itemsPtr += 1;
			itemsPtr += 4;
			item.rarity = *reinterpret_cast<uint16_t*>(itemsPtr);
			itemsPtr += 2;
			itemsPtr += 1;
			int audioLen = *reinterpret_cast<uint16_t*>(itemsPtr);
			itemsPtr += 2;
			string audiofile;
			audiofile.resize(audioLen);
			memcpy(&audiofile[0], itemsPtr, audioLen);
			item.audiofile = audiofile;
			itemsPtr += audioLen;
			item.audiohash = *reinterpret_cast<uint32_t*>(itemsPtr);
			itemsPtr += 4;
			item.audioVol = *reinterpret_cast<uint16_t*>(itemsPtr);
			itemsPtr += 2;
			itemsPtr += 16;
			item.seedBase = *static_cast<uint8_t*>(itemsPtr++);
			item.seedOverlay = *static_cast<uint8_t*>(itemsPtr++);
			item.treeBase = *static_cast<uint8_t*>(itemsPtr++);
			item.treeOverlay = *static_cast<uint8_t*>(itemsPtr++);
			item.color1 = *reinterpret_cast<uint32_t*>(itemsPtr);
			itemsPtr += 4;
			item.color2 = *reinterpret_cast<uint32_t*>(itemsPtr);
			itemsPtr += 4;
			return item;
		}
		else
		{
			itemsPtr += 8;
			itemsPtr += *reinterpret_cast<uint16_t*>(itemsPtr) + 2;
			itemsPtr += *reinterpret_cast<uint16_t*>(itemsPtr) + 2;
			itemsPtr += 23;
			itemsPtr += *reinterpret_cast<uint16_t*>(itemsPtr) + 2;
			itemsPtr += 8;
			for (int i = 0; i < 4; i++) itemsPtr += *reinterpret_cast<uint16_t*>(itemsPtr) + 2;
			itemsPtr += 24;
			itemsPtr += *reinterpret_cast<uint16_t*>(itemsPtr) + 2;
			itemsPtr += *reinterpret_cast<uint16_t*>(itemsPtr) + 2;
			itemsPtr += *reinterpret_cast<uint16_t*>(itemsPtr) + 2;
			itemsPtr += *reinterpret_cast<uint16_t*>(itemsPtr) + 2;
			itemsPtr += 78;
		}
		if (itemsPtr - itemsDat >= itemsDatSize)
		{
			itemDataStruct item;
			item.id = -1;
			return item;
		}
	}
}

void serializeItems()
{
	SendConsole("Loading all items...", "INFO");
	auto i = 0;
	while (true)
	{
		auto item = getItem(i++);
		if (item.id == -1) break;
		items.push_back(item);
		coredatasize++;
	}
	SendConsole("Finished loading all items...", "INFO");
}
