CREATE TABLE IF NOT EXISTS `contractors` (
  `id_contractor` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `symbol` varchar(70) COLLATE utf8_polish_ci NOT NULL,
  `name` varchar(70) COLLATE utf8_polish_ci NOT NULL,
  `contractor_group` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `postcode` varchar(6) COLLATE utf8_polish_ci NOT NULL,
  `city` varchar(40) COLLATE utf8_polish_ci NOT NULL,
  `adress` varchar(60) COLLATE utf8_polish_ci NOT NULL,
  `nip` varchar(13) COLLATE utf8_polish_ci NOT NULL,
  `regon` varchar(12) COLLATE utf8_polish_ci NOT NULL,
  `discount` float NOT NULL DEFAULT '0.0',
  `additional` varchar(60) COLLATE utf8_polish_ci NOT NULL,
  `account_number` varchar(34) COLLATE utf8_polish_ci NOT NULL,
  `website` varchar(60) COLLATE utf8_polish_ci NOT NULL,
  `email` varchar(60) COLLATE utf8_polish_ci NOT NULL,
  `comments` text COLLATE utf8_polish_ci NOT NULL,
  `source_of_mem` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id_contractor`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;





--
-- Struktura tabeli dla  `contractors_groups`
--

CREATE TABLE IF NOT EXISTS `contractors_groups` (
  `id_group` tinyint(3) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(60) COLLATE utf8_polish_ci NOT NULL,
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id_group`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci AUTO_INCREMENT=2 ;

--
-- Zrzut danych tabeli `contractors_groups`
--

INSERT INTO `contractors_groups` (`id_group`, `name`, `isActive`) VALUES
(1, 'BRAK', 1);



--
-- Struktura tabeli dla  `contractors_phones`
--

CREATE TABLE IF NOT EXISTS `contractors_phones` (
  `id_contractors_phone` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `contractor` int(10) unsigned NOT NULL,
  `phone_name` varchar(60) COLLATE utf8_polish_ci NOT NULL,
  `number` varchar(20) COLLATE utf8_polish_ci NOT NULL,
  PRIMARY KEY (`id_contractors_phone`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;


--
-- Struktura tabeli dla  `documents_positions`
--

CREATE TABLE IF NOT EXISTS `documents_positions` (
  `document` varchar(16) COLLATE utf8_polish_ci NOT NULL,
  `good` int(10) unsigned NOT NULL,
  `quantity` float NOT NULL,
  `price_net` decimal(10,2) NOT NULL,
  `tax_id` smallint(5) unsigned NOT NULL DEFAULT '1'
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;



--
-- Struktura tabeli dla  `document_places`
--

CREATE TABLE IF NOT EXISTS `document_places` (
  `id_place` tinyint(3) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(35) COLLATE utf8_polish_ci NOT NULL,
  PRIMARY KEY (`id_place`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci AUTO_INCREMENT=2 ;

--
-- Zrzut danych tabeli `document_places`
--

INSERT INTO `document_places` (`id_place`, `name`) VALUES
(1, 'Łódź');

--
-- Struktura tabeli dla  `features`
--

CREATE TABLE IF NOT EXISTS `features` (
  `id_feature` smallint(5) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(40) COLLATE utf8_polish_ci NOT NULL,
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id_feature`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;



--
-- Struktura tabeli dla  `goods`
--

CREATE TABLE IF NOT EXISTS `goods` (
  `id_good` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `symbol` varchar(20) COLLATE utf8_polish_ci NOT NULL,
  `name` varchar(70) COLLATE utf8_polish_ci NOT NULL,
  `quantity` float NOT NULL DEFAULT '0',
  `tax` smallint(5) unsigned NOT NULL DEFAULT '1',
  `unit` smallint(5) unsigned NOT NULL DEFAULT '1',
  `pkwiu` varchar(25) COLLATE utf8_polish_ci NOT NULL,
  `goods_group` smallint(5) unsigned NOT NULL DEFAULT '1',
  `price_a_net` decimal(10,2) NOT NULL,
  `price_a_gross` decimal(10,2) NOT NULL,
  `price_mag_net` decimal(10,2) NOT NULL,
  `price_mag_gross` decimal(10,2) NOT NULL,
  `price_b_net` decimal(10,2) NOT NULL,
  `price_b_gross` decimal(10,2) NOT NULL,
  `price_c_net` decimal(10,2) NOT NULL,
  `price_c_gross` decimal(10,2) NOT NULL,
  `description` text COLLATE utf8_polish_ci NOT NULL,
  `foto` varchar(180) COLLATE utf8_polish_ci NOT NULL,
  `weight` float NOT NULL DEFAULT '0.0',
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id_good`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;



--
-- Struktura tabeli dla  `goods_future_values`
--

CREATE TABLE IF NOT EXISTS `goods_future_values` (
  `id_goods_future` tinyint(3) unsigned NOT NULL AUTO_INCREMENT,
  `good` int(10) unsigned NOT NULL,
  `feature` smallint(5) unsigned NOT NULL,
  `value` text COLLATE utf8_polish_ci NOT NULL,
  PRIMARY KEY (`id_goods_future`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci ;





--
-- Struktura tabeli dla  `goods_groups`
--

CREATE TABLE IF NOT EXISTS `goods_groups` (
  `id_group` smallint(5) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(60) COLLATE utf8_polish_ci NOT NULL,
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id_group`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci AUTO_INCREMENT=2 ;

--
-- Zrzut danych tabeli `goods_groups`
--

INSERT INTO `goods_groups` (`id_group`, `name`, `isActive`) VALUES
(1, 'BRAK', 1);

--
-- Struktura tabeli dla  `g_groups_features`
--

CREATE TABLE IF NOT EXISTS `g_groups_features` (
  `goods_group` smallint(5) unsigned DEFAULT NULL,
  `feature` smallint(5) unsigned DEFAULT NULL,
  `isActive` tinyint(1) NOT NULL DEFAULT '1'
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;



--
-- Struktura tabeli dla  `methods_of_paymant`
--

CREATE TABLE IF NOT EXISTS `methods_of_paymant` (
  `id_method` tinyint(3) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(35) COLLATE utf8_polish_ci DEFAULT NULL,
  `maturity` smallint(5) unsigned DEFAULT '0',
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id_method`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci AUTO_INCREMENT=3 ;

--
-- Zrzut danych tabeli `methods_of_paymant`
--

INSERT INTO `methods_of_paymant` (`id_method`, `name`, `maturity`, `isActive`) VALUES
(1, 'Gotówka', 0, 1),
(2, 'Przelew', 14, 1);


--
-- Struktura tabeli dla  `sale_documents`
--

CREATE TABLE IF NOT EXISTS `sale_documents` (
  `symbol` varchar(16) COLLATE utf8_polish_ci NOT NULL,
  `contractor` int(10) unsigned NOT NULL,
  `method_of_payment` tinyint(3) unsigned NOT NULL,
  `document_place` tinyint(4) NOT NULL DEFAULT '1',
  `document_date` date NOT NULL,
  `sale_date` date NOT NULL,
  `payment_date` date NOT NULL,
  `total` decimal(10,2) NOT NULL,
  `discount` decimal(3,1) NOT NULL DEFAULT '0.0',
  `paid` tinyint(1) NOT NULL DEFAULT '1',
  `store_result` tinyint(1) NOT NULL DEFAULT '1',
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`symbol`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;



--
-- Struktura tabeli dla  `sources_of_mem`
--

CREATE TABLE IF NOT EXISTS `sources_of_mem` (
  `id_source` tinyint(3) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(60) COLLATE utf8_polish_ci NOT NULL,
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id_source`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci AUTO_INCREMENT=2 ;

--
-- Zrzut danych tabeli `sources_of_mem`
--

INSERT INTO `sources_of_mem` (`id_source`, `name`, `isActive`) VALUES
(1, 'BRAK', 1);


-- --------------------------------------------------------

--
-- Struktura tabeli dla  `store_documents`
--

CREATE TABLE IF NOT EXISTS `store_documents` (
  `symbol` varchar(16) COLLATE utf8_polish_ci NOT NULL,
  `contractor` int(10) unsigned DEFAULT '0',
  `document_date` date DEFAULT NULL,
  `store_date` date DEFAULT NULL,
  `total` decimal(10,2) NOT NULL,
  `store_result` tinyint(1) NOT NULL DEFAULT '1',
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`symbol`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;



--
-- Struktura tabeli dla  `taxes`
--

CREATE TABLE IF NOT EXISTS `taxes` (
  `id_tax` smallint(5) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(50) COLLATE utf8_polish_ci NOT NULL,
  `value` float NOT NULL,
  `letter` varchar(3) COLLATE utf8_polish_ci NOT NULL,
  `active_in_app` tinyint(1) NOT NULL DEFAULT '1',
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id_tax`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci AUTO_INCREMENT=6 ;

--
-- Zrzut danych tabeli `taxes`
--

INSERT INTO `taxes` (`id_tax`, `name`, `value`, `letter`, `active_in_app`, `isActive`) VALUES
(1, 'Stawka podstawowa 23%', 23, 'A', 1, 1),
(2, 'Stawka podstawowa 8%', 8, 'B', 1, 1),
(3, 'Stawka podstawowa 5%', 5, 'C', 1, 1),
(4, 'Stawka podstawowa 0%', 0, 'D', 1, 1),
(5, 'Stawka zw.', 0, 'zw.', 1, 1);

--
-- Struktura tabeli dla  `units`
--

CREATE TABLE IF NOT EXISTS `units` (
  `id_unit` smallint(5) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(5) COLLATE utf8_polish_ci NOT NULL,
  `zero_places` tinyint(3) unsigned NOT NULL DEFAULT '2',
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id_unit`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci AUTO_INCREMENT=3 ;

--
-- Zrzut danych tabeli `units`
--

INSERT INTO `units` (`id_unit`, `name`, `zero_places`, `isActive`) VALUES
(1, 'szt.', 2, 1),
(2, 'kg', 3, 1);

CREATE TABLE IF NOT EXISTS `document_text` (
  `document_type` varchar(3) COLLATE utf8_polish_ci NOT NULL,
  `text` varchar(255) COLLATE utf8_polish_ci NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Zrzut danych tabeli `document_text`
--

INSERT INTO `document_text` (`document_type`, `text`) VALUES
('FV', 'Dziękujemy za zakupy. Zapraszamy ponownie.'),
('PZ', ''),
('WZ', ''),
('PW', '');

CREATE TABLE IF NOT EXISTS `document_numbering` (
`document_type` VARCHAR( 3 ) NOT NULL ,
`numbering` VARCHAR( 24 ) NOT NULL 
) ENGINE = MYISAM ;


INSERT INTO `document_numbering` (`document_type`, `numbering`)
VALUES ('FV', 'FV/#/YYYY'), 
	('PZ', 'PZ/#/YYYY'),
	('WZ', 'WZ/#/YYYY'), 
	('PW', 'PW/#/YYYY'),
	('RW', 'RW/#/YYYY');
