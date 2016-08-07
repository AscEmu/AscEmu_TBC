--
-- Delete all items greater 39656 (all higher numbers are fun stuff/wotlk)
--
DELETE FROM `items` WHERE entry > 39656;

--
-- Update world_db_version
--
UPDATE `world_db_version` SET `LastUpdate` = '2016-08-07_01_items' WHERE `LastUpdate` = '2016-08-06_00_creature_spawns';
