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
/* Instance_HellfireRamparts.cpp Script		                            */
/************************************************************************/

// Watchkeeper GargolmarAI

enum WatchkeeperGargolmarData
{
    CN_WATCHKEEPER_GARGOLMAR = 17306,
    CN_HELLFIRE_WATCHER = 17309,
    SPELL_SURGE = 34645,
    SPELL_MORTAL_WOUND = 30641,
    SPELL_RETATLIATION = 22857
};

class WatchkeeperGargolmarAI : public ArcScriptBossAI
{
    ARCSCRIPT_FACTORY_FUNCTION(WatchkeeperGargolmarAI, ArcScriptBossAI);
    WatchkeeperGargolmarAI(Creature* pCreature) : ArcScriptBossAI(pCreature)
    {
        AddEmote(Event_OnCombatStart, "This may hurt a little...", Text_Yell, 10332);
        AddEmote(Event_OnCombatStart, "What have we here?", Text_Yell, 10331);
        AddEmote(Event_OnCombatStart, "I'm going to enjoy this...", Text_Yell, 10333);
        AddEmote(Event_OnTargetDied, "Say farewell!", Text_Yell, 10334);
        AddEmote(Event_OnTargetDied, "Much too easy...", Text_Yell, 10335);

        AddSpell(SPELL_MORTAL_WOUND, Target_Current, 95, 0, RandomUInt(5, 13));
        AddSpell(SPELL_SURGE, Target_RandomPlayerNotCurrent, 95, 0, RandomUInt(5, 13), 0, 0, false, "Back off, pup!", Text_Yell, 10330);
        AddSpell(SPELL_RETATLIATION, Target_Self, 95, 0, 30);
    };

    void OnLoad()
    {
        RegisterAIUpdateEvent(1000);
    }

    void AIUpdate()
    {
        if (_unit->GetInRangePlayersCount() <= 1 && _introSpeech == false)
        {
            Emote("Do you smell that? Fresh meat has somehow breached our citadel. Be wary of any intruders.", Text_Yell, 0);
            _introSpeech = true;
            RemoveAIUpdateEvent();
        }
        if (_unit->GetHealthPct() <= 40 && GetPhase() == 1)
        {
            Emote("Heal me, quickly!", Text_Yell, 10329);
            HellfireWatcher->CastSpell(_unit, 12039, false);
            SetPhase(2);
        }
    }
protected:
    bool _introSpeech = false;
    Unit* HellfireWatcher = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), CN_HELLFIRE_WATCHER);
};

// Omor the UnscarredAI

