--
-- Delete all creature data greater 29095 (higher entry are fun stuff/wotlk)
--
DELETE FROM `creature_names` WHERE entry > 29095;
DELETE FROM `creature_proto` WHERE entry > 29095;
DELETE FROM `creature_spawns` WHERE entry > 29095;

--
-- Update world_db_version
--
UPDATE `world_db_version` SET `LastUpdate` = '2016-08-07_04_creature' WHERE `LastUpdate` = '2016-08-07_03_creature_difficulty';
