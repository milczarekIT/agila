update goods set goods_group=3 where id_good=4;
update goods set goods_group=5 where id_good=5;
update goods set goods_group=5 where id_good=1;

CREATE TABLE `document_numbering` (
`document_type` VARCHAR( 3 ) NOT NULL ,
`numbering` VARCHAR( 24 ) NOT NULL 
) ENGINE = MYISAM ;

INSERT INTO `document_numbering` (`document_type`, `numbering`)
VALUES ('FV', 'FV/#/YYYY'), 
	('PZ', 'PZ/#/YYYY'),
	('WZ', 'WZ/#/YYYY'), 
	('PW', 'PW/#/YYYY'),
	('RW', 'RW/#/YYYY');
