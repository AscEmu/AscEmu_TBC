/*
 * ArcScript Scripts for Arcemu MMORPG Server
 * Copyright (C) 2008 Arcemu Team
 * Copyright (C) 2007 Moon++ <http://www.moonplusplus.com/>
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

#include "StdAfx.h"
#include "Setup.h"
#include "Base.h"

/************************************************************************/
/* Instance_BloodFurnace.cpp Script		                                */
/************************************************************************/

/*****************************/
/*                           */
/*         Boss AIs          */
/*                           */
/*****************************/

// Keli'dan the BreakerAI

#define CN_KELIDAN_THE_BREAKER 17377

#define SHADOW_BOLT_VOLLEY 30510 // DBC: 17228; 38840/29924/40070/30510/30354 //CONE_SHADOW_BOLTS 
#define BLAST_WAVE 30600 // DBC: 33775; 39038 or 30600
#define CORRUPTION 30938

class KELIDANTHEBREAKERAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(KELIDANTHEBREAKERAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    KELIDANTHEBREAKERAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

        spells[0].info = dbcSpell.LookupEntry(SHADOW_BOLT_VOLLEY);
		spells[0].targettype = TARGET_VARIOUS;
		spells[0].instant = false;
		spells[0].cooldown = 10;
		spells[0].perctrigger = 15.0f;
		spells[0].attackstoptimer = 1000;

        spells[1].info = dbcSpell.LookupEntry(CORRUPTION);
		spells[1].targettype = TARGET_RANDOM_SINGLE;
		spells[1].instant = true;
		spells[1].cooldown = 30;
		spells[1].perctrigger = 10.0f;
		spells[1].attackstoptimer = 1000;
		spells[1].mindist2cast = 0.0f;
		spells[1].maxdist2cast = 40.0f;

		spells[2].info = dbcSpell.LookupEntry(BLAST_WAVE);
		spells[2].targettype = TARGET_VARIOUS;
		spells[2].instant = false;
		spells[2].cooldown = 30;
		spells[2].perctrigger = 0.0f;
		spells[2].attackstoptimer = 1000;
		spells[2].speech = "Closer... Come closer... And burn!";
		spells[2].soundid = 10165;

		BlastWave = false;
    }
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		spells[2].casttime = (uint32)time(NULL) + 30;
		int RandomSpeach = rand()%3;
		switch (RandomSpeach)
		{
		case 0:
			_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "You mustn't let him loose!");
			_unit->PlaySoundToSet(10166);
			break;
		case 1:
			_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Ignorant whelps!");
			_unit->PlaySoundToSet(10167);
			break;
		case 2:
			_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "You fools, he'll kill us all!");
			_unit->PlaySoundToSet(10168);
			break;
		}

		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));

		BlastWave = false;
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = 0;
	}

	void OnTargetDied(Unit* mTarget)
    {
		if (_unit->GetHealthPct() > 0)	// Hack to prevent double yelling (OnDied and OnTargetDied when creature is dying)
		{
			int RandomSpeach = rand()%2;
			switch (RandomSpeach)
			{
			case 0:
				_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Just as you deserve.");
				_unit->PlaySoundToSet(10169);
				break;
			case 1:
				_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Your friends, will soon be joining you.");
				_unit->PlaySoundToSet(10170);
				break;
			}
		}
    }

    void OnCombatStop(Unit *mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Good luck... You'll need it.");
		_unit->PlaySoundToSet(10171);
		RemoveAIUpdateEvent();

		GameObject *pDoor = NULL;
		pDoor = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(263.873871f, -128.438812f, -25.098160f, 181823);
		if(pDoor)
			pDoor->SetUInt32Value(GAMEOBJECT_STATE, 0);

		GameObject *pDoor2 = NULL;
		pDoor2 = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(-2.067811f, -111.613785f, -41.340549f, 181766);
		if(pDoor2)
			pDoor2->SetUInt32Value(GAMEOBJECT_STATE, 0);
    }

    void AIUpdate()
	{
		uint32 t = (uint32)time(NULL);
		if (BlastWave && _unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
		{
			_unit->GetAIInterface()->StopMovement(1);
			_unit->setAttackTimer(3000, false);

			Unit *target = NULL;
			target = _unit->GetAIInterface()->GetNextTarget();
			if (_unit->GetDistance2dSq(target) <= 100.0f)
			{
				_unit->CastSpell(_unit, spells[2].info, spells[2].instant);
			}

			else
			{
				_unit->CastSpell(_unit, spells[0].info, spells[0].instant);
			}

			spells[2].casttime = t + spells[2].cooldown;
			BlastWave = false;
			return;
		}

		if (t > spells[2].casttime && _unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget() && !BlastWave)
		{
			_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Closer... Come closer... And burn!");
			_unit->PlaySoundToSet(10165);

			_unit->GetAIInterface()->StopMovement(2000);
			_unit->setAttackTimer(2000, false);

			BlastWave = true;
			return;
		}

		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
    {
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i=0;i<nrspells;i++)
			{
				if(!spells[i].perctrigger) continue;
				
				if(m_spellcheck[i])
				{
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
						case TARGET_RANDOM_FRIEND:
						case TARGET_RANDOM_SINGLE:
						case TARGET_RANDOM_DESTINATION:
							CastSpellOnRandomTarget(i, spells[i].mindist2cast, spells[i].maxdist2cast, spells[i].minhp2cast, spells[i].maxhp2cast); break;
					}

					m_spellcheck[i] = false;
					return;
				}

				uint32 t = (uint32)time(NULL);
				if(val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger) && t > spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					spells[i].casttime = t + spells[i].cooldown;
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
        }
    }

	void CastSpellOnRandomTarget(uint32 i, float mindist2cast, float maxdist2cast, int minhp2cast, int maxhp2cast)
	{
		if (!maxdist2cast) maxdist2cast = 100.0f;
		if (!maxhp2cast) maxhp2cast = 100;

		if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			std::vector<Unit*> TargetTable;		/* From M4ksiu - Big THX to Capt who helped me with std stuff to make it simple and fully working <3 */
												/* If anyone wants to use this function, then leave this note!										 */
            for (std::set<Object*>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr)
			{ 
				if (((spells[i].targettype == TARGET_RANDOM_FRIEND && isFriendly(_unit, (*itr))) || (spells[i].targettype != TARGET_RANDOM_FRIEND && isHostile(_unit, (*itr)) && (*itr) != _unit)) && ((*itr)->GetTypeId()== TYPEID_UNIT || (*itr)->GetTypeId() == TYPEID_PLAYER) && (*itr)->GetInstanceID() == _unit->GetInstanceID()) // isAttackable(_unit, (*itr)) && 
				{
					Unit* RandomTarget = NULL;
					RandomTarget = (Unit*)(*itr);

					if (RandomTarget->isAlive() && _unit->GetDistance2dSq(RandomTarget) >= mindist2cast*mindist2cast && _unit->GetDistance2dSq(RandomTarget) <= maxdist2cast*maxdist2cast && ((RandomTarget->GetHealthPct() >= minhp2cast && RandomTarget->GetHealthPct() <= maxhp2cast && spells[i].targettype == TARGET_RANDOM_FRIEND) || (_unit->GetAIInterface()->getThreatByPtr(RandomTarget) > 0 && isHostile(_unit, RandomTarget))))
					{
						TargetTable.push_back(RandomTarget);
					} 
				} 
			}

			if (_unit->GetHealthPct() >= minhp2cast && _unit->GetHealthPct() <= maxhp2cast && spells[i].targettype == TARGET_RANDOM_FRIEND)
				TargetTable.push_back(_unit);

			if (!TargetTable.size())
				return;

			size_t RandTarget = rand()%TargetTable.size();

			Unit * RTarget = TargetTable[RandTarget];

			if (!RTarget)
				return;

			switch (spells[i].targettype)
			{
			case TARGET_RANDOM_FRIEND:
			case TARGET_RANDOM_SINGLE:
				_unit->CastSpell(RTarget, spells[i].info, spells[i].instant); break;
			case TARGET_RANDOM_DESTINATION:
				_unit->CastSpellAoF(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), spells[i].info, spells[i].instant); break;
			}

			TargetTable.clear();
		}
	}

