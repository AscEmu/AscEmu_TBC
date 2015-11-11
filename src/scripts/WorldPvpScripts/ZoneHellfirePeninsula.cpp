/*
 * Moon++ Scripts for Ascent MMORPG Server
 * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (C) 2007-2008 Moon++ Team <http://www.moonplusplus.info/>
 * Copyright (C) 2008-2011 Sun++ Team <http://Sunscripting.org/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * Summit MMORPG Server Software
 * Copyright (c) 2008 Summit Server Team
 * See COPYING for license details.
 */

#include "StdAfx.h"

// Some customizable defines.
// Maybe move these to config?

#define BANNER_RANGE	900
#define UPDATE_PERIOD	1000
#define CAPTURE_RATE	1

// Towers
enum Towers
{
	TOWER_OVERLOOK,
	TOWER_STADIUM,
	TOWER_BROKENHILL,
	TOWER_COUNT,
};

// Tower GameObject Ids
#define TOWER_WEST 182173
#define TOWER_NORTH 182174
#define TOWER_SOUTH 182175

// Buff Ids
#define HELLFIRE_SUPERORITY_ALLIANCE 32071
#define HELLFIRE_SUPERORITY_HORDE 32049

// Owners of the towers, used for save/restore
int32 g_towerOwners[TOWER_COUNT]  = { -1, -1, -1 };

// global variables
uint32 g_hordeTowers	= 0;
uint32 g_allianceTowers = 0;
int32 g_superiorTeam	= -1;			// SUPERIORITY

// Fields to update visual view of the client map
static const uint32 g_hordeStateFields[3]	= { WORLDSTATE_HELLFIRE_STADIUM_HORDE, WORLDSTATE_HELLFIRE_OVERLOOK_HORDE, WORLDSTATE_HELLFIRE_BROKENHILL_HORDE };
static const uint32 g_allianceStateFields[3] = { WORLDSTATE_HELLFIRE_STADIUM_ALLIANCE, WORLDSTATE_HELLFIRE_OVERLOOK_ALLIANCE, WORLDSTATE_HELLFIRE_BROKENHILL_ALLIANCE };
static const uint32 g_neutralStateFields[3]	= { WORLDSTATE_HELLFIRE_STADIUM_NEUTRAL, WORLDSTATE_HELLFIRE_OVERLOOK_NEUTRAL, WORLDSTATE_HELLFIRE_BROKENHILL_NEUTRAL };

// updates clients visual counter, and adds the buffs to players if needed
AscEmu_INLINE void UpdateTowerCount(MapMgr * mgr)
{
	mgr->GetWorldStateManager()->SetWorldState(WORLDSTATE_HELLFIRE_ALLIANCE_TOWERS_CONTROLLED, g_allianceTowers);
	mgr->GetWorldStateManager()->SetWorldState(WORLDSTATE_HELLFIRE_HORDE_TOWERS_CONTROLLED, g_hordeTowers);

	if(g_superiorTeam == 0 && g_allianceTowers != 3)
	{
		mgr->RemovePositiveAuraFromPlayers(0, HELLFIRE_SUPERORITY_ALLIANCE);
		g_superiorTeam = -1;
	}

	if(g_superiorTeam == 1 && g_hordeTowers != 3)
	{
		mgr->RemovePositiveAuraFromPlayers(1, HELLFIRE_SUPERORITY_HORDE);
		g_superiorTeam = -1;
	}

	if(g_allianceTowers == 3 && g_superiorTeam != 0)
	{
		g_superiorTeam = 0;
		mgr->CastSpellOnPlayers(0, HELLFIRE_SUPERORITY_ALLIANCE);
	}

	if(g_hordeTowers == 3 && g_superiorTeam != 1)
	{
		g_superiorTeam = 1;
		mgr->CastSpellOnPlayers(1, HELLFIRE_SUPERORITY_HORDE);
	}
}

enum BannerStatus
{
	BANNER_STATUS_NEUTRAL	= 0,
	BANNER_STATUS_ALLIANCE	= 1,
	BANNER_STATUS_HORDE		= 2,
};

class HellfirePeninsulaBannerAI : public GameObjectAIScript
{
private:
	std::map<uint32, uint32>	m_StoredPlayers;
	uint32						m_Status;
	string						m_ControlPointName;
	uint32						m_towerid;
	uint32						m_bannerStatus;

public:
	GameObject * pBanner;

