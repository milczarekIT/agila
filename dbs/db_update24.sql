

-- BOTH

USE pigstore;
ALTER TABLE `cash_documents` ADD `owner` INT NOT NULL DEFAULT '1' AFTER `description`;
ALTER TABLE `documents_nk` ADD `owner` INT NOT NULL DEFAULT '1' AFTER `issue_person`;
ALTER TABLE `orders` ADD `owner` INT NOT NULL DEFAULT '1' AFTER `realized`;
ALTER TABLE `purchase_documents` ADD `owner` INT NOT NULL DEFAULT '1' AFTER `store_result`;
ALTER TABLE `sale_documents` ADD `owner` INT NOT NULL DEFAULT '1' AFTER `store_result`;
ALTER TABLE `store_documents` ADD `owner` INT NOT NULL DEFAULT '1' AFTER `store_result`;


USE pigstore_magazyn2;
ALTER TABLE `cash_documents` ADD `owner` INT NOT NULL DEFAULT '1' AFTER `description`;
ALTER TABLE `documents_nk` ADD `owner` INT NOT NULL DEFAULT '1' AFTER `issue_person`;
ALTER TABLE `orders` ADD `owner` INT NOT NULL DEFAULT '1' AFTER `realized`;
ALTER TABLE `purchase_documents` ADD `owner` INT NOT NULL DEFAULT '1' AFTER `store_result`;
ALTER TABLE `sale_documents` ADD `owner` INT NOT NULL DEFAULT '1' AFTER `store_result`;
ALTER TABLE `store_documents` ADD `owner` INT NOT NULL DEFAULT '1' AFTER `store_result`;