protected:

	bool BlastWave;
	int nrspells;
};

//------------------------------------
//	-= Broggok =-
//------------------------------------
#define CN_BROGGOK 17380

#define POISON_BOLT 30917
#define POISON_CLOUD 31259 // DBC: 30916; no idea if correct
#define SLIME_SPRAY 30913

class BroggokAI : public ArcScriptCreatureAI
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(BroggokAI);
	BroggokAI(Creature* pCreature) : ArcScriptCreatureAI(pCreature)
	{
		AddSpell(POISON_BOLT, Target_Self, 12.0f, 0, 15);
		AddSpell(POISON_CLOUD, Target_RandomDestination, 8.0f, 0, 40, 0, 40);
		AddSpell(SLIME_SPRAY, Target_Self, 10.0f, 0, 25);
	}

	void OnDied(Unit *pKiller)
	{
		GameObject *pDoor = NULL;
		pDoor = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(456.157349f, 34.248005f, 9.559463f, 181819);
		if(pDoor)
			pDoor->SetUInt32Value(GAMEOBJECT_STATE, 0);

		ArcScriptCreatureAI::OnDied(pKiller);
	}
};

//------------------------------------
//	-= The Maker =-
//------------------------------------
#define CN_THE_MAKER 17381

#define DOMINATION 30923 // 36866
#define ACID_SPRAY 38973 // 38973 or 38153	// not sure about casting of this
#define THROW_BEAKER 30925 // Throw beaker <--- maybe this is it?

