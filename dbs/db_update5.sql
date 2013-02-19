ALTER TABLE `taxes` ADD `active_in_app` TINYINT( 1 ) NOT NULL DEFAULT '1' AFTER `letter`;
ALTER TABLE `goods` CHANGE `price_a_net` `price_a_net` DECIMAL( 10, 2 ) NOT NULL ,
	CHANGE `price_a_gross` `price_a_gross` DECIMAL( 10, 2 ) NOT NULL;
ALTER TABLE `goods` CHANGE `price_b_net` `price_b_net` DECIMAL( 10,2 ) NOT NULL ,
	CHANGE `price_b_gross` `price_b_gross` DECIMAL( 10,2 ) NOT NULL;
ALTER TABLE `goods` CHANGE `price_c_net` `price_a_net` DECIMAL( 10,2 ) NOT NULL ,
	CHANGE `price_c_gross` `price_c_gross` DECIMAL( 10,2 ) NOT NULL;
ALTER TABLE `goods` CHANGE `price_mag_net` `price_mag_net` DECIMAL( 10,2 ) NOT NULL ,
	CHANGE `price_mag_gross` `price_mag_gross` DECIMAL( 10,2 ) NOT NULL;
ALTER TABLE `sale_documents` CHANGE `total` `total` DECIMAL( 10,2 ) NOT NULL;
ALTER TABLE `store_documents` CHANGE `total` `total` DECIMAL( 10,2 ) NOT NULL;
ALTER TABLE `documents_positions` CHANGE `price_net` `price_net` DECIMAL( 10,2 ) NOT NULL;
ALTER TABLE `features` ADD `isActive` TINYINT( 1 ) NOT NULL DEFAULT '1';
