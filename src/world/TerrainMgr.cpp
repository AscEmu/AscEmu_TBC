/*
 * AscEmu Framework based on ArcEmu MMORPG Server
 * Copyright (C) 2014-2015 AscEmu Team <http://www.ascemu.org/>
 * Copyright (C) 2008-2010 <http://www.ArcEmu.org/>
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

#include "StdAfx.h"
#include "TerrainMgr.h"

TerrainHolder::TerrainHolder(uint32 mapid)
{
    for (int32 i = 0; i < TERRAIN_NUM_TILES; ++i)
        for (int32 j = 0; j < TERRAIN_NUM_TILES; ++j)
            m_tiles[i][j] = NULL;
    m_mapid = mapid;
}

TerrainHolder::~TerrainHolder()
{
    for (int32 i = 0; i < TERRAIN_NUM_TILES; ++i)
        for (int32 j = 0; j < TERRAIN_NUM_TILES; ++j)
            UnloadTile(i, j);
}

uint16 TerrainHolder::GetAreaFlagWithoutAdtId(float x, float y)
{
    auto tile = this->GetTile(x, y);
    if (tile)
    {
        return tile->m_map.GetArea(x, y);
    }

    return 0;
}

TerrainTile* TerrainHolder::GetTile(float x, float y)
{
    int32 tx = (int32)(32 - (x / TERRAIN_TILE_SIZE));
    int32 ty = (int32)(32 - (y / TERRAIN_TILE_SIZE));

    return GetTile(tx, ty);
}

TerrainTile* TerrainHolder::GetTile(int32 tx, int32 ty)
{
    TerrainTile* rv = NULL;
    m_lock[tx][ty].Acquire();
    rv = m_tiles[tx][ty];
    if (rv != NULL)
        rv->AddRef();
    m_lock[tx][ty].Release();

    return rv;
}

void TerrainHolder::LoadTile(float x, float y)
{
    int32 tx = (int32)(32 - (x / TERRAIN_TILE_SIZE));
    int32 ty = (int32)(32 - (y / TERRAIN_TILE_SIZE));
    LoadTile(tx, ty);
}

void TerrainHolder::LoadTile(int32 tx, int32 ty)
{
    m_lock[tx][ty].Acquire();
    ++m_tilerefs[tx][ty];
    if (m_tiles[tx][ty] == NULL)
    {
        m_tiles[tx][ty] = new TerrainTile(this, m_mapid, tx, ty);
        m_tiles[tx][ty]->Load();
    }
    m_lock[tx][ty].Release();
}

void TerrainHolder::UnloadTile(float x, float y)
{
    int32 tx = (int32)(32 - (x / TERRAIN_TILE_SIZE));
    int32 ty = (int32)(32 - (y / TERRAIN_TILE_SIZE));
    UnloadTile(tx, ty);
}

void TerrainHolder::UnloadTile(int32 tx, int32 ty)
{
    m_lock[tx][ty].Acquire();
    if (m_tiles[tx][ty] == NULL)
    {
        m_lock[tx][ty].Release();
        return;
    }
    m_lock[tx][ty].Release();

    if (--m_tilerefs[tx][ty] == 0)
    {
        m_lock[tx][ty].Acquire();
        if (m_tiles[tx][ty] != NULL)
            m_tiles[tx][ty]->DecRef();
        m_tiles[tx][ty] = NULL;
        m_lock[tx][ty].Release();
    }
}

float TerrainHolder::GetADTLandHeight(float x, float y)
{
    TerrainTile* tile = GetTile(x, y);

    if (tile == NULL)
        return TERRAIN_INVALID_HEIGHT;
    float rv = tile->m_map.GetHeight(x, y);
    tile->DecRef();
    return rv;
}

float TerrainHolder::GetLandHeight(float x, float y, float z)
{
    float adtheight = GetADTLandHeight(x, y);

    VMAP::IVMapManager* vmgr = VMAP::VMapFactory::createOrGetVMapManager();
    float vmapheight = vmgr->getHeight(m_mapid, x, y, z + 0.5f, 10000.0f);

    if (adtheight > z)
        return vmapheight; //underground
    return std::max(vmapheight, adtheight);
}

float TerrainHolder::GetLiquidHeight(float x, float y)
{
    TerrainTile* tile = GetTile(x, y);

    if (tile == NULL)
        return TERRAIN_INVALID_HEIGHT;
    float rv = tile->m_map.GetLiquidHeight(x, y);
    tile->DecRef();
    return rv;
}

uint8 TerrainHolder::GetLiquidType(float x, float y)
{
    TerrainTile* tile = GetTile(x, y);

    if (tile == NULL)
        return 0;
    uint8 rv = tile->m_map.GetLiquidType(x, y);
    tile->DecRef();
    return rv;
}

uint32 TerrainHolder::GetAreaFlag(float x, float y)
{
    TerrainTile* tile = GetTile(x, y);

    if (tile == NULL)
    {
        // No generated map for this area (usually instances)
        return 0;
    }
    uint32 rv = tile->m_map.GetArea(x, y);
    tile->DecRef();
    return rv;
}

bool TerrainHolder::GetLiquidInfo(float x, float y, float z, float & liquidlevel, uint32 & liquidtype)
{
    VMAP::IVMapManager* vmgr = VMAP::VMapFactory::createOrGetVMapManager();

    float flr;
    if (vmgr->GetLiquidLevel(m_mapid, x, y, z, 0xFF, liquidlevel, flr, liquidtype))
        return true;

    liquidlevel = GetLiquidHeight(x, y);
    liquidtype = GetLiquidType(x, y);

    if (liquidtype == 0)
        return false;
    return true;
}

bool TerrainHolder::InLineOfSight(float x, float y, float z, float x2, float y2, float z2)
{
    VMAP::IVMapManager* vmgr = VMAP::VMapFactory::createOrGetVMapManager();

    return vmgr->isInLineOfSight(m_mapid, x, y, z, x2, y2, z2);
}

TerrainTile::~TerrainTile()
{
    m_parent->m_tiles[m_tx][m_ty] = NULL;
}

TerrainTile::TerrainTile(TerrainHolder* parent, uint32 mapid, int32 x, int32 y)
{
    m_parent = parent;
    m_mapid = mapid;
    m_tx = x;
    m_ty = y;
    ++m_refs;
}

float TileMap::GetHeightB(float x, float y, int x_int, int y_int)
{
    int32 a, b, c;
    uint8 *V9_h1_ptr = &m_heightMap9B[x_int * 128 + x_int + y_int];
    if (x + y < 1)
    {
        if (x > y)
        {
            // 1 triangle (h1, h2, h5 points)
            int32 h1 = V9_h1_ptr[0];
            int32 h2 = V9_h1_ptr[129];
            int32 h5 = 2 * m_heightMap8B[x_int * 128 + y_int];
            a = h2 - h1;
            b = h5 - h1 - h2;
            c = h1;
        }
        else
        {
            // 2 triangle (h1, h3, h5 points)
            int32 h1 = V9_h1_ptr[0];
            int32 h3 = V9_h1_ptr[1];
            int32 h5 = 2 * m_heightMap8B[x_int * 128 + y_int];
            a = h5 - h1 - h3;
            b = h3 - h1;
            c = h1;
        }
    }
    else
    {
        if (x > y)
        {
            // 3 triangle (h2, h4, h5 points)
            int32 h2 = V9_h1_ptr[129];
            int32 h4 = V9_h1_ptr[130];
            int32 h5 = 2 * m_heightMap8B[x_int * 128 + y_int];
            a = h2 + h4 - h5;
            b = h4 - h2;
            c = h5 - h4;
        }
        else
        {
            // 4 triangle (h3, h4, h5 points)
            int32 h3 = V9_h1_ptr[1];
            int32 h4 = V9_h1_ptr[130];
            int32 h5 = 2 * m_heightMap8B[x_int * 128 + y_int];
            a = h4 - h3;
            b = h3 + h4 - h5;
            c = h5 - h4;
        }
    }

    // Calculate height
    return (float)((a * x) + (b * y) + c)*m_heightMapMult + m_tileHeight;
}

float TileMap::GetHeightS(float x, float y, int x_int, int y_int)
{
    int32 a, b, c;
    uint16 *V9_h1_ptr = &m_heightMap9S[x_int * 128 + x_int + y_int];
    if (x + y < 1)
    {
        if (x > y)
        {
            // 1 triangle (h1, h2, h5 points)
            int32 h1 = V9_h1_ptr[0];
            int32 h2 = V9_h1_ptr[129];
            int32 h5 = 2 * m_heightMap8S[x_int * 128 + y_int];
            a = h2 - h1;
            b = h5 - h1 - h2;
            c = h1;
        }
        else
        {
            // 2 triangle (h1, h3, h5 points)
            int32 h1 = V9_h1_ptr[0];
            int32 h3 = V9_h1_ptr[1];
            int32 h5 = 2 * m_heightMap8S[x_int * 128 + y_int];
            a = h5 - h1 - h3;
            b = h3 - h1;
            c = h1;
        }
    }
    else
    {
        if (x > y)
        {
            // 3 triangle (h2, h4, h5 points)
            int32 h2 = V9_h1_ptr[129];
            int32 h4 = V9_h1_ptr[130];
            int32 h5 = 2 * m_heightMap8S[x_int * 128 + y_int];
            a = h2 + h4 - h5;
            b = h4 - h2;
            c = h5 - h4;
        }
        else
        {
            // 4 triangle (h3, h4, h5 points)
            int32 h3 = V9_h1_ptr[1];
            int32 h4 = V9_h1_ptr[130];
            int32 h5 = 2 * m_heightMap8S[x_int * 128 + y_int];
            a = h4 - h3;
            b = h3 + h4 - h5;
            c = h5 - h4;
        }
    }

    // Calculate height
    return (float)((a * x) + (b * y) + c)*m_heightMapMult + m_tileHeight;
}

float TileMap::GetHeightF(float x, float y, int x_int, int y_int)
{
    float a, b, c;
    // Select triangle:
    if (x + y < 1)
    {
        if (x > y)
        {
            // 1 triangle (h1, h2, h5 points)
            float h1 = m_heightMap9F[(x_int)* 129 + y_int];
            float h2 = m_heightMap9F[(x_int + 1) * 129 + y_int];
            float h5 = 2 * m_heightMap8F[x_int * 128 + y_int];
            a = h2 - h1;
            b = h5 - h1 - h2;
            c = h1;
        }
        else
        {
            // 2 triangle (h1, h3, h5 points)
            float h1 = m_heightMap9F[x_int * 129 + y_int];
            float h3 = m_heightMap9F[x_int * 129 + y_int + 1];
            float h5 = 2 * m_heightMap8F[x_int * 128 + y_int];
            a = h5 - h1 - h3;
            b = h3 - h1;
            c = h1;
        }
    }
    else
    {
        if (x > y)
        {
            // 3 triangle (h2, h4, h5 points)
            float h2 = m_heightMap9F[(x_int + 1) * 129 + y_int];
            float h4 = m_heightMap9F[(x_int + 1) * 129 + y_int + 1];
            float h5 = 2 * m_heightMap8F[x_int * 128 + y_int];
            a = h2 + h4 - h5;
            b = h4 - h2;
            c = h5 - h4;
        }
        else
        {
            // 4 triangle (h3, h4, h5 points)
            float h3 = m_heightMap9F[(x_int)* 129 + y_int + 1];
            float h4 = m_heightMap9F[(x_int + 1) * 129 + y_int + 1];
            float h5 = 2 * m_heightMap8F[x_int * 128 + y_int];
            a = h4 - h3;
            b = h3 + h4 - h5;
            c = h5 - h4;
        }
    }
    // Calculate height
    return a * x + b * y + c;
}

float TileMap::GetHeight(float x, float y)
{
    if (m_heightMap9F == NULL)
        return m_tileHeight;

    x = TERRAIN_MAP_RESOLUTION * (32 - x / TERRAIN_TILE_SIZE);
    y = TERRAIN_MAP_RESOLUTION * (32 - y / TERRAIN_TILE_SIZE);

    int x_int = (int)x;
    int y_int = (int)y;
    x -= x_int;
    y -= y_int;
    x_int &= (TERRAIN_MAP_RESOLUTION - 1);
    y_int &= (TERRAIN_MAP_RESOLUTION - 1);

    if (m_heightMapFlags & MAP_HEIGHT_AS_INT16)
        return GetHeightS(x, y, x_int, y_int);
    else if (m_heightMapFlags & MAP_HEIGHT_AS_INT8)
        return GetHeightB(x, y, x_int, y_int);
    return GetHeightF(x, y, x_int, y_int);
}

const bool TerrainHolder::GetAreaInfo(float x, float y, float z, uint32 &mogp_flags, int32 &adt_id, int32 &root_id, int32 &group_id)
{
    float vmap_z = z;
    auto vmap_manager = VMAP::VMapFactory::createOrGetVMapManager();
    if (vmap_manager->getAreaInfo(m_mapid, x, y, vmap_z, mogp_flags, adt_id, root_id, group_id))
    {
        if (auto tile = this->GetTile(x, y))
        {
            float map_height = tile->m_map.GetHeight(x, y);
            if (z + 2.0f > map_height && map_height > vmap_z)
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

void TileMap::Load(char* filename)
{
    Log.Debug("Terrain", "Loading %s", filename);
    FILE* f = fopen(filename, "rb");

    if (f == NULL)
    {
        Log.Error("Terrain", "%s does not exist", filename);
        return;
    }

    TileMapHeader header;

    fread(&header, 1, sizeof(header), f);

    if (header.buildMagic != 8606) //wow version
    {
        Log.Error("Terrain", "%s: from incorrect client (you: %u us: %u)", filename, header.buildMagic, 8606);
        fclose(f);
        return;
    }


    if (header.areaMapOffset != 0)
        LoadAreaData(f, header);

    if (header.heightMapOffset != 0)
        LoadHeightData(f, header);

    if (header.liquidMapOffset != 0)
        LoadLiquidData(f, header);

    fclose(f);
}

void TileMap::LoadLiquidData(FILE* f, TileMapHeader &header)
{
    TileMapLiquidHeader liquidHeader;
    fseek(f, header.liquidMapOffset, SEEK_SET);
    fread(&liquidHeader, 1, sizeof(liquidHeader), f);

    m_defaultLiquidType = liquidHeader.liquidType;
    m_liquidLevel = liquidHeader.liquidLevel;
    m_liquidOffX = liquidHeader.offsetX;
    m_liquidOffY = liquidHeader.offsetY;
    m_liquidWidth = liquidHeader.width;
    m_liquidHeight = liquidHeader.height;

    if (!(liquidHeader.flags & MAP_LIQUID_NO_TYPE))
    {
        m_liquidType = new uint8[16 * 16];
        fread(m_liquidType, sizeof(uint8), 16 * 16, f);
    }

    if (!(liquidHeader.flags & MAP_LIQUID_NO_HEIGHT))
    {
        m_liquidMap = new float[m_liquidWidth * m_liquidHeight];
        fread(m_liquidMap, sizeof(float), m_liquidWidth * m_liquidHeight, f);
    }
}

void TileMap::LoadHeightData(FILE* f, TileMapHeader &header)
{
    TileMapHeightHeader mapHeader;
    fseek(f, header.heightMapOffset, SEEK_SET);
    fread(&mapHeader, 1, sizeof(mapHeader), f);

    m_tileHeight = mapHeader.gridHeight;
    m_heightMapFlags = mapHeader.flags;

    if (m_heightMapFlags & MAP_HEIGHT_AS_INT16)
    {
        m_heightMapMult = (mapHeader.gridMaxHeight - mapHeader.gridHeight) / 65535;

        m_heightMap9S = new uint16[129 * 129];
        m_heightMap8S = new uint16[128 * 128];
        fread(m_heightMap9S, sizeof(uint16), 129 * 129, f);
        fread(m_heightMap8S, sizeof(uint16), 128 * 128, f);
    }
    else if (m_heightMapFlags & MAP_HEIGHT_AS_INT8)
    {
        m_heightMapMult = (mapHeader.gridMaxHeight - mapHeader.gridHeight) / 255;

        m_heightMap9B = new uint8[129 * 129];
        m_heightMap8B = new uint8[128 * 128];
        fread(m_heightMap9B, sizeof(uint8), 129 * 129, f);
        fread(m_heightMap8B, sizeof(uint8), 128 * 128, f);
    }
    else
    {
        m_heightMap9F = new float[129 * 129];
        m_heightMap8F = new float[128 * 128];
        fread(m_heightMap9F, sizeof(float), 129 * 129, f);
        fread(m_heightMap8F, sizeof(float), 128 * 128, f);
    }
}

void TileMap::LoadAreaData(FILE* f, TileMapHeader &header)
{
    TileMapAreaHeader areaHeader;

    fseek(f, header.areaMapOffset, SEEK_SET);
    fread(&areaHeader, 1, sizeof(areaHeader), f);

    m_area = areaHeader.gridArea;
    if (!(areaHeader.flags & MAP_AREA_NO_AREA))
    {
        m_areaMap = new uint16[16 * 16];
        fread(m_areaMap, sizeof(uint16), 16 * 16, f);
    }
}

float TileMap::GetLiquidHeight(float x, float y)
{
    if (m_liquidMap == NULL)
        return m_liquidLevel;

    x = TERRAIN_MAP_RESOLUTION * (32 - x / TERRAIN_TILE_SIZE);
    y = TERRAIN_MAP_RESOLUTION * (32 - y / TERRAIN_TILE_SIZE);

    int cx_int = ((int)x & (TERRAIN_MAP_RESOLUTION - 1)) - m_liquidOffX;
    int cy_int = ((int)y & (TERRAIN_MAP_RESOLUTION - 1)) - m_liquidOffY;

    if (cx_int < 0 || cx_int >= m_liquidHeight)
        return TERRAIN_INVALID_HEIGHT;

    if (cy_int < 0 || cy_int >= m_liquidWidth)
        return TERRAIN_INVALID_HEIGHT;

    return m_liquidMap[cx_int*m_liquidWidth + cy_int];
}

uint8 TileMap::GetLiquidType(float x, float y)
{
    if (m_liquidType == NULL)
        return (uint8)m_defaultLiquidType;

    x = 16 * (32 - x / TERRAIN_TILE_SIZE);
    y = 16 * (32 - y / TERRAIN_TILE_SIZE);
    int lx = (int)x & 15;
    int ly = (int)y & 15;
    return m_liquidType[lx * 16 + ly];
}

uint32 TileMap::GetArea(float x, float y)
{
    if (m_areaMap == NULL)
        return m_area;

    x = 16 * (32 - x / TERRAIN_TILE_SIZE);
    y = 16 * (32 - y / TERRAIN_TILE_SIZE);
    int lx = (int)x & 15;
    int ly = (int)y & 15;
    return m_areaMap[lx * 16 + ly];
}
