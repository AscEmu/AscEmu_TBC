/*
 * AscEmu Framework based on AscEmu MMORPG Server
 * Copyright (C) 2014-2015 AscEmu Team <http://www.ascemu.org>
 * Copyright (C) 2008 <http://www.AscEmu.org/>
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

#ifndef _SKILLNAMEMGR_H
#define _SKILLNAMEMGR_H

#include "StdAfx.h"

class SkillNameMgr
{
    public:
    char** SkillNames;
    uint32 maxskill;

    SkillNameMgr()
    {
        DBCStorage<skilllineentry>::iterator itr = dbcSkillLine.end();
        --itr;
        skilllineentry* skillline = *itr;

        /// This will become the size of the skill name lookup table
        maxskill = skillline->id;

        /// SkillNames = (char **) malloc(maxskill * sizeof(char *));
        SkillNames = new char *[maxskill + 1]; //(+1, arrays count from 0.. not 1.)
        memset(SkillNames, 0, (maxskill + 1) * sizeof(char*));

        for (itr = dbcSkillLine.begin(); itr != dbcSkillLine.end(); ++itr)
        {
            skillline = *itr;

            unsigned int SkillID = skillline->id;
            const char* SkillName = skillline->Name;

            SkillNames[SkillID] = new char[strlen(SkillName) + 1];
            //When the DBCFile gets cleaned up, so does the record data, so make a copy of it..
            memcpy(SkillNames[SkillID], SkillName, strlen(SkillName) + 1);
        }
    }
    ~SkillNameMgr()
    {
        for (uint32 i = 0; i <= maxskill; i++)
        {
            if (SkillNames[i] != 0)
                delete[] SkillNames[i];
        }
        delete[] SkillNames;
    }
};

#endif // _SKILLNAMEMGR_H
