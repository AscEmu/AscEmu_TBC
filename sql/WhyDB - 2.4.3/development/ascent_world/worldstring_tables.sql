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
-- Table structure for table `worldstring_tables`
--

DROP TABLE IF EXISTS `worldstring_tables`;
CREATE TABLE `worldstring_tables` (
  `entry` int(11) NOT NULL AUTO_INCREMENT,
  `text` varchar(255) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`entry`)
) ENGINE=MyISAM AUTO_INCREMENT=81 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `worldstring_tables`
--

LOCK TABLES `worldstring_tables` WRITE;
/*!40000 ALTER TABLE `worldstring_tables` DISABLE KEYS */;
INSERT INTO `worldstring_tables` VALUES (1,'I would like to browse your goods.'),(2,'I seek '),(3,'mage'),(4,'shaman'),(5,'warrior'),(6,'paladin'),(7,'warlock'),(8,'hunter'),(9,'rogue'),(10,'druid'),(11,'priest'),(12,'training'),(13,'Train me in the ways of the beast.'),(14,'Give me a ride.'),(15,'I would like to make a bid.'),(16,'Make this inn your home.'),(17,'I would like to check my deposit box.'),(18,'Bring me back to life.'),(19,'How do I create a guild/arena team?'),(20,'I want to create a guild crest.'),(21,'I would like to go to the battleground.'),(22,'I would like to reset my talents.'),(23,'I wish to untrain my pet.'),(24,'I understand, continue.'),(25,'Yes, please do.'),(26,'This instance is unavailable.'),(27,'You must have The Burning Crusade Expansion to access this content.'),(28,'Heroic mode unavailable for this instance.'),(29,'You must be in a raid group to pass through here.'),(30,'You do not have the required attunement to pass through here.'),(31,'You must be at least level %u to pass through here.'),(32,'You must be in a party to pass through here.'),(33,'You must be level 70 to enter heroic mode.'),(34,'-'),(35,'You must have the item, `%s` to pass through here.'),(36,'You must have the item, UNKNOWN to pass through here.'),(37,'What can I teach you, $N?'),(38,'Alterac Valley'),(39,'Warsong Gulch'),(40,'Arathi Basin'),(41,'Arena 2v2'),(42,'Arena 3v3'),(43,'Arena 5v5'),(44,'Eye of the Storm'),(45,'Unknown Battleground'),(46,'One minute until the battle for %s begins!'),(47,'Thirty seconds until the battle for %s begins!'),(48,'Fifteen seconds until the battle for %s begins!'),(49,'The battle for %s has begun!'),(50,'Arena'),(51,'You have tried to join an invalid instance id.'),(52,'Your queue on battleground instance id %u is no longer valid. Reason: Instance Deleted.'),(53,'You cannot join this battleground as it has already ended.'),(54,'Your queue on battleground instance %u is no longer valid, the instance no longer exists.'),(55,'Sorry, raid groups joining battlegrounds are currently unsupported.'),(56,'You must be the party leader to add a group to an arena.'),(57,'You must be in a team to join rated arena.'),(58,'You have too many players in your party to join this type of arena.'),(59,'Sorry, some of your party members are not level 70.'),(60,'One or more of your party members are already queued or inside a battleground.'),(61,'One or more of your party members are not members of your team.'),(62,'Welcome to'),(63,'Horde'),(64,'Alliance'),(65,'[ |cff00ccffAttention|r ] Welcome! A new challenger (|cff00ff00{%d}|r - |cffff0000%s|r) has arrived and joined into |cffff0000%s|r,their force has already been increased.'),(66,'This instance is scheduled to reset on'),(67,'Auto loot passing is now %s'),(68,'On'),(69,'Off'),(70,'Hey there, $N. How can I help you?'),(71,'You are already in an arena team.'),(72,'That name is already in use.'),(73,'You already have an arena charter.'),(74,'A guild with that name already exists.'),(75,'You already have a guild charter.'),(76,'Item not found.'),(77,'Target is of the wrong faction.'),(78,'Target player cannot sign your charter for one or more reasons.'),(79,'You have already signed that charter.'),(80,'You don\'t have the required amount of signatures to turn in this petition.');
/*!40000 ALTER TABLE `worldstring_tables` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2010-11-08 19:15:10
