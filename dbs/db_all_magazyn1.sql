--
-- PostgreSQL database dump
--

SET statement_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

SET search_path = public, pg_catalog;

ALTER TABLE ONLY public.cash_documents DROP CONSTRAINT fk_cash_documents_recipment;
ALTER TABLE ONLY public.cash_documents DROP CONSTRAINT fk_cash_documents_contractor;
DROP INDEX public."unique_type_oldId";
DROP INDEX public."unique_type_newId";
DROP INDEX public.unique_goodsgroup_features;
DROP INDEX public.unique_doc_pos;
ALTER TABLE ONLY public.units DROP CONSTRAINT units_pkey;
ALTER TABLE ONLY public.taxes DROP CONSTRAINT taxes_pkey;
ALTER TABLE ONLY public.store_documents DROP CONSTRAINT store_documents_pkey;
ALTER TABLE ONLY public.sources_of_mem DROP CONSTRAINT sources_of_mem_pkey;
ALTER TABLE ONLY public.sale_documents DROP CONSTRAINT sale_documents_pkey;
ALTER TABLE ONLY public.purchase_documents DROP CONSTRAINT purchase_documents_pkey;
ALTER TABLE ONLY public.people DROP CONSTRAINT people_pkey;
ALTER TABLE ONLY public.orders DROP CONSTRAINT orders_pkey;
ALTER TABLE ONLY public.methods_of_payment DROP CONSTRAINT methods_of_payment_pkey;
ALTER TABLE ONLY public.means_of_transport DROP CONSTRAINT means_of_transport_pkey;
ALTER TABLE ONLY public.goods DROP CONSTRAINT goods_pkey;
ALTER TABLE ONLY public.goods_groups DROP CONSTRAINT goods_groups_pkey;
ALTER TABLE ONLY public.goods_future_values DROP CONSTRAINT goods_future_values_pkey;
ALTER TABLE ONLY public.features DROP CONSTRAINT features_pkey;
ALTER TABLE ONLY public.documents DROP CONSTRAINT documents_pkey;
ALTER TABLE ONLY public.documents_nk DROP CONSTRAINT documents_nk_pkey;
ALTER TABLE ONLY public.documents_family DROP CONSTRAINT documents_family_pkey;
ALTER TABLE ONLY public.document_places DROP CONSTRAINT document_places_pkey;
ALTER TABLE ONLY public.departments DROP CONSTRAINT departments_pkey;
ALTER TABLE ONLY public.contractors DROP CONSTRAINT contractors_pkey;
ALTER TABLE ONLY public.contractors_phones DROP CONSTRAINT contractors_phones_pkey;
ALTER TABLE ONLY public.contractors_groups DROP CONSTRAINT contractors_groups_pkey;
ALTER TABLE ONLY public.contractors_additional_ids DROP CONSTRAINT contractors_additional_ids_pkey;
ALTER TABLE ONLY public.cash_documents DROP CONSTRAINT cash_documents_pkey;
ALTER TABLE public.contractors ALTER COLUMN id_contractor DROP DEFAULT;
ALTER TABLE public.cache_history ALTER COLUMN id_temp DROP DEFAULT;
DROP TABLE public.units;
DROP SEQUENCE public.units_id_seq;
DROP TABLE public.taxes;
DROP SEQUENCE public.taxes_id_seq;
DROP TABLE public.store_documents;
DROP TABLE public.sources_of_mem;
DROP SEQUENCE public.sources_of_mem_id_seq;
DROP TABLE public.sale_documents;
DROP TABLE public.purchase_documents;
DROP TABLE public.people;
DROP SEQUENCE public.people_id_seq;
DROP TABLE public.orders;
DROP TABLE public.methods_of_payment;
DROP SEQUENCE public.methods_of_payment_id_seq;
DROP TABLE public.means_of_transport;
DROP SEQUENCE public.means_of_transport_id_seq;
DROP TABLE public.linked_documents;
DROP TABLE public.goods_groups;
DROP SEQUENCE public.goods_groups_id_seq;
DROP TABLE public.goods_future_values;
DROP SEQUENCE public.goods_future_values_id_seq;
DROP TABLE public.goods;
DROP SEQUENCE public.goods_id_seq;
DROP TABLE public.g_groups_features;
DROP TABLE public.features;
DROP SEQUENCE public.features_id_seq;
DROP TABLE public.documents_positions;
DROP TABLE public.documents_nk;
DROP TABLE public.documents_family;
DROP TABLE public.documents;
DROP TABLE public.document_places;
DROP SEQUENCE public.document_places_id_seq;
DROP TABLE public.departments;
DROP SEQUENCE public.departments_id_seq;
DROP TABLE public.contractors_phones;
DROP SEQUENCE public.contractors_phones_id_seq;
DROP SEQUENCE public.contractors_id_seq;
DROP TABLE public.contractors_groups;
DROP SEQUENCE public.contractors_groups_id_seq;
DROP TABLE public.contractors_additional_ids;
DROP SEQUENCE public.contractors_additional_ids_id_seq;
DROP TABLE public.contractors;
DROP TABLE public.cash_documents;
DROP SEQUENCE public.cache_history_id_temp_seq;
DROP TABLE public.cache_history;
DROP EXTENSION plpgsql;
DROP SCHEMA public;
--
-- Name: public; Type: SCHEMA; Schema: -; Owner: postgres
--

CREATE SCHEMA public;


ALTER SCHEMA public OWNER TO postgres;

--
-- Name: SCHEMA public; Type: COMMENT; Schema: -; Owner: postgres
--

COMMENT ON SCHEMA public IS 'standard public schema';


--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: cache_history; Type: TABLE; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE TABLE cache_history (
    type character varying(10) NOT NULL,
    old character varying(16) NOT NULL,
    new character varying(16) NOT NULL,
    id_temp integer NOT NULL
);


ALTER TABLE public.cache_history OWNER TO bbraces;

--
-- Name: cache_history_id_temp_seq; Type: SEQUENCE; Schema: public; Owner: bbraces
--

CREATE SEQUENCE cache_history_id_temp_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.cache_history_id_temp_seq OWNER TO bbraces;

--
-- Name: cache_history_id_temp_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: bbraces
--

ALTER SEQUENCE cache_history_id_temp_seq OWNED BY cache_history.id_temp;


--
-- Name: cache_history_id_temp_seq; Type: SEQUENCE SET; Schema: public; Owner: bbraces
--

SELECT pg_catalog.setval('cache_history_id_temp_seq', 24, true);


--
-- Name: cash_documents; Type: TABLE; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE TABLE cash_documents (
    type character varying(3) DEFAULT 'KP'::character varying NOT NULL,
    symbol character varying(16) NOT NULL,
    contractor integer NOT NULL,
    document_place smallint DEFAULT (1)::smallint NOT NULL,
    value numeric(10,2) NOT NULL,
    document_date date NOT NULL,
    payment_date date NOT NULL,
    document character varying(16) NOT NULL,
    title character varying(255) NOT NULL,
    receive_person integer NOT NULL,
    issue_person integer NOT NULL,
    description text NOT NULL,
    owner integer DEFAULT 1 NOT NULL,
    is_active boolean DEFAULT true NOT NULL
);


ALTER TABLE public.cash_documents OWNER TO bbraces;

SET default_with_oids = true;

--
-- Name: contractors; Type: TABLE; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE TABLE contractors (
    id_contractor integer NOT NULL,
    symbol character varying(70) NOT NULL,
    name text NOT NULL,
    contractor_group smallint DEFAULT (0)::smallint NOT NULL,
    type smallint DEFAULT (1)::smallint NOT NULL,
    postcode character varying(6) NOT NULL,
    city character varying(40) NOT NULL,
    adress character varying(60) NOT NULL,
    nip character varying(13) NOT NULL,
    additional_id_type smallint DEFAULT (1)::smallint NOT NULL,
    additional_id_value character varying(12) NOT NULL,
    discount numeric(4,2) DEFAULT 0.00 NOT NULL,
    additional character varying(60) NOT NULL,
    account_number character varying(34) NOT NULL,
    website character varying(60) NOT NULL,
    email character varying(60) NOT NULL,
    comments text NOT NULL,
    source_of_mem smallint DEFAULT (1)::smallint NOT NULL,
    representative character varying(70) NOT NULL,
    is_company boolean DEFAULT false,
    is_active boolean DEFAULT true
);


ALTER TABLE public.contractors OWNER TO bbraces;

--
-- Name: contractors_additional_ids_id_seq; Type: SEQUENCE; Schema: public; Owner: bbraces
--

CREATE SEQUENCE contractors_additional_ids_id_seq
    START WITH 4
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.contractors_additional_ids_id_seq OWNER TO bbraces;

--
-- Name: contractors_additional_ids_id_seq; Type: SEQUENCE SET; Schema: public; Owner: bbraces
--

SELECT pg_catalog.setval('contractors_additional_ids_id_seq', 5, true);


SET default_with_oids = false;

--
-- Name: contractors_additional_ids; Type: TABLE; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE TABLE contractors_additional_ids (
    id smallint DEFAULT nextval('contractors_additional_ids_id_seq'::regclass) NOT NULL,
    name character varying(25) NOT NULL
);


ALTER TABLE public.contractors_additional_ids OWNER TO bbraces;

--
-- Name: contractors_groups_id_seq; Type: SEQUENCE; Schema: public; Owner: bbraces
--

CREATE SEQUENCE contractors_groups_id_seq
    START WITH 13
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.contractors_groups_id_seq OWNER TO bbraces;

--
-- Name: contractors_groups_id_seq; Type: SEQUENCE SET; Schema: public; Owner: bbraces
--

SELECT pg_catalog.setval('contractors_groups_id_seq', 14, true);


--
-- Name: contractors_groups; Type: TABLE; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE TABLE contractors_groups (
    id_group smallint DEFAULT nextval('contractors_groups_id_seq'::regclass) NOT NULL,
    name character varying(60) NOT NULL,
    is_active boolean DEFAULT true NOT NULL
);


ALTER TABLE public.contractors_groups OWNER TO bbraces;

--
-- Name: contractors_id_seq; Type: SEQUENCE; Schema: public; Owner: bbraces
--

CREATE SEQUENCE contractors_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.contractors_id_seq OWNER TO bbraces;

--
-- Name: contractors_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: bbraces
--

ALTER SEQUENCE contractors_id_seq OWNED BY contractors.id_contractor;


--
-- Name: contractors_id_seq; Type: SEQUENCE SET; Schema: public; Owner: bbraces
--

SELECT pg_catalog.setval('contractors_id_seq', 65, true);


--
-- Name: contractors_phones_id_seq; Type: SEQUENCE; Schema: public; Owner: bbraces
--

CREATE SEQUENCE contractors_phones_id_seq
    START WITH 32
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.contractors_phones_id_seq OWNER TO bbraces;

--
-- Name: contractors_phones_id_seq; Type: SEQUENCE SET; Schema: public; Owner: bbraces
--

SELECT pg_catalog.setval('contractors_phones_id_seq', 39, true);


--
-- Name: contractors_phones; Type: TABLE; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE TABLE contractors_phones (
    id_contractors_phone integer DEFAULT nextval('contractors_phones_id_seq'::regclass) NOT NULL,
    contractor integer NOT NULL,
    phone_name character varying(60) NOT NULL,
    number character varying(20) NOT NULL,
    is_default smallint DEFAULT (0)::smallint NOT NULL
);


ALTER TABLE public.contractors_phones OWNER TO bbraces;

--
-- Name: departments_id_seq; Type: SEQUENCE; Schema: public; Owner: bbraces
--

CREATE SEQUENCE departments_id_seq
    START WITH 3
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.departments_id_seq OWNER TO bbraces;

--
-- Name: departments_id_seq; Type: SEQUENCE SET; Schema: public; Owner: bbraces
--

SELECT pg_catalog.setval('departments_id_seq', 3, false);


--
-- Name: departments; Type: TABLE; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE TABLE departments (
    id_department smallint DEFAULT nextval('departments_id_seq'::regclass) NOT NULL,
    name character varying(70) NOT NULL,
    is_active boolean DEFAULT true NOT NULL
);


ALTER TABLE public.departments OWNER TO bbraces;

--
-- Name: document_places_id_seq; Type: SEQUENCE; Schema: public; Owner: bbraces
--

CREATE SEQUENCE document_places_id_seq
    START WITH 5
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.document_places_id_seq OWNER TO bbraces;

--
-- Name: document_places_id_seq; Type: SEQUENCE SET; Schema: public; Owner: bbraces
--

SELECT pg_catalog.setval('document_places_id_seq', 5, false);


--
-- Name: document_places; Type: TABLE; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE TABLE document_places (
    id_place smallint DEFAULT nextval('document_places_id_seq'::regclass) NOT NULL,
    name character varying(35) NOT NULL
);


ALTER TABLE public.document_places OWNER TO bbraces;

--
-- Name: documents; Type: TABLE; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE TABLE documents (
    type character varying(3) NOT NULL,
    name character varying(30) NOT NULL,
    numbering character varying(18) NOT NULL,
    last_symbol character varying(16) NOT NULL,
    after_text text NOT NULL,
    family character varying(10) DEFAULT 'SALE'::character varying NOT NULL
);


