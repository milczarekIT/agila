-- phpMyAdmin SQL Dump
-- version 3.3.7deb5build0.10.10.1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Czas wygenerowania: 04 Gru 2011, 10:22
-- Wersja serwera: 5.1.49
-- Wersja PHP: 5.3.3-1ubuntu9.6

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Baza danych: `pigstore_magazyn2`
--

-- --------------------------------------------------------

--
-- Struktura tabeli dla  `cache_history`
--

CREATE TABLE IF NOT EXISTS `cache_history` (
  `type` varchar(10) COLLATE utf8_polish_ci NOT NULL,
  `old` varchar(16) COLLATE utf8_polish_ci NOT NULL,
  `new` varchar(16) COLLATE utf8_polish_ci NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Zrzut danych tabeli `cache_history`
--


-- --------------------------------------------------------

--
-- Struktura tabeli dla  `cash_documents`
--

CREATE TABLE IF NOT EXISTS `cash_documents` (
  `symbol` varchar(16) COLLATE utf8_polish_ci NOT NULL,
  `contractor` int(10) unsigned NOT NULL,
  `document_place` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `value` decimal(10,2) NOT NULL,
  `document_date` date NOT NULL,
  `payment_date` date NOT NULL,
  `document` varchar(16) COLLATE utf8_polish_ci NOT NULL,
  `title` varchar(255) COLLATE utf8_polish_ci NOT NULL,
  `receive_person` int(10) unsigned NOT NULL,
  `issue_person` int(10) unsigned NOT NULL,
  `description` text COLLATE utf8_polish_ci NOT NULL,
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`symbol`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Zrzut danych tabeli `cash_documents`
--


-- --------------------------------------------------------

--
-- Struktura tabeli dla  `contractors`
--

CREATE TABLE IF NOT EXISTS `contractors` (
  `id_contractor` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `symbol` varchar(70) COLLATE utf8_polish_ci NOT NULL,
  `name` text COLLATE utf8_polish_ci NOT NULL,
  `contractor_group` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `type` tinyint(1) unsigned NOT NULL DEFAULT '1',
  `postcode` varchar(6) COLLATE utf8_polish_ci NOT NULL,
  `city` varchar(40) COLLATE utf8_polish_ci NOT NULL,
  `adress` varchar(60) COLLATE utf8_polish_ci NOT NULL,
  `nip` varchar(13) COLLATE utf8_polish_ci NOT NULL,
  `additional_id_type` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `additional_id_value` varchar(12) COLLATE utf8_polish_ci NOT NULL,
  `discount` decimal(4,2) NOT NULL DEFAULT '0.00',
  `additional` varchar(60) COLLATE utf8_polish_ci NOT NULL,
  `account_number` varchar(34) COLLATE utf8_polish_ci NOT NULL,
  `website` varchar(60) COLLATE utf8_polish_ci NOT NULL,
  `email` varchar(60) COLLATE utf8_polish_ci NOT NULL,
  `comments` text COLLATE utf8_polish_ci NOT NULL,
  `source_of_mem` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id_contractor`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci AUTO_INCREMENT=20 ;

--
-- Zrzut danych tabeli `contractors`
--

INSERT INTO `contractors` (`id_contractor`, `symbol`, `name`, `contractor_group`, `type`, `postcode`, `city`, `adress`, `nip`, `additional_id_type`, `additional_id_value`, `discount`, `additional`, `account_number`, `website`, `email`, `comments`, `source_of_mem`, `isActive`) VALUES
(2, 'JAKIŚ KLIENT', 'Jakiś Klient', 1, 1, '99-400', 'Łowicz', 'Zagórska 31', '', 1, '', '1.00', '', '12 1412 1313 1313 1313 1313 1313', '', '', '', 1, 1),
(1, 'ADAM ORZESZKO', 'Adam Orzeszko', 1, 1, '85-500', 'Karolew', 'Karolew 66', '834-147-87-52', 1, '', '0.00', '', '', '', '', '', 1, 1);

-- --------------------------------------------------------

--
-- Struktura tabeli dla  `contractors_additional_ids`
--

CREATE TABLE IF NOT EXISTS `contractors_additional_ids` (
  `id` tinyint(3) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(25) COLLATE utf8_polish_ci NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci AUTO_INCREMENT=5 ;

--
-- Zrzut danych tabeli `contractors_additional_ids`
--

INSERT INTO `contractors_additional_ids` (`id`, `name`) VALUES
(1, 'REGON'),
(2, 'PESEL'),
(3, 'Dowód osobisty'),
(4, 'Paszport');

-- --------------------------------------------------------

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
(1, 'Podstawowa', 1);

-- --------------------------------------------------------

--
-- Struktura tabeli dla  `contractors_phones`
--

CREATE TABLE IF NOT EXISTS `contractors_phones` (
  `id_contractors_phone` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `contractor` int(10) unsigned NOT NULL,
  `phone_name` varchar(60) COLLATE utf8_polish_ci NOT NULL,
  `number` varchar(20) COLLATE utf8_polish_ci NOT NULL,
  `is_default` tinyint(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id_contractors_phone`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci AUTO_INCREMENT=14 ;

--
-- Zrzut danych tabeli `contractors_phones`
--


-- --------------------------------------------------------

--
-- Struktura tabeli dla  `departments`
--

CREATE TABLE IF NOT EXISTS `departments` (
  `id_department` smallint(5) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(70) COLLATE utf8_polish_ci NOT NULL,
  `isActive` tinyint(1) unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`id_department`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci AUTO_INCREMENT=1 ;

--
-- Zrzut danych tabeli `departments`
--


-- --------------------------------------------------------

--
-- Struktura tabeli dla  `documents`
--

CREATE TABLE IF NOT EXISTS `documents` (
  `type` varchar(3) COLLATE utf8_polish_ci NOT NULL,
  `name` varchar(30) COLLATE utf8_polish_ci NOT NULL,
  `numbering` varchar(18) COLLATE utf8_polish_ci NOT NULL,
  `last_symbol` varchar(16) COLLATE utf8_polish_ci NOT NULL,
  `after_text` text COLLATE utf8_polish_ci NOT NULL,
  `family` varchar(10) COLLATE utf8_polish_ci NOT NULL DEFAULT 'SALE',
  PRIMARY KEY (`type`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Zrzut danych tabeli `documents`
--

INSERT INTO `documents` (`type`, `name`, `numbering`, `last_symbol`, `after_text`, `family`) VALUES
('FV', 'Faktura VAT', 'FV/#/B/YYYY', 'FV/B/1/2011', 'Dziękujemy za zakupy. Zapraszamy ponownie....', 'SALE'),
('PZ', 'Przychód Zewnętrzny', 'PZ/#/YYYY', '', '', 'STORE'),
('WZ', 'Wydanie Zewnętrzne', 'WZ/#/YYYY', '', '', 'STORE'),
('PW', 'Przychód Wewnętrzny', 'PW/#/YYYY', '', '', 'STORE'),
('RW', 'Rozchód Wewnętrzny', 'RW/#/YYYY', '', '', 'STORE'),
('KP', 'Kasa Przyjmie', 'KP/#/YYYY', '', '', 'CASH'),
('FK', 'Faktura korygująca', 'FK/#/YYYY', '', '', 'SALE'),
('FMP', 'Faktura VAT-MP', 'FMP/#/YYYY', '', '', 'SALE'),
('PRO', 'Faktura proforma', 'PRO/#/YYYY', '', '', 'SALE'),
('PA', 'Paragon', 'PA/#/YYYY', '', '', 'SALE'),
('PI', 'Paragon imienny', 'PI/#/YYYY', '', '', 'SALE'),
('NK', 'Nota Korygująca', 'NK/#/YYYY', '', '', 'PURCHASE'),
('FM', 'Faktura VAT Marża', 'FM/#/YYYY', '', '', 'SALE'),
('RR', 'Faktura VAT RR', 'RR/#/YYYY', '', '', 'PURCHASE'),
('ZK', 'Zamówienie od klienta', 'ZK/#/YYYY', '', '', 'ORDER'),
('ZD', 'Zamówienie do dostawcy', 'ZD/#/YYYY', '', '', 'ORDER'),
('FZ', 'Faktura zakupu', 'FZ/#/YYYY', '', '', 'PURCHASE'),
('FZK', 'Faktura zakupu korygująca', 'FZK/#/YYYY', '', '', 'PURCHASE'),
('ZAL', 'Faktura VAT zaliczkowa', 'ZAL/#/YYYY', '', '', 'SALE'),
('RZL', 'Faktura VAT końcowa', 'RZL/#/YYYY', '', '', 'SALE'),
('OF', 'Oferta', 'OF/#/YYYY', '', '', 'OTHER'),
('CN', 'Cennik', 'CN/#/YYYY', '', '', 'OTHER'),
('KW', 'Kasa Wyda', 'KW/#/2011', '', '', 'CASH');

-- --------------------------------------------------------

--
-- Struktura tabeli dla  `documents_family`
--

CREATE TABLE IF NOT EXISTS `documents_family` (
  `id` varchar(10) COLLATE utf8_polish_ci NOT NULL DEFAULT 'SALE',
  `name` varchar(25) COLLATE utf8_polish_ci NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Zrzut danych tabeli `documents_family`
--

INSERT INTO `documents_family` (`id`, `name`) VALUES
('SALE', 'Dokumenty sprzedaży'),
('STORE', 'Dokumenty magazynowe'),
('OTHER', 'Pozostałe dokumenty'),
('PURCHASE', 'Dokumenty zakupu'),
('ORDER', 'Zamówienia'),
('CASH', 'Dokumenty kasowe');

-- --------------------------------------------------------

--
-- Struktura tabeli dla  `documents_nk`
--

CREATE TABLE IF NOT EXISTS `documents_nk` (
  `type` varchar(3) COLLATE utf8_polish_ci NOT NULL DEFAULT 'NK',
  `symbol` varchar(16) COLLATE utf8_polish_ci NOT NULL,
  `document_date` date NOT NULL,
  `issuer` int(10) unsigned NOT NULL,
  `receiver` int(10) unsigned NOT NULL,
  `invoice_symbol` varchar(16) COLLATE utf8_polish_ci NOT NULL,
  `invoice_date` date NOT NULL,
  `corrected_content` text COLLATE utf8_polish_ci NOT NULL,
  `correct_content` text COLLATE utf8_polish_ci NOT NULL,
  `document_place` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `receive_person` int(10) unsigned NOT NULL DEFAULT '0',
  `issue_person` int(10) unsigned NOT NULL DEFAULT '0',
  `isActive` tinyint(1) unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`symbol`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Zrzut danych tabeli `documents_nk`
--


-- --------------------------------------------------------

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
-- Zrzut danych tabeli `documents_positions`
--

INSERT INTO `documents_positions` (`document`, `good`, `quantity`, `price_net`, `tax_id`) VALUES
('FV/B/1/2011', 1, 1, '99.00', 3);

-- --------------------------------------------------------

--
-- Struktura tabeli dla  `document_places`
--

CREATE TABLE IF NOT EXISTS `document_places` (
  `id_place` tinyint(3) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(35) COLLATE utf8_polish_ci NOT NULL,
  PRIMARY KEY (`id_place`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci AUTO_INCREMENT=4 ;

--
-- Zrzut danych tabeli `document_places`
--

INSERT INTO `document_places` (`id_place`, `name`) VALUES
(1, 'Łódź');

-- --------------------------------------------------------

--
-- Struktura tabeli dla  `features`
--

CREATE TABLE IF NOT EXISTS `features` (
  `id_feature` smallint(5) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(40) COLLATE utf8_polish_ci NOT NULL,
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id_feature`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci AUTO_INCREMENT=1 ;

--
-- Zrzut danych tabeli `features`
--


-- --------------------------------------------------------

--
-- Struktura tabeli dla  `goods`
--

CREATE TABLE IF NOT EXISTS `goods` (
  `id_good` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `symbol` varchar(20) COLLATE utf8_polish_ci NOT NULL,
  `name` varchar(70) COLLATE utf8_polish_ci NOT NULL,
  `type` tinyint(1) unsigned NOT NULL DEFAULT '1',
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
  `weight` float NOT NULL DEFAULT '0',
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id_good`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci AUTO_INCREMENT=2 ;

--
-- Zrzut danych tabeli `goods`
--

INSERT INTO `goods` (`id_good`, `symbol`, `name`, `type`, `quantity`, `tax`, `unit`, `pkwiu`, `goods_group`, `price_a_net`, `price_a_gross`, `price_mag_net`, `price_mag_gross`, `price_b_net`, `price_b_gross`, `price_c_net`, `price_c_gross`, `description`, `foto`, `weight`, `isActive`) VALUES
(1, 'INSTALACJA WIN XP', 'Instalacja Win XP', 2, 0, 3, 1, '', 1, '99.00', '103.95', '0.00', '0.00', '0.00', '0.00', '0.00', '0.00', '', '', 0, 1);

-- --------------------------------------------------------

--
-- Struktura tabeli dla  `goods_future_values`
--

CREATE TABLE IF NOT EXISTS `goods_future_values` (
  `id_goods_future` tinyint(3) unsigned NOT NULL AUTO_INCREMENT,
  `good` int(10) unsigned NOT NULL,
  `feature` smallint(5) unsigned NOT NULL,
  `value` text COLLATE utf8_polish_ci NOT NULL,
  PRIMARY KEY (`id_goods_future`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci AUTO_INCREMENT=1 ;

--
-- Zrzut danych tabeli `goods_future_values`
--


-- --------------------------------------------------------

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
(1, 'Inne', 1);

-- --------------------------------------------------------

--
-- Struktura tabeli dla  `g_groups_features`
--

CREATE TABLE IF NOT EXISTS `g_groups_features` (
  `goods_group` smallint(5) unsigned DEFAULT NULL,
  `feature` smallint(5) unsigned DEFAULT NULL,
  `isActive` tinyint(1) NOT NULL DEFAULT '1'
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Zrzut danych tabeli `g_groups_features`
--


-- --------------------------------------------------------

--
-- Struktura tabeli dla  `linked_documents`
--

CREATE TABLE IF NOT EXISTS `linked_documents` (
  `base_document` varchar(16) COLLATE utf8_polish_ci NOT NULL,
  `linked_document` varchar(16) COLLATE utf8_polish_ci NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Zrzut danych tabeli `linked_documents`
--


-- --------------------------------------------------------

--
-- Struktura tabeli dla  `means_of_transport`
--

CREATE TABLE IF NOT EXISTS `means_of_transport` (
  `id_transport` smallint(6) NOT NULL AUTO_INCREMENT,
  `name` varchar(40) COLLATE utf8_polish_ci NOT NULL,
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id_transport`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci AUTO_INCREMENT=2 ;

--
-- Zrzut danych tabeli `means_of_transport`
--


-- --------------------------------------------------------

--
-- Struktura tabeli dla  `methods_of_payment`
--

CREATE TABLE IF NOT EXISTS `methods_of_payment` (
  `id_method` tinyint(3) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(35) COLLATE utf8_polish_ci DEFAULT NULL,
  `maturity` smallint(5) unsigned DEFAULT '0',
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id_method`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci AUTO_INCREMENT=5 ;

--
-- Zrzut danych tabeli `methods_of_payment`
--

INSERT INTO `methods_of_payment` (`id_method`, `name`, `maturity`, `isActive`) VALUES
(1, 'Gotówka', 0, 1),
(2, 'Przelew', 14, 1),
(3, 'Płacę z allegro', 0, 1);

-- --------------------------------------------------------

--
-- Struktura tabeli dla  `orders`
--

CREATE TABLE IF NOT EXISTS `orders` (
  `type` varchar(3) COLLATE utf8_polish_ci NOT NULL,
  `symbol` varchar(16) COLLATE utf8_polish_ci NOT NULL,
  `contractor` int(10) NOT NULL,
  `document_place` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `document_date` date NOT NULL,
  `realization_date` date NOT NULL,
  `total` decimal(10,2) NOT NULL,
  `discount` decimal(4,2) NOT NULL DEFAULT '0.00',
  `receive_person` int(10) unsigned NOT NULL DEFAULT '0',
  `issue_person` int(10) unsigned NOT NULL DEFAULT '0',
  `realized` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`symbol`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Zrzut danych tabeli `orders`
--


-- --------------------------------------------------------

--
-- Struktura tabeli dla  `people`
--

CREATE TABLE IF NOT EXISTS `people` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(70) COLLATE utf8_polish_ci NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci AUTO_INCREMENT=5 ;

--
-- Zrzut danych tabeli `people`
--

INSERT INTO `people` (`id`, `name`) VALUES
(1, 'Marczak Marcin'),
(2, 'Jakiś Klient'),
(3, 'Adam Orzeszko'),
(0, '');

-- --------------------------------------------------------

--
-- Struktura tabeli dla  `purchase_documents`
--

CREATE TABLE IF NOT EXISTS `purchase_documents` (
  `type` varchar(3) COLLATE utf8_polish_ci NOT NULL,
  `symbol` varchar(16) COLLATE utf8_polish_ci NOT NULL,
  `contractor` int(10) NOT NULL,
  `method_of_payment` tinyint(3) unsigned NOT NULL,
  `document_place` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `document_date` date NOT NULL,
  `sale_date` date NOT NULL,
  `payment_date` date NOT NULL,
  `total` decimal(10,2) NOT NULL,
  `discount` decimal(4,2) NOT NULL DEFAULT '0.00',
  `order` varchar(16) COLLATE utf8_polish_ci NOT NULL,
  `purchase_document` varchar(16) COLLATE utf8_polish_ci NOT NULL,
  `receive_person` int(10) unsigned NOT NULL DEFAULT '0',
  `issue_person` int(10) unsigned NOT NULL DEFAULT '0',
  `paid` tinyint(1) NOT NULL DEFAULT '1',
  `store_result` tinyint(1) NOT NULL DEFAULT '1',
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`symbol`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Zrzut danych tabeli `purchase_documents`
--


-- --------------------------------------------------------

--
-- Struktura tabeli dla  `sale_documents`
--

CREATE TABLE IF NOT EXISTS `sale_documents` (
  `type` varchar(3) COLLATE utf8_polish_ci NOT NULL,
  `symbol` varchar(16) COLLATE utf8_polish_ci NOT NULL,
  `contractor` int(10) unsigned NOT NULL,
  `method_of_payment` tinyint(3) unsigned NOT NULL,
  `document_place` tinyint(4) NOT NULL DEFAULT '1',
  `document_date` date NOT NULL,
  `sale_date` date NOT NULL,
  `payment_date` date NOT NULL,
  `total` decimal(10,2) NOT NULL,
  `discount` decimal(4,2) NOT NULL DEFAULT '0.00',
  `order_symbol` varchar(16) COLLATE utf8_polish_ci NOT NULL,
  `receive_person` int(10) unsigned NOT NULL DEFAULT '0',
  `issue_person` int(10) unsigned NOT NULL DEFAULT '0',
  `paid` tinyint(1) NOT NULL DEFAULT '1',
  `store_result` tinyint(1) NOT NULL DEFAULT '1',
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`symbol`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Zrzut danych tabeli `sale_documents`
--

INSERT INTO `sale_documents` (`type`, `symbol`, `contractor`, `method_of_payment`, `document_place`, `document_date`, `sale_date`, `payment_date`, `total`, `discount`, `order_symbol`, `receive_person`, `issue_person`, `paid`, `store_result`, `isActive`) VALUES
('FV', 'FV/B/1/2011', 1, 1, 1, '2011-07-28', '2011-07-28', '2011-07-28', '103.95', '0.00', '', 3, 1, 1, 0, 1);

-- --------------------------------------------------------

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
  `type` varchar(3) COLLATE utf8_polish_ci NOT NULL,
  `symbol` varchar(16) COLLATE utf8_polish_ci NOT NULL,
  `contractor` int(10) unsigned DEFAULT '0',
  `document_date` date DEFAULT NULL,
  `store_date` date DEFAULT NULL,
  `total` decimal(10,2) NOT NULL,
  `receive_person` int(10) unsigned NOT NULL DEFAULT '0',
  `issue_person` int(10) unsigned NOT NULL DEFAULT '0',
  `department` smallint(5) unsigned NOT NULL,
  `transport` smallint(6) NOT NULL DEFAULT '0',
  `store_result` tinyint(1) NOT NULL DEFAULT '1',
  `isActive` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`symbol`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Zrzut danych tabeli `store_documents`
--


-- --------------------------------------------------------

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

-- --------------------------------------------------------

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
