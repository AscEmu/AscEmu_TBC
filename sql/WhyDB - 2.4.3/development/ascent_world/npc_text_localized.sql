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
-- Table structure for table `npc_text_localized`
--

DROP TABLE IF EXISTS `npc_text_localized`;
CREATE TABLE `npc_text_localized` (
  `entry` int(30) NOT NULL,
  `language_code` varchar(5) CHARACTER SET latin1 NOT NULL,
  `text0` varchar(200) CHARACTER SET latin1 NOT NULL,
  `text0_1` varchar(200) CHARACTER SET latin1 NOT NULL,
  `text1` varchar(200) CHARACTER SET latin1 NOT NULL,
  `text1_1` varchar(200) CHARACTER SET latin1 NOT NULL,
  `text2` varchar(200) CHARACTER SET latin1 NOT NULL,
  `text2_1` varchar(200) CHARACTER SET latin1 NOT NULL,
  `text3` varchar(200) CHARACTER SET latin1 NOT NULL,
  `text3_1` varchar(200) CHARACTER SET latin1 NOT NULL,
  `text4` varchar(200) CHARACTER SET latin1 NOT NULL,
  `text4_1` varchar(200) CHARACTER SET latin1 NOT NULL,
  `text5` varchar(200) CHARACTER SET latin1 NOT NULL,
  `text5_1` varchar(200) CHARACTER SET latin1 NOT NULL,
  `text6` varchar(200) CHARACTER SET latin1 NOT NULL,
  `text6_1` varchar(200) CHARACTER SET latin1 NOT NULL,
  `text7` varchar(200) CHARACTER SET latin1 NOT NULL,
  `text7_1` varchar(200) CHARACTER SET latin1 NOT NULL,
  PRIMARY KEY (`entry`,`language_code`),
  KEY `lol` (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Dumping data for table `npc_text_localized`
--

LOCK TABLES `npc_text_localized` WRITE;
/*!40000 ALTER TABLE `npc_text_localized` DISABLE KEYS */;
INSERT INTO `npc_text_localized` VALUES (1,'enGB','1','2','3','4','5','6','8','98','98','98','98','98','998','98','98','8888');
/*!40000 ALTER TABLE `npc_text_localized` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2010-11-08 19:15:08
