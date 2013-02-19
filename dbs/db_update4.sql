ALTER TABLE `documents_positions` DROP `tax_value`;
ALTER TABLE `documents_positions` DROP `tax_letter`;
ALTER TABLE `documents_positions` ADD `tax_id` SMALLINT( 5 ) UNSIGNED NOT NULL DEFAULT '1';
ALTER TABLE `sale_documents` ADD `isActive` TINYINT( 1 ) NOT NULL DEFAULT '1';
ALTER TABLE `sale_documents` ADD `store_result` TINYINT( 1 ) NOT NULL DEFAULT '1' AFTER `total`;
ALTER TABLE `store_documents` ADD `store_result` TINYINT( 1 ) NOT NULL DEFAULT '1',
	ADD `isActive` TINYINT( 1 ) NOT NULL DEFAULT '1';
ALTER TABLE `sale_documents` ADD `paid` BOOLEAN NOT NULL DEFAULT '1' AFTER `total`;
ALTER TABLE `sources_of_mem` ADD `isActive` TINYINT( 1 ) NOT NULL DEFAULT '1';
ALTER TABLE `documents_positions` DROP `id_doc_pos` ;
