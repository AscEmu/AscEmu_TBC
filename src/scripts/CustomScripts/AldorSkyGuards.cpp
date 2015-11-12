#include "StdAfx.h"
#include "Setup.h"

#define SPELL_BANISH    36642
#define SPELL_EXILE		39533

class AldorSkyrGuard : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(AldorSkyrGuard);
    AldorSkyrGuard(Creature* pCreature) : CreatureAIScript(pCreature) { };

    void OnCombatStart(Unit* mTarget)
    {
        if (!mTarget->IsPlayer())
            return;

        Player* pPlayer = static_cast<Player*>(mTarget);
        _unit->CastSpell(pPlayer, SPELL_BANISH, true);
        _unit->CastSpell(pPlayer, SPELL_EXILE, true);
        pPlayer->SafeTeleport(530, pPlayer->GetInstanceID(), 1544.691650f, 5320.947266f, 6.712060f, 0.5f);
    };

    void Destroy()
    {
        delete this;
    };
};

void SetupAldorSkyrGuard(ScriptMgr * mgr)
{
    mgr->register_creature_script(18568, &AldorSkyrGuard::Create);
    mgr->register_creature_script(19142, &AldorSkyrGuard::Create);
};