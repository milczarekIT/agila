
ALTER TABLE warehouses ADD column is_active boolean default true;
UPDATE wh_numbering SET numbering = 'KW/#/YYYY' WHERE type = 'KW';
DROP INDEX unique_shortname;

CREATE UNIQUE INDEX unique_shortName ON warehouses USING btree (short_name) WHERE is_active = true;



--- funkcja inicjująca numerowanie
CREATE FUNCTION init_whnumbering() RETURNS trigger AS $init_whnumbering$
    BEGIN
	INSERT INTO wh_numbering SELECT NEW.id, type, '', type || '/#/YYYY' FROM documents;
        
	RETURN NEW;
    END;
$init_whnumbering$ LANGUAGE plpgsql;

-- wyzwalacz wywołujący funkcja inicjującą numerowanie przy dodawnaiu nowego mag
CREATE TRIGGER tr_init_whnumbering AFTER INSERT ON warehouses
FOR EACH ROW EXECUTE PROCEDURE init_whnumbering();

ALTER TABLE wh_numbering DROP CONSTRAINT wh_numbering_warehouse_fkey;
ALTER TABLE ONLY wh_numbering
    ADD CONSTRAINT wh_numbering_warehouse_fkey FOREIGN KEY (warehouse) REFERENCES warehouses(id) ON DELETE CASCADE;

ALTER TABLE wh_goods DROP CONSTRAINT wh_goods_warehouse_fkey;
ALTER TABLE ONLY wh_goods
    ADD CONSTRAINT wh_goods_warehouse_fkey FOREIGN KEY (warehouse) REFERENCES warehouses(id) ON DELETE CASCADE;

ALTER TABLE sale_documents DROP CONSTRAINT sale_documents_warehouse_fkey;
ALTER TABLE ONLY sale_documents
    ADD CONSTRAINT sale_documents_warehouse_fkey FOREIGN KEY (warehouse) REFERENCES warehouses(id) ON DELETE CASCADE;

ALTER TABLE cash_documents DROP CONSTRAINT cash_documents_warehouse_fkey;
ALTER TABLE cash_documents 
	ADD CONSTRAINT cash_documents_warehouse_fkey
	FOREIGN KEY (warehouse) REFERENCES warehouses(id) ON DELETE CASCADE;

ALTER TABLE documents_nk DROP CONSTRAINT documents_nk_warehouse_fkey;
ALTER TABLE documents_nk ADD CONSTRAINT documents_nk_warehouse_fkey
	FOREIGN KEY (warehouse) REFERENCES warehouses(id) ON DELETE CASCADE;

ALTER TABLE documents_positions DROP CONSTRAINT documents_positions_warehouse_fkey;
ALTER TABLE documents_positions ADD CONSTRAINT documents_positions_warehouse_fkey FOREIGN KEY (warehouse) REFERENCES warehouses(id) ON DELETE CASCADE;

ALTER TABLE orders DROP CONSTRAINT orders_warehouse_fkey;
ALTER TABLE orders ADD CONSTRAINT orders_warehouse_fkey	FOREIGN KEY (warehouse) REFERENCES warehouses(id) ON DELETE CASCADE;

ALTER TABLE purchase_documents DROP CONSTRAINT purchase_documents_warehouse_fkey;
ALTER TABLE purchase_documents ADD CONSTRAINT purchase_documents_warehouse_fkey FOREIGN KEY (warehouse) REFERENCES warehouses(id) ON DELETE CASCADE;

ALTER TABLE USERS ADD CONSTRAINT users_pkey PRIMARY KEY(id);

ALTER TABLE warehouse_documents DROP CONSTRAINT warehouse_documnets_warehouse_fkey;
ALTER TABLE warehouse_documents ADD CONSTRAINT warehouse_documents_warehouse_fkey FOREIGN KEY (warehouse) REFERENCES warehouses(id) ON DELETE CASCADE;



