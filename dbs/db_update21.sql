
-- BOTH
---
USE pigstore;
ALTER TABLE `store_documents` ADD `department` SMALLINT UNSIGNED NOT NULL AFTER `issue_person`;

UPDATE `store_documents` SET `department` = '1' WHERE `type` = 'PW' OR type='RW';

ALTER TABLE `sale_documents` ADD `order` VARCHAR( 16 ) NOT NULL AFTER `discount`;
ALTER TABLE `purchase_documents` ADD `order` VARCHAR( 16 ) NOT NULL AFTER `discount`;

ALTER TABLE `purchase_documents` ADD `purchase_document` VARCHAR( 16 ) NOT NULL AFTER `order`;

INSERT INTO `documents_family` (`id` ,`name` )
VALUES ('CASH', 'Dokumenty kasowe');

UPDATE `documents` SET `family` = 'CASH' WHERE `type` = 'KP';

INSERT INTO `documents` (`type` , `name` , `numbering` , `last_symbol` , `after_text` , `family`  )
VALUES ('KW', 'Kasa Wyda', 'KW/#/2011', '', '', 'CASH');

DROP TABLE `documents_kp`;

CREATE TABLE IF NOT EXISTS `cash_documents` (
  `symbol` varchar(16) COLLATE utf8_polish_ci NOT NULL,
  `contractor` int(10) unsigned NOT NULL,
  `document_place` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `value` decimal(10,2) NOT NULL,
  `document_date` date NOT NULL,
  `payment_date` date NOT NULL,
  `title` varchar(255) COLLATE utf8_polish_ci NOT NULL,
  `receive_person` int(10) unsigned NOT NULL,
  `issue_person` int(10) unsigned NOT NULL,
  `description` text COLLATE utf8_polish_ci NOT NULL,
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`symbol`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

ALTER TABLE `cash_documents` ADD `document` VARCHAR( 16 ) NOT NULL AFTER `payment_date`;

---
USE pigstore_magazyn2;
ALTER TABLE `store_documents` ADD `department` SMALLINT UNSIGNED NOT NULL AFTER `issue_person`;

UPDATE `store_documents` SET `department` = '1' WHERE `type` = 'PW' OR type='RW';

ALTER TABLE `sale_documents` ADD `order` VARCHAR( 16 ) NOT NULL AFTER `discount`;
ALTER TABLE `purchase_documents` ADD `order` VARCHAR( 16 ) NOT NULL AFTER `discount`;

ALTER TABLE `purchase_documents` ADD `purchase_document` VARCHAR( 16 ) NOT NULL AFTER `order`;

INSERT INTO `documents_family` (`id` ,`name` )
VALUES ('CASH', 'Dokumenty kasowe');

UPDATE `documents` SET `family` = 'CASH' WHERE `type` = 'KP';

INSERT INTO `documents` (`type` , `name` , `numbering` , `last_symbol` , `after_text` , `family`  )
VALUES ('KW', 'Kasa Wyda', 'KW/#/2011', '', '', 'CASH');

DROP TABLE `documents_kp`;

CREATE TABLE IF NOT EXISTS `cash_documents` (
  `symbol` varchar(16) COLLATE utf8_polish_ci NOT NULL,
  `contractor` int(10) unsigned NOT NULL,
  `document_place` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `value` decimal(10,2) NOT NULL,
  `document_date` date NOT NULL,
  `payment_date` date NOT NULL,
  `title` varchar(255) COLLATE utf8_polish_ci NOT NULL,
  `receive_person` int(10) unsigned NOT NULL,
  `issue_person` int(10) unsigned NOT NULL,
  `description` text COLLATE utf8_polish_ci NOT NULL,
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`symbol`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

ALTER TABLE `cash_documents` ADD `document` VARCHAR( 16 ) NOT NULL AFTER `payment_date`;


--FIRST
USE pigstore;
UPDATE `store_documents` SET `transport` = '2' WHERE `type` = 'WZ';

INSERT INTO `cash_documents` (`symbol`, `contractor`, `document_place`, `value`, `document_date`, `payment_date`, `title`, `receive_person`, `issue_person`, `description`, `isActive`) VALUES
('KP/1/2011', 1, 1, '4919.76', '2011-05-31', '2011-05-31', 'Wpłata za: FV/5/2011', 7, 1, '', 1),
('KP/2/2011', 6, 1, '3100.00', '2011-07-16', '2011-07-16', 'Wpłata za: FV/6/2011', 9, 1, '', 1);

UPDATE `cash_documents` SET `document` = 'FV/5/2011' WHERE `symbol` = 'KP/1/2011';
UPDATE `cash_documents` SET `document` = 'FV/6/2011' WHERE `symbol` = 'KP/2/2011';


-- SECOND
