CREATE USER bbraces WITH ENCRYPTED PASSWORD 'bb123456';
ALTER USER bbraces CREATEDB;

CREATE DATABASE pigstore;
CREATE DATABASE pigstore_conf;
CREATE DATABASE pigstore_magazyn2;

GRANT ALL PRIVILEGES ON DATABASE pigstore TO bbraces;
GRANT ALL PRIVILEGES ON DATABASE pigstore_conf TO bbraces;
GRANT ALL PRIVILEGES ON DATABASE pigstore_magazyn2 TO bbraces;