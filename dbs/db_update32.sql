ALTER TABLE cash_documents ALTER COLUMN symbol TYPE VARCHAR(20);
ALTER TABLE cash_documents ALTER COLUMN document TYPE VARCHAR(20);

ALTER TABLE contractors ALTER COLUMN symbol TYPE VARCHAR(255);
ALTER TABLE contractors ALTER COLUMN name TYPE VARCHAR(255);
ALTER TABLE contractors ALTER COLUMN additional_id_value TYPE VARCHAR(25);
ALTER TABLE contractors_groups ALTER COLUMN name TYPE VARCHAR(60);

ALTER TABLE document_places ALTER COLUMN name TYPE VARCHAR(40);

ALTER TABLE documents_nk ALTER COLUMN symbol TYPE VARCHAR(20);
ALTER TABLE documents_nk ALTER COLUMN invoice_symbol TYPE VARCHAR(20);

ALTER TABLE documents_positions ALTER COLUMN document TYPE VARCHAR(20);

ALTER TABLE goods ALTER COLUMN symbol TYPE VARCHAR(127);
ALTER TABLE goods ALTER COLUMN name TYPE VARCHAR(127);

ALTER TABLE goods_future_values ALTER COLUMN value TYPE VARCHAR(70);

ALTER TABLE  linked_documents ALTER COLUMN base_document TYPE VARCHAR(20);
ALTER TABLE  linked_documents ALTER COLUMN linked_document TYPE VARCHAR(20);

ALTER TABLE means_of_transport ALTER COLUMN name TYPE VARCHAR(60);

ALTER TABLE methods_of_payment ALTER COLUMN name TYPE VARCHAR(60);

ALTER TABLE orders ALTER COLUMN symbol TYPE VARCHAR(20);

ALTER TABLE purchase_documents ALTER COLUMN symbol TYPE VARCHAR(20);
ALTER TABLE purchase_documents ALTER COLUMN order_symbol TYPE VARCHAR(20);
ALTER TABLE purchase_documents ALTER COLUMN purchase_document TYPE VARCHAR(20);

ALTER TABLE sale_documents ALTER COLUMN symbol  TYPE VARCHAR(20);
ALTER TABLE sale_documents ALTER COLUMN order_symbol TYPE VARCHAR(20);

ALTER TABLE warehouse_documents ALTER COLUMN symbol TYPE VARCHAR(20);
ALTER TABLE warehouse_documents ALTER COLUMN waybill_number TYPE VARCHAR(20);

ALTER TABLE wh_numbering ALTER COLUMN last_symbol TYPE VARCHAR(20);

ALTER TABLE sale_documents ADD COLUMN id SERIAL;
ALTER TABLE purchase_documents ADD COLUMN id SERIAL;
ALTER TABLE orders ADD COLUMN id SERIAL;
ALTER TABLE cash_documents;
ALTER TABLE warehouse_documents ADD COLUMN id SERIAL;
ALTER TABLE documents_nk ADD COLUMN id SERIAL;

-- naprawa błędnych wpisów
UPDATE warehouse_documents SET transport = department WhERE type = 'PZ';
UPDATE warehouse_documents SET department = 0 WhERE type = 'PZ';

ALTER TABLE documents ALTER COLUMN name TYPE VARCHAR(33);
INSERT INTO documents (type, name, after_text, family) VALUES ('MM+', 'Przesunięcie Międzymagazynowe +', '', 'STORE');
INSERT INTO documents (type, name, after_text, family) VALUES ('MM-', 'Przesunięcie Międzymagazynowe -', '', 'STORE');