enum OmorData
{
    CN_OMOR_THE_UNSCARRED = 17308,
    OMOR_DEMONIC_SHIELD = 31901,
    OMOR_SUMMON_FIENDISH_HOUND = 30707,
    OMOR_SHADOW_WHIP = 30638,
    OMOR_SHADOW_BOLT = 30686,
    OMOR_SHADOW_BOLT2 = 39297,
    OMOR_TREACHEROUS_AURA = 30695,
    OMOR_BANE_OF_TREACHERY = 37566
};
class OmorTheUnscarredAI : public ArcScriptCreatureAI
{
public:
    ARCSCRIPT_FACTORY_FUNCTION(OmorTheUnscarredAI, ArcScriptCreatureAI);
    OmorTheUnscarredAI(Creature* pCreature) : ArcScriptCreatureAI(pCreature)
    {
        SpellDesc* pShield = AddSpell(OMOR_DEMONIC_SHIELD, Target_Self, 30, 0, 25);
        pShield->mEnabled = false;
        SpellDesc* pSummon = AddSpell(OMOR_SUMMON_FIENDISH_HOUND, Target_Self, 8, 1, 20);
        pSummon->AddEmote("Achor-she-ki! Feast my pet! Eat your fill!", Text_Yell, 10277);
        AddSpell(OMOR_SHADOW_WHIP, Target_RandomPlayer, 10, 0, 30);
        if (_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
        {
            AddSpell(OMOR_SHADOW_BOLT, Target_RandomPlayer, 8, 3, 15, 10, 60, true);
            SpellDesc* pAura = AddSpell(OMOR_TREACHEROUS_AURA, Target_RandomPlayer, 8, 2, 35, 0, 60, true);
            pAura->AddEmote("A-Kreesh!", Text_Yell, 10278);
        }
        else
        {
            AddSpell(OMOR_SHADOW_BOLT2, Target_RandomPlayer, 8, 3, 15, 10, 60, true);
            SpellDesc* pAura = AddSpell(OMOR_BANE_OF_TREACHERY, Target_RandomPlayer, 8, 2, 35, 0, 60, true);
            pAura->AddEmote("A-Kreesh!", Text_Yell, 10278);
        }
    }

    void OnCombatStart(Unit* pTarget)
    {
        switch (RandomUInt(2))
        {
        case 0:
            _unit->SendScriptTextChatMessage(4856);     // I will not be defeated!
            break;
        case 1:
            _unit->SendScriptTextChatMessage(4855);     // You dare stand against ME?
            break;
        case 2:
            _unit->SendScriptTextChatMessage(4857);     // Your insolence will be your death!
            break;
        }
        ParentClass::OnCombatStart(pTarget);
        SetCanMove(false);
    }

    void OnTargetDied(Unit* pKiller)
    {
        _unit->SendScriptTextChatMessage(4860);     // Die, weakling!
    }

    void OnDied(Unit* pKiller)
    {
        _unit->SendScriptTextChatMessage(4861);     // It is... not over.
    }

    void OnCombatStop(Unit* pTarget)
    {
        ParentClass::OnCombatStop(pTarget);
        if (IsAlive())
        {
            _unit->SendScriptTextChatMessage(4862);     // I am victorious!
        }
    }

    void AIUpdate()
    {
        SpellDesc* pShield = FindSpellById(OMOR_DEMONIC_SHIELD);
        if (GetHealthPercent() <= 20 && pShield != NULL && !pShield->mEnabled)
        {
            pShield->mEnabled = true;
        }

        Unit* pTarget = _unit->GetAIInterface()->GetNextTarget();
        if (pTarget != NULL)
        {
            if (GetRangeToUnit(pTarget) > 10.0f)
            {
                pTarget = GetBestPlayerTarget(TargetFilter_Closest);
                if (pTarget != NULL)
                {
                    if (GetRangeToUnit(pTarget) > 10.0f)
                    {
                        pTarget = NULL;
                    }
                    else
                    {
                        ClearHateList();
                        _unit->GetAIInterface()->AttackReaction(pTarget, 500);
                        _unit->GetAIInterface()->SetNextTarget(pTarget);
                    }
                }
                else
                    return;
            }

            if (pTarget == NULL)
            {
                SpellDesc* pWhip = FindSpellById(OMOR_SHADOW_WHIP);    // used for now
                if (pWhip != NULL)
                {
                    pWhip->mLastCastTime = 0;
                    CastSpellNowNoScheduling(pWhip);
                    return;
                }
            }
        }

        SetCanMove(false);
    }
};

/*****************************/
/*                           */
/*    Vazruden the Herald	 */
/*			*Full Event*	 */
/*                           */
/*****************************/

// EVENT DEFINITIONS/VARIABLES
uint32 VAZRUDEN_THE_HERALD_EVENT_PHASE;
uint32 HERALDS_SENTRY_DEATHS;	

// Hellfire Sentry AI - mob

#define CN_HELLFIRE_SENTRY 17517

#define KIDNEY_SHOT_SENTRY 30621
// Not sure!
class HELLFIRESENTRYAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(HELLFIRESENTRYAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    HELLFIRESENTRYAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}
		
        spells[0].info = dbcSpell.LookupEntry(KIDNEY_SHOT_SENTRY);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = 25;
		spells[0].perctrigger = 0.0f;
		spells[0].attackstoptimer = 1000;
    }
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
		RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
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
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:

	int nrspells;
};

// VazrudenAI

#define CN_VAZRUDEN 17537

#define REVENGE 40392 // DBC: 19130; 37517, 40392, 19130 or other

class VAZRUDENAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(VAZRUDENAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    VAZRUDENAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		PHASE_LIMITER = 2;
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

        spells[0].info = dbcSpell.LookupEntry(REVENGE);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = 10;
		spells[0].perctrigger = 0.0f;
		spells[0].attackstoptimer = 1000;

    }
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
		PHASE_LIMITER = 2;
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
		PHASE_LIMITER = 2;
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
		RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		if (_unit->GetHealthPct() <= 20 && PHASE_LIMITER == 2)
		{
			VAZRUDEN_THE_HERALD_EVENT_PHASE = 3;
			PHASE_LIMITER = 3;
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
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:

	uint32 PHASE_LIMITER;
	int nrspells;
};

// NazanAI
								// DOESN'T WORK YET!
#define WALK 0
#define RUN 256
#define FLY 768

//#define CN_NAZAN 17536
#define CN_NAZAN 17307 // 17307 = 17536 + 17537; VAZRUDEN THE HERALD = NAZAN (MOUNT) + VAZRUDEN
// Event: Phase1 spells
#define SUMMON_VAZRUDEN 30717
// Event: Phase2 spells
#define FIREBALL 30691	// DBC: 34653, 30691
#define LIQUID_FLAME 1
#define CONE_OF_FIRE 30926
// FACE HIGHEST THREAT 30700
struct Coords
{
    float x;
    float y;
    float z;
    float o;
};

static Coords fly[] = 
{
	{ 0, 0, 0, 0 },
	{ -1413.410034f, 1744.969971f,  80.900000f, 0.147398f },	// fly starting position
	{ -1413.410034f, 1744.969971f,  92.948196f, 0.147398f },	// fly !
	{ -1378.454712f, 1687.340332f, 110.200218f, 1.017074f },	// 1 full fly in circle wp
	{ -1352.973145f, 1726.131470f, 110.408745f, 1.297234f },	// 2
    { -1362.943970f, 1767.925415f, 110.101616f, 5.212438f },	// 3
	{ -1415.544189f, 1804.141357f, 110.075363f, 5.974271f },	// 4
	{ -1461.189575f, 1780.554932f, 110.854507f, 0.460774f },	// 5
	{ -1482.489380f, 1718.727783f, 110.248772f, 5.847037f },	// 6
	{ -1418.811646f, 1676.112427f, 110.405968f, 0.231439f },	// 7
	{ -1413.408203f, 1744.974121f,  92.000000f, 0.147398f }		// land place
};
//	{ -1413.410034, 1744.969971,  80.948196, 0.147398 },	// fly starting position

class NAZANAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(NAZANAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    NAZANAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		VAZRUDEN_THE_HERALD_EVENT_PHASE = 1;
		HERALDS_SENTRY_DEATHS = 0;
        m_entry = pCreature->GetEntry();
        m_useSpell = false;
        m_FireballCooldown = 5;
        m_ConeOfFireCooldown = 0;

		_unit->GetAIInterface()->addWayPoint(CreateWaypoint(1, 2000, RUN));	//RUN
		_unit->GetAIInterface()->addWayPoint(CreateWaypoint(2, 0, FLY));	// FLY START!
        _unit->GetAIInterface()->addWayPoint(CreateWaypoint(3, 0, FLY));
        _unit->GetAIInterface()->addWayPoint(CreateWaypoint(4, 0, FLY));
        _unit->GetAIInterface()->addWayPoint(CreateWaypoint(5, 0, FLY));
        _unit->GetAIInterface()->addWayPoint(CreateWaypoint(6, 0, FLY));
        _unit->GetAIInterface()->addWayPoint(CreateWaypoint(7, 0, FLY));
        _unit->GetAIInterface()->addWayPoint(CreateWaypoint(8, 0, FLY));
        _unit->GetAIInterface()->addWayPoint(CreateWaypoint(9, 0, FLY));
		_unit->GetAIInterface()->addWayPoint(CreateWaypoint(10, 1000, FLY));	// SPECIAL WP! (FOR VAZRUDEN LANDING!)

        //infoFireball = dbcSpell.LookupEntry(FIREBALL);
        infoLiquidFlame = dbcSpell.LookupEntry(LIQUID_FLAME);
        //infoConeOfFire = dbcSpell.LookupEntry(CONE_OF_FIRE);
		infoSummonVazruden = dbcSpell.LookupEntry(SUMMON_VAZRUDEN);

		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

        spells[0].info = dbcSpell.LookupEntry(FIREBALL);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = false;
		spells[0].cooldown = 10;
		spells[0].perctrigger = 0.0f;
		spells[0].attackstoptimer = 1000;

        spells[1].info = dbcSpell.LookupEntry(CONE_OF_FIRE);
		spells[1].targettype = TARGET_VARIOUS;
		spells[1].instant = true;
		spells[1].cooldown = 20;
		spells[1].perctrigger = 0.0f;
		spells[1].attackstoptimer = 1000;

        if(/*!infoFireball || */!infoLiquidFlame ||/* !infoConeOfFire || */!infoSummonVazruden)
            m_useSpell = false;

        _unit->GetAIInterface()->setOutOfCombatRange(200000);

		VAZRUDEN_LAND = false;
		NAZAN_LAND = false;
		_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
        _unit->GetAIInterface()->StopMovement(0);
        _unit->GetAIInterface()->SetAIState(STATE_SCRIPTMOVE);
		_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
		_unit->GetAIInterface()->setWaypointToMove(1);

    }
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)	// not finished yet, as I must force Nazan to go into combat state
    {
		_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
		if (VAZRUDEN_THE_HERALD_EVENT_PHASE == 3)
		{
			VAZRUDEN_THE_HERALD_EVENT_PHASE = 1;
			HERALDS_SENTRY_DEATHS = 0;
			_unit->GetAIInterface()->SetAIState(STATE_SCRIPTMOVE);
			_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
			_unit->GetAIInterface()->setWaypointToMove(1);
			VAZRUDEN_LAND = false;
			NAZAN_LAND = false;
		}

		if (VAZRUDEN_THE_HERALD_EVENT_PHASE == 2)
		{
			HERALDS_SENTRY_DEATHS = 0;
			VAZRUDEN_THE_HERALD_EVENT_PHASE = 1;
			VAZRUDEN_LAND = false;
		}

        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		VAZRUDEN_THE_HERALD_EVENT_PHASE = 1;
		HERALDS_SENTRY_DEATHS = 0;
		VAZRUDEN_LAND = false;
		NAZAN_LAND = false;
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
    {
		switch (VAZRUDEN_THE_HERALD_EVENT_PHASE)
		{
		case 1: 
			{
				PhaseOne();
			}break;
		case 2:
			{
				PhaseTwo();
			}break;
		case 3: 
			{
				PhaseThree();
			}break;
		default:
			{
				VAZRUDEN_THE_HERALD_EVENT_PHASE = 1;
			};
		};
		//float val = (float)RandomFloat(100.0f);
		//SpellCast(val);
    }

    void PhaseOne()
    {
    }

	void PhaseTwo()
	{
		m_useSpell = true;
		m_FireballCooldown--;
        if(!m_FireballCooldown && _unit->GetAIInterface()->GetNextTarget())
        {
            _unit->CastSpell(_unit->GetAIInterface()->GetNextTarget(), infoFireball, false);
            m_FireballCooldown = 5;
        }
	}

    void PhaseThree()
    {
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
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

    void Fly()
    {
        _unit->Emote(EMOTE_ONESHOT_LIFTOFF);
        _unit->GetAIInterface()->m_moveFly = true;
    }

    void Land()
    {
        _unit->Emote(EMOTE_ONESHOT_LAND);
        _unit->GetAIInterface()->m_moveFly = false;
    }

    void OnReachWP(uint32 iWaypointId, bool bForwards)
    {
		if (HERALDS_SENTRY_DEATHS == 2 && VAZRUDEN_LAND == false) /*VAZRUDEN_THE_HERALD_EVENT_PHASE == 2*/
		{
			VAZRUDEN_THE_HERALD_EVENT_PHASE = 2;
			VAZRUDEN_LAND = true;
			_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
            _unit->GetAIInterface()->setWaypointToMove(10);
		}

		if (VAZRUDEN_THE_HERALD_EVENT_PHASE == 3 && NAZAN_LAND == false)
		{
			NAZAN_LAND = true;
            _unit->SetFloatValue(UNIT_MOD_CAST_SPEED, 1.0f);
            if(_unit->GetCurrentSpell() != NULL)				// these 3 lines added from Onyxia script
                _unit->GetCurrentSpell()->cancel();
            _unit->GetAIInterface()->m_canMove = true;
            _unit->GetAIInterface()->SetAllowedToEnterCombat(false);
            //_unit->GetAIInterface()->StopMovement(0);	// commented? this crap "despawns" creature
            _unit->GetAIInterface()->SetAIState(STATE_SCRIPTMOVE);
			_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
			_unit->GetAIInterface()->setWaypointToMove(2);
			if (_unit->GetAIInterface()->GetNextTarget())
			{
				Unit *target = NULL;
				target = _unit->GetAIInterface()->GetNextTarget();
				_unit->CastSpell(target, spells[1].info, spells[1].instant);
			}
		}

		else
		{
			switch(iWaypointId)
			{
			case 1:
				{
					if (VAZRUDEN_THE_HERALD_EVENT_PHASE == 3)
					{
						_unit->GetAIInterface()->SetAllowedToEnterCombat(true);
						_unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
						_unit->GetAIInterface()->SetAIState(STATE_SCRIPTIDLE);
						_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_DONTMOVEWP);
						_unit->GetAIInterface()->setWaypointToMove(0);
						WorldPacket data(SMSG_MOVE_UNSET_HOVER, 13);
						data << _unit->GetNewGUID();
						data << uint32(0);
						_unit->SendMessageToSet(&data, false);
						Land();

					}

					else
					{
						_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
						_unit->GetAIInterface()->setWaypointToMove(2);
						Fly();
					}
				}break;

			case 2:
				{
					if (VAZRUDEN_THE_HERALD_EVENT_PHASE == 3)
					{
						_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
						_unit->GetAIInterface()->setWaypointToMove(1);
					}

					else
					{
						_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
						_unit->GetAIInterface()->setWaypointToMove(3);	
					}
				}break;

			case 3:
			    {
			        _unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
			        _unit->GetAIInterface()->setWaypointToMove(4);
			    }break;

			case 4:
			    {
			        _unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
			        _unit->GetAIInterface()->setWaypointToMove(5);
			    }break;

			case 5:
			    {
			        _unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
			        _unit->GetAIInterface()->setWaypointToMove(6);
					/*
			        _unit->GetAIInterface()->m_canMove = false;
			        _unit->GetAIInterface()->SetAllowedToEnterCombat(true);
			        _unit->GetAIInterface()->setCurrentAgent(AGENT_SPELL);
			        //_unit->m_pacified--;
			        _unit->GetAIInterface()->SetAIState(STATE_SCRIPTIDLE);
			        _unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_DONTMOVEWP);
			        _unit->GetAIInterface()->setWaypointToMove(0);
			        WorldPacket data(SMSG_MOVE_SET_HOVER, 13);
			        data << _unit->GetNewGUID();
			        data << uint32(0);
			        _unit->SendMessageToSet(&data, false);
			        m_currentWP = 3;*/
			    }break;

			case 6:
			    {
			        _unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
			        _unit->GetAIInterface()->setWaypointToMove(7);
			    }break;

			case 7:
			    {
			        _unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
			        _unit->GetAIInterface()->setWaypointToMove(8);
			    }break;

			case 8:
			    {
			        _unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
			        _unit->GetAIInterface()->setWaypointToMove(9);
			    }break;

			case 9:
			    {
			        _unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
			        _unit->GetAIInterface()->setWaypointToMove(3);
			    }break;

			case 10:
			    {
					if (VAZRUDEN_THE_HERALD_EVENT_PHASE == 3)
					{
						/*_unit->GetAIInterface()->SetAllowedToEnterCombat(true);
						_unit->GetAInterface()->setCurrentAgent(AGENT_NULL);
						_unit->GetAIInterface()->SetAIState(STATE_SCRIPTIDLE);
						_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_DONTMOVEWP);
						//_unit->GetAIInterface()->setWaypointToMove(0);
						//_unit->GetAIInterface()->m_canMove = true;
						//_unit->GetAIInterface()->SetAllowedToEnterCombat(true);
						//_unit->GetAIInterface()->StopMovement(0);
						//_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_DONTMOVEWP);
						//_unit->GetAIInterface()->SetAIState(STATE_SCRIPTMOVE);
						//_unit->GetAIInterface()->SetAIState(STATE_SCRIPTIDLE);
						Land();
						m_useSpell = true;
		                _unit->GetAIInterface()->SetAllowedToEnterCombat(true);
						_unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
						_unit->GetAIInterface()->SetAIState(STATE_SCRIPTIDLE);
						_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_DONTMOVEWP);
						_unit->GetAIInterface()->setWaypointToMove(0);
		                WorldPacket data(SMSG_MOVE_UNSET_HOVER, 13);
						data << _unit->GetNewGUID();
						data << uint32(0);
						_unit->SendMessageToSet(&data, false);
						Land();*/
					    //_unit->GetAIInterface()->SetAllowedToEnterCombat(true);
						//_unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
						/*nit->GetAIInterface()->SetAIState(STATE_SCRIPTIDLE);*/	// this shit messes all =/ // SCRIPTIDLE
						_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_DONTMOVEWP);
						_unit->GetAIInterface()->setWaypointToMove(9);
						/*_unit->m_pacified--;
						if(_unit->m_pacified > 0)
					    _unit->m_pacified--;*/
						/*WorldPacket data(SMSG_MOVE_UNSET_HOVER, 13);
						data << _unit->GetNewGUID();
						data << uint32(0);
						_unit->SendMessageToSet(&data, false);*/ // Hover disabled for now
						//_unit->GetAIInterface()->m_moveFly = false;
						Land();
						/* working partially
						_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_DONTMOVEWP);
						_unit->GetAIInterface()->setWaypointToMove(0);
						Land();
						*/
					}

					if (VAZRUDEN_THE_HERALD_EVENT_PHASE == 2)
					{
						m_useSpell = true;
						_unit->CastSpell(_unit, infoSummonVazruden, true);
						_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
						_unit->GetAIInterface()->setWaypointToMove(3);
					}

				}break;

			default:
				{
                _unit->GetAIInterface()->m_canMove = false;
                _unit->GetAIInterface()->SetAllowedToEnterCombat(true);
                _unit->GetAIInterface()->SetAIState(STATE_SCRIPTIDLE);
                _unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_DONTMOVEWP);
                _unit->GetAIInterface()->setWaypointToMove(0);
                WorldPacket data(SMSG_MOVE_SET_HOVER, 13);
                data << _unit->GetNewGUID();
                data << uint32(0);
                _unit->SendMessageToSet(&data, false);
				}break;
			}
		}
    }

    inline Movement::WayPoint* CreateWaypoint(int id, uint32 waittime, uint32 flags)
    {
        Movement::WayPoint * wp = _unit->CreateWaypointStruct();
        wp->id = id;
        wp->x = fly[id].x;
        wp->y = fly[id].y;
        wp->z = fly[id].z;
        wp->o = fly[id].o;
        wp->waittime = waittime;
        wp->flags = flags;
        wp->forwardemoteoneshot = 0;
        wp->forwardemoteid = 0;
        wp->backwardemoteoneshot = 0;
        wp->backwardemoteid = 0;
        wp->forwardskinid = 0;
        wp->backwardskinid = 0;
        return wp;
    }

protected:

    uint32 m_entry;
    bool m_useSpell;
	bool VAZRUDEN_LAND;
	bool NAZAN_LAND;
    uint32 m_FireballCooldown;
    uint32 m_ConeOfFireCooldown;
    uint32 m_fCastCount;
    uint32 m_currentWP;
    SpellEntry *infoConeOfFire, *infoLiquidFlame, *infoFireball, *infoSummonVazruden;
	int nrspells;
};

void SetupHellfireRamparts(ScriptMgr * mgr)
{
	mgr->register_creature_script(CN_WATCHKEEPER_GARGOLMAR, &WatchkeeperGargolmarAI::Create);
	mgr->register_creature_script(CN_OMOR_THE_UNSCARRED, OmorTheUnscarredAI::Create);
	/*mgr->register_creature_script(CN_HELLFIRE_SENTRY, &HELLFIRESENTRYAI::Create);
	mgr->register_creature_script(CN_VAZRUDEN, &VAZRUDENAI::Create);
	mgr->register_creature_script(CN_NAZAN, &NAZANAI::Create);*/
}
