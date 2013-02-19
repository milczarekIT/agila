

-- ALL
---1
USE `pigstore`;
ALTER TABLE `documents_kp` ADD `receive_person` INT UNSIGNED NOT NULL AFTER `title` ,
ADD `issue_person` INT UNSIGNED NOT NULL AFTER `receive_person`;

ALTER TABLE `sale_documents` CHANGE `document_place` `document_place` TINYINT( 3 ) UNSIGNED NOT NULL DEFAULT '1';

ALTER TABLE `documents_kp` ADD `document_place` TINYINT UNSIGNED NOT NULL DEFAULT '1' AFTER `contractor`;

ALTER TABLE `store_documents` ADD `document_place` TINYINT UNSIGNED NOT NULL DEFAULT '1' AFTER `contractor`;

ALTER TABLE `documents_kp` ADD `isActive` TINYINT( 1 ) NOT NULL DEFAULT '1';

ALTER TABLE `contractors` ADD `representative` VARCHAR( 70 ) NOT NULL AFTER `source_of_mem` ,
ADD `is_company` TINYINT( 1 ) NOT NULL AFTER `representative`;
--
CREATE TABLE `documents` (
`type` VARCHAR( 3 ) NOT NULL ,
`name` VARCHAR( 30 ) NOT NULL ,
`numbering` VARCHAR( 18 ) NOT NULL ,
`after_text` TEXT NOT NULL ,
PRIMARY KEY ( `type` ) 
) ENGINE = MYISAM ;

INSERT INTO `documents` (`type` ,`name` ,`numbering` ,`after_text` )
VALUES ('FV', 'Faktura VAT', 'FV/#/YYYY', 'Dziękujemy za zakupy. Zapraszamy ponownie....'), ('PZ', 'Przychód Wewnętrzny', 'PZ/#/YYYY', '');

INSERT INTO `documents` (`type` ,`name` ,`numbering` ,`after_text` )
VALUES ('WZ', 'Wydanie Zewnętrzne', 'WZ/#/YYYY', ''), ('PW', 'Przychód Wewnętrzny', 'PW/#/YYYY', '');

INSERT INTO `documents` (`type` ,`name` ,`numbering` ,`after_text` )
VALUES ('RW', 'Rozchód Wewnętrzny', 'RW/#/YYYY', ''), ('KP', 'Kasa Przyjmie', 'KP/#/YYYY', '');

INSERT INTO `documents` (`type` ,`name` ,`numbering` ,`after_text` )
VALUES ('FK', 'Faktura korygująca', 'FK/#/YYYY', '');

DROP TABLE `document_numbering`, `document_text`;

ALTER TABLE `contractors` CHANGE `discount` `discount` DECIMAL( 4, 2 ) NOT NULL DEFAULT '0';
ALTER TABLE `sale_documents` CHANGE `discount` `discount` DECIMAL( 4, 2 ) NOT NULL DEFAULT '0.0';

CREATE TABLE `linked_documents` (
`base_document` VARCHAR( 16 ) NOT NULL ,
`linked_document` VARCHAR( 16 ) NOT NULL 
) ENGINE = MYISAM ;
---2
USE `pigstore_magazyn2`;
ALTER TABLE `documents_kp` ADD `receive_person` INT UNSIGNED NOT NULL AFTER `title` ,
ADD `issue_person` INT UNSIGNED NOT NULL AFTER `receive_person`;

ALTER TABLE `sale_documents` CHANGE `document_place` `document_place` TINYINT( 3 ) UNSIGNED NOT NULL DEFAULT '1';

ALTER TABLE `documents_kp` ADD `document_place` TINYINT UNSIGNED NOT NULL DEFAULT '1' AFTER `contractor`;

ALTER TABLE `store_documents` ADD `document_place` TINYINT UNSIGNED NOT NULL DEFAULT '1' AFTER `contractor`;

ALTER TABLE `documents_kp` ADD `isActive` TINYINT( 1 ) NOT NULL DEFAULT '1';

ALTER TABLE `contractors` ADD `representative` VARCHAR( 70 ) NOT NULL AFTER `source_of_mem` ,
ADD `is_company` TINYINT( 1 ) NOT NULL AFTER `representative`;
--
CREATE TABLE `documents` (
`type` VARCHAR( 3 ) NOT NULL ,
`name` VARCHAR( 30 ) NOT NULL ,
`numbering` VARCHAR( 18 ) NOT NULL ,
`after_text` TEXT NOT NULL ,
PRIMARY KEY ( `type` ) 
) ENGINE = MYISAM ;

