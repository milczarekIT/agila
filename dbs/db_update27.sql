
CREATE UNIQUE INDEX unique_goodsgroup_features ON g_groups_features USING btree (goods_group, feature);
ALTER TABLE taxes DROP COLUMN letter;
ALTER TABLE taxes ADD COLUMN short_name VARCHAR(6) NOT NULL DEFAULT '';

UPDATE taxes SET short_name = CAST(CAST(value as integer) as VARCHAR)||'%';
UPDATE taxes SET short_name = 'zw.' WHERE name LIKE '%zw.%'
