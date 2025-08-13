DROP PROCEDURE IF EXISTS add_migration;
DELIMITER ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20250813174400');
IF v = 0 THEN
INSERT INTO `migrations` VALUES ('20250813174400');
-- Add your query below.


UPDATE mangos.spell_template SET `script_name` = 'spell_rogue_sap'
WHERE entry IN (6770, 2070, 11297);


-- End of migration.
END IF;
END??
DELIMITER ;
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;