INSERT INTO `documents` (`type` ,`name` ,`numbering` ,`after_text` )
VALUES ('FV', 'Faktura VAT', 'FV/#/YYYY', 'Dziękujemy za zakupy. Zapraszamy ponownie....'), ('PZ', 'Przychód Wewnętrzny', 'PZ/#/YYYY', '');

INSERT INTO `documents` (`type` ,`name` ,`numbering` ,`after_text` )
VALUES ('WZ', 'Wydanie Zewnętrzne', 'WZ/#/YYYY', ''), ('PW', 'Przychód Wewnętrzny', 'PW/#/YYYY', '');

INSERT INTO `documents` (`type` ,`name` ,`numbering` ,`after_text` )
VALUES ('RW', 'Rozchód Wewnętrzny', 'RW/#/YYYY', ''), ('KP', 'Kasa Przyjmie', 'KP/#/YYYY', '');

INSERT INTO `documents` (`type` ,`name` ,`numbering` ,`after_text` )
VALUES ('FK', 'Faktura korygująca', 'FK/#/YYYY', '');

DROP TABLE `document_numbering`, `document_text`;

ALTER TABLE `contractors` CHANGE `discount` `discount` DECIMAL( 4, 2 ) NOT NULL DEFAULT '0';
ALTER TABLE `sale_documents` CHANGE `discount` `discount` DECIMAL( 4, 2 ) NOT NULL DEFAULT '0.0';

CREATE TABLE `linked_documents` (
`base_document` VARCHAR( 16 ) NOT NULL ,
`linked_document` VARCHAR( 16 ) NOT NULL 
) ENGINE = MYISAM ;
------------------

-- FIRST
USE `pigstore`;
UPDATE `pigstore`.`documents_kp` SET `receive_person` = '7',
`issue_person` = '1' WHERE `documents_kp`.`symbol` = 'KP/1/2011' AND `documents_kp`.`contractor` =1 AND `documents_kp`.`document_placace` =1 AND CONCAT( `documents_kp`.`value` ) = '4919.76' AND `documents_kp`.`payment_date` = '2011-05-31' AND `documents_kp`.`title` = 'Wpłata za: FV/5/2011' AND `documents_kp`.`receive_person` =0 AND `documents_kp`.`issue_person` =0 AND `documents_kp`.`description` = '' LIMIT 1 ;

UPDATE `pigstore`.`documents_kp` SET `receive_person` = '9',
`issue_person` = '1' WHERE `documents_kp`.`symbol` = 'KP/2/2011' AND `documents_kp`.`contractor` =6 AND `documents_kp`.`document_placace` =1 AND CONCAT( `documents_kp`.`value` ) = '3100.00' AND `documents_kp`.`payment_date` = '2011-07-16' AND `documents_kp`.`title` = 'Wpłata za: FV/6/2011' AND `documents_kp`.`receive_person` =0 AND `documents_kp`.`issue_person` =0 AND `documents_kp`.`description` = '' LIMIT 1 ;

INSERT INTO `pigstore`.`sale_documents` (`symbol` ,`contractor` ,`method_of_payment` ,`document_place` ,`document_date` ,`sale_date` ,`payment_date` ,`total` , `discount` ,`receive_person` ,`issue_person` ,`paid` ,`store_result` ,`isActive` )
VALUES ('FK/1/2011', '3', '1', '2', '2011-08-12', '2011-07-16', '2011-07-16', '606.00', '1.0', '8', '1', '1', '1', '1');

INSERT INTO `pigstore`.`documents_positions` (`document`, `good`, `quantity`, `price_net`, `tax_id`) VALUES ('FK/1/2011', '2', '1', '100.00', '2'), ('FK/1/2011', '4', '2', '202.44', '1');

INSERT INTO `pigstore`.`linked_documents` (`base_document` ,`linked_document` )
VALUES ('FV/6/2011', 'FK/1/2011');

INSERT INTO `pigstore`.`linked_documents` (`base_document` ,`linked_document` )
VALUES ('FV/6/2011', 'KP/1/2011');

INSERT INTO `pigstore`.`linked_documents` (`base_document` ,`linked_document` )
VALUES ('FV/6/2011', 'WZ/1/2011');

INSERT INTO `pigstore`.`store_documents` (`symbol` ,`contractor` ,`document_place` ,`document_date` ,`store_date` ,`total` ,`receive_person` ,`issue_person` ,`transport` , `store_result` ,`isActive` ) VALUES ('WZ/1/2011', '3', '1', '2011-07-16', '2011-07-16', '855.00', '6', '1', '1', '1', '1');


-- SECOND



