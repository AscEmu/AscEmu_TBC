UPDATE `creature_spawns` SET `standstate`= 3 WHERE `entry` = 16483;

--
-- Update world_db_version
--
UPDATE `world_db_version` SET `LastUpdate` = '2016-5-26_01_creature_spawns' WHERE `LastUpdate` = '2015-11-10_02_npc_script_text';