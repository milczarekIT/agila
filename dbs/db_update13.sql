-- ALL
---1
USE pigstore;
INSERT INTO `people` (`id` ,`name` ) VALUES ('0', 'NULL');
UPDATE `people` SET `id` = '0' WHERE `people`.`name` ='NULL';
UPDATE `people` SET `name` = '' WHERE `id` =0;

ALTER TABLE `store_documents` CHANGE `receive_person` `receive_person` INT( 10 ) UNSIGNED NOT NULL DEFAULT '0',
CHANGE `issue_person` `issue_person` INT( 10 ) UNSIGNED NOT NULL DEFAULT '0';

ALTER TABLE `sale_documents` CHANGE `receive_person` `receive_person` INT( 10 ) UNSIGNED NOT NULL DEFAULT '0',
CHANGE `issue_person` `issue_person` INT( 10 ) UNSIGNED NOT NULL DEFAULT '0';

ALTER TABLE `contractors_phones` ADD `is_default` TINYINT( 1 ) NOT NULL DEFAULT '0';

---2
USE pigstore_magazyn2;
INSERT INTO `people` (`id` ,`name` ) VALUES ('0', 'NULL');
UPDATE `people` SET `id` = '0' WHERE `people`.`name` ='NULL';
UPDATE `people` SET `name` = '' WHERE `id` =0;

ALTER TABLE `store_documents` CHANGE `receive_person` `receive_person` INT( 10 ) UNSIGNED NOT NULL DEFAULT '0',
CHANGE `issue_person` `issue_person` INT( 10 ) UNSIGNED NOT NULL DEFAULT '0';

ALTER TABLE `sale_documents` CHANGE `receive_person` `receive_person` INT( 10 ) UNSIGNED NOT NULL DEFAULT '0',
CHANGE `issue_person` `issue_person` INT( 10 ) UNSIGNED NOT NULL DEFAULT '0';

ALTER TABLE `contractors_phones` ADD `is_default` TINYINT( 1 ) NOT NULL DEFAULT '0';

-- FIRST

INSERT INTO `pigstore`.`store_documents` (`symbol`, `contractor`, `document_place`, `document_date`, `total`, `receive_person`, `issue_person`, `transport` , `store_result` , `isActive` ) 
VALUES ('RW/1/2011', '0', '1', '2011-08-25', '620', '0', '1', '0', '1', '1');

INSERT INTO `pigstore`.`documents_positions` (`document` , `good` , `quantity` , `price_net` , `tax_id` )
VALUES ('RW/1/2011', '7', '2', '310', '1');

INSERT INTO `pigstore`.`store_documents` ( `symbol` , `contractor` , `document_place` , `document_date` , `store_date` , `total` , `receive_person` , `issue_person` , `transport` , `store_result` , `isActive`  )
VALUES ('PW/1/2011', '0', '1', '2011-08-25', NULL , '2100', '0', '1', '0', '1', '1' );

INSERT INTO `pigstore`.`documents_positions` (`document` , `good` , `quantity` , `price_net` , `tax_id`  )
VALUES ('PW/1/2011', '2', '2', '857.22', '1' );
