ALTER TABLE `g_groups_features` DROP `id_g_groups_features`;
ALTER TABLE `g_groups_features` ADD `isActive` TINYINT( 1 ) NOT NULL DEFAULT '1';
CREATE TABLE `pigstore`.`document_places` (
`id_place` TINYINT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY  DEFAULT '1',
`name` VARCHAR( 35 ) NOT NULL 
) ENGINE = MYISAM ;
ALTER TABLE `sale_documents` ADD `document_place` TINYINT NOT NULL AFTER `method_of_payment`
INSERT INTO `pigstore`.`document_places` (`id_place`, `name`) VALUES (NULL , 'Łódź');
ALTER TABLE `sale_documents` ADD `discount` DECIMAL( 3, 1 ) NOT NULL DEFAULT '0' AFTER `total`;

INSERT INTO `pigstore`.`store_documents` (`symbol` ,`contractor` ,`document_date` ,`store_date` ,`total` ,`store_result` ,`isActive` )
VALUES ('PZ/3/2011', '3', '2011-07-22', '2011-07-22', '1200', '1', '1'), 
	('PZ/4/2011', '2', '2011-07-23', '2011-07-23', '950', '1', '1');
ALTER TABLE `store_documents` CHANGE `contractor` `contractor` INT( 10 ) UNSIGNED NULL DEFAULT '0';