	HellfirePeninsulaBannerAI(GameObject *go) : GameObjectAIScript(go)
	{
		m_bannerStatus = BANNER_STATUS_NEUTRAL;
		m_Status = 50;

		switch(go->GetEntry())
		{
		case TOWER_WEST:
			m_ControlPointName	= "The Stadium";
			m_towerid			= TOWER_STADIUM;
			break;

		case TOWER_NORTH:
			m_ControlPointName	= "The Overlook";
			m_towerid			= TOWER_OVERLOOK;
			break;

		case TOWER_SOUTH:
			m_ControlPointName	= "Broken Hill";
			m_towerid			= TOWER_BROKENHILL;
			break;

		default:
			m_ControlPointName	= "Unknown";
			break;
		}
	}

	void AIUpdate()
	{
		uint32 plrcounts[2]  = { 0, 0 };

		// details:
		//   loop through inrange players, for new ones, send the enable CP worldstate.
		//   the value of the map is a timestamp of the last update, to avoid cpu time wasted
		//   doing lookups of objects that have already been updated
		map<uint32,uint32>::iterator it2, it3;
		uint32 timeptr = static_cast<uint32>(UNIXTIME);
		bool in_range = false;
		bool is_valid = false;
		
		for(PlayerSet::const_iterator itr = _gameobject->GetInRangePlayerSetBegin();itr != _gameobject->GetInRangePlayerSetEnd();)
		{
			Player * plr = (*itr);
			++itr;

			if(!plr->IsPvPFlagged() || plr->IsStealth())
				is_valid = false;
			else
				is_valid = true;

			in_range = (_gameobject->GetDistanceSq(plr) <= BANNER_RANGE) ? true : false;

			it2 = m_StoredPlayers.find(plr->GetLowGUID());
			if(it2 == m_StoredPlayers.end())
			{
				// new player :)
				if(in_range)
				{
					plr->SendWorldStateUpdate(WORLDSTATE_HELLFIRE_PVP_CAPTURE_BAR_DISPLAY, 1);
					plr->SendWorldStateUpdate(WORLDSTATE_HELLFIRE_PVP_CAPTURE_BAR_VALUE, m_Status);
					m_StoredPlayers.insert(make_pair(plr->GetLowGUID(), timeptr));

					if(is_valid)
					{
						plrcounts[plr->GetTeam()]++;
					}
				}
			}
			else
			{
				// oldie
				if(!in_range)
				{
					plr->SendWorldStateUpdate(WORLDSTATE_HELLFIRE_PVP_CAPTURE_BAR_DISPLAY, 0);
					m_StoredPlayers.erase(it2);
				}
				else
				{
					plr->SendWorldStateUpdate(WORLDSTATE_HELLFIRE_PVP_CAPTURE_BAR_VALUE, m_Status);
					it2->second = timeptr;
					if(is_valid)
					{
						plrcounts[plr->GetTeam()]++;
					}
				}
			}
		}

		// handle stuff for the last tick
		if(m_Status == 100 && m_bannerStatus != BANNER_STATUS_ALLIANCE)
		{
			m_bannerStatus = BANNER_STATUS_ALLIANCE;
			SetArtKit();

			// send message to everyone in the zone, has been captured by the Alliance
			_gameobject->GetMapMgr()->SendPvPCaptureMessage(ZONE_HELLFIRE_PENINSULA, ZONE_HELLFIRE_PENINSULA, "|cffffff00%s has been taken by the Alliance!|r", m_ControlPointName.c_str());

			// tower update
			g_allianceTowers++;
			UpdateTowerCount(_gameobject->GetMapMgr());

			// state update
			_gameobject->GetMapMgr()->GetWorldStateManager()->SetWorldState(g_neutralStateFields[m_towerid], 0);
			_gameobject->GetMapMgr()->GetWorldStateManager()->SetWorldState(g_allianceStateFields[m_towerid], 1);

			// woot
			g_towerOwners[m_towerid] = 1;
			UpdateInDB();

			//Hellfire Fortifications - complete objective
																					
			for(PlayerSet::iterator itr = _gameobject->GetInRangePlayerSetBegin();itr != _gameobject->GetInRangePlayerSetEnd();)  
			{																											
				Player * pPlr = (*itr);																					
				++itr;	
				{
					if(pPlr->GetTeam() == HORDE && pPlr->HasQuest(10106))
					{
						QuestLogEntry * pQLE = pPlr->GetQuestLogForEntry(10106);
						if(pQLE && pQLE->GetMobCount(m_towerid) == 0)
						{
							pQLE->SetMobCount(m_towerid, 1);
							pQLE->SendUpdateAddKill(m_towerid);
							pQLE->UpdatePlayerFields();
						}
					}
				}
			}
		}
		else if(m_Status == 0 && m_bannerStatus != BANNER_STATUS_HORDE)
		{
			m_bannerStatus = BANNER_STATUS_HORDE;
			SetArtKit();

			// send message to everyone in the zone, has been captured by the Horde
			_gameobject->GetMapMgr()->SendPvPCaptureMessage(ZONE_HELLFIRE_PENINSULA, ZONE_HELLFIRE_PENINSULA, "|cffffff00%s has been taken by the Horde!|r", m_ControlPointName.c_str());
			
			// tower update
			g_hordeTowers++;
			UpdateTowerCount(_gameobject->GetMapMgr());

			// state update
			_gameobject->GetMapMgr()->GetWorldStateManager()->SetWorldState(g_neutralStateFields[m_towerid], 0);
			_gameobject->GetMapMgr()->GetWorldStateManager()->SetWorldState(g_hordeStateFields[m_towerid], 1);

			// woot
			g_towerOwners[m_towerid] = 0;
			UpdateInDB();
			//Hellfire Fortifications - complete objective			
			
			for(PlayerSet::iterator itr = _gameobject->GetInRangePlayerSetBegin();itr != _gameobject->GetInRangePlayerSetEnd();)  
			{																											
				Player * pPlr = (*itr);																					
				++itr;	
				{
					if(pPlr->GetTeam() == HORDE && pPlr->HasQuest(10110))
					{
						QuestLogEntry * pQLE = pPlr->GetQuestLogForEntry(10110);
						if(pQLE && pQLE->GetMobCount(m_towerid) == 0)
						{
							pQLE->SetMobCount(m_towerid, 1);
							pQLE->SendUpdateAddKill(m_towerid);
							pQLE->UpdatePlayerFields();
						}
					}
				}
			}
		}
		else if(m_bannerStatus != BANNER_STATUS_NEUTRAL)
		{
			// if the difference for the faction is >50, change to neutral
			if(m_bannerStatus == BANNER_STATUS_ALLIANCE && m_Status <= 50)
			{
				// send message: The Alliance has lost control of point xxx
				m_bannerStatus = BANNER_STATUS_NEUTRAL;
				SetArtKit();
				
				g_allianceTowers--;
				UpdateTowerCount(_gameobject->GetMapMgr());

				_gameobject->GetMapMgr()->SendPvPCaptureMessage(ZONE_HELLFIRE_PENINSULA, ZONE_HELLFIRE_PENINSULA, "|cffffff00The Alliance have lost control of %s!|r", m_ControlPointName.c_str());

				// state update
				_gameobject->GetMapMgr()->GetWorldStateManager()->SetWorldState(g_allianceStateFields[m_towerid], 0);
				_gameobject->GetMapMgr()->GetWorldStateManager()->SetWorldState(g_neutralStateFields[m_towerid], 1);

				// woot
				g_towerOwners[m_towerid] = -1;
				UpdateInDB();
			}
			else if(m_bannerStatus == BANNER_STATUS_HORDE && m_Status >= 50)
			{
				// send message: The Alliance has lost control of point xxx
				m_bannerStatus = BANNER_STATUS_NEUTRAL;
				SetArtKit();

				g_hordeTowers--;
				UpdateTowerCount(_gameobject->GetMapMgr());

				_gameobject->GetMapMgr()->SendPvPCaptureMessage(ZONE_HELLFIRE_PENINSULA, ZONE_HELLFIRE_PENINSULA, "|cffffff00The Horde have lost control of %s!|r", m_ControlPointName.c_str());

				// state update
				_gameobject->GetMapMgr()->GetWorldStateManager()->SetWorldState(g_hordeStateFields[m_towerid], 0);
				_gameobject->GetMapMgr()->GetWorldStateManager()->SetWorldState(g_neutralStateFields[m_towerid], 1);

				// woot
				g_towerOwners[m_towerid] = -1;
				UpdateInDB();
			}
		}

		// send any out of range players the disable flag
		for(it2 = m_StoredPlayers.begin(); it2 != m_StoredPlayers.end();)
		{
			it3 = it2;
			++it2;

			if(it3->second != timeptr)
			{
				Player * plr = _gameobject->GetMapMgr()->GetPlayer(it3->first);
				if(plr != NULL)
				{
					plr->SendWorldStateUpdate(WORLDSTATE_HELLFIRE_PVP_CAPTURE_BAR_DISPLAY, 0);
				}
				m_StoredPlayers.erase(it3);
			}
		}

		// work out current status for next tick
		uint32 delta = 0;
		if(plrcounts[0] > plrcounts[1])
		{
			delta = plrcounts[0] - plrcounts[1];
			delta *= CAPTURE_RATE;

			// cap it at 25 so the banner always gets removed.
			if(delta > 25)
				delta = 25;

			m_Status += delta;
			if(m_Status >= 100)
				m_Status = 100;
		}
		else if(plrcounts[1] > plrcounts[0])
		{
			delta = plrcounts[1] - plrcounts[0];
			delta *= CAPTURE_RATE;
			
			// cap it at 25 so the banner always gets removed.
			if(delta > 25)
				delta = 25;

			if(delta > m_Status)
				m_Status = 0;
			else
				m_Status -= delta;
		}
	}

