SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for accounts
-- ----------------------------
DROP TABLE IF EXISTS `accounts`;
CREATE TABLE `accounts` (
  `acct` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT 'Unique ID',
  `login` varchar(32) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Login username',
  `password` varchar(32) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Login password',
  `encrypted_password` varchar(42) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `gm` varchar(32) COLLATE utf8_unicode_ci NOT NULL DEFAULT '' COMMENT 'Game permissions',
  `banned` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT 'Account Standing',
  `lastlogin` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00' COMMENT 'Last login timestamp',
  `lastip` varchar(16) COLLATE utf8_unicode_ci NOT NULL DEFAULT '' COMMENT 'Last remote address',
  `email` varchar(64) COLLATE utf8_unicode_ci NOT NULL DEFAULT '' COMMENT 'Contact e-mail address',
  `flags` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT 'Client flags',
  `forceLanguage` varchar(5) COLLATE utf8_unicode_ci NOT NULL DEFAULT 'enUS',
  `muted` int(30) NOT NULL DEFAULT '0',
  `banreason` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`acct`),
  UNIQUE KEY `a` (`login`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='Account Information';

-- ----------------------------
-- Table structure for ipbans
-- ----------------------------
DROP TABLE IF EXISTS `ipbans`;
CREATE TABLE `ipbans` (
  `ip` varchar(20) COLLATE utf8_unicode_ci NOT NULL,
  `expire` int(10) NOT NULL COMMENT 'Expiry time (s)',
  `banreason` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`ip`),
  UNIQUE KEY `a` (`ip`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='IPBanner';

-- ----------------------------
-- Records 
-- ----------------------------
