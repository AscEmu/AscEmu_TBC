--
-- Structure for table world_db_version
--
CREATE TABLE IF NOT EXISTS `world_db_version` (
  `LastUpdate` varchar(255) NOT NULL DEFAULT '',
  PRIMARY KEY (`LastUpdate`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Data for table world_db_version
--
INSERT INTO `world_db_version` (`LastUpdate`) VALUES
	('2015-11-10_01_world_db_version');

