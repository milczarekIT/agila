ALTER TABLE store_documents ALTER COLUMN department SET DEFAULT 0;
ALTER TABLE store_documents ALTER COLUMN shipping SET DEFAULT 0;
ALTER TABLE store_documents ALTER COLUMN waybill_number SET DEFAULT '';

ALTER TABLE stores DROP column is_default;
ALTER TABLE stores ADD COLUMN is_default boolean NOT NULL DEFAULT false;
UPDATE stores SET is_default = true WHERE id = 'MAG';
ALTER TABLE stores DROP COLUMN id;
ALTER TABLE stores ADD COLUMN id SERIAL;
ALTER TABLE stores ADD COLUMN shortName VARCHAR(4) NOT NULL DEFAULT '';
UPDATE stores SET short_name = 'MAG' where id = 1;
ALTER TABLE ONLY stores
    ADD CONSTRAINT stores_pkey PRIMARY KEY (id);

Alter table stores rename to warehouses;

ALTER TABLE warehouses RENAME COLUMN store_name TO warehouse_name;
CREATE UNIQUE INDEX unique_shortName ON warehouses USING btree (short_name);

ALTER TABLE users DROP column id;
ALTER TABLE users ADD column id SERIAL;
ALTER TABLE users DROP column is_active;
ALTER TABLE users ADD COLUMN is_active boolean default true;

ALTER TABLE g_groups_features RENAME TO goods_groups_features;
ALTER TABLE sources_of_mem RENAME TO sources_of_member;

UPDATE goods SET quantity = 0::double precision WHERE quantity = 4.59163e-41;

CREATE TABLE wh_goods (
	warehouse INTEGER NOT NULL,
	good INTEGER NOT NULL,
	quantity double precision default 0::double precision,
	is_active boolean default true,
	FOREIGN KEY (warehouse) REFERENCES warehouses (id),
	FOREIGN KEY (good) REFERENCES goods (id_good)
);
CREATE UNIQUE INDEX unique_wh_goods ON wh_goods USING btree (warehouse, good);

INSERT INTO wh_goods(warehouse, good, quantity, is_active) SELECT 1, id_good, quantity, is_active FROM goods;
ALTER TABLE wh_goods ADD PRIMARY KEY (warehouse, good);

ALTER TABLE goods DROP COLUMN quantity;

CREATE TABLE wh_numbering (
	warehouse INTEGER, 
	type character varying(3),
	last_symbol character varying(16) NOT NULL DEFAULT '',
	FOREIGN KEY (warehouse) REFERENCES warehouses(id),	
	FOREIGN KEY (type) REFERENCES documents (type)
);
CREATE UNIQUE INDEX unique_wh_numbering ON wh_numbering USING btree (warehouse, type, last_symbol);

INSERT INTO wh_numbering(warehouse, type, last_symbol) SELECT 1, type, last_symbol FROM documents;
ALTER TABLE wh_numbering ADD PRIMARY KEY (warehouse, type);

ALTER TABLE cache_history DROP COLUMN IF EXISTS id_temp;

ALTER TABLE documents DROP COLUMN last_symbol;
 
ALTER TABLE wh_numbering ADD column numbering character varying(18) DEFAULT '';

UPDATE wh_numbering wh SET numbering = (SELECT numbering FROM documents WHERE type = wh.type);

ALTER TABLE documents DROP COLUMN numbering;


ALTER TABLE sale_documents ADD column warehouse INTEGER;
AlTER TABLE sale_documents ADD FOREIGN KEY (warehouse) REFERENCES warehouses(id);
ALTER TABLE store_documents RENAME TO warehouse_documnets;
ALTER TABLE warehouse_documents ADD column warehouse INTEGER;
AlTER TABLE warehouse_documents ADD FOREIGN KEY (warehouse) REFERENCES warehouses(id);
ALTER TABLE cash_documents ADD column warehouse INTEGER;
AlTER TABLE cash_documents ADD FOREIGN KEY (warehouse) REFERENCES warehouses(id);
ALTER TABLE orders ADD column warehouse INTEGER;
AlTER TABLE orders ADD FOREIGN KEY (warehouse) REFERENCES warehouses(id);
ALTER TABLE purchase_documents ADD column warehouse INTEGER;
AlTER TABLE purchase_documents ADD FOREIGN KEY (warehouse) REFERENCES warehouses(id);
ALTER TABLE documents_nk ADD column warehouse INTEGER;
AlTER TABLE documents_nk ADD FOREIGN KEY (warehouse) REFERENCES warehouses(id);

UPDATE sale_documents SET warehouse = 1;
UPDATE warehouse_documents SET warehouse = 1;
UPDATE cash_documents SET warehouse = 1;
UPDATE orders SET warehouse = 1;
UPDATE purchase_documents SET warehouse = 1;
UPDATE documents_nk SET warehouse = 1;

ALTER TABLE sale_documents DROP constraint sale_documents_pkey;
ALTER TABLE warehouse_documents DROP constraint store_documents_pkey;
ALTER TABLE cash_documents DROP constraint cash_documents_pkey;
ALTER TABLE orders DROP constraint orders_pkey;
ALTER TABLE purchase_documents DROP constraint purchase_documents_pkey;
ALTER TABLE documents_nk DROP constraint documents_nk_pkey;

ALTER TABLE sale_documents ADD PRIMARY KEY (symbol, warehouse);
ALTER TABLE warehouse_documents ADD PRIMARY KEY (symbol, warehouse);
ALTER TABLE cash_documents ADD PRIMARY KEY (symbol, warehouse);
ALTER TABLE orders ADD PRIMARY KEY (symbol, warehouse);
ALTER TABLE purchase_documents ADD PRIMARY KEY (symbol, warehouse);
ALTER TABLE documents_nk ADD PRIMARY KEY (symbol, warehouse);

ALTER TABLE warehouse_documents RENAME COLUMN store_date TO warehouse_date;

ALTER TABLE warehouse_documents RENAME COLUMN store_result TO warehouse_result;
ALTER TABLE sale_documents RENAME COLUMN store_result TO warehouse_result;
ALTER TABLE purchase_documents RENAME COLUMN store_result TO warehouse_result;


DROP INDEX unique_doc_pos;
ALTER TABLE documents_positions ADD COLUMN warehouse INTEGER NOT NULL DEFAULT 1;
ALTER TABLE documents_positions ADD FOREIGN KEY (warehouse) REFERENCES warehouses(id);
ALTER TABLE documents_positions ADD PRIMARY KEY (warehouse, document, good);


--- 
SELECT base_document, linked_document INTO doubled_row FROM linked_documents GROUP BY base_document, linked_document HAVING count(*) > 1;
DELETE FROM linked_documents ld WHERE EXISTS (SELECT base_document, linked_document FROM doubled_row WHERE base_document = ld.base_document AND linked_document = ld.linked_document)
INSERT INTO linked_documents SELECT * FROM doubled_row;
DELETE FROM linked_documents WHERE base_document = '' OR linked_document = '';

DROP TABLE doubled_row;


ALTER TABLE linked_documents ADD COLUMN warehouse INTEGER;
UPDATE linked_documents SET warehouse = 1;
CREATE UNIQUE INDEX unique_linkedDocuments ON linked_documents USING btree (base_document, linked_document, warehouse);

--


 
