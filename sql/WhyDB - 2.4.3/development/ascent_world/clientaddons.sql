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
-- Table structure for table `clientaddons`
--

DROP TABLE IF EXISTS `clientaddons`;
CREATE TABLE `clientaddons` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(50) CHARACTER SET utf8 COLLATE utf8_unicode_ci DEFAULT NULL,
  `crc` bigint(20) unsigned DEFAULT NULL,
  `banned` int(10) unsigned NOT NULL DEFAULT '0',
  `showinlist` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `a` (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=153 DEFAULT CHARSET=latin1 COMMENT='Client Addons';

--
-- Dumping data for table `clientaddons`
--

LOCK TABLES `clientaddons` WRITE;
/*!40000 ALTER TABLE `clientaddons` DISABLE KEYS */;
INSERT INTO `clientaddons` VALUES (1,'Blizzard_AuctionUI',345757989377,0,0),(3,'Blizzard_BattlefieldMinimap',0,0,0),(4,'Blizzard_BindingUI',0,0,0),(5,'Blizzard_CraftUI',0,0,0),(6,'Blizzard_InspectUI',0,0,0),(7,'Blizzard_MacroUI',0,0,0),(8,'Blizzard_RaidUI',0,0,0),(9,'Blizzard_TalentUI',0,0,0),(10,'Blizzard_TradeSkillUI',0,0,0),(11,'Blizzard_TrainerUI',0,0,0),(12,'Chronos',65934531841,0,1),(13,'FriendsList',0,0,1),(14,'Merchant',99303299329,0,1),(15,'PetSystem',0,0,1),(16,'Rivera_Auction',0,1,1),(17,'Rivera_Mail',65934531841,1,1),(18,'SpiritHonor',0,1,1),(19,'StatSystem',0,1,1),(20,'Tame',99303299329,1,1),(21,'myAddOns',65934531841,1,1),(23,'Blizzard_GMSurveyUI',326895103233,0,1),(24,'ard_AuctionUI',326895103233,0,1),(25,'Sea',0,0,1),(26,'Thottbot',0,0,1),(27,'!ImprovedErrorFrame',0,0,1),(28,'AllInOneInventory',0,0,1),(29,'AltInvite',0,0,1),(30,'ArcaneBar',0,0,1),(31,'ArcanePartyBars',0,0,1),(32,'Archaeologist',0,0,1),(33,'AssistMe',0,0,1),(34,'Atlas',0,0,1),(35,'AutoBindOnPickup',0,0,1),(36,'BarOptions',0,0,1),(37,'BetterItemCount',0,0,1),(38,'BetterKeyBinding',0,0,1),(39,'BuffOptions',0,0,1),(40,'CastOptions',0,0,1),(41,'CastTime',0,0,1),(42,'CensusPlus',0,0,1),(43,'ChannelManager',0,0,1),(44,'CharactersViewer',0,0,1),(45,'ChatScroll',0,0,1),(46,'ChatTimeStamps',0,0,1),(47,'Clock',0,0,1),(48,'CombatCaller',0,0,1),(49,'CombatStats',0,0,1),(50,'CooldownCount',0,0,1),(51,'DamageMeters',0,0,1),(52,'DivineBlessing',0,0,1),(53,'Earth',0,0,1),(54,'EasyMail',0,0,1),(55,'EquipCompare',0,0,1),(56,'FeralSkills',0,0,1),(57,'FreeBagSlots',0,0,1),(58,'FriendsFacts',0,0,1),(59,'Gymnast',0,0,1),(60,'IsMounted',0,0,1),(61,'Khaos',0,0,1),(62,'Libram',0,0,1),(63,'LookLock',0,0,1),(64,'MCom',0,0,1),(65,'MapNotes',0,0,1),(66,'Meteorologist',0,0,1),(67,'MiniGames',0,0,1),(68,'MinimapZoom',0,0,1),(69,'MobHealth',0,0,1),(70,'MobInfo2',0,0,1),(71,'MobileFrames',0,0,1),(72,'MobileMinimapButtons',0,0,1),(73,'Modifier2Sell',0,0,1),(74,'MonitorStatus',0,0,1),(75,'Notepad',0,0,1),(76,'PartyQuests',0,0,1),(77,'PopBar',0,0,1),(78,'QuestLogLevelPatch',0,0,1),(79,'QuickLoot',0,0,1),(80,'RaidMinion',0,0,1),(81,'ReagentHelper',0,0,1),(82,'ReloadUI',0,0,1),(83,'RogueHelper',0,0,1),(84,'ShardTracker',0,0,1),(85,'Sky',0,0,1),(86,'SocialMods',0,0,1),(87,'StupidMount2',0,0,1),(88,'TackleBox',0,0,1),(89,'TellTrack',0,0,1),(90,'TooltipsKhaos',0,0,1),(91,'TrackerToggle',0,0,1),(92,'VisibilityOptions',0,0,1),(93,'WorldMapInfo',0,0,1),(94,'sct',0,0,1),(95,'DiscordActionBars',0,0,1),(96,'DiscordActionBarsOptions',0,0,1),(97,'DiscordArt',0,0,1),(98,'DiscordArtOptions',0,0,1),(99,'DiscordLibrary',0,0,1),(100,'DiscordUnitFrames',0,0,1),(101,'DiscordUnitFramesOptions',0,0,1),(102,'AvailableOnly',0,0,1),(103,'Backdrop',0,0,1),(104,'CCWatch',0,0,1),(105,'CT_RABossMods',0,0,1),(106,'CT_RaidAssist',0,0,1),(107,'Carnival_EnemyCastBar',0,0,1),(108,'CleanMinimap',0,0,1),(109,'Confab',0,0,1),(110,'Decursive',0,0,1),(111,'DefendYourself',0,0,1),(112,'EnchanterAdShrinker',0,0,1),(113,'FlightTime',0,0,1),(114,'Gatherer',0,0,1),(115,'LS_Chat',0,0,1),(116,'MetaMap',0,0,1),(117,'MetaMapFWM',0,0,1),(118,'MoveAnything',0,0,1),(119,'NotesUNeed',0,0,1),(120,'QuestLevels',0,0,1),(121,'QuickMountEquip',0,0,1),(122,'SelfCast',0,0,1),(123,'SimpleMail',0,0,1),(124,'SimpleTip',0,0,1),(125,'Slash_GM',0,0,1),(126,'SuperInspect',0,0,1),(127,'SuperInspect_UI',0,0,1),(128,'Titan',0,0,1),(129,'TitanAmmo',0,0,1),(130,'TitanBag',0,0,1),(131,'TitanClock',0,0,1),(132,'TitanCoords',0,0,1),(133,'TitanHonorPlus',0,0,1),(134,'TitanItemBonuses',0,0,1),(135,'TitanLootType',0,0,1),(136,'TitanMoney',0,0,1),(137,'TitanPerformance',0,0,1),(138,'TitanRegen',0,0,1),(139,'TitanRepair',0,0,1),(140,'TitanRider',0,0,1),(141,'TitanSpeed',0,0,1),(142,'TitanStanceSets',0,0,1),(143,'TitanXP',0,0,1),(144,'TooltipsBase',0,0,1),(145,'TrinketMenu',0,0,1),(146,'UUIVersion',0,0,1),(147,'UltimateUI',0,0,1),(148,'WatchTower',0,1,1),(149,'whopinged',0,1,1),(150,'GPS',0,0,1),(151,'MobTalk',1021028909313,0,1),(152,'ToolBoxGM',0,0,1);
/*!40000 ALTER TABLE `clientaddons` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2010-11-08 19:15:03
