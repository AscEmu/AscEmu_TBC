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
-- Table structure for table `gameobject_staticspawns`
--

DROP TABLE IF EXISTS `gameobject_staticspawns`;
CREATE TABLE `gameobject_staticspawns` (
  `id` int(30) NOT NULL AUTO_INCREMENT,
  `entry` int(30) NOT NULL,
  `map` int(11) NOT NULL DEFAULT '0',
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `facing` float NOT NULL,
  `o` float NOT NULL,
  `o1` float NOT NULL,
  `o2` float NOT NULL,
  `o3` float NOT NULL,
  `state` int(11) NOT NULL DEFAULT '0',
  `flags` int(30) NOT NULL DEFAULT '0',
  `faction` int(11) NOT NULL DEFAULT '0',
  `scale` float NOT NULL,
  `respawnNpcLink` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Spawn System';

--
-- Dumping data for table `gameobject_staticspawns`
--

LOCK TABLES `gameobject_staticspawns` WRITE;
/*!40000 ALTER TABLE `gameobject_staticspawns` DISABLE KEYS */;
/*!40000 ALTER TABLE `gameobject_staticspawns` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2010-11-08 19:15:06
