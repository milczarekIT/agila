USE `pigstore`;

CREATE TABLE `pigstore`.`means_of_transport` (
`id_transport` SMALLINT NOT NULL AUTO_INCREMENT PRIMARY KEY ,
`name` VARCHAR( 40 ) NOT NULL 
) ENGINE = MYISAM ;

INSERT INTO `pigstore`.`means_of_transport` (`id_transport` ,`name` )
VALUES (NULL , 'BRAK'), (NULL , 'Firma kurierska');

ALTER TABLE `means_of_transport` ADD `isActive` TINYINT( 1 ) NOT NULL DEFAULT '1';

CREATE TABLE `pigstore`.`people` (
`id` INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY ,
`name` VARCHAR( 70 ) NOT NULL 
) ENGINE = MYISAM ;

ALTER TABLE `store_documents` ADD `receive_person` INT UNSIGNED NOT NULL AFTER `total` ,
ADD `issue_person` INT UNSIGNED NOT NULL AFTER `receive_person`;

ALTER TABLE `store_documents` ADD `transport` SMALLINT NOT NULL DEFAULT '0' AFTER `issue_person`;

ALTER TABLE `sale_documents` ADD `receive_person` INT UNSIGNED NOT NULL AFTER `discount` ,
ADD `issue_person` INT UNSIGNED NOT NULL AFTER `receive_person`;

