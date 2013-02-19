CREATE TABLE documents_positions (
  id_doc_pos INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  document VARCHAR(16) NULL,
  good INTEGER UNSIGNED NULL,
  quantity FLOAT NULL,
  price_net FLOAT NULL,
  tax_value FLOAT NULL,
  tax_letter VARCHAR(3) NULL,
  PRIMARY KEY(id_doc_pos)
);

CREATE TABLE methods_of_paymant (
  id_method TINYINT UNSIGNED NOT NULL AUTO_INCREMENT,
  name VARCHAR(35) NULL,
  maturity SMALLINT UNSIGNED DEFAULT '0',
  PRIMARY KEY(id_method)
);

CREATE TABLE sale_documents (
  symbol VARCHAR(16) NOT NULL,
  method_of_paymant TINYINT UNSIGNED NOT NULL,
  contractor INTEGER UNSIGNED,
  method_of_payment TINYINT UNSIGNED,
  document_date DATE,
  sale_date DATE,
  payment_date DATE,
  total FLOAT,
  PRIMARY KEY(symbol)
);

CREATE TABLE store_documents (
  symbol VARCHAR(16) NOT NULL,
  contractor INTEGER UNSIGNED,
  document_date DATE,
  store_date DATE,
  total FLOAT,
  PRIMARY KEY(symbol)
);

INSERT INTO `methods_of_paymant` (`id_method` ,`name` ,`maturity` )VALUE (NULL ,'Gotówka','0');
INSERT INTO `methods_of_paymant` (`id_method` ,`name` ,`maturity` )VALUE (NULL ,'Przelew','14');