ALTER TABLE public.documents OWNER TO bbraces;

--
-- Name: documents_family; Type: TABLE; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE TABLE documents_family (
    id character varying(10) DEFAULT 'SALE'::character varying NOT NULL,
    name character varying(25) NOT NULL
);


ALTER TABLE public.documents_family OWNER TO bbraces;

--
-- Name: documents_nk; Type: TABLE; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE TABLE documents_nk (
    type character varying(3) DEFAULT 'NK'::character varying NOT NULL,
    symbol character varying(16) NOT NULL,
    document_date date NOT NULL,
    contractor integer NOT NULL,
    invoice_symbol character varying(16) NOT NULL,
    invoice_date date NOT NULL,
    corrected_content text NOT NULL,
    correct_content text NOT NULL,
    document_place smallint DEFAULT (1)::smallint NOT NULL,
    receive_person integer DEFAULT 0 NOT NULL,
    issue_person integer DEFAULT 0 NOT NULL,
    owner smallint DEFAULT (1)::smallint NOT NULL,
    is_active boolean DEFAULT true NOT NULL
);


ALTER TABLE public.documents_nk OWNER TO bbraces;

--
-- Name: documents_positions; Type: TABLE; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE TABLE documents_positions (
    document character varying(16) NOT NULL,
    good integer NOT NULL,
    quantity double precision NOT NULL,
    price_net numeric(10,2) NOT NULL,
    tax_id smallint DEFAULT (1)::smallint NOT NULL
);


ALTER TABLE public.documents_positions OWNER TO bbraces;

--
-- Name: features_id_seq; Type: SEQUENCE; Schema: public; Owner: bbraces
--

CREATE SEQUENCE features_id_seq
    START WITH 6
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.features_id_seq OWNER TO bbraces;

--
-- Name: features_id_seq; Type: SEQUENCE SET; Schema: public; Owner: bbraces
--

SELECT pg_catalog.setval('features_id_seq', 6, false);


--
-- Name: features; Type: TABLE; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE TABLE features (
    id_feature smallint DEFAULT nextval('features_id_seq'::regclass) NOT NULL,
    name character varying(40) NOT NULL,
    is_active boolean DEFAULT true NOT NULL
);


ALTER TABLE public.features OWNER TO bbraces;

--
-- Name: g_groups_features; Type: TABLE; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE TABLE g_groups_features (
    goods_group smallint,
    feature smallint
);


ALTER TABLE public.g_groups_features OWNER TO bbraces;

--
-- Name: goods_id_seq; Type: SEQUENCE; Schema: public; Owner: bbraces
--

CREATE SEQUENCE goods_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.goods_id_seq OWNER TO bbraces;

--
-- Name: goods_id_seq; Type: SEQUENCE SET; Schema: public; Owner: bbraces
--

SELECT pg_catalog.setval('goods_id_seq', 23, true);


--
-- Name: goods; Type: TABLE; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE TABLE goods (
    id_good integer DEFAULT nextval('goods_id_seq'::regclass) NOT NULL,
    symbol character varying(70) NOT NULL,
    name character varying(70) NOT NULL,
    type smallint DEFAULT (1)::smallint NOT NULL,
    quantity double precision DEFAULT (0)::double precision NOT NULL,
    tax smallint DEFAULT (1)::smallint NOT NULL,
    unit smallint DEFAULT (1)::smallint NOT NULL,
    pkwiu character varying(25) NOT NULL,
    goods_group smallint DEFAULT (1)::smallint NOT NULL,
    price_a_net numeric(10,2) NOT NULL,
    price_a_gross numeric(10,2) NOT NULL,
    price_mag_net numeric(10,2) NOT NULL,
    price_mag_gross numeric(10,2) NOT NULL,
    price_b_net numeric(10,2) NOT NULL,
    price_b_gross numeric(10,2) NOT NULL,
    price_c_net numeric(10,2) NOT NULL,
    price_c_gross numeric(10,2) NOT NULL,
    description text NOT NULL,
    foto character varying(180) NOT NULL,
    weight double precision DEFAULT (0)::double precision NOT NULL,
    is_active boolean DEFAULT true NOT NULL
);


ALTER TABLE public.goods OWNER TO bbraces;

--
-- Name: goods_future_values_id_seq; Type: SEQUENCE; Schema: public; Owner: bbraces
--

CREATE SEQUENCE goods_future_values_id_seq
    START WITH 34
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.goods_future_values_id_seq OWNER TO bbraces;

--
-- Name: goods_future_values_id_seq; Type: SEQUENCE SET; Schema: public; Owner: bbraces
--

SELECT pg_catalog.setval('goods_future_values_id_seq', 34, true);


--
-- Name: goods_future_values; Type: TABLE; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE TABLE goods_future_values (
    id_goods_future smallint DEFAULT nextval('goods_future_values_id_seq'::regclass) NOT NULL,
    good integer NOT NULL,
    feature smallint NOT NULL,
    value text NOT NULL
);


ALTER TABLE public.goods_future_values OWNER TO bbraces;

--
-- Name: goods_groups_id_seq; Type: SEQUENCE; Schema: public; Owner: bbraces
--

CREATE SEQUENCE goods_groups_id_seq
    START WITH 6
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.goods_groups_id_seq OWNER TO bbraces;

--
-- Name: goods_groups_id_seq; Type: SEQUENCE SET; Schema: public; Owner: bbraces
--

SELECT pg_catalog.setval('goods_groups_id_seq', 6, false);


--
-- Name: goods_groups; Type: TABLE; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE TABLE goods_groups (
    id_group smallint DEFAULT nextval('goods_groups_id_seq'::regclass) NOT NULL,
    name character varying(60) NOT NULL,
    is_active boolean DEFAULT true NOT NULL
);


ALTER TABLE public.goods_groups OWNER TO bbraces;

--
-- Name: linked_documents; Type: TABLE; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE TABLE linked_documents (
    base_document character varying(16) NOT NULL,
    linked_document character varying(16) NOT NULL
);


ALTER TABLE public.linked_documents OWNER TO bbraces;

--
-- Name: means_of_transport_id_seq; Type: SEQUENCE; Schema: public; Owner: bbraces
--

CREATE SEQUENCE means_of_transport_id_seq
    START WITH 4
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.means_of_transport_id_seq OWNER TO bbraces;

--
-- Name: means_of_transport_id_seq; Type: SEQUENCE SET; Schema: public; Owner: bbraces
--

SELECT pg_catalog.setval('means_of_transport_id_seq', 4, false);


--
-- Name: means_of_transport; Type: TABLE; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE TABLE means_of_transport (
    id_transport smallint DEFAULT nextval('means_of_transport_id_seq'::regclass) NOT NULL,
    name character varying(40) NOT NULL,
    is_active boolean DEFAULT true NOT NULL
);


ALTER TABLE public.means_of_transport OWNER TO bbraces;

--
-- Name: methods_of_payment_id_seq; Type: SEQUENCE; Schema: public; Owner: bbraces
--

CREATE SEQUENCE methods_of_payment_id_seq
    START WITH 4
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.methods_of_payment_id_seq OWNER TO bbraces;

--
-- Name: methods_of_payment_id_seq; Type: SEQUENCE SET; Schema: public; Owner: bbraces
--

SELECT pg_catalog.setval('methods_of_payment_id_seq', 4, false);


--
-- Name: methods_of_payment; Type: TABLE; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE TABLE methods_of_payment (
    id_method smallint DEFAULT nextval('methods_of_payment_id_seq'::regclass) NOT NULL,
    name character varying(35) DEFAULT NULL::character varying,
    maturity smallint DEFAULT (0)::smallint,
    is_active boolean DEFAULT true NOT NULL
);


ALTER TABLE public.methods_of_payment OWNER TO bbraces;

--
-- Name: orders; Type: TABLE; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE TABLE orders (
    type character varying(3) NOT NULL,
    symbol character varying(16) NOT NULL,
    contractor integer NOT NULL,
    document_place smallint DEFAULT (1)::smallint NOT NULL,
    document_date date NOT NULL,
    realization_date date NOT NULL,
    total numeric(10,2) NOT NULL,
    discount numeric(4,2) DEFAULT 0.00 NOT NULL,
    receive_person integer DEFAULT 0 NOT NULL,
    issue_person integer DEFAULT 0 NOT NULL,
    realized smallint DEFAULT (0)::smallint NOT NULL,
    owner smallint DEFAULT (1)::smallint NOT NULL,
    is_active boolean DEFAULT true NOT NULL
);


ALTER TABLE public.orders OWNER TO bbraces;

--
-- Name: people_id_seq; Type: SEQUENCE; Schema: public; Owner: bbraces
--

CREATE SEQUENCE people_id_seq
    START WITH 106
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.people_id_seq OWNER TO bbraces;

--
-- Name: people_id_seq; Type: SEQUENCE SET; Schema: public; Owner: bbraces
--

SELECT pg_catalog.setval('people_id_seq', 108, true);


--
-- Name: people; Type: TABLE; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE TABLE people (
    id integer DEFAULT nextval('people_id_seq'::regclass) NOT NULL,
    name character varying(70) NOT NULL
);


ALTER TABLE public.people OWNER TO bbraces;

--
-- Name: purchase_documents; Type: TABLE; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE TABLE purchase_documents (
    type character varying(3) NOT NULL,
    symbol character varying(16) NOT NULL,
    contractor integer NOT NULL,
    method_of_payment smallint NOT NULL,
    document_place smallint DEFAULT (1)::smallint NOT NULL,
    document_date date NOT NULL,
    purchase_date date NOT NULL,
    payment_date date NOT NULL,
    total numeric(10,2) NOT NULL,
    discount numeric(4,2) DEFAULT 0.00 NOT NULL,
    order_symbol character varying(16) NOT NULL,
    purchase_document character varying(16) NOT NULL,
    receive_person integer DEFAULT 0 NOT NULL,
    issue_person integer DEFAULT 0 NOT NULL,
    is_paid boolean DEFAULT true NOT NULL,
    store_result boolean DEFAULT true NOT NULL,
    owner smallint DEFAULT (1)::smallint NOT NULL,
    is_active boolean DEFAULT true NOT NULL
);


ALTER TABLE public.purchase_documents OWNER TO bbraces;

--
-- Name: sale_documents; Type: TABLE; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE TABLE sale_documents (
    type character varying(3) NOT NULL,
    symbol character varying(16) NOT NULL,
    contractor integer NOT NULL,
    method_of_payment smallint NOT NULL,
    document_place smallint DEFAULT (1)::smallint NOT NULL,
    document_date date NOT NULL,
    sale_date date NOT NULL,
    payment_date date NOT NULL,
    total numeric(10,2) NOT NULL,
    paid numeric(10,2) DEFAULT 0 NOT NULL,
    discount numeric(4,2) DEFAULT 0.00 NOT NULL,
    order_symbol character varying(16) NOT NULL,
    receive_person integer DEFAULT 0 NOT NULL,
    issue_person integer DEFAULT 0 NOT NULL,
    is_paid boolean DEFAULT true NOT NULL,
    store_result boolean DEFAULT true NOT NULL,
    owner smallint DEFAULT (1)::smallint NOT NULL,
    is_active boolean DEFAULT true NOT NULL
);


ALTER TABLE public.sale_documents OWNER TO bbraces;

--
-- Name: sources_of_mem_id_seq; Type: SEQUENCE; Schema: public; Owner: bbraces
--

CREATE SEQUENCE sources_of_mem_id_seq
    START WITH 5
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.sources_of_mem_id_seq OWNER TO bbraces;

--
-- Name: sources_of_mem_id_seq; Type: SEQUENCE SET; Schema: public; Owner: bbraces
--

SELECT pg_catalog.setval('sources_of_mem_id_seq', 5, false);


--
-- Name: sources_of_mem; Type: TABLE; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE TABLE sources_of_mem (
    id_source smallint DEFAULT nextval('sources_of_mem_id_seq'::regclass) NOT NULL,
    name character varying(60) NOT NULL,
    is_active boolean DEFAULT true NOT NULL
);


ALTER TABLE public.sources_of_mem OWNER TO bbraces;

--
-- Name: store_documents; Type: TABLE; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE TABLE store_documents (
    type character varying(3) NOT NULL,
    symbol character varying(16) NOT NULL,
    contractor integer DEFAULT 0,
    document_place smallint DEFAULT (1)::smallint NOT NULL,
    document_date date,
    store_date date,
    total numeric(10,2) NOT NULL,
    receive_person integer DEFAULT 0 NOT NULL,
    issue_person integer DEFAULT 0 NOT NULL,
    department smallint NOT NULL,
    transport smallint DEFAULT (0)::smallint NOT NULL,
    shipping smallint NOT NULL,
    waybill_number character varying(15) NOT NULL,
    store_result boolean DEFAULT true NOT NULL,
    owner smallint DEFAULT (1)::smallint NOT NULL,
    is_active boolean DEFAULT true NOT NULL
);


