-- MySQL dump 10.11
--
-- Host: 127.0.0.1    Database: ascent_world
-- ------------------------------------------------------
-- Server version	5.1.45-community

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `creature_staticspawns`
--

DROP TABLE IF EXISTS `creature_staticspawns`;
CREATE TABLE `creature_staticspawns` (
  `id` int(30) unsigned NOT NULL AUTO_INCREMENT,
  `entry` int(30) NOT NULL,
  `Map` int(30) NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `o` float NOT NULL,
  `movetype` int(30) NOT NULL DEFAULT '0',
  `displayid` int(30) unsigned NOT NULL DEFAULT '0',
  `factionid` int(30) NOT NULL DEFAULT '35',
  `flags` int(30) NOT NULL DEFAULT '0',
  `bytes0` int(30) NOT NULL DEFAULT '0',
  `bytes1` int(30) NOT NULL DEFAULT '0',
  `bytes2` int(30) NOT NULL DEFAULT '0',
  `emote_state` int(30) NOT NULL DEFAULT '0',
  `npc_respawn_link` int(30) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `id` (`id`),
  KEY `a` (`Map`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Spawn System';

--
-- Dumping data for table `creature_staticspawns`
--

LOCK TABLES `creature_staticspawns` WRITE;
/*!40000 ALTER TABLE `creature_staticspawns` DISABLE KEYS */;
/*!40000 ALTER TABLE `creature_staticspawns` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2010-11-08 19:15:05
