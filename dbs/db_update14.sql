
-- BOTH

---1
USE pigstore;
INSERT INTO `documents` ( `type` , `name` , `numbering` , `last_symbol` , `after_text` ,  `family`  ) 
VALUES ('FMP', 'Faktura VAT-MP', 'FMP/#/YYYY', '', '', 'SALE'),
('PRO', 'Faktura proforma', 'PRO/#/YYYY', '', '', 'SALE'),
('PA', 'Paragon', 'PA/#/YYYY', '', '', 'SALE'), 
('PI', 'Paragon imienny', 'PI/#/YYYY', '', '', 'SALE'),
('NK', 'Nota Korygująca', 'NK/#/YYYY', '', '', 'OTHER');

CREATE TABLE `documents_nk` (
`symbol` VARCHAR( 16 ) NOT NULL ,
`document_date` DATE NOT NULL ,
`issuer` INT UNSIGNED NOT NULL ,
`receiver` INT UNSIGNED NOT NULL ,
`invoice_symbol` VARCHAR( 16 ) NOT NULL ,
`invoice_date` DATE NOT NULL ,
`corrected_content` TEXT NOT NULL ,
`correct_content` TEXT NOT NULL ,
PRIMARY KEY ( `symbol` ) 
) ENGINE = MYISAM ;

ALTER TABLE `documents_nk` ADD `document_place` TINYINT( 3 ) UNSIGNED NOT NULL DEFAULT '1',
ADD `receive_person` INT UNSIGNED NOT NULL DEFAULT '0',
ADD `issue_person` INT UNSIGNED NOT NULL DEFAULT '0',
ADD `isActive` TINYINT( 1 ) UNSIGNED NOT NULL DEFAULT '1';


---2
USE pigstore_magazyn2;
INSERT INTO `documents` ( `type` , `name` , `numbering` , `last_symbol` , `after_text` ,  `family`  ) 
VALUES ('FMP', 'Faktura VAT-MP', 'FMP/#/YYYY', '', '', 'SALE'),
('PRO', 'Faktura proforma', 'PRO/#/YYYY', '', '', 'SALE'),
('PA', 'Paragon', 'PA/#/YYYY', '', '', 'SALE'), 
('PI', 'Paragon imienny', 'PI/#/YYYY', '', '', 'SALE'),
('NK', 'Nota Korygująca', 'NK/#/YYYY', '', '', 'OTHER');

CREATE TABLE `documents_nk` (
`symbol` VARCHAR( 16 ) NOT NULL ,
`document_date` DATE NOT NULL ,
`issuer` INT UNSIGNED NOT NULL ,
`receiver` INT UNSIGNED NOT NULL ,
`invoice_symbol` VARCHAR( 16 ) NOT NULL ,
`invoice_date` DATE NOT NULL ,
`corrected_content` TEXT NOT NULL ,
`correct_content` TEXT NOT NULL ,
PRIMARY KEY ( `symbol` ) 
) ENGINE = MYISAM ;

ALTER TABLE `documents_nk` ADD `document_place` TINYINT( 3 ) UNSIGNED NOT NULL DEFAULT '1',
ADD `receive_person` INT UNSIGNED NOT NULL DEFAULT '0',
ADD `issue_person` INT UNSIGNED NOT NULL DEFAULT '0',
ADD `isActive` TINYINT( 1 ) UNSIGNED NOT NULL DEFAULT '1';


-- FIRST
USE pigstore;
INSERT INTO `pigstore`.`documents_nk` (`symbol`, `document_date`, `issuer`, `receiver`, `invoice_symbol`, `invoice_date`, `corrected_content`, `correct_content`) VALUES ('NK/1/2011', '2011-09-07', '3', '0', 'FV/8/2011', '2011-07-16', 'Kupała Adam
Warchlewo 144
40-200 Katowice	', 'Kupała Adam
Warchlewo 104
40-200 Katowice	');
UPDATE `pigstore`.`documents` SET `last_symbol` = 'NK/1/2011' WHERE `documents`.`type` = 'NK';

-- SECOND