ALTER TABLE public.store_documents OWNER TO bbraces;

--
-- Name: taxes_id_seq; Type: SEQUENCE; Schema: public; Owner: bbraces
--

CREATE SEQUENCE taxes_id_seq
    START WITH 7
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.taxes_id_seq OWNER TO bbraces;

--
-- Name: taxes_id_seq; Type: SEQUENCE SET; Schema: public; Owner: bbraces
--

SELECT pg_catalog.setval('taxes_id_seq', 8, true);


--
-- Name: taxes; Type: TABLE; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE TABLE taxes (
    id_tax smallint DEFAULT nextval('taxes_id_seq'::regclass) NOT NULL,
    name character varying(50) NOT NULL,
    value numeric(4,2) NOT NULL,
    active_in_app boolean DEFAULT true NOT NULL,
    is_active boolean DEFAULT true NOT NULL,
    short_name character varying(6) DEFAULT ''::character varying NOT NULL
);


ALTER TABLE public.taxes OWNER TO bbraces;

--
-- Name: units_id_seq; Type: SEQUENCE; Schema: public; Owner: bbraces
--

CREATE SEQUENCE units_id_seq
    START WITH 6
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.units_id_seq OWNER TO bbraces;

--
-- Name: units_id_seq; Type: SEQUENCE SET; Schema: public; Owner: bbraces
--

SELECT pg_catalog.setval('units_id_seq', 6, false);


--
-- Name: units; Type: TABLE; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE TABLE units (
    id_unit smallint DEFAULT nextval('units_id_seq'::regclass) NOT NULL,
    name character varying(5) NOT NULL,
    zero_places smallint DEFAULT (2)::smallint NOT NULL,
    is_active boolean DEFAULT true NOT NULL
);


ALTER TABLE public.units OWNER TO bbraces;

--
-- Name: id_temp; Type: DEFAULT; Schema: public; Owner: bbraces
--

ALTER TABLE cache_history ALTER COLUMN id_temp SET DEFAULT nextval('cache_history_id_temp_seq'::regclass);


--
-- Name: id_contractor; Type: DEFAULT; Schema: public; Owner: bbraces
--

ALTER TABLE contractors ALTER COLUMN id_contractor SET DEFAULT nextval('contractors_id_seq'::regclass);


--
-- Data for Name: cache_history; Type: TABLE DATA; Schema: public; Owner: bbraces
--

INSERT INTO cache_history VALUES ('CON', '3', '33', 1);
INSERT INTO cache_history VALUES ('CON', '6', '34', 2);
INSERT INTO cache_history VALUES ('CON', '33', '35', 3);
INSERT INTO cache_history VALUES ('CON', '35', '36', 4);
INSERT INTO cache_history VALUES ('CON', '23', '37', 5);
INSERT INTO cache_history VALUES ('GOOD', '7', '9', 6);
INSERT INTO cache_history VALUES ('CON', '34', '39', 7);
INSERT INTO cache_history VALUES ('OWNER', '1', '6', 8);
INSERT INTO cache_history VALUES ('CON', '21', '62', 17);
INSERT INTO cache_history VALUES ('CON', '32', '63', 18);
INSERT INTO cache_history VALUES ('CON', '30', '64', 19);
INSERT INTO cache_history VALUES ('CON', '57', '65', 20);
INSERT INTO cache_history VALUES ('GOOD', '3', '23', 24);


--
-- Data for Name: cash_documents; Type: TABLE DATA; Schema: public; Owner: bbraces
--

INSERT INTO cash_documents VALUES ('KP', 'KP/1/2011', 1, 1, 4919.76, '2011-05-31', '2011-05-31', 'FV/5/2011', 'Wpłata za: FV/5/2011', 7, 1, '', 1, true);
INSERT INTO cash_documents VALUES ('KP', 'KP/2/2011', 6, 1, 3100.00, '2011-07-16', '2011-07-16', 'FV/6/2011', 'Wpłata za: FV/6/2011', 9, 1, '', 1, true);


--
-- Data for Name: contractors; Type: TABLE DATA; Schema: public; Owner: bbraces
--

