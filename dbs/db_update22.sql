
-- BOTH
USE `pigstore`;
ALTER TABLE  `sale_documents` CHANGE  `order`  `order_symbol` VARCHAR( 16 ) CHARACTER SET utf8 COLLATE utf8_polish_ci NOT NULL;

ALTER TABLE  `documents_nk` ADD  `type` VARCHAR( 3 ) NOT NULL DEFAULT  'NK' FIRST;

UPDATE `documents` SET `family` = 'PURCHASE' WHERE `documents`.`type` = 'NK';

USE `pigstore_magazyn2`;
ALTER TABLE  `sale_documents` CHANGE  `order`  `order_symbol` VARCHAR( 16 ) CHARACTER SET utf8 COLLATE utf8_polish_ci NOT NULL;

ALTER TABLE  `documents_nk` ADD  `type` VARCHAR( 3 ) NOT NULL DEFAULT  'NK' FIRST;

UPDATE `documents` SET `family` = 'PURCHASE' WHERE `documents`.`type` = 'NK';

-- FIRST


-- SECOND
