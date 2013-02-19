
-- BOTH
USE pigstore;
ALTER TABLE `contractors` CHANGE `name` `name` TEXT CHARACTER SET utf8 COLLATE utf8_polish_ci NOT NULL;

CREATE TABLE IF NOT EXISTS `purchase_documents` (
  `symbol` varchar(16) COLLATE utf8_polish_ci NOT NULL,
  `contractor` int(10) NOT NULL,
  `method_of_payment` tinyint(3) unsigned NOT NULL,
  `document_place` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `document_date` date NOT NULL,
  `sale_date` date NOT NULL,
  `payment_date` date NOT NULL,
  `total` decimal(10,2) NOT NULL,
  `discount` decimal(4,2) NOT NULL DEFAULT '0.00',
  `receive_person` int(10) unsigned NOT NULL DEFAULT '0',
  `issue_person` int(10) unsigned NOT NULL DEFAULT '0',
  `paid` tinyint(1) NOT NULL DEFAULT '1',
  `store_result` tinyint(1) NOT NULL DEFAULT '1',
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`symbol`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

ALTER TABLE `sale_documents` ADD `type` VARCHAR( 3 ) NOT NULL FIRST;
UPDATE `sale_documents` SET TYPE = SUBSTRING( symbol, 1, 2 ) ;

ALTER TABLE `store_documents` ADD `type` VARCHAR( 3 ) NOT NULL FIRST;
UPDATE `store_documents` SET TYPE = SUBSTRING( symbol, 1, 2 ) ;

ALTER TABLE `purchase_documents` ADD `type` VARCHAR( 3 ) NOT NULL FIRST;
UPDATE `purchase_documents` SET TYPE = SUBSTRING( symbol, 1, 2 ) ;

ALTER TABLE `orders` ADD `type` VARCHAR( 3 ) NOT NULL FIRST;
UPDATE `orders` SET TYPE = SUBSTRING( symbol, 1, 2 ) ;

INSERT INTO `documents` (`type` ,`name` ,`numbering` ,`last_symbol` ,`after_text` ,`family` )
VALUES ('FZ', 'Faktura zakupu', 'FZ/#/YYYY', '', '', 'PURCHASE'),
('FZK', 'Faktura zakupu korygująca', 'FZK/#/YYYY', '', '', 'PURCHASE'),
('ZAL', 'Faktura VAT zaliczkowa', 'ZAL/#/YYYY', '', '', 'SALE'),
('RZL', 'Faktura VAT końcowa', 'RZL/#/YYYY', '', '', 'SALE');

CREATE TABLE `contractors_additional_ids` (
`id` TINYINT(3) UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY ,
`name` VARCHAR( 25 ) NOT NULL 
) ENGINE = MYISAM ;

INSERT INTO `contractors_additional_ids` (`id` ,`name` )
VALUES (NULL , 'REGON'), (NULL , 'PESEL'),
(NULL , 'Dowód osobisty'), (NULL , 'Paszport');

ALTER TABLE `contractors` CHANGE `regon` `additional_id_value` VARCHAR( 12 ) CHARACTER SET utf8 COLLATE utf8_polish_ci NOT NULL;

ALTER TABLE `contractors` ADD `additional_id_type` TINYINT( 3 ) UNSIGNED NOT NULL DEFAULT '1' AFTER `nip`;

INSERT INTO `documents` (`type` ,`name` ,`numbering` ,`last_symbol` ,`after_text` ,`family` )
VALUES ('OF', 'Oferta', 'OF/#/YYYY', '', '', 'OTHER'), 
('CN', 'Cennik', 'CN/#/YYYY', '', '', 'OTHER');

CREATE TABLE IF NOT EXISTS `cache_history` (
  `type` varchar(10) COLLATE utf8_polish_ci NOT NULL,
  `old` varchar(16) COLLATE utf8_polish_ci NOT NULL,
  `new` varchar(16) COLLATE utf8_polish_ci NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;


--
USE pigstore_magazyn2;
ALTER TABLE `contractors` CHANGE `name` `name` TEXT CHARACTER SET utf8 COLLATE utf8_polish_ci NOT NULL;

CREATE TABLE IF NOT EXISTS `purchase_documents` (
  `symbol` varchar(16) COLLATE utf8_polish_ci NOT NULL,
  `contractor` int(10) NOT NULL,
  `method_of_payment` tinyint(3) unsigned NOT NULL,
  `document_place` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `document_date` date NOT NULL,
  `sale_date` date NOT NULL,
  `payment_date` date NOT NULL,
  `total` decimal(10,2) NOT NULL,
  `discount` decimal(4,2) NOT NULL DEFAULT '0.00',
  `receive_person` int(10) unsigned NOT NULL DEFAULT '0',
  `issue_person` int(10) unsigned NOT NULL DEFAULT '0',
  `paid` tinyint(1) NOT NULL DEFAULT '1',
  `store_result` tinyint(1) NOT NULL DEFAULT '1',
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`symbol`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

ALTER TABLE `sale_documents` ADD `type` VARCHAR( 3 ) NOT NULL FIRST;
UPDATE `sale_documents` SET TYPE = SUBSTRING( symbol, 1, 2 ) ;

ALTER TABLE `store_documents` ADD `type` VARCHAR( 3 ) NOT NULL FIRST;
UPDATE `store_documents` SET TYPE = SUBSTRING( symbol, 1, 2 ) ;

ALTER TABLE `purchase_documents` ADD `type` VARCHAR( 3 ) NOT NULL FIRST;
UPDATE `purchase_documents` SET TYPE = SUBSTRING( symbol, 1, 2 ) ;

ALTER TABLE `orders` ADD `type` VARCHAR( 3 ) NOT NULL FIRST;
UPDATE `orders` SET TYPE = SUBSTRING( symbol, 1, 2 ) ;

INSERT INTO `documents` (`type` ,`name` ,`numbering` ,`last_symbol` ,`after_text` ,`family` )
VALUES ('FZ', 'Faktura zakupu', 'FZ/#/YYYY', '', '', 'PURCHASE'),
('FZK', 'Faktura zakupu korygująca', 'FZK/#/YYYY', '', '', 'PURCHASE'),
('ZAL', 'Faktura VAT zaliczkowa', 'ZAL/#/YYYY', '', '', 'SALE'),
('RZL', 'Faktura VAT końcowa', 'RZL/#/YYYY', '', '', 'SALE');

CREATE TABLE `contractors_additional_ids` (
`id` TINYINT(3) UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY ,
`name` VARCHAR( 25 ) NOT NULL 
) ENGINE = MYISAM ;

INSERT INTO `contractors_additional_ids` (`id` ,`name` )
VALUES (NULL , 'REGON'), (NULL , 'PESEL'),
(NULL , 'Dowód osobisty'), (NULL , 'Paszport');

ALTER TABLE `contractors` CHANGE `regon` `additional_id_value` VARCHAR( 12 ) CHARACTER SET utf8 COLLATE utf8_polish_ci NOT NULL;

ALTER TABLE `contractors` ADD `additional_id_type` TINYINT( 3 ) UNSIGNED NOT NULL DEFAULT '1' AFTER `nip`;

INSERT INTO `documents` (`type` ,`name` ,`numbering` ,`last_symbol` ,`after_text` ,`family` )
VALUES ('OF', 'Oferta', 'OF/#/YYYY', '', '', 'OTHER'), 
('CN', 'Cennik', 'CN/#/YYYY', '', '', 'OTHER');

CREATE TABLE IF NOT EXISTS `cache_history` (
  `type` varchar(10) COLLATE utf8_polish_ci NOT NULL,
  `old` varchar(16) COLLATE utf8_polish_ci NOT NULL,
  `new` varchar(16) COLLATE utf8_polish_ci NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;



-- FIRST
USE pigstore;
INSERT INTO `pigstore`.`departments` (`id_department` ,`name` ,`isActive` )
VALUES (NULL , 'Łódź', '1'), (NULL , 'Warszawa', '1');



-- SECOND
