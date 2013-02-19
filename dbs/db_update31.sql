ALTER TABLE document_places ADD COLUMN is_default BOOLEAN DEFAULT false;
UPDATE document_places SET is_default = true WHERE id_place = 1;
