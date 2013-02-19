
-- BOTH
USE pigstore;
ALTER TABLE `store_documents` ADD `shipping` TINYINT UNSIGNED NOT NULL AFTER `transport` ,
ADD `waybill_number` VARCHAR( 15 ) NOT NULL AFTER `shipping`;

DELETE FROM `means_of_transport` WHERE `means_of_transport`.`id_transport` = 1;

USE pigstore_magazyn2;
ALTER TABLE `store_documents` ADD `shipping` TINYINT UNSIGNED NOT NULL AFTER `transport` ,
ADD `waybill_number` VARCHAR( 15 ) NOT NULL AFTER `shipping`;

DELETE FROM `means_of_transport` WHERE `means_of_transport`.`id_transport` = 1;



-- FIRST


-- SECOND

-- CONF

CREATE TABLE `pigstore_conf`.`users` (
`id` SMALLINT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY ,
`login` VARCHAR( 20 ) NOT NULL ,
`password` CHAR( 32 ) NOT NULL ,
`name` VARCHAR( 60 ) NOT NULL ,
`type` TINYINT UNSIGNED NOT NULL ,
`isActive` TINYINT( 1 ) UNSIGNED NOT NULL DEFAULT '1'
) ENGINE = MYISAM ;

INSERT INTO `pigstore_conf`.`users` (`id` , `login` ,  `password` , `name` , `type` , `isActive` )
VALUES (NULL , 'admin', '21232f297a57a5a743894a0e4a801fc3', 'Administrator', '1', '1'),
(NULL , 'test1', '5a105e8b9d40e1329780d62ea2265d8a', 'Testerski Tester1', '0', '1'), 
(NULL , 'test2', 'ad0234829205b9033196ba818f7a872b', 'Testerski Tester2', '0', '1');



