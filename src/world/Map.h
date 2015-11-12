/*
 * AscEmu Framework based on ArcEmu MMORPG Server
 * Copyright (C) 2014-2015 AscEmu Team <http://www.ascemu.org/>
 * Copyright (C) 2008 <http://www.ArcEmu.org/>
 * Copyright (C) 2005-2007 Ascent Team
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __MAP_H
#define __MAP_H

class MapMgr;
class TemplateMgr;
struct MapInfo;
class TerrainMgr;

#include "TerrainMgr.h"

struct Formation;

typedef struct
{
    uint32	id;//spawn ID
    uint32	entry;
    float	x;
    float	y;
    float	z;
    float	o;
    Formation* form;
    uint8 movetype;
    uint32 displayid;
    uint32 factionid;
    uint32 flags;
    uint32 bytes0;
    uint32 bytes1;
    uint32 bytes2;
    uint32 emote_state;
    //uint32 respawnNpcLink;
    uint16 channel_spell;
    uint32 channel_target_go;
    uint32 channel_target_creature;
    uint16 stand_state;
}CreatureSpawn;

typedef struct
{
    uint32	id;//spawn ID
    uint32	entry;
    float	x;
    float	y;
    float	z;
    float	o;
    float	o1;
    float	o2;
    float	o3;
    float	facing;
    uint32	flags;
    uint32	state;
    uint32	faction;
    //	uint32	level;
    float scale;
    //uint32 stateNpcLink;
} GOSpawn;

typedef std::vector<CreatureSpawn*> CreatureSpawnList;
typedef std::vector<GOSpawn*> GOSpawnList;

typedef struct
{
    CreatureSpawnList CreatureSpawns;
    GOSpawnList GOSpawns;
}CellSpawns;

class SERVER_DECL Map
{
    public:
    Map(uint32 mapid, MapInfo * inf);
    ~Map();

    inline std::string GetNameString() { return name; }
    inline const char* GetName() { return name.c_str(); }
    inline MapEntry* GetDBCEntry() { return me; }

    inline CellSpawns *GetSpawnsList(uint32 cellx, uint32 celly)
    {
        ASSERT(cellx < _sizeX);
        ASSERT(celly < _sizeY);
        if (spawns[cellx] == NULL) return NULL;

        return spawns[cellx][celly];
    }
    inline CellSpawns * GetSpawnsListAndCreate(uint32 cellx, uint32 celly)
    {
        ASSERT(cellx < _sizeX);
        ASSERT(celly < _sizeY);
        if (spawns[cellx] == NULL)
        {
            spawns[cellx] = new CellSpawns*[_sizeY];
            memset(spawns[cellx], 0, sizeof(CellSpawns*)*_sizeY);
        }

        if (spawns[cellx][celly] == 0)
            spawns[cellx][celly] = new CellSpawns;
        return spawns[cellx][celly];
    }

    void LoadSpawns(bool reload);//set to true to make clean up
    uint32 CreatureSpawnCount;
    uint32 GameObjectSpawnCount;


    inline void CellGoneActive(uint32 x, uint32 y)
    {}

    inline void CellGoneIdle(uint32 x, uint32 y)
    {}

    private:
    MapInfo *	   _mapInfo;
    uint32 _mapId;
    std::string name;
    MapEntry * me;

    //new stuff
    CellSpawns **spawns[_sizeX];
    public:
    CellSpawns staticSpawns;
};

#endif
