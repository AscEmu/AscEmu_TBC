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
-- Table structure for table `worldmap_info`
--

DROP TABLE IF EXISTS `worldmap_info`;
CREATE TABLE `worldmap_info` (
  `entry` int(10) unsigned NOT NULL DEFAULT '0',
  `screenid` int(10) unsigned DEFAULT '0',
  `type` int(10) unsigned DEFAULT '0',
  `maxplayers` int(10) unsigned DEFAULT '0',
  `minlevel` int(10) unsigned DEFAULT '1',
  `repopx` float DEFAULT '0',
  `repopy` float DEFAULT '0',
  `repopz` float DEFAULT '0',
  `repopentry` int(10) unsigned DEFAULT '0',
  `area_name` varchar(100) CHARACTER SET utf8 COLLATE utf8_unicode_ci DEFAULT '0',
  `flags` int(10) unsigned NOT NULL DEFAULT '0',
  `cooldown` int(10) unsigned NOT NULL DEFAULT '0',
  `lvl_mod_a` int(10) unsigned NOT NULL DEFAULT '0',
  `required_quest` int(10) unsigned NOT NULL DEFAULT '0',
  `required_item` int(10) unsigned NOT NULL DEFAULT '0',
  `heroic_keyid_1` int(30) NOT NULL DEFAULT '0',
  `heroic_keyid_2` int(30) NOT NULL DEFAULT '0',
  `viewingDistance` float NOT NULL DEFAULT '80',
  `required_checkpoint` int(30) NOT NULL DEFAULT '0',
  PRIMARY KEY (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='World System';

--
-- Dumping data for table `worldmap_info`
--

LOCK TABLES `worldmap_info` WRITE;
/*!40000 ALTER TABLE `worldmap_info` DISABLE KEYS */;
INSERT INTO `worldmap_info` VALUES (0,0,0,0,1,0,0,0,0,'Eastern Kingdoms',1,0,0,0,0,0,0,80,0),(1,1,0,0,1,0,0,0,1,'Kalimdor',1,0,0,0,0,0,0,80,0),(13,13,0,0,1,0,0,0,0,'Testing',1,0,0,0,0,0,0,80,0),(25,25,0,0,1,0,0,0,0,'Scott Test',1,0,0,0,0,0,0,80,0),(29,29,0,0,1,0,0,0,0,'CashTest',1,0,0,0,0,0,0,80,0),(30,30,2,80,1,628.53,-207.67,39.0523,0,'Alterac Valley',3,0,0,0,0,0,0,80,0),(33,204,2,5,14,-229.49,1576.35,78.8909,0,'Shadowfang Keep',3,7200,0,0,0,0,0,80,0),(34,34,2,5,15,-8769.86,842.181,89.8765,0,'The Stockades',3,7200,0,0,0,0,0,80,0),(35,194,2,5,68,0,0,0,0,'Stormwind Vault',3,0,0,0,0,0,0,800,0),(36,36,2,5,13,-11208.4,1673.85,24.6245,0,'The Deadmines',3,7200,0,0,0,0,0,80,0),(37,143,2,5,1,1154.43,-165.231,313.603,0,'Azshara Crater',3,0,0,0,0,0,0,80,0),(42,42,0,0,1,0,0,0,0,'Collins Test',1,0,0,0,0,0,0,80,0),(43,143,2,5,13,-753.596,-2212.78,21.5403,1,'Wailing Caverns',3,7200,0,0,0,0,0,80,0),(44,44,0,0,1,0,0,0,0,'<unused> Monastery',1,0,0,0,0,0,0,80,0),(47,188,2,5,19,-4456.7,-1655.99,86.1095,1,'Razorfen Kraul',3,7200,0,0,0,0,0,80,0),(48,196,2,5,19,4252.37,756.974,-23.0632,1,'Blackfathom Deeps',3,7200,0,0,0,0,0,80,0),(70,144,2,5,29,-6606.48,-3762.19,266.91,0,'Uldaman',3,7200,0,0,0,0,0,80,0),(90,193,2,5,23,-5081.82,719.549,260.554,0,'Gnomeregan',3,7200,0,0,0,0,0,80,0),(109,109,2,5,45,-10184.9,-3992.84,-109.194,0,'The Sunken Temple',3,7200,0,0,0,0,0,80,0),(129,145,2,5,30,-4666.52,-2536.82,86.9671,1,'Razorfen Downs',3,7200,0,0,0,0,0,80,0),(169,169,0,0,1,-2128.12,-1005.89,132.213,169,'EmeraldDream',1,0,0,0,0,0,0,800,0),(189,42,2,5,25,2870.97,-759.845,160.333,0,'The Scarlet Monastery',3,7200,0,0,0,0,0,80,0),(209,146,2,5,35,-6773.49,-2889.77,15.1063,1,'Zul\'Farrak',3,7200,0,0,0,0,0,80,0),(229,189,1,10,55,-7518.19,-1239.13,287.243,0,'Blackrock Spire',3,120000,0,0,0,0,0,80,0),(230,103,2,5,48,-7176.63,-937.667,170.206,0,'Blackrock Depths',3,7200,0,0,0,0,0,80,0),(249,61,1,40,60,-4768.61,-3752.11,53.4317,1,'Onyxia\'s Lair',3,432000,0,0,16309,0,0,80,0),(269,269,4,5,68,-8770.08,-4171.7,-210.158,1,'Opening of the Dark Portal',9,7200,0,0,0,30635,0,80,0),(289,102,2,5,53,1282.05,-2548.73,85.3994,0,'Scholomance',3,7200,0,0,0,0,0,80,0),(309,161,1,20,51,-11916.8,-975.43,64.1502,0,'Zul\'Gurub',3,259200,0,0,0,0,0,80,0),(329,101,2,5,53,3237.46,-4060.6,112.01,0,'Stratholme',3,7200,0,0,0,0,0,80,0),(349,81,2,5,36,-1443.48,1973.36,85.491,1,'Maraudon',3,7200,0,0,0,0,0,80,0),(369,369,0,0,1,0,0,0,0,'Deeprun Tram',1,0,0,0,0,0,0,80,0),(389,195,2,5,8,1818.4,-4427.26,-10.4478,1,'Ragefire Chasm',3,7200,0,0,0,0,0,80,0),(409,192,1,40,58,-7510.31,-1041.63,180.912,0,'Molten Core',3,604800,0,7848,0,0,0,80,0),(429,82,2,5,50,-4278.76,1332.49,161.214,1,'Dire Maul',3,7200,0,0,0,0,0,80,0),(449,181,0,0,1,-8761.85,848.557,87.8052,0,'Alliance Military Barracks',1,0,0,0,0,0,0,80,0),(450,182,0,0,1,1643.36,-4233.6,56.1557,1,'Horde Military Barracks',1,0,0,0,0,0,0,80,0),(451,451,0,0,1,0,0,0,0,'Development Land',1,0,0,0,0,0,0,80,0),(469,141,1,40,60,-7655.63,-1221.93,287.798,0,'Blackwing Lair',3,604800,0,7761,0,0,0,80,0),(489,489,3,20,10,0,0,0,0,'Warsong Gulch',0,0,0,0,0,0,0,120,0),(509,184,1,20,60,-8134.79,1525.9,6.1904,1,'Ruins of Ahn\'Qiraj',3,259200,0,0,0,0,0,80,0),(529,529,3,30,20,0,0,0,0,'Arathi Basin ',0,0,0,0,0,0,0,120,0),(530,530,0,0,58,0,0,0,530,'Outlands',9,0,0,0,0,0,0,80,0),(531,531,1,40,60,-8231.33,2010.6,129.861,1,'Temple of Ahn\'Qiraj',3,604800,0,0,0,0,0,80,0),(532,532,1,10,70,-11112.9,-2005.89,49.3307,0,'Karazhan',3,604800,0,0,0,0,0,80,0),(533,533,1,40,60,3118.88,-3724.26,137.129,0,'Naxxramas',3,604800,0,9122,0,0,0,80,0),(534,534,1,25,70,-8178.25,-4184.74,-168.4,1,'The Battle for Mount Hyjal',3,604800,0,0,0,0,0,80,0),(540,540,4,5,67,-310.402,3082.47,-3.73108,530,'The Shattered Halls',3,7200,0,0,0,30637,30622,80,0),(542,542,4,5,58,-301.116,3161.07,31.7029,530,'The Blood Furnace',3,7200,9,0,0,30637,30622,80,0),(543,543,4,5,58,-362.679,3076.29,-15.0364,530,'Hellfire Ramparts',3,7200,10,0,0,30637,30622,80,0),(544,544,1,25,70,-313.679,3088.35,-116.502,530,'Magtheridon\'s Lair',3,604800,0,0,0,0,0,80,0),(545,545,4,5,62,816.87,6935.02,-80.5606,530,'The Steam Vaults',3,7200,0,0,0,30623,0,80,0),(546,546,4,5,60,777.089,6763.45,-72.0662,530,'The Underbog',3,7200,7,0,0,30623,0,80,0),(547,547,4,5,60,719.508,6999.34,-73.0743,530,'The Slave Pens',3,7200,8,0,0,30623,0,80,0),(548,548,1,25,70,783.103,6866.53,-65.9414,530,'Serpentshrine Cavern',3,604800,0,0,0,0,0,80,0),(550,550,1,25,70,3087.31,1373.79,184.643,530,'Tempest Keep',3,604800,0,0,0,0,0,80,0),(552,552,4,5,68,3312.09,1331.89,505.559,530,'The Arcatraz',3,7200,0,0,0,30634,0,80,0),(553,553,4,5,68,3365.84,1519.15,179.541,530,'The Botanica',3,7200,0,0,0,30634,0,80,0),(554,554,4,5,68,2863.4,1546.33,252.159,530,'The Mechanar',3,7200,0,0,0,30634,0,80,0),(555,555,4,5,65,-3637.51,4940.85,-101.047,530,'Shadow Labyrinth',3,7200,0,0,0,30633,0,80,0),(556,556,4,5,64,-3361.9,4666.01,-101.048,530,'Sethekk Halls',3,7200,3,0,0,30633,0,80,0),(557,557,4,5,62,-3083.3,4942.84,-101.048,530,'Mana-Tombs',3,7200,6,0,0,30633,0,80,0),(558,558,4,5,60,-3361.87,5220.98,-101.048,530,'Auchenai Crypts',3,7200,5,0,0,30633,0,80,0),(559,559,3,5,10,0,0,0,0,'Nagrand Arena',0,0,0,0,0,0,0,195,0),(560,560,4,5,66,-8343.69,-4057.43,207.924,1,'Old Hillsbrad Foothills',3,7200,0,0,0,30635,0,195,0),(562,562,3,10,10,0,0,0,0,'Blade\'s Edge Arena',0,0,0,0,0,0,0,120,0),(564,564,1,25,70,-3653.51,317.493,36.1671,530,'Black Temple',3,604800,0,0,0,0,0,80,0),(565,565,1,25,70,3549.8,5085.97,2.46332,530,'Gruul\'s Lair',3,604800,0,0,0,0,0,80,0),(566,566,3,30,61,0,0,0,0,'Eye of the Storm',0,0,0,0,0,0,0,120,0),(568,568,1,10,70,6852.58,-7994.12,192.37,530,'Zul\'Aman',3,259200,0,0,0,0,0,80,0),(572,572,3,5,10,0,0,0,0,'Ruins of Lordaeron',0,0,0,0,0,0,0,195,0),(580,580,1,25,70,12556,-6774.69,15.07,530,'Sunwell Plateau',3,259200,0,0,0,0,0,80,0),(582,582,0,0,1,0,0,0,0,'Transport: Ruttheran to Auberdine',1,0,0,0,0,0,0,80,0),(584,584,0,0,1,0,0,0,0,'Transport: Menethil to Theramore',1,0,0,0,0,0,0,80,0),(585,585,4,5,70,12885,-7335.97,65.48,530,'Magisters\' Terrace',3,7200,0,0,0,0,0,80,0),(586,586,0,0,1,0,0,0,0,'Transport: Exodar to Auberdine',1,0,0,0,0,0,0,80,0),(587,587,0,0,1,0,0,0,0,'Transport: Feathermoon Ferry',1,0,0,0,0,0,0,80,0),(588,589,0,0,1,0,0,0,0,'Transport: Menethil to Auberdine',1,0,0,0,0,0,0,80,0),(589,588,0,0,1,0,0,0,0,'Transport: Orgrimmar to GromGol',1,0,0,0,0,0,0,80,0),(590,590,0,0,1,0,0,0,0,'Transport: GromGol to Undercity',1,0,0,0,0,0,0,80,0),(591,591,0,0,1,0,0,0,0,'Transport: Undercity to Orgrimmar',1,0,0,0,0,0,0,80,0),(593,593,0,0,1,0,0,0,0,'Transport: Booty Bay to Ratchet',1,0,0,0,0,0,0,80,0),(598,598,0,0,0,0,0,0,0,'Sunwell Fix (Unused)',0,0,0,0,0,0,0,195,0);
/*!40000 ALTER TABLE `worldmap_info` ENABLE KEYS */;
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
