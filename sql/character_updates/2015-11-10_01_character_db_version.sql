--
-- Structure for table character_db_version
--
CREATE TABLE IF NOT EXISTS `character_db_version` (
  `LastUpdate` varchar(255) NOT NULL DEFAULT '',
  PRIMARY KEY (`LastUpdate`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Data for table character_db_version
--
INSERT INTO `character_db_version` (`LastUpdate`) VALUES
	('2015-11-10_01_character_db_version');