class TheMakerAI : public ArcScriptCreatureAI
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(TheMakerAI);
	TheMakerAI(Creature* pCreature) : ArcScriptCreatureAI(pCreature)
	{
		AddEmote(Event_OnCombatStart, "My work must not be interrupted.", Text_Yell, 10286);
		AddEmote(Event_OnCombatStart, "Perhaps I can find a use for you.", Text_Yell, 10287);
		AddEmote(Event_OnCombatStart, "Anger... Hate... These are tools I can use.", Text_Yell, 10288);
		AddEmote(Event_OnTargetDied, "Let's see what I can make of you.", Text_Yell, 10289);
		AddEmote(Event_OnTargetDied, "It is pointless to resist.", Text_Yell, 10290);
		AddEmote(Event_OnDied, "Stay away from... me.", Text_Yell, 10291);

		AddSpell(DOMINATION, Target_RandomPlayer, 8.0f, 0, 30);
		AddSpell(ACID_SPRAY, Target_Self, 10.0f, 0, 20);
		AddSpell(THROW_BEAKER, Target_RandomDestination, 20.0f, 0, 0, 0, 40);
	}

	void OnDied(Unit *pKiller)
	{
		GameObject *pDoor = NULL;
		pDoor = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(327.155487f, 149.753418f, 9.559869f, 181812);
		if(pDoor)
			pDoor->SetUInt32Value(GAMEOBJECT_STATE, 0);

		ArcScriptCreatureAI::OnDied(pKiller);
	}
};

void SetupBloodFurnace(ScriptMgr * mgr)
{
	mgr->register_creature_script(CN_KELIDAN_THE_BREAKER, &KELIDANTHEBREAKERAI::Create);
	mgr->register_creature_script(CN_BROGGOK, &BroggokAI::Create);
	mgr->register_creature_script(CN_THE_MAKER, &TheMakerAI::Create);
}

// No info about spells: Orc Captive (17416), Emeriss (14889)
// No idea if I should script NPC Bill (19621) as he has 2 spell with visual effects only