DROP TABLE `sale_documents`;
CREATE TABLE IF NOT EXISTS `sale_documents` (
  `symbol` varchar(16) COLLATE utf8_polish_ci NOT NULL,
  `contractor` int(10) unsigned NOT NULL,
  `method_of_payment` tinyint(3) unsigned NOT NULL,
  `document_place` tinyint(4) NOT NULL DEFAULT '1',
  `document_date` date NOT NULL,
  `sale_date` date NOT NULL,
  `payment_date` date NOT NULL,
  `total` decimal(10,2) NOT NULL,
  `discount` decimal(3,1) NOT NULL DEFAULT '0.0',
  `receive_person` int(10) unsigned NOT NULL,
  `issue_person` int(10) unsigned NOT NULL,
  `paid` tinyint(1) NOT NULL DEFAULT '1',
  `store_result` tinyint(1) NOT NULL DEFAULT '1',
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`symbol`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Zrzut danych tabeli `sale_documents`
--

INSERT INTO `sale_documents` (`symbol`, `contractor`, `method_of_payment`, `document_place`, `document_date`, `sale_date`, `payment_date`, `total`, `discount`, `receive_person`, `issue_person`, `paid`, `store_result`, `isActive`) VALUES
('FV/5/2011', 1, 2, 1, '2011-05-17', '2011-05-17', '2011-05-31', '4919.75', '2.0', 7, 1, 1, 1, 1),
('FV/6/2011', 3, 1, 1, '2011-07-16', '2011-07-16', '2011-07-16', '855.00', '2.5', 6, 1, 1, 1, 1),
('FV/7/2011', 2, 1, 1, '2011-07-16', '2011-07-16', '2011-07-16', '1700.00', '0.0', 5, 1, 1, 1, 1),
('FV/8/2011', 3, 1, 1, '2011-07-16', '2011-07-16', '2011-07-16', '8570.68', '1.0', 6, 1, 1, 1, 1),
('FV/9/2011', 3, 1, 2, '2011-07-16', '2011-07-16', '2011-07-16', '2581.77', '1.0', 8, 1, 1, 1, 1);

DROP TABLE `store_documents`;
CREATE TABLE IF NOT EXISTS `store_documents` (
  `symbol` varchar(16) COLLATE utf8_polish_ci NOT NULL,
  `contractor` int(10) unsigned DEFAULT '0',
  `document_date` date DEFAULT NULL,
  `store_date` date DEFAULT NULL,
  `total` decimal(10,2) NOT NULL,
  `receive_person` int(10) unsigned NOT NULL,
  `issue_person` int(10) unsigned NOT NULL,
  `transport` smallint(6) NOT NULL DEFAULT '0',
  `store_result` tinyint(1) NOT NULL DEFAULT '1',
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`symbol`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Zrzut danych tabeli `store_documents`
--

INSERT INTO `store_documents` (`symbol`, `contractor`, `document_date`, `store_date`, `total`, `receive_person`, `issue_person`, `transport`, `store_result`, `isActive`) VALUES
('PZ/3/2011', 3, '2011-07-22', '2011-07-22', '1200.00', 6, 1, 2, 1, 1),
('PZ/4/2011', 2, '2011-07-23', '2011-07-23', '950.00', 5, 1, 1, 1, 1),
('PZ/5/2011', 3, '2011-07-25', '2011-07-25', '1200.00', 5, 1, 2, 1, 1),
('PZ/6/2011', 3, '2011-07-25', '2011-07-25', '1200.00', 6, 1, 1, 1, 1),
('PZ/7/2011', 1, '2011-07-28', '2011-07-28', '104950.00', 4, 1, 1, 1, 1),
('PZ/8/2011', 1, '2011-08-05', '2011-08-05', '14585.40', 13, 12, 2, 1, 1);

INSERT INTO `people` (`id`, `name`) VALUES
(1, 'Michał Pietrzak'),
(2, 'Konrad Marczak'),
(3, 'Grzegorz Mularski'),
(4, 'Paweł Rolewski'),
(5, 'Solimo Katarzyna'),
(6, 'Kupała Adam'),
(7, 'Filip Kozakiewicz'),
(8, 'Milczarek Bartosz'),
(9, 'Pasikonik Mariusz'),
(10, 'Krzemiński Daniel'),
(11, 'Mariusz Kobiela'),
(12, 'Marek Pietrzak'),
(13, 'Konrad Mazur');

--------- MAG2
USE `pigstore_magazyn2`;

CREATE TABLE `pigstore_magazyn2`.`means_of_transport` (
`id_transport` SMALLINT NOT NULL AUTO_INCREMENT PRIMARY KEY ,
`name` VARCHAR( 40 ) NOT NULL 
) ENGINE = MYISAM ;

INSERT INTO `pigstore_magazyn2`.`means_of_transport` (`id_transport` ,`name` )
VALUES (NULL , 'BRAK');

ALTER TABLE `means_of_transport` ADD `isActive` TINYINT( 1 ) NOT NULL DEFAULT '1';

CREATE TABLE `pigstore_magazyn2`.`people` (
`id` INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY ,
`name` VARCHAR( 70 ) NOT NULL 
) ENGINE = MYISAM ;

ALTER TABLE `store_documents` ADD `receive_person` INT UNSIGNED NOT NULL AFTER `total` ,
ADD `issue_person` INT UNSIGNED NOT NULL AFTER `receive_person`;

ALTER TABLE `store_documents` ADD `transport` SMALLINT NOT NULL DEFAULT '0' AFTER `issue_person`;

ALTER TABLE `sale_documents` ADD `receive_person` INT UNSIGNED NOT NULL AFTER `discount` ,
ADD `issue_person` INT UNSIGNED NOT NULL AFTER `receive_person`;

INSERT INTO `people` (`id`, `name`) VALUES
(1, 'Marczak Marcin'),
(2, 'Jakiś Klient'),
(3, 'Adam Orzeszko');

DROP TABLE `sale_documents`; 
CREATE TABLE IF NOT EXISTS `sale_documents` (
  `symbol` varchar(16) COLLATE utf8_polish_ci NOT NULL,
  `contractor` int(10) unsigned NOT NULL,
  `method_of_payment` tinyint(3) unsigned NOT NULL,
  `document_place` tinyint(4) NOT NULL DEFAULT '1',
  `document_date` date NOT NULL,
  `sale_date` date NOT NULL,
  `payment_date` date NOT NULL,
  `total` decimal(10,2) NOT NULL,
  `discount` decimal(3,1) NOT NULL DEFAULT '0.0',
  `receive_person` int(10) unsigned NOT NULL,
  `issue_person` int(10) unsigned NOT NULL,
  `paid` tinyint(1) NOT NULL DEFAULT '1',
  `store_result` tinyint(1) NOT NULL DEFAULT '1',
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`symbol`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Zrzut danych tabeli `sale_documents`
--

INSERT INTO `sale_documents` (`symbol`, `contractor`, `method_of_payment`, `document_place`, `document_date`, `sale_date`, `payment_date`, `total`, `discount`, `receive_person`, `issue_person`, `paid`, `store_result`, `isActive`) VALUES
('FV/B/1/2011', 1, 1, 1, '2011-07-28', '2011-07-28', '2011-07-28', '103.95', '0.0', 3, 1, 1, 0, 1);
