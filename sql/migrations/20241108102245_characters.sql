DROP PROCEDURE IF EXISTS add_migration;
DELIMITER ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20241108102245');
IF v = 0 THEN
INSERT INTO `migrations` VALUES ('20241108102245');
-- Add your query below.

DROP TABLE IF EXISTS `worldstates`;
CREATE TABLE `worldstates` (
  `index` int(10) unsigned NOT NULL DEFAULT 0,
  `value` int(10) unsigned NOT NULL DEFAULT 0,
  PRIMARY KEY (`index`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Wareffort, Stranglethorn Vale Fishing , ...';

-- End of migration.
END IF;
END??
DELIMITER ;
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