INSERT INTO contractors VALUES (1, 'FILIP KOZAKIEWICZ', 'Filip Kozakiewicz', 3, 1, '42-200', 'Częstochowa', 'Wypizdówek 12', '834-500-14-85', 1, '945-102-754', 3.00, '-', '74 1140 2004 0000 3002 3862 8149', '', '', 'http://www.milczarek.it/testDlugiegoUrl', 2, '', false, true);
INSERT INTO contractors VALUES (65, 'SOLIMO KATARZYNA', 'Solimo Katarzyna', 2, 1, '64-100', 'Leszno', 'Gałczyńska 65', '834-100-11-05', 1, '945-102-754', 1.00, '', '74 1140 2004 0000 3002 3862 8149', 'http://www.milczarek.it/testDlugiegoUrl', 'jakismail@wjakiejsdomenie.pl', '', 2, '', false, true);
INSERT INTO contractors VALUES (3, 'KUPAŁA ADAM', 'Kupała Adam', 2, 1, '40-200', 'Katowice', 'Warchlewo 145', '834521121', 1, '754121211', 1.00, '', '      ', '', '', '', 1, '', false, false);
INSERT INTO contractors VALUES (6, 'PASIKONIK MARIUSZ', 'Pasikonik Mariusz', 3, 1, '99-400', 'Łowicz', 'Milczarskiego 14/7', '', 1, '', 0.00, '', '', '', 'email@gmail.com', '', 1, '', false, false);
INSERT INTO contractors VALUES (7, 'PROGRAMMER SP J', 'Programmer sp. j.', 1, 1, '99-100', 'Łęczyca', 'Wypizdówek 127', '834-500-14-85', 1, '945-102-754', 6.00, 'KRS 0000000980', '74 1140 2004 0000 3002 3862 8149', 'http://www.milczarek.it/testDlugiegoUrl', 'jakismail@wjakiejsdomenie.pl', 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Duis iaculis iaculis ipsum et congue. Etiam mollis arcu metus. Morbi vel lorem sapien, sit amet consequat felis. Sed tempor vestibulum risus sed lobortis. Aenean pretium, risus id eleifend feugiat, erat est ornare justo, eget sollicitudin sem diam sit amet dui. Maecenas orci lectus, suscipit eu sollicitudin id, rhoncus ac augue.', 2, 'Majcher Tadeusz', true, true);
INSERT INTO contractors VALUES (16, 'KOLEJNY TEST', 'Kolejny test', 0, 1, '99-413', 'Chąśno', 'Zagórska 21', '', 1, '', 5.00, '', '12 3131 3216 5646 4646 4646 4645', '', '', '', 1, '', false, true);
INSERT INTO contractors VALUES (17, 'BUDZYŃ TOMASZ', 'Budzyń Tomasz', 3, 1, '90-319', 'Łódź', 'Kilińskiego 120', '8341001185', 1, '65471001185', 1.00, 'KRS 145210224', '74 1024 0000 2004 2132 1156 1316', 'www.budzyn.pl', 'tomasz@budzyn.pl', 'Kontrahent nastawiony za zakup hurtowy', 2, '', false, true);
INSERT INTO contractors VALUES (22, 'KLAMKA', 'Klamka', 3, 3, '88-400', 'Żnin', 'wakowo 15', '', 1, '', 0.00, '', '      ', '', '', '', 1, '', false, true);
INSERT INTO contractors VALUES (23, 'MARCZAK STANISŁAW', 'Marczak Stanisław', 3, 3, '88-150', 'Kruszwica', 'Walidacyjna 1/5', '', 1, '', 0.00, '', '      ', '', '', '', 1, '', false, false);
INSERT INTO contractors VALUES (25, 'MAKOWSKI TRADING SP Z OO', 'Makowski Trading sp. z o.o.', 2, 3, '44-100', 'Gliwice', 'Chełmińska 125', '754-123-12-12', 1, '', 0.00, '', '      ', '', '', '', 1, 'Makowski Dariusz', true, true);
INSERT INTO contractors VALUES (26, 'KALIŃSKI STEFAN', 'Kaliński Stefan', 1, 3, '74-200', 'Pyrzyce', 'Karlicka 124', '', 1, '', 0.00, '', '      ', '', '', '', 1, '', false, true);
INSERT INTO contractors VALUES (29, 'WOLIŃSKI & KIESZKOWSKI MEBLE SP J', 'Woliński & Kieszkowski Meble sp. j.', 1, 3, '66-200', 'Świebodzin', 'Krynicka 121', '524-142-12-74', 1, '', 0.00, '', '      ', '', '', '', 1, 'Woliński Mariusz', true, true);
INSERT INTO contractors VALUES (33, 'KUPAŁA ADAM', 'Kupała Adam', 2, 1, '40-200', 'Katowice', 'Warchlewo 188', '834521121', 1, '754121211', 1.00, '', '      ', '', '', '', 1, '', false, false);
INSERT INTO contractors VALUES (34, 'PASIKONIK MARIUSZ', 'Pasikonik Mariusz', 3, 1, '99-400', 'Łowicz', 'Milczarskiego 14/8', '', 1, '', 0.00, '', '      ', '', 'email@gmail.com', '', 1, '', false, false);
INSERT INTO contractors VALUES (35, 'KUPAŁA ADAM', 'Kupała Adam', 2, 1, '40-200', 'Katowice', 'Warchlewo 15', '834521121', 1, '754121211', 1.00, '', '      ', '', '', '', 1, '', false, false);
INSERT INTO contractors VALUES (36, 'KUPAŁA ADAM', 'Kupała Adam', 2, 1, '40-200', 'Katowice', 'Warchlewo 1000', '834521121', 1, '754121211', 1.00, '', '      ', '', '', '', 1, '', false, true);
INSERT INTO contractors VALUES (37, 'MARCZAK STANISŁAW', 'Marczak Stanisław', 3, 1, '88-150', 'Kruszwica', 'Walidacyjna 1/50', '', 1, '', 0.00, '', '      ', '', '', '', 1, '', false, true);
INSERT INTO contractors VALUES (39, 'PASIKONIK MARIUSZ', 'Pasikonik Mariusz', 3, 3, '99-400', 'Łowicz', 'Milczarskiego 14/8', '', 1, '', 0.00, '', '      ', '', 'email@gmail.com', '', 1, '', false, true);
INSERT INTO contractors VALUES (43, 'MAKOWICZ TADUESZ	', 'Makowicz Taduesz	', 3, 1, '99-400', 'Łowicz', 'Halamy 54', '', 0, '', 0.00, '', '      ', '', '', '', 1, '', false, true);
INSERT INTO contractors VALUES (44, 'KOZERAWSKI TOMASZ', 'Kozerawski Tomasz', 2, 1, '87-200', 'Wąbrzeźno', 'Kaliska 14/5', '', 0, '', 0.00, '', '      ', '', '', '', 1, '', false, true);
INSERT INTO contractors VALUES (45, 'KOZAKIEWICZ MARTYNA', 'Kozakiewicz Martyna', 2, 1, '87-200', 'Wąbrzeźno', 'Jąkalska 21', '', 0, '', 0.00, '', '      ', '', '', '', 1, '', false, true);
INSERT INTO contractors VALUES (46, 'KAZIEWICZ ADAM', 'Kaziewicz Adam', 2, 1, '95-500', 'Małszyce', 'Wagowa 15', '', 0, '', 0.00, '', '      ', '', '', '', 1, '', false, true);
INSERT INTO contractors VALUES (47, 'POMARAŃSKI JAN', 'Pomarański Jan', 0, 1, '99-400', 'Łowicz', 'Kalińska 54', '', 0, '', 0.00, '', '      ', '', '', '', 1, '', false, true);
INSERT INTO contractors VALUES (48, 'MAKOWSKI HENRYK', 'Makowski Henryk', 2, 1, '64-200', 'Wolsztyn', 'Kawowa 17', '', 0, '', 0.00, '', '      ', '', '', '', 1, '', false, true);
INSERT INTO contractors VALUES (49, 'KORLIŃSKI PIOTR', 'Korliński Piotr', 0, 1, '25-100', 'Remberowo', 'Wakacyjna 15', '', 0, '', 0.00, '', '      ', '', '', '', 1, '', false, true);
INSERT INTO contractors VALUES (51, 'GALEREWICZ WŁADYSŁAW', 'Galerewicz Władysław', 0, 1, '32-410', 'Dobczyce', 'Korlewp 6', '', 0, '', 0.00, '', '      ', '', '', '', 1, '', false, true);
INSERT INTO contractors VALUES (52, 'KŁOS TOMASZ', 'Kłos Tomasz', 0, 1, '62-400', 'Słupca', 'Łęczycka 5', '', 0, '', 0.00, '', '      ', '', '', '', 1, '', false, true);
INSERT INTO contractors VALUES (53, 'KAWALEROWICZ PAWEŁ', 'Kawalerowicz Paweł', 0, 1, '54-300', 'Malewo', 'Końska 51', '', 0, '', 0.00, '', '      ', '', '', '', 1, '', false, true);
INSERT INTO contractors VALUES (55, 'KOWALEWICZ ŁUKASZ', 'Kowalewicz Łukasz', 0, 1, '87-100', 'Toruń', 'Gdańska 150', '', 0, '', 0.00, '', '      ', '', '', '', 1, '', false, true);
INSERT INTO contractors VALUES (56, 'MALEC WANDA', 'Malec Wanda', 2, 1, '65-200', 'Kazuń', 'Emilii Plater 100', '', 0, '', 0.00, '', '      ', '', '', '', 1, '', false, true);
INSERT INTO contractors VALUES (27, 'SKOWROŃSKI TYMON', 'Skowroński Tymon', 1, 1, '33-100', 'Tarnów', 'Gliwicka 153', '', 1, '', 0.00, '', '      ', '', '', '', 1, '', false, false);
INSERT INTO contractors VALUES (54, 'WACHOWSKI ADRIAN', 'Wachowski Adrian', 0, 1, '99-400', 'Łowicz', 'Kolonia Brzezińska 15', '', 0, '', 0.00, '', '      ', '', '', '', 1, '', false, false);
INSERT INTO contractors VALUES (30, 'MIZIOŁEK FRANCISZEK', 'Miziołek Franciszek', 1, 2, '40-150', 'Katowice', 'Waracka 2/14', '154-045-25-25', 1, '', 0.00, '', '      ', '', '', '', 1, '', false, false);
INSERT INTO contractors VALUES (24, 'KOWALSKI TADEUSZ', 'Kowalski Tadeusz', 1, 1, '99-400', 'Łowicz', 'Poniatowskiego 60', '834-100-11-05', 1, '', 0.00, '', '      ', '', '', '', 1, '', false, true);
INSERT INTO contractors VALUES (28, 'MAJHER MARJAN', 'Majher Marjan', 12, 1, '44-100', 'Gliwice', 'Malewicka 147', '', 1, '', 0.00, '', '      ', '', '', '', 1, '', false, true);
INSERT INTO contractors VALUES (50, 'KORLIŃSKI PIOTR', 'Korliński Piotr', 0, 1, '24-200', 'Bełżyce', 'Walewska 165', '', 0, '', 0.00, '', '      ', '', '', '', 1, '', false, true);
INSERT INTO contractors VALUES (31, 'KLECZYŃSKI STANISŁAW', 'Kleczyński Stanisław', 1, 1, '55-300', 'Środa Śląska', 'Śląska 70', '', 1, '', 0.00, '', '      ', '', '', '', 1, '', false, true);
INSERT INTO contractors VALUES (40, 'WARACKI PRZEMYSŁAW', 'Waracki Przemysław', 0, 2, '99-400', 'Łowicz', 'Pomorska 187', '', 1, '', 0.00, '', '      ', '', '', '', 1, '', false, true);
INSERT INTO contractors VALUES (21, 'POMORSKI STANISŁAW', 'Pomorski stanisław', 1, 3, '88-200', 'Radziejów', 'Kowalewicza 15', '', 1, '', 0.00, '', '      ', '', '', '', 1, '', false, false);
INSERT INTO contractors VALUES (32, 'MICHANIUK ADAM', 'Michaniuk Adam', 1, 2, '32-100', 'Proszowice', 'Horyzontalna 1', '', 1, '', 0.00, '', '      ', '', '', '', 1, '', false, false);
INSERT INTO contractors VALUES (57, 'SOLIMO KATARZYNA', 'Solimo Katarzyna', 2, 1, '64-100', 'Leszno', 'Gałczyńska 60', '834-100-11-05', 1, '945-102-754', 1.00, '', '74 1140 2004 0000 3002 3862 8149', 'http://www.milczarek.it/testDlugiegoUrl', 'jakismail@wjakiejsdomenie.pl', '', 2, '', false, false);
INSERT INTO contractors VALUES (2, 'SOLIMO KATARZYNA', 'Solimo Katarzyna', 2, 1, '64-100', 'Leszno', 'Gałczyńska 60', '834-100-11-05', 1, '945-102-754', 1.00, '', '74 1140 2004 0000 3002 3862 8149', 'http://www.milczarek.it/testDlugiegoUrl', 'jakismail@wjakiejsdomenie.pl', '', 2, '', false, false);
INSERT INTO contractors VALUES (58, 'SKOWROŃSKI TYMON', 'Skowroński Tymon', 1, 3, '33-100', 'Tarnów', 'Gliwicka 153', '', 1, '', 0.00, '', '      ', '', '', '', 1, '', false, true);
INSERT INTO contractors VALUES (61, 'CODEARTS SP Z OO', 'CodeArts sp. z o.o.', 1, 1, '64-200', 'Wolsztyn', 'Kielecka', '', 1, '', 0.00, '', '      ', '', '', '', 1, '', false, true);
INSERT INTO contractors VALUES (60, 'CODEARTS SP Z OO', 'CodeArts sp. z o.o.', 1, 3, '64-200', 'Wolsztyn', 'Kielecka', '', 1, '', 0.00, '', '      ', '', '', '', 1, '', false, false);
INSERT INTO contractors VALUES (59, 'WACHOWSKI ADRIAN', 'Wachowski Adrian', 0, 2, '99-400', 'Łowicz', 'Kolonia Brzezińska 15', '', 0, '', 0.00, '', '      ', '', '', '', 1, '', false, true);
INSERT INTO contractors VALUES (62, 'POMORSKI STANISŁAW', 'Pomorski stanisław', 1, 1, '88-200', 'Radziejów', 'Kowalewicza 15', '', 1, '', 0.00, '', '      ', '', '', '', 1, '', false, true);
INSERT INTO contractors VALUES (63, 'MICHANIUK ADAM', 'Michaniuk Adam', 1, 1, '32-100', 'Proszowice', 'Horyzontalna 1', '', 1, '', 0.00, '', '      ', '', '', '', 1, '', false, true);
INSERT INTO contractors VALUES (64, 'MIZIOŁEK FRANCISZEK', 'Miziołek Franciszek', 1, 1, '40-150', 'Katowice', 'Waracka 2/14', '154-045-25-25', 1, '', 0.00, '', '      ', '', '', '', 1, '', false, true);


--
-- Data for Name: contractors_additional_ids; Type: TABLE DATA; Schema: public; Owner: bbraces
--

INSERT INTO contractors_additional_ids VALUES (1, 'REGON');
INSERT INTO contractors_additional_ids VALUES (2, 'PESEL');
INSERT INTO contractors_additional_ids VALUES (3, 'Dowód osobisty');
INSERT INTO contractors_additional_ids VALUES (4, 'Paszport');


--
-- Data for Name: contractors_groups; Type: TABLE DATA; Schema: public; Owner: bbraces
--

INSERT INTO contractors_groups VALUES (1, 'Podstawowa', true);
INSERT INTO contractors_groups VALUES (2, 'Odbiorca zagraniczny', true);
INSERT INTO contractors_groups VALUES (3, 'Kluczowy klient', true);
INSERT INTO contractors_groups VALUES (12, 'Hurtownicy', true);
INSERT INTO contractors_groups VALUES (11, 'Test', false);
INSERT INTO contractors_groups VALUES (10, 'Dostawca', false);
INSERT INTO contractors_groups VALUES (14, 'ASD', true);


--
-- Data for Name: contractors_phones; Type: TABLE DATA; Schema: public; Owner: bbraces
--

INSERT INTO contractors_phones VALUES (1, 1, '', '780-120-485', 0);
INSERT INTO contractors_phones VALUES (2, 1, '', '46 839-15-14', 0);
INSERT INTO contractors_phones VALUES (3, 2, 'sekretariat', '62 784-02-14', 0);
INSERT INTO contractors_phones VALUES (4, 2, 'Dział Logistyczny', '62 784-87-63', 1);
INSERT INTO contractors_phones VALUES (5, 2, 'Nowak', '603 021 150', 0);
INSERT INTO contractors_phones VALUES (6, 11, 'tel.', '780-401-042', 0);
INSERT INTO contractors_phones VALUES (14, 2, 'Solimo Jan', '603 022 154', 0);
INSERT INTO contractors_phones VALUES (25, 25, 'tel.', '605 154 312', 1);
INSERT INTO contractors_phones VALUES (24, 23, '', '750-123-100', 1);
INSERT INTO contractors_phones VALUES (26, 26, 'tel.', '546 231 546', 1);
INSERT INTO contractors_phones VALUES (27, 28, 'tel.', '501 666 541', 1);
INSERT INTO contractors_phones VALUES (28, 29, 'tel.', '501 621 541', 1);
INSERT INTO contractors_phones VALUES (29, 24, 'tel. ', '123456', 1);
INSERT INTO contractors_phones VALUES (30, 31, 'tel.', '123456789', 1);
INSERT INTO contractors_phones VALUES (31, 37, '', '750-123-100', 1);
INSERT INTO contractors_phones VALUES (34, 57, 'Nowak', '603 021 150', 0);
INSERT INTO contractors_phones VALUES (35, 57, 'Solimo Jan', '603 022 154', 0);
INSERT INTO contractors_phones VALUES (32, 57, 'sekretariat', '62 784-02-14', 1);
INSERT INTO contractors_phones VALUES (33, 57, 'Dział Logistyczny', '62 784-87-63', 0);
INSERT INTO contractors_phones VALUES (36, 65, 'Nowak', '603 021 150', 0);
INSERT INTO contractors_phones VALUES (37, 65, 'Solimo Jan', '603 022 154', 0);
INSERT INTO contractors_phones VALUES (38, 65, 'sekretariat', '62 784-02-14', 1);
INSERT INTO contractors_phones VALUES (39, 65, 'Dział Logistyczny', '62 784-87-63', 0);


--
-- Data for Name: departments; Type: TABLE DATA; Schema: public; Owner: bbraces
--

INSERT INTO departments VALUES (1, 'Łódź', true);
INSERT INTO departments VALUES (2, 'Warszawa', true);


--
-- Data for Name: document_places; Type: TABLE DATA; Schema: public; Owner: bbraces
--

INSERT INTO document_places VALUES (1, 'Łódź');
INSERT INTO document_places VALUES (2, 'Warszawa');
INSERT INTO document_places VALUES (3, 'Łęczyca');
INSERT INTO document_places VALUES (4, 'Mińsk Mazowiecki');


--
-- Data for Name: documents; Type: TABLE DATA; Schema: public; Owner: bbraces
--

INSERT INTO documents VALUES ('PZ', 'Przychód Zewnętrzny', 'PZ/#/YYYY', 'PZ/11/2011', '', 'STORE');
INSERT INTO documents VALUES ('WZ', 'Wydanie Zewnętrzne', 'WZ/#/YYYY', 'WZ/8/2011', 'Przy reklamacji uwzględniamy tylko wady fabryczne', 'STORE');
INSERT INTO documents VALUES ('PW', 'Przychód Wewnętrzny', 'PW/#/YYYY', 'PW/2/2011', '', 'STORE');
INSERT INTO documents VALUES ('RW', 'Rozchód Wewnętrzny', 'RW/#/YYYY', 'RW/2/2011', '', 'STORE');
INSERT INTO documents VALUES ('FK', 'Faktura korygująca', 'FK/#/YYYY', 'FK/9/2011', '', 'SALE');
INSERT INTO documents VALUES ('PRO', 'Faktura proforma', 'PRO/#/YYYY', '', '', 'SALE');
INSERT INTO documents VALUES ('PA', 'Paragon', 'PA/#/YYYY', 'PA/2/2011', '', 'SALE');
INSERT INTO documents VALUES ('PI', 'Paragon imienny', 'PI/#/YYYY', 'PI/4/2011', '', 'SALE');
INSERT INTO documents VALUES ('FM', 'Faktura VAT Marża', 'FM/#/YYYY', 'FM/1/2011', '', 'SALE');
INSERT INTO documents VALUES ('RR', 'Faktura VAT RR', 'RR/#/YYYY', 'RR/3/2011', '', 'PURCHASE');
INSERT INTO documents VALUES ('ZD', 'Zamówienie do dostawcy', 'ZD/#/YYYY', '', '', 'ORDER');
INSERT INTO documents VALUES ('FZK', 'Faktura zakupu korygująca', 'FZK/#/YYYY', '', '', 'PURCHASE');
INSERT INTO documents VALUES ('ZAL', 'Faktura VAT zaliczkowa', 'ZAL/#/YYYY', '', '', 'SALE');
INSERT INTO documents VALUES ('RZL', 'Faktura VAT końcowa', 'RZL/#/YYYY', '', '', 'SALE');
INSERT INTO documents VALUES ('OF', 'Oferta', 'OF/#/YYYY', '', '', 'OTHER');
INSERT INTO documents VALUES ('CN', 'Cennik', 'CN/#/YYYY', '', '', 'OTHER');
INSERT INTO documents VALUES ('KW', 'Kasa Wyda', 'KW/#/2011', '', '', 'CASH');
INSERT INTO documents VALUES ('KP', 'Kasa Przyjmie', 'KP/#/YYYY', 'KP/1/2012', '', 'CASH');
INSERT INTO documents VALUES ('NK', 'Nota Korygująca', 'NK/#/YYYY', 'NK/1/2012', '', 'PURCHASE');
INSERT INTO documents VALUES ('FZ', 'Faktura zakupu', 'FZ/#/YYYY', 'FZ/1/2012', '', 'PURCHASE');
INSERT INTO documents VALUES ('ZK', 'Zamówienie od klienta', 'ZK/#/YYYY', 'ZK/1/2012', '', 'ORDER');
INSERT INTO documents VALUES ('FMP', 'Faktura VAT-MP', 'FMP/#/YYYY', 'FMP/4/2012', 'Dziękujemy za zakupy. Zapraszamy ponownie...', 'SALE');
INSERT INTO documents VALUES ('FV', 'Faktura VAT', 'FV/#/YYYY', 'FV/8/2012', 'Dziękujemy za zakupy. Zapraszamy ponownie...', 'SALE');


--
-- Data for Name: documents_family; Type: TABLE DATA; Schema: public; Owner: bbraces
--

INSERT INTO documents_family VALUES ('SALE', 'Dokumenty sprzedaży');
INSERT INTO documents_family VALUES ('STORE', 'Dokumenty magazynowe');
INSERT INTO documents_family VALUES ('OTHER', 'Pozostałe dokumenty');
INSERT INTO documents_family VALUES ('PURCHASE', 'Dokumenty zakupu');
INSERT INTO documents_family VALUES ('ORDER', 'Zamówienia');
INSERT INTO documents_family VALUES ('CASH', 'Dokumenty kasowe');


--
-- Data for Name: documents_nk; Type: TABLE DATA; Schema: public; Owner: bbraces
--

INSERT INTO documents_nk VALUES ('NK', 'NK/1/2011', '2011-09-07', 2, 'FV/7/2011', '2011-07-16', 'Solimo Katarzyna 
Gałczyńska 60
64-100 Leszno 
tel. 62 784-87-63
NIP: 834-100-11-07', 'Solimo Katarzyna 
Gałczyńska 60
64-100 Leszno 
tel. 62 784-87-63
NIP: 834-100-11-05', 4, 5, 0, 1, true);
INSERT INTO documents_nk VALUES ('NK', 'NK/2/2011', '2011-09-08', 3, 'FV/8/2011', '2011-07-16', 'Kupała Adam 
Warchlewo 666
40-200 Katowice 
NIP: 834521121', 'Kupała Adam
Warchlewo 144
40-200 Katowice 
NIP: 834521121', 1, 6, 0, 1, true);
INSERT INTO documents_nk VALUES ('NK', 'NK/3/2011', '2011-09-09', 37, 'FV/12/2011', '2011-08-29', 'Marczak Stanisław 
Walidacyjna 125
88-100 Kruszwica 
tel. 750-123-100', 'Marczak Stanisław
Walidacyjna 125
88-150 Kruszwica
tel. 750-123-100', 1, 101, 0, 1, true);
INSERT INTO documents_nk VALUES ('NK', 'NK/1/2012', '2012-02-07', 58, 'FV/5/2012', '2012-01-10', 'Skowroński Tymon 
Gliwicka 150
33-100 Tarnów 
', 'Skowroński Tymon 
Gliwicka 153
33-100 Tarnów 
', 1, 108, 8, 1, true);


--
-- Data for Name: documents_positions; Type: TABLE DATA; Schema: public; Owner: bbraces
--

INSERT INTO documents_positions VALUES ('FV/5/2011', 5, 2, 1999.90, 1);
INSERT INTO documents_positions VALUES ('FK/1/2011', 2, 1, 100.00, 2);
INSERT INTO documents_positions VALUES ('FV/8/2011', 3, 1, 1500.00, 1);
INSERT INTO documents_positions VALUES ('PZ/3/2011', 4, 3, 100.00, 1);
INSERT INTO documents_positions VALUES ('FV/6/2011', 4, 3, 202.44, 1);
INSERT INTO documents_positions VALUES ('PZ/3/2011', 5, 4, 1500.00, 1);
INSERT INTO documents_positions VALUES ('RW/1/2011', 7, 2, 310.00, 1);
INSERT INTO documents_positions VALUES ('FV/8/2011', 8, 10, 243.09, 1);
INSERT INTO documents_positions VALUES ('FV/9/2011', 5, 1, 2099.00, 1);
INSERT INTO documents_positions VALUES ('PZ/6/2011', 5, 10, 1500.00, 1);
INSERT INTO documents_positions VALUES ('PZ/6/2011', 4, 10, 100.00, 1);
INSERT INTO documents_positions VALUES ('PZ/5/2011', 4, 10, 100.00, 1);
INSERT INTO documents_positions VALUES ('PZ/3/2011', 3, 2, 1999.90, 2);
INSERT INTO documents_positions VALUES ('FV/6/2011', 2, 1, 100.00, 2);
INSERT INTO documents_positions VALUES ('FK/1/2011', 4, 2, 202.44, 1);
INSERT INTO documents_positions VALUES ('FV/10/2011', 5, 3, 2099.00, 1);
INSERT INTO documents_positions VALUES ('PZ/11/2011', 5, 10, 2099.00, 1);
INSERT INTO documents_positions VALUES ('FV/11/2011', 7, 3, 316.26, 1);
INSERT INTO documents_positions VALUES ('RW/2/2011', 7, 10, 310.00, 1);
INSERT INTO documents_positions VALUES ('FV/8/2011', 7, 7, 316.26, 1);
INSERT INTO documents_positions VALUES ('PW/1/2011', 2, 2, 857.22, 1);
INSERT INTO documents_positions VALUES ('PW/2/2011', 2, 5, 857.22, 1);
INSERT INTO documents_positions VALUES ('FK/2/2011', 3, 0, 1500.00, 1);
INSERT INTO documents_positions VALUES ('FK/2/2011', 8, 5, 243.09, 1);
INSERT INTO documents_positions VALUES ('FK/2/2011', 7, 7, 316.26, 1);
INSERT INTO documents_positions VALUES ('FV/12/2011', 8, 20, 243.09, 1);
INSERT INTO documents_positions VALUES ('FK/3/2011', 3, 2, 1500.00, 1);
INSERT INTO documents_positions VALUES ('FK/3/2011', 8, 9, 243.09, 5);
INSERT INTO documents_positions VALUES ('FV/13/2011', 3, 5, 1500.00, 1);
INSERT INTO documents_positions VALUES ('FV/13/2011', 1, 1, 1999.90, 1);
INSERT INTO documents_positions VALUES ('ZD/1/2011', 4, 50, 202.44, 1);
INSERT INTO documents_positions VALUES ('PA/1/2011', 8, 3, 243.09, 3);
INSERT INTO documents_positions VALUES ('PA/2/2011', 2, 2, 1219.51, 1);
INSERT INTO documents_positions VALUES ('WZ/2/2011', 8, 3, 243.09, 3);
INSERT INTO documents_positions VALUES ('WZ/3/2011', 7, 5, 316.26, 1);
INSERT INTO documents_positions VALUES ('RR/1/2011', 3, 3, 1500.00, 1);
INSERT INTO documents_positions VALUES ('FV/14/2011', 3, 5, 1500.00, 1);
INSERT INTO documents_positions VALUES ('FMP/1/2011', 5, 3, 2099.00, 1);
INSERT INTO documents_positions VALUES ('FK/4/2011', 4, 3, 202.44, 1);
INSERT INTO documents_positions VALUES ('FK/4/2011', 2, 1, 100.00, 2);
INSERT INTO documents_positions VALUES ('FK/5/2011', 8, 20, 243.09, 1);
INSERT INTO documents_positions VALUES ('FK/6/2011', 8, 19, 243.09, 1);
INSERT INTO documents_positions VALUES ('WZ/4/2011', 8, 4, 243.09, 3);
INSERT INTO documents_positions VALUES ('WZ/4/2011', 5, 2, 2099.00, 1);
INSERT INTO documents_positions VALUES ('PI/1/2011', 2, 4, 1219.51, 1);
INSERT INTO documents_positions VALUES ('WZ/5/2011', 4, 5, 202.44, 1);
INSERT INTO documents_positions VALUES ('WZ/6/2011', 7, 4, 316.26, 1);
INSERT INTO documents_positions VALUES ('WZ/6/2011', 3, 3, 1500.00, 1);
INSERT INTO documents_positions VALUES ('WZ/6/2011', 4, 5, 202.44, 1);
INSERT INTO documents_positions VALUES ('WZ/7/2011', 5, 1, 2099.00, 1);
INSERT INTO documents_positions VALUES ('WZ/7/2011', 7, 1, 316.26, 1);
INSERT INTO documents_positions VALUES ('RR/2/2011', 8, 5, 243.09, 3);
INSERT INTO documents_positions VALUES ('FM/1/2011', 3, 15, 0.00, 1);
INSERT INTO documents_positions VALUES ('FV/15/2011', 8, 3, 243.09, 3);
INSERT INTO documents_positions VALUES ('FV/16/2011', 3, 3, 1500.00, 1);
INSERT INTO documents_positions VALUES ('FV/17/2011', 8, 2, 243.09, 3);
INSERT INTO documents_positions VALUES ('FV/18/2011', 2, 2, 1219.51, 1);
INSERT INTO documents_positions VALUES ('FV/19/2011', 3, 2, 1500.00, 1);
INSERT INTO documents_positions VALUES ('FV/20/2011', 2, 7, 1219.51, 1);
INSERT INTO documents_positions VALUES ('FK/7/2011', 2, 2, 1219.51, 1);
INSERT INTO documents_positions VALUES ('FK/7/2011', 3, 2, 1500.00, 1);
INSERT INTO documents_positions VALUES ('FK/8/2011', 3, 9, 1500.00, 1);
INSERT INTO documents_positions VALUES ('FK/8/2011', 1, 0, 1999.90, 1);
INSERT INTO documents_positions VALUES ('FV/22/2011', 5, 4, 2099.00, 1);
INSERT INTO documents_positions VALUES ('WZ/8/2011', 4, 3, 202.44, 1);
INSERT INTO documents_positions VALUES ('WZ/8/2011', 2, 1, 100.00, 2);
INSERT INTO documents_positions VALUES ('ZK/1/2011', 1, 5, 1999.90, 1);
INSERT INTO documents_positions VALUES ('ZK/1/2011', 3, 3, 1500.00, 1);
INSERT INTO documents_positions VALUES ('FMP/2/2011', 1, 5, 1999.90, 1);
INSERT INTO documents_positions VALUES ('FMP/2/2011', 3, 3, 1500.00, 1);
INSERT INTO documents_positions VALUES ('RR/3/2011', 4, 50, 202.44, 1);
INSERT INTO documents_positions VALUES ('PI/2/2011', 8, 3, 243.09, 3);
INSERT INTO documents_positions VALUES ('PI/3/2011', 5, 5, 2099.00, 1);
INSERT INTO documents_positions VALUES ('PI/4/2011', 5, 1, 2099.00, 1);
INSERT INTO documents_positions VALUES ('ZK/2/2011', 5, 6, 1749.00, 1);
INSERT INTO documents_positions VALUES ('ZK/2/2011', 3, 3, 0.00, 1);
INSERT INTO documents_positions VALUES ('ZK/3/2011', 8, 3, 195.00, 3);
INSERT INTO documents_positions VALUES ('ZK/3/2011', 3, 6, 0.00, 1);
INSERT INTO documents_positions VALUES ('ZK/3/2011', 9, 1, 252.03, 1);
INSERT INTO documents_positions VALUES ('ZK/4/2011', 8, 15, 195.00, 3);
INSERT INTO documents_positions VALUES ('ZK/4/2011', 9, 10, 252.03, 1);
INSERT INTO documents_positions VALUES ('FV/23/2011', 5, 4, 2099.00, 1);
INSERT INTO documents_positions VALUES ('FK/9/2011', 5, 2, 2099.00, 1);
INSERT INTO documents_positions VALUES ('FV/1/2012', 3, 3, 1500.00, 1);
INSERT INTO documents_positions VALUES ('FMP/1/2012', 3, 3, 1500.00, 1);
INSERT INTO documents_positions VALUES ('FMP/2/2012', 4, 9, 202.44, 1);
INSERT INTO documents_positions VALUES ('FV/2/2012', 3, 2, 1500.00, 1);
INSERT INTO documents_positions VALUES ('FMP/3/2012', 9, 1, 316.26, 1);
INSERT INTO documents_positions VALUES ('FV/3/2012', 8, 2, 243.09, 3);
INSERT INTO documents_positions VALUES ('FV/6/2012', 17, 5, 47.15, 1);
INSERT INTO documents_positions VALUES ('FV/20/2011', 3, 5, 1500.00, 1);
INSERT INTO documents_positions VALUES ('FV/7/2012', 8, 2, 243.09, 3);
INSERT INTO documents_positions VALUES ('FV/8/2012', 18, 2, 100.00, 1);


--
-- Data for Name: features; Type: TABLE DATA; Schema: public; Owner: bbraces
--

INSERT INTO features VALUES (1, 'Producent', true);
INSERT INTO features VALUES (2, 'przekątna ekranu', true);
INSERT INTO features VALUES (4, 'wielkość pamięci RAM', true);
INSERT INTO features VALUES (5, 'kontrast', true);
INSERT INTO features VALUES (3, 'procesor', true);


--
-- Data for Name: g_groups_features; Type: TABLE DATA; Schema: public; Owner: bbraces
--

INSERT INTO g_groups_features VALUES (1, 5);
INSERT INTO g_groups_features VALUES (2, 1);
INSERT INTO g_groups_features VALUES (2, 2);
INSERT INTO g_groups_features VALUES (2, 5);
INSERT INTO g_groups_features VALUES (3, 1);
INSERT INTO g_groups_features VALUES (3, 2);
INSERT INTO g_groups_features VALUES (4, 1);
INSERT INTO g_groups_features VALUES (1, 1);
INSERT INTO g_groups_features VALUES (4, 4);


--
-- Data for Name: goods; Type: TABLE DATA; Schema: public; Owner: bbraces
--

INSERT INTO goods VALUES (15, 'VB175T CZARNY', 'Monitor LCD 17"  ASUS VB175T czarny', 1, 1, 1, 1, '', 0, 356.91, 439.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, '', '/home/milczu/Blue Braces/proj/app/img/photos/', 0, true);
INSERT INTO goods VALUES (16, 'TABLET EEE PAD TRANSFORMER TF101 32GB', 'Tablet Eee PAD Transformer TF101 32GB', 1, 1, 1, 1, '', 0, 1413.82, 1739.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, '', '', 0, true);
INSERT INTO goods VALUES (1, '5742G-5463G50MNCC', 'Acer Aspire XLR 5742G-5463G50MNCC HTL', 1, 55, 1, 1, '', 5, 1999.90, 2459.88, 1499.93, 1844.91, 1890.00, 2324.70, 2228.76, 1812.00, '', '/media/DANE/Blue Braces/proj/PigStore-build-desktop/img/photos/foto', 2.60000000000000009, true);
INSERT INTO goods VALUES (18, 'TEST', 'Test', 1, 53, 1, 1, '', 0, 100.00, 123.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, '', '/home/milczu/Blue Braces/proj/app/img/photos/', 0, true);
INSERT INTO goods VALUES (9, 'Drukarka test', 'Drukarka testasdx', 1, 1, 1, 2, '', 1, 316.26, 389.00, 252.03, 310.00, 0.00, 0.00, 0.00, 0.00, 'Opis testowy', '/media/DANE/Blue Braces/proj/PigStore-build-desktop/img/photos/foto', 0, true);
INSERT INTO goods VALUES (13, 'IP2700', 'Canon Pixma iP2700', 1, 1, 1, 1, '', 4, 147.15, 181.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, '', '', 0, true);
INSERT INTO goods VALUES (14, '', 'Głośniki Creative 2.0 SBS A35', 1, 1, 1, 1, '', 0, 38.21, 47.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, '', '', 0, true);
INSERT INTO goods VALUES (2, '22-LG-Flatron-E2260T', '22'''' LG Flatron E2260T-PN (LED)', 1, 55, 1, 1, '', 4, 1219.51, 1500.00, 857.72, 1055.00, 1016.26, 1250.00, 1199.00, 1474.77, '', '/media/DANE/Blue Braces/proj/PigStore-build-desktop/img/photos/22_lg_flatron_e2260t_pn_led_.png', 2.56999999999999984, true);
INSERT INTO goods VALUES (6, 'Name', 'Nazwa', 1, 55, 1, 1, '', 0, 650.41, 800.00, 26.02, 32.00, 12.00, 14.76, 0.00, 0.00, '', '/media/DANE/Blue Braces/proj/PigStore-build-desktop/img/photos/foto', 0, true);
INSERT INTO goods VALUES (4, 'WD-ELEMENTS-PORTABLE', 'WD Elements Portable 500GB USB2.0 Black2', 1, 146, 1, 1, '', 3, 202.44, 249.00, 162.00, 199.26, 194.31, 239.00, 0.00, 0.00, '', 'foto', 0.200000000000000011, true);
INSERT INTO goods VALUES (5, '5742G-5463G50MNCC', 'Acer Aspire GWT 5742G-5463G50MNCC', 1, 200, 1, 1, '', 5, 2099.00, 2581.77, 1749.00, 2151.27, 2031.71, 2499.00, 1869.11, 2299.00, '', 'foto', 2.60000000000000009, true);
INSERT INTO goods VALUES (19, 'DYSK TWARDY SATA II  SAMSUNG 1TB ', 'Dysk twardy SATA II  Samsung 2TB ', 2, 55, 1, 1, '', 0, 324.39, 399.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, '', '/home/milczu/Blue Braces/proj/app/img/photos/', 0, true);
INSERT INTO goods VALUES (17, 'GŁOŚNIKI LOGITECH 20 S120', 'Głośniki Logitech 2.0 S120', 1, 50, 1, 1, '', 2, 47.15, 58.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, '', '/home/milczu/Blue Braces/proj/app/img/photos/', 0, true);
INSERT INTO goods VALUES (23, 'SEAGATE-EXTERNAL-FRE', 'Seagate External FreeAgent GoFlex 500 GB USB 2.0 Black', 1, 20, 1, 1, '', 3, 1500.00, 1845.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, '', '/home/milczu/Blue Braces/proj/app/img/photos/foto', 0.200000000000000011, true);
INSERT INTO goods VALUES (7, 'Drukarka test', 'Drukarka testasd', 1, 0, 1, 2, '', 1, 316.26, 389.00, 252.03, 310.00, 0.00, 0.00, 0.00, 0.00, 'Opis testowy', '/media/DANE/Blue Braces/proj/PigStore-build-desktop/img/photos/foto', 0, false);
INSERT INTO goods VALUES (3, 'SEAGATE-EXTERNAL-FRE', 'Seagate External FreeAgent GoFlex 500 GB USB 2.0 Black', 1, 0, 1, 1, '', 3, 1500.00, 1845.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, '.', '/media/DANE/Blue Braces/proj/PigStore-build-desktop/img/photos/foto', 0.149999999999999994, false);
INSERT INTO goods VALUES (8, 'HP LASERJET P1102', 'HP LaserJet P1102', 1, 18, 3, 3, '', 2, 243.09, 255.24, 195.00, 204.75, 0.00, 0.00, 0.00, 0.00, 'Obsługiwane systemy operacyjne: Microsoft Windows 2003 Server, Microsoft Windows 2008 Server, Microsoft Windows XP, Microsoft Windows Vista, Microsoft Windows 7, Mac OS Xv10.4.0 lub nowszy, Pojemność tac odbiorczych papieru: 100 szt.', '/media/DANE/Blue Braces/proj/PigStore-build-desktop/img/photos/', 1, true);


--
-- Data for Name: goods_future_values; Type: TABLE DATA; Schema: public; Owner: bbraces
--

INSERT INTO goods_future_values VALUES (34, 1, 4, '3 GB');
INSERT INTO goods_future_values VALUES (33, 1, 3, 'Intel® Core™ i5');
INSERT INTO goods_future_values VALUES (32, 1, 2, '15.6 cali');
INSERT INTO goods_future_values VALUES (31, 1, 1, 'Acer');
INSERT INTO goods_future_values VALUES (28, 2, 1, 'HP');
INSERT INTO goods_future_values VALUES (30, 8, 2, '15\"');


--
-- Data for Name: goods_groups; Type: TABLE DATA; Schema: public; Owner: bbraces
--

INSERT INTO goods_groups VALUES (1, 'Inne', true);
INSERT INTO goods_groups VALUES (3, 'Dyski twarde', true);
INSERT INTO goods_groups VALUES (4, 'Drukarki', true);
INSERT INTO goods_groups VALUES (5, 'Notebooki', true);
INSERT INTO goods_groups VALUES (2, 'Monitory', true);


--
-- Data for Name: linked_documents; Type: TABLE DATA; Schema: public; Owner: bbraces
--

INSERT INTO linked_documents VALUES ('FV/6/2011', 'FK/1/2011');
INSERT INTO linked_documents VALUES ('FV/6/2011', 'KP/1/2011');
INSERT INTO linked_documents VALUES ('FV/6/2011', 'WZ/1/2011');
INSERT INTO linked_documents VALUES ('FV/8/2011', 'FK/2/2011');
INSERT INTO linked_documents VALUES ('FV/12/2011', 'FK/6/2011');
INSERT INTO linked_documents VALUES ('FV/8/2011', 'FK/3/2011');
INSERT INTO linked_documents VALUES ('FV/20/2011', 'FK/7/2011');
INSERT INTO linked_documents VALUES ('FV/6/2011', 'FK/4/2011');
INSERT INTO linked_documents VALUES ('FV/12/2011', 'FK/5/2011');
INSERT INTO linked_documents VALUES ('FV/6/2011', 'WZ/4/2011');
INSERT INTO linked_documents VALUES ('FV/12/2011', 'WZ/5/2011');
INSERT INTO linked_documents VALUES ('FV/11/2011', 'WZ/6/2011');
INSERT INTO linked_documents VALUES ('FV/9/2011', 'WZ/7/2011');
INSERT INTO linked_documents VALUES ('FV/13/2011', 'FK/8/2011');
INSERT INTO linked_documents VALUES ('FV/23/2011', 'FK/9/2011');
INSERT INTO linked_documents VALUES ('FV/6/2011', 'FK/1/2011');
INSERT INTO linked_documents VALUES ('FV/6/2011', 'KP/1/2011');
INSERT INTO linked_documents VALUES ('FV/6/2011', 'WZ/1/2011');
INSERT INTO linked_documents VALUES ('FV/8/2011', 'FK/2/2011');
INSERT INTO linked_documents VALUES ('FV/12/2011', 'FK/6/2011');
INSERT INTO linked_documents VALUES ('FV/8/2011', 'FK/3/2011');
INSERT INTO linked_documents VALUES ('FV/20/2011', 'FK/7/2011');
INSERT INTO linked_documents VALUES ('FV/6/2011', 'FK/4/2011');
INSERT INTO linked_documents VALUES ('FV/12/2011', 'FK/5/2011');
INSERT INTO linked_documents VALUES ('FV/6/2011', 'WZ/4/2011');
INSERT INTO linked_documents VALUES ('FV/12/2011', 'WZ/5/2011');
INSERT INTO linked_documents VALUES ('FV/11/2011', 'WZ/6/2011');
INSERT INTO linked_documents VALUES ('FV/9/2011', 'WZ/7/2011');
INSERT INTO linked_documents VALUES ('FV/13/2011', 'FK/8/2011');
INSERT INTO linked_documents VALUES ('FV/23/2011', 'FK/9/2011');
INSERT INTO linked_documents VALUES ('FV/12/2011', 'NK/3/2011');
INSERT INTO linked_documents VALUES ('FV/12/2011', 'NK/3/2011');
INSERT INTO linked_documents VALUES ('FV/5/2012', 'NK/1/2012');


--
-- Data for Name: means_of_transport; Type: TABLE DATA; Schema: public; Owner: bbraces
--

INSERT INTO means_of_transport VALUES (2, 'Firma kurierska', true);
INSERT INTO means_of_transport VALUES (3, 'Inne', true);


--
-- Data for Name: methods_of_payment; Type: TABLE DATA; Schema: public; Owner: bbraces
--

INSERT INTO methods_of_payment VALUES (1, 'Gotówka', 0, true);
INSERT INTO methods_of_payment VALUES (2, 'Przelew', 14, true);
INSERT INTO methods_of_payment VALUES (3, 'Płacę z allegro', 0, true);


--
-- Data for Name: orders; Type: TABLE DATA; Schema: public; Owner: bbraces
--

INSERT INTO orders VALUES ('ZD', 'ZD/1/2011', 6, 1, '2011-10-10', '2011-10-10', 12450.00, 0.00, 0, 0, 0, 1, true);
INSERT INTO orders VALUES ('ZK', 'ZK/1/2011', 21, 1, '2011-12-07', '2011-12-07', 17834.40, 0.00, 0, 0, 1, 1, true);
INSERT INTO orders VALUES ('ZK', 'ZK/3/2011', 27, 1, '2011-12-23', '2011-12-31', 924.25, 0.00, 0, 0, 0, 1, true);
INSERT INTO orders VALUES ('ZK', 'ZK/4/2011', 25, 1, '2011-12-23', '2011-12-23', 6171.22, 0.00, 1, 1, 0, 1, true);
INSERT INTO orders VALUES ('ZK', 'ZK/2/2011', 39, 1, '2011-12-23', '2012-01-31', 12907.60, 0.00, 0, 0, 0, 1, false);
INSERT INTO orders VALUES ('ZK', 'ZK/1/2012', 57, 1, '2012-02-07', '2012-02-07', 1992.01, 1.00, 0, 0, 1, 1, true);


--
-- Data for Name: people; Type: TABLE DATA; Schema: public; Owner: bbraces
--

INSERT INTO people VALUES (1, 'Michał Pietrzak');
INSERT INTO people VALUES (2, 'Konrad Marczak');
INSERT INTO people VALUES (3, 'Grzegorz Mularski');
INSERT INTO people VALUES (4, 'Paweł Rolewski');
INSERT INTO people VALUES (5, 'Solimo Katarzyna');
INSERT INTO people VALUES (6, 'Kupała Adam');
INSERT INTO people VALUES (7, 'Filip Kozakiewicz');
INSERT INTO people VALUES (8, 'Milczarek Bartosz');
INSERT INTO people VALUES (9, 'Pasikonik Mariusz');
INSERT INTO people VALUES (10, 'Krzemiński Daniel');
INSERT INTO people VALUES (11, 'Mariusz Kobiela');
INSERT INTO people VALUES (12, 'Marek Pietrzak');
INSERT INTO people VALUES (13, 'Konrad Mazur');
INSERT INTO people VALUES (14, 'Budzyń Tomasz');
INSERT INTO people VALUES (101, 'Marczak Stanisław');
INSERT INTO people VALUES (102, 'Michaniuk Adam');
INSERT INTO people VALUES (103, 'Miziołek Hak');
INSERT INTO people VALUES (104, 'Krynicki Tadeusz');
INSERT INTO people VALUES (105, 'Miziołek Franciszek');
INSERT INTO people VALUES (106, 'Michaniuk Anna');
INSERT INTO people VALUES (107, 'Wachowska Katarzyna');
INSERT INTO people VALUES (108, 'Skowroński Tymon');


--
-- Data for Name: purchase_documents; Type: TABLE DATA; Schema: public; Owner: bbraces
--

INSERT INTO purchase_documents VALUES ('RR', 'RR/2/2011', 37, 1, 1, '2011-10-31', '2011-10-31', '2011-10-31', 1276.22, 0.00, '', '', 0, 0, true, true, 1, true);
INSERT INTO purchase_documents VALUES ('RR', 'RR/1/2011', 7, 1, 1, '2011-10-13', '2011-10-13', '2011-10-13', 5535.00, 6.00, '', '', 0, 0, true, true, 1, false);
INSERT INTO purchase_documents VALUES ('RR', 'RR/3/2011', 39, 2, 1, '2011-12-16', '2011-12-16', '2011-12-30', 12450.10, 0.00, 'ZD/1/2011', '', 1, 1, true, true, 1, true);
INSERT INTO purchase_documents VALUES ('FZ', 'FZ/1/2012', 6, 1, 1, '2012-02-07', '2012-02-07', '2012-02-07', 12450.10, 0.00, 'ZD/1/2011', '', 0, 0, true, true, 1, true);


--
-- Data for Name: sale_documents; Type: TABLE DATA; Schema: public; Owner: bbraces
--

INSERT INTO sale_documents VALUES ('FV', 'FV/6/2011', 3, 1, 1, '2011-07-16', '2011-07-16', '2011-07-16', 855.00, 0.00, 2.50, '', 6, 1, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FV', 'FV/7/2011', 2, 1, 1, '2011-07-16', '2011-07-16', '2011-07-16', 1700.00, 0.00, 0.00, '', 5, 1, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FV', 'FV/8/2011', 3, 1, 2, '2011-07-16', '2011-07-16', '2011-07-16', 7558.01, 0.00, 1.00, '', 6, 1, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FV', 'FV/9/2011', 3, 1, 2, '2011-07-16', '2011-07-16', '2011-07-16', 2581.77, 0.00, 1.00, '', 8, 1, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FK', 'FK/1/2011', 3, 1, 2, '2011-08-12', '2011-07-16', '2011-07-16', 606.00, 0.00, 1.00, '', 8, 1, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FV', 'FV/10/2011', 17, 1, 1, '2011-08-18', '2011-08-18', '2011-08-18', 7745.31, 0.00, 1.00, '', 14, 1, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FV', 'FV/11/2011', 3, 1, 1, '2011-08-18', '2011-08-18', '2011-08-18', 1167.00, 0.00, 12.00, '', 6, 1, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FK', 'FK/2/2011', 3, 1, 1, '2011-08-29', '2011-07-16', '2011-07-16', 4218.00, 0.00, 1.00, '', 6, 1, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FV', 'FV/12/2011', 23, 1, 1, '2011-08-29', '2011-08-29', '2011-08-29', 5980.01, 0.00, 0.00, '', 0, 0, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FK', 'FK/3/2011', 3, 1, 1, '2011-09-22', '2011-07-16', '2011-07-16', 5877.81, 0.00, 1.00, '', 6, 1, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FV', 'FV/13/2011', 2, 1, 1, '2011-09-30', '2011-09-30', '2011-09-30', 11684.90, 0.00, 10.00, '', 5, 0, true, true, 1, true);
INSERT INTO sale_documents VALUES ('PA', 'PA/1/2011', 0, 0, 1, '2011-10-10', '2011-10-10', '2011-10-10', 765.73, 0.00, 0.00, '', 0, 0, true, true, 1, true);
INSERT INTO sale_documents VALUES ('PA', 'PA/2/2011', 0, 0, 1, '2011-10-10', '2011-10-10', '2011-10-10', 2999.99, 0.00, 0.00, '', 0, 0, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FMP', 'FMP/1/2011', 35, 1, 1, '2011-10-13', '2011-10-13', '2011-10-13', 7745.31, 0.00, 1.00, '', 0, 0, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FK', 'FK/4/2011', 36, 1, 1, '2011-10-13', '2011-07-16', '2011-07-16', 855.00, 0.00, 2.50, '', 6, 1, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FK', 'FK/5/2011', 37, 1, 1, '2011-10-13', '2011-08-29', '2011-08-29', 5980.01, 0.00, 0.00, '', 101, 0, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FK', 'FK/6/2011', 37, 1, 1, '2011-10-17', '2011-08-29', '2011-08-29', 5681.01, 0.00, 0.00, '', 101, 0, true, true, 1, true);
INSERT INTO sale_documents VALUES ('PI', 'PI/1/2011', 27, 1, 1, '2011-10-23', '2011-10-23', '2011-10-23', 5999.99, 0.00, 0.00, '', 0, 0, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FM', 'FM/1/2011', 21, 1, 1, '2011-10-31', '2011-10-31', '2011-10-31', 22500.00, 0.00, 0.00, '', 0, 0, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FV', 'FV/16/2011', 34, 1, 1, '2011-12-03', '2011-12-03', '2011-12-03', 5535.00, 0.00, 0.00, '', 0, 0, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FV', 'FV/17/2011', 30, 1, 1, '2011-12-03', '2011-12-03', '2011-12-03', 510.49, 0.00, 0.00, '', 0, 0, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FV', 'FV/18/2011', 32, 1, 1, '2011-12-03', '2011-12-03', '2011-12-03', 2999.99, 0.00, 0.00, '', 0, 0, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FV', 'FV/19/2011', 34, 1, 1, '2011-12-03', '2011-12-03', '2011-12-03', 3690.00, 0.00, 0.00, '', 0, 0, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FK', 'FK/7/2011', 30, 1, 1, '2011-12-04', '2011-12-03', '2011-12-03', 6689.99, 0.00, 0.00, '', 105, 0, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FK', 'FK/8/2011', 32, 1, 1, '2011-12-04', '2011-09-30', '2011-09-30', 16605.00, 0.00, 10.00, '', 5, 0, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FV', 'FV/22/2011', 27, 1, 1, '2011-12-04', '2011-12-04', '2011-12-04', 10327.10, 0.00, 0.00, ' ', 0, 0, true, true, 1, true);
INSERT INTO sale_documents VALUES ('PI', 'PI/2/2011', 32, 1, 1, '2011-12-22', '2011-12-22', '2011-12-22', 765.73, 0.00, 0.00, '', 0, 0, true, true, 1, true);
INSERT INTO sale_documents VALUES ('PI', 'PI/3/2011', 27, 1, 1, '2011-12-22', '2011-12-22', '2011-12-22', 12908.80, 0.00, 0.00, '', 0, 0, true, true, 1, true);
INSERT INTO sale_documents VALUES ('PI', 'PI/4/2011', 2, 1, 1, '2011-12-22', '2011-12-22', '2011-12-22', 2581.77, 0.00, 1.00, '', 0, 0, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FV', 'FV/23/2011', 30, 1, 1, '2011-12-23', '2011-12-23', '2011-12-23', 10327.10, 0.00, 0.00, '', 0, 0, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FK', 'FK/9/2011', 30, 1, 1, '2011-12-23', '2011-12-23', '2011-12-23', 5163.54, 0.00, 0.00, '', 105, 0, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FV', 'FV/1/2012', 27, 1, 1, '2012-01-03', '2012-01-03', '2012-01-03', 5535.00, 0.00, 0.00, '', 0, 0, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FMP', 'FMP/2/2012', 30, 1, 1, '2012-01-03', '2012-01-03', '2012-01-03', 2241.01, 0.00, 0.00, '', 0, 0, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FV', 'FV/14/2011', 33, 1, 1, '2011-10-13', '2011-10-13', '2011-10-13', 9225.00, 0.00, 1.00, '', 0, 0, false, true, 1, true);
INSERT INTO sale_documents VALUES ('FV', 'FV/15/2011', 21, 1, 1, '2011-12-03', '2011-12-03', '2011-12-03', 765.73, 0.00, 0.00, '', 0, 0, false, true, 1, true);
INSERT INTO sale_documents VALUES ('FMP', 'FMP/2/2011', 21, 2, 1, '2011-12-16', '2011-12-16', '2012-01-06', 17834.40, 0.00, 0.00, 'ZK/1/2011', 1, 1, false, false, 1, true);
INSERT INTO sale_documents VALUES ('FV', 'FV/5/2011', 1, 2, 1, '2011-05-17', '2011-05-17', '2011-05-31', 4919.75, 0.00, 2.00, '', 7, 1, true, true, 1, false);
INSERT INTO sale_documents VALUES ('FMP', 'FMP/1/2012', 37, 1, 1, '2012-01-03', '2012-01-03', '2012-01-03', 5535.00, 0.00, 0.00, '', 0, 0, true, true, 1, false);
INSERT INTO sale_documents VALUES ('FV', 'FV/2/2012', 39, 1, 1, '2012-01-05', '2012-01-05', '2012-01-05', 3690.00, 0.00, 0.00, '', 0, 0, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FMP', 'FMP/3/2012', 54, 3, 1, '2012-01-05', '2012-01-05', '2012-01-05', 389.00, 0.00, 0.00, '', 0, 0, true, false, 1, true);
INSERT INTO sale_documents VALUES ('FV', 'FV/3/2012', 54, 1, 1, '2012-01-06', '2012-01-06', '2012-01-06', 510.49, 0.00, 0.00, '', 107, 0, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FV', 'FV/20/2011', 30, 1, 1, '2011-12-03', '2011-12-03', '2011-12-03', 19725.00, 0.00, 0.00, '', 0, 0, false, true, 1, true);
INSERT INTO sale_documents VALUES ('FMP', 'FMP/4/2012', 63, 1, 1, '2012-02-07', '2012-02-07', '2012-02-07', 1020.98, 0.00, 0.00, '', 0, 0, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FV', 'FV/5/2012', 58, 1, 1, '2012-01-10', '2012-01-10', '2012-01-10', 771949.00, 0.00, 0.00, '', 0, 0, true, true, 1, false);
INSERT INTO sale_documents VALUES ('FV', 'FV/4/2012', 60, 1, 1, '2012-01-09', '2012-01-09', '2012-01-09', 255.24, 0.00, 0.00, '', 0, 0, true, true, 1, false);
INSERT INTO sale_documents VALUES ('FV', 'FV/6/2012', 40, 1, 1, '2012-02-15', '2012-02-15', '2012-02-15', 289.97, 0.00, 0.00, '', 0, 0, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FV', 'FV/7/2012', 65, 1, 1, '2012-02-24', '2012-02-24', '2012-02-24', 510.49, 0.00, 1.00, '', 0, 0, true, true, 1, true);
INSERT INTO sale_documents VALUES ('FV', 'FV/8/2012', 65, 1, 1, '2012-02-24', '2012-02-24', '2012-02-24', 246.00, 0.00, 1.00, '', 0, 0, true, true, 1, true);


--
-- Data for Name: sources_of_mem; Type: TABLE DATA; Schema: public; Owner: bbraces
--

INSERT INTO sources_of_mem VALUES (1, 'BRAK', true);
INSERT INTO sources_of_mem VALUES (2, 'Przedstawiciel handlowy', true);
INSERT INTO sources_of_mem VALUES (3, 'Strona internetowa', true);
INSERT INTO sources_of_mem VALUES (4, 'Program partnerski', false);


--
-- Data for Name: store_documents; Type: TABLE DATA; Schema: public; Owner: bbraces
--

INSERT INTO store_documents VALUES ('PZ', 'PZ/3/2011', 3, 1, '2011-07-22', '2011-07-22', 1200.00, 6, 1, 0, 2, 0, '', true, 1, true);
INSERT INTO store_documents VALUES ('PZ', 'PZ/4/2011', 2, 1, '2011-07-23', '2011-07-23', 950.00, 5, 1, 0, 1, 0, '', true, 1, true);
INSERT INTO store_documents VALUES ('PZ', 'PZ/5/2011', 3, 1, '2011-07-25', '2011-07-25', 1200.00, 5, 1, 0, 2, 0, '', true, 1, true);
INSERT INTO store_documents VALUES ('PZ', 'PZ/6/2011', 3, 1, '2011-07-25', '2011-07-25', 1200.00, 6, 1, 0, 1, 0, '', true, 1, true);
INSERT INTO store_documents VALUES ('PZ', 'PZ/7/2011', 1, 1, '2011-07-28', '2011-07-28', 104950.00, 4, 1, 0, 1, 0, '', true, 1, true);
INSERT INTO store_documents VALUES ('PZ', 'PZ/8/2011', 1, 1, '2011-08-05', '2011-08-05', 14585.40, 13, 12, 0, 2, 0, '', true, 1, true);
INSERT INTO store_documents VALUES ('PZ', 'PZ/9/2011', 1, 1, '2011-08-11', '2011-08-11', 1000.00, 6, 1, 0, 1, 0, '', true, 1, true);
INSERT INTO store_documents VALUES ('PZ', 'PZ/10/2011', 1, 1, '2011-08-11', '2011-08-11', 1000.00, 6, 1, 0, 1, 0, '', true, 1, true);
INSERT INTO store_documents VALUES ('WZ', 'WZ/1/2011', 3, 1, '2011-07-16', '2011-07-16', 855.00, 6, 1, 0, 2, 0, '', true, 1, true);
INSERT INTO store_documents VALUES ('PZ', 'PZ/11/2011', 3, 1, '2011-08-18', '2011-08-18', 20990.00, 1, 1, 0, 2, 0, '', true, 1, true);
INSERT INTO store_documents VALUES ('RW', 'RW/1/2011', 0, 1, '2011-08-25', NULL, 620.00, 0, 1, 2, 0, 0, '', true, 1, true);
INSERT INTO store_documents VALUES ('RW', 'RW/2/2011', 0, 1, '2011-08-25', NULL, 3100.00, 0, 1, 1, 0, 0, '', true, 1, true);
INSERT INTO store_documents VALUES ('PW', 'PW/1/2011', 0, 1, '2011-08-25', NULL, 2100.00, 0, 1, 1, 0, 0, '', true, 1, true);
INSERT INTO store_documents VALUES ('PW', 'PW/2/2011', 0, 1, '2011-08-25', NULL, 5275.00, 0, 1, 1, 0, 0, '', true, 1, true);
INSERT INTO store_documents VALUES ('WZ', 'WZ/2/2011', 7, 1, '2011-10-13', NULL, 729.27, 0, 0, 0, 2, 0, '', true, 1, true);
INSERT INTO store_documents VALUES ('WZ', 'WZ/3/2011', 6, 1, '2011-10-13', '2011-10-31', 1581.30, 0, 0, 0, 3, 2, '', true, 1, true);
INSERT INTO store_documents VALUES ('WZ', 'WZ/4/2011', 34, 1, '2011-10-23', '2011-10-31', 5170.36, 0, 0, 0, 2, 0, '1234', true, 1, true);
INSERT INTO store_documents VALUES ('WZ', 'WZ/5/2011', 30, 1, '2011-10-23', '2011-10-23', 1012.20, 0, 0, 0, 2, 0, '', true, 1, true);
INSERT INTO store_documents VALUES ('WZ', 'WZ/6/2011', 3, 1, '2011-10-31', '2011-10-31', 6777.24, 0, 0, 0, 2, 0, '', true, 1, true);
INSERT INTO store_documents VALUES ('WZ', 'WZ/7/2011', 3, 1, '2011-10-31', '2011-10-31', 2415.26, 0, 8, 0, 3, 2, '', true, 1, true);
INSERT INTO store_documents VALUES ('WZ', 'WZ/8/2011', 3, 1, '2011-12-04', '2011-12-04', 707.32, 0, 0, 0, 2, 0, '', true, 1, true);


--
-- Data for Name: taxes; Type: TABLE DATA; Schema: public; Owner: bbraces
--

INSERT INTO taxes VALUES (2, 'Stawka obniżona 8%', 8.00, true, true, '8%');
INSERT INTO taxes VALUES (1, 'Stawka podstawowa 23%', 23.00, true, true, '23%');
INSERT INTO taxes VALUES (3, 'Stawka obniżona 5%', 5.00, true, true, '5%');
INSERT INTO taxes VALUES (4, 'Stawka obniżona 0%', 0.00, true, true, '0%');
INSERT INTO taxes VALUES (7, 'Stawka podstawowa 24%', 24.00, false, false, '24%');
INSERT INTO taxes VALUES (5, 'Stawka zw.', 0.00, true, true, 'zw.');
INSERT INTO taxes VALUES (8, 'Stawka obniżona 6.5%', 6.50, false, false, '6.5%');


--
-- Data for Name: units; Type: TABLE DATA; Schema: public; Owner: bbraces
--

INSERT INTO units VALUES (1, 'szt.', 1, true);
INSERT INTO units VALUES (2, 'kg', 3, true);
INSERT INTO units VALUES (3, 'm', 2, true);
INSERT INTO units VALUES (5, 't', 3, false);


--
-- Name: cash_documents_pkey; Type: CONSTRAINT; Schema: public; Owner: bbraces; Tablespace: 
--

ALTER TABLE ONLY cash_documents
    ADD CONSTRAINT cash_documents_pkey PRIMARY KEY (symbol);


--
-- Name: contractors_additional_ids_pkey; Type: CONSTRAINT; Schema: public; Owner: bbraces; Tablespace: 
--

ALTER TABLE ONLY contractors_additional_ids
    ADD CONSTRAINT contractors_additional_ids_pkey PRIMARY KEY (id);


--
-- Name: contractors_groups_pkey; Type: CONSTRAINT; Schema: public; Owner: bbraces; Tablespace: 
--

ALTER TABLE ONLY contractors_groups
    ADD CONSTRAINT contractors_groups_pkey PRIMARY KEY (id_group);


--
-- Name: contractors_phones_pkey; Type: CONSTRAINT; Schema: public; Owner: bbraces; Tablespace: 
--

ALTER TABLE ONLY contractors_phones
    ADD CONSTRAINT contractors_phones_pkey PRIMARY KEY (id_contractors_phone);


--
-- Name: contractors_pkey; Type: CONSTRAINT; Schema: public; Owner: bbraces; Tablespace: 
--

ALTER TABLE ONLY contractors
    ADD CONSTRAINT contractors_pkey PRIMARY KEY (id_contractor);

ALTER TABLE contractors CLUSTER ON contractors_pkey;


--
-- Name: departments_pkey; Type: CONSTRAINT; Schema: public; Owner: bbraces; Tablespace: 
--

ALTER TABLE ONLY departments
    ADD CONSTRAINT departments_pkey PRIMARY KEY (id_department);


--
-- Name: document_places_pkey; Type: CONSTRAINT; Schema: public; Owner: bbraces; Tablespace: 
--

ALTER TABLE ONLY document_places
    ADD CONSTRAINT document_places_pkey PRIMARY KEY (id_place);


--
-- Name: documents_family_pkey; Type: CONSTRAINT; Schema: public; Owner: bbraces; Tablespace: 
--

ALTER TABLE ONLY documents_family
    ADD CONSTRAINT documents_family_pkey PRIMARY KEY (id);


--
-- Name: documents_nk_pkey; Type: CONSTRAINT; Schema: public; Owner: bbraces; Tablespace: 
--

ALTER TABLE ONLY documents_nk
    ADD CONSTRAINT documents_nk_pkey PRIMARY KEY (symbol);


--
-- Name: documents_pkey; Type: CONSTRAINT; Schema: public; Owner: bbraces; Tablespace: 
--

ALTER TABLE ONLY documents
    ADD CONSTRAINT documents_pkey PRIMARY KEY (type);


--
-- Name: features_pkey; Type: CONSTRAINT; Schema: public; Owner: bbraces; Tablespace: 
--

ALTER TABLE ONLY features
    ADD CONSTRAINT features_pkey PRIMARY KEY (id_feature);


--
-- Name: goods_future_values_pkey; Type: CONSTRAINT; Schema: public; Owner: bbraces; Tablespace: 
--

ALTER TABLE ONLY goods_future_values
    ADD CONSTRAINT goods_future_values_pkey PRIMARY KEY (id_goods_future);


--
-- Name: goods_groups_pkey; Type: CONSTRAINT; Schema: public; Owner: bbraces; Tablespace: 
--

ALTER TABLE ONLY goods_groups
    ADD CONSTRAINT goods_groups_pkey PRIMARY KEY (id_group);


--
-- Name: goods_pkey; Type: CONSTRAINT; Schema: public; Owner: bbraces; Tablespace: 
--

ALTER TABLE ONLY goods
    ADD CONSTRAINT goods_pkey PRIMARY KEY (id_good);


--
-- Name: means_of_transport_pkey; Type: CONSTRAINT; Schema: public; Owner: bbraces; Tablespace: 
--

ALTER TABLE ONLY means_of_transport
    ADD CONSTRAINT means_of_transport_pkey PRIMARY KEY (id_transport);


--
-- Name: methods_of_payment_pkey; Type: CONSTRAINT; Schema: public; Owner: bbraces; Tablespace: 
--

ALTER TABLE ONLY methods_of_payment
    ADD CONSTRAINT methods_of_payment_pkey PRIMARY KEY (id_method);


--
-- Name: orders_pkey; Type: CONSTRAINT; Schema: public; Owner: bbraces; Tablespace: 
--

ALTER TABLE ONLY orders
    ADD CONSTRAINT orders_pkey PRIMARY KEY (symbol);


--
-- Name: people_pkey; Type: CONSTRAINT; Schema: public; Owner: bbraces; Tablespace: 
--

ALTER TABLE ONLY people
    ADD CONSTRAINT people_pkey PRIMARY KEY (id);


--
-- Name: purchase_documents_pkey; Type: CONSTRAINT; Schema: public; Owner: bbraces; Tablespace: 
--

ALTER TABLE ONLY purchase_documents
    ADD CONSTRAINT purchase_documents_pkey PRIMARY KEY (symbol);


--
-- Name: sale_documents_pkey; Type: CONSTRAINT; Schema: public; Owner: bbraces; Tablespace: 
--

ALTER TABLE ONLY sale_documents
    ADD CONSTRAINT sale_documents_pkey PRIMARY KEY (symbol);


--
-- Name: sources_of_mem_pkey; Type: CONSTRAINT; Schema: public; Owner: bbraces; Tablespace: 
--

ALTER TABLE ONLY sources_of_mem
    ADD CONSTRAINT sources_of_mem_pkey PRIMARY KEY (id_source);


--
-- Name: store_documents_pkey; Type: CONSTRAINT; Schema: public; Owner: bbraces; Tablespace: 
--

ALTER TABLE ONLY store_documents
    ADD CONSTRAINT store_documents_pkey PRIMARY KEY (symbol);


--
-- Name: taxes_pkey; Type: CONSTRAINT; Schema: public; Owner: bbraces; Tablespace: 
--

ALTER TABLE ONLY taxes
    ADD CONSTRAINT taxes_pkey PRIMARY KEY (id_tax);


--
-- Name: units_pkey; Type: CONSTRAINT; Schema: public; Owner: bbraces; Tablespace: 
--

ALTER TABLE ONLY units
    ADD CONSTRAINT units_pkey PRIMARY KEY (id_unit);


--
-- Name: unique_doc_pos; Type: INDEX; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE UNIQUE INDEX unique_doc_pos ON documents_positions USING btree (document, good);


--
-- Name: unique_goodsgroup_features; Type: INDEX; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE UNIQUE INDEX unique_goodsgroup_features ON g_groups_features USING btree (goods_group, feature);


--
-- Name: unique_type_newId; Type: INDEX; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE UNIQUE INDEX "unique_type_newId" ON cache_history USING btree (type, new);


--
-- Name: unique_type_oldId; Type: INDEX; Schema: public; Owner: bbraces; Tablespace: 
--

CREATE UNIQUE INDEX "unique_type_oldId" ON cache_history USING btree (type, old);


--
-- Name: fk_cash_documents_contractor; Type: FK CONSTRAINT; Schema: public; Owner: bbraces
--

ALTER TABLE ONLY cash_documents
    ADD CONSTRAINT fk_cash_documents_contractor FOREIGN KEY (contractor) REFERENCES contractors(id_contractor) ON DELETE CASCADE;


--
-- Name: fk_cash_documents_recipment; Type: FK CONSTRAINT; Schema: public; Owner: bbraces
--

ALTER TABLE ONLY cash_documents
    ADD CONSTRAINT fk_cash_documents_recipment FOREIGN KEY (receive_person) REFERENCES people(id) ON DELETE CASCADE;


--
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- PostgreSQL database dump complete
--

