// ReSharper disable All
#pragma once
#include "stdafx.h"
#include <fstream>
// ReSharper disable once CppUnusedIncludeDirective
#include <iostream>
#include "Server_player.h"
#include "Server_world.h"
#include "enet/enet.h"
// ReSharper disable once CppUnusedIncludeDirective
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <locale>
#include <regex>
#include <string>
#include <thread>
#include <vector>
#include <experimental/filesystem>
#include "json.hpp"
// ReSharper disable once CppUnusedIncludeDirective
#include "Player_mods.h"
#ifdef _WIN32
#include <windows.h>
typedef __int8 __int8_t;
typedef __int16 __int16_t;
#elif __APPLE__ || __linux__
typedef unsigned int DWORD;
#endif
typedef unsigned char BYTE;

inline void sendTileUpdate(int x, int y, int tile, int causedBy, ENetPeer* peer)
{
	if (serverIsFrozen == true) return;
	if (tile > itemDefs.size()) return;
	if (!static_cast<PlayerInfo*>(peer->data)->haveGrowId)
	if (!static_cast<PlayerInfo*>(peer->data)->haveGrowId)
	if (!static_cast<PlayerInfo*>(peer->data)->haveGrowId)
	{
		SendBreakPacket(peer, x, y);
		return;
	}
	if (static_cast<PlayerInfo*>(peer->data)->isIn == false) return;
	if (static_cast<PlayerInfo*>(peer->data)->currentWorld == "EXIT") return;
	auto dicenr = 0;
	PlayerMoving data;  
	PlayerInfo* pinfo = static_cast<PlayerInfo*>(peer->data);
	auto world = getPlyersWorld(peer);
 	data.packetType = 0x3;
	data.characterState = 0x0;
	data.x = x;
	data.y = y;
	data.punchX = x;
	data.punchY = y;
	data.XSpeed = 0;
	data.YSpeed = 0;
	data.netID = causedBy;
	data.plantingTree = tile;
	auto isTree = false;
	auto isLock = false;
	auto isSmallLock = false;
	auto isHeartMonitor = false;
	bool isMannequin = false;
	auto isScience = false;
	auto isMagplant = false;
	auto isgateway = false;
	auto VendUpdate = false;
	bool isDoor = false;
	auto squaresign = x + (y * 100);
	auto iscontains = false;
	if (world == nullptr) return;
	if (x < 0 || y < 0 || x > world->width - 1 || y > world->height - 1 || tile > itemDefs.size()) return;
	
	SendBreakPacket(peer, x, y);

	if (world->name == "GAME1BACKUP")
	{
		return;
	}
	if (world->name == "GAME1")
	{
		if (game1status == false && world->items[x + (y * world->width)].foreground != 658) return;
		if (game1status == true) return;
	}
	if (world->name == "GAME2")
	{
		if (game2status == false && world->items[x + (y * world->width)].foreground != 658) return;
		if (game2status == true) return;
	}
	if (world->name == "HELL" && static_cast<PlayerInfo*>(peer->data)->isCursed == true)
	{
		return;
	}

	auto contains = false;
	SearchInventoryItem(peer, tile, 1, contains);
	if (!contains)	return;

	bool foundone = false;
	for (int i = 0; i < world->width * world->height; i++) {
		if (world->items[i].foreground == 6952) {
			foundone = true; // tunggu gw bilang udah anjINc
		}
	}
	if (isWorldOwner(peer, world) || world->isPublic || world->owner == "" || isDev(peer)) {
		if (foundone) {
			auto itemid = 0;
			int xx = static_cast<PlayerInfo*>(peer->data)->lastPunchX;
			int yy = static_cast<PlayerInfo*>(peer->data)->lastPunchY;
			auto squaresign = xx + (yy * 100);
			auto currentworld = static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(squaresign);
			string Sucker = "tesseractmanipulator";
			ifstream fdss(Sucker + "/storeditem/" + currentworld + ".txt"); /*Read the storeditem IDS*/
			fdss >> itemid;
			fdss.close();
			string autobreakcheck = "";
			string autobreakis = "false";
			auto autotm = std::experimental::filesystem::exists(Sucker + "/autobreak/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(squaresign) + ".txt"); /*Check if item sucker data file exists*/
			if (autotm) {
				ifstream basic_ifstream(Sucker + "/autobreak/" + currentworld + ".txt"); /*Read the storeditem counts*/
				basic_ifstream >> autobreakis;
				basic_ifstream.close();
			}
			if (autobreakis == "true") {
				if (tile == itemid) {
					thread checkPlayerState(AutoBreak, peer, x, y);
					if (checkPlayerState.joinable()) {
						checkPlayerState.detach();
					}
				}
			}
		}
	}

	if (((PlayerInfo*)(peer->data))->tradeSomeone == true)
	{
		ENetPeer* currentPeer;
		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			if (isHere(peer, currentPeer))
			{
				if (((PlayerInfo*)(currentPeer->data))->netID == ((PlayerInfo*)(peer->data))->lastTradeNetID && ((PlayerInfo*)(currentPeer->data))->lastTradeNetID == ((PlayerInfo*)(peer->data))->netID)
				{
					if (((PlayerInfo*)(currentPeer->data))->tradeSomeone == true) {
						Player::OnTextOverlay(peer, ((PlayerInfo*)(peer->data))->displayName + " `wis too busy to trade!");
						Player::OnTextOverlay(currentPeer, ((PlayerInfo*)(peer->data))->displayName + " `wis too busy to trade!");
						Player::OnForceTradeEnd(peer);
						Player::OnForceTradeEnd(currentPeer);
						((PlayerInfo*)(peer->data))->currentTradeItems = "";
						((PlayerInfo*)(currentPeer->data))->currentTradeItems = "";
						((PlayerInfo*)(peer->data))->lastTradeAcceptCount = 0;
						((PlayerInfo*)(currentPeer->data))->lastTradeAcceptCount = 0;
						((PlayerInfo*)(peer->data))->lastTradeNetID = 0;
						((PlayerInfo*)(currentPeer->data))->lastTradeNetID = 0;
						((PlayerInfo*)(peer->data))->tradeSomeone = false;
						((PlayerInfo*)(currentPeer->data))->tradeSomeone = false;
						((PlayerInfo*)(peer->data))->isDoTrade = 0;
						((PlayerInfo*)(currentPeer->data))->isDoTrade = 0;
						((PlayerInfo*)(peer->data))->lastTD1 = 0;
						((PlayerInfo*)(peer->data))->lastTD2 = 0;
						((PlayerInfo*)(peer->data))->lastTD3 = 0;
						((PlayerInfo*)(peer->data))->lastTD4 = 0;
						((PlayerInfo*)(peer->data))->lastCT1 = 0;
						((PlayerInfo*)(peer->data))->lastCT2 = 0;
						((PlayerInfo*)(peer->data))->lastCT3 = 0;
						((PlayerInfo*)(peer->data))->lastCT4 = 0;
						((PlayerInfo*)(currentPeer->data))->lastTD1 = 0;
						((PlayerInfo*)(currentPeer->data))->lastTD2 = 0;
						((PlayerInfo*)(currentPeer->data))->lastTD3 = 0;
						((PlayerInfo*)(currentPeer->data))->lastTD4 = 0;
						((PlayerInfo*)(currentPeer->data))->lastCT1 = 0;
						((PlayerInfo*)(currentPeer->data))->lastCT2 = 0;
						((PlayerInfo*)(currentPeer->data))->lastCT3 = 0;
						((PlayerInfo*)(currentPeer->data))->lastCT4 = 0;
					}
					else
					{
						Player::OnTextOverlay(peer, ((PlayerInfo*)(peer->data))->displayName + " `wis too busy to trade!");
						Player::OnForceTradeEnd(peer);
						((PlayerInfo*)(peer->data))->currentTradeItems = "";
						((PlayerInfo*)(peer->data))->lastTradeAcceptCount = 0;
						((PlayerInfo*)(peer->data))->lastTradeNetID = 0;
						((PlayerInfo*)(peer->data))->tradeSomeone = false;
						((PlayerInfo*)(peer->data))->isDoTrade = 0;
						((PlayerInfo*)(peer->data))->lastTD1 = 0;
						((PlayerInfo*)(peer->data))->lastTD2 = 0;
						((PlayerInfo*)(peer->data))->lastTD3 = 0;
						((PlayerInfo*)(peer->data))->lastTD4 = 0;
						((PlayerInfo*)(peer->data))->lastCT1 = 0;
						((PlayerInfo*)(peer->data))->lastCT2 = 0;
						((PlayerInfo*)(peer->data))->lastCT3 = 0;
						((PlayerInfo*)(peer->data))->lastCT4 = 0;
					}
				}
			}
		}
	}
	if (world->items[x + (y * world->width)].foreground == 1792) { // legendary orb by KangSomay#0150
		bool iscontains = false;
		SearchInventoryItem(peer, 1794, 1, iscontains);
		if (!iscontains)
		{
			bool success = true;
			SaveShopsItemMoreTimer(1794, 1, peer, success);
			GamePacket p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), "`9You have claimed a Legendary Orb"), 0));
			ENetPacket* packet2 = enet_packet_create(p2.data,
				p2.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet2);
			delete p2.data;
			GamePacket psp = packetEnd(appendFloat(appendIntx(appendString(createPacket(), "OnParticleEffect"), 50), x * 32, y * 32));
			ENetPacket* packetd = enet_packet_create(psp.data,
				psp.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packetd);
		}
		else {
			bool success = true;
			if (success)
			{
				GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnTextOverlay"), "`9You already have it"));
				ENetPacket* packet2 = enet_packet_create(p2.data,
					p2.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet2);
				delete p2.data;
			}
		}
	}
	if (getItemDef(tile).blockType == BlockTypes::SEED && !world->items[x + (y * world->width)].fire) {
		if (world->items[x + (y * world->width)].foreground != 0) {
			if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::SEED) {
				if (world->isPublic || isWorldAdmin(peer, world) || static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || world->owner == "" || isDev(peer) || !RestrictedArea(peer, world, x, y)) {
					if (calcBanDuration(world->items[x + (y * world->width)].growtime) == 0) {
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "This tree is already too big to splice another seed with.", 0, true);
						return;
					}
					if (getItemDef(world->items[x + (y * world->width)].foreground).name == getItemDef(tile).name || getItemDef(world->items[x + (y * world->width)].foreground).rarity == 999 || getItemDef(tile).rarity == 999) {
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Hmm, it looks like `w" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`` and `w" + getItemDef(tile).name + "`` can't be spliced.", 0, true);
						return;
					}
					auto iscontains = false;
					SearchInventoryItem(peer, tile, 1, iscontains);
					if (!iscontains) return;
					if (!world->items[x + (y * world->width)].spliced) {
						auto targetvalue = getItemDef(world->items[x + (y * world->width)].foreground).rarity + getItemDef(tile).rarity;
						if (static_cast<PlayerInfo*>(peer->data)->level >= 15) targetvalue += 1;
						for (auto i = 0; i < 10016; i++) {
							if (getItemDef(i).rarity == targetvalue) {
								world->items[x + (y * world->width)].spliced = true;
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`` and `w" + getItemDef(tile).name + "`` have been spliced to make a `$" + getItemDef(i + 1).name + "``!", 0, true);
								Player::PlayAudio(peer, "audio/success.wav", 0);
								world->items[x + (y * world->width)].foreground = i + 1;
								int growTimeSeed = getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity * getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity * getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity;
								growTimeSeed += 30 * getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity;
								if (world->items[x + (y * world->width)].foreground - 1 == 954) growTimeSeed = 1800;
								if (world->items[x + (y * world->width)].foreground - 1 == 340) growTimeSeed = 3600;
								if (world->items[x + (y * world->width)].foreground - 1 == 5666) growTimeSeed = 2700;
								if (world->items[x + (y * world->width)].foreground - 1 == 4584) growTimeSeed = 2400;
								if (world->items[x + (y * world->width)].foreground - 1 == 4762) growTimeSeed = 14544;
								if (world->items[x + (y * world->width)].foreground - 1 == 7382) growTimeSeed = 22544;
								if (world->items[x + (y * world->width)].foreground - 1 == 9460) growTimeSeed = 29544;
								if (world->items[x + (y * world->width)].foreground - 1 == 9468) growTimeSeed = 36544;
								if (world->items[x + (y * world->width)].foreground - 1 == 10024) growTimeSeed = 56544;
								if (world->items[x + (y * world->width)].foreground - 1 == 10029) growTimeSeed = 86400;
								world->items[x + (y * world->width)].growtime = (GetCurrentTimeInternalSeconds() + growTimeSeed);
								if (getItemDef(world->items[x + (y * world->width)].foreground).rarity == 999) {
									world->items[x + (y * world->width)].fruitcount = (rand() % 1) + 1;
								}
								else {
									world->items[x + (y * world->width)].fruitcount = (rand() % 3) + 1;
								}
								if (getItemDef(world->items[x + (y * world->width)].foreground - 1).blockType == BlockTypes::CLOTHING) world->items[x + (y * world->width)].fruitcount = 1;
								UpdateTreeVisuals(peer, world->items[x + (y * world->width)].foreground, x, y, world->items[x + (y * world->width)].background, world->items[x + (y * world->width)].fruitcount, 0, true, 0);
								RemoveInventoryItem(tile, 1, peer, true);
								break;
							}
							else if (i >= 10015) {
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Hmm, it looks like `w" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`` and `w" + getItemDef(tile).name + "`` can't be spliced.", 0, true);
								break;
							}
						}
					}
					else {
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "It would be too dangerous to try to mix three seeds.", 0, true);
					}
				}
				return;
			}
		}
		else {
			isTree = true;
		}
	}
	switch (tile)
	{
	case 18: /*punch*/
		{
			if (world->items[x + (y * world->width)].foreground == 1420 || world->items[x + (y * world->width)].foreground == 6214)
            {
                if (world->owner == "" || static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner))
                {
                    auto seedexist = std::experimental::filesystem::exists("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
                    if (seedexist)
                    {
                        json j;
                        ifstream fs("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
                        fs >> j;
                        fs.close();
                        bool found = false, success = false;
                        if (j["clothHead"].get<string>() != "0")
                        {
                            SaveItemMoreTimes(atoi(j["clothHead"].get<string>().c_str()), 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from Mannequin");
                            found = true;
                            j["clothHead"] = "0";
                        }
                        else if (j["clothHair"].get<string>() != "0")
                        {
                            SaveItemMoreTimes(atoi(j["clothHair"].get<string>().c_str()), 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from Mannequin");
                            found = true;
                            j["clothHair"] = "0";
                        }
                        else if (j["clothMask"].get<string>() != "0")
                        {
                            SaveItemMoreTimes(atoi(j["clothMask"].get<string>().c_str()), 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from Mannequin");
                            found = true;
                            j["clothMask"] = "0";
                        }
                        else if (j["clothNeck"].get<string>() != "0")
                        {
                            SaveItemMoreTimes(atoi(j["clothNeck"].get<string>().c_str()), 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from Mannequin");
                            found = true;
                            j["clothNeck"] = "0";
                        }
						else if (j["clothBack"].get<string>() != "0")
                        {
                            SaveItemMoreTimes(atoi(j["clothBack"].get<string>().c_str()), 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from Mannequin");
                            found = true;
                            j["clothBack"] = "0";
                        }
                        else if (j["clothShirt"].get<string>() != "0")
                        {
                            SaveItemMoreTimes(atoi(j["clothShirt"].get<string>().c_str()), 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from Mannequin");
                            found = true;
                            j["clothShirt"] = "0";
                        }
                        else if (j["clothPants"].get<string>() != "0")
                        {
                            SaveItemMoreTimes(atoi(j["clothPants"].get<string>().c_str()), 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from Mannequin");
                            found = true;
                            j["clothPants"] = "0";
                        }
                        else if (j["clothFeet"].get<string>() != "0")
                        {
							SaveItemMoreTimes(atoi(j["clothFeet"].get<string>().c_str()), 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from Mannequin");
                            found = true;
                            j["clothFeet"] = "0";
                        }
                        else if (j["clothHand"].get<string>() != "0")
                        {
                            SaveItemMoreTimes(atoi(j["clothHand"].get<string>().c_str()), 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from Mannequin");
                            found = true;
                            j["clothHand"] = "0";
                        }

                        if (found)
                        {
                            updateMannequin(peer, world->items[x + (y * world->width)].foreground, x, y, world->items[x + (y * world->width)].background, world->items[x + (y * world->width)].sign,
                                atoi(j["clothHair"].get<string>().c_str()), atoi(j["clothHead"].get<string>().c_str()),
                                atoi(j["clothMask"].get<string>().c_str()), atoi(j["clothHand"].get<string>().c_str()), atoi(j["clothNeck"].get<string>().c_str()),
                                atoi(j["clothShirt"].get<string>().c_str()), atoi(j["clothPants"].get<string>().c_str()), atoi(j["clothFeet"].get<string>().c_str()),
                                atoi(j["clothBack"].get<string>().c_str()), true, 0);

                            ofstream of("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
                            of << j;
                            of.close();
                        }
                    }
                }
            }
			if (world->items[x + (y * world->width)].foreground == 3616) {
				if (world->items[x + (y * world->width)].activated) {
					world->items[x + (y * world->width)].activated = false;
					UpdateBlockState(peer, x, y, true, world);
					world->isPineappleGuard = false;
				}
				else {
					world->isPineappleGuard = true;
					world->items[x + (y * world->width)].activated = true;
					UpdateBlockState(peer, x, y, true, world);

				}
			}
			// WE ARE GOOD TO GO
			if (tile == 18)
			{
				if (world->items[x + (y * world->width)].foreground == 3832)
				{
					world->weather = 29;
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
			// WE ARE GOOD TO GO
			if (tile == 18)
			{
				if (world->items[x + (y * world->width)].foreground == 5000)
				{
					world->weather = 34;
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
			if (world->items[x + (y * world->width)].foreground == 3554) {
				std::ifstream ifszxdd("pet/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
				std::string contentzzz((std::istreambuf_iterator<char>(ifszxdd)),
					(std::istreambuf_iterator<char>()));
				int b = atoi(contentzzz.c_str());

				int pet = b;


				ofstream myfile2;
				myfile2.open("pet/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
				myfile2 << std::to_string(pet);
				myfile2.close();

				std::ifstream ifszi("pet/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
				std::string contentx((std::istreambuf_iterator<char>(ifszi)),
					(std::istreambuf_iterator<char>()));
				if (pet == 0) {
					Player::OnDialogRequest(peer, "add_label_with_icon|big|Pet Combiner|left|3554|\nadd_spacer|small|\nadd_textbox|You Dont Have Pet Battle Combine Now!|left|\nadd_smalltext|You Need this Item For Combine Pet Battle : |left|\nadd_smalltext|- Ice Dragon Hand|left|\nadd_smalltext|- Fiesta Dragon|left|\nadd_button_with_icon|||staticBlueFrame|1378|\nadd_button_with_icon|||staticBlueFrame|1576|\nadd_button_with_icon||END_LIST|noflags|0|0|\nadd_button|combinepet|Combine Now|noflags|0|0|\nend_dialog|cl0se|Close|Update|\n");
				}
				else {
					Player::OnDialogRequest(peer, "add_label_with_icon|big|Pet Battle|left|3554|\nadd_spacer|small|\nadd_textbox|You Have Pet Battle Now!|left|\nadd_smalltext|You Need this Item For Pet Battle : |left|\nadd_smalltext|- Element - Wind|left|\nadd_smalltext|- Element - Fire|left|\nadd_button_with_icon|||staticBlueFrame|6022|\nadd_button_with_icon|||staticBlueFrame|6020|\nadd_button_with_icon||END_LIST|noflags|0|0|\nadd_button|battlepet|Battle Now|noflags|0|0|\nend_dialog|cl0se|Close|Update|\n");
				}
			}
			if (world->items[x + (y * world->width)].foreground == 758) sendRoulete(peer);
			if (world->owner != "" && !isWorldOwner(peer, world))
			{
				if (!isDev(peer))
				{
					if (isWorldAdmin(peer, world))
					{
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
						{
							string ownername = PlayerDB::getProperName(world->owner);
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`2Access Granted`w)", 0, true);
							Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
							return;
						}
					}
					else if (world->isPublic)
					{
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
						{
							string ownername = PlayerDB::getProperName(world->owner);
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`9Open to Public`w)", 0, true);
							Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
							return;
						}
					}
					else if (world->isEvent)
					{
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
						{
							string ownername = PlayerDB::getProperName(world->owner);
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`4No Access`w)", 0, true);
							Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
							return;
						}
						else if (world->items[x + (y * world->width)].foreground != world->interactableid)
						{
							Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
							return;
						}
					}
					else
					{
						if (static_cast<PlayerInfo*>(peer->data)->haveGrowId == false)
						{
							Player::OnTextOverlay(peer, "`#Create `9Grow-ID `#First`9!");
						}
						else
						{
							Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
							return;
						}
					}
				}
				if (tile == 18 && isMod(peer))
				{
					if (isWorldAdmin(peer, world) && !isWorldOwner(peer, world))
					{
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
						{
							string ownername = PlayerDB::getProperName(world->owner);
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`2Access Granted`w)", 0, true);
						}
					}
					else if (world->isPublic && !isWorldOwner(peer, world))
					{
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
						{
							string ownername = PlayerDB::getProperName(world->owner);
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`9Open to Public`w)", 0, true);
						}
					}
					else if (world->isEvent && !isWorldOwner(peer, world))
					{
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
						{
							string ownername = PlayerDB::getProperName(world->owner);
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`4No Access`w)", 0, true);
						}
					}
				}
			}
			if (!isDev(peer))
			{
				if (world->items[x + (y * world->width)].foreground == 6)
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wIt's too strong to break.", 0, true);
					return;
				}
				if (world->items[x + (y * world->width)].foreground == 8 || world->items[x + (y * world->width)].foreground == 7372 || world->items[x + (y * world->width)].foreground == 3760)
				{
					if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 8452)
					{
					}
					else
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wIt's too strong to break.", 0, true);
						return;
					}
				}
				if (tile == 9444)
				{
					if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 2952 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9430 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9448 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9452 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 2592)
					{
					}
					else
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`5This stone is too strong!", 0, true);
						return;
					}
				}
				if (tile == 6 || tile == 3760 || tile == 1000 || tile == 7372 || tile == 1770 || tile == 1832 || tile == 4720)
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wIt's too heavy to place.", 0, true);
					return;
				}
			}
			if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::WEATHER && isWorldOwner(peer, world)) SendWeather(peer, tile, world, x, y);
			if (world->items[x + (y * world->width)].foreground == 10026 || world->items[x + (y * world->width)].foreground == 9474)
			{
				if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 5480)
				{
					Player::OnTextOverlay(peer, "`@You can't break this `4Block `@With `wRayman`@!");
					return;
				}
				if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9430)
				{
					Player::OnTextOverlay(peer, "`@You can't break this `4Block `@With `9Golden Spade`@!");
					return;
				}
				if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9452)
				{
					Player::OnTextOverlay(peer, "`@You can't break this `4Block `@With `#Rainbow Spade`@!");
					return;
				}
				if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9454)
				{
					Player::OnTextOverlay(peer, "`@You can't break this `4Block `@With `4Demon Spade`@!");
					return;
				}
				if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9456)
				{
					Player::OnTextOverlay(peer, "`@You can't break this `4Block `@With `9Golden `4Demon Spade`@!");
					return;
				}
				if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 10390)
				{
					Player::OnTextOverlay(peer, "`@You can't break this `4Block `@With `4Burning Spade`@!");
					return;
				}
			}
			if (world->items[x + (y * world->width)].foreground == 1008)
			{
				if (static_cast<PlayerInfo*>(peer->data)->haveGrowId && static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner || isMod(peer))
				{
					int valgem;
					valgem = rand() % 40;
					std::ifstream ifs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
					std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
					using namespace std::chrono;
					if (static_cast<PlayerInfo*>(peer->data)->lastATM + 1200 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count())
					{
						static_cast<PlayerInfo*>(peer->data)->lastATM = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
					}
					else
					{
						int kiekDar = (static_cast<PlayerInfo*>(peer->data)->lastATM + 1200 - (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count());
						long milli = kiekDar;
						auto hr = milli / 3600000;
						milli = milli - 3600000 * hr;
						auto min = milli / 60000;
						milli = milli - 60000 * min;
						auto sec = milli / 1000;
						Player::OnConsoleMessage(peer, "`9Cooldown `@Please Wait `9" + to_string(sec) + "s. `@To Use ATM!");
						return;
					}
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`^You found `9" + std::to_string(valgem) + " `2Gems`w!", 0, true);
					auto gembux = atoi(content.c_str());
					auto fingembux = gembux + valgem;
					ofstream myfile;
					myfile.open("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
					myfile << fingembux;
					myfile.close();
					auto gemcalc = gembux + valgem;
					Player::OnSetBux(peer, gemcalc, 0);
					auto hi = data.punchX * 32;
					auto hi2 = data.punchY * 32;
					Player::OnParticleEffect(peer, 29, hi, hi2, 0);
				}
				else
				{
					Player::OnConsoleMessage(peer, "`@You don't have access to break this `eATM Machine`@!");
				}
			}
			if (world->items[x + (y * world->width)].foreground == 2946)
			{
				if (getPlyersWorld(peer)->isPublic || isWorldAdmin(peer, world))
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "That area is owned by " + world->owner + "", 0, true);
					return;
				}
			}
			if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::TOGGLE_FOREGROUND || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::CHEMICAL_COMBINER || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::CHEST)
			{
				if (isWorldOwner(peer, world) || world->owner == "" || isMod(peer) || isWorldAdmin(peer, world))
				{
					if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::CHEMICAL_COMBINER)
					{
						if (world->items[x + (y * world->width)].activated)
						{

							SendCombiner(peer, x, y, 1096, 1098, 1828, 4, 4, 6, 1056, true); /*Songpyeon*/
							SendCombiner(peer, x, y, 1056, 1096, 1828, 15, 30, 15, 1804, true); /*Zeus Lightning Bolt*/
							SendCombiner(peer, x, y, 611, 874, 0, 100, 15, 0, 1552, false); /*Pet Bunny Recipe*/
							SendCombiner(peer, x, y, 1056, 1804, 3870, 5, 10, 15, 1824, true); /*AutumnWings*/
							SendCombiner(peer, x, y, 1056, 7058, 10030, 3, 10, 1, 1826, true); /*AutumnBomb*/
							SendCombiner(peer, x, y, 1056, 1804, 10030, 1, 5, 1, 3074, true); /*FloatingLeaf*/
							SendCombiner(peer, x, y, 10322, 10324, 10326, 1, 1, 1, 10328, false); /*Dark Kings Offering*/
							SendCombiner(peer, x, y, 898, 4538, 5018, 2, 1, 1, 5022, false); /*Chicken Plow*/
							SendCombiner(peer, x, y, 2274, 5026, 5028, 1, 5, 20, 5060, false); /*Verdant Gate*/
							SendCombiner(peer, x, y, 2274, 5028, 5024, 1, 5, 20, 5054, false); /*Inferno Gate*/
							SendCombiner(peer, x, y, 2274, 5024, 5030, 1, 5, 20, 5058, false); /*Typhoon Gate*/
							SendCombiner(peer, x, y, 2274, 5030, 5026, 1, 5, 20, 5056, false); /*Tidal Gate*/
							SendCombiner(peer, x, y, 2492, 5028, 5026, 1, 20, 5, 5050, false); /*Earth Asteroid*/
							SendCombiner(peer, x, y, 2492, 5024, 5028, 1, 20, 5, 5046, false); /*Fire Asteroid*/
							SendCombiner(peer, x, y, 2492, 5030, 5024, 1, 20, 5, 5052, false); /*Wind Asteroid*/
							SendCombiner(peer, x, y, 2492, 5026, 5030, 1, 20, 5, 5048, false); /*Water Asteroid*/
							SendCombiner(peer, x, y, 3946, 5060, 5028, 100, 4, 5, 5070, false); /*Crystallized Reality*/
							SendCombiner(peer, x, y, 3838, 5054, 5024, 200, 4, 5, 5072, false); /*Crystallized Wealth*/
							SendCombiner(peer, x, y, 340, 5058, 5030, 200, 4, 5, 5074, false); /*Crystallized Brilliance*/
							SendCombiner(peer, x, y, 2272, 5056, 5026, 30, 4, 5, 5076, false); /*Crystallized Nature*/
							SendCombiner(peer, x, y, 5050, 5048, 5028, 2, 2, 5, 5066, false); /*Ancient Bracket*/
							SendCombiner(peer, x, y, 5046, 5052, 5024, 2, 2, 5, 5062, false); /*Ancient Hinge*/
							SendCombiner(peer, x, y, 5052, 5050, 5030, 2, 2, 5, 5068, false); /*Ancient Lens*/
							SendCombiner(peer, x, y, 5048, 5046, 5026, 2, 2, 5, 5064, false); /*Ancient Pin*/
							SendCombiner(peer, x, y, 5070, 5066, 5064, 1, 2, 5, 5080, false); /*Ancestral Tesseract of Dimensions*/
							SendCombiner(peer, x, y, 5076, 5068, 5066, 1, 2, 5, 5082, false); /*Ancestral Seed of Life*/
							SendCombiner(peer, x, y, 5072, 5064, 5062, 1, 2, 5, 5084, false); /*Ancestral Lens of Riches*/
							SendCombiner(peer, x, y, 5074, 5062, 5068, 1, 2, 5, 5078, false); /*Ancestral Totem of Wisdom*/			
							SendCombiner(peer, x, y, 362, 386, 1458, 1, 200, 1, 1460, false); /*Golden Angel Wings*/
							SendCombiner(peer, x, y, 364, 386, 1458, 1, 200, 1, 1462, false); /*Golden Diaper*/
							SendCombiner(peer, x, y, 1470, 386, 1458, 1, 200, 1, 1466, false); /*Golden Diamond Necklace*/
							SendCombiner(peer, x, y, 366, 386, 1458, 1, 200, 1, 1464, false); /*Golden Heartbow*/
							SendCombiner(peer, x, y, 2388, 386, 1458, 1, 20, 1, 2386, false); /*Heavenly Scythe*/
							SendCombiner(peer, x, y, 2390, 386, 1458, 1, 20, 1, 2392, false); /*Teeny Golden Wings*/
							SendCombiner(peer, x, y, 2384, 386, 1458, 1, 20, 1, 2394, false); /*Golden Love Bug*/
							SendCombiner(peer, x, y, 4412, 386, 1458, 1, 20, 1, 4414, false); /*Golden Pegasus*/
							SendCombiner(peer, x, y, 4416, 386, 1458, 1, 20, 1, 4420, false); /*Golden Heart Glasses*/
							SendCombiner(peer, x, y, 5644, 386, 1458, 1, 20, 1, 5646, false); /*Golden Heart Shirt*/
							SendCombiner(peer, x, y, 5648, 386, 1458, 1, 20, 1, 5650, false); /*Golden Talaria*/
							SendCombiner(peer, x, y, 7826, 386, 1458, 1, 200, 1, 7828, false); /*Golden Heartstaff*/
							SendCombiner(peer, x, y, 7830, 386, 1458, 1, 200, 1, 7832, false); /*Golden Heartsword*/
							SendCombiner(peer, x, y, 7826, 7830, 1458, 1, 1, 1, 7834, false); /*Stained Glass Heartwings*/
							SendCombiner(peer, x, y, 9320, 386, 1458, 1, 200, 1, 9322, false); /*Golden Sunset Cape*/
							SendCombiner(peer, x, y, 9342, 9340, 1458, 1, 1, 1, 9344, false); /*Datemaster's Heart Locket*/
							SendCombiner(peer, x, y, 9324, 386, 1458, 1, 200, 1, 9326, false); /*Golden Heartthrob Helm*/
							SendCombiner(peer, x, y, 9314, 1800, 186, 1, 1, 200, 9316, false); /*Beefy Biceps*/
							SendCombiner(peer, x, y, 1506, 8794, 4406, 1, 1, 1, 9318, false); /*Snuggly Kitty Scarf*/



							UpdateBlockState(peer, x, y, true, world);
							world->items[x + (y * world->width)].activated = false;
						}
						else
						{
							UpdateBlockState(peer, x, y, true, world);
							world->items[x + (y * world->width)].activated = true;
						}
					}
					else
					{
						if (world->items[x + (y * world->width)].activated)
						{
							UpdateBlockState(peer, x, y, true, world);
							world->items[x + (y * world->width)].activated = false;
						}
						else
						{
							UpdateBlockState(peer, x, y, true, world);
							world->items[x + (y * world->width)].activated = true;
						}
					}
				}
			}
			if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3066) {
				if (world->items[x + (y * world->width)].fire) {
					world->items[x + (y * world->width)].fire = false;
					UpdateBlockState(peer, x, y, true, world);
					ENetPeer* net_peer;
					for (net_peer = server->peers; net_peer < &server->peers[server->peerCount]; ++net_peer) {
						if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, net_peer)) {
							Player::OnParticleEffect(net_peer, 149, x * 32, y * 32, 0);
						}
					}
				}
				return;
			}
			if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::PROVIDER) {
				if (world->owner == "" || static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner)) {
					if (calcBanDuration(world->items[x + (y * world->width)].growtime) == 0) {
						int weedmagic = 1;
						if (world->items[x + (y * world->width)].foreground == 872) {
							if (rand() % 100 <= 25) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 874, 2 * weedmagic, 0);
							else DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 874, 1 * weedmagic, 0);
						}

						if (world->items[x + (y * world->width)].foreground == 866) {
							if (rand() % 100 <= 25) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 868, 2 * weedmagic, 0);
							else DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 868, 1 * weedmagic, 0);
						}

						if (world->items[x + (y * world->width)].foreground == 3888) {
							if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3914) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 3890, rand() % 5 + 1 * weedmagic, 0);
							else DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 3890, rand() % 2 + 1 * weedmagic, 0);
						}

						if (world->items[x + (y * world->width)].foreground == 928) {
							vector<int> Dailyb{ 914, 916, 918, 920, 924 };
							const int Index = rand() % Dailyb.size();
							const auto ItemID = Dailyb[Index];
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), ItemID, 1 * weedmagic, 0);
						}

						if (world->items[x + (y * world->width)].foreground == 1044) {
							if (rand() % 100 <= 25) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 868, 2 * weedmagic, 0);
							else DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 868, 1 * weedmagic, 0);
						}

						if (world->items[x + (y * world->width)].foreground == 2798) {
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 822, 1 * weedmagic, 0);
						}

						if (world->items[x + (y * world->width)].foreground == 1008) {
							SendFarmableDrops(peer, 500, x, y);
						}

						if (world->items[x + (y * world->width)].foreground == 1636) {
							vector<int> Dailyb{ 728, 360, 308, 306, 2966, 1646, 3170, 1644, 1642, 3524, 1640, 1638, 2582, 3198, 8838, 6794, 10110 };
							const int Index = rand() % Dailyb.size();
							const auto ItemID = Dailyb[Index];
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), ItemID, 1 * weedmagic, 0);
						}

						if (world->items[x + (y * world->width)].foreground == 3044) {
							vector<int> Dailyb{ 2914, 3012, 3014, 3016, 3018, 5528, 5526 };
							const int Index = rand() % Dailyb.size();
							const auto ItemID = Dailyb[Index];
							if (rand() % 100 <= 25) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), ItemID, 2 * weedmagic, 0);
							else DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), ItemID, 1 * weedmagic, 0);
						}

						if (world->items[x + (y * world->width)].foreground == 6212) {
							vector<int> Dailyb{ 1258, 1260, 1262, 1264, 1266, 1268, 1270, 4308, 4310, 4312, 4314, 4316, 4318 };
							const int Index = rand() % Dailyb.size();
							const auto ItemID = Dailyb[Index];
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), ItemID, 1 * weedmagic, 0);
						}

						if (world->items[x + (y * world->width)].foreground == 6414) {
							vector<int> Dailyb{ 6520, 6538, 6522, 6528, 6540, 6518, 6530, 6524, 6536, 6534, 6532, 6526, 6416 };
							const int Index = rand() % Dailyb.size();
							const auto ItemID = Dailyb[Index];
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), ItemID, 1 * weedmagic, 0);
						}

						if (world->items[x + (y * world->width)].foreground == 5116) {
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5114, 1 * weedmagic, 0);
						}

						if (world->items[x + (y * world->width)].foreground == 1632) {
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 1634, 1 * weedmagic, 0);
						}
						int buvoid = world->items[x + (y * world->width)].foreground;
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
						for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, currentPeer)) {
								auto raw = packPlayerMoving(&data3);
								raw[2] = dicenr;
								raw[3] = dicenr;
								SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
							}
						}
						world->items[x + (y * world->width)].foreground = buvoid;
						PlayerMoving data4;
						data4.packetType = 0x3;
						data4.characterState = 0x0;
						data4.x = x;
						data4.y = y;
						data4.punchX = x;
						data4.punchY = y;
						data4.XSpeed = 0;
						data4.YSpeed = 0;
						data4.netID = -1;
						data4.plantingTree = buvoid;
						for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, currentPeer)) {
								auto raw = packPlayerMoving(&data4);
								raw[2] = dicenr;
								raw[3] = dicenr;
								SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
							}
						}
						world->items[x + (y * world->width)].growtime = (GetCurrentTimeInternalSeconds() + getItemDef(world->items[x + (y * world->width)].foreground).growTime);
					}
				}
			}
			if (isSeed(world->items[x + (y * world->width)].foreground) && calcBanDuration(world->items[x + (y * world->width)].growtime) == 0 && static_cast<PlayerInfo*>(peer->data)->cloth_hand != 3066) {
				if (world->isPublic || isWorldAdmin(peer, world) || isWorldOwner(peer, world) || world->owner == "" || isMod(peer) || !RestrictedArea(peer, world, x, y)) {
					for (ENetPeer* net_peer = server->peers; net_peer < &server->peers[server->peerCount]; ++net_peer) {
						if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, net_peer)) {
							treeModify(net_peer, x, y, static_cast<PlayerInfo*>(peer->data)->netID);
						}
					}
					auto chance = (rand() % 100) + 1;
					int numb = world->items[x + (y * world->width)].fruitcount;
					DropGem(peer, x, y);
					if (chance < 15 && getItemDef(world->items[x + (y * world->width)].foreground).rarity != 999) {
						if (getItemDef(world->items[x + (y * world->width)].foreground - 1).blockType != BlockTypes::CLOTHING) {
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "A " + getItemDef(world->items[x + (y * world->width)].foreground).name + " seed falls out!", 0, true);
							DropItem(peer, -1, x * 32 - (rand() % 8), y * 32 + (rand() % 8), world->items[x + (y * world->width)].foreground, 1, 0);
						}
					}
					if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 6840) {
						auto chance1 = (rand() % 100) + 1;
						if (chance1 <= 30) {
							numb += 1;
							Player::OnParticleEffect(peer, 49, data.punchX * 32, data.punchY * 32, 0);
						}
					}
					int chanceofbuff = 1;
					if (static_cast<PlayerInfo*>(peer->data)->level >= 10) chanceofbuff = 1;
					if (static_cast<PlayerInfo*>(peer->data)->level >= 13) chanceofbuff = 2;
					if (static_cast<PlayerInfo*>(peer->data)->level >= 10 && rand() % 100 <= chanceofbuff) {
						numb += 1;
						Player::OnConsoleMessage(peer, "Harvester bonus extra block drop");
					}
					DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), world->items[x + (y * world->width)].foreground - 1, numb, 0);
					world->items[x + (y * world->width)].spliced = false;
					world->items[x + (y * world->width)].growtime = 0;
					world->items[x + (y * world->width)].fruitcount = 0;
					if (HarvestEvent) {
						SendHarvestFestivalDrop(peer, x, y, getItemDef(world->items[x + (y * world->width)].foreground).rarity);
					}
					if (getItemDef(world->items[x + (y * world->width)].foreground).rarity < 25) {
						SendXP(peer, 1);
					}
					else if (getItemDef(world->items[x + (y * world->width)].foreground).rarity >= 25 && getItemDef(world->items[x + (y * world->width)].foreground).rarity < 40) {
						SendXP(peer, 2);
					}
					else if (getItemDef(world->items[x + (y * world->width)].foreground).rarity >= 40 && getItemDef(world->items[x + (y * world->width)].foreground).rarity < 60) {
						SendXP(peer, 3);
					}
					else if (getItemDef(world->items[x + (y * world->width)].foreground).rarity >= 60 && getItemDef(world->items[x + (y * world->width)].foreground).rarity < 80) {
						SendXP(peer, 4);
					}
					else if (getItemDef(world->items[x + (y * world->width)].foreground).rarity >= 80 && getItemDef(world->items[x + (y * world->width)].foreground).rarity < 100) {
						SendXP(peer, 5);
					}
					else if (getItemDef(world->items[x + (y * world->width)].foreground).rarity >= 100) {
						SendXP(peer, 6);
					}
					world->items[x + (y * world->width)].foreground = 0;
					return;
				}
				return;
			}
			if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9482)
			{
				if (static_cast<PlayerInfo*>(peer->data)->rawName == world->owner && static_cast<PlayerInfo*>(peer->data)->haveGrowId == true || isMod(peer))
				{
					auto xlast = static_cast<PlayerInfo*>(peer->data)->lastPunchX = x;
					auto ylast = static_cast<PlayerInfo*>(peer->data)->lastPunchX = y;
					changetile(peer, xlast, ylast);
					auto hi = static_cast<PlayerInfo*>(peer->data)->lastPunchX;
					auto hi2 = static_cast<PlayerInfo*>(peer->data)->lastPunchY;
					ENetPeer* currentPeer;
					for (currentPeer = server->peers;
						currentPeer < &server->peers[server->peerCount];
						++currentPeer)
					{
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
							continue;
						if (isHere(peer, currentPeer))
						{
							Player::OnParticleEffect(currentPeer, 168, hi, hi2, 0);
						}
					}
				}
			}
			if (!static_cast<PlayerInfo*>(peer->data)->Fishing) break;
		}
	case 32: /*wrench*/
		{
		 	if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK) {
                if (isWorldOwner(peer, world) || isMod(peer) || static_cast<PlayerInfo*>(peer->data)->rawName == world->items[x + (y * world->width)].monitorname) {
                    static_cast<PlayerInfo*>(peer->data)->wrenchedBlockLocation = x + (y * world->width);
                    if (world->items[x + (y * world->width)].foreground == 202 || world->items[x + (y * world->width)].foreground == 204 || world->items[x + (y * world->width)].foreground == 206 || world->items[x + (y * world->width)].foreground == 4994) {
                        string allow_dialog = "\nadd_checkbox|checkbox_public|Allow anyone to Build and Break|0";
                        if (world->items[x + (y * world->width)].opened) {
                            allow_dialog = "\nadd_checkbox|checkbox_public|Allow anyone to Build and Break|1";
                        }
                        Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wEdit Small Lock``|left|202|\nadd_label|small|`wAccess list:``|left\nadd_spacer|small|\nadd_label|small|Currently, you're the only one with access.``|left\nadd_spacer|small|\nadd_player_picker|playerNetID|`wAdd``|" + allow_dialog + "\nadd_checkbox|checkbox_ignore|Ignore empty air|0\nadd_button|recalcLock|`wRe-apply lock``|noflags|0|0|\nend_dialog|lock_edit|Cancel|OK|");
                        return;
                    }
					int ispub = world->isPublic;
					string str = "";
					for (auto i = 0; i < world->accessed.size(); i++) {
						auto st = world->accessed.at(i);
						str += "\nadd_label|small|" + st.substr(st.find("|") + 1, st.length()) + "|left|";
					}
					int muted = world->silence;
					string wlmenu = "";
					if (world->items[x + (y * world->width)].foreground == 4802) {
						string rainbows = "0";
						if (world->rainbow) rainbows = "1";
						if (str == "") {
							wlmenu = "set_default_color|`o\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(getItemDef(world->items[x + (y * world->width)].foreground).id) + "|\nadd_label|small|`wAccess list:``|left\nadd_spacer|small|\nadd_label|small|Currently, you're the only one with access.``|left\nadd_spacer|small|\nadd_player_picker|netid|`wAdd``|\nadd_button|WorldDropPickup|`wEnable/Disable Collecting Items``|\nadd_checkbox|checkbox_public|Allow anyone to Build and Break|" + to_string(ispub) + "\nadd_checkbox|checkbox_disable_music|Disable Custom Music Blocks|0|\nadd_checkbox|checkbox_disable_music_render|Make Custom Music Blocks invisible|\nadd_checkbox|checkbox_rainbow|Enable Rainbows!|" + rainbows + "\nadd_checkbox|checkbox_muted|Silence, Peasants!|" + to_string(muted) + "|noflags|0|0|\nadd_text_input|minimum_entry_level|World Level: |1|3|\nadd_smalltext|Set minimum world entry level.|\nadd_button|changecat|`wCategory: " + world->category + "``|noflags|0|0|\nend_dialog|lock_edit|Cancel|OK|";
						} else {
							wlmenu = "set_default_color|`o\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(getItemDef(world->items[x + (y * world->width)].foreground).id) + "|\nadd_label|small|`wAccess list:``|left\nadd_spacer|small|\nadd_label|small|" + str + "|left\nadd_spacer|small|\nadd_player_picker|netid|`wAdd``|\nadd_button|WorldDropPickup|`wEnable/Disable Collecting Items``|\nadd_checkbox|checkbox_public|Allow anyone to Build and Break|" + to_string(ispub) + "\nadd_checkbox|checkbox_disable_music|Disable Custom Music Blocks|0|\nadd_checkbox|checkbox_disable_music_render|Make Custom Music Blocks invisible|\nadd_checkbox|checkbox_rainbow|Enable Rainbows!|" + rainbows + "\nadd_checkbox|checkbox_muted|Silence, Peasants!|" + to_string(muted) + "|noflags|0|0|\nadd_text_input|minimum_entry_level|World Level: |1|3|\nadd_smalltext|Set minimum world entry level.|\nadd_button|changecat|`wCategory: " + world->category + "``|noflags|0|0|\nend_dialog|lock_edit|Cancel|OK|";
						}
						Player::OnDialogRequest(peer, wlmenu);
					} else {
						if (str == "") {
							wlmenu = "set_default_color|`o\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(getItemDef(world->items[x + (y * world->width)].foreground).id) + "|\nadd_label|small|`wAccess list:``|left\nadd_spacer|small|\nadd_label|small|Currently, you're the only one with access.``|left\nadd_spacer|small|\nadd_player_picker|netid|`wAdd``|\nadd_button|WorldDropPickup|`wEnable/Disable Collecting Items``|\nadd_checkbox|checkbox_public|Allow anyone to Build and Break|" + to_string(ispub) + "\nadd_checkbox|checkbox_disable_music|Disable Custom Music Blocks|0|\nadd_checkbox|checkbox_disable_music_render|Make Custom Music Blocks invisible|noflags|0|0|\nadd_text_input|minimum_entry_level|World Level: |" + to_string(world->entrylevel) + "|3|\nadd_smalltext|Set minimum world entry level.|\nadd_button|changecat|`wCategory: " + world->category + "``|noflags|0|0|\nend_dialog|lock_edit|Cancel|OK|";
						} else {
							wlmenu = "set_default_color|`o\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "`|left|" + to_string(getItemDef(world->items[x + (y * world->width)].foreground).id) + "|\nadd_label|small|`wAccess list:``|left\nadd_spacer|small|\nadd_label|small|" + str + "|left\nadd_spacer|small|\nadd_player_picker|netid|`wAdd``|\nadd_button|WorldDropPickup|`wEnable/Disable Collecting Items``|\nadd_checkbox|checkbox_public|Allow anyone to Build and Break|" + to_string(ispub) + "\nadd_checkbox|checkbox_disable_music|Disable Custom Music Blocks|0|\nadd_checkbox|checkbox_disable_music_render|Make Custom Music Blocks invisible|noflags|0|0|\nadd_text_input|minimum_entry_level|World Level: |" + to_string(world->entrylevel) + "|3|\nadd_smalltext|Set minimum world entry level.|\nadd_button|changecat|`wCategory: " + world->category + "``|noflags|0|0|\nend_dialog|lock_edit|Cancel|OK|";
						}
						Player::OnDialogRequest(peer, wlmenu);
					}
				}
				else
				{
					if (isWorldAdmin(peer, world))
					{
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
						{
							string ownername = PlayerDB::getProperName(world->owner);
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`2Access Granted`w)", 0, true);
							Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
							return;
						}
					}
					else if (world->isPublic)
					{
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
						{
							string ownername = PlayerDB::getProperName(world->owner);
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`9Open to Public`w)", 0, true);
							Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
							return;
						}
					}
					else if (world->isEvent)
					{
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
						{
							string ownername = PlayerDB::getProperName(world->owner);
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`4No Access`w)", 0, true);
							Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
							return;
						}
					}
				}
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 3528 && tile == 32) {
				if (world->owner == "" || ((PlayerInfo*)(peer->data))->rawName == PlayerDB::getProperName(world->owner) || !isDev(peer)) {
					auto targetworld = getPlyersWorld(peer);
					if (targetworld->items[x + (y * targetworld->width)].intdata != 0 && static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
					{
						Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wArt Canvas|left|3528|\nadd_spacer|small|\nadd_textbox|`oThis is a lovely still-life of " + getItemDef(world->items[x + (y * world->width)].intdata).name + "|left|\nadd_item_picker|art_pick|`wErase Painting|Select an item to paint|\nadd_smalltext|`5(Painting costs 2 Paint Bucket of each color)|left|\nadd_text_input|artsign|Signed: |" + getItemDef(world->items[x + (y * world->width)].intdata).name + "|35|\nend_dialog|artupdate|Cancel|Update|");
						pinfo->wrenchedBlockLocation = x + (y * world->width);
					}
					else if (getPlyersWorld(peer)->owner == "" && targetworld->items[x + (y * targetworld->width)].intdata != 0)
					{
						Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wArt Canvas|left|3528|\nadd_spacer|small|\nadd_textbox|`oThis is a lovely still-life of " + getItemDef(world->items[x + (y * world->width)].intdata).name + "|left|\nadd_item_picker|art_pick|`wErase Painting|Select an item to paint|\nadd_smalltext|`5(Painting costs 2 Paint Bucket of each color)|left|\nadd_text_input|artsign|Signed: |" + getItemDef(world->items[x + (y * world->width)].intdata).name + "|35|\nend_dialog|artupdate|Cancel|Update|");
						pinfo->wrenchedBlockLocation = x + (y * world->width);
					}
					else
					{
						Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wArt Canvas|left|3528|\nadd_spacer|small|\nadd_textbox|`oThe canvas is blank.|left|\nadd_item_picker|art_pick|`wPaint Something|Select an item to paint|\nadd_smalltext|`5(Painting costs 2 Paint Bucket of each color)|left|\nadd_text_input|artsign|Signed: |" + getItemDef(world->items[x + (y * world->width)].intdata).name + "|35|\nend_dialog|artupdate|Cancel|Update|");
						pinfo->wrenchedBlockLocation = x + (y * world->width);
					}
					return;
				}
				else
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "That area is owned by " + world->owner + "", 0, true);
					return;
				}
				return;
			}
			if (world->owner == "" || isWorldOwner(peer, world) || pinfo->adminLevel > 6) {
				if (world->items[x + (y * world->width)].foreground == 3794 && tile == 32) {// Made by KangSomay
					Player::OnDialogRequest(peer, "add_label_with_icon|big|`wDisplay Shelf|left|3794|\nadd_spacer|small|\nadd_item_picker|ds1|Item 1: `2" + getItemDef(world->items[x + (y * world->width)].display1).name + "|Select any item to use|\nadd_item_picker|ds2|Item 2: `2" + getItemDef(world->items[x + (y * world->width)].display2).name + "|Select any item to use|\nadd_item_picker|ds3|Item 3: `2" + getItemDef(world->items[x + (y * world->width)].display3).name + "|Select any item to use|\nadd_item_picker|ds4|Item 4: `2" + getItemDef(world->items[x + (y * world->width)].display4).name + "|Select any item to use|\nend_dialog|displayself|cancel|ok|");
					pinfo->wrenchedBlockLocation = x + (y * world->width);



				}
			}
			if (world->items[x + (y * world->width)].foreground == 3818 && tile == 32) {
				if (world->owner == "" || ((PlayerInfo*)(peer->data))->rawName == PlayerDB::getProperName(world->owner)) {
					auto targetworld = getPlyersWorld(peer);
					if (targetworld->items[x + (y * targetworld->width)].intdata != 0 && static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
					{
						Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wEdit Portrait``|left|3818|0|0|\nadd_spacer|small|\nadd_textbox|`oThis is a lovely portrait of a GrowTopian.|left|\nadd_textbox|`oYou'll need 4 Paint Bucket - Varnish to erase this|left|\nadd_text_input|artsign|Signed: |" + getItemDef(world->items[x + (y * world->width)].intdata).name + "|35|left|\nadd_smalltext|`oIf you'd like to touch up the painting slightly. you could change the expression:|left|\nadd_checkbox|unconcerned|Unconcerned|\nadd_checkbox|happy|Happy|\nend_dialog|portrait|Cancel|Okay|");
						pinfo->wrenchedBlockLocation = x + (y * world->width);
					}
					else if (getPlyersWorld(peer)->owner == "" && targetworld->items[x + (y * targetworld->width)].intdata != 0)
					{
						Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wEdit Portrait``|left|3818|0|0|\nadd_spacer|small|\nadd_textbox|`oThis is a lovely portrait of a GrowTopian.|left|\nadd_textbox|`oYou'll need 4 Paint Bucket - Varnish to erase this|left|\nadd_text_input|artsign|Title: |" + getItemDef(world->items[x + (y * world->width)].intdata).name + "|35|left|\nadd_smalltext|`oIf you'd like to touch up the painting slightly. you could change the expression:|left|\nadd_checkbox|unconcerned|Unconcerned|\nadd_checkbox|happy|Happy|\nend_dialog|portrait|Cancel|Okay|");
						pinfo->wrenchedBlockLocation = x + (y * world->width);
					}
					else
					{
						Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wPortrait``|left|3818|0|0|\nadd_spacer|small|\nadd_textbox|`oThe canvas is blank.|left|\nadd_player_picker|addportrait|`wPaint Someone|\nadd_smalltext|`5(Painting costs 2 Paint Bucket of each color)|left|\nend_dialog|portrait|Cancel|Okay|");
						pinfo->wrenchedBlockLocation = x + (y * world->width);
					}
				}
			}
			if (world->owner == "" || isWorldOwner(peer, world) || pinfo->adminLevel > 6) {
				if (world->items[x + (y * world->width)].foreground == 4758 && tile == 32) {
					Player::OnDialogRequest(peer, "add_label_with_icon|big|`wMini-Mod|left|4758|\nadd_spacer|small|\nadd_checkbox|minimod1|Dont allow Drop Item|" + to_string(world->minimod) + "|\nend_dialog|minimod|cancel|ok|");
					pinfo->wrenchedBlockLocation = x + (y * world->width);

				}
			}
			if (world->items[x + (y * world->width)].foreground == 6952)
			{
				if (isWorldOwner(peer, world) || isMod(peer) || world->isPublic || world->owner == "" || isDev(peer))
				{
					auto itemid = 0;
					int x = static_cast<PlayerInfo*>(peer->data)->lastPunchX;
					int y = static_cast<PlayerInfo*>(peer->data)->lastPunchY;
					string autobreakcheck = "";
					string autobreakis = "false";
					auto squaresign = x + (y * 100);
					auto currentworld = static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(squaresign);
					string Sucker = "tesseractmanipulator";
					ifstream fdss(Sucker + "/storeditem/" + currentworld + ".txt");
					fdss >> itemid;
					fdss.close();
					auto autotm = std::experimental::filesystem::exists(Sucker + "/autobreak/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(squaresign) + ".txt");
					if (autotm)
					{
						ifstream basic_ifstream(Sucker + "/autobreak/" + currentworld + ".txt");
						basic_ifstream >> autobreakis;
						basic_ifstream.close();
					}
					if (autobreakis == "true")
					{
						autobreakcheck = "\nadd_checkbox|checkbox_autobreak|`oAuto break to blocks|1|";
					}
					else
					{
						autobreakcheck = "\nadd_checkbox|checkbox_autobreak|`oAuto break to blocks|0|";
					}
					if (itemid >= 1) {
						Player::OnDialogRequest(peer, "set_default_color|\nadd_button|machineactive|`wBreak `2" + getItemDef(itemid).name + "|" + autobreakcheck + "|\nadd_spacer|small|\nadd_button|machineactives|`2Placing|\nadd_spacer|small|\nadd_item_picker|tesseractitem|`6Change item|Choose any item you want to pick|\nend_dialog|tesseractupdate|Close|`wUpdate|");
					}
					Player::OnDialogRequest(peer, "set_default_color|\nadd_label_with_icon|big|`wTesseract Manipulator|left|6952|\nadd_textbox|`oThis machine will break blocks for you! Select one and it will start breaking it immediately! Just make sure to select the right one|left|\nadd_item_picker|tesseractitem|`wTest pick item|Choose any item you want to pick|\nadd_quick_exit|");
				}
			}
			if (world->items[x + (y * world->width)].foreground == 5000) {

				string itemname = getItemDef(world->bgID).name;
				GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\nadd_label_with_icon|big|`wWeather Machine - Background``|left|5000|\nadd_spacer|small|\nadd_textbox|`oYou can scan any Background Block to set it up in your weather machine.|\nadd_item_picker|bg_pick|Item: `2" + itemname + "|Select any Background Block|\nadd_quick_exit|\nend_dialog|bg_weather|Cancel|Okay|"));
				ENetPacket* packet = enet_packet_create(p.data,
					p.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet);
				delete p.data;
				pinfo->wrenchedBlockLocation = x + (y * world->width);

			}
			if (world->items[x + (y * world->width)].foreground == 3832) {
				string stuff_dialog = "set_default_color|`o\nadd_label_with_icon|big|`wWeather Machine - Stuff``|left|3832|\nadd_spacer|small|\nadd_item_picker|stuff_pick|Item: `2" + getItemDef(world->stuffID).name + "|Select any item to rain down|\nadd_text_input|stuff_gravity|Gravity:|" + to_string(world->stuff_gravity) + "|3|\nadd_checkbox|stuff_spin|Spin Items|" + to_string(world->stuff_spin) + "|\nadd_checkbox|stuff_invert|Invert Sky Colors|" + to_string(world->stuff_invert) + "|\nadd_textbox|`oSelect item and click okay to continue!|\nend_dialog|stuff_weather|Cancel|Okay|";

				GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), stuff_dialog));
				ENetPacket* packet = enet_packet_create(p.data,
					p.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet);
				delete p.data;
				pinfo->wrenchedBlockLocation = x + (y * world->width);

			}
			if (world->owner == "" || isWorldOwner(peer, world) || pinfo->adminLevel == 7) {//Made by KangSomay
				if (world->items[x + (y * world->width)].foreground == 5958 && tile == 32) {
					Player::OnDialogRequest(peer, "add_label_with_icon|big|`wEpoch weather machine|left|5958|\nadd_textbox|`oSelect Your Doom:|\nadd_spacer|small|\nadd_checkbox|checkMag|ice|" + to_string(world->ice) + "|\nadd_checkbox|checkMag1|Volcano|" + to_string(world->vol) + "|\nadd_checkbox|checkMag2|Land|" + to_string(world->land) + "|\nend_dialog|mag|cancel|ok|");
					pinfo->wrenchedBlockLocation = x + (y * world->width);



				}
			}
			if (world->owner == "" || isWorldOwner(peer, world) || pinfo->adminLevel == 7) {//Made by KangSomay
				if (world->items[x + (y * world->width)].foreground == 5958 && tile == 32) {
					Player::OnDialogRequest(peer, "add_label_with_icon|big|`wEpoch weather machine|left|5958|\nadd_textbox|`oSelect Your Doom:|\nadd_spacer|small|\nadd_checkbox|checkMag|ice|" + to_string(world->ice) + "|\nadd_checkbox|checkMag1|Volcano|" + to_string(world->vol) + "|\nadd_checkbox|checkMag2|Land|" + to_string(world->land) + "|\nend_dialog|mag|cancel|ok|");
					pinfo->wrenchedBlockLocation = x + (y * world->width);



				}
			}
			// VIP ENTRANCE DIALOG 
			if (world->name != "ADMIN") {
				if (world->owner != "") {

					string name = ((PlayerInfo*)(peer->data))->rawName;
					if (((PlayerInfo*)(peer->data))->rawName == world->owner || (find(world->viplist.begin(), world->viplist.end(), name) != world->viplist.end())) {
						if (((PlayerInfo*)(peer->data))->rawName == "") return;

						if (tile == 18 && world->items[x + (y * world->width)].foreground == 3798 && (find(world->viplist.begin(), world->viplist.end(), name) != world->viplist.end())) {
							return;
						}
						if (world->items[x + (y * world->width)].foreground == 3798 && tile == 32) {
							((PlayerInfo*)(peer->data))->lastPunchX = x;
							((PlayerInfo*)(peer->data))->lastPunchY = y;
							if ((find(world->viplist.begin(), world->viplist.end(), name) != world->viplist.end())) {
								Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`w" + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|small|\nadd_textbox|`oThis lock is owned by `w" + world->owner + "`o, but i have access on it.|small|\nend_dialog|RemoveMyVipAccess|Cancel|`wRemove my Access|");
								return;
							}
						}
						string offlinelist = ""; string offname = ""; int ischecked;
						for (std::vector<string>::const_iterator i = world->viplist.begin(); i != world->viplist.end(); ++i) {
							offname = *i;
							offlinelist += "\nadd_checkbox|VipAccess|" + offname + "|1|\n";
							((PlayerInfo*)(peer->data))->lastPunchX = x;
							((PlayerInfo*)(peer->data))->lastPunchY = y;
						}
						if (world->items[x + (y * world->width)].VipPublic == true) {
							ischecked = 1;
						}
						else {
							ischecked = 0;
						}
						string VipPublic = to_string(ischecked);
						if (world->items[x + (y * world->width)].foreground == 3798) {
							if (tile == 32) {
								if (world->viplist.size() == 0) {
									((PlayerInfo*)(peer->data))->lastPunchX = x;
									((PlayerInfo*)(peer->data))->lastPunchY = y;
									Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wEdit VIP Entrance|left|3798|\nadd_label|small|`wVip list:``|left\nadd_spacer|small|\nadd_label|small|`oNobody!``|left\nadd_spacer|small|\nadd_player_picker|VipAcc|`wAdd``|\nadd_checkbox|vip_public|Allow Anyone to enter|" + VipPublic + "|\nend_dialog|vip_entrance|Cancel|OK|");
								}
								else {
									((PlayerInfo*)(peer->data))->lastPunchX = x;
									((PlayerInfo*)(peer->data))->lastPunchY = y;
									Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wEdit VIP Entrance|left|3798|\nadd_label|small|`wVip list:``|left|\nadd_spacer|small|" + offlinelist + "nadd_spacer|small|\nadd_player_picker|VipAcc|`wAdd``|\nadd_checkbox|vip_public|Allow Anyone to enter|" + VipPublic + "|\nend_dialog|vip_entrance|Cancel|OK|");
								}
							}
						}
					}
				}
			}
			if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::SUCKER) /*magplant gaia ut*/
			{
				if (world->isPublic) return; /*Item suckers cannot be used in public worlds*/
				auto squaresign = x + (y * 100);
				auto currentworld = static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(squaresign);
				string Sucker = "";
				if (world->items[x + (y * world->width)].foreground == 5638)
				{
					Sucker = "magplant";
					static_cast<PlayerInfo*>(peer->data)->suckername = "magplant";
					static_cast<PlayerInfo*>(peer->data)->suckerid = 5638;
				}
				if (world->items[x + (y * world->width)].foreground == 6946)
				{
					Sucker = "gaiabeacon";
					static_cast<PlayerInfo*>(peer->data)->suckername = "gaiabeacon";
					static_cast<PlayerInfo*>(peer->data)->suckerid = 6946;
				}
				if (world->items[x + (y * world->width)].foreground == 6948)
				{
					Sucker = "unstabletesseract";
					static_cast<PlayerInfo*>(peer->data)->suckername = "unstabletesseract";
					static_cast<PlayerInfo*>(peer->data)->suckerid = 6948;
				}
				static_cast<PlayerInfo*>(peer->data)->lastPunchX = x;
				static_cast<PlayerInfo*>(peer->data)->lastPunchY = y;
				if (static_cast<PlayerInfo*>(peer->data)->rawName != getPlyersWorld(peer)->owner && !isDev(peer)) /*Make sure the player has rights to use item suckers*/
				{
					string publicremoteis = "false";
					auto remmag = std::experimental::filesystem::exists(Sucker + "/publicremote/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(squaresign) + ".txt"); /*Check if item sucker data file exists*/
					if (remmag)
					{
						ifstream fdss3(Sucker + "/publicremote/" + currentworld + ".txt"); /*Read the storeditem counts*/
						fdss3 >> publicremoteis;
						fdss3.close();
					}
					if (publicremoteis == "true")
					{
						auto itemid = 0;
						ifstream fdss(Sucker + "/storeditem/" + currentworld + ".txt"); /*Read the storeditem IDS*/
						fdss >> itemid;
						fdss.close();
						auto count = 0;
						ifstream fdss3(Sucker + "/count/" + currentworld + ".txt"); /*Read the storeditem counts*/
						fdss3 >> count;
						fdss3.close();
						string label = "`6The machine is currently empty!";
						string RemoteDialog = "";
						if (count >= 1)
						{
							RemoteDialog = "\nadd_textbox|`oUse the " + getItemDef(world->items[x + (y * world->width)].foreground).name + " Remote to build `2" + getItemDef(itemid).name + " `odirectly from the " + getItemDef(world->items[x + (y * world->width)].foreground).name + "'s storage.|\nadd_button|getremote|`oGet Remote|";
							label = "`oThe machine contains " + to_string(count) + " `2" + getItemDef(itemid).name + ""; /*The message if something exists in item sucker*/
						}
						Player::OnDialogRequest(peer, "set_default_color|\nadd_label_with_icon|big|`w" + getItemDef(world->items[x + (y * world->width)].foreground).name + "|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_spacer|small|\nadd_label_with_icon|small|`5" + getItemDef(itemid).name + "|left|" + to_string(itemid) + "|\nadd_textbox|" + label + "|" + RemoteDialog + "|\nend_dialog|magplantupdate|Close||");
					}
					else
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "This magplant public mode is disabled!", 0, false);
					}
					return;
				}
				auto ismag = std::experimental::filesystem::exists(Sucker + "/storeditem/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(squaresign) + ".txt"); /*Check if item sucker data file exists*/
				if (ismag)
				{
					auto itemid = 0;
					ifstream fdss(Sucker + "/storeditem/" + currentworld + ".txt"); /*Read the storeditem IDS*/
					fdss >> itemid;
					fdss.close();
					auto count = 0;
					ifstream fdss3(Sucker + "/count/" + currentworld + ".txt"); /*Read the storeditem counts*/
					fdss3 >> count;
					fdss3.close();
					string label = "`6The machine is currently empty!"; /*The message if nothing is in item sucker*/
					string RemoteDialog = "";
					string publicremotecheck = "";
					bool Farmable = false;
					if (itemid == 7382 || itemid == 4762 || itemid == 10024 || itemid == 9468 || itemid == 9460 || itemid == 10028 || itemid == 340 || itemid == 954 || itemid == 5666) Farmable = true;
					if (Sucker == "magplant" && getItemDef(itemid).blockType == BlockTypes::FOREGROUND || Sucker == "magplant" && Farmable || Sucker == "magplant" && getItemDef(itemid).blockType == BlockTypes::BACKGROUND || Sucker == "magplant" && getItemDef(itemid).blockType == BlockTypes::GROUND_BLOCK)
					{
						string publicremoteis = "false";
						auto remmag = std::experimental::filesystem::exists(Sucker + "/publicremote/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(squaresign) + ".txt"); /*Check if item sucker data file exists*/
						if (remmag)
						{
							ifstream basic_ifstream(Sucker + "/publicremote/" + currentworld + ".txt"); /*Read the storeditem counts*/
							basic_ifstream >> publicremoteis;
							basic_ifstream.close();
						}
						if (publicremoteis == "true")
						{
							publicremotecheck = "\nadd_checkbox|checkbox_publicremote|`oAllow visitors to take remote|1|";
						}
						else
						{
							publicremotecheck = "\nadd_checkbox|checkbox_publicremote|`oAllow visitors to take remote|0|";
						}
						RemoteDialog = "\nadd_textbox|`oUse the " + getItemDef(world->items[x + (y * world->width)].foreground).name + " Remote to build `2" + getItemDef(itemid).name + " `odirectly from the " + getItemDef(world->items[x + (y * world->width)].foreground).name + "'s storage.|\nadd_button|getremote|`oGet Remote|";
					}
					if (count >= 1)
					{
						label = "`oThe machine contains " + to_string(count) + " `2" + getItemDef(itemid).name + ""; /*The message if something exists in item sucker*/
						Player::OnDialogRequest(peer, "set_default_color|\nadd_label_with_icon|big|`w" + getItemDef(world->items[x + (y * world->width)].foreground).name + "|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_spacer|small|\nadd_label_with_icon|small|`5" + getItemDef(itemid).name + "|left|" + to_string(itemid) + "|\nadd_textbox|" + label + "|\nadd_button|retrieveitem|`oRetrieve Items|" + RemoteDialog + "|" + publicremotecheck + "|\nend_dialog|magplantupdate|Close|`wUpdate|");
					}
					else
					{
						Player::OnDialogRequest(peer, "set_default_color|\nadd_label_with_icon|big|`w" + getItemDef(world->items[x + (y * world->width)].foreground).name + "|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_spacer|small|\nadd_label_with_icon|small|`5" + getItemDef(itemid).name + "|left|" + to_string(itemid) + "|\nadd_textbox|" + label + "|\nadd_item_picker|magplantitem|Change Item|Choose an item to put in the " + getItemDef(world->items[x + (y * world->width)].foreground).name + "!|" + publicremotecheck + "|\nend_dialog|magplantupdate|Close|`wUpdate|");
					}
				}
				else
				{
					Player::OnDialogRequest(peer, "set_default_color|\nadd_label_with_icon|big|`w" + getItemDef(world->items[x + (y * world->width)].foreground).name + "|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_spacer|small|\nadd_textbox|`6The machine is empty.|\nadd_item_picker|magplantitem|Choose Item|Choose an item to put in the " + getItemDef(world->items[x + (y * world->width)].foreground).name + "!|\nend_dialog|magplant|Close||");
				}
				return;
			}
			string gay = world->items[x + (y * world->width)].text;
			int gay2 = world->items[x + (y * world->width)].foreground;
			if (world->items[x + (y * world->width)].foreground == 4722)
			{
				if (world->owner != "") {
					if (((PlayerInfo*)(peer->data))->rawName == world->owner) {
						if (tile == 32) {
							((PlayerInfo*)(peer->data))->wrenchx = x;
							((PlayerInfo*)(peer->data))->wrenchy = y;
							GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(gay2) + "|\n\nadd_text_input|ch3|Adventure Message:|" + gay + "|100|\nembed_data|tilex|" + std::to_string(((PlayerInfo*)(peer->data))->wrenchx) + "\nembed_data|tiley|" + std::to_string(((PlayerInfo*)(peer->data))->wrenchy) + "\nend_dialog|sign_edit|Cancel|OK|"));
							ENetPacket* packet = enet_packet_create(p.data,
								p.len,
								ENET_PACKET_FLAG_RELIABLE);
							enet_peer_send(peer, 0, packet);
							delete p.data;
						}
					}
				}
			}
			if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::DOOR || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::PORTAL) {
				if (isWorldOwner(peer, world) || isWorldAdmin(peer, world) || isMod(peer) || world->owner == "" || !RestrictedArea(peer, world, x, y)) {
					static_cast<PlayerInfo*>(peer->data)->wrenchsession = x + (y * world->width);
					auto item = world->items[x + (y * world->width)];
					string DestWorldDialog = world->items[x + (y * world->width)].destWorld;
					if (world->items[x + (y * world->width)].destId != "") {
						DestWorldDialog += ":" + world->items[x + (y * world->width)].destId;
					}
					string IdDialog = "\nadd_text_input|door_id|ID|" + world->items[x + (y * world->width)].currId + "|11|\nadd_smalltext|Set a unique `2ID`` to target this door as a Destination from another!|left|";
					if (world->items[x + (y * world->width)].foreground == 762) {
						IdDialog = "\nadd_text_input|door_id|Password|" + world->items[x + (y * world->width)].password + "|23|";
					}
					Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(item.foreground) + "|\nadd_text_input|door_name|Label|" + world->items[x + (y * world->width)].label + "|100|\nadd_text_input|door_target|Destination|" + DestWorldDialog + "|24|\nadd_smalltext|Enter a Destination in this format: `2WORLDNAME:ID``|left|\nadd_smalltext|Leave `2WORLDNAME`` blank (:ID) to go to the door with `2ID`` in the `2Current World``.|left|" + IdDialog + "\nend_dialog|door_edit|Cancel|OK|");
				}
				return;
			}
			if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::SIGN || world->items[x + (y * world->width)].foreground == 6214 || world->items[x + (y * world->width)].foreground == 1420) {
				if (world->owner == "" || isWorldOwner(peer, world) || isWorldAdmin(peer, world) || isMod(peer) || !RestrictedArea(peer, world, x, y)) {
					auto signtext = world->items[x + (y * world->width)].sign;
					static_cast<PlayerInfo*>(peer->data)->wrenchedBlockLocation = x + (y * world->width);
					if (world->items[x + (y * world->width)].foreground == 6214 || world->items[x + (y * world->width)].foreground == 1420) {
						Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_textbox|To dress, select a clothing item then use on the mannequin. To remove clothes, punch it or select which item to remove.<CR><CR>It will go into your backpack if you have room.|\nadd_textbox|<CR><CR>What would you like to write on its sign?``|left|\nadd_text_input|sign_textas||" + signtext + "|128|\nend_dialog|mannequin_edit|Cancel|OK|");
						return;
					}
					Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_textbox|What would you like to write on this sign?``|left|\nadd_text_input|signtextas||" + signtext + "|128|\nend_dialog|editsign|Cancel|OK|");
				}
				return;
			}
			if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::GATEWAY) {
				if (isWorldOwner(peer, world) || world->owner == "" || isWorldAdmin(peer, world) || isMod(peer) || !RestrictedArea(peer, world, x, y)) {
					if (world->owner == "") {
						Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(getItemDef(world->items[x + (y * world->width)].foreground).id) + "|\nadd_textbox|This object has additional properties to edit if in a locked area.|left|\nend_dialog|gateway_edit|Cancel|OK|");
						return;
					}
					static_cast<PlayerInfo*>(peer->data)->wrenchx = x;
					static_cast<PlayerInfo*>(peer->data)->wrenchy = y;
					if (!world->items[x + (y * world->width)].opened) {
						Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(getItemDef(world->items[x + (y * world->width)].foreground).id) + "|\nadd_checkbox|checkbox_public|Is open to public|0\nend_dialog|gateway_edit|Cancel|OK|");
					}
					else {
						Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(getItemDef(world->items[x + (y * world->width)].foreground).id) + "|\nadd_checkbox|checkbox_public|Is open to public|1\nend_dialog|gateway_edit|Cancel|OK|");
					}
				}
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 9288)
			{
				Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wThe Underground Trader``|left|9288|0|0|\n\nadd_spacer|small|\nadd_textbox|`oWelcome Traveler! Here you can exchange `bDark Fragments `oInto `9Powerful `oItems Or Blocks! Click `^View Offers `oTo See!|\n\nadd_spacer|small|\nadd_button|undergroundtrader|`9View Offers|0|0|\nadd_quick_exit|");
				
			}
			if (tile == 32 || tile == 18) {
				if (world->items[x + (y * world->width)].foreground == 1790) {
					if (((PlayerInfo*)(peer->data))->haveGrowId == false) { // fix growid
						sendConsoleMsg(peer, "Create a growid first!");
					}
					else
						if (((PlayerInfo*)(peer->data))->lstep == 0) {
							string ownername = world->owner;

							GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`9The Legendary Wizard!`|left|1790|\nadd_label|small|`oGreetings, traveler! I am the Legendary Wizard. Sadly We Don't Provide Titles For Free!Complete A Quest To Get Them!``|left|4|\n\nadd_spacer|small|\nadd_button|lfire1|`oQuest For Fire|\nadd_button|lbots1|`oQuest For Steel|\nadd_button|lwings1|`oQuest For Heaven|\nadd_button|lkatanas1|`oQuest For Blade|\nadd_button|lcandours1|`oQuest For Candour|\nadd_button|ldwings1|`oQuest For Sky|0|\nadd_spacer|small|\nadd_quick_exit|\nend_dialog|noty|No Thanks||gazette||"));
							ENetPacket* packet = enet_packet_create(p.data,
								p.len,
								ENET_PACKET_FLAG_RELIABLE);
							enet_peer_send(peer, 0, packet);

							//enet_host_flush(server);
							delete p.data;
						}
						else
							if (((PlayerInfo*)(peer->data))->lstep == 5 & ((PlayerInfo*)(peer->data))->lprogress == 5) {
								string ownername = world->owner;

								GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`9Quest For Candour``|left|1790|\nadd_label|small|`o(Step 5/5)``|left|4|\n\nadd_spacer|small|\nadd_label|small|`oI challenge you to show me the `2Legendary Orb!``|left|4|\n\nadd_spacer|small|\nadd_button|lcandour6|`oShow The Legendary Orb!``|0|0|\nadd_quick_exit|\nend_dialog|noty|Give up on quest!|"));
								ENetPacket* packet = enet_packet_create(p.data,
									p.len,
									ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(peer, 0, packet);
								delete p.data;
							}
							else
								if (((PlayerInfo*)(peer->data))->lstep == 5 & ((PlayerInfo*)(peer->data))->lprogress == 4) {
									string ownername = world->owner;

									GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`9Quest For Candour``|left|1790|\nadd_label|small|`o(Step 4/5)``|left|4|\n\nadd_spacer|small|\nadd_label|small|`oI challenge you to bring me `2200 Chandeliers!``|left|4|\n\nadd_spacer|small|\nadd_button|lcandour4|`oDeliver The Chandeliers!``|0|0|\nadd_quick_exit|\nend_dialog|noty|Give up on quest!|"));
									ENetPacket* packet = enet_packet_create(p.data,
										p.len,
										ENET_PACKET_FLAG_RELIABLE);
									enet_peer_send(peer, 0, packet);
									delete p.data;
								}
								else
									if (((PlayerInfo*)(peer->data))->lstep == 5 & ((PlayerInfo*)(peer->data))->lprogress == 3) {
										string ownername = world->owner;

										GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`9Quest For Candour``|left|1790|\nadd_label|small|`o(Step 3/5)``|left|4|\n\nadd_spacer|small|\nadd_label|small|`oI challenge you to bring me `2200 Dirt Seeds!``|left|4|\n\nadd_spacer|small|\nadd_button|lcandour3|`oDeliver Dirt Seeds!``|0|0|\nadd_quick_exit|\nend_dialog|noty|Give up on quest!|"));
										ENetPacket* packet = enet_packet_create(p.data,
											p.len,
											ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send(peer, 0, packet);
										delete p.data;
									}
									else
										if (((PlayerInfo*)(peer->data))->lstep == 5 & ((PlayerInfo*)(peer->data))->lprogress == 2) {
											string ownername = world->owner;

											GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`9Quest For Candour``|left|1790|\nadd_label|small|`o(Step 2/5)``|left|4|\n\nadd_spacer|small|\nadd_label|small|`oI challenge you to bring me `250 World Locks!``|left|4|\n\nadd_spacer|small|\nadd_button|lcandour2|`oDeliver The World Locks!``|0|0|\nadd_quick_exit|\nend_dialog|noty|Give up on quest!|"));
											ENetPacket* packet = enet_packet_create(p.data,
												p.len,
												ENET_PACKET_FLAG_RELIABLE);
											enet_peer_send(peer, 0, packet);
											delete p.data;
										}
										else
											if (((PlayerInfo*)(peer->data))->lstep == 5 & ((PlayerInfo*)(peer->data))->lprogress == 1) {
												string ownername = world->owner;

												GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`9Quest For Candour``|left|1790|\nadd_label|small|`o(Step 1/5)``|left|4|\n\nadd_spacer|small|\nadd_label|small|`oI challenge you to bring me `2 Rayman's Fist!``|left|4|\n\nadd_spacer|small|\nadd_button|lcandour1|`oDeliver 1 Rayman's fist!``|0|0|\nadd_quick_exit|\nend_dialog|noty|Give up on quest!|"));
												ENetPacket* packet = enet_packet_create(p.data,
													p.len,
													ENET_PACKET_FLAG_RELIABLE);
												enet_peer_send(peer, 0, packet);
												delete p.data;
											}
											else
												if (((PlayerInfo*)(peer->data))->lstep == 4 & ((PlayerInfo*)(peer->data))->lprogress == 5) {
													string ownername = world->owner;

													GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`9Quest For Blade``|left|1790|\nadd_label|small|`o(Step 5/5)``|left|4|\n\nadd_spacer|small|\nadd_label|small|`oI challenge you to show me the `2Legendary Orb!``|left|4|\n\nadd_spacer|small|\nadd_button|lkatana6|`oShow The Legendary Orb!``|0|0|\nadd_quick_exit|\nend_dialog|noty|Give up on quest!|"));
													ENetPacket* packet = enet_packet_create(p.data,
														p.len,
														ENET_PACKET_FLAG_RELIABLE);
													enet_peer_send(peer, 0, packet);
													delete p.data;
												}
												else
													if (((PlayerInfo*)(peer->data))->lstep == 4 & ((PlayerInfo*)(peer->data))->lprogress == 4) {
														string ownername = world->owner;

														GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`9Quest For Blade``|left|1790|\nadd_label|small|`o(Step 4/5)``|left|4|\n\nadd_spacer|small|\nadd_label|small|`oI challenge you to bring me `2200 Chandeliers!``|left|4|\n\nadd_spacer|small|\nadd_button|lkatana4|`oDeliver The Chandeliers!``|0|0|\nadd_quick_exit|\nend_dialog|noty|Give up on quest!|"));
														ENetPacket* packet = enet_packet_create(p.data,
															p.len,
															ENET_PACKET_FLAG_RELIABLE);
														enet_peer_send(peer, 0, packet);
														delete p.data;
													}
													else
														if (((PlayerInfo*)(peer->data))->lstep == 4 & ((PlayerInfo*)(peer->data))->lprogress == 3) {
															string ownername = world->owner;

															GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`9Quest For Blade``|left|1790|\nadd_label|small|`o(Step 3/5)``|left|4|\n\nadd_spacer|small|\nadd_label|small|`oI challenge you to bring me `2200 Dirt Seeds!``|left|4|\n\nadd_spacer|small|\nadd_button|lkatana3|`oDeliver Dirt Seeds!``|0|0|\nadd_quick_exit|\nend_dialog|noty|Give up on quest!|"));
															ENetPacket* packet = enet_packet_create(p.data,
																p.len,
																ENET_PACKET_FLAG_RELIABLE);
															enet_peer_send(peer, 0, packet);
															delete p.data;
														}
														else
															if (((PlayerInfo*)(peer->data))->lstep == 4 & ((PlayerInfo*)(peer->data))->lprogress == 2) {
																string ownername = world->owner;

																GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`9Quest For Blade``|left|1790|\nadd_label|small|`o(Step 2/5)``|left|4|\n\nadd_spacer|small|\nadd_label|small|`oI challenge you to bring me `250 World Locks!``|left|4|\n\nadd_spacer|small|\nadd_button|lkatana2|`oDeliver The World Locks!``|0|0|\nadd_quick_exit|\nend_dialog|noty|Give up on quest!|"));
																ENetPacket* packet = enet_packet_create(p.data,
																	p.len,
																	ENET_PACKET_FLAG_RELIABLE);
																enet_peer_send(peer, 0, packet);
																delete p.data;
															}
															else
																if (((PlayerInfo*)(peer->data))->lstep == 4 & ((PlayerInfo*)(peer->data))->lprogress == 1) {
																	string ownername = world->owner;

																	GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`9Quest For Blade``|left|1790|\nadd_label|small|`o(Step 1/5)``|left|4|\n\nadd_spacer|small|\nadd_label|small|`oI challenge you to bring me `2 Rayman's Fist!``|left|4|\n\nadd_spacer|small|\nadd_button|lkatana1|`oDeliver 1 Rayman's fist!``|0|0|\nadd_quick_exit|\nend_dialog|noty|Give up on quest!|"));
																	ENetPacket* packet = enet_packet_create(p.data,
																		p.len,
																		ENET_PACKET_FLAG_RELIABLE);
																	enet_peer_send(peer, 0, packet);
																	delete p.data;
																}
																else
																	if (((PlayerInfo*)(peer->data))->lstep == 3 & ((PlayerInfo*)(peer->data))->lprogress == 5) {
																		string ownername = world->owner;

																		GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`9Quest For Heaven``|left|1790|\nadd_label|small|`o(Step 5/5)``|left|4|\n\nadd_spacer|small|\nadd_label|small|`oI challenge you to show me the `2Legendary Orb!``|left|4|\n\nadd_spacer|small|\nadd_button|lwing6|`oShow The Legendary Orb!``|0|0|\nadd_quick_exit|\nend_dialog|noty|Give up on quest!|"));
																		ENetPacket* packet = enet_packet_create(p.data,
																			p.len,
																			ENET_PACKET_FLAG_RELIABLE);
																		enet_peer_send(peer, 0, packet);
																		delete p.data;
																	}
																	else
																		if (((PlayerInfo*)(peer->data))->lstep == 3 & ((PlayerInfo*)(peer->data))->lprogress == 4) {
																			string ownername = world->owner;

																			GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`9Quest For Heaven``|left|1790|\nadd_label|small|`o(Step 4/5)``|left|4|\n\nadd_spacer|small|\nadd_label|small|`oI challenge you to bring me `2200 Chandeliers!``|left|4|\n\nadd_spacer|small|\nadd_button|lwing4|`oDeliver The Chandeliers!``|0|0|\nadd_quick_exit|\nend_dialog|noty|Give up on quest!|"));
																			ENetPacket* packet = enet_packet_create(p.data,
																				p.len,
																				ENET_PACKET_FLAG_RELIABLE);
																			enet_peer_send(peer, 0, packet);
																			delete p.data;
																		}
																		else
																			if (((PlayerInfo*)(peer->data))->lstep == 3 & ((PlayerInfo*)(peer->data))->lprogress == 3) {
																				string ownername = world->owner;

																				GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`9Quest For Heaven``|left|1790|\nadd_label|small|`o(Step 3/5)``|left|4|\n\nadd_spacer|small|\nadd_label|small|`oI challenge you to bring me `2200 Dirt Seeds!``|left|4|\n\nadd_spacer|small|\nadd_button|lwing3|`oDeliver Dirt Seeds!``|0|0|\nadd_quick_exit|\nend_dialog|noty|Give up on quest!|"));
																				ENetPacket* packet = enet_packet_create(p.data,
																					p.len,
																					ENET_PACKET_FLAG_RELIABLE);
																				enet_peer_send(peer, 0, packet);
																				delete p.data;
																			}
																			else
																				if (((PlayerInfo*)(peer->data))->lstep == 3 & ((PlayerInfo*)(peer->data))->lprogress == 2) {
																					string ownername = world->owner;

																					GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`9Quest For Heaven``|left|1790|\nadd_label|small|`o(Step 2/5)``|left|4|\n\nadd_spacer|small|\nadd_label|small|`oI challenge you to bring me `250 World Locks!``|left|4|\n\nadd_spacer|small|\nadd_button|lwing2|`oDeliver The World Locks!``|0|0|\nadd_quick_exit|\nend_dialog|noty|Give up on quest!|"));
																					ENetPacket* packet = enet_packet_create(p.data,
																						p.len,
																						ENET_PACKET_FLAG_RELIABLE);
																					enet_peer_send(peer, 0, packet);
																					delete p.data;
																				}
																				else
																					if (((PlayerInfo*)(peer->data))->lstep == 3 & ((PlayerInfo*)(peer->data))->lprogress == 1) {
																						string ownername = world->owner;

																						GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`9Quest For Heaven``|left|1790|\nadd_label|small|`o(Step 1/5)``|left|4|\n\nadd_spacer|small|\nadd_label|small|`oI challenge you to bring me `2 Rayman's Fist!``|left|4|\n\nadd_spacer|small|\nadd_button|lwing1|`oDeliver 1 Rayman's fist!``|0|0|\nadd_quick_exit|\nend_dialog|noty|Give up on quest!|"));
																						ENetPacket* packet = enet_packet_create(p.data,
																							p.len,
																							ENET_PACKET_FLAG_RELIABLE);
																						enet_peer_send(peer, 0, packet);
																						delete p.data;
																					}
																					else
																						if (((PlayerInfo*)(peer->data))->lstep == 2 & ((PlayerInfo*)(peer->data))->lprogress == 1) {
																							string ownername = world->owner;

																							GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`9Quest For Bot``|left|1790|\nadd_label|small|`o(Step 1/5)``|left|4|\n\nadd_spacer|small|\nadd_label|small|`oI challenge you to bring me `2 Rayman's Fist!``|left|4|\n\nadd_spacer|small|\nadd_button|lbot1|`oDeliver 1 Rayman's fist!``|0|0|\nadd_quick_exit|\nend_dialog|noty|Give up on quest!|"));
																							ENetPacket* packet = enet_packet_create(p.data,
																								p.len,
																								ENET_PACKET_FLAG_RELIABLE);
																							enet_peer_send(peer, 0, packet);
																							delete p.data;
																						}
																						else
																							if (((PlayerInfo*)(peer->data))->lstep == 2 & ((PlayerInfo*)(peer->data))->lprogress == 2) {
																								string ownername = world->owner;

																								GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`9Quest For Bot``|left|1790|\nadd_label|small|`o(Step 2/5)``|left|4|\n\nadd_spacer|small|\nadd_label|small|`oI challenge you to bring me `250 World Locks!``|left|4|\n\nadd_spacer|small|\nadd_button|lbot2|`oDeliver The World Locks!``|0|0|\nadd_quick_exit|\nend_dialog|noty|Give up on quest!|"));
																								ENetPacket* packet = enet_packet_create(p.data,
																									p.len,
																									ENET_PACKET_FLAG_RELIABLE);
																								enet_peer_send(peer, 0, packet);
																								delete p.data;
																							}
																							else
																								if (((PlayerInfo*)(peer->data))->lstep == 2 & ((PlayerInfo*)(peer->data))->lprogress == 3) {
																									string ownername = world->owner;

																									GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`9Quest For Bot``|left|1790|\nadd_label|small|`o(Step 3/5)``|left|4|\n\nadd_spacer|small|\nadd_label|small|`oI challenge you to bring me `2200 Dirt Seeds!``|left|4|\n\nadd_spacer|small|\nadd_button|lbot3|`oDeliver The Dirt Seeds!``|0|0|\nadd_quick_exit|\nend_dialog|noty|Give up on quest!|"));
																									ENetPacket* packet = enet_packet_create(p.data,
																										p.len,
																										ENET_PACKET_FLAG_RELIABLE);
																									enet_peer_send(peer, 0, packet);
																									delete p.data;
																								}
																								else
																									if (((PlayerInfo*)(peer->data))->lstep == 2 & ((PlayerInfo*)(peer->data))->lprogress == 4) {
																										string ownername = world->owner;

																										GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`9Quest For Bot``|left|1790|\nadd_label|small|`o(Step 4/5)``|left|4|\n\nadd_spacer|small|\nadd_label|small|`oI challenge you to bring me `2200 Chandeliers!``|left|4|\n\nadd_spacer|small|\nadd_button|lbot4|`oDeliver The Chandeliers!``|0|0|\nadd_quick_exit|\nend_dialog|noty|Give up on quest!|"));
																										ENetPacket* packet = enet_packet_create(p.data,
																											p.len,
																											ENET_PACKET_FLAG_RELIABLE);
																										enet_peer_send(peer, 0, packet);
																										delete p.data;
																									}
																									else
																										if (((PlayerInfo*)(peer->data))->lstep == 2 & ((PlayerInfo*)(peer->data))->lprogress == 5) {
																											string ownername = world->owner;

																											GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`9Quest For Bot``|left|1790|\nadd_label|small|`o(Step 5/5)``|left|4|\n\nadd_spacer|small|\nadd_label|small|`oI challenge you to show me the `2Legendary Orb!``|left|4|\n\nadd_spacer|small|\nadd_button|lbot6|`oShow The Legendary Orb!``|0|0|\nadd_quick_exit|\nend_dialog|noty|Give up on quest!|"));
																											ENetPacket* packet = enet_packet_create(p.data,
																												p.len,
																												ENET_PACKET_FLAG_RELIABLE);
																											enet_peer_send(peer, 0, packet);
																											delete p.data;
																										}
																										else
																											if (((PlayerInfo*)(peer->data))->lstep == 1 & ((PlayerInfo*)(peer->data))->lprogress == 1) {
																												string ownername = world->owner;

																												GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`9Quest For Fire``|left|1790|\nadd_label|small|`o(Step 1/5)``|left|4|\n\nadd_spacer|small|\nadd_label|small|`oI challenge you to bring me `2 Rayman's Fist!``|left|4|\n\nadd_spacer|small|\nadd_button|ldrag1|`oDeliver 1 Rayman's fist!``|0|0|\nadd_quick_exit|\nend_dialog|noty|Give up on quest!|"));
																												ENetPacket* packet = enet_packet_create(p.data,
																													p.len,
																													ENET_PACKET_FLAG_RELIABLE);
																												enet_peer_send(peer, 0, packet);
																												delete p.data;
																											}
																											else
																												if (((PlayerInfo*)(peer->data))->lstep == 1 & ((PlayerInfo*)(peer->data))->lprogress == 2) {
																													string ownername = world->owner;

																													GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`9Quest For Fire``|left|1790|\nadd_label|small|`o(Step 2/5)``|left|4|\n\nadd_spacer|small|\nadd_label|small|`oI challenge you to bring me `250 World Locks!``|left|4|\n\nadd_spacer|small|\nadd_button|ldrag2|`oDeliver The World Locks!``|0|0|\nadd_quick_exit|\nend_dialog|noty|Give up on quest!|"));
																													ENetPacket* packet = enet_packet_create(p.data,
																														p.len,
																														ENET_PACKET_FLAG_RELIABLE);
																													enet_peer_send(peer, 0, packet);
																													delete p.data;
																												}
																												else
																													if (((PlayerInfo*)(peer->data))->lstep == 1 & ((PlayerInfo*)(peer->data))->lprogress == 3) {
																														string ownername = world->owner;

																														GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`9Quest For Fire``|left|1790|\nadd_label|small|`o(Step 3/5)``|left|4|\n\nadd_spacer|small|\nadd_label|small|`oI challenge you to bring me `2200 Dirt Seeds!``|left|4|\n\nadd_spacer|small|\nadd_button|ldrag3|`oDeliver The Dirt Seeds!``|0|0|\nadd_quick_exit|\nend_dialog|noty|Give up on quest!|"));
																														ENetPacket* packet = enet_packet_create(p.data,
																															p.len,
																															ENET_PACKET_FLAG_RELIABLE);
																														enet_peer_send(peer, 0, packet);
																														delete p.data;
																													}
																													else
																														if (((PlayerInfo*)(peer->data))->lstep == 1 & ((PlayerInfo*)(peer->data))->lprogress == 4) {
																															string ownername = world->owner;

																															GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`9Quest For Fire``|left|1790|\nadd_label|small|`o(Step 4/5)``|left|4|\n\nadd_spacer|small|\nadd_label|small|`oI challenge you to bring me `2200 Chandeliers!``|left|4|\n\nadd_spacer|small|\nadd_button|ldrag4|`oDeliver The Chandeliers!``|0|0|\nadd_quick_exit|\nend_dialog|noty|Give up on quest!|"));
																															ENetPacket* packet = enet_packet_create(p.data,
																																p.len,
																																ENET_PACKET_FLAG_RELIABLE);
																															enet_peer_send(peer, 0, packet);
																															delete p.data;
																														}
																														else
																															if (((PlayerInfo*)(peer->data))->lstep == 1 & ((PlayerInfo*)(peer->data))->lprogress == 5) {
																																string ownername = world->owner;

																																GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`9Quest For Fire``|left|1790|\nadd_label|small|`o(Step 5/5)``|left|4|\n\nadd_spacer|small|\nadd_label|small|`oI challenge you to show me the `2Legendary Orb!``|left|4|\n\nadd_spacer|small|\nadd_button|ldrag5|`oShow The Legendary Orb!``|0|0|\nadd_quick_exit|\nend_dialog|noty|Give up on quest!|"));
																																ENetPacket* packet = enet_packet_create(p.data,
																																	p.len,
																																	ENET_PACKET_FLAG_RELIABLE);
																																enet_peer_send(peer, 0, packet);
																																delete p.data;
																															}
																															else
																																if (((PlayerInfo*)(peer->data))->lstep == 2 & ((PlayerInfo*)(peer->data))->lprogress == 1) {
																																	string ownername = world->owner;

																																	GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`9Quest For Fire``|left|1790|\nadd_label|small|`o(Step 5/5)``|left|4|\n\nadd_spacer|small|\nadd_label|small|`oI challenge you to show me the `2Legendary Orb!``|left|4|\n\nadd_spacer|small|\nadd_button|ldrag6|`oShow The Legendary Orb!``|0|0|\nadd_quick_exit|\nend_dialog|noty|Give up on quest!|"));
																																	ENetPacket* packet = enet_packet_create(p.data,
																																		p.len,
																																		ENET_PACKET_FLAG_RELIABLE);
																																	enet_peer_send(peer, 0, packet);
																																	delete p.data;
																																}
				}
			}
			if (world->items[x + (y * world->width)].foreground == 2978)
			{
				if (x == static_cast<PlayerInfo*>(peer->data)->x / 32 && y == static_cast<PlayerInfo*>(peer->data)->y / 32)
				{
					static_cast<PlayerInfo*>(peer->data)->lastPunchX = x;
					static_cast<PlayerInfo*>(peer->data)->lastPunchY = y;
					if (world->owner != "" && !isWorldOwner(peer, world) && !isMod(peer))
					{
						SendBuyerVendDialog(peer, world);
						return;
					}
					SendVendDialog(peer, world);
				}
				else {
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Get closer!", 0, false);
				}
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 4296)
			{
				if (world->owner == "" || isWorldOwner(peer, world) || isMod(peer))
				{

					if (static_cast<PlayerInfo*>(peer->data)->SurgeryCooldown)
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "I know it's just a robot, but the authorities don't even trust you operating on that with your malpractice issues.", 0, true);
						return;
					}
					if (static_cast<PlayerInfo*>(peer->data)->PerformingSurgery)
					{
						end_surgery(peer, true);
					}
					static_cast<PlayerInfo*>(peer->data)->lastPunchX = x;
					static_cast<PlayerInfo*>(peer->data)->lastPunchY = y;
					string surgerywarning = "";
					vector<int> Tools;
					SearchInventoryItem(peer, 1258, 20, iscontains);
					if (!iscontains)
					{
						auto KiekTuri = 0;
						for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
						{
							if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 1258 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
							{
								KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
							}
						}
						//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Sponge ";

						if (KiekTuri != 0) Tools.push_back(1258);

					}
					else Tools.push_back(1258);
					SearchInventoryItem(peer, 1260, 20, iscontains);
					if (!iscontains)
					{
						auto KiekTuri = 0;
						for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
						{
							if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 1260 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
							{
								KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
							}
						}
						//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Scalpel ";

						if (KiekTuri != 0) Tools.push_back(1260);

					}
					else Tools.push_back(1260);
					SearchInventoryItem(peer, 1262, 20, iscontains);
					if (!iscontains)
					{
						auto KiekTuri = 0;
						for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
						{
							if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 1262 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
							{
								KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
							}
						}
						//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Anesthetic ";

						if (KiekTuri != 0) Tools.push_back(1262);

					}
					else Tools.push_back(1262);
					SearchInventoryItem(peer, 1264, 20, iscontains);
					if (!iscontains)
					{
						auto KiekTuri = 0;
						for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
						{
							if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 1264 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
							{
								KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
							}
						}
						//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Antiseptic ";

						if (KiekTuri != 0) Tools.push_back(1264);

					}
					else Tools.push_back(1264);
					SearchInventoryItem(peer, 1266, 20, iscontains);
					if (!iscontains)
					{
						auto KiekTuri = 0;
						for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
						{
							if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 1266 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
							{
								KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
							}
						}
						//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Antibiotics ";

						if (KiekTuri != 0 && static_cast<PlayerInfo*>(peer->data)->UnlockedAntibiotic) Tools.push_back(1266);

					}
					else if (static_cast<PlayerInfo*>(peer->data)->UnlockedAntibiotic) Tools.push_back(1266);
					SearchInventoryItem(peer, 1268, 20, iscontains);
					if (!iscontains)
					{
						auto KiekTuri = 0;
						for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
						{
							if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 1268 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
							{
								KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
							}
						}
						//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Splint ";

						if (KiekTuri != 0) Tools.push_back(1268);

					}
					else Tools.push_back(1268);
					SearchInventoryItem(peer, 1270, 20, iscontains);
					if (!iscontains)
					{
						auto KiekTuri = 0;
						for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
						{
							if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 1270 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
							{
								KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
							}
						}
						//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Stitches ";

						if (KiekTuri != 0) Tools.push_back(1270);

					}
					else Tools.push_back(1270);
					SearchInventoryItem(peer, 4308, 20, iscontains);
					if (!iscontains)
					{
						auto KiekTuri = 0;
						for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
						{
							if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 4308 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
							{
								KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
							}
						}
						//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Pins ";

						if (KiekTuri != 0) Tools.push_back(4308);

					}
					else Tools.push_back(4308);
					SearchInventoryItem(peer, 4310, 20, iscontains);
					if (!iscontains)
					{
						auto KiekTuri = 0;
						for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
						{
							if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 4310 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
							{
								KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
							}
						}
						//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Transfusion ";

						if (KiekTuri != 0) Tools.push_back(4310);

					}
					else Tools.push_back(4310);
					SearchInventoryItem(peer, 4312, 20, iscontains);
					if (!iscontains)
					{
						auto KiekTuri = 0;
						for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
						{
							if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 4312 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
							{
								KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
							}
						}
						//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Defibrillator ";

						if (KiekTuri != 0 && static_cast<PlayerInfo*>(peer->data)->PatientHeartStopped) Tools.push_back(4312);

					}
					else if (static_cast<PlayerInfo*>(peer->data)->PatientHeartStopped) Tools.push_back(4312);
					SearchInventoryItem(peer, 4314, 20, iscontains);
					if (!iscontains)
					{
						auto KiekTuri = 0;
						for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
						{
							if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 4314 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
							{
								KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
							}
						}
						//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Clamp ";

						if (KiekTuri != 0) Tools.push_back(4314);

					}
					else Tools.push_back(4314);
					SearchInventoryItem(peer, 4316, 20, iscontains);
					if (!iscontains)
					{
						auto KiekTuri = 0;
						for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
						{
							if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 4316 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
							{
								KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
							}
						}
						//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Ultrasound ";

						if (KiekTuri != 0) Tools.push_back(4316);

					}
					else Tools.push_back(4316);
					SearchInventoryItem(peer, 4318, 20, iscontains);
					if (!iscontains)
					{
						auto KiekTuri = 0;
						for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
						{
							if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 4318 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
							{
								KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
							}
						}
						//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Lab Kit";

						if (KiekTuri != 0) Tools.push_back(4318);

					}
					else Tools.push_back(4318);

					for (int i = 0; i < Tools.size(); i++)
					{
						if (i == 0) static_cast<PlayerInfo*>(peer->data)->SurgItem1 = Tools[i];
						if (i == 1) static_cast<PlayerInfo*>(peer->data)->SurgItem2 = Tools[i];
						if (i == 2) static_cast<PlayerInfo*>(peer->data)->SurgItem3 = Tools[i];
						if (i == 3) static_cast<PlayerInfo*>(peer->data)->SurgItem4 = Tools[i];
						if (i == 4) static_cast<PlayerInfo*>(peer->data)->SurgItem5 = Tools[i];
						if (i == 5) static_cast<PlayerInfo*>(peer->data)->SurgItem6 = Tools[i];
						if (i == 6) static_cast<PlayerInfo*>(peer->data)->SurgItem7 = Tools[i];
						if (i == 7) static_cast<PlayerInfo*>(peer->data)->SurgItem8 = Tools[i];
						if (i == 8) static_cast<PlayerInfo*>(peer->data)->SurgItem9 = Tools[i];
						if (i == 9) static_cast<PlayerInfo*>(peer->data)->SurgItem10 = Tools[i];
						if (i == 10) static_cast<PlayerInfo*>(peer->data)->SurgItem11 = Tools[i];
						if (i == 11) static_cast<PlayerInfo*>(peer->data)->SurgItem12 = Tools[i];
						if (i == 12) static_cast<PlayerInfo*>(peer->data)->SurgItem13 = Tools[i];
					}

					vector<int> VisiTools{ 1258, 1260, 1262, 1264, 1266, 1268, 1270, 4308, 4310, 4312, 4314, 4316, 4318 };

					int TuriKartu = 1;
					bool Taip = false;
					for (int isd = 0; isd < VisiTools.size(); isd++)
					{
						bool Pirmas = false;
						SearchInventoryItem(peer, VisiTools[isd], 20, Pirmas);
						if (Pirmas)
						{
							continue;
						}
						bool Antras = false;
						SearchInventoryItem(peer, VisiTools[isd], 20, Antras);
						if (!Antras)
						{
							//cout << "keistas yra " + to_string(TuriKartu) << endl;
							int arrayd = VisiTools.size() - TuriKartu;
							//cout << "array yra " + to_string(arrayd) << endl;
							auto KiekTuri = 0;
							for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
							{
								if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == VisiTools[isd] && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
								{
									KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
								}
							}
							if (!Taip) surgerywarning += "You only have `4" + to_string(KiekTuri) + "`` " + getItemDef(VisiTools[isd]).name + ", ";
							else if (isd == arrayd)  surgerywarning += "and `4" + to_string(KiekTuri) + "`` " + getItemDef(VisiTools[isd]).name + " ";
							else surgerywarning += "`4" + to_string(KiekTuri) + "`` " + getItemDef(VisiTools[isd]).name + ", ";
							Taip = true;
						}
					}



					static_cast<PlayerInfo*>(peer->data)->RequestedSurgery = true;



					string LowSupplyWarning = "";
					if (surgerywarning != "") LowSupplyWarning = "\nadd_smalltext|`9Low Supply Warning: ``" + surgerywarning + "``|left|";
					Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`9Surg-E Anatomical Dummy``|left|4296|\nadd_spacer|small|\nadd_smalltext|Surgeon Skill: " + to_string(static_cast<PlayerInfo*>(peer->data)->SurgerySkill) + "|left|\nadd_textbox|Are you sure you want to perform surgery on this robot? Whether you succeed or fail, the robot will be destroyed in the process.|left|" + LowSupplyWarning + "\nend_dialog|surge|Cancel|Okay!|");
				}
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 6016) {
				static_cast<PlayerInfo*>(peer->data)->lastPunchX = x;
				static_cast<PlayerInfo*>(peer->data)->lastPunchY = y;
				SendGScan(peer, world, x, y);
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 9432)
			{
				if (static_cast<PlayerInfo*>(peer->data)->haveGrowId && static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner || isMod(peer))
				{
					Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`5World Generation Machine``|left|9432|0|0|\n\nadd_spacer|small|\nadd_textbox|`oWelcome captain! This machine allows you to generate any world you wish, you can choose the width, height, blocks and even more! Press Start Machine to continue...|\n\nadd_spacer|small|\nadd_button|worldgenmachine|`9Start Machine|0|0|\nadd_quick_exit|");
				}
				else
				{
					Player::OnConsoleMessage(peer, "`#You must be world owner to use this machine!");
				}
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 1436)
			{
				if (static_cast<PlayerInfo*>(peer->data)->haveGrowId && static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner || isMod(peer))
				{
					string line;
					GTDialog allLog;
					ifstream breaklog("securitycam/logs/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + ".txt");
					allLog.addLabelWithIcon("`wBreak Block Logs", 1434, LABEL_SMALL);
					allLog.addSpacer(SPACER_SMALL);
					while (getline(breaklog, line))
					{
						allLog.addTextBox(line);
					}
					if (isDev(peer))
					{
						Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wSecurity Camera``|left|1436||\nadd_textbox|`oThis camera is suitable for logging actions which was made by other peoples such as `#Moderators `oand `6Developers`o!|" + allLog.finishDialog() + "|\nadd_spacer|small|\nadd_button|clearworldlogs|`4Clear Logs|0|0|\nadd_button|asfasfasd|`wClose|0|0|\nadd_quick_exit|");
					}
					else if (isMod(peer))
					{
						Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wSecurity Camera``|left|1436||\nadd_textbox|`oThis camera is suitable for logging actions which was made by other peoples such as `#Moderators `oand `6Developers`o!|" + allLog.finishDialog() + "|\nadd_spacer|small|\nadd_button|asfasfasd|`wClose|0|0|\nadd_quick_exit|");
					}
					else
					{
						Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wSecurity Camera``|left|1436||\nadd_textbox|`oThis camera is suitable for logging actions which was made by other peoples such as `#Moderators `oand `6Developers`o!|" + allLog.finishDialog() + "|\nadd_spacer|small|\nadd_button|clearworldlogs|`4Clear Logs|0|0|\nadd_button|asfasfasd|`wClose|0|0|\nadd_quick_exit|");
					}
				}
				else
				{
					Player::OnTextOverlay(peer, "`#Only world owner can view world logs!");
				}
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 9170)
			{
				if (static_cast<PlayerInfo*>(peer->data)->haveGrowId && static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner || isMod(peer))
				{
					Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wMagic Machine``|left|9170|0|0|\n\nadd_spacer|small|\nadd_textbox|`oThis machine is stronger than you think! It has ability to convert premium blocks into crystals! `4Warning! `oYou must have at least 100 blocks! Click `9Start `oTo get started!|\n\nadd_spacer|small|\nadd_button|magicmachine|`9Start|0|0|\nadd_quick_exit|");
				}
				else
				{
					Player::OnTextOverlay(peer, "`#You must be world owner to use this machine!");
				}
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 3898)
			{
				Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wTelephone`|left|3898|\n\nadd_spacer|small|\nadd_label|small|`oDial a number to call somebody in Growtopia. Phone numbers have 5 digits. Most numbers are not in service!|\nadd_spacer|small|\nadd_text_input|telephonenumber|Phone #||5|\nend_dialog|usetelephone|Hang Up|`wDial|\n");
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 658)
			{
				auto squaresign = x + (y * 100);
				auto isdbox = std::experimental::filesystem::exists("bulletinboard/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
				if (!isdbox)
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4An error occured. Break the bulletin board.", 0, true);
				}
				else
				{
					if (static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || world->owner == "" || isDev(peer))
					{
						GTDialog myLetterBox;
						myLetterBox.addLabelWithIcon("`wBulletin Board", 658, LABEL_BIG);
						myLetterBox.addSpacer(SPACER_SMALL);
						try
						{
							ifstream ifff("bulletinboard/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
							json j;
							ifff >> j;
							ifff.close();
							if (j["inmail"] <= 0)
							{
								myLetterBox.addTextBox("`oThe Bulletin Board is empty.");
								myLetterBox.addSpacer(SPACER_SMALL);
							}
							else
							{
								for (int i = 0; i < 20; i++)
								{
									if (j["mails"][i]["growid"] != "")
									{
										if (j["hidenames"] == 0)
										{
											int apos = j["mails"][i]["aposition"];
											myLetterBox.addLabelWithIconButton("`w" + j["mails"][i]["growid"].get<string>() + ":`2 " + j["mails"][i]["text"].get<string>() + "", 660, "removeselectedbulletin_" + to_string(squaresign) + "_" + to_string(apos));
											//myLetterBox.addSpacer(SPACER_SMALL);
										}
										else
										{
											myLetterBox.addTextBox("`2" + j["mails"][i]["text"].get<string>());
											//myLetterBox.addSpacer(SPACER_SMALL);
										}
									}
								}
							}

							if (j["inmail"] < 90)
							{
								myLetterBox.addTextBox("`oAdd to conversation?");
								myLetterBox.addInputBox("addbulletinletterinput", "", "", 50);
								myLetterBox.addSpacer(SPACER_SMALL);
								myLetterBox.addButton("addbulletinletter_" + to_string(squaresign), "`2Add");
								myLetterBox.addSpacer(SPACER_SMALL);
							}

							myLetterBox.addLabelWithIcon("`wOwner Options", 242, LABEL_BIG);
							myLetterBox.addSpacer(SPACER_SMALL);
							if (j["hidenames"] == 1)
							{
								myLetterBox.addTextBox("`oUncheck `5Hide names `oto enable individual comment removal options.");
								myLetterBox.addSpacer(SPACER_SMALL);
							}
							else
							{
								myLetterBox.addTextBox("`oTo remove an individual comment, press the icon to the left of it.");
								myLetterBox.addSpacer(SPACER_SMALL);
							}
							if (j["inmail"] > 0)
							{
								myLetterBox.addButton("bulletinboardclear_" + to_string(squaresign), "`4Clear Board");
								myLetterBox.addSpacer(SPACER_SMALL);
							}
							if (j["publiccanadd"] == 1)
								myLetterBox.addCheckbox("publiccanaddbulletinboard", "`oPublic can add", CHECKBOX_SELECTED);
							else
								myLetterBox.addCheckbox("publiccanaddbulletinboard", "`oPublic can add", CHECKBOX_NOT_SELECTED);

							if (j["hidenames"] == 1)
								myLetterBox.addCheckbox("hidenamesbulletinboard", "`oHide names", CHECKBOX_SELECTED);
							else
								myLetterBox.addCheckbox("hidenamesbulletinboard", "`oHide names", CHECKBOX_NOT_SELECTED);
							myLetterBox.addSpacer(SPACER_SMALL);
							myLetterBox.addButton("bulletinletterok_" + to_string(squaresign), "`wOK");
							myLetterBox.addQuickExit();
							myLetterBox.endDialog("Close", "", "Cancel");
							Player::OnDialogRequest(peer, myLetterBox.finishDialog());
						}
						catch (std::exception&)
						{
							cout << "bulletin tile failed" << endl;
							return; /*tipo jeigu nera*/
						}
					}
					else
					{
						GTDialog myLetterBox;
						myLetterBox.addLabelWithIcon("`wBulletin Board", 658, LABEL_BIG);
						myLetterBox.addSpacer(SPACER_SMALL);
						try
						{
							ifstream ifff("bulletinboard/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
							json j;
							ifff >> j;
							ifff.close();

							if (j["inmail"] > 0)
							{
								for (int i = 0; i < 20; i++)
								{
									if (j["mails"][i]["growid"] != "")
									{
										if (j["hidenames"] == 0)
										{
											myLetterBox.addLabelWithIcon("`w" + j["mails"][i]["growid"].get<string>() + ":`2 " + j["mails"][i]["text"].get<string>() + "", 660, LABEL_SMALL);
											myLetterBox.addSpacer(SPACER_SMALL);
										}
										else
										{
											myLetterBox.addTextBox("`2" + j["mails"][i]["text"].get<string>());
											myLetterBox.addSpacer(SPACER_SMALL);
										}
									}
								}
							}

							if (j["publiccanadd"] == 1 && j["inmail"] < 90)
							{
								myLetterBox.addSpacer(SPACER_SMALL);
								myLetterBox.addTextBox("`oAdd to conversation?");
								myLetterBox.addInputBox("addbulletinletterinput", "", "", 50);
								myLetterBox.addSpacer(SPACER_SMALL);
								myLetterBox.addButton("addbulletinletter_" + to_string(squaresign), "`2Add");
								myLetterBox.addSpacer(SPACER_SMALL);
							}

							myLetterBox.addQuickExit();
							myLetterBox.endDialog("Close", "", "Cancel");
							Player::OnDialogRequest(peer, myLetterBox.finishDialog());
						}
						catch (std::exception&)
						{
							cout << "bulletin tile failed" << endl;
							return; /*tipo jeigu nera*/
						}
					}
				}
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 656)
			{
				auto squaresign = x + (y * 100);
				auto isdbox = std::experimental::filesystem::exists("mailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
				if (!isdbox)
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4An error occured. Break the mailbox.", 0, true);
				}
				else
				{
					if (static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || world->owner == "" || isMod(peer))
					{
						GTDialog myLetterBox;
						myLetterBox.addLabelWithIcon("`wMail Box", 656, LABEL_BIG);
						ifstream ifff("mailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						json j;
						ifff >> j;
						ifff.close();
						if (j["inmail"] <= 0)
						{
							myLetterBox.addTextBox("`oThe mailbox is currently empty.");
						}
						else
						{
							int donated = j["inmail"];

							myLetterBox.addTextBox("`oYou have `w" + to_string(donated) + " `oletters:");
							myLetterBox.addSpacer(SPACER_SMALL);
							for (int i = 0; i < 20; i++)
							{
								if (j["mails"][i]["growid"] != "")
								{
									myLetterBox.addLabelWithIcon("`5\"" + j["mails"][i]["text"].get<string>() + "\" - `w" + j["mails"][i]["growid"].get<string>() + "", 660, LABEL_SMALL);
									myLetterBox.addSpacer(SPACER_SMALL);
								}
							}
							myLetterBox.addSpacer(SPACER_SMALL);
							myLetterBox.addButton("mailempty_" + to_string(squaresign), "`4Empty mailbox");
						}
						myLetterBox.addTextBox("`oWrite a letter to yourself?");
						myLetterBox.addInputBox("addletterinput_" + to_string(squaresign), "", "", 50);
						myLetterBox.addSpacer(SPACER_SMALL);
						myLetterBox.addButton("addletter", "`2Send Letter");
						myLetterBox.addSpacer(SPACER_SMALL);
						myLetterBox.addQuickExit();
						myLetterBox.endDialog("Close", "", "Cancel");
						Player::OnDialogRequest(peer, myLetterBox.finishDialog());
					}
					else
					{
						GTDialog myLetterBox;
						myLetterBox.addLabelWithIcon("`wMail Box", 656, LABEL_BIG);
						ifstream ifff("mailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						json j;
						ifff >> j;
						ifff.close();

						myLetterBox.addTextBox("`$Want to leave a message for the owner?");
						myLetterBox.addSpacer(SPACER_SMALL);
						myLetterBox.addInputBox("addletterinput_" + to_string(squaresign), "", "", 50);
						myLetterBox.addSpacer(SPACER_SMALL);
						myLetterBox.addButton("addletter", "`2Send Letter");

						myLetterBox.addSpacer(SPACER_SMALL);
						myLetterBox.addQuickExit();
						myLetterBox.endDialog("Close", "", "Cancel");
						Player::OnDialogRequest(peer, myLetterBox.finishDialog());
					}
				}
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 6286)
			{
				auto squaresign = x + (y * 100);
				auto isdbox = std::experimental::filesystem::exists("storageboxlvl1/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
				if (!isdbox)
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4An error occured. Break the box.", 0, true);
				}
				else
				{
					if (static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || world->owner == "" || isDev(peer))
					{
						GTDialog myBox;
						myBox.addLabelWithIcon("`wStorage Box Xtreme - Level 1", 6286, LABEL_BIG);
						ifstream ifff("storageboxlvl1/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						json j;
						ifff >> j;
						ifff.close();

						int stored = j["instorage"];

						if (stored > 0)
						{
							myBox.addSpacer(SPACER_SMALL);
						}

						int count = 0;
						int id = 0;
						int aposition = 0;
						for (int i = 0; i < 20; i++)
						{
							if (j["storage"][i]["itemid"] != 0)
							{
								count = j["storage"][i]["itemcount"];
								id = j["storage"][i]["itemid"];
								aposition = j["storage"][i]["aposition"];

								if (i % 6 == 0 && i != 0)
								{
									myBox.addStaticBlueFrameWithIdCountText(to_string(id), to_string(count), getItemDef(id).name, "boxlvl1DepositedItem_" + to_string(aposition) + "_" + to_string(squaresign), true);
								}
								else
								{
									myBox.addStaticBlueFrameWithIdCountText(to_string(id), to_string(count), getItemDef(id).name, "boxlvl1DepositedItem_" + to_string(aposition) + "_" + to_string(squaresign), false);
								}
							}
						}

						if (stored > 0)
						{
							myBox.addNewLineAfterFrame();
						}

						myBox.addTextBox("`w" + to_string(stored) + "/20 `$items stored.");
						myBox.addSpacer(SPACER_SMALL);
						myBox.addPicker("boxlvl1deposit_" + to_string(squaresign), "Deposit item", "Select an item");
						myBox.addSpacer(SPACER_SMALL);
						myBox.addQuickExit();
						myBox.endDialog("Close", "", "Exit");
						Player::OnDialogRequest(peer, myBox.finishDialog());
					}
				}
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 6288)
			{
				auto squaresign = x + (y * 100);
				auto isdbox = std::experimental::filesystem::exists("storageboxlvl2/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
				if (!isdbox)
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4An error occured. Break the box.", 0, true);
				}
				else
				{
					if (static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || world->owner == "" || isDev(peer))
					{
						GTDialog myBox;
						myBox.addLabelWithIcon("`wStorage Box Xtreme - Level 2", 6288, LABEL_BIG);
						ifstream ifff("storageboxlvl2/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						json j;
						ifff >> j;
						ifff.close();

						int stored = j["instorage"];

						if (stored > 0)
						{
							myBox.addSpacer(SPACER_SMALL);
						}

						int count = 0;
						int id = 0;
						int aposition = 0;
						for (int i = 0; i < 40; i++)
						{
							if (j["storage"][i]["itemid"] != 0)
							{
								count = j["storage"][i]["itemcount"];
								id = j["storage"][i]["itemid"];
								aposition = j["storage"][i]["aposition"];

								if (i % 6 == 0 && i != 0)
								{
									myBox.addStaticBlueFrameWithIdCountText(to_string(id), to_string(count), getItemDef(id).name, "boxlvl2DepositedItem_" + to_string(aposition) + "_" + to_string(squaresign), true);
								}
								else
								{
									myBox.addStaticBlueFrameWithIdCountText(to_string(id), to_string(count), getItemDef(id).name, "boxlvl2DepositedItem_" + to_string(aposition) + "_" + to_string(squaresign), false);
								}
							}
						}

						if (stored > 0)
						{
							myBox.addNewLineAfterFrame();
						}

						myBox.addTextBox("`w" + to_string(stored) + "/40 `$items stored.");
						myBox.addSpacer(SPACER_SMALL);
						myBox.addPicker("boxlvl2deposit_" + to_string(squaresign), "Deposit item", "Select an item");
						myBox.addSpacer(SPACER_SMALL);
						myBox.addQuickExit();
						myBox.endDialog("Close", "", "Exit");
						Player::OnDialogRequest(peer, myBox.finishDialog());
					}
				}
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 6290)
			{
				auto squaresign = x + (y * 100);
				auto isdbox = std::experimental::filesystem::exists("storageboxlvl3/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
				if (!isdbox)
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4An error occured. Break the box.", 0, true);
				}
				else
				{
					if (static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || world->owner == "" || isDev(peer))
					{
						GTDialog myBox;
						myBox.addLabelWithIcon("`wStorage Box Xtreme - Level 3", 6290, LABEL_BIG);
						ifstream ifff("storageboxlvl3/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						json j;
						ifff >> j;
						ifff.close();

						int stored = j["instorage"];

						if (stored > 0)
						{
							myBox.addSpacer(SPACER_SMALL);
						}

						int count = 0;
						int id = 0;
						int aposition = 0;
						for (int i = 0; i < 90; i++)
						{
							if (j["storage"][i]["itemid"] != 0)
							{
								count = j["storage"][i]["itemcount"];
								id = j["storage"][i]["itemid"];
								aposition = j["storage"][i]["aposition"];

								if (i % 6 == 0 && i != 0)
								{
									myBox.addStaticBlueFrameWithIdCountText(to_string(id), to_string(count), getItemDef(id).name, "boxlvl3DepositedItem_" + to_string(aposition) + "_" + to_string(squaresign), true);
								}
								else
								{
									myBox.addStaticBlueFrameWithIdCountText(to_string(id), to_string(count), getItemDef(id).name, "boxlvl3DepositedItem_" + to_string(aposition) + "_" + to_string(squaresign), false);
								}
							}
						}

						if (stored > 0)
						{
							myBox.addNewLineAfterFrame();
						}

						myBox.addTextBox("`w" + to_string(stored) + "/90 `$items stored.");
						myBox.addSpacer(SPACER_SMALL);
						myBox.addPicker("boxlvl3deposit_" + to_string(squaresign), "Deposit item", "Select an item");
						myBox.addSpacer(SPACER_SMALL);
						myBox.addQuickExit();
						myBox.endDialog("Close", "", "Exit");
						Player::OnDialogRequest(peer, myBox.finishDialog());
					}
				}
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 8878)
			{
				auto squaresign = x + (y * 100);
				auto isdbox = std::experimental::filesystem::exists("safevault/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
				if (!isdbox)
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4An error occured. Break the safe.", 0, true);
				}
				else
				{
					if (static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || world->owner == "" || isMod(peer))
					{
						ifstream ifff("safevault/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + to_string(squaresign) + ".json");
						json j;
						ifff >> j;
						ifff.close();

						int stored = j["insafe"];
						string password = j["password"];

						if (password != "")
						{
							GTDialog mySafeConfirm;
							mySafeConfirm.addLabelWithIcon("`wSafe Vault", 8878, LABEL_BIG);
							mySafeConfirm.addTextBox("Please enter your password to access the Save Vault.");
							mySafeConfirm.addInputBox("safeconfirmpassInput_" + to_string(squaresign), "", "", 18);
							mySafeConfirm.addButton("safe_confirmpass", "Enter Password");
							mySafeConfirm.addButton("saferecoverPasswordInConfirm_" + to_string(squaresign), "Recover Password");
							mySafeConfirm.addSpacer(SPACER_SMALL);
							mySafeConfirm.addQuickExit();
							mySafeConfirm.endDialog("Close", "", "Exit");
							Player::OnDialogRequest(peer, mySafeConfirm.finishDialog());
							return;
						}

						GTDialog mySafe;
						mySafe.addLabelWithIcon("`wSafe Vault", 8878, LABEL_BIG);

						if (stored > 0)
						{
							mySafe.addSpacer(SPACER_SMALL);
						}

						int count = 0;
						int id = 0;
						int aposition = 0;
						for (int i = 0; i < 20; i++)
						{
							if (j["safe"][i]["itemid"] != 0)
							{
								count = j["safe"][i]["itemcount"];
								id = j["safe"][i]["itemid"];
								aposition = j["safe"][i]["aposition"];

								if (i % 3 == 0 && i != 0)
								{
									mySafe.addStaticBlueFrameWithIdCountText(to_string(id), to_string(count), getItemDef(id).name, "safeBoxDepositedItem_" + to_string(aposition) + "_" + to_string(squaresign), true);
								}
								else
								{
									mySafe.addStaticBlueFrameWithIdCountText(to_string(id), to_string(count), getItemDef(id).name, "safeBoxDepositedItem_" + to_string(aposition) + "_" + to_string(squaresign), false);
								}
							}
						}

						if (stored > 0)
						{
							mySafe.addNewLineAfterFrame();
						}

						mySafe.addTextBox("`w" + to_string(stored) + "/20 `$items stored.");
						mySafe.addSpacer(SPACER_SMALL);
						mySafe.addPicker("safedeposit_" + to_string(squaresign), "Deposit item", "Select an item");
						if (j["password"] == "")
						{
							mySafe.addTextBox("`$This Safe Vault is not `4password protected`$!");
						}
						else
						{
							mySafe.addTextBox("`$This Safe Vault is `2password protected`$!");
						}
						mySafe.addSpacer(SPACER_SMALL);
						mySafe.addTextBox("`$Change your password.");
						mySafe.addButton("safeupdatepass_" + to_string(squaresign), "Update Password");

						mySafe.addSpacer(SPACER_SMALL);
						mySafe.addQuickExit();
						mySafe.endDialog("Close", "", "Exit");
						Player::OnDialogRequest(peer, mySafe.finishDialog());
					}
				}
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 1452)
			{
				auto squaresign = x + (y * world->width);
				auto isdbox = std::experimental::filesystem::exists("donationboxes/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
				if (!isdbox)
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4An error occured. Break the donation box.", 0, true);
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->lastPunchX = x;
					static_cast<PlayerInfo*>(peer->data)->lastPunchY = y;
					static_cast<PlayerInfo*>(peer->data)->lastPunchForeground = world->items[x + (y * world->width)].foreground;
					static_cast<PlayerInfo*>(peer->data)->lastPunchBackground = world->items[x + (y * world->width)].background;
					if (static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || world->owner == "" || isOwner(peer))
					{
						GTDialog myDbox;
						myDbox.addLabelWithIcon("`wDonation Box", world->items[x + (y * world->width)].foreground, LABEL_BIG);
						ifstream ifff("donationboxes/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						json j;
						ifff >> j;
						ifff.close();
						if (j["donated"] <= 0)
						{
							myDbox.addTextBox("`$The box is currently empty.");
						}
						else
						{
							int donated = j["donated"];
							int count = 0;
							myDbox.addTextBox("`oYou have `w" + to_string(donated) + " `ogifts waiting:");
							myDbox.addSpacer(SPACER_SMALL);
							for (int i = 0; i < 20; i++)
							{
								if (j["donatedItems"][i]["itemid"] != 0)
								{
									count = j["donatedItems"][i]["itemcount"];
									myDbox.addLabelWithIcon("`o" + getItemDef(j["donatedItems"][i]["itemid"]).name + " (`w" + to_string(count) + "`o) from `w" + j["donatedItems"][i]["sentBy"].get<string>() + "`#- '" + j["donatedItems"][i]["note"].get<string>() + "'", j["donatedItems"][i]["itemid"], LABEL_SMALL);
									myDbox.addSpacer(SPACER_SMALL);
								}
							}
							myDbox.addSpacer(SPACER_SMALL);
							myDbox.addButton("retrieveGifts_" + to_string(squaresign), "`4Retrieve Gifts");
						}
						myDbox.addSpacer(SPACER_SMALL);
						myDbox.addPicker("addDonationItem_" + to_string(squaresign), "`wGive Gift `o(Min rarity: `52`o)", "Select an item");
						myDbox.addSpacer(SPACER_SMALL);
						myDbox.addQuickExit();
						myDbox.endDialog("Close", "", "Cancel");
						Player::OnDialogRequest(peer, myDbox.finishDialog());
					}
					else
					{
						GTDialog myDbox;
						myDbox.addLabelWithIcon("`wDonation Box", world->items[x + (y * world->width)].foreground, LABEL_BIG);
						ifstream ifff("donationboxes/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						json j;
						ifff >> j;
						ifff.close();

						int donated = j["donated"];

						myDbox.addTextBox("`$You see `w" + to_string(donated) + "`$ gifts in the box!");
						myDbox.addTextBox("`$Want to leave a gift for the owner?");
						myDbox.addSpacer(SPACER_SMALL);

						myDbox.addPicker("addDonationItem_" + to_string(squaresign), "`wGive Gift `o(Min rarity: `52`o)", "Select an item");

						myDbox.addSpacer(SPACER_SMALL);
						myDbox.addQuickExit();
						myDbox.endDialog("Close", "", "Cancel");
						Player::OnDialogRequest(peer, myDbox.finishDialog());
					}
				}
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 1006)
			{
				auto squaresign = x + (y * 100);
				auto isdbox = std::experimental::filesystem::exists("bluemailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
				if (!isdbox)
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4An error occured. Break the mailbox.", 0, true);
				}
				else
				{
					if (static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || world->owner == "" || isMod(peer))
					{
						GTDialog myLetterBox;
						myLetterBox.addLabelWithIcon("`wBlue Mail Box", 1006, LABEL_BIG);
						ifstream ifff("bluemailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						json j;
						ifff >> j;
						ifff.close();
						if (j["inmail"] <= 0)
						{
							myLetterBox.addTextBox("`oThe mailbox is currently empty.");
						}
						else
						{
							int donated = j["inmail"];

							myLetterBox.addTextBox("`oYou have `w" + to_string(donated) + " `oletters:");
							myLetterBox.addSpacer(SPACER_SMALL);
							for (int i = 0; i < 20; i++)
							{
								if (j["mails"][i]["growid"] != "")
								{
									myLetterBox.addLabelWithIcon("`5\"" + j["mails"][i]["text"].get<string>() + "\" - `w" + j["mails"][i]["growid"].get<string>() + "", 660, LABEL_SMALL);
									myLetterBox.addSpacer(SPACER_SMALL);
								}
							}
							myLetterBox.addSpacer(SPACER_SMALL);
							myLetterBox.addButton("bluemailempty_" + to_string(squaresign), "`4Empty mailbox");
						}
						myLetterBox.addTextBox("`oWrite a letter to yourself?");
						myLetterBox.addInputBox("addblueletterinput_" + to_string(squaresign), "", "", 50);
						myLetterBox.addSpacer(SPACER_SMALL);
						myLetterBox.addButton("addblueletter", "`2Send Letter");
						myLetterBox.addSpacer(SPACER_SMALL);
						myLetterBox.addQuickExit();
						myLetterBox.endDialog("Close", "", "Cancel");
						Player::OnDialogRequest(peer, myLetterBox.finishDialog());
					}
					else
					{
						GTDialog myLetterBox;
						myLetterBox.addLabelWithIcon("`wMail Box", 1006, LABEL_BIG);
						ifstream ifff("bluemailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						json j;
						ifff >> j;
						ifff.close();

						myLetterBox.addTextBox("`$Want to leave a message for the owner?");
						myLetterBox.addSpacer(SPACER_SMALL);
						myLetterBox.addInputBox("addblueletterinput_" + to_string(squaresign), "", "", 50);
						myLetterBox.addSpacer(SPACER_SMALL);
						myLetterBox.addButton("addblueletter", "`2Send Letter");

						myLetterBox.addSpacer(SPACER_SMALL);
						myLetterBox.addQuickExit();
						myLetterBox.endDialog("Close", "", "Cancel");
						Player::OnDialogRequest(peer, myLetterBox.finishDialog());
					}
				}
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 2946)
			{
				if (static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || world->owner == "" || getPlyersWorld(peer)->isPublic)
				{
					auto targetworld = getPlyersWorld(peer);
					int itemid = world->items[x + (y * world->width)].foreground;
					int itembg = world->items[x + (y * world->width)].background;
					static_cast<PlayerInfo*>(peer->data)->displayfg = itemid;
					static_cast<PlayerInfo*>(peer->data)->displaybg = itembg;
					static_cast<PlayerInfo*>(peer->data)->displaypunchx = data.punchX;
					static_cast<PlayerInfo*>(peer->data)->displaypunchy = data.punchY;
					if (targetworld->items[x + (y * targetworld->width)].intdata != 0 && static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
					{
						Player::OnDialogRequest(peer, "add_label_with_icon|big|`wDisplay Block|left|" + to_string(itemid) + "|\nadd_spacer|small||\nadd_label|small|`oA " + getItemDef(targetworld->items[x + (y * targetworld->width)].intdata).name + " is on display here.|\nadd_button|pickupdisplayitem|Pick it up|0|0|\nadd_quick_exit|\n");
					}
					else if (targetworld->items[x + (y * targetworld->width)].intdata != 0)
					{
						Player::OnDialogRequest(peer, "add_label_with_icon|big|`wDisplay Block|left|" + to_string(itemid) + "|\nadd_spacer|small||\nadd_label|small|`oA " + getItemDef(targetworld->items[x + (y * targetworld->width)].intdata).name + " is on display here.|\nadd_button|chc000|Okay|0|0|\nadd_quick_exit|\n");
					}
					else if (getPlyersWorld(peer)->isPublic && targetworld->items[x + (y * targetworld->width)].intdata != 0 && static_cast<PlayerInfo*>(peer->data)->rawName != getPlyersWorld(peer)->owner)
					{
						Player::OnDialogRequest(peer, "add_label_with_icon|big|`wDisplay Block|left|" + to_string(itemid) + "|\nadd_spacer|small||\nadd_label|small|`oA " + getItemDef(targetworld->items[x + (y * targetworld->width)].intdata).name + " is on display here.|\nadd_button|chc000|Okay|0|0|\nadd_quick_exit|\n");
					}
					else if (getPlyersWorld(peer)->owner == "" && targetworld->items[x + (y * targetworld->width)].intdata != 0)
					{
						Player::OnDialogRequest(peer, "add_label_with_icon|big|`wDisplay Block|left|" + to_string(itemid) + "|\nadd_spacer|small||\nadd_label|small|`oA " + getItemDef(targetworld->items[x + (y * targetworld->width)].intdata).name + " is on display here.|\nadd_button|pickupdisplayitem|Pick it up|0|0|\nadd_quick_exit|\n");
					}
					else
					{
						Player::OnDialogRequest(peer, "add_label_with_icon|big|`wDisplay Block|left|" + to_string(itemid) + "|\nadd_spacer|small||\nadd_label|small|`oThe Display Block is empty. Use an item on it to display the item!|\nend_dialog||Close||\n");
					}
					return;
				}
				else
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "That area is owned by " + world->owner + "", 0, true);
					return;
				}
				return;
			}
			return;
		}
	case 6336:
		{
			Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wWelcome Back `9" + static_cast<PlayerInfo*>(peer->data)->rawName + "`w!|left|18|\nadd_spacer|small|\nadd_label|small|`^Your current `2Skill `^Group:`w " + static_cast<PlayerInfo*>(peer->data)->skill + "|left|4|\nadd_button|changeskillgroup|`!Choose Skill Group|0|0|\nadd_spacer|small|\nadd_label|small|`^Your current `2Level`^:`w " + std::to_string(static_cast<PlayerInfo*>(peer->data)->level) + "|left|4|\nadd_button|lvluprewards|`!Level Rewards|0|0|\nadd_spacer|small|\nadd_label|small|`^Your current `2Rank`^:`w " + getRankName(static_cast<PlayerInfo*>(peer->data)->adminLevel) + "|left|4|\nadd_button|rankup|`!Get Rankup|0|0|\nadd_spacer|small|\nadd_label|small|`^Your current `2Kills `^Count:`w " + std::to_string(static_cast<PlayerInfo*>(peer->data)->TotalKills) + "|left|4|\nadd_button|killrewards|`!Kill Rewards|0|0|\nadd_spacer|small|\nadd_button||Continue|0|0|\nadd_quick_exit");
			return;
		}
	case 10034: /*merge*/
		{
			SendMergeBook(peer);
			return;
		}
	case 764:
		{
			if (static_cast<PlayerInfo*>(peer->data)->isZombie == true) return;
			if (static_cast<PlayerInfo*>(peer->data)->canWalkInBlocks == true)
			{
				static_cast<PlayerInfo*>(peer->data)->canWalkInBlocks = false;
				static_cast<PlayerInfo*>(peer->data)->skinColor = 0x8295C3FF;
				send_state(peer);
			}
			sendSound(peer, "skel.wav");
			static_cast<PlayerInfo*>(peer->data)->isZombie = true;
			send_state(peer);
			RemoveInventoryItem(764, 1, peer, true);
			playerconfig(peer, 1150, 130, 0x14);
			return;
		}
	case 782:
		{
			if (static_cast<PlayerInfo*>(peer->data)->isZombie == false) return;
			static_cast<PlayerInfo*>(peer->data)->isZombie = false;
			send_state(peer);
			RemoveInventoryItem(782, 1, peer, true);
			playerconfig(peer, 1150, 300, 0x14);
			return;
		}
	case 6286: case 6288: case 6290: case 6214: case 1420: case 656: case 658: case 1006: case 8878: case 1240: case 762: case 6016: case 1452:
		{
			if (world->owner == "" || isWorldOwner(peer, world) || isWorldAdmin(peer, world))
			{
				if (world->name == "CON" || world->name == "PRN" || world->name == "AUX" || world->name == "NUL" || world->name == "COM1" || world->name == "COM2" || world->name == "COM3" || world->name == "COM4" || world->name == "COM5" || world->name == "COM6" || world->name == "COM7" || world->name == "COM8" || world->name == "COM9" || world->name == "LPT1" || world->name == "LPT2" || world->name == "LPT3" || world->name == "LPT4" || world->name == "LPT5" || world->name == "LPT6" || world->name == "LPT7" || world->name == "LPT8" || world->name == "LPT9") return;
				if (tile == 762) {
					world->items[x + (y * world->width)].label = getItemDef(tile).name;
					isDoor = true;
				}
				if (tile == 6016) {
					if (world->owner == "") {
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "This item can only be used in World-Locked worlds!", 0, true);
						return;
					}
				}
				if (tile == 6286 || tile == 6288 || tile == 6290)
				{
					auto Space = 20;
					string Directory = "storageboxlvl1";
					if (tile == 6288)
					{
						Space = 40; 
						Directory = "storageboxlvl2";
					}
					else if (tile == 6290)
					{
						Space = 90;
						Directory = "storageboxlvl3";
					}
					namespace fs = std::experimental::filesystem;
					if (!fs::is_directory(Directory + "/" + world->name) || !fs::exists(Directory + "/" + world->name))
					{
						fs::create_directory(Directory + "/" + world->name);
					}
					ofstream of(Directory + "/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					json j;
					j["instorage"] = 0;
					auto jArray = json::array();
					json jmid;
					for (auto i = 1; i <= Space; i++)
					{
						jmid["aposition"] = i;
						jmid["itemid"] = 0;
						jmid["placedby"] = static_cast<PlayerInfo*>(peer->data)->rawName;
						jmid["itemcount"] = 0;
						jArray.push_back(jmid);
					}
					j["storage"] = jArray;
					of << j << std::endl;
					of.close();
				}
				if (tile == 1240)
				{
					isHeartMonitor = true;
				}
				if (tile == 8878)
				{
					namespace fs = std::experimental::filesystem;
					if (!fs::is_directory("safevault/" + getPlyersWorld(peer)->name) || !fs::exists("safevault/" + getPlyersWorld(peer)->name))
					{
						fs::create_directory("safevault/" + getPlyersWorld(peer)->name);
					}
					ofstream of("safevault/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					json j;
					j["insafe"] = 0;
					j["password"] = "";
					j["recovery"] = "";
					json jArray = json::array();
					json jmid;
					for (int i = 1; i <= 20; i++)
					{
						jmid["aposition"] = i;
						jmid["itemid"] = 0;
						jmid["placedby"] = static_cast<PlayerInfo*>(peer->data)->rawName;
						jmid["itemcount"] = 0;
						jArray.push_back(jmid);
					}
					j["safe"] = jArray;
					of << j << std::endl;
					of.close();
				}
				if (tile == 656)
				{
					namespace fs = std::experimental::filesystem;
					if (!fs::is_directory("mailbox/" + getPlyersWorld(peer)->name) || !fs::exists("mailbox/" + getPlyersWorld(peer)->name))
					{
						fs::create_directory("mailbox/" + getPlyersWorld(peer)->name);
					}
					ofstream of("mailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					json j;
					j["x"] = x;
					j["y"] = y;
					j["inmail"] = 0;
					json jArray = json::array();
					json jmid;
					for (int i = 1; i <= 90; i++)
					{
						jmid["aposition"] = i;
						jmid["growid"] = "";
						jmid["text"] = "";
						jArray.push_back(jmid);
					}
					j["mails"] = jArray;
					of << j << std::endl;
					of.close();
				}
				if (tile == 658)
				{
					namespace fs = std::experimental::filesystem;
					if (!fs::is_directory("bulletinboard/" + getPlyersWorld(peer)->name) || !fs::exists("bulletinboard/" + getPlyersWorld(peer)->name))
					{
						fs::create_directory("bulletinboard/" + getPlyersWorld(peer)->name);
					}
					ofstream of("bulletinboard/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					json j;
					j["inmail"] = 0;
					j["publiccanadd"] = 1;
					j["hidenames"] = 0;
					json jArray = json::array();
					json jmid;
					for (int i = 1; i <= 90; i++)
					{
						jmid["aposition"] = i;
						jmid["growid"] = "";
						jmid["text"] = "";
						jArray.push_back(jmid);
					}
					j["mails"] = jArray;
					of << j << std::endl;
					of.close();
				}
				if (tile == 1006)
				{
					namespace fs = std::experimental::filesystem;
					if (!fs::is_directory("bluemailbox/" + getPlyersWorld(peer)->name) || !fs::exists("bluemailbox/" + getPlyersWorld(peer)->name))
					{
						fs::create_directory("bluemailbox/" + getPlyersWorld(peer)->name);
					}
					ofstream of("bluemailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					json j;
					j["x"] = x;
					j["y"] = y;
					j["inmail"] = 0;
					json jArray = json::array();
					json jmid;
					for (int i = 1; i <= 90; i++)
					{
						jmid["aposition"] = i;
						jmid["growid"] = "";
						jmid["text"] = "";
						jArray.push_back(jmid);
					}
					j["mails"] = jArray;

					of << j << std::endl;
					of.close();
				}
				if (tile == 6214 || tile == 1420)
                {
                    isMannequin = true;
                    namespace fs = std::experimental::filesystem;
                    if (!fs::is_directory("mannequin/" + world->name) || !fs::exists("mannequin/" + world->name))
                    {
                        fs::create_directory("mannequin/" + world->name);
                    }
                    json j;
                    auto seedexist = std::experimental::filesystem::exists("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
                    if (!seedexist)
                    {
                        j["clothHead"] = "0";
                        j["clothHair"] = "0";
                        j["clothMask"] = "0";
                        j["clothNeck"] = "0";
                        j["clothBack"] = "0";
                        j["clothShirt"] = "0";
                        j["clothPants"] = "0";
                        j["clothFeet"] = "0";
                        j["clothHand"] = "0";
                        ofstream of("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
                        of << j;
                        of.close();
                    }
                }
				if (tile == 1452)
				{
					namespace fs = std::experimental::filesystem;
					if (!fs::is_directory("donationboxes/" + world->name) || !fs::exists("donationboxes/" + world->name))
					{
						fs::create_directory("donationboxes/" + world->name);
					}
					ofstream of("donationboxes/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					json j;
					j["donated"] = 0;
					json jArray = json::array();
					json jmid;
					for (int i = 1; i <= 20; i++)
					{
						jmid["aposition"] = i;
						jmid["sentBy"] = "";
						jmid["note"] = "";
						jmid["itemid"] = 0;
						jmid["itemcount"] = 0;
						jArray.push_back(jmid);
					}
					j["donatedItems"] = jArray;
					of << j << std::endl;
					of.close();
				}
				break;
			}
		}
	case 2978: /*vend*/
		{
			if (world->owner == "" || isWorldOwner(peer, world) || isMod(peer) || isWorldAdmin(peer, world)) {
				VendUpdate = true;
				world->items[squaresign].vcount = 0;
				world->items[squaresign].vprice = 0;
				world->items[squaresign].vid = 0;
				world->items[squaresign].vdraw = 0;
				world->items[squaresign].opened = true;
				world->items[squaresign].rm = false;
				break;
			}
			else return;
		}
	case 2410: case 4426: case 1212: case 1234: case 3110: case 1976: case 2000: case 3122: case 10386: case 5664: case 5662: case 9644:
		{

			if (tile == 9644)
			{
				SearchInventoryItem(peer, 9644, 1, iscontains);
				if (!iscontains) return;
				else
				{
					if (CheckItemMaxed(peer, 1258, 5))
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(1258).name + " wouldnt fit into my inventory!", 0, true);
						return;
					}

					if (CheckItemMaxed(peer, 1260, 5))
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(1260).name + " wouldnt fit into my inventory!", 0, true);
						return;
					}

					if (CheckItemMaxed(peer, 1262, 5))
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(1262).name + " wouldnt fit into my inventory!", 0, true);
						return;
					}

					if (CheckItemMaxed(peer, 1264, 5))
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(1264).name + " wouldnt fit into my inventory!", 0, true);
						return;
					}

					if (CheckItemMaxed(peer, 1266, 5))
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(1266).name + " wouldnt fit into my inventory!", 0, true);
						return;
					}

					if (CheckItemMaxed(peer, 1268, 5))
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(1268).name + " wouldnt fit into my inventory!", 0, true);
						return;
					}

					if (CheckItemMaxed(peer, 1270, 5))
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(1270).name + " wouldnt fit into my inventory!", 0, true);
						return;
					}

					if (CheckItemMaxed(peer, 4308, 5))
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(4308).name + " wouldnt fit into my inventory!", 0, true);
						return;
					}

					if (CheckItemMaxed(peer, 4310, 5))
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(4310).name + " wouldnt fit into my inventory!", 0, true);
						return;
					}

					if (CheckItemMaxed(peer, 4312, 5))
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(4312).name + " wouldnt fit into my inventory!", 0, true);
						return;
					}

					if (CheckItemMaxed(peer, 4314, 5))
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(4314).name + " wouldnt fit into my inventory!", 0, true);
						return;
					}

					if (CheckItemMaxed(peer, 4316, 5))
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(4316).name + " wouldnt fit into my inventory!", 0, true);
						return;
					}

					if (CheckItemMaxed(peer, 4318, 5))
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(4318).name + " wouldnt fit into my inventory!", 0, true);
						return;
					}

					if (CheckItemMaxed(peer, 4296, 5))
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(4296).name + " wouldnt fit into my inventory!", 0, true);
						return;
					}


					RemoveInventoryItem(9644, 1, peer, true);
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou received 5 Surgical Sponge, 5 Surgical Scalpel, 5 Surgical Anesthetic, 5 Surgical Antiseptic, 5 Surgical Antibiotics, 5 Surgical Splint, 1 Surgical Stitches, 5 Surgical Pins, 5 Surgical Transfusion, 5 Surgical Defibrillator, 5 Surgical Clamp, 5 Surgical Ultrasound, 5 Surgical Lab Kit and a 1 Surg-E", 0, true);
					Player::OnConsoleMessage(peer, "`oYou received 5 Surgical Sponge, 5 Surgical Scalpel, 5 Surgical Anesthetic, 5 Surgical Antiseptic, 5 Surgical Antibiotics, 5 Surgical Splint, 1 Surgical Stitches, 5 Surgical Pins, 5 Surgical Transfusion, 5 Surgical Defibrillator, 5 Surgical Clamp, 5 Surgical Ultrasound, 5 Surgical Lab Kit and a 1 Surg-E");
					bool success = true;
					SaveItemMoreTimes(1258, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
					SaveItemMoreTimes(1260, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
					SaveItemMoreTimes(1262, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
					SaveItemMoreTimes(1264, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
					SaveItemMoreTimes(1266, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
					SaveItemMoreTimes(1268, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
					SaveItemMoreTimes(1270, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
					SaveItemMoreTimes(4308, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
					SaveItemMoreTimes(4310, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
					SaveItemMoreTimes(4312, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
					SaveItemMoreTimes(4314, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
					SaveItemMoreTimes(4316, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
					SaveItemMoreTimes(4318, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
					SaveItemMoreTimes(4296, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");

					ENetPeer* currentPeer;
					for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
					{
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, currentPeer))
						{
							SendTradeEffect(currentPeer, 1258, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
							SendTradeEffect(currentPeer, 1260, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
							SendTradeEffect(currentPeer, 1262, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
							SendTradeEffect(currentPeer, 1264, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
							SendTradeEffect(currentPeer, 1266, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
							SendTradeEffect(currentPeer, 1268, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
							SendTradeEffect(currentPeer, 1270, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
							SendTradeEffect(currentPeer, 4308, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
							SendTradeEffect(currentPeer, 4310, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
							SendTradeEffect(currentPeer, 4312, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
							SendTradeEffect(currentPeer, 4314, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
							SendTradeEffect(currentPeer, 4316, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
							SendTradeEffect(currentPeer, 4318, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
							SendTradeEffect(currentPeer, 4296, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);

						}
					}


				}
			}

			if (tile == 5662)
			{
				SearchInventoryItem(peer, 5662, 200, iscontains);
				if (!iscontains) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`6You will need more dust than that!", 0, true);
				else
				{
					RemoveInventoryItem(5662, 200, peer, true);
					bool success = true;
					SaveItemMoreTimes(5642, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`5The dust stirs and begins to swirl! Cupid appears before you.", 0, true);
					static_cast<PlayerInfo*>(peer->data)->cloth_hand = 5642;
					sendClothes(peer);
				}
			}

			if (tile == 5664)
			{
				SearchInventoryItem(peer, 5664, 1, iscontains);
				if (!iscontains) return;
				else
				{
					RemoveInventoryItem(5664, 1, peer, true);
					bool success = true;
					SaveItemMoreTimes(5662, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
					//Player::OnConsoleMessage(peer, "`oYou received `21 " + getItemDef(itemid).name + " `ofrom the Gift of Growganoth.");
				}
			}
			if (tile == 10386)
			{
				SearchInventoryItem(peer, 10386, 1, iscontains);
				if (!iscontains) return;
				else
				{
					RemoveInventoryItem(10386, 1, peer, true);
					int itemuMas[59] = { 1216, 1218, 1992, 1982, 1994, 1972, 1980, 1988, 1984, 3116, 3102, 3106, 3110, 4160, 4162, 4164, 4154, 4158, 5224, 5222, 5232, 5240, 5248, 5238, 5256, 7116, 7108, 7110, 7128, 7112, 7114, 7130, 1198, 1208, 1222, 1200, 1220, 1202, 1238, 1168, 1172, 1230, 1194, 1192, 1226, 1196, 1236, 1182, 1184, 1186, 1188, 1170, 10198, 10196, 10202, 10204, 10326, 10324, 10322 };
					auto randIndex = rand() % 59;
					int itemid = itemuMas[randIndex];
					bool success = true;
					SaveItemMoreTimes(itemid, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
					Player::OnConsoleMessage(peer, "`oYou received `21 " + getItemDef(itemid).name + " `ofrom the Gift of Growganoth.");
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou received `21 " + getItemDef(itemid).name + " `wfrom the Gift of Growganoth.", 0, true);
				}
			}
			if (tile == 3122)
			{
				SearchInventoryItem(peer, 3122, 16, iscontains);
				if (!iscontains) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`6There's just not enough fragments here to make anything. Get more!", 0, true);
				else
				{
					RemoveInventoryItem(3122, 16, peer, true);
					bool success = true;
					SaveItemMoreTimes(3120, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`5SQUISH! The fragments forms into a teeny devil wings!", 0, true);
					static_cast<PlayerInfo*>(peer->data)->cloth_back = 3120;
					Player::PlayAudio(peer, "audio/change_clothes.wav", 0);
					sendClothes(peer);
				}
			}
			if (tile == 2000)
			{
				SearchInventoryItem(peer, 2000, 20, iscontains);
				if (!iscontains) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`6There's just not enough bones here to make anything. Get more!", 0, true);
				else
				{
					RemoveInventoryItem(2000, 20, peer, true);
					bool success = true;
					SaveItemMoreTimes(1998, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`5SQUISH! The bones forms into a skeletal dragon claw!", 0, true);
					static_cast<PlayerInfo*>(peer->data)->cloth_hand = 1998;
					Player::PlayAudio(peer, "audio/change_clothes.wav", 0);
					sendClothes(peer);
				}
			}
			if (tile == 1976)
			{
				SearchInventoryItem(peer, 1976, 10, iscontains);
				if (!iscontains) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`6There's just not enough skulls here to make anything. Get more!", 0, true);
				else
				{
					RemoveInventoryItem(1976, 10, peer, true);
					bool success = true;
					SaveItemMoreTimes(1974, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`5SQUISH! The skulls forms into a nightmare magnifying glass!", 0, true);
					static_cast<PlayerInfo*>(peer->data)->cloth_hand = 1974;
					Player::PlayAudio(peer, "audio/change_clothes.wav", 0);
					sendClothes(peer);
				}
			}
			if (tile == 1212)
			{
				SearchInventoryItem(peer, 1212, 25, iscontains);
				if (!iscontains) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`6There's just not enough fur here to make anything. Get more!", 0, true);
				else
				{
					RemoveInventoryItem(1212, 25, peer, true);
					bool success = true;
					SaveItemMoreTimes(1190, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`5SQUISH! The fur forms into a cuddly black cat!", 0, true);
					static_cast<PlayerInfo*>(peer->data)->cloth_hand = 1190;
					Player::PlayAudio(peer, "audio/change_clothes.wav", 0);
					sendClothes(peer);
				}
			}
			if (tile == 1234)
			{
				SearchInventoryItem(peer, 1234, 4, iscontains);
				if (!iscontains) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`6There's just not enough shards here to make anything. Get more!", 0, true);
				else
				{
					RemoveInventoryItem(1234, 4, peer, true);
					bool success = true;
					SaveItemMoreTimes(1206, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`5SQUISH! The shards forms into a devil wings!", 0, true);
					static_cast<PlayerInfo*>(peer->data)->cloth_back = 1206;
					Player::PlayAudio(peer, "audio/change_clothes.wav", 0);
					sendClothes(peer);
				}
			}
			if (tile == 3110)
			{
				SearchInventoryItem(peer, 3110, 25, iscontains);
				if (!iscontains) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`6There's just not enough tatters here to make anything. Get more!", 0, true);
				else
				{
					RemoveInventoryItem(3110, 25, peer, true);
					if ((rand() % 100) <= 15)
					{
						bool success = true;
						SaveItemMoreTimes(3112, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`5SQUISH! The tatters forms into a inside-out vampire cape!", 0, true);
						static_cast<PlayerInfo*>(peer->data)->cloth_back = 3112;
						Player::PlayAudio(peer, "audio/change_clothes.wav", 0);
						sendClothes(peer);
					}
					else
					{
						bool success = true;
						SaveItemMoreTimes(1166, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`5SQUISH! The tatters forms into a vampire cape!", 0, true);
						static_cast<PlayerInfo*>(peer->data)->cloth_back = 1166;
						Player::PlayAudio(peer, "audio/change_clothes.wav", 0);
						sendClothes(peer);
					}
				}
			}
			if (tile == 2410)
			{
				SearchInventoryItem(peer, 2410, 200, iscontains);
				if (!iscontains) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`oYou will need more `^Emerald Shards `oFor that!", 0, true);
				else
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`oThe power of `^Emerald Shards `oCompressed into `2Emerald Lock`o!", 0, true);
					RemoveInventoryItem(2410, 200, peer, true);
					bool success = true;
					SaveItemMoreTimes(2408, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
					Player::OnConsoleMessage(peer, "`o>> You received emerald lock!");
				}
			}
			if (tile == 4426)
			{
				SearchInventoryItem(peer, 4426, 200, iscontains);
				if (!iscontains) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`oYou will need more `4Ruby Shards `oFor that!", 0, true);
				else
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`oThe power of `4Ruby Shards `oCompressed into `4Ruby Lock`o!", 0, true);
					RemoveInventoryItem(4426, 200, peer, true);
					auto success = true;
					SaveItemMoreTimes(4428, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
					Player::OnConsoleMessage(peer, "`o>> You received ruby lock!");
				}
			}
			return;
		}
	case 6856: case 6858: case 6860: case 6862: case 9266: /*subtokens*/
		{
			auto contains = false;
			SearchInventoryItem(peer, tile, 1, contains);
			if (!contains)
			{
				autoBan(peer, false, 24 * 30, "Used sub exploit");
				break;
			}
			auto Sub_Days = 3;
			string Sub_Type = "free";
			if (tile == 9266) Sub_Days = 1;
			if (tile == 6856) Sub_Days = 3;
			if (tile == 6858) Sub_Days = 14;
			if (tile == 6860) Sub_Days = 30; Sub_Type = "premium";
			if (tile == 6862) Sub_Days = 365; Sub_Type = "premium";
			if (x == static_cast<PlayerInfo*>(peer->data)->x / 32 && y == static_cast<PlayerInfo*>(peer->data)->y / 32)
			{
				if (static_cast<PlayerInfo*>(peer->data)->Subscriber)
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You already have a Subscription!", 0, false);
					return;
				}

					ifstream fg("players/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".json");
					json j;
					fg >> j;
					fg.close();

					j["subtype"] = Sub_Type;
					j["subdate"] = to_string(Sub_Days);

					ofstream fs("players/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".json");
					fs << j;
					fs.close();
					RemoveInventoryItem(tile, 1, peer, true);
					SendTradeEffect(peer, tile, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
					static_cast<PlayerInfo*>(peer->data)->Subscriber = true;
					static_cast<PlayerInfo*>(peer->data)->haveSuperSupporterName = true;
					static_cast<PlayerInfo*>(peer->data)->SubscribtionEndDay = Sub_Days;
					Player::OnParticleEffect(peer, 46, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
					Player::OnAddNotification(peer, "`wYou've unlocked `5Premium Subscribtion `$benefits`w!", "audio/hub_open.wav", "interface/cash_icon_overlay.rttex");
					Player::PlayAudio(peer, "audio/thunderclap.wav", 0);

					static_cast<PlayerInfo*>(peer->data)->NickPrefix = j["title"].get<string>();
					static_cast<PlayerInfo*>(peer->data)->chatcolor = j["chatcolor"].get<string>();
					if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
					{
						restoreplayernick(peer);
						GamePacket p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName));
						memcpy(p7.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
						ENetPacket* packet7 = enet_packet_create(p7.data, p7.len, ENET_PACKET_FLAG_RELIABLE);
						ENetPeer* currentPeer;
						for (currentPeer = server->peers;
							currentPeer < &server->peers[server->peerCount];
							++currentPeer)
						{
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, currentPeer))
							{
								enet_peer_send(currentPeer, 0, packet7);
							}
						}
						delete p7.data;
					}

					send_state(peer);
					auto iscontains = false;
					SearchInventoryItem(peer, 6260, 1, iscontains);
					if (!iscontains)
					{
						bool success = true;
						SaveItemMoreTimes(6260, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from subscription");
						Player::OnAddNotification(peer, "`wYou've obtained `5Amulet Of Force`w!", "audio/hub_open.wav", "interface/cash_icon_overlay.rttex");
					}
				}
			return;
			}
	case 196: case 2480: case 10456: case 7480: case 528: case 540: case 6918: case 6924: case 1662: case 3062: case 822: /*consumables*/
		{
			if (tile == 196) /*blueberry*/
			{
				if (x == static_cast<PlayerInfo*>(peer->data)->x / 32 && y == static_cast<PlayerInfo*>(peer->data)->y / 32)
				{
					SendTradeEffect(peer, 196, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
					string txt = "A `1blueberry`o slides down your throat! (`$Feelin' Blue`o mod added, `$5 secs`o left)";
					static_cast<PlayerInfo*>(peer->data)->skinColor = 4278190335;
					sendClothes(peer);
					sendSound(peer, "audio/spray.wav");
					RemoveInventoryItem(196, 1, peer, true);
					if (static_cast<PlayerInfo*>(peer->data)->blueBerry == false)
					{
						Player::OnConsoleMessage(peer, txt);
						static_cast<PlayerInfo*>(peer->data)->lastBerry = 5;
						static_cast<PlayerInfo*>(peer->data)->usedBerry = GetCurrentTimeInternalSeconds();
					}
					static_cast<PlayerInfo*>(peer->data)->blueBerry = true;
				}
				ENetPeer* peer2;
				for (peer2 = server->peers; peer2 < &server->peers[server->peerCount]; ++peer2)
				{
					if (peer2->state != ENET_PEER_STATE_CONNECTED) continue;
					if (isHere(peer, peer2))
					{
						PlayerInfo* cpinfo = static_cast<PlayerInfo*>(peer2->data);
						if (x == cpinfo->x / 32 && y == cpinfo->y / 32)
						{
							SendTradeEffect(peer2, 196, static_cast<PlayerInfo*>(peer->data)->netID, cpinfo->netID, 150);
							SendTradeEffect(peer, 196, static_cast<PlayerInfo*>(peer->data)->netID, cpinfo->netID, 150);
							string txt = "A `1blueberry`o slides down your throat! (`$Feelin' Blue`o mod added, `$5 secs`o left)";
							cpinfo->skinColor = 4278190335;
							sendClothes(peer2);
							sendSound(peer2, "audio/spray.wav");
							if (cpinfo->blueBerry == false)
							{
								Player::OnConsoleMessage(peer2, txt);
								static_cast<PlayerInfo*>(peer2->data)->lastBerry = 5;
								static_cast<PlayerInfo*>(peer2->data)->usedBerry = GetCurrentTimeInternalSeconds();
							}
							cpinfo->blueBerry = true;
							break;
						}
					}
				}
			} 
			if (tile == 2480) {
				GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`w\n\nadd_label_with_icon|big|`wMegaphone|left|2480|\nadd_spacer|small|\nadd_label_with_icon|small|`oThis will broadcast to all players in the server!|left|486|\nadd_spacer|small|\nadd_text_input|sbtext|||50|\nend_dialog|sendsbg|Cancel|SenKd Broadcast|\n"));
				ENetPacket* packet2 = enet_packet_create(p2.data,
					p2.len,
					ENET_PACKET_FLAG_RELIABLE);

				enet_peer_send(peer, 0, packet2);
				delete p2.data;
				return;
			}
			if (tile == 10456) {
				if (pinfo->cloth_back != 10456) {
					pinfo->cloth_back = 10456;
					pinfo->peffect = 8421559;
					sendPuncheffectpeer(peer, ((PlayerInfo*)(peer->data))->peffect);
					sendClothes(peer);
				}
				else {
					pinfo->cloth_back = 0;
					((PlayerInfo*)(peer->data))->peffect = 8421376;
					sendPuncheffectpeer(peer, ((PlayerInfo*)(peer->data))->peffect);
					sendClothes(peer);
				}
			}
			if (tile == 7480) {
				if (pinfo->cloth_back != 7480) {
					pinfo->cloth_feet = 7384;
					pinfo->peffect = 8421396;
					sendPuncheffectpeer(peer, ((PlayerInfo*)(peer->data))->peffect);
					sendClothes(peer);
				}
				else {
					pinfo->cloth_back = 0;
					((PlayerInfo*)(peer->data))->peffect = 8421376;
					sendPuncheffectpeer(peer, ((PlayerInfo*)(peer->data))->peffect);
					sendClothes(peer);
				}
			}
			if (tile == 528) /*luckyclover*/
			{
				if (x == static_cast<PlayerInfo*>(peer->data)->x / 32 && y == static_cast<PlayerInfo*>(peer->data)->y / 32)
				{
					if (static_cast<PlayerInfo*>(peer->data)->LuckyClover == false)
					{
						SendTradeEffect(peer, 528, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
						sendSound(peer, "audio/spray.wav");
						RemoveInventoryItem(528, 1, peer, true);
						Player::OnConsoleMessage(peer, "You're `$luckier `othan before! (`$Lucky! `omod added, `$5 mins`o left)");
						static_cast<PlayerInfo*>(peer->data)->lastClover = 300;
						static_cast<PlayerInfo*>(peer->data)->usedClover = GetCurrentTimeInternalSeconds();
						static_cast<PlayerInfo*>(peer->data)->LuckyClover = true;
					}
					else Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You already have active lucky clover!", 0, true);
				}
			}
			if (tile == 6918) /*punchpotion*/
			{
				if (x == static_cast<PlayerInfo*>(peer->data)->x / 32 && y == static_cast<PlayerInfo*>(peer->data)->y / 32)
				{
					if (static_cast<PlayerInfo*>(peer->data)->PunchPotion == false)
					{
						SendTradeEffect(peer, 6918, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
						sendSound(peer, "audio/spray.wav");
						RemoveInventoryItem(6918, 1, peer, true);
						Player::OnConsoleMessage(peer, "You're `$stronger `othan before! (`$One HIT! `omod added, `$5 mins`o left)");
						static_cast<PlayerInfo*>(peer->data)->lastPunchPotion = 300;
						static_cast<PlayerInfo*>(peer->data)->usedPunchPotion = GetCurrentTimeInternalSeconds();
						static_cast<PlayerInfo*>(peer->data)->PunchPotion = true;
					}
					else Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You already have active punch potion!", 0, true);
				}
			}
			if (tile == 6924) /*placepotion*/
			{
				if (x == static_cast<PlayerInfo*>(peer->data)->x / 32 && y == static_cast<PlayerInfo*>(peer->data)->y / 32)
				{
					if (static_cast<PlayerInfo*>(peer->data)->PlacePotion == false)
					{
						SendTradeEffect(peer, 6924, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
						sendSound(peer, "audio/spray.wav");
						RemoveInventoryItem(6924, 1, peer, true);
						Player::OnConsoleMessage(peer, "Your hands are `$exceeding`o! (`$Triple Place! `omod added, `$5 mins`o left)");
						static_cast<PlayerInfo*>(peer->data)->lastPlacePotion = 300;
						static_cast<PlayerInfo*>(peer->data)->usedPlacePotion = GetCurrentTimeInternalSeconds();
						static_cast<PlayerInfo*>(peer->data)->PlacePotion = true;
					}
					else Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You already have active place potion!", 0, true);
				}
			}
			if (tile == 1662) /*spikejuice*/
			{
				if (x == static_cast<PlayerInfo*>(peer->data)->x / 32 && y == static_cast<PlayerInfo*>(peer->data)->y / 32)
				{
					if (static_cast<PlayerInfo*>(peer->data)->SpikeJuice == false)
					{
						SendTradeEffect(peer, 1662, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
						sendSound(peer, "audio/spray.wav");
						RemoveInventoryItem(1662, 1, peer, true);
						Player::OnConsoleMessage(peer, "You are immune to spikes and lava! (`$Spikeproof! `omod added, `$5 secs`o left)");
						static_cast<PlayerInfo*>(peer->data)->lastSpike = 5;
						static_cast<PlayerInfo*>(peer->data)->usedSpike = GetCurrentTimeInternalSeconds();
						static_cast<PlayerInfo*>(peer->data)->SpikeJuice = true;
					}
					else Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You already have active spike juice!", 0, true);
				}
			}
			if (tile == 540)
			{
				RemoveInventoryItem(540, 1, peer, true);
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`2BURRRPPP...!", 0, true);
			}
			if (tile == 3062)
			{
				if (world->items[x + (y * world->width)].fire == false && world->items[x + (y * world->width)].water == false)
				{
					if (world->items[x + (y * world->width)].foreground != 6 && world->items[x + (y * world->width)].foreground != 8 && getItemDef(world->items[x + (y * world->width)].foreground).blockType != BlockTypes::LOCK)
					{
						if (world->isPineappleGuard)
						{
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou cant use consumables here!", 0, true);
							return;
						}
						if (world->items[x + (y * world->width)].foreground == 0 && world->items[x + (y * world->width)].background == 0)
						{
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wTheres nothing to burn!", 0, true);
							return;
						}
						world->items[x + (y * world->width)].fire = !world->items[x + (y * world->width)].fire;
						ENetPeer* net_peer;
						for (net_peer = server->peers;
							net_peer < &server->peers[server->peerCount];
							++net_peer)
						{
							if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, net_peer))
							{
								Player::OnParticleEffect(net_peer, 150, x * 32 + 16, y * 32 + 16, 0);
								Player::OnTalkBubble(net_peer, static_cast<PlayerInfo*>(peer->data)->netID, "`7[```4MWAHAHAHA!! FIRE FIRE FIRE```7]``", 0, false);
							}
						}
						RemoveInventoryItem(3062, 1, peer, true);
						UpdateVisualsForBlock(peer, true, x, y, world);
						if (world->items[x + (y * world->width)].foreground == 0)
						{
							if (getItemDef(tile).rarity != 999)
							{
								int b = getGemCount(tile) + rand() % 1;
								while (b > 0)
								{
									if (b >= 100)
									{
										DropItem(
											peer, -1,
											x * 32 + (rand() % 16),
											y * 32 + (rand() % 16),
											112,
											100, 0);
										b -= 100;
										for (int i = 0; i < rand() % 1; i++) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 10, 0);
										for (int i = 0; i < rand() % 4; i++) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
										continue;
									}
									if (b >= 50)
									{
										DropItem(
											peer, -1,
											x * 32 + (rand() % 16),
											y * 32 + (rand() % 16),
											112,
											50, 0);
										b -= 50;
										for (int i = 0; i < rand() % 1; i++) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 5, 0);
										for (int i = 0; i < rand() % 3; i++) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
										continue;
									}
									if (b >= 10)
									{
										DropItem(
											peer, -1,
											x * 32 + (rand() % 16),
											y * 32 + (rand() % 16),
											112,
											10, 0);
										b -= 10;
										for (int i = 0; i < rand() % 4; i++) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
										continue;
									}
									if (b >= 7)
									{
										DropItem(
											peer, -1,
											x * 32 + (rand() % 16),
											y * 32 + (rand() % 16),
											112,
											10, 0);
										b -= 5;
										for (int i = 0; i < rand() % 2; i++) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
										continue;
									}
									if (b >= 5)
									{
										DropItem(
											peer, -1,
											x * 32 + (rand() % 16),
											y * 32 + (rand() % 16),
											112,
											5, 0);
										b -= 5;
										for (int i = 0; i < rand() % 2; i++) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
										continue;
									}
									if (b >= 1)
									{
										DropItem(
											peer, -1,
											x * 32 + (rand() % 16),
											y * 32 + (rand() % 16),
											112,
											1, 0);
										b -= 1;
										for (int i = 0; i < rand() % 1; i++) DropItem(peer, -1, x * 32 + (rand() % 8), y * 32 + (rand() % 16), 112, 1, 0);
										continue;
									}
								}
							}
						}
					}
				}
			}
			if (tile == 822)
			{
				if (world->items[x + (y * world->width)].water == false)
				{
					if (world->items[x + (y * world->width)].foreground != 6 && world->items[x + (y * world->width)].foreground != 8 && getItemDef(world->items[x + (y * world->width)].foreground).blockType != BlockTypes::LOCK)
					{
						if (isWorldOwner(peer, world) || world->owner == "" || isMod(peer))
						{
							world->items[x + (y * world->width)].water = false;
							UpdateBlockState(peer, x, y, true, world);
							if (world->isPineappleGuard)
							{
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou cant use consumables here!", 0, true);
								return;
							}
							world->items[x + (y * world->width)].water = !world->items[x + (y * world->width)].water;
							SendThrowEffect(peer, 822, static_cast<PlayerInfo*>(peer->data)->netID, -1, 150, 0, x * 32 + 16, y * 32 + 16);
							UpdateVisualsForBlock(peer, true, x, y, world);
						}
					}
				}
			}
			return;
		}
	case 1866:
		{
			if (world->owner == "" || static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || isMod(peer))
			{
				if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
				{
					return;
				}
				world->items[x + (y * world->width)].glue = !world->items[x + (y * world->width)].glue;
				UpdateVisualsForBlock(peer, true, x, y, world);
			}
			return;
		}
	case 8428:
		{
			auto iscontainsss = false;
			SearchInventoryItem(peer, 8428, 1, iscontainsss);
			if (!iscontainsss)
			{
				autoBan(peer, true, 1, "he tried to punch 8428 item, but did not has it.");
			}
			else
			{
				Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wUranus Blast`|left|8428|\n\nadd_spacer|small|\nadd_label|small|`oThis item creates a new world! Enter a unique name for it.|\nadd_spacer|small|\nadd_text_input|uranusname|New World Name||30|\nend_dialog|useuranusblast|Cancel|`5Create!|\n");
			}
			return;
		}
	case 3562:
		{
			auto iscontainsss = false;
			SearchInventoryItem(peer, 3562, 1, iscontainsss);
			if (!iscontainsss)
			{
				autoBan(peer, true, 1, "he tried to punch 8428 item, but did not has it.");
			}
			else
			{
				Player::OnDialogRequest(peer, "set_default_color|`w\n\nadd_label_with_icon|big|`wCave Blast|left|3562|\nadd_textbox|`oThis item creates a new world! Enter a unique name for it.|left|\nadd_text_input|cavetext|`oNew World Name||30|\nend_dialog|sendcave|Cancel|`5Create!|\n");
			}
			return;
		}
	case 1136:
		{
			auto iscontainsss = false;
			SearchInventoryItem(peer, 1136, 1, iscontainsss);
			if (!iscontainsss)
			{
				autoBan(peer, true, 1, "he tried to punch 8428 item, but did not has it.");
			}
			else
			{
				Player::OnDialogRequest(peer, "set_default_color|`w\n\nadd_label_with_icon|big|`wMars Blast|left|1136|\nadd_textbox|`oThis item creates a new world! Enter a unique name for it.|left|\nadd_text_input|marstext|`oNew World Name||30|\nend_dialog|sendmb|Cancel|`5Create!|\n");
			}
			return;
		}
	case 1060:
		{
			auto iscontainsss = false;
			SearchInventoryItem(peer, 1060, 1, iscontainsss);
			if (!iscontainsss)
			{
				autoBan(peer, true, 1, "he tried to punch 8428 item, but did not has it.");
			}
			else
			{
				Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wHarvest Moon Blast`|left|1060|\n\nadd_spacer|small|\nadd_label|small|`oThis item creates a new world! Enter a unique name for it.|\nadd_spacer|small|\nadd_text_input|harvestname|New World Name||30|\nend_dialog|harvestblast1|Cancel|`5Create!|\n");
			}
			return;
		}
	case 1826:
		{
			if (!isWorldOwner(peer, world)) return;
			auto iscontainsss = false;
			SearchInventoryItem(peer, 1826, 1, iscontainsss);
			if (!iscontainsss)
			{
				autoBan(peer, true, 1, "he tried to punch 1826 item, but did not has it.");
			}
			else
			{
				auto FoundSomething = false;
				for (auto i = 0; i < world->width * world->height; i++)
				{
					if (isSeed(world->items[i].foreground))
					{
						sendTileUpdate((i % world->width), (i / world->width), 18, static_cast<PlayerInfo*>(peer->data)->netID, peer);
						ENetPeer* net_peer;
						for (net_peer = server->peers;
							net_peer < &server->peers[server->peerCount];
							++net_peer)
						{
							if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, net_peer))
							{
								Player::OnParticleEffect(net_peer, 182, (i % world->width) * 32, (i / world->width) * 32, 0);
							}
						}
						FoundSomething = true;
					}
				}
				if (FoundSomething) RemoveInventoryItem(1826, 1, peer, true);
			}
			return;
		}
	case 5640: /*magplantremote*/
		{
			bool aryra = false;
			for (int i = 0; i < world->width * world->height; i++)
			{
				if (world->items[i].foreground == 5638)
				{
					aryra = true;
				}
			}
			if (aryra == true)
			{
				if (static_cast<PlayerInfo*>(peer->data)->magplantx != 0 && static_cast<PlayerInfo*>(peer->data)->magplanty != 0)
				{
					int squaresign = static_cast<PlayerInfo*>(peer->data)->magplantx + (static_cast<PlayerInfo*>(peer->data)->magplanty * 100);
					string currentworld = static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(squaresign);
					int itemid = 0;
					ifstream fdss("magplant/storeditem/" + currentworld + ".txt");
					fdss >> itemid;
					fdss.close();
					int count = 0;
					ifstream fdss3("magplant/count/" + currentworld + ".txt");
					fdss3 >> count;
					fdss3.close();
					if (itemid == static_cast<PlayerInfo*>(peer->data)->magplantitemid && count > 0)
					{
						int magplantid = static_cast<PlayerInfo*>(peer->data)->magplantitemid;
						bool RotatedRight = false;
						auto xpos = x * 32;
						auto ppos = static_cast<PlayerInfo*>(peer->data)->x;
						if (static_cast<PlayerInfo*>(peer->data)->x < x * 32) RotatedRight = true;
						if (RotatedRight) ppos += 19;
						xpos = xpos / 32;
						ppos = ppos / 32;
						if (world->items[x + (y * world->width)].foreground != 0 && getItemDef(magplantid).blockType != BlockTypes::BACKGROUND && getItemDef(magplantid).blockType != BlockTypes::GROUND_BLOCK) return;
						ENetPeer* currentPeer;
						for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount];
							++currentPeer)
						{
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, currentPeer))
							{
								bool RotatedRight = false;
								auto xpos = x * 32;
								auto ppos = static_cast<PlayerInfo*>(currentPeer->data)->x;
								if (static_cast<PlayerInfo*>(currentPeer->data)->x < x * 32) RotatedRight = true;
								if (RotatedRight) ppos += 19;
								xpos = xpos / 32;
								ppos = ppos / 32;
								if (ppos == xpos && static_cast<PlayerInfo*>(currentPeer->data)->y / 32 == y && getItemDef(magplantid).properties != Property_NoSeed && getItemDef(magplantid).properties != Property_Foreground && getItemDef(magplantid).properties != Property_MultiFacing && getItemDef(magplantid).blockType != BlockTypes::SEED && getItemDef(magplantid).blockType != BlockTypes::STEAM && getItemDef(magplantid).blockType != BlockTypes::UNKNOWN && getItemDef(magplantid).blockType != BlockTypes::VENDING && getItemDef(magplantid).blockType != BlockTypes::ANIM_FOREGROUND && getItemDef(magplantid).blockType != BlockTypes::BULLETIN_BOARD && getItemDef(magplantid).blockType != BlockTypes::FACTION && getItemDef(magplantid).blockType != BlockTypes::CHEST && getItemDef(magplantid).blockType != BlockTypes::GEMS && getItemDef(magplantid).blockType != BlockTypes::MAGIC_EGG && getItemDef(magplantid).blockType != BlockTypes::CRYSTAL && getItemDef(magplantid).blockType != BlockTypes::MAILBOX && getItemDef(magplantid).blockType != BlockTypes::PORTAL && getItemDef(magplantid).blockType != BlockTypes::PLATFORM && getItemDef(magplantid).blockType != BlockTypes::SFX_FOREGROUND && getItemDef(magplantid).blockType != BlockTypes::CHEMICAL_COMBINER && getItemDef(magplantid).blockType != BlockTypes::SWITCH_BLOCK && getItemDef(magplantid).blockType != BlockTypes::TRAMPOLINE && getItemDef(magplantid).blockType != BlockTypes::TOGGLE_FOREGROUND && getItemDef(magplantid).blockType != BlockTypes::GROUND_BLOCK && getItemDef(magplantid).blockType != BlockTypes::BACKGROUND && getItemDef(magplantid).blockType != BlockTypes::MAIN_DOOR && getItemDef(magplantid).blockType != BlockTypes::SIGN && getItemDef(magplantid).blockType != BlockTypes::DOOR && getItemDef(magplantid).blockType != BlockTypes::CHECKPOINT && getItemDef(magplantid).blockType != BlockTypes::GATEWAY && getItemDef(magplantid).blockType != BlockTypes::TREASURE && getItemDef(magplantid).blockType != BlockTypes::WEATHER) return;
							}
						}
						world->items[x + (y * world->width)].foreground = magplantid;
						count -= 1;
						ofstream savemag("magplant/count/" + currentworld + ".txt");
						savemag << count;
						savemag.close();
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
						data3.plantingTree = magplantid;
						for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
						{
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, currentPeer))
							{
								auto raw = packPlayerMoving(&data3);
								raw[2] = dicenr;
								raw[3] = dicenr;
								SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
							}
						}
						for (currentPeer = server->peers;
							currentPeer < &server->peers[server->peerCount];
							++currentPeer)
						{
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, currentPeer))
							{
								if (count <= 0)
								{
									SendItemSucker(currentPeer, 5638, static_cast<PlayerInfo*>(peer->data)->magplantx, static_cast<PlayerInfo*>(peer->data)->magplanty, itemid, 0, true, true);
								}
								else if (count >= 5000)
								{
									SendItemSucker(currentPeer, 5638, static_cast<PlayerInfo*>(peer->data)->magplantx, static_cast<PlayerInfo*>(peer->data)->magplanty, itemid, -1, true, true);
								}
								else
								{
									SendItemSucker(currentPeer, 5638, static_cast<PlayerInfo*>(peer->data)->magplantx, static_cast<PlayerInfo*>(peer->data)->magplanty, itemid, 1, true, true);
								}
							}
						}
					}
					else
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wThe `2MAGPLANT 5000 `wis empty!", 0, false);
					}
				}
			}
			return;
		}
	case 1436: /*securitycamera*/
		{
			bool aryra = false;
			for (int i = 0; i < world->width * world->height; i++)
			{
				if (world->items[i].foreground == 1436)
				{
					aryra = true;
				}
			}
			if (aryra == false)
			{
				if (static_cast<PlayerInfo*>(peer->data)->rawName != world->owner)
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`0You need to be world owner to place `cSecurity Camera`0!", 0, true);
					return;
				}
			}
			else
			{
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`0You cant place more than one `cSecurity Camera`0!", 0, true);
				return;
			}
			break;
		}
	case 1790: /*legendarywizard*/
		{
			if (static_cast<PlayerInfo*>(peer->data)->rawName != world->owner)
			{
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`0You need to be world owner to place `#Legendary Wizard`0!", 0, true);
				return;
			}
			else if (getPlyersWorld(peer)->isPublic == true)
			{
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`0You cannot place `#Legendary Wizard `0In public worlds`0!", 0, true);
				return;
			}
			break;
		}
	case 5524: /*nuclear clear world*/
	{
		GTDialog myTest;
		myTest.addLabelWithIcon("`wAre you sure?.", 5524, LABEL_BIG);
		myTest.addSpacer(SPACER_SMALL);
		myTest.addTextBox("`1Are you sure that you want to clear this world?");
		myTest.addSpacer(SPACER_SMALL);
		myTest.addButton("clearworldyes", "`w`2Yes, I want to clear this world.");
		myTest.addButton("", "`4No, I don't want to clear this world.");
		myTest.endDialog("", "", "");
		Player::OnDialogRequest(peer, myTest.finishDialog());
		return;

	}
	case 6204: case 6202: case 6200: case 7484: case 7954: case 1360: /*chest*/
		{
			if (tile == 1360)
			{
				vector<int> Dailyb{ 242, 242, 242, 10028, 828, 68, 82, 10032, 98, 404, 400, 3402, 3400 };
				const int Index = rand() % Dailyb.size();
				const auto ItemID = Dailyb[Index];
				RemoveInventoryItem(1360, 1, peer, true);
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou received " + getItemDef(ItemID).name + "", 0, true);
				Player::OnConsoleMessage(peer, "`oYou received " + getItemDef(ItemID).name + "");
				bool success = true;
				SaveItemMoreTimes(ItemID, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from daily gift");
			}
			if (tile == 6204) 
			{
				if (static_cast<PlayerInfo*>(peer->data)->haveGrowId == false) return;
				auto iscontains = false;
				SearchInventoryItem(peer, 6204, 1, iscontains);
				if (!iscontains)
				{
					return;
				}
				else
				{
					RemoveInventoryItem(6204, 1, peer, true);
					auto kuriPrizaDuot = rand() % 2 + 1;
					if (kuriPrizaDuot == 1)
					{
						auto gemChance = rand() % 20000;
						GiveChestPrizeGems(peer, gemChance);
					}
					if (kuriPrizaDuot == 2)
					{
						int itemuMas[5] = { 7912, 7912, 7912, 5078, 8834 };
						auto randIndex = rand() % 5;
						auto itemId = itemuMas[randIndex];
						send_item(peer, itemId, 1, 6204);
					}
				}
			}
			if (tile == 6202)
			{
				if (static_cast<PlayerInfo*>(peer->data)->haveGrowId == false) return;
				auto iscontains = false;
				SearchInventoryItem(peer, 6202, 1, iscontains);
				if (!iscontains)
				{
					return;
				}
				else
				{
					RemoveInventoryItem(6202, 1, peer, true);
					auto kuriPrizaDuot = rand() % 2 + 1;
					if (kuriPrizaDuot == 1)
					{
						auto gemChance = rand() % 70000;
						GiveChestPrizeGems(peer, gemChance);
					}
					if (kuriPrizaDuot == 2)
					{
						int itemuMas[5] = { 7912, 5078, 5078, 5078, 8834 };
						auto randIndex = rand() % 5;
						auto itemId = itemuMas[randIndex];
						send_item(peer, itemId, 1, 6202);
					}
				}
			}
			if (tile == 6200)
			{
				if (static_cast<PlayerInfo*>(peer->data)->haveGrowId == false) return;
				auto iscontains = false;
				SearchInventoryItem(peer, 6200, 1, iscontains);
				if (!iscontains)
				{
					return;
				}
				else
				{
					RemoveInventoryItem(6200, 1, peer, true);
					auto kuriPrizaDuot = rand() % 2 + 1;
					if (kuriPrizaDuot == 1)
					{
						auto gemChance = rand() % 120000;
						GiveChestPrizeGems(peer, gemChance);
					}
					if (kuriPrizaDuot == 2)
					{
						int itemuMas[8] = { 7912, 7912, 7912, 7912, 5078, 5078, 5078, 8834 };
						auto randIndex = rand() % 8;
						auto itemId = itemuMas[randIndex];
						send_item(peer, itemId, 1, 6200);
					}
				}
			}
			if (tile == 7484)
			{
				if (static_cast<PlayerInfo*>(peer->data)->haveGrowId == false) return;
				auto iscontains = false;
				SearchInventoryItem(peer, 7484, 1, iscontains);
				if (!iscontains)
				{
					return;
				}
				else
				{
					RemoveInventoryItem(7484, 1, peer, true);
					auto kuriPrizaDuot = rand() % 2 + 1;
					if (kuriPrizaDuot == 1)
					{
						auto gemChance = rand() % 170000;
						GiveChestPrizeGems(peer, gemChance);
					}
					if (kuriPrizaDuot == 2)
					{
						int itemuMas[12] = { 7912, 7912, 7912, 7912, 5078, 5078, 5078, 8834, 8834, 8834, 8834, 8834 };
						auto randIndex = rand() % 12;
						int itemId = itemuMas[randIndex];
						send_item(peer, itemId, 1, 7484);
					}
				}
			}
			if (tile == 7954)
			{
				if (static_cast<PlayerInfo*>(peer->data)->haveGrowId == false) return;
				auto iscontains = false;
				SearchInventoryItem(peer, 7954, 1, iscontains);
				if (!iscontains)
				{
					return;
				}
				else
				{
					RemoveInventoryItem(7954, 1, peer, true);
					auto kuriPrizaDuot = rand() % 2 + 1;
					if (kuriPrizaDuot == 1)
					{
						int gemChance = rand() % 200000;
						GiveChestPrizeGems(peer, gemChance);
					}
					if (kuriPrizaDuot == 2)
					{
						int itemuMas[12] = { 7912, 7912, 7912, 7912, 5078, 5078, 5078, 8834, 8834, 8834, 8834, 8834 };
						auto randIndex = rand() % 12;
						auto itemId = itemuMas[randIndex];
						send_item(peer, itemId, 1, 7954);
					}
				}
			}
			return;
		}
	case 1404: /*doormover*/
		{
			if (static_cast<PlayerInfo*>(peer->data)->rawName != world->owner && !isMod(peer) && world->owner != "") return;
            if (world->items[x + (y * world->width)].foreground != 0) {
                Player::OnTextOverlay(peer, "`@There Is `4No `@Space For `wMain Door`@!");
                return;
            } else {
                RemoveInventoryItem(1404, 1, peer, true);
                for (int i = 0; i < world->width * world->height; i++) {
                    if (i >= 5400) {
                        world->items[i].foreground = 8;
                    } else if (world->items[i].foreground == 6) {
                        world->items[i].foreground = 0;
                    } else if (world->items[i].foreground != 6) {
                        world->items[x + (y * world->width)].foreground = 6;
                    }
                }
                for (ENetPeer* net_peer = server->peers; net_peer < &server->peers[server->peerCount]; ++net_peer) {
                    if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
                    if (isHere(peer, net_peer)) {
						//string act = static_cast<PlayerInfo*>(peer->data)->currentWorld;
						sendPlayerLeave(net_peer, static_cast<PlayerInfo*>(net_peer->data));
						sendWorldOffers(peer);
                        Player::OnTextOverlay(peer, "`^You Have `2Used `wDoor Mover`^!");
                    }
                }
            }
            return;
        }
	case 5460: case 4520: case 382: case 3116: case 732: case 2994: case 4368: case 274: case 276: case 278: case 5708: case 5709: case 5780: case 5781: case 5782: case 5783: case 5784: case 5785: case 5710: case 5711: case 5786: case 5787: case 5788: case 5789: case 5790: case 5791: case 6146: case 6147: case 6148: case 6149: case 6150: case 6151: case 6152: case 6153: case 5670: case 5671: case 5798: case 5799: case 5800: case 5801: case 5802: case 5803: case 5668: case 5669: case 5792: case 5793: case 5794: case 5795: case 5796: case 5797: case 54600: case 1902: case 1508: case 428: case 3808: case 5132: case 7166: case 5078: case 5080: case 5082: case 5084: case 5126: case 5128: case 5130: case 5144: case 5146: case 5148: case 5150: case 5162: case 5164: case 5166: case 5168: case 5180: case 5182: case 5184: case 5186: case 7168: case 7170: case 7172: case 7174: case 9999: case 980: case 3212: case 4742: case 3496: case 3270: case 4722: case 9212: case 5134: case 5152: case 5170: case 5188: case 611:
		{
			return;
		}
	default:
		{

			if (getItemDef(tile).blockType == BlockTypes::GATEWAY) {
				world->items[squaresign].opened = true;
				isgateway = true;
			}
			if (getItemDef(tile).blockType == BlockTypes::PROVIDER) {
				isScience = true;
			}
			if (world->items[x + (y * world->width)].foreground == 1420 || world->items[x + (y * world->width)].foreground == 6214 && tile != 18) {
				if (getItemDef(tile).blockType == BlockTypes::CLOTHING)
				{
					if (world->owner == "" || static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner))
					{
						if (getItemDef(tile).properties & Property_Untradable) {
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You can't use untradeable items with mannequins.", 0, true);
							return;
						}
						auto seedexist = std::experimental::filesystem::exists("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						if (seedexist)
						{
							json j;
							ifstream fs("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
							fs >> j;
							fs.close();

							int c = getItemDef(tile).clothType;
							if (c == 0) {
								//world->items[x + (y * world->width)].clothHead = tile;
								if (j["clothHead"].get<string>() != "0") return;
								j["clothHead"] = to_string(tile);
							}
							else if (c == 7) {
								//world->items[x + (y * world->width)].clothHair = tile;
								if (j["clothHair"].get<string>() != "0") return;
								j["clothHair"] = to_string(tile);
							}
							else if (c == 4) {
								//world->items[x + (y * world->width)].clothMask = tile;
								if (j["clothMask"].get<string>() != "0") return;
								j["clothMask"] = to_string(tile);
							}
							else if (c == 8) {
								//world->items[x + (y * world->width)].clothNeck = tile;
								if (j["clothNeck"].get<string>() != "0") return;
								j["clothNeck"] = to_string(tile);
							}
							else if (c == 6) {
								//world->items[x + (y * world->width)].clothBack = tile;
								if (j["clothBack"].get<string>() != "0") return;
								j["clothBack"] = to_string(tile);
							}
							else if (c == 1) {
								//world->items[x + (y * world->width)].clothShirt = tile;
								if (j["clothShirt"].get<string>() != "0") return;
								j["clothShirt"] = to_string(tile);
							}
							else if (c == 2) {
								//world->items[x + (y * world->width)].clothPants = tile;
								if (j["clothPants"].get<string>() != "0") return;
								j["clothPants"] = to_string(tile);
							}
							else if (c == 3) {
								//world->items[x + (y * world->width)].clothFeet = tile;
								if (j["clothFeet"].get<string>() != "0") return;
								j["clothFeet"] = to_string(tile);
							}
							else if (c == 5) {
								//world->items[x + (y * world->width)].clothHand = tile;
								if (j["clothHand"].get<string>() != "0") return;
								j["clothHand"] = to_string(tile);
							}

							if (c != 10) {
								auto iscontains = false;
								SearchInventoryItem(peer, tile, 1, iscontains);
								if (iscontains)
								{
									updateMannequin(peer, world->items[x + (y * world->width)].foreground, x, y, world->items[x + (y * world->width)].background, world->items[x + (y * world->width)].sign,
										atoi(j["clothHair"].get<string>().c_str()), atoi(j["clothHead"].get<string>().c_str()),
										atoi(j["clothMask"].get<string>().c_str()), atoi(j["clothHand"].get<string>().c_str()), atoi(j["clothNeck"].get<string>().c_str()),
										atoi(j["clothShirt"].get<string>().c_str()), atoi(j["clothPants"].get<string>().c_str()), atoi(j["clothFeet"].get<string>().c_str()),
										atoi(j["clothBack"].get<string>().c_str()), true, 0);

									ofstream of("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
									of << j;
									of.close();
									RemoveInventoryItem(tile, 1, peer, true);
								}
							}
						}
					}
				}
			}
			if (static_cast<PlayerInfo*>(peer->data)->Fishing && static_cast<PlayerInfo*>(peer->data)->TriggerFish)
			{
				static_cast<PlayerInfo*>(peer->data)->FishPosX = 0;
				static_cast<PlayerInfo*>(peer->data)->FishPosY = 0;
				static_cast<PlayerInfo*>(peer->data)->Fishing = false;
				send_state(peer);
				if (static_cast<PlayerInfo*>(peer->data)->TriggerFish)
				{
					static_cast<PlayerInfo*>(peer->data)->TriggerFish = false;
					vector<int> FishBase{ 3000, 3024, 3026, 3030, 3032, 3034, 3036, 3038, 3092, 3094, 3096, 3220, 3222, 3224, 3226, 3434, 3436, 3438, 3440, 3450, 3452, 3454, 3456, 3458, 3460, 3544, 3550, 3620, 3746, 3814, 3820, 4958, 5100, 5448, 5450, 5538, 5542, 5548, 5552, 5574, 5580, 7744, 8460 };
					srand(GetTickCount());
					const int Index = rand() % FishBase.size();
					const auto ItemID = FishBase[Index];
					vector<int> GearBase{ 344, 242, 3042, 3016, 10032, 5232, 5604, 5606, 5608, 6902, 6996, 9746 };
					const int GearIndex = rand() % GearBase.size();
					const auto GearID = GearBase[GearIndex];
					vector<int> BlockBase{ 444, 242, 1522, 3016, 3810, 4658, 5530, 5602, 5614, 5624, 6328, 7002, 8964, 8966 };
					const int BlockIndex = rand() % BlockBase.size();
					const auto BlockID = BlockBase[BlockIndex];
					auto count = 1;
					int ChanceOfGear = 0;
					int HowMuchLbs;
					int ChanceOfBlock = 0;
					if (static_cast<PlayerInfo*>(peer->data)->LastBait == "Fishing Fly")
					{
						ChanceOfBlock = (rand() % 400) + 1;
					}
					if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 2912) /*regular*/
					{
						HowMuchLbs = (rand() % 25) + 1;
					}
					else if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3008) /*ezrod*/
					{
						HowMuchLbs = (rand() % 40) + 1;
					}
					else if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3010) /*licorice*/
					{
						HowMuchLbs = (rand() % 60) + 1;
						ChanceOfGear = (rand() % 450) + 1;
					}
					else if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3100) /*cursed*/
					{
						HowMuchLbs = (rand() % 200) + 1;
						ChanceOfGear = (rand() % 150) + 1;
					}
					else if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3040) /*golden*/
					{
						HowMuchLbs = (rand() % 200) + 1;
						ChanceOfGear = (rand() % 200) + 1;
					}
					else if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 5740) /*magical*/
					{
						HowMuchLbs = (rand() % 90) + 1;
						ChanceOfGear = (rand() % 350) + 1;
					}
					else
					{
						return;
					}
					count = HowMuchLbs;
					if (ChanceOfBlock <= 30 && ChanceOfBlock != 0)
					{
						auto success = true;
						SaveItemMoreTimes(BlockID, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from fishing");
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`2You caught `5" + getItemDef(BlockID).name + "`2!", 0, false);
						auto Gems = (rand() % 500) + 1;
						auto currentGems = 0;
						ifstream ifs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
						ifs >> currentGems;
						ifs.close();
						currentGems += Gems;
						ofstream ofs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
						ofs << currentGems;
						ofs.close();
						SendXP(peer, 3);
						Player::OnSetBux(peer, currentGems, 0);
						ENetPeer* currentPeer;
						for (currentPeer = server->peers;
							currentPeer < &server->peers[server->peerCount];
							++currentPeer)
						{
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, currentPeer))
							{
								Player::OnConsoleMessage(currentPeer, "`$" + static_cast<PlayerInfo*>(peer->data)->displayName + " `oCaught `$" + getItemDef(BlockID).name + " `oAnd got `$" + to_string(Gems) + " `oGems!");
								Player::PlayAudio(currentPeer, "audio/choir.wav", 0);
							}
						}
						Player::OnSetPos(peer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y);
						SendBreakPacket(peer, x, y);
						return;
					}
					if (ChanceOfGear <= 10 && ChanceOfGear != 0)
					{
						auto success = true;
						SaveItemMoreTimes(GearID, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from fishing");
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`2You caught `5" + getItemDef(GearID).name + "`2!", 0, false);
						auto Gems = (rand() % 600) + 1;
						auto currentGems = 0;
						ifstream ifs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
						ifs >> currentGems;
						ifs.close();
						currentGems += Gems;
						ofstream ofs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
						ofs << currentGems;
						ofs.close();
						SendXP(peer, 5);
						Player::OnSetBux(peer, currentGems, 0);
						ENetPeer* currentPeer;
						for (currentPeer = server->peers;
							currentPeer < &server->peers[server->peerCount];
							++currentPeer)
						{
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, currentPeer))
							{
								Player::OnConsoleMessage(currentPeer, "`$" + static_cast<PlayerInfo*>(peer->data)->displayName + " `oCaught `$" + getItemDef(GearID).name + " `oAnd got `$" + to_string(Gems) + " `oGems!");
								Player::PlayAudio(currentPeer, "audio/choir.wav", 0);
							}
						}
						Player::OnSetPos(peer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y);
						SendBreakPacket(peer, x, y);
						return;
					}
					auto iscontains = false;
					SearchInventoryItem(peer, ItemID, 1, iscontains);
					if (!iscontains)
					{
						auto success = true;
						SaveItemMoreTimes(ItemID, count, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from fishing");
					}
					else
					{
						DropItem(peer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, ItemID, count, 0);
					}
					if (getItemDef(ItemID).blockType == BlockTypes::FISH)
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`2You caught `5" + getItemDef(ItemID).name + "`2! (`5" + to_string(count) + "`2 LBS)", 0, false);
					}
					else
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`2You caught `5" + getItemDef(ItemID).name + "`2!", 0, false);
					}
					auto Gems = 0;
					if (count >= 1 && count < 30)
					{
						Gems = (rand() % 150) + 1;
					}
					else if (count >= 30 && count < 60)
					{
						Gems = (rand() % 250) + 1;
					}
					else if (count >= 60 && count < 90)
					{
						Gems = (rand() % 400) + 1;
					}
					else if (count >= 90 && count < 120)
					{
						Gems = (rand() % 450) + 1;
					}
					else if (count >= 120 && count < 150)
					{
						Gems = (rand() % 500) + 1;
					}
					else if (count >= 150 && count < 199)
					{
						Gems = (rand() % 550) + 1;
					}
					else if (count >= 200)
					{
						Gems = (rand() % 900) + 1;
					}
					auto currentGems = 0;
					ifstream ifs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
					ifs >> currentGems;
					ifs.close();
					currentGems += Gems;
					ofstream ofs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
					ofs << currentGems;
					ofs.close();
					SendXP(peer, 2);
					Player::OnSetBux(peer, currentGems, 0);
					ENetPeer* currentPeer;
					for (currentPeer = server->peers;
						currentPeer < &server->peers[server->peerCount];
						++currentPeer)
					{
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, currentPeer))
						{
							Player::OnConsoleMessage(currentPeer, "`$" + static_cast<PlayerInfo*>(peer->data)->displayName + " `oCaught `$" + getItemDef(ItemID).name + " `o(`$" + to_string(count) + "`o LBS) And got `$" + to_string(Gems) + " `oGems!");
							Player::PlayAudio(currentPeer, "audio/keypad_hit.wav", 0);
						}
					}
				}
				Player::OnSetPos(peer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y);
				SendBreakPacket(peer, x, y);
				return;
			}
			if (tile == 2914 && isFishingRod(peer) || tile == 3016 && isFishingRod(peer))
			{
				if (world->items[x + (y * world->width)].water)
				{
					int PlayerPos = round(static_cast<PlayerInfo*>(peer->data)->x / 32);
					int PlayerPosY = round(static_cast<PlayerInfo*>(peer->data)->y / 32);
					if (PlayerPos != x && PlayerPos + 1 != x && PlayerPos - 1 != x || PlayerPosY != y && PlayerPosY + 1 != y)
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Too far away...", 0, true);
						return;
					}
					if (static_cast<PlayerInfo*>(peer->data)->x != 0 && !static_cast<PlayerInfo*>(peer->data)->Fishing)
					{
						RemoveInventoryItem(tile, 1, peer, true);
						static_cast<PlayerInfo*>(peer->data)->FishPosX = x * 32;
						static_cast<PlayerInfo*>(peer->data)->FishPosY = y * 32;
						static_cast<PlayerInfo*>(peer->data)->Fishing = true;
						static_cast<PlayerInfo*>(peer->data)->LastBait = getItemDef(tile).name;
						SendFishingState(peer);
						for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, currentPeer)) {
								SendFishing(currentPeer, static_cast<PlayerInfo*>(peer->data)->netID, x, y);
							}
						}
					}
					else
					{
						static_cast<PlayerInfo*>(peer->data)->FishPosX = 0;
						static_cast<PlayerInfo*>(peer->data)->FishPosY = 0;
						static_cast<PlayerInfo*>(peer->data)->Fishing = false;
						send_state(peer);
						Player::OnSetPos(peer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y);
					}
				}
				return;
			}
			if (static_cast<PlayerInfo*>(peer->data)->Fishing)
			{
				static_cast<PlayerInfo*>(peer->data)->FishPosX = 0;
				static_cast<PlayerInfo*>(peer->data)->FishPosY = 0;
				static_cast<PlayerInfo*>(peer->data)->Fishing = false;
				send_state(peer);
				Player::OnSetPos(peer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y);
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wSit perfectly while fishing`w!", 0, true);
				return;
			}
			if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3494)
			{
				if (world->owner == "" || static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || isMod(peer))
				{
					switch (tile)
					{
					case 3478:
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
						{
							return;
						}
						world->items[x + (y * world->width)].red = true;
						world->items[x + (y * world->width)].green = false;
						world->items[x + (y * world->width)].blue = false;
						UpdateVisualsForBlock(peer, true, x, y, world);
						return;
					case 3480:
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
						{
							return;
						}
						world->items[x + (y * world->width)].red = true;
						world->items[x + (y * world->width)].green = true;
						world->items[x + (y * world->width)].blue = false;
						UpdateVisualsForBlock(peer, true, x, y, world);
						return;
					case 3482:
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
						{
							return;
						}
						world->items[x + (y * world->width)].red = false;
						world->items[x + (y * world->width)].green = true;
						world->items[x + (y * world->width)].blue = false;
						UpdateVisualsForBlock(peer, true, x, y, world);
						return;
					case 3484:
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK || world->items[x + (y * world->width)].foreground == 2946)
						{
							return;
						}
						world->items[x + (y * world->width)].red = false;
						world->items[x + (y * world->width)].green = true;
						world->items[x + (y * world->width)].blue = true;
						UpdateVisualsForBlock(peer, true, x, y, world);
						return;
					case 3486:
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK || world->items[x + (y * world->width)].foreground == 2946)
						{
							return;
						}
						world->items[x + (y * world->width)].red = false;
						world->items[x + (y * world->width)].green = false;
						world->items[x + (y * world->width)].blue = true;
						UpdateVisualsForBlock(peer, true, x, y, world);
						return;
					case 3488:
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK || world->items[x + (y * world->width)].foreground == 2946)
						{
							return;
						}
						world->items[x + (y * world->width)].red = true;
						world->items[x + (y * world->width)].green = false;
						world->items[x + (y * world->width)].blue = true;
						UpdateVisualsForBlock(peer, true, x, y, world);
						return;
					case 3490:
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK || world->items[x + (y * world->width)].foreground == 2946)
						{
							return;
						}
						world->items[x + (y * world->width)].red = true;
						world->items[x + (y * world->width)].green = true;
						world->items[x + (y * world->width)].blue = true;
						UpdateVisualsForBlock(peer, true, x, y, world);
						return;
					case 3492:
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK || world->items[x + (y * world->width)].foreground == 2946)
						{
							return;
						}
						world->items[x + (y * world->width)].red = false;
						world->items[x + (y * world->width)].green = false;
						world->items[x + (y * world->width)].blue = false;
						UpdateVisualsForBlock(peer, true, x, y, world);
						return;
					default: break;
					}
				}
			}
			if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3066 && world->items[x + (y * world->width)].fire)
			{
				if (tile == 822)
				{
					SendThrowEffect(peer, 822, static_cast<PlayerInfo*>(peer->data)->netID, -1, 150, 0, x * 32 + 16, y * 32 + 16);
					world->items[x + (y * world->width)].fire = false;
					UpdateBlockState(peer, x, y, true, world);
					ENetPeer* net_peer;
					for (net_peer = server->peers;
						net_peer < &server->peers[server->peerCount];
						++net_peer)
					{
						if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, net_peer))
						{
							Player::OnParticleEffect(net_peer, 149, x * 32, y * 32, 0);
						}
					}
				}
				else
				{
					ENetPeer* net_peer;
					for (net_peer = server->peers;
						net_peer < &server->peers[server->peerCount];
						++net_peer)
					{
						if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, net_peer))
						{
							Player::OnParticleEffect(net_peer, 149, x * 32, y * 32, 0);
						}
					}
					world->items[x + (y * world->width)].fire = false;
					UpdateBlockState(peer, x, y, true, world);
				}
			}
			if (world->owner != "" && !isWorldOwner(peer, world) && !isWorldAdmin(peer, world) && !isMod(peer))
			{
				if (static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || isMod(peer) || tile == world->interactableid || tile == 5640)
				{
					// everything ok
				}
				else if (isWorldAdmin(peer, world))
				{
					if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
					{
						string ownername = PlayerDB::getProperName(world->owner);
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`2Access Granted`w)", 0, true);
						Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
						return;
					}
				}
				else if (world->isPublic)
				{
					if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
					{
						string ownername = PlayerDB::getProperName(world->owner);
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`9Open to Public`w)", 0, true);
						Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
						return;
					}
				}
				else if (world->isEvent)
				{
					if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
					{
						string ownername = PlayerDB::getProperName(world->owner);
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`4No Access`w)", 0, true);
						Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
						return;
					}
					else if (world->items[x + (y * world->width)].foreground != world->interactableid)
					{
						Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
						return;
					}
				}
				else
				{
					if (static_cast<PlayerInfo*>(peer->data)->haveGrowId == false)
					{
						Player::OnTextOverlay(peer, "`#Create `9Grow-ID `#First`9!");
					}
					else
					{
						Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
						return;
					}
				}
				if (tile == 18 && isMod(peer))
				{
					if (isWorldAdmin(peer, world) && !isWorldOwner(peer, world))
					{
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
						{
							string ownername = PlayerDB::getProperName(world->owner);
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`2Access Granted`w)", 0, true);
						}
					}
					else if (world->isPublic && !isWorldOwner(peer, world))
					{
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
						{
							string ownername = PlayerDB::getProperName(world->owner);
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`9Open to Public`w)", 0, true);
						}
					}
					else if (world->isEvent && !isWorldOwner(peer, world))
					{
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
						{
							string ownername = PlayerDB::getProperName(world->owner);
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`4No Access`w)", 0, true);
						}
					}
				}
				if (tile == 242 || tile == 2408 || tile == 1796 || tile == 4428 || tile == 7188 || tile == 8470 || tile == 9290 || tile == 9308 || tile == 9504 || tile == 2950 || tile == 4802 || tile == 5260 || tile == 5814 || tile == 5980 || tile == 9640 || tile == 10410)
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`0Only one `$World Lock `0Can be placed in a world!", 0, true);
					return;
				}
			}
			if (world->owner != "")
			{
				if (tile == 242 || tile == 2408 || tile == 1796 || tile == 4428 || tile == 7188 || tile == 8470 || tile == 9290 || tile == 9308 || tile == 9504 || tile == 2950 || tile == 4802 || tile == 5260 || tile == 5814 || tile == 5980 || tile == 9640 || tile == 10410)
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`0Only one `$World Lock `0Can be placed in a world!", 0, true);
					return;
				}
			}

			if (world->items[x + (y * world->width)].foreground == 10 && tile == 3400)
			{
				if (static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || isMod(peer) || world->owner == "")
				{
					RemoveInventoryItem(3400, 1, peer, true);
					world->items[x + (y * world->width)].foreground = 392;
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
					data3.plantingTree = 392;
					ENetPeer* currentPeer;
					for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
					{
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, currentPeer))
						{
							auto raw = packPlayerMoving(&data3);
							raw[2] = dicenr;
							raw[3] = dicenr;
							SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
						}
					}
					for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
					{
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
						Player::OnParticleEffect(currentPeer, 44, x * 32, y * 32, 0);
					}
				}
			}

			if (isSeed(world->items[x + (y * world->width)].foreground) && tile == 228 || isSeed(world->items[x + (y * world->width)].foreground) && tile == 1778) {
				if (calcBanDuration(world->items[x + (y * world->width)].growtime) == 0) {
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "This tree has already bloomed, don't waste your spray on it!", 0, true);
					return;
				}
				int NewGrowTime = 0;
				int InternalGrowTime = 0;
				if (tile == 228) {
					NewGrowTime = calcBanDuration(world->items[x + (y * world->width)].growtime) - 3600;
					RemoveInventoryItem(228, 1, peer, true);
				}
				if (tile == 1778) {
					NewGrowTime = calcBanDuration(world->items[x + (y * world->width)].growtime) - 86400;
					RemoveInventoryItem(1778, 1, peer, true);
				}
				if (NewGrowTime < 0) NewGrowTime = 0;
				world->items[x + (y * world->width)].growtime = (GetCurrentTimeInternalSeconds() + NewGrowTime);
				int growTimeSeed = getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity * getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity * getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity;
				growTimeSeed += 30 * getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity;
				if (world->items[x + (y * world->width)].foreground - 1 == 954) growTimeSeed = 1800;
				if (world->items[x + (y * world->width)].foreground - 1 == 340) growTimeSeed = 3600;
				if (world->items[x + (y * world->width)].foreground - 1 == 5666) growTimeSeed = 2700;
				if (world->items[x + (y * world->width)].foreground - 1 == 4584) growTimeSeed = 2400;
				if (world->items[x + (y * world->width)].foreground - 1 == 4762) growTimeSeed = 14544;
				if (world->items[x + (y * world->width)].foreground - 1 == 7382) growTimeSeed = 22544;
				if (world->items[x + (y * world->width)].foreground - 1 == 9460) growTimeSeed = 29544;
				if (world->items[x + (y * world->width)].foreground - 1 == 9468) growTimeSeed = 36544;
				if (world->items[x + (y * world->width)].foreground - 1 == 10024) growTimeSeed = 56544;
				if (world->items[x + (y * world->width)].foreground - 1 == 10029) growTimeSeed = 86400;
				InternalGrowTime = growTimeSeed - calcBanDuration(world->items[x + (y * world->width)].growtime);
				UpdateTreeVisuals(peer, world->items[x + (y * world->width)].foreground, x, y, world->items[x + (y * world->width)].background, world->items[x + (y * world->width)].fruitcount, InternalGrowTime, true, 0);
				if (calcBanDuration(world->items[x + (y * world->width)].growtime) == 0) {
					Player::OnTextOverlay(peer, "" + getItemDef(world->items[x + (y * world->width)].foreground - 1).name + " Tree grew to full size!");
				}
				else if (tile == 228) {
					Player::OnTextOverlay(peer, "" + getItemDef(world->items[x + (y * world->width)].foreground - 1).name + " Tree aged `$1`` hours");
				}
				else if (tile == 1778) {
					Player::OnTextOverlay(peer, "" + getItemDef(world->items[x + (y * world->width)].foreground - 1).name + " Tree aged `$1`` day");
				}
				Player::PlayAudio(peer, "audio/spray.wav", 0);
				return;
			}

			if (world->items[x + (y * world->width)].foreground == 2946 && tile != 18 && tile != 32 && tile > 0)
			{
				if (static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || isMod(peer))
				{
					using namespace std::chrono;
					if (static_cast<PlayerInfo*>(peer->data)->lastDISPLAY + 1000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count())
					{
						static_cast<PlayerInfo*>(peer->data)->lastDISPLAY = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
						auto iscontains = false;
						SearchInventoryItem(peer, tile, 1, iscontains);
						if (!iscontains) return;
						else
						{
							auto xSize = world->width;
							auto ySize = world->height;
							if (xSize == 100 && ySize == 60)
							{
								auto n = tile;
								if (getItemDef(n).properties & Property_Untradable || n == 6336 || n == 8552 || n == 9472 || n == 5640 || n == 9482 || n == 9356 || n == 9492 || n == 9498 || n == 8774 || n == 1790 || n == 2592 || n == 1784 || n == 1792 || n == 1794 || n == 7734 || n == 8306 || n == 9458)
								{
									Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You can't display untradeable items.", 0, true);
									return;
								}
								if (getItemDef(n).blockType == BlockTypes::LOCK || n == 2946)
								{
									Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Sorry, no displaying Display Blocks or Locks.", 0, true);
									return;
								}
								auto targetworld = getPlyersWorld(peer);
								if (targetworld->items[x + (y * targetworld->width)].intdata == 0)
								{
									targetworld->items[x + (y * targetworld->width)].intdata = tile;
									ENetPeer* currentPeer;
									for (currentPeer = server->peers;
										currentPeer < &server->peers[server->peerCount];
										++currentPeer)
									{
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
										if (isHere(peer, currentPeer))
										{
											UpdateVisualsForBlock(currentPeer, true, x, y, targetworld);
											SendThrowEffect(currentPeer, tile, static_cast<PlayerInfo*>(peer->data)->netID, -1, 150, 0, x * 32 + 16, y * 32 + 16);
										}
									}
									RemoveInventoryItem(n, 1, peer, true);
									updateplayerset(peer, n);
								}
								else
								{
									Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Remove what's in there first!", 0, true);
								}
								return;
							}
							else
							{
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Display blocks cannot be used in uranus worlds!", 0, true);
								return;
							}
						}
					}
					else
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Slow down while using display blocks!", 0, true);;
						return;
					}
				}
				else
				{
					if (world->owner == "")
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "This area must be locked to put your item on display!", 0, true);
					}
					else if (getPlyersWorld(peer)->isPublic)
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "That area is owned by " + world->owner + "", 0, true);
					}
					else
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "That area is owned by " + world->owner + "", 0, true);
					}
					return;
				}
			}
			if (getItemDef(tile).blockType == BlockTypes::CONSUMABLE || getItemDef(tile).blockType == BlockTypes::CLOTHING) return;
			break;
		}
	}
	if (causedBy != -1)
	{
		auto iscontains = false;
		SearchInventoryItem(peer, tile, 1, iscontains);
		if (!iscontains) return;
	}
	ENetPeer* currentPeer;
	if (tile == 18)
	{
		if (world->items[x + (y * world->width)].background == 6864 && world->items[x + (y * world->width)].foreground == 0) return;
		if (world->items[x + (y * world->width)].background == 0 && world->items[x + (y * world->width)].foreground == 0) return;
		ItemDefinition brak;
		if (world->items[x + (y * world->width)].foreground != 0)
		{
			brak = getItemDef(world->items[x + (y * world->width)].foreground);
		}
		else
		{
			brak = getItemDef(world->items[x + (y * world->width)].background);
		}
		data.packetType = 0x8;
		data.plantingTree = 6;
		using namespace std::chrono;

		if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 10390 && tile == 18) 
		{
			if (isWorldOwner(peer, world) || isMod(peer) || world->isPublic || world->owner == "")
			{
				//data.packetType = 0x3;
				//data.netID = causedBy;
				int kek = world->items[x + (y * world->width)].foreground;
				//data.plantingTree = 18;
				if (world->items[x + (y * world->width)].foreground != 0)
				{
					kek = world->items[x + (y * world->width)].foreground;
					//world->items[x + (y * world->width)].foreground = 0;
				}
				else
				{
					kek = world->items[x + (y * world->width)].background;
					//world->items[x + (y * world->width)].foreground = 0;
					//world->items[x + (y * world->width)].background = 0;
				}
				ENetPeer* net_peer;
				for (net_peer = server->peers;
					net_peer < &server->peers[server->peerCount];
					++net_peer)
				{
					if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (isHere(peer, net_peer))
					{
						//auto rawx = packPlayerMoving(&data);
						//SendPacketRaw(4, rawx, 56, nullptr, net_peer, ENET_PACKET_FLAG_RELIABLE);
						SendParticleEffect(net_peer, x * 32, y * 32, kek, 97, 0);
					}
				}
			}
		}

		if (static_cast<PlayerInfo*>(peer->data)->PunchPotion && tile == 18 || static_cast<PlayerInfo*>(peer->data)->cloth_necklace == 6260 && tile == 18 && static_cast<PlayerInfo*>(peer->data)->Subscriber)
		{
			if (world->items[x + (y * world->width)].foreground == 4762 || world->items[x + (y * world->width)].foreground == 7382 || world->items[x + (y * world->width)].foreground == 9468 || world->items[x + (y * world->width)].foreground == 10024 || world->items[x + (y * world->width)].foreground == 10028 || world->items[x + (y * world->width)].foreground == 9460 || world->items[x + (y * world->width)].foreground == 340 || world->items[x + (y * world->width)].foreground == 954 || world->items[x + (y * world->width)].foreground == 5666)
			{
				if (isWorldOwner(peer, world) || isMod(peer) || world->isPublic || world->owner == "")
				{
					data.packetType = 0x3;
					data.netID = causedBy;
					int kek = world->items[x + (y * world->width)].foreground;
					data.plantingTree = 18;
					if (world->items[x + (y * world->width)].foreground == 4762) /*amethyst*/
					{
						SendFarmableDrop(peer, 150);
						SendGuildPoints(peer, 1);
						SendXP(peer, 2);
						SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
					}
					else if (world->items[x + (y * world->width)].foreground == 7382) /*Onyx*/
					{
						SendFarmableDrop(peer, 250);
						SendGuildPoints(peer, 2);
						SendXP(peer, 2);
						SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
					}
					else if (world->items[x + (y * world->width)].foreground == 9468) /*Diamondstone*/
					{
						SendFarmableDrop(peer, 600);
						SendGuildPoints(peer, 5);
						SendXP(peer, 10);
						SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
					}
					else if (world->items[x + (y * world->width)].foreground == 10024) /*Pinkdiamond*/
					{
						SendFarmableDrop(peer, 1200);
						SendGuildPoints(peer, 7);
						SendXP(peer, 10);
						SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
					}
					else if (world->items[x + (y * world->width)].foreground == 340) /*Chands*/
					{
						SendFarmableDropCustom(peer, 15, 35);
						SendGuildPoints(peer, 3);
						SendXP(peer, 3);
						SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
					}
					else if (world->items[x + (y * world->width)].foreground == 954) /*sugar cane*/
					{
						SendFarmableDropCustom(peer, 1, 8);
						SendGuildPoints(peer, 1);
						SendXP(peer, 1);
						SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
					}
					else if (world->items[x + (y * world->width)].foreground == 5666) /*laser grid*/
					{
						SendFarmableDropCustom(peer, 5, 15);
						SendGuildPoints(peer, 2);
						SendXP(peer, 2);
						SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
					}
					else if (world->items[x + (y * world->width)].foreground == 10028) /*Citrine*/
					{
						SendFarmableDrop(peer, 2200);
						SendGuildPoints(peer, 10);
						SendXP(peer, 15);
						SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
					}
					else if (world->items[x + (y * world->width)].foreground == 9460) /*Smaraged*/
					{
						SendFarmableDrop(peer, 350);
						SendGuildPoints(peer, 3);
						SendXP(peer, 5);
						SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
					}
					if (world->items[x + (y * world->width)].foreground != 0)
					{
						kek = world->items[x + (y * world->width)].foreground;
						world->items[x + (y * world->width)].foreground = 0;
					}
					else
					{
						kek = world->items[x + (y * world->width)].background;
						world->items[x + (y * world->width)].foreground = 0;
						world->items[x + (y * world->width)].background = 0;
					}
					ENetPeer* net_peer;
					for (net_peer = server->peers;
						net_peer < &server->peers[server->peerCount];
						++net_peer)
					{
						if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, net_peer))
						{
							auto rawx = packPlayerMoving(&data);
							SendPacketRaw(4, rawx, 56, nullptr, net_peer, ENET_PACKET_FLAG_RELIABLE);
							SendParticleEffect(net_peer, x * 32, y * 32, kek, 97, 0);
						}
					}
					return;
				}
			}
		}
		if ((duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count() - world->items[x + (y * world->width)].breakTime >= 4000 && static_cast<PlayerInfo*>(peer->data)->cloth_hand != 10390)
		{
			world->items[x + (y * world->width)].breakTime = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
			world->items[x + (y * world->width)].breakLevel = 4;
		}
		else
		{
			if (y < world->height && world->items[x + (y * world->width)].breakLevel + 4 >= brak.breakHits * 4 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 10390 && tile == 18)
			{
				data.packetType = 0x3;
				data.netID = causedBy;
				data.plantingTree = 18;
				data.punchX = x;
				data.punchY = y;
				world->items[x + (y * world->width)].breakLevel = 0;
				auto hi = data.punchX * 32;
				auto hi2 = data.punchY * 32;
				if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9456)
				{
					std::vector<int> lists{ 0, 0, 0, 242, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
					int indexs = rand() % lists.size();
					auto values = lists[indexs];
					if (values == 242)
					{
						auto droplocs = rand() % 18;
						auto droploc = rand() % 18;
						DropItem(peer, -1, hi + droploc, hi2 + droplocs, 242, 1, 0);
					}
					else
					{
						Player::OnParticleEffect(peer, 72, hi, hi2, 0);
					}
				}
				if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9454)
				{
					Player::OnParticleEffect(peer, 108, hi, hi2, 0);
				}
				if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9452)
				{
					Player::OnParticleEffect(peer, 44, hi, hi2, 0);
				}
				if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9448)
				{
					Player::OnParticleEffect(peer, 58, hi, hi2, 0);
				}
				if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 2952)
				{
					Player::OnParticleEffect(peer, 97, hi, hi2, 0);
				}
				if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 1874)
				{
					Player::OnParticleEffect(peer, 97, hi, hi2, 0);
				}
				if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9430)
				{
					Player::OnParticleEffect(peer, 97, hi, hi2, 0);
				}
				if (world->items[x + (y * world->width)].foreground == 10024)
				{
					std::vector<int> list{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4426 };
					int index = rand() % list.size();
					auto value = list[index];
					if (value == 4426)
					{
						srand(GetTickCount());
						auto droploc = rand() % 18;
						auto droplocs = rand() % 18;
						DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, 4426, 1, 0);
					}
				}
				else if (world->items[x + (y * world->width)].foreground == 9460)
				{
					std::vector<int> list{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2410 };
					int index = rand() % list.size(); // pick a random index
					int value = list[index];
					if (value == 2410)
					{
						bool success = true;
						srand(GetTickCount());
						int droploc = rand() % 18;
						int droplocs = rand() % 18;
						DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, 2410, 1, 0);
						int hi = data.punchX * 32;
						int hi2 = data.punchY * 32;
					}
				}
				else if (world->items[x + (y * world->width)].foreground == 7382)
				{
					std::vector<int> list{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9240 };
					int index = rand() % list.size(); // pick a random index
					int value = list[index];
					if (value == 9240)
					{
						srand(GetTickCount());
						int droploc = rand() % 18;
						int droplocs = rand() % 18;
						DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, 9240, 1, 0);
					}
				}
				else if (world->items[x + (y * world->width)].foreground == 9414)
				{
					world->items[x + (y * world->width)].foreground = 0;
					int kuriPrizaDuot = rand() % 3 + 1;
					if (kuriPrizaDuot == 1)
					{
						int gemChance = rand() % 12000;
						GiveChestPrizeGems(peer, gemChance);
					}
					if (kuriPrizaDuot == 2)
					{
						int luck = rand() % 3 + 1;
						if (luck == 1)
						{
							GamePacket p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), static_cast<PlayerInfo*>(peer->data)->netID), "`^Your `1Luck `^Shines Away..."), 0));
							ENetPacket* packet2 = enet_packet_create(p2.data,
								p2.len,
								ENET_PACKET_FLAG_RELIABLE);
							enet_peer_send(peer, 0, packet2);
							delete p2.data;
						}
						if (luck == 2)
						{
							GamePacket p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), static_cast<PlayerInfo*>(peer->data)->netID), "`^The `1Ocean `9Gods `^Didn't Want To Play With You..."), 0));
							ENetPacket* packet2 = enet_packet_create(p2.data,
								p2.len,
								ENET_PACKET_FLAG_RELIABLE);
							enet_peer_send(peer, 0, packet2);
							delete p2.data;
						}
						if (luck == 3)
						{
							GamePacket p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), static_cast<PlayerInfo*>(peer->data)->netID), "`^You `9Starting `^To Feel `1Tired`^..."), 0));
							ENetPacket* packet2 = enet_packet_create(p2.data,
								p2.len,
								ENET_PACKET_FLAG_RELIABLE);
							enet_peer_send(peer, 0, packet2);
							delete p2.data;
						}
					}
					if (kuriPrizaDuot == 3)
					{
						int itemuMas[62] = { 9416, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 9416, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 9414, 9414, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 9414, 1796, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328 };
						int randIndex = rand() % 62;
						int itemId = itemuMas[randIndex];
						send_item(peer, itemId, 1, 9414);
					}
				}
				else if (world->items[x + (y * world->width)].foreground == 3402 || world->items[x + (y * world->width)].foreground == 392 || world->items[x + (y * world->width)].foreground == 9350)
				{
					if (world->items[x + (y * world->width)].foreground == 3402) static_cast<PlayerInfo*>(peer->data)->bootybreaken++;
					if (static_cast<PlayerInfo*>(peer->data)->bootybreaken >= 30)
					{
						static_cast<PlayerInfo*>(peer->data)->bootybreaken = 0;
						bool success = true;
						SaveItemMoreTimes(9350, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
						SendTradeEffect(peer, 9350, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
					}
					vector<int> list{ 362, 3398, 386, 4422, 364, 9340, 9342, 9332, 9334, 9336, 9338, 366, 2388, 7808, 7810, 4416, 7818, 7820, 5652, 7822, 7824, 5644, 390, 7826, 7830, 9324, 5658, 3396, 2384, 5660, 3400, 4418, 4412, 388, 3408, 1470, 3404, 3406, 2390, 5656, 5648, 2396, 384, 5664, 4424, 4400, 1458 };
					int itemid = list[rand() % list.size()];
					if (itemid == 1458) 
					{ 
						int target = 5;
						if (world->items[x + (y * world->width)].foreground == 9350) target = 10;
						if ((rand() % 10000) <= target) { }
						else itemid = 7808;
					}
					DropItem(peer, -1, x * 32 + rand() % 18, y * 32 + rand() % 18, itemid, 1, 0);
				}
				else if (world->items[x + (y * world->width)].foreground == 192 || world->items[x + (y * world->width)].foreground == 1004)
				{
					std::vector<int> list{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9490 };
					int index = rand() % list.size();
					int value = list[index];
					if (value == 9490)
					{
						srand(GetTickCount());
						int droploc = rand() % 18;
						int droplocs = rand() % 18;
						DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, 9490, 1, 0);
					}
				}
				else if (world->items[x + (y * world->width)].foreground == 2)
				{
					if (static_cast<PlayerInfo*>(peer->data)->cloth_back == 9506)
					{
						std::vector<int> list{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7382 };
						int index = rand() % list.size();
						int value = list[index];
						if (value == 7382)
						{
							srand(GetTickCount());
							int droploc = rand() % 18;
							int droplocs = rand() % 18;
							DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, 7382, 1, 0);
						}
					}
				}
				else if (world->items[x + (y * world->width)].foreground == 7382 || world->items[x + (y * world->width)].foreground == 10028 || world->items[x + (y * world->width)].foreground == 4762 || world->items[x + (y * world->width)].foreground == 9240 || world->items[x + (y * world->width)].foreground == 9460 || world->items[x + (y * world->width)].foreground == 9468)
				{
					std::vector<int> list{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9462 };
					int index = rand() % list.size();
					int value = list[index];
					if (value == 9462)
					{
						srand(GetTickCount());
						int droploc = rand() % 18;
						int droplocs = rand() % 18;
						DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, 9462, 1, 0);
					}
				}
				else if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 8452)
				{
					int i = data.punchX * 32;
					int i1 = data.punchY * 32;
					Player::OnParticleEffect(peer, 149, i, i1, 0);
				}
				if (world->items[x + (y * world->width)].foreground != 0)
				{
					if (world->items[x + (y * world->width)].foreground == 2978) {
						if (world->items[x + (y * world->width)].vcount != 0 || world->items[x + (y * world->width)].vdraw != 0) {
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Empty the machine before breaking it!", 0, true);
							return;
						}
						world->items[x + (y * world->width)].vcount = 0;
						world->items[x + (y * world->width)].vprice = 0;
						world->items[x + (y * world->width)].vid = 0;
						world->items[x + (y * world->width)].vdraw = 0;
						world->items[x + (y * world->width)].opened = false;
						world->items[x + (y * world->width)].rm = false;
						auto success = true;
						SaveItemMoreTimes(2978, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
					}
					if (world->items[x + (y * world->width)].foreground == 1420 || world->items[x + (y * world->width)].foreground == 6214) {
						auto squaresign = x + (y * world->width);
						auto ismannequin = std::experimental::filesystem::exists("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						if (ismannequin) {
							remove(("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json").c_str());
						}
						world->items[x + (y * world->width)].sign = "";
					}
					if (world->items[x + (y * world->width)].foreground == 6286)
					{
						if (isWorldOwner(peer, world) || world->owner == "" || isDev(peer) || isWorldAdmin(peer, world))
						{
							auto squaresign = x + (y * 100);
							auto isdbox = std::experimental::filesystem::exists("storageboxlvl1/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
							if (isdbox)
							{
								ifstream ifff("storageboxlvl1/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
								json j;
								ifff >> j;
								ifff.close();
								if (j["instorage"] > 0)
								{
									Player::OnTextOverlay(peer, "Empty the box first!");
									return;
								}
								remove(("storageboxlvl1/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json").c_str());
							}
							bool success = true;
							SaveItemMoreTimes(6286, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
						}
						else
						{
							Player::OnTextOverlay(peer, "only world owner can break the box!");
							return;
						}
					}
					if (world->items[x + (y * world->width)].foreground == 6288)
					{
						if (isWorldOwner(peer, world) || world->owner == "" || isDev(peer) || isWorldAdmin(peer, world))
						{
							auto squaresign = x + (y * 100);
							auto isdbox = std::experimental::filesystem::exists("storageboxlvl2/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
							if (isdbox)
							{
								ifstream ifff("storageboxlvl2/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
								json j;
								ifff >> j;
								ifff.close();
								if (j["instorage"] > 0)
								{
									Player::OnTextOverlay(peer, "Empty the box first!");
									return;
								}
								remove(("storageboxlvl2/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json").c_str());
							}
							bool success = true;
							SaveItemMoreTimes(6288, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
						}
						else
						{
							Player::OnTextOverlay(peer, "only world owner can break the box!");
							return;
						}
					}
					if (world->items[x + (y * world->width)].foreground == 6290)
					{
						if (isWorldOwner(peer, world) || world->owner == "" || isDev(peer) || isWorldAdmin(peer, world))
						{
							auto squaresign = x + (y * 100);
							auto isdbox = std::experimental::filesystem::exists("storageboxlvl3/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
							if (isdbox)
							{
								ifstream ifff("storageboxlvl3/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
								json j;
								ifff >> j;
								ifff.close();
								if (j["instorage"] > 0)
								{
									Player::OnTextOverlay(peer, "Empty the box first!");
									return;
								}
								remove(("storageboxlvl3/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json").c_str());
							}
							bool success = true;
							SaveItemMoreTimes(6290, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
						}
						else
						{
							Player::OnTextOverlay(peer, "only world owner can break the box!");
							return;
						}
					}
					if (world->items[x + (y * world->width)].foreground == 656)
					{
						if (isWorldOwner(peer, world) || world->owner == "" || isDev(peer) || isWorldAdmin(peer, world))
						{
							auto squaresign = x + (y * 100);
							auto isdbox = std::experimental::filesystem::exists("mailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
							if (isdbox)
							{
								ifstream ifff("mailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
								json j;
								ifff >> j;
								ifff.close();
								int count = j["inmail"];
								if (j["inmail"] > 0)
								{
									Player::OnTextOverlay(peer, "`wThere are `5" + to_string(count) + " `wletter(s) in the mailbox.");
								}
								remove(("mailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json").c_str());
							}
						}
						else
						{
							Player::OnTextOverlay(peer, "only world owner can break the mailbox!");
							return;
						}
					}
					if (world->items[x + (y * world->width)].foreground == 658)
					{
						if (isWorldOwner(peer, world) || world->owner == "" || isDev(peer) || isWorldAdmin(peer, world))
						{
							auto squaresign = x + (y * 100);
							auto isdbox = std::experimental::filesystem::exists("bulletinboard/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
							if (isdbox)
							{
								remove(("bulletinboard/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json").c_str());
							}
						}
						else
						{
							Player::OnTextOverlay(peer, "only world owner can break the bulletin board!");
							return;
						}
					}
					if (world->items[x + (y * world->width)].foreground == 1006)
					{
						if (isWorldOwner(peer, world) || world->owner == "" || isDev(peer) || isWorldAdmin(peer, world))
						{
							auto squaresign = x + (y * 100);
							auto isdbox = std::experimental::filesystem::exists("bluemailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
							if (isdbox)
							{
								ifstream ifff("bluemailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
								json j;
								ifff >> j;
								ifff.close();
								int count = j["inmail"];
								if (j["inmail"] > 0)
								{
									Player::OnTextOverlay(peer, "`wThere are `5" + to_string(count) + " `wletter(s) in the mailbox.");
								}
								remove(("bluemailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json").c_str());
							}
						}
						else
						{
							Player::OnTextOverlay(peer, "only world owner can break the mailbox!");
							return;
						}
					}
					if (world->items[x + (y * world->width)].foreground == 8878)
					{
						if (isWorldOwner(peer, world) || world->owner == "" || isDev(peer) || isWorldAdmin(peer, world))
						{
							auto squaresign = x + (y * 100);
							auto isdbox = std::experimental::filesystem::exists("safevault/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
							if (isdbox)
							{
								ifstream ifff("safevault/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
								json j;
								ifff >> j;
								ifff.close();
								if (j["insafe"] > 0)
								{
									Player::OnTextOverlay(peer, "Empty the safe first!");
									return;
								}
								remove(("safevault/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json").c_str());
							}
							bool success = true;
							SaveItemMoreTimes(8878, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
						}
						else
						{
							Player::OnTextOverlay(peer, "only world owner can break the safe fault!");
							return;
						}
					}
					if (world->items[x + (y * world->width)].foreground == 1240) {
						world->items[x + (y * world->width)].monitorname = "";
						world->items[x + (y * world->width)].monitoronline = false;
					}
					if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::GATEWAY) {
						world->items[x + (y * world->width)].opened = false;
					}
					if (world->items[x + (y * world->width)].foreground == 1452)
					{
						if (isWorldOwner(peer, world) || world->owner == "" || isDev(peer) || isWorldAdmin(peer, world))
						{
							auto squaresign = x + (y * 100);
							auto isdbox = std::experimental::filesystem::exists("donationboxes/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
							if (isdbox)
							{
								ifstream ifff("donationboxes/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
								json j;
								ifff >> j;
								ifff.close();
								if (j["donated"] > 0)
								{
									Player::OnTextOverlay(peer, "Empty donation box first!");
									return;
								}
								remove(("donationboxes/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json").c_str());
							}
						}
						else
						{
							Player::OnTextOverlay(peer, "only world owner can break donation box!");
							return;
						}
					}
					if (world->items[x + (y * world->width)].foreground == 1436)
					{
						if (isWorldOwner(peer, world) || world->owner == "")
						{
							remove(("securitycam/logs/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + ".txt").c_str());
							bool success = true;
							SaveItemMoreTimes(1436, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
						}
						else
						{
							Player::OnTextOverlay(peer, "only world owner can break security camera!");
							return;
						}
					}
					if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::DOOR)
					{
						if (isWorldOwner(peer, world) || world->owner == "" || isDev(peer)) {
							world->items[x + (y * world->width)].label = "";
							world->items[x + (y * world->width)].destWorld = "";
							world->items[x + (y * world->width)].destId = "";
							world->items[x + (y * world->width)].currId = "";
							world->items[x + (y * world->width)].password = "";
						}
					}
					int valgem;
					if (world->items[x + (y * world->width)].foreground == 10026) /*darkstone*/
					{
						srand(GetTickCount());
						int droploc = rand() % 18;
						int droplocs = rand() % 18;
						int itemid = rand() % maxItems;
						if (getItemDef(itemid).name.find("null_item") != string::npos) itemid = 10026;
						if (getItemDef(itemid).name.find("Subscription") != string::npos) itemid = 10026;
						string name = getItemDef(itemid).name;
						if (itemid % 2 == 0)
						{
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "The power of the dark stone dropped " + name + "!", 0, true);
							DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, itemid, 1, 0);
							int x1 = data.punchX * 32;
							int y1 = data.punchY * 32;
							ENetPeer* peer2;
							for (peer2 = server->peers;
								peer2 < &server->peers[server->peerCount];
								++peer2)
							{
								if (peer2->state != ENET_PEER_STATE_CONNECTED) continue;
								if (isHere(peer, peer2))
								{
									Player::OnParticleEffect(peer2, 182, x1, y1, 0);
								}
							}
						}
						else
						{
							itemid += 1;
							string name321 = getItemDef(itemid).name;
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "The power of the dark stone dropped " + name321 + "!", 0, true);
							DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, itemid, 1, 0);
							int hi1 = data.punchX * 32;
							int hi3 = data.punchY * 32;
							ENetPeer* peer2;
							for (peer2 = server->peers;
								peer2 < &server->peers[server->peerCount];
								++peer2)
							{
								if (peer2->state != ENET_PEER_STATE_CONNECTED) continue;
								if (isHere(peer, peer2))
								{
									Player::OnParticleEffect(peer2, 182, hi1, hi3, 0);
								}
							}
						}
					}
					else if (world->items[x + (y * world->width)].foreground == 4762)
					{ /*amethyst*/
						SendFarmableDrop(peer, 150);
						SendGuildPoints(peer, 1);
						SendXP(peer, 2);
						SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
					}
					else if (world->items[x + (y * world->width)].foreground == 7382)
					{ /*Onyx*/
						SendFarmableDrop(peer, 250);
						SendGuildPoints(peer, 2);
						SendXP(peer, 2);
						SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
					}
					else if (world->items[x + (y * world->width)].foreground == 9468)
					{ /*Diamondstone*/
						SendFarmableDrop(peer, 600);
						SendGuildPoints(peer, 5);
						SendXP(peer, 10);
						SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
					}
					else if (world->items[x + (y * world->width)].foreground == 10024)
					{ /*Pinkdiamond*/
						SendFarmableDrop(peer, 1200);
						SendGuildPoints(peer, 7);
						SendXP(peer, 10);
						SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
					}
					else if (world->items[x + (y * world->width)].foreground == 340) /*Chands*/
					{
						SendFarmableDropCustom(peer, 15, 35);
						SendGuildPoints(peer, 3);
						SendXP(peer, 3);
						SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
					}
					else if (world->items[x + (y * world->width)].foreground == 954) /*sugar cane*/
					{
						SendFarmableDropCustom(peer, 1, 8);
						SendGuildPoints(peer, 1);
						SendXP(peer, 1);
						SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
					}
					else if (world->items[x + (y * world->width)].foreground == 5666) /*laser grid*/
					{
						SendFarmableDropCustom(peer, 5, 15);
						SendGuildPoints(peer, 2);
						SendXP(peer, 2);
						SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
					}
					else if (world->items[x + (y * world->width)].foreground == 10028)
					{ /*Citrine*/
						SendFarmableDrop(peer, 2200);
						SendGuildPoints(peer, 10);
						SendXP(peer, 15);
						SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
					}
					else if (world->items[x + (y * world->width)].foreground == 9460)
					{ /*Smaraged*/
						SendFarmableDrop(peer, 350);
						SendGuildPoints(peer, 3);
						SendXP(peer, 5);
						SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
					}
					else if (world->items[x + (y * world->width)].foreground == 9474)
					{
						std::vector<int> list{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9476 };
						int index = rand() % list.size();
						int value = list[index];
						if (value == 9476)
						{
							srand(GetTickCount());
							int droploc = rand() % 18;
							int droplocs = rand() % 18;
							DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, 9476, 1, 0);
						}
						else
						{
							valgem = rand() % 30000;
							SendXP(peer, 30);
							std::ifstream ifs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
							std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`^You found `9" + std::to_string(valgem) + " `2Gems`w!", 0, true);
							int gembux = atoi(content.c_str());
							int fingembux = gembux + valgem;
							ofstream myfile;
							myfile.open("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
							myfile << fingembux;
							myfile.close();
							int gemcalc = gembux + valgem;
							GamePacket pp = packetEnd(appendInt(appendString(createPacket(), "OnSetBux"), gemcalc));
							ENetPacket* packetpp = enet_packet_create(pp.data, pp.len, ENET_PACKET_FLAG_RELIABLE);
							enet_peer_send(peer, 0, packetpp);
							delete pp.data;
						}
					}
					else if (world->items[x + (y * world->width)].foreground == 7628)
					{
						std::vector<int> lists{ 1, 2, 3, 4 };
						srand(GetTickCount());
						int indexs = rand() % lists.size();
						int values = lists[indexs];
						if (values == 1)
						{
							std::vector<int> is{ 3, 3, 3, 6, 6, 6, 5, 5, 5 };
							srand(GetTickCount());
							int indexs1 = rand() % is.size();
							int droplocs = rand() % 18;
							int droploc = rand() % 18;
							int count = is[indexs1];
							DropItem(peer, -1, hi + droploc, hi2 + droplocs, 9426, count, 0);
						}
						if (values == 2)
						{
							std::vector<int> is{ 30, 30, 30, 60, 60, 60, 50, 50, 50 };
							srand(GetTickCount());
							int indexs1 = rand() % is.size();
							int droplocs = rand() % 18;
							int droploc = rand() % 18;
							int count = is[indexs1];
							DropItem(peer, -1, hi + droploc, hi2 + droplocs, 242, count, 0);
						}
						if (values == 3)
						{
							srand(GetTickCount());
							int droplocs = rand() % 18;
							int droploc = rand() % 18;
							DropItem(peer, -1, hi + droploc, hi2 + droplocs, 1796, 1, 0);
						}
						if (values == 4)
						{
							std::vector<int> is{ 30, 30, 30, 60, 60, 60, 50, 50, 50 };
							srand(GetTickCount());
							int indexs1 = rand() % is.size();
							int droplocs = rand() % 18;
							int droploc = rand() % 18;
							int count = is[indexs1];
							DropItem(peer, -1, hi + droploc, hi2 + droplocs, 9440, count, 0);
						}
						SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
					}
					else if (world->items[x + (y * world->width)].foreground == 9442)
					{
						std::vector<int> lists{ 10, 50, 50, 50, 50, 10, 100, 100, 50, 100, 10 };
						srand(GetTickCount());
						int indexs = rand() % lists.size();
						int droplocs = rand() % 18;
						int droploc = rand() % 18;
						int droplocs1 = rand() % 18;
						int droploc1 = rand() % 18;
						int droplocs3 = rand() % 18;
						int droploc3 = rand() % 18;
						int values = lists[indexs];
						std::vector<int> lists1{ 10, 50, 50, 50, 50, 10, 100, 100, 50, 100, 10 };
						int indexs1 = rand() % lists1.size();
						int values1 = lists[indexs1];
						std::vector<int> lists3{ 10, 50, 50, 50, 50, 10, 100, 100, 50, 100, 10 };
						int indexs3 = rand() % lists3.size();
						int values3 = lists[indexs3];
						DropItem(peer, -1, hi + droploc, hi2 + droplocs, 112, values, 0);
						DropItem(peer, -1, hi + droploc1, hi2 + droplocs1, 112, values1, 0);
						DropItem(peer, -1, hi + droploc3, hi2 + droplocs3, 112, values3, 0);
					}
					else if (world->items[x + (y * world->width)].foreground == 7960)
					{
						valgem = rand() % 9;
						if (valgem > 0)
						{
							SendXP(peer, 4);
							AddPlayerFragmentFire(peer, valgem);
						}
						else
						{
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`^Your `2Luck `^Shines away...", 0, true);
						}
						SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
					}
					else if (world->items[x + (y * world->width)].foreground == 9440)
					{
						std::vector<int> lists{ 10, 50, 50, 50, 50, 10, 100, 100, 50, 100, 10 };
						srand(GetTickCount());
						int indexs = rand() % lists.size();
						int droplocs = rand() % 18;
						int droploc = rand() % 18;
						int droplocs1 = rand() % 18;
						int droploc1 = rand() % 18;
						int droplocs3 = rand() % 18;
						int droploc3 = rand() % 18;
						int values = lists[indexs];
						std::vector<int> lists1{ 10, 50, 50, 50, 50, 10, 100, 100, 50, 100, 10 };
						int indexs1 = rand() % lists1.size();
						int values1 = lists[indexs1];
						std::vector<int> lists3{ 10, 50, 50, 50, 50, 10, 100, 100, 50, 100, 10 };
						int indexs3 = rand() % lists3.size();
						int values3 = lists[indexs3];
						DropItem(peer, -1, hi + droploc, hi2 + droplocs, 112, values, 0);
						DropItem(peer, -1, hi + droploc1, hi2 + droplocs1, 112, values1, 0);
						DropItem(peer, -1, hi + droploc3, hi2 + droplocs3, 112, values3, 0);
						SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
					}
					else if (world->items[x + (y * world->width)].foreground == 9240)
					{
						if (static_cast<PlayerInfo*>(peer->data)->skill == "Farmer")
						{
							valgem = rand() % 1500;
							SendXP(peer, 3);
							std::ifstream ifs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
							std::string content((std::istreambuf_iterator<char>(ifs)),
								(std::istreambuf_iterator<char>()));
							GamePacket p3 = packetEnd(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), static_cast<PlayerInfo*>(peer->data)->netID), "`^You found `9" + std::to_string(valgem) + " `2Gems`w!"));
							ENetPacket* packet3 = enet_packet_create(p3.data,
								p3.len,
								ENET_PACKET_FLAG_RELIABLE);
							enet_peer_send(peer, 0, packet3);
							delete p3.data;
							int gembux = atoi(content.c_str());
							int fingembux = gembux + valgem;
							ofstream myfile;
							myfile.open("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
							myfile << fingembux;
							myfile.close();
							int gemcalc = gembux + valgem;
							GamePacket pp = packetEnd(appendInt(appendString(createPacket(), "OnSetBux"), gemcalc));
							ENetPacket* packetpp = enet_packet_create(pp.data,
								pp.len,
								ENET_PACKET_FLAG_RELIABLE);
							enet_peer_send(peer, 0, packetpp);
							delete pp.data;
						}
						else
						{
							valgem = rand() % 1200;
							SendXP(peer, 3);
							std::ifstream ifs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
							std::string content((std::istreambuf_iterator<char>(ifs)),
								(std::istreambuf_iterator<char>()));
							GamePacket p3 = packetEnd(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), static_cast<PlayerInfo*>(peer->data)->netID), "`^You found `9" + std::to_string(valgem) + " `2Gems`w!"));
							ENetPacket* packet3 = enet_packet_create(p3.data,
								p3.len,
								ENET_PACKET_FLAG_RELIABLE);
							enet_peer_send(peer, 0, packet3);
							delete p3.data;
							int gembux = atoi(content.c_str());
							int fingembux = gembux + valgem;
							ofstream myfile;
							myfile.open("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
							myfile << fingembux;
							myfile.close();
							int gemcalc = gembux + valgem;
							GamePacket pp = packetEnd(appendInt(appendString(createPacket(), "OnSetBux"), gemcalc));
							ENetPacket* packetpp = enet_packet_create(pp.data,
								pp.len,
								ENET_PACKET_FLAG_RELIABLE);
							enet_peer_send(peer, 0, packetpp);
							delete pp.data;
						}
						SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
						world->items[x + (y * world->width)].foreground = 0;
					}
					else if (world->items[x + (y * world->width)].foreground == 9462)
					{
						std::vector<int> lists{ 50, 100, 50, 100, 50, 100, 50, 100 };
						srand(GetTickCount());
						int indexs = rand() % lists.size();
						int droploc = rand() % 18; // pick a random index
						int droplocs = rand() % 18;
						int values = lists[indexs];
						DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, 112, values, 0);
						std::vector<int> listsss{ 5, 10, 15, 50, 40, 25, 30, 20 };
						srand(GetTickCount());
						int indexsss = rand() % listsss.size();
						int xpvalue = listsss[indexsss];
						Player::OnConsoleMessage(peer, "`^You have obtained `@" + std::to_string(xpvalue) + " `!Experience`^!");
						SendXP(peer, xpvalue);
						SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
						world->items[x + (y * world->width)].foreground = 0;
					}
					else if (world->items[x + (y * world->width)].foreground == 8)
					{
						world->items[x + (y * world->width)].foreground = 0;
						valgem = rand() % 6;
						if (valgem > 0)
						{
							SendXP(peer, 1);
							AddPlayerFragmentDark(peer, valgem);
						}
					}
					else if(world->items[x + (y * world->width)].foreground == 242 || world->items[x + (y * world->width)].foreground == 2408 || world->items[x + (y * world->width)].foreground == 1796 || world->items[x + (y * world->width)].foreground == 4428 || world->items[x + (y * world->width)].foreground == 7188 || world->items[x + (y * world->width)].foreground == 8470 || world->items[x + (y * world->width)].foreground == 9290 || world->items[x + (y * world->width)].foreground == 9308 || world->items[x + (y * world->width)].foreground == 9504 || world->items[x + (y * world->width)].foreground == 2950 || world->items[x + (y * world->width)].foreground == 4802 || world->items[x + (y * world->width)].foreground == 5260 || world->items[x + (y * world->width)].foreground == 5814 || world->items[x + (y * world->width)].foreground == 5980 || world->items[x + (y * world->width)].foreground == 9640 || world->items[x + (y * world->width)].foreground == 10410)
					{
						for (auto i = 0; i < world->width * world->height; i++)
						{
							if (world->items[i].foreground == 1790)
							{
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`oTake all `cUntradeable `oBlocks, before breaking The `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`o!", 0, true);
								return;
							}
						}
						if (static_cast<PlayerInfo*>(peer->data)->NickPrefix == "") updateworldremove(peer);
						auto success = true;
						auto info = getPlyersWorld(peer);
						auto nameworld = info->name;
						SaveItemMoreTimes(info->items[x + (y * info->width)].foreground, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
						ENetPeer* net_peer;
						for (net_peer = server->peers;
							net_peer < &server->peers[server->peerCount];
							++net_peer)
						{
							if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, net_peer))
							{
								Player::OnConsoleMessage(net_peer, "`5[`w" + nameworld + " `ohas had its `$" + getItemDef(info->items[x + (y * info->width)].foreground).name + " `oremoved!`5]");
								Player::PlayAudio(net_peer, "audio/fireball.wav", 0);
							}
							if (static_cast<PlayerInfo*>(net_peer->data)->rawName == info->owner && info->owner != "")
							{
								for (int i = 0; i < static_cast<PlayerInfo*>(net_peer->data)->worldsowned.size(); i++)
								{
									if (static_cast<PlayerInfo*>(net_peer->data)->worldsowned[i] == info->name)
									{
										static_cast<PlayerInfo*>(net_peer->data)->worldsowned.erase(static_cast<PlayerInfo*>(net_peer->data)->worldsowned.begin() + i);
									}
								}
							}
						}

						if (info->owner != "")
						{
							auto existsplayer = std::experimental::filesystem::exists("players/"+ info->owner+".json");
							if (existsplayer)
							{
								vector<string> hisowned;
								ifstream fg("players/" + info->owner + ".json");
								json j;
								fg >> j;
								fg.close();

								hisowned = j["worldsowned"].get<vector<string>>();

								for (int i = 0; i < hisowned.size(); i++)
								{
									if (hisowned[i] == info->name)
									{
										hisowned.erase(hisowned.begin() + i);
									}
								}
								j["worldsowned"] = hisowned;
								ofstream fs("players/" + info->owner + ".json");
								fs << j;
								fs.close();
							}					
						}
						if (info->owner != static_cast<PlayerInfo*>(peer->data)->rawName && info->owner != "")
						{
							ofstream removelocklogs("logs/removelock.txt", ios::app);
							removelocklogs << "User " << static_cast<PlayerInfo*>(peer->data)->rawName << " removed lock from " << nameworld << " world. This world was locked by " << info->owner << endl;
							removelocklogs.close();
						}
						info->owner = "";
						info->ownerID = 0;
						info->isPublic = false;
						info->ownerDisplayName = "";
						info->accessed.clear();
						info->silence = false;
						info->items[x + (y * info->width)].foreground = 0;

					}
					else if (world->items[x + (y * world->width)].foreground == 9488)
					{
						auto success = true;
						SaveItemMoreTimes(9488, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
					}
					else if (world->items[x + (y * world->width)].foreground == 6016)
					{
						auto success = true;
						SaveItemMoreTimes(6016, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
					}
					else if (world->items[x + (y * world->width)].foreground == 9432)
					{
						auto success = true;
						SaveItemMoreTimes(9432, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
					}
					else if (world->items[x + (y * world->width)].foreground == 9170)
					{
						auto success = true;
						SaveItemMoreTimes(9170, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
					}
					else if (world->items[x + (y * world->width)].foreground == 1008)
					{
						auto success = true;
						SaveItemMoreTimes(1008, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
					}
					else if (world->items[x + (y * world->width)].foreground == 1790)
					{
						auto success = true;
						SaveItemMoreTimes(1790, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
					}
					else if (world->items[x + (y * world->width)].foreground == 3528) {
						auto success = true;
						SaveItemMoreTimes(3528, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
						world->items[x + (y * world->width)].intdata = 0;
					}
					else if (world->items[x + (y * world->width)].foreground == 2946)
					{
						if (static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || world->owner == "" || isDev(peer))
						{
							auto targetworld = getPlyersWorld(peer);
							if (targetworld->items[x + (y * targetworld->width)].intdata != 0)
							{
								auto success = true;
								SaveItemMoreTimes(targetworld->items[x + (y * targetworld->width)].intdata, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You picked up 1 " + getItemDef(targetworld->items[x + (y * targetworld->width)].intdata).name + ".", 0, true);
								targetworld->items[x + (y * targetworld->width)].intdata = 0;
							}
						}
						else
						{
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Only the block's owner can break it!", 0, true);
							return;
						}
					}
					else if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::SUCKER)
					{
						if (static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || world->owner == "" || isDev(peer))
						{
							auto squaresign = x + (y * 100);
							string Sucker = "";
							if (world->items[x + (y * world->width)].foreground == 5638)
							{
								Sucker = "magplant";
							}
							if (world->items[x + (y * world->width)].foreground == 6946)
							{
								Sucker = "gaiabeacon";
							}
							if (world->items[x + (y * world->width)].foreground == 6948)
							{
								Sucker = "unstabletesseract";
							}
							auto currentworld = static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(squaresign);
							auto existmagplant = std::experimental::filesystem::exists(Sucker + "/storeditem/" + currentworld + ".txt");
							if (existmagplant)
							{
								auto existmagplantcount = std::experimental::filesystem::exists(Sucker + "/count/" + currentworld + ".txt");
								if (existmagplantcount)
								{
									auto count = 0;
									ifstream fdss(Sucker + "/count/" + currentworld + ".txt");
									fdss >> count;
									fdss.close();
									if (count == 0)
									{
										remove((Sucker + "/storeditem/" + currentworld + ".txt").c_str());
										remove((Sucker + "/count/" + currentworld + ".txt").c_str());
										auto success = true;
										SaveItemMoreTimes(world->items[x + (y * world->width)].foreground, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
									}
									else
									{
										Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Empty the " + getItemDef(world->items[x + (y * world->width)].foreground).name + " before breaking it!", 0, true);
										return;
									}
								}
							}
							else
							{
								auto success = true;
								SaveItemMoreTimes(world->items[x + (y * world->width)].foreground, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
							}
						}
						else
						{
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Only the block's owner can break it!", 0, true);
							return;
						}
					}
					else if (getItemDef(world->items[x + (y * world->width)].foreground).rarity != 999)
					{
						if (getItemDef(world->items[x + (y * world->width)].foreground).properties & Property_Dropless) return;
						SendTileData(peer, x, y, data.punchX, data.punchY);
					}
					if (static_cast<PlayerInfo*>(peer->data)->rawName != world->owner && isDev(peer) && world->owner != "") /*Log moderator actions into security camera*/
					{
						auto islegitnow = false;
						for (auto i = 0; i < world->width * world->height; i++)
						{
							if (world->items[i].foreground == 1436)
							{
								islegitnow = true;
								break;
							}
						}
						if (islegitnow == true)
						{
							string toLogs = "";
							toLogs = static_cast<PlayerInfo*>(peer->data)->displayName + " `w(" + static_cast<PlayerInfo*>(peer->data)->rawName + "`w) `5Break `2" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`5.";
							ofstream breaklogs("securitycam/logs/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + ".txt", ios::app);
							breaklogs << toLogs << endl;
							breaklogs.close();
						}
					}
					if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 7912)
					{
						if (world->items[x + (y * world->width)].foreground == 7382 || world->items[x + (y * world->width)].foreground == 4762 || world->items[x + (y * world->width)].foreground == 9240 || world->items[x + (y * world->width)].foreground == 9460 || world->items[x + (y * world->width)].foreground == 9468 || world->items[x + (y * world->width)].foreground == 9462 || world->items[x + (y * world->width)].foreground == 1008 || world->items[x + (y * world->width)].foreground == 1796 || world->items[x + (y * world->width)].foreground == 242 || world->items[x + (y * world->width)].foreground == 9290 || world->items[x + (y * world->width)].foreground == 8470 || world->items[x + (y * world->width)].foreground == 8 || world->items[x + (y * world->width)].foreground == 9308)
						{
							world->items[x + (y * world->width)].foreground = 0;
						}
						else
						{
							if (world->items[x + (y * world->width)].foreground == 2)
							{
								world->items[x + (y * world->width)].foreground = 0;
								srand(GetTickCount());
								valgem = rand() % 10;
								SendXP(peer, 1);
								AddPlayerFragmentEarth(peer, valgem);
							}
							else
							{
								world->items[x + (y * world->width)].foreground = 0;
								SendXP(peer, 1);
							}
						}
					}
					else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 7166)
					{
						if (world->items[x + (y * world->width)].foreground == 7382 || world->items[x + (y * world->width)].foreground == 4762 || world->items[x + (y * world->width)].foreground == 9240 || world->items[x + (y * world->width)].foreground == 9460 || world->items[x + (y * world->width)].foreground == 9468 || world->items[x + (y * world->width)].foreground == 9462 || world->items[x + (y * world->width)].foreground == 1008 || world->items[x + (y * world->width)].foreground == 1796 || world->items[x + (y * world->width)].foreground == 242 || world->items[x + (y * world->width)].foreground == 9290 || world->items[x + (y * world->width)].foreground == 8470 || world->items[x + (y * world->width)].foreground == 8 || world->items[x + (y * world->width)].foreground == 9308)
						{
							world->items[x + (y * world->width)].foreground = 0;
						}
						else
						{
							if (world->items[x + (y * world->width)].foreground == 2)
							{
								world->items[x + (y * world->width)].foreground = 0;
								srand(GetTickCount());
								valgem = rand() % 10;
								SendXP(peer, 1);
								AddPlayerFragmentEarth(peer, valgem);
							}
							else
							{
								world->items[x + (y * world->width)].foreground = 0;
								SendXP(peer, 1);
							}
						}
					}
					else if (static_cast<PlayerInfo*>(peer->data)->cloth_feet == 8834)
					{
						if (world->items[x + (y * world->width)].foreground == 7382 || world->items[x + (y * world->width)].foreground == 4762 || world->items[x + (y * world->width)].foreground == 9240 || world->items[x + (y * world->width)].foreground == 9460 || world->items[x + (y * world->width)].foreground == 9468 || world->items[x + (y * world->width)].foreground == 9462 || world->items[x + (y * world->width)].foreground == 1008 || world->items[x + (y * world->width)].foreground == 1796 || world->items[x + (y * world->width)].foreground == 242 || world->items[x + (y * world->width)].foreground == 9290 || world->items[x + (y * world->width)].foreground == 8470 || world->items[x + (y * world->width)].foreground == 8 || world->items[x + (y * world->width)].foreground == 9308)
						{
							world->items[x + (y * world->width)].foreground = 0;
						}
						else
						{
							if (world->items[x + (y * world->width)].foreground == 2)
							{
								world->items[x + (y * world->width)].foreground = 0;
								srand(GetTickCount());
								valgem = rand() % 10;
								SendXP(peer, 1);
								AddPlayerFragmentEarth(peer, valgem);
							}
							else
							{
								world->items[x + (y * world->width)].foreground = 0;
								SendXP(peer, 1);
							}
						}
					}
					else
					{
						if (world->items[x + (y * world->width)].foreground == 2)
						{
							world->items[x + (y * world->width)].foreground = 0;
							srand(GetTickCount());
							SendXP(peer, 1);
							valgem = rand() % 10;
							AddPlayerFragmentEarth(peer, valgem);
						}
						else
						{
							valgem = rand() % 5;
							world->items[x + (y * world->width)].foreground = 0;
						}
					}
#pragma region crystals
					if (world->items[x + (y * world->width)].foreground == 1008 || world->items[x + (y * world->width)].foreground == 1796 || world->items[x + (y * world->width)].foreground == 242 || world->items[x + (y * world->width)].foreground == 9290 || world->items[x + (y * world->width)].foreground == 8470 || world->items[x + (y * world->width)].foreground == 8 || world->items[x + (y * world->width)].foreground == 9308)
					{
						world->items[x + (y * world->width)].foreground = 0;
					}
#pragma endregion
					if (static_cast<PlayerInfo*>(peer->data)->xp >= (static_cast<PlayerInfo*>(peer->data)->level * 1500) && static_cast<PlayerInfo*>(peer->data)->level < 125)
					{
						static_cast<PlayerInfo*>(peer->data)->xp = 0;
						static_cast<PlayerInfo*>(peer->data)->level = static_cast<PlayerInfo*>(peer->data)->level + 1;
						ENetPeer* net_peer;
						for (net_peer = server->peers;
							net_peer < &server->peers[server->peerCount];
							++net_peer)
						{
							if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, net_peer))
							{
								auto name = static_cast<PlayerInfo*>(peer->data)->displayName;
								auto p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), name + " `wis now level " + std::to_string(static_cast<PlayerInfo*>(peer->data)->level) + "!"));
								string text = "action|play_sfx\nfile|audio/levelup2.wav\ndelayMS|0\n";
								auto dst = new BYTE[5 + text.length()];
								BYTE zero = 0;
								auto type = 3;
								memcpy(dst, &type, 4);
								memcpy(dst + 4, text.c_str(), text.length());
								memcpy(dst + 4 + text.length(), &zero, 1);
								auto packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(net_peer, 0, packet);
								auto packet2 = enet_packet_create(dst, 5 + text.length(), ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(net_peer, 0, packet2);
								delete dst;
								delete p.data;
								auto p3 = packetEnd(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), static_cast<PlayerInfo*>(peer->data)->netID), name + " `wis now level " + std::to_string(static_cast<PlayerInfo*>(peer->data)->level) + "!"));
								auto packet3 = enet_packet_create(p3.data, p3.len, ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(net_peer, 0, packet3);
							}
						}
						ifstream fg("players/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".json");
						json j;
						fg >> j;
						fg.close();

						j["level"] = static_cast<PlayerInfo*>(peer->data)->level;
						j["xp"] = static_cast<PlayerInfo*>(peer->data)->xp;

						ofstream fs("players/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".json");
						fs << j;
						fs.close();
					}
				}
				else
				{
					if (getItemDef(world->items[x + (y * world->width)].background).rarity != 999 && tile == 18)
					{
						if (getItemDef(world->items[x + (y * world->width)].background).properties & Property_Dropless) return;
						SendTileData(peer, x, y, data.punchX, data.punchY);
					}
					SendDropSeed(peer, x, y, world->items[x + (y * world->width)].background);
					world->items[x + (y * world->width)].background = 6864;
					if (world->items[x + (y * world->width)].foreground == 1008 || world->items[x + (y * world->width)].foreground == 1796 || world->items[x + (y * world->width)].foreground == 242 || world->items[x + (y * world->width)].foreground == 9290 || world->items[x + (y * world->width)].foreground == 8470 || world->items[x + (y * world->width)].foreground == 8 || world->items[x + (y * world->width)].foreground == 9308)
					{
						world->items[x + (y * world->width)].foreground = 0;
					}
					if (static_cast<PlayerInfo*>(peer->data)->xp >= (static_cast<PlayerInfo*>(peer->data)->level * 1500) && static_cast<PlayerInfo*>(peer->data)->level < 125)
					{
						static_cast<PlayerInfo*>(peer->data)->xp = 0;
						static_cast<PlayerInfo*>(peer->data)->level = static_cast<PlayerInfo*>(peer->data)->level + 1;
						ENetPeer* net_peer;
						for (net_peer = server->peers;
							net_peer < &server->peers[server->peerCount];
							++net_peer)
						{
							if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, net_peer))
							{
								auto name = static_cast<PlayerInfo*>(peer->data)->displayName;
								auto p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), name + " `wis now level " + std::to_string(static_cast<PlayerInfo*>(peer->data)->level) + "!"));
								string text = "action|play_sfx\nfile|audio/levelup2.wav\ndelayMS|0\n";
								auto dst = new BYTE[5 + text.length()];
								BYTE zero = 0;
								auto type = 3;
								memcpy(dst, &type, 4);
								memcpy(dst + 4, text.c_str(), text.length());
								memcpy(dst + 4 + text.length(), &zero, 1);
								auto packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(net_peer, 0, packet);
								auto packet2 = enet_packet_create(dst, 5 + text.length(), ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(net_peer, 0, packet2);
								delete dst;
								delete p.data;
								auto p3 = packetEnd(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), static_cast<PlayerInfo*>(peer->data)->netID), name + " `wis now level " + std::to_string(static_cast<PlayerInfo*>(peer->data)->level) + "!"));
								auto packet3 = enet_packet_create(p3.data, p3.len, ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(net_peer, 0, packet3);
							}
							data.plantingTree = tile;
						}
						ifstream fg("players/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".json");
						json j;
						fg >> j;
						fg.close();

						j["level"] = static_cast<PlayerInfo*>(peer->data)->level;
						j["xp"] = static_cast<PlayerInfo*>(peer->data)->xp;

						ofstream fs("players/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".json");
						fs << j;
						fs.close();
					}
				}
			}
			else
			{
				if (y < world->height)
				{
					world->items[x + (y * world->width)].breakTime = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
					world->items[x + (y * world->width)].breakLevel += 4;
				}
			}
		}
	}
	else
	{
		if (world->items[x + (y * world->width)].foreground != 0 && getItemDef(tile).blockType != BlockTypes::BACKGROUND && getItemDef(tile).blockType != BlockTypes::GROUND_BLOCK) return;
		for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				bool RotatedRight = false;
				auto xpos = x * 32;
				auto ppos = static_cast<PlayerInfo*>(currentPeer->data)->x;
				if (static_cast<PlayerInfo*>(currentPeer->data)->x < x * 32) RotatedRight = true;
				if (RotatedRight) ppos += 19;
				xpos = xpos / 32;
				ppos = ppos / 32;
				if (ppos == xpos && static_cast<PlayerInfo*>(currentPeer->data)->y / 32 == y && getItemDef(tile).properties != Property_NoSeed && getItemDef(tile).properties != Property_Foreground && getItemDef(tile).properties != Property_MultiFacing && getItemDef(tile).blockType != BlockTypes::SEED && getItemDef(tile).blockType != BlockTypes::STEAM && getItemDef(tile).blockType != BlockTypes::UNKNOWN && getItemDef(tile).blockType != BlockTypes::VENDING && getItemDef(tile).blockType != BlockTypes::ANIM_FOREGROUND && getItemDef(tile).blockType != BlockTypes::BULLETIN_BOARD && getItemDef(tile).blockType != BlockTypes::FACTION && getItemDef(tile).blockType != BlockTypes::CHEST && getItemDef(tile).blockType != BlockTypes::GEMS && getItemDef(tile).blockType != BlockTypes::MAGIC_EGG && getItemDef(tile).blockType != BlockTypes::CRYSTAL && getItemDef(tile).blockType != BlockTypes::MAILBOX && getItemDef(tile).blockType != BlockTypes::PORTAL && getItemDef(tile).blockType != BlockTypes::PLATFORM && getItemDef(tile).blockType != BlockTypes::SFX_FOREGROUND && getItemDef(tile).blockType != BlockTypes::CHEMICAL_COMBINER && getItemDef(tile).blockType != BlockTypes::SWITCH_BLOCK && getItemDef(tile).blockType != BlockTypes::TRAMPOLINE && getItemDef(tile).blockType != BlockTypes::TOGGLE_FOREGROUND && getItemDef(tile).blockType != BlockTypes::GROUND_BLOCK && getItemDef(tile).blockType != BlockTypes::BACKGROUND && getItemDef(tile).blockType != BlockTypes::MAIN_DOOR && getItemDef(tile).blockType != BlockTypes::SIGN && getItemDef(tile).blockType != BlockTypes::DOOR && getItemDef(tile).blockType != BlockTypes::CHECKPOINT && getItemDef(tile).blockType != BlockTypes::GATEWAY && getItemDef(tile).blockType != BlockTypes::TREASURE && getItemDef(tile).blockType != BlockTypes::WEATHER) return;
			}
		}
		if (causedBy != -1)
		{
			auto iscontains = false;
			SearchInventoryItem(peer, tile, 1, iscontains);
			if (!iscontains) return;
		}
		for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
		{
			if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == tile)
			{
				if (static_cast<unsigned int>(static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount) > 1)
				{
					static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount--;
					static_cast<PlayerInfo*>(peer->data)->needsaveinventory = true;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->inventory.items.erase(static_cast<PlayerInfo*>(peer->data)->inventory.items.begin() + i);
					static_cast<PlayerInfo*>(peer->data)->needsaveinventory = true;
				}
			}
		}
		if (tile != 18 && tile != 32 && getItemDef(tile).blockType != BlockTypes::CONSUMABLE)
		{
			bool Farmable = false;
			if (tile == 7382 || tile == 4762 || tile == 10024 || tile == 9468 || tile == 9460 || tile == 10029 || tile == 340 || tile == 954 || tile == 5666) Farmable = true;
			if (static_cast<PlayerInfo*>(peer->data)->PlacePotion && Farmable)
			{
				SendPlacingEffect(peer, data.punchX, data.punchY, 229);
			}
			else if (static_cast<PlayerInfo*>(peer->data)->cloth_back == 9466)
			{
				SendPlacingEffect(peer, data.punchX, data.punchY, 125);
			}
		}
		if (getItemDef(tile).blockType == BlockTypes::BACKGROUND || getItemDef(tile).blockType == BlockTypes::GROUND_BLOCK)
		{
			world->items[x + (y * world->width)].background = tile;
		}
		else if (getItemDef(tile).blockType == BlockTypes::SEED)
		{
			world->items[x + (y * world->width)].foreground = tile;
		}
		else
		{
			world->items[x + (y * world->width)].foreground = tile;
		}
		if (world->areLogsEnabled == true)
		{
			ofstream savelogs("worldlogs/" + world->name + ".txt", std::ios_base::app);
			savelogs << static_cast<PlayerInfo*>(peer->data)->rawName << " placed " << getItemDef(tile).name << "(" << tile << ")" << endl;
		}
		if (getItemDef(tile).blockType == BlockTypes::LOCK) {
			if (tile == 202 || tile == 204 || tile == 206 || tile == 4994) {
				if (!RestrictedArea_check(world, x, y)) {
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Cant place " + getItemDef(tile).name + " here!", 0, false);
					return;
				}
				world->items[x + (y * world->width)].monitorname = static_cast<PlayerInfo*>(peer->data)->rawName;
				isSmallLock = true;
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Area locked.", 0, false);
				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (isHere(peer, currentPeer)) {
						Player::PlayAudio(currentPeer, "audio/use_lock.wav", 0);
					}
				}
			}
			else {
				world->owner = static_cast<PlayerInfo*>(peer->data)->rawName;
				world->isPublic = false;
				static_cast<PlayerInfo*>(peer->data)->worldsowned.push_back(static_cast<PlayerInfo*>(peer->data)->currentWorld);
				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (isHere(peer, currentPeer)) {
						Player::OnConsoleMessage(currentPeer, "`3[`w" + world->name + " `ohas been `$" + getItemDef(tile).name + "ed `oBy " + static_cast<PlayerInfo*>(peer->data)->displayName + "`3]");
						Player::PlayAudio(currentPeer, "audio/use_lock.wav", 0);
					}
				}
				if (static_cast<PlayerInfo*>(peer->data)->displayName.find("`") != string::npos) {}
				else {
					static_cast<PlayerInfo*>(peer->data)->displayName = "`2" + static_cast<PlayerInfo*>(peer->data)->displayName;
					auto p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), "`2" + static_cast<PlayerInfo*>(peer->data)->displayName));
					memcpy(p7.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
					auto packet7 = enet_packet_create(p7.data, p7.len, ENET_PACKET_FLAG_RELIABLE);
					delete p7.data;
					for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, currentPeer)) {
							if (static_cast<PlayerInfo*>(peer->data)->adminLevel >= 0) {
								enet_peer_send(currentPeer, 0, packet7);
							}
						}
					}
				}
				isLock = true;
			}
		}
		world->items[x + (y * world->width)].breakLevel = 0;
	}
	for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			auto raw = packPlayerMoving(&data);
			raw[2] = dicenr;
			raw[3] = dicenr;
			SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
	if (getItemDef(tile).properties & Property_MultiFacing)
	{
		if (((PlayerInfo*)(peer->data))->RotatedLeft == true) {
			int squaresign = x + (y * 100);
			world->items[squaresign].rotatedLeft = true;
			world->items[squaresign].flipped = !world->items[squaresign].flipped;
			updateRotatedItem(peer, world->items[squaresign].foreground, squaresign % world->width, squaresign / world->width, "", world->items[squaresign].background);
		}
	}
	if (tile == 3798) {
		int squaresign = x + (y * 100);
		sendTileData(peer, x, y, 0x10, world->items[squaresign].foreground, world->items[squaresign].background, EntranceTiles(0x20, ((PlayerInfo*)(peer->data))->netID));
	}
	if (VendUpdate)
	{
		if (world->items[x + (y * world->width)].opened && world->items[x + (y * world->width)].vcount < world->items[x + (y * world->width)].vprice) {
			UpdateVend(peer, x, y, 0, false, world->items[x + (y * world->width)].vprice, world->items[x + (y * world->width)].background, world->items[x + (y * world->width)].opened);
		}
		else UpdateVend(peer, x, y, world->items[x + (y * world->width)].vid, false, world->items[x + (y * world->width)].vprice, world->items[x + (y * world->width)].background, world->items[x + (y * world->width)].opened);
	}
	if (isLock) {
		sendTileData(peer, x, y, 0x10, world->items[x + (y * world->width)].foreground, world->items[x + (y * world->width)].background, lockTileDatas(0x20, ((PlayerInfo*)(peer->data))->netID, 0, 0, false, 100));
	}
	if (isMannequin) {
		updateMannequin(peer, world->items[x + (y * world->width)].foreground, x, y, world->items[x + (y * world->width)].background, world->items[x + (y * world->width)].sign, 0, 0, 0, 0, 0, 0, 0, 0, 0, true, 0);
	}
	if (isSmallLock) {
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer)) {
				if (world->items[x + (y * world->width)].monitorname == static_cast<PlayerInfo*>(peer->data)->rawName) ApplyLockPacket(world, currentPeer, x, y, world->items[x + (y * world->width)].foreground, static_cast<PlayerInfo*>(peer->data)->netID);
				else ApplyLockPacket(world, currentPeer, x, y, world->items[x + (y * world->width)].foreground, -1);
			}
		}
	}
	if (isTree) {
		int growTimeSeed = getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity * getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity * getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity;
		growTimeSeed += 30 * getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity;
		if (world->items[x + (y * world->width)].foreground - 1 == 954) growTimeSeed = 1800;
		if (world->items[x + (y * world->width)].foreground - 1 == 340) growTimeSeed = 3600;
		if (world->items[x + (y * world->width)].foreground - 1 == 5666) growTimeSeed = 2700;
		if (world->items[x + (y * world->width)].foreground - 1 == 4584) growTimeSeed = 2400;
		if (world->items[x + (y * world->width)].foreground - 1 == 4762) growTimeSeed = 14544;
		if (world->items[x + (y * world->width)].foreground - 1 == 7382) growTimeSeed = 22544;
		if (world->items[x + (y * world->width)].foreground - 1 == 9460) growTimeSeed = 29544;
		if (world->items[x + (y * world->width)].foreground - 1 == 9468) growTimeSeed = 36544;
		if (world->items[x + (y * world->width)].foreground - 1 == 10024) growTimeSeed = 56544;
		if (world->items[x + (y * world->width)].foreground - 1 == 10029) growTimeSeed = 86400;
		world->items[x + (y * world->width)].growtime = (GetCurrentTimeInternalSeconds() + growTimeSeed);
		if (getItemDef(world->items[x + (y * world->width)].foreground).rarity == 999) {
			world->items[x + (y * world->width)].fruitcount = (rand() % 1) + 1;
		}
		else {
			world->items[x + (y * world->width)].fruitcount = (rand() % 6) + 1;
		}
		if (getItemDef(world->items[x + (y * world->width)].foreground - 1).blockType == BlockTypes::CLOTHING) world->items[x + (y * world->width)].fruitcount = (rand() % 2) + 1;

		int chanceofbuff = 1;
		if (static_cast<PlayerInfo*>(peer->data)->level >= 8) chanceofbuff = 1;
		if (static_cast<PlayerInfo*>(peer->data)->level >= 11) chanceofbuff = 2;
		if (static_cast<PlayerInfo*>(peer->data)->level >= 8 && rand() % 100 <= chanceofbuff) {
			Player::OnConsoleMessage(peer, "Flawless bonus reduced 1 hour grow time");
			int NewGrowTime = 0;
			int InternalGrowTime = 0;
			NewGrowTime = calcBanDuration(world->items[x + (y * world->width)].growtime) - 3600;
			if (NewGrowTime < 0) NewGrowTime = 0;
			world->items[x + (y * world->width)].growtime = (GetCurrentTimeInternalSeconds() + NewGrowTime);
			int growTimeSeed = getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity * getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity * getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity;
			growTimeSeed += 30 * getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity;
			if (world->items[x + (y * world->width)].foreground - 1 == 954) growTimeSeed = 1800;
			if (world->items[x + (y * world->width)].foreground - 1 == 340) growTimeSeed = 3600;
			if (world->items[x + (y * world->width)].foreground - 1 == 5666) growTimeSeed = 2700;
			if (world->items[x + (y * world->width)].foreground - 1 == 4584) growTimeSeed = 2400;
			if (world->items[x + (y * world->width)].foreground - 1 == 4762) growTimeSeed = 14544;
			if (world->items[x + (y * world->width)].foreground - 1 == 7382) growTimeSeed = 22544;
			if (world->items[x + (y * world->width)].foreground - 1 == 9460) growTimeSeed = 29544;
			if (world->items[x + (y * world->width)].foreground - 1 == 9468) growTimeSeed = 36544;
			if (world->items[x + (y * world->width)].foreground - 1 == 10024) growTimeSeed = 56544;
			if (world->items[x + (y * world->width)].foreground - 1 == 10029) growTimeSeed = 86400;
			InternalGrowTime = growTimeSeed - calcBanDuration(world->items[x + (y * world->width)].growtime);
			UpdateTreeVisuals(peer, world->items[x + (y * world->width)].foreground, x, y, world->items[x + (y * world->width)].background, world->items[x + (y * world->width)].fruitcount, InternalGrowTime, true, 0);
		}
	}
	if (isScience) {
		world->items[x + (y * world->width)].growtime = (GetCurrentTimeInternalSeconds() + getItemDef(world->items[x + (y * world->width)].foreground).growTime);
	}
	if (isHeartMonitor) {
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer)) {
				world->items[x + (y * world->width)].monitorname = static_cast<PlayerInfo*>(peer->data)->displayName;
				world->items[x + (y * world->width)].monitoronline = true;
				sendHMonitor(currentPeer, x, y, static_cast<PlayerInfo*>(peer->data)->displayName, true, world->items[x + (y * world->width)].background);
			}
		}
	}
	if (isgateway)
	{
		updateEntrance(peer, world->items[x + (y * world->width)].foreground, x, y, 0, world->items[x + (y * world->width)].background, true);
	}
	if (isDoor) {
		updateDoor(peer, world->items[x + (y * world->width)].foreground, x, y, world->items[x + (y * world->width)].background, getItemDef(world->items[x + (y * world->width)].foreground).name, false, true);
	}
}
inline void sendWorld(ENetPeer* peer, WorldInfo* worldInfo) {
	if (!worldInfo) return;
	if (worldInfo->items == nullptr) return;
	auto zero = 0;
	static_cast<PlayerInfo*>(peer->data)->droppeditemcount = worldInfo->droppedCount;
	static_cast<PlayerInfo*>(peer->data)->joinClothesUpdated = false;
	string asdf = "0400000004A7379237BB2509E8E0EC04F8720B050000000000000000FBBB0000010000007D920100FDFDFDFD04000000040000000000000000000000070000000000";
	auto worldName = worldInfo->name;
	auto xSize = worldInfo->width;
	auto ySize = worldInfo->height;
	auto square = xSize * ySize;
	auto nameLen = static_cast<__int16_t>(worldName.length());
	int payloadLen = asdf.length() / 2;
	auto dataLen = payloadLen + 2 + nameLen + 12 + (square * 8) + 4 + 100;
	auto offsetData = dataLen - 100;
	int allocMem = payloadLen + 2 + nameLen + 12 + (square * 8) + 4 + 16000 + 100 + (worldInfo->droppedItems.size() * 20);
	auto data = new BYTE[allocMem];
	memset(data, 0, allocMem);
	for (auto i = 0; i < asdf.length(); i += 2)
	{
		char x = ch2n(asdf[i]);
		x = x << 4;
		x += ch2n(asdf[i + 1]);
		memcpy(data + (i / 2), &x, 1);
	}
	__int16_t item = 0;
	auto smth = 0;
	for (auto i = 0; i < square * 8; i += 4) memcpy(data + payloadLen + i + 14 + nameLen, &zero, 4);
	for (auto i = 0; i < square * 8; i += 8) memcpy(data + payloadLen + i + 14 + nameLen, &item, 2);
	memcpy(data + payloadLen, &nameLen, 2);
	memcpy(data + payloadLen + 2, worldName.c_str(), nameLen);
	memcpy(data + payloadLen + 2 + nameLen, &xSize, 4);
	memcpy(data + payloadLen + 6 + nameLen, &ySize, 4);
	memcpy(data + payloadLen + 10 + nameLen, &square, 4);
	auto blockPtr = data + payloadLen + 14 + nameLen;
	auto sizeofblockstruct = 8;
	for (auto i = 0; i < square; i++)
	{
		int tile = worldInfo->items[i].foreground;
		sizeofblockstruct = 8;
		if (tile == 6)
		{
			auto type = 0x00000000;
			if (worldInfo->items[i].activated)
				type |= 0x00200000;
			if (worldInfo->items[i].flipped)
				type |= 0x00400000;
			if (worldInfo->items[i].water)
				type |= 0x04000000;
			if (worldInfo->items[i].glue)
				type |= 0x08000000;
			if (worldInfo->items[i].fire)
				type |= 0x10000000;
			if (worldInfo->items[i].red)
				type |= 0x20000000;
			if (worldInfo->items[i].green)
				type |= 0x40000000;
			if (worldInfo->items[i].blue)
				type |= 0x80000000;
			memcpy(blockPtr, &tile, 2);
			memcpy(blockPtr + 4, &type, 4);
			BYTE btype = 1;
			memcpy(blockPtr + 8, &btype, 1);
			string doorText = "EXIT";
			auto doorTextChars = doorText.c_str();
			auto length = static_cast<short>(doorText.size());
			memcpy(blockPtr + 9, &length, 2);
			memcpy(blockPtr + 11, doorTextChars, length);
			sizeofblockstruct += 4 + length;
			dataLen += 4 + length;
		}
		else if (getItemDef(tile).blockType == BlockTypes::SIGN || tile == 1420 || tile == 6124)
		{
			auto type = 0x00000000;
			if (worldInfo->items[i].activated)
				type |= 0x00200000;
			if (worldInfo->items[i].flipped)
				type |= 0x00400000;
			if (worldInfo->items[i].water)
				type |= 0x04000000;
			if (worldInfo->items[i].glue)
				type |= 0x08000000;
			if (worldInfo->items[i].fire)
				type |= 0x10000000;
			if (worldInfo->items[i].red)
				type |= 0x20000000;
			if (worldInfo->items[i].green)
				type |= 0x40000000;
			if (worldInfo->items[i].blue)
				type |= 0x80000000;
			memcpy(blockPtr, &worldInfo->items[i].foreground, 2);
			memcpy(blockPtr + 4, &type, 4);
			BYTE btype = 2;
			memcpy(blockPtr + 8, &btype, 1);
			auto signText = worldInfo->items[i].sign;
			auto signTextChars = signText.c_str();
			auto length = static_cast<short>(signText.size());
			memcpy(blockPtr + 9, &length, 2);
			memcpy(blockPtr + 11, signTextChars, length);
			auto minus1 = -1;
			memcpy(blockPtr + 11 + length, &minus1, 4);
			sizeofblockstruct += 3 + length + 4;
			dataLen += 3 + length + 4;
		}
		else if (tile == 3832) {
			int type = 0x00010000;
			memcpy(blockPtr, &worldInfo->items[i].foreground, 2);
			memcpy(blockPtr + 4, &type, 4);
			BYTE btype = 0x31;
			memcpy(blockPtr + 8, &btype, 1);


			short flags = 0;
			int item = worldInfo->stuffID;
			int gravity = worldInfo->stuff_gravity;
			int spinhehe = worldInfo->stuff_spin;

			memcpy(blockPtr + 9, &item, 4);
			memcpy(blockPtr + 13, &gravity, 4);
			memcpy(blockPtr + 17, &spinhehe, 4);
			sizeofblockstruct += 10;
			dataLen += 10;
		}
		else if (tile == 2946)
		{
			auto type = 0x00000000;
			if (worldInfo->items[i].activated)
				type |= 0x00200000;
			if (worldInfo->items[i].flipped)
				type |= 0x00400000;
			if (worldInfo->items[i].water)
				type |= 0x04000000;
			if (worldInfo->items[i].glue)
				type |= 0x08000000;
			if (worldInfo->items[i].fire)
				type |= 0x10000000;
			if (worldInfo->items[i].red)
				type |= 0x20000000;
			if (worldInfo->items[i].green)
				type |= 0x40000000;
			if (worldInfo->items[i].blue)
				type |= 0x80000000;
			memcpy(blockPtr, &worldInfo->items[i].foreground, 2);
			memcpy(blockPtr + 4, &type, 4);
			BYTE btype = 0x17;
			memcpy(blockPtr + 8, &btype, 1);
			auto item1 = worldInfo->items[i].intdata;
			memcpy(blockPtr + 9, &item1, 4);
			sizeofblockstruct += 5;
			dataLen += 5;
		}
		else if (tile == 5000) {
			memcpy(blockPtr, &worldInfo->items[i].foreground, 2);
			int type = 0x00000000;

			// type 1 = locked
			if (worldInfo->items[i].activated)
				type |= 0x00200000;
			if (worldInfo->items[i].flipped)
				type |= 0x00400000;
			if (worldInfo->items[i].water)
				type |= 0x04000000;
			if (worldInfo->items[i].glue)
				type |= 0x08000000;
			if (worldInfo->items[i].fire)
				type |= 0x10000000;
			if (worldInfo->items[i].red)
				type |= 0x20000000;
			if (worldInfo->items[i].green)
				type |= 0x40000000;
			if (worldInfo->items[i].blue)
				type |= 0x80000000;
			memcpy(blockPtr + 4, &type, 4);
			BYTE btype = 0x28;
			memcpy(blockPtr + 8, &btype, 1);
			int item = 0;
			int gravity = 0;
			short flags = 0;
			item = worldInfo->bgID;
			memcpy(blockPtr + 9, &item, 4);
			sizeofblockstruct += 5;
			dataLen += 5;
		}
		else if (getItemDef(tile).blockType == BlockTypes::DOOR || getItemDef(tile).blockType == BlockTypes::PORTAL)
		{
			auto type = 0x00000000;
			if (worldInfo->items[i].activated)
				type |= 0x00200000;
			if (worldInfo->items[i].flipped)
				type |= 0x00400000;
			if (worldInfo->items[i].water)
				type |= 0x04000000;
			if (worldInfo->items[i].glue)
				type |= 0x08000000;
			if (worldInfo->items[i].fire)
				type |= 0x10000000;
			if (worldInfo->items[i].red)
				type |= 0x20000000;
			if (worldInfo->items[i].green)
				type |= 0x40000000;
			if (worldInfo->items[i].blue)
				type |= 0x80000000;
			memcpy(blockPtr, &worldInfo->items[i].foreground, 2);
			memcpy(blockPtr + 4, &type, 4);
			BYTE btype = 1;
			memcpy(blockPtr + 8, &btype, 1);
			auto doorText = worldInfo->items[i].sign;
			auto doorTextChars = doorText.c_str();
			auto length = static_cast<short>(doorText.size());
			memcpy(blockPtr + 9, &length, 2);
			memcpy(blockPtr + 11, doorTextChars, length);
			auto minus1 = -1;
			memcpy(blockPtr + 11 + length, &minus1, 4);
			sizeofblockstruct += 4 + length;
			dataLen += 4 + length;
		}
		else if (getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::PROVIDER)
        {
            auto type = 0x00000000;
            if (worldInfo->items[i].activated)
                type |= 0x00200000;
            if (worldInfo->items[i].flipped)
                type |= 0x00400000;
            if (worldInfo->items[i].water)
                type |= 0x04000000;
            if (worldInfo->items[i].glue)
                type |= 0x08000000;
            if (worldInfo->items[i].fire)
                type |= 0x10000000;
            if (worldInfo->items[i].red)
                type |= 0x20000000;
            if (worldInfo->items[i].green)
                type |= 0x40000000;
            if (worldInfo->items[i].blue)
                type |= 0x80000000;

            BYTE btype = 9;
            auto timeIntoGrowth = getItemDef(worldInfo->items[i].foreground).growTime - calcBanDuration(worldInfo->items[i].growtime);
            memcpy(blockPtr, &worldInfo->items[i].foreground, 2);
            memcpy(blockPtr + 4, &type, 4);
            memcpy(blockPtr + 8, &btype, 1);
            memcpy(blockPtr + 9, &timeIntoGrowth, 4);
            sizeofblockstruct += 5;
            dataLen += 5;
        }
		else if ((worldInfo->items[i].foreground == 0) || (worldInfo->items[i].foreground == 2) || (worldInfo->items[i].foreground == 8) || (worldInfo->items[i].foreground == 100) || (worldInfo->items[i].foreground == 4) || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::FOREGROUND || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::BACKGROUND || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::TOGGLE_FOREGROUND || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::CHEMICAL_COMBINER || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::CHEST || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::SWITCH_BLOCK)
		{
			memcpy(blockPtr, &worldInfo->items[i].foreground, 2);
			auto type = 0;
			if (worldInfo->items[i].activated)
				type |= 0x00400000;
			if (worldInfo->items[i].flipped)
				type |= 0x00200000;
			if (worldInfo->items[i].water)
				type |= 0x04000000;
			if (worldInfo->items[i].glue)
				type |= 0x08000000;
			if (worldInfo->items[i].fire)
				type |= 0x10000000;
			if (worldInfo->items[i].red)
				type |= 0x20000000;
			if (worldInfo->items[i].green)
				type |= 0x40000000;
			if (worldInfo->items[i].blue)
				type |= 0x80000000;
			memcpy(blockPtr + 4, &type, 4);
		}
		else
		{
			memcpy(blockPtr, &zero, 2);
		}
		memcpy(blockPtr + 2, &worldInfo->items[i].background, 2);
		blockPtr += sizeofblockstruct;
	}
	dataLen += 8;
	int itemcount = worldInfo->droppedItems.size();
	auto itemuid = worldInfo->droppedCount;
	memcpy(blockPtr, &itemcount, 4);
	memcpy(blockPtr + 4, &itemuid, 4);
	blockPtr += 8;
	auto iteminfosize = 16;
	for (auto i = 0; i < itemcount; i++)
	{
		auto item1 = worldInfo->droppedItems[i].id;
		auto count = worldInfo->droppedItems[i].count;
		auto uid = worldInfo->droppedItems[i].uid;
		auto x = static_cast<float>(worldInfo->droppedItems[i].x);
		auto y = static_cast<float>(worldInfo->droppedItems[i].y);
		memcpy(blockPtr, &item1, 2);
		memcpy(blockPtr + 2, &x, 4);
		memcpy(blockPtr + 6, &y, 4);
		memcpy(blockPtr + 10, &count, 2);
		memcpy(blockPtr + 12, &uid, 4);
		blockPtr += iteminfosize;
		dataLen += iteminfosize;
	}
	dataLen += 100;
	blockPtr += 4;
	memcpy(blockPtr, &worldInfo->weather, 4);
	blockPtr += 4;
	offsetData = dataLen - 100;
	auto data2 = new BYTE[101];
	memset(data2, 0, 101);
	memcpy(data2 + 0, &zero, 4);
	auto weather = worldInfo->weather;
	memcpy(data2 + 4, &weather, 4);
	memcpy(data + dataLen - 4, &smth, 4);
	auto packet2 = enet_packet_create(data, dataLen, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet2);
	static_cast<PlayerInfo*>(peer->data)->currentWorld = worldInfo->name;
	for (auto i = 0; i < square; i++)
	{
		switch (worldInfo->items[i].foreground)
		{
		case 3528: //Painting Easel
		{
			int xx = i % xSize, yy = i / xSize;
			SendCanvasData(peer, worldInfo->items[i].foreground, worldInfo->items[i].background, xx, yy, worldInfo->items[i].intdata, getItemDef(worldInfo->items[i].intdata).name);
			break;
		}
		case 3818: //Portrait
		{
			int xx = i % xSize, yy = i / xSize;
			SendCanvasData(peer, worldInfo->items[i].foreground, worldInfo->items[i].background, xx, yy, worldInfo->items[i].intdata, getItemDef(worldInfo->items[i].intdata).name);
			break;
		}
		case 2978: //Vending Machine
		{
			auto islocks = false;
			if (worldInfo->items[i].vdraw >= 1) {
				islocks = true;
			}
			if (worldInfo->items[i].vcount == 0 && worldInfo->items[i].vprice == 0 && worldInfo->items[i].vid != 0) {
				UpdateVend(peer, i % worldInfo->width, i / worldInfo->width, 0, islocks, 0, worldInfo->items[i].background, worldInfo->items[i].opened);
			}
			else if (worldInfo->items[i].opened && worldInfo->items[i].vcount < worldInfo->items[i].vprice) {
				UpdateVend(peer, i % worldInfo->width, i / worldInfo->width, 0, islocks, worldInfo->items[i].vprice, worldInfo->items[i].background, worldInfo->items[i].opened);
			}
			else UpdateVend(peer, i % worldInfo->width, i / worldInfo->width, worldInfo->items[i].vid, islocks, worldInfo->items[i].vprice, worldInfo->items[i].background, worldInfo->items[i].opened);
			break;
		}
		case 1240: //Heart Monitor
		{
			bool found = false;
			ENetPeer* currentPeer;
			for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
				if (static_cast<PlayerInfo*>(currentPeer->data)->displayName == worldInfo->items[i].monitorname) {
					found = true;
					sendHMonitor(peer, i % worldInfo->width, i / worldInfo->width, worldInfo->items[i].monitorname, true, worldInfo->items[i].background);
					break;
				}
			}
			if (!found) sendHMonitor(peer, i % worldInfo->width, i / worldInfo->width, worldInfo->items[i].monitorname, false, worldInfo->items[i].background);
			break;
		}
		case 1420: case 6214: //Mannequin
		{
			auto ismannequin = std::experimental::filesystem::exists("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(i) + ".json");
			if (ismannequin)
			{
				json j;
				ifstream fs("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(i) + ".json");
				fs >> j;
				fs.close();
				auto x = i % worldInfo->width;
				auto y = i / worldInfo->width;
				//0x00200000
				updateMannequin(peer, worldInfo->items[i].foreground, x, y, worldInfo->items[i].background, worldInfo->items[i].sign, atoi(j["clothHair"].get<string>().c_str()), atoi(j["clothHead"].get<string>().c_str()), atoi(j["clothMask"].get<string>().c_str()), atoi(j["clothHand"].get<string>().c_str()), atoi(j["clothNeck"].get<string>().c_str()), atoi(j["clothShirt"].get<string>().c_str()), atoi(j["clothPants"].get<string>().c_str()), atoi(j["clothFeet"].get<string>().c_str()), atoi(j["clothBack"].get<string>().c_str()), false, 0);
			}
			break;
		}
		case 0: case 6: case 3832: case 2946: case 5000: case 1008: case 866: case 6414: case 6212: case 5116: case 4858: case 3888: case 3044: case 2798: case 1632: case 1636: case 1044: case 928: case 872: case 4: case 2: case 8: case 100:
		{
			if (worldInfo->items[i].destroy && worldInfo->items[i].foreground != 0) {
				for (int asd = 0; asd < getItemDef(worldInfo->items[i].foreground).breakHits; asd++) {
					if (worldInfo->items[i].foreground != 0) sendTileUpdate(i % worldInfo->width, i / worldInfo->width, 18, -1, peer);
				}
				worldInfo->items[i].destroy = false;
			}
			break;
		}
		default:
		{
			if (worldInfo->items[i].destroy && worldInfo->items[i].foreground != 0) {
				for (int asd = 0; asd <= getItemDef(worldInfo->items[i].foreground).breakHits; asd++) {
					if (worldInfo->items[i].foreground != 0) sendTileUpdate(i % worldInfo->width, i / worldInfo->width, 18, -1, peer);
				}
				worldInfo->items[i].destroy = false;
			}
			else if (getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::FOREGROUND || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::BACKGROUND || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::CHEST || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::SWITCH_BLOCK || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::TOGGLE_FOREGROUND || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::CHEMICAL_COMBINER || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::SIGN || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::PORTAL) {
				break;
			}
			else if (getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::SEED) {
				int growTimeSeed = getItemDef(worldInfo->items[i].foreground - 1).rarity * getItemDef(worldInfo->items[i].foreground - 1).rarity * getItemDef(worldInfo->items[i].foreground - 1).rarity;
				growTimeSeed += 30 * getItemDef(worldInfo->items[i].foreground - 1).rarity;
				if (worldInfo->items[i].foreground - 1 == 954) growTimeSeed = 1800;
				if (worldInfo->items[i].foreground - 1 == 340) growTimeSeed = 3600;
				if (worldInfo->items[i].foreground - 1 == 5666) growTimeSeed = 2700;
				if (worldInfo->items[i].foreground - 1 == 4584) growTimeSeed = 2400;
				if (worldInfo->items[i].foreground - 1 == 4762) growTimeSeed = 14544;
				if (worldInfo->items[i].foreground - 1 == 7382) growTimeSeed = 22544;
				if (worldInfo->items[i].foreground - 1 == 9460) growTimeSeed = 29544;
				if (worldInfo->items[i].foreground - 1 == 9468) growTimeSeed = 36544;
				if (worldInfo->items[i].foreground - 1 == 10024) growTimeSeed = 56544;
				if (worldInfo->items[i].foreground - 1 == 10029) growTimeSeed = 86400;
				UpdateTreeVisuals(peer, worldInfo->items[i].foreground, i % xSize, i / xSize, worldInfo->items[i].background, worldInfo->items[i].fruitcount, growTimeSeed - calcBanDuration(worldInfo->items[i].growtime), false, 0);
			}
			else if (getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::GATEWAY) {
				updateEntrance(peer, worldInfo->items[i].foreground, i % worldInfo->width, i / worldInfo->width, worldInfo->items[i].opened, worldInfo->items[i].background, false);
			}
			else if (worldInfo->items[i].foreground == 3794) {
				PlayerInfo* pinfo = ((PlayerInfo*)(peer->data));
				int x = i % xSize, y = i / xSize;

				sendDShelf(peer, x, y, worldInfo->items[i].display1, worldInfo->items[i].display2, worldInfo->items[i].display3, worldInfo->items[i].display4);
			}
			else if (getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::DOOR)
			{
				updateDoor(peer, worldInfo->items[i].foreground, i % worldInfo->width, i / worldInfo->width, worldInfo->items[i].background, worldInfo->items[i].label == "" ? (worldInfo->items[i].destId == "" ? worldInfo->items[i].destWorld : worldInfo->items[i].destWorld + "...") : worldInfo->items[i].label, false, false);
			}
			else if (getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::LOCK) {
				if (worldInfo->items[i].foreground == 202 || worldInfo->items[i].foreground == 204 || worldInfo->items[i].foreground == 206 || worldInfo->items[i].foreground == 4994) {
					if (worldInfo->items[i].monitorname == static_cast<PlayerInfo*>(peer->data)->rawName) ApplyLockPacket(worldInfo, peer, i % worldInfo->width, i / worldInfo->width, worldInfo->items[i].foreground, static_cast<PlayerInfo*>(peer->data)->netID);
					else if (worldInfo->items[i].opened) ApplyLockPacket(worldInfo, peer, i % worldInfo->width, i / worldInfo->width, worldInfo->items[i].foreground, -3);
					else ApplyLockPacket(worldInfo, peer, i % worldInfo->width, i / worldInfo->width, worldInfo->items[i].foreground, -1);
				}
				else if (isWorldOwner(peer, worldInfo)) sendTileData(peer, i % worldInfo->width, i / worldInfo->width, 0x10, worldInfo->items[i].foreground, worldInfo->items[i].background, lockTileDatas(0x20, static_cast<PlayerInfo*>(peer->data)->netID, 0, 0, false, 100));
				else if (isWorldAdmin(peer, worldInfo)) sendTileData(peer, i % worldInfo->width, i / worldInfo->width, 0x10, worldInfo->items[i].foreground, worldInfo->items[i].background, lockTileDatas(0x20, static_cast<PlayerInfo*>(peer->data)->netID, 0, 0, true, 100));
				else {
					PlayerMoving moving;
					moving.packetType = 0x3;
					moving.characterState = 0x0;
					moving.x = i % worldInfo->width;
					moving.y = i / worldInfo->height;
					moving.punchX = i % worldInfo->width;
					moving.punchY = i / worldInfo->width;
					moving.XSpeed = 0;
					moving.YSpeed = 0;
					moving.netID = -1;
					moving.plantingTree = worldInfo->items[i].foreground;
					SendPacketRaw(4, packPlayerMoving(&moving), 56, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
				}
				if (worldInfo->items[i].foreground == 4802 && worldInfo->rainbow && isWorldOwner(peer, worldInfo)) {
					SendRainbowShitData(peer, worldInfo->items[i].foreground, worldInfo->items[i].background, i % worldInfo->width, i / worldInfo->width, true, static_cast<PlayerInfo*>(peer->data)->netID);
					for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, currentPeer) && !isWorldOwner(currentPeer, worldInfo)) {
							SendRainbowShitData(currentPeer, worldInfo->items[i].foreground, worldInfo->items[i].background, i % worldInfo->width, i / worldInfo->width, true, static_cast<PlayerInfo*>(peer->data)->netID);
						}
					}
				}
				else if (worldInfo->items[i].foreground == 4802 && !isWorldOwner(peer, worldInfo)) {
					for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, currentPeer) && isWorldOwner(currentPeer, worldInfo)) {
							SendRainbowShitData(peer, worldInfo->items[i].foreground, worldInfo->items[i].background, i % worldInfo->width, i / worldInfo->width, true, static_cast<PlayerInfo*>(currentPeer->data)->netID);
							break;
						}
					}
				}
			}
			else
			{
				PlayerMoving moving;
				moving.packetType = 0x3;
				moving.characterState = 0x0;
				moving.x = i % worldInfo->width;
				moving.y = i / worldInfo->height;
				moving.punchX = i % worldInfo->width;
				moving.punchY = i / worldInfo->width;
				moving.XSpeed = 0;
				moving.YSpeed = 0;
				moving.netID = -1;
				moving.plantingTree = worldInfo->items[i].foreground;
				SendPacketRaw(4, packPlayerMoving(&moving), 56, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
			}
			break;
		}
		}
	}
	auto wname = worldInfo->name;
	static_cast<PlayerInfo*>(peer->data)->currentWorld = wname;
	if (static_cast<PlayerInfo*>(peer->data)->haveGrowId)
	{
		ofstream ofs("lastnormalworld/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
		ofs << static_cast<PlayerInfo*>(peer->data)->currentWorld;
		ofs.close();
	}
	if (xSize == 100 && ySize == 60)
	{
		for (auto i = 0; i < xSize; i++)
		{
			for (auto j = 0; j < ySize; j++)
			{
				auto squaresign = i + (j * 100);
				int x = squaresign % worldInfo->width;
				int y = squaresign / worldInfo->width;
				auto isbfg = std::experimental::filesystem::exists("bfg/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(squaresign) + ".txt");
				if (isbfg)
				{
					if (worldInfo->items[squaresign].foreground == 2408)
					{
						auto magplantitemi = 0;
						ifstream fdss("bfg/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(squaresign) + ".txt");
						fdss >> magplantitemi;
						fdss.close();
						if (magplantitemi != 0)
						{
							getPlyersWorld(peer)->interactableid = magplantitemi;
						}
					}
				}
				if (worldInfo->items[squaresign].foreground == 3798) {
					if (worldInfo->owner == "" || isWorldOwner(peer, worldInfo) || worldInfo->items[x + (y * worldInfo->width)].VipPublic == true || (find(worldInfo->viplist.begin(), worldInfo->viplist.end(), ((PlayerInfo*)(peer->data))->rawName) != worldInfo->viplist.end())) {
						sendTileData(peer, x, y, 0x10, worldInfo->items[squaresign].foreground, worldInfo->items[squaresign].background, EntranceTiles(0x20, ((PlayerInfo*)(peer->data))->netID));
					}
				}
				if (worldInfo->items[squaresign].foreground == 5638 || worldInfo->items[squaresign].foreground == 6946 || worldInfo->items[squaresign].foreground == 6948)
				{
					string Sucker = "";
					auto BlockID = 0;
					if (worldInfo->items[squaresign].foreground == 5638)
					{
						Sucker = "magplant";
						BlockID = 5638;
					}
					if (worldInfo->items[squaresign].foreground == 6946)
					{
						Sucker = "gaiabeacon";
						BlockID = 6946;
					}
					if (worldInfo->items[squaresign].foreground == 6948)
					{
						Sucker = "unstabletesseract";
						BlockID = 6948;
					}
					auto ismag = std::experimental::filesystem::exists(Sucker + "/storeditem/" + worldInfo->name + "X" + std::to_string(squaresign) + ".txt");
					if (ismag)
					{
						auto x = squaresign % worldInfo->width;
						auto y = squaresign / worldInfo->width;
						auto currentworld = worldInfo->name + "X" + std::to_string(squaresign);
						auto itemid = 0;
						ifstream fdss(Sucker + "/storeditem/" + currentworld + ".txt");
						fdss >> itemid;
						fdss.close();
						auto count = 0;
						ifstream fdss3(Sucker + "/count/" + currentworld + ".txt");
						fdss3 >> count;
						fdss3.close();
						if (count <= 0)
						{
							SendItemSucker(peer, BlockID, x, y, itemid, 0, true, true);
						}
						else if (count >= 5000)
						{
							SendItemSucker(peer, BlockID, x, y, itemid, -1, true, true);
						}
						else
						{
							SendItemSucker(peer, BlockID, x, y, itemid, 1, true, true);
						}
					}
				}
				auto isdbox = std::experimental::filesystem::exists("donationboxes/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
				if (isdbox)
				{
					if (worldInfo->items[squaresign].foreground == 1452)
					{
						ifstream ifff("donationboxes/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						json basic_json;
						ifff >> basic_json;
						ifff.close();
						if (basic_json["donated"] > 0)
						{
							auto x = squaresign % worldInfo->width;
							auto y = squaresign / worldInfo->width;
							SendItemPacket(peer, worldInfo->items[squaresign].foreground, worldInfo->items[squaresign].background, x, y, 1);
						}
					}
				}
				auto isbluemail = std::experimental::filesystem::exists("bluemailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
				if (isbluemail)
				{
					if (worldInfo->items[squaresign].foreground == 1006)
					{
						ifstream ifff("bluemailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						json basic_json;
						ifff >> basic_json;
						ifff.close();
						if (basic_json["inmail"] > 0)
						{
							auto x = squaresign % worldInfo->width;
							auto y = squaresign / worldInfo->width;
							SendItemPacket(peer, worldInfo->items[squaresign].foreground, worldInfo->items[squaresign].background, x, y, 1);
						}
					}
				}
				auto ismailbox = std::experimental::filesystem::exists("mailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
				if (ismailbox)
				{
					if (worldInfo->items[squaresign].foreground == 656)
					{
						ifstream ifff("mailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						json basic_json;
						ifff >> basic_json;
						ifff.close();
						if (basic_json["inmail"] > 0)
						{
							auto x = squaresign % worldInfo->width;
							auto y = squaresign / worldInfo->width;
							SendItemPacket(peer, worldInfo->items[squaresign].foreground, worldInfo->items[squaresign].background, x, y, 1);
						}
					}
				}
			}
		}
	}
	ifstream ifs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
	string content((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));
	auto gembux = atoi(content.c_str());
	Player::OnSetBux(peer, gembux, 1);
	Player::PlayAudio(peer, "audio/door_open.wav", 0);
	delete data;
	delete data2;
	//LoadPlayerData(peer);
	if (worldInfo->allowMod != true && !isMod(peer))
	{
		static_cast<PlayerInfo*>(peer->data)->canWalkInBlocks = false;
	}
	else
	{
		if (isMod(peer))
		{
		}
		else if (static_cast<PlayerInfo*>(peer->data)->isZombie == false)
		{
			Player::OnConsoleMessage(peer, "`2Owner `ohas `2enabled `5Mod-Noclip `oin this world.");
			static_cast<PlayerInfo*>(peer->data)->canWalkInBlocks = true;
			send_state(peer);
		}
	}
	if (((PlayerInfo*)(peer->data))->rawName == ((PlayerInfo*)(peer->data))->guildLeader) {
		((PlayerInfo*)(peer->data))->displayName = ((PlayerInfo*)(peer->data))->tankIDName + " `e(GL)";
		((PlayerInfo*)(peer->data))->displayNamebackup = ((PlayerInfo*)(peer->data))->tankIDName + " `e(GL)";
	}
	if (static_cast<PlayerInfo*>(peer->data)->cloth_feet == 898 || static_cast<PlayerInfo*>(peer->data)->cloth_feet == 1830 || static_cast<PlayerInfo*>(peer->data)->cloth_feet == 1966)
	{
		send_state(peer);
	}
	if (static_cast<PlayerInfo*>(peer->data)->effect != 8421376)
	{
		// ReSharper disable once CppIdenticalOperandsInBinaryExpression
		static_cast<PlayerInfo*>(peer->data)->effect = static_cast<PlayerInfo*>(peer->data)->effect;
		send_state(peer);
		sendPuncheffectpeer(peer, static_cast<PlayerInfo*>(peer->data)->effect);
	}
}
inline void joinWorld(ENetPeer* peer, string act, int x2, int y2)
{
	if (serverIsFrozen)
	{
		return;
	}
	if (static_cast<PlayerInfo*>(peer->data)->isBot == true)
	{
		enet_peer_disconnect_later(peer, 0);
	}
	if (static_cast<PlayerInfo*>(peer->data)->isConfirmingCode == true)
	{
		enet_peer_disconnect_later(peer, 0);
	}
	if (act.length() > 24 || act.length() < 0)
	{
		Player::OnConsoleMessage(peer, "`4Sorry, but world names with more than 24 characters are not allowed!");
		Player::OnFailedToEnterWorld(peer);
	}
	else
	{
		auto upsd = act;
		transform(upsd.begin(), upsd.end(), upsd.begin(), ::toupper);
		if (upsd == "EXIT")
		{
			static_cast<PlayerInfo*>(peer->data)->currentWorld = "EXIT";
			Player::OnConsoleMessage(peer, "`4To reduce confusion, this is not a valid world name`w. `oTry another one`w?``");
			Player::OnFailedToEnterWorld(peer);
			return;
		}
		if (upsd.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != string::npos)
		{
			Player::OnTextOverlay(peer, "Symbols not allowed!");
			Player::OnFailedToEnterWorld(peer);
			return;
		}
		if (frozenworlds.size() != 0) {
			if (find(frozenworlds.begin(), frozenworlds.end(), upsd) != frozenworlds.end()) {
				SendConsole("Saved server from crashing! in world " + upsd + "", "ERROR");
				Player::OnConsoleMessage(peer, "This world is busy... Try again");
				Player::OnFailedToEnterWorld(peer);
				return;
			}
		}
		if (static_cast<PlayerInfo*>(peer->data)->isCursed) act = "HELL";
		auto info = worldDB.get(act);
		if (info.name == "error") {
			Player::OnConsoleMessage(peer, "An error occured while trying to enter this world, please try again!");
			Player::OnFailedToEnterWorld(peer);
			return;
		}
		if (info.name == "PARKUR" && static_cast<PlayerInfo*>(peer->data)->lprogress == 0)
		{
			Player::OnConsoleMessage(peer, "`oYou're not Legendary enough for this Parkour");
			Player::OnFailedToEnterWorld(peer);
			return;
		}
		const auto playeriai = getPlayersCountInWorldSave(info.name);
		if (playeriai >= 60)
		{
			Player::OnConsoleMessage(peer, "World is at max capacity. Try again later...");
			Player::OnFailedToEnterWorld(peer);
			return;
		}
		const auto existsban = std::experimental::filesystem::exists("worldbans/" + info.name + "/" + static_cast<PlayerInfo*>(peer->data)->rawName);
		if (existsban) {
			Player::OnConsoleMessage(peer, "`4Oh no! ``You've been banned from that world by its owner! Try again later after ban wears off.");
			Player::OnFailedToEnterWorld(peer);
			return;
		}
		if (static_cast<PlayerInfo*>(peer->data)->haveGrowId) {
			DailyRewardCheck(peer);
			auto iscontains = false;
			SearchInventoryItem(peer, 6336, 1, iscontains);
			if (!iscontains) {
				auto success = true;
				SaveItemMoreTimes(6336, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from system");
			}
			/*magplant*/
			auto iscontainss = false;
			SearchInventoryItem(peer, 5640, 1, iscontainss);
			if (iscontainss) {
				static_cast<PlayerInfo*>(peer->data)->magplantitemid = 0;
				RemoveInventoryItem(5640, 1, peer, true);
			}
		}
		static_cast<PlayerInfo*>(peer->data)->netID = cId;
		if (static_cast<PlayerInfo*>(peer->data)->isinv == false) {
			for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
				if (isHere(peer, currentPeer)) {
					if (static_cast<PlayerInfo*>(currentPeer->data)->currentWorld == "EXIT") continue;
					Player::OnConsoleMessage(currentPeer, "`5<`w" + static_cast<PlayerInfo*>(peer->data)->displayName + " `5entered, `w" + std::to_string(getPlayersCountInWorld(static_cast<PlayerInfo*>(peer->data)->currentWorld) - 1) + "`` others here>``");
				}
			}
		}
		string Definitions = " `0[";
		if (info.category != "None") Definitions += "`9" + info.category;
		for (auto jss = 0; jss < info.width * info.height; jss++) {
			if (info.items[jss].foreground == 226 && info.items[jss].activated) {
				if (Definitions == " `0[") Definitions += "`4JAMMED";
				else Definitions += "``, `4JAMMED";
			}
			if (info.items[jss].foreground == 1276 && info.items[jss].activated) {
				if (Definitions == " `0[") Definitions += "`2NOPUNCH";
				else Definitions += "``, `2NOPUNCH";
			}
			if (info.items[jss].foreground == 1278 && info.items[jss].activated) {
				if (Definitions == " `0[") Definitions += "`2IMMUNE";
				else Definitions += "``, `2IMMUNE";
			}
			if (info.items[jss].foreground == 4992 && info.items[jss].activated) {
				if (Definitions == " `0[") Definitions += "`2ANTIGRAVITY";
				else Definitions += "``, `2ANTIGRAVITY";
			}
		}
		if (info.isNuked) {
			if (Definitions == " `0[") Definitions += "`4World is banned, can't be reached by users";
			else Definitions += "``, `4World is banned, can't be reached by users";
		}
		Definitions += "`0]";
		if (Definitions == " `0[`0]") Definitions = "";
		Player::OnConsoleMessage(peer, "World `w" + info.name + "``" + Definitions + " `oentered. There are `w" + to_string(getPlayersCountInWorld(info.name)) + "`` other people here, `w" + to_string(GetPlayerCountServer()) + "`` online.");

		if (info.owner != "")
		{
			if (info.owner == static_cast<PlayerInfo*>(peer->data)->rawName || isWorldAdmin2(peer, info))
			{
				Player::OnConsoleMessage(peer, "`5[`w" + info.name + "`$ World Locked`o by " + info.owner + " `o(`2ACCESS GRANTED`o)`5]");
			}
			if (info.owner == static_cast<PlayerInfo*>(peer->data)->rawName) {
				if (static_cast<PlayerInfo*>(peer->data)->displayName.find("`") != string::npos) {}
				else {
					static_cast<PlayerInfo*>(peer->data)->displayName = "`2" + static_cast<PlayerInfo*>(peer->data)->displayName;
					auto p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), "`2" + static_cast<PlayerInfo*>(peer->data)->displayName));
					memcpy(p7.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
					auto packet7 = enet_packet_create(p7.data, p7.len, ENET_PACKET_FLAG_RELIABLE);
					delete p7.data;
					for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, currentPeer)) {
							if (static_cast<PlayerInfo*>(peer->data)->adminLevel >= 0) {
								enet_peer_send(currentPeer, 0, packet7);
							}
						}
					}
				}
			}
		}
		else if (info.interactableid != -1 && info.interactableid != 0) {
			Player::OnConsoleMessage(peer, "`5[`w" + info.name + "`$ World Locked`o by " + info.owner + " ``(`^BFG``)`5]");
		}
		else
		{
			Player::OnConsoleMessage(peer, "`5[`w" + info.name + "`$ World Locked`o by " + info.owner + "`5]");
		}
	}
	auto info = worldDB.get(act);
	if (info.owner == static_cast<PlayerInfo*>(peer->data)->rawName) {
		if (static_cast<PlayerInfo*>(peer->data)->displayName.find("`2") != string::npos) {
			size_t pos;
			while ((pos = static_cast<PlayerInfo*>(peer->data)->displayName.find("`2")) != string::npos) {
				static_cast<PlayerInfo*>(peer->data)->displayName.replace(pos, 2, "");
			}
			auto p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), static_cast<PlayerInfo*>(peer->data)->displayName));
			memcpy(p7.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
			auto packet7 = enet_packet_create(p7.data, p7.len, ENET_PACKET_FLAG_RELIABLE);
			delete p7.data;
			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
				if (isHere(peer, currentPeer)) {
					if (static_cast<PlayerInfo*>(peer->data)->adminLevel >= 0) {
						enet_peer_send(currentPeer, 0, packet7);
					}
				}
			}
		}
	}
	sendWorld(peer, &info);
	SendInventory(peer, static_cast<PlayerInfo*>(peer->data)->inventory);
	auto x = 3040;
	auto y = 736;
	for (auto j = 0; j < info.width * info.height; j++) {
		if (info.items[j].foreground == 6) {
			x = (j % info.width) * 32;
			y = (j / info.width) * 32;
		}
	}
	if (x2 != 0 && y2 != 0) {
		x = x2;
		y = y2;
	}
	static_cast<PlayerInfo*>(peer->data)->x = x;
	static_cast<PlayerInfo*>(peer->data)->x = y;
	if (static_cast<PlayerInfo*>(peer->data)->adminLevel >= 1) {
		auto p = packetEnd(appendString(appendString(createPacket(), "OnSpawn"), "spawn|avatar\nnetID|" + std::to_string(cId) + "\nuserID|" + std::to_string(cId) + "\ncolrect|0|0|20|30\nposXY|" + std::to_string(x) + "|" + std::to_string(y) + "\nname|``" + static_cast<PlayerInfo*>(peer->data)->displayName + "``\ncountry|" + static_cast<PlayerInfo*>(peer->data)->country + "\ninvis|0\nmstate|0\nsmstate|1\nonlineID|\ntype|local\n"));
		const auto packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
	}
	else {
		auto p = packetEnd(appendString(appendString(createPacket(), "OnSpawn"), "spawn|avatar\nnetID|" + std::to_string(cId) + "\nuserID|" + std::to_string(cId) + "\ncolrect|0|0|20|30\nposXY|" + std::to_string(x) + "|" + std::to_string(y) + "\nname|``" + static_cast<PlayerInfo*>(peer->data)->displayName + "``\ncountry|" + static_cast<PlayerInfo*>(peer->data)->country + "\ninvis|0\nmstate|0\nsmstate|0\nonlineID|\ntype|local\n"));
		const auto packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
	}
	static_cast<PlayerInfo*>(peer->data)->netID = cId;
	onPeerConnect(peer);
	cId++;
}
inline void sendPlayerToWorld(ENetPeer* peer, PlayerInfo* player, string wrldname)
{
	if (serverIsFrozen) return;
	toUpperCase(wrldname);

	const auto playeriai = getPlayersCountInWorldSave(wrldname);

	if (wrldname == "EXIT")
	{
		Player::OnConsoleMessage(peer, "You cannot warp to that world!");
	}
	else if (playeriai >= 60)
	{
		Player::OnConsoleMessage(peer, "World is at max capacity. Try again later...");
	}
	else if (wrldname == "GAME1" && playeriai >= 15)
	{
		Player::OnConsoleMessage(peer, "GAME1 world is at max capacity. Max 15 players are allowed to play here. Try again later...");
	}
	else if (wrldname == "GAME2" && playeriai >= 15)
	{
		Player::OnConsoleMessage(peer, "GAME2 world is at max capacity. Max 15 players are allowed to play here. Try again later...");
	}
	else if (wrldname == "GROWGANOTH" && !GrowganothEvent && !isDev(peer))
	{
		Player::OnTextOverlay(peer, "Growganoth is currently closed!");
	}
	else if (wrldname == "GAME1" && game1status == true)
	{
		Player::OnConsoleMessage(peer, "`oThe game is already started");
	}
	else if (wrldname == "GAME1" && static_cast<PlayerInfo*>(peer->data)->isinv == true)
	{
		Player::OnConsoleMessage(peer, "`oYou cant enter this world while you are invisible");
	}
	else if (wrldname == "GAME2" && game2status == true)
	{
		Player::OnConsoleMessage(peer, "`oThe game is already started");
	}
	else if (wrldname == "GAME2" && static_cast<PlayerInfo*>(peer->data)->isinv == true)
	{
		Player::OnConsoleMessage(peer, "`oYou cant enter this world while you are invisible");
	}
	else if (wrldname == "GAME2")
	{
		if (!SearchInventoryItemsForGame2(peer))
		{
			Player::OnConsoleMessage(peer, "`oYou can enter this world only if you have in your inventory " + itemDefs[9484].name + " `&OR `o" + itemDefs[9486].name + " `&OR `o" + itemDefs[9494].name + " `&OR `o" + itemDefs[9502].name);
			Player::OnFailedToEnterWorld(peer);
			return;
		}
	}
	else if (wrldname == "PARKUR" && static_cast<PlayerInfo*>(peer->data)->lprogress == 0)
	{
		Player::OnConsoleMessage(peer, "`oYou're not Legendary enough for this Parkour");
		Player::OnFailedToEnterWorld(peer);
		return;
	}
	else if (static_cast<PlayerInfo*>(peer->data)->isConfirmingCode == true)
	{
		enet_peer_disconnect_now(peer, 0);
	}
	else
	{
		sendPlayerLeave(peer, static_cast<PlayerInfo*>(peer->data));
		auto info = worldDB.get(wrldname);
		sendWorld(peer, &info);
		auto x = 3040;
		auto y = 736;
		for (auto j = 0; j < info.width * info.height; j++)
		{
			if (info.items[j].foreground == 6)
			{
				x = (j % info.width) * 32;
				y = (j / info.width) * 32;
			}
		}
		/*magplant*/
		auto iscontainss = false;
		SearchInventoryItem(peer, 5640, 1, iscontainss);
		if (iscontainss)
		{
			static_cast<PlayerInfo*>(peer->data)->magplantitemid = 0;
			RemoveInventoryItem(5640, 1, peer, true);
		}
		if (!static_cast<PlayerInfo*>(peer->data)->Console)
		{
			auto p = packetEnd(appendString(appendString(createPacket(), "OnSpawn"), "spawn|avatar\nnetID|" + std::to_string(cId) + "\nuserID|" + std::to_string(cId) + "\ncolrect|0|0|20|30\nposXY|" + std::to_string(x) + "|" + std::to_string(y) + "\nname|``" + static_cast<PlayerInfo*>(peer->data)->displayName + "``\ncountry|" + static_cast<PlayerInfo*>(peer->data)->country + "\ninvis|0\nmstate|0\nsmstate|0\ntype|local\n"));
			const auto packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet);
			delete p.data;
		}
		static_cast<PlayerInfo*>(peer->data)->netID = cId;
		onPeerConnect(peer);
		cId++;
		SendInventory(peer, static_cast<PlayerInfo*>(peer->data)->inventory);
	}
}
inline void sendPlayerToWorld2(ENetPeer* peer, PlayerInfo* player, string wrldname, const int x_ = -1, const int y_ = -1)
{
	if (serverIsFrozen) return;
	toUpperCase(wrldname);
	if (wrldname == "EXIT")
	{
		Player::OnConsoleMessage(peer, "You cant warp to that world!");
	}
	else if (wrldname == "GAME1" && game1status == true)
	{
		Player::OnConsoleMessage(peer, "`oThe game is already started");
	}
	else if (wrldname == "GAME1" && static_cast<PlayerInfo*>(peer->data)->isinv == true)
	{
		Player::OnConsoleMessage(peer, "`oYou cant enter this world while you are invisible");
	}
	else if (wrldname == "GAME2" && game2status == true)
	{
		Player::OnConsoleMessage(peer, "`oThe game is already started");
	}
	else if (wrldname == "GAME2" && static_cast<PlayerInfo*>(peer->data)->isinv == true)
	{
		Player::OnConsoleMessage(peer, "`oYou cant enter this world while you are invisible");
	}
	else if (wrldname == "GAME2")
	{
		if (!SearchInventoryItemsForGame2(peer))
		{
			Player::OnConsoleMessage(peer, "`oYou can enter this world only if you have in your inventory " + itemDefs[9484].name + " `&OR `o" + itemDefs[9486].name + " `&OR `o" + itemDefs[9494].name + " `&OR `o" + itemDefs[9502].name);
			Player::OnFailedToEnterWorld(peer);
			return;
		}
	}
	else if (wrldname == "PARKUR" && static_cast<PlayerInfo*>(peer->data)->lprogress == 0)
	{
		Player::OnConsoleMessage(peer, "`oYou're not Legendary enough for this Parkour");
		Player::OnFailedToEnterWorld(peer);
		return;
	}
	else
	{
		sendPlayerLeave(peer, static_cast<PlayerInfo*>(peer->data));
		auto info = worldDB.get(wrldname);
		sendWorld(peer, &info);
		auto x = 3040;
		auto y = 736;
		for (auto j = 0; j < info.width * info.height; j++)
		{
			if (info.items[j].foreground == 6)
			{
				x = (j % info.width) * 32;
				y = (j / info.width) * 32;
			}
		}
		/*magplant*/
		auto iscontainss = false;
		SearchInventoryItem(peer, 5640, 1, iscontainss);
		if (iscontainss)
		{
			static_cast<PlayerInfo*>(peer->data)->magplantitemid = 0;
			RemoveInventoryItem(5640, 1, peer, true);
		}
		if (x_ != -1 && y_ != -1)
		{
			x = x_ * 32;
			y = y_ * 32;
		}
		if (!static_cast<PlayerInfo*>(peer->data)->Console)
		{
			auto p = packetEnd(appendString(appendString(createPacket(), "OnSpawn"), "spawn|avatar\nnetID|" + std::to_string(cId) + "\nuserID|" + std::to_string(cId) + "\ncolrect|0|0|20|30\nposXY|" + std::to_string(x) + "|" + std::to_string(y) + "\nname|``" + static_cast<PlayerInfo*>(peer->data)->displayName + "``\ncountry|" + static_cast<PlayerInfo*>(peer->data)->country + "\ninvis|0\nmstate|0\nsmstate|0\ntype|local\n"));
			const auto packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet);
			delete p.data;
		}
		static_cast<PlayerInfo*>(peer->data)->netID = cId;
		onPeerConnect(peer);
		cId++;
		SendInventory(peer, static_cast<PlayerInfo*>(peer->data)->inventory);
	}
}
inline void handle_world(ENetPeer* peer, string act, bool sync = false, bool door = false, string destId = "", bool animations = true, int x = 0, int y = 0) {
	if (serverIsFrozen || !static_cast<PlayerInfo*>(peer->data)->HasLogged && static_cast<PlayerInfo*>(peer->data)->haveGrowId) return;
	toUpperCase(act);
	if (act.size() > 24) return;
	if (act.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != string::npos) {
		Player::OnConsoleMessage(peer, "Sorry, spaces and special characters are not allowed in world or door names.  Try again.");
		Player::OnFailedToEnterWorld(peer);
		return;
	}
	if (act == "EXIT" && static_cast<PlayerInfo*>(peer->data)->currentWorld == "EXIT") {
		Player::OnConsoleMessage(peer, "Exit from what? Press back if you're done playing.");
		Player::OnFailedToEnterWorld(peer);
		return;
	}
	else if (act == "EXIT") {
		Player::OnConsoleMessage(peer, "Where would you like to go? (`w" + to_string(GetPlayerCountServer()) + " `oonline)");
		sendPlayerLeave(peer, static_cast<PlayerInfo*>(peer->data));
		static_cast<PlayerInfo*>(peer->data)->currentWorld = "EXIT";
		sendWorldOffers(peer);
		return;
	}
	if (act == "ANAL" || act == "ANUS" || act == "ARSE" || act == "KONTOL" || act == "MEMEK" || act == "ASS" || act == "BALLSACK" || act == "BALLS" || act == "BASTARD" || act == "BITCH" || act == "BIATCH" || act == "BLOODY" || act == "BLOWJOB" || act == "BOLLOCK" || act == "BOLLOK" || act == "BONER" || act == "BOOB" || act == "BUGGER" || act == "BUM" || act == "BUTT" || act == "BUTTPLUG" || act == "CLITORIS" || act == "COCK" || act == "COON" || act == "CRAP" || act == "CUNT" || act == "DAMN" || act == "DICK" || act == "DILDO" || act == "DYKE" || act == "FAG" || act == "FECK" || act == "FELLATE" || act == "FELLATIO" || act == "FELCHING" || act == "FUCK" || act == "FUDGEPACKER" || act == "FLANGE" || act == "GODDAMN" || act == "HOMO" || act == "JERK" || act == "JIZZ" || act == "KNOBEND" || act == "LABIA" || act == "LMAO" || act == "LMFAO" || act == "MUFF" || act == "NIGGER" || act == "NIGGA" || act == "OMG" || act == "PENIS" || act == "PISS" || act == "POOP" || act == "PRICK" || act == "PUBE" || act == "PUSSY" || act == "QUEER" || act == "SCROTUM" || act == "SEX" || act == "SHIT" || act == "SH1T" || act == "SLUT" || act == "SMEGMA" || act == "SPUNK" || act == "TIT" || act == "TOSSER" || act == "TURD" || act == "TWAT" || act == "VAGINA" || act == "WANK" || act == "WHORE" || act == "WTF" || act == "SEBIA" || act == "ADMIN" || act == "SETH" || act == "HAMUMU" || act == "GOD" || act == "SATAN" || act == "RTSOFT" || act == "HEROMAN" || act == "SYSTEM" || act == "MIKEHOMMEL" || act == "SKIDS" || act == "MODERATOR" || act == "GODS" || act == "THEGODS" || act == "ALMANTAS") {
		Player::OnConsoleMessage(peer, "`4To reduce confusion, that is not a valid world name.``  Try another?");
		Player::OnFailedToEnterWorld(peer);
		return;
	}
	if (static_cast<PlayerInfo*>(peer->data)->haveGrowId == false) act = "START";
	if (frozenworlds.size() != 0) {
		if (find(frozenworlds.begin(), frozenworlds.end(), act) != frozenworlds.end()) {
			SendConsole("Saved server from crashing! in world " + act + "", "ERROR");
			Player::OnConsoleMessage(peer, "This world is busy... Try again");
			Player::OnFailedToEnterWorld(peer);
			return;
		}
	}
	if (static_cast<PlayerInfo*>(peer->data)->currentWorld != "EXIT" && !door) {
		sendPlayerLeave(peer, static_cast<PlayerInfo*>(peer->data));
	}
	if (act == "" && !door) {
		joinWorld(peer, "START", 0, 0);
		return;
	}
	WorldInfo info;
	if (door && act == "") info = worldDB.get(static_cast<PlayerInfo*>(peer->data)->currentWorld);
	else info = worldDB.get(act);
	if (info.items == nullptr || info.name == "error") {
		Player::OnConsoleMessage(peer, "An error occured while trying to enter this world, please try again!");
		Player::OnFailedToEnterWorld(peer);
		return;
	}
	if (door) {
		if (destId != "") {
			for (auto i = 0; i < info.width * info.height; i++) {
				if (getItemDef(info.items[i].foreground).blockType == BlockTypes::DOOR || getItemDef(info.items[i].foreground).blockType == BlockTypes::PORTAL) {
					if (info.items[i].currId == destId) {
						if (act == static_cast<PlayerInfo*>(peer->data)->currentWorld || act == "") {
							DoCancelTransitionAndTeleport(peer, (i % info.width), (i / info.width), false, animations);
						}
						else {
							joinWorld(peer, act, (i % info.width) * 32, (i / info.width) * 32);
						}
						return;
					}
				}
			}
		}
		for (auto s = 0; s < info.width * info.height; s++) {
			if (info.items[s].foreground == 6) {
				if (act == static_cast<PlayerInfo*>(peer->data)->currentWorld || act == "") {
					DoCancelTransitionAndTeleport(peer, (s % info.width), (s / info.width), false, animations);
				}
				else {
					joinWorld(peer, act, 0, 0);
				}
				return;
			}
		}
		return;
	}
	if (getPlayersCountInWorldSave(info.name) > 60) {
		Player::OnConsoleMessage(peer, "Oops, `5" + info.name + "`` already has `460`` people in it. Try again later.");
		Player::OnFailedToEnterWorld(peer);
		return;
	}
	if (act == "GROWGANOTH" && !GrowganothEvent && !isDev(peer)) {
		Player::OnConsoleMessage(peer, "Growganoth is currently closed.");
		Player::OnFailedToEnterWorld(peer);
		return;
	}
	if (info.isNuked && !isMod(peer)) {
		Player::OnConsoleMessage(peer, "That world is inaccessible.");
		Player::OnFailedToEnterWorld(peer);
		return;
	}
	if (info.entrylevel > static_cast<PlayerInfo*>(peer->data)->level && info.owner != static_cast<PlayerInfo*>(peer->data)->rawName && !isMod(peer)) {
		Player::OnConsoleMessage(peer, "Players lower than level " + to_string(info.entrylevel) + " can't enter " + info.name + ".");
		Player::OnFailedToEnterWorld(peer);
		return;
	}
	joinWorld(peer, act, x, y);
	if (sync) Player::PlayAudio(peer, "audio/choir.wav", 200);
}
inline void playerRespawn(ENetPeer* peer, const bool isDeadByTile)
{
	if (static_cast<PlayerInfo*>(peer->data)->Fishing)
	{
		static_cast<PlayerInfo*>(peer->data)->TriggerFish = false;
		static_cast<PlayerInfo*>(peer->data)->FishPosX = 0;
		static_cast<PlayerInfo*>(peer->data)->FishPosY = 0;
		static_cast<PlayerInfo*>(peer->data)->Fishing = false;
		send_state(peer);
		Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wSit perfectly when fishing!", 0, false);
		Player::OnSetPos(peer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y);
	}
	auto netID = static_cast<PlayerInfo*>(peer->data)->netID;
	if (isDeadByTile == false)
	{
		Player::OnKilled(peer, static_cast<PlayerInfo*>(peer->data)->netID);
	}
	auto p2x = packetEnd(appendInt(appendString(createPacket(), "OnSetFreezeState"), 0));
	memcpy(p2x.data + 8, &netID, 4);
	auto respawnTimeout = 2000;
	auto deathFlag = 0x19;
	memcpy(p2x.data + 24, &respawnTimeout, 4);
	memcpy(p2x.data + 56, &deathFlag, 4);
	const auto packet2x = enet_packet_create(p2x.data, p2x.len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet2x);
	delete p2x.data;
	const auto p5 = packetEnd(appendInt(appendString(createPacket(), "OnSetFreezeState"), 2));
	memcpy(p5.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
	const auto packet5 = enet_packet_create(p5.data, p5.len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet5);
	GamePacket p2;
	const auto world = getPlyersWorld(peer);
	auto x = 3040;
	auto y = 736;
	if (!world) return;
	for (auto i = 0; i < world->width * world->height; i++)
	{
		if (world->items[i].foreground == 6)
		{
			x = (i % world->width) * 32;
			y = (i / world->width) * 32;
		}
	}
	if (static_cast<PlayerInfo*>(peer->data)->ischeck == true)
	{
		p2 = packetEnd(appendFloat(appendString(createPacket(), "OnSetPos"), static_cast<PlayerInfo*>(peer->data)->checkx, static_cast<PlayerInfo*>(peer->data)->checky));
	}
	else
	{
		p2 = packetEnd(appendFloat(appendString(createPacket(), "OnSetPos"), x, y));
	}
	memcpy(p2.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
	respawnTimeout = 2000;
	memcpy(p2.data + 24, &respawnTimeout, 4);
	memcpy(p2.data + 56, &deathFlag, 4);
	const auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet2);
	delete p2.data;
	auto p2a = packetEnd(appendString(appendString(createPacket(), "OnPlayPositioned"), "audio/teleport.wav"));
	memcpy(p2a.data + 8, &netID, 4);
	respawnTimeout = 2000;
	memcpy(p2a.data + 24, &respawnTimeout, 4);
	memcpy(p2a.data + 56, &deathFlag, 4);
	const auto packet2a = enet_packet_create(p2a.data, p2a.len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet2a);
	delete p2a.data;


	if (game2status == true && static_cast<PlayerInfo*>(peer->data)->currentWorld == "GAME2")
	{
		sendPlayerToWorld(peer, static_cast<PlayerInfo*>(peer->data), "START");
	}

}
inline void playerRespawns(WorldInfo* world, ENetPeer* peer, const bool isDeadByTile) {
	if (static_cast<PlayerInfo*>(peer->data)->Fishing) {
		static_cast<PlayerInfo*>(peer->data)->TriggerFish = false;
		static_cast<PlayerInfo*>(peer->data)->FishPosX = 0;
		static_cast<PlayerInfo*>(peer->data)->FishPosY = 0;
		static_cast<PlayerInfo*>(peer->data)->Fishing = false;
		send_state(peer);
		Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wSit perfectly when fishing!", 0, false);
		Player::OnSetPos(peer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y);
	}
	auto netID = static_cast<PlayerInfo*>(peer->data)->netID;
	if (isDeadByTile == false) {
		Player::OnKilled(peer, static_cast<PlayerInfo*>(peer->data)->netID);
	}
	auto p2x = packetEnd(appendInt(appendString(createPacket(), "OnSetFreezeState"), 0));
	memcpy(p2x.data + 8, &netID, 4);
	auto respawnTimeout = 2000;
	auto deathFlag = 0x19;
	memcpy(p2x.data + 24, &respawnTimeout, 4);
	memcpy(p2x.data + 56, &deathFlag, 4);
	const auto packet2x = enet_packet_create(p2x.data, p2x.len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet2x);
	delete p2x.data;
	const auto p5 = packetEnd(appendInt(appendString(createPacket(), "OnSetFreezeState"), 2));
	memcpy(p5.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
	const auto packet5 = enet_packet_create(p5.data, p5.len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet5);
	GamePacket p2;
	if (world == NULL || world == nullptr) {
		SendConsole("Failed to run playerrespawn world was NULL", "ERROR");
		return;
	}
	//const auto world = getPlyersWorld(peer);
	auto x = 3040;
	auto y = 736;
	for (auto i = 0; i < world->width * world->height; i++) {
		if (world->items[i].foreground == 6) {
			x = (i % world->width) * 32;
			y = (i / world->width) * 32;
		}
	}
	if (static_cast<PlayerInfo*>(peer->data)->ischeck == true) {
		p2 = packetEnd(appendFloat(appendString(createPacket(), "OnSetPos"), static_cast<PlayerInfo*>(peer->data)->checkx, static_cast<PlayerInfo*>(peer->data)->checky));
	}
	else {
		p2 = packetEnd(appendFloat(appendString(createPacket(), "OnSetPos"), x, y));
	}
	memcpy(p2.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
	respawnTimeout = 2000;
	memcpy(p2.data + 24, &respawnTimeout, 4);
	memcpy(p2.data + 56, &deathFlag, 4);
	const auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet2);
	delete p2.data;
	auto p2a = packetEnd(appendString(appendString(createPacket(), "OnPlayPositioned"), "audio/teleport.wav"));
	memcpy(p2a.data + 8, &netID, 4);
	respawnTimeout = 2000;
	memcpy(p2a.data + 24, &respawnTimeout, 4);
	memcpy(p2a.data + 56, &deathFlag, 4);
	const auto packet2a = enet_packet_create(p2a.data, p2a.len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet2a);
	delete p2a.data;
}
inline void DoEnterDoor(ENetPeer* peer, WorldInfo* world, int x, int y, bool animations = true) {
	if (static_cast<PlayerInfo*>(peer->data)->Fishing) {
		static_cast<PlayerInfo*>(peer->data)->TriggerFish = false;
		static_cast<PlayerInfo*>(peer->data)->FishPosX = 0;
		static_cast<PlayerInfo*>(peer->data)->FishPosY = 0;
		static_cast<PlayerInfo*>(peer->data)->Fishing = false;
		send_state(peer);
		Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wSit perfectly when fishing!", 0, false);
		Player::OnSetPos(peer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y);
	}
	handle_world(peer, world->items[x + world->width * y].destWorld, false, true, world->items[x + world->width * y].destId, animations);
}
inline void SendSacrifice(WorldInfo* world, ENetPeer* peer, int itemid, int count)
{



	int pradinis = itemid;

	int Rarity = getItemDef(itemid).rarity;
	if (getItemDef(itemid).rarity >= 10)
	{
		Rarity = getItemDef(itemid).rarity * count;
	}

	if (itemid == 242) itemid = 1212;
	else if (itemid == 1190) itemid = 1214;
	else if (itemid == 882) itemid = 1232;
	else if (itemid == 592 || itemid == 1018) itemid = 1178;
	else if (itemid == 362) itemid = 1234;
	else if (itemid == 910) itemid = 1250;
	else if (itemid == 274 || itemid == 276) itemid = 1956;
	else if (itemid == 1474) itemid = 1990;
	else if (itemid == 1506) itemid = 1968;
	else if (itemid == 1746) itemid = 1960;
	else if (itemid == 1252) itemid = 1948;
	else if (itemid == 1830) itemid = 1966;
	else if (itemid == 2722) itemid = 3114;
	else if (itemid == 2984) itemid = 3118;
	else if (itemid == 3040) itemid = 3100;
	else if (itemid == 2390) itemid = 3122;
	else if (itemid == 1934) itemid = 3124;
	else if (itemid == 1162) itemid = 3126;
	else if (itemid == 604 || itemid == 2636) itemid = 3108;
	else if (itemid == 3020) itemid = 3098;
	else if (itemid == 914 || itemid == 916 || itemid == 918 || itemid == 920 || itemid == 924) itemid = 1962;
	else if (itemid == 900 || itemid == 1378 || itemid == 1576 || itemid == 7136 || itemid == 7754 || itemid == 7752 || itemid == 7758 || itemid == 7760) itemid = 2000;
	else if (itemid == 1460) itemid = 1970;
	else if (itemid == 3556) itemid = 4186;
	else if (itemid == 3556) itemid = 4188;
	else if (itemid == 2914 || itemid == 3012 || itemid == 3014) itemid = 4246;
	else if (itemid == 3016 || itemid == 3018) itemid = 4248;
	else if (itemid == 414 || itemid == 416 || itemid == 418 || itemid == 420 || itemid == 422 || itemid == 424 || itemid == 426 || itemid == 4634 || itemid == 4636 || itemid == 4638 || itemid == 4640 || itemid == 4642) itemid = 4192;
	else if (itemid == 1114) itemid = 4156;
	else if (itemid == 366) itemid = 4136;
	else if (itemid == 1950) itemid = 4152;
	else if (itemid == 2386) itemid = 4166;
	else if (itemid == 762) itemid = 4190;
	else if (itemid == 2860 || itemid == 2268) itemid = 4172;
	else if (itemid == 2972) itemid = 4182;
	else if (itemid == 3294) itemid = 4144;
	else if (itemid == 3296) itemid = 4146;
	else if (itemid == 3298) itemid = 4148;
	else if (itemid == 3290) itemid = 4140;
	else if (itemid == 3288) itemid = 4138;
	else if (itemid == 3292) itemid = 4142;
	else if (itemid == 1198) itemid = 5256;
	else if (itemid == 4960) itemid = 5208;
	else if (itemid == 1242) itemid = 5216;
	else if (itemid == 1244) itemid = 5218;
	else if (itemid == 1248) itemid = 5220;
	else if (itemid == 1246) itemid = 5214;
	else if (itemid == 5018) itemid = 5210;
	else if (itemid == 1408) itemid = 5254;
	else if (itemid == 4334) itemid = 5250;
	else if (itemid == 4338) itemid = 5252;
	else if (itemid == 3792) itemid = 5244;
	else if (itemid == 1294) itemid = 5236;
	else if (itemid == 6144) itemid = 7104;
	else if (itemid == 4732) itemid = 7124;
	else if (itemid == 4326) itemid = 7122;
	else if (itemid == 6300) itemid = 7102;
	else if (itemid == 2868) itemid = 7100;
	else if (itemid == 6798) itemid = 7126;
	else if (itemid == 6160) itemid = 7104;
	else if (itemid == 6176) itemid = 7124;
	else if (itemid == 5246) itemid = 7122;
	else if (itemid == 5246) itemid = 7102;
	else if (itemid == 5246) itemid = 7100;
	else if (itemid == 7998) itemid = 9048;
	else if (itemid == 6196) itemid = 9056;
	else if (itemid == 2392) itemid = 9114;
	else if (itemid == 8018) itemid = 9034;
	else if (itemid == 8468) itemid = 10232;

	else if (itemid == 4360) itemid = 10194;
	else if (itemid == 9364) itemid = 10206;
	else if (itemid == 9322) itemid = 10184;

	else if (itemid == 3818) itemid = 10192;
	else if (itemid == 3794) itemid = 10190;
	else if (itemid == 7696) itemid = 10186;

	else if (itemid == 10212) itemid = 10212;

	else if (itemid == 10328)
	{
		int itemuMas[154] = { 10232, 10194, 10206, 10184, 10192, 10190, 10186, 10212, 1212, 1190, 1206, 1166, 1964, 1976, 1998, 1946, 2002, 1958, 1952, 2030, 3104, 3112, 3120, 3092, 3094, 3096, 4184, 4178, 4174, 4180, 4170, 4168, 4150, 1180, 1224, 5226, 5228, 5230, 5212, 5246, 5242, 5234, 7134, 7118, 7132, 7120, 7098, 9018, 9038, 9026, 9066, 9058, 9044, 9024, 9032, 9036, 9028, 9030, 9110, 9112, 10386, 10326, 10324, 10322, 10328, 10316, 1198, 1208, 1222, 1200, 1220, 1202, 1238, 1168, 1172, 1230, 1194, 1192, 1226, 1196, 1236, 1182, 1184, 1186, 1188, 1170, 1212, 1214, 1232, 1178, 1234, 1250, 1956, 1990, 1968, 1960, 1948, 1966, 3114, 3118, 3100, 3122, 3124, 3126, 3108, 3098, 1962, 2000, 1970, 4186, 4188, 4246, 4248, 4192, 4156, 4136, 4152, 4166, 4190, 4172, 4182, 4144, 4146, 4148, 4140, 4138, 4142, 5256, 5208, 5216, 5218, 5220, 5214, 5210, 5254, 5250, 5252, 5244, 5236, 7104, 7124, 7122, 7102, 7100, 7126, 7104, 7124, 7122, 7102, 7100, 9048, 9056, 9114, 9034 };
		auto randIndex = rand() % 154;
		itemid = itemuMas[randIndex];
		playerRespawns(world, peer, false);
		Player::OnConsoleMessage(peer, "`2" + getItemDef(pradinis).name + " `owas devoursed by Growganoth!");
		Player::OnConsoleMessage(peer, "`4Growganoth retrieves a very special artifact from his tomb on your behalf and kills you for the service!");
		Player::OnConsoleMessage(peer, "`oA `2" + getItemDef(itemid).name + " `owas bestoved upon you!");
		if (getItemDef(itemid).name.find("Wings") != string::npos || getItemDef(itemid).name.find("Cape") != string::npos || getItemDef(itemid).name.find("Cloak") != string::npos)
		{
			ENetPeer* currentPeer;
			for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
			{
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
				Player::OnConsoleMessage(currentPeer, "`4Growganoth `ohonors `w" + static_cast<PlayerInfo*>(peer->data)->displayName + " `owith a `5Rare " + getItemDef(itemid).name + "");
			}
		}
		auto success = true;
		SaveItemMoreTimes(itemid, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from growganoth");
		if (count >= 2)
		{
			auto success = true;
			SaveItemMoreTimes(10328, count - 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from growganoth");
		}
		return;
	}

	else if (getItemDef(itemid).blockType == BlockTypes::WEATHER && itemid != 932) itemid = 1210;

	else if (Rarity < 10)
	{
		int itemuMas[2] = { 1208, 5256 };
		auto randIndex = rand() % 2;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity < 15)
	{
		int itemuMas[5] = { 1222, 1198, 1992, 5256, 1208 };
		auto randIndex = rand() % 5;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity < 20)
	{
		int itemuMas[7] = { 1200, 1992, 1982, 5256, 1198, 1208, 1222 };
		auto randIndex = rand() % 7;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity < 25)
	{
		int itemuMas[9] = { 1220, 1992, 1982, 5256, 1198, 1208, 1222, 1200, 10198 };
		auto randIndex = rand() % 9;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity < 30)
	{
		int itemuMas[11] = { 1202, 1992, 1982, 5240, 5256, 1198, 1208, 1222, 1200, 1220, 10198 };
		auto randIndex = rand() % 11;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity < 35)
	{
		int itemuMas[17] = { 1238, 1992, 1982, 4160, 4162, 5240, 5238, 5256, 7116, 1198, 1208, 1222, 1200, 1220, 1202, 10198, 10196 };
		auto randIndex = rand() % 17;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity < 40)
	{
		int itemuMas[18] = { 1168, 1992, 1982, 4160, 4162, 5240, 5238, 5256, 7116, 1198, 1208, 1222, 1200, 1220, 1202, 1238, 10198, 10196 };
		auto randIndex = rand() % 18;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity < 45)
	{
		int itemuMas[21] = { 1172, 1992, 1982, 3116, 4160, 4162, 4164, 5240, 5238, 5256, 7116, 1198, 1208, 1222, 1200, 1220, 1202, 1238, 1168, 10198, 10196 };
		auto randIndex = rand() % 21;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity < 50)
	{
		int itemuMas[22] = { 1230, 1992, 1982, 3116, 4160, 4162, 4164, 5240, 5238, 5256, 7116, 1198, 1208, 1222, 1200, 1220, 1202, 1238, 1168, 1172, 10198, 10196 };
		auto randIndex = rand() % 22;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity < 55)
	{
		int itemuMas[25] = { 1194, 1192, 1992, 1982, 3116, 4160, 4162, 4164, 5240, 5238, 5256, 7116, 1198, 1208, 1222, 1200, 1220, 1202, 1238, 1168, 1172, 1230, 10198, 10196, 10202 };
		auto randIndex = rand() % 25;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity < 60)
	{
		int itemuMas[27] = { 1226, 1992, 1982, 3116, 4160, 4162, 4164, 5240, 5238, 5256, 7116, 7108, 1198, 1208, 1222, 1200, 1220, 1202, 1238, 1168, 1172, 1230, 1194, 1192, 10198, 10196, 10202 };
		auto randIndex = rand() % 27;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity < 65)
	{
		int itemuMas[28] = { 1196, 1992, 1982, 3116, 4160, 4162, 4164, 5240, 5238, 5256, 7116, 7108, 1198, 1208, 1222, 1200, 1220, 1202, 1238, 1168, 1172, 1230, 1194, 1192, 1226, 10198, 10196, 10202 };
		auto randIndex = rand() % 28;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity < 70)
	{
		int itemuMas[29] = { 1236, 1992, 1982, 3116, 4160, 4162, 4164, 5240, 5238, 5256, 7116, 7108, 1198, 1208, 1222, 1200, 1220, 1202, 1238, 1168, 1172, 1230, 1194, 1192, 1226, 1196, 10198, 10196, 10202 };
		auto randIndex = rand() % 29;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity < 80)
	{
		int itemuMas[44] = { 1182, 1184, 1186, 1188, 1992, 1982, 1994, 1972, 1980, 1988, 3116, 3102, 4160, 4162, 4164, 4154, 5224, 5222, 5232, 5240, 5238, 5256, 7116, 7108, 7110, 1198, 1208, 1222, 1200, 1220, 1202, 1238, 1168, 1172, 1230, 1194, 1192, 1226, 1196, 1236, 10198, 10196, 10202, 10204 };
		auto randIndex = rand() % 44;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity < 90)
	{
		int itemuMas[48] = { 1170, 1992, 1982, 1994, 1972, 1980, 1988, 1984, 3116, 3102, 4160, 4162, 4164, 4154, 4158, 5224, 5222, 5232, 5240, 5238, 5256, 7116, 7108, 7110, 7128, 1198, 1208, 1222, 1200, 1220, 1202, 1238, 1168, 1172, 1230, 1194, 1192, 1226, 1196, 1236, 1182, 1184, 1186, 1188, 10198, 10196, 10202, 10204 };
		auto randIndex = rand() % 48;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity >= 90 && Rarity != 999)
	{
		int itemuMas[56] = { 1216, 1218, 1992, 1982, 1994, 1972, 1980, 1988, 1984, 3116, 3102, 3106, 3110, 4160, 4162, 4164, 4154, 4158, 5224, 5222, 5232, 5240, 5248, 5238, 5256, 7116, 7108, 7110, 7128, 7112, 7114, 7130, 1198, 1208, 1222, 1200, 1220, 1202, 1238, 1168, 1172, 1230, 1194, 1192, 1226, 1196, 1236, 1182, 1184, 1186, 1188, 1170, 10198, 10196, 10202, 10204 };
		auto randIndex = rand() % 56;
		itemid = itemuMas[randIndex];
		count = 1;
	}

	if (pradinis == itemid)
	{
		playerRespawns(world, peer, false);
		Player::OnConsoleMessage(peer, "`4Growganoth rejects your puny offering and eats you instead!");
		Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4Growganoth rejects your puny offering and eats you instead!", 0, true);
		auto success = true;
		SaveItemMoreTimes(pradinis, count, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from growganoth");
		return;
	}

	playerRespawns(world, peer, false);
	Player::OnConsoleMessage(peer, "`2" + getItemDef(pradinis).name + " `owas devoursed by Growganoth!");
	Player::OnConsoleMessage(peer, "`oA `2" + getItemDef(itemid).name + " `owas bestoved upon you!");
	auto success = true;
	SaveItemMoreTimes(itemid, count, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from growganoth");

}