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
-- Table structure for table `teleport_coords`
--

DROP TABLE IF EXISTS `teleport_coords`;
CREATE TABLE `teleport_coords` (
  `id` int(10) unsigned NOT NULL DEFAULT '0',
  `name` char(255) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `mapId` int(10) unsigned NOT NULL DEFAULT '0',
  `position_x` float NOT NULL DEFAULT '0',
  `position_y` float NOT NULL DEFAULT '0',
  `position_z` float NOT NULL DEFAULT '0',
  `totrigger` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='World System';

--
-- Dumping data for table `teleport_coords`
--

LOCK TABLES `teleport_coords` WRITE;
/*!40000 ALTER TABLE `teleport_coords` DISABLE KEYS */;
INSERT INTO `teleport_coords` VALUES (31,'Teleport: Goldshire',0,-9458.81,64.826,55.957,0),(33,'Teleport: Westfall',530,13005.5,-6910.9,9.58423,0),(34,'Teleport: Duskwood',0,-9973.92,-1633.17,26.94,0),(35,'Teleport: Elwynn',0,-9760.26,678.23,27.021,0),(427,'Teleport: Scarlet Monastery',0,2889.91,-811.148,160.332,0),(428,'Teleport: Moonbrook',0,-11025.2,1497.86,43.1953,0),(442,'Teleport: Northshire Abbey',0,-8914.38,-135.35,80.45,0),(444,'Teleport: Westfall Lighthouse',0,-11409.9,1968.42,10.4271,0),(445,'Teleport: Darkshire',0,-10413.9,-1136.88,24.1288,0),(446,'Teleport: Raven Hill Cemetary',0,-10531.2,296.656,30.9649,0),(1936,'Teleport: Anvilmar',0,-6133.84,383.79,395.54,0),(3561,'Teleport: Stormwind',0,-8913.23,554.633,93.7944,0),(3562,'Teleport: Ironforge',0,-4981.25,-881.542,501.66,0),(3563,'Teleport: Undercity',0,1586.48,239.562,-52.149,0),(3565,'Teleport: Darnassus',1,9951.52,2280.32,1341.39,0),(3566,'Teleport: Thunder Bluff',1,-1196.22,29.0941,176.949,0),(3567,'Teleport: Orgrimmar',1,1676.21,-4315.29,61.5293,0),(4996,'[PH] Teleport to Orgrimmar',1,1676.21,-4315.29,61.5293,0),(4997,'[PH] Teleport to Booty Bay',0,-14284.9,557.354,8.841,0),(4998,'[PH] Teleport to Grom\'Gol',0,-12437.4,212.47,31.29,0),(4999,'[PH] Teleport to Ratchet',1,-994.248,-3830.1,7,0),(5000,'[PH] Teleport to Undercity',0,1586.48,239.562,-52.149,0),(6348,'[PH] Teleport to Menethil Harbor',0,-3774.99,-742.22,8.037,0),(6349,'[PH] Teleport to Auberdine',1,6498.78,794.2,7.89,0),(6483,'[PH] Teleport to Felwood',1,6200,-1035,387,0),(6484,'[PH] Teleport to Balthule',1,7245,-652,35,0),(6719,'[PH] Teleport to Theramore',1,-3984.52,-4708.26,4.367,0),(8735,'[PH] Teleport to Blackfathom Deeps',1,4127.5,867.8,9.69,0),(9268,'Teleport to Darnassus - Event',1,9951.52,2280.32,1341.39,0),(11362,'Teleport to Gnomeregan',0,-5183.1,602.77,409.11,0),(11409,'Teleport to Booty Bay',0,-14319.3,442.7,22.94,0),(12510,'Teleport to Azshara Tower',1,3778.6,-4612.2,227.254,0),(12520,'Teleport from Azshara Tower',1,3648,-4702,122,0),(12885,'Teleport to Razelikh',0,-11235,-2834,158,0),(13044,'Teleport to Ground',0,-11072,-2859,11,0),(13142,'Teleport to Razelikh',0,-11235,-2834,158,0),(17334,'Portal Effect: Stormwind',0,-8913.23,554.633,93.7944,0),(17607,'Portal Effect: Ironforge',0,-4981.25,-881.542,501.66,0),(17608,'Portal Effect: Darnassus',1,9951.52,2280.32,1341.39,0),(17609,'Portal Effect: Orgrimmar',1,1676.21,-4315.29,61.5293,0),(17610,'Portal Effect: Thunder Bluff',1,-1196.22,29.0941,176.949,0),(17611,'Portal Effect: Undercity',0,1586.48,239.562,-52.149,0),(18960,'Teleport: Moonglade',1,7979,-2500,489,0),(21128,'Portal Effect: Maraudon',349,428,15,-112,0),(23442,'teleport trinket everlook',1,6721.44,-4659.09,720.893,0),(23453,'teleport trinket Gadgetzan',1,-7124.13,-3818.93,8.4107,0),(25649,'duskwitherspiretop',530,9338.34,-7809.24,136.568,0),(26566,'duskwitherspirebottom',530,9334.35,-7880.74,74.91,0),(26572,'FirewingUp',530,-2263.21,3112.64,136.349,0),(28147,'AtieshPorttoKara',0,-11112.9,-2005.89,49.3307,0),(30141,'FirewingUp2',530,-2260.33,3211.06,14.1116,0),(32268,'Exodar',530,-3987.29,-11846.6,-2.01903,0),(32270,'Silvermoon',530,9473.03,-7279.67,14.2285,0),(32271,'Exodar',530,-3987.29,-11846.6,-2.01903,0),(32272,'Silvermoon',530,9473.03,-7279.67,14.2285,0),(32568,'FirewingDown',530,-2259.65,3114.53,25.017,0),(32569,'FalconTowerUpper',530,-588.9,4070.8,93.8,0),(32571,'FalconTowerLower',530,-592.2,4070.2,143.3,0),(32572,'OrbOfTransLocSILVM',0,1805.82,334.01,70.3975,0),(33690,'Teleport to Shattarah',530,-1863.03,4998.05,-21.1847,0),(33691,'Portal Effect: Shattarah',530,-1863.03,4998.05,-21.1847,0),(33728,'Shattrath',530,-1863.03,4998.05,-21.1847,0),(35715,'Shattrath',530,-1863.03,4998.05,-21.1847,0),(35717,'Portal Effect: Shattarah',530,-1863.03,4998.05,-21.1847,0),(35718,'Shattrath',530,-1863.03,4998.05,-21.1847,0),(35730,'OrbOfTransLocUC',530,10021.3,-7014.89,49.7177,0),(36890,'teleport trinket area 52',530,3049.15,3686.12,142.387,0),(36941,'teleport trinket Toshley\'s Station',530,1907.43,5562.55,262.439,0),(37778,'Quest - Teleport: Caverns of Time',1,-8169.37,-4763.09,33.6819,0),(44089,'Portal Effect: Ironforge',0,-4981.25,-881.542,501.66,0),(44870,'Portal Effect: Sunwell Isle',530,13005.5,-6910.9,9.58423,0),(45038,'Legion Teleporter',530,894.396,2557.13,298.968,0),(45368,'SunsReachUp',530,12791.6,-6891.95,31.1053,0),(45371,'SunsReachDown',530,12782.5,-6879.06,23.0944,0),(49358,'Teleport: Stonard',0,-10435.9,-3260.51,20.1786,0),(49363,'Portal Effect: Stonard',0,-10435.9,-3260.51,20.1786,0),(49359,'Teleport: Theramore',1,-3678.44,-4522.46,10.2432,0),(49362,'Portal Effect: Theramore',1,-3678.44,-4522.46,10.2432,0),(53822,'Death Gate',609,2355.23,-5661.32,426.028,0);
/*!40000 ALTER TABLE `teleport_coords` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2010-11-08 19:15:09
