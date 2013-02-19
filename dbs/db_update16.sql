
-- BOTH
USE pigstore;
ALTER TABLE `documents_kp` ADD `document_date` DATE NOT NULL AFTER `value`;
ALTER TABLE `documents_kp` ADD PRIMARY KEY ( `symbol` );

USE pigstore_magazyn2;
ALTER TABLE `documents_kp` ADD `document_date` DATE NOT NULL AFTER `value`;
ALTER TABLE `documents_kp` ADD PRIMARY KEY ( `symbol` );

-- FIRST
UPDATE `pigstore`.`documents_kp` SET `document_date` = '2011-05-31' WHERE `documents_kp`.`symbol` = 'KP/1/2011';
UPDATE `pigstore`.`documents_kp` SET `document_date` = '2011-07-16' WHERE `documents_kp`.`symbol` = 'KP/2/2011'; 
