CREATE TABLE settings_preferences (
	name VARCHAR(40) PRIMARY KEY,
	value VARCHAR(70)
);


INSERT INTO settings_preferences (name, value) VALUES ('DEFAULT_GOODS_MARGIN', '25');
INSERT INTO settings_preferences (name, value) VALUES ('DEFAULT_GOODS_DISCOUNT_B', '2.5');
INSERT INTO settings_preferences (name, value) VALUES ('DEFAULT_GOODS_DISCOUNT_C', '5.0');
INSERT INTO settings_preferences (name, value) VALUES ('DEFAULT_PRINT_NUMBER_OF_COPIES', '1');
INSERT INTO settings_preferences (name, value) VALUES ('DEFAULT_PRINT_ACTION', 'PRINT+PDF');
ALTER TABLE settings_preferences OWNER TO bbraces;
