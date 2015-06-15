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
-- Table structure for table `spell_coef_override`
--

DROP TABLE IF EXISTS `spell_coef_override`;
CREATE TABLE `spell_coef_override` (
  `id` double DEFAULT NULL,
  `name` varchar(300) DEFAULT NULL,
  `Dspell_coef_override` float DEFAULT NULL,
  `OTspell_coef_override` float DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `spell_coef_override`
--

LOCK TABLES `spell_coef_override` WRITE;
/*!40000 ALTER TABLE `spell_coef_override` DISABLE KEYS */;
INSERT INTO `spell_coef_override` VALUES (17,'Power Word: Shield Rank 1',0.3,-1),(139,'Renew Rank 1',0,1),(543,'Fire Ward Rank 1',-1,0.3),(592,'Power Word: Shield Rank 2',0.3,-1),(600,'Power Word: Shield Rank 3',0.3,-1),(603,'Curse of Doom Rank 1',0,2),(980,'Curse of Agony Rank 1',0,1.2),(1014,'Curse of Agony Rank 2',0,1.2),(3747,'Power Word: Shield Rank 4',0.3,-1),(6065,'Power Word: Shield Rank 5',0.3,-1),(6066,'Power Word: Shield Rank 6',0.3,-1),(6074,'Renew Rank 2',0,1),(6075,'Renew Rank 3',0,1),(6076,'Renew Rank 4',0,1),(6077,'Renew Rank 5',0,1),(6078,'Renew Rank 6',0,1),(6143,'Frost Ward Rank 1',-1,0.3),(6217,'Curse of Agony Rank 3',0,1.2),(6229,'Shadow Ward Rank 1',-1,0.3),(8400,'Fireball Rank 5',1,0),(8401,'Fireball Rank 6',1,0),(8402,'Fireball Rank 7',1,0),(8457,'Fire Ward Rank 2',-1,0.3),(8458,'Fire Ward Rank 3',-1,0.3),(8461,'Frost Ward Rank 2',-1,0.3),(8462,'Frost Ward Rank 3',-1,0.3),(10148,'Fireball Rank 8',1,0),(10149,'Fireball Rank 9',1,0),(10150,'Fireball Rank 10',1,0),(10151,'Fireball Rank 11',1,0),(10177,'Frost Ward Rank 4',-1,0.3),(10223,'Fire Ward Rank 4',-1,0.3),(10225,'Fire Ward Rank 5',-1,0.3),(10898,'Power Word: Shield Rank 7',0.3,-1),(10899,'Power Word: Shield Rank 8',0.3,-1),(10900,'Power Word: Shield Rank 9',0.3,-1),(10901,'Power Word: Shield Rank 10',0.3,-1),(10927,'Renew Rank 7',0,1),(10928,'Renew Rank 8',0,1),(10929,'Renew Rank 9',0,1),(11426,'Ice Barrier Rank 1',-1,0.1),(11711,'Curse of Agony Rank 4',0,1.2),(11712,'Curse of Agony Rank 5',0,1.2),(11713,'Curse of Agony Rank 6',0,1.2),(11739,'Shadow Ward Rank 2',-1,0.3),(11740,'Shadow Ward Rank 3',-1,0.3),(13031,'Ice Barrier Rank 2',-1,0.1),(13032,'Ice Barrier Rank 3',-1,0.1),(13033,'Ice Barrier Rank 4',-1,0.1),(18265,'Siphon Life Rank 1',0,2),(18879,'Siphon Life Rank 2',0,2),(18880,'Siphon Life Rank 3',0,2),(18881,'Siphon Life Rank 4',0,2),(20287,'Seal of Righteousness Rank 2',0.1,0),(20288,'Seal of Righteousness Rank 3',0.1,0),(20289,'Seal of Righteousness Rank 4',0.1,0),(20290,'Seal of Righteousness Rank 5',0.1,0),(20291,'Seal of Righteousness Rank 6',0.1,0),(20292,'Seal of Righteousness Rank 7',0.1,0),(20293,'Seal of Righteousness Rank 8',0.1,0),(20424,'Seal of Command',0.2,0),(21084,'Seal of Righteousness Rank 1',0.1,0),(25217,'Power Word: Shield Rank 11',0.3,-1),(25218,'Power Word: Shield Rank 12',0.3,-1),(25221,'Renew Rank 11',0,1),(25306,'Fireball Rank 12',1,0),(25315,'Renew Rank 10',0,1),(25608,'Citrine Pendant of Golden Healing',0,0),(27070,'Fireball Rank 13',1,0),(27128,'Fire Ward Rank 6',-1,0.3),(27134,'Ice Barrier Rank 5',-1,0.1),(27155,'Seal of Righteousness Rank 9',0.1,0),(27218,'Curse of Agony Rank 7',0,1.2),(27264,'Siphon Life Rank 5',0,2),(28609,'Frost Ward Rank 5',-1,0.3),(28610,'Shadow Ward Rank 4',-1,0.3),(30455,'Ice Lance',0.1429,0),(30910,'Curse of Doom Rank 2',0,2),(30911,'Siphon Life Rank 6',0,2),(31024,'Living Ruby Pendant',0,0),(32796,'Frost Ward Rank 6',-1,0.3),(33405,'Ice Barrier Rank 6',-1,0.1),(33763,'Libebloom',0.4286,0.518),(38395,'Siphon Essence',0,0),(38692,'Fireball Rank 14',1,0);
/*!40000 ALTER TABLE `spell_coef_override` ENABLE KEYS */;
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
