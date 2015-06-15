UPDATE `creature_waypoints` SET `waittime`='3000' WHERE (`spawnid`='125515') AND (`waypointid`='1');
UPDATE `creature_waypoints` SET `forwardemoteoneshot`='1', `forwardemoteid`='69' WHERE (`spawnid`='125515') AND (`waypointid`='1');
UPDATE `creature_waypoints` SET `waittime`='2000' WHERE (`spawnid`='125515') AND (`waypointid`='2');
UPDATE `creature_waypoints` SET `waittime`='5000', `forwardemoteoneshot`='1', `forwardemoteid`='69' WHERE (`spawnid`='125515') AND (`waypointid`='4')
INSERT INTO `ascemu_world`.`creature_waypoints` (`spawnid`, `waypointid`, `position_x`, `position_y`, `position_z`, `waittime`, `flags`, `forwardemoteoneshot`, `forwardemoteid`, `backwardemoteoneshot`, `backwardemoteid`, `forwardskinid`, `backwardskinid`) VALUES ('125515', '5', '1820.03', '803.97', '44.36', '0', '0', '0', '0', '0', '0', '0', '0');
INSERT INTO `ascemu_world`.`creature_waypoints` (`spawnid`, `waypointid`, `position_x`, `position_y`, `position_z`, `waittime`, `flags`, `forwardemoteoneshot`, `forwardemoteid`, `backwardemoteoneshot`, `backwardemoteid`, `forwardskinid`, `backwardskinid`) VALUES ('125515', '6', '1814.70', '804.16', '44.36', '0', '0', '0', '0', '0', '0', '0', '0');

UPDATE `world_db_version` SET `LastUpdate` = '2015-06-06_01_vh_sinclari_wp';