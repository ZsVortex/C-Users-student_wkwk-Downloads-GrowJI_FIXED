#pragma once
#include "stdafx.h"
#include <vector>
using namespace std;
vector<WorldInfo> worlds;

/*Dropping the event item*/
inline void SendDropEventItem(const string WorldName, const int netID, const int x, int y, const int item, const int count, const BYTE specialEffect)
{
	if (item >= maxItems) return;
	if (item < 0) return;
	auto world = worldDB.get2(WorldName).ptr;
	DroppedItem itemDropped;
	itemDropped.id = item;
	itemDropped.count = count;
	itemDropped.x = x;
	itemDropped.y = y;
	itemDropped.droppedby = "Special Event";
	world->droppedCount++;
	itemDropped.uid = world->droppedCount;
	world->droppedItems.push_back(itemDropped);
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (EventWorld(currentPeer, WorldName))
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

/*Spawning the event items*/
inline void SpawnEventItem(const string WorldName, const int ItemID, const int count, int Time, const int x, const int y, const int Multiple)
{
	for (auto i = 0; i < Multiple; i++)
	{
		const auto DropX = rand() % x * 32;
		const auto DropY = rand() % y * 32;
		SendDropEventItem(WorldName, -1, DropX, DropY, ItemID, count, 0);
	}
}

/*Basically the all world event things, this is a loop which finds active worlds*/
inline void WorldEvents()
{
	while (true)
	{
		Sleep(600000); /*every 10 minutes event happens*/
		auto worlds = worldDB.getRandomWorlds();
		for (auto i = 0; i < worlds.size(); i++)
		{
			if (serverIsFrozen)break;
			if (getPlayersCountInWorld(worlds[i].name) <= 0) continue; /*to avoid events in empty worlds*/
			SendConsole("Event starting in " + worlds[i].name, "EVENT");
			/*Choose event type*/
			string Notification = "";
			auto ItemID = 0;
			auto Count = 0;
			const auto Time = 0; /*Not used for now*/
			auto Multiple = 0; /*How much times the drop will be repeated*/
			int values;
			srand(time(nullptr));
			if (HarvestEvent) values = rand() % 15 + 1;
			else if (ValentineEvent) values = rand() % 30 + 1;
			else values = rand() % 13 + 1;
			switch (values)
			{
			case 1: /*World Lock Event*/
			{
				Notification = "`wDont Do Anything That Violates The `4RULES";
				ItemID = 0;
				Count = 0;
				Multiple = 0;
				break;
			}
			case 2: /*Surgery Split Event*/
			{
				Notification = "`wDont Do Anything That Violates The `4RULES";
				ItemID = 0;
				Count = 0;
				Multiple = 0;
				break;
			}
			case 3: /*The Fireworks Event*/
			{
				Notification = "`wDont Do Anything That Violates The `4RULES";
				ItemID = 0;
				Count = 0;
				Multiple = 0;
				break;
			}
			case 4: /*Blessed Rock Event*/
			{
				Notification = "`wDont Do Anything That Violates The `4RULES";
				ItemID = 0;
				Count = 0;
				Multiple = 0;
				break;
			}
			case 5: /*Sparkling Gold Event*/
			{
				Notification = "`wDont Do Anything That Violates The `4RULES";
				ItemID = 0;
				Count = 0;
				Multiple = 0;
				break;
			}
			case 6: /*Blessing Token Event*/
			{
				Notification = "`wDont Do Anything That Violates The `4RULES";
				ItemID = 0;
				Count = 0;
				Multiple = 0;
				break;
			}
			case 7: /*Beautiful Crystal Event*/
			{
				Notification = "`wDont Do Anything That Violates The `4RULES";
				ItemID = 0;
				Count = 0;
				Multiple = 0;
				break;
			}
			case 8: /*Magical Seeds Event*/
			{
				/*auto SeedID = rand() % maxItems;
				if (!isSeed(SeedID)) SeedID += 1;
				Notification = "`wDont Do Anything That Violates The `4RULES";
				ItemID = SeedID;
				Count = 0;
				Multiple = 0;
				break;*/

				Notification = "`wDont Do Anything That Violates The `4RULES";
				ItemID = 0;
				Count = 0;
				Multiple = 0;
				break;
			}
			case 9: /*Luck of the Growish Event*/
			{
				Notification = "`wDont Do Anything That Violates The `4RULES";
				ItemID = 0;
				Count = 0;
				Multiple = 0;
				break;
			}
			case 10: /*Shinny Potion*/
			{
				Notification = "`wDont Do Anything That Violates The `4RULES";
				ItemID = 0;
				Count = 0;
				Multiple = 0;
				break;
			}
			case 11: /*What's that?*/
			{
				Notification = "`wDont Do Anything That Violates The `4RULES";
				ItemID = 0;
				Count = 0;
				Multiple = 0;
				break;
			}
			case 12: /*Egg Hunt*/
			{
				Notification = "`wDont Do Anything That Violates The `4RULES";
				ItemID = 0;
				Count = 0;
				Multiple = 0;
				break;
			}
			case 13: /*Jackpot*/
			{
				Notification = "`wDont Do Anything That Violates The `4RULES";
				ItemID = 0;
				Count = 0;
				Multiple = 0;
				break;
			}
			case 14: /*Songpyeon Hunt (harvest fest only)*/
			{
				Notification = "`wDont Do Anything That Violates The `4RULES";
				ItemID = 0;
				Count = 0;
				Multiple = 0;
				break;
			}
			case 15: /*Mooncake Rain (harvest fest only)*/
			{
				vector<int> CakeBase{ 1058, 1094, 1096, 1098, 1828, 3870, 7058 };
				const int Index = rand() % CakeBase.size();
				const auto IID = CakeBase[Index];
				Notification = "`wDont Do Anything That Violates The `4RULES" + getItemDef(IID).name + " `4Warning!";
				ItemID = IID;
				Count = 0;
				Multiple = 0;
				break;
			}
			case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29: case 30: /*Share The Love (valentine event only)*/
			{
				Notification = "`wDont Do Anything That Violates The `4RULES";
				bool success = true;
				for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (EventWorld(currentPeer, worlds[i].name)) /*Display message for all players in world*/
					{
						SaveItemMoreTimes(3402, 1, currentPeer, success, static_cast<PlayerInfo*>(currentPeer->data)->rawName + " `4Warning");
						SendTradeEffect(currentPeer, 3402, static_cast<PlayerInfo*>(currentPeer->data)->netID, static_cast<PlayerInfo*>(currentPeer->data)->netID, 150);
					}
				}
				break;
			}
			default: break;
			}
			for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
			{
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
				if (EventWorld(currentPeer, worlds[i].name)) /*Display message for all players in world*/
				{
					Player::OnAddNotification(currentPeer, Notification, "audio/cumbia_horns.wav", "interface/large/special_event.rttex");
				}
			}
			if (ItemID != 0) SpawnEventItem(worlds[i].name, ItemID, Count, Time, worlds[i].width, worlds[i].height, Multiple); /*Spawn the Item*/
			break;
		}
	}
}
