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
-- Table structure for table `spell_effects_override`
--

DROP TABLE IF EXISTS `spell_effects_override`;
CREATE TABLE `spell_effects_override` (
  `spellId` int(30) NOT NULL DEFAULT '0',
  `EffectID` int(30) NOT NULL,
  `Disable` int(30) NOT NULL,
  `Effect` int(30) NOT NULL DEFAULT '0',
  `BasePoints` int(30) NOT NULL DEFAULT '0',
  `ApplyAuraName` int(30) NOT NULL DEFAULT '0',
  `SpellGroupRelation` int(30) NOT NULL DEFAULT '0',
  `MiscValue` int(30) NOT NULL DEFAULT '0',
  `TriggerSpell` int(30) NOT NULL DEFAULT '0',
  `ImplicitTargetA` int(30) NOT NULL DEFAULT '0',
  `ImplicitTargetB` int(30) NOT NULL DEFAULT '0',
  PRIMARY KEY (`spellId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `spell_effects_override`
--

LOCK TABLES `spell_effects_override` WRITE;
/*!40000 ALTER TABLE `spell_effects_override` DISABLE KEYS */;
/*!40000 ALTER TABLE `spell_effects_override` ENABLE KEYS */;
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
