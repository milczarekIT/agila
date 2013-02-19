
-- BOTH
USE pigstore;
CREATE TABLE `departments` (
`id_department` SMALLINT( 5 ) UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY ,
`name` VARCHAR( 70 ) NOT NULL ,
`isActive` TINYINT( 1 ) UNSIGNED NOT NULL DEFAULT '1'
) ENGINE = MYISAM ;

INSERT INTO `documents_family` (`id` ,`name` )
VALUES ('ORDER', 'Zamówienia');


INSERT INTO `documents` (`type` ,`name` ,`numbering` ,`last_symbol` ,`after_text` ,`family`) 
VALUES ('ZK', 'Zamówienie od klienta', 'ZK/#/YYYY', '', '', 'ORDER'), 
('ZD', 'Zamówienie do dostawcy', 'ZD/#/YYYY', '', '', 'ORDER');

CREATE TABLE IF NOT EXISTS `orders` (
  `symbol` varchar(16) COLLATE utf8_polish_ci NOT NULL,
  `contractor` int(10) NOT NULL,
  `document_place` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `document_date` date NOT NULL,
  `realization_date` date NOT NULL,
  `total` decimal(10,2) NOT NULL,
  `discount` decimal(4,2) NOT NULL DEFAULT '0.00',
  `receive_person` int(10) unsigned NOT NULL DEFAULT '0',
  `issue_person` int(10) unsigned NOT NULL DEFAULT '0',
  `realized` TINYINT( 1 ) UNSIGNED NOT NULL DEFAULT '0',
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`symbol`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

USE pigstore_magazyn2;

CREATE TABLE `departments` (
`id_department` SMALLINT( 5 ) UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY ,
`name` VARCHAR( 70 ) NOT NULL ,
`isActive` TINYINT( 1 ) UNSIGNED NOT NULL DEFAULT '1'
) ENGINE = MYISAM ;

INSERT INTO `documents_family` (`id` ,`name` )
VALUES ('ORDER', 'Zamówienia');


INSERT INTO `documents` (`type` ,`name` ,`numbering` ,`last_symbol` ,`after_text` ,`family`) 
VALUES ('ZK', 'Zamówienie od klienta', 'ZK/#/YYYY', '', '', 'ORDER'), 
('ZD', 'Zamówienie do dostawcy', 'ZD/#/YYYY', '', '', 'ORDER');

CREATE TABLE IF NOT EXISTS `orders` (
  `symbol` varchar(16) COLLATE utf8_polish_ci NOT NULL,
  `contractor` int(10) NOT NULL,
  `document_place` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `document_date` date NOT NULL,
  `realization_date` date NOT NULL,
  `total` decimal(10,2) NOT NULL,
  `discount` decimal(4,2) NOT NULL DEFAULT '0.00',
  `receive_person` int(10) unsigned NOT NULL DEFAULT '0',
  `issue_person` int(10) unsigned NOT NULL DEFAULT '0',
  `realized` TINYINT( 1 ) UNSIGNED NOT NULL DEFAULT '0',
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`symbol`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

-- FIRST

USE pigstore;
INSERT INTO `orders` (`symbol` ,`contractor` ,`document_place` ,`document_date` ,`realization_date` ,`total` 
,`discount` ,`receive_person` ,`issue_person` ,`isActive` )
VALUES ('ZD/1/2011', '6', '1', '2011-10-10', '2011-10-10', '12450.00', '0.00', '0', '0', '1');

INSERT INTO `documents_positions` (`document` , `good` , `quantity` , `price_net` , `tax_id` ) 
VALUES ('ZD/1/2011', '4', '50', '202.44', '1');



-- SECOND
