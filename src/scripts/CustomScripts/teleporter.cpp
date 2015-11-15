#include "StdAfx.h"
#include "Setup.h"

class SCRIPT_DECL TeleNPC : public GossipScript
{
public:

    void Destroy()
    {
        delete this;
    }

    void GossipHello(Object* pObject, Player * Plr, bool AutoS)
    {
        GossipMenu* Menu;
        objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2593, Plr);
        if (Plr->CombatStatus.IsInCombat() == true)
        {
            Plr->BroadcastMessage("You are in combat!");
            return;
        }

        if (Plr->GetTeam() == 1)
        {
            Menu->AddItem(4, "Horde Cities", 1000);
            Menu->AddItem(4, "Zum Playertreff", 20000);
        }
        else
        {
            Menu->AddItem(4, "Alliance Cities", 2000);
            Menu->AddItem(4, "Zum Playertreff", 10000);
        }

        Menu->AddItem(9, "Neutral Cities", 3000);
        Menu->AddItem(9, "Dungeons", 5000);
        Menu->AddItem(9, "SWV Instance (Custom instance)", 30000);
        Menu->AddItem(9, "Gurbashi Arena - PvP", 3500);
        Menu->AddItem(10, "Remove Resurrection Sickness", 4020);

        if (AutoS)
            Menu->SendTo(Plr);
    }

    void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char * Code)
    {
        GossipMenu* Menu;
        switch (IntId)
        {
        case 1000: //Horde Town
            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
            Menu->AddItem(10, "Orgrimmar", 2001);
            Menu->AddItem(10, "Silvermoon", 2005);
            Menu->AddItem(10, "Thunder Bluff", 2010);
            Menu->AddItem(10, "Undercity", 2015);
            Menu->AddItem(4, "<- Main Menu", 5005);
            Menu->SendTo(Plr);
            break;
        case 2000: //Alliance Town
            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);

            Menu->AddItem(10, "Darnassus", 1001);
            Menu->AddItem(10, "Exodar", 1005);
            Menu->AddItem(10, "Ironforge", 1010);
            Menu->AddItem(10, "Stormwind", 1015);
            Menu->AddItem(4, "<- Main Menu", 5005);
            Menu->SendTo(Plr);
            break;
        case 3000: //Neutral Town
            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
            if (Plr->getClass() == 6)
            {
                Menu->AddItem(10, "Ebon Hold", 3001);
                Menu->AddItem(10, "Booty Bay", 3005);
                Menu->AddItem(10, "Dalaran", 3010);
                Menu->AddItem(10, "Everlook", 3015);
                Menu->AddItem(10, "Gadegetzan", 3020);
                Menu->AddItem(10, "Mudsprocket", 3025);
                Menu->AddItem(10, "Ratchet", 3030);
                Menu->AddItem(10, "Shattrath City", 3035);
                Menu->AddItem(10, "Isle Of Quel'Danas", 3040);
                Menu->AddItem(4, "Dungeons ->", 5000);
                Menu->AddItem(4, "<- Main Menu", 5005);
            }
            else
            {
                Menu->AddItem(10, "Booty Bay", 3005);
                Menu->AddItem(10, "Dalaran", 3010);
                Menu->AddItem(10, "Everlook", 3015);
                Menu->AddItem(10, "Gadegetzan", 3020);
                Menu->AddItem(10, "Mudsprocket", 3025);
                Menu->AddItem(10, "Ratchet", 3030);
                Menu->AddItem(10, "Shattrath City", 3035);
                Menu->AddItem(10, "Isle Of Quel'Danas", 3040);
                Menu->AddItem(4, "Dungeons ->", 5000);
                Menu->AddItem(4, "<- Main Menu", 5005);
            }
            Menu->SendTo(Plr);
            break;
        case 5000: //Dungeons
            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
            Menu->AddItem(4, "Kalimdor ->", 5010);
            Menu->AddItem(4, "Eastern Kingdoms ->", 5015);
            Menu->AddItem(4, "Outland ->", 5025);
            Menu->AddItem(4, "<- Main Menu", 5005);
            Menu->SendTo(Plr);
            break;
        case 5005:
            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
            if (Plr->GetTeam() == 1)
            {
                Menu->AddItem(4, "Horde Cities", 1000);
                Menu->AddItem(4, "Zum Playertreff", 20000);
            }
            else
            {
                Menu->AddItem(4, "Alliance Cities", 2000);
                Menu->AddItem(4, "Zum Playertreff", 30000);
            }
            Menu->AddItem(4, "Neutral Cities", 3000);
            Menu->AddItem(4, "Dungeons", 5000);
            Menu->AddItem(9, "SWV Instance (Custom instance)", 30000);
            Menu->AddItem(9, "Gurbashi Arena - PvP", 3500);
            Menu->AddItem(10, "Remove Resurrection Sickness", 4020);
            Menu->SendTo(Plr);
            break;
        case 5010: //Kalimdor
            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
            Menu->AddItem(10, "Blackfathom Deeps", 6001);
            Menu->AddItem(10, "Caverns of Time", 6005);
            Menu->AddItem(10, "Dire Maul", 6010);
            Menu->AddItem(10, "Maraudon", 6015);
            Menu->AddItem(10, "Onyxia's Lair", 6020);
            Menu->AddItem(10, "Ragefire Chasm", 6025);
            Menu->AddItem(10, "Razorfen Downs", 6030);
            Menu->AddItem(10, "Razorfen Kraul", 6035);
            Menu->AddItem(10, "Ruins of Ahn'Qiraj", 6040);
            Menu->AddItem(10, "Temple of Ahn'Qiraj", 6045);
            Menu->AddItem(10, "Wailing Caverns", 6050);
            Menu->AddItem(10, "Zul'Farrak", 6055);
            Menu->AddItem(4, "<- Back", 5000);
            Menu->SendTo(Plr);
        case 5015: //Eastern Kingdoms 1
            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
            Menu->AddItem(10, "Blackrock Depths", 7001);
            Menu->AddItem(10, "Blackrock Spire", 7005);
            Menu->AddItem(10, "Blackwing Lair", 7010);
            Menu->AddItem(10, "Deadmines", 7015);
            Menu->AddItem(10, "Gnomeregan", 7020);
            Menu->AddItem(10, "Isle Of Quel'Danas", 7025);
            Menu->AddItem(10, "Karazhan", 7030);
            Menu->AddItem(10, "Molten Core", 7035);
            Menu->AddItem(4, "More ->", 5020);
            Menu->AddItem(4, "<- Back", 5000);
            Menu->SendTo(Plr);
            break;
        case 5020: //Eastern Kingdoms 2
            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
            Menu->AddItem(10, "Scarlet Monastery", 7040);
            Menu->AddItem(10, "Scholomance", 7045);
            Menu->AddItem(10, "Shadowfang Keep", 7050);
            Menu->AddItem(10, "Stratholme", 7055);
            Menu->AddItem(10, "Sunken Temple", 7060);
            Menu->AddItem(10, "The Stockade", 7065);
            Menu->AddItem(10, "Uldaman", 7070);
            Menu->AddItem(10, "Zul'Aman", 7075);
            Menu->AddItem(10, "Zul'Gurub", 7080);
            Menu->AddItem(4, "<- Back", 5015);
            Menu->AddItem(4, "<- Main Menu", 5005);
            Menu->SendTo(Plr);
            break;
        case 5025: //Outland
            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
            Menu->AddItem(10, "Auchindoun", 8001);
            Menu->AddItem(10, "Black Temple", 8005);
            Menu->AddItem(10, "Coilfang Reservoir", 8010);
            Menu->AddItem(10, "Gruul's Lair", 8015);
            Menu->AddItem(10, "Hellfire Citadel", 8020);
            Menu->AddItem(10, "Tempest Keep", 8025);
            Menu->AddItem(4, "<- Back", 5000);
            Menu->SendTo(Plr);
            break;
            //////////////////////////////////////////////////ALLIANCE///////////////////////////////////////////////////////////////
        case 1001: // Darnassus
            Plr->Gossip_Complete();
            Plr->EventTeleport(1, 9947.52f, 2482.73f, 1316.21f);
            break;
        case 1005: // Exodar
            Plr->Gossip_Complete();
            Plr->EventTeleport(530, -3954.20f, -11656.54f, -138.69f);
            break;
        case 1010: // Ironforge
            Plr->Gossip_Complete();
            Plr->EventTeleport(0, -4924.07f, -951.95f, 501.55f);
            break;
        case 1015: // Stormwind
            Plr->Gossip_Complete();
            Plr->EventTeleport(0, -8960.14f, 516.266f, 96.3568f);
            break;
            //////////////////////////////////////////////////HORDE///////////////////////////////////////////////////////////////
        case 2001: // Orgrimmar
            Plr->Gossip_Complete();
            Plr->EventTeleport(1, 1552.5f, -4420.66f, 8.94802f);
            break;
        case 2005: // Silvermoon
            Plr->Gossip_Complete();
            Plr->EventTeleport(530, 9338.74f, -7277.27f, 13.7895f);
            break;
        case 2010: // Thunder Bluff
            Plr->Gossip_Complete();
            Plr->EventTeleport(1, -1290.0f, 147.033997f, 129.682007f);
            break;
        case 2015: // Undercity
            Plr->Gossip_Complete();
            Plr->EventTeleport(0, 1819.71f, 238.79f, 60.5321f);
            break;
            //////////////////////////////////////////////////NEUTRAL///////////////////////////////////////////////////////////////
        case 3001:// Ebon Hold
            Plr->Gossip_Complete();
            Plr->EventTeleport(0, 2353.530029f, -5665.819824f, 426.028015f);
            break;
        case 3005:// Booty Bay
            Plr->Gossip_Complete();
            Plr->EventTeleport(0, -14438.2f, 472.22f, 15.32f);
            break;
        case 3010: //Dalaran
            Plr->Gossip_Complete();
            Plr->EventTeleport(571, 5819.08f, 643.99f, 647.80f);
            break;
        case 3015: //Everlook
            Plr->Gossip_Complete();
            Plr->EventTeleport(1, 6724.77f, -4610.68f, 720.78f);
            break;
        case 3020: //Gadgetzan
            Plr->Gossip_Complete();
            Plr->EventTeleport(1, -7173.26f, -3785.60f, 8.37f);
            break;
        case 3025: //Mudsprocket
            Plr->Gossip_Complete();
            Plr->EventTeleport(1, -4564.79f, -3172.38f, 33.93f);
            break;
        case 3030: //Ratchet
            Plr->Gossip_Complete();
            Plr->EventTeleport(1, -956.664f, -3754.71f, 5.33239f);
            break;
        case 3035:// Shattrath City
            Plr->Gossip_Complete();
            Plr->EventTeleport(530, -1850.209961f, 5435.821777f, -10.961435f);
            break;
        case 3040:// Isle Of Quel'Danas
            Plr->Gossip_Complete();
            Plr->EventTeleport(530, 12947.4f, -6893.31f, 5.68398f);
            break;
        case 3500: // Arena PvP Option
            Plr->Gossip_Complete();
            Plr->EventTeleport(0, -13277.4f, 127.372f, 26.1418f);
            break;
        case 4020:
            if (Plr->HasAura(15007) == true)
            {
                Plr->RemoveAura(15007);
                Plr->BroadcastMessage("You have been cured of Resurrection Sickness!");
                Plr->Gossip_Complete();
            }
            else
            {
                Plr->BroadcastMessage("You do not currently have Resurrection Sickness!");
                Plr->Gossip_Complete();
            }
            break;
            //////////////////////////////////////////////////KALIMDOR///////////////////////////////////////////////////////////////
        case 6001:// Blackfathom Deeps
            Plr->Gossip_Complete();
            Plr->EventTeleport(1, 4248.72f, 744.35f, -24.67f);
            break;
        case 6005:// Caverns of Time
            Plr->Gossip_Complete();
            Plr->EventTeleport(1, -8173.66f, -4746.36f, 33.84f);
            break;
        case 6010:// Dire Maul
            Plr->Gossip_Complete();
            Plr->EventTeleport(1, -3960.95f, 1130.64f, 161.05f);
            break;
        case 6015:// Maraudon
            Plr->Gossip_Complete();
            Plr->EventTeleport(1, -1431.33f, 2962.34f, 98.23f);
            break;
        case 6020:// Onyxia's Lair
            Plr->Gossip_Complete();
            Plr->EventTeleport(1, -4707.44f, -3726.82f, 54.6723f);
            break;
        case 6025:// Ragefire Chasm
            Plr->Gossip_Complete();
            Plr->EventTeleport(1, 1814.47f, -4419.46f, -18.78f);
            break;
        case 6030:// Razorfen Downs
            Plr->Gossip_Complete();
            Plr->EventTeleport(1, -4657.88f, -2525.59f, 81.4f);
            break;
        case 6035:// Razorfen Kraul
            Plr->Gossip_Complete();
            Plr->EventTeleport(1, -4463.6f, -1664.53f, 82.26f);
            break;
        case 6040:// Ruins of Ahn'Qiraj
            Plr->Gossip_Complete();
            Plr->EventTeleport(1, -8413.33f, 1501.27f, 29.64f);
            break;
        case 6045:// Temple of Ahn'Qiraj
            Plr->Gossip_Complete();
            Plr->EventTeleport(1, -8245.837891f, 1983.736206f, 129.071686f);
            break;
        case 6050:// Wailing Caverns
            Plr->Gossip_Complete();
            Plr->EventTeleport(1, -722.53f, -2226.30f, 16.94f);
            break;
        case 6055:// Zul'Farrak
            Plr->Gossip_Complete();
            Plr->EventTeleport(1, -6801.9f, -2890.22f, 8.88f);
            break;
            //////////////////////////////////////////////////EASTERN KINGDOMS///////////////////////////////////////////////////////////////
        case 7001:// Blackrock Depths
            Plr->Gossip_Complete();
            Plr->EventTeleport(0, -7180.57f, -920.04f, 165.49f);
            break;
        case 7005:// Blackrock Spire
            Plr->Gossip_Complete();
            Plr->EventTeleport(0, -7526.77f, -1225.64f, 285.73f);
            break;
        case 7010:// Blackwing Lair
            Plr->Gossip_Complete();
            Plr->EventTeleport(469, -7672.61f, -1107.21f, 396.65f);
            break;
        case 7015:// Deadmines
            Plr->Gossip_Complete();
            Plr->EventTeleport(0, -11208.2f, 1675.92f, 24.57f);
            break;
        case 7020:// Gnomeregan
            Plr->Gossip_Complete();
            Plr->EventTeleport(0, -5163.32f, 927.18f, 257.158f);
            break;
        case 7025:// Isle Of Quel'Danas
            Plr->Gossip_Complete();
            Plr->EventTeleport(530, 13010.00f, -6907.64f, 9.58f);
            break;
        case 7030:// Karazhan
            Plr->Gossip_Complete();
            Plr->EventTeleport(0, -11119.6f, -2011.42f, 47.09f);
            break;
        case 7035:// Molten Core
            Plr->Gossip_Complete();
            Plr->EventTeleport(230, 1114.85f, -457.76f, -102.81f);
            break;
        case 7040:// Scarlet Monastery
            Plr->Gossip_Complete();
            Plr->EventTeleport(0, 2843.89f, -693.74f, 139.32f);
            break;
        case 7045:// Scholomance
            Plr->Gossip_Complete();
            Plr->EventTeleport(0, 1273.06f, -2574.01f, 92.66f);
            break;
        case 7050:// Shadowfang Keep
            Plr->Gossip_Complete();
            Plr->EventTeleport(0, -239.54f, 1550.8f, 76.89f);
            break;
        case 7055:// Stratholme
            Plr->Gossip_Complete();
            Plr->EventTeleport(0, 3370.76f, -3343.63f, 142.26f);
            break;
        case 7060:// Sunken Temple
            Plr->Gossip_Complete();
            Plr->EventTeleport(0, -10346.92f, -3851.90f, -43.41f);
            break;
        case 7065:// The Stockade
            Plr->Gossip_Complete();
            Plr->EventTeleport(0, -8766.89f, 844.6f, 88.43f);
            break;
        case 7070:// Uldaman
            Plr->Gossip_Complete();
            Plr->EventTeleport(0, -6070.72f, -2955.33f, 209.78f);
            break;
        case 7075:// Zul'Aman
            Plr->Gossip_Complete();
            Plr->EventTeleport(530, 6851.09f, -7979.71f, 183.54f);
            break;
        case 7080:// Zul'Gurub
            Plr->Gossip_Complete();
            Plr->EventTeleport(0, -11916.4f, -1216.23f, 92.28f);
            break;
            //////////////////////////////////////////////////OUTLAND///////////////////////////////////////////////////////////////
        case 8001:// Auchindoun
            Plr->Gossip_Complete();
            Plr->EventTeleport(530, -3322.92f, 4931.02f, -100.56f);
            break;
        case 8005:// Black Temple
            Plr->Gossip_Complete();
            Plr->EventTeleport(530, -3649.1f, 317.33f, 35.19f);
            break;
        case 8010:// Coilfang Reservoir
            Plr->Gossip_Complete();
            Plr->EventTeleport(530, 721.08f, 6846.77f, -68.75f);
            break;
        case 8015:// Gruul's Lair
            Plr->Gossip_Complete();
            Plr->EventTeleport(530, 3539.01f, 5082.36f, 1.69f);
            break;
        case 8020:// Hellfire Citadel
            Plr->Gossip_Complete();
            Plr->EventTeleport(530, -292.71f, 3146.77f, 31.60f);
            break;
        case 8025:// Tempest Keep
            Plr->Gossip_Complete();
            Plr->EventTeleport(530, 3087.62f, 1376.27f, 184.8f);
            break;
        case 10000:// Allianz Playertreff
            Plr->Gossip_Complete();
            Plr->EventTeleport(0, 2918.74f, -1437.36f, 150.782f);
            break;
        case 20000:// Horde Playertreff
            Plr->Gossip_Complete();
            Plr->EventTeleport(1, 7447.3f, -1693.77f, 194.899f);
            break;
        case 30000:// SWV instanz
            Plr->Gossip_Complete();
            Plr->EventTeleport(0, -8645.188477f, 595.820679f, 95.705704f);
            break;
        }
    }
};

void SetupTeleNPC(ScriptMgr * mgr)
{
    GossipScript * teleporter = (GossipScript*) new TeleNPC();
    mgr->register_gossip_script(123456, teleporter);
}
