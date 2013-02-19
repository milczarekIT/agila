
-- FIRST
USE pigstore;
DROP TABLE `methods_of_paymant`;

CREATE TABLE IF NOT EXISTS `methods_of_payment` (
  `id_method` tinyint(3) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(35) COLLATE utf8_polish_ci DEFAULT NULL,
  `maturity` smallint(5) unsigned DEFAULT '0',
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id_method`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci AUTO_INCREMENT=5 ;


INSERT INTO `methods_of_payment` (`id_method`, `name`, `maturity`, `isActive`) VALUES
(1, 'Gotówka', 0, 1),
(2, 'Przelew', 14, 1),
(3, 'Płacę z allegro', 0, 1);

-- SECOND
USE pigstore_magazyn2;
DROP TABLE `methods_of_paymant`;

CREATE TABLE IF NOT EXISTS `methods_of_payment` (
  `id_method` tinyint(3) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(35) COLLATE utf8_polish_ci DEFAULT NULL,
  `maturity` smallint(5) unsigned DEFAULT '0',
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id_method`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci AUTO_INCREMENT=5 ;



INSERT INTO `methods_of_payment` (`id_method`, `name`, `maturity`, `isActive`) VALUES
(1, 'Gotówka', 0, 1),
(2, 'Przelew', 14, 1),
(3, 'Płacę z allegro', 0, 1);