	void SetArtKit()
	{
		// big towers
		static const uint32 artkits_towers[3][3] = {
			{ 69, 67, 68 }, { 63, 62, 61 }, { 66, 65, 64 },
		};

		// flag poles
		static const uint32 artkits_flagpole[3] = { 3, 2, 1 };

		// set away
		_gameobject->SetUInt32Value(GAMEOBJECT_ARTKIT, artkits_flagpole[m_bannerStatus]);
		pBanner->SetUInt32Value(GAMEOBJECT_ARTKIT, artkits_towers[m_towerid][m_bannerStatus]);
	}

	void SetupGo(MapMgr * pMapMgr)
	{
		m_bannerStatus = BANNER_STATUS_NEUTRAL;

		// preloaded data, do we have any?
		if(g_towerOwners[m_towerid] == 1)
		{
			m_bannerStatus = BANNER_STATUS_HORDE;
			m_Status = 0;

			// state update
			pMapMgr->GetWorldStateManager()->SetWorldState(g_hordeStateFields[m_towerid], 1);
			pMapMgr->GetWorldStateManager()->SetWorldState(g_neutralStateFields[m_towerid], 0);

			// countz
			g_hordeTowers++;
			UpdateTowerCount(pMapMgr);
			SetArtKit();
		}
		else if(g_towerOwners[m_towerid] == 0)
		{
			m_bannerStatus = BANNER_STATUS_ALLIANCE;
			m_Status = 100;

			// state update
			pMapMgr->GetWorldStateManager()->SetWorldState(g_allianceStateFields[m_towerid], 1);
			pMapMgr->GetWorldStateManager()->SetWorldState(g_neutralStateFields[m_towerid], 0);

			// countz
			g_allianceTowers++;
			UpdateTowerCount(pMapMgr);
			SetArtKit();
		}

		// start the event timer
		RegisterAIUpdateEvent(UPDATE_PERIOD);
	}

