CREATE UNIQUE INDEX "unique_type_oldId" ON cache_history USING btree (type, old);
CREATE UNIQUE INDEX "unique_type_newId" ON cache_history USING btree (type, new);	


CREATE UNIQUE INDEX unique_doc_pos ON documents_positions USING btree (document, good);
