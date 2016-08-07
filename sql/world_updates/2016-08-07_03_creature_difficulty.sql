--
-- Table structure for creature_difficulty
--
DROP TABLE IF EXISTS `creature_difficulty`;
CREATE TABLE `creature_difficulty` (
  `entry` int(30) unsigned NOT NULL DEFAULT '0',
  `difficulty_1` int(30) unsigned NOT NULL DEFAULT '0' COMMENT 'Dungeon heroic / Raid 25 man',
  `difficulty_2` int(30) unsigned NOT NULL DEFAULT '0' COMMENT 'Raid heroic 10 man (not used in tbc)',
  `difficulty_3` int(30) unsigned NOT NULL DEFAULT '0' COMMENT 'Raid heroic 25 man (not used in tbc)',
  PRIMARY KEY (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Creature Difficulty System';


UPDATE `world_db_version` SET `LastUpdate` = '2016-08-07_03_creature_difficulty' WHERE `LastUpdate` = '2016-08-07_02_itempetfood';
