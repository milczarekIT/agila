USE pigstore;

ALTER table documents_nk DROP COLUMN issuer;
ALTER TABLE documents_nk RENAME COLUMN receiver TO contractor
