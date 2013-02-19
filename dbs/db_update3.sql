ALTER TABLE contractors ADD isActive TINYINT(1) NOT NULL DEFAULT '1';
ALTER TABLE goods ADD isActive TINYINT(1) NOT NULL DEFAULT '1';
ALTER TABLE units ADD isActive TINYINT(1) NOT NULL DEFAULT '1';
ALTER TABLE methods_of_paymant ADD isActive TINYINT(1) NOT NULL DEFAULT '1';
ALTER TABLE taxes ADD isActive TINYINT(1) NOT NULL DEFAULT '1';
ALTER TABLE goods_groups ADD isActive TINYINT(1) NOT NULL DEFAULT '1';
ALTER TABLE contractors_groups ADD isActive TINYINT(1) NOT NULL DEFAULT '1';

-- było zdublowane pole
ALTER TABLE sale_documents DROP method_of_paymant;

ALTER TABLE sale_documents CHANGE `contractor` `contractor` INT( 10 ) UNSIGNED NOT NULL ,
	CHANGE `method_of_payment` `method_of_payment` TINYINT( 3 ) UNSIGNED NOT NULL ,
	CHANGE `document_date` `document_date` DATE NOT NULL ,
	CHANGE `sale_date` `sale_date` DATE NOT NULL ,
	CHANGE `payment_date` `payment_date` DATE NOT NULL ,
	CHANGE `total` `total` FLOAT NOT NULL;

ALTER TABLE documents_positions CHANGE document document VARCHAR(16) CHARACTER SET utf8 COLLATE utf8_polish_ci NOT NULL,
	CHANGE good good INT(10) UNSIGNED NOT NULL,
	CHANGE quantity quantity FLOAT NOT NULL,
	CHANGE price_net price_net FLOAT NOT NULL,
	CHANGE tax_value tax_value FLOAT NOT NULL,
	CHANGE tax_letter tax_letter VARCHAR(3) CHARACTER SET utf8 COLLATE utf8_polish_ci NOT NULL;

-- przykladowa faktura
INSERT INTO sale_documents (symbol, contractor, method_of_payment, document_date, sale_date, payment_date, total) 
VALUES ('FV/5/2011', '1', '2', '2011-05-17', '2011-05-17', '2011-05-31', '4919.76');

-- przykladowe pozycje (jedna) do powyzszej faktury
INSERT INTO documents_positions (id_doc_pos, document, good, quantity, price_net, tax_value, tax_letter)
VALUES (NULL , 'FV/5/2011', '5', '2', '1999.9', '23', 'A');
