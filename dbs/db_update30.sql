ALTER TABLE owners ADD CONSTRAINT owners_pkey PRIMARY KEY(id_owner);

ALTER TABLE documents_positions ADD COLUMN price_level VARCHAR(3);

UPDATE documents_positions SET price_level = 'A' WHERE price_net = (SELECT price_a_net FROM goods WHERE id_good = documents_positions.good);
UPDATE documents_positions SET price_level = 'B' WHERE price_net = (SELECT price_b_net FROM goods WHERE id_good = documents_positions.good);
UPDATE documents_positions SET price_level = 'C' WHERE price_net = (SELECT price_c_net FROM goods WHERE id_good = documents_positions.good);
UPDATE documents_positions SET price_level = 'MAG' WHERE price_net = (SELECT price_mag_net FROM goods WHERE id_good = documents_positions.good);

UPDATE documents_positions SET price_level = 'MAG' WHERE document LIKE 'PW/%' OR document LIKE 'RW/%' or document LIKE 'PZ/%' or document LIKE 'WZ/%';
UPDATE documents_positions SET price_level = 'A' WHERE price_level IS NULL;
UPDATE documents_positions SET price_level = 'MAG' WHERE document LIKE 'ZD/%';
UPDATE documents_positions SET price_level = 'A' WHERE document LIKE 'ZK/%';

ALTER TABLE documents_positions DROP COLUMN price_net;



CREATE OR REPLACE FUNCTION "getpricenet"("goodId" INTEGER, "_priceLevel" character varying) RETURNS NUMERIC(10,2) AS $BODY$
	DECLARE
		price NUMERIC(10,2);
	BEGIN 
		IF("_priceLevel" = 'A')
		THEN
			SELECT price_a_net INTO price FROM goods WhERE id_good = "goodId";
		END IF;
		IF("_priceLevel" = 'B')
		THEN
			SELECT price_b_net INTO price FROM goods WhERE id_good = "goodId";
		END IF;
		IF("_priceLevel" = 'C')
		THEN
			SELECT price_b_net INTO price FROM goods WhERE id_good = "goodId";
		END IF;
		IF("_priceLevel" = 'MAG')
		THEN
			SELECT price_mag_net INTO price FROM goods WhERE id_good = "goodId";
		END IF;

		RETURN price;
	END;
$BODY$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION "getpricegross"("goodId" INTEGER, "_priceLevel" character varying) RETURNS NUMERIC(10,2) AS $BODY$
	DECLARE
		price NUMERIC(10,2);
	BEGIN 
		IF("_priceLevel" = 'A')
		THEN
			SELECT price_a_gross INTO price FROM goods WhERE id_good = "goodId";
		END IF;
		IF("_priceLevel" = 'B')
		THEN
			SELECT price_b_gross INTO price FROM goods WhERE id_good = "goodId";
		END IF;
		IF("_priceLevel" = 'C')
		THEN
			SELECT price_b_gross INTO price FROM goods WhERE id_good = "goodId";
		END IF;
		IF("_priceLevel" = 'MAG')
		THEN
			SELECT price_mag_gross INTO price FROM goods WhERE id_good = "goodId";
		END IF;

		RETURN price;
	END;
$BODY$ LANGUAGE 'plpgsql';

COMMENT ON FUNCTION getpricenet (integer, character varying) IS 'Zwraca cenę netto jako NUMERIC(10,2) o podanym w parametrze id towaru i poziomie ceny, np. SELECT getpricenet(1, CAST("MAG" AS VARCHAR));';


COMMENT ON FUNCTION getpricegross (integer, character varying) IS 'Zwraca cenę brutto jako NUMERIC(10,2) o podanym w parametrze id towaru i poziomie ceny, np. SELECT getpricegross(1, CAST("MAG" AS VARCHAR));';

COMMENT ON FUNCTION init_whnumbering () IS 'Inicjalizuje numeracje w nowym magazynie. Wywoływana przez trigger';





