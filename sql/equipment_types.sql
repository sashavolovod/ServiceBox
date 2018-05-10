--
-- PostgreSQL database dump
--

-- Dumped from database version 9.1.24
-- Dumped by pg_dump version 9.6.7

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

SET search_path = public, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: equipment_types; Type: TABLE; Schema: public; Owner: texac_admin
--

CREATE TABLE equipment_types (
    equipment_types_id integer NOT NULL,
    equipment_type_name character varying(128) NOT NULL
);


ALTER TABLE equipment_types OWNER TO texac_admin;

--
-- Name: equipment_types_equipment_types_id_seq; Type: SEQUENCE; Schema: public; Owner: texac_admin
--

CREATE SEQUENCE equipment_types_equipment_types_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE equipment_types_equipment_types_id_seq OWNER TO texac_admin;

--
-- Name: equipment_types_equipment_types_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: texac_admin
--

ALTER SEQUENCE equipment_types_equipment_types_id_seq OWNED BY equipment_types.equipment_types_id;


--
-- Name: equipment_types equipment_types_id; Type: DEFAULT; Schema: public; Owner: texac_admin
--

ALTER TABLE ONLY equipment_types ALTER COLUMN equipment_types_id SET DEFAULT nextval('equipment_types_equipment_types_id_seq'::regclass);


--
-- Data for Name: equipment_types; Type: TABLE DATA; Schema: public; Owner: texac_admin
--

COPY equipment_types (equipment_types_id, equipment_type_name) FROM stdin;
1	Токарный
3	Фрезерный
2	Токарный с ЧПУ
4	Горизонтально-расточной
5	Координатно-расточной с ЧПУ
6	Строгальный
7	Ленточно-пильный
8	Заточной
9	Заточной с ЧПУ
10	Плоскошлифовальный
11	Плоскошлифовальный с ЧПУ
12	Круглошлифовальный
13	Внутришлифовальный
14	Бесцентрово-шлифовальный
15	Профилешлифовальный
16	Координатно-шлифовальный
17	Сверлильный
18	Резьбонарезной
19	Раскрыватель штампов
20	Лазерное оборудование
21	Пресс
22	Термическое оборудование
23	Установка охладительная
24	Твердомер
\.


--
-- Name: equipment_types_equipment_types_id_seq; Type: SEQUENCE SET; Schema: public; Owner: texac_admin
--

SELECT pg_catalog.setval('equipment_types_equipment_types_id_seq', 24, true);


--
-- Name: equipment_types equipment_types_pkey; Type: CONSTRAINT; Schema: public; Owner: texac_admin
--

ALTER TABLE ONLY equipment_types
    ADD CONSTRAINT equipment_types_pkey PRIMARY KEY (equipment_types_id);


--
-- PostgreSQL database dump complete
--

