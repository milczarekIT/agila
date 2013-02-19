
-- BOTH
USE `pigstore`;
ALTER TABLE `sale_documents` CHANGE `paid` `is_paid` TINYINT( 1 ) NOT NULL DEFAULT '1';
ALTER TABLE `sale_documents` ADD `paid` DECIMAL( 10, 2 ) NOT NULL AFTER `total`;

ALTER TABLE `purchase_documents` CHANGE `paid` `is_paid` TINYINT( 1 ) NOT NULL DEFAULT '1';

ALTER TABLE `purchase_documents` CHANGE `order` `order_symbol` VARCHAR( 16 ) CHARACTER SET utf8 COLLATE utf8_polish_ci NOT NULL;

ALTER TABLE `purchase_documents` CHANGE `sale_date` `purchase_date` DATE NOT NULL;

USE `pigstore_magazyn2`;

ALTER TABLE `sale_documents` CHANGE `paid` `is_paid` TINYINT( 1 ) NOT NULL DEFAULT '1';
ALTER TABLE `sale_documents` ADD `paid` DECIMAL( 10, 2 ) NOT NULL AFTER `total`;

ALTER TABLE `purchase_documents` CHANGE `paid` `is_paid` TINYINT( 1 ) NOT NULL DEFAULT '1';

ALTER TABLE `purchase_documents` CHANGE `order` `order_symbol` VARCHAR( 16 ) CHARACTER SET utf8 COLLATE utf8_polish_ci NOT NULL;

ALTER TABLE `purchase_documents` CHANGE `sale_date` `purchase_date` DATE NOT NULL;


-- FIRST


-- SECOND

-- CONF

USE `pigstore_conf`;
CREATE TABLE IF NOT EXISTS `owner` (
  `id_owner` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `name` text COLLATE utf8_polish_ci NOT NULL,
  `postcode` varchar(6) COLLATE utf8_polish_ci NOT NULL,
  `city` varchar(40) COLLATE utf8_polish_ci NOT NULL,
  `adress` varchar(60) COLLATE utf8_polish_ci NOT NULL,
  `nip` varchar(13) COLLATE utf8_polish_ci NOT NULL,
  `additional` varchar(60) COLLATE utf8_polish_ci NOT NULL,
  `account_bank_name` varchar(25) COLLATE utf8_polish_ci NOT NULL,
  `account_number` varchar(34) COLLATE utf8_polish_ci NOT NULL,
  `website` varchar(60) COLLATE utf8_polish_ci NOT NULL,
  `email` varchar(60) COLLATE utf8_polish_ci NOT NULL,
  `logo` varchar(180) COLLATE utf8_polish_ci NOT NULL,
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id_owner`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

INSERT INTO `pigstore_conf`.`owner` (`id_owner`, `name`, `postcode`, `city`, `adress`, `nip`, `additional`, `account_bank_name`, `account_number`, `website`, `email`, `logo`, `isActive`) VALUES (NULL, 'Blue Braces sp. z o.o.', '90-319', 'Łódź', 'Al. Politechniki 2', '834-652-10-05', 'KRS: 2320213131', 'mBank', '74 1040 2202 2132 3265 2132 3265', 'www.bluebraces.com', 'kontakt@bluebraces.com', '', '1');

ALTER TABLE `owner` ADD `phone1` VARCHAR( 20 ) NOT NULL AFTER `nip` ,
ADD `phone2` VARCHAR( 20 ) NOT NULL AFTER `phone1` ,
ADD `phone3` VARCHAR( 20 ) NOT NULL AFTER `phone2`;

UPDATE `pigstore_conf`.`owner` SET `phone1` = '801-777-777' WHERE `owner`.`id_owner` =1;
