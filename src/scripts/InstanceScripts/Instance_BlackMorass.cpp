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

/************************************************************************/
/* Instance_BlackMorrass.cpp Script                                     */
/************************************************************************/

#define CN_CHRONO_LORD_DEJA 17879

#define ARCANE_BLAST 24857
#define TIME_LAPSE 31467
//#define MAGNETIC_PULL 31705 Only in Heroics - Correct ID?

class CHRONOLORDDEJAAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(CHRONOLORDDEJAAI);
   SP_AI_Spell spells[2];
   bool m_spellcheck[2];

     CHRONOLORDDEJAAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
      nrspells = 2;
      for(int i=0;i<nrspells;i++)
      {
         m_spellcheck[i] = false;
      }
        spells[0].info = dbcSpell.LookupEntry(ARCANE_BLAST);
      spells[0].targettype = TARGET_ATTACKING;
      spells[0].instant = true;
      spells[0].cooldown = 10;
      spells[0].perctrigger = 0.0f;
      spells[0].attackstoptimer = 1000;

      spells[1].info = dbcSpell.LookupEntry(TIME_LAPSE);
      spells[1].targettype = TARGET_ATTACKING;
      spells[1].instant = true;
      spells[1].cooldown = 8;
      spells[1].perctrigger = 0.0f;
      spells[1].attackstoptimer = 1000;
      
      /*spells[2].info = dbcSpell.LookupEntry(MAGNETIC_PULL);
      spells[2].targettype = TARGET_VARIOUS;
      spells[2].instant = true;
      spells[2].cooldown = 15;
      spells[2].perctrigger = 0.0f;
      spells[2].attackstoptimer = 1000;*/
    }
    
    void OnCombatStart(Unit* mTarget)
    {
      CastTime();
      _unit->SendScriptTextChatMessage(3563);   // If you will not cease this foolish quest, then you will die!
      RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

   void CastTime()
   {
      for(int i=0;i<nrspells;i++)
         spells[i].casttime = spells[i].cooldown;
   }

   void OnTargetDied(Unit* mTarget)
   {
       if (_unit->GetHealthPct() > 0)
       {
           switch (RandomUInt(1))
           {
               case 0:
                   _unit->SendScriptTextChatMessage(3565);  // I told you it was a fool's quest!
                   break;
               case 1:
                   _unit->SendScriptTextChatMessage(3566);  // Leaving so soon?
                   break;
           }
       }
   }

    void OnCombatStop(Unit *mTarget)
    {
      CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit* mKiller)
    {
        CastTime();
        _unit->SendScriptTextChatMessage(3567); // Time... is on our side.
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

#define CN_TEMPORUS 17880

#define HASTEN 31458
#define MORTAL_WOUND 28467
//#define SPELL_REFLECTION 31705 Only in Heroics - Correct ID?

class TEMPORUSAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(TEMPORUSAI);
   SP_AI_Spell spells[2];
   bool m_spellcheck[2];

     TEMPORUSAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
      nrspells = 2;
      for(int i=0;i<nrspells;i++)
      {
         m_spellcheck[i] = false;
      }
        spells[0].info = dbcSpell.LookupEntry(HASTEN);
      spells[0].targettype = TARGET_SELF;
      spells[0].instant = true;
      spells[0].cooldown = 10;
      spells[0].perctrigger = 0.0f;
      spells[0].attackstoptimer = 1000;

      spells[1].info = dbcSpell.LookupEntry(MORTAL_WOUND);
      spells[1].targettype = TARGET_ATTACKING;
      spells[1].instant = true;
      spells[1].cooldown = 5;
      spells[1].perctrigger = 0.0f;
      spells[1].attackstoptimer = 1000;
      
      /*spells[2].info = dbcSpell.LookupEntry(SPELL_REFLECTION);
      spells[2].targettype = TARGET_VARIOUS;
      spells[2].instant = true;
      spells[2].cooldown = 15;
      spells[2].perctrigger = 0.0f;
      spells[2].attackstoptimer = 1000;*/
    }
    
    void OnCombatStart(Unit* mTarget)
    {
      CastTime();
      _unit->SendScriptTextChatMessage(3585);       // So be it... you have been warned.
      RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

   void CastTime()
   {
      for(int i=0;i<nrspells;i++)
         spells[i].casttime = spells[i].cooldown;
   }

   void OnTargetDied(Unit* mTarget)
   {
       if (_unit->GetHealthPct() > 0)
       {
           switch (RandomUInt(1))
           {
               case 0:
                   _unit->SendScriptTextChatMessage(3587);  // You should have left when you had the chance.
                   break;
               case 1:
                   _unit->SendScriptTextChatMessage(3588);  // Your days are done.
                   break;
           }
       }
   }

    void OnCombatStop(Unit *mTarget)
    {
      CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit* mKiller)
    {
      CastTime();
      _unit->SendScriptTextChatMessage(3589);  // My death means... little.
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

#define CN_AEONUS 17881

#define SAND_BREATH 31478
#define TIME_STOP 31422
#define FRENZY 28371 //ID according to wowwiki

class AEONUSAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(AEONUSAI);
   SP_AI_Spell spells[3];
   bool m_spellcheck[3];

     AEONUSAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
      nrspells = 3;
      for(int i=0;i<nrspells;i++)
      {
         m_spellcheck[i] = false;
      }
        spells[0].info = dbcSpell.LookupEntry(SAND_BREATH);
      spells[0].targettype = TARGET_DESTINATION;
      spells[0].instant = true;
      spells[0].cooldown = 15;
      spells[0].perctrigger = 0.0f;
      spells[0].attackstoptimer = 1000;

      spells[1].info = dbcSpell.LookupEntry(TIME_STOP);
      spells[1].targettype = TARGET_VARIOUS;
      spells[1].instant = true;
      spells[1].cooldown = 15;
      spells[1].perctrigger = 0.0f;
      spells[1].attackstoptimer = 1000;
      
      spells[2].info = dbcSpell.LookupEntry(FRENZY);
      spells[2].targettype = TARGET_SELF;
      spells[2].instant = true;
      spells[2].cooldown = 8;
      spells[2].perctrigger = 0.0f;
      spells[2].attackstoptimer = 1000;
    }
    
    void OnCombatStart(Unit* mTarget)
    {
      CastTime();
      _unit->SendScriptTextChatMessage(3569);       // Let us see what fate has in store....
      RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

   void CastTime()
   {
      for(int i=0;i<nrspells;i++)
         spells[i].casttime = spells[i].cooldown;
   }

   void OnTargetDied(Unit* mTarget)
   {
       if (_unit->GetHealthPct() > 0)
       {
           switch (RandomUInt(1))
           {
               case 0:
                   _unit->SendScriptTextChatMessage(3572);      // No one will stop us! old:No one can stop us! No one!
                   break;
               case 1:
                   _unit->SendScriptTextChatMessage(3571);      // One less obstacle in our way!
                   break;
           }
       }
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
      _unit->SendScriptTextChatMessage(3573);       // It is only a matter...of time.
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

void SetupTheBlackMorass(ScriptMgr * mgr)
{
   mgr->register_creature_script(CN_CHRONO_LORD_DEJA, &CHRONOLORDDEJAAI::Create);
   mgr->register_creature_script(CN_TEMPORUS, &TEMPORUSAI::Create);
   mgr->register_creature_script(CN_AEONUS, &AEONUSAI::Create);
}