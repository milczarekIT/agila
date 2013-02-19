
-- ALL

---1
USE pigstore;
ALTER TABLE `documents` ADD `last_symbol` VARCHAR( 16 ) NOT NULL AFTER `numbering`;

CREATE TABLE `documents_family` (
`id` TINYINT UNSIGNED NOT NULL AUTO_INCREMENT,
`name` VARCHAR( 25 ) NOT NULL ,
PRIMARY KEY ( `id` ) 
) ENGINE = MYISAM ;

INSERT INTO `documents_family` (`id` ,`name` )
VALUES (NULL , 'Dokumenty sprzedaży'), (NULL , 'Dokumenty magazynowe'), (NULL , 'Pozostałe dokumenty');

ALTER TABLE `documents` ADD `family` TINYINT UNSIGNED NOT NULL DEFAULT '1';

UPDATE `documents` SET `family` = '2' WHERE `documents`.`type` = 'PZ';
UPDATE `documents` SET `family` = '2' WHERE `documents`.`type` = 'WZ';
UPDATE `documents` SET `family` = '2' WHERE `documents`.`type` = 'PW';
UPDATE `documents` SET `family` = '2' WHERE `documents`.`type` = 'RW';
UPDATE `documents` SET `family` = '3' WHERE `documents`.`type` = 'KP';

ALTER TABLE `documents_family` CHANGE `id` `id` VARCHAR( 10 ) NOT NULL DEFAULT 'SALE';

UPDATE `documents_family` SET `id` = 'SALE' WHERE `documents_family`.`id` = '1';
UPDATE `documents_family` SET `id` = 'STORE' WHERE `documents_family`.`id` = '2';
UPDATE `documents_family` SET `id` = 'OTHER' WHERE `documents_family`.`id` = '3';

ALTER TABLE `documents` CHANGE `family` `family` VARCHAR( 10 ) NOT NULL DEFAULT 'SALE'

UPDATE `documents` SET `family` = 'SALE' WHERE `documents`.`type` = 'FV';
UPDATE `documents` SET `family` = 'STORE' WHERE `documents`.`type` = 'PZ';
UPDATE `documents` SET `family` = 'STORE' WHERE `documents`.`type` = 'WZ';
UPDATE `documents` SET `family` = 'STORE' WHERE `documents`.`type` = 'PW';
UPDATE `documents` SET `family` = 'STORE' WHERE `documents`.`type` = 'RW';
UPDATE `documents` SET `family` = 'OTHER' WHERE `documents`.`type` = 'KP';
UPDATE `documents` SET `family` = 'SALE' WHERE `documents`.`type` = 'FK';

UPDATE `documents` SET `name` = 'Przychód Zewnętrzny' WHERE `documents`.`type` = 'PZ';

--2
USE pigstore_magazyn2;
ALTER TABLE `documents` ADD `last_symbol` VARCHAR( 16 ) NOT NULL AFTER `numbering`;

CREATE TABLE `documents_family` (
`id` TINYINT UNSIGNED NOT NULL AUTO_INCREMENT,
`name` VARCHAR( 25 ) NOT NULL ,
PRIMARY KEY ( `id` ) 
) ENGINE = MYISAM ;

INSERT INTO `documents_family` (`id` ,`name` )
VALUES (NULL , 'Dokumenty sprzedaży'), (NULL , 'Dokumenty magazynowe'), (NULL , 'Pozostałe dokumenty');

ALTER TABLE `documents` ADD `family` TINYINT UNSIGNED NOT NULL DEFAULT '1';

UPDATE `documents` SET `family` = '2' WHERE `documents`.`type` = 'PZ';
UPDATE `documents` SET `family` = '2' WHERE `documents`.`type` = 'WZ';
UPDATE `documents` SET `family` = '2' WHERE `documents`.`type` = 'PW';
UPDATE `documents` SET `family` = '2' WHERE `documents`.`type` = 'RW';
UPDATE `documents` SET `family` = '3' WHERE `documents`.`type` = 'KP';

ALTER TABLE `documents_family` CHANGE `id` `id` VARCHAR( 10 ) NOT NULL DEFAULT 'SALE';

UPDATE `documents_family` SET `id` = 'SALE' WHERE `documents_family`.`id` = '1';
UPDATE `documents_family` SET `id` = 'STORE' WHERE `documents_family`.`id` = '2';
UPDATE `documents_family` SET `id` = 'OTHER' WHERE `documents_family`.`id` = '3';

ALTER TABLE `documents` CHANGE `family` `family` VARCHAR( 10 ) NOT NULL DEFAULT 'SALE';

UPDATE `documents` SET `family` = 'SALE' WHERE `documents`.`type` = 'FV';
UPDATE `documents` SET `family` = 'STORE' WHERE `documents`.`type` = 'PZ';
UPDATE `documents` SET `family` = 'STORE' WHERE `documents`.`type` = 'WZ';
UPDATE `documents` SET `family` = 'STORE' WHERE `documents`.`type` = 'PW';
UPDATE `documents` SET `family` = 'STORE' WHERE `documents`.`type` = 'RW';
UPDATE `documents` SET `family` = 'OTHER' WHERE `documents`.`type` = 'KP';
UPDATE `documents` SET `family` = 'SALE' WHERE `documents`.`type` = 'FK';

UPDATE `documents` SET `name` = 'Przychód Zewnętrzny' WHERE `documents`.`type` = 'PZ';
--/2

-- FIRST
UPDATE `pigstore`.`documents` SET `last_symbol` = 'FV/9/2011' WHERE `documents`.`type` = 'FV';
UPDATE `pigstore`.`documents` SET `last_symbol` = 'PZ/10/2011' WHERE `documents`.`type` = 'PZ';
UPDATE `pigstore`.`documents` SET `last_symbol` = 'WZ/1/2011' WHERE `documents`.`type` = 'WZ';
UPDATE `pigstore`.`documents` SET `last_symbol` = 'KP/2/2011' WHERE `documents`.`type` = 'KP';
UPDATE `pigstore`.`documents` SET `last_symbol` = 'FK/1/2011' WHERE `documents`.`type` = 'FK';

-- SECOND
UPDATE `pigstore_magazyn2`.`documents` SET `last_symbol` = 'FV/B/1/2011' WHERE `documents`.`type` = 'FV';
