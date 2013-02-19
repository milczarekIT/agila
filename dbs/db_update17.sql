
-- BOTH
USE pigstore;
UPDATE `goods_groups` SET `name` = 'Inne' WHERE `goods_groups`.`id_group` =1;
UPDATE `contractors_groups` SET `name` = 'Podstawowa' WHERE `contractors_groups`.`id_group` =1;

INSERT INTO `documents_family` (`id` ,`name` )
VALUES ('PURCHASE', 'Dokumenty zakupu');

INSERT INTO `documents` (`type` , `name` , `numbering` ,  `last_symbol` , `after_text` , `family` )
VALUES ( 'FM', 'Faktura VAT Marża', 'FM/#/YYYY', '', '', 'SALE' ),('RR', 'Faktura VAT RR', 'RR/#/YYYY', '', '', 'PURCHASE');

ALTER TABLE `contractors` ADD `type` TINYINT( 1 ) UNSIGNED NOT NULL DEFAULT '1' AFTER `contractor_group`;
UPDATE contractors SET type = 3 WHERE id_contractor > 20 AND id_contractor < 30; -- troche przykladowych dostawcow/odbiorcow
UPDATE contractors SET type = 2 WHERE id_contractor >= 30; -- przykladowi dostawcy

ALTER TABLE `goods` ADD `type` TINYINT( 1 ) UNSIGNED NOT NULL DEFAULT '1' AFTER `name`;

USE pigstore_magazyn2;
UPDATE `goods_groups` SET `name` = 'Inne' WHERE `goods_groups`.`id_group` =1;
UPDATE `contractors_groups` SET `name` = 'Podstawowa' WHERE `contractors_groups`.`id_group` =1;

INSERT INTO `documents_family` (`id` ,`name` )
VALUES ('PURCHASE', 'Dokumenty zakupu');

INSERT INTO `documents` (`type` , `name` , `numbering` ,  `last_symbol` , `after_text` , `family` )
VALUES ( 'FM', 'Faktura VAT Marża', 'FM/#/YYYY', '', '', 'SALE' ),('RR', 'Faktura VAT RR', 'RR/#/YYYY', '', '', 'PURCHASE');

ALTER TABLE `contractors` ADD `type` TINYINT( 1 ) UNSIGNED NOT NULL DEFAULT '1' AFTER `contractor_group`;
UPDATE contractors SET type = 3 WHERE id_contractor > 20 AND id_contractor < 30; -- troche przykladowych dostawcow/odbiorcow
UPDATE contractors SET type = 2 WHERE id_contractor >= 30; -- przykladowi dostawcy

ALTER TABLE `goods` ADD `type` TINYINT( 1 ) UNSIGNED NOT NULL DEFAULT '1' AFTER `name`;

-- FIRST


-- SECOND
