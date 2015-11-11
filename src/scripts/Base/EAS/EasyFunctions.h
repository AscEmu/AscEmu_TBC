/*
 * Moon++ Scripts for Ascent MMORPG Server
 * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (C) 2007-2008 Moon++ Team <http://www.moonplusplus.info/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.	If not, see <http://www.gnu.org/licenses/>.
 *
 * EasyFunctions for ASCENT v0.4
 *
 */

#ifndef EASYFUNC_H
#define EASYFUNC_H

#include "StdAfx.h"

// Uncomment if you want debug texts
// #define ENABLE_DEBUG_TEXT

#pragma warning(disable:4305) // warning C4305: 'argument' : truncation from 'double' to 'float'
#pragma warning(disable:4267) // warning C4267: '=' : conversion from 'size_t' to 'uint32', possible loss of data

#define arr_length(a) sizeof(a)/sizeof(*a)

#define CREATE_QUESTSCRIPT(cl) (QuestScript*)new cl
#define CREATE_GOSSIPSCRIPT(cl) (GossipScript*)new cl
#define CREATE_GAMEOBJECT_SCRIPT(cl) &cl::Create
#define CREATE_CREATURESCRIPT(cl) &cl::Create

namespace EASY_FUNCTIONS
{
    struct EASWaypoint
    {
        float x;
        float y;
        float z;
        float o; 
        uint32 waitTime;
        uint32 flags;
        uint32 modelId;
    };

	void PrintMessage(const char *text, ...);

	void WaypointCreate(Creature *pCreature, float x, float y, float z, float o, uint32 waittime, uint32 flags, uint32 modelId);
    void WaypointCreate(Creature *pCreature, EASWaypoint * pWpData);
    void MoveToPlayer(Player *plr, Creature *creat);
	void CreateCustomWaypointMap(Creature *creat);
	void DeleteWaypoints(Creature *creat);
	void DeleteSpawned(Creature *creat);
	void GameobjectDelete(GameObject *pC, uint32 duration);

	Creature* SpawnCreature(Player *pThis, uint32 entry, float posX, float posY, float posZ, float posO, uint32 duration = 0);
	GameObject *SpawnGameobject(Player *plr, uint32 entry_id, float x, float y, float z, float o, float scale);

	bool AddItem(uint32 entry, Player *plr, uint32 count = 1);
  
	AscEmu_INLINE void EventCastSpell(Unit* caster, Unit* target, uint32 spellid, uint32 time)
	{
		sEventMgr.AddEvent(((Unit*)caster), &Unit::EventCastSpell, ((Unit*)target), dbcSpell.LookupEntry(spellid), EVENT_UNK, time, 0, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	}
}

namespace EAS = EASY_FUNCTIONS;

#endif