	//////////////////////////////////////////////////////////////////////////
	// Save Data To DB
	//////////////////////////////////////////////////////////////////////////
	void UpdateInDB()
	{
		static const string fieldnames[TOWER_COUNT] = { "hellfire-stadium-status", "hellfire-overlook-status", "hellfire-brokenhill-status" };
		string msg = "-1";
		if(m_Status == 100)
			msg = "0";
		else
			msg = "1";
			
		WorldStateManager::SetPersistantSetting(fieldnames[m_towerid].c_str(), msg.c_str());
	}

	static GameObjectAIScript *Create(GameObject* pGameObject) { return new HellfirePeninsulaBannerAI(pGameObject); }
};

//////////////////////////////////////////////////////////////////////////
// Zone Hook
//////////////////////////////////////////////////////////////////////////

void ZoneHook(Player *plr, uint32 Zone, uint32 OldZone)
{
	static const uint32 spellids[2]  = { HELLFIRE_SUPERORITY_ALLIANCE, HELLFIRE_SUPERORITY_HORDE };
	if(Zone == ZONE_HELLFIRE_PENINSULA)
	{
		if(g_superiorTeam == plr->GetTeam())
		{
			plr->CastSpell(plr, dbcSpell.LookupEntryForced(spellids[plr->GetTeam()]), true);
		}
	}
	else if(OldZone == ZONE_HELLFIRE_PENINSULA)
	{
		if(g_superiorTeam == plr->GetTeam())
		{
			plr->RemoveAura(spellids[plr->GetTeam()]);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Object Spawn Data
//////////////////////////////////////////////////////////////////////////

struct sgodata
{
	uint32 entry;
	float posx;
	float posy;
	float posz;
	float facing;
	float orientation[4];
	uint32 state;
	uint32 flags;
	uint32 faction;
	float scale;
	uint32 is_banner;
};

void SpawnObjects(MapMgr *pmgr)
{
	if(pmgr->GetMapId() != 530)
		return;

	const static sgodata godata[] = {
		{ 182173, -290.016f, 3702.42f, 56.6729f, 0.0349066f, 0, 0, 0.0174524f, 0.999848f, 1, 32, 0, 1 },			// stadium
		{ 182174, -184.889f, 3476.93f, 38.205f, -0.0174535f, 0, 0, 0.00872664f, -0.999962f, 1, 32, 0, 1 },			// overlook
		{ 182175, -471.462f, 3451.09f, 34.6432f, 0.174533f, 0, 0, 0.0871557f, 0.996195f, 1, 32, 0, 1 },				// brokenhill
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	};

	const static sgodata godata_banner[] = {
		{ 183515, -289.61f, 3696.83f, 75.9447f, 3.12414f, 0, 0, 0.999962f, 0.00872656f, 1, 32, 1375, 1 },					// stadium
		{ 182525, -187.887f, 3459.38f, 60.0403f, -3.12414f, 0, 0, 0.999962f, -0.00872653f, 1, 32, 1375, 1 },				// overlook
		{ 183514, -467.078f, 3528.17f, 64.7121f, 3.14159f, 0, 0, 1, -4.37114E-8f, 1, 32, 1375, 1 },						// brokenhill
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	};

	for(uint32 i = 0; i < 3; ++i)
	{
		GameObject *pGo = pmgr->GetInterface()->SpawnGameObject(godata[i].entry, godata[i].posx, godata[i].posy, godata[i].posz, godata[i].facing, false, 0, 0);
		if(pGo == NULL)
			continue;

		GameObject *pGo2 = pmgr->GetInterface()->SpawnGameObject(godata_banner[i].entry, godata_banner[i].posx, godata_banner[i].posy, godata_banner[i].posz, godata_banner[i].facing, false, 0, 0);
		if(pGo2 == NULL)
		{
			pGo->Delete();
			continue;
		}

		pGo->SetUInt32Value(GAMEOBJECT_STATE, godata[i].state);
		pGo->SetUInt32Value(GAMEOBJECT_FLAGS, godata[i].flags);
		pGo->SetUInt32Value(GAMEOBJECT_FACTION, godata[i].faction);

		pGo2->SetUInt32Value(GAMEOBJECT_STATE, godata_banner[i].state);
		pGo2->SetUInt32Value(GAMEOBJECT_FLAGS, godata_banner[i].flags);
		pGo2->SetUInt32Value(GAMEOBJECT_FACTION, godata_banner[i].faction);

		for(uint32 j = 0; j < 4; ++j)
		{
			pGo->SetFloatValue(GAMEOBJECT_ROTATION + j, godata[i].orientation[j]);
			pGo2->SetFloatValue(GAMEOBJECT_ROTATION + j, godata_banner[i].orientation[j]);
		}

		// now make his script
		pGo->SetScript(new HellfirePeninsulaBannerAI(pGo));
		dynamic_cast<HellfirePeninsulaBannerAI*>(pGo->GetScript())->pBanner = pGo2;

		pGo->AddToWorld(pmgr);
		pGo2->AddToWorld(pmgr);

		dynamic_cast<HellfirePeninsulaBannerAI*>(pGo->GetScript())->SetupGo(pmgr);
	}
}

void SetupPvPHellfirePeninsula(ScriptMgr *mgr)
{
	// register instance hooker
	mgr->register_hook(SERVER_HOOK_EVENT_ON_ZONE, ZoneHook);
	mgr->register_hook(SERVER_HOOK_EVENT_ON_CONTIENT_CREATE, SpawnObjects);

	// load data
	const string tstadium = WorldStateManager::GetPersistantSetting("hellfire-stadium-status", "-1");
	const string toverlook = WorldStateManager::GetPersistantSetting("hellfire-overlook-status", "-1");
	const string tbrokenhill = WorldStateManager::GetPersistantSetting("hellfire-brokenhill-status", "-1");

	g_towerOwners[TOWER_STADIUM] = atoi(tstadium.c_str());
	g_towerOwners[TOWER_OVERLOOK] = atoi(toverlook.c_str());
	g_towerOwners[TOWER_BROKENHILL] = atoi(tbrokenhill.c_str());

	mgr->register_gameobject_script(182173, &HellfirePeninsulaBannerAI::Create);
	mgr->register_gameobject_script(182174, &HellfirePeninsulaBannerAI::Create);
	mgr->register_gameobject_script(182175, &HellfirePeninsulaBannerAI::Create);
